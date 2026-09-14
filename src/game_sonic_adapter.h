#pragma once

#include <stddef.h>
#include <stdint.h>

struct S3KRingSpill;

/* Sonic is presented at 4/5 of S3K's pixel size, so his 39px standing body
 * reads like Big Mario's 32px one. Everything drawn for him and his touch
 * geometry use this scale; S3K's velocities and radii keep source units. */
#define SONIC_SCALE_NUM 4
#define SONIC_SCALE_DEN 5

static inline int sonic_scale_px(int v)
{
    return v >= 0 ? (v * SONIC_SCALE_NUM + SONIC_SCALE_DEN / 2) / SONIC_SCALE_DEN
                  : -((-v * SONIC_SCALE_NUM + SONIC_SCALE_DEN / 2) /
                      SONIC_SCALE_DEN);
}

/*
 * SMB1 host consequences for the S3K Sonic controller: S3K's TouchResponse
 * against SMB enemies, HurtCharacter/Kill_Character mapped onto SMB's power
 * state, power-ups as shields, S3K sensor probes, springs, and the area
 * parser servicing that lets S3K speeds stream through SMB1 worlds.
 *
 * Movement integration itself lives in game_smash64.c beside the other
 * player hooks it shares state with.
 */

int  game_sonic_adapter_register_hooks(void);
void game_sonic_adapter_set_enabled(int enabled);

/* PlayerPhysicsSub: publish S3K's sensor facts for this frame's control. */
void game_sonic_adapter_prepare_control(void);

/* SMB1 collides Sonic as a crouching Big Mario: a ball rolling on the
 * ground, or one that jumped out of a gap it still does not stand up in. */
int game_sonic_adapter_low_profile(void);

/* The Fire Shield dash broke into a block this frame. */
void game_sonic_adapter_note_dash_plow(void);

/* SMB1's jumpspring wrote `force` into Player_Y_Speed. */
void game_sonic_adapter_spring_launch(int8_t force);

/* Play every S3K sound id the controller has queued. */
void game_sonic_adapter_play_sfx(uint64_t frame);

/* InjuryTimer read at ChkForPlayerInjury/InjurePlayer. */
uint8_t game_sonic_adapter_injury_read(uint16_t pc, uint8_t val);

/* Enemy slot `slot` holds a platform that carried Sonic at its latest
 * collision check (last frame, for a slot the enemy loop has not reached). */
int game_sonic_adapter_platform_carried(int slot);

/* Pixels the horizontal lift Sonic is riding will carry him later in this
 * frame's enemy loop (PositionPlayerOnHPlat), computed from its movement
 * state before it runs; 0 when he is not riding one. */
int game_sonic_adapter_lift_step(void);

/* Post-NMI: pending hazard hits, rings, parser servicing. */
void game_sonic_adapter_post_frame(uint64_t frame);

/* Owner-ROM tables the adapter needs (SineTable for Obj_Bouncing_Ring). */
void game_sonic_adapter_load_owner_data(const uint8_t *rom, size_t size);

/* Scattered rings, for presentation. */
const struct S3KRingSpill *game_sonic_adapter_rings(void);

/* Brick chunks for bricks Sonic's ball shatters sideways. SMB1 animates
 * debris in its two block-object slots; a spindash through a wall breaks a
 * brick every few frames, so each brick gets its own four chunks here,
 * moved exactly as BlockObjectsCore moves a Block_State $12 pair. */
#define SONIC_BRICK_DEBRIS_MAX 32

typedef struct SonicBrickChunkRow {
    uint8_t y_pos;       /* Block_Y_Position   */
    uint8_t y_high;      /* Block_Y_HighPos    */
    uint8_t y_speed;     /* Block_Y_Speed      */
    uint8_t y_force;     /* Block_Y_MoveForce  */
    uint8_t ymf_dummy;   /* Block_YMF_Dummy    */
} SonicBrickChunkRow;

typedef struct SonicBrickDebris {
    uint8_t active;
    uint8_t pad;
    int16_t orig_x;              /* Block_Orig_XPos (world pixels)       */
    int16_t x;                   /* the left-moving chunks (world pixels) */
    SonicBrickChunkRow row[2];   /* top pair, and the pair 8px below     */
} SonicBrickDebris;

/* tile_x: world x of the brick's left edge; tile_top: its screen y. */
void game_sonic_adapter_spawn_brick_debris(int tile_x, int tile_top);
const SonicBrickDebris *game_sonic_adapter_brick_debris(void);

/* The Sonic host's own frame-to-frame state in game_smash64.c, which the
 * adapter's savestate record carries: MoveCameraX's Pos_table, the 8.8
 * sub-pixels and the jumpspring latch. Without it, a state loaded in a
 * running session kept the history of wherever Sonic was before the load, and
 * a spindash released within 32 frames aimed the camera there. */
#define SONIC_CAMERA_HISTORY 64

typedef struct SonicHostSave {
    int32_t x_history[SONIC_CAMERA_HISTORY];   /* world x, newest at index */
    uint8_t x_history_index;
    uint8_t x_history_valid;
    uint8_t x_sub;
    uint8_t y_sub;
    uint8_t spring_armed;
    uint8_t pad[3];
} SonicHostSave;

void game_smash64_sonic_save_host(SonicHostSave *out);
/* NULL (a record from before the host state was saved) starts it the way a
 * fresh session does. */
void game_smash64_sonic_load_host(const SonicHostSave *in);

/* Implemented in game_smash64.c. The in-loop variant is for a touch found
 * while SMB1 processes enemy `slot`, before later slots have run. */
void game_smash64_sonic_reconcile(void);
void game_smash64_sonic_reconcile_in_enemy_loop(int slot);
/* ExecGameLoopback is about to move the world `dx` pixels. */
void game_smash64_sonic_shift_world_x(int dx);
/* Pixels Sonic's own vertical move covered this frame (+down). */
int game_smash64_sonic_frame_dy(void);
