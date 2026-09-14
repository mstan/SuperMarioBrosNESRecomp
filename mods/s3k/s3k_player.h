/*
 * s3k_player.h -- Sonic 3 & Knuckles player object core, ported from
 * skdisasm (sonic3k.asm) with exact 68000 word/byte arithmetic.
 *
 * This module is the "how does Sonic want to move" half only. It never sees
 * NES RAM: a host feeds it the logical pad, then reports what its own
 * collision did with the motion. Everything else -- ground_vel, x_vel,
 * y_vel, status bits, the spindash counter, the Insta-Shield flag, the
 * animation script state -- is S3K's own object state with S3K's own units:
 *
 *   velocities   signed 8.8 pixels per frame (x_vel, y_vel, ground_vel)
 *   positions    host-owned; S3K adds (vel << 8) into a 16.16 position
 *   Y axis       grows DOWNWARD, as in S3K
 *
 * One S3K frame is split at the only point a host that owns collision can
 * split it:
 *
 *   s3k_player_control()   Sonic_Control's mode code up to MoveSprite:
 *                          Spindash, Jump, Move, Roll, RollSpeed,
 *                          JumpHeight/ShieldMoves, ChgJumpDir. Produces the
 *                          velocity to integrate this frame.
 *   (host integrates and collides)
 *   s3k_player_reconcile() the collision half of the same frame (landing =
 *                          Player_TouchFloor, walls, ceilings, walking off
 *                          a ledge), then Sonic_Display timers, Sonic_Water,
 *                          Animate_Sonic and the shield/dust objects.
 *
 * SMB1 has no slopes, loops or tubes, so angle is always 0 and the code paths
 * gated on a non-zero angle are intentionally absent rather than stubbed.
 */
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Ctrl_1_logical bit layout (sonic3k.constants.asm button_*). */
#define S3K_BTN_UP     0x01u
#define S3K_BTN_DOWN   0x02u
#define S3K_BTN_LEFT   0x04u
#define S3K_BTN_RIGHT  0x08u
#define S3K_BTN_B      0x10u
#define S3K_BTN_C      0x20u
#define S3K_BTN_A      0x40u
#define S3K_BTN_START  0x80u
#define S3K_BTN_ABC    (S3K_BTN_A | S3K_BTN_B | S3K_BTN_C)

/* status(a0) bits (Status_*). */
#define S3K_STATUS_FACING_LEFT 0x01u
#define S3K_STATUS_IN_AIR      0x02u
#define S3K_STATUS_ROLL        0x04u
#define S3K_STATUS_ON_OBJ      0x08u
#define S3K_STATUS_ROLL_JUMP   0x10u
#define S3K_STATUS_PUSH        0x20u
#define S3K_STATUS_UNDERWATER  0x40u

/* status_secondary(a0) bits. */
#define S3K_STATUS2_SHIELD      0x01u
#define S3K_STATUS2_INVINCIBLE  0x02u
#define S3K_STATUS2_SPEED_SHOES 0x04u
#define S3K_STATUS2_FIRE        0x10u
#define S3K_STATUS2_LIGHTNING   0x20u
#define S3K_STATUS2_BUBBLE      0x40u
#define S3K_STATUS2_ELEMENTAL   (S3K_STATUS2_FIRE | S3K_STATUS2_LIGHTNING | \
                                 S3K_STATUS2_BUBBLE)

/* Player routine(a0). */
#define S3K_ROUTINE_CONTROL 2
#define S3K_ROUTINE_HURT    4
#define S3K_ROUTINE_DEATH   6

/* AniSonic script ids used by gameplay code. */
#define S3K_ANIM_WALK       0x00
#define S3K_ANIM_RUN        0x01
#define S3K_ANIM_ROLL       0x02
#define S3K_ANIM_ROLL2      0x03
#define S3K_ANIM_PUSH       0x04
#define S3K_ANIM_WAIT       0x05
#define S3K_ANIM_BALANCE    0x06
#define S3K_ANIM_LOOK_UP    0x07
#define S3K_ANIM_DUCK       0x08
#define S3K_ANIM_SPINDASH   0x09
#define S3K_ANIM_BALANCE2   0x0C
#define S3K_ANIM_SKID       0x0D
#define S3K_ANIM_SPRING     0x10
#define S3K_ANIM_DEATH      0x18
#define S3K_ANIM_HURT       0x1A

