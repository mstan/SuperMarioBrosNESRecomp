/* Executable assertions for behavior_vectors.json's normative timing. */
#include "../../mods/smash64/ssb_ported/pikachu_locomotion.h"

#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static int failures;
#define CHECK(expr) do { if (!(expr)) { fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #expr); failures++; } } while (0)
#define CHECK_NEAR(actual, expected) CHECK(fabs((actual) - (expected)) < 0.0001)

static PikachuMotion step(PikachuFighter *f, PikachuInputRaw in)
{
    PikachuMotion m;
    PikachuCollision hit;
    memset(&hit, 0, sizeof(hit));
    hit.actual_dx = 0.0; hit.actual_dy = 0.0;
    pikachu_tick(f, &in, &m);
    hit.grounded = f->grounded;
    pikachu_resolve(f, &hit);
    return m;
}

static int solid_at_twelve(double x, double y, void *user)
{
    (void)y; (void)user;
    return x >= 12.0;
}

static void selection_vectors(void)
{
    PikachuFighter f; PikachuInputRaw in;
    memset(&in, 0, sizeof(in)); pikachu_reset(&f);
    in.attack_pressed = 1; step(&f, in); CHECK(f.state == PK_JAB);
    pikachu_reset(&f); in.stick_x = 80; step(&f, in); CHECK(f.state == PK_FTILT);
    pikachu_reset(&f); f.grounded = 0; in.stick_x = 0; step(&f, in); CHECK(f.state == PK_NAIR);
    pikachu_reset(&f); f.grounded = 0; in.stick_x = 80; step(&f, in); CHECK(f.state == PK_FAIR);
    pikachu_reset(&f); f.grounded = 0; in.stick_x = -80; step(&f, in); CHECK(f.state == PK_BAIR);
    pikachu_reset(&f); f.grounded = 0; in.stick_x = 0; in.stick_y = -80; step(&f, in); CHECK(f.state == PK_DAIR);
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.attack_pressed = 1; in.stick_y = -80; step(&f, in); CHECK(f.state == PK_DTILT);
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.attack_pressed = 1; in.stick_y = 80; step(&f, in); CHECK(f.state == PK_UTILT);
    pikachu_reset(&f); f.grounded = 0; memset(&in, 0, sizeof(in)); in.attack_pressed = 1; in.stick_y = 80; step(&f, in); CHECK(f.state == PK_UAIR);
    pikachu_reset(&f); f.state = PK_RUN; f.vel_x = PIKACHU_SOURCE_RUN_SPEED; memset(&in, 0, sizeof(in)); in.attack_pressed = 1; in.stick_x = 80; step(&f, in); CHECK(f.state == PK_DASH_ATTACK);
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.special_pressed = 1; in.stick_x = 80; step(&f, in); CHECK(f.state == PK_THUNDER_JOLT_GROUND);
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.special_pressed = 1; in.stick_y = 80; step(&f, in); CHECK(f.state == PK_QUICK_ATTACK_START);
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.special_pressed = 1; in.stick_y = -80; step(&f, in); CHECK(f.state == PK_THUNDER_START);
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.attack_pressed = in.special_pressed = 1; step(&f, in); CHECK(f.state == PK_THUNDER_JOLT_GROUND);
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.jump_pressed = 1; step(&f, in); CHECK(f.state == PK_JUMP_GROUND && f.jumps_used == 1);
    memset(&in, 0, sizeof(in)); step(&f, in); in.jump_pressed = 1; step(&f, in); CHECK(f.state == PK_JUMP_AERIAL && f.jumps_used == 2);
}

static void timing_and_projectile_vectors(void)
{
    PikachuFighter f; PikachuInputRaw in; PikachuMotion m; int i;
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.attack_pressed = 1;
    m = step(&f, in); CHECK(!m.attack.active);
    memset(&in, 0, sizeof(in));
    for (i = 1; i <= 6; ++i) { m = step(&f, in); if (i >= 2 && i < 6) CHECK(m.attack.active && m.attack.damage == 4 && m.attack.break_blocks); else CHECK(!m.attack.active); if (i == 2) CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LIGHT_S)); }
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.special_pressed = 1;
    m = step(&f, in);
    CHECK(m.events == PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_N));
    memset(&in, 0, sizeof(in));
    for (i = 1; i <= 21; ++i) { m = step(&f, in); if (i == 21) { CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_PROJECTILE_JOLT_SPAWN)); CHECK(m.projectile.kind == PIKACHU_PROJECTILE_JOLT); CHECK(!m.projectile.can_break_blocks); } }
    pikachu_reset(&f); memset(&in, 0, sizeof(in));
    f.grounded = 0; f.state = PK_AIR_FALL; in.special_pressed = 1;
    m = step(&f, in);
    CHECK(m.events ==
          (PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_N) |
           PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_5)));
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.special_pressed = 1; in.stick_y = -80;
    m = step(&f, in); CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_LW));
    memset(&in, 0, sizeof(in));
    for (i = 1; i <= 24; ++i) { m = step(&f, in); if (i < 24) CHECK((m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_THUNDER)) == 0); if (i == 24) { CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_PROJECTILE_THUNDER_SPAWN)); CHECK(!m.projectile.can_break_blocks); } }
    CHECK(f.state == PK_THUNDER_LOOP);
    CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_THUNDER));
    pikachu_note_thunder_self_contact(&f); m = step(&f, in);
    CHECK(f.state == PK_THUNDER_SELF_HIT);
    CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_PROJECTILE_THUNDER_SELF_HIT));
    CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_THUNDER_AMP));
    CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_DUST_HEAVY_DOUBLE));
    CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_QUAKE_MAG1));
    CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_THUNDER_HIT_COLOR));
    CHECK(m.attack.active && !m.attack.break_blocks);
}

