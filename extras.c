/*
 * games/super-mario-bros/extras.c — Super Mario Bros. runner hooks
 *
 * Implements the stubs required by game_extras.h plus widescreen
 * runahead for right-margin tile lookahead.
 */
#include "game_extras.h"
#include "nes_runtime.h"
#include <string.h>

/* Generated functions we call for runahead */
extern void func_86E6_b0(void);  /* State 8: column-write loop (area parser) */
extern void func_8EDD_b0(void);  /* NMI VRAM upload routine */
extern void func_8220_b0(void);  /* OAM clear (fills $0200+Y with $F8) */
extern void func_8212_b0(void);  /* OperMode dispatcher (full game engine) */

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

/*
 * Sprite runahead: run the game engine with a camera shifted right by 256px
 * so that entities in the widescreen right margin (screen_x 256+) get
 * rendered into the 0-255 OAM X range.  The renderer draws g_ppu_oam_ext
 * sprites at (OAM_X + 256 + g_widescreen_left).
 *
 * By shifting exactly 256px, there's no overlap with normal OAM:
 * - Normal: game's off-screen check hides entities at screen_x >= 256
 * - Extended: shifted camera makes screen_x < 256 off-screen to the left
 *
 * g_suppress_vblank prevents NMI re-entry during the runahead frame.
 * g_runahead_mode redirects nametable writes to g_shadow_nt (harmless).
 * All state (RAM, CPU, PPU, OAM, nametables) is saved and restored.
 */
static void runahead_sprites(void) {
    if (g_widescreen_right <= 0) return;

    /* Only during gameplay (OperMode == 1) */
    if (g_ram[0x0770] != 1) {
        g_ext_oam_valid = 0;
        return;
    }

    /* ---- Save ALL mutable state ---- */
    uint8_t ram_save[0x0800];
    memcpy(ram_save, g_ram, sizeof(ram_save));

    CPU6502State cpu_save = g_cpu;

    uint8_t oam_save[0x100];
    memcpy(oam_save, g_ppu_oam, sizeof(oam_save));

    uint8_t nt_save[0x1000];
    memcpy(nt_save, g_ppu_nt, sizeof(nt_save));

    uint8_t shadow_save[0x1000];
    memcpy(shadow_save, g_shadow_nt, sizeof(shadow_save));

    uint8_t pal_save[0x20];
    memcpy(pal_save, g_ppu_pal, sizeof(pal_save));

    uint8_t ppuctrl_save   = g_ppuctrl;
    uint8_t ppumask_save   = g_ppumask;
    uint8_t ppustatus_save = g_ppustatus;
    uint16_t ppuaddr_save  = g_ppuaddr;
    uint8_t scrollx_save   = g_ppuscroll_x;
    uint8_t scrolly_save   = g_ppuscroll_y;

    uint8_t latch_ppu, latch_scroll;
    runtime_get_latch_state(&latch_ppu, &latch_scroll);

    uint8_t ctrl_save = g_controller1_buttons;
    int shadow_valid_save = g_shadow_nt_valid;

    /* ---- Shift camera right by 256 pixels ---- */
    g_ram[0x071A]++;  /* ScreenLeft_PageLoc += 1 */
    g_ram[0x071B]++;  /* ScreenRight_PageLoc += 1 */

    /* ---- Set up runahead ---- */
    g_controller1_buttons = 0;   /* no input during runahead */
    g_suppress_vblank = 1;       /* prevent NMI re-entry */
    g_runahead_mode = 1;         /* redirect NT writes to shadow (don't corrupt real NT) */

    /* ---- Clear OAM and run full game engine ---- */
    func_8220_b0();   /* Clear OAM (fills $0200+Y with $F8) */
    func_8212_b0();   /* OperMode dispatch → game logic + sprite rendering */

    /* ---- Capture extended OAM from RAM ---- */
    memcpy(g_ppu_oam_ext, &g_ram[0x0200], 256);

    /* ---- Remove ghost player from extended OAM ----
     * The player rendering at $F176 uses pure 8-bit subtraction:
     *   screen_x = SprObject_X - ScreenLeft_X
     * During the runahead, the camera tracking code scrolls ScreenLeft_X
     * to follow the player, so the ghost's OAM X differs from the real
     * frame's OAM X.  Compute the player's screen X from the RUNAHEAD
     * state (g_ram, not ram_save) and blank sprites near that X.
     * The player is 16px wide (two 8x8 tiles), so blank [-4, +20].
     *
     * IMPORTANT: use uint8_t subtraction for the X delta — this mirrors
     * the NES's 8-bit wrapping.  When player_sx is near 255/0, the
     * second tile column wraps (e.g. 254+8 = 6 mod 256).  Signed int
     * subtraction would give -248 instead of 8, letting tiles escape. */
    {
        uint8_t player_sx = g_ram[0x86] - g_ram[0x071C];
        for (int s = 0; s < 64; s++) {
            int eo = s * 4;
            if (g_ppu_oam_ext[eo] >= 0xEF) continue;
            uint8_t dx = (uint8_t)(g_ppu_oam_ext[eo + 3] - player_sx);
            if (dx <= 20 || dx >= 252) {  /* [-4, +20] circular */
                g_ppu_oam_ext[eo] = 0xFF;  /* hide */
            }
        }
    }

    g_ext_oam_valid = 1;

    /* ---- Clean up ---- */
    g_runahead_mode = 0;
    g_suppress_vblank = 0;

    /* ---- Restore ALL state ---- */
    memcpy(g_ram, ram_save, sizeof(ram_save));
    g_cpu = cpu_save;
    memcpy(g_ppu_oam, oam_save, sizeof(oam_save));
    memcpy(g_ppu_nt, nt_save, sizeof(nt_save));
    memcpy(g_shadow_nt, shadow_save, sizeof(shadow_save));
    memcpy(g_ppu_pal, pal_save, sizeof(pal_save));

    g_ppuctrl     = ppuctrl_save;
    g_ppumask     = ppumask_save;
    g_ppustatus   = ppustatus_save;
    g_ppuaddr     = ppuaddr_save;
    g_ppuscroll_x = scrollx_save;
    g_ppuscroll_y = scrolly_save;

    runtime_set_latch_state(latch_ppu, latch_scroll);
    g_controller1_buttons = ctrl_save;
    g_shadow_nt_valid = shadow_valid_save;
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

    /* Run column-write pipeline ahead for right-margin tiles */
    runahead_widescreen();

    /* Run sprite runahead for right-margin enemies */
    runahead_sprites();
}

