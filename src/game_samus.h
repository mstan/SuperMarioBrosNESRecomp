#pragma once

#include <stdint.h>

int game_samus_set_enabled(int enabled, const char *owner_rom_path);
int game_samus_active(void);
int game_samus_register_hooks(void);
void game_samus_update_input(uint64_t frame_count);
void game_samus_update(uint64_t frame_count);
void game_samus_render_post_render(uint32_t *framebuffer);
