/*
 * Super Mario Bros. semantic profile for NESRecomp's opt-in screen diorama.
 * Brown blocks and green terrain gain depth; clouds and HUD art stay flat.
 */
#include "game_voxel.h"

#include "nes_runtime.h"
#include "voxel_screen_profile.h"

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

    /* Overworld collision materials are warm brick/soil or dense green pipe
     * and hill masses. White clouds remain part of the painted ground plane,
     * rather than becoming arbitrary floating cubes. */
    if (sample->warm_pixels >= 4)
        return sample->non_background_pixels >= 32 ? 16.0f : 12.0f;
    if (sample->green_pixels >= 8 &&
        sample->non_background_pixels >= 16)
        return 12.0f;

    /* Underground/castle rooms use a dark universal background and cool
     * masonry palettes, so density is the more reliable solid signal there. */
    if (bg_sum < 150u && sample->non_background_pixels >= 14)
        return sample->non_background_pixels >= 36 ? 16.0f : 10.0f;
    return 0.0f;
}

static const NesVoxelScreenProfile s_profile = {
    "Super Mario Bros. diorama",
    32, 208, 32, 0, 85,
    25, -20, 0, 100, 120,
    0xFF637BDDu, 0xFFBBD8F0u,
    smb_scene_visible,
    smb_tile_height,
    0
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
