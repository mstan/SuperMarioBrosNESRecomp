/*
 * falcon_locomotion.h — Captain Falcon's Super Smash Bros. 64 locomotion.
 *
 * ==================== QUARANTINED — DO NOT PUBLISH ====================
 * Ported directly from VetriTheRetri/ssb-decomp-re @
 * 054ffc23f396868cd1db2b87ee3a2c1d3bebb75a, which publishes no license.
 * See UNPUBLISHED.md in this directory.
 * ======================================================================
 *
 * This module is a faithful port of the locomotion subset mapped in
 * docs/falcon_movement_dependency.md. It works entirely in the SOURCE
 * GAME'S UNITS -- stick range +/-80, velocities in the source's world
 * units per frame -- and knows nothing about SMB1, the NES, or pixels.
 * The single world-scale conversion happens in game_smash64.c, at the
 * host boundary, exactly once.
 *
 * Everything the source got from its engine that we cannot reproduce is
 * excluded per the classification in that document, and the three forced
 * adaptations are marked ADAPTATION where they occur.
 */
#ifndef FALCON_LOCOMOTION_H
#define FALCON_LOCOMOTION_H

/* Action states. Only the locomotion subset; combat, shields, grabs,
 * cliffs and item states are deliberately absent. */
typedef enum {
    FL_WAIT = 0,
    FL_WALK_SLOW,
    FL_WALK_MIDDLE,
    FL_WALK_FAST,
    FL_DASH,
    FL_RUN,
    FL_RUN_BRAKE,
    FL_TURN,
    FL_TURN_RUN,
    FL_KNEEBEND,
    FL_JUMP_F,
    FL_JUMP_B,
    FL_JUMP_AERIAL_F,
    FL_JUMP_AERIAL_B,
    FL_FALL,
    FL_FALL_AERIAL,
    FL_LANDING_LIGHT,
    FL_LANDING_HEAVY,
    FL_STATE_COUNT
} FalconState;

const char *falcon_state_name(int state);

/* Per-frame input, in the source game's units. */
typedef struct {
    int stick_x;        /* -80 .. +80 */
    int stick_y;        /* -80 .. +80 */
    int jump_held;      /* jump button currently down */
    int jump_pressed;   /* jump button newly pressed this frame */
} FalconInputRaw;

/* What the host's collision permitted, in source units. */
typedef struct {
    double actual_dx;
    double actual_dy;
    int    grounded;
    int    hit_ceiling;
    int    hit_floor;
    int    hit_wall;

    /*
     * ADAPTATION. The host imposed its own vertical velocity this frame, in
     * SOURCE units, +y up. Not from the source game: in Smash the fighter owns
     * its vertical motion outright, but SMB1 launches the player for reasons
     * the fighter has no model of -- a stomp bounce off a Goomba, a jumpspring,
     * a shattered brick, a ceiling that kills the jump. Those are the host's
     * world acting on the character, which is squarely the host's half of the
     * contract, so the fighter adopts them rather than modelling them.
     */
    int    has_imposed_vy;
    double imposed_vy;
} FalconCollision;

/*
 * Complete fighter state. All of it is ours -- nothing here contends for
 * a guest byte, per the host-owned-state rule in
 * nesrecomp/docs/FOREIGN_CONTROLLER.md.
 */
typedef struct {
    int    state;
    double anim_frame;      /* counts DOWN for Dash/Turn, UP elsewhere */
    double state_frame;     /* monotonic frames in state, for tracing */

    double vel_ground_x;
    double vel_air_x;
    double vel_air_y;

    double pos_x;
    double pos_y;

    int    lr;              /* -1 left, +1 right */
    int    is_fastfall;
    int    jumps_used;

    /*
     * Host truth, written by the bridge before each falcon_tick. Not from the
     * source game -- in Smash the fighter owns the ground check, but here the
     * host game owns its own collision, jump trigger and ledge detection, so
     * these are how it tells us.
     *
     * host_air_cause matches ForeignAirCause: 0 none, 1 launched, 2 fell. When
     * grounded goes to 0 without our own state machine having caused it, this
     * is what distinguishes "the host started a jump" (apply jump velocity)
     * from "the host walked us off a ledge" (just fall). grounded alone is
     * ambiguous and the input is a frame behind the host's decision.
     */
    int    grounded;
    int    host_air_cause;

    /* Stick-tap buffers, per ftmain.c:1320-1345. 1 on the frame the stick
     * crosses the +/-20 deadzone, counting up while held, pinned to 254
     * while neutral. "< 3" therefore means a fresh tap. */
    unsigned char tap_stick_x;
    unsigned char tap_stick_y;
    int    stick_prev_x;
    int    stick_prev_y;

    /* KneeBend (jumpsquat) working set. */
    double kneebend_anim_frame;
    int    kneebend_jump_force;
    int    kneebend_input_source;
    int    kneebend_is_shorthop;

    /* Turn / TurnRun working set. */
    int    turn_flag1;
    int    turn_lr_dash;
    int    turn_lr_turn;

    /* Motion flag reused by Dash and RunBrake (motion_vars.flags.flag1). */
    int    motion_flag1;
} FalconFighter;

/* Motion the state machine wants this frame, before host collision. */
typedef struct {
    double requested_dx;
    double requested_dy;
} FalconMotion;

void falcon_reset(FalconFighter *f);

/*
 * One frame. Order matches the source's per-status dispatch:
 * input buffers, then ProcUpdate, then ProcInterrupt, then ProcPhysics.
 */
void falcon_tick(FalconFighter *f, const FalconInputRaw *in,
                 FalconMotion *out);

/* Feed the host's collision outcome back in. */
void falcon_resolve(FalconFighter *f, const FalconCollision *hit);

#endif /* FALCON_LOCOMOTION_H */
