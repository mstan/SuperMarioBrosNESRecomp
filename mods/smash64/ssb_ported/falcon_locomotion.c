/*
 * falcon_locomotion.c — Captain Falcon's Super Smash Bros. 64 locomotion.
 *
 * ==================== QUARANTINED — DO NOT PUBLISH ====================
 * Ported directly from VetriTheRetri/ssb-decomp-re @
 * 054ffc23f396868cd1db2b87ee3a2c1d3bebb75a, which publishes no license.
 * See UNPUBLISHED.md in this directory.
 * ======================================================================
 *
 * Every constant and every branch below is cited to its source location.
 * Where the port deliberately differs, the line is marked ADAPTATION and the
 * reason is given. Where a number could not be recovered from source, it is
 * marked UNRESOLVED and collected in one table so nothing is silently
 * invented.
 *
 * Full analysis: docs/falcon_movement_dependency.md.
 */
#include "falcon_locomotion.h"

#include <math.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/* Attributes — src/relocData/236_CaptainMain.c, dCaptainMain_attr    */
/*                                                                    */
/* US column throughout. Six of these differ in the JP build and      */
/* ftcommonrunbrake.c carries a US-only momentum-slide fix; mixing     */
/* regions would produce a Falcon that exists in no released build.    */
/* ------------------------------------------------------------------ */

#define A_WALK_SPEED_MUL      0.32
#define A_TRACTION            1.8
#define A_DASH_SPEED         80.0
#define A_DASH_DECEL          6.0
#define A_RUN_SPEED          75.0   /* JP: 70.0 */
#define A_KNEEBEND_LENGTH     4.0
#define A_JUMP_VEL_X          0.31  /* JP: 0.35 */
#define A_JUMP_HEIGHT_MUL     1.0
#define A_JUMP_HEIGHT_BASE   24.0   /* JP: 25.0 */
#define A_JUMPAERIAL_VEL_X    0.35
#define A_JUMPAERIAL_HEIGHT   0.9   /* JP: 0.95 */
#define A_AIR_ACCEL           0.04
#define A_AIR_SPEED_MAX_X    31.0
#define A_AIR_FRICTION        0.2
#define A_GRAVITY             3.4
#define A_TVEL_BASE          66.0   /* JP: 60.0 */
#define A_TVEL_FAST         100.0
#define A_JUMPS_MAX           2
#define A_DASH_TO_RUN        16.0

/* ------------------------------------------------------------------ */
/* Shared constants — src/ft/ftcommon.h, ftphysics.h, include/macros.h */
/* ------------------------------------------------------------------ */

#define C_STICK_MAX                     80
#define C_WALKMIDDLE_STICK_MIN          26
#define C_WALKFAST_STICK_MIN            62
#define C_DASH_STICK_MIN                56
#define C_DASH_BUFFER_TICS               3
#define C_DASH_DECELERATE_BEGIN        7.0
#define C_RUN_STICK_MIN                 50
#define C_TURN_STICK_MIN              (-20)
#define C_TURNRUN_STICK_MIN           (-30)
#define C_KNEEBEND_STICK_MIN            53
#define C_KNEEBEND_RUN_STICK_MIN        44
#define C_KNEEBEND_BUFFER_TICS           3
#define C_KNEEBEND_SHORTHOP_FRAMES     3.0
#define C_KNEEBEND_JUMP_F_OR_B       (-10)
#define C_KNEEBEND_BTN_SHORT_FORCE    9.0
#define C_KNEEBEND_BTN_LONG_FORCE    17.0
#define C_KNEEBEND_BTN_SHORT_MIN     36.0
#define C_KNEEBEND_BTN_LONG_MIN      63.0
#define C_KNEEBEND_BTN_HEIGHT_CLAMP  77.0
#define C_FASTFALL_STICK_MIN         (-53)
#define C_FASTFALL_BUFFER_TICS           4
#define C_AIRDRIFT_CLAMP_RANGE_MIN       8
#define C_STICKBUFFER_TICS_MAX         254
#define C_LANDING_INTERRUPT_BEGIN      4.0
#define C_STICK_DEADZONE                20  /* ftmain.c tap threshold */

#define KB_INPUT_NONE   0
#define KB_INPUT_STICK  1
#define KB_INPUT_BUTTON 2

/* ------------------------------------------------------------------ */
/* State durations                                                    */
/*                                                                    */
/* `anim_frame` counts UP by anim_speed (1.0 for every locomotion      */
/* state) and is set <= 0 when the motion script ends — see            */
/* src/ft/ftanim.c:83 and :119. So "anim_frame <= 0" in the source     */
/* means "the animation finished", and each state needs a length.      */
/*                                                                    */
/* SOURCED values come from the motion-script event timings in         */
/* src/relocData/235_CaptainMainMotion.c.                             */
/*                                                                    */
/* UNRESOLVED values would need the Figatree animation length from    */
/* src/relocData/1517_FTCaptainAnimDash.c and friends, which is        */
/* per-joint keyframe data requiring the AObj timing interpreter to    */
/* sum. Provisional values are chosen to satisfy the source's own      */
/* constraints and are the only invented numbers in this file.         */
/* ------------------------------------------------------------------ */

static const double s_state_length[FL_STATE_COUNT] = {
    [FL_WAIT]           = 0.0,   /* looping idle; never ends on its own */
    [FL_WALK_SLOW]      = 85.0,  /* SOURCED attr->walkslow_anim_length */
    [FL_WALK_MIDDLE]    = 95.0,  /* SOURCED attr->walkmiddle_anim_length */
    [FL_WALK_FAST]      = 64.0,  /* SOURCED attr->walkfast_anim_length */
    [FL_DASH]           = 21.0,  /* UNRESOLVED provisional; must exceed
                                  * A_DASH_TO_RUN (16) or dash->run is
                                  * unreachable, and exceed
                                  * C_DASH_DECELERATE_BEGIN (7) */
    [FL_RUN]            = 14.0,  /* SOURCED: Run script waits to t=14, loops */
    [FL_RUN_BRAKE]      = 6.0,   /* SOURCED: RunBrake End() at t=6 */
    [FL_TURN]           = 4.0,   /* SOURCED: Turn SetFlag1 + End at t=4 */
    [FL_TURN_RUN]       = 19.0,  /* SOURCED: TurnRun SetFlag1/2 + End at t=19 */
    [FL_KNEEBEND]       = A_KNEEBEND_LENGTH, /* SOURCED attr */
    [FL_JUMP_F]         = 30.0,  /* SOURCED: JumpF Wait(30) + End */
    [FL_JUMP_B]         = 30.0,  /* SOURCED: JumpB Wait(30) + End */
    [FL_JUMP_AERIAL_F]  = 6.0,   /* SOURCED: JumpAerial loop x2, End at t=6 */
    [FL_JUMP_AERIAL_B]  = 6.0,
    [FL_FALL]           = 0.0,   /* looping fall */
    [FL_FALL_AERIAL]    = 0.0,
    [FL_LANDING_LIGHT]  = 8.0,   /* UNRESOLVED provisional; must exceed
                                  * C_LANDING_INTERRUPT_BEGIN (4) */
    [FL_LANDING_HEAVY]  = 16.0,  /* UNRESOLVED provisional; heavy landing
                                  * plays at 0.5x speed
                                  * (FTCOMMON_LANDING_HEAVY_ANIM_SPEED) */
    /* SOURCED: exact final Figatree keyframe in the corresponding extracted
     * 1619/1628/1638-40/1652-54/1657 animation script. */
    [FL_JAB]                  = 21.0,
    [FL_FTILT]                = 29.0,
    [FL_ATTACK_AIR_N]         = 49.0,
    [FL_ATTACK_AIR_F]         = 44.0,
    [FL_ATTACK_AIR_B]         = 35.0,
    [FL_FALCON_PUNCH_GROUND]  = 89.0,
    [FL_FALCON_PUNCH_AIR]     = 89.0,
    [FL_FALCON_KICK_GROUND]      = 85.0,
    [FL_FALCON_KICK_GROUND_AIR]  = 30.0,
    [FL_FALCON_KICK_LANDING]     = 45.0,
    [FL_FALCON_KICK_AIR]         = 50.0,
    [FL_FALCON_KICK_BOUND]       = 60.0,
};

