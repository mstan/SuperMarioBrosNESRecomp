/*
 * game_smash64_render.c — M6.1/M6.2 presentation glue for the Smash 64
 * player replacement mod. See game_smash64_render.h for scope and the
 * screen-to-world convention.
 *
 * Deliberately thin and read-only against game_smash64.c: everything here
 * reads a presentation predicate or g_ram's screen-space player mirror bytes,
 * and only ever writes into the presentation framebuffer via the voxel mesh
 * API. Nothing here touches NES RAM, ownership, or physics.
 */
#include "game_smash64_render.h"

#include "game_smash64_assets.h"
#include "game_smash64_actions.h"
#include "game_smash64.h"
#include "nes_runtime.h"
#include "voxel_renderer.h"

#include "generated/super-mario-bros_full_decls.h"

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
#define SMB1_PLAYFIELD_TOP         32
#define FALCON_DEATH_HIDE_MARGIN 32.0f

/* Falcon alone is rendered at 2x and box-filtered over the already complete
 * NES frame.  This keeps every background tile and native sprite pixel-crisp
 * while giving the now-32px fighter four coverage samples per output pixel. */
static uint32_t
    s_falcon_ssaa[FALCON_SSAA_MAX_WIDTH * FALCON_SSAA_MAX_HEIGHT];
static uint32_t
    s_native_status_bar[FALCON_SSAA_MAX_WIDTH * SMB1_PLAYFIELD_TOP];

/* Presentation-only death clock. SMB1 still owns the PlayerDeath routine,
 * life decrement, delay, and respawn; these values only drive the replacement
 * mesh's falling Star-KO adaptation. */
static int s_falcon_death_sequence_latched;
static int s_falcon_death_hidden;
static unsigned s_falcon_death_frame;
static float s_falcon_death_start_center_y;
static Smash64ScriptedPresentation s_scripted_presentation;
static unsigned s_scripted_presentation_frame;

/* Flat placeholder color (a Falcon-blue). One 1x1 texel reused for every
 * face; nes_voxel_mesh_bind_texture's shade parameter fakes basic per-face
 * lighting the same way render_terrain's side faces already do (see
 * voxel_renderer.c), so no real texture image is needed for M6.1/M6.2. */
static const uint32_t k_cube_color[1] = { 0xFF3060C8u };

/*
 * Per-slot suppression predicate for ppu_renderer_set_sprite_suppress().
 *
 * Player identity comes from SMB1's own Player_SprDataOffset rather than a
 * coordinate guess, so clipping and wrapping near the HUD cannot expose one
 * or more native Mario tiles.
 *
 * Self-gates on the ordinary and narrowly scoped scripted presentation
 * predicates. With the mod off this always returns 0 and ppu_render_frame
 * draws every sprite exactly as before.
 */
static int smash64_suppress_player_sprite(int oam_slot, int x, int y,
                                          void *user) {
    int player_oam_byte, first_player_oam_byte;
    (void)x;
    (void)y;
    (void)user;

    if (!game_smash64_active() &&
        !game_smash64_death_presentation_active() &&
        !game_smash64_still_presentation_active() &&
        !game_smash64_swim_presentation_active() &&
        game_smash64_scripted_presentation() ==
            SMASH64_SCRIPTED_PRESENTATION_NONE) return 0;

    /* Ghidra nes/SuperMarioBrosNES: RenderPlayerSub $EFBE loads
     * Player_SprDataOffset $06E4 at $EFD9, and PlayerGfxProcessing $EF45
     * passes four rows to it. Each row is two four-byte OAM entries, so the
     * player's identity is this exact eight-slot/32-byte block. Unlike the
     * old coordinate-overlap guess, it remains correct when top-edge clipping
     * dumps some rows to $F8 or wraps their screen Y near the HUD. */
    first_player_oam_byte = g_ram[Player_SprDataOffset];
    player_oam_byte = oam_slot * 4;
    return player_oam_byte >= first_player_oam_byte &&
           player_oam_byte < first_player_oam_byte + 32;
}

