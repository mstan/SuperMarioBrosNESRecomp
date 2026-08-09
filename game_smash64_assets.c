/* Runtime loader and skeletal renderer for the ignored Falcon asset blob. */
#include "game_smash64_assets.h"

#include "game_smash64.h"
#include "foreign_controller.h"
#include "mods/smash64/characters/captain_falcon.h"
#include "voxel_renderer.h"

#include <SDL.h>

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALCON_BLOB_VERSION 3u
#define FALCON_JOINT_COUNT 26u
#define FALCON_RENDER_HEIGHT 32.0f
#define FALCON_YAW_DEG 88.0f
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
    uint16_t joint;
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
static const uint32_t s_fallback_color[1] = { 0xFF3060C8u };

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
                           float pose_translate[FALCON_JOINT_COUNT][3],
                           float pose_rotate[FALCON_JOINT_COUNT][3],
                           float pose_scale[FALCON_JOINT_COUNT][3],
                           Mat4 world[FALCON_JOINT_COUNT])
{
    uint32_t i;
    for (i = 0; i < model->joint_count; ++i) {
        Mat4 local = mat_local(pose_translate[i], pose_rotate[i], pose_scale[i]);
        int parent = model->joints[i].parent;
        world[i] = parent >= 0 ? mat_mul(world[parent], local) : local;
    }
}

static void compute_world_bounds(const FalconAssetModel *model,
                                 Mat4 world[FALCON_JOINT_COUNT],
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
            mat_point(world[triangle->joint], triangle->vertex[v].pos, point);
            for (axis = 0; axis < 3; ++axis) {
                if (point[axis] < bounds_min[axis]) bounds_min[axis] = point[axis];
                if (point[axis] > bounds_max[axis]) bounds_max[axis] = point[axis];
            }
        }
    }
}

