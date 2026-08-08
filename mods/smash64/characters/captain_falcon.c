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
#include "mod_savestate.h"

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
    state->jump_phase = FOREIGN_JUMP_NONE;
}

static void cf_tick(ForeignState *state, const ForeignInput *input,
                    ForeignMoveResult *out)
{
    FalconInputRaw raw;
    FalconMotion motion;
    int was_kneebend;

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

    was_kneebend = (s_fighter.state == FL_KNEEBEND);

    falcon_tick(&s_fighter, &raw, &motion);

    /*
     * Publish the jumpsquat handshake (ForeignJumpPhase). Falcon's jump height
     * is chosen inside KneeBend -- ftCommonKneeBendProcUpdate flags a short hop
     * when the button comes up within C_KNEEBEND_SHORTHOP_FRAMES -- so a host
     * that launches on the button's rising edge collapses the window and every
     * jump is a full hop. Here we tell the host to hold its trigger for the
     * squat and fire on the frame the module itself leaves the ground.
     *
     * LAUNCH is the KneeBend -> airborne edge, which is exactly where
     * ftCommonJumpSetStatus ran and vel_air_y became nonzero. Detecting it from
     * `grounded` rather than from the state enum keeps this correct if the
     * module ever gains another way out of a squat.
     */
    if (s_fighter.state == FL_KNEEBEND)
        state->jump_phase = FOREIGN_JUMP_CHARGING;
    else if (was_kneebend && !s_fighter.grounded)
        state->jump_phase = FOREIGN_JUMP_LAUNCH;
    else
        state->jump_phase = FOREIGN_JUMP_NONE;

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
    c.has_imposed_vy = hit->has_imposed_vy;
    c.imposed_vy = hit->imposed_vy;

    falcon_resolve(&s_fighter, &c);

    state->x = s_fighter.pos_x;
    state->y = s_fighter.pos_y;
    state->grounded = s_fighter.grounded;
    state->state = s_fighter.state;

    /*
     * Publish velocity AFTER resolve, not just after tick.
     *
     * falcon_resolve is where the host's answer lands -- a wall zeroing
     * vel_air_x, a ceiling zeroing vel_air_y, a stomp bounce replacing it
     * outright. Without this the ring reports the velocity the fighter WANTED
     * at tick time and never the one it ended the frame with, so a bounce that
     * worked and a bounce that was discarded look identical in the trace.
     *
     * Measured: a stomp showed imposed_vy +50.00 on the same row as
     * vy -66.00, which reads as "the impulse was ignored" when in fact it had
     * been applied a few microseconds earlier in the same function.
     */
    state->vx = s_fighter.grounded
                    ? (s_fighter.vel_ground_x * (double)s_fighter.lr)
                    : s_fighter.vel_air_x;
    state->vy = s_fighter.vel_air_y;
    state->fast_fall = s_fighter.is_fastfall;
}

/* Delegates to the ported module so a trace can never disagree with the
 * physics about which state the fighter is in. */
static const char *cf_state_name(ForeignMoveState state)
{
    return falcon_state_name(state);
}

/*
 * Save-state hook (M5.5). Registered under SMASH64_CAPTAIN_FALCON_ID -- the
 * fighter's own instance lives here (s_fighter above), and s_fighter is what
 * every host, not just SMB1's adapter, drives through this ABI.
 *
 * ForeignState travels in the same blob as the fighter, not the adapter's:
 * it is engine-owned but per-fighter (nes_foreign_state() returns whichever
 * controller is active), and this file already owns the reset path for both
 * (cf_reset sets state fields straight from s_fighter). Splitting it into a
 * second hook would let the two drift out of sync on load with no way to
 * detect it; one hook, one atomic restore.
 *
 * Layout: [0] version, [1] fighter blob length, [2..] fighter blob (itself
 * version-tagged by falcon_serialize), [2+n] ForeignState length, [3+n..]
 * raw ForeignState. The length prefixes let either half change size across
 * a future version without the other needing to know.
 */
#define CF_SAVESTATE_VERSION 1

static int cf_savestate_get(uint8_t *buf, int cap)
{
    const ForeignState *fs = nes_foreign_state();
    uint8_t fs_len = fs ? (uint8_t)sizeof(*fs) : 0;
    int fighter_len;
    int off = 0;

    if (cap < 3) return -1;
    buf[off++] = CF_SAVESTATE_VERSION;

    /* Reserve the length byte, then let falcon_serialize write straight past
     * it -- avoids a second buffer and a copy. */
    fighter_len = falcon_serialize(&s_fighter, buf + off + 1, cap - off - 1);
    if (fighter_len < 0 || fighter_len > 255) return -1;
    buf[off] = (uint8_t)fighter_len;
    off += 1 + fighter_len;

    if (off + 1 > cap) return -1;
    buf[off++] = fs_len;
    if (fs_len) {
        if (off + fs_len > cap) return -1;
        memcpy(buf + off, fs, fs_len);
        off += fs_len;
    }
    return off;
}

static int cf_savestate_set(const uint8_t *buf, int len)
{
    uint8_t fighter_len, fs_len;
    ForeignState *fs;
    int off = 1;

    if (len < 1 || buf[0] != CF_SAVESTATE_VERSION) return 0;

    if (off + 1 > len) return 0;
    fighter_len = buf[off++];
    if (off + fighter_len > len) return 0;
    if (!falcon_deserialize(&s_fighter, buf + off, fighter_len))
        return 0;
    off += fighter_len;

    if (off + 1 > len) return 0;
    fs_len = buf[off++];
    fs = nes_foreign_state();
    if (fs_len && fs) {
        if (off + fs_len > len) return 0;
        /* Size mismatch means a layout drift this version byte does not
         * otherwise gate on (e.g. built against a different engine). Skip
         * restoring ForeignState rather than memcpy a foreign layout over
         * it; the fighter half above is still restored. */
        if (fs_len == (uint8_t)sizeof(*fs))
            memcpy(fs, buf + off, fs_len);
        off += fs_len;
    }
    return 1;
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
    int ok = nes_foreign_register(&kCaptainFalcon);
    ok &= nes_mod_register_savestate_hook(SMASH64_CAPTAIN_FALCON_ID,
                                          cf_savestate_get, cf_savestate_set);
    return ok;
}
