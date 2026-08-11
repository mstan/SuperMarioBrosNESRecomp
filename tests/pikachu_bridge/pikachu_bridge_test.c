#include "mods/smash64/characters/pikachu.h"
#include "foreign_controller.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

static const ForeignController *registered;
static int failures;

#define CHECK(expr) do { if (!(expr)) { \
    fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #expr); \
    ++failures; \
} } while (0)
#define CHECK_NEAR(a, b) CHECK(fabs((double)(a) - (double)(b)) < 0.0001)

int nes_foreign_register(const ForeignController *controller)
{
    registered = controller;
    return controller != NULL;
}

int nes_foreign_register_private_state(const char *controller_id,
                                       ForeignControllerPrivateStateGet get,
                                       ForeignControllerPrivateStateSet set)
{
    return controller_id != NULL && get != NULL && set != NULL;
}

int main(void)
{
    ForeignState state;
    ForeignInput input;
    ForeignMoveResult move;
    const ForeignActionEvent *jolt = NULL;
    int tick;
    int thunder_audio_count = 0;
    uint32_t thunder_instance_id = 0;

    CHECK(smash64_pikachu_register());
    CHECK(registered != NULL);
    memset(&state, 0, sizeof(state));
    registered->reset(&state);

    /* Production calls resolve after every tick. A no-op same-ground resolve
     * must not overwrite the pre-increment presentation frame published by
     * tick with the private controller's next frame. */
    memset(&input, 0, sizeof(input));
    memset(&move, 0, sizeof(move));
    input.special_pressed = 1;
    input.stick_y = 1.0f;
    registered->tick(&state, &input, &move);
    CHECK(state.state == PK_QUICK_ATTACK_START);
    CHECK(state.state_frame == 0u);
    {
        ForeignCollisionResult hit;
        memset(&hit, 0, sizeof(hit));
        hit.grounded = 1;
        registered->resolve(&state, &hit);
    }
    CHECK(state.state_frame == 0u);
    memset(&input, 0, sizeof(input));
    memset(&move, 0, sizeof(move));
    registered->tick(&state, &input, &move);
    CHECK(state.state_frame == 1u);
    {
        ForeignCollisionResult hit;
        memset(&hit, 0, sizeof(hit));
        hit.grounded = 1;
        registered->resolve(&state, &hit);
    }
    CHECK(state.state_frame == 1u);

    registered->reset(&state);

    for (tick = 0; tick < 40 && !jolt; ++tick) {
        memset(&input, 0, sizeof(input));
        memset(&move, 0, sizeof(move));
        input.special_pressed = tick == 0;
        registered->tick(&state, &input, &move);
        if (move.actions.count != 0)
            jolt = &move.actions.events[0];
    }

    CHECK(jolt != NULL);
    if (jolt) {
        CHECK(jolt->kind == PIKACHU_PROJECTILE_JOLT);
        CHECK(jolt->command == FOREIGN_ACTION_SPAWN);
        CHECK((jolt->flags & FOREIGN_ACTION_HOSTILE) != 0);
        CHECK((jolt->flags & FOREIGN_ACTION_FOLLOW_SURFACES) != 0);
        CHECK((jolt->flags & FOREIGN_ACTION_SURFACE_SPEED) != 0);
        CHECK(jolt->source_joint == 11);
        CHECK(jolt->offset_x == 0.0 && jolt->offset_y == 0.0);
        CHECK_NEAR(jolt->velocity_x, 28.284271);
        CHECK_NEAR(jolt->velocity_y, -28.284271);
        CHECK_NEAR(jolt->surface_velocity, 55.0);
        CHECK(jolt->lifetime_ticks == 100);
        CHECK(jolt->damage == 10);
    }

    /* Source sound timing is Start voice f0, bolt creation f24, then the
     * Thunder FGM exactly once as Loop begins. Weapon spawn is not the FGM. */
    registered->reset(&state);
    for (tick = 0;
         tick <= (int)PIKACHU_SOURCE_THUNDER_START_GROUND_CLIP_FRAMES;
         ++tick) {
        uint32_t audio_index;
        memset(&input, 0, sizeof(input));
        memset(&move, 0, sizeof(move));
        input.special_pressed = tick == 0;
        input.stick_y = -1.0f;
        registered->tick(&state, &input, &move);
        for (audio_index = 0; audio_index < move.audio.count; ++audio_index) {
            if (move.audio.events[audio_index].cue == PIKACHU_AUDIO_THUNDER) {
                ++thunder_audio_count;
                CHECK(tick ==
                      (int)PIKACHU_SOURCE_THUNDER_START_GROUND_CLIP_FRAMES);
            }
        }
        if (tick < (int)PIKACHU_SOURCE_THUNDER_SPAWN_FRAME)
            CHECK(thunder_audio_count == 0);
        if (move.actions.count != 0) {
            CHECK(tick == (int)PIKACHU_SOURCE_THUNDER_SPAWN_FRAME);
            CHECK(move.actions.events[0].kind == PIKACHU_PROJECTILE_THUNDER);
            CHECK((move.actions.events[0].flags &
                   FOREIGN_ACTION_PERSIST_AFTER_TARGET) != 0);
            thunder_instance_id = move.actions.events[0].instance_id;
        }
        {
            ForeignCollisionResult hit;
            memset(&hit, 0, sizeof(hit));
            hit.grounded = 1;
            registered->resolve(&state, &hit);
        }
        if (tick == (int)PIKACHU_SOURCE_THUNDER_SPAWN_FRAME) {
            CHECK(state.state == PK_THUNDER_LOOP);
            CHECK(state.state_frame == 0u);
        }
    }
    CHECK(state.state == PK_THUNDER_LOOP);
    CHECK(thunder_audio_count == 1);
    CHECK(thunder_instance_id != 0);
    {
        ForeignCollisionResult hit;
        memset(&hit, 0, sizeof(hit));
        hit.grounded = 1;
        hit.action_feedback.count = 1;
        hit.action_feedback.events[0].instance_id = thunder_instance_id;
        hit.action_feedback.events[0].flags = FOREIGN_ACTION_HIT_TARGET;
        registered->resolve(&state, &hit);
    }
    memset(&input, 0, sizeof(input));
    memset(&move, 0, sizeof(move));
    registered->tick(&state, &input, &move);
    CHECK(state.state == PK_THUNDER_LOOP);
    {
        ForeignCollisionResult hit;
        memset(&hit, 0, sizeof(hit));
        hit.grounded = 1;
        hit.action_feedback.count = 1;
        hit.action_feedback.events[0].instance_id = thunder_instance_id;
        hit.action_feedback.events[0].flags = FOREIGN_ACTION_HIT_SELF;
        registered->resolve(&state, &hit);
    }
    memset(&input, 0, sizeof(input));
    memset(&move, 0, sizeof(move));
    registered->tick(&state, &input, &move);
    CHECK(state.state == PK_THUNDER_SELF_HIT);
    CHECK(state.state_frame == 0u);
    CHECK(move.attack.active && move.attack.damage == 16);
    {
        ForeignCollisionResult hit;
        memset(&hit, 0, sizeof(hit));
        hit.grounded = 1;
        registered->resolve(&state, &hit);
    }
    CHECK(state.state_frame == 0u);

    /* A syntactically valid host-rejected Thunder spawn reports EXPIRED.
     * Feeding that public rejection back while Loop begins must choose End on
     * the next controller tick rather than waiting out the 60-frame loop. */
    registered->reset(&state);
    thunder_instance_id = 0;
    for (tick = 0;
         tick <= (int)PIKACHU_SOURCE_THUNDER_START_GROUND_CLIP_FRAMES;
         ++tick) {
        ForeignCollisionResult hit;
        memset(&input, 0, sizeof(input));
        memset(&move, 0, sizeof(move));
        input.special_pressed = tick == 0;
        input.stick_y = -1.0f;
        registered->tick(&state, &input, &move);
        memset(&hit, 0, sizeof(hit));
        hit.grounded = 1;
        if (move.actions.count != 0) {
            thunder_instance_id = move.actions.events[0].instance_id;
            hit.action_feedback.count = 1;
            hit.action_feedback.events[0].instance_id = thunder_instance_id;
            hit.action_feedback.events[0].flags = FOREIGN_ACTION_EXPIRED;
        }
        registered->resolve(&state, &hit);
    }
    CHECK(thunder_instance_id != 0);
    CHECK(state.state == PK_THUNDER_LOOP);
    memset(&input, 0, sizeof(input));
    memset(&move, 0, sizeof(move));
    registered->tick(&state, &input, &move);
    CHECK(state.state == PK_THUNDER_END);
    CHECK(state.state_frame == 0u);

    /* Resolve publishes a landing status and its reset phase frame together. */
    registered->reset(&state);
    state.grounded = 0;
    for (tick = 0; tick < 4; ++tick) {
        memset(&input, 0, sizeof(input));
        memset(&move, 0, sizeof(move));
        input.attack_pressed = tick == 0;
        registered->tick(&state, &input, &move);
    }
    {
        ForeignCollisionResult hit;
        memset(&hit, 0, sizeof(hit));
        hit.grounded = 1;
        registered->resolve(&state, &hit);
        CHECK(state.state == PK_LANDING_AIR_NULL);
        CHECK(state.state_frame == 0u);
    }

    /* Thunder Air->Ground preserves source remaining animation time and the
     * bridge exposes the converted frame on the same resolve callback. */
    registered->reset(&state);
    state.grounded = 0;
    for (tick = 0; tick < 10; ++tick) {
        memset(&input, 0, sizeof(input));
        memset(&move, 0, sizeof(move));
        input.special_pressed = tick == 0;
        input.stick_y = -1.0f;
        registered->tick(&state, &input, &move);
    }
    {
        ForeignCollisionResult hit;
        memset(&hit, 0, sizeof(hit));
        hit.grounded = 1;
        registered->resolve(&state, &hit);
        CHECK(state.state == PK_THUNDER_START);
        /* Ten ticks publish source frames 0..9. The paired map switch keeps
         * public frame 9 even though the private next-tick clock is 10. */
        CHECK(state.state_frame == 9u);
    }

    if (failures) return 1;
    puts("pikachu_bridge_test: PASS");
    return 0;
}
