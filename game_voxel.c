/*
 * Super Mario Bros. first-person experiment for NESRecomp's opt-in voxel
 * compositor. The camera rides at Mario's screen-relative position and looks
 * along his facing direction through the reconstructed level geometry.
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

static float smb_tile_height(const NesVoxelScreenSample *sample,
                             void *user) {
    unsigned bg_sum =
        ((sample->background >> 16) & 0xFFu) +
        ((sample->background >> 8) & 0xFFu) +
        (sample->background & 0xFFu);
    (void)user;
    if (sample->non_background_pixels < 5) return 0.0f;

    /* Warm brick/soil are reliable structural materials. Green is deliberately
     * left flat in first person: the framebuffer-only sampler cannot reliably
     * distinguish pipes from large decorative hills, and a false-positive
     * hill becomes an impassable wall directly in front of the camera. */
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
    int facing = g_ram[0x0033] == 2 ? -1 : 1;
    float player_x = (float)g_ram[0x03AD] + 8.0f;
    float player_y = (float)g_ram[0x03B8];
    float heading = (facing < 0 ? SMB_PI : 0.0f) +
                    yaw * SMB_PI / 180.0f;
    float look_pitch = (pitch - 15.0f) * SMB_PI / 180.0f;
    float look_distance = 128.0f;
    (void)roll;
    (void)user;

    if (player_x < 8.0f || player_x > 248.0f) player_x = 64.0f;
    if (player_y < 32.0f || player_y > 224.0f) player_y = 176.0f;

    camera->enabled = 1;
    camera->eye_x = player_x + facing * 5.0f;
    camera->eye_y = 10.0f;
    /* Screen Y is the tabletop depth axis. Sitting slightly north of
     * Mario's feet puts the lens in the open lane immediately above the
     * ground row instead of inside its raised prisms. */
    camera->eye_z = clamp_float(
        player_y + 8.0f - SMB_SOURCE_Y, 12.0f, 192.0f);
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

static const NesVoxelScreenProfile s_profile = {
    "Super Mario Bros. first-person voxel",
    32, 208, 32, 0, 85,
    15, 0, 0, 100, 120,
    0xFF637BDDu, 0xFFBBD8F0u,
    smb_scene_visible,
    smb_tile_height,
    0,
    smb_first_person_camera,
    smb_first_person_sprite_visible
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
