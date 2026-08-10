/* Runtime loader and skeletal renderer for one selected owner-cache fighter. */
#include "game_smash64_assets.h"

#include "game_smash64.h"
#include "foreign_controller.h"
#include "mods/smash64/characters/captain_falcon.h"
#include "mods/smash64/characters/pikachu.h"
#include "voxel_renderer.h"

#include <SDL.h>

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMASH64_BLOB_VERSION_LEGACY 4u
#define SMASH64_BLOB_VERSION_SKINNED 5u
#define SMASH64_BLOB_VERSION_PIKACHU_EFFECTS 6u
#define SMASH64_BLOB_VERSION_PIKACHU_EFFECTS_V2 7u
#define SMASH64_MAX_JOINTS 32u
#define FALCON_JOINT_COUNT 26u
#define FALCON_RENDER_HEIGHT 32.0f
#define PIKACHU_RENDER_HEIGHT 16.0f
#define FALCON_YAW_DEG 88.0f
#define PIKACHU_YAW_DEG 90.0f
#define FALCON_WAIT_GROUNDED_FIRST 37.0f
#define FALCON_WAIT_GROUNDED_SPAN   4.0f
#define FALCON_WAIT_RATE            0.25f
/* BattleShip's fp->joints[] reserves TopN/TransN/XRotN/YRotN at 0..3.
 * The baked DObjDesc skeleton begins at nFTPartsJointCommonStart (4), so
 * source joint 16 is baked model slot 12. */
#define FALCON_PUNCH_EFFECT_JOINT     12u
#define FALCON_PUNCH_EFFECT_FIRST_FRAME 42u
#define FALCON_PUNCH_EFFECT_END_FRAME   55u
#define FALCON_PUNCH_EFFECT_TEXTURES     3u
/* fp->joints[23] is model slot 19 after TopN/TransN/XRotN/YRotN. */
#define FALCON_KICK_EFFECT_JOINT          19u
#define FALCON_KICK_EFFECT_FIRST_FRAME    12u
#define FALCON_KICK_EFFECT_END_FRAME      32u
#define FALCON_KICK_EFFECT_TEXTURES        2u
/* BattleShip's CaptainMainMotion schedules Falcon Dive's generic effect
 * events at frames 0 and 13.  Those effects are shared Smash particles, not
 * Captain-owned texture cards, so the host represents them with the existing
 * one-texel fallback texture rather than baking unrelated assets into the
 * owner blob. */
#define FALCON_DIVE_LAUNCH_FRAME             0u
#define FALCON_DIVE_DASH_FRAME              13u
#define FALCON_DIVE_ATTACK_END_FRAME        45u
#define FALCON_ROOT_TRACK_JOINT        0xFFFFu
#define PIKACHU_EFFECT_TEXTURES_V1      5u
#define PIKACHU_EFFECT_TEXTURES         7u
#define PIKACHU_JOLT_EFFECT_TEXTURES    2u
#define PIKACHU_THUNDER_EFFECT_TEXTURES 3u
#define PIKACHU_THUNDER_SHOCK_TEXTURES  2u

typedef struct FalconAssetJoint {
    int parent;
    float translate[3];
    float rotate[3];
    float scale[3];
    uint32_t first_triangle;
    uint32_t triangle_count;
} FalconAssetJoint;

typedef struct FalconAssetVertex {
    float pos[3];
    float uv[2];
} FalconAssetVertex;

typedef struct FalconAssetTriangle {
    uint16_t joint[3];
    uint16_t texture;
    FalconAssetVertex vertex[3];
} FalconAssetTriangle;

typedef struct FalconAssetTexture {
    uint16_t width;
    uint16_t height;
    uint32_t *pixels;
} FalconAssetTexture;

typedef struct FalconAssetAnimation {
    char name[32];
    float duration;
    uint32_t loop;
    uint32_t first_track;
    uint32_t track_count;
} FalconAssetAnimation;

typedef struct FalconAssetTrack {
    uint16_t joint;
    uint16_t kind;
    uint32_t first_key;
    uint32_t key_count;
} FalconAssetTrack;

typedef struct FalconAssetSegment {
    float frame;
    float duration;
    float value_base;
    float value_target;
    float rate_base;
    float rate_target;
    uint32_t kind;
} FalconAssetSegment;

typedef struct FalconAssetModel {
    FalconAssetJoint *joints;
    FalconAssetTriangle *triangles;
    FalconAssetTexture *textures;
    FalconAssetAnimation *animations;
    FalconAssetTrack *tracks;
    FalconAssetSegment *segments;
    uint32_t joint_count;
    uint32_t triangle_count;
    uint32_t texture_count;
    uint32_t animation_count;
    uint32_t track_count;
    uint32_t segment_count;
    uint32_t punch_effect_texture_first;
    uint32_t punch_effect_texture_count;
    float bounds_min[3];
    float bounds_max[3];
} FalconAssetModel;

typedef struct BlobReader {
    const uint8_t *data;
    size_t size;
    size_t offset;
    int ok;
} BlobReader;

typedef struct Mat4 {
    float m[16];
} Mat4;

static FalconAssetModel s_model;
static int s_load_attempted;
static int s_pikachu_joint11_valid;
static float s_pikachu_joint11_x, s_pikachu_joint11_y;
/* The controller deliberately preserves one action clock across Thunder's
 * start/loop/self-hit phases.  Presentation needs the self-hit-local clock
 * for effects authored at source frame zero. */
static int s_pikachu_thunder_self_hit_active;
static unsigned s_pikachu_thunder_self_hit_start_frame;
static const uint32_t s_fallback_color[1] = { 0xFF3060C8u };

static int active_is_pikachu(void)
{
    const ForeignController *controller = nes_foreign_active();
    return controller && controller->id &&
           strcmp(controller->id, SMASH64_PIKACHU_ID) == 0;
}
static const uint32_t s_dive_dust_color[1] = { 0xFFC07838u };
static const uint32_t s_dive_spark_color[1] = { 0xFFFFD848u };
static const uint32_t s_dive_white_color[1] = { 0xFFFFFFFFu };
static const uint32_t s_pikachu_spark_color[1] = { 0xFFFFF2A6u };
static const uint32_t s_pikachu_dust_color[1] = { 0xFFC89B5Du };

static int env_enabled(const char *name)
{
    const char *value = SDL_getenv(name);
    return value && *value && strcmp(value, "0") != 0;
}

static float env_float(const char *name, float fallback)
{
    const char *value = SDL_getenv(name);
    char *end;
    float parsed;
    if (!value || !*value) return fallback;
    parsed = strtof(value, &end);
    return end != value && isfinite(parsed) ? parsed : fallback;
}

static uint16_t read_u16(BlobReader *reader)
{
    uint16_t value;
    if (!reader->ok || reader->offset > reader->size ||
        2 > reader->size - reader->offset) {
        reader->ok = 0;
        return 0;
    }
    value = (uint16_t)reader->data[reader->offset] |
            ((uint16_t)reader->data[reader->offset + 1] << 8);
    reader->offset += 2;
    return value;
}

static uint32_t read_u32(BlobReader *reader)
{
    uint32_t value;
    if (!reader->ok || reader->offset > reader->size ||
        4 > reader->size - reader->offset) {
        reader->ok = 0;
        return 0;
    }
    value = (uint32_t)reader->data[reader->offset] |
            ((uint32_t)reader->data[reader->offset + 1] << 8) |
            ((uint32_t)reader->data[reader->offset + 2] << 16) |
            ((uint32_t)reader->data[reader->offset + 3] << 24);
    reader->offset += 4;
    return value;
}

static int32_t read_i32(BlobReader *reader)
{
    return (int32_t)read_u32(reader);
}

static float read_f32(BlobReader *reader)
{
    uint32_t bits = read_u32(reader);
    float value = 0.0f;
    memcpy(&value, &bits, sizeof(value));
    return value;
}

static int read_bytes(BlobReader *reader, void *out, size_t count)
{
    if (!reader->ok || reader->offset > reader->size ||
        count > reader->size - reader->offset) {
        reader->ok = 0;
        return 0;
    }
    memcpy(out, reader->data + reader->offset, count);
    reader->offset += count;
    return 1;
}

static void free_model(FalconAssetModel *model)
{
    uint32_t i;
    if (!model) return;
    for (i = 0; i < model->texture_count; ++i)
        free(model->textures[i].pixels);
    free(model->joints);
    free(model->triangles);
    free(model->textures);
    free(model->animations);
    free(model->tracks);
    free(model->segments);
    memset(model, 0, sizeof(*model));
}

static int count_is_safe(uint32_t value, uint32_t maximum)
{
    return value > 0 && value <= maximum;
}

static int range_is_safe(uint32_t first, uint32_t count, uint32_t total)
{
    return first <= total && count <= total - first;
}

static Mat4 mat_identity(void)
{
    Mat4 out;
    int i;
    memset(&out, 0, sizeof(out));
    for (i = 0; i < 4; ++i) out.m[i * 4 + i] = 1.0f;
    return out;
}

static Mat4 mat_mul(Mat4 a, Mat4 b)
{
    Mat4 out;
    int row, col, k;
    for (row = 0; row < 4; ++row) {
        for (col = 0; col < 4; ++col) {
            float sum = 0.0f;
            for (k = 0; k < 4; ++k)
                sum += a.m[row * 4 + k] * b.m[k * 4 + col];
            out.m[row * 4 + col] = sum;
        }
    }
    return out;
}

static Mat4 mat_local(const float translate[3], const float rotate[3],
                      const float scale[3])
{
    Mat4 t = mat_identity();
    Mat4 rx = mat_identity(), ry = mat_identity(), rz = mat_identity();
    Mat4 s = mat_identity();
    float cx = cosf(rotate[0]), sx = sinf(rotate[0]);
    float cy = cosf(rotate[1]), sy = sinf(rotate[1]);
    float cz = cosf(rotate[2]), sz = sinf(rotate[2]);

    t.m[3] = translate[0];
    t.m[7] = translate[1];
    t.m[11] = translate[2];
    rx.m[5] = cx; rx.m[6] = -sx; rx.m[9] = sx; rx.m[10] = cx;
    ry.m[0] = cy; ry.m[2] = sy; ry.m[8] = -sy; ry.m[10] = cy;
    rz.m[0] = cz; rz.m[1] = -sz; rz.m[4] = sz; rz.m[5] = cz;
    s.m[0] = scale[0]; s.m[5] = scale[1]; s.m[10] = scale[2];
    return mat_mul(t, mat_mul(rz, mat_mul(ry, mat_mul(rx, s))));
}

