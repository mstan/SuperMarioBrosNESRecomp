/*
 * Sonic 3 & Knuckles Sonic controller adapted to SMB1.
 *
 * Source anchors from skdisasm/s3.asm:
 *   normal max/accel/decel: $600/$0C/$80
 *   speed shoes max/accel/decel: $A00/$30/$100
 *   underwater max/accel/decel: $300/$06/$40
 *   Sonic_Jump / Sonic_JumpHeight / Sonic_ChgJumpDir
 *
 * The Mega Drive values are 8.8 px/frame. SMB's streamer cannot safely accept
 * S3&K's full top speed, so the ratios are preserved and then capped by the
 * shared SMB fighter profile.
 */
#include "sonic_controller.h"

#include "foreign_controller.h"
#include "mod_savestate.h"

#include <math.h>
#include <string.h>

#define SONIC_MAX_SPEED      4.00
#define SONIC_ACCEL          0.18
#define SONIC_DECEL          1.20
#define SONIC_FRICTION       0.18
#define SONIC_AIR_ACCEL      0.09
#define SONIC_JUMP_SPEED     6.15
#define SONIC_GRAVITY        0.21875
#define SONIC_RELEASE_CUT    4.00
#define SONIC_FALL_MAX       6.50
#define SONIC_ROLL_MIN       1.20
#define SONIC_ROLL_EXIT_MIN  0.30
#define SONIC_ROLL_FRICTION  0.012
#define SONIC_SPINDASH_BASE  5.60
#define SONIC_SPINDASH_STEP  0.75
#define SONIC_SPINDASH_MAX   9.60
#define SONIC_FIRE_DASH_SPEED 9.25
#define SONIC_FIRE_DASH_TICKS 8

static int s_jump_held_last;
static int s_spindash_charge;
static int s_fire_shield;
static int s_air_dash_used;
static int s_fire_dash_timer;
static int s_destructive_roll;
static unsigned s_anim_clock;

static double clampd(double v, double lo, double hi)
{
    return v < lo ? lo : (v > hi ? hi : v);
}

static double approach(double value, double target, double amount)
{
    if (value < target) {
        value += amount;
        return value > target ? target : value;
    }
    if (value > target) {
        value -= amount;
        return value < target ? target : value;
    }
    return value;
}

static int ball_state(int state)
{
    return state == S3K_SONIC_ROLL ||
           state == S3K_SONIC_SPINDASH ||
           state == S3K_SONIC_JUMP ||
           state == S3K_SONIC_FALL ||
           state == S3K_SONIC_FIRE_DASH;
}

static int spin_attack_state(int state)
{
    return state == S3K_SONIC_ROLL ||
           state == S3K_SONIC_JUMP ||
           state == S3K_SONIC_FALL ||
           state == S3K_SONIC_FIRE_DASH;
}

static int side_block_break_state(int state)
{
    return (state == S3K_SONIC_ROLL && s_destructive_roll) ||
           state == S3K_SONIC_FIRE_DASH;
}

static void emit_audio(ForeignMoveResult *out, uint32_t cue, int gain_percent)
{
    if (out->audio.count >= FOREIGN_AUDIO_EVENT_CAPACITY) return;
    out->audio.events[out->audio.count].cue = cue;
    out->audio.events[out->audio.count].gain_percent = gain_percent;
    out->audio.count++;
}

static void publish_spin_hitbox(const ForeignState *state,
                                ForeignMoveResult *out)
{
    if (!spin_attack_state(state->state)) return;
    out->attack.active = 1;
    out->attack.damage = 1;
    if (state->state == S3K_SONIC_JUMP ||
        state->state == S3K_SONIC_FALL ||
        (state->state == S3K_SONIC_ROLL && s_destructive_roll) ||
        state->state == S3K_SONIC_FIRE_DASH)
        out->attack.flags = FOREIGN_ATTACK_BREAK_BLOCKS;
    out->attack.offset_x = 0.0;
    out->attack.offset_y = 10.0;
    out->attack.width = 20.0;
    out->attack.height = 20.0;
    out->attack.knockback_x = fabs(state->vx) + 1.0;
    out->attack.knockback_y = 2.0;
}

