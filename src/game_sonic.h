#pragma once

#include <stdint.h>

int game_sonic_set_enabled(int enabled, const char *owner_rom_path);
/* Optional Sonic 2 (Rev A) owner ROM for the standard shield's art; call
 * before enabling. NULL or an unreadable file keeps the Bubble stand-in. */
void game_sonic_set_sonic2_rom(const char *path);
int game_sonic_active(void);
int game_sonic_register_hooks(void);
void game_sonic_update_input(uint64_t frame_count);
void game_sonic_update(uint64_t frame_count);
/* Shows the previous frame's Sonic over the picture (which is SMB1's
 * previous frame), then draws this frame's for the next one. */
void game_sonic_render_post_render(uint32_t *framebuffer);
/* A savestate replaced the running frame. */
void game_sonic_note_state_loaded(void);
/* A castle loopback moved the world `dx` pixels: move the presentation's
 * world-x records (dust puffs, splash, the invincibility trail) with it. */
void game_sonic_shift_world_x(int dx);