static void mat_point(Mat4 matrix, const float in[3], float out[3])
{
    out[0] = matrix.m[0] * in[0] + matrix.m[1] * in[1] +
             matrix.m[2] * in[2] + matrix.m[3];
    out[1] = matrix.m[4] * in[0] + matrix.m[5] * in[1] +
             matrix.m[6] * in[2] + matrix.m[7];
    out[2] = matrix.m[8] * in[0] + matrix.m[9] * in[1] +
             matrix.m[10] * in[2] + matrix.m[11];
}

static void build_matrices(const FalconAssetModel *model,
                           float pose_translate[SMASH64_MAX_JOINTS][3],
                           float pose_rotate[SMASH64_MAX_JOINTS][3],
                           float pose_scale[SMASH64_MAX_JOINTS][3],
                           Mat4 world[SMASH64_MAX_JOINTS])
{
    uint32_t i;
    for (i = 0; i < model->joint_count; ++i) {
        Mat4 local = mat_local(pose_translate[i], pose_rotate[i], pose_scale[i]);
        int parent = model->joints[i].parent;
        world[i] = parent >= 0 ? mat_mul(world[parent], local) : local;
    }
}

static void compute_world_bounds(const FalconAssetModel *model,
                                 Mat4 world[SMASH64_MAX_JOINTS],
                                 float bounds_min[3], float bounds_max[3])
{
    uint32_t i, v;
    for (i = 0; i < 3; ++i) {
        bounds_min[i] = FLT_MAX;
        bounds_max[i] = -FLT_MAX;
    }
    for (i = 0; i < model->triangle_count; ++i) {
        const FalconAssetTriangle *triangle = &model->triangles[i];
        for (v = 0; v < 3; ++v) {
            float point[3];
            int axis;
            mat_point(world[triangle->joint[v]], triangle->vertex[v].pos,
                      point);
            for (axis = 0; axis < 3; ++axis) {
                if (point[axis] < bounds_min[axis]) bounds_min[axis] = point[axis];
                if (point[axis] > bounds_max[axis]) bounds_max[axis] = point[axis];
            }
        }
    }
}

static void compute_bind_bounds(FalconAssetModel *model)
{
    float t[SMASH64_MAX_JOINTS][3];
    float r[SMASH64_MAX_JOINTS][3];
    float s[SMASH64_MAX_JOINTS][3];
    Mat4 world[SMASH64_MAX_JOINTS];
    uint32_t i;

    for (i = 0; i < model->joint_count; ++i) {
        memcpy(t[i], model->joints[i].translate, sizeof(t[i]));
        memcpy(r[i], model->joints[i].rotate, sizeof(r[i]));
        memcpy(s[i], model->joints[i].scale, sizeof(s[i]));
    }
    build_matrices(model, t, r, s, world);
    compute_world_bounds(model, world, model->bounds_min, model->bounds_max);
}

static int parse_blob(const uint8_t *data, size_t size, FalconAssetModel *model)
{
    static const uint8_t expected_magic[8] = { 'F','L','C','N','6','4','B',0 };
    BlobReader reader;
    uint8_t magic[8];
    uint32_t version, i, j;

    memset(model, 0, sizeof(*model));
    reader.data = data;
    reader.size = size;
    reader.offset = 0;
    reader.ok = 1;
    if (!read_bytes(&reader, magic, sizeof(magic)) ||
        memcmp(magic, expected_magic, sizeof(magic)) != 0)
        return 0;
    version = read_u32(&reader);
    if (version != SMASH64_BLOB_VERSION_LEGACY &&
        version != SMASH64_BLOB_VERSION_SKINNED &&
        version != SMASH64_BLOB_VERSION_PIKACHU_EFFECTS &&
        version != SMASH64_BLOB_VERSION_PIKACHU_EFFECTS_V2)
        return 0;

    model->joint_count = read_u32(&reader);
    model->triangle_count = read_u32(&reader);
    model->texture_count = read_u32(&reader);
    model->animation_count = read_u32(&reader);
    model->track_count = read_u32(&reader);
    model->segment_count = read_u32(&reader);
    model->punch_effect_texture_first = read_u32(&reader);
    model->punch_effect_texture_count = read_u32(&reader);
    if (!model->joint_count || model->joint_count > SMASH64_MAX_JOINTS ||
        !count_is_safe(model->triangle_count, 10000) ||
        !count_is_safe(model->texture_count, 256) ||
        !count_is_safe(model->animation_count, 128) ||
        !count_is_safe(model->track_count, 100000) ||
        !count_is_safe(model->segment_count, 1000000) ||
        (version == SMASH64_BLOB_VERSION_LEGACY &&
         (model->joint_count != FALCON_JOINT_COUNT ||
          model->punch_effect_texture_count !=
              FALCON_PUNCH_EFFECT_TEXTURES ||
          !range_is_safe(model->punch_effect_texture_first,
                         model->punch_effect_texture_count,
                         model->texture_count) ||
          !range_is_safe(model->punch_effect_texture_first +
                             model->punch_effect_texture_count,
                         FALCON_KICK_EFFECT_TEXTURES,
                         model->texture_count))) ||
        (version == SMASH64_BLOB_VERSION_SKINNED &&
         (model->punch_effect_texture_count != 0u ||
          model->punch_effect_texture_first != model->texture_count)) ||
        (version == SMASH64_BLOB_VERSION_PIKACHU_EFFECTS &&
         (model->punch_effect_texture_count != PIKACHU_EFFECT_TEXTURES_V1 ||
          !range_is_safe(model->punch_effect_texture_first,
                         model->punch_effect_texture_count,
                         model->texture_count) ||
          model->punch_effect_texture_first +
                  model->punch_effect_texture_count != model->texture_count)) ||
        (version == SMASH64_BLOB_VERSION_PIKACHU_EFFECTS_V2 &&
         (model->punch_effect_texture_count != PIKACHU_EFFECT_TEXTURES ||
          !range_is_safe(model->punch_effect_texture_first,
                         model->punch_effect_texture_count,
                         model->texture_count) ||
          model->punch_effect_texture_first +
                  model->punch_effect_texture_count != model->texture_count)))
        return 0;

    model->joints = (FalconAssetJoint *)calloc(model->joint_count,
                                               sizeof(*model->joints));
    model->triangles = (FalconAssetTriangle *)calloc(model->triangle_count,
                                                     sizeof(*model->triangles));
    model->textures = (FalconAssetTexture *)calloc(model->texture_count,
                                                   sizeof(*model->textures));
    model->animations = (FalconAssetAnimation *)calloc(model->animation_count,
                                                       sizeof(*model->animations));
    model->tracks = (FalconAssetTrack *)calloc(model->track_count,
                                               sizeof(*model->tracks));
    model->segments = (FalconAssetSegment *)calloc(model->segment_count,
                                                   sizeof(*model->segments));
    if (!model->joints || !model->triangles || !model->textures ||
        !model->animations || !model->tracks || !model->segments)
        goto fail;

    for (i = 0; i < model->joint_count; ++i) {
        FalconAssetJoint *joint = &model->joints[i];
        joint->parent = read_i32(&reader);
        for (j = 0; j < 3; ++j) joint->translate[j] = read_f32(&reader);
        for (j = 0; j < 3; ++j) joint->rotate[j] = read_f32(&reader);
        for (j = 0; j < 3; ++j) joint->scale[j] = read_f32(&reader);
        joint->first_triangle = read_u32(&reader);
        joint->triangle_count = read_u32(&reader);
        if (joint->parent < -1 || joint->parent >= (int)i ||
            !range_is_safe(joint->first_triangle, joint->triangle_count,
                           model->triangle_count))
            reader.ok = 0;
    }
    for (i = 0; i < model->triangle_count; ++i) {
        FalconAssetTriangle *triangle = &model->triangles[i];
        if (version == SMASH64_BLOB_VERSION_LEGACY) {
            triangle->joint[0] = read_u16(&reader);
            triangle->joint[1] = triangle->joint[0];
            triangle->joint[2] = triangle->joint[0];
            triangle->texture = read_u16(&reader);
        } else {
            triangle->joint[0] = read_u16(&reader);
            triangle->joint[1] = read_u16(&reader);
            triangle->joint[2] = read_u16(&reader);
            triangle->texture = read_u16(&reader);
        }
        for (j = 0; j < 3; ++j) {
            uint32_t axis;
            for (axis = 0; axis < 3; ++axis)
                triangle->vertex[j].pos[axis] = read_f32(&reader);
            for (axis = 0; axis < 2; ++axis)
                triangle->vertex[j].uv[axis] = read_f32(&reader);
        }
        if (triangle->joint[0] >= model->joint_count ||
            triangle->joint[1] >= model->joint_count ||
            triangle->joint[2] >= model->joint_count ||
            (triangle->texture != 0xFFFFu &&
             triangle->texture >= model->texture_count))
            reader.ok = 0;
    }
    for (i = 0; i < model->texture_count; ++i) {
        FalconAssetTexture *texture = &model->textures[i];
        uint32_t byte_count;
        uint64_t expected;
        texture->width = read_u16(&reader);
        texture->height = read_u16(&reader);
        byte_count = read_u32(&reader);
        expected = (uint64_t)texture->width * texture->height * 4u;
        if (!reader.ok || !texture->width || !texture->height ||
            texture->width > 4096 || texture->height > 4096 ||
            expected > UINT32_MAX || byte_count != (uint32_t)expected)
            goto fail;
        texture->pixels = (uint32_t *)malloc(byte_count);
        if (!texture->pixels || !read_bytes(&reader, texture->pixels, byte_count))
            goto fail;
    }
    for (i = 0; i < model->animation_count; ++i) {
        FalconAssetAnimation *animation = &model->animations[i];
        if (!read_bytes(&reader, animation->name, sizeof(animation->name)))
            break;
        animation->name[31] = '\0';
        animation->duration = read_f32(&reader);
        animation->loop = read_u32(&reader);
        animation->first_track = read_u32(&reader);
        animation->track_count = read_u32(&reader);
        if (!range_is_safe(animation->first_track, animation->track_count,
                           model->track_count))
            reader.ok = 0;
    }
    for (i = 0; i < model->track_count; ++i) {
        FalconAssetTrack *track = &model->tracks[i];
        track->joint = read_u16(&reader);
        track->kind = read_u16(&reader);
        track->first_key = read_u32(&reader);
        track->key_count = read_u32(&reader);
        if ((track->joint >= model->joint_count &&
             track->joint != FALCON_ROOT_TRACK_JOINT) || track->kind > 8 ||
            !track->key_count ||
            !range_is_safe(track->first_key, track->key_count,
                           model->segment_count))
            reader.ok = 0;
    }
    for (i = 0; i < model->segment_count; ++i) {
        FalconAssetSegment *segment = &model->segments[i];
        segment->frame = read_f32(&reader);
        segment->duration = read_f32(&reader);
        segment->value_base = read_f32(&reader);
        segment->value_target = read_f32(&reader);
        segment->rate_base = read_f32(&reader);
        segment->rate_target = read_f32(&reader);
        segment->kind = read_u32(&reader);
        if (segment->duration < 0.0f || segment->kind > 3u)
            reader.ok = 0;
    }
    if (!reader.ok || reader.offset != reader.size) goto fail;
    compute_bind_bounds(model);
    if (model->bounds_max[1] - model->bounds_min[1] < 1.0f) goto fail;
    return 1;

fail:
    free_model(model);
    return 0;
}

