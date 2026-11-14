#pragma once

#include <stdint.h>

/* Widescreen presentation and the separately selectable traversal policy. */
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
void game_backtracking_set_enabled(int enabled);
int game_backtracking_active(void);
int game_backtracking_compose_native(uint32_t *out,const uint32_t *native);