void game_smash64_render_init(void) {
    /* The predicate self-gates, so registering it before the mod is ever
     * enabled changes nothing -- ppu_render_frame calls it every frame, and
     * it returns 0 until a Falcon presentation predicate does. */
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

static void draw_persistent_effect_card(unsigned effect, unsigned frame,
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
        v[i] = mesh_vertex(center_x + x[i] * c - y[i] * s,
                           center_y + x[i] * s + y[i] * c, z);
    }
    v[0].u = 0.0f;                 v[0].v = 0.0f;
    v[1].u = (float)texture_width; v[1].v = 0.0f;
    v[2].u = (float)texture_width; v[2].v = (float)texture_height;
    v[3].u = 0.0f;                 v[3].v = (float)texture_height;
    nes_voxel_mesh_bind_texture(pixels, texture_width, texture_height,
                                texture_width, 1.0f, 1);
    /* PikachuSpecial3's alpha cards are two-sided. */
    nes_voxel_mesh_triangle(v[0], v[1], v[2]);
    nes_voxel_mesh_triangle(v[0], v[2], v[3]);
    nes_voxel_mesh_triangle(v[2], v[1], v[0]);
    nes_voxel_mesh_triangle(v[3], v[2], v[0]);
}

static unsigned pikachu_jolt_material_frame(unsigned joint, unsigned phase)
{
    /* Exact texture-id spans from the six 342:PikachuSpecial3
     * ThunderJoltBMatAnimJoint streams (0x1AE0).  The source loop duration
     * is 10/9/9/10/8/9 frames respectively; each stream selects card 0 or 1.
     */
    static const unsigned period[6] = { 10u, 9u, 9u, 10u, 8u, 9u };
    const unsigned p = phase % period[joint];
    switch (joint) {
    case 0: return (p >= 2u && p < 3u) || (p >= 4u && p < 5u);
    case 1: return p >= 4u && p < 6u || p == 8u;
    case 2: return p == 8u;
    case 3: return p == 1u || p == 3u || p >= 5u;
    case 4: return p >= 3u && p < 4u || p == 5u;
    default: return p >= 6u && p < 7u;
    }
}

static int pikachu_jolt_card_visible(unsigned joint, unsigned phase)
{
    /* The matching six ThunderJoltBAnimJoint SetFlags streams (0x1A78..
     * 0x1AC4) gate each card.  Bit 0x002 is hidden; flag 0 exposes it.
     * This traveling visibility gate is why a single static card is wrong. */
    phase %= 9u;
    switch (joint) {
    case 0: return phase >= 1u && phase < 5u;
    case 1: return phase >= 3u && phase < 7u;
    case 2: return phase >= 5u && phase < 9u;
    case 3: return phase < 4u;
    case 4: return phase >= 2u && phase < 6u;
    default: return phase >= 4u && phase < 8u;
    }
}

static void draw_pikachu_jolt_rig(const Smash64ActionSlot *action,
                                  float center_x, float center_y,
                                  float output_scale)
{
    /* Ground Jolt is an eight-DObj rig, not the transient two-card Thunder
     * Jolt hit effect. wpPikachuThunderJoltGroundAddAnim reattaches its
     * 0x1A20 AnimJoint and 0x1AE0 material streams at every surface segment
     * and turn. Joint 1 sweeps -390..600 over 9 frames; joints 2..7 carry
     * the six cards with authored -45,+15,+75,-75,-15,+45 degree rotations.
     * Evaluate those visibility/material timelines here against saved action
     * age, keeping physics and deterministic save state entirely separate.
     */
    static const float card_angle[6] = {
        -0.785398006f, 0.261799008f, 1.30899704f,
        -1.30899704f, -0.261799008f, 0.785398006f
    };
    const unsigned phase = action->age % 90u;
    const float unit = output_scale > 0.0f ? output_scale : 1.0f;
    const float tangent_x = (float)action->vx;
    const float tangent_y = -(float)action->vy;
    const float length = sqrtf(tangent_x * tangent_x + tangent_y * tangent_y);
    const float heading = length > 0.0001f ? atan2f(tangent_y, tangent_x) : 0.0f;
    /* The source's -390..600 local translation is in its effect coordinate
     * system. Map that 990-unit cycle to a compact 10px host-space sweep,
     * preserving direction and phase without turning a 16px SMB projectile
     * into an 80px collision-looking billboard. */
    const float root_shift = (-5.0f + 10.0f * (float)(phase % 9u) / 8.0f) * unit;
    unsigned joint;
    for (joint = 0; joint < 6u; ++joint) {
        if (!pikachu_jolt_card_visible(joint, phase)) continue;
        draw_persistent_effect_card(
            SMASH64_PIKACHU_EFFECT_THUNDER_JOLT,
            pikachu_jolt_material_frame(joint, phase),
            center_x + cosf(heading) * root_shift,
            center_y + sinf(heading) * root_shift,
            3.5f * unit, 4.5f * unit,
            heading + card_angle[joint], 3.0f * unit);
    }
}