int game_smash64_assets_pikachu_effect_texture(
    unsigned effect, unsigned frame, const unsigned int **pixels,
    int *width, int *height)
{
    uint32_t first, count, index;
    if (pixels) *pixels = NULL;
    if (width) *width = 0;
    if (height) *height = 0;
    if (!active_is_pikachu() || !s_model.textures ||
        s_model.punch_effect_texture_count < PIKACHU_EFFECT_TEXTURES_V1)
        return 0;
    first = s_model.punch_effect_texture_first;
    if (effect == SMASH64_PIKACHU_EFFECT_THUNDER_JOLT) {
        count = PIKACHU_JOLT_EFFECT_TEXTURES;
    } else if (effect == SMASH64_PIKACHU_EFFECT_THUNDER) {
        first += PIKACHU_JOLT_EFFECT_TEXTURES;
        count = PIKACHU_THUNDER_EFFECT_TEXTURES;
    } else if (effect == SMASH64_PIKACHU_EFFECT_THUNDER_SHOCK) {
        if (s_model.punch_effect_texture_count < PIKACHU_EFFECT_TEXTURES)
            return 0;
        first += PIKACHU_JOLT_EFFECT_TEXTURES +
                 PIKACHU_THUNDER_EFFECT_TEXTURES;
        count = PIKACHU_THUNDER_SHOCK_TEXTURES;
    } else {
        return 0;
    }
    index = first + frame % count;
    if (index >= s_model.texture_count || !s_model.textures[index].pixels)
        return 0;
    if (pixels) *pixels = s_model.textures[index].pixels;
    if (width) *width = s_model.textures[index].width;
    if (height) *height = s_model.textures[index].height;
    return 1;
}

int game_smash64_assets_pikachu_joint11_screen(float *x, float *y)
{
    if (!s_pikachu_joint11_valid) return 0;
    if (x) *x = s_pikachu_joint11_x;
    if (y) *y = s_pikachu_joint11_y;
    return 1;
}

static int load_path(const char *path, FalconAssetModel *model)
{
    FILE *file;
    long length;
    uint8_t *data;
    int ok;
#if defined(_MSC_VER)
    file = NULL;
    if (fopen_s(&file, path, "rb") != 0) file = NULL;
#else
    file = fopen(path, "rb");
#endif
    if (!file) return 0;
    if (fseek(file, 0, SEEK_END) != 0 || (length = ftell(file)) <= 0 ||
        fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return 0;
    }
    data = (uint8_t *)malloc((size_t)length);
    if (!data) {
        fclose(file);
        return 0;
    }
    if (fread(data, 1, (size_t)length, file) != (size_t)length) {
        free(data);
        fclose(file);
        return 0;
    }
    fclose(file);
    ok = parse_blob(data, (size_t)length, model);
    free(data);
    if (ok) {
        fprintf(stderr,
                "[Smash64] fighter assets loaded: %u triangles, %u textures, %u animations (%s)\n",
                model->triangle_count, model->texture_count,
                model->animation_count, path);
    }
    return ok;
}

static int ensure_loaded(void)
{
    const char *configured;
    char path[1024];
    char *base;
    size_t len;
    if (s_load_attempted) return s_model.joints != NULL;
    s_load_attempted = 1;

    configured = SDL_getenv("NESRECOMP_SSB64_ASSETS");
    if (configured && *configured) {
        len = strlen(configured);
        if (len >= 4 && strcmp(configured + len - 4, ".bin") == 0) {
            if (load_path(configured, &s_model)) return 1;
        } else {
            snprintf(path, sizeof(path), "%s/falcon_runtime.bin", configured);
            if (load_path(path, &s_model)) return 1;
        }
    }
    if (load_path("assets_ssb64/falcon_runtime.bin", &s_model)) return 1;

    base = SDL_GetBasePath();
    if (base) {
        snprintf(path, sizeof(path), "%sassets_ssb64/falcon_runtime.bin", base);
        if (load_path(path, &s_model)) {
            SDL_free(base);
            return 1;
        }
        snprintf(path, sizeof(path), "%s../../assets_ssb64/falcon_runtime.bin", base);
        if (load_path(path, &s_model)) {
            SDL_free(base);
            return 1;
        }
        SDL_free(base);
    }

    fprintf(stderr,
            "[Smash64] Falcon runtime assets unavailable; using cube fallback\n");
    return 0;
}

int game_smash64_assets_prepare_character_root(const char *root,
                                                const char *controller_id)
{
    char path[1024];
    const char *filename = "falcon_runtime.bin";
    size_t len;
    int written;
    if (!root || !*root) return 0;
    if (controller_id && strcmp(controller_id, SMASH64_PIKACHU_ID) == 0)
        filename = "pikachu_runtime.bin";
    len = strlen(root);
    written = snprintf(path, sizeof(path), "%s%s%s", root,
                       (root[len - 1] == '/' || root[len - 1] == '\\')
                           ? "" : "/",
                       filename);
    if (written < 0 || (size_t)written >= sizeof(path)) return 0;
    free_model(&s_model);
    memset(&s_model, 0, sizeof(s_model));
    s_load_attempted = 1;
    return load_path(path, &s_model);
}

int game_smash64_assets_prepare_root(const char *root)
{
    return game_smash64_assets_prepare_character_root(
        root, SMASH64_CAPTAIN_FALCON_ID);
}

void game_smash64_assets_clear(void)
{
    free_model(&s_model);
    memset(&s_model, 0, sizeof(s_model));
    s_load_attempted = 0;
    s_pikachu_joint11_valid = 0;
    s_pikachu_thunder_self_hit_active = 0;
}

static int pikachu_walk_tier(const ForeignState *state)
{
    double stick_magnitude;
    if (!state || PIKACHU_SOURCE_WALK_MULTIPLIER <= 0.0)
        return 2;
    /* ftCommonWalkGetWalkStatus selects the source motion from stick range.
     * The generic state retains velocity rather than the synthetic NES stick,
     * so invert Pikachu's sourced walk multiplier to recover that range. */
    stick_magnitude = fabs(state->vx) / PIKACHU_SOURCE_WALK_MULTIPLIER;
    if (stick_magnitude >= PIKACHU_SOURCE_WALK_FAST_STICK_MIN)
        return 3;
    if (stick_magnitude >= PIKACHU_SOURCE_WALK_MIDDLE_STICK_MIN)
        return 2;
    return 1;
}

