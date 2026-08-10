#include "pikachu_locomotion.h"

#include <string.h>

#define PIKACHU_SAVE_VERSION 1u

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
    case PK_THUNDER_SELF_HIT: return "THUNDER_SELF_HIT"; default: return "INVALID";
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
    return state >= PK_JAB;
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
        if (n == 3) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LIGHT_M);
        if (n >= 3 && n < 11) set_attack(out, 0, 48, 100, 100, 14, 1);
        if (n >= 11 && n < 29) set_attack(out, 0, 48, 100, 100, 11, 1);
        if (n >= 35) enter(f, PK_AIR_FALL);
        break;
    case PK_FAIR:
        if (n == 7) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_2);
        if (n >= 7 && n < 27 && ((n - 7) % 3) < 2) {
            if ((n - 7) % 3 == 0) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_SWING_PULSE);
            set_attack(out, 58, 48, 70, 60, 3, 1);
        }
        if (n >= 34) enter(f, PK_AIR_FALL);
        break;
    case PK_BAIR:
        if (n == 10) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LIGHT_L);
        if (n >= 10 && n < 14) set_attack(out, -50, 50, 70, 60, 16, 1);
        if (n >= 14 && n < 22) set_attack(out, -50, 50, 70, 60, 14, 1);
        if (n >= 30) enter(f, PK_AIR_FALL);
        break;
    case PK_DAIR:
        if (n == 8) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_3);
        if (n >= 8 && n < 26) set_attack(out, 0, -15, 72, 78, 13, 1);
        if (n >= 34) enter(f, PK_AIR_FALL);
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
        if (air && in->stick_y <= -20) enter(f, PK_DAIR);
        else if (air && in->stick_x * f->lr < -20) enter(f, PK_BAIR);
        else if (air && in->stick_x * f->lr >= 20) enter(f, PK_FAIR);
        else if (air) enter(f, PK_NAIR);
        else if (in->stick_x * f->lr >= 20) enter(f, PK_FTILT);
        else enter(f, PK_JAB);
        return;
    }
    if (in->jump_pressed && (f->grounded || f->jumps_used < PIKACHU_SOURCE_JUMP_COUNT)) {
        int aerial = !f->grounded;
        f->grounded = 0; f->vel_y = aerial ? 44.0 : 50.0; f->jumps_used++;
        enter(f, aerial ? PK_JUMP_AERIAL : PK_JUMP_GROUND);
    }
}

static int vector_changed_enough(const PikachuFighter *f, const PikachuInputRaw *in)
{
    long dot, old_sq, new_sq;
    if (in->stick_x * in->stick_x + in->stick_y * in->stick_y < 60 * 60) return 0;
    dot = (long)f->quick_first_x * in->stick_x + (long)f->quick_first_y * in->stick_y;
    old_sq = (long)f->quick_first_x * f->quick_first_x + (long)f->quick_first_y * f->quick_first_y;
    new_sq = (long)in->stick_x * in->stick_x + (long)in->stick_y * in->stick_y;
    /* cos(42 degrees)^2 ~= .552. Negative dot is necessarily a changed aim. */
    return dot < 0 || dot * dot * 1000L < old_sq * new_sq * 552L;
}

