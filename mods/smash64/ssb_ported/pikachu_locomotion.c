#include "pikachu_locomotion.h"

#include <math.h>
#include <stddef.h>
#include <string.h>

#define PIKACHU_SAVE_VERSION 2u

static void enter(PikachuFighter *f, int state)
{
    f->state = state;
    f->action_frame = 0;
    f->persistent_action_id = ++f->next_action_id;
}

/* A source action can change its presentation phase without becoming a new
 * action: Quick Attack's two zips are frame 20 and frame 34 of ONE action. */
static void phase(PikachuFighter *f, int state) { f->state = state; }

const char *pikachu_state_name(int state)
{
    switch (state) {
    case PK_GROUND_WAIT: return "GROUND_WAIT"; case PK_WALK: return "WALK";
    case PK_DASH: return "DASH"; case PK_RUN: return "RUN";
    case PK_JUMP_GROUND: return "JUMP_GROUND"; case PK_JUMP_AERIAL: return "JUMP_AERIAL";
    case PK_AIR_FALL: return "AIR_FALL"; case PK_JAB: return "JAB";
    case PK_FTILT: return "FTILT"; case PK_NAIR: return "NAIR";
    case PK_FAIR: return "FAIR"; case PK_BAIR: return "BAIR";
    case PK_DAIR: return "DAIR"; case PK_THUNDER_JOLT_GROUND: return "THUNDER_JOLT_GROUND";
    case PK_THUNDER_JOLT_AIR: return "THUNDER_JOLT_AIR";
    case PK_QUICK_ATTACK_START: return "QUICK_ATTACK_START";
    case PK_QUICK_ATTACK_ZIP1: return "QUICK_ATTACK_ZIP1";
    case PK_QUICK_ATTACK_WINDOW: return "QUICK_ATTACK_WINDOW";
    case PK_QUICK_ATTACK_ZIP2: return "QUICK_ATTACK_ZIP2";
    case PK_QUICK_ATTACK_RECOVERY: return "QUICK_ATTACK_RECOVERY";
    case PK_THUNDER_START: return "THUNDER_START"; case PK_THUNDER_LOOP: return "THUNDER_LOOP";
    case PK_THUNDER_SELF_HIT: return "THUNDER_SELF_HIT";
    case PK_RUN_BRAKE: return "RUN_BRAKE"; case PK_TURN_RUN: return "TURN_RUN";
    case PK_CROUCH: return "CROUCH"; case PK_CROUCH_WAIT: return "CROUCH_WAIT";
    case PK_CROUCH_END: return "CROUCH_END"; case PK_LANDING: return "LANDING";
    case PK_DASH_ATTACK: return "DASH_ATTACK"; case PK_UTILT: return "UTILT";
    case PK_DTILT: return "DTILT"; case PK_UAIR: return "UAIR";
    default: return "INVALID";
    }
}

void pikachu_reset(PikachuFighter *f)
{
    memset(f, 0, sizeof(*f));
    f->state = PK_GROUND_WAIT;
    f->lr = 1;
    f->grounded = 1;
}

static int is_action(int state)
{
    switch (state) {
    case PK_JAB: case PK_FTILT: case PK_NAIR: case PK_FAIR: case PK_BAIR:
    case PK_DAIR: case PK_DASH_ATTACK: case PK_UTILT: case PK_DTILT: case PK_UAIR:
    case PK_THUNDER_JOLT_GROUND: case PK_THUNDER_JOLT_AIR:
    case PK_QUICK_ATTACK_START: case PK_QUICK_ATTACK_ZIP1:
    case PK_QUICK_ATTACK_WINDOW: case PK_QUICK_ATTACK_ZIP2:
    case PK_QUICK_ATTACK_RECOVERY: case PK_THUNDER_START: case PK_THUNDER_LOOP:
    case PK_THUNDER_SELF_HIT:
        return 1;
    default:
        return 0;
    }
}

static int is_timed_ground_state(int state)
{
    return state == PK_DASH || state == PK_RUN_BRAKE || state == PK_TURN_RUN ||
           state == PK_CROUCH || state == PK_CROUCH_END || state == PK_LANDING;
}

static int is_standard_air_state(int state)
{
    switch (state) {
    case PK_JUMP_GROUND: case PK_JUMP_AERIAL: case PK_AIR_FALL:
    case PK_NAIR: case PK_FAIR: case PK_BAIR: case PK_DAIR: case PK_UAIR:
        return 1;
    default:
        return 0;
    }
}

static void set_attack(PikachuMotion *out, double x, double y, double w,
                       double h, int damage, int break_blocks)
{
    out->attack.offset_x = x; out->attack.offset_y = y;
    out->attack.width = w; out->attack.height = h;
    out->attack.damage = damage; out->attack.break_blocks = break_blocks;
    out->attack.active = 1;
}