static void thunder_phase_vectors(void)
{
    PikachuFighter f, restored;
    PikachuInputRaw in;
    PikachuMotion m;
    PikachuCollision hit;
    uint8_t blob[1 + sizeof(f)];
    int i, len;
    const int phases[] = {
        PK_THUNDER_START, PK_THUNDER_LOOP, PK_THUNDER_SELF_HIT,
        PK_THUNDER_END, PK_THUNDER_AIR_START, PK_THUNDER_AIR_LOOP,
        PK_THUNDER_AIR_SELF_HIT, PK_THUNDER_AIR_END
    };

    /* Destroy/no-contact feedback chooses End, never Hit. */
    pikachu_reset(&f);
    f.state = PK_THUNDER_LOOP;
    f.action_frame = 7u;
    f.projectile.kind = PIKACHU_PROJECTILE_THUNDER;
    f.projectile.active = 1;
    f.projectile.persistent_action_id = 9u;
    pikachu_note_projectile_finished(&f, 9u);
    memset(&in, 0, sizeof(in));
    m = step(&f, in);
    CHECK(f.state == PK_THUNDER_END);
    CHECK((m.events & PIKACHU_EVENT_BIT(
               PIKACHU_EVENT_PROJECTILE_THUNDER_SELF_HIT)) == 0);

    /* The authored loop flag is another no-contact End path. */
    pikachu_reset(&f);
    f.state = PK_THUNDER_LOOP;
    f.action_frame = PIKACHU_SOURCE_THUNDER_LOOP_FRAMES;
    f.projectile.kind = PIKACHU_PROJECTILE_THUNDER;
    f.projectile.active = 1;
    step(&f, in);
    CHECK(f.state == PK_THUNDER_END);

    /* Air Hit launches at +20, then applies source 0.5 gravity and native air
     * X clamp/friction. Landing preserves the Hit phase/frame. */
    pikachu_reset(&f);
    f.grounded = 0;
    f.state = PK_THUNDER_AIR_LOOP;
    f.action_frame = 3u;
    f.vel_x = 50.0;
    f.vel_y = -7.0;
    f.projectile.kind = PIKACHU_PROJECTILE_THUNDER;
    f.projectile.active = 1;
    pikachu_note_thunder_self_contact(&f);
    m = step(&f, in);
    CHECK(f.state == PK_THUNDER_AIR_SELF_HIT);
    CHECK_NEAR(f.vel_y, PIKACHU_SOURCE_THUNDER_HIT_VELOCITY_Y);
    CHECK(m.attack.active && m.attack.damage == 16);
    m = step(&f, in);
    CHECK_NEAR(f.vel_y,
               PIKACHU_SOURCE_THUNDER_HIT_VELOCITY_Y -
                   PIKACHU_SOURCE_THUNDER_HIT_GRAVITY);
    CHECK_NEAR(f.vel_x, PIKACHU_SOURCE_AIR_SPEED_MAX);
    memset(&hit, 0, sizeof(hit));
    hit.grounded = 1;
    pikachu_resolve(&f, &hit);
    CHECK(f.state == PK_THUNDER_SELF_HIT && f.vel_y == 0.0);

    /* Paired ground/air animations have identical live-blob end clocks, so
     * switching kinetics preserves the elapsed source frame unchanged. */
    pikachu_reset(&f);
    f.grounded = 0;
    f.state = PK_THUNDER_AIR_START;
    f.action_frame = 10u;
    memset(&hit, 0, sizeof(hit)); hit.grounded = 1;
    pikachu_resolve(&f, &hit);
    CHECK(f.state == PK_THUNDER_START && f.action_frame == 10u);
    memset(&hit, 0, sizeof(hit)); hit.grounded = 0;
    pikachu_resolve(&f, &hit);
    CHECK(f.state == PK_THUNDER_AIR_START && f.action_frame == 10u);

    pikachu_reset(&f);
    f.grounded = 0;
    f.state = PK_THUNDER_AIR_END;
    f.action_frame = PIKACHU_SOURCE_THUNDER_END_AIR_CLIP_FRAMES;
    step(&f, in);
    CHECK(f.state == PK_AIR_FALL);

    /* Every explicit phase survives v2 save/load with its local frame and
     * projectile lifetime identity intact. Appended ordinals do not migrate
     * or reinterpret the legacy ground phases. */
    for (i = 0; i < (int)(sizeof(phases) / sizeof(phases[0])); ++i) {
        pikachu_reset(&f);
        f.state = phases[i];
        f.grounded = phases[i] < PK_THUNDER_AIR_START;
        f.action_frame = 7u;
        f.projectile.kind = PIKACHU_PROJECTILE_THUNDER;
        f.projectile.active = 1;
        f.projectile.persistent_action_id = 123u;
        len = pikachu_serialize(&f, blob, (int)sizeof(blob));
        pikachu_reset(&restored);
        CHECK(len == (int)sizeof(blob));
        CHECK(pikachu_deserialize(&restored, blob, len));
        CHECK(restored.state == f.state);
        CHECK(restored.action_frame == 7u);
        CHECK(restored.projectile.active);
        CHECK(restored.projectile.persistent_action_id == 123u);
    }

    /* v2 represented airborne Thunder with a ground ordinal plus grounded=0.
     * v3 migrates all three legacy phases and leaves the destination unchanged
     * on malformed input. */
    {
        const int legacy_states[] = {
            PK_THUNDER_START, PK_THUNDER_LOOP, PK_THUNDER_SELF_HIT
        };
        const int air_states[] = {
            PK_THUNDER_AIR_START, PK_THUNDER_AIR_LOOP,
            PK_THUNDER_AIR_SELF_HIT
        };
        for (i = 0; i < 3; ++i) {
            pikachu_reset(&f);
            f.state = legacy_states[i];
            f.grounded = 0;
            f.action_frame = 9u;
            blob[0] = 2u;
            memcpy(blob + 1, &f, sizeof(f));
            pikachu_reset(&restored);
            CHECK(pikachu_deserialize(&restored, blob, (int)sizeof(blob)));
            CHECK(restored.state == air_states[i]);
            CHECK(restored.action_frame == 9u);
        }
        pikachu_reset(&restored);
        restored.state = PK_WALK;
        f = restored;
        blob[0] = 3u;
        memcpy(blob + 1, &f, sizeof(f));
        {
            int invalid = PK_STATE_COUNT;
            memcpy(blob + 1 + offsetof(PikachuFighter, state), &invalid,
                   sizeof(invalid));
        }
        CHECK(!pikachu_deserialize(&restored, blob, (int)sizeof(blob)));
        CHECK(restored.state == PK_WALK);

        /* v3 records must not smuggle a phase/kinetics contradiction past
         * restore; failure is transactional for both directions. */
        f = restored;
        f.state = PK_THUNDER_START;
        f.grounded = 0;
        blob[0] = 3u;
        memcpy(blob + 1, &f, sizeof(f));
        CHECK(!pikachu_deserialize(&restored, blob, (int)sizeof(blob)));
        CHECK(restored.state == PK_WALK);
        f.state = PK_THUNDER_AIR_LOOP;
        f.grounded = 1;
        memcpy(blob + 1, &f, sizeof(f));
        CHECK(!pikachu_deserialize(&restored, blob, (int)sizeof(blob)));
        CHECK(restored.state == PK_WALK);
    }
}

