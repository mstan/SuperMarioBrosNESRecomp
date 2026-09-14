#pragma once

#include "game_sonic_adapter.h"

#include <stdint.h>

/*
 * SMB1's block objects, jumping coins and power-ups beyond SMB1's own slots
 * while Sonic is the player (game_sonic_items.c).
 */

#define SONIC_BUMP_BLOCK_MAX 32
#define SONIC_JUMP_COIN_MAX  32
#define SONIC_POWERUP_MAX    16
/* Enemy slot 5's bytes PowerUpObjHandler runs on, and PowerUpType. */
#define SONIC_POWERUP_BYTES  24

/* A block bouncing after a hit (BouncingBlockHandler). */
typedef struct SonicBumpBlock {
    uint8_t active;       /* 1 bouncing, 2 settled: its metatile goes back */
    uint8_t metatile;     /* Block_Metatile                                */
    uint8_t bbuf_low;     /* Block_BBuf_Low                                */
    uint8_t orig_ypos;    /* Block_Orig_YPos                               */
    int16_t x;            /* Block_PageLoc:Block_X_Position (world pixels) */
    SonicBrickChunkRow row;
} SonicBumpBlock;

/* A coin jumping out of a block, then its floatey "200" (ProcJumpCoin). */
typedef struct SonicJumpCoin {
    uint8_t state;        /* Misc_State: 1 rising coin, 2-$2F the number   */
    uint8_t pad;
    int16_t x;            /* Misc_PageLoc:Misc_X_Position (world pixels)   */
    SonicBrickChunkRow row;
} SonicJumpCoin;

/* A power-up that a newer item would have replaced in enemy slot 5. */
typedef struct SonicPowerUp {
    uint8_t active;
    uint8_t bytes[SONIC_POWERUP_BYTES];
    uint8_t oam[16];      /* the four sprites DrawPowerUp wrote last run   */
} SonicPowerUp;

typedef struct SonicItems {
    SonicBumpBlock blocks[SONIC_BUMP_BLOCK_MAX];
    SonicJumpCoin coins[SONIC_JUMP_COIN_MAX];
    SonicPowerUp powerups[SONIC_POWERUP_MAX];
} SonicItems;

int  game_sonic_items_register_hooks(void);
void game_sonic_items_set_enabled(int enabled);
void game_sonic_items_clear(void);

/* Around PlayerHeadCollision for a block the host hits for Sonic: SMB1's
 * block slot, jumping-coin slots and BlockBounceTimer are set aside, and what
 * the hit made of them moves into the pools before they are put back. */
void game_sonic_items_begin_host_hit(void);
void game_sonic_items_end_host_hit(void);

/* A pooled block still owns the $23 it left at this BlockBufferCollision
 * address ($06 low byte, $02 row offset) until its metatile goes back. */
int game_sonic_items_owns_cell(uint8_t bbuf_low, uint8_t row);

/* A block is still bouncing out of this cell and will put a metatile back,
 * whether SMB1's own slot or the pool animates it. Its cell can already read
 * as air: an enemy standing on a bumped block blanks it
 * (EnemyToBGCollisionDet), though the block is still there. */
int game_sonic_items_cell_bouncing(uint8_t bbuf_low, uint8_t row);

/* Pooled power-ups, in the guest frame after SMB1's own objects. */
void game_sonic_items_run_power_ups(void);

/* Bouncing blocks and jumping coins, once per guest frame after it ran. */
void game_sonic_items_post_frame(void);

void game_sonic_items_shift_world_x(int dx);
const SonicItems *game_sonic_items(void);
void game_sonic_items_save(SonicItems *out);
/* NULL clears the pools. */
void game_sonic_items_load(const SonicItems *in);

/* ImposeGravity with no upward force: `down` added to Y_MoveForce each frame,
 * Y speed held at `max`. */
void game_sonic_items_impose_gravity(SonicBrickChunkRow *r, uint8_t down,
                                     uint8_t max);