/* Turn / TurnRun set motion flag1 from the script at these frames —
 * SOURCED from 235_CaptainMainMotion.c. The flag is what triggers the
 * facing flip and velocity negation in ProcUpdate. */
#define TURN_FLAG_FRAME      4.0
#define TURNRUN_FLAG_FRAME  19.0

const char *falcon_state_name(int state)
{
    switch (state) {
        case FL_WAIT:          return "WAIT";
        case FL_WALK_SLOW:     return "WALK_SLOW";
        case FL_WALK_MIDDLE:   return "WALK_MID";
        case FL_WALK_FAST:     return "WALK_FAST";
        case FL_DASH:          return "DASH";
        case FL_RUN:           return "RUN";
        case FL_RUN_BRAKE:     return "RUN_BRAKE";
        case FL_TURN:          return "TURN";
        case FL_TURN_RUN:      return "TURN_RUN";
        case FL_KNEEBEND:      return "KNEEBEND";
        case FL_JUMP_F:        return "JUMP_F";
        case FL_JUMP_B:        return "JUMP_B";
        case FL_JUMP_AERIAL_F: return "JUMPAERIAL_F";
        case FL_JUMP_AERIAL_B: return "JUMPAERIAL_B";
        case FL_FALL:          return "FALL";
        case FL_FALL_AERIAL:   return "FALL_AERIAL";
        case FL_LANDING_LIGHT: return "LANDING_LIGHT";
        case FL_LANDING_HEAVY: return "LANDING_HEAVY";
        case FL_JAB: return "JAB";
        case FL_FTILT: return "FTILT";
        case FL_ATTACK_AIR_N: return "ATTACK_AIR_N";
        case FL_ATTACK_AIR_F: return "ATTACK_AIR_F";
        case FL_ATTACK_AIR_B: return "ATTACK_AIR_B";
        case FL_FALCON_PUNCH_GROUND: return "FALCON_PUNCH_GROUND";
        case FL_FALCON_PUNCH_AIR: return "FALCON_PUNCH_AIR";
        case FL_FALCON_KICK_GROUND: return "FALCON_KICK_GROUND";
        case FL_FALCON_KICK_GROUND_AIR: return "FALCON_KICK_GROUND_AIR";
        case FL_FALCON_KICK_LANDING: return "FALCON_KICK_LANDING";
        case FL_FALCON_KICK_AIR: return "FALCON_KICK_AIR";
        case FL_FALCON_KICK_BOUND: return "FALCON_KICK_BOUND";
    }
    return "?";
}

/* ------------------------------------------------------------------ */
/* Helpers                                                            */
/* ------------------------------------------------------------------ */

static int iabs(int v) { return v < 0 ? -v : v; }

static void set_status(FalconFighter *f, int state)
{
    f->state = state;
    f->anim_frame = 0.0;
    f->state_frame = 0.0;
}

static int is_air_state(int s)
{
    return s == FL_JUMP_F || s == FL_JUMP_B || s == FL_JUMP_AERIAL_F ||
           s == FL_JUMP_AERIAL_B || s == FL_FALL || s == FL_FALL_AERIAL ||
           s == FL_ATTACK_AIR_N || s == FL_ATTACK_AIR_F ||
           s == FL_ATTACK_AIR_B || s == FL_FALCON_PUNCH_AIR ||
           s == FL_FALCON_KICK_GROUND_AIR ||
           s == FL_FALCON_KICK_AIR || s == FL_FALCON_KICK_BOUND;
}

/* True once the state's animation has run out. Length 0 means looping. */
static int anim_ended(const FalconFighter *f)
{
    double len = s_state_length[f->state];
    return (len > 0.0) && (f->anim_frame >= len);
}

/* ------------------------------------------------------------------ */
/* ftphysics.c                                                        */
/* ------------------------------------------------------------------ */

/* ftPhysicsSetGroundVelFriction, 0x800D8978 */
static void phys_ground_friction(FalconFighter *f, double friction)
{
    if (f->vel_ground_x < 0.0) {
        f->vel_ground_x += friction;
        if (f->vel_ground_x > 0.0) f->vel_ground_x = 0.0;
    } else {
        f->vel_ground_x -= friction;
        if (f->vel_ground_x < 0.0) f->vel_ground_x = 0.0;
    }
}

/*
 * ftPhysicsApplyGroundVelFriction, 0x800D8BB4.
 *
 * ADAPTATION: the source scales traction by
 * dMPCollisionMaterialFrictions[floor_flags & MAP_VERTEX_MAT_MASK], a
 * per-surface material multiplier. SMB1 has no material classes, so the
 * multiplier is 1.0. Recorded as adaptation #1.
 */
static void phys_apply_ground_friction(FalconFighter *f)
{
    phys_ground_friction(f, 1.0 * A_TRACTION);
}

/* ftPhysicsSetGroundVelAbsStickRange, 0x800D8A70 — the walk model */
static void phys_ground_vel_abs_stick(FalconFighter *f, int stick_x,
                                      double vel, double friction)
{
    double v = (double)iabs(stick_x) * vel;

    if (f->vel_ground_x < v) {
        f->vel_ground_x = v;
    } else {
        f->vel_ground_x -= friction;
        if (f->vel_ground_x < v) f->vel_ground_x = v;
    }
}

/* ftPhysicsApplyGravityClampTVel, 0x800D8D68 */
static void phys_gravity(FalconFighter *f)
{
    f->vel_air_y -= A_GRAVITY;
    if (f->vel_air_y < -A_TVEL_BASE) f->vel_air_y = -A_TVEL_BASE;
}

/* ftPhysicsApplyFastFall, 0x800D8DA0 — a SET, not an add */
static void phys_fastfall(FalconFighter *f)
{
    f->vel_air_y = -A_TVEL_FAST;
}