static void sonic_reset(ForeignState *state)
{
    memset(state, 0, sizeof(*state));
    state->state = S3K_SONIC_STAND;
    state->facing = 1.0f;
    state->grounded = 1;
    s_jump_held_last = 0;
    s_spindash_charge = 0;
    s_fire_shield = 0;
    s_air_dash_used = 0;
    s_fire_dash_timer = 0;
    s_destructive_roll = 0;
    s_anim_clock = 0;
}

static void start_jump(ForeignState *state, ForeignMoveResult *out)
{
    state->vy = SONIC_JUMP_SPEED;
    state->grounded = 0;
    state->state = S3K_SONIC_JUMP;
    state->jump_phase = FOREIGN_JUMP_LAUNCH;
    out->force_airborne = 1;
    emit_audio(out, S3K_SONIC_AUDIO_JUMP, 100);
}

static void sonic_tick(ForeignState *state, const ForeignInput *input,
                       ForeignMoveResult *out)
{
    const int old_state = state->state;
    const int down_held = input->stick_y < -0.5f;
    const int charge_pressed =
        (input->special_pressed || input->attack_pressed) && down_held;
    double abs_vx;

    memset(out, 0, sizeof(*out));
    state->jump_phase = FOREIGN_JUMP_NONE;

    if (input->stick_x != 0.0f)
        state->facing = input->stick_x < 0.0f ? -1.0f : 1.0f;

    if (state->grounded) {
        state->vy = 0.0;
        s_air_dash_used = 0;
        s_fire_dash_timer = 0;
        if (state->state == S3K_SONIC_SPINDASH) {
            state->vx = approach(state->vx, 0.0, SONIC_FRICTION);
            if (charge_pressed && s_spindash_charge < 6)
                s_spindash_charge++;
            if (charge_pressed)
                emit_audio(out, S3K_SONIC_AUDIO_SPINDASH, 88);
            if (!down_held) {
                const double burst = clampd(SONIC_SPINDASH_BASE +
                                            s_spindash_charge *
                                                SONIC_SPINDASH_STEP,
                                            SONIC_SPINDASH_BASE,
                                            SONIC_SPINDASH_MAX);
                state->vx = (state->facing < 0.0f ? -burst : burst);
                state->state = S3K_SONIC_ROLL;
                s_destructive_roll = 1;
                s_spindash_charge = 0;
                emit_audio(out, S3K_SONIC_AUDIO_DASH, 100);
                emit_audio(out, S3K_SONIC_AUDIO_ROLL, 80);
            }
        } else if (charge_pressed) {
            state->state = S3K_SONIC_SPINDASH;
            s_spindash_charge = 1;
            state->vx = approach(state->vx, 0.0, SONIC_DECEL);
            emit_audio(out, S3K_SONIC_AUDIO_SPINDASH, 100);
        } else if (input->jump_pressed) {
            start_jump(state, out);
        } else if (state->state == S3K_SONIC_ROLL) {
            state->vx = approach(state->vx, 0.0, SONIC_ROLL_FRICTION);
            if (fabs(state->vx) < SONIC_ROLL_EXIT_MIN && !down_held) {
                state->state = S3K_SONIC_STAND;
                s_destructive_roll = 0;
            }
        } else if (down_held && fabs(state->vx) < 0.5) {
            state->state = S3K_SONIC_CROUCH;
            s_destructive_roll = 0;
            state->vx = approach(state->vx, 0.0, SONIC_FRICTION);
        } else {
            const double target = input->stick_x * SONIC_MAX_SPEED;
            const int braking = input->stick_x != 0.0f &&
                                state->vx * target < 0.0;
            state->vx = approach(state->vx, target,
                                 braking ? SONIC_DECEL :
                                 input->stick_x == 0.0f ? SONIC_FRICTION :
                                                          SONIC_ACCEL);
            abs_vx = fabs(state->vx);
            if (braking && abs_vx > 1.0)
                state->state = S3K_SONIC_SKID;
            else if (down_held && abs_vx >= SONIC_ROLL_MIN)
                state->state = S3K_SONIC_ROLL;
            else if (abs_vx > 2.25)
                state->state = S3K_SONIC_RUN;
            else if (abs_vx > 0.15)
                state->state = S3K_SONIC_WALK;
            else
                state->state = S3K_SONIC_STAND;
            if (state->state == S3K_SONIC_ROLL && old_state != S3K_SONIC_ROLL) {
                s_destructive_roll = 0;
                emit_audio(out, S3K_SONIC_AUDIO_ROLL, 100);
            }
        }
    } else {
        const double target = input->stick_x * SONIC_MAX_SPEED;
        if (s_fire_shield && input->jump_pressed && !s_air_dash_used) {
            state->vx = state->facing < 0.0f
                            ? -SONIC_FIRE_DASH_SPEED
                            : SONIC_FIRE_DASH_SPEED;
            state->vy = 0.0;
            state->state = S3K_SONIC_FIRE_DASH;
            s_destructive_roll = 0;
            s_fire_dash_timer = SONIC_FIRE_DASH_TICKS;
            s_air_dash_used = 1;
            emit_audio(out, S3K_SONIC_AUDIO_FIRE_DASH, 100);
        } else if (state->state == S3K_SONIC_FIRE_DASH &&
                   s_fire_dash_timer > 0) {
            s_fire_dash_timer--;
            state->vx = state->facing < 0.0f
                            ? -SONIC_FIRE_DASH_SPEED
                            : SONIC_FIRE_DASH_SPEED;
            state->vy = 0.0;
        } else {
            state->vx = approach(state->vx, target, SONIC_AIR_ACCEL);
            state->vy -= SONIC_GRAVITY;
            if (!input->jump_held && s_jump_held_last &&
                state->vy > SONIC_RELEASE_CUT)
                state->vy = SONIC_RELEASE_CUT;
            if (state->vy < -SONIC_FALL_MAX) state->vy = -SONIC_FALL_MAX;
            state->state = state->vy >= 0.0 ? S3K_SONIC_JUMP : S3K_SONIC_FALL;
            s_destructive_roll = 0;
        }
    }

    out->requested_dx = state->vx;
    out->requested_dy = state->vy;
    out->vx = state->vx;
    out->vy = state->vy;
    out->state = state->state;
    publish_spin_hitbox(state, out);

    if (state->state == old_state) state->state_frame++;
    else state->state_frame = 0;
    s_jump_held_last = input->jump_held;
    s_anim_clock++;
}

