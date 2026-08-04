/*
 * Super Mario Bros. first-person experiment for NESRecomp's opt-in voxel
 * compositor. The camera rides at Mario's screen-relative position and looks
 * forward along the course through an upright reconstruction of the level.
 */
#include "game_voxel.h"

#include "config.h"
#include "controller.h"
#include "nes_runtime.h"
#include "voxel_screen_profile.h"

#include <math.h>
#include <stdio.h>

#define SMB_PI 3.14159265358979323846f
#define SMB_SOURCE_Y 32

static NesVoxelScreenState s_voxel;
static float s_first_person_heading;
static float s_first_person_target_heading;
static float s_first_person_aim_pitch;
static float s_first_person_crouch_offset;
static float s_first_person_free_yaw;
static float s_right_stick_x;
static float s_right_stick_y;
static int s_first_person_heading_initialized;
static int s_first_person_was_crouching;
static int s_mod_enabled;
static int s_tank_facing;
static int s_tank_facing_initialized;
static uint8_t s_first_person_raw_buttons;
static uint64_t s_first_person_raw_buttons_frame = UINT64_MAX;
static int s_first_person_input_overridden;

static int smb_scene_visible(const uint32_t *framebuffer,
                             int stride, void *user) {
    uint8_t mode = g_ram[0x0770];
    (void)framebuffer;
    (void)stride;
    (void)user;
    return mode == 1 || mode == 2;
}

static uint8_t smb_metatile_at_sample(
    const NesVoxelScreenSample *sample) {
    int camera_x = ((int)g_ram[0x071A] << 8) | g_ram[0x071C];
    int screen_x = -(camera_x & 15) + sample->tile_x * 8 + 4;
    int world_x = camera_x + screen_x;
    int row = sample->tile_y / 2;
    int column;
    int buffer;

    if (world_x < 0 || row < 0 || row >= 13) return 0;
    column = (world_x >> 4) & 15;
    buffer = ((world_x >> 8) & 1) ? 0x05D0 : 0x0500;
    return g_ram[buffer + row * 16 + column];
}

static float smb_tile_height(const NesVoxelScreenSample *sample,
                             void *user) {
    uint8_t metatile = smb_metatile_at_sample(sample);
    unsigned bg_sum =
        ((sample->background >> 16) & 0xFFu) +
        ((sample->background >> 8) & 0xFFu) +
        (sample->background & 0xFFu);
    (void)user;
    if (sample->non_background_pixels < 5) return 0.0f;

    /* Use SMB's native collision/metatile buffers for green structures that
     * cannot safely be recognized from color alone.  $12-$15 are vertical
     * pipe quadrants; $24-$25 are the flagpole cap and shaft. Decorative
     * hills use different metatiles and remain flat scenery. */
    if ((metatile >= 0x12 && metatile <= 0x15) ||
        metatile == 0x24 || metatile == 0x25)
        return 16.0f;

    /* Scenery such as 3-1's fence and trees is painted into the nametable but
     * deliberately absent from SMB's collision/metatile buffer.  Keep those
     * pixels on the background plane instead of turning their warm colors
     * into first-person walls. */
    if (metatile == 0)
        return 0.0f;

    /* Warm brick/soil are reliable structural materials. Green is deliberately
     * otherwise left flat in first person: a false-positive hill would become
     * an impassable wall directly in front of the camera. */
    if (sample->warm_pixels >= 4)
        return sample->non_background_pixels >= 32 ? 16.0f : 12.0f;

    /* Underground/castle rooms use a dark universal background and cool
     * masonry palettes, so density is the more reliable solid signal there. */
    if (bg_sum < 150u && sample->non_background_pixels >= 14)
        return sample->non_background_pixels >= 36 ? 16.0f : 10.0f;
    return 0.0f;
}