/* ftPhysicsCheckSetFastFall, 0x800D8DB0 */
static void phys_check_set_fastfall(FalconFighter *f, int stick_y)
{
    if (!f->is_fastfall && (f->vel_air_y < 0.0) &&
        (stick_y <= C_FASTFALL_STICK_MIN) &&
        (f->tap_stick_y < C_FASTFALL_BUFFER_TICS)) {
        f->is_fastfall = 1;
        f->tap_stick_y = C_STICKBUFFER_TICS_MAX;
        /* Source also sets a colour-anim id here — presentation, excluded. */
    }
}

/* ftPhysicsCheckClampAirVelXDec, 0x800D8EDC */
static int phys_check_clamp_air_x_dec(FalconFighter *f, double clamp)
{
    if (fabs(f->vel_air_x) > clamp) {
        f->vel_air_x += (f->vel_air_x >= 0.0) ? -1.0 : 1.0;
        if (fabs(f->vel_air_x) < clamp)
            f->vel_air_x = (f->vel_air_x >= 0.0) ? clamp : -clamp;
        return 1;
    }
    return 0;
}

/* ftPhysicsClampAirVelXStickRange, 0x800D8FC8 */
static void phys_air_drift_stick(FalconFighter *f, int stick_x)
{
    if (iabs(stick_x) >= C_AIRDRIFT_CLAMP_RANGE_MIN) {
        f->vel_air_x += (double)stick_x * A_AIR_ACCEL;
        if (f->vel_air_x < -A_AIR_SPEED_MAX_X)      f->vel_air_x = -A_AIR_SPEED_MAX_X;
        else if (f->vel_air_x > A_AIR_SPEED_MAX_X)  f->vel_air_x =  A_AIR_SPEED_MAX_X;
    }
}

/* ftPhysicsApplyAirVelXFriction, 0x800D9074 */
static void phys_air_friction(FalconFighter *f)
{
    if (f->vel_air_x < 0.0) {
        f->vel_air_x += A_AIR_FRICTION;
        if (f->vel_air_x >= 0.0) f->vel_air_x = 0.0;
    } else {
        f->vel_air_x -= A_AIR_FRICTION;
        if (f->vel_air_x <= 0.0) f->vel_air_x = 0.0;
    }
}

/*
 * ftPhysicsApplyAirVelDriftFastFall, 0x800D9160 — the single air tick
 * shared by JumpF/B, JumpAerialF/B, Fall and FallAerial.
 *
 * The early-out matters: while |vel_air_x| exceeds air_speed_max_x it bleeds
 * off at exactly 1.0/frame and stick drift AND air friction are both skipped
 * that frame. That is how momentum survives leaving the ground fast.
 */
static void phys_air_tick(FalconFighter *f, const FalconInputRaw *in)
{
    phys_check_set_fastfall(f, in->stick_y);

    if (f->is_fastfall) phys_fastfall(f);
    else                phys_gravity(f);

    if (!phys_check_clamp_air_x_dec(f, A_AIR_SPEED_MAX_X)) {
        phys_air_drift_stick(f, in->stick_x);
        phys_air_friction(f);
    }
}

/* ------------------------------------------------------------------ */
/* State entry                                                        */
/* ------------------------------------------------------------------ */

static void enter_wait(FalconFighter *f)
{
    if (!f->grounded) f->grounded = 1;
    set_status(f, FL_WAIT);
}

/* ftCommonWalkGetWalkStatus, 0x8013E340 */
static int walk_status_for(int stick_x)
{
    int m = iabs(stick_x);
    if (m >= C_WALKFAST_STICK_MIN)   return FL_WALK_FAST;
    if (m >= C_WALKMIDDLE_STICK_MIN) return FL_WALK_MIDDLE;
    return FL_WALK_SLOW;
}

/* ftCommonDashSetStatus, 0x8013ED00 */
static void enter_dash(FalconFighter *f, int flag)
{
    set_status(f, FL_DASH);
    /* Facing-relative, exactly as the source: ftCommonDashSetStatus assigns
     * attr->dash_speed with no lr. The facing is applied when ground velocity
     * is transferred to world space -- see falcon_tick. */
    f->vel_ground_x = A_DASH_SPEED;
    f->tap_stick_x = C_STICKBUFFER_TICS_MAX;
    f->motion_flag1 = flag;
}

/* ftCommonRunSetStatus, 0x8013EEE8 */
static void enter_run(FalconFighter *f)
{
    set_status(f, FL_RUN);
    f->vel_ground_x = A_RUN_SPEED;   /* facing-relative, as the source */
}

/* ftCommonRunBrakeSetStatus, 0x8013F05C */
static void enter_run_brake(FalconFighter *f, int flag)
{
    set_status(f, FL_RUN_BRAKE);
    f->motion_flag1 = flag;
}

/* ftCommonTurnSetStatus, 0x8013E908 */
static void enter_turn(FalconFighter *f, int lr_dash)
{
    f->motion_flag1 = 0;
    set_status(f, FL_TURN);
    f->turn_flag1 = 0;
    f->turn_lr_dash = lr_dash;
    f->turn_lr_turn = -f->lr;
}

/* ftCommonTurnRunSetStatus, 0x8013F208 */
static void enter_turn_run(FalconFighter *f)
{
    set_status(f, FL_TURN_RUN);
    f->turn_flag1 = 0;
}

/* ftCommonKneeBendSetStatusParam, 0x8013F3A0 */
static void enter_kneebend(FalconFighter *f, int stick_y, int input_source)
{
    set_status(f, FL_KNEEBEND);
    f->kneebend_jump_force = stick_y;
    f->kneebend_anim_frame = 0.0;
    f->kneebend_input_source = input_source;
    f->kneebend_is_shorthop = 0;
}

/* ftCommonJumpGetJumpForceButton, 0x8013F6A0 */
static void jump_force_button(int stick_x, int is_shorthop,
                              double *out_vx, double *out_vy)
{
    double vel_x = (double)iabs(stick_x);
    double sq = sqrt(1.0 - (vel_x / (double)C_STICK_MAX) *
                           (vel_x / (double)C_STICK_MAX));
    double force = is_shorthop ? C_KNEEBEND_BTN_SHORT_FORCE
                               : C_KNEEBEND_BTN_LONG_FORCE;
    double mn    = is_shorthop ? C_KNEEBEND_BTN_SHORT_MIN
                               : C_KNEEBEND_BTN_LONG_MIN;
    double vel_y = (force * sq) + mn;

    /* Clamp onto the stick's unit circle, then to the floor, then the cap. */
    if ((vel_x * vel_x + vel_y * vel_y) >
        ((double)C_STICK_MAX * (double)C_STICK_MAX))
        vel_y = sqrt(((double)C_STICK_MAX * (double)C_STICK_MAX) - vel_x * vel_x);
    if (vel_y < mn) vel_y = mn;
    if (vel_y > C_KNEEBEND_BTN_HEIGHT_CLAMP) vel_y = C_KNEEBEND_BTN_HEIGHT_CLAMP;

    *out_vx = (stick_x >= 0) ? vel_x : -vel_x;
    *out_vy = vel_y;
}

