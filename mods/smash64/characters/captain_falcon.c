/*
 * captain_falcon.c — Captain Falcon's Smash 64 locomotion.
 *
 * ============================== STATUS ==============================
 * SCAFFOLD ONLY. This controller is registered and ticked, and it reports
 * its state honestly, but it does NOT yet move the player: every tick
 * requests zero motion and stays in FALCON_IDLE.
 *
 * That is deliberate. The physics comes from a bounded, evidence-backed
 * dependency closure over the Smash 64 decompilation (see
 * docs/falcon_movement_dependency.md, milestone M0), and hand-tuning an
 * approximation in the meantime would produce something that feels
 * vaguely Falcon-ish and can never be checked against anything. An
 * obviously-inert controller is easier to reason about than a plausible
 * wrong one.
 *
 * Do not populate the constants below from memory, from a wiki, or from
 * feel. They come from ftparam/ftdata at the pinned revision, or from a
 * verified runtime trace, and every intentional adaptation gets recorded.
 * ====================================================================
 *
 * This file must stay free of SMB1 knowledge. It sees an analog-shaped
 * stick and reports desired motion; the adapter in game_smash64.c owns
 * everything about NES RAM, tiles, scale and scripted states. Keeping that
 * line clean is what lets the same controller drive a different NES game
 * later.
 */
#include "captain_falcon.h"

#include "foreign_controller.h"

#include <string.h>

/* ------------------------------------------------------------------ */
/* Character attributes                                               */
/*                                                                    */
/* Populated in M0 from src/ft/ftparam.c and src/ft/ftdata.c at pinned */
/* revision 054ffc23f396868cd1db2b87ee3a2c1d3bebb75a, in the source's  */
/* own units. The single world-scale conversion happens in the         */
/* adapter, never here — see docs/FOREIGN_CONTROLLER.md on scale.      */
/* ------------------------------------------------------------------ */

/* TODO(M0): ground accel, max walk/dash/run speed, traction, turn frames,
 * jumpsquat duration, initial jump velocity, gravity, terminal velocity,
 * air accel/drift limit, fast-fall velocity, landing lag. */

/* ------------------------------------------------------------------ */
/* Controller                                                         */
/* ------------------------------------------------------------------ */

static void falcon_reset(ForeignState *state) {
    state->state = FALCON_IDLE;
    state->state_frame = 0;
    state->vx = 0.0;
    state->vy = 0.0;
    state->facing = 1.0f;
    state->grounded = 1;
    state->fast_fall = 0;
}

static void falcon_tick(ForeignState *state, const ForeignInput *input,
                        ForeignMoveResult *out) {
    /* Facing is the one thing that is unambiguous without the source, and
     * having it live makes the trace ring readable while the rest is being
     * built out. It costs nothing and moves nobody. */
    if (input->stick_x > 0.5f) state->facing = 1.0f;
    else if (input->stick_x < -0.5f) state->facing = -1.0f;

    state->state_frame++;

    /* M0/M1 land the real state machine here. Until then: no motion. */
    out->requested_dx = 0.0;
    out->requested_dy = 0.0;
    out->vx = state->vx;
    out->vy = state->vy;
    out->state = FALCON_IDLE;
}

static void falcon_resolve(ForeignState *state,
                           const ForeignCollisionResult *hit) {
    state->x += hit->actual_dx;
    state->y += hit->actual_dy;
    state->grounded = hit->grounded;

    /* Sign convention: +y is down (NES screen space). The source's own
     * convention is confirmed in M0; if it differs, it is converted at the
     * adapter boundary, not by flipping comparisons here. */
    if (hit->hit_ceiling && state->vy < 0.0) state->vy = 0.0;
    if (hit->hit_floor   && state->vy > 0.0) state->vy = 0.0;
    if (hit->hit_wall) state->vx = 0.0;
}

static const char *falcon_state_name(ForeignMoveState state) {
    switch ((FalconMoveState)state) {
        case FALCON_IDLE:      return "IDLE";
        case FALCON_WALK:      return "WALK";
        case FALCON_DASH:      return "DASH";
        case FALCON_RUN:       return "RUN";
        case FALCON_TURN:      return "TURN";
        case FALCON_JUMPSQUAT: return "JUMPSQUAT";
        case FALCON_AIR:       return "AIR";
        case FALCON_LANDING:   return "LANDING";
    }
    return "?";
}

static const ForeignController kCaptainFalcon = {
    SMASH64_CAPTAIN_FALCON_ID,
    "Captain Falcon",
    falcon_reset,
    falcon_tick,
    falcon_resolve,
    falcon_state_name,
};

int smash64_captain_falcon_register(void) {
    return nes_foreign_register(&kCaptainFalcon);
}