static const char *animation_for_state(const ForeignState *state)
{
    const int move_state = state ? state->state : 0;
    if (active_is_pikachu()) {
        switch (move_state) {
        case PK_GROUND_WAIT: return "Idle";
        case PK_WALK:
            switch (pikachu_walk_tier(state)) {
            case 1: return "Walk1";
            case 3: return "Walk3";
            default: return "Walk2";
            }
        case PK_DASH: return "Dash";
        case PK_RUN: return "Run";
        case PK_RUN_BRAKE: return "RunBrake";
        case PK_TURN_RUN: return "TurnRun";
        case PK_CROUCH: return "Crouch";
        case PK_CROUCH_WAIT: return "CrouchIdle";
        case PK_CROUCH_END: return "CrouchEnd";
        case PK_LANDING: return "LandingAirX";
        case PK_JUMP_GROUND: return "JumpF";
        case PK_JUMP_AERIAL: return "JumpAerialF";
        case PK_AIR_FALL: return "Fall";
        case PK_JAB: return "Jab1";
        case PK_DASH_ATTACK: return "DashAttack";
        case PK_FTILT: return "AttackS3";
        case PK_UTILT: return "AttackHi3";
        case PK_DTILT: return "AttackLw3";
        case PK_NAIR: return "AttackAirN";
        case PK_FAIR: return "AttackAirF";
        case PK_BAIR: return "AttackAirB";
        case PK_UAIR: return "AttackAirHi";
        case PK_DAIR: return "AttackAirD";
        case PK_THUNDER_JOLT_GROUND: return "NeutralSpecialGround";
        case PK_THUNDER_JOLT_AIR: return "NeutralSpecialAir";
        case PK_QUICK_ATTACK_START:
        case PK_QUICK_ATTACK_ZIP1:
        case PK_QUICK_ATTACK_WINDOW:
        case PK_QUICK_ATTACK_ZIP2:
        case PK_QUICK_ATTACK_RECOVERY: return "UpSpecialAirEnd";
        /* Ground Thunder has four distinct ftdata motions.  In particular
         * GettingThundered carries the 0x1644 loop and 0x1668 self-hit
         * submotions; mapping either phase to the airborne end pose loses
         * the authored grounded silhouette. */
        case PK_THUNDER_START: return "DownSpecialStart";
        case PK_THUNDER_LOOP:
        case PK_THUNDER_SELF_HIT: return "GettingThundered";
        default: return "Idle";
        }
    }
    switch (move_state) {
    case FL_WAIT: return "Wait";
    case FL_WALK_SLOW: return "Walk1";
    case FL_WALK_MIDDLE: return "Walk2";
    case FL_WALK_FAST: return "Walk3";
    case FL_DASH: return "Dash";
    case FL_RUN: return "Run";
    case FL_RUN_BRAKE: return "RunBrake";
    case FL_TURN: return "Turn";
    case FL_TURN_RUN: return "TurnRun";
    case FL_KNEEBEND: return "Crouch_kneebend";
    case FL_JUMP_F: return "JumpF";
    case FL_JUMP_B: return "JumpB";
    case FL_JUMP_AERIAL_F: return "JumpAerialF";
    case FL_JUMP_AERIAL_B: return "JumpAerialB";
    case FL_FALL: return "Fall";
    case FL_FALL_AERIAL: return "FallAerial";
    case FL_LANDING_LIGHT:
    case FL_LANDING_HEAVY: return "LandingAirX";
    case FL_JAB: return "Jab1";
    case FL_FTILT: return "AttackS3";
    case FL_ATTACK_AIR_N: return "AttackAirN";
    case FL_ATTACK_AIR_F: return "AttackAirF";
    case FL_ATTACK_AIR_B: return "AttackAirB";
    case FL_ATTACK_AIR_LW: return "AttackAirD";
    case FL_FALCON_PUNCH_GROUND: return "FalconPunchGround";
    case FL_FALCON_PUNCH_AIR: return "FalconPunchAir";
    case FL_FALCON_KICK_GROUND: return "DownSpecial";
    case FL_FALCON_KICK_GROUND_AIR: return "VelocityXDownSpecialAir";
    case FL_FALCON_KICK_LANDING: return "LandingDownSpecial";
    case FL_FALCON_KICK_AIR: return "DownSpecialAir";
    case FL_FALCON_KICK_BOUND: return "FalconDiveEnd1";
    case FL_FALCON_DIVE_GROUND: return "FalconDive";
    case FL_FALCON_DIVE_AIR: return "FalconDiveEnd2";
    case FL_FALCON_DIVE_CATCH: return "CatchingEnemyWhileDiving";
    case FL_FALCON_DIVE_THROW: return "FalconDiveEnd1";
    case FL_FALCON_DIVE_FALL: return "FallSpecial";
    case FL_FALCON_DIVE_LANDING: return "LandingAirX";
    default: return "Wait";
    }
}

static const FalconAssetAnimation *find_animation(const FalconAssetModel *model,
                                                   const char *name)
{
    uint32_t i;
    for (i = 0; i < model->animation_count; ++i) {
        if (strcmp(model->animations[i].name, name) == 0)
            return &model->animations[i];
    }
    return NULL;
}

static float sample_track(const FalconAssetModel *model,
                          const FalconAssetTrack *track, float frame)
{
    const FalconAssetSegment *segments =
        model->segments + track->first_key;
    uint32_t i;
    if (frame <= segments[0].frame) return segments[0].value_base;
    for (i = 0; i < track->key_count; ++i) {
        const FalconAssetSegment *segment = &segments[i];
        float elapsed;
        if (frame < segment->frame) {
            return i ? segments[i - 1].value_target : segment->value_base;
        }
        if (segment->duration <= 0.0f) continue;
        elapsed = frame - segment->frame;
        if (elapsed <= segment->duration) {
            float amount = elapsed / segment->duration;
            if (segment->kind == 1u) {
                return segment->value_base +
                    (segment->value_target - segment->value_base) * amount;
            }
            if (segment->kind == 2u) {
                float amount2 = amount * amount;
                float amount3 = amount2 * amount;
                float h00 = 2.0f * amount3 - 3.0f * amount2 + 1.0f;
                float h10 = amount3 - 2.0f * amount2 + amount;
                float h01 = -2.0f * amount3 + 3.0f * amount2;
                float h11 = amount3 - amount2;
                return h00 * segment->value_base +
                       h10 * segment->duration * segment->rate_base +
                       h01 * segment->value_target +
                       h11 * segment->duration * segment->rate_target;
            }
            if (segment->kind == 3u)
                return elapsed >= segment->duration
                    ? segment->value_target : segment->value_base;
            return segment->value_base;
        }
    }
    return segments[track->key_count - 1].value_target;
}

int game_smash64_assets_root_delta(const char *animation_name, float frame,
                                   float *delta_y, float *delta_z)
{
    const FalconAssetAnimation *animation;
    float previous = frame > 0.0f ? frame - 1.0f : frame;
    float y_now = 0.0f, y_previous = 0.0f;
    float z_now = 0.0f, z_previous = 0.0f;
    int have_y = 0, have_z = 0;
    uint32_t i;

    if (delta_y) *delta_y = 0.0f;
    if (delta_z) *delta_z = 0.0f;
    if (!animation_name || !ensure_loaded()) return 0;
    animation = find_animation(&s_model, animation_name);
    if (!animation) return 0;
    if (frame > animation->duration) frame = animation->duration;
    if (previous > animation->duration) previous = animation->duration;

    for (i = 0; i < animation->track_count; ++i) {
        const FalconAssetTrack *track =
            &s_model.tracks[animation->first_track + i];
        if (track->joint != FALCON_ROOT_TRACK_JOINT) continue;
        if (track->kind == 4u) {
            y_now = sample_track(&s_model, track, frame);
            y_previous = sample_track(&s_model, track, previous);
            have_y = 1;
        } else if (track->kind == 5u) {
            z_now = sample_track(&s_model, track, frame);
            z_previous = sample_track(&s_model, track, previous);
            have_z = 1;
        }
    }
    if (!have_y && !have_z) return 0;
    /* Captain's TopN scale is exactly attr->size = 1.05. Translation values
     * have already been decoded from Figatree's quarter-unit representation
     * by the baker, so this is the only remaining source-space scale. */
    if (delta_y) *delta_y = (y_now - y_previous) * 1.05f;
    if (delta_z) *delta_z = (z_now - z_previous) * 1.05f;
    return 1;
}

static void apply_animation(const FalconAssetModel *model,
                            const FalconAssetAnimation *animation, float frame,
                            float t[SMASH64_MAX_JOINTS][3],
                            float r[SMASH64_MAX_JOINTS][3],
                            float s[SMASH64_MAX_JOINTS][3])
{
    uint32_t i;
    if (!animation) return;
    if (animation->loop && animation->duration > 0.0f)
        frame = fmodf(frame, animation->duration);
    else if (frame > animation->duration)
        frame = animation->duration;

    for (i = 0; i < animation->track_count; ++i) {
        const FalconAssetTrack *track =
            &model->tracks[animation->first_track + i];
        float value = sample_track(model, track, frame);
        if (track->joint == FALCON_ROOT_TRACK_JOINT) continue;
        if (track->kind < 3) r[track->joint][track->kind] = value;
        else if (track->kind < 6) t[track->joint][track->kind - 3] = value;
        else s[track->joint][track->kind - 6] = value;
    }
}

static float presentation_animation_frame(const ForeignState *state)
{
    const char *forced = SDL_getenv("NESRECOMP_FALCON_ANIM_FRAME");
    if (forced && *forced)
        return env_float("NESRECOMP_FALCON_ANIM_FRAME",
                         (float)state->state_frame);
    if (!active_is_pikachu() && state->state == FL_WAIT) {
        const float extent = FALCON_WAIT_GROUNDED_SPAN * 2.0f;
        float phase = fmodf((float)state->state_frame * FALCON_WAIT_RATE,
                            extent);
        if (phase > FALCON_WAIT_GROUNDED_SPAN)
            phase = extent - phase;
        return FALCON_WAIT_GROUNDED_FIRST + phase;
    }
    if (!active_is_pikachu() && state->state == FL_FALCON_DIVE_LANDING)
        return (float)state->state_frame * 0.65f;
    if (active_is_pikachu() && state->state == PK_WALK) {
        /* The cached Figatree timelines end at 45/30/24, while Pikachu's
         * source walk phase lengths are 60/30/30. Preserve the source cycle
         * cadence instead of making the fast clip skate 20% too quickly. */
        switch (pikachu_walk_tier(state)) {
        case 1: return (float)state->state_frame * (45.0f / 60.0f);
        case 3: return (float)state->state_frame * (24.0f / 30.0f);
        default: break;
        }
    }
    return (float)state->state_frame;
}

static NesVoxelMeshVertex render_vertex(const FalconAssetModel *model,
                                        Mat4 matrix,
                                        const FalconAssetVertex *vertex,
                                        const float pose_min[3],
                                        const float pose_max[3],
                                        float center_x, float foot_y,
                                        float facing, float model_scale,
                                        float yaw_rad)
{
    NesVoxelMeshVertex out;
    float point[3];
    float x, y, z, c = cosf(yaw_rad), yaw_sin = sinf(yaw_rad);
    mat_point(matrix, vertex->pos, point);
    (void)model;
    x = point[0] - (pose_min[0] + pose_max[0]) * 0.5f;
    y = point[1] - pose_min[1];
    z = point[2] - (pose_min[2] + pose_max[2]) * 0.5f;
    x *= facing;
    z *= facing;
    out.x = center_x + (x * c - z * yaw_sin) * model_scale;
    out.y = foot_y + y * model_scale;
    out.z = (x * yaw_sin + z * c) * model_scale;
    out.u = vertex->uv[0];
    out.v = vertex->uv[1];
    return out;
}