static void spawn_jolt(PikachuFighter *f, PikachuMotion *out)
{
    f->projectile.kind = PIKACHU_PROJECTILE_JOLT;
    f->projectile.persistent_action_id = f->persistent_action_id;
    f->projectile.can_defeat_enemy_once = 1;
    f->projectile.can_break_blocks = 0;
    f->projectile.follows_surfaces = 1;
    f->projectile.source_joint = 11;
    f->projectile.speed_x = 28.284271 * f->lr;
    f->projectile.speed_y = -28.284271;
    f->projectile.active = 1;
    out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_PROJECTILE_JOLT_SPAWN);
}

static void spawn_thunder(PikachuFighter *f, PikachuMotion *out)
{
    f->projectile.kind = PIKACHU_PROJECTILE_THUNDER;
    f->projectile.persistent_action_id = f->persistent_action_id;
    f->projectile.can_defeat_enemy_once = 1;
    f->projectile.can_break_blocks = 0;
    f->projectile.follows_surfaces = 0;
    f->projectile.source_joint = -1;
    f->projectile.speed_x = 0.0;
    f->projectile.speed_y = -450.0;
    f->projectile.active = 1;
    out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_PROJECTILE_THUNDER_SPAWN);
}

/* Aerial attacks keep the fighter's air kinetic state authoritative. They
 * deliberately do not derive travel from animation/root motion. */
static void air_motion(PikachuFighter *f, PikachuMotion *out)
{
    f->vel_y -= PIKACHU_SOURCE_GRAVITY;
    if (f->vel_y < -PIKACHU_SOURCE_TERMINAL_VELOCITY)
        f->vel_y = -PIKACHU_SOURCE_TERMINAL_VELOCITY;
    out->requested_dx = f->vel_x;
    out->requested_dy = f->vel_y;
}

static void normal_schedule(PikachuFighter *f, PikachuMotion *out)
{
    unsigned n = f->action_frame;
    switch (f->state) {
    case PK_JAB:
        if (n == 2) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LIGHT_S);
        if (n >= 2 && n < 6) set_attack(out, 45, 40, 65, 55, 4, 1);
        if (n >= 20) enter(f, f->grounded ? PK_GROUND_WAIT : PK_AIR_FALL);
        break;
    case PK_FTILT:
        if (n == 5) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LIGHT_M);
        if (n >= 5 && n < 15) set_attack(out, 55, 42, 75, 55, 10, 1);
        if (n >= 24) enter(f, f->grounded ? PK_GROUND_WAIT : PK_AIR_FALL);
        break;
    case PK_NAIR:
        air_motion(f, out);
        if (n == 3) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LIGHT_M);
        if (n >= 3 && n < 11) set_attack(out, 0, 48, 100, 100, 14, 1);
        if (n >= 11 && n < 29) set_attack(out, 0, 48, 100, 100, 11, 1);
        if (n >= 35) enter(f, PK_AIR_FALL);
        break;
    case PK_FAIR:
        air_motion(f, out);
        if (n == 7) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_2);
        if (n >= 7 && n < 27 && ((n - 7) % 3) < 2) {
            if ((n - 7) % 3 == 0) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_SWING_PULSE);
            set_attack(out, 58, 48, 70, 60, 3, 1);
        }
        if (n >= 34) enter(f, PK_AIR_FALL);
        break;
    case PK_BAIR:
        air_motion(f, out);
        if (n == 10) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LIGHT_L);
        if (n >= 10 && n < 14) set_attack(out, -50, 50, 70, 60, 16, 1);
        if (n >= 14 && n < 22) set_attack(out, -50, 50, 70, 60, 14, 1);
        if (n >= 30) enter(f, PK_AIR_FALL);
        break;
    case PK_DAIR:
        air_motion(f, out);
        if (n == 8) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_3);
        if (n >= 8 && n < 26) set_attack(out, 0, -15, 72, 78, 13, 1);
        if (n >= 34) enter(f, PK_AIR_FALL);
        break;
    case PK_DASH_ATTACK:
        if (n == 4) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LIGHT_L);
        /* MOTION_ATTACK is (aid, gid, jid, damage, ..., kbb). The US 0x0E80
         * record's damage is 12; 40 is knockback base, not damage. */
        if (n >= 4 && n < 23) set_attack(out, 85, 45, 160, 90, 12, 1);
        if (n >= PIKACHU_SOURCE_DASH_ATTACK_FRAMES)
            enter(f, f->grounded ? PK_GROUND_WAIT : PK_AIR_FALL);
        break;
    case PK_UTILT:
        if (n == 5) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LIGHT_M);
        /* The US 0x0FF0 macro likewise spells source damage 11. */
        if (n >= 5 && n < 15) set_attack(out, 0, 135, 150, 120, 11, 1);
        if (n >= PIKACHU_SOURCE_UTILT_FRAMES)
            enter(f, f->grounded ? PK_GROUND_WAIT : PK_AIR_FALL);
        break;
    case PK_DTILT:
        if (n == 6) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LIGHT_M);
        if (n >= 6 && n < 14) set_attack(out, 85, 18, 145, 58, 12, 1);
        if (n >= PIKACHU_SOURCE_DTILT_FRAMES)
            enter(f, f->grounded ? PK_GROUND_WAIT : PK_AIR_FALL);
        break;
    case PK_UAIR:
        air_motion(f, out);
        if (n == 3) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LIGHT_M);
        if (n >= 3 && n < 11) set_attack(out, 0, 145, 150, 120, 10, 1);
        if (n >= PIKACHU_SOURCE_UAIR_FRAMES) enter(f, PK_AIR_FALL);
        break;
    default: break;
    }
}

