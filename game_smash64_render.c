/*
 * game_smash64_render.c — M6.1/M6.2 presentation glue for the Smash 64
 * player replacement mod. See game_smash64_render.h for scope and the
 * screen-to-world convention.
 *
 * Deliberately thin and read-only against game_smash64.c: everything here
 * either reads game_smash64_active() or reads g_ram's screen-space player
 * mirror bytes, and only ever writes into the presentation framebuffer via
 * the voxel mesh API. Nothing here touches NES RAM, ownership, or physics.
 */
#include "game_smash64_render.h"

#include "game_smash64_assets.h"
#include "game_smash64.h"
#include "nes_runtime.h"
#include "voxel_renderer.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

/* Cube extent, in world pixels (1 world unit = 1 NES pixel). Comparable to
 * the ~16x24px footprint of Mario's own 8x16 (or 8x8-doubled) metasprite so
 * the cube reads as roughly the same size as the sprite it replaces. */
#define FALCON_CUBE_HALF_WIDTH 8.0f
#define FALCON_CUBE_HEIGHT     24.0f
#define FALCON_CUBE_HALF_DEPTH 8.0f

/*
 * Straight-on camera, yawed CUBE. An off-axis eye (tilted look direction)
 * was tried first and shifts every projected point by roughly
 * tilt * focal / distance -- the cube landed ~40px from the sprite box it
 * replaces. Keeping the view axis perpendicular to the sprite plane makes
 * registration exact by construction: with focal == FALCON_CAM_BACK, a
 * world point on the Z=0 plane projects to precisely its own framebuffer
 * pixel. The 3D read comes instead from (a) yawing the cube's vertices
 * around its own vertical axis, exposing two side faces, and (b) plain
 * perspective: the cube lives below (or, mid-jump, above) the view axis,
 * so its top (or bottom) face is naturally visible.
 */
#define FALCON_CAM_BACK         150.0f
#define FALCON_CUBE_YAW_DEG      35.0f

#define FALCON_SSAA_SCALE          2
#define FALCON_SSAA_MAX_WIDTH   1024
#define FALCON_SSAA_MAX_HEIGHT   480

/* Falcon alone is rendered at 2x and box-filtered over the already complete
 * NES frame.  This keeps every background tile and native sprite pixel-crisp
 * while giving the now-32px fighter four coverage samples per output pixel. */
static uint32_t
    s_falcon_ssaa[FALCON_SSAA_MAX_WIDTH * FALCON_SSAA_MAX_HEIGHT];

/* Presentation-only death clock. SMB1 still owns the PlayerDeath routine,
 * life decrement, delay, and respawn; these values only drive the replacement
 * mesh's falling Star-KO adaptation. */
static int s_falcon_death_was_active;
static unsigned s_falcon_death_frame;
static float s_falcon_death_start_center_y;

/* Flat placeholder color (a Falcon-blue). One 1x1 texel reused for every
 * face; nes_voxel_mesh_bind_texture's shade parameter fakes basic per-face
 * lighting the same way render_terrain's side faces already do (see
 * voxel_renderer.c), so no real texture image is needed for M6.1/M6.2. */
static const uint32_t k_cube_color[1] = { 0xFF3060C8u };

static int smb1_sprite_height(void) {
    /* PPUCTRL bit 5: 0 = 8x8 sprites, 1 = 8x16. Mirrors ppu_renderer.c's own
     * spr_tall/spr_height computation. */
    return (g_ppuctrl & 0x20) ? 16 : 8;
}

