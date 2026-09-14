/*
 * Sonic 3 & Knuckles Sonic as a ForeignController.
 *
 * All movement decisions come from s3k_player.c, a routine-by-routine port of
 * sonic3k.asm's player object. This file only translates between the engine's
 * portable controller ABI and S3K's own units:
 *
 *   ForeignInput  -> Ctrl_1_logical held/pressed bytes (A, B and C all jump,
 *                    exactly as in S3K; the NES pad's A and B are both jump)
 *   S3K 8.8 +Y-down velocities -> ForeignMoveResult/ForeignState px/frame +Y-up
 *   ForeignCollisionResult     -> the collision half of the same S3K frame
 *
 * The host (game_smash64.c) integrates s3k_sonic_move_dx/dy exactly in 8.8
 * rather than through the double-precision ForeignMoveResult fields, which
 * exist for traces and for hosts without a fixed-point path.
 */
#include "sonic_controller.h"

#include "foreign_controller.h"
#include "mod_savestate.h"

#include <string.h>

static S3KPlayer s_player;
static S3KPlayerEnvironment s_env;
static int s_env_valid;
static int s_extra_spring;
static int16_t s_move_dx;
static int16_t s_move_dy;
static uint8_t s_held;
static uint8_t s_launched;
static int s_splash_pending;
/* The Fire Shield dash's flames were out in this frame's control. */
static int s_dash_flames;

/* Obj_FireShield plays its dash animation (anim 1, set only by the dash) to
 * the end, whether or not Sonic has landed meanwhile. */
static int fire_dash_flames(const S3KPlayer *p)
{
    return (p->status_secondary & S3K_STATUS2_FIRE) && p->shield_anim == 1;
}

static uint8_t input_held(const ForeignInput *input)
{
    uint8_t held = 0;
    if (input->stick_x < -0.5f) held |= S3K_BTN_LEFT;
    if (input->stick_x > 0.5f) held |= S3K_BTN_RIGHT;
    if (input->stick_y > 0.5f) held |= S3K_BTN_UP;
    if (input->stick_y < -0.5f) held |= S3K_BTN_DOWN;
    if (input->jump_held) held |= S3K_BTN_ABC;
    return held;
}

static S3KSonicMoveState derive_state(const S3KPlayer *p)
{
    uint16_t speed = (uint16_t)(p->ground_vel < 0 ? -p->ground_vel
                                                  : p->ground_vel);
    if (p->routine == S3K_ROUTINE_DEATH) return S3K_SONIC_DEATH;
    if (p->routine == S3K_ROUTINE_HURT) return S3K_SONIC_HURT;
    if (p->spin_dash_flag && !(p->status & S3K_STATUS_ROLL))
        return S3K_SONIC_SPINDASH;
    if (p->status & S3K_STATUS_IN_AIR) {
        if (p->double_jump_flag == 1 &&
            (p->status_secondary & S3K_STATUS2_FIRE))
            return S3K_SONIC_FIRE_DASH;
        if (s3k_player_insta_shield_active(p)) return S3K_SONIC_INSTA_SHIELD;
        if (p->anim == S3K_ANIM_SPRING) return S3K_SONIC_SPRING;
        return (p->status & S3K_STATUS_ROLL) ? S3K_SONIC_JUMP
                                             : S3K_SONIC_FALL;
    }
    if (p->status & S3K_STATUS_ROLL) return S3K_SONIC_ROLL;
    switch (p->anim) {
    case S3K_ANIM_SKID: return S3K_SONIC_SKID;
    case S3K_ANIM_DUCK: return S3K_SONIC_CROUCH;
    case S3K_ANIM_LOOK_UP: return S3K_SONIC_LOOK_UP;
    case S3K_ANIM_BALANCE:
    case S3K_ANIM_BALANCE2: return S3K_SONIC_BALANCE;
    default: break;
    }
    if (p->status & S3K_STATUS_PUSH) return S3K_SONIC_PUSH;
    if (speed >= 0x600) return S3K_SONIC_RUN;
    if (speed != 0) return S3K_SONIC_WALK;
    return S3K_SONIC_STAND;
}

static void publish_state(ForeignState *state)
{
    state->state = derive_state(&s_player);
    state->vx = (double)s_move_dx / 256.0;
    state->vy = -(double)s_move_dy / 256.0;
    state->facing = (s_player.status & S3K_STATUS_FACING_LEFT) ? -1.0f : 1.0f;
    state->grounded = !(s_player.status & S3K_STATUS_IN_AIR);
}

static void sonic_reset(ForeignState *state)
{
    memset(state, 0, sizeof(*state));
    s3k_player_init(&s_player);
    s_env_valid = 0;
    s_extra_spring = 0;
    s_move_dx = 0;
    s_move_dy = 0;
    s_held = 0;
    s_launched = 0;
    s_splash_pending = 0;
    s_dash_flames = 0;
    publish_state(state);
    state->grounded = 1;
}

