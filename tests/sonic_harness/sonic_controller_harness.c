#include "../../mods/s3k/sonic_controller.h"

#include "foreign_controller.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

static int failures;

static void expect(int cond, const char *msg)
{
    if (!cond) {
        fprintf(stderr, "FAIL: %s\n", msg);
        failures++;
    }
}

static ForeignMoveResult tick(ForeignState *state, ForeignInput in)
{
    ForeignMoveResult out;
    memset(&out, 0, sizeof(out));
    nes_foreign_tick(0, &in, &out);
    *state = *nes_foreign_state();
    return out;
}

static void resolve_flat(void)
{
    ForeignCollisionResult hit;
    memset(&hit, 0, sizeof(hit));
    hit.grounded = 1;
    nes_foreign_resolve(&hit);
}

int main(void)
{
    ForeignInput in;
    ForeignState state;
    ForeignMoveResult out;

    expect(s3k_sonic_controller_register(), "Sonic registers");
    expect(nes_foreign_select(S3K_SONIC_CONTROLLER_ID), "Sonic selects");
    nes_foreign_set_ownership(FOREIGN_OWNERSHIP_FOREIGN);
    state = *nes_foreign_state();
    expect(state.state == S3K_SONIC_STAND, "starts standing");

    memset(&in, 0, sizeof(in));
    in.stick_x = 1.0f;
    for (int i = 0; i < 40; ++i) {
        out = tick(&state, in);
        resolve_flat();
        state = *nes_foreign_state();
    }
    expect(state.vx > 3.5 && state.vx <= 4.01, "accelerates to adapted S3K top speed");
    expect(out.state == S3K_SONIC_RUN, "fast ground motion presents run");

    memset(&in, 0, sizeof(in));
    in.jump_pressed = 1;
    in.jump_held = 1;
    out = tick(&state, in);
    expect(out.force_airborne, "jump asks host to leave ground");
    expect(out.vy > 6.0, "jump impulse adapted from S3K");
    expect(out.audio.count == 1 &&
           out.audio.events[0].cue == S3K_SONIC_AUDIO_JUMP,
           "jump emits the S3&K jump cue");

    state = *nes_foreign_state();
    state.grounded = 0;
    *nes_foreign_state() = state;
    memset(&in, 0, sizeof(in));
    in.jump_held = 0;
    out = tick(&state, in);
    expect(out.vy <= 4.0, "released jump cuts upward speed");
    expect(out.attack.active, "jumping Sonic has spin attack");
    expect(!s3k_sonic_breaks_side_blocks(),
           "ordinary jump/fall does not grind side bricks");

    expect(nes_foreign_select(S3K_SONIC_CONTROLLER_ID),
           "reselect for ordinary roll");
    nes_foreign_set_ownership(FOREIGN_OWNERSHIP_FOREIGN);
    state = *nes_foreign_state();
    state.vx = 2.0;
    state.grounded = 1;
    *nes_foreign_state() = state;
    memset(&in, 0, sizeof(in));
    in.stick_y = -1.0f;
    out = tick(&state, in);
    resolve_flat();
    state = *nes_foreign_state();
    expect(out.state == S3K_SONIC_ROLL,
           "holding Down while moving enters ordinary roll");
    expect(out.attack.active &&
           !(out.attack.flags & FOREIGN_ATTACK_BREAK_BLOCKS),
           "ordinary roll attacks enemies but not bricks");
    expect(!s3k_sonic_breaks_side_blocks(),
           "ordinary roll cannot grind side bricks");

    expect(nes_foreign_select(S3K_SONIC_CONTROLLER_ID), "reselect for spindash");
    nes_foreign_set_ownership(FOREIGN_OWNERSHIP_FOREIGN);
    memset(&in, 0, sizeof(in));
    in.stick_y = -1.0f;
    in.special_pressed = 1;
    out = tick(&state, in);
    resolve_flat();
    state = *nes_foreign_state();
    expect(out.state == S3K_SONIC_SPINDASH, "Down+B enters spindash");
    expect(out.audio.count == 1 &&
           out.audio.events[0].cue == S3K_SONIC_AUDIO_SPINDASH,
           "spindash charge emits its rev cue");
    for (int i = 0; i < 3; ++i) {
        in.special_pressed = 1;
        out = tick(&state, in);
        resolve_flat();
        state = *nes_foreign_state();
    }
    memset(&in, 0, sizeof(in));
    out = tick(&state, in);
    expect(out.state == S3K_SONIC_ROLL, "releasing Down launches roll");
    expect(out.audio.count == 2 &&
           out.audio.events[0].cue == S3K_SONIC_AUDIO_DASH &&
           out.audio.events[1].cue == S3K_SONIC_AUDIO_ROLL,
           "spindash release emits dash and rolling cues");
    expect(fabs(out.vx) >= 7.5, "charged spindash has faster burst speed");
    expect(out.attack.active && (out.attack.flags & FOREIGN_ATTACK_BREAK_BLOCKS),
           "roll attacks enemies and bricks");
    expect(s3k_sonic_breaks_side_blocks(),
           "spindash roll can grind side bricks");
    expect(out.attack.width <= 20.0 && out.attack.height <= 20.0,
           "ball attack volume stays close to Small Mario size");

    expect(nes_foreign_select(S3K_SONIC_CONTROLLER_ID),
           "reselect for fire shield dash");
    nes_foreign_set_ownership(FOREIGN_OWNERSHIP_FOREIGN);
    s3k_sonic_set_fire_shield(1);
    expect(s3k_sonic_has_fire_shield(), "fire flower enables fire shield");

    memset(&in, 0, sizeof(in));
    in.jump_pressed = 1;
    in.jump_held = 1;
    out = tick(&state, in);
    expect(out.force_airborne, "fire shield jump leaves the ground normally");
    memset(&in, 0, sizeof(in));
    tick(&state, in);
    in.jump_pressed = 1;
    in.jump_held = 1;
    out = tick(&state, in);
    expect(out.state == S3K_SONIC_FIRE_DASH,
           "second airborne A press starts fire dash");
    expect(out.audio.count == 1 &&
           out.audio.events[0].cue == S3K_SONIC_AUDIO_FIRE_DASH,
           "fire dash emits the shield-attack cue");
    expect(fabs(out.vx) >= 9.0 && fabs(out.vy) < 0.001,
           "fire dash uses S3&K horizontal burst speed");
    expect(out.attack.active, "fire dash retains Sonic's ball attack");
    expect(s3k_sonic_breaks_side_blocks(),
           "fire dash can grind side bricks");

    for (int i = 0; i < 20; ++i) {
        memset(&in, 0, sizeof(in));
        if (i == 5) {
            in.jump_pressed = 1;
            in.jump_held = 1;
        }
        out = tick(&state, in);
    }
    expect(out.state != S3K_SONIC_FIRE_DASH,
           "additional airborne A press cannot restart the same fire dash");

    expect(nes_foreign_select(S3K_SONIC_CONTROLLER_ID),
           "reselect for unshielded double jump check");
    nes_foreign_set_ownership(FOREIGN_OWNERSHIP_FOREIGN);
    memset(&in, 0, sizeof(in));
    in.jump_pressed = 1;
    in.jump_held = 1;
    tick(&state, in);
    memset(&in, 0, sizeof(in));
    tick(&state, in);
    in.jump_pressed = 1;
    in.jump_held = 1;
    out = tick(&state, in);
    expect(out.state != S3K_SONIC_FIRE_DASH,
           "airborne A press does not dash without fire shield");

    if (failures) {
        fprintf(stderr, "%d Sonic controller assertion(s) failed\n", failures);
        return 1;
    }
    puts("Sonic controller harness passed");
    return 0;
}