static void choose_action(PikachuFighter *f, const PikachuInputRaw *in)
{
    int air = !f->grounded;
    if (in->special_pressed) {
        if (in->stick_y >= 20) { enter(f, PK_QUICK_ATTACK_START); return; }
        if (in->stick_y <= -20) { enter(f, PK_THUNDER_START); return; }
        enter(f, air ? PK_THUNDER_JOLT_AIR : PK_THUNDER_JOLT_GROUND); return;
    }
    if (in->attack_pressed) {
        if (!air && in->stick_y >= 20) enter(f, PK_UTILT);
        else if (!air && in->stick_y <= -20) enter(f, PK_DTILT);
        else if (air && in->stick_y <= -20) enter(f, PK_DAIR);
        else if (air && in->stick_y >= 20) enter(f, PK_UAIR);
        else if (air && in->stick_x * f->lr < -20) enter(f, PK_BAIR);
        else if (air && in->stick_x * f->lr >= 20) enter(f, PK_FAIR);
        else if (air) enter(f, PK_NAIR);
        else if ((f->state == PK_DASH || f->state == PK_RUN) &&
                 in->stick_x * f->lr >= 20) enter(f, PK_DASH_ATTACK);
        else if (in->stick_x * f->lr >= 20) enter(f, PK_FTILT);
        else enter(f, PK_JAB);
        return;
    }
    if (in->jump_pressed && (f->grounded || f->jumps_used < PIKACHU_SOURCE_JUMP_COUNT)) {
        int aerial = !f->grounded;
        f->grounded = 0;
        f->vel_y = PIKACHU_SOURCE_JUMP_LAUNCH_VELOCITY;
        f->vel_x = in->stick_x * PIKACHU_SOURCE_JUMP_HORIZONTAL_MULTIPLIER;
        f->jumps_used++;
        enter(f, aerial ? PK_JUMP_AERIAL : PK_JUMP_GROUND);
    }
}

static int vector_changed_enough(const PikachuFighter *f, const PikachuInputRaw *in)
{
    long dot, old_sq, new_sq;
    if (in->stick_x * in->stick_x + in->stick_y * in->stick_y <
        (int)(PIKACHU_SOURCE_QUICK_ATTACK_STICK_MIN *
              PIKACHU_SOURCE_QUICK_ATTACK_STICK_MIN)) return 0;
    dot = (long)f->quick_first_x * in->stick_x + (long)f->quick_first_y * in->stick_y;
    old_sq = (long)f->quick_first_x * f->quick_first_x + (long)f->quick_first_y * f->quick_first_y;
    new_sq = (long)in->stick_x * in->stick_x + (long)in->stick_y * in->stick_y;
    /* cos(42 degrees)^2 ~= .552. Negative dot is necessarily a changed aim. */
    return dot < 0 || dot * dot * 1000L < old_sq * new_sq * 552L;
}

/* SpecialHi does not use raw stick components as its velocity.  The source
 * clamps the vector length, normalizes it, then uses
 * speed = 3 * min(|stick|, 80) + 90.  The second zip applies 0.9x.
 * Keep it source-correct here; the SMB adapter makes one direction-preserving
 * safety projection rather than independently clipping X and Y. */