/* S3K sound ids (sonic3k.constants.asm sfx_*), used verbatim as cues. */
#define S3K_SFX_DEATH           0x35
#define S3K_SFX_SKID            0x36
#define S3K_SFX_SPIKE_HIT       0x37
#define S3K_SFX_SPLASH          0x39
#define S3K_SFX_ROLL            0x3C
#define S3K_SFX_FIRE_SHIELD     0x3E
#define S3K_SFX_BUBBLE_SHIELD   0x3F
#define S3K_SFX_LIGHTNING_SHIELD 0x41
#define S3K_SFX_INSTA_ATTACK    0x42
#define S3K_SFX_FIRE_ATTACK     0x43
#define S3K_SFX_BUBBLE_ATTACK   0x44
#define S3K_SFX_ELECTRIC_ATTACK 0x45
#define S3K_SFX_JUMP            0x62
#define S3K_SFX_SPRING          0xB1
#define S3K_SFX_RING_LOSS       0xB9
#define S3K_SFX_SPINDASH        0xAB
#define S3K_SFX_DASH            0xB6

#define S3K_PLAYER_SFX_CAPACITY 4

/* Dash-dust object (Obj_DashDust at a6) requests. */
#define S3K_DUST_NONE     0
#define S3K_DUST_SPINDASH 1  /* anim(a6) = 2 while charging */
#define S3K_DUST_SKID     2  /* routine(a6) = 6, frames spawned per skid */

typedef struct S3KPlayer {
    int16_t  x_vel;
    int16_t  y_vel;
    int16_t  ground_vel;
    uint8_t  status;
    uint8_t  status_secondary;
    uint8_t  routine;

    int16_t  max_speed;      /* Max_speed    */
    int16_t  acceleration;   /* Acceleration */
    int16_t  deceleration;   /* Deceleration */

    uint8_t  y_radius;
    uint8_t  x_radius;
    uint8_t  jumping;
    uint8_t  double_jump_flag;
    uint8_t  spin_dash_flag;
    uint16_t spin_dash_counter;
    uint16_t move_lock;
    uint8_t  scroll_delay_counter;
    uint8_t  invulnerability_timer;
    uint8_t  invincibility_timer;
    uint8_t  speed_shoes_timer;
    uint8_t  air_left;
    /* Sonic_Display skipped Draw_Sprite this frame (invulnerability blink). */
    uint8_t  display_hidden;

    /* Animate_Sonic state. */
    uint8_t  anim;
    uint8_t  prev_anim;
    uint8_t  anim_frame;
    uint8_t  anim_frame_timer;
    uint8_t  mapping_frame;
    uint8_t  render_hflip;

    /* Shield object (Obj_InstaShield / Obj_FireShield ...) animation. */
    uint8_t  shield_anim;
    uint8_t  shield_prev_anim;
    uint8_t  shield_anim_frame;
    uint8_t  shield_anim_timer;
    uint8_t  shield_mapping_frame;
    uint8_t  shield_facing;  /* status(a0) orientation bit the shield holds */
    uint8_t  shield_hflip;   /* render flip of the current shield mapping   */

    /* Dash dust object (Obj_DashDust) request, presentation only. */
    uint8_t  dust_state;
    uint8_t  dust_timer;

    /* H_scroll_frame_offset written by spindash release / fire dash. */
    uint16_t h_scroll_frame_offset;

    uint16_t level_frame_counter;

    /* One-shot host requests produced by control. */
    uint8_t  launched_jump;     /* Sonic_Jump ran: host must leave ground */
    uint8_t  sfx_count;
    uint8_t  sfx[S3K_PLAYER_SFX_CAPACITY];
} S3KPlayer;

/* Host observations for the collision half of a frame. The host fills this
 * after it has applied the velocity s3k_player_control() produced. */
