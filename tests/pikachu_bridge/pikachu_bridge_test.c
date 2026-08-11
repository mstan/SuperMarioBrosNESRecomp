#include "mods/smash64/characters/pikachu.h"
#include "foreign_controller.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

static const ForeignController *registered;
static ForeignControllerPrivateStateGet private_get;
static ForeignControllerPrivateStateSet private_set;
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
    private_get = get;
    private_set = set;
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
    registered->tick(&state, &input, &move);
    CHECK(state.state == PK_THUNDER_JOLT_GROUND);
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

    /* Quick's source Start/zip motions are static. A collision that enters
     * End/Recovery restarts its public motion at local frame zero even though
     * the private decision clock remains continuous and serialized. */
    registered->reset(&state);
    state.grounded = 0;
    memset(&input, 0, sizeof(input));
    input.special_pressed = 1;
    input.stick_y = 1.0f;
    memset(&move, 0, sizeof(move));
    registered->tick(&state, &input, &move);
    CHECK(state.state == PK_QUICK_ATTACK_START && state.state_frame == 0u);
    memset(&input, 0, sizeof(input));
    for (tick = 1; tick <= (int)PIKACHU_SOURCE_QUICK_ATTACK_AIM_FRAMES;
         ++tick) {
        memset(&move, 0, sizeof(move));
        registered->tick(&state, &input, &move);
    }
    CHECK(state.state == PK_QUICK_ATTACK_ZIP1 && state.state_frame == 0u);
    {
        ForeignCollisionResult hit;
        memset(&hit, 0, sizeof(hit));
        hit.hit_ceiling = 1;
        hit.grounded = 0;
        registered->resolve(&state, &hit);
    }
    CHECK(state.state == PK_QUICK_ATTACK_WINDOW);
    CHECK(state.state_frame == 0u);

    /* Ground Quick uses the same phase-local public clock without being
     * mislabeled as the air graph. */
    registered->reset(&state);
    memset(&input, 0, sizeof(input)); input.special_pressed = 1;
    input.stick_y = 1.0f; memset(&move, 0, sizeof(move));
    registered->tick(&state, &input, &move);
    CHECK(state.state == PK_QUICK_ATTACK_GROUND_START);
    CHECK(state.state_frame == 0u && state.grounded);

    /* SpecialHi Start's source motion is -1: freeze the exact public entry
     * pose rather than substituting an End pose. Exercise three distinct
     * locomotion clocks and replay the captured Wait pose from private save. */
    {
        uint8_t private_blob[512];
        ForeignState saved_state;
        int entry_state;
        unsigned entry_frame;
        int private_len;
        registered->reset(&state);
        state.state = PK_GROUND_WAIT; state.state_frame = 37u;
        memset(&input, 0, sizeof(input)); input.special_pressed = 1;
        input.stick_y = 1.0f; memset(&move, 0, sizeof(move));
        registered->tick(&state, &input, &move);
        CHECK(smash64_pikachu_quick_entry_pose(
            state.state, &entry_state, &entry_frame));
        CHECK(entry_state == PK_GROUND_WAIT && entry_frame == 37u);
        saved_state = state;
        private_len = private_get(&state, private_blob,
                                  (int)sizeof(private_blob));
        CHECK(private_len > 0);
        memset(&input, 0, sizeof(input)); memset(&move, 0, sizeof(move));
        registered->tick(&state, &input, &move);
        state = saved_state;
        CHECK(private_set(&state, private_blob, private_len));
        CHECK(smash64_pikachu_quick_entry_pose(
            state.state, &entry_state, &entry_frame));
        CHECK(entry_state == PK_GROUND_WAIT && entry_frame == 37u);

        registered->reset(&state);
        state.state = PK_RUN; state.state_frame = 23u;
        memset(&input, 0, sizeof(input)); input.special_pressed = 1;
        input.stick_y = 1.0f; memset(&move, 0, sizeof(move));
        registered->tick(&state, &input, &move);
        CHECK(smash64_pikachu_quick_entry_pose(
            state.state, &entry_state, &entry_frame));
        CHECK(entry_state == PK_RUN && entry_frame == 23u);

        registered->reset(&state);
        state.state = PK_AIR_FALL; state.state_frame = 11u;
        state.grounded = 0;
        memset(&input, 0, sizeof(input)); input.special_pressed = 1;
        input.stick_y = 1.0f; memset(&move, 0, sizeof(move));
        registered->tick(&state, &input, &move);
        CHECK(smash64_pikachu_quick_entry_pose(
            state.state, &entry_state, &entry_frame));
        CHECK(entry_state == PK_AIR_FALL && entry_frame == 11u);
    }

    /* The bridge must publish the host's down edge into the private buffered
     * fast-fall input and mirror the resulting latch back to ForeignState. */
    registered->reset(&state);
    state.grounded = 0;
    memset(&input, 0, sizeof(input)); input.stick_y = -1.0f;
    input.down_pressed = 1; memset(&move, 0, sizeof(move));
    registered->tick(&state, &input, &move);
    CHECK(!state.fast_fall);
    input.down_pressed = 0; memset(&move, 0, sizeof(move));
    registered->tick(&state, &input, &move);
    CHECK(state.fast_fall && move.vy == -PIKACHU_SOURCE_FAST_FALL_VELOCITY);

    /* FallAerial is append-only and therefore cannot rely on an ordinal
     * `state < PK_JAB` shortcut for presentation time. Its generic clock and
     * private controller state resume together across save/load. */
    {
        ForeignState saved_state;
        uint8_t private_blob[512];
        int private_len;
        registered->reset(&state);
        state.grounded = 0;
        memset(&input, 0, sizeof(input)); input.jump_pressed = 1;
        input.stick_x = -1.0f; memset(&move, 0, sizeof(move));
        registered->tick(&state, &input, &move);
        for (tick = 0; tick < (int)PIKACHU_SOURCE_JUMP_AERIAL_FRAMES + 2 &&
                        state.state != PK_AIR_FALL_AERIAL; ++tick) {
            memset(&input, 0, sizeof(input)); memset(&move, 0, sizeof(move));
            registered->tick(&state, &input, &move);
        }
        CHECK(state.state == PK_AIR_FALL_AERIAL && state.state_frame == 0u);
        memset(&move, 0, sizeof(move)); registered->tick(&state, &input, &move);
        CHECK(state.state_frame == 1u);
        memset(&move, 0, sizeof(move)); registered->tick(&state, &input, &move);
        CHECK(state.state_frame == 2u);
        saved_state = state;
        private_len = private_get(&state, private_blob,
                                  (int)sizeof(private_blob));
        registered->reset(&state);
        state = saved_state;
        CHECK(private_len > 0 &&
              private_set(&state, private_blob, private_len));
        memset(&move, 0, sizeof(move)); registered->tick(&state, &input, &move);
        CHECK(state.state == PK_AIR_FALL_AERIAL && state.state_frame == 3u);
    }

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

    /* Production publishes host floor contact before tick, then supplies the
     * collision to resolve. The bridge must retain the private airborne edge
     * across that tick so resolve—not ground locomotion—chooses the landing
     * status. Exercise Jump, Fall, and authored AttackAir landing separately. */
    registered->reset(&state);
    memset(&input, 0, sizeof(input)); input.jump_pressed = 1;
    memset(&move, 0, sizeof(move)); registered->tick(&state, &input, &move);
    for (tick = 0; tick < 8 && state.state == PK_KNEEBEND; ++tick) {
        memset(&input, 0, sizeof(input)); memset(&move, 0, sizeof(move));
        registered->tick(&state, &input, &move);
    }
    CHECK(state.state == PK_JUMP_GROUND || state.state == PK_JUMP_GROUND_B);
    state.grounded = 1; /* host's first floor-contact publication */
    memset(&input, 0, sizeof(input)); memset(&move, 0, sizeof(move));
    registered->tick(&state, &input, &move);
    CHECK(state.state == PK_JUMP_GROUND || state.state == PK_JUMP_GROUND_B);
    {
        ForeignCollisionResult floor;
        memset(&floor, 0, sizeof(floor)); floor.grounded = 1;
        floor.hit_floor = 1;
        registered->resolve(&state, &floor);
    }
    CHECK(state.state == PK_LANDING && state.state_frame == 0u);

    registered->reset(&state);
    state.grounded = 0;
    memset(&input, 0, sizeof(input)); memset(&move, 0, sizeof(move));
    registered->tick(&state, &input, &move);
    CHECK(state.state == PK_AIR_FALL);
    state.grounded = 1;
    memset(&input, 0, sizeof(input)); memset(&move, 0, sizeof(move));
    registered->tick(&state, &input, &move);
    CHECK(state.state == PK_AIR_FALL); /* no unsolicited ground action */
    {
        ForeignCollisionResult floor;
        memset(&floor, 0, sizeof(floor)); floor.grounded = 1;
        floor.hit_floor = 1;
        registered->resolve(&state, &floor);
    }
    CHECK(state.state == PK_LANDING && state.state_frame == 0u);

    registered->reset(&state);
    state.grounded = 0;
    memset(&input, 0, sizeof(input)); input.attack_pressed = 1;
    memset(&move, 0, sizeof(move)); registered->tick(&state, &input, &move);
    CHECK(state.state == PK_NAIR);
    for (tick = 0; tick < 3; ++tick) {
        memset(&input, 0, sizeof(input)); memset(&move, 0, sizeof(move));
        registered->tick(&state, &input, &move);
    }
    state.grounded = 1;
    memset(&input, 0, sizeof(input)); memset(&move, 0, sizeof(move));
    registered->tick(&state, &input, &move);
    CHECK(state.state == PK_NAIR); /* retain authored aerial before resolve */
    {
        ForeignCollisionResult floor;
        memset(&floor, 0, sizeof(floor)); floor.grounded = 1;
        floor.hit_floor = 1;
        registered->resolve(&state, &floor);
    }
    CHECK(state.state == PK_LANDING_AIR_NULL && state.state_frame == 0u);

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