static NesVoxelMeshVertex render_punch_effect_vertex(
    Mat4 joint_world, float local_y, float local_z, float u, float v,
    const float pose_min[3], const float pose_max[3],
    float center_x, float foot_y, float facing, float source_lr,
    float model_scale, float yaw_rad, float output_scale,
    float effect_scale)
{
    NesVoxelMeshVertex out;
    static const float origin[3] = { 0.0f, 0.0f, 0.0f };
    float point[3];
    float x, y, z;
    float yaw_cos = cosf(yaw_rad), yaw_sin = sinf(yaw_rad);

    /* BattleShip efManagerCaptainFalconPunchMakeEffect attaches the single
     * CaptainSpecial3 quad to Captain runtime joint 16 (baked slot 12) and
     * rotates it by lr * -90
     * degrees to face Smash's fixed side camera. This renderer has already
     * yawed Falcon's authored coordinates 88 degrees into an SMB side view;
     * applying the source billboard turn a second time makes the card edge-on.
     * Project the authentic attachment point first, then express the same
     * 44..212-unit card directly in that side-camera plane. */
    mat_point(joint_world, origin, point);

    x = (point[0] - (pose_min[0] + pose_max[0]) * 0.5f) * facing;
    y = point[1] - pose_min[1];
    z = (point[2] - (pose_min[2] + pose_max[2]) * 0.5f) * facing;
    /* The fighter is normalized to Big Mario's 32-pixel height after its
     * animation bounds are evaluated. Applying that same normalization to
     * this independently-authored effect makes its opaque plume only a few
     * pixels wide. Enlarge around the source quad's hand-side corner (44,
     * 44), preserving the exact joint attachment while keeping the effect
     * readable at NES resolution. */
    local_y = 44.0f + (local_y - 44.0f) * effect_scale;
    local_z = 44.0f + (local_z - 44.0f) * effect_scale;
    out.x = center_x + (x * yaw_cos - z * yaw_sin) * model_scale +
        source_lr * local_z * model_scale;
    out.y = foot_y + (y + local_y) * model_scale;
    /* Pull the alpha billboard fractionally camera-ward so the attached
     * wrist/forearm cannot depth-fight it at the source active pose. */
    out.z = (x * yaw_sin + z * yaw_cos) * model_scale + output_scale;
    out.u = u;
    out.v = v;
    return out;
}

static void draw_falcon_punch_effect(
    const FalconAssetModel *model, const ForeignState *state,
    Mat4 world[SMASH64_MAX_JOINTS], const float pose_min[3],
    const float pose_max[3], float center_x, float foot_y, float facing,
    float model_scale, float yaw_rad, float output_scale)
{
    const FalconAssetTexture *texture;
    NesVoxelMeshVertex vertices[4];
    uint32_t state_frame, texture_index;
    float source_lr;
    float effect_scale;

    if (state->state != FL_FALCON_PUNCH_GROUND &&
        state->state != FL_FALCON_PUNCH_AIR)
        return;
    if (state->state_frame < (double)FALCON_PUNCH_EFFECT_FIRST_FRAME ||
        state->state_frame >= (double)FALCON_PUNCH_EFFECT_END_FRAME)
        return;

    state_frame = (uint32_t)state->state_frame;
    texture_index = model->punch_effect_texture_first +
        (state_frame - FALCON_PUNCH_EFFECT_FIRST_FRAME) %
            model->punch_effect_texture_count;
    texture = &model->textures[texture_index];
    source_lr = state->facing < 0.0f ? -1.0f : 1.0f;
    effect_scale = env_float("NESRECOMP_FALCON_PUNCH_EFFECT_SCALE", 2.0f);
    if (effect_scale < 0.25f) effect_scale = 0.25f;
    if (effect_scale > 4.0f) effect_scale = 4.0f;

    vertices[0] = render_punch_effect_vertex(
        world[FALCON_PUNCH_EFFECT_JOINT], 44.0f, 212.0f, 32.0f, 32.0f,
        pose_min, pose_max, center_x, foot_y, facing, source_lr,
        model_scale, yaw_rad, output_scale, effect_scale);
    vertices[1] = render_punch_effect_vertex(
        world[FALCON_PUNCH_EFFECT_JOINT], 212.0f, 212.0f, 32.0f, 0.0f,
        pose_min, pose_max, center_x, foot_y, facing, source_lr,
        model_scale, yaw_rad, output_scale, effect_scale);
    vertices[2] = render_punch_effect_vertex(
        world[FALCON_PUNCH_EFFECT_JOINT], 212.0f, 44.0f, 0.0f, 0.0f,
        pose_min, pose_max, center_x, foot_y, facing, source_lr,
        model_scale, yaw_rad, output_scale, effect_scale);
    vertices[3] = render_punch_effect_vertex(
        world[FALCON_PUNCH_EFFECT_JOINT], 44.0f, 44.0f, 0.0f, 32.0f,
        pose_min, pose_max, center_x, foot_y, facing, source_lr,
        model_scale, yaw_rad, output_scale, effect_scale);

    nes_voxel_mesh_bind_texture(texture->pixels, texture->width,
                                texture->height, texture->width, 1.0f, 1);
    nes_voxel_mesh_triangle(vertices[3], vertices[2], vertices[1]);
    nes_voxel_mesh_triangle(vertices[0], vertices[3], vertices[1]);
}

static NesVoxelMeshVertex render_kick_effect_vertex(
    Mat4 joint_world, float card_y, float card_z, float u, float v,
    const float pose_min[3], const float pose_max[3],
    float center_x, float foot_y, float facing, float source_lr,
    float model_scale, float yaw_rad, float output_scale, float roll_rad,
    float scale_y, float scale_z, float rotate_x_rad)
{
    static const float origin[3] = { 0.0f, 0.0f, 0.0f };
    NesVoxelMeshVertex out;
    float point[3];
    float x, y, z, base_x, base_y, source_y, source_z;
    float screen_x, screen_y;
    float yaw_cos = cosf(yaw_rad), yaw_sin = sinf(yaw_rad);
    float roll_cos = cosf(roll_rad), roll_sin = sinf(roll_rad);
    float rotate_x_cos = cosf(rotate_x_rad);
    float rotate_x_sin = sinf(rotate_x_rad);

    mat_point(joint_world, origin, point);
    x = (point[0] - (pose_min[0] + pose_max[0]) * 0.5f) * facing;
    y = point[1] - pose_min[1];
    z = (point[2] - (pose_min[2] + pose_max[2]) * 0.5f) * facing;
    base_x = center_x + (x * yaw_cos - z * yaw_sin) * model_scale;
    base_y = foot_y + y * model_scale;

    /* CaptainSpecial2's authored quad lies in source Y/Z (X is zero), from
     * Z=-2 back to Z=-1246. The effect root first turns that card +/-90
     * degrees around Y, making negative Z trail behind the kick, and the
     * direct-air variant then rolls the resulting screen-plane card +/-60
     * degrees around Z. Keeping those source axes matters: treating the card
     * as already-X/Y made one facing disappear offscreen and put the ground
     * flame in front of the boot. */
    card_y *= scale_y;
    card_z *= scale_z;
    source_y = card_y * rotate_x_cos - card_z * rotate_x_sin;
    source_z = card_y * rotate_x_sin + card_z * rotate_x_cos;
    screen_x = source_lr * source_z;
    screen_y = source_y;
    out.x = base_x +
        (screen_x * roll_cos - screen_y * roll_sin) * model_scale;
    out.y = base_y +
        (screen_x * roll_sin + screen_y * roll_cos) * model_scale;
    /* Keep CaptainSpecial2's attached fire card behind the kicking leg.
     * Biasing it cameraward hides Falcon's already-small silhouette. The
     * source card's bright edge is rooted at the boot; its negative-Z end is
     * the tapered trail (preserved by the source U coordinates below). */
    out.z = (x * yaw_sin + z * yaw_cos) * model_scale - output_scale;
    out.u = u;
    out.v = v;
    return out;
}

static void draw_falcon_kick_effect(
    const FalconAssetModel *model, const ForeignState *state,
    Mat4 world[SMASH64_MAX_JOINTS], const float pose_min[3],
    const float pose_max[3], float center_x, float foot_y, float facing,
    float model_scale, float yaw_rad, float output_scale)
{
    const FalconAssetTexture *texture;
    NesVoxelMeshVertex vertices[4];
    uint32_t phase, texture_index;
    float source_lr, roll_rad = 0.0f;
    float effect_scale_y, effect_scale_z, rotate_x_rad;
    static const float scale_y_cycle[4] = { 1.0f, 0.84f, 1.2f, 0.9f };
    static const float scale_z_cycle[4] = { 1.0f, 0.84f, 1.2f, 0.6f };
    static const float rotate_x_degrees[4] = {
        -1.5f, -8.55f, -15.6f, -8.55f
    };

    if (state->state != FL_FALCON_KICK_GROUND &&
        state->state != FL_FALCON_KICK_AIR)
        return;
    if (state->state_frame < (double)FALCON_KICK_EFFECT_FIRST_FRAME ||
        state->state_frame >= (double)FALCON_KICK_EFFECT_END_FRAME)
        return;

    phase = (uint32_t)state->state_frame - FALCON_KICK_EFFECT_FIRST_FRAME;
    texture_index = model->punch_effect_texture_first +
        model->punch_effect_texture_count +
        (phase / 2u) % FALCON_KICK_EFFECT_TEXTURES;
    texture = &model->textures[texture_index];
    source_lr = state->facing < 0.0f ? -1.0f : 1.0f;
    if (state->state == FL_FALCON_KICK_AIR)
        roll_rad = -source_lr *
            env_float("NESRECOMP_FALCON_KICK_AIR_ROLL_DEG", 60.0f) *
            (3.14159265358979323846f / 180.0f);
    /* CaptainSpecial2's loop scales source Y/Z as
     * 1/1 -> .84/.84 -> 1.2/1.2 -> .9/.6 -> 1/1 while RotX travels from
     * -1.5 to -15.6 degrees and back over two-frame cubic commands. At NES
     * cadence we retain the authored endpoints plus their midpoint and,
     * crucially, the non-uniform .9/.6 squash. */
    effect_scale_y = scale_y_cycle[phase % 4u];
    effect_scale_z = scale_z_cycle[phase % 4u];
    rotate_x_rad = rotate_x_degrees[phase % 4u] *
        (3.14159265358979323846f / 180.0f);

    vertices[0] = render_kick_effect_vertex(
        world[FALCON_KICK_EFFECT_JOINT], 467.0f, -2.0f, 48.0f, 48.0f,
        pose_min, pose_max, center_x, foot_y, facing, source_lr,
        model_scale, yaw_rad, output_scale, roll_rad,
        effect_scale_y, effect_scale_z, rotate_x_rad);
    vertices[1] = render_kick_effect_vertex(
        world[FALCON_KICK_EFFECT_JOINT], -467.0f, -2.0f, 48.0f, 0.0f,
        pose_min, pose_max, center_x, foot_y, facing, source_lr,
        model_scale, yaw_rad, output_scale, roll_rad,
        effect_scale_y, effect_scale_z, rotate_x_rad);
    vertices[2] = render_kick_effect_vertex(
        world[FALCON_KICK_EFFECT_JOINT], -467.0f, -1246.0f, 0.0f, 0.0f,
        pose_min, pose_max, center_x, foot_y, facing, source_lr,
        model_scale, yaw_rad, output_scale, roll_rad,
        effect_scale_y, effect_scale_z, rotate_x_rad);
    vertices[3] = render_kick_effect_vertex(
        world[FALCON_KICK_EFFECT_JOINT], 467.0f, -1246.0f, 0.0f, 48.0f,
        pose_min, pose_max, center_x, foot_y, facing, source_lr,
        model_scale, yaw_rad, output_scale, roll_rad,
        effect_scale_y, effect_scale_z, rotate_x_rad);

    nes_voxel_mesh_bind_texture(texture->pixels, texture->width,
                                texture->height, texture->width, 1.0f, 1);
    /* The source effect material is two-sided. Mirroring Falcon changes the
     * projected winding of this alpha card, so submit both windings instead
     * of letting one facing vanish behind host back-face culling. */
    nes_voxel_mesh_triangle(vertices[3], vertices[2], vertices[1]);
    nes_voxel_mesh_triangle(vertices[0], vertices[3], vertices[1]);
    nes_voxel_mesh_triangle(vertices[1], vertices[2], vertices[3]);
    nes_voxel_mesh_triangle(vertices[1], vertices[3], vertices[0]);
}