static void quick_zip_velocity(const PikachuFighter *f, int stick_x, int stick_y,
                               double multiplier, double *out_x, double *out_y)
{
    double length = sqrt((double)stick_x * stick_x +
                         (double)stick_y * stick_y);
    double capped, speed;

    if (length == 0.0) {
        stick_x = f->lr * (int)PIKACHU_SOURCE_QUICK_ATTACK_STICK_CAP;
        stick_y = 0;
        length = PIKACHU_SOURCE_QUICK_ATTACK_STICK_CAP;
    }
    capped = length > PIKACHU_SOURCE_QUICK_ATTACK_STICK_CAP
                 ? PIKACHU_SOURCE_QUICK_ATTACK_STICK_CAP : length;
    speed = (PIKACHU_SOURCE_QUICK_ATTACK_STICK_SPEED * capped +
             PIKACHU_SOURCE_QUICK_ATTACK_BASE_SPEED) * multiplier;
    *out_x = speed * (double)stick_x / length;
    *out_y = speed * (double)stick_y / length;
}

/* ftpikachuspecialhi.c:326-351 defaults the *first* low-magnitude aim upward,
 * not toward facing. This is why neutral Up+B then Right is a valid 90-degree
 * two-point route. Store the substituted direction before angle comparison so
 * the source's second-point test compares against the same vector it used. */
static void quick_first_direction(PikachuFighter *f, const PikachuInputRaw *in)
{
    const double length = sqrt((double)in->stick_x * in->stick_x +
                               (double)in->stick_y * in->stick_y);
    if (length > PIKACHU_SOURCE_QUICK_ATTACK_STICK_MIN) {
        f->quick_first_x = in->stick_x;
        f->quick_first_y = in->stick_y;
    } else {
        f->quick_first_x = 0;
        f->quick_first_y = (int)PIKACHU_SOURCE_QUICK_ATTACK_STICK_CAP;
    }
}

static void quick_attack_begin_end(PikachuFighter *f)
{
    /* ftPikachuSpecialAirHiEndSetStatus backs the completed zip up by 0.2
     * and restarts the 46-frame UpSpecialAirEnd motion. */
    f->vel_x *= PIKACHU_SOURCE_QUICK_ATTACK_VELOCITY_BACKUP_MULTIPLIER;
    f->vel_y *= PIKACHU_SOURCE_QUICK_ATTACK_VELOCITY_BACKUP_MULTIPLIER;
    f->quick_end_frame = 0;
    f->quick_fall_special = 0;
}

static void quick_air_control(PikachuFighter *f, const PikachuInputRaw *in,
                              double accel, double speed_cap)
{
    const double target = (double)in->stick_x / 80.0 * speed_cap;
    if (in->stick_x > 10 || in->stick_x < -10) {
        if (f->vel_x < target) f->vel_x += accel;
        else if (f->vel_x > target) f->vel_x -= accel;
    }
    if ((f->vel_x > 0.0 && (in->stick_x <= 10 || f->vel_x > target)) ||
        (f->vel_x < 0.0 && (in->stick_x >= -10 || f->vel_x < target))) {
        if (f->vel_x > 0.0) f->vel_x -= PIKACHU_SOURCE_AIR_FRICTION;
        else f->vel_x += PIKACHU_SOURCE_AIR_FRICTION;
        if ((f->vel_x > 0.0 && f->vel_x < PIKACHU_SOURCE_AIR_FRICTION) ||
            (f->vel_x < 0.0 && f->vel_x > -PIKACHU_SOURCE_AIR_FRICTION))
            f->vel_x = 0.0;
    }
    if (f->vel_x > speed_cap) f->vel_x = speed_cap;
    if (f->vel_x < -speed_cap) f->vel_x = -speed_cap;
}

static int stick_abs(int value) { return value < 0 ? -value : value; }

