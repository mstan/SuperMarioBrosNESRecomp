/* Clean-room NES Metroid-style locomotion behind the generic controller ABI. */
#include "samus_controller.h"

#include "foreign_controller.h"
#include "mod_savestate.h"

#include <math.h>
#include <string.h>

/* The SMB adapter's documented projection is .08 pixels per source unit. */
#define U(px) ((px) * 12.5)
#define RUN_ACCEL U(0.125)
#define AIR_ACCEL U(0.09375)
#define RUN_MAX U(2.5)
#define GROUND_DRAG U(0.1875)
#define GRAVITY U(0.25)
#define JUMP_SPEED U(5.75)
#define RELEASE_CAP U(2.5)
#define FALL_MAX U(5.0)

static int s_jump_held_last;

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

static int morphed_state(ForeignMoveState state)
{
    return state == METROID_SAMUS_MORPH || state == METROID_SAMUS_ROLL;
}

static void samus_reset(ForeignState *state)
{
    memset(state, 0, sizeof(*state));
    state->state = METROID_SAMUS_STAND;
    state->facing = 1.0f;
    state->grounded = 1;
    s_jump_held_last = 0;
}

static void samus_tick(ForeignState *state, const ForeignInput *input,
                       ForeignMoveResult *out)
{
    ForeignMoveState old_state = state->state;
    double target_x = (double)input->stick_x * RUN_MAX;
    int morphed = morphed_state(state->state);

    memset(out, 0, sizeof(*out));
    state->jump_phase = FOREIGN_JUMP_NONE;

    if (input->stick_x != 0.0f)
        state->facing = input->stick_x < 0.0f ? -1.0f : 1.0f;

    if (state->grounded) {
        state->vy = 0.0;
        if (!morphed && input->stick_y < -0.5f) {
            morphed = 1;
            state->state = METROID_SAMUS_MORPH;
        } else if (morphed && input->stick_y > 0.5f) {
            morphed = 0;
            state->state = METROID_SAMUS_STAND;
        }

        state->vx = approach(state->vx, target_x,
                             input->stick_x == 0.0f ? GROUND_DRAG : RUN_ACCEL);
        if (!morphed && input->jump_pressed) {
            state->vy = JUMP_SPEED;
            state->grounded = 0;
            state->state = METROID_SAMUS_SPIN;
            state->jump_phase = FOREIGN_JUMP_LAUNCH;
            out->force_airborne = 1;
        } else if (morphed) {
            state->state = fabs(state->vx) > U(0.1)
                               ? METROID_SAMUS_ROLL : METROID_SAMUS_MORPH;
        } else {
            state->state = fabs(state->vx) > U(0.1)
                               ? METROID_SAMUS_RUN : METROID_SAMUS_STAND;
        }
    } else {
        state->vx = approach(state->vx, target_x, AIR_ACCEL);
        if (!input->jump_held && state->vy > RELEASE_CAP)
            state->vy = RELEASE_CAP;
        state->vy -= GRAVITY;
        if (state->vy < -FALL_MAX) state->vy = -FALL_MAX;
        if (input->stick_y < -0.5f) morphed = 1;
        state->state = morphed ? METROID_SAMUS_ROLL : METROID_SAMUS_SPIN;
    }

    out->requested_dx = state->vx;
    out->requested_dy = state->vy;
    out->vx = state->vx;
    out->vy = state->vy;
    out->state = state->state;
    if (state->state == old_state) state->state_frame++;
    else state->state_frame = 0;
    s_jump_held_last = input->jump_held;
}

static void samus_resolve(ForeignState *state,
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
            state->state = morphed_state(state->state)
                               ? METROID_SAMUS_MORPH : METROID_SAMUS_STAND;
    } else {
        state->grounded = 0;
    }
}

static const char *samus_state_name(ForeignMoveState state)
{
    switch (state) {
    case METROID_SAMUS_STAND: return "Stand";
    case METROID_SAMUS_RUN: return "Run";
    case METROID_SAMUS_JUMP: return "Jump";
    case METROID_SAMUS_SPIN: return "ScrewAttack";
    case METROID_SAMUS_MORPH: return "MorphBall";
    case METROID_SAMUS_ROLL: return "Roll";
    case METROID_SAMUS_HURT: return "Hurt";
    default: return "Unknown";
    }
}

typedef struct SamusSave {
    unsigned char version;
    unsigned char jump_held_last;
    ForeignState state;
} SamusSave;

static int samus_save_get(unsigned char *buf, int cap)
{
    const ForeignState *state = nes_foreign_state();
    SamusSave save;
    if (!state || cap < (int)sizeof(save)) return 0;
    memset(&save, 0, sizeof(save));
    save.version = 1;
    save.jump_held_last = (unsigned char)s_jump_held_last;
    save.state = *state;
    memcpy(buf, &save, sizeof(save));
    return (int)sizeof(save);
}

static int samus_save_set(const unsigned char *buf, int len)
{
    ForeignState *state = nes_foreign_state();
    SamusSave save;
    if (!state || len != (int)sizeof(save)) return 0;
    memcpy(&save, buf, sizeof(save));
    if (save.version != 1) return 0;
    s_jump_held_last = save.jump_held_last != 0;
    *state = save.state;
    return 1;
}

static const ForeignController kSamusController = {
    METROID_SAMUS_CONTROLLER_ID,
    "Samus Aran (NES Metroid)",
    samus_reset,
    samus_tick,
    samus_resolve,
    samus_state_name
};

int metroid_samus_controller_register(void)
{
    int ok = nes_foreign_register(&kSamusController);
    ok &= nes_mod_register_savestate_hook(METROID_SAMUS_CONTROLLER_ID,
                                          samus_save_get, samus_save_set);
    return ok;
}

int metroid_samus_is_morphed(void)
{
    const ForeignState *state = nes_foreign_state();
    return state && morphed_state(state->state);
}

int metroid_samus_is_spinning(void)
{
    const ForeignState *state = nes_foreign_state();
    return state && state->state == METROID_SAMUS_SPIN && !state->grounded;
}

void metroid_samus_force_morph(void)
{
    ForeignState *state = nes_foreign_state();
    if (state) state->state = METROID_SAMUS_MORPH;
}

void metroid_samus_bomb_jump(void)
{
    ForeignState *state = nes_foreign_state();
    if (!state || !morphed_state(state->state)) return;
    if (state->vy < U(4.0)) state->vy = U(4.0);
    state->grounded = 0;
    state->state = METROID_SAMUS_ROLL;
}