static void aerial_normal_motion_vectors(void)
{
    PikachuFighter f; PikachuInputRaw in; PikachuMotion m;
    pikachu_reset(&f);
    f.grounded = 0; f.vel_x = 17.0; f.vel_y = 12.0;
    memset(&in, 0, sizeof(in)); in.attack_pressed = 1;
    m = step(&f, in);
    CHECK(f.state == PK_NAIR);
    CHECK(m.requested_dx == 17.0 && m.requested_dy == 9.0);
    CHECK(f.vel_x == 17.0 && f.vel_y == 9.0);
    memset(&in, 0, sizeof(in));
    m = step(&f, in);
    CHECK(m.requested_dx == 17.0 && m.requested_dy == 6.0);
}

static void locomotion_vectors(void)
{
    PikachuFighter f; PikachuInputRaw in; PikachuMotion m; int i;
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.stick_x = 80;
    for (i = 0; i < (int)PIKACHU_SOURCE_DASH_TO_RUN_FRAMES; ++i) {
        const double expected = i >= 7
            ? PIKACHU_SOURCE_DASH_SPEED -
                  PIKACHU_SOURCE_DASH_DECEL * (double)(i - 6)
            : PIKACHU_SOURCE_DASH_SPEED;
        m = step(&f, in);
        CHECK(f.state == PK_DASH);
        CHECK(m.requested_dx == expected);
    }
    m = step(&f, in);
    CHECK(f.state == PK_RUN);
    CHECK(m.requested_dx == PIKACHU_SOURCE_RUN_SPEED);
    for (i = 0; i < 100; ++i) {
        m = step(&f, in);
        CHECK(f.state == PK_RUN);
        CHECK(m.requested_dx == PIKACHU_SOURCE_RUN_SPEED);
    }
    in.stick_x = -80;
    m = step(&f, in);
    CHECK(f.state == PK_TURN_RUN && f.lr == 1 &&
          m.requested_dx == PIKACHU_SOURCE_RUN_SPEED);
    for (i = 0; i < (int)PIKACHU_SOURCE_TURN_RUN_FLIP_FRAME - 1; ++i) {
        m = step(&f, in);
        CHECK(f.state == PK_TURN_RUN && f.lr == 1);
    }
    m = step(&f, in);
    CHECK(f.state == PK_TURN_RUN && f.lr == -1 &&
          m.requested_dx == -PIKACHU_SOURCE_RUN_SPEED);
    for (i = 0; i < 10 && f.state == PK_TURN_RUN; ++i) m = step(&f, in);
    CHECK(f.state == PK_RUN && f.lr == -1 &&
          m.requested_dx == -PIKACHU_SOURCE_RUN_SPEED);
    memset(&in, 0, sizeof(in));
    m = step(&f, in);
    CHECK(f.state == PK_RUN_BRAKE && m.requested_dx == -PIKACHU_SOURCE_RUN_SPEED);
    for (i = 0; i < 24 && f.state != PK_GROUND_WAIT; ++i) m = step(&f, in);
    CHECK(f.state == PK_GROUND_WAIT && m.requested_dx == 0.0);

    /* Analog tiers remain deterministic even though an NES pad normally
     * supplies only the fast tier. */
    pikachu_reset(&f); in.stick_x = 20; m = step(&f, in);
    CHECK(f.state == PK_WALK && m.requested_dx == 8.4);
    in.stick_x = 40; m = step(&f, in);
    CHECK(f.state == PK_WALK && m.requested_dx == 16.8);
}

