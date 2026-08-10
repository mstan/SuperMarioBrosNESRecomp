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
#include "game_smash64_assets.h"
#include "mod_savestate.h"

#include <string.h>

/* One fighter instance behind the ABI. The adapter owns its own instance for
 * the SMB1 path; this one serves any host that drives the controller through
 * the generic interface. */
static FalconFighter s_fighter;

static const char *root_motion_animation(void)
{
    switch (s_fighter.state) {
    case FL_FALCON_KICK_GROUND:
        return "DownSpecial";
    case FL_FALCON_KICK_GROUND_AIR:
        return (s_fighter.grounded || s_fighter.state_frame < 16.0)
                   ? "VelocityXDownSpecialAir" : NULL;
    case FL_FALCON_KICK_LANDING:
        return "LandingDownSpecial";
    case FL_FALCON_KICK_AIR:
        return "DownSpecialAir";
    case FL_FALCON_KICK_BOUND:
        return "FalconDiveEnd1";
    case FL_FALCON_DIVE_GROUND:
        return "FalconDive";
    case FL_FALCON_DIVE_AIR:
        return "FalconDiveEnd2";
    case FL_FALCON_DIVE_THROW:
        return "FalconDiveEnd1";
    default:
        return NULL;
    }
}

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
    unsigned cue;

    /* ForeignInput is normalised -1..+1; the ported module works in the source
     * game's own +/-80 stick range. */
    memset(&raw, 0, sizeof(raw));
    raw.stick_x = (int)(input->stick_x * 80.0f);
    raw.stick_y = (int)(input->stick_y * 80.0f);
    raw.jump_held = input->jump_held;
    raw.jump_pressed = input->jump_pressed;
    raw.attack_pressed = input->attack_pressed;
    raw.special_pressed = input->special_pressed;

    /* Host truth in before the tick; the module reconciles a transition it
     * did not initiate (see falcon_tick). air_cause is what tells a launched
     * jump apart from a walked-off ledge. */
    s_fighter.grounded = state->grounded;
    s_fighter.host_air_cause = (int)state->air_cause;

    was_kneebend = (s_fighter.state == FL_KNEEBEND);

    falcon_tick(&s_fighter, &raw, &motion);

    {
        const char *animation = root_motion_animation();
        float delta_y, delta_z;
        if (animation && game_smash64_assets_root_delta(
                             animation, (float)s_fighter.state_frame,
                             &delta_y, &delta_z)) {
            if (!s_fighter.grounded) {
                const int dive_launch =
                    s_fighter.state == FL_FALCON_DIVE_GROUND ||
                    s_fighter.state == FL_FALCON_DIVE_AIR;
                s_fighter.vel_air_x =
                    (double)delta_z * (double)s_fighter.lr +
                    (dive_launch ? s_fighter.specialhi_vel_x : 0.0);
                s_fighter.vel_air_y = (double)delta_y +
                    (dive_launch ? s_fighter.specialhi_vel_y : 0.0);
                motion.requested_dx = s_fighter.vel_air_x;
                motion.requested_dy = s_fighter.vel_air_y;
            } else {
                s_fighter.vel_ground_x = (double)delta_z;
                motion.requested_dx =
                    (double)delta_z * (double)s_fighter.lr;
                motion.requested_dy = 0.0;
            }
        }
    }

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
    out->vx = s_fighter.grounded
                  ? s_fighter.vel_ground_x * (double)s_fighter.lr
                  : s_fighter.vel_air_x;
    out->vy = s_fighter.vel_air_y;
    out->state = s_fighter.state;
    /* This ABI is an edge, never a held state. Ground Dive is entered during
     * tick and can publish its frame-0 departure immediately. Kick Bound is
     * entered later in resolve, so its first observable tick is frame 1.
     * Catch and Throw are continuations of an already-airborne action. */
    out->force_airborne =
        (s_fighter.state == FL_FALCON_DIVE_GROUND &&
         s_fighter.state_frame == 0.0) ||
        (s_fighter.state == FL_FALCON_KICK_BOUND &&
         s_fighter.state_frame == 1.0);
    out->attack.offset_x = motion.attack.offset_x;
    out->attack.offset_y = motion.attack.offset_y;
    out->attack.width = motion.attack.width;
    out->attack.height = motion.attack.height;
    out->attack.knockback_x = motion.attack.knockback_x;
    out->attack.knockback_y = motion.attack.knockback_y;
    out->attack.damage = motion.attack.damage;
    out->attack.flags = 0;
    if (motion.attack.break_blocks)
        out->attack.flags |= FOREIGN_ATTACK_BREAK_BLOCKS;
    if (motion.attack.contact_only)
        out->attack.flags |= FOREIGN_ATTACK_CONTACT_ONLY;
    out->attack.active = motion.attack.active;

    for (cue = 1; cue < (unsigned)FALCON_AUDIO_CUE_COUNT; ++cue) {
        if ((motion.audio_cues & FALCON_AUDIO_CUE_BIT(cue)) != 0 &&
            out->audio.count < FOREIGN_AUDIO_EVENT_CAPACITY) {
            ForeignAudioEvent *event = &out->audio.events[out->audio.count++];
            event->cue = cue;
            event->gain_percent = 100;
        }
    }

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
    c.attack_connected = hit->attack_connected;
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

