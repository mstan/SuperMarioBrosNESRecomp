#pragma once

#include <stdint.h>

int game_link_set_enabled(int enabled, const char *owner_rom_path);
int game_link_active(void);
int game_link_register_hooks(void);
void game_link_update_input(uint64_t frame_count);
void game_link_update(uint64_t frame_count);
void game_link_render_post_render(uint32_t *framebuffer);
