/* Deterministic, clean-room Pikachu action controller for the SMB bridge.
 * Values are source-facing units; adapters perform the single 0.08 conversion. */
#ifndef PIKACHU_LOCOMOTION_H
#define PIKACHU_LOCOMOTION_H

#include <stdint.h>

#define PIKACHU_SOURCE_SCALE 0.08
#define PIKACHU_SOURCE_SIZE 0.95
#define PIKACHU_SOURCE_WALK_MULTIPLIER 0.42
#define PIKACHU_SOURCE_WALK_MIDDLE_STICK_MIN 26
#define PIKACHU_SOURCE_WALK_FAST_STICK_MIN 62
#define PIKACHU_SOURCE_DASH_SPEED 60.0
#define PIKACHU_SOURCE_DASH_DECEL 4.5
#define PIKACHU_SOURCE_DASH_TO_RUN_FRAMES 13u
#define PIKACHU_SOURCE_RUN_STICK_MIN 50
#define PIKACHU_SOURCE_RUN_SPEED 55.0
#define PIKACHU_SOURCE_TRACTION 2.0
#define PIKACHU_SOURCE_RUN_BRAKE_FRICTION 2.5
#define PIKACHU_SOURCE_RUN_BRAKE_FRAMES 20u
#define PIKACHU_SOURCE_TURN_RUN_FLIP_FRAME 13u
#define PIKACHU_SOURCE_TURN_RUN_FRAMES 18u
#define PIKACHU_SOURCE_CROUCH_FRAMES 4u
#define PIKACHU_SOURCE_CROUCH_END_FRAMES 8u
#define PIKACHU_SOURCE_LANDING_FRAMES 8u
#define PIKACHU_SOURCE_LANDING_HEAVY_FRAMES 16u
#define PIKACHU_SOURCE_KNEEBEND_FRAMES 3u
#define PIKACHU_SOURCE_ATTACK_AIR_SKIP_LANDING_VEL_Y (-20.0)
#define PIKACHU_SOURCE_LANDING_AIR_NULL_FRAMES 16u
#define PIKACHU_SOURCE_LANDING_AIR_F_FRAMES 16u
#define PIKACHU_SOURCE_LANDING_AIR_D_FRAMES 40u
#define PIKACHU_SOURCE_JAB_FRAMES 34u
#define PIKACHU_SOURCE_FTILT_FRAMES 30u
#define PIKACHU_SOURCE_NAIR_FRAMES 37u
#define PIKACHU_SOURCE_FAIR_FRAMES 40u
#define PIKACHU_SOURCE_BAIR_FRAMES 42u
#define PIKACHU_SOURCE_DAIR_FRAMES 45u
#define PIKACHU_SOURCE_DASH_ATTACK_FRAMES 57u
#define PIKACHU_SOURCE_UTILT_FRAMES 26u
#define PIKACHU_SOURCE_DTILT_FRAMES 26u
#define PIKACHU_SOURCE_UAIR_FRAMES 34u
#define PIKACHU_SOURCE_THUNDER_JOLT_FRAMES 64u
#define PIKACHU_SOURCE_GRAVITY 3.0
#define PIKACHU_SOURCE_TERMINAL_VELOCITY 52.0
#define PIKACHU_SOURCE_JUMP_COUNT 2
#define PIKACHU_SOURCE_JUMP_LAUNCH_VELOCITY 90.6
#define PIKACHU_SOURCE_JUMP_HORIZONTAL_MULTIPLIER 0.35
#define PIKACHU_SOURCE_JUMP_GROUND_FRAMES 45u
#define PIKACHU_SOURCE_JUMP_AERIAL_FRAMES 60u
#define PIKACHU_SOURCE_QUICK_ATTACK_AIM_FRAMES 20u
#define PIKACHU_SOURCE_QUICK_ATTACK_ZIP_FRAMES 5u
#define PIKACHU_SOURCE_QUICK_ATTACK_SECOND_AIM_FRAMES 9u
#define PIKACHU_SOURCE_QUICK_ATTACK_STICK_CAP 80.0
#define PIKACHU_SOURCE_QUICK_ATTACK_BASE_SPEED 90.0
#define PIKACHU_SOURCE_QUICK_ATTACK_STICK_SPEED 3.0
#define PIKACHU_SOURCE_QUICK_ATTACK_SECOND_MULTIPLIER 0.9
#define PIKACHU_SOURCE_QUICK_ATTACK_STICK_MIN 60.0
#define PIKACHU_SOURCE_QUICK_ATTACK_VELOCITY_BACKUP_MULTIPLIER 0.2
#define PIKACHU_SOURCE_QUICK_ATTACK_FALL_SPECIAL_DRIFT 0.4
#define PIKACHU_SOURCE_QUICK_ATTACK_FALL_SPECIAL_LANDING_FRAMES 20u
#define PIKACHU_SOURCE_QUICK_ATTACK_END_ANIMATION_FRAMES 46u
#define PIKACHU_SOURCE_THUNDER_SPAWN_FRAME 24u
#define PIKACHU_SOURCE_THUNDER_START_GROUND_CLIP_FRAMES 24u
#define PIKACHU_SOURCE_THUNDER_START_AIR_CLIP_FRAMES 24u
#define PIKACHU_SOURCE_THUNDER_LOOP_FRAMES 60u
#define PIKACHU_SOURCE_THUNDER_HIT_ACTIVE_FRAMES 10u
#define PIKACHU_SOURCE_THUNDER_HIT_TO_END_FRAMES 30u
#define PIKACHU_SOURCE_THUNDER_END_GROUND_CLIP_FRAMES 38u
#define PIKACHU_SOURCE_THUNDER_END_AIR_CLIP_FRAMES 38u
#define PIKACHU_SOURCE_THUNDER_HIT_GRAVITY 0.5
#define PIKACHU_SOURCE_THUNDER_HIT_VELOCITY_Y 20.0
#define PIKACHU_SOURCE_AIR_ACCEL 0.055
#define PIKACHU_SOURCE_AIR_FRICTION 0.45
#define PIKACHU_SOURCE_AIR_SPEED_MAX 37.5
#define PIKACHU_SOURCE_AIR_STICK_MIN 8
#define PIKACHU_SOURCE_AIR_OVERCAP_DECEL 1.0
#define PIKACHU_SOURCE_FAST_FALL_VELOCITY 83.0
#define PIKACHU_SOURCE_FAST_FALL_TAP_MAX 4u