static void sonic_tick(ForeignState *state, const ForeignInput *input,
                       ForeignMoveResult *out)
{
    static const S3KPlayerEnvironment k_default_env = { 0, 1, 1, 1, 1, 1, 1 };
    const int old_state = state->state;
    uint8_t held = input_held(input);
    uint8_t pressed = input->jump_pressed ? S3K_BTN_ABC : 0;

    memset(out, 0, sizeof(*out));
    pressed |= (uint8_t)(held & (uint8_t)~s_held & 0x0F);
    s_held = held;

    /* Sonic_Water, applied here so the host hears about the splash; control
     * then finds the underwater bit already up to date. */
    if (s_env_valid && s3k_player_set_underwater(&s_player, s_env.underwater))
        s_splash_pending = 1;
    s3k_player_control(&s_player, held, pressed,
                       s_env_valid ? &s_env : &k_default_env,
                       &s_move_dx, &s_move_dy);
    s_env_valid = 0;
    s_launched = s_player.launched_jump;
    s_dash_flames = fire_dash_flames(&s_player);

    publish_state(state);
    state->jump_phase = s_launched ? FOREIGN_JUMP_LAUNCH : FOREIGN_JUMP_NONE;
    if (s_launched) {
        state->grounded = 0;
        out->force_airborne = 1;
    }
    out->requested_dx = state->vx;
    out->requested_dy = state->vy;
    out->vx = state->vx;
    out->vy = state->vy;
    out->state = state->state;

    if (state->state == old_state) state->state_frame++;
    else state->state_frame = 0;
}

static void sonic_resolve(ForeignState *state,
                          const ForeignCollisionResult *hit)
{
    S3KPlayerCollision c;

    memset(&c, 0, sizeof(c));
    c.on_ground = (uint8_t)(hit->grounded ? 1 : 0);
    c.hit_wall = (uint8_t)(hit->hit_wall ? 1 : 0);
    c.wall_side = hit->actual_dx < 0.0 ? -1 : 1;
    c.hit_ceiling = (uint8_t)(hit->hit_ceiling ? 1 : 0);
    if (hit->has_imposed_vy) {
        double v = -hit->imposed_vy * 256.0;
        if (v > 32767.0) v = 32767.0;
        if (v < -32768.0) v = -32768.0;
        c.has_imposed_y_vel = 1;
        c.imposed_y_vel = (int16_t)v;
    }
    c.spring = (uint8_t)(s_extra_spring ? 1 : 0);
    s_extra_spring = 0;

    state->x += hit->actual_dx;
    state->y += hit->actual_dy;
    s3k_player_reconcile(&s_player, &c, s_held);
    publish_state(state);
}

static const char *sonic_state_name(ForeignMoveState state)
{
    switch (state) {
    case S3K_SONIC_STAND: return "Stand";
    case S3K_SONIC_WALK: return "Walk";
    case S3K_SONIC_RUN: return "Run";
    case S3K_SONIC_SKID: return "Skid";
    case S3K_SONIC_CROUCH: return "Duck";
    case S3K_SONIC_SPINDASH: return "Spindash";
    case S3K_SONIC_ROLL: return "Roll";
    case S3K_SONIC_JUMP: return "Jump";
    case S3K_SONIC_FALL: return "Fall";
    case S3K_SONIC_FIRE_DASH: return "FireDash";
    case S3K_SONIC_LOOK_UP: return "LookUp";
    case S3K_SONIC_PUSH: return "Push";
    case S3K_SONIC_BALANCE: return "Balance";
    case S3K_SONIC_SPRING: return "Spring";
    case S3K_SONIC_INSTA_SHIELD: return "InstaShield";
    case S3K_SONIC_HURT: return "Hurt";
    case S3K_SONIC_DEATH: return "Death";
    default: return "Unknown";
    }
}

#define SONIC_SAVE_VERSION 3

typedef struct SonicSave {
    uint8_t version;
    uint8_t held;
    uint8_t launched;
    uint8_t pad;
    int16_t move_dx;
    int16_t move_dy;
    S3KPlayer player;
} SonicSave;

static int sonic_save_get(unsigned char *buf, int cap)
{
    SonicSave save;
    if (!buf || cap < (int)sizeof(save)) return 0;
    memset(&save, 0, sizeof(save));
    save.version = SONIC_SAVE_VERSION;
    save.held = s_held;
    save.launched = s_launched;
    save.move_dx = s_move_dx;
    save.move_dy = s_move_dy;
    save.player = s_player;
    memcpy(buf, &save, sizeof(save));
    return (int)sizeof(save);
}

