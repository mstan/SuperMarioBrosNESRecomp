/*
 * games/super-mario-bros/extras.c — Super Mario Bros. runner hooks
 *
 * No game-specific features yet. Implements the empty stubs required
 * by game_extras.h so the runner links cleanly.
 */
#include "game_extras.h"
#include "nes_runtime.h"

uint32_t    game_get_expected_crc32(void)                { return 0x3337EC46u; }
const char *game_get_name(void)                          { return "Super Mario Bros."; }
void        game_on_init(void)                           {}
void        game_on_frame(uint64_t frame_count) {
    (void)frame_count;
    /* Bump NT generation on OperMode change (title↔gameplay↔death etc.) */
    static uint8_t s_last_opermode = 0xFF;
    uint8_t opermode = g_ram[0x0770];
    if (opermode != s_last_opermode) {
        s_last_opermode = opermode;
        g_nt_generation++;
    }
    /* Bump when rendering transitions ON→OFF (nametable load in progress) */
    static uint8_t s_was_rendering = 0;
    uint8_t is_rendering = g_ppumask & 0x18;
    if (s_was_rendering && !is_rendering)
        g_nt_generation++;
    s_was_rendering = is_rendering;
    /* Bump on AreaNumber/WorldNumber/ScreenRoutineTask changes */
    static uint8_t s_last_area = 0xFF, s_last_world = 0xFF, s_last_task = 0xFF;
    uint8_t area  = g_ram[0x074E];
    uint8_t world = g_ram[0x075F];
    uint8_t task  = g_ram[0x0772];
    if (area != s_last_area || world != s_last_world || task != s_last_task) {
        s_last_area  = area;
        s_last_world = world;
        s_last_task  = task;
        g_nt_generation++;
    }
    /* Periodic safety net: bump every 300 frames (5 sec) to age out any
     * stale data that slipped through the above triggers. */
    if (frame_count > 0 && (frame_count % 300) == 0)
        g_nt_generation++;
}
void        game_post_nmi(uint64_t frame_count) {
    (void)frame_count;
    /* Keep-alive: re-stamp columns currently visible in the NES viewport
     * so that periodic generation bumps don't falsely blank them.
     * This ensures the main 256px area + nearby margin columns stay fresh. */
    if (g_widescreen_left > 0) {
        int origin_x = g_ppuscroll_x + ((g_ppuctrl & 0x01) ? 256 : 0);
        for (int sx = -8; sx < 264; sx += 8) {
            int col = ((origin_x + sx) / 8) & 63;
            g_nt_col_gen[col] = g_nt_generation;
        }
    }
}
int         game_handle_arg(const char *key, const char *val) { (void)key; (void)val; return 0; }
const char *game_arg_usage(void)                         { return NULL; }