typedef enum {
    PK_GROUND_WAIT, PK_WALK, PK_DASH, PK_RUN, PK_JUMP_GROUND, PK_JUMP_AERIAL,
    PK_AIR_FALL, PK_JAB, PK_FTILT, PK_NAIR, PK_FAIR, PK_BAIR, PK_DAIR,
    PK_THUNDER_JOLT_GROUND, PK_THUNDER_JOLT_AIR, PK_QUICK_ATTACK_START,
    PK_QUICK_ATTACK_ZIP1, PK_QUICK_ATTACK_WINDOW, PK_QUICK_ATTACK_ZIP2,
    PK_QUICK_ATTACK_RECOVERY, PK_THUNDER_START, PK_THUNDER_LOOP,
    PK_THUNDER_SELF_HIT,
    /* Append only: save-state records serialize these numeric values. */
    PK_RUN_BRAKE, PK_TURN_RUN, PK_CROUCH, PK_CROUCH_WAIT,
    PK_CROUCH_END, PK_LANDING, PK_DASH_ATTACK, PK_UTILT, PK_DTILT,
    PK_UAIR, PK_FALL_SPECIAL_LANDING,
    /* Append only: source Quick Attack's 46f EndProc hands off to this
     * ordinary aerial FallSpecial before any special landing animation. */
    PK_FALL_SPECIAL,
    /* Append only: failed Z-cancel outcomes selected by the aerial scripts'
     * flag1 windows. Pikachu has authored F/D landings; N/B use AirNull. */
    PK_LANDING_AIR_NULL, PK_LANDING_AIR_F, PK_LANDING_AIR_D,
    /* Append only: legacy PK_THUNDER_{START,LOOP,SELF_HIT} are the grounded
     * source statuses. These complete the distinct ground/air status graph
     * without changing any serialized legacy ordinal. */
    PK_THUNDER_END, PK_THUNDER_AIR_START, PK_THUNDER_AIR_LOOP,
    PK_THUNDER_AIR_SELF_HIT, PK_THUNDER_AIR_END,
    /* Append only: source-distinct common locomotion states. */
    PK_KNEEBEND, PK_LANDING_HEAVY, PK_JUMP_GROUND_B,
    PK_JUMP_AERIAL_B, PK_AIR_FALL_AERIAL,
    PK_QUICK_ATTACK_GROUND_START, PK_QUICK_ATTACK_GROUND_ZIP1,
    PK_QUICK_ATTACK_GROUND_WINDOW, PK_QUICK_ATTACK_GROUND_ZIP2,
    PK_QUICK_ATTACK_GROUND_RECOVERY,
    PK_STATE_COUNT
} PikachuState;