static void draw_persistent_actions(float output_scale)
{
    Smash64ActionSlot slots[SMASH64_ACTION_SLOT_CAPACITY];
    const double screen_left =
        (double)g_ram[ScreenLeft_PageLoc] * 256.0 +
        (double)g_ram[ScreenLeft_X_Pos];
    int i, count = smash64_actions_snapshot(
        slots, SMASH64_ACTION_SLOT_CAPACITY);
    for (i = 0; i < count; ++i) {
        const Smash64ActionSlot *action = &slots[i];
        float center_x = (float)(action->x - screen_left +
                                 g_widescreen_left) * output_scale;
        /* Action simulation uses native framebuffer rows, where +Y points
         * down. The voxel renderer's world convention is the opposite (+Y
         * points up), exactly like the fighter foot conversion below. Keep
         * the simulation native and invert only at this presentation seam.
         * Without this conversion, a Jolt physically following the floor at
         * row 204 was drawn near row 36 and appeared to fly through the HUD. */
        float center_y = (240.0f - (float)action->y) * output_scale;
        float half_width = fmaxf(2.0f, (float)action->width * 0.5f) *
                           output_scale;
        float half_height = fmaxf(2.0f, (float)action->height * 0.5f) *
                            output_scale;
        const unsigned effect = action->kind == 2u
                                    ? SMASH64_PIKACHU_EFFECT_THUNDER
                                    : SMASH64_PIKACHU_EFFECT_THUNDER_JOLT;
        if (effect == SMASH64_PIKACHU_EFFECT_THUNDER_JOLT) {
            if (action->age == 0u) {
                float joint_x, joint_y;
                /* Source ftPikachuSpecialN calls
                 * gmCollisionGetFighterPartsWorldPosition(joints[11]). The
                 * persistent action already owns collision at its bridge
                 * origin, but its first visible card must use the same
                 * evaluated attachment rather than a fixed sprite offset. */
                if (game_smash64_assets_pikachu_joint11_screen(&joint_x,
                                                               &joint_y)) {
                    center_x = joint_x;
                    center_y = joint_y;
                }
            }
            draw_pikachu_jolt_rig(action, center_x, center_y, output_scale);
            continue;
        }
        /* Persistent actions advance at NES cadence.  Source cards are a
         * short material cycle, so the action age is the exact deterministic
         * phase key; its physics/save data remains untouched. */
        draw_persistent_effect_card(effect, action->age, center_x, center_y,
                                    half_width, half_height, 0.0f,
                                    2.0f * output_scale);
    }
}

static int falcon_ssaa_enabled(void) {
    const char *value = getenv("NESRECOMP_FALCON_SSAA");
    return !value || atoi(value) != 0;
}

