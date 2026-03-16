/*
 * games/super-mario-bros/extras.c — Super Mario Bros. runner hooks
 *
 * Implements the stubs required by game_extras.h plus widescreen
 * runahead for right-margin tile lookahead.
 */
#include "game_extras.h"
#include "nes_runtime.h"
#include <string.h>
#include <stdio.h>

/* Generated functions we call for runahead */
extern void func_86E6_b0(void);  /* State 8: column-write loop (area parser) */
extern void func_8EDD_b0(void);  /* NMI VRAM upload routine */

uint32_t    game_get_expected_crc32(void)                { return 0x3337EC46u; }
const char *game_get_name(void)                          { return "Super Mario Bros."; }
void        game_on_init(void)                           {}
void        game_on_frame(uint64_t frame_count) {
    (void)frame_count;
}

/*
 * Widescreen runahead: run the game's column-write pipeline ahead to fill
 * g_shadow_nt with upcoming tile data for the right margin.
 *
 * After the real NMI completes, we:
 *   1. Save all mutable state (RAM, CPU, PPU regs, OAM)
 *   2. Seed g_shadow_nt from g_ppu_nt, enable g_runahead_mode
 *   3. For each column: set ColumnSets, call func_86E6_b0 (area parser),
 *      set ZP $00/$01 to point at upload buffer, call func_8EDD_b0
 *      (uploads buffer → shadow NT via redirected $2007 writes)
 *   4. Restore all state (g_ppu_nt never touched — writes go to shadow)
 *
 * This is safe because game_post_nmi runs inside the VBlank callback,
 * so nes_read/nes_write won't trigger re-entrant VBlank.
 */
static void runahead_widescreen(void) {
    if (g_widescreen_right <= 0) return;

    /* Only during gameplay (OperMode == 1) */
    if (g_ram[0x0770] != 1) {
        g_shadow_nt_valid = 0;
        return;
    }

    int extra_cols = (g_widescreen_right + 7) / 8 + 2;

    /* ---- Save mutable state (RAM, CPU, PPU regs) ---- */
    uint8_t ram_save[0x0800];
    memcpy(ram_save, g_ram, sizeof(ram_save));

    CPU6502State cpu_save = g_cpu;

    uint8_t oam_save[0x100];
    memcpy(oam_save, g_ppu_oam, sizeof(oam_save));

    uint8_t ppuctrl_save   = g_ppuctrl;
    uint8_t ppumask_save   = g_ppumask;
    uint8_t ppustatus_save = g_ppustatus;
    uint16_t ppuaddr_save  = g_ppuaddr;
    uint8_t scrollx_save   = g_ppuscroll_x;
    uint8_t scrolly_save   = g_ppuscroll_y;

    uint8_t latch_ppu, latch_scroll;
    runtime_get_latch_state(&latch_ppu, &latch_scroll);

    uint8_t ctrl_save = g_controller1_buttons;

    /* ---- Seed shadow NT from current real NT ---- */
    memcpy(g_shadow_nt, g_ppu_nt, sizeof(g_shadow_nt));

    /* ---- Set up runahead state ---- */
    g_controller1_buttons = 0;         /* no input during runahead */

    /* ---- Redirect PPU writes to shadow NT ---- */
    g_runahead_mode = 1;

    /* ---- Run column-write pipeline ONE COLUMN AT A TIME ----
     * The upload buffer at $0341-$03FF is only ~190 bytes.
     * Each column needs ~30 bytes, so writing many at once overflows.
     * Process one column per iteration: parse → upload → clear → repeat. */
    for (int i = 0; i < extra_cols; i++) {
        g_ram[0x071E] = 1;                /* ColumnSets: process 1 column */
        g_ram[0x0340] = 0;                /* reset buffer write position */
        memset(&g_ram[0x0341], 0, 0xBF);  /* clear upload buffer */

        func_86E6_b0();                   /* area parser writes 1 column to buffer */

        /* func_8EDD_b0 reads buffer from ZP pointer $00/$01, not $0773.
         * Point it at our runahead buffer at $0341. */
        g_ram[0x00] = 0x41;               /* low byte of $0341 */
        g_ram[0x01] = 0x03;               /* high byte of $0341 */
        func_8EDD_b0();                   /* upload buffer → shadow NT via $2007 */
    }

    g_runahead_mode = 0;
    g_shadow_nt_valid = 1;

    /* ---- Restore all state (g_ppu_nt and g_ppu_pal were never touched) ---- */
    memcpy(g_ram, ram_save, sizeof(ram_save));
    g_cpu = cpu_save;
    memcpy(g_ppu_oam, oam_save, sizeof(oam_save));

    g_ppuctrl   = ppuctrl_save;
    g_ppumask   = ppumask_save;
    g_ppustatus = ppustatus_save;
    g_ppuaddr   = ppuaddr_save;
    g_ppuscroll_x = scrollx_save;
    g_ppuscroll_y = scrolly_save;

    runtime_set_latch_state(latch_ppu, latch_scroll);
    g_controller1_buttons = ctrl_save;
}

void game_post_nmi(uint64_t frame_count) {
    (void)frame_count;
    /* Update absolute world scroll for widescreen margin clamping.
     * ScreenLeft: $071A = PageLoc, $071C = X_Pos. */
    g_ws_world_scroll = (int)nes_read(0x071A) * 256 + (int)nes_read(0x071C);

    /* Bump nametable generation on scene transitions so stale columns
     * (e.g. title screen text) get blanked in widescreen margins.
     * Reset all column stamps so only post-transition writes are fresh. */
    static uint8_t s_prev_opermode = 0xFF;
    uint8_t opermode = g_ram[0x0770];
    if (opermode != s_prev_opermode) {
        memset(g_nt_col_gen, 0, sizeof(g_nt_col_gen));
        g_nt_generation++;
        s_prev_opermode = opermode;
    }

    /* Debug: log alignment between scroll, game write cursor, and right margin */
    if (opermode == 1 && g_widescreen_right > 0) {
        static int s_dbg_count = 0;
        if (s_dbg_count < 20 || (s_dbg_count % 60 == 0 && s_dbg_count < 600)) {
            int origin_x = (g_ppuctrl & 1) * 256 + g_ppuscroll_x;
            int viewport_right_col = ((origin_x + 256) / 8) & 63;
            /* $0726/$0725 = CurrentNTAddr hi/lo (area parser write position) */
            uint16_t nt_addr = ((uint16_t)g_ram[0x0726] << 8) | g_ram[0x0725];
            int write_col = (nt_addr & 0x1F);  /* low 5 bits = column within NT */
            int write_nt  = (nt_addr >> 10) & 1; /* which nametable */
            int write_col_abs = write_nt * 32 + write_col; /* absolute 0-63 */
            int margin_end_col = ((origin_x + g_render_width) / 8) & 63;
            int delta = (write_col_abs - viewport_right_col) & 63;
            fprintf(stderr, "[ALIGN] f=%d origin=%d vp_right_col=%d write_col=%d(nt%d+%d) "
                    "margin_end=%d delta=%d extra_cols=%d\n",
                    (int)frame_count, origin_x, viewport_right_col,
                    write_col_abs, write_nt, write_col,
                    margin_end_col, delta,
                    (g_widescreen_right + 7) / 8 + 2);
            s_dbg_count++;
        }
        s_dbg_count++;
    }

    /* Run column-write pipeline ahead for right-margin tiles */
    runahead_widescreen();
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
    /* TODO: Phase C — extend spawn/despawn thresholds for widescreen.
     * Disabled for now while getting 16:9 visuals stable. */
    return val;
}