static void ground_locomotion(PikachuFighter *f, const PikachuInputRaw *in)
{
    const int magnitude = stick_abs(in->stick_x);
    const int input_lr = in->stick_x < 0 ? -1 : 1;

    if (f->state == PK_CROUCH || f->state == PK_CROUCH_WAIT) {
        f->vel_x = 0.0;
        if (in->stick_y >= -18) {
            f->state = PK_CROUCH_END;
            f->action_frame = 0;
        } else if (f->state == PK_CROUCH &&
                   f->action_frame >= PIKACHU_SOURCE_CROUCH_FRAMES) {
            f->state = PK_CROUCH_WAIT;
            f->action_frame = 0;
        }
        return;
    }

    if (f->state == PK_CROUCH_END) {
        f->vel_x = 0.0;
        if (in->stick_y <= -20) {
            f->state = PK_CROUCH;
            f->action_frame = 0;
        } else if (f->action_frame >= PIKACHU_SOURCE_CROUCH_END_FRAMES) {
            f->state = PK_GROUND_WAIT;
            f->action_frame = 0;
        }
        return;
    }

    if (f->state == PK_LANDING) {
        f->vel_x = 0.0;
        if (f->action_frame >= PIKACHU_SOURCE_LANDING_FRAMES) {
            f->state = PK_GROUND_WAIT;
            f->action_frame = 0;
        }
        return;
    }

    if (in->stick_y <= -20) {
        f->vel_x = 0.0;
        f->state = PK_CROUCH;
        f->action_frame = 0;
        return;
    }

    if (f->state == PK_TURN_RUN) {
        if (magnitude < PIKACHU_SOURCE_RUN_STICK_MIN) {
            f->state = PK_RUN_BRAKE;
            f->action_frame = 0;
            return;
        }
        if (f->action_frame >= PIKACHU_SOURCE_TURN_RUN_FLIP_FRAME) {
            f->lr = input_lr;
            f->vel_x = PIKACHU_SOURCE_RUN_SPEED * f->lr;
        }
        if (f->action_frame >= PIKACHU_SOURCE_TURN_RUN_FRAMES) {
            f->state = PK_RUN;
            f->action_frame = 0;
        }
        return;
    }

    if (f->state == PK_RUN_BRAKE) {
        if (magnitude >= PIKACHU_SOURCE_RUN_STICK_MIN && input_lr != f->lr) {
            f->state = PK_TURN_RUN;
            f->action_frame = 0;
            return;
        }
        if (f->vel_x > 0.0) {
            f->vel_x -= PIKACHU_SOURCE_RUN_BRAKE_FRICTION;
            if (f->vel_x < 0.0) f->vel_x = 0.0;
        } else if (f->vel_x < 0.0) {
            f->vel_x += PIKACHU_SOURCE_RUN_BRAKE_FRICTION;
            if (f->vel_x > 0.0) f->vel_x = 0.0;
        }
        if (f->vel_x == 0.0 ||
            f->action_frame >= PIKACHU_SOURCE_RUN_BRAKE_FRAMES) {
            f->vel_x = 0.0;
            f->state = PK_GROUND_WAIT;
            f->action_frame = 0;
        }
        return;
    }

    if (magnitude <= 10) {
        if (f->state == PK_RUN) {
            f->state = PK_RUN_BRAKE;
            f->action_frame = 0;
        } else {
            f->vel_x = 0.0;
            f->state = PK_GROUND_WAIT;
        }
        f->action_frame = 0;
        return;
    }

    if (f->state == PK_DASH) {
        if (input_lr != f->lr) {
            /* Source Dash reversals use the separate common Turn motion.
             * TurnRun itself is reserved for a reversal after Run. */
            f->lr = input_lr;
            f->vel_x = PIKACHU_SOURCE_DASH_SPEED * f->lr;
            f->action_frame = 0;
            return;
        }
        if (f->action_frame >= PIKACHU_SOURCE_DASH_TO_RUN_FRAMES) {
            f->state = PK_RUN;
            f->vel_x = PIKACHU_SOURCE_RUN_SPEED * f->lr;
            f->action_frame = 0;
            return;
        }
        {
            double speed = PIKACHU_SOURCE_DASH_SPEED;
            if (f->action_frame >= 7u) {
                speed -= PIKACHU_SOURCE_DASH_DECEL *
                         (double)(f->action_frame - 6u);
            }
            f->vel_x = speed * f->lr;
        }
        return;
    }

    if (f->state == PK_RUN) {
        if (input_lr != f->lr) {
            f->state = PK_TURN_RUN;
            f->action_frame = 0;
            return;
        }
        if (magnitude >= PIKACHU_SOURCE_RUN_STICK_MIN) {
            f->vel_x = PIKACHU_SOURCE_RUN_SPEED * f->lr;
            return;
        }
        f->state = PK_RUN_BRAKE;
        f->action_frame = 0;
        return;
    }

    if ((f->state == PK_GROUND_WAIT || f->state == PK_RUN ||
         f->state == PK_WALK) &&
        magnitude >= PIKACHU_SOURCE_RUN_STICK_MIN) {
        f->state = PK_DASH;
        f->lr = input_lr;
        f->vel_x = PIKACHU_SOURCE_DASH_SPEED * f->lr;
        f->action_frame = 0;
        return;
    }

    f->state = PK_WALK;
    f->lr = input_lr;
    f->vel_x = in->stick_x * PIKACHU_SOURCE_WALK_MULTIPLIER;
    f->action_frame = 0;
}