static void jump_fall_vectors(void)
{
    PikachuFighter f; PikachuInputRaw in; PikachuMotion m; unsigned i;
    double ground_peak = 0.0, aerial_peak = 0.0;
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.jump_pressed = 1;
    in.stick_x = 80;
    m = step(&f, in); CHECK(f.state == PK_JUMP_GROUND);
    CHECK(f.vel_y == PIKACHU_SOURCE_JUMP_LAUNCH_VELOCITY - PIKACHU_SOURCE_GRAVITY);
    CHECK(f.vel_x == 80.0 * PIKACHU_SOURCE_JUMP_HORIZONTAL_MULTIPLIER);
    ground_peak += m.requested_dy;
    memset(&in, 0, sizeof(in));
    for (i = 1; i < PIKACHU_SOURCE_JUMP_GROUND_FRAMES; ++i) {
        m = step(&f, in); if (m.requested_dy > 0.0) ground_peak += m.requested_dy;
        CHECK(f.state == PK_JUMP_GROUND);
    }
    step(&f, in); CHECK(f.state == PK_AIR_FALL);

    pikachu_reset(&f); f.grounded = 0; f.state = PK_AIR_FALL;
    memset(&in, 0, sizeof(in)); in.jump_pressed = 1; in.stick_x = -80;
    m = step(&f, in); CHECK(f.state == PK_JUMP_AERIAL);
    CHECK(f.vel_y == PIKACHU_SOURCE_JUMP_LAUNCH_VELOCITY - PIKACHU_SOURCE_GRAVITY);
    CHECK(f.vel_x == -80.0 * PIKACHU_SOURCE_JUMP_HORIZONTAL_MULTIPLIER);
    aerial_peak += m.requested_dy;
    memset(&in, 0, sizeof(in));
    for (i = 1; i < PIKACHU_SOURCE_JUMP_AERIAL_FRAMES; ++i) {
        m = step(&f, in); if (m.requested_dy > 0.0) aerial_peak += m.requested_dy;
        CHECK(f.state == PK_JUMP_AERIAL);
    }
    step(&f, in); CHECK(f.state == PK_AIR_FALL);
    CHECK(ground_peak > 1200.0 && ground_peak == aerial_peak);
}

static void standard_state_timing_vectors(void)
{
    PikachuFighter f; PikachuInputRaw in; PikachuMotion m; int i;
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.attack_pressed = 1;
    in.stick_y = 80;
    for (i = 0; i < 16; ++i) { m = step(&f, in); CHECK(m.attack.active == (i >= 5 && i < 15)); if (m.attack.active) CHECK(m.attack.damage == 11); }
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.attack_pressed = 1;
    in.stick_y = -80;
    for (i = 0; i < 15; ++i) { m = step(&f, in); CHECK(m.attack.active == (i >= 6 && i < 14)); }
    pikachu_reset(&f); f.grounded = 0; f.vel_y = 20.0;
    memset(&in, 0, sizeof(in)); in.attack_pressed = 1; in.stick_y = 80;
    for (i = 0; i < 12; ++i) { m = step(&f, in); CHECK(m.attack.active == (i >= 3 && i < 11)); }
    pikachu_reset(&f); f.state = PK_RUN; f.vel_x = PIKACHU_SOURCE_RUN_SPEED;
    memset(&in, 0, sizeof(in)); in.attack_pressed = 1; in.stick_x = 80;
    for (i = 0; i < 24; ++i) { m = step(&f, in); CHECK(m.attack.active == (i >= 4 && i < 23)); if (m.attack.active) CHECK(m.attack.damage == 12); }
}

static void crouch_and_landing_vectors(void)
{
    PikachuFighter f; PikachuInputRaw in; PikachuMotion m; PikachuCollision hit;
    int i;
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.stick_y = -80;
    m = step(&f, in); CHECK(f.state == PK_CROUCH && m.requested_dx == 0.0);
    for (i = 0; i < 4; ++i) m = step(&f, in);
    CHECK(f.state == PK_CROUCH_WAIT && m.requested_dx == 0.0);
    memset(&in, 0, sizeof(in)); m = step(&f, in);
    CHECK(f.state == PK_CROUCH_END);

    pikachu_reset(&f); f.grounded = 0; f.state = PK_AIR_FALL; f.vel_y = -10.0;
    memset(&in, 0, sizeof(in)); pikachu_tick(&f, &in, &m);
    memset(&hit, 0, sizeof(hit)); hit.grounded = 1;
    pikachu_resolve(&f, &hit);
    CHECK(f.state == PK_LANDING && f.vel_x == 0.0 && f.vel_y == 0.0);
    for (i = 0; i < (int)PIKACHU_SOURCE_LANDING_FRAMES; ++i) {
        m = step(&f, in);
        CHECK(f.state == PK_LANDING);
    }
    m = step(&f, in);
    CHECK(f.state == PK_GROUND_WAIT && m.requested_dx == 0.0);
}

static void resolve_aerial_attack_landing(PikachuFighter *f, int state,
                                          unsigned frame, double vel_y)
{
    PikachuInputRaw in;
    PikachuMotion motion;
    PikachuCollision hit;
    pikachu_reset(f);
    f->grounded = 0;
    f->state = state;
    f->action_frame = frame;
    f->vel_x = 10.0;
    f->vel_y = vel_y;
    memset(&in, 0, sizeof(in));
    pikachu_tick(f, &in, &motion);
    memset(&hit, 0, sizeof(hit));
    hit.grounded = 1;
    pikachu_resolve(f, &hit);
}

