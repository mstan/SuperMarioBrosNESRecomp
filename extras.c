/*
 * games/super-mario-bros/extras.c — Super Mario Bros. runner hooks
 *
 * Implements the stubs required by game_extras.h plus widescreen
 * entity spawning extension via ram_read_hook.
 */
#include "game_extras.h"
#include "nes_runtime.h"

uint32_t    game_get_expected_crc32(void)                { return 0x3337EC46u; }
const char *game_get_name(void)                          { return "Super Mario Bros."; }
void        game_on_init(void)                           {}
void        game_on_frame(uint64_t frame_count) {
    (void)frame_count;
}
void        game_post_nmi(uint64_t frame_count) {
    (void)frame_count;
    /* Update absolute world scroll for widescreen margin clamping.
     * ScreenLeft: $071A = PageLoc, $071C = X_Pos. */
    g_ws_world_scroll = (int)nes_read(0x071A) * 256 + (int)nes_read(0x071C);
}
int         game_handle_arg(const char *key, const char *val) { (void)key; (void)val; return 0; }
const char *game_arg_usage(void)                         { return NULL; }

/*
 * RAM read hook — extend ScreenRight reads at CheckRightBounds so
 * enemies spawn earlier for the wider viewport.
 *
 * Only applied when widescreen is active (g_widescreen_right > 0).
 * Only at the spawn-threshold computation ($C164/$C16E) — all other
 * game logic reads the raw ScreenRight unchanged.
 *
 * CheckRightBounds flow:
 *   $C164: LDA $071D   (ScreenRight X)
 *   $C167: CLC
 *   $C168: ADC #$30    (48px lookahead)
 *   $C16E: LDA $071B   (ScreenRight Page)
 *   $C171: ADC #$00    (carry from ADC #$30)
 *
 * We add g_widescreen_right to the X read at $C164, and the carry
 * from that addition to the page read at $C16E.  No global state —
 * the page hook re-reads $071D to compute carry independently.
 */
uint8_t game_ram_read_hook(uint16_t pc, uint16_t addr, uint8_t val) {
    (void)pc; (void)addr;
    /* TODO: Phase 3 — extend spawn/despawn thresholds for widescreen.
     * Disabled for now while getting 16:9 visuals stable. */
    return val;
}
