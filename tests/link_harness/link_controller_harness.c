#include "../../mods/zelda2/link_controller.h"
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

    expect(zelda2_link_controller_register(), "Link registers");
    expect(nes_foreign_select(ZELDA2_LINK_CONTROLLER_ID), "Link selects");
    nes_foreign_set_ownership(FOREIGN_OWNERSHIP_FOREIGN);
    state = nes_foreign_state();
    expect(state && state->state == ZELDA2_LINK_STAND, "starts standing");

    memset(&input, 0, sizeof(input));
    input.stick_x = 1.0f;
    for (int i = 0; i < 48; ++i) {
        move = tick(input);
        accept(&move, 1);
    }
    expect(state->state == ZELDA2_LINK_WALK, "walking state");
    expect(fabs(move.requested_dx - 37.5) < 0.01,
           "Zelda II Link top walk is three SMB pixels/frame");

    memset(&input, 0, sizeof(input));
    input.jump_pressed = 1;
    input.jump_held = 1;
    move = tick(input);
    expect(move.force_airborne, "A jump requests host departure");
    expect(state->jump_phase == FOREIGN_JUMP_LAUNCH,
           "A jump handshake launches");
    expect(fabs(move.vy - 66.875) < 0.01,
           "Link jump impulse is tuned near Zelda II with SMB clearance");
    accept(&move, 0);
    expect(state->state == ZELDA2_LINK_JUMP, "jumping state");

    memset(&input, 0, sizeof(input));
    input.jump_held = 1;
    move = tick(input);
    accept(&move, 0);
    {
        double held_vy = move.vy;
        memset(&input, 0, sizeof(input));
        move = tick(input);
        expect(move.vy < held_vy - 1.0,
               "releasing A increases gravity like Zelda II");
    }

    memset(&input, 0, sizeof(input));
    input.stick_y = 1.0f;
    input.special_pressed = 1;
    move = tick(input);
    expect(state->state == ZELDA2_LINK_UPSTAB, "air Up+B enters upstab");
    expect(move.attack.active, "upstab publishes an attack hitbox");
    expect(move.attack.offset_y > 300.0, "upstab attacks above Link");
    accept(&move, 0);

    memset(&input, 0, sizeof(input));
    input.stick_y = -1.0f;
    input.special_pressed = 1;
    move = tick(input);
    expect(state->state == ZELDA2_LINK_DOWNSTAB, "air Down+B enters downstab");
    expect(move.attack.active, "downstab publishes an attack hitbox");
    expect(move.attack.offset_y < 30.0, "downstab attacks below Link");
    accept(&move, 1);

    memset(&input, 0, sizeof(input));
    input.stick_y = -1.0f;
    move = tick(input);
    accept(&move, 1);
    expect(zelda2_link_is_crouching(), "Down crouches on the ground");

    memset(&input, 0, sizeof(input));
    input.stick_y = -1.0f;
    input.special_pressed = 1;
    move = tick(input);
    expect(state->state == ZELDA2_LINK_CROUCH_SLASH,
           "Down+B enters crouch slash");
    expect(move.attack.active, "crouch slash publishes sword hitbox");
    expect(move.attack.flags & FOREIGN_ATTACK_BREAK_BLOCKS,
           "sword hitbox can break SMB bricks");
    accept(&move, 1);
    for (int i = 0; i < 20; ++i) {
        memset(&input, 0, sizeof(input));
        move = tick(input);
        accept(&move, 1);
    }

    memset(&input, 0, sizeof(input));
    input.special_pressed = 1;
    move = tick(input);
    expect(state->state == ZELDA2_LINK_SLASH_START,
           "B starts standing sword slash");
    for (int i = 0; i < 8; ++i) {
        memset(&input, 0, sizeof(input));
        move = tick(input);
        accept(&move, 1);
    }
    expect(state->state == ZELDA2_LINK_SLASH_ACTIVE,
           "standing slash reaches active frame");
    expect(move.attack.active, "standing slash has active sword hitbox");
    expect(move.actions.count == 0,
           "standing slash does not emit a beam without fire flower");

    zelda2_link_set_fire_power(1);
    for (int i = 0; i < 60 && state->state != ZELDA2_LINK_STAND; ++i) {
        memset(&input, 0, sizeof(input));
        move = tick(input);
        accept(&move, 1);
    }
    expect(state->state == ZELDA2_LINK_STAND,
           "standing slash recovers before fire beam test");
    memset(&input, 0, sizeof(input));
    input.special_pressed = 1;
    move = tick(input);
    expect(state->state == ZELDA2_LINK_SLASH_START,
           "fire flower B starts standing sword slash");
    int beam_seen = 0;
    for (int i = 0; i < 8; ++i) {
        memset(&input, 0, sizeof(input));
        move = tick(input);
        if (move.actions.count == 1 &&
            move.actions.events[0].kind == ZELDA2_LINK_ACTION_SWORD_BEAM &&
            (move.actions.events[0].flags &
             (FOREIGN_ACTION_HOSTILE | FOREIGN_ACTION_DESTROY_ON_SOLID)) ==
                (FOREIGN_ACTION_HOSTILE | FOREIGN_ACTION_DESTROY_ON_SOLID) &&
            move.actions.events[0].velocity_x > 0.0 &&
            move.audio.count == 1 &&
            move.audio.events[0].cue == ZELDA2_LINK_AUDIO_SWORD_BEAM &&
            move.audio.events[0].gain_percent == 100)
            beam_seen = 1;
        accept(&move, 1);
    }
    expect(state->state == ZELDA2_LINK_SLASH_ACTIVE,
           "fire flower slash reaches active frame");
    expect(beam_seen, "fire flower slash emits a forward hostile sword beam");

    for (int i = 0; i < 60 && state->state != ZELDA2_LINK_STAND; ++i) {
        memset(&input, 0, sizeof(input));
        move = tick(input);
        accept(&move, 1);
    }
    expect(state->state == ZELDA2_LINK_STAND,
           "standing slash recovers before crouch beam test");
    memset(&input, 0, sizeof(input));
    input.stick_y = -1.0f;
    input.special_pressed = 1;
    move = tick(input);
    expect(state->state == ZELDA2_LINK_CROUCH_SLASH,
           "fire flower Down+B starts crouch slash");
    expect(move.actions.count == 1 &&
           move.actions.events[0].kind == ZELDA2_LINK_ACTION_SWORD_BEAM &&
           move.actions.events[0].offset_y < 300.0 &&
           move.audio.count == 1 &&
           move.audio.events[0].cue == ZELDA2_LINK_AUDIO_SWORD_BEAM,
           "fire flower crouch slash emits lower Zelda II sword beam");

    if (failures) {
        fprintf(stderr, "%d Link controller assertion(s) failed\n", failures);
        return 1;
    }
    puts("Link controller harness passed");
    return 0;
}