static void aerial_landing_vectors(void)
{
    PikachuFighter f;
    PikachuInputRaw in;
    PikachuMotion m;
    uint8_t blob[1 + sizeof(f)];
    int i, len, state;
    const uint32_t common_events =
        PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_LANDING) |
        PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_DUST_HEAVY_DOUBLE);

    /* The new values are append-only after the v2 FallSpecial ordinal. */
    CHECK(PK_LANDING_AIR_NULL == PK_FALL_SPECIAL + 1);
    CHECK(PK_LANDING_AIR_F == PK_LANDING_AIR_NULL + 1);
    CHECK(PK_LANDING_AIR_D == PK_LANDING_AIR_F + 1);

    /* NAir and BAir have no landing-motion assets in Pikachu's motion table;
     * their flag1=50 windows therefore select 8f LandingAirX at 0.5 speed. */
    resolve_aerial_attack_landing(&f, PK_NAIR, 2, -30.0);
    CHECK(f.state == PK_LANDING);
    resolve_aerial_attack_landing(&f, PK_NAIR, 3, -30.0);
    CHECK(f.state == PK_LANDING_AIR_NULL);
    resolve_aerial_attack_landing(&f, PK_NAIR, 28, -30.0);
    CHECK(f.state == PK_LANDING_AIR_NULL);
    resolve_aerial_attack_landing(&f, PK_NAIR, 29, -30.0);
    CHECK(f.state == PK_LANDING);
    resolve_aerial_attack_landing(&f, PK_NAIR, 2, -16.9);
    CHECK(f.state == PK_GROUND_WAIT); /* collision velocity -19.9 > -20 */
    resolve_aerial_attack_landing(&f, PK_NAIR, 2, -17.0);
    CHECK(f.state == PK_LANDING); /* collision velocity -20 is not skipped */
    resolve_aerial_attack_landing(&f, PK_BAIR, 9, -30.0);
    CHECK(f.state == PK_LANDING);
    resolve_aerial_attack_landing(&f, PK_BAIR, 10, -30.0);
    CHECK(f.state == PK_LANDING_AIR_NULL);
    resolve_aerial_attack_landing(&f, PK_BAIR, 21, -30.0);
    CHECK(f.state == PK_LANDING_AIR_NULL);
    resolve_aerial_attack_landing(&f, PK_BAIR, 22, -30.0);
    CHECK(f.state == PK_LANDING);

    /* Fair and DAir own dedicated source landing motions. */
    resolve_aerial_attack_landing(&f, PK_FAIR, 6, -30.0);
    CHECK(f.state == PK_LANDING);
    resolve_aerial_attack_landing(&f, PK_FAIR, 7, -30.0);
    CHECK(f.state == PK_LANDING_AIR_F);
    len = pikachu_serialize(&f, blob, (int)sizeof(blob));
    pikachu_reset(&f);
    CHECK(len == (int)sizeof(blob) && pikachu_deserialize(&f, blob, len));
    CHECK(f.state == PK_LANDING_AIR_F && f.action_frame == 0u);
    memset(&in, 0, sizeof(in));
    m = step(&f, in);
    CHECK(m.events == common_events);
    CHECK(m.attack.active && m.attack.damage == 6 && m.attack.break_blocks);
    CHECK_NEAR(m.requested_dx, 8.0);
    m = step(&f, in);
    CHECK(m.attack.active && m.attack.damage == 6 && m.events == 0u);
    m = step(&f, in);
    CHECK(!m.attack.active);
    for (i = 3; i <= (int)PIKACHU_SOURCE_LANDING_AIR_F_FRAMES; ++i)
        m = step(&f, in);
    CHECK(f.state == PK_GROUND_WAIT);

    resolve_aerial_attack_landing(&f, PK_FAIR, 26, -30.0);
    CHECK(f.state == PK_LANDING_AIR_F);
    resolve_aerial_attack_landing(&f, PK_FAIR, 27, -30.0);
    CHECK(f.state == PK_LANDING);
    resolve_aerial_attack_landing(&f, PK_DAIR, 0, -30.0);
    CHECK(f.state == PK_LANDING_AIR_D);
    memset(&in, 0, sizeof(in));
    m = step(&f, in);
    CHECK(m.events ==
          (PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_DEAD_SLAM) |
           PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_DUST_HEAVY_DOUBLE) |
           PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_IMPACT_WAVE) |
           PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_QUAKE_MAG1)));
    CHECK(!m.attack.active);
    for (i = 1; i <= (int)PIKACHU_SOURCE_LANDING_AIR_D_FRAMES; ++i)
        m = step(&f, in);
    CHECK(f.state == PK_GROUND_WAIT);
    resolve_aerial_attack_landing(&f, PK_DAIR, 25, -30.0);
    CHECK(f.state == PK_LANDING_AIR_D);
    resolve_aerial_attack_landing(&f, PK_DAIR, 26, -30.0);
    CHECK(f.state == PK_LANDING);

    /* UAir has no flag1 command. With no active flag the common map callback
     * skips landing above -20 and uses ordinary landing at or below it. */
    resolve_aerial_attack_landing(&f, PK_UAIR, 3, 0.0);
    CHECK(f.state == PK_GROUND_WAIT);
    resolve_aerial_attack_landing(&f, PK_UAIR, 3, -20.0);
    CHECK(f.state == PK_LANDING);

    resolve_aerial_attack_landing(&f, PK_NAIR, 3, -30.0);
    memset(&in, 0, sizeof(in));
    m = step(&f, in);
    CHECK(m.events == common_events && !m.attack.active);
    for (i = 1; i <= (int)PIKACHU_SOURCE_LANDING_AIR_NULL_FRAMES; ++i)
        m = step(&f, in);
    CHECK(f.state == PK_GROUND_WAIT);

    /* All appended states survive the v3 struct blob; invalid
     * future ordinals are rejected by the same validation gate. */
    for (state = PK_LANDING_AIR_NULL; state <= PK_LANDING_AIR_D; ++state) {
        pikachu_reset(&f);
        f.state = state;
        f.action_frame = 7u;
        len = pikachu_serialize(&f, blob, (int)sizeof(blob));
        pikachu_reset(&f);
        CHECK(len == (int)sizeof(blob) && pikachu_deserialize(&f, blob, len));
        CHECK(f.state == state && f.action_frame == 7u);
    }
    {
        int invalid_state = PK_STATE_COUNT;
        memcpy(blob + 1 + offsetof(PikachuFighter, state), &invalid_state,
               sizeof(invalid_state));
        CHECK(!pikachu_deserialize(&f, blob, (int)sizeof(blob)));
    }
}

