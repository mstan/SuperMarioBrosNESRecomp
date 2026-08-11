#include "../../mods/metroid/samus_controller.h"
#include "foreign_controller.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

static int failures;
static unsigned long frame;

static void expect(int value, const char *message)
{
    if (value) return;
    fprintf(stderr, "FAIL: %s\n", message);
    failures++;
}

static ForeignMoveResult tick(ForeignInput input)
{
    ForeignMoveResult move;
    memset(&move, 0, sizeof(move));
    expect(nes_foreign_tick(frame++, &input, &move), "controller ticked");
    return move;
}

static void accept(const ForeignMoveResult *move, int grounded)
{
    ForeignCollisionResult hit;
    memset(&hit, 0, sizeof(hit));
    hit.actual_dx = move->requested_dx;
    hit.actual_dy = move->requested_dy;
    hit.grounded = grounded;
    nes_foreign_resolve(&hit);
}

int main(void)
{
    ForeignInput input;
    ForeignMoveResult move;
    ForeignState *state;

    expect(metroid_samus_controller_register(), "Samus registers");
    expect(nes_foreign_select(METROID_SAMUS_CONTROLLER_ID), "Samus selects");
    nes_foreign_set_ownership(FOREIGN_OWNERSHIP_FOREIGN);
    state = nes_foreign_state();
    expect(state && state->state == METROID_SAMUS_STAND, "starts standing");

    memset(&input, 0, sizeof(input));
    input.stick_x = 1.0f;
    for (int i = 0; i < 40; ++i) {
        move = tick(input);
        accept(&move, 1);
    }
    expect(state->state == METROID_SAMUS_RUN, "running state");
    expect(fabs(move.requested_dx - 31.25) < 0.01,
           "Metroid top run is 2.5 SMB pixels/frame");

    memset(&input, 0, sizeof(input));
    input.jump_pressed = 1;
    input.jump_held = 1;
    move = tick(input);
    expect(move.force_airborne, "jump requests host departure");
    expect(state->jump_phase == FOREIGN_JUMP_LAUNCH, "jump handshake launches");
    expect(fabs(move.vy - 71.875) < 0.01, "High Jump impulse is 5.75 pixels");
    accept(&move, 0);
    expect(metroid_samus_is_spinning(), "air jump enters Screw Attack spin");

    memset(&input, 0, sizeof(input));
    move = tick(input);
    expect(move.vy <= 31.25, "button release cuts jump height");
    accept(&move, 0);
    accept(&move, 1);
    expect(state->grounded, "host landing reconciles");

    memset(&input, 0, sizeof(input));
    input.jump_pressed = 1;
    input.jump_held = 1;
    move = tick(input);
    expect(move.force_airborne, "straight-up jump requests host departure");
    expect(state->state == METROID_SAMUS_JUMP,
           "straight-up jump stays in upright jump state");
    accept(&move, 0);
    expect(!metroid_samus_is_spinning(),
           "straight-up jump does not activate Screw Attack");

    memset(&input, 0, sizeof(input));
    input.stick_x = -1.0f;
    input.jump_held = 1;
    move = tick(input);
    accept(&move, 0);
    expect(state->state == METROID_SAMUS_JUMP,
           "adding direction in midair does not turn a straight jump into a spin");
    expect(!metroid_samus_is_spinning(),
           "midair direction does not activate Screw Attack retroactively");
    accept(&move, 1);

    memset(&input, 0, sizeof(input));
    input.stick_x = -1.0f;
    input.jump_pressed = 1;
    input.jump_held = 1;
    move = tick(input);
    expect(state->state == METROID_SAMUS_SPIN,
           "direction-plus-jump enters the somersault state");
    accept(&move, 0);
    expect(metroid_samus_is_spinning(),
           "directional takeoff activates Screw Attack");
    accept(&move, 1);

    memset(&input, 0, sizeof(input));
    input.stick_y = -1.0f;
    move = tick(input);
    accept(&move, 1);
    expect(metroid_samus_is_morphed(), "Down enters Morph Ball");
    metroid_samus_bomb_jump();
    expect(!state->grounded && state->vy == 37.5,
           "bomb blast applies Metroid's three-pixel/frame vertical boost");
    memset(&input, 0, sizeof(input));
    move = tick(input);
    expect(move.force_airborne && move.vy == 34.375,
           "bomb boost survives SMB's next-frame floor reconciliation");
    accept(&move, 1);
    input.stick_y = 1.0f;
    move = tick(input);
    accept(&move, 1);
    expect(!metroid_samus_is_morphed(), "Up leaves Morph Ball");

    if (failures) {
        fprintf(stderr, "%d Samus controller assertion(s) failed\n", failures);
        return 1;
    }
    puts("Samus controller harness passed");
    return 0;
}