/*
 * Per-slot suppression predicate for ppu_renderer_set_sprite_suppress().
 *
 * Mirrors game_voxel.c:236-248's smb_first_person_sprite_visible bbox
 * against the same screen-space player mirror bytes (g_ram[0x03AD]/[0x03B8]
 * -- distinct from game_smash64.c's Ghidra-cited Player_X_Position, which is
 * internal fixed-point state, not the OAM draw position). That precedent
 * tests one assembled metasprite's bbox against a generous margin (-4..+20
 * horizontally, -4..+28 vertically) sized to cover Mario's whole 1-4-tile
 * posture. This hook fires per OAM slot rather than per assembled
 * metasprite, so it applies the same generous box to each individual
 * sprite's own [x, x+8) x [y, y+height) extent -- every OAM piece of
 * Mario's metasprite falls inside it, and nothing else does.
 *
 * Self-gates on game_smash64_active(): with the mod off (or scripted), this
 * always returns 0 and ppu_render_frame draws every sprite exactly as
 * before.
 */
static int smash64_suppress_player_sprite(int oam_slot, int x, int y,
                                          void *user) {
    int player_x, player_y, spr_h;
    (void)oam_slot;
    (void)user;

    if (!game_smash64_active() &&
        !game_smash64_death_presentation_active()) return 0;

    player_x = g_ram[0x03AD];
    player_y = g_ram[0x03B8];
    spr_h = smb1_sprite_height();

    return x + 8     >= player_x - 4 && x <= player_x + 20 &&
           y + spr_h >= player_y - 4 && y <= player_y + 28;
}

void game_smash64_render_init(void) {
    /* The predicate self-gates, so registering it before the mod is ever
     * enabled changes nothing -- ppu_render_frame calls it every frame, and
     * it returns 0 until game_smash64_active() does. */
    ppu_renderer_set_sprite_suppress(smash64_suppress_player_sprite, NULL);
}

/* One vertex, one 1x1-texel binding: u/v are irrelevant since a 1x1 texture
 * samples the same texel regardless, so every vertex below uses 0,0. */
static NesVoxelMeshVertex mesh_vertex(float x, float y, float z) {
    NesVoxelMeshVertex v;
    v.x = x; v.y = y; v.z = z;
    v.u = 0.0f; v.v = 0.0f;
    return v;
}

static void draw_cube_face(NesVoxelMeshVertex p0, NesVoxelMeshVertex p1,
                           NesVoxelMeshVertex p2, NesVoxelMeshVertex p3,
                           float shade) {
    nes_voxel_mesh_bind_texture(k_cube_color, 1, 1, 1, shade, 0);
    nes_voxel_mesh_triangle(p0, p1, p2);
    nes_voxel_mesh_triangle(p0, p2, p3);
}

static int falcon_ssaa_enabled(void) {
    const char *value = getenv("NESRECOMP_FALCON_SSAA");
    return !value || atoi(value) != 0;
}

static void composite_falcon_ssaa(uint32_t *framebuffer, int width,
                                  int height) {
    const int source_width = width * FALCON_SSAA_SCALE;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const int sx = x * FALCON_SSAA_SCALE;
            const int sy = y * FALCON_SSAA_SCALE;
            const uint32_t samples[4] = {
                s_falcon_ssaa[sy * source_width + sx],
                s_falcon_ssaa[sy * source_width + sx + 1],
                s_falcon_ssaa[(sy + 1) * source_width + sx],
                s_falcon_ssaa[(sy + 1) * source_width + sx + 1]
            };
            unsigned count = 0, red = 0, green = 0, blue = 0;
            uint32_t destination;
            unsigned dr, dg, db;
            for (int i = 0; i < 4; ++i) {
                if ((samples[i] >> 24) == 0) continue;
                ++count;
                red += (samples[i] >> 16) & 0xFFu;
                green += (samples[i] >> 8) & 0xFFu;
                blue += samples[i] & 0xFFu;
            }
            if (!count) continue;

            destination = framebuffer[y * width + x];
            dr = (destination >> 16) & 0xFFu;
            dg = (destination >> 8) & 0xFFu;
            db = destination & 0xFFu;
            /* Averaging the covered model samples with one copy of the
             * untouched NES pixel per uncovered subpixel is a 2x box filter
             * in premultiplied-coverage form. */
            red = (red + (4u - count) * dr + 2u) / 4u;
            green = (green + (4u - count) * dg + 2u) / 4u;
            blue = (blue + (4u - count) * db + 2u) / 4u;
            framebuffer[y * width + x] =
                0xFF000000u | (red << 16) | (green << 8) | blue;
        }
    }
}