static void sonic_resolve(ForeignState *state,
                          const ForeignCollisionResult *hit)
{
    state->x += hit->actual_dx;
    state->y += hit->actual_dy;
    if (hit->hit_wall) {
        state->vx = 0.0;
        if (state->state == S3K_SONIC_ROLL) {
            state->state = S3K_SONIC_STAND;
            s_destructive_roll = 0;
        }
        if (state->state == S3K_SONIC_FIRE_DASH) {
            state->state = S3K_SONIC_FALL;
            s_fire_dash_timer = 0;
        }
    }
    if (hit->hit_ceiling && state->vy > 0.0) state->vy = 0.0;
    if (hit->has_imposed_vy) {
        state->vy = hit->imposed_vy;
        if (state->vy > 0.0) {
            state->grounded = 0;
            state->state = S3K_SONIC_JUMP;
            s_destructive_roll = 0;
            if (state->vy < 5.20) state->vy = 5.20;
        }
    }
    if ((hit->grounded || hit->hit_floor) &&
        !(hit->has_imposed_vy && hit->imposed_vy > 0.0)) {
        const int was_airborne = !state->grounded;
        state->grounded = 1;
        state->vy = 0.0;
        s_air_dash_used = 0;
        s_fire_dash_timer = 0;
        if (was_airborne) {
            state->state = fabs(state->vx) >= SONIC_ROLL_MIN
                               ? S3K_SONIC_ROLL : S3K_SONIC_STAND;
            s_destructive_roll = 0;
        }
    } else {
        state->grounded = 0;
    }
}