static void composite_falcon_ssaa(uint32_t *framebuffer, int width,
                                  int height, int behind_background) {
    const int source_width = width * FALCON_SSAA_SCALE;
    /* The first four tile rows are SMB1's fixed HUD. Native player sprites
     * are clipped as they leave the playfield; never paint the replacement
     * mesh over score text. */
    for (int y = SMB1_PLAYFIELD_TOP; y < height; ++y) {
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
            if (behind_background &&
                ppu_renderer_background_opaque(x, y))
                continue;
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

static void restore_falcon_priority(uint32_t *framebuffer,
                                    const uint32_t *before,
                                    int width, int height,
                                    int behind_background) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (y < SMB1_PLAYFIELD_TOP ||
                (behind_background &&
                 ppu_renderer_background_opaque(x, y))) {
                framebuffer[y * width + x] = before[y * width + x];
            }
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
    int still_active;
    int swim_active;
    int preserve_status_bar = 0;
    int preserve_native_frame = 0;
    int behind_background = 0;
    Smash64ScriptedPresentation scripted_presentation;
    float x0, x1, y0, y1, z0, z1;
    NesVoxelMeshVertex a, b, c, d, e, f, g, h;

    if (!framebuffer) return;
    death_active = game_smash64_death_presentation_active();
    still_active = game_smash64_still_presentation_active();
    swim_active = game_smash64_swim_presentation_active();
    scripted_presentation = game_smash64_scripted_presentation();
    behind_background =
        (scripted_presentation == SMASH64_SCRIPTED_PRESENTATION_PIPE_SIDE ||
         scripted_presentation ==
             SMASH64_SCRIPTED_PRESENTATION_PIPE_VERTICAL) &&
        (g_ram[Player_SprAttrib] & 0x20) != 0;
    if (!game_smash64_active() && !death_active && !still_active &&
        !swim_active &&
        scripted_presentation == SMASH64_SCRIPTED_PRESENTATION_NONE) {
        /* OperMode and the game-engine dispatch can briefly leave their death
         * values during the native restart flow. Do not treat those transient
         * frames as a new death: the presentation stays latched and, once it
         * has left the screen, hidden. A genuine return to ordinary control
         * below is the only reset point. */
        s_scripted_presentation = SMASH64_SCRIPTED_PRESENTATION_NONE;
        s_scripted_presentation_frame = 0;
        return;
    }

    if (scripted_presentation != s_scripted_presentation) {
        s_scripted_presentation = scripted_presentation;
        s_scripted_presentation_frame = 0;
    } else if (scripted_presentation !=
               SMASH64_SCRIPTED_PRESENTATION_NONE) {
        ++s_scripted_presentation_frame;
    }

    if (falcon_ssaa_enabled() &&
        g_render_width * FALCON_SSAA_SCALE <= FALCON_SSAA_MAX_WIDTH &&
        240 * FALCON_SSAA_SCALE <= FALCON_SSAA_MAX_HEIGHT) {
        output_scale = (float)FALCON_SSAA_SCALE;
        target_width = g_render_width * FALCON_SSAA_SCALE;
        target_height = 240 * FALCON_SSAA_SCALE;
        target = s_falcon_ssaa;
        memset(target, 0, (size_t)target_width * target_height * sizeof(*target));
    } else if ((size_t)g_render_width * 240u <=
               sizeof(s_falcon_ssaa) / sizeof(s_falcon_ssaa[0])) {
        preserve_native_frame = 1;
        memcpy(s_falcon_ssaa, framebuffer,
               (size_t)g_render_width * 240u * sizeof(*framebuffer));
    } else if (g_render_width <= FALCON_SSAA_MAX_WIDTH) {
        preserve_status_bar = 1;
        memcpy(s_native_status_bar, framebuffer,
               (size_t)g_render_width * SMB1_PLAYFIELD_TOP *
                   sizeof(*framebuffer));
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
    cx = ((float)(g_ram[Player_Rel_XPos] + g_widescreen_left) + 8.0f) *
        output_scale;
    cz = 0.0f;
    /* $03B8 is SMB1's 32px player-box top, not necessarily the top of the
     * small-Mario OAM pieces. Small Mario's one-row metasprite is emitted at
     * a +16px offset inside that box, so both sizes share the authoritative
     * foot row $03B8+32. Measured in ordinary 1-1 play: native_y=$B0 and the
     * floor begins at screen row $D0. */
    {
        int player_y = g_ram[Player_Rel_YPos];
        /* SMB1's ordinary visible playfield is Y high page 1. Preserve the
         * whole signed 16-bit displacement from that page: World 1-2's legal
         * above-ceiling route continues well past $00f0, and treating only
         * that first wrapped strip as negative makes Falcon reappear through
         * the floor once the low byte reaches $ef. Conversely, pit travel on
         * page 2 must remain below the screen instead of wrapping overhead. */
        player_y += ((int)(int8_t)g_ram[Player_Y_HighPos] - 1) * 0x100;
        foot_y = (240.0f - (float)(player_y + 32)) * output_scale;
    }

    if (death_active) {
        const float frame = (float)s_falcon_death_frame;
        if (!s_falcon_death_sequence_latched) {
            s_falcon_death_start_center_y =
                240.0f - (float)(g_ram[0x03B8] + 16);
            s_falcon_death_frame = 0;
            s_falcon_death_hidden = 0;
            s_falcon_death_sequence_latched = 1;
        }
        /* DeadUpStar uses DamageFall while translating through depth for 180
         * frames. In a side-view platformer, depth is unreadable, so preserve
         * the tumble and adapt that travel into a gently accelerating fall. */
        death_center_y = (s_falcon_death_start_center_y -
                          (0.30f * frame + 0.018f * frame * frame)) *
                         output_scale;
        death_spin = frame * (18.0f * 3.14159265358979323846f / 180.0f);
        death_anim_frame = frame * 0.5f;
        if (death_center_y < -FALCON_DEATH_HIDE_MARGIN * output_scale)
            s_falcon_death_hidden = 1;
        ++s_falcon_death_frame;
    } else if (game_smash64_active() || swim_active) {
        /* Ordinary Falcon control or ordinary native swimming proves SMB1
         * completed the prior death and respawn. The next PlayerDeath may now
         * begin one fresh fall. */
        s_falcon_death_sequence_latched = 0;
        s_falcon_death_hidden = 0;
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
    if (!((death_active && s_falcon_death_hidden) ||
          (death_active
              ? game_smash64_assets_draw_death(
                    cx, death_center_y, output_scale, death_spin,
                    death_anim_frame)
              : (scripted_presentation !=
                         SMASH64_SCRIPTED_PRESENTATION_NONE
                     ? game_smash64_assets_draw_scripted(
                           cx, foot_y, output_scale, scripted_presentation,
                           (float)s_scripted_presentation_frame)
                     : (still_active
                            ? game_smash64_assets_draw_idle(
                                  cx, foot_y, output_scale)
                            : (swim_active
                                   ? game_smash64_assets_draw_swim(
                                         cx, foot_y, output_scale,
                                         g_ram[PlayerFacingDir] == 1)
                                   : game_smash64_assets_draw(
                                         cx, foot_y, output_scale))))))) {
        draw_cube_face(e, f, g, h, 1.00f);  /* top */
        draw_cube_face(a, b, f, e, 0.85f);  /* front (z0, camera-facing) */
        draw_cube_face(d, c, g, h, 0.45f);  /* back */
        draw_cube_face(a, e, h, d, 0.55f);  /* left */
        draw_cube_face(b, c, g, f, 0.70f);  /* right */
        draw_cube_face(a, d, c, b, 0.35f);  /* bottom */
    }

    draw_persistent_actions(output_scale);

    nes_voxel_mesh_end();
    if (output_scale > 1.0f) {
        composite_falcon_ssaa(framebuffer, g_render_width, 240,
                              behind_background);
    } else if (preserve_native_frame) {
        restore_falcon_priority(framebuffer, s_falcon_ssaa,
                                g_render_width, 240, behind_background);
    } else if (preserve_status_bar) {
        memcpy(framebuffer, s_native_status_bar,
               (size_t)g_render_width * SMB1_PLAYFIELD_TOP *
                   sizeof(*framebuffer));
    }
}
