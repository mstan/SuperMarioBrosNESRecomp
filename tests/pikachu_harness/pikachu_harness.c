/* Executable assertions for behavior_vectors.json's normative timing. */
#include "../../mods/smash64/ssb_ported/pikachu_locomotion.h"

#include <stdio.h>
#include <string.h>

static int failures;
#define CHECK(expr) do { if (!(expr)) { fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #expr); failures++; } } while (0)

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
    m = step(&f, in); CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_N));
    memset(&in, 0, sizeof(in));
    for (i = 1; i <= 21; ++i) { m = step(&f, in); if (i == 21) { CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_PROJECTILE_JOLT_SPAWN)); CHECK(m.projectile.kind == PIKACHU_PROJECTILE_JOLT); CHECK(!m.projectile.can_break_blocks); } }
    pikachu_reset(&f); memset(&in, 0, sizeof(in)); in.special_pressed = 1; in.stick_y = -80;
    m = step(&f, in); CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_VOICE_SPECIAL_LW));
    memset(&in, 0, sizeof(in));
    for (i = 1; i <= 24; ++i) { m = step(&f, in); if (i == 24) { CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_PROJECTILE_THUNDER_SPAWN)); CHECK(!m.projectile.can_break_blocks); } }
    pikachu_note_thunder_self_contact(&f); m = step(&f, in);
    CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_PROJECTILE_THUNDER_SELF_HIT));
    CHECK(m.events & PIKACHU_EVENT_BIT(PIKACHU_EVENT_EFFECT_THUNDER_AMP));
    CHECK(m.attack.active && !m.attack.break_blocks);
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

static void quick_attack_and_save_vectors(void)
{
    PikachuFighter f, saved; PikachuInputRaw in; PikachuMotion m; int i;
    pikachu_reset(&f); f.grounded = 0; memset(&in, 0, sizeof(in)); in.special_pressed = 1; in.stick_y = 80; step(&f, in);
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
}

static void quick_attack_second_zip_motion_vector(void)
{
    PikachuFighter f; PikachuInputRaw in; PikachuMotion m; int i;
    pikachu_reset(&f); f.grounded = 0;
    memset(&in, 0, sizeof(in)); in.special_pressed = 1; in.stick_y = 80;
    step(&f, in);
    memset(&in, 0, sizeof(in)); in.stick_x = 80;
    for (i = 1; i <= 20; ++i) m = step(&f, in);
    CHECK(f.state == PK_QUICK_ATTACK_ZIP1 && m.requested_dx == 60.0);
    memset(&in, 0, sizeof(in)); in.stick_y = 80;
    for (i = 21; i <= 34; ++i) m = step(&f, in);
    CHECK(f.state == PK_QUICK_ATTACK_ZIP2);
    CHECK(!f.grounded && f.vel_x == 0.0 && f.vel_y == 60.0);
    CHECK(m.requested_dx == f.vel_x && m.requested_dy == f.vel_y);
    m = step(&f, in);
    CHECK(m.requested_dx == 0.0 && m.requested_dy == 60.0);
}

int main(void)
{
    selection_vectors(); timing_and_projectile_vectors(); aerial_normal_motion_vectors();
    quick_attack_and_save_vectors(); quick_attack_second_zip_motion_vector();
    if (failures) { fprintf(stderr, "pikachu_harness: %d failures\n", failures); return 1; }
    puts("pikachu_harness: PASS behavior_vectors.json"); return 0;
}