static void quick_attack_and_save_vectors(void)
{
    PikachuFighter f, saved; PikachuInputRaw in; PikachuMotion m; int i;
    pikachu_reset(&f); f.grounded = 0; memset(&in, 0, sizeof(in)); in.special_pressed = 1; in.stick_y = 80;
    m = step(&f, in);
    CHECK(m.events == PIKACHU_EVENT_BIT(
              PIKACHU_EVENT_FGM_QUICK_ATTACK_START));
    memset(&in, 0, sizeof(in)); in.stick_x = 80;
    for (i = 1; i <= 20; ++i) m = step(&f, in);
    CHECK(m.events == (PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_HI) | PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_1) | PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_SPARKLE)));
    CHECK(!m.attack.active && m.requested_dx > 0.0);
    CHECK(!f.grounded && f.vel_x == m.requested_dx && f.vel_y == m.requested_dy);
    saved = f;
    { uint8_t blob[1 + sizeof(f)]; int len = pikachu_serialize(&f, blob, sizeof(blob)); pikachu_reset(&f); CHECK(len > 0 && pikachu_deserialize(&f, blob, len)); }
    m = step(&f, in); CHECK((m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_HI)) == 0);
    /* The first solid sampled pixel stops the zip before a host resolve; the
     * probe is read-only, so this cannot mutate a tile. */
    { PikachuCollision hit; pikachu_sweep_zip(&f, &m, solid_at_twelve, NULL, &hit); CHECK(hit.hit_wall && hit.actual_dx == 0.0); pikachu_resolve(&f, &hit); CHECK(f.state == PK_QUICK_ATTACK_RECOVERY); }
    CHECK(saved.persistent_action_id == f.persistent_action_id);

    /* v1 records ended before End/FallSpecial bookkeeping. Non-Quick states
     * retain their prefix, but active Quick phases must reject rather than
     * invent an end clock or a second-zip decision. */
    {
        uint8_t v1[1 + offsetof(PikachuFighter, quick_end_frame)];
        saved.state = PK_AIR_FALL;
        saved.quick_end_frame = 0;
        saved.quick_fall_special = 0;
        v1[0] = 1;
        memcpy(v1 + 1, &saved, offsetof(PikachuFighter, quick_end_frame));
        pikachu_reset(&f);
        CHECK(pikachu_deserialize(&f, v1, (int)sizeof(v1)));
        CHECK(f.quick_end_frame == 0 && f.quick_fall_special == 0);
        saved.state = PK_QUICK_ATTACK_WINDOW;
        memcpy(v1 + 1, &saved, offsetof(PikachuFighter, quick_end_frame));
        CHECK(!pikachu_deserialize(&f, v1, (int)sizeof(v1)));
        saved.state = PK_QUICK_ATTACK_RECOVERY;
        memcpy(v1 + 1, &saved, offsetof(PikachuFighter, quick_end_frame));
        CHECK(!pikachu_deserialize(&f, v1, (int)sizeof(v1)));
    }
}

static void quick_attack_source_recovery_vector(void)
{
    PikachuFighter f; PikachuCollision hit; PikachuInputRaw in; int i;
    int fall_special_state = PK_FALL_SPECIAL;
    int special_landing_state = PK_FALL_SPECIAL_LANDING;
    /* Append-only controller enum: existing v2 FALL_SPECIAL_LANDING saves
     * retain their numeric value when aerial FALL_SPECIAL is introduced. */
    CHECK(fall_special_state == special_landing_state + 1);
    pikachu_reset(&f);
    f.grounded = 0;
    f.state = PK_QUICK_ATTACK_ZIP1;
    f.vel_x = 330.0;
    f.vel_y = 297.0;
    memset(&hit, 0, sizeof(hit));
    hit.hit_wall = 1;
    pikachu_resolve(&f, &hit);
    CHECK(f.state == PK_QUICK_ATTACK_RECOVERY);
    CHECK_NEAR(f.vel_x, 66.0);
    CHECK_NEAR(f.vel_y, 59.4);
    CHECK(f.quick_end_frame == 0 && !f.quick_fall_special);

    memset(&in, 0, sizeof(in));
    for (i = 0; i < (int)PIKACHU_SOURCE_QUICK_ATTACK_END_ANIMATION_FRAMES;
         ++i)
        step(&f, in);
    CHECK(f.quick_fall_special);
    CHECK(f.quick_end_frame == PIKACHU_SOURCE_QUICK_ATTACK_END_ANIMATION_FRAMES);
    CHECK(f.state == PK_FALL_SPECIAL);
    {
        uint8_t blob[1 + sizeof(f)]; int len;
        len = pikachu_serialize(&f, blob, sizeof(blob));
        pikachu_reset(&f);
        CHECK(len > 0 && pikachu_deserialize(&f, blob, len));
        CHECK(f.state == PK_FALL_SPECIAL && f.quick_fall_special);
    }
    in.stick_x = 80;
    for (i = 0; i < 400; ++i) step(&f, in);
    CHECK(f.vel_x <= PIKACHU_SOURCE_AIR_SPEED_MAX *
          PIKACHU_SOURCE_QUICK_ATTACK_FALL_SPECIAL_DRIFT + 0.0001);
    memset(&hit, 0, sizeof(hit)); hit.grounded = 1;
    pikachu_resolve(&f, &hit);
    CHECK(f.state == PK_FALL_SPECIAL_LANDING);
    memset(&in, 0, sizeof(in));
    for (i = 0;
         i <= (int)PIKACHU_SOURCE_QUICK_ATTACK_FALL_SPECIAL_LANDING_FRAMES;
         ++i)
        step(&f, in);
    CHECK(f.state == PK_GROUND_WAIT);
}

