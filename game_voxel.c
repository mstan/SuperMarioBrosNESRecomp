/*
 * Super Mario Bros. first-person experiment for NESRecomp's opt-in voxel
 * compositor. The camera rides at Mario's screen-relative position and looks
 * forward along the course through an upright reconstruction of the level.
 */
#include "game_voxel.h"

#include "nes_runtime.h"
#include "voxel_screen_profile.h"

#include <math.h>

#define SMB_PI 3.14159265358979323846f
#define SMB_SOURCE_Y 32

static NesVoxelScreenState s_voxel;

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

static void smb_first_person_camera(NesVoxelScreenCamera *camera,
                                    float pitch, float yaw, float roll,
                                    float zoom_percent, void *user) {
    float player_x = (float)g_ram[0x03AD] + 8.0f;
    float player_y = (float)g_ram[0x03B8];
    /* In the upright side-scroller layout, +X is level progress and screen Y
     * is actual world height. Keep the course direction stable: Right moves
     * forward, Left backpedals, and numpad yaw is deliberate head turning. */
    float heading = yaw * SMB_PI / 180.0f;
    float look_pitch = (pitch - 15.0f) * SMB_PI / 180.0f;
    float look_distance = 128.0f;
    (void)roll;
    (void)user;

    if (player_x < 8.0f || player_x > 248.0f) player_x = 64.0f;
    if (player_y < 32.0f || player_y > 224.0f) player_y = 176.0f;

    camera->enabled = 1;
    camera->eye_x = player_x + 5.0f;
    camera->eye_y = clamp_float(
        (float)(SMB_SOURCE_Y + 208) - player_y - 8.0f,
        12.0f, 196.0f);
    camera->eye_z = 0.0f;
    camera->look_at_x =
        camera->eye_x + cosf(heading) * cosf(look_pitch) * look_distance;
    camera->look_at_y =
        camera->eye_y + sinf(look_pitch) * look_distance;
    camera->look_at_z =
        camera->eye_z + sinf(heading) * cosf(look_pitch) * look_distance;
    camera->focal_scale =
        clamp_float(0.72f * zoom_percent / 100.0f, 0.42f, 1.25f);
    camera->center_y = 0.53f;
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
    nes_voxel_screen_set_enabled(&s_voxel, enabled);
}

void game_voxel_configure_mod(int pitch, int yaw, int roll,
                              int zoom_percent, int sprite_scale_percent) {
    nes_voxel_screen_configure(&s_voxel, pitch, yaw, roll,
                               zoom_percent, sprite_scale_percent);
}

void game_voxel_handle_event(const SDL_Event *event) {
    nes_voxel_screen_handle_event(&s_voxel, event);
}

void game_voxel_init(void) {
    nes_voxel_screen_init(&s_voxel, &s_profile);
}

void game_voxel_update(void) {
    nes_voxel_screen_update(&s_voxel, &s_profile);
}

void game_voxel_post_render(uint32_t *framebuffer) {
    nes_voxel_screen_post_render(&s_voxel, &s_profile, framebuffer);
}