int         game_handle_arg(const char *key, const char *val) { (void)key; (void)val; return 0; }
const char *game_arg_usage(void)                         { return NULL; }

/*
 * RAM read hook — extend ScreenRight reads at CheckRightBounds so
 * enemies spawn earlier for the wider viewport.
 *
 * Only applied when widescreen is active (g_widescreen_right > 0).
 * PC-gated to the spawn-threshold computation ONLY ($C164/$C16E).
 *
 * CheckRightBounds flow:
 *   $C164: LDA $071D   (ScreenRight X)
 *   $C167: CLC
 *   $C168: ADC #$30    (48px lookahead)
 *   $C16E: LDA $071B   (ScreenRight Page)
 *   $C171: ADC #$00    (carry from ADC #$30)
 *
 * We add g_widescreen_right to the X read at $C164, and the carry
 * from that addition to the page read at $C16E.
 *
 * NOT hooked: $D69A/$D6A1 (72px activation check) — that check is
 * used for enemy behavior/rendering, not just spawning.  Extending it
 * causes off-screen enemies to be treated as "on screen", leading to
 * sprite X wrapping (8-bit) and reversed movement.
 */
uint8_t game_ram_read_hook(uint16_t pc, uint16_t addr, uint8_t val) {
    (void)pc; (void)addr;
    /* Spawn extension disabled — NES sprites use 8-bit X coordinates,
     * so enemies activated beyond X=255 from ScreenLeft have their
     * positions wrap around, causing wrong placement and reversed
     * movement.  Proper fix requires an extended sprite renderer
     * that can place sprites at X > 255 in the widescreen margin. */
    return val;
}