/* The original effects below are generic Smash 64 particles (Ripple,
 * ImpactWave, DustDashSmall, and SparkleWhite), so no owner-authored card is
 * available to bind here.  Keep their host approximation deliberately tiny:
 * a few 1x1 fallback-colour quads in the same screen plane as Falcon. */
static NesVoxelMeshVertex dive_effect_vertex(float x, float y, float z)
{
    NesVoxelMeshVertex out;
    out.x = x;
    out.y = y;
    out.z = z;
    out.u = 0.0f;
    out.v = 0.0f;
    return out;
}

static void draw_dive_effect_quad(float center_x, float center_y, float z,
                                  float half_width, float half_height)
{
    NesVoxelMeshVertex top_left = dive_effect_vertex(
        center_x - half_width, center_y - half_height, z);
    NesVoxelMeshVertex top_right = dive_effect_vertex(
        center_x + half_width, center_y - half_height, z);
    NesVoxelMeshVertex bottom_right = dive_effect_vertex(
        center_x + half_width, center_y + half_height, z);
    NesVoxelMeshVertex bottom_left = dive_effect_vertex(
        center_x - half_width, center_y + half_height, z);

    nes_voxel_mesh_triangle(top_left, top_right, bottom_right);
    nes_voxel_mesh_triangle(top_left, bottom_right, bottom_left);
    nes_voxel_mesh_triangle(bottom_right, top_right, top_left);
    nes_voxel_mesh_triangle(bottom_left, bottom_right, top_left);
}

static void draw_dive_effect_spark(float center_x, float center_y, float z,
                                   float radius)
{
    NesVoxelMeshVertex top = dive_effect_vertex(center_x, center_y - radius,
                                                 z);
    NesVoxelMeshVertex right = dive_effect_vertex(center_x + radius, center_y,
                                                   z);
    NesVoxelMeshVertex bottom = dive_effect_vertex(center_x, center_y + radius,
                                                    z);
    NesVoxelMeshVertex left = dive_effect_vertex(center_x - radius, center_y,
                                                  z);

    nes_voxel_mesh_triangle(top, right, bottom);
    nes_voxel_mesh_triangle(top, bottom, left);
    nes_voxel_mesh_triangle(bottom, right, top);
    nes_voxel_mesh_triangle(left, bottom, top);
}

static void draw_falcon_dive_effect(const ForeignState *state,
                                    float center_x, float anchor_y,
                                    float output_scale)
{
    const uint32_t frame = (uint32_t)state->state_frame;
    const float unit = output_scale > 0.0f ? output_scale : 1.0f;
    /* draw_model receives Falcon's authoritative foot row in +Y-up render
     * space. Effects described as ground/launch-point particles belong on
     * that row; the body extends upward from it. */
    const float ground_y = anchor_y;
    const float middle_y = anchor_y + FALCON_RENDER_HEIGHT * unit * 0.5f;
    const float z = unit * 2.0f;
    const float source_lr = state->facing < 0.0f ? -1.0f : 1.0f;

    if (state->state == FL_FALCON_DIVE_GROUND ||
        state->state == FL_FALCON_DIVE_AIR) {
        if (frame < FALCON_DIVE_LAUNCH_FRAME + 6u) {
            const float phase = (float)frame;
            /* Source f0 spawns Ripple + ImpactWave. The host has no particle
             * manager, so let the spawned ring persist and expand briefly
             * instead of rendering an effectively invisible one-frame line. */
            nes_voxel_mesh_bind_texture(s_dive_white_color, 1, 1, 1,
                                        0.65f - phase * 0.08f, 0);
            draw_dive_effect_quad(center_x, ground_y + 0.4f * unit, z,
                                  (3.0f + phase * 1.2f) * unit,
                                  0.45f * unit);
        }
        if (frame >= FALCON_DIVE_DASH_FRAME &&
            frame < FALCON_DIVE_ATTACK_END_FRAME) {
            const uint32_t phase = frame - FALCON_DIVE_DASH_FRAME;
            /* Source f13 spawns DustDashSmall, then ten Star Rod sparks at
             * two-frame intervals during the active launch. Preserve that
             * cadence with compact host diamonds that remain readable after
             * Falcon-only 2x downsampling. */
            if (phase < 6u) {
                nes_voxel_mesh_bind_texture(s_dive_dust_color, 1, 1, 1,
                                            0.72f - (float)phase * 0.08f, 0);
                draw_dive_effect_quad(
                    center_x - source_lr * (3.0f + (float)phase) * unit,
                    ground_y + 0.8f * unit, z,
                    (1.8f + (float)phase * 0.35f) * unit, 0.7f * unit);
            }
            if (phase < 20u) {
                const float step = (float)(phase / 2u);
                const float side = (phase & 2u) ? -1.0f : 1.0f;
                nes_voxel_mesh_bind_texture(s_dive_spark_color, 1, 1, 1,
                                            0.85f, 0);
                draw_dive_effect_spark(
                    center_x + source_lr * (4.0f + fmodf(step, 3.0f)) * unit,
                    middle_y + side * (3.0f + fmodf(step, 4.0f)) * unit,
                    z, (0.8f + 0.12f * fmodf(step, 3.0f)) * unit);
                draw_dive_effect_spark(
                    center_x - source_lr * (2.0f + fmodf(step, 2.0f)) * unit,
                    middle_y - side * 5.0f * unit, z, 0.55f * unit);
            }
        }
        if (frame >= FALCON_DIVE_ATTACK_END_FRAME &&
            frame < FALCON_DIVE_ATTACK_END_FRAME + 4u) {
            /* Source f45 clears the catch boxes and spawns a white sparkle. */
            const float phase = (float)(frame - FALCON_DIVE_ATTACK_END_FRAME);
            nes_voxel_mesh_bind_texture(s_dive_white_color, 1, 1, 1,
                                        0.8f - phase * 0.15f, 0);
            draw_dive_effect_spark(center_x + source_lr * 5.0f * unit,
                                   middle_y + 2.0f * unit, z,
                                   (1.6f - phase * 0.2f) * unit);
        }
        return;
    }

    if (state->state == FL_FALCON_DIVE_CATCH) {
        if (frame >= 6u) return;
        /* Source Catch f0: shared Effect(17,38) and catch impact. */
        nes_voxel_mesh_bind_texture(s_dive_spark_color, 1, 1, 1,
                                    0.85f - (float)frame * 0.08f, 0);
        draw_dive_effect_spark(center_x + source_lr * 5.0f * unit,
                               middle_y + 2.0f * unit, z,
                               (1.5f + (float)frame * 0.12f) * unit);
        draw_dive_effect_spark(center_x + source_lr * 8.0f * unit,
                               middle_y + 1.5f * unit, z, 0.75f * unit);
    } else if (state->state == FL_FALCON_DIVE_THROW) {
        if (frame >= 10u) return;
        /* Source Throw f0: SparkleWhiteMultiExplode + ImpactWave. */
        nes_voxel_mesh_bind_texture(s_dive_white_color, 1, 1, 1,
                                    0.9f - (float)frame * 0.07f, 0);
        draw_dive_effect_spark(center_x + source_lr * 6.0f * unit,
                               middle_y, z,
                               (1.8f + (float)frame * 0.16f) * unit);
        draw_dive_effect_spark(center_x - source_lr * 2.5f * unit,
                               middle_y + 4.0f * unit, z, 0.9f * unit);
        draw_dive_effect_spark(center_x + source_lr * 1.0f * unit,
                               middle_y - 4.0f * unit, z, 0.7f * unit);
        draw_dive_effect_quad(center_x, ground_y + 0.4f * unit, z,
                              (4.5f + (float)frame * 0.6f) * unit,
                              0.45f * unit);
    }
}

/* Source Pikachu effects are alpha cards, and their DObjs are deliberately
 * two-sided.  Keep the source card pixels and cycle intact while translating
 * only their 3D placement to the NES screen plane. */