void pikachu_tick(PikachuFighter *f, const PikachuInputRaw *in, PikachuMotion *out)
{
    unsigned n;
    memset(out, 0, sizeof(*out));
    if (!is_action(f->state)) choose_action(f, in);
    n = f->action_frame;

    if (!is_action(f->state)) {
        if (f->grounded) {
            ground_locomotion(f, in);
        } else if ((in->stick_x > 10 || in->stick_x < -10) &&
                   f->state != PK_JUMP_GROUND &&
                   f->state != PK_JUMP_AERIAL) {
            f->lr = in->stick_x < 0 ? -1 : 1;
            f->vel_x = in->stick_x * PIKACHU_SOURCE_WALK_MULTIPLIER;
        }
        if (!f->grounded) {
            f->vel_y -= PIKACHU_SOURCE_GRAVITY;
            if (f->vel_y < -PIKACHU_SOURCE_TERMINAL_VELOCITY) f->vel_y = -PIKACHU_SOURCE_TERMINAL_VELOCITY;
            if ((f->state == PK_JUMP_GROUND &&
                 n >= PIKACHU_SOURCE_JUMP_GROUND_FRAMES) ||
                (f->state == PK_JUMP_AERIAL &&
                 n >= PIKACHU_SOURCE_JUMP_AERIAL_FRAMES)) {
                enter(f, PK_AIR_FALL);
            } else if (f->state != PK_JUMP_GROUND &&
                       f->state != PK_JUMP_AERIAL) {
                f->state = PK_AIR_FALL;
            }
        }
        out->requested_dx = f->vel_x; out->requested_dy = f->vel_y;
    } else if (f->state == PK_JAB || f->state == PK_FTILT ||
               f->state == PK_NAIR || f->state == PK_FAIR ||
               f->state == PK_BAIR || f->state == PK_DAIR ||
               f->state == PK_DASH_ATTACK || f->state == PK_UTILT ||
               f->state == PK_DTILT || f->state == PK_UAIR) {
        normal_schedule(f, out);
    } else if (f->state == PK_THUNDER_JOLT_GROUND || f->state == PK_THUNDER_JOLT_AIR) {
        if (n == 0) {
            /* PikachuMainMotion plays only the voice on grounded SpecialN;
             * the aerial script adds Electric5. Electric1 belongs to Quick
             * Attack and must not be doubled onto Thunder Jolt. */
            out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_N);
            if (f->state == PK_THUNDER_JOLT_AIR)
                out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_5);
        }
        if (n == 21) spawn_jolt(f, out);
        if (n >= 35) enter(f, f->grounded ? PK_GROUND_WAIT : PK_AIR_FALL);
    } else if (f->state == PK_QUICK_ATTACK_START) {
        if (n == 0)
            out->events |= PIKACHU_EVENT_BIT(
                PIKACHU_EVENT_FGM_QUICK_ATTACK_START);
        if (n == PIKACHU_SOURCE_QUICK_ATTACK_AIM_FRAMES) {
            quick_first_direction(f, in);
            phase(f, PK_QUICK_ATTACK_ZIP1);
            /* Quick Attack owns an airborne velocity from the first zip, so
             * the host's vertical mover sees the same kinetic state as the
             * swept horizontal/vertical request. */
            f->grounded = 0;
            /* SpecialHi consumes both source jumps when its zip starts. */
            f->jumps_used = PIKACHU_SOURCE_JUMP_COUNT;
            quick_zip_velocity(f, f->quick_first_x, f->quick_first_y, 1.0,
                               &f->vel_x, &f->vel_y);
            out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_HI) |
                PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_1) |
                PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_SPARKLE);
            out->requested_dx = f->vel_x;
            out->requested_dy = f->vel_y;
        }
    } else if (f->state == PK_QUICK_ATTACK_ZIP1 || f->state == PK_QUICK_ATTACK_ZIP2) {
        if ((f->state == PK_QUICK_ATTACK_ZIP1 &&
             n < PIKACHU_SOURCE_QUICK_ATTACK_AIM_FRAMES +
                 PIKACHU_SOURCE_QUICK_ATTACK_ZIP_FRAMES) ||
            (f->state == PK_QUICK_ATTACK_ZIP2 &&
             n < PIKACHU_SOURCE_QUICK_ATTACK_AIM_FRAMES +
                 PIKACHU_SOURCE_QUICK_ATTACK_ZIP_FRAMES +
                 PIKACHU_SOURCE_QUICK_ATTACK_SECOND_AIM_FRAMES +
                 PIKACHU_SOURCE_QUICK_ATTACK_ZIP_FRAMES)) {
            out->requested_dx = f->vel_x;
            out->requested_dy = f->vel_y; /* swept by host */
        }
        if ((f->state == PK_QUICK_ATTACK_ZIP1 &&
             n == PIKACHU_SOURCE_QUICK_ATTACK_AIM_FRAMES +
                  PIKACHU_SOURCE_QUICK_ATTACK_ZIP_FRAMES) ||
            (f->state == PK_QUICK_ATTACK_ZIP2 &&
             n == PIKACHU_SOURCE_QUICK_ATTACK_AIM_FRAMES +
                  PIKACHU_SOURCE_QUICK_ATTACK_ZIP_FRAMES +
                  PIKACHU_SOURCE_QUICK_ATTACK_SECOND_AIM_FRAMES +
                  PIKACHU_SOURCE_QUICK_ATTACK_ZIP_FRAMES)) {
            out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_RIPPLE);
            quick_attack_begin_end(f);
            phase(f, f->state == PK_QUICK_ATTACK_ZIP1
                         ? PK_QUICK_ATTACK_WINDOW : PK_QUICK_ATTACK_RECOVERY);
        }
    } else if (f->state == PK_QUICK_ATTACK_WINDOW) {
        /* End motion 0x1730 waits 9 ticks then raises flag1 for exactly one
         * changed-direction decision. While waiting it decays vertical zip
         * velocity by /9 and applies normal air friction. */
        f->vel_y -= f->vel_y / 9.0;
        quick_air_control(f, in, 0.0, PIKACHU_SOURCE_AIR_SPEED_MAX);
        out->requested_dx = f->vel_x;
        out->requested_dy = f->vel_y;
        if (++f->quick_end_frame >= PIKACHU_SOURCE_QUICK_ATTACK_SECOND_AIM_FRAMES) {
            if (vector_changed_enough(f, in)) {
                phase(f, PK_QUICK_ATTACK_ZIP2);
                f->grounded = 0;
                quick_zip_velocity(f, in->stick_x, in->stick_y,
                                   PIKACHU_SOURCE_QUICK_ATTACK_SECOND_MULTIPLIER,
                                   &f->vel_x, &f->vel_y);
                out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_HI) |
                    PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_1) |
                    PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_SPARKLE);
                out->requested_dx = f->vel_x;
                out->requested_dy = f->vel_y;
            } else phase(f, PK_QUICK_ATTACK_RECOVERY);
        }
    } else if (f->state == PK_QUICK_ATTACK_RECOVERY) {
        /* Once flag1 has rejected (or exhausted) the second point, EndProc
         * uses gravity + half air control until the actual 46-frame end clip
         * completes. Then the common FallSpecial path uses full source air
         * accel capped at 37.5 * 0.4 = 15, without cancelling its landing
         * animation. This is a physical state, not the former frame-60 hack. */
        f->vel_y -= PIKACHU_SOURCE_GRAVITY;
        if (f->vel_y < -PIKACHU_SOURCE_TERMINAL_VELOCITY)
            f->vel_y = -PIKACHU_SOURCE_TERMINAL_VELOCITY;
        if (!f->quick_fall_special &&
            ++f->quick_end_frame >= PIKACHU_SOURCE_QUICK_ATTACK_END_ANIMATION_FRAMES)
            f->quick_fall_special = 1;
        if (f->quick_fall_special)
            quick_air_control(f, in, PIKACHU_SOURCE_AIR_ACCEL,
                              PIKACHU_SOURCE_AIR_SPEED_MAX *
                              PIKACHU_SOURCE_QUICK_ATTACK_FALL_SPECIAL_DRIFT);
        else
            quick_air_control(f, in, PIKACHU_SOURCE_AIR_ACCEL * 0.5,
                              PIKACHU_SOURCE_AIR_SPEED_MAX * 0.5);
        out->requested_dx = f->vel_x;
        out->requested_dy = f->vel_y;
    } else if (f->state == PK_THUNDER_START || f->state == PK_THUNDER_LOOP || f->state == PK_THUNDER_SELF_HIT) {
        if (n == 0 && f->state == PK_THUNDER_START) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_LW);
        if (n == 24) { spawn_thunder(f, out); phase(f, PK_THUNDER_LOOP); }
        if (f->thunder_contact_pending) { f->thunder_contact_pending = 0; f->thunder_contact_frame = n; f->projectile.active = 0; out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_PROJECTILE_THUNDER_SELF_HIT) | PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_THUNDER_AMP); if (!f->grounded) f->vel_y = 20.0; phase(f, PK_THUNDER_SELF_HIT); }
        if (f->state == PK_THUNDER_SELF_HIT && n >= f->thunder_contact_frame && n < f->thunder_contact_frame + 10) set_attack(out, 0, 90, 80, 180, 16, 0);
        if (n >= 70) enter(f, f->grounded ? PK_GROUND_WAIT : PK_AIR_FALL);
    }
    if (is_action(f->state) || is_timed_ground_state(f->state) ||
        f->state == PK_JUMP_GROUND || f->state == PK_JUMP_AERIAL)
        f->action_frame++;
    out->projectile = f->projectile;
    out->persistent_action_id = f->persistent_action_id;
    out->action_frame = n;
}

