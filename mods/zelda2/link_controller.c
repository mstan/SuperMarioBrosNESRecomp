/*
 * Clean-room Zelda II side-view Link controller.
 *
 * The constants mirror the validated Zelda II disassembly at the behavior
 * level: directional acceleration of one source unit, terminal walk velocity
 * of $18/-$18, A-jump with held-button gravity reduction, B sword slash,
 * crouched slash, and airborne up/down stabs.
 */
#include "link_controller.h"

#include "foreign_controller.h"
#include "mod_savestate.h"

#include <math.h>
#include <string.h>

/* The SMB adapter projects source units at 0.08 SMB pixels per source unit. */
#define U(px) ((px) * 12.5)

#define WALK_ACCEL U(0.125)
#define AIR_ACCEL U(0.09375)
#define WALK_MAX U(3.0)
#define GROUND_DRAG U(0.125)
#define JUMP_SPEED U(5.35)
#define GRAVITY_HELD U(0.18)
#define GRAVITY_RELEASED U(0.30)
#define FALL_MAX U(5.0)

#define SLASH_START_TICKS 6u
#define SLASH_ACTIVE_TICKS 8u
#define SLASH_RECOVER_TICKS 20u
#define CROUCH_SLASH_TICKS 16u

static int s_jump_held_last;
static int s_fire_powered;
static uint32_t s_next_beam_id = 0x5A020000u;

static double approach(double value, double target, double amount)
{
    if (value < target) {
        value += amount;
        return value > target ? target : value;
    }
    if (value > target) {
        value -= amount;
        return value < target ? target : value;
    }
    return value;
}

static int slash_state(ForeignMoveState state)
{
    return state == ZELDA2_LINK_SLASH_START ||
           state == ZELDA2_LINK_SLASH_ACTIVE ||
           state == ZELDA2_LINK_SLASH_RECOVER ||
           state == ZELDA2_LINK_CROUCH_SLASH;
}

static int sword_hitbox_active(const ForeignState *state)
{
    if (!state) return 0;
    if (state->state == ZELDA2_LINK_SLASH_ACTIVE ||
        state->state == ZELDA2_LINK_CROUCH_SLASH ||
        state->state == ZELDA2_LINK_UPSTAB ||
        state->state == ZELDA2_LINK_DOWNSTAB)
        return 1;
    return 0;
}

static void publish_sword_hitbox(const ForeignState *state,
                                 ForeignMoveResult *out)
{
    if (!sword_hitbox_active(state)) return;

    out->attack.active = 1;
    out->attack.damage = 1;
    out->attack.flags = FOREIGN_ATTACK_BREAK_BLOCKS;
    out->attack.knockback_x = U(1.25);
    out->attack.knockback_y = U(1.0);

    if (state->state == ZELDA2_LINK_UPSTAB) {
        out->attack.offset_x = 0.0;
        out->attack.offset_y = U(35.0);
        out->attack.width = U(12.0);
        out->attack.height = U(18.0);
    } else if (state->state == ZELDA2_LINK_DOWNSTAB) {
        out->attack.offset_x = U(2.0);
        out->attack.offset_y = U(1.0);
        out->attack.width = U(12.0);
        out->attack.height = U(18.0);
    } else {
        out->attack.offset_x = U(18.0);
        out->attack.offset_y = state->state == ZELDA2_LINK_CROUCH_SLASH
                                   ? U(12.0) : U(20.0);
        out->attack.width = U(18.0);
        out->attack.height = U(10.0);
    }
}

static void publish_sword_beam(const ForeignMoveState old_state,
                               const ForeignState *state,
                               ForeignMoveResult *out)
{
    ForeignActionEvent *event;
    int crouched;
    if (!s_fire_powered || !state || !out) return;
    if (state->state != ZELDA2_LINK_SLASH_ACTIVE &&
        state->state != ZELDA2_LINK_CROUCH_SLASH)
        return;
    if (state->state == old_state) return;
    if (out->actions.count >= FOREIGN_ACTION_EVENT_CAPACITY) return;

    crouched = state->state == ZELDA2_LINK_CROUCH_SLASH;
    event = &out->actions.events[out->actions.count++];
    memset(event, 0, sizeof(*event));
    event->instance_id = ++s_next_beam_id;
    if (event->instance_id == 0) event->instance_id = ++s_next_beam_id;
    event->kind = ZELDA2_LINK_ACTION_SWORD_BEAM;
    event->command = FOREIGN_ACTION_SPAWN;
    event->flags = FOREIGN_ACTION_HOSTILE | FOREIGN_ACTION_DESTROY_ON_SOLID;
    event->offset_x = U(34.0);
    event->offset_y = crouched ? U(14.0) : U(24.0);
    event->velocity_x = U(4.0);
    event->velocity_y = 0.0;
    event->width = U(12.0);
    event->height = U(10.0);
    event->damage = 1;
    event->lifetime_ticks = 56;

    if (out->audio.count < FOREIGN_AUDIO_EVENT_CAPACITY) {
        ForeignAudioEvent *audio = &out->audio.events[out->audio.count++];
        audio->cue = ZELDA2_LINK_AUDIO_SWORD_BEAM;
        audio->gain_percent = 100;
    }
}