void pikachu_tick(PikachuFighter *f, const PikachuInputRaw *in, PikachuMotion *out)
{
    unsigned n;
    memset(out, 0, sizeof(*out));
    if (!is_action(f->state)) choose_action(f, in);
    n = f->action_frame;

    if (!is_action(f->state)) {
        if (in->stick_x > 10 || in->stick_x < -10) {
            f->lr = in->stick_x < 0 ? -1 : 1;
            if (f->state == PK_GROUND_WAIT) {
                f->vel_x = PIKACHU_SOURCE_DASH_SPEED * f->lr;
                f->state = PK_DASH;
            } else if (f->state == PK_DASH) {
                f->vel_x = PIKACHU_SOURCE_RUN_SPEED * f->lr;
                f->state = PK_RUN;
            } else {
                f->vel_x = in->stick_x * PIKACHU_SOURCE_WALK_MULTIPLIER;
                f->state = PK_WALK;
            }
        } else if (f->grounded) { f->vel_x = 0.0; f->state = PK_GROUND_WAIT; }
        if (!f->grounded) {
            f->vel_y -= PIKACHU_SOURCE_GRAVITY;
            if (f->vel_y < -PIKACHU_SOURCE_TERMINAL_VELOCITY) f->vel_y = -PIKACHU_SOURCE_TERMINAL_VELOCITY;
            if (f->state != PK_JUMP_GROUND && f->state != PK_JUMP_AERIAL) f->state = PK_AIR_FALL;
        }
        out->requested_dx = f->vel_x; out->requested_dy = f->vel_y;
    } else if (f->state >= PK_JAB && f->state <= PK_DAIR) {
        normal_schedule(f, out);
    } else if (f->state == PK_THUNDER_JOLT_GROUND || f->state == PK_THUNDER_JOLT_AIR) {
        if (n == 0) { out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_N); if (f->state == PK_THUNDER_JOLT_AIR) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_5); }
        if (n == 21) spawn_jolt(f, out);
        if (n >= 35) enter(f, f->grounded ? PK_GROUND_WAIT : PK_AIR_FALL);
    } else if (f->state == PK_QUICK_ATTACK_START) {
        if (n == 20) {
            f->quick_first_x = in->stick_x; f->quick_first_y = in->stick_y;
            if (!f->quick_first_x && !f->quick_first_y) f->quick_first_x = f->lr * 80;
            phase(f, PK_QUICK_ATTACK_ZIP1);
            out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_HI) |
                PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_1) |
                PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_SPARKLE);
            out->requested_dx = f->quick_first_x * 0.75;
            out->requested_dy = f->quick_first_y * 0.75;
        }
    } else if (f->state == PK_QUICK_ATTACK_ZIP1 || f->state == PK_QUICK_ATTACK_ZIP2) {
        int x = f->state == PK_QUICK_ATTACK_ZIP1 ? f->quick_first_x : in->stick_x;
        int y = f->state == PK_QUICK_ATTACK_ZIP1 ? f->quick_first_y : in->stick_y;
        if ((f->state == PK_QUICK_ATTACK_ZIP1 && n < 25) ||
            (f->state == PK_QUICK_ATTACK_ZIP2 && n < 39)) {
            out->requested_dx = x * 0.75; out->requested_dy = y * 0.75; /* swept by host */
        }
        if ((f->state == PK_QUICK_ATTACK_ZIP1 && n == 25) || (f->state == PK_QUICK_ATTACK_ZIP2 && n == 39)) { out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_RIPPLE); phase(f, f->state == PK_QUICK_ATTACK_ZIP1 ? PK_QUICK_ATTACK_WINDOW : PK_QUICK_ATTACK_RECOVERY); }
    } else if (f->state == PK_QUICK_ATTACK_WINDOW) {
        if (n >= 34) {
            if (vector_changed_enough(f, in)) {
                phase(f, PK_QUICK_ATTACK_ZIP2);
                out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_HI) |
                    PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_1) |
                    PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_SPARKLE);
                out->requested_dx = in->stick_x * 0.75;
                out->requested_dy = in->stick_y * 0.75;
            } else phase(f, PK_QUICK_ATTACK_RECOVERY);
        }
    } else if (f->state == PK_QUICK_ATTACK_RECOVERY) {
        f->vel_x *= 0.4; f->vel_y -= PIKACHU_SOURCE_GRAVITY; out->requested_dx = f->vel_x; out->requested_dy = f->vel_y;
        if (n >= 60) enter(f, PK_AIR_FALL);
    } else if (f->state == PK_THUNDER_START || f->state == PK_THUNDER_LOOP || f->state == PK_THUNDER_SELF_HIT) {
        if (n == 0 && f->state == PK_THUNDER_START) out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_LW);
        if (n == 24) { spawn_thunder(f, out); phase(f, PK_THUNDER_LOOP); }
        if (f->thunder_contact_pending) { f->thunder_contact_pending = 0; f->thunder_contact_frame = n; f->projectile.active = 0; out->events |= PIKACHU_EVENT_BIT(PIKACHU_EVENT_PROJECTILE_THUNDER_SELF_HIT) | PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_THUNDER_AMP); if (!f->grounded) f->vel_y = 20.0; phase(f, PK_THUNDER_SELF_HIT); }
        if (f->state == PK_THUNDER_SELF_HIT && n >= f->thunder_contact_frame && n < f->thunder_contact_frame + 10) set_attack(out, 0, 90, 80, 180, 16, 0);
        if (n >= 70) enter(f, f->grounded ? PK_GROUND_WAIT : PK_AIR_FALL);
    }
    if (is_action(f->state)) f->action_frame++;
    out->projectile = f->projectile;
    out->persistent_action_id = f->persistent_action_id;
    out->action_frame = n;
}

void pikachu_resolve(PikachuFighter *f, const PikachuCollision *hit)
{
    f->pos_x += hit->actual_dx; f->pos_y += hit->actual_dy;
    if (hit->hit_wall && (f->state == PK_QUICK_ATTACK_ZIP1 || f->state == PK_QUICK_ATTACK_ZIP2)) phase(f, PK_QUICK_ATTACK_RECOVERY);
    if (hit->hit_ceiling && f->vel_y > 0.0) f->vel_y = 0.0;
    f->grounded = hit->grounded;
    if (hit->grounded) { f->jumps_used = 0; if (f->state == PK_AIR_FALL || f->state == PK_QUICK_ATTACK_RECOVERY) f->state = PK_GROUND_WAIT; }
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

static int valid(const PikachuFighter *f)
{
    return f->state >= 0 && f->state < PK_STATE_COUNT && (f->lr == -1 || f->lr == 1) && f->grounded >= 0 && f->grounded <= 1 && f->jumps_used >= 0 && f->jumps_used <= PIKACHU_SOURCE_JUMP_COUNT && f->projectile.kind >= PIKACHU_PROJECTILE_NONE && f->projectile.kind <= PIKACHU_PROJECTILE_THUNDER;
}
int pikachu_serialize(const PikachuFighter *f, uint8_t *buf, int cap)
{
    if (!f || !buf || !valid(f) || cap < (int)(1 + sizeof(*f))) return -1;
    buf[0] = PIKACHU_SAVE_VERSION; memcpy(buf + 1, f, sizeof(*f)); return (int)(1 + sizeof(*f));
}
int pikachu_deserialize(PikachuFighter *f, const uint8_t *buf, int len)
{
    PikachuFighter candidate;
    if (!f || !buf || len != (int)(1 + sizeof(candidate)) || buf[0] != PIKACHU_SAVE_VERSION) return 0;
    memcpy(&candidate, buf + 1, sizeof(candidate)); if (!valid(&candidate)) return 0; *f = candidate; return 1;
}