/* ftCommonJumpSetStatus, 0x8013F880 */
static void enter_jump(FalconFighter *f, const FalconInputRaw *in)
{
    double vel_x, vel_y;

    f->grounded = 0;

    set_status(f, ((in->stick_x * f->lr) > C_KNEEBEND_JUMP_F_OR_B)
                      ? FL_JUMP_F : FL_JUMP_B);

    if (f->kneebend_input_source == KB_INPUT_BUTTON) {
        jump_force_button(in->stick_x, f->kneebend_is_shorthop, &vel_x, &vel_y);
    } else {
        vel_x = (double)in->stick_x;
        vel_y = (double)f->kneebend_jump_force;
        if (vel_y < C_KNEEBEND_STICK_MIN) vel_y = C_KNEEBEND_STICK_MIN;
    }

    f->vel_air_y = (vel_y * A_JUMP_HEIGHT_MUL) + A_JUMP_HEIGHT_BASE;
    f->vel_air_x = vel_x * A_JUMP_VEL_X;

    f->tap_stick_y = C_STICKBUFFER_TICS_MAX;
    f->jumps_used = 1;
}

/* ftCommonFallSetStatus, 0x8013F9E0 */
static void enter_fall(FalconFighter *f)
{
    f->grounded = 0;
    set_status(f, (f->jumps_used >= A_JUMPS_MAX) ? FL_FALL_AERIAL : FL_FALL);
    /* ftPhysicsClampAirVelXMax */
    if (f->vel_air_x < -A_AIR_SPEED_MAX_X)     f->vel_air_x = -A_AIR_SPEED_MAX_X;
    else if (f->vel_air_x > A_AIR_SPEED_MAX_X) f->vel_air_x =  A_AIR_SPEED_MAX_X;
}

/* ftCommonLandingSetStatus, 0x80142D9C */
static void enter_landing(FalconFighter *f)
{
    int heavy = (f->is_fastfall && (f->vel_air_y <= -A_TVEL_FAST));

    f->grounded = 1;
    f->jumps_used = 0;
    f->is_fastfall = 0;

    /* Air momentum carries into ground velocity. vel_air_x is world-space and
     * vel_ground_x is facing-relative, so undo the facing on the way in. */
    f->vel_ground_x = f->vel_air_x * (double)f->lr;
    f->vel_air_x = f->vel_air_y = 0.0;

    set_status(f, heavy ? FL_LANDING_HEAVY : FL_LANDING_LIGHT);
}

/* ftCaptainSpecialLwLandingSetStatus: direct aerial Falcon Kick has its own
 * root-motion landing pose and one-frame impact, rather than generic aerial
 * landing lag. */
static void enter_falcon_kick_landing(FalconFighter *f)
{
    f->grounded = 1;
    f->jumps_used = 0;
    f->is_fastfall = 0;
    f->vel_ground_x = 0.0;
    f->vel_air_x = f->vel_air_y = 0.0;
    set_status(f, FL_FALCON_KICK_LANDING);
}

/* M7 combat selection is an NES-pad adaptation around authentic SSB64 move
 * scripts: B is the attack button, with the d-pad choosing the move. The
 * attack timing and damage emitted below come from
 * 235_CaptainMainMotion.c; only this compact input mapping is new. */
static void enter_ground_attack(FalconFighter *f, const FalconInputRaw *in)
{
    if (in->stick_y <= -20) {
        set_status(f, FL_FALCON_KICK_GROUND);
    } else if (in->stick_y >= 20) {
        set_status(f, FL_JAB);
    } else if (iabs(in->stick_x) >= 20) {
        f->lr = in->stick_x < 0 ? -1 : 1;
        set_status(f, FL_FTILT);
    } else {
        set_status(f, FL_FALCON_PUNCH_GROUND);
    }
}

static void enter_air_attack(FalconFighter *f, const FalconInputRaw *in)
{
    if (in->stick_y <= -20) {
        set_status(f, FL_FALCON_KICK_AIR);
    } else if (in->stick_y >= 20) {
        set_status(f, FL_ATTACK_AIR_N);
    } else if (iabs(in->stick_x) >= 20) {
        set_status(f, (in->stick_x * f->lr) >= 0
                          ? FL_ATTACK_AIR_F : FL_ATTACK_AIR_B);
    } else {
        set_status(f, FL_FALCON_PUNCH_AIR);
    }
}

static int check_ground_attack(FalconFighter *f, const FalconInputRaw *in)
{
    if (!in->attack_pressed) return 0;
    enter_ground_attack(f, in);
    return 1;
}

static int check_air_attack(FalconFighter *f, const FalconInputRaw *in)
{
    if (!in->attack_pressed) return 0;
    enter_air_attack(f, in);
    return 1;
}

/* ------------------------------------------------------------------ */
/* Interrupt checks — locomotion subset only.                         */
/*                                                                    */
/* The source's ProcInterrupt bodies are dominated by combat checks    */
/* (specials, attacks, catch, guard, appeal, squat, pass, dokan). All  */
/* are early-outs that never affect locomotion, and all are excluded   */
/* per docs/falcon_movement_dependency.md §6.                          */
/* ------------------------------------------------------------------ */

/* ftCommonDashCheckInterruptCommon, 0x8013ED64 */
static int check_dash(FalconFighter *f, const FalconInputRaw *in)
{
    if ((iabs(in->stick_x) >= C_DASH_STICK_MIN) &&
        (f->tap_stick_x < C_DASH_BUFFER_TICS)) {
        if ((in->stick_x * f->lr) < 0) {
            enter_turn(f, -f->lr);
            return 1;
        }
        f->lr = (in->stick_x >= 0) ? 1 : -1;   /* ftParamSetStickLR */
        enter_dash(f, 1);
        return 1;
    }
    return 0;
}

/* ftCommonTurnCheckInterruptCommon, 0x8013EA04 */
static int check_turn(FalconFighter *f, const FalconInputRaw *in)
{
    if ((in->stick_x * f->lr) <= C_TURN_STICK_MIN) {
        enter_turn(f, 0);
        return 1;
    }
    return 0;
}

/* ftCommonWalkCheckInterruptCommon, 0x8013E648 */
static int check_walk(FalconFighter *f, const FalconInputRaw *in)
{
    if ((in->stick_x * f->lr) >= 8) {
        set_status(f, walk_status_for(in->stick_x));
        return 1;
    }
    return 0;
}

/* ftCommonWaitCheckInterruptCommon, 0x8013E2A0 */
static int check_wait(FalconFighter *f, const FalconInputRaw *in)
{
    if (((in->stick_x * f->lr) < 0) || (iabs(in->stick_x) < 8)) {
        enter_wait(f);
        return 1;
    }
    return 0;
}

/* ftCommonKneeBendGetInputTypeCommon / ...Run, 0x8013F474 / 0x8013F53C */
static int kneebend_input_type(const FalconFighter *f,
                               const FalconInputRaw *in, int from_run)
{
    int min = from_run ? C_KNEEBEND_RUN_STICK_MIN : C_KNEEBEND_STICK_MIN;
    int stick_ok = from_run ? (in->stick_y >  min) : (in->stick_y >= min);

    if (stick_ok && (f->tap_stick_y <= C_KNEEBEND_BUFFER_TICS))
        return KB_INPUT_STICK;
    if (in->jump_pressed)
        return KB_INPUT_BUTTON;
    return KB_INPUT_NONE;
}