static void draw_pikachu_effect_card(unsigned effect, unsigned frame,
                                     float center_x, float center_y,
                                     float half_width, float half_height,
                                     float rotation, float z)
{
    const unsigned int *pixels;
    int texture_width, texture_height;
    const float c = cosf(rotation), s = sinf(rotation);
    const float x[4] = { -half_width, half_width, half_width, -half_width };
    const float y[4] = { -half_height, -half_height, half_height, half_height };
    NesVoxelMeshVertex v[4];
    unsigned i;

    if (!game_smash64_assets_pikachu_effect_texture(
            effect, frame, &pixels, &texture_width, &texture_height))
        return;
    for (i = 0; i < 4; ++i) {
        v[i].x = center_x + x[i] * c - y[i] * s;
        v[i].y = center_y + x[i] * s + y[i] * c;
        v[i].z = z;
    }
    v[0].u = 0.0f;                 v[0].v = 0.0f;
    v[1].u = (float)texture_width; v[1].v = 0.0f;
    v[2].u = (float)texture_width; v[2].v = (float)texture_height;
    v[3].u = 0.0f;                 v[3].v = (float)texture_height;
    nes_voxel_mesh_bind_texture(pixels, texture_width, texture_height,
                                texture_width, 1.0f, 1);
    nes_voxel_mesh_triangle(v[0], v[1], v[2]);
    nes_voxel_mesh_triangle(v[0], v[2], v[3]);
    nes_voxel_mesh_triangle(v[2], v[1], v[0]);
    nes_voxel_mesh_triangle(v[3], v[2], v[0]);
}

static void draw_pikachu_spark(float center_x, float center_y, float z,
                                float radius)
{
    NesVoxelMeshVertex top = dive_effect_vertex(center_x, center_y + radius, z);
    NesVoxelMeshVertex right = dive_effect_vertex(center_x + radius, center_y, z);
    NesVoxelMeshVertex bottom = dive_effect_vertex(center_x, center_y - radius, z);
    NesVoxelMeshVertex left = dive_effect_vertex(center_x - radius, center_y, z);
    nes_voxel_mesh_triangle(top, right, bottom);
    nes_voxel_mesh_triangle(top, bottom, left);
    nes_voxel_mesh_triangle(bottom, right, top);
    nes_voxel_mesh_triangle(left, bottom, top);
}

static int pikachu_quick_state(unsigned state)
{
    return state >= PK_QUICK_ATTACK_START && state <= PK_QUICK_ATTACK_RECOVERY;
}

static void apply_pikachu_quick_attack_pose(const ForeignState *state,
                                            float r[SMASH64_MAX_JOINTS][3],
                                            float s[SMASH64_MAX_JOINTS][3])
{
    const float pi = 3.14159265358979323846f;
    /* BattleShip ftPikachuSpecialHiUpdateModelPitchScale rotates the complete
     * joint-4 subtree by ArcTan2(vx, vy) * lr - 90deg and uses exactly
     * {0.8, 0.8, 1.2}.  The bridge exposes the same source velocity/facing,
     * so this is a skeletal transform rather than a screen-space squash. */
    if (!state || !pikachu_quick_state(state->state) ||
        s_model.joint_count <= 4u)
        return;
    r[4][0] = atan2f((float)state->vx, (float)state->vy) * state->facing -
              pi * 0.5f;
    s[4][0] = 0.8f;
    s[4][1] = 0.8f;
    s[4][2] = 1.2f;
}

static void draw_pikachu_quick_attack_effect(const ForeignState *state,
                                              float center_x, float foot_y,
                                              float output_scale)
{
    const unsigned frame = state->state_frame;
    const float unit = output_scale > 0.0f ? output_scale : 1.0f;
    const float middle_y = foot_y + PIKACHU_RENDER_HEIGHT * 0.48f * unit;
    const float z = 3.0f * unit;
    unsigned i;

    if (!pikachu_quick_state(state->state)) return;
    /* Quick Attack's source status marks the fighter intangible and applies
     * colour animation throughout startup/zip/end. The host has no fighter
     * colour-animation API, so show a bounded owner-card halo instead of
     * silently omitting that visible status. */
    if (state->state == PK_QUICK_ATTACK_START) {
        const float pulse = 5.0f + 1.5f * sinf((float)frame * 0.7f);
        draw_pikachu_effect_card(SMASH64_PIKACHU_EFFECT_THUNDER_SHOCK, frame,
                                 center_x, middle_y, pulse * unit,
                                 pulse * unit, (float)frame * 0.18f, z);
        return;
    }
    if (state->state == PK_QUICK_ATTACK_ZIP1 ||
        state->state == PK_QUICK_ATTACK_ZIP2) {
        const float direction = atan2f((float)state->vy, (float)state->vx);
        const float forward_x = cosf(direction), forward_y = sinf(direction);
        nes_voxel_mesh_bind_texture(s_pikachu_spark_color, 1, 1, 1, 0.92f, 0);
        for (i = 0; i < 5; ++i) {
            const float angle = direction + (float)i * 1.25663706f +
                                (float)frame * 0.35f;
            const float distance = (3.0f + (float)(i & 1u) * 1.5f) * unit;
            draw_pikachu_spark(center_x - forward_x * 2.0f * unit +
                                    cosf(angle) * distance,
                                middle_y - forward_y * 2.0f * unit +
                                    sinf(angle) * distance,
                                z, (0.70f + 0.15f * (float)(i & 1u)) * unit);
        }
        return;
    }
    /* Controller emits Ripple precisely at action frame 25 / 39, then
     * changes state. Preserve an eight-frame expanding residual ring without
     * needing a mutable particle pool in the authoritative gameplay code. */
    if ((state->state == PK_QUICK_ATTACK_WINDOW && frame >= 25u && frame < 33u) ||
        (state->state == PK_QUICK_ATTACK_RECOVERY && frame >= 39u && frame < 47u)) {
        const unsigned first = state->state == PK_QUICK_ATTACK_WINDOW ? 25u : 39u;
        const float phase = (float)(frame - first);
        const float radius = (3.0f + phase * 1.1f) * unit;
        nes_voxel_mesh_bind_texture(s_pikachu_spark_color, 1, 1, 1,
                                    0.80f - phase * 0.075f, 0);
        for (i = 0; i < 8; ++i) {
            const float angle = (float)i * 0.78539816f;
            draw_pikachu_spark(center_x + cosf(angle) * radius,
                                middle_y + sinf(angle) * radius, z,
                                0.45f * unit);
        }
    }
}

static void draw_pikachu_thunder_amp(const ForeignState *state,
                                     float center_x, float foot_y,
                                     float output_scale)
{
    unsigned frame;
    const float unit = output_scale > 0.0f ? output_scale : 1.0f;
    const float middle_y = foot_y + PIKACHU_RENDER_HEIGHT * 0.50f * unit;
    const float z = 3.5f * unit;
    unsigned i;

    if (state->state != PK_THUNDER_SELF_HIT) {
        s_pikachu_thunder_self_hit_active = 0;
        return;
    }
    /* PK_THUNDER_SELF_HIT does not reset ForeignState::state_frame: source
     * motion 0x1668 starts at zero but the compact controller keeps the
     * complete Down-B action time. Latch the transition solely for rendering.
     * A savestate restore makes that counter go backwards, which is likewise
     * a new local presentation epoch. */
    if (!s_pikachu_thunder_self_hit_active ||
        state->state_frame < s_pikachu_thunder_self_hit_start_frame) {
        s_pikachu_thunder_self_hit_active = 1;
        s_pikachu_thunder_self_hit_start_frame = state->state_frame;
    }
    frame = state->state_frame - s_pikachu_thunder_self_hit_start_frame;
    if (frame >= 18u) return;
    /* ThunderAmp itself is a common particle-bank script (0x74), whereas
     * PikachuSpecial2 owns the adjacent ThunderShock cards. Use those actual
     * owner cards as a short, rotating contact aura; the dust/ring supplies
     * the common particle's ground-response silhouette without fabricating
     * unowned texture data. */
    for (i = 0; i < 6; ++i) {
        const float phase = (float)frame * 0.32f + (float)i * 1.04719755f;
        const float orbit = (2.5f + 0.30f * (float)frame) * unit;
        const float scale = (3.5f + 0.10f * (float)(frame & 3u)) * unit;
        draw_pikachu_effect_card(SMASH64_PIKACHU_EFFECT_THUNDER_SHOCK,
                                 frame + i,
                                 center_x + cosf(phase) * orbit,
                                 middle_y + sinf(phase) * orbit,
                                 scale, scale, phase, z);
    }
    if (frame < 9u) {
        const float phase = (float)frame;
        nes_voxel_mesh_bind_texture(s_pikachu_dust_color, 1, 1, 1,
                                    0.75f - phase * 0.07f, 0);
        draw_dive_effect_quad(center_x, foot_y + 0.6f * unit, z,
                              (3.0f + phase * 1.2f) * unit,
                              (0.55f + phase * 0.05f) * unit);
    }
}

static NesVoxelMeshVertex render_death_vertex(
    Mat4 matrix, const FalconAssetVertex *vertex,
    const float pose_min[3], const float pose_max[3],
    float center_x, float center_y, float facing, float model_scale,
    float yaw_rad, float spin_rad)
{
    NesVoxelMeshVertex out;
    float point[3];
    float x, y, z;
    const float yaw_cos = cosf(yaw_rad);
    const float yaw_sin = sinf(yaw_rad);
    const float spin_cos = cosf(spin_rad);
    const float spin_sin = sinf(spin_rad);
    float screen_x;

    mat_point(matrix, vertex->pos, point);
    x = (point[0] - (pose_min[0] + pose_max[0]) * 0.5f) * facing;
    y = point[1] - (pose_min[1] + pose_max[1]) * 0.5f;
    z = (point[2] - (pose_min[2] + pose_max[2]) * 0.5f) * facing;
    screen_x = (x * yaw_cos - z * yaw_sin) * model_scale;
    y *= model_scale;

    out.x = center_x + screen_x * spin_cos - y * spin_sin;
    out.y = center_y + screen_x * spin_sin + y * spin_cos;
    out.z = (x * yaw_sin + z * yaw_cos) * model_scale;
    out.u = vertex->uv[0];
    out.v = vertex->uv[1];
    return out;
}

