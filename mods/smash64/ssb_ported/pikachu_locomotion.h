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
#define PIKACHU_SOURCE_GRAVITY 3.0
#define PIKACHU_SOURCE_TERMINAL_VELOCITY 52.0
#define PIKACHU_SOURCE_JUMP_COUNT 2
#define PIKACHU_SOURCE_JUMP_GROUND_FRAMES 45u
#define PIKACHU_SOURCE_JUMP_AERIAL_FRAMES 60u

typedef enum {
    PK_GROUND_WAIT, PK_WALK, PK_DASH, PK_RUN, PK_JUMP_GROUND, PK_JUMP_AERIAL,
    PK_AIR_FALL, PK_JAB, PK_FTILT, PK_NAIR, PK_FAIR, PK_BAIR, PK_DAIR,
    PK_THUNDER_JOLT_GROUND, PK_THUNDER_JOLT_AIR, PK_QUICK_ATTACK_START,
    PK_QUICK_ATTACK_ZIP1, PK_QUICK_ATTACK_WINDOW, PK_QUICK_ATTACK_ZIP2,
    PK_QUICK_ATTACK_RECOVERY, PK_THUNDER_START, PK_THUNDER_LOOP,
    PK_THUNDER_SELF_HIT, PK_STATE_COUNT
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
    PIKACHU_EVENT_COUNT
} PikachuEvent;

#define PIKACHU_EVENT_BIT(event) (1u << (unsigned)(event))

typedef enum { PIKACHU_PROJECTILE_NONE, PIKACHU_PROJECTILE_JOLT,
               PIKACHU_PROJECTILE_THUNDER } PikachuProjectileKind;

typedef struct { int stick_x, stick_y, jump_pressed, jump_held, attack_pressed,
                 special_pressed; } PikachuInputRaw;
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