void pikachu_resolve(PikachuFighter *f, const PikachuCollision *hit)
{
    const int was_grounded = f->grounded;
    f->pos_x += hit->actual_dx; f->pos_y += hit->actual_dy;
    if (hit->hit_wall && (f->state == PK_QUICK_ATTACK_ZIP1 || f->state == PK_QUICK_ATTACK_ZIP2)) {
        quick_attack_begin_end(f);
        phase(f, PK_QUICK_ATTACK_RECOVERY);
    }
    if (hit->hit_ceiling && f->vel_y > 0.0) f->vel_y = 0.0;
    f->grounded = hit->grounded;
    if (hit->grounded) {
        f->jumps_used = 0;
        if (!was_grounded && is_standard_air_state(f->state)) {
            f->state = PK_LANDING;
            f->action_frame = 0;
            f->vel_x = 0.0;
            f->vel_y = 0.0;
        } else if (f->state == PK_AIR_FALL ||
                   f->state == PK_QUICK_ATTACK_RECOVERY) {
            f->state = PK_GROUND_WAIT;
        }
    }
}

void pikachu_sweep_zip(const PikachuFighter *f, const PikachuMotion *motion,
                       PikachuSweepProbe probe, void *user,
                       PikachuCollision *out)
{
    double x, y, dx, dy, length, walked = 0.0;
    int steps, i;
    memset(out, 0, sizeof(*out));
    if (!f || !motion || !probe) return;
    x = f->pos_x; y = f->pos_y; dx = motion->requested_dx; dy = motion->requested_dy;
    length = dx < 0.0 ? -dx : dx; if ((dy < 0.0 ? -dy : dy) > length) length = dy < 0.0 ? -dy : dy;
    steps = (int)((length + 12.499999) / 12.5);
    if (steps < 1) steps = 1;
    for (i = 1; i <= steps; ++i) {
        double nx = f->pos_x + dx * (double)i / (double)steps;
        double ny = f->pos_y + dy * (double)i / (double)steps;
        if (probe(nx, ny, user)) { out->hit_wall = dx != 0.0; out->hit_ceiling = dy > 0.0; out->hit_floor = dy < 0.0; break; }
        x = nx; y = ny; walked = (double)i;
    }
    out->actual_dx = x - f->pos_x; out->actual_dy = y - f->pos_y;
    (void)walked;
}

