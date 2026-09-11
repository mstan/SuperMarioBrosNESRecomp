#pragma once
#include <stdint.h>

typedef enum { SMB_ENEMIES_NATIVE, SMB_ENEMIES_CLASSIC, SMB_ENEMIES_VIEWPORT } SmbEnemyMode;
void smb_ws_actors_configure(int enabled, SmbEnemyMode mode);
void smb_ws_actors_reset(void);
void smb_ws_actors_begin_frame(void);
void smb_ws_actors_update(void);
void smb_ws_actors_draw(uint32_t *out, int width, int native_x0, int render_camera, const uint8_t *opaque);
int smb_ws_actors_debug(const char *cmd, int id);
int smb_ws_actors_suppress_sprite(int oam_slot);