/* The engine's active-controller record now owns ForeignState and the stable
 * controller identity. Captain Falcon contributes only its private fighter
 * struct. The old id below remains registered as a read-only migration path
 * for existing Falcon saves; new saves emit no record under that id. */
#define CF_SAVESTATE_VERSION 1

static int cf_private_state_get(const ForeignState *state, uint8_t *buf,
                                int cap)
{
    (void)state;
    return falcon_serialize(&s_fighter, buf, cap);
}

static int cf_private_state_set(ForeignState *state, const uint8_t *buf,
                                int len)
{
    FalconFighter candidate;
    (void)state;
    if (!falcon_deserialize(&candidate, buf, len)) return 0;
    s_fighter = candidate;
    return 1;
}

static int cf_legacy_savestate_get(uint8_t *buf, int cap)
{
    (void)buf;
    (void)cap;
    return 0;
}

static int cf_legacy_savestate_set(const uint8_t *buf, int len)
{
    uint8_t fighter_len, fs_len;
    FalconFighter fighter_candidate;
    ForeignState fs_candidate;
    const ForeignController *active;
    ForeignState *fs;
    int off = 1;

    if (len == 0) return 1;
    active = nes_foreign_active();
    if (!active || strcmp(active->id, SMASH64_CAPTAIN_FALCON_ID) != 0)
        return 1; /* A legacy Falcon record cannot alter another fighter. */
    if (len < 1 || buf[0] != CF_SAVESTATE_VERSION) return 0;

    if (off + 1 > len) return 0;
    fighter_len = buf[off++];
    if (off + fighter_len > len) return 0;
    if (!falcon_deserialize(&fighter_candidate, buf + off, fighter_len))
        return 0;
    off += fighter_len;

    if (off + 1 > len) return 0;
    fs_len = buf[off++];
    fs = nes_foreign_state();
    if (!fs || (fs_len != 0 && fs_len != (uint8_t)sizeof(*fs))) return 0;
    if (off + fs_len != len) return 0;
    if (fs_len) memcpy(&fs_candidate, buf + off, sizeof(fs_candidate));

    s_fighter = fighter_candidate;
    if (fs_len) *fs = fs_candidate;
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
    ok &= nes_foreign_register_private_state(SMASH64_CAPTAIN_FALCON_ID,
                                             cf_private_state_get,
                                             cf_private_state_set);
    ok &= nes_mod_register_savestate_hook(SMASH64_CAPTAIN_FALCON_ID,
                                          cf_legacy_savestate_get,
                                          cf_legacy_savestate_set);
    return ok;
}