static float clamp_float(float value, float low, float high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

static float ease_heading(float current, float target) {
    float delta = target - current;
    while (delta > 180.0f) delta -= 360.0f;
    while (delta < -180.0f) delta += 360.0f;
    if (delta > -0.25f && delta < 0.25f) return target;
    current += delta * 0.38f;
    while (current > 180.0f) current -= 360.0f;
    while (current < -180.0f) current += 360.0f;
    return current;
}

static void restore_first_person_input(void) {
    if (s_first_person_input_overridden &&
        s_first_person_raw_buttons_frame == g_frame_count)
        g_controller1_buttons = s_first_person_raw_buttons;
    s_first_person_input_overridden = 0;
}

static int current_tank_facing(void) {
    if (!s_tank_facing_initialized) {
        s_tank_facing = g_ram[0x0033] == 2 ? 2 : 1;
        s_tank_facing_initialized = 1;
    }
    return s_tank_facing;
}

static void smb_first_person_camera(NesVoxelScreenCamera *camera,
                                    float pitch, float yaw, float roll,
                                    float zoom_percent, void *user) {
    float player_x = (float)g_ram[0x03AD] + 8.0f;
    float player_y = (float)g_ram[0x03B8];
    float heading;
    float look_pitch;
    float look_distance = 128.0f;
    float upward_blend;
    float vertical_look;
    float target_aim_pitch;
    int crouching = g_ram[0x0714] != 0 && g_ram[0x0754] == 0;
    (void)roll;
    (void)user;

    if (player_x < 8.0f || player_x > 248.0f) player_x = 64.0f;
    /* Screen Y=0 with world-page Y=1 is valid in 1-2's upper route. The
     * former blanket <32 fallback teleported the eye down to the ordinary
     * ground layer and exposed the warp room below Mario. Retain a fallback
     * for transition/death wraparound on other world-page values. */
    if (player_y > 239.0f ||
        (player_y < 32.0f && g_ram[0x00B5] != 1))
        player_y = 176.0f;

    /* Tank-facing is presentation state selected by Left/Right. It remains
     * stable while Down backpedals, rather than flipping with Mario's native
     * movement direction. */
    if (!s_first_person_heading_initialized) {
        s_first_person_heading =
            current_tank_facing() == 2 ? 180.0f : 0.0f;
        s_first_person_target_heading = s_first_person_heading;
        s_first_person_heading_initialized = 1;
    }
    if (current_tank_facing() == 2 &&
        s_first_person_target_heading != 180.0f) {
        s_first_person_target_heading = 180.0f;
        printf("[Voxel] SMB first-person facing left: heading=180\n");
    } else if (current_tank_facing() == 1 &&
               s_first_person_target_heading != 0.0f) {
        s_first_person_target_heading = 0.0f;
        printf("[Voxel] SMB first-person facing right: heading=0\n");
    }
    s_first_person_heading = ease_heading(
        s_first_person_heading, s_first_person_target_heading);
    s_first_person_free_yaw +=
        ((fabsf(s_right_stick_x) > 0.18f
              ? s_right_stick_x * 70.0f : 0.0f) -
         s_first_person_free_yaw) * 0.24f;
    heading =
        (s_first_person_heading + yaw + s_first_person_free_yaw) *
        SMB_PI / 180.0f;

    /* Right-stick vertical look mirrors the Zelda first-person experiment.
     * Full Up stops just shy of the mathematical 90-degree singularity, which
     * is visually straight up but leaves the renderer a stable basis. */
    vertical_look = s_right_stick_y;
    if (vertical_look < -0.18f)
        target_aim_pitch =
            89.0f * (-vertical_look - 0.18f) / 0.82f;
    else if (vertical_look > 0.18f)
        target_aim_pitch =
            -25.0f * (vertical_look - 0.18f) / 0.82f;
    else
        target_aim_pitch = 0.0f;
    s_first_person_aim_pitch +=
        (target_aim_pitch - s_first_person_aim_pitch) * 0.30f;
    upward_blend =
        clamp_float(s_first_person_aim_pitch / 89.0f, 0.0f, 1.0f);
    look_pitch =
        ((pitch - 15.0f) + s_first_person_aim_pitch) *
        SMB_PI / 180.0f;

    /* CrouchingFlag ($714) distinguishes a real tall-Mario crouch from small
     * Mario merely holding Down and from pipe-entry input. */
    if (crouching != s_first_person_was_crouching) {
        printf("[Voxel] SMB first-person camera %s crouch eye level\n",
               crouching ? "entered" : "left");
        s_first_person_was_crouching = crouching;
    }
    s_first_person_crouch_offset +=
        ((crouching ? -10.0f : 0.0f) -
         s_first_person_crouch_offset) * 0.35f;

    camera->enabled = 1;
    /* The normal five-pixel forward offset prevents wall clipping. Remove it
     * during the overhead check so Mario's own vertical column is centered. */
    camera->eye_x =
        player_x + cosf(heading) * 5.0f * (1.0f - upward_blend);
    camera->eye_y = clamp_float(
        (float)(SMB_SOURCE_Y + 208) - player_y - 8.0f +
            s_first_person_crouch_offset,
        12.0f, 232.0f);
    camera->eye_z = 0.0f;
    camera->look_at_x =
        camera->eye_x + cosf(heading) * cosf(look_pitch) * look_distance;
    camera->look_at_y =
        camera->eye_y + sinf(look_pitch) * look_distance;
    camera->look_at_z =
        camera->eye_z + sinf(heading) * cosf(look_pitch) * look_distance;
    camera->focal_scale = clamp_float(
        (0.72f - 0.14f * upward_blend) *
            zoom_percent / 100.0f,
        0.40f, 1.25f);
    camera->center_y = 0.55f - 0.05f * upward_blend;
}

static int smb_first_person_sprite_visible(int min_x, int min_y,
                                           int max_x, int max_y,
                                           void *user) {
    int player_x = g_ram[0x03AD];
    int player_y = g_ram[0x03B8];
    (void)user;
    /* Suppress only the metasprite occupying Mario's body. Enemies, items,
     * particles, and projectiles remain camera-facing cards in the world. */
    if (max_x >= player_x - 4 && min_x <= player_x + 20 &&
        max_y >= player_y - 4 && min_y <= player_y + 28)
        return 0;
    return 1;
}

static int smb_metatile_grid_offset(void *user) {
    int camera_x = ((int)g_ram[0x071A] << 8) | g_ram[0x071C];
    (void)user;
    return -(camera_x & 15);
}

static const NesVoxelScreenProfile s_profile = {
    "Super Mario Bros. first-person voxel",
    32, 208, 32, 0, 85,
    15, 0, 0, 100, 120,
    0xFF637BDDu, 0xFFBBD8F0u,
    smb_scene_visible,
    smb_tile_height,
    0,
    smb_first_person_camera,
    smb_first_person_sprite_visible,
    NES_VOXEL_LAYOUT_SIDE,
    2,
    smb_metatile_grid_offset,
    16
};

void game_voxel_set_mod_enabled(int enabled) {
    if (!enabled)
        restore_first_person_input();
    s_mod_enabled = enabled != 0;
    nes_voxel_screen_set_enabled(&s_voxel, enabled);
}

void game_voxel_configure_mod(int pitch, int yaw, int roll,
                              int zoom_percent, int sprite_scale_percent) {
    s_first_person_heading_initialized = 0;
    s_first_person_aim_pitch = 0.0f;
    s_first_person_crouch_offset = 0.0f;
    s_first_person_free_yaw = 0.0f;
    s_right_stick_x = s_right_stick_y = 0.0f;
    s_first_person_was_crouching = 0;
    s_tank_facing_initialized = 0;
    s_first_person_raw_buttons_frame = UINT64_MAX;
    restore_first_person_input();
    nes_voxel_screen_configure(&s_voxel, pitch, yaw, roll,
                               zoom_percent, sprite_scale_percent);
}

void game_voxel_handle_event(const SDL_Event *event) {
    int view_was_enabled = s_voxel.view_enabled;
    if (s_mod_enabled && event &&
        event->type == SDL_CONTROLLERAXISMOTION &&
        g_nes_config.player_src[0] == 2 &&
        controller_instance_is_player(event->caxis.which, 1)) {
        float value = event->caxis.value < 0
            ? (float)event->caxis.value / 32768.0f
            : (float)event->caxis.value / 32767.0f;
        if (event->caxis.axis == SDL_CONTROLLER_AXIS_RIGHTX)
            s_right_stick_x = value;
        else if (event->caxis.axis == SDL_CONTROLLER_AXIS_RIGHTY)
            s_right_stick_y = value;
    } else if (event &&
               event->type == SDL_CONTROLLERDEVICEREMOVED) {
        s_right_stick_x = s_right_stick_y = 0.0f;
    }
    nes_voxel_screen_handle_event(&s_voxel, event);
    if (view_was_enabled && !s_voxel.view_enabled)
        restore_first_person_input();
}

void game_voxel_init(void) {
    nes_voxel_screen_init(&s_voxel, &s_profile);
}

void game_voxel_update_input(void) {
    uint8_t raw;
    uint8_t directions;
    uint8_t mapped = 0;
    int facing;

    if (!s_mod_enabled || !s_voxel.view_enabled ||
        !smb_scene_visible(0, 0, 0)) {
        restore_first_person_input();
        return;
    }
    if (s_first_person_raw_buttons_frame != g_frame_count) {
        s_first_person_raw_buttons = g_controller1_buttons;
        s_first_person_raw_buttons_frame = g_frame_count;
    }
    raw = s_first_person_raw_buttons;
    directions = raw & 0x0Fu;
    facing = current_tank_facing();

    /* Compact tank controls for SMB's one-dimensional world:
     * Left/Right select facing without walking; Up advances in that facing;
     * Down backpedals while the camera continues to face forward. */
    if ((directions & 0x02u) && !(directions & 0x01u))
        facing = 2;
    else if ((directions & 0x01u) && !(directions & 0x02u))
        facing = 1;
    s_tank_facing = facing;

    if ((directions & 0x08u) && !(directions & 0x04u))
        mapped = facing == 2 ? 0x02u : 0x01u;
    else if ((directions & 0x04u) && !(directions & 0x08u)) {
        /* Preserve SMB's real crouch when tall Mario is grounded. Small Mario
         * cannot crouch, so Down remains useful as tank-style reverse there. */
        if (g_ram[0x0754] == 0 && g_ram[0x001D] == 0)
            mapped = 0x04u;
        else
            mapped = facing == 2 ? 0x01u : 0x02u;
    }

    g_controller1_buttons = (raw & 0xF0u) | mapped;
    s_first_person_input_overridden = 1;
}

void game_voxel_update(void) {
    nes_voxel_screen_update(&s_voxel, &s_profile);
}

void game_voxel_post_render(uint32_t *framebuffer) {
    NesVoxelScreenProfile scene_profile = s_profile;
    uint32_t background =
        g_nes_palette[g_ppu_pal[0] & 0x3Fu];

    /* Preserve the level's actual environment color.  SMB swaps universal
     * background palettes for daytime, night, underground, and castle areas;
     * a fixed blue gradient made every one of those scenes look outdoors. */
    scene_profile.sky_top = background;
    scene_profile.sky_bottom = background;
    nes_voxel_screen_post_render(
        &s_voxel, &scene_profile, framebuffer);
}
