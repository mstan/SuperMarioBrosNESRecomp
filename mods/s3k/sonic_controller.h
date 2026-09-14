#pragma once

#include "s3k_player.h"

#include <stdint.h>

#define S3K_SONIC_CONTROLLER_ID "super-mario-bros.s3k.sonic"

/* Audio cues are S3K's own sound ids tagged with 'S3K' in the upper bytes,
 * so the host audio layer can map them without a private table. */
#define S3K_SONIC_AUDIO_TAG         0x53334B00u
#define S3K_SONIC_AUDIO_CUE(id)     (S3K_SONIC_AUDIO_TAG | (uint32_t)(uint8_t)(id))
#define S3K_SONIC_AUDIO_JUMP        S3K_SONIC_AUDIO_CUE(S3K_SFX_JUMP)
#define S3K_SONIC_AUDIO_ROLL        S3K_SONIC_AUDIO_CUE(S3K_SFX_ROLL)
#define S3K_SONIC_AUDIO_SPINDASH    S3K_SONIC_AUDIO_CUE(S3K_SFX_SPINDASH)
#define S3K_SONIC_AUDIO_DASH        S3K_SONIC_AUDIO_CUE(S3K_SFX_DASH)
#define S3K_SONIC_AUDIO_FIRE_DASH   S3K_SONIC_AUDIO_CUE(S3K_SFX_FIRE_ATTACK)
#define S3K_SONIC_AUDIO_INSTA       S3K_SONIC_AUDIO_CUE(S3K_SFX_INSTA_ATTACK)
#define S3K_SONIC_AUDIO_SKID        S3K_SONIC_AUDIO_CUE(S3K_SFX_SKID)

/* Trace-facing locomotion states derived from the S3K object each frame. */
typedef enum S3KSonicMoveState {
    S3K_SONIC_STAND = 300,
    S3K_SONIC_WALK,
    S3K_SONIC_RUN,
    S3K_SONIC_SKID,
    S3K_SONIC_CROUCH,
    S3K_SONIC_SPINDASH,
    S3K_SONIC_ROLL,
    S3K_SONIC_JUMP,
    S3K_SONIC_FALL,
    S3K_SONIC_FIRE_DASH,
    S3K_SONIC_LOOK_UP,
    S3K_SONIC_PUSH,
    S3K_SONIC_BALANCE,
    S3K_SONIC_SPRING,
    S3K_SONIC_INSTA_SHIELD,
    S3K_SONIC_HURT,
    S3K_SONIC_DEATH
} S3KSonicMoveState;

int s3k_sonic_controller_register(void);

/* Live S3K object. The adapter writes through the mutable accessor only for
 * host events S3K itself models as external writes (hurt, enemy bounce,
 * shields, invincibility, water). */
const S3KPlayer *s3k_sonic_player(void);
S3KPlayer *s3k_sonic_player_mut(void);

/* Host facts for the next tick (sampled at the frame's starting position). */
void s3k_sonic_set_environment(const S3KPlayerEnvironment *env);
/* Extra collision facts for the next resolve that ForeignCollisionResult
 * cannot carry. */
void s3k_sonic_set_collision_extras(int spring);

/* This frame's integration velocity (signed 8.8 px/frame, +Y down). Zero on
 * frames S3K skips MoveSprite (jump start, spindash charge/release). */
int16_t s3k_sonic_move_dx(void);
int16_t s3k_sonic_move_dy(void);
/* 1 on the tick Sonic_Jump ran. */
int s3k_sonic_launched_jump(void);

/* Drain S3K sound ids queued by control, reconcile and host events. */
int s3k_sonic_take_sfx(uint8_t *ids, int cap);
/* 1 once after Sonic_Water made a splash (presentation's Dust anim 1). */
int s3k_sonic_take_splash(void);

int s3k_sonic_is_ball(void);
/* Obj_BreakableWall: ball animation with |x_vel| >= $480, pushing the wall
 * on the ground; in the air only the Fire Shield's dash does it. */
int s3k_sonic_breaks_side_blocks(void);
/* Rolling on the ground: the ball's height, which fits a one-tile gap the way
 * a crouching Big Mario does. */
int s3k_sonic_low_profile(void);
/* The Fire Shield's air dash is live (until Sonic lands). */
int s3k_sonic_fire_dashing(void);
/* The dash's flames (Ani_FireShield anim 1, about 24 frames) were out during
 * this frame's control. Unlike S3K, where only the ball attacks, the flames
 * attack whatever their $30x$30 reach touches (the Insta-Shield's box) for
 * as long as they burn, so a dash that lands (on a pipe, say) keeps hitting
 * the enemies it runs into. */
int s3k_sonic_fire_dash_flames(void);
/* SMB1 block hits by the shield moves. The Insta-Shield hits every brick,
 * ? block and hidden block it touches; the Fire Shield's dash, while still
 * at breakable-wall speed, hits the ones its leading edge runs into. */
int s3k_sonic_insta_shield_active(void);
int s3k_sonic_fire_dash_hits_blocks(void);
int s3k_sonic_is_crouching(void);
int s3k_sonic_has_fire_shield(void);
void s3k_sonic_set_fire_shield(int enabled);
int s3k_sonic_has_shield(void);   /* any shield, standard or elemental */
/* Touch_Enemy's "attacking" verdict: rolling/spindash animation,
 * invincibility, an active Insta-Shield, or the Fire Shield dash's flames. */
int s3k_sonic_touch_attacking(void);
/* Touch_Hurt immunity: invulnerability frames, invincibility, hurt bounce,
 * death, or the Insta-Shield's temporary invincibility. */
int s3k_sonic_touch_immune(void);
unsigned s3k_sonic_anim_frame(void);