static int quick_attack_second_at_raw_angle_y(int y)
{
    PikachuFighter f; PikachuInputRaw in; int i;
    pikachu_reset(&f); f.grounded = 0;
    memset(&in, 0, sizeof(in)); in.special_pressed = 1; in.stick_y = 80;
    step(&f, in);
    memset(&in, 0, sizeof(in)); in.stick_x = 1000;
    for (i = 0; i < (int)PIKACHU_SOURCE_QUICK_ATTACK_AIM_FRAMES; ++i)
        step(&f, in);
    for (i = 1; i < (int)PIKACHU_SOURCE_QUICK_ATTACK_ZIP_FRAMES; ++i)
        step(&f, in);
    in.stick_y = y;
    for (i = 0; i <= (int)PIKACHU_SOURCE_QUICK_ATTACK_SECOND_AIM_FRAMES; ++i)
        step(&f, in);
    return f.state == PK_QUICK_ATTACK_ZIP2;
}

static void quick_attack_second_zip_motion_vector(void)
{
    PikachuFighter f; PikachuInputRaw in; PikachuMotion m; int i;
    pikachu_reset(&f); f.grounded = 0;
    memset(&in, 0, sizeof(in)); in.special_pressed = 1; in.stick_y = 80;
    step(&f, in);
    memset(&in, 0, sizeof(in)); in.stick_x = 80;
    for (i = 1; i <= 20; ++i) m = step(&f, in);
    CHECK(f.state == PK_QUICK_ATTACK_ZIP1); CHECK_NEAR(m.requested_dx, 330.0);
    memset(&in, 0, sizeof(in)); in.stick_y = 80;
    for (i = 21; i <= 34; ++i) m = step(&f, in);
    CHECK(f.state == PK_QUICK_ATTACK_ZIP2);
    CHECK(m.events ==
          (PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_HI) |
           PIKACHU_EVENT_BIT(PIKACHU_EVENT_FGM_ELECTRIC_1) |
           PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_SPARKLE)));
    CHECK(!f.grounded && f.vel_x == 0.0); CHECK_NEAR(f.vel_y, 297.0);
    CHECK(m.requested_dx == f.vel_x && m.requested_dy == f.vel_y);
    m = step(&f, in);
    CHECK(m.requested_dx == 0.0); CHECK_NEAR(m.requested_dy, 297.0);
}

