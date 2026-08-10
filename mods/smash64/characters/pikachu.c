/* Pikachu's publishable ForeignController bridge. Game-specific collision,
 * rendering, and audio mapping intentionally remain outside this file. */
#include "pikachu.h"

#include "foreign_controller.h"

#include <string.h>

/* The sole mutable fighter instance behind the generic controller ABI. */
static PikachuFighter s_fighter;

static void pk_reset(ForeignState *state)
{
    pikachu_reset(&s_fighter);
    state->state = s_fighter.state;
    state->state_frame = 0;
    state->vx = state->vy = 0.0;
    state->facing = 1.0f;
    state->grounded = 1;
    state->fast_fall = 0;
    state->air_cause = FOREIGN_AIR_NONE;
    state->jump_phase = FOREIGN_JUMP_NONE;
}

static void pk_tick(ForeignState *state, const ForeignInput *input,
                    ForeignMoveResult *out)
{
    PikachuInputRaw raw;
    memset(&raw, 0, sizeof(raw));
    raw.stick_x = (int)(input->stick_x * 80.0f);
    raw.stick_y = (int)(input->stick_y * 80.0f);
    raw.jump_pressed = input->jump_pressed;
    raw.jump_held = input->jump_held;
    raw.attack_pressed = input->attack_pressed;
    raw.special_pressed = input->special_pressed;
    s_fighter.grounded = state->grounded;
    pikachu_tick(&s_fighter, &raw, &s_fighter.last_motion);

    out->requested_dx = s_fighter.last_motion.requested_dx;
    out->requested_dy = s_fighter.last_motion.requested_dy;
    out->vx = s_fighter.vel_x;
    out->vy = s_fighter.vel_y;
    out->state = s_fighter.state;
    out->force_airborne = s_fighter.last_motion.force_airborne;
    out->attack.offset_x = s_fighter.last_motion.attack.offset_x * s_fighter.lr;
    out->attack.offset_y = s_fighter.last_motion.attack.offset_y;
    out->attack.width = s_fighter.last_motion.attack.width;
    out->attack.height = s_fighter.last_motion.attack.height;
    out->attack.damage = s_fighter.last_motion.attack.damage;
    out->attack.flags = s_fighter.last_motion.attack.break_blocks ? FOREIGN_ATTACK_BREAK_BLOCKS : 0;
    out->attack.active = s_fighter.last_motion.attack.active;

    state->state = s_fighter.state;
    state->state_frame = s_fighter.last_motion.action_frame;
    state->facing = (float)s_fighter.lr;
    state->grounded = s_fighter.grounded;
    state->vx = out->vx;
    state->vy = out->vy;
    state->jump_phase = FOREIGN_JUMP_NONE;
}

static void pk_resolve(ForeignState *state, const ForeignCollisionResult *hit)
{
    PikachuCollision collision;
    memset(&collision, 0, sizeof(collision));
    collision.actual_dx = hit->actual_dx;
    collision.actual_dy = hit->actual_dy;
    collision.grounded = hit->grounded;
    collision.hit_ceiling = hit->hit_ceiling;
    collision.hit_floor = hit->hit_floor;
    collision.hit_wall = hit->hit_wall;
    pikachu_resolve(&s_fighter, &collision);
    state->x = s_fighter.pos_x;
    state->y = s_fighter.pos_y;
    state->vx = s_fighter.vel_x;
    state->vy = s_fighter.vel_y;
    state->grounded = s_fighter.grounded;
    state->state = s_fighter.state;
}

static const char *pk_state_name(ForeignMoveState state)
{
    return pikachu_state_name(state);
}

static int pk_private_get(const ForeignState *state, uint8_t *buf, int cap)
{
    (void)state;
    return pikachu_serialize(&s_fighter, buf, cap);
}

static int pk_private_set(ForeignState *state, const uint8_t *buf, int len)
{
    PikachuFighter candidate;
    (void)state;
    if (!pikachu_deserialize(&candidate, buf, len)) return 0;
    s_fighter = candidate;
    return 1;
}

static const ForeignController kPikachu = {
    SMASH64_PIKACHU_ID, "Pikachu", pk_reset, pk_tick, pk_resolve, pk_state_name
};

int smash64_pikachu_register(void)
{
    int ok = nes_foreign_register(&kPikachu);
    ok &= nes_foreign_register_private_state(SMASH64_PIKACHU_ID,
                                             pk_private_get, pk_private_set);
    return ok;
}

const PikachuMotion *smash64_pikachu_last_motion(void) { return &s_fighter.last_motion; }
void smash64_pikachu_thunder_self_contact(void) { pikachu_note_thunder_self_contact(&s_fighter); }