void pikachu_note_thunder_self_contact(PikachuFighter *f) { if (f->projectile.kind == PIKACHU_PROJECTILE_THUNDER && f->projectile.active) f->thunder_contact_pending = 1; }
void pikachu_note_projectile_finished(PikachuFighter *f, uint32_t id)
{
    if (f && f->projectile.active && f->projectile.persistent_action_id == id)
        f->projectile.active = 0;
}

static int valid(const PikachuFighter *f)
{
    return f->state >= 0 && f->state < PK_STATE_COUNT &&
        (f->lr == -1 || f->lr == 1) &&
        f->grounded >= 0 && f->grounded <= 1 &&
        f->jumps_used >= 0 && f->jumps_used <= PIKACHU_SOURCE_JUMP_COUNT &&
        f->projectile.kind >= PIKACHU_PROJECTILE_NONE &&
        f->projectile.kind <= PIKACHU_PROJECTILE_THUNDER &&
        f->quick_end_frame <= PIKACHU_SOURCE_QUICK_ATTACK_END_ANIMATION_FRAMES &&
        f->quick_fall_special >= 0 && f->quick_fall_special <= 1;
}
int pikachu_serialize(const PikachuFighter *f, uint8_t *buf, int cap)
{
    if (!f || !buf || !valid(f) || cap < (int)(1 + sizeof(*f))) return -1;
    buf[0] = PIKACHU_SAVE_VERSION; memcpy(buf + 1, f, sizeof(*f)); return (int)(1 + sizeof(*f));
}
int pikachu_deserialize(PikachuFighter *f, const uint8_t *buf, int len)
{
    PikachuFighter candidate;
    const size_t v1_size = offsetof(PikachuFighter, quick_end_frame);
    if (!f || !buf) return 0;
    memset(&candidate, 0, sizeof(candidate));
    if (buf[0] == PIKACHU_SAVE_VERSION && len == (int)(1 + sizeof(candidate))) {
        memcpy(&candidate, buf + 1, sizeof(candidate));
    } else if (buf[0] == 1u && len == (int)(1 + v1_size)) {
        /* v1 ended immediately after quick_first_{x,y}. Its new End/Fall
         * Special bookkeeping has no active legacy equivalent, so zero is
         * the only safe reconstruction. */
        memcpy(&candidate, buf + 1, v1_size);
    } else return 0;
    if (!valid(&candidate)) return 0;
    *f = candidate;
    return 1;
}