static int sonic_save_set(const unsigned char *buf, int len)
{
    SonicSave save;
    if (!buf || len != (int)sizeof(save)) return 0;
    memcpy(&save, buf, sizeof(save));
    if (save.version != SONIC_SAVE_VERSION) return 0;
    if (save.player.routine != S3K_ROUTINE_CONTROL &&
        save.player.routine != S3K_ROUTINE_HURT &&
        save.player.routine != S3K_ROUTINE_DEATH)
        return 0;
    if (save.player.sfx_count > S3K_PLAYER_SFX_CAPACITY) return 0;
    s_held = save.held;
    s_launched = save.launched;
    s_move_dx = save.move_dx;
    s_move_dy = save.move_dy;
    s_player = save.player;
    s_env_valid = 0;
    s_extra_spring = 0;
    s_dash_flames = fire_dash_flames(&s_player);
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

const S3KPlayer *s3k_sonic_player(void) { return &s_player; }
S3KPlayer *s3k_sonic_player_mut(void) { return &s_player; }

void s3k_sonic_set_environment(const S3KPlayerEnvironment *env)
{
    if (!env) {
        s_env_valid = 0;
        return;
    }
    s_env = *env;
    s_env_valid = 1;
}

void s3k_sonic_set_collision_extras(int spring)
{
    s_extra_spring = spring != 0;
}

int16_t s3k_sonic_move_dx(void) { return s_move_dx; }
int16_t s3k_sonic_move_dy(void) { return s_move_dy; }
int s3k_sonic_launched_jump(void) { return s_launched; }

int s3k_sonic_take_sfx(uint8_t *ids, int cap)
{
    return s3k_player_take_sfx(&s_player, ids, cap);
}

int s3k_sonic_take_splash(void)
{
    const int splash = s_splash_pending;
    s_splash_pending = 0;
    return splash;
}

int s3k_sonic_is_ball(void)
{
    return s3k_player_is_ball(&s_player);
}

int s3k_sonic_breaks_side_blocks(void)
{
    uint16_t speed = (uint16_t)(s_player.x_vel < 0 ? -s_player.x_vel
                                                   : s_player.x_vel);
    /* loc_215B2: without the Fire Shield the wall must have the player's
     * pushing bit, which SolidObjectFull sets only for a player on the
     * ground; a jumping ball stops against it like any wall. S3K lets any
     * Fire Shield ball through; here only its dash breaks blocks in the air. */
    if ((s_player.status & S3K_STATUS_IN_AIR) && !s3k_sonic_fire_dashing())
        return 0;
    return s_player.anim == S3K_ANIM_ROLL && speed >= 0x480;
}

int s3k_sonic_insta_shield_active(void)
{
    return s3k_player_insta_shield_active(&s_player);
}

int s3k_sonic_fire_dash_hits_blocks(void)
{
    return s3k_sonic_fire_dashing() && s3k_sonic_breaks_side_blocks();
}

int s3k_sonic_low_profile(void)
{
    return (s_player.status & (S3K_STATUS_ROLL | S3K_STATUS_IN_AIR)) ==
           S3K_STATUS_ROLL;
}

int s3k_sonic_fire_dashing(void)
{
    return s_player.double_jump_flag == 1 &&
           (s_player.status & S3K_STATUS_IN_AIR) &&
           (s_player.status_secondary & S3K_STATUS2_FIRE);
}

int s3k_sonic_is_crouching(void)
{
    return s_player.anim == S3K_ANIM_DUCK || s_player.spin_dash_flag;
}

int s3k_sonic_has_fire_shield(void)
{
    return (s_player.status_secondary & S3K_STATUS2_FIRE) != 0;
}

void s3k_sonic_set_fire_shield(int enabled)
{
    s3k_player_set_shield(&s_player, enabled ? S3K_STATUS2_FIRE : 0);
}

int s3k_sonic_has_shield(void)
{
    return (s_player.status_secondary & S3K_STATUS2_SHIELD) != 0;
}

int s3k_sonic_fire_dash_flames(void)
{
    return s_dash_flames;
}

int s3k_sonic_touch_attacking(void)
{
    return s3k_player_touch_attacking(&s_player) ||
           s3k_player_invincible(&s_player) ||
           s3k_player_insta_shield_active(&s_player) || s_dash_flames;
}

int s3k_sonic_touch_immune(void)
{
    return s_player.invulnerability_timer != 0 ||
           s3k_player_invincible(&s_player) ||
           s3k_player_insta_shield_active(&s_player) ||
           s_player.routine != S3K_ROUTINE_CONTROL;
}

unsigned s3k_sonic_anim_frame(void)
{
    return s_player.level_frame_counter;
}