typedef struct S3KPlayerCollision {
    uint8_t on_ground;       /* feet on floor after this frame's motion   */
    uint8_t hit_wall;        /* horizontal motion was stopped             */
    int8_t  wall_side;       /* -1 left wall, +1 right wall               */
    uint8_t hit_ceiling;     /* upward motion was stopped by a ceiling    */
    uint8_t has_imposed_y_vel; /* host launched/bounced the player itself */
    int16_t imposed_y_vel;
    uint8_t spring;          /* the imposed launch was a spring (sfx/anim) */
} S3KPlayerCollision;

/* Host facts consulted by control, sampled at the position the player
 * starts the frame at (which is where S3K's own sensors would look). */
typedef struct S3KPlayerEnvironment {
    uint8_t underwater;      /* host level is an underwater level          */
    uint8_t room_overhead;   /* CalcRoomOverHead result >= 6 (jump allowed) */
    /* Floor probes for Sonic_Balance: floor within reach below x, under the
     * x+radius (next_tilt) and x-radius (tilt) sensors, and at x-6 / x+6. */
    uint8_t floor_center;
    uint8_t floor_right;
    uint8_t floor_left;
    uint8_t floor_center_left6;
    uint8_t floor_center_right6;
    /* The roll's spin_dash_flag is held by a host tunnel, not by S3K level
     * design: Sonic_MdRoll lets it jump (room_overhead still applies). */
    uint8_t tunnel_jump;
} S3KPlayerEnvironment;

void s3k_player_init(S3KPlayer *p);

/* Sonic_Control mode code for one frame, up to (not including) collision.
 * Returns the velocity to integrate in *move_dx / *move_dy (8.8, +Y down):
 * zero on frames S3K itself skips MoveSprite (jump start, spindash). */
void s3k_player_control(S3KPlayer *p, uint8_t held, uint8_t pressed,
                        const S3KPlayerEnvironment *env,
                        int16_t *move_dx, int16_t *move_dy);

/* Collision half of the same frame plus display timers and animation. */
void s3k_player_reconcile(S3KPlayer *p, const S3KPlayerCollision *hit,
                          uint8_t held);

/* Sonic_Water entry/exit with S3K's velocity halving. Returns 1 when the
 * crossing makes a splash (Dust anim 1, sfx_Splash queued). */
int s3k_player_set_underwater(S3KPlayer *p, int underwater);

/* HurtCharacter with the source's knockback. `from_left` is nonzero when
 * the hazard is to Sonic's left (Sonic x >= hazard x). Clears shields. */
void s3k_player_hurt(S3KPlayer *p, int from_left, int spike);

/* Kill_Character. */
void s3k_player_kill(S3KPlayer *p);

/* Touch_EnemyNormal bounce after destroying an enemy. `player_below` is the
 * source's "y_pos(a0) >= y_pos(a1)" test. */
void s3k_player_enemy_bounce(S3KPlayer *p, int player_below);

/* SonicKnux_Roll's curl without its sound: a host keeps a moving ball
 * curled (Status_Roll, roll radii, ball animation). */
void s3k_player_curl(S3KPlayer *p);

/* Elemental shield grant/removal (status_secondary). */
void s3k_player_set_shield(S3KPlayer *p, uint8_t elemental_bits);

void s3k_player_set_invincible(S3KPlayer *p, int invincible);

/* Predicates the host uses for touch response. */
int s3k_player_touch_attacking(const S3KPlayer *p);   /* anim 2 / 9     */
int s3k_player_insta_shield_active(const S3KPlayer *p);
int s3k_player_invincible(const S3KPlayer *p);
int s3k_player_is_ball(const S3KPlayer *p);

/* Touch box (Touch_NoInstaShield / Insta-Shield), relative to the object's
 * centre: left/top offsets and width/height in pixels. */
void s3k_player_touch_box(const S3KPlayer *p, int *left, int *top,
                          int *width, int *height);

int s3k_player_take_sfx(S3KPlayer *p, uint8_t *out, int cap);

#ifdef __cplusplus
}
#endif
