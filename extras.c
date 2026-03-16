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
void        game_on_init(void) {
    /* Default to 16:9 widescreen unless --widescreen was explicitly passed */
    if (g_aspect_ratio == ASPECT_4_3)
        widescreen_set(ASPECT_16_9);
}
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

    /* ---- Hide player so it doesn't appear as a ghost ----
     * The sprite renderer at $F171 reads Player_Y from $00CE+X.
     * Setting it to $FF puts the player below the visible screen
     * (Y=255 > 240 scanlines), so no player sprites appear in OAM.
     * This is much more robust than post-hoc ghost removal, which
     * fails when animation frames differ between real and runahead. */
    g_ram[0x00CE] = 0xFF;  /* Player_Y_Position = off-screen */

    /* ---- Set up runahead ---- */
    g_controller1_buttons = 0;   /* no input during runahead */
    g_suppress_vblank = 1;       /* prevent NMI re-entry */
    g_runahead_mode = 1;         /* redirect NT writes to shadow (don't corrupt real NT) */

    /* ---- Clear OAM and run full game engine ---- */
    func_8220_b0();   /* Clear OAM (fills $0200+Y with $F8) */
    func_8212_b0();   /* OperMode dispatch → game logic + sprite rendering */

    /* ---- Capture extended OAM from RAM ---- */
    memcpy(g_ppu_oam_ext, &g_ram[0x0200], 256);

    /* ---- Deduplicate: blank sprites that already exist in real OAM ----
     * HUD sprites (coin icon, etc.) would appear as ghosts in the right
     * margin if not deduped.  Match by (Y, tile, attr).
     *
     * IMPORTANT: only dedup when the real OAM sprite is well inside the
     * 4:3 viewport (X < 232).  Sprites near the right edge (X >= 232)
     * straddle the 4:3/widescreen boundary — their sub-sprites split
     * across real and extended OAM.  If we dedup the extended half, the
     * sprite visibly splits in two and flickers during the transition.
     * Keeping both copies is safe: the extended version at X+256 lands
     * off-screen in the framebuffer when X >= 232. */
    for (int s = 0; s < 64; s++) {
        int eo = s * 4;
        if (g_ppu_oam_ext[eo] >= 0xEF) continue;

        uint8_t ey = g_ppu_oam_ext[eo];
        uint8_t et = g_ppu_oam_ext[eo + 1];
        uint8_t ea = g_ppu_oam_ext[eo + 2];

        for (int r = 0; r < 64; r++) {
            int ro = r * 4;
            if (oam_save[ro] >= 0xEF) continue;
            if (oam_save[ro + 3] >= 232) continue;  /* skip boundary sprites */
            if (oam_save[ro] == ey &&
                oam_save[ro + 1] == et &&
                oam_save[ro + 2] == ea) {
                g_ppu_oam_ext[eo] = 0xFF;  /* blank duplicate */
                break;
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
 * RAM read hook — modify screen boundary reads for widescreen support.
 *
 * Only applied when widescreen is active (g_widescreen_right > 0).
 *
 * Enemy bounds check at $D67A-$D6D5 creates a keep-alive zone from
 * (ScreenLeft - 72) to (ScreenRight + 72).  Enemies outside this zone
 * get deactivated via JSR $C998.
 *
 * For widescreen, we need two adjustments to the bounds check:
 *
 * 1. REAL FRAME — extend right boundary (+1 page):
 *    The real frame's right boundary would deactivate enemies that are
 *    visible in the widescreen right margin.  Hook $D6A1 (LDA $071B)
 *    to add 1 page, extending the keep-alive zone rightward by 256px.
 *
 * 2. RUNAHEAD FRAME — restore left boundary (-1 page):
 *    The runahead shifts the camera +256px, which shifts the left
 *    boundary +256px.  Hook $D693 (LDA $071A) to subtract 1 page,
 *    restoring the left boundary to match the real frame.
 *
 * Combined effect: enemies stay alive from the real camera's left edge
 * all the way to the runahead camera's right edge.
 *
 * Bounds check disassembly ($D67A-$D6D5):
 *   Left boundary:
 *     $D680: LDA $071C   (ScreenLeft X)
 *     $D68F: SBC #$48    (-72px)
 *     $D691: STA $01     (left boundary X)
 *     $D693: LDA $071A   (ScreenLeft Page)  ← HOOKED (runahead: -1)
 *     $D696: SBC #$00    (subtract borrow)
 *     $D698: STA $00     (left boundary Page)
 *   Right boundary:
 *     $D69A: LDA $071D   (ScreenRight X)
 *     $D69D: ADC #$48    (+72px)
 *     $D69F: STA $03     (right boundary X)
 *     $D6A1: LDA $071B   (ScreenRight Page)  ← HOOKED (real: +1)
 *     $D6A4: ADC #$00    (add carry)
 *     $D6A6: STA $02     (right boundary Page)
 */
uint8_t game_ram_read_hook(uint16_t pc, uint16_t addr, uint8_t val) {
    if (g_widescreen_right <= 0) return val;

    /* REAL FRAME: extend right boundary so enemies in the widescreen
     * margin are not deactivated before the runahead can render them.
     * Round up to whole pages — better to keep enemies alive slightly
     * too long off-screen than to despawn them while still visible. */
    if (!g_runahead_mode) {
        if (pc == 0xD6A1 && addr == 0x071B) {
            int extra_pages = (g_widescreen_right + 255) / 256;
            return val + extra_pages;
        }
    }

    /* RUNAHEAD FRAME: restore left boundary to match the real frame.
     * The runahead shifted ScreenLeft_PageLoc +1; undo that here so
     * enemies in the real viewport aren't deactivated. */
    if (g_runahead_mode) {
        if (pc == 0xD693 && addr == 0x071A) {
            return (val > 0) ? val - 1 : val;
        }
    }

    return val;
}
