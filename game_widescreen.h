#pragma once

#include <stdint.h>

/* Default-off custom renderer. Rendering never changes guest screen edges. */
void game_widescreen_set_mod_enabled(int enabled);
void game_widescreen_configure(const char *aspect, const char *hud, const char *enemies);
void game_widescreen_set_camera(const char *camera);
int game_widescreen_view_left(int native_camera, int width);
void game_widescreen_actor_range(int native_camera, int width, int pad, int *left, int *right);
void game_widescreen_begin_frame(void);
void game_widescreen_init(void);
void game_widescreen_update(void);
int game_widescreen_arg(const char *key, const char *value);
int game_widescreen_debug(const char *cmd, int id);
int game_widescreen_column_hook(uint16_t addr);
