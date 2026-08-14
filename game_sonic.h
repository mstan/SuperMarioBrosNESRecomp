#pragma once

#include <stdint.h>

int game_sonic_set_enabled(int enabled, const char *owner_rom_path);
int game_sonic_active(void);
int game_sonic_register_hooks(void);
void game_sonic_update_input(uint64_t frame_count);
void game_sonic_update(uint64_t frame_count);
void game_sonic_render_post_render(uint32_t *framebuffer);
