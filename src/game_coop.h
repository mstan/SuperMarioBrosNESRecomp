#pragma once
#include <stdint.h>

int game_coop_register(void);
void game_coop_configure(int players, int shared_pause);
int game_coop_enabled(void);
void game_coop_before_frame(void);
int game_coop_suppress_sprite(int slot);
void game_coop_render(uint32_t *framebuffer);
int game_coop_debug(const char *command, int id, const char *json);
int game_coop_arg(const char *key, const char *value);
