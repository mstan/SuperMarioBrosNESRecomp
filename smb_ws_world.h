#pragma once
#include <stdint.h>

enum { SMB_WS_META_COLUMNS = 512, SMB_WS_TILE_COLUMNS = 1024, SMB_WS_ROWS = 26 };
enum { SMB_WS_MAX_PLANTS = 256 };
typedef struct { uint16_t x; uint8_t y; } SmbWsPlant;
typedef struct {
    uint32_t version;
    uint16_t area_data;
    uint8_t area_type, world, valid;
    uint8_t tiles[SMB_WS_TILE_COLUMNS][SMB_WS_ROWS];
    uint8_t palettes[SMB_WS_TILE_COLUMNS][SMB_WS_ROWS];
    uint8_t metatiles[SMB_WS_META_COLUMNS][13];
    uint8_t collision[SMB_WS_META_COLUMNS][13];
    int16_t block_world[32];
    int16_t nt_world[2][32], pending_world[2][32];
    uint8_t pending_tiles[2][32][SMB_WS_ROWS];
    uint32_t decoded_columns, verified_columns, mismatched_columns;
    int first_mismatch_column, first_mismatch_row;
    uint8_t first_expected, first_actual;
    int16_t flag_x;
    uint16_t plant_count;
    SmbWsPlant plants[SMB_WS_MAX_PLANTS];
} SmbWsWorld;

extern SmbWsWorld g_smb_ws_world;
void smb_ws_world_reset(void);
void smb_ws_world_update(void);
void smb_ws_world_observe_column(void);
int smb_ws_world_pixel(int world_x, int y, uint8_t *palette, uint8_t *tile);
int smb_ws_world_busy(void);
int smb_ws_world_flag_x(void);
void smb_ws_world_begin_column(void);