static void quick_attack_source_velocity_and_two_point_vectors(void)
{
    PikachuFighter f; PikachuInputRaw in; PikachuMotion m; int i;

    /* A diagonal uses its normalized heading after the 80-unit magnitude cap,
     * not a per-component 330/330 square. */
    pikachu_reset(&f); f.grounded = 0;
    memset(&in, 0, sizeof(in)); in.special_pressed = 1; in.stick_y = 80;
    step(&f, in);
    memset(&in, 0, sizeof(in)); in.stick_x = 80; in.stick_y = 80;
    for (i = 1; i <= (int)PIKACHU_SOURCE_QUICK_ATTACK_AIM_FRAMES; ++i)
        m = step(&f, in);
    CHECK(f.state == PK_QUICK_ATTACK_ZIP1);
    CHECK_NEAR(m.requested_dx, 330.0 / sqrt(2.0));
    CHECK_NEAR(m.requested_dy, 330.0 / sqrt(2.0));

    /* Literal source threshold: atan(900/1000) is 41.987° and must fail;
     * atan(901/1000) is 42.013° and must pass. The old cos² approximation
     * accepted/rejected a different boundary. */
    CHECK(!quick_attack_second_at_raw_angle_y(900));
    CHECK(quick_attack_second_at_raw_angle_y(901));

    /* The source's low-stick fallback is UP, not logical facing. Holding
     * Right only for the second decision therefore forms a valid 90-degree
     * upward-then-right two-point Quick Attack. */
    pikachu_reset(&f); f.grounded = 0; f.lr = -1;
    memset(&in, 0, sizeof(in)); in.special_pressed = 1; in.stick_y = 80;
    step(&f, in);
    memset(&in, 0, sizeof(in));
    for (i = 1; i <= (int)PIKACHU_SOURCE_QUICK_ATTACK_AIM_FRAMES; ++i)
        m = step(&f, in);
    CHECK(f.state == PK_QUICK_ATTACK_ZIP1);
    CHECK_NEAR(m.requested_dx, 0.0); CHECK_NEAR(m.requested_dy, 330.0);
    for (i = 1; i < (int)PIKACHU_SOURCE_QUICK_ATTACK_ZIP_FRAMES; ++i)
        m = step(&f, in);
    memset(&in, 0, sizeof(in)); in.stick_x = 80;
    for (i = 0; i <= (int)PIKACHU_SOURCE_QUICK_ATTACK_SECOND_AIM_FRAMES; ++i)
        m = step(&f, in);
    CHECK(f.state == PK_QUICK_ATTACK_ZIP2);
    CHECK_NEAR(m.requested_dx, 297.0); CHECK_NEAR(m.requested_dy, 0.0);

    /* The five-tick first point finishes before the nine-tick direction
     * window. A held perpendicular aim deterministically produces one 0.9x
     * second point, and cannot queue a third. */
    pikachu_reset(&f); f.grounded = 0;
    memset(&in, 0, sizeof(in)); in.special_pressed = 1; in.stick_y = 80;
    step(&f, in);
    memset(&in, 0, sizeof(in)); in.stick_x = 80;
    for (i = 1; i <= (int)PIKACHU_SOURCE_QUICK_ATTACK_AIM_FRAMES; ++i)
        m = step(&f, in);
    CHECK_NEAR(m.requested_dx, 330.0);
    for (i = 1; i <= (int)PIKACHU_SOURCE_QUICK_ATTACK_ZIP_FRAMES - 1; ++i)
        m = step(&f, in);
    memset(&in, 0, sizeof(in)); in.stick_y = 80;
    /* The end-script tick begins the 9-frame window; the following decision
     * tick is its first possible second-zip entry. */
    for (i = 0; i <= (int)PIKACHU_SOURCE_QUICK_ATTACK_SECOND_AIM_FRAMES; ++i)
        m = step(&f, in);
    CHECK(f.state == PK_QUICK_ATTACK_ZIP2);
    CHECK_NEAR(m.requested_dy, 297.0);
    for (i = 0; i < (int)PIKACHU_SOURCE_QUICK_ATTACK_ZIP_FRAMES + 2; ++i)
        m = step(&f, in);
    CHECK(f.state == PK_QUICK_ATTACK_RECOVERY);
    CHECK(!m.attack.active);
}

static void source_action_end_clock_vectors(void)
{
    PikachuFighter f;
    PikachuInputRaw in;
    PikachuMotion m;
#define CHECK_ACTION_END(action_state, end_frame, is_ground, next_state) do { \
    pikachu_reset(&f); \
    f.state = (action_state); \
    f.grounded = (is_ground); \
    f.action_frame = (end_frame) - 1u; \
    memset(&in, 0, sizeof(in)); \
    m = step(&f, in); \
    CHECK(f.state == (action_state)); \
    m = step(&f, in); \
    CHECK(f.state == (next_state)); \
    (void)m; \
} while (0)

    CHECK_ACTION_END(PK_JAB, PIKACHU_SOURCE_JAB_FRAMES, 1,
                     PK_GROUND_WAIT);
    CHECK_ACTION_END(PK_FTILT, PIKACHU_SOURCE_FTILT_FRAMES, 1,
                     PK_GROUND_WAIT);
    CHECK_ACTION_END(PK_NAIR, PIKACHU_SOURCE_NAIR_FRAMES, 0, PK_AIR_FALL);
    CHECK_ACTION_END(PK_FAIR, PIKACHU_SOURCE_FAIR_FRAMES, 0, PK_AIR_FALL);
    CHECK_ACTION_END(PK_BAIR, PIKACHU_SOURCE_BAIR_FRAMES, 0, PK_AIR_FALL);
    CHECK_ACTION_END(PK_DAIR, PIKACHU_SOURCE_DAIR_FRAMES, 0, PK_AIR_FALL);
    CHECK_ACTION_END(PK_DASH_ATTACK, PIKACHU_SOURCE_DASH_ATTACK_FRAMES, 1,
                     PK_GROUND_WAIT);
    CHECK_ACTION_END(PK_UTILT, PIKACHU_SOURCE_UTILT_FRAMES, 1,
                     PK_GROUND_WAIT);
    CHECK_ACTION_END(PK_DTILT, PIKACHU_SOURCE_DTILT_FRAMES, 1,
                     PK_GROUND_WAIT);
    CHECK_ACTION_END(PK_UAIR, PIKACHU_SOURCE_UAIR_FRAMES, 0, PK_AIR_FALL);
    CHECK_ACTION_END(PK_THUNDER_JOLT_GROUND,
                     PIKACHU_SOURCE_THUNDER_JOLT_FRAMES, 1,
                     PK_GROUND_WAIT);
    CHECK_ACTION_END(PK_THUNDER_JOLT_AIR,
                     PIKACHU_SOURCE_THUNDER_JOLT_FRAMES, 0, PK_AIR_FALL);
#undef CHECK_ACTION_END
}

int main(void)
{
    selection_vectors(); timing_and_projectile_vectors(); aerial_normal_motion_vectors();
    thunder_phase_vectors();
    locomotion_vectors(); jump_fall_vectors(); standard_state_timing_vectors();
    crouch_and_landing_vectors(); aerial_landing_vectors();
    quick_attack_and_save_vectors(); quick_attack_source_recovery_vector();
    quick_attack_second_zip_motion_vector();
    quick_attack_source_velocity_and_two_point_vectors();
    source_action_end_clock_vectors();
    if (failures) { fprintf(stderr, "pikachu_harness: %d failures\n", failures); return 1; }
    puts("pikachu_harness: PASS behavior_vectors.json"); return 0;
}