static const char *sonic_state_name(ForeignMoveState state)
{
    switch (state) {
    case S3K_SONIC_STAND: return "Stand";
    case S3K_SONIC_WALK: return "Walk";
    case S3K_SONIC_RUN: return "Run";
    case S3K_SONIC_SKID: return "Skid";
    case S3K_SONIC_CROUCH: return "Crouch";
    case S3K_SONIC_SPINDASH: return "Spindash";
    case S3K_SONIC_ROLL: return "Roll";
    case S3K_SONIC_JUMP: return "Jump";
    case S3K_SONIC_FALL: return "Fall";
    case S3K_SONIC_FIRE_DASH: return "FireDash";
    default: return "Unknown";
    }
}

typedef struct SonicSave {
    unsigned char version;
    unsigned char jump_held_last;
    unsigned char spindash_charge;
    unsigned char fire_shield;
    unsigned char air_dash_used;
    unsigned char fire_dash_timer;
    unsigned char destructive_roll;
    unsigned char pad[2];
    unsigned anim_clock;
} SonicSave;

static int sonic_save_get(unsigned char *buf, int cap)
{
    SonicSave save;
    if (!buf || cap < (int)sizeof(save)) return 0;
    memset(&save, 0, sizeof(save));
    save.version = 2;
    save.jump_held_last = (unsigned char)(s_jump_held_last ? 1 : 0);
    save.spindash_charge = (unsigned char)s_spindash_charge;
    save.fire_shield = (unsigned char)(s_fire_shield ? 1 : 0);
    save.air_dash_used = (unsigned char)(s_air_dash_used ? 1 : 0);
    save.fire_dash_timer = (unsigned char)s_fire_dash_timer;
    save.destructive_roll = (unsigned char)(s_destructive_roll ? 1 : 0);
    save.anim_clock = s_anim_clock;
    memcpy(buf, &save, sizeof(save));
    return (int)sizeof(save);
}

static int sonic_save_set(const unsigned char *buf, int len)
{
    SonicSave save;
    if (!buf || len != (int)sizeof(save)) return 0;
    memcpy(&save, buf, sizeof(save));
    if (save.version != 2 || save.spindash_charge > 6 ||
        save.fire_dash_timer > SONIC_FIRE_DASH_TICKS)
        return 0;
    s_jump_held_last = save.jump_held_last != 0;
    s_spindash_charge = save.spindash_charge;
    s_fire_shield = save.fire_shield != 0;
    s_air_dash_used = save.air_dash_used != 0;
    s_fire_dash_timer = save.fire_dash_timer;
    s_destructive_roll = save.destructive_roll != 0;
    s_anim_clock = save.anim_clock;
    return 1;
}

static const ForeignController kSonicController = {
    S3K_SONIC_CONTROLLER_ID,
    "Sonic (Sonic 3 & Knuckles)",
    sonic_reset,
    sonic_tick,
    sonic_resolve,
    sonic_state_name
};

int s3k_sonic_controller_register(void)
{
    int ok = nes_foreign_register(&kSonicController);
    ok &= nes_mod_register_savestate_hook(S3K_SONIC_CONTROLLER_ID,
                                          sonic_save_get, sonic_save_set);
    return ok;
}

int s3k_sonic_is_ball(void)
{
    const ForeignState *state = nes_foreign_state();
    return state && ball_state(state->state);
}

int s3k_sonic_breaks_side_blocks(void)
{
    const ForeignState *state = nes_foreign_state();
    return state && side_block_break_state(state->state);
}

int s3k_sonic_is_crouching(void)
{
    const ForeignState *state = nes_foreign_state();
    return state && (state->state == S3K_SONIC_CROUCH ||
                     state->state == S3K_SONIC_SPINDASH);
}

int s3k_sonic_has_fire_shield(void)
{
    return s_fire_shield;
}

void s3k_sonic_set_fire_shield(int enabled)
{
    s_fire_shield = enabled != 0;
    if (!s_fire_shield) {
        s_air_dash_used = 0;
        s_fire_dash_timer = 0;
    }
}

unsigned s3k_sonic_anim_frame(void)
{
    return s_anim_clock;
}
