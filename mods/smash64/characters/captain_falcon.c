/*
 * captain_falcon.c — Captain Falcon as a ForeignController.
 *
 * Deliberately thin. The state machine, physics and attributes are in
 * mods/smash64/ssb_ported/falcon_locomotion.c; this file only bridges them to
 * the engine's game-agnostic ABI. That split is what lets the bridge stay
 * publishable while the direct port stays quarantined.
 *
 * The SMB1 adapter (game_smash64.c) currently drives the ported module
 * directly, because it needs the module's own richer state to decide
 * ownership. This controller registration is what makes the character
 * selectable and gives the always-on trace ring its state names; when a
 * second game or a second fighter appears, the tick/resolve callbacks below
 * become the shared path.
 */
#include "captain_falcon.h"

#include "foreign_controller.h"

#include <string.h>

/* One fighter instance behind the ABI. The adapter owns its own instance for
 * the SMB1 path; this one serves any host that drives the controller through
 * the generic interface. */
static FalconFighter s_fighter;

static void cf_reset(ForeignState *state)
{
    falcon_reset(&s_fighter);
    state->state = s_fighter.state;
    state->state_frame = 0;
    state->vx = state->vy = 0.0;
    state->facing = 1.0f;
    state->grounded = 1;
    state->fast_fall = 0;
    state->air_cause = FOREIGN_AIR_NONE;
}

static void cf_tick(ForeignState *state, const ForeignInput *input,
                    ForeignMoveResult *out)
{
    FalconInputRaw raw;
    FalconMotion motion;

    /* ForeignInput is normalised -1..+1; the ported module works in the source
     * game's own +/-80 stick range. */
    memset(&raw, 0, sizeof(raw));
    raw.stick_x = (int)(input->stick_x * 80.0f);
    raw.stick_y = (int)(input->stick_y * 80.0f);
    raw.jump_held = input->jump_held;
    raw.jump_pressed = input->jump_pressed;

    /* Host truth in before the tick; the module reconciles a transition it
     * did not initiate (see falcon_tick). air_cause is what tells a launched
     * jump apart from a walked-off ledge. */
    s_fighter.grounded = state->grounded;
    s_fighter.host_air_cause = (int)state->air_cause;

    falcon_tick(&s_fighter, &raw, &motion);

    out->requested_dx = motion.requested_dx;
    out->requested_dy = motion.requested_dy;
    out->vx = s_fighter.vel_ground_x * (double)s_fighter.lr;
    out->vy = s_fighter.vel_air_y;
    out->state = s_fighter.state;

    state->state = s_fighter.state;
    state->state_frame = (unsigned)s_fighter.state_frame;
    state->facing = (float)s_fighter.lr;
    state->fast_fall = s_fighter.is_fastfall;
    state->grounded = s_fighter.grounded;
    state->vx = out->vx;
    state->vy = s_fighter.vel_air_y;
}

static void cf_resolve(ForeignState *state, const ForeignCollisionResult *hit)
{
    FalconCollision c;

    memset(&c, 0, sizeof(c));
    c.actual_dx = hit->actual_dx;
    c.actual_dy = hit->actual_dy;
    c.grounded = hit->grounded;
    c.hit_ceiling = hit->hit_ceiling;
    c.hit_floor = hit->hit_floor;
    c.hit_wall = hit->hit_wall;

    falcon_resolve(&s_fighter, &c);

    state->x = s_fighter.pos_x;
    state->y = s_fighter.pos_y;
    state->grounded = s_fighter.grounded;
    state->state = s_fighter.state;
}

/* Delegates to the ported module so a trace can never disagree with the
 * physics about which state the fighter is in. */
static const char *cf_state_name(ForeignMoveState state)
{
    return falcon_state_name(state);
}

static const ForeignController kCaptainFalcon = {
    SMASH64_CAPTAIN_FALCON_ID,
    "Captain Falcon",
    cf_reset,
    cf_tick,
    cf_resolve,
    cf_state_name,
};

int smash64_captain_falcon_register(void)
{
    return nes_foreign_register(&kCaptainFalcon);
}