static void link_reset(ForeignState *state)
{
    memset(state, 0, sizeof(*state));
    state->state = ZELDA2_LINK_STAND;
    state->facing = 1.0f;
    state->grounded = 1;
    s_jump_held_last = 0;
    s_fire_powered = 0;
}

static void link_tick(ForeignState *state, const ForeignInput *input,
                      ForeignMoveResult *out)
{
    const ForeignMoveState old_state = state->state;
    const int attack_pressed = input->special_pressed || input->attack_pressed;
    const int down_held = input->stick_y < -0.5f;
    const int up_held = input->stick_y > 0.5f;
    double target_x = (double)input->stick_x * WALK_MAX;

    memset(out, 0, sizeof(*out));
    state->jump_phase = FOREIGN_JUMP_NONE;

    if (input->stick_x != 0.0f)
        state->facing = input->stick_x < 0.0f ? -1.0f : 1.0f;

    if (state->grounded) {
        state->vy = 0.0;
        state->vx = approach(state->vx, target_x,
                             input->stick_x == 0.0f ? GROUND_DRAG
                                                     : WALK_ACCEL);

        if (attack_pressed && down_held) {
            state->state = ZELDA2_LINK_CROUCH_SLASH;
        } else if (attack_pressed && !slash_state(state->state)) {
            state->state = ZELDA2_LINK_SLASH_START;
        } else if (state->state == ZELDA2_LINK_CROUCH_SLASH) {
            if (state->state_frame >= CROUCH_SLASH_TICKS)
                state->state = down_held ? ZELDA2_LINK_CROUCH
                                         : ZELDA2_LINK_STAND;
        } else if (state->state == ZELDA2_LINK_SLASH_START) {
            if (state->state_frame >= SLASH_START_TICKS)
                state->state = ZELDA2_LINK_SLASH_ACTIVE;
        } else if (state->state == ZELDA2_LINK_SLASH_ACTIVE) {
            if (state->state_frame >= SLASH_ACTIVE_TICKS)
                state->state = ZELDA2_LINK_SLASH_RECOVER;
        } else if (state->state == ZELDA2_LINK_SLASH_RECOVER) {
            if (state->state_frame >= SLASH_RECOVER_TICKS)
                state->state = ZELDA2_LINK_STAND;
        } else if (input->jump_pressed) {
            state->vy = JUMP_SPEED;
            state->grounded = 0;
            state->state = ZELDA2_LINK_JUMP;
            state->jump_phase = FOREIGN_JUMP_LAUNCH;
            out->force_airborne = 1;
        } else if (down_held) {
            state->state = ZELDA2_LINK_CROUCH;
        } else {
            state->state = fabs(state->vx) > U(0.1) ? ZELDA2_LINK_WALK
                                                    : ZELDA2_LINK_STAND;
        }
    } else {
        state->vx = approach(state->vx, target_x, AIR_ACCEL);
        state->vy -= input->jump_held && state->vy > 0.0
                         ? GRAVITY_HELD : GRAVITY_RELEASED;
        if (state->vy < -FALL_MAX) state->vy = -FALL_MAX;

        if (attack_pressed || state->state == ZELDA2_LINK_UPSTAB ||
            state->state == ZELDA2_LINK_DOWNSTAB) {
            if (up_held)
                state->state = ZELDA2_LINK_UPSTAB;
            else if (down_held)
                state->state = ZELDA2_LINK_DOWNSTAB;
            else if (state->state == ZELDA2_LINK_UPSTAB ||
                     state->state == ZELDA2_LINK_DOWNSTAB)
                state->state = state->vy >= 0.0 ? ZELDA2_LINK_JUMP
                                                : ZELDA2_LINK_FALL;
        } else {
            state->state = state->vy >= 0.0 ? ZELDA2_LINK_JUMP
                                            : ZELDA2_LINK_FALL;
        }
    }

    out->requested_dx = state->vx;
    out->requested_dy = state->vy;
    out->vx = state->vx;
    out->vy = state->vy;
    out->state = state->state;
    publish_sword_hitbox(state, out);
    publish_sword_beam(old_state, state, out);

    if (state->state == old_state) state->state_frame++;
    else state->state_frame = 0;
    s_jump_held_last = input->jump_held;
}