void game_smash64_render_post_render(uint32_t *framebuffer) {
    NesVoxelCamera camera;
    uint32_t *target = framebuffer;
    int target_width = g_render_width;
    int target_height = 240;
    float output_scale = 1.0f;
    float cx, cz, foot_y;
    float death_center_y = 0.0f;
    float death_spin = 0.0f;
    float death_anim_frame = 0.0f;
    int death_active;
    float x0, x1, y0, y1, z0, z1;
    NesVoxelMeshVertex a, b, c, d, e, f, g, h;

    if (!framebuffer) return;
    death_active = game_smash64_death_presentation_active();
    if (!game_smash64_active() && !death_active) {
        s_falcon_death_was_active = 0;
        s_falcon_death_frame = 0;
        return;
    }

    if (falcon_ssaa_enabled() &&
        g_render_width * FALCON_SSAA_SCALE <= FALCON_SSAA_MAX_WIDTH &&
        240 * FALCON_SSAA_SCALE <= FALCON_SSAA_MAX_HEIGHT) {
        output_scale = (float)FALCON_SSAA_SCALE;
        target_width = g_render_width * FALCON_SSAA_SCALE;
        target_height = 240 * FALCON_SSAA_SCALE;
        target = s_falcon_ssaa;
        memset(target, 0, (size_t)target_width * target_height * sizeof(*target));
    }

    /*
     * World space IS screen space: X = framebuffer column, Y = 240 minus
     * the framebuffer row (so +Y is up), Z = 0 on the sprite plane. The
     * camera is fixed relative to the SCREEN -- look-at pinned to the view
     * center, never to the cube -- so the cube's projected position moves
     * 1:1 with the player's OAM box on both axes. (The first cut aimed the
     * camera at the cube itself, which glued the cube to one screen spot
     * regardless of where the player went: a camera that follows its
     * subject cannot show the subject moving.)
     */
    cx = ((float)(g_ram[0x03AD] + g_widescreen_left) + 8.0f) *
        output_scale;
    cz = 0.0f;
    /* $03B8 is SMB1's 32px player-box top, not necessarily the top of the
     * small-Mario OAM pieces. Small Mario's one-row metasprite is emitted at
     * a +16px offset inside that box, so both sizes share the authoritative
     * foot row $03B8+32. Measured in ordinary 1-1 play: native_y=$B0 and the
     * floor begins at screen row $D0. */
    foot_y = (240.0f - (float)(g_ram[0x03B8] + 32)) * output_scale;

    if (death_active) {
        const float frame = (float)s_falcon_death_frame;
        if (!s_falcon_death_was_active) {
            s_falcon_death_start_center_y =
                240.0f - (float)(g_ram[0x03B8] + 16);
            s_falcon_death_frame = 0;
        }
        /* DeadUpStar uses DamageFall while translating through depth for 180
         * frames. In a side-view platformer, depth is unreadable, so preserve
         * the tumble and adapt that travel into a gently accelerating fall. */
        death_center_y = (s_falcon_death_start_center_y -
                          (0.30f * frame + 0.018f * frame * frame)) *
                         output_scale;
        death_spin = frame * (18.0f * 3.14159265358979323846f / 180.0f);
        death_anim_frame = frame * 0.5f;
        s_falcon_death_was_active = 1;
        ++s_falcon_death_frame;
    } else {
        s_falcon_death_was_active = 0;
        s_falcon_death_frame = 0;
    }

    x0 = cx - FALCON_CUBE_HALF_WIDTH * output_scale;
    x1 = cx + FALCON_CUBE_HALF_WIDTH * output_scale;
    y0 = foot_y;
    y1 = foot_y + FALCON_CUBE_HEIGHT * output_scale;
    z0 = cz - FALCON_CUBE_HALF_DEPTH * output_scale;
    z1 = cz + FALCON_CUBE_HALF_DEPTH * output_scale;

    /* Yaw the cube's corners around its own vertical axis (see the camera
     * comment): cos/sin of FALCON_CUBE_YAW_DEG, precomputed. */
    {
        const float yc = 0.81915f;   /* cos 35 deg */
        const float ys = 0.57358f;   /* sin 35 deg */
        float rx0, rz0, rx1, rz1, rx2, rz2, rx3, rz3;

        rx0 = cx + (x0 - cx) * yc - (z0 - cz) * ys;
        rz0 = cz + (x0 - cx) * ys + (z0 - cz) * yc;
        rx1 = cx + (x1 - cx) * yc - (z0 - cz) * ys;
        rz1 = cz + (x1 - cx) * ys + (z0 - cz) * yc;
        rx2 = cx + (x1 - cx) * yc - (z1 - cz) * ys;
        rz2 = cz + (x1 - cx) * ys + (z1 - cz) * yc;
        rx3 = cx + (x0 - cx) * yc - (z1 - cz) * ys;
        rz3 = cz + (x0 - cx) * ys + (z1 - cz) * yc;

        a = mesh_vertex(rx0, y0, rz0);
        b = mesh_vertex(rx1, y0, rz1);
        c = mesh_vertex(rx2, y0, rz2);
        d = mesh_vertex(rx3, y0, rz3);
        e = mesh_vertex(rx0, y1, rz0);
        f = mesh_vertex(rx1, y1, rz1);
        g = mesh_vertex(rx2, y1, rz2);
        h = mesh_vertex(rx3, y1, rz3);
    }

    /* Straight-on camera: view axis perpendicular to the sprite plane, eye
     * centered on the view. focal = FALCON_CAM_BACK makes the Z=0 plane
     * project 1:1 (focal_scale is focal/width by the mesh API contract).
     *
     * The eye sits at +Z looking toward -Z. Looking along +Z instead makes
     * build_camera_basis's right vector cross(forward, world-up) come out
     * (-1,0,0) and the whole scene mirrors horizontally -- measured as the
     * cube rendering reflected about the screen center. */
    camera.look_at_x = (float)target_width * 0.5f;
    camera.look_at_y = (float)target_height * 0.5f;
    camera.look_at_z = 0.0f;
    camera.eye_x = camera.look_at_x;
    camera.eye_y = camera.look_at_y;
    camera.eye_z = FALCON_CAM_BACK * output_scale;
    camera.focal_scale = camera.eye_z / (float)target_width;
    camera.center_y = 0.5f;

    if (!nes_voxel_mesh_begin(target, target_width, target_height, &camera))
        return;

    /* The real model is loaded lazily from the ignored local asset blob.
     * Missing or invalid assets deliberately leave the M6.2 cube intact so
     * a publishable checkout remains usable without proprietary data. */
    if (!(death_active
              ? game_smash64_assets_draw_death(
                    cx, death_center_y, output_scale, death_spin,
                    death_anim_frame)
              : game_smash64_assets_draw(cx, foot_y, output_scale))) {
        draw_cube_face(e, f, g, h, 1.00f);  /* top */
        draw_cube_face(a, b, f, e, 0.85f);  /* front (z0, camera-facing) */
        draw_cube_face(d, c, g, h, 0.45f);  /* back */
        draw_cube_face(a, e, h, d, 0.55f);  /* left */
        draw_cube_face(b, c, g, f, 0.70f);  /* right */
        draw_cube_face(a, d, c, b, 0.35f);  /* bottom */
    }

    nes_voxel_mesh_end();
    if (output_scale > 1.0f)
        composite_falcon_ssaa(framebuffer, g_render_width, 240);
}