static void compute_bind_bounds(FalconAssetModel *model)
{
    float t[FALCON_JOINT_COUNT][3];
    float r[FALCON_JOINT_COUNT][3];
    float s[FALCON_JOINT_COUNT][3];
    Mat4 world[FALCON_JOINT_COUNT];
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
    if (version != FALCON_BLOB_VERSION) return 0;

    model->joint_count = read_u32(&reader);
    model->triangle_count = read_u32(&reader);
    model->texture_count = read_u32(&reader);
    model->animation_count = read_u32(&reader);
    model->track_count = read_u32(&reader);
    model->segment_count = read_u32(&reader);
    model->punch_effect_texture_first = read_u32(&reader);
    model->punch_effect_texture_count = read_u32(&reader);
    if (model->joint_count != FALCON_JOINT_COUNT ||
        !count_is_safe(model->triangle_count, 10000) ||
        !count_is_safe(model->texture_count, 256) ||
        !count_is_safe(model->animation_count, 128) ||
        !count_is_safe(model->track_count, 100000) ||
        !count_is_safe(model->segment_count, 1000000) ||
        model->punch_effect_texture_count !=
            FALCON_PUNCH_EFFECT_TEXTURES ||
        !range_is_safe(model->punch_effect_texture_first,
                       model->punch_effect_texture_count,
                       model->texture_count))
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
        triangle->joint = read_u16(&reader);
        triangle->texture = read_u16(&reader);
        for (j = 0; j < 3; ++j) {
            uint32_t axis;
            for (axis = 0; axis < 3; ++axis)
                triangle->vertex[j].pos[axis] = read_f32(&reader);
            for (axis = 0; axis < 2; ++axis)
                triangle->vertex[j].uv[axis] = read_f32(&reader);
        }
        if (triangle->joint >= model->joint_count ||
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
        if (track->joint >= model->joint_count || track->kind > 8 ||
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
                "[Smash64] Falcon assets loaded: %u triangles, %u textures, %u animations (%s)\n",
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

static const char *animation_for_state(int state)
{
    switch (state) {
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
    case FL_FALCON_PUNCH_GROUND: return "FalconPunchGround";
    case FL_FALCON_PUNCH_AIR: return "FalconPunchAir";
    case FL_FALCON_KICK_GROUND: return "DownSpecial";
    case FL_FALCON_KICK_AIR: return "DownSpecialAir";
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

static void apply_animation(const FalconAssetModel *model,
                            const FalconAssetAnimation *animation, float frame,
                            float t[FALCON_JOINT_COUNT][3],
                            float r[FALCON_JOINT_COUNT][3],
                            float s[FALCON_JOINT_COUNT][3])
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
    if (state->state == FL_WAIT) {
        const float extent = FALCON_WAIT_GROUNDED_SPAN * 2.0f;
        float phase = fmodf((float)state->state_frame * FALCON_WAIT_RATE,
                            extent);
        if (phase > FALCON_WAIT_GROUNDED_SPAN)
            phase = extent - phase;
        return FALCON_WAIT_GROUNDED_FIRST + phase;
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
    Mat4 world[FALCON_JOINT_COUNT], const float pose_min[3],
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
                      float spin_radians, float animation_frame)
{
    const ForeignState *state;
    const FalconAssetAnimation *animation;
    float t[FALCON_JOINT_COUNT][3];
    float r[FALCON_JOINT_COUNT][3];
    float s[FALCON_JOINT_COUNT][3];
    Mat4 world[FALCON_JOINT_COUNT];
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
                             : (still_mode ? "Wait"
                                           : animation_for_state(state->state)));
    if (death_mode && !animation)
        animation = find_animation(&s_model, "FallAerial");
    if (!env_enabled("NESRECOMP_FALCON_BIND_POSE"))
        apply_animation(&s_model, animation,
                        (death_mode || animation_override)
                            ? animation_frame
                            : (still_mode
                                   ? FALCON_WAIT_GROUNDED_FIRST +
                                         FALCON_WAIT_GROUNDED_SPAN * 0.5f
                                   : presentation_animation_frame(state)),
                        t, r, s);
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
    model_scale = env_float("NESRECOMP_FALCON_RENDER_HEIGHT",
                            FALCON_RENDER_HEIGHT) * output_scale /
                  reference_height;
    /* Smash's +LR model orientation is opposite our screen-space projection.
     * Mirror the mesh against that authored convention, not against movement
     * directly; the old sign made rightward Run visibly face left. */
    facing = state->facing < 0.0f ? 1.0f : -1.0f;
    {
        float yaw_degrees =
            env_float("NESRECOMP_FALCON_YAW_DEG", FALCON_YAW_DEG);
        if (state->state == FL_FALCON_PUNCH_GROUND ||
            state->state == FL_FALCON_PUNCH_AIR) {
            yaw_degrees = env_float("NESRECOMP_FALCON_PUNCH_YAW_DEG",
                                    yaw_degrees);
        }
        yaw_rad = yaw_degrees *
            (3.14159265358979323846f / 180.0f);
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
            a = render_death_vertex(world[triangle->joint],
                                    &triangle->vertex[0], pose_min, pose_max,
                                    center_x, anchor_y, facing, model_scale,
                                    yaw_rad, spin_radians);
            b = render_death_vertex(world[triangle->joint],
                                    &triangle->vertex[1], pose_min, pose_max,
                                    center_x, anchor_y, facing, model_scale,
                                    yaw_rad, spin_radians);
            c = render_death_vertex(world[triangle->joint],
                                    &triangle->vertex[2], pose_min, pose_max,
                                    center_x, anchor_y, facing, model_scale,
                                    yaw_rad, spin_radians);
        } else {
            a = render_vertex(&s_model, world[triangle->joint],
                              &triangle->vertex[0], pose_min, pose_max,
                              center_x, anchor_y,
                              facing, model_scale, yaw_rad);
            b = render_vertex(&s_model, world[triangle->joint],
                              &triangle->vertex[1], pose_min, pose_max,
                              center_x, anchor_y,
                              facing, model_scale, yaw_rad);
            c = render_vertex(&s_model, world[triangle->joint],
                              &triangle->vertex[2], pose_min, pose_max,
                              center_x, anchor_y,
                              facing, model_scale, yaw_rad);
        }
        nes_voxel_mesh_triangle(a, b, c);
    }
    if (!death_mode && !still_mode && !animation_override) {
        draw_falcon_punch_effect(&s_model, state, world, pose_min, pose_max,
                                 center_x, anchor_y, facing, model_scale,
                                 yaw_rad, output_scale);
    }
    return 1;
}

int game_smash64_assets_draw(float center_x, float foot_y,
                             float output_scale)
{
    return draw_model(center_x, foot_y, output_scale, 0, 0, NULL,
                      0.0f, 0.0f);
}

int game_smash64_assets_draw_idle(float center_x, float foot_y,
                                  float output_scale)
{
    return draw_model(center_x, foot_y, output_scale, 0, 1, NULL,
                      0.0f, 0.0f);
}

int game_smash64_assets_draw_scripted(float center_x, float foot_y,
                                      float output_scale,
                                      int scripted_presentation,
                                      float presentation_frame)
{
    const char *animation = scripted_presentation ==
                                    SMASH64_SCRIPTED_PRESENTATION_WALK
                                ? "Walk2"
                                : "Fall";
    /* The extracted set has no ledge/ladder motion. A calm source Fall pose
     * is the nearest authentic side-on silhouette for a vertical flagpole;
     * SMB1 supplies the actual slide. Autowalk advances Walk2 at source rate. */
    if (scripted_presentation == SMASH64_SCRIPTED_PRESENTATION_FLAGPOLE)
        presentation_frame = 4.0f;
    return draw_model(center_x, foot_y, output_scale, 0, 0, animation,
                      0.0f, presentation_frame);
}

int game_smash64_assets_draw_death(float center_x, float center_y,
                                   float output_scale, float spin_radians,
                                   float animation_frame)
{
    return draw_model(center_x, center_y, output_scale, 1, 0, NULL,
                      spin_radians, animation_frame);
}