static void link_resolve(ForeignState *state,
                         const ForeignCollisionResult *hit)
{
    state->x += hit->actual_dx;
    state->y += hit->actual_dy;
    if (hit->hit_wall) state->vx = 0.0;
    if (hit->hit_ceiling && state->vy > 0.0) state->vy = 0.0;
    if (hit->has_imposed_vy) state->vy = hit->imposed_vy;
    if (hit->grounded || hit->hit_floor) {
        const int was_airborne = !state->grounded;
        state->grounded = 1;
        state->vy = 0.0;
        if (was_airborne)
            state->state = ZELDA2_LINK_STAND;
    } else {
        state->grounded = 0;
    }
}

static const char *link_state_name(ForeignMoveState state)
{
    switch (state) {
    case ZELDA2_LINK_STAND: return "Stand";
    case ZELDA2_LINK_WALK: return "Walk";
    case ZELDA2_LINK_CROUCH: return "Crouch";
    case ZELDA2_LINK_JUMP: return "Jump";
    case ZELDA2_LINK_FALL: return "Fall";
    case ZELDA2_LINK_SLASH_START: return "SlashStart";
    case ZELDA2_LINK_SLASH_ACTIVE: return "Slash";
    case ZELDA2_LINK_SLASH_RECOVER: return "SlashRecover";
    case ZELDA2_LINK_CROUCH_SLASH: return "CrouchSlash";
    case ZELDA2_LINK_UPSTAB: return "UpStab";
    case ZELDA2_LINK_DOWNSTAB: return "DownStab";
    default: return "Unknown";
    }
}

typedef struct LinkSave {
    unsigned char version;
    unsigned char jump_held_last;
    uint32_t next_beam_id;
    ForeignState state;
} LinkSave;

typedef struct LinkSaveV1 {
    unsigned char version;
    unsigned char jump_held_last;
    ForeignState state;
} LinkSaveV1;

static int link_save_get(unsigned char *buf, int cap)
{
    const ForeignState *state = nes_foreign_state();
    LinkSave save;
    if (!state || cap < (int)sizeof(save)) return 0;
    memset(&save, 0, sizeof(save));
    save.version = 2;
    save.jump_held_last = (unsigned char)(s_jump_held_last ? 1 : 0);
    save.next_beam_id = s_next_beam_id;
    save.state = *state;
    memcpy(buf, &save, sizeof(save));
    return (int)sizeof(save);
}

static int link_save_set(const unsigned char *buf, int len)
{
    ForeignState *state = nes_foreign_state();
    LinkSave save;
    if (!state) return 0;
    memset(&save, 0, sizeof(save));
    if (len == (int)sizeof(save)) {
        memcpy(&save, buf, sizeof(save));
        if (save.version != 2) return 0;
    } else if (len == (int)sizeof(LinkSaveV1)) {
        LinkSaveV1 old;
        memcpy(&old, buf, sizeof(old));
        if (old.version != 1) return 0;
        save.version = 2;
        save.jump_held_last = old.jump_held_last;
        save.next_beam_id = 0x5A020000u;
        save.state = old.state;
    } else {
        return 0;
    }
    s_jump_held_last = save.jump_held_last != 0;
    s_next_beam_id = save.next_beam_id ? save.next_beam_id : 0x5A020000u;
    *state = save.state;
    return 1;
}

static const ForeignController kLinkController = {
    ZELDA2_LINK_CONTROLLER_ID,
    "Link (Zelda II)",
    link_reset,
    link_tick,
    link_resolve,
    link_state_name
};

int zelda2_link_controller_register(void)
{
    int ok = nes_foreign_register(&kLinkController);
    ok &= nes_mod_register_savestate_hook(ZELDA2_LINK_CONTROLLER_ID,
                                          link_save_get, link_save_set);
    return ok;
}

void zelda2_link_set_fire_power(int enabled)
{
    s_fire_powered = enabled != 0;
}

int zelda2_link_fire_powered(void)
{
    return s_fire_powered;
}

int zelda2_link_is_crouching(void)
{
    const ForeignState *state = nes_foreign_state();
    return state && (state->state == ZELDA2_LINK_CROUCH ||
                     state->state == ZELDA2_LINK_CROUCH_SLASH);
}

int zelda2_link_sword_active(void)
{
    return sword_hitbox_active(nes_foreign_state());
}