static int check_kneebend(FalconFighter *f, const FalconInputRaw *in,
                          int from_run)
{
    int src = kneebend_input_type(f, in, from_run);
    if (src != KB_INPUT_NONE) {
        enter_kneebend(f, in->stick_y, src);
        return 1;
    }
    return 0;
}

/* ftCommonRunCheckInterruptDash, 0x8013EF2C — a ONE-FRAME window */
static int check_run_from_dash(FalconFighter *f, const FalconInputRaw *in)
{
    if ((f->anim_frame >= A_DASH_TO_RUN) &&
        (f->anim_frame < (A_DASH_TO_RUN + 1.0)) &&
        ((in->stick_x * f->lr) >= C_RUN_STICK_MIN)) {
        enter_run(f);
        return 1;
    }
    return 0;
}

/* ftCommonRunBrakeCheckInterruptRun, 0x8013F0A0 */
static int check_run_brake_from_run(FalconFighter *f, const FalconInputRaw *in)
{
    if ((in->stick_x * f->lr) < C_RUN_STICK_MIN) {
        enter_run_brake(f, 1);
        return 1;
    }
    return 0;
}

/* ftCommonTurnRunCheckInterruptRun, 0x8013F248 */
static int check_turn_run_from_run(FalconFighter *f, const FalconInputRaw *in)
{
    if ((in->stick_x * f->lr) <= C_TURNRUN_STICK_MIN) {
        enter_turn_run(f);
        return 1;
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/* Per-state ProcUpdate / ProcInterrupt / ProcPhysics                 */
/* Bindings from src/ft/ftcommon/ftcommonstatus.h                     */
/* ------------------------------------------------------------------ */

static void proc_update(FalconFighter *f, const FalconInputRaw *in)
{
    switch (f->state) {

    case FL_DASH:  /* ftCommonDashProcUpdate, 0x8013EA40 */
        if (anim_ended(f)) {
            f->vel_ground_x *= 0.75;
            enter_wait(f);
        }
        break;

    case FL_TURN:  /* ftCommonTurnProcUpdate, 0x8013E690 */
        if (!f->turn_flag1 && (f->anim_frame >= TURN_FLAG_FRAME)) {
            f->turn_flag1 = 1;
            f->lr = -f->lr;
            f->vel_ground_x = -f->vel_ground_x;
        }
        if (anim_ended(f)) enter_wait(f);
        break;

    case FL_TURN_RUN:  /* ftCommonTurnRunProcUpdate, 0x8013F170 */
        if (!f->turn_flag1 && (f->anim_frame >= TURNRUN_FLAG_FRAME)) {
            f->turn_flag1 = 1;
            f->lr = -f->lr;
            f->vel_ground_x = -f->vel_ground_x;
        }
        if (anim_ended(f)) enter_run(f);   /* ftAnimEndCheckSetStatus */
        break;

    case FL_KNEEBEND:  /* ftCommonKneeBendProcUpdate, 0x8013F2A0 */
        f->kneebend_anim_frame += 1.0;
        if ((f->kneebend_input_source == KB_INPUT_BUTTON) &&
            (f->kneebend_anim_frame <= C_KNEEBEND_SHORTHOP_FRAMES) &&
            !in->jump_held) {
            f->kneebend_is_shorthop = 1;
        }
        if (A_KNEEBEND_LENGTH <= f->kneebend_anim_frame) enter_jump(f, in);
        break;

    case FL_RUN_BRAKE:      /* ftAnimEndSetWait */
    case FL_LANDING_LIGHT:
    case FL_LANDING_HEAVY:
        if (anim_ended(f)) enter_wait(f);
        break;

    case FL_JAB:
    case FL_FTILT:
    case FL_FALCON_PUNCH_GROUND:
    case FL_FALCON_KICK_GROUND:
        if (anim_ended(f)) enter_wait(f);
        break;

    case FL_FALCON_KICK_LANDING:
        if (anim_ended(f)) enter_wait(f);
        break;

    case FL_JUMP_F:         /* ftAnimEndSetFall */
    case FL_JUMP_B:
    case FL_JUMP_AERIAL_F:
    case FL_JUMP_AERIAL_B:
        if (anim_ended(f)) enter_fall(f);
        break;

    case FL_ATTACK_AIR_N:
    case FL_ATTACK_AIR_F:
    case FL_ATTACK_AIR_B:
    case FL_FALCON_PUNCH_AIR:
    case FL_FALCON_KICK_AIR:
    case FL_FALCON_KICK_BOUND:
        if (f->state == FL_FALCON_PUNCH_AIR && f->state_frame == 40.0)
            f->vel_air_x = 65.0 * (double)f->lr;
        if (anim_ended(f)) enter_fall(f);
        break;

    case FL_FALCON_KICK_GROUND_AIR:
        if (anim_ended(f)) {
            if (f->grounded) enter_wait(f);
            else enter_fall(f);
        }
        break;

    default:
        break;
    }
}

static void proc_interrupt(FalconFighter *f, const FalconInputRaw *in)
{
    int entry = f->state;

    switch (entry) {

    /* ftCommonWaitProcInterrupt -> ftCommonGroundCheckInterrupt,
     * fighter.h:47. Locomotion members, in the macro's own order. */
    case FL_WAIT:
        if (check_ground_attack(f, in)) return;
        if (check_kneebend(f, in, 0)) return;
        if (check_dash(f, in))        return;
        if (check_turn(f, in))        return;
        if (check_walk(f, in))        return;
        break;

    /* ftCommonWalkProcInterrupt, 0x8013E390 */
    case FL_WALK_SLOW:
    case FL_WALK_MIDDLE:
    case FL_WALK_FAST:
        if (check_ground_attack(f, in)) return;
        if (check_kneebend(f, in, 0)) return;
        if (check_dash(f, in))        return;
        if (check_wait(f, in))        return;
        /* Re-select the walk tier without restarting the state. */
        {
            int want = walk_status_for(in->stick_x);
            if (want != f->state) f->state = want;
        }
        break;

    /* ftCommonDashProcInterrupt, 0x8013EA90 — representative combat check
     * restored ahead of the locomotion-only dash interrupts. */
    case FL_DASH:
        if (check_ground_attack(f, in)) return;
        if (f->anim_frame > 5.0 && f->anim_frame <= 20.0) {
            /* Re-dash only when the stick is not already held forward. */
            if (((in->stick_x * f->lr) < 0) && check_dash(f, in)) return;
        }
        if (check_kneebend(f, in, 1))       return;
        if (check_run_from_dash(f, in))     return;
        break;

    /* ftCommonRunProcInterrupt, 0x8013EE50 */
    case FL_RUN:
        if (check_ground_attack(f, in)) return;
        if (check_kneebend(f, in, 1))          return;
        if (check_turn_run_from_run(f, in))    return;
        if (check_run_brake_from_run(f, in))   return;
        break;

    /* ftCommonRunBrakeProcInterrupt, 0x8013EFB0 */
    case FL_RUN_BRAKE:
        if (check_ground_attack(f, in)) return;
        if (check_kneebend(f, in, 1)) return;
        if (f->motion_flag1 && (f->anim_frame <= 4.0)) {
            if (check_turn_run_from_run(f, in)) return;
        }
        break;

    /* ftCommonTurnProcInterrupt — dash-out-of-turn is the locomotion part. */
    case FL_TURN:
        if (check_ground_attack(f, in)) return;
        if (check_kneebend(f, in, 0)) return;
        if (f->turn_flag1 && f->turn_lr_dash != 0 &&
            ((in->stick_x * f->turn_lr_turn) >= C_DASH_STICK_MIN) &&
            (f->tap_stick_x < C_DASH_BUFFER_TICS)) {
            enter_dash(f, 0);
            return;
        }
        break;

    /* ftCommonTurnRunProcInterrupt, 0x8013F1C0 */
    case FL_TURN_RUN:
        if (check_ground_attack(f, in)) return;
        if (check_kneebend(f, in, 1)) return;
        break;

    /* ftCommonKneeBendProcInterrupt, 0x8013F334 — track the peak stick Y,
     * which becomes the jump force. */
    case FL_KNEEBEND:
        if (f->kneebend_jump_force < in->stick_y)
            f->kneebend_jump_force = in->stick_y;
        break;

    /* ftCommonLandingProcInterrupt, 0x80142B70 */
    case FL_LANDING_LIGHT:
    case FL_LANDING_HEAVY:
        if (f->anim_frame < C_LANDING_INTERRUPT_BEGIN) break;
        if (check_ground_attack(f, in)) return;
        if (check_kneebend(f, in, 0)) return;
        if (check_dash(f, in))        return;
        if (check_turn(f, in))        return;
        if (check_walk(f, in))        return;
        break;

    /* Air states: ftCommonJumpProcInterrupt / ftCommonFallProcInterrupt only
     * reach ftCommonJumpAerialCheckInterruptCommon, the double jump. Left out
     * of M1 deliberately — SMB1 has no double jump and enabling it is a scope
     * decision (jumps_max is 2). */
    case FL_JUMP_F:
    case FL_JUMP_B:
    case FL_JUMP_AERIAL_F:
    case FL_JUMP_AERIAL_B:
    case FL_FALL:
    case FL_FALL_AERIAL:
        if (check_air_attack(f, in)) return;
        break;

    default:
        break;
    }
}

static void proc_physics(FalconFighter *f, const FalconInputRaw *in)
{
    switch (f->state) {

    case FL_WAIT:
    case FL_TURN:
    case FL_KNEEBEND:
    case FL_LANDING_LIGHT:
    case FL_LANDING_HEAVY:
    case FL_JAB:
    case FL_FTILT:
    case FL_FALCON_PUNCH_GROUND:
        phys_apply_ground_friction(f);
        break;

    case FL_FALCON_KICK_GROUND:
    case FL_FALCON_KICK_LANDING:
        /* Source velocity comes from the hidden TransN animation stream. The
         * host asset bridge samples it and writes the resulting velocity back
         * into this fighter before collision resolution. */
        break;

    case FL_WALK_SLOW:
    case FL_WALK_MIDDLE:
    case FL_WALK_FAST:
        /* ftCommonWalkProcPhysics, 0x8013E548 */
        phys_ground_vel_abs_stick(f, in->stick_x, A_WALK_SPEED_MUL, A_TRACTION);
        break;

    case FL_DASH:
        /* ftCommonDashProcPhysics, 0x8013EC58 */
        if (f->anim_frame >= C_DASH_DECELERATE_BEGIN)
            phys_ground_friction(f, A_DASH_DECEL);
        break;

    case FL_RUN:
        /* ftPhysicsApplyGroundVelTransferAir — touches nothing on flat
         * ground. Run holds run_speed exactly. NOT a missing friction call. */
        break;

    case FL_RUN_BRAKE:
        /* ftCommonRunBrakeProcPhysics, 0x8013F014 */
        phys_ground_friction(f, A_TRACTION * 1.25);
        break;

    case FL_TURN_RUN:
        /*
         * ADAPTATION #3. The source binds ftPhysicsApplyGroundVelTransN here,
         * deriving velocity from the TransN skeleton joint's animated
         * translation. That needs the model, so instead hold velocity for the
         * state's duration — the observable flip already happens in
         * proc_update. This is NOT Falcon's real TurnRun.
         */
        break;

    case FL_JUMP_F:
    case FL_JUMP_B:
    case FL_JUMP_AERIAL_F:
    case FL_JUMP_AERIAL_B:
    case FL_FALL:
    case FL_FALL_AERIAL:
    case FL_ATTACK_AIR_N:
    case FL_ATTACK_AIR_F:
    case FL_ATTACK_AIR_B:
    case FL_FALCON_PUNCH_AIR:
        phys_air_tick(f, in);
        break;

    case FL_FALCON_KICK_GROUND_AIR:
        /* The continuation owns TransN through source script frame 15, then
         * flag0 changes this status to ordinary air friction. */
        if (!f->grounded && f->state_frame >= 16.0) phys_air_tick(f, in);
        break;

    case FL_FALCON_KICK_AIR:
    case FL_FALCON_KICK_BOUND:
        /* Direct-air Kick and wall-bound use authored TransN on every frame. */
        break;

    default:
        break;
    }
}

/* ------------------------------------------------------------------ */
/* Public                                                             */
/* ------------------------------------------------------------------ */

void falcon_reset(FalconFighter *f)
{
    memset(f, 0, sizeof(*f));
    f->state = FL_WAIT;
    f->lr = 1;
    f->grounded = 1;
    f->tap_stick_x = C_STICKBUFFER_TICS_MAX;
    f->tap_stick_y = C_STICKBUFFER_TICS_MAX;
}

/* ftmain.c:1320-1345 — the stick-tap buffer everything else keys on. */
static void update_tap_buffers(FalconFighter *f, const FalconInputRaw *in)
{
    if (in->stick_x >= C_STICK_DEADZONE) {
        f->tap_stick_x = (f->stick_prev_x >= C_STICK_DEADZONE)
                             ? (unsigned char)(f->tap_stick_x + 1) : 1;
    } else if (in->stick_x <= -C_STICK_DEADZONE) {
        f->tap_stick_x = (f->stick_prev_x <= -C_STICK_DEADZONE)
                             ? (unsigned char)(f->tap_stick_x + 1) : 1;
    } else {
        f->tap_stick_x = C_STICKBUFFER_TICS_MAX;
    }
    if (f->tap_stick_x > C_STICKBUFFER_TICS_MAX)
        f->tap_stick_x = C_STICKBUFFER_TICS_MAX;

    if (in->stick_y >= C_STICK_DEADZONE) {
        f->tap_stick_y = (f->stick_prev_y >= C_STICK_DEADZONE)
                             ? (unsigned char)(f->tap_stick_y + 1) : 1;
    } else if (in->stick_y <= -C_STICK_DEADZONE) {
        f->tap_stick_y = (f->stick_prev_y <= -C_STICK_DEADZONE)
                             ? (unsigned char)(f->tap_stick_y + 1) : 1;
    } else {
        f->tap_stick_y = C_STICKBUFFER_TICS_MAX;
    }
    if (f->tap_stick_y > C_STICKBUFFER_TICS_MAX)
        f->tap_stick_y = C_STICKBUFFER_TICS_MAX;

    f->stick_prev_x = in->stick_x;
    f->stick_prev_y = in->stick_y;
}

static void set_attack(FalconMotion *out, double x, double y,
                       double w, double h, int damage,
                       double kx, double ky, int break_blocks)
{
    out->attack.offset_x = x;
    out->attack.offset_y = y;
    out->attack.width = w;
    out->attack.height = h;
    out->attack.damage = damage;
    out->attack.knockback_x = kx;
    out->attack.knockback_y = ky;
    out->attack.break_blocks = break_blocks;
    out->attack.active = 1;
}

/* Hit windows and damage are sourced from the attack-event commands in
 * 235_CaptainMainMotion.c. The rectangular volumes are the portable ABI's
 * conservative union around each move's source collision spheres; they stay
 * in source units and are projected exactly once by the host adapter. */
static void emit_attack(const FalconFighter *f, FalconMotion *out)
{
    const double t = f->state_frame;

    switch (f->state) {
    case FL_JAB: /* active 5..8, damage 3 */
        if (t >= 5.0 && t < 9.0)
            set_attack(out, 210.0, 220.0, 280.0, 180.0, 3, 35.0, 20.0, 0);
        break;
    case FL_FTILT: /* active 9..15, damage 13 */
        if (t >= 9.0 && t < 16.0)
            set_attack(out, 250.0, 220.0, 380.0, 220.0, 13, 65.0, 28.0, 0);
        break;
    case FL_ATTACK_AIR_N: /* strong 4..7, late through 27 */
        if (t >= 4.0 && t < 28.0)
            set_attack(out, 40.0, 250.0, 600.0, 320.0,
                       t < 8.0 ? 16 : 13, 55.0, 42.0, 0);
        break;
    case FL_ATTACK_AIR_F: /* two source hit phases */
        if (t >= 7.0 && t < 13.0)
            set_attack(out, 260.0, 250.0, 380.0, 280.0, 10, 52.0, 32.0, 0);
        else if (t >= 21.0 && t < 29.0)
            set_attack(out, 260.0, 220.0, 400.0, 260.0, 12, 60.0, 35.0, 0);
        break;
    case FL_ATTACK_AIR_B: /* active 7..18, damage 16 */
        if (t >= 7.0 && t < 19.0)
            set_attack(out, -250.0, 240.0, 390.0, 280.0, 16, -72.0, 34.0, 0);
        break;
    case FL_FALCON_PUNCH_GROUND:
    case FL_FALCON_PUNCH_AIR: /* active 42..46, damage 24/25/26 */
        if (t >= 42.0 && t < 47.0)
            set_attack(out, 320.0, 220.0, 500.0, 320.0, 25, 105.0, 55.0, 1);
        break;
    case FL_FALCON_KICK_GROUND:
    case FL_FALCON_KICK_AIR: /* active 12..31, damage 15 */
        if (t >= 12.0 && t < 32.0)
            set_attack(out, 300.0, 150.0, 520.0, 250.0, 15, 82.0, 25.0, 1);
        break;
    case FL_FALCON_KICK_LANDING: /* source one-frame landing impact */
        if (t <= 1.0)
            set_attack(out, 0.0, 140.0, 400.0, 280.0, 12, 20.0, 20.0, 1);
        break;
    default:
        break;
    }
}

/* Audio-command frames from 235_CaptainMainMotion.c:
 *   Falcon Punch: "Falcon" on entry; punch FGM + "Punch" at frame 42.
 *   Falcon Kick:  voice + LightSwingL on entry; SpecialNStart at frame 12.
 * SMB1 has no aerial jump, so the source's JumpAerial effort clip is emitted
 * on the one host-supported jump transition as the deliberate roster adapter.
 */
static void emit_audio(const FalconFighter *f, FalconMotion *out)
{
    const double t = f->state_frame;

    if (t == 0.0) {
        switch (f->state) {
        case FL_JUMP_F:
        case FL_JUMP_B:
            out->audio_cues |= FALCON_AUDIO_CUE_BIT(FALCON_AUDIO_JUMP_EFFORT);
            break;
        case FL_FALCON_PUNCH_GROUND:
        case FL_FALCON_PUNCH_AIR:
            out->audio_cues |= FALCON_AUDIO_CUE_BIT(FALCON_AUDIO_PUNCH_FALCON);
            break;
        case FL_FALCON_KICK_GROUND:
        case FL_FALCON_KICK_AIR:
            out->audio_cues |= FALCON_AUDIO_CUE_BIT(FALCON_AUDIO_KICK);
            out->audio_cues |= FALCON_AUDIO_CUE_BIT(FALCON_AUDIO_KICK_SWING);
            break;
        default:
            break;
        }
    }

    if ((f->state == FL_FALCON_PUNCH_GROUND ||
         f->state == FL_FALCON_PUNCH_AIR) && t == 42.0) {
        out->audio_cues |= FALCON_AUDIO_CUE_BIT(FALCON_AUDIO_PUNCH_PUNCH);
        out->audio_cues |= FALCON_AUDIO_CUE_BIT(FALCON_AUDIO_PUNCH_IMPACT);
    }
    if ((f->state == FL_FALCON_KICK_GROUND ||
         f->state == FL_FALCON_KICK_AIR) && t == 12.0)
        out->audio_cues |= FALCON_AUDIO_CUE_BIT(FALCON_AUDIO_KICK_START);
}

void falcon_tick(FalconFighter *f, const FalconInputRaw *in, FalconMotion *out)
{
    int was_air;

    if (out) memset(out, 0, sizeof(*out));
    update_tap_buffers(f, in);

    /* Bound is entered from a grounded wall contact but source
     * mpCommonSetFighterAir takes effect immediately. The host may still
     * report its prior grounded byte on this first tick; preserve the forced
     * air kinetics long enough for the bridge's one-tick airborne request. */
    if (f->state == FL_FALCON_KICK_BOUND && f->state_frame == 0.0)
        f->grounded = 0;

    /*
     * Reconcile with the host before anything else.
     *
     * `grounded` is host truth -- only the host game knows whether the player
     * is standing on something. When the host reports a transition the state
     * machine did not initiate, adopt it: the host owns the DECISION to leave
     * or reach the ground, and Falcon owns what happens as a result.
     *
     * This is what lets a host keep its own jump trigger and landing detection
     * while Falcon still supplies the jump velocity, gravity and air physics.
     */
    if (!f->grounded && f->state == FL_FALCON_KICK_GROUND) {
        /* Source map handling changes kinetics immediately on floor loss but
         * preserves DownSpecial until its frame-32 flag selects the dedicated
         * VelocityXDownSpecialAir continuation. */
        f->grounded = 0;
        f->jumps_used = 1;
        if (f->state_frame >= 32.0)
            set_status(f, FL_FALCON_KICK_GROUND_AIR);
    } else if (!f->grounded && !is_air_state(f->state)) {
        if (f->host_air_cause == 1 /* FOREIGN_AIR_LAUNCHED */) {
            /* Take off with Falcon's own jump velocity, from the full-hop
             * button path -- short hop needs the jumpsquat window, which needs
             * the host to hand over its jump timing too. */
            f->kneebend_input_source = KB_INPUT_BUTTON;
            f->kneebend_is_shorthop = 0;
            f->kneebend_jump_force = in->stick_y;
            enter_jump(f, in);
        } else {
            /* Walked off a ledge, or otherwise airborne with no impulse. No
             * jump is consumed, so the character can still jump from here. */
            enter_fall(f);
            f->jumps_used = 0;
        }
        f->grounded = 0;
    } else if (f->grounded && is_air_state(f->state)) {
        if (f->state == FL_FALCON_KICK_GROUND_AIR) {
            /* A ground-origin Kick may regain the floor without changing its
             * continuation status; only direct aerial Kick uses the impact
             * landing motion. */
        } else if (f->state == FL_FALCON_KICK_AIR) {
            enter_falcon_kick_landing(f);
        } else {
            enter_landing(f);
        }
    }

    /* Animation advances before the procs observe it, per ftanim.c:83. */
    f->anim_frame += 1.0;
    f->state_frame += 1.0;

    was_air = is_air_state(f->state);

    proc_update(f, in);
    proc_interrupt(f, in);
    proc_physics(f, in);

    if (out) {
        if (is_air_state(f->state) || (!f->grounded && was_air)) {
            out->requested_dx = f->vel_air_x;
            out->requested_dy = f->vel_air_y;
        } else {
            /*
             * ftPhysicsSetGroundVelTransferAir, 0x800D87D0: world X is
             *     lr * floor_angle.y * vel_ground.x
             * On flat ground floor_angle.y is 1, which leaves the facing
             * multiply -- this is where facing-relative becomes world-space.
             * ADAPTATION #2: no slope term and no Z axis, SMB1 has neither.
             */
            out->requested_dx = (double)f->lr * f->vel_ground_x;
            out->requested_dy = 0.0;
        }
        emit_attack(f, out);
        emit_audio(f, out);
    }
}

void falcon_resolve(FalconFighter *f, const FalconCollision *hit)
{
    int in_air = !f->grounded;

    f->pos_x += hit->actual_dx;
    f->pos_y += hit->actual_dy;

    if (in_air) {
        /* Sign convention: the host reports +y as DOWN, the source works in
         * +y UP. The adapter converts; here vel_air_y > 0 is upward. */
        if (hit->hit_ceiling && f->vel_air_y > 0.0) f->vel_air_y = 0.0;
        if (hit->hit_wall) {
            f->vel_air_x = 0.0;
            if (f->state == FL_FALCON_KICK_GROUND &&
                f->state_frame >= 12.0 && f->state_frame < 32.0) {
                set_status(f, FL_FALCON_KICK_BOUND);
                f->grounded = 0;
                return;
            }
        }

        /*
         * ADAPTATION. The host launched us. Adopt it outright -- this is the
         * host's world acting on the character (a stomp bounce, a spring, a
         * shattered block, a killed jump), and the fighter has no model for
         * any of it. Applied after the ceiling clamp above so an imposed
         * velocity wins: a host that both reports a ceiling and hands us a
         * velocity is describing one event, and its number is the specific one.
         */
        if (hit->has_imposed_vy) f->vel_air_y = hit->imposed_vy;

        /* An upward impulse means we are emphatically not landing, whatever
         * the host's footing check said a frame ago. */
        if (hit->grounded && !(hit->has_imposed_vy && hit->imposed_vy > 0.0)) {
            if (f->state == FL_FALCON_KICK_GROUND ||
                f->state == FL_FALCON_KICK_GROUND_AIR) {
                f->grounded = 1;
                f->vel_ground_x = f->vel_air_x * (double)f->lr;
                f->vel_air_x = f->vel_air_y = 0.0;
            } else if (f->state == FL_FALCON_KICK_AIR) {
                enter_falcon_kick_landing(f);
            } else {
                enter_landing(f);
            }
            return;
        }
        if (hit->has_imposed_vy && hit->imposed_vy > 0.0) {
            f->grounded = 0;
            return;
        }
    } else {
        if (hit->hit_wall) {
            f->vel_ground_x = 0.0;
            if (f->state == FL_FALCON_KICK_GROUND &&
                f->state_frame >= 12.0 && f->state_frame < 32.0) {
                set_status(f, FL_FALCON_KICK_BOUND);
                f->grounded = 0;
                return;
            }
        }

        /* Walked off an edge. */
        if (!hit->grounded) {
            /*
             * ADAPTATION, restoring a source behaviour the port had dropped.
             * ftPhysicsSetGroundVelTransferAir (0x800D87D0) writes
             *     vel_air.x = lr * floor_angle.y * vel_ground.x
             * on EVERY ground physics tick, so in the source a fighter leaving
             * the ground already carries its world-space ground velocity --
             * ftCommonFallSetStatus then only clamps it. This port kept ground
             * velocity solely in vel_ground_x and projected it at the output,
             * so vel_air_x was still zero here and walking off a ledge dropped
             * all horizontal momentum. Do the transfer, then let enter_fall
             * clamp exactly as ftCommonFallSetStatus does.
             */
            f->vel_air_x = f->vel_ground_x * (double)f->lr;
            if (f->state == FL_FALCON_KICK_GROUND) {
                f->jumps_used = 1;
                f->grounded = 0;
                if (f->state_frame >= 32.0)
                    set_status(f, FL_FALCON_KICK_GROUND_AIR);
            } else {
                enter_fall(f);
            }
            if (hit->has_imposed_vy) f->vel_air_y = hit->imposed_vy;
            return;
        }
    }
    f->grounded = hit->grounded;
}

/* ------------------------------------------------------------------ */
/* Save states -- see mod_savestate.h in the engine                   */
/* ------------------------------------------------------------------ */

#define FALCON_SAVESTATE_VERSION 3

int falcon_serialize(const FalconFighter *f, uint8_t *buf, int cap)
{
    if (cap < (int)(1 + sizeof(*f))) return -1;

    buf[0] = FALCON_SAVESTATE_VERSION;
    memcpy(buf + 1, f, sizeof(*f));
    return (int)(1 + sizeof(*f));
}

int falcon_deserialize(FalconFighter *f, const uint8_t *buf, int len)
{
    /* Unknown or truncated blob -- caller keeps whatever f already holds
     * rather than getting a half-written struct. */
    if (len != (int)(1 + sizeof(*f))) return 0;
    if (buf[0] != FALCON_SAVESTATE_VERSION) return 0;

    memcpy(f, buf + 1, sizeof(*f));
    return 1;
}
