#include "../../game_smash64_pikachu_presentation.h"

#include <assert.h>
#include <stdio.h>

int main(void)
{
    static const unsigned int end_frames[] = {0u, 1u, 2u, 3u, 4u, 5u};
    static const unsigned int end_colors[] = {
        0x50FFFFFFu, 0x50000000u, 0u, 0u, 0x50FFFFFFu, 0x50000000u,
    };
    unsigned i;

    /* Execute all six source phases, including the End script's Goto wrap. */
    for (i = 0u; i < sizeof(end_frames) / sizeof(end_frames[0]); ++i)
        assert(game_smash64_pikachu_thunder_color_overlay(
            1, 0, 1, end_frames[i]) == end_colors[i]);

    assert(game_smash64_pikachu_thunder_color_overlay(1, 1, 0, 0u) ==
           0x5A0000FFu);
    assert(game_smash64_pikachu_thunder_color_overlay(1, 1, 0, 1u) ==
           0x64FFFFFFu);
    assert(game_smash64_pikachu_thunder_color_overlay(1, 1, 0, 2u) == 0u);
    /* Death/still/scripted renders must not inherit a stale special tint. */
    assert(game_smash64_pikachu_thunder_color_overlay(0, 1, 0, 0u) == 0u);
    assert(game_smash64_pikachu_thunder_color_overlay(0, 0, 1, 0u) == 0u);

    puts("pikachu_presentation_test: PASS");
    return 0;
}