typedef enum {
    PIKACHU_EVENT_VOICE_SPECIAL_N = 0, PIKACHU_EVENT_VOICE_SPECIAL_HI,
    PIKACHU_EVENT_VOICE_SPECIAL_LW, PIKACHU_EVENT_FGM_LIGHT_S,
    PIKACHU_EVENT_FGM_LIGHT_M, PIKACHU_EVENT_FGM_LIGHT_L,
    PIKACHU_EVENT_FGM_ELECTRIC_1, PIKACHU_EVENT_FGM_ELECTRIC_2,
    PIKACHU_EVENT_FGM_ELECTRIC_3, PIKACHU_EVENT_FGM_ELECTRIC_5,
    PIKACHU_EVENT_FGM_QUICK_ATTACK_START,
    PIKACHU_EVENT_FGM_SWING_PULSE, PIKACHU_EVENT_EFFECT_SPARKLE,
    PIKACHU_EVENT_EFFECT_RIPPLE, PIKACHU_EVENT_EFFECT_THUNDER_AMP,
    PIKACHU_EVENT_PROJECTILE_JOLT_SPAWN,
    PIKACHU_EVENT_PROJECTILE_THUNDER_SPAWN,
    PIKACHU_EVENT_PROJECTILE_THUNDER_SELF_HIT,
    PIKACHU_EVENT_FGM_LANDING,
    PIKACHU_EVENT_FGM_DEAD_SLAM,
    PIKACHU_EVENT_EFFECT_DUST_HEAVY_DOUBLE,
    PIKACHU_EVENT_EFFECT_IMPACT_WAVE,
    PIKACHU_EVENT_EFFECT_QUAKE_MAG1,
    PIKACHU_EVENT_EFFECT_THUNDER_HIT_COLOR,
    /* Append only: source DownSpecialLoop frame-zero FGM. This is distinct
     * from the frame-24 Start event that creates the Thunder weapon. */
    PIKACHU_EVENT_FGM_THUNDER,
    PIKACHU_EVENT_COUNT
} PikachuEvent;

#define PIKACHU_EVENT_BIT(event) (1u << (unsigned)(event))

typedef enum { PIKACHU_PROJECTILE_NONE, PIKACHU_PROJECTILE_JOLT,
               PIKACHU_PROJECTILE_THUNDER } PikachuProjectileKind;

typedef struct { int stick_x, stick_y, jump_pressed, jump_held, attack_pressed,
                 special_pressed;
                 /* Append-only v5 input edge used by common fast-fall. */
                 int down_pressed; } PikachuInputRaw;
typedef struct { double actual_dx, actual_dy; int grounded, hit_ceiling,
                 hit_floor, hit_wall; } PikachuCollision;
/* Read-only host collision callback. A Quick Attack path is sampled at no
 * more than one SMB pixel (12.5 source units) per candidate. */
typedef int (*PikachuSweepProbe)(double x, double y, void *user);
typedef struct { double offset_x, offset_y, width, height; int damage,
                 break_blocks, active; } PikachuAttack;
typedef struct { PikachuProjectileKind kind; uint32_t persistent_action_id;
                 int can_defeat_enemy_once, can_break_blocks, follows_surfaces;
                 int source_joint; double speed_x, speed_y; int active; } PikachuProjectile;
typedef struct { double requested_dx, requested_dy; PikachuAttack attack;
                 uint32_t events; PikachuProjectile projectile;
                 uint32_t persistent_action_id; unsigned action_frame;
                 int force_airborne; } PikachuMotion;

typedef struct {
    int state, lr, grounded, jumps_used;
    unsigned action_frame;
    uint32_t persistent_action_id, next_action_id;
    double pos_x, pos_y, vel_x, vel_y;
    int quick_first_x, quick_first_y;
    int thunder_contact_pending;
    unsigned thunder_contact_frame;
    PikachuProjectile projectile;
    PikachuMotion last_motion;
    /* Appended: private source End/FallSpecial clock. Versioned serializer
     * accepts pre-clock v1 records with these fields cleared. */
    unsigned quick_end_frame;
    int quick_fall_special;
    /* Append-only v4 field: Attack11's asynchronous frame-10 repeat latch. */
    int jab_repeat_pending;
    /* Append-only v5 field: common fast-fall status flag. */
    int fast_fall;
    unsigned down_tap_age;
    /* Append-only v6 latch: the second zip's End waits the same nine source
     * frames as the first End, but must never accept a third direction. */
    int quick_is_subsequent;
    /* Append-only v7 presentation latch. SpecialHi Start has motion id -1:
     * it freezes the exact pose that was active on entry for all 20 ticks. */
    int quick_entry_state;
    unsigned quick_entry_frame;
} PikachuFighter;

const char *pikachu_state_name(int state);
void pikachu_reset(PikachuFighter *fighter);
void pikachu_tick(PikachuFighter *fighter, const PikachuInputRaw *input,
                  PikachuMotion *out);
void pikachu_resolve(PikachuFighter *fighter, const PikachuCollision *hit);
void pikachu_sweep_zip(const PikachuFighter *fighter, const PikachuMotion *motion,
                       PikachuSweepProbe probe, void *user,
                       PikachuCollision *out);
/* Host projectile ownership reports an intersection with Pikachu here. */
void pikachu_note_thunder_self_contact(PikachuFighter *fighter);
void pikachu_note_projectile_finished(PikachuFighter *fighter,
                                      uint32_t persistent_action_id);
int pikachu_serialize(const PikachuFighter *fighter, uint8_t *buf, int cap);
int pikachu_deserialize(PikachuFighter *fighter, const uint8_t *buf, int len);

#endif