static int draw_model(float center_x, float anchor_y, float output_scale,
                      int death_mode, int still_mode,
                      const char *animation_override,
                      float spin_radians, float animation_frame,
                      int facing_override)
{
    const ForeignState *state;
    const FalconAssetAnimation *animation;
    float t[SMASH64_MAX_JOINTS][3];
    float r[SMASH64_MAX_JOINTS][3];
    float s[SMASH64_MAX_JOINTS][3];
    Mat4 world[SMASH64_MAX_JOINTS];
    float pose_min[3], pose_max[3];
    float model_scale, reference_height, facing, yaw_rad;
    uint16_t bound_texture = 0xFFFEu;
    uint32_t i;

    if (!ensure_loaded()) return 0;
    state = nes_foreign_state();
    if (!state) return 0;

    for (i = 0; i < s_model.joint_count; ++i) {
        memcpy(t[i], s_model.joints[i].translate, sizeof(t[i]));
        memcpy(r[i], s_model.joints[i].rotate, sizeof(r[i]));
        memcpy(s[i], s_model.joints[i].scale, sizeof(s[i]));
    }
    /* Smash 64's DeadUpStar status uses the common DamageFall motion. The
     * owner-only runtime currently carries Falcon's closest extracted aerial
     * tumble (FallAerial), then the host applies the status' whole-body spin.
     * Prefer DamageFlyTop automatically when a fuller local extraction adds
     * it to the blob. */
    animation = death_mode
        ? find_animation(&s_model, "DamageFlyTop")
        : find_animation(&s_model,
                         animation_override
                             ? animation_override
                             : (still_mode ? (active_is_pikachu()
                                                  ? "Idle" : "Wait")
                                           : animation_for_state(state)));
    if (death_mode && !animation)
        animation = find_animation(&s_model, "FallAerial");
    if (!env_enabled("NESRECOMP_FALCON_BIND_POSE"))
        apply_animation(&s_model, animation,
                        (death_mode || animation_override)
                            ? animation_frame
                            : (still_mode && !active_is_pikachu()
                                   ? FALCON_WAIT_GROUNDED_FIRST +
                                         FALCON_WAIT_GROUNDED_SPAN * 0.5f
                                   : (still_mode
                                          ? 0.0f
                                          : presentation_animation_frame(state))),
                        t, r, s);
    if (active_is_pikachu() && !death_mode && !still_mode &&
        !animation_override)
        apply_pikachu_quick_attack_pose(state, r, s);
    build_matrices(&s_model, t, r, s, world);
    /* Figatree root translations are absolute fighter-pose coordinates, not
     * SMB1 world motion. Anchor the animated mesh's current lowest point to
     * SMB1's authoritative foot row so animation can bob/crouch without
     * lifting the whole fighter dozens of pixels off the floor. */
    compute_world_bounds(&s_model, world, pose_min, pose_max);

    /* Scale must be invariant across animation frames. The previous renderer
     * divided by each pose's animated height, so tucked and extended jump
     * silhouettes made the whole body pump larger/smaller and read as a
     * stretch. Bind bounds are stable owner-derived model data; animated
     * bounds remain useful only for centering and foot anchoring. */
    reference_height = s_model.bounds_max[1] - s_model.bounds_min[1];
    if (output_scale <= 0.0f) output_scale = 1.0f;
    model_scale = env_float(active_is_pikachu()
                                ? "NESRECOMP_PIKACHU_RENDER_HEIGHT"
                                : "NESRECOMP_FALCON_RENDER_HEIGHT",
                            active_is_pikachu()
                                ? PIKACHU_RENDER_HEIGHT
                                : FALCON_RENDER_HEIGHT) * output_scale /
                  reference_height;
    /* Smash's +LR model orientation is opposite our screen-space projection.
     * Mirror the mesh against that authored convention, not against movement
     * directly; the old sign made rightward Run visibly face left. */
    facing = (facing_override >= 0
                  ? (facing_override ? 1.0f : -1.0f)
                  : state->facing) < 0.0f
                 ? 1.0f
                 : -1.0f;
    {
        float yaw_degrees =
            env_float(active_is_pikachu()
                          ? "NESRECOMP_PIKACHU_YAW_DEG"
                          : "NESRECOMP_FALCON_YAW_DEG",
                      active_is_pikachu() ? PIKACHU_YAW_DEG
                                          : FALCON_YAW_DEG);
        if (!active_is_pikachu() &&
            (state->state == FL_FALCON_PUNCH_GROUND ||
             state->state == FL_FALCON_PUNCH_AIR)) {
            yaw_degrees = env_float("NESRECOMP_FALCON_PUNCH_YAW_DEG",
                                    yaw_degrees);
        }
        yaw_rad = yaw_degrees *
            (3.14159265358979323846f / 180.0f);
    }

    s_pikachu_joint11_valid = 0;
    if (active_is_pikachu() && s_model.joint_count > 11u) {
        float origin[3] = { 0.0f, 0.0f, 0.0f }, point[3];
        const float c = cosf(yaw_rad), yaw_sin = sinf(yaw_rad);
        mat_point(world[11], origin, point);
        point[0] = (point[0] - (pose_min[0] + pose_max[0]) * 0.5f) * facing;
        point[2] = (point[2] - (pose_min[2] + pose_max[2]) * 0.5f) * facing;
        s_pikachu_joint11_x = center_x +
            (point[0] * c - point[2] * yaw_sin) * model_scale;
        s_pikachu_joint11_y = anchor_y +
            (point[1] - pose_min[1]) * model_scale;
        s_pikachu_joint11_valid = 1;
    }

    for (i = 0; i < s_model.triangle_count; ++i) {
        const FalconAssetTriangle *triangle = &s_model.triangles[i];
        NesVoxelMeshVertex a, b, c;
        if (triangle->texture != bound_texture) {
            bound_texture = triangle->texture;
            if (bound_texture == 0xFFFFu) {
                nes_voxel_mesh_bind_texture(s_fallback_color, 1, 1, 1,
                                            0.85f, 0);
            } else {
                const FalconAssetTexture *texture =
                    &s_model.textures[bound_texture];
                nes_voxel_mesh_bind_texture(texture->pixels, texture->width,
                                            texture->height, texture->width,
                                            1.0f, 1);
            }
        }
        if (death_mode) {
            a = render_death_vertex(world[triangle->joint[0]],
                                    &triangle->vertex[0], pose_min, pose_max,
                                    center_x, anchor_y, facing, model_scale,
                                    yaw_rad, spin_radians);
            b = render_death_vertex(world[triangle->joint[1]],
                                    &triangle->vertex[1], pose_min, pose_max,
                                    center_x, anchor_y, facing, model_scale,
                                    yaw_rad, spin_radians);
            c = render_death_vertex(world[triangle->joint[2]],
                                    &triangle->vertex[2], pose_min, pose_max,
                                    center_x, anchor_y, facing, model_scale,
                                    yaw_rad, spin_radians);
        } else {
            a = render_vertex(&s_model, world[triangle->joint[0]],
                              &triangle->vertex[0], pose_min, pose_max,
                              center_x, anchor_y,
                              facing, model_scale, yaw_rad);
            b = render_vertex(&s_model, world[triangle->joint[1]],
                              &triangle->vertex[1], pose_min, pose_max,
                              center_x, anchor_y,
                              facing, model_scale, yaw_rad);
            c = render_vertex(&s_model, world[triangle->joint[2]],
                              &triangle->vertex[2], pose_min, pose_max,
                              center_x, anchor_y,
                              facing, model_scale, yaw_rad);
        }
        nes_voxel_mesh_triangle(a, b, c);
    }
    if (active_is_pikachu() && !death_mode && !still_mode &&
        !animation_override) {
        draw_pikachu_quick_attack_effect(state, center_x, anchor_y,
                                         output_scale);
        draw_pikachu_thunder_amp(state, center_x, anchor_y, output_scale);
    } else if (!active_is_pikachu() && !death_mode && !still_mode &&
        !animation_override) {
        draw_falcon_punch_effect(&s_model, state, world, pose_min, pose_max,
                                 center_x, anchor_y, facing, model_scale,
                                 yaw_rad, output_scale);
        draw_falcon_kick_effect(&s_model, state, world, pose_min, pose_max,
                                center_x, anchor_y, facing, model_scale,
                                yaw_rad, output_scale);
        draw_falcon_dive_effect(state, center_x, anchor_y, output_scale);
    }
    return 1;
}

int game_smash64_assets_draw(float center_x, float foot_y,
                             float output_scale)
{
    return draw_model(center_x, foot_y, output_scale, 0, 0, NULL,
                      0.0f, 0.0f, -1);
}

int game_smash64_assets_draw_idle(float center_x, float foot_y,
                                  float output_scale)
{
    return draw_model(center_x, foot_y, output_scale, 0, 1, NULL,
                      0.0f, 0.0f, -1);
}

int game_smash64_assets_draw_swim(float center_x, float foot_y,
                                  float output_scale, int facing_right)
{
    return draw_model(center_x, foot_y, output_scale, 0, 1, NULL,
                      0.0f, 0.0f, facing_right ? 1 : 0);
}

int game_smash64_assets_draw_scripted(float center_x, float foot_y,
                                      float output_scale,
                                      int scripted_presentation,
                                      float presentation_frame)
{
    const char *animation;
    if (scripted_presentation == SMASH64_SCRIPTED_PRESENTATION_WALK ||
        scripted_presentation == SMASH64_SCRIPTED_PRESENTATION_PIPE_SIDE) {
        animation = "Walk2";
    } else if (scripted_presentation ==
               SMASH64_SCRIPTED_PRESENTATION_PIPE_VERTICAL) {
        animation = "CrouchIdle";
    } else {
        animation = "Fall";
    }
    /* The extracted set has no ledge/ladder motion. A calm source Fall pose
     * is the nearest authentic side-on silhouette for a vertical flagpole;
     * SMB1 supplies the actual slide. Autowalk advances Walk2 at source rate. */
    if (scripted_presentation == SMASH64_SCRIPTED_PRESENTATION_FLAGPOLE)
        presentation_frame = 4.0f;
    else if (scripted_presentation ==
             SMASH64_SCRIPTED_PRESENTATION_PIPE_VERTICAL)
        presentation_frame = 0.0f;
    return draw_model(center_x, foot_y, output_scale, 0, 0, animation,
                      0.0f, presentation_frame, -1);
}

int game_smash64_assets_draw_death(float center_x, float center_y,
                                   float output_scale, float spin_radians,
                                   float animation_frame)
{
    return draw_model(center_x, center_y, output_scale, 1, 0, NULL,
                      spin_radians, animation_frame, -1);
}
