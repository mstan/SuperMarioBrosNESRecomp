#include "../../game_smash64_fighter_profile.h"
#include "../../mods/smash64/characters/pikachu.h"

#include <math.h>
#include <stdio.h>

static int failures;
#define CHECK(expr) do { if (!(expr)) { \
    fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #expr); failures++; \
} } while (0)
#define CHECK_NEAR(a, b) CHECK(fabs((a) - (b)) < 0.0001)

int main(void)
{
    const Smash64FighterProfile *pikachu =
        smash64_fighter_profile_find(SMASH64_PIKACHU_ID);

    CHECK(pikachu != NULL);
    /* Exact entry boundaries: $20/$6C are on the unsafe side. */
    CHECK_NEAR(smash64_fighter_profile_coupled_burst_component_px_limit(
                   pikachu, PK_QUICK_ATTACK_ZIP1, 0x1F), 16.0);
    CHECK_NEAR(smash64_fighter_profile_coupled_burst_component_px_limit(
                   pikachu, PK_QUICK_ATTACK_ZIP1, 0x20), 4.0);
    CHECK_NEAR(smash64_fighter_profile_coupled_burst_component_px_limit(
                   pikachu, PK_QUICK_ATTACK_ZIP2, 0x6B), 14.4);
    CHECK_NEAR(smash64_fighter_profile_coupled_burst_component_px_limit(
                   pikachu, PK_QUICK_ATTACK_ZIP2, 0x6C), 4.0);
    CHECK_NEAR(smash64_fighter_profile_coupled_burst_component_px_limit(
                   pikachu, PK_QUICK_ATTACK_WINDOW, 0), 4.0);

    if (failures) return 1;
    puts("pikachu_host_burst_plan_test: PASS");
    return 0;
}
