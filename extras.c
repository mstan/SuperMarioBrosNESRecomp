/*
 * games/super-mario-bros/extras.c — Super Mario Bros. runner hooks
 *
 * Implements game_extras.h for Super Mario Bros.
 * Features:
 *   TCP debug server on port 4370 (gated behind debug.ini)
 *   Verify mode (--verify, --emulated) via Nestopia oracle
 *   Watchdog timer for stuck frames
 */
#include "game_extras.h"
#include "nes_runtime.h"
#include "config.h"
#include "input_script.h"
#include "debug_server.h"
#include "verify_mode.h"
#ifdef ENABLE_NESTOPIA_ORACLE
#include "nestopia_bridge.h"
#endif
#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif

/* ---- Debug mode ---- */
static int s_debug_enabled = 0;
static void get_exe_relative_path(const char *filename, char *out, int max_len);

static int check_debug_ini(void) {
    char path[512];
    get_exe_relative_path("debug.ini", path, sizeof(path));
    FILE *f = fopen(path, "r");
    if (f) { fclose(f); return 1; }
    return 0;
}

/* ---- Debug server state ---- */
static int s_tcp_port = 4370;

/* ROM path exposed by runner for verify mode init */
const char *g_rom_path_for_extras = NULL;

/* ---- Path helper ---- */

/* Build path: <exe_dir>/filename. Same pattern as launcher.c:get_rom_cfg_path(). */
static void get_exe_relative_path(const char *filename, char *out, int max_len) {
#ifdef _WIN32
    char exe_path[MAX_PATH];
    GetModuleFileNameA(NULL, exe_path, MAX_PATH);
    char *last_sep = strrchr(exe_path, '\\');
    if (last_sep) *(last_sep + 1) = '\0';
    snprintf(out, max_len, "%s%s", exe_path, filename);
#else
    snprintf(out, max_len, "%s", filename);
#endif
}

/* =====================================================================
 * Widescreen (opt-in enhancement, default OFF — see WIDESCREEN.md)
 *
 * Three coordinated layers, all gated at runtime on s_ws_enabled plus the
 * gameplay-mode discriminator (OperMode $0770 == 1 game / 2 victory; the
 * title screen and its attract demo run under mode 0 and stay fully
 * vanilla, in simulation and presentation):
 *
 *  1. Presentation — g_widescreen_left/right widen the runner's BG render
 *     (SMB's two vertically-mirrored nametables hold 512px; the column
 *     writer leads ScreenRight by ~98-117px, capping the right margin at
 *     96; the left margin shows just-scrolled-out columns, capped at 128).
 *     Non-gameplay modes pillarbox via g_ws_eff_left/right = 0.
 *
 *  2. Sprite-X sidecar — SMB computes sprite X with 8-bit math, so any
 *     object whose screen X leaves [0,255] wraps and would teleport to
 *     the opposite edge.  At GetObjRelativePosition's SBC ScreenLeft_X
 *     ($F179) we publish the object's true 16-bit screen X (g_cpu.X is
 *     the SprObject index for player/enemy/fireball/bubble/misc/block
 *     alike) and remember it per rel slot (g_cpu.Y); reads of any
 *     SprObject_Rel_XPos var ($03AD-$03B3, hooked in game.toml) re-arm
 *     the live bias for that slot's object, so batch-computed rels
 *     (e.g. both block slots) can't clobber each other's draw context.
 *     The runner unwraps every subsequent shadow-OAM X write.
 *
 *  3. Window widening — the game's own draw-cull, despawn, and spawn
 *     decisions are widened by shifting the screen-edge values they read,
 *     at exactly the PCs that implement each decision (the hook receives
 *     the reading PC).  16-bit edges are read low-byte-then-page; a
 *     pending carry propagates between the paired reads.  Every shift is
 *     ±margin, so spawn/despawn hysteresis gaps stay vanilla-sized, and
 *     margin = 0 reduces exactly to vanilla.
 *
 * Complete classification of all $071A-$071D readers (PC → policy):
 *   $F179            GetObjRelativePosition   → sidecar bias capture
 *   $F1FA/$F202      GetXOffscreenBits edges  → widen ±margin (indexed)
 *   $D680/$D693      OffscreenBoundsCheck L   → widen -left
 *   $D69A/$D6A1      OffscreenBoundsCheck R   → widen +right
 *   $C164/$C16E      CheckRightBounds base    → widen +right (spawn window end)
 *   $C1B6/$C1BB      spawn raw-edge compare   → widen +right (spawn window start)
 *   $C5DA/$C5E2      frenzy spawn placement   → VANILLA (widening embeds it)
 *   $C73C/$C741      group spawn placement    → VANILLA (widening embeds it)
 *   $B013/$B01C      player screen-edge clamp → VANILLA (repositions the player)
 *   $C09C/$C0A5      loop command rewind      → VANILLA (castle maze logic)
 *   $9206            area parser page gate    → VANILLA (terrain write-ahead)
 *   $908B/$9131      area/player init         → VANILLA
 *   $83B0/$83D4/$85E2 victory mode logic      → VANILLA (watch star flag pop-in)
 *   $DDE4/$DE96/$DEB3 enemy-specific logic    → VANILLA (page-0/player checks)
 *   $E255/$E25C      bounding-box screen-rel  → VANILLA (collision = vanilla)
 *   $E2DE/$E2E6      camera+0x80 midpoint     → VANILLA
 *   $EC8C            platform draw rel        → VANILLA (sidecar covers draw)
 *   $AFD1/$AFDA/$B038/$B041 scroll bookkeeping → VANILLA (no hook configured)
 * ===================================================================== */

#define SMB_WS_MAX_LEFT  128  /* just-scrolled-out columns stay valid this far */
#define SMB_WS_MAX_RIGHT 96   /* SMB column writer leads ScreenRight by ~98px min */

static int s_ws_enabled = 0;
static int s_ws_left = 0, s_ws_right = 0;   /* configured margins */

/* Pending page-carry per hooked read pair (low byte read sets it, the
 * page read consumes it).  Separate vars per pair — SMB's logic runs
 * inside the NMI handler, so pairs never interleave, but isolation is
 * free and removes the assumption. */
static int     s_ws_pend_bits    = 0;
static int     s_ws_pend_despawn = 0;
static int     s_ws_pend_spawnb  = 0;
static int     s_ws_pend_spawnc  = 0;

/* Per-rel-slot sidecar bias table.  GetObjRelativePosition stores rel X
 * into SprObject_Rel_XPos ($03AD,Y); Y is the rel slot (0 player, 1 enemy,
 * 2 fireball, 3/4 block 0/1, 5 bubble, 6 misc).  The slot's true 16-bit
 * rel is captured at $F179.  A single live context is not enough: SMB
 * batch-computes some rels before drawing (RelativeBlockPosition does both
 * block slots back-to-back, so block 0 would draw under block 1's bias).
 * Any READ of a rel X var therefore re-arms the live context for that
 * slot's object — draw code always loads its own rel var right before
 * laying out sprites. */
#define SMB_WS_REL_BASE  0x03AD
#define SMB_WS_REL_SLOTS 7
static int16_t s_ws_rel16_tab[SMB_WS_REL_SLOTS];
static uint8_t s_ws_rel8_tab[SMB_WS_REL_SLOTS];
static uint8_t s_ws_rel_mask = 0;   /* bit n: slot n captured this mode */

/* Shift an 8-bit edge value by ±margin, recording the page carry. */
static uint8_t ws_shift_lo(uint8_t val, int shift, int *pend) {
    int wide = (int)val + shift;
    *pend = (wide < 0) ? -1 : (wide > 0xFF ? 1 : 0);
    return (uint8_t)(wide & 0xFF);
}
static uint8_t ws_shift_hi(uint8_t val, int *pend) {
    uint8_t r = (uint8_t)((int)val + *pend);
    *pend = 0;
    return r;
}

/* In widened-simulation mode this frame?  Game (1) and victory (2) modes
 * widen; title/demo (0) and game-over (3) stay vanilla + pillarboxed. */
static int ws_sim_active(void) {
    if (!s_ws_enabled) return 0;
    uint8_t mode = g_ram[0x0770];
    return mode == 1 || mode == 2;
}

/* =====================================================================
 * Enemy spawn geometry guard (ISSUE #12)
 *
 * Group ($C73C) and frenzy ($C5DA) spawners place an enemy at
 * (screen-edge + offset).  The window-widening hooks shift that edge by
 * +right, so an edge-relative spawn lands up to `right` px deeper in the
 * world — sometimes INSIDE solid geometry (pipe/brick), where the enemy
 * has no collision to escape and is stuck forever.  Authored enemies
 * ($C1AB PositionEnemyObj) take their position from level data, not the
 * edge, so they are never mis-placed — only these two edge-relative
 * classes are.
 *
 * Guard: on the frame an enemy first goes active, if its body cell is
 * solid, pull it left one metatile at a time until it clears.  When the
 * widened edge is already empty the enemy stays at the 16:9 edge (no
 * pop-in); only embedded spawns are nudged, worst case toward the 4:3
 * edge (clear by vanilla design).  The block buffer is valid this far
 * right because SMB's column writer leads ScreenRight by ~98px and the
 * right margin is capped at 96.
 *
 * ws_block_metatile/ws_world_solid are a read-only reimplementation of
 * SMB BlockBufferCollision + ChkForNonSolids (no game state touched). */

/* Metatile id at world (page*256 + x_lo, y).  Block_Buffer_1 @ $0500,
 * Block_Buffer_2 @ $05D0 (13 cols x 16 rows each); page bit0 selects the
 * buffer, X high-nibble the column, (Y&0xF0)-0x20 the row (8-bit wrap). */
static uint8_t ws_block_metatile(uint8_t page, uint8_t x_lo, uint8_t y) {
    uint16_t base = (page & 1) ? 0x05D0 : 0x0500;
    uint8_t  col  = (uint8_t)(x_lo >> 4);
    uint8_t  rowo = (uint8_t)((y & 0xF0) - 0x20);
    return g_ram[(uint16_t)(base + (uint8_t)(col + rowo))];
}
/* SMB enemy solidity: a nonzero metatile that isn't a known passable id
 * (climb $26, coins $C2/$C3, water/decor $5F/$60). */
static int ws_world_solid(uint16_t world_x, uint8_t y) {
    uint8_t m = ws_block_metatile((uint8_t)(world_x >> 8), (uint8_t)world_x, y);
    if (m == 0x00) return 0;
    if (m == 0x26 || m == 0xC2 || m == 0xC3 || m == 0x5F || m == 0x60) return 0;
    return 1;
}

#define SMB_ENEMY_SLOTS 5
#define SMB_ENEMY_ID_PIRANHA 0x0D   /* lives inside pipes — never count it */
static unsigned s_ws_embed_detect = 0;  /* slot-frames an enemy sat in solid geom */
static unsigned s_ws_guard_frames = 0;  /* frames the detector swept */

/* Footprint solidity: "embedded" if the body centre OR any of the four
 * 16x16 corners (inset 1px) lands on a solid metatile.  Centre-only
 * misses side/lip embedding — a Goomba wedged against a pipe can have an
 * air centre while its lower corners overlap the column. */
static int ws_enemy_embedded(uint16_t world_x, uint8_t y) {
    static const int8_t sx[5] = { 8,  1, 14,  1, 14 };
    static const int8_t sy[5] = { 8,  1,  1, 14, 14 };
    for (int k = 0; k < 5; k++)
        if (ws_world_solid((uint16_t)(world_x + sx[k]), (uint8_t)(y + sy[k])))
            return 1;
    return 0;
}

/* Always-on spawn-geometry INVARIANT CHECK (observe, never mutate).
 *
 * With the split-edge placement fix (edge-relative spawns served vanilla
 * ScreenRight, authored spawns already edge-independent) no enemy can be
 * placed into solid geometry by widescreen, so s_ws_embed_detect must
 * stay 0 in play — it is the live invariant we validate against, queried
 * via smb_ws_state.  We deliberately do NOT move or drop enemies: a
 * per-frame position mutator risks corrupting legit vanilla behaviour
 * (stairs, pipe lips, frenzy flyers, Lakitu/Spiny, slot recycling), and
 * the real fix is upstream in the placement reads.  Piranha Plants (live
 * in pipes by design) and defeated/dying enemies are not counted.
 * Widescreen gameplay only — vanilla/oracle builds never enter here. */
static void ws_guard_embedded(void) {
    if (!ws_sim_active()) return;
    s_ws_guard_frames++;

    for (int i = 0; i < SMB_ENEMY_SLOTS; i++) {
        if (!g_ram[0x0F + i]) continue;                 /* inactive slot     */
        if (g_ram[0x16 + i] == SMB_ENEMY_ID_PIRANHA) continue;
        if (g_ram[0x1E + i] & 0xE0) continue;           /* defeated/dying    */

        uint16_t wx = (uint16_t)((g_ram[0x6E + i] << 8) | g_ram[0x87 + i]);
        if (ws_enemy_embedded(wx, g_ram[0xCF + i]))
            s_ws_embed_detect++;
    }
}

/* Parse "16:9" / "21:9" style aspect, or "WxH" margins like "85x85". */
static void ws_set_margins_from_spec(const char *spec) {
    int a = 0, b = 0;
    if (sscanf(spec, "%d:%d", &a, &b) == 2 && a > 0 && b > 0) {
        int target = (240 * a + b / 2) / b;     /* width at 240 lines */
        int extra  = (target - 256 + 1) / 2;
        if (extra < 0) extra = 0;
        s_ws_left = s_ws_right = extra;
    } else if (sscanf(spec, "%dx%d", &a, &b) == 2 && a >= 0 && b >= 0) {
        s_ws_left = a; s_ws_right = b;
    }
    if (s_ws_left  > SMB_WS_MAX_LEFT)  s_ws_left  = SMB_WS_MAX_LEFT;
    if (s_ws_right > SMB_WS_MAX_RIGHT) s_ws_right = SMB_WS_MAX_RIGHT;
    s_ws_enabled = (s_ws_left + s_ws_right) > 0;
}

/* widescreen.ini next to the exe:
 *   enabled = 1
 *   aspect = 16:9        (or: margins = 85x85)
 * Absent file or enabled=0 → fully vanilla. */
static void ws_load_config(void) {
    /* Launcher toggle: config.ini "Widescreen = 1" enables widescreen with a 16:9
     * default. A widescreen.ini below can still override the margins. */
    if (g_nes_config.widescreen) ws_set_margins_from_spec("16:9");

    char path[512];
    get_exe_relative_path("widescreen.ini", path, sizeof(path));
    FILE *f = fopen(path, "r");
    if (!f) return;
    int enabled = 0;
    char aspect[32] = "16:9";
    char line[128];
    while (fgets(line, sizeof(line), f)) {
        char key[32], val[64];
        if (sscanf(line, " %31[A-Za-z_] = %63s", key, val) == 2) {
            if (strcmp(key, "enabled") == 0) enabled = atoi(val);
            else if (strcmp(key, "aspect") == 0 || strcmp(key, "margins") == 0)
                snprintf(aspect, sizeof(aspect), "%s", val);
        }
    }
    fclose(f);
    if (enabled) ws_set_margins_from_spec(aspect);
}

static void ws_apply_init(void) {
    if (!s_ws_enabled) return;
    g_widescreen_left  = s_ws_left;
    g_widescreen_right = s_ws_right;
    g_render_width     = 256 + s_ws_left + s_ws_right;
    g_ws_oam_sidecar   = 1;
    /* Start pillarboxed; the per-frame gate opens the margins in gameplay. */
    g_ws_eff_left = g_ws_eff_right = 0;
    printf("[Widescreen] %dpx (%dL + 256 + %dR), sidecar on\n",
           g_render_width, s_ws_left, s_ws_right);
}

/* Per-frame presentation gate, called from game_post_nmi (before render). */
static void ws_update_frame_gate(void) {
    if (!s_ws_enabled) return;
    int wide = ws_sim_active();
    g_ws_eff_left  = wide ? s_ws_left  : 0;
    g_ws_eff_right = wide ? s_ws_right : 0;
    if (!wide) { g_ws_obj_ctx_valid = 0; s_ws_rel_mask = 0; }
}

/* ---- game_extras.h implementation ---- */

uint32_t game_get_expected_crc32(void) { return 0xD445F698u; }

const char *game_get_name(void) { return "Super Mario Bros."; }

void game_on_init(void) {
    ws_load_config();
    ws_apply_init();

    s_debug_enabled = check_debug_ini();

    if (s_debug_enabled) {
        printf("[Debug] debug.ini found — TCP server and verify mode enabled\n");
        debug_server_init(s_tcp_port);

        if (g_run_mode != RUN_MODE_NATIVE && g_rom_path_for_extras) {
            verify_mode_init(g_rom_path_for_extras);
        }
    } else if (g_run_mode != RUN_MODE_NATIVE) {
        /* --verify or --emulated implies debug even without ini */
        s_debug_enabled = 1;
        debug_server_init(s_tcp_port);
        if (g_rom_path_for_extras)
            verify_mode_init(g_rom_path_for_extras);
    }
}

void game_on_frame(uint64_t frame_count) {
    (void)frame_count;
    if (s_debug_enabled) {
        debug_server_poll();
        debug_server_wait_if_paused();
        int ovr = debug_server_get_input_override();
        if (ovr >= 0)
            g_controller1_buttons = (uint8_t)ovr;
    }
}

void game_post_nmi(uint64_t frame_count) {
    (void)frame_count;
    ws_update_frame_gate();
    ws_guard_embedded();
    if (s_debug_enabled) {
        debug_server_record_frame();
    }
}

int game_handle_arg(const char *key, const char *val) {
    if (strcmp(key, "--widescreen") == 0 && val) {
        /* Overrides widescreen.ini.  "off" disables; "16:9" or "85x85". */
        s_ws_enabled = 0; s_ws_left = s_ws_right = 0;
        if (strcmp(val, "off") != 0)
            ws_set_margins_from_spec(val);
        return 1;
    }
    if (strcmp(key, "--tcp-port") == 0 && val) {
        s_tcp_port = atoi(val);
        printf("[Debug] TCP port set to %d\n", s_tcp_port);
        return 1;
    }
    if (strcmp(key, "--verify") == 0) {
        g_run_mode = RUN_MODE_VERIFY;
        printf("[Verify] Dual-execution verify mode enabled\n");
        return 1;
    }
    if (strcmp(key, "--emulated") == 0) {
        g_run_mode = RUN_MODE_EMULATED;
        printf("[Verify] Nestopia emulated mode enabled\n");
        return 1;
    }
    return 0;
}

const char *game_arg_usage(void) {
    return "  --widescreen SPEC   Widescreen: \"16:9\", \"85x85\" (LxR margins), or \"off\"\n"
           "  --tcp-port PORT     TCP debug server port (default 4370)\n"
           "  --verify            Enable dual-execution verify mode (Nestopia oracle)\n"
           "  --emulated          Run purely via Nestopia emulator (no recompiled code)\n";
}

void game_run_nmi(void) {
    verify_mode_run_nmi();
}

void game_run_main(void) {
    if (g_run_mode == RUN_MODE_EMULATED) {
#ifdef ENABLE_NESTOPIA_ORACLE
        /* Nestopia drives the entire execution — its own CPU, PPU, APU. */
        printf("[Emulated] Nestopia driving main loop\n");

        static uint32_t emu_argb[256 * 240];  /* ARGB framebuffer */

        extern void runner_present_framebuf(const uint32_t *argb_buf);

        for (;;) {
            /* Poll SDL events */
            {
                SDL_Event ev;
                while (SDL_PollEvent(&ev)) {
                    if (ev.type == SDL_QUIT) exit(0);
                    if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE) exit(0);
                    if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_F5)
                        g_turbo ^= 1;
                }

                /* Read keyboard for controller input */
                const uint8_t *keys = SDL_GetKeyboardState(NULL);
                uint8_t btn = 0;
                if (keys[SDL_SCANCODE_Z])      btn |= 0x80;
                if (keys[SDL_SCANCODE_X])      btn |= 0x40;
                if (keys[SDL_SCANCODE_TAB])    btn |= 0x20;
                if (keys[SDL_SCANCODE_RETURN]) btn |= 0x10;
                if (keys[SDL_SCANCODE_UP])     btn |= 0x08;
                if (keys[SDL_SCANCODE_DOWN])   btn |= 0x04;
                if (keys[SDL_SCANCODE_LEFT])   btn |= 0x02;
                if (keys[SDL_SCANCODE_RIGHT])  btn |= 0x01;
                g_controller1_buttons = btn;
            }

            /* Debug server */
            debug_server_poll();
            debug_server_wait_if_paused();

            /* Run one Nestopia frame */
            nestopia_bridge_run_frame(g_controller1_buttons);

            /* Get Nestopia's rendered framebuffer */
            nestopia_bridge_get_framebuf_argb(emu_argb);

            /* Present Nestopia's frame directly to SDL window */
            runner_present_framebuf(emu_argb);

            /* Also extract RAM state for debug server queries */
            nestopia_bridge_get_ram(g_ram);
            nestopia_bridge_get_sram(g_sram);
            g_frame_count++;

            /* Record frame for debug server */
            debug_server_record_frame();

            /* Frame pacing: ~60fps */
            if (!g_turbo) SDL_Delay(16);
        }
#else
        fprintf(stderr, "[Error] Nestopia not compiled in, falling back to native\n");
        func_RESET();
#endif
    } else {
        /* Native or verify mode: func_RESET() drives the main loop,
         * NMI fires via nes_vblank_callback -> game_run_nmi(). */
        func_RESET();
    }
}

int game_dispatch_override(uint16_t addr) { (void)addr; return 0; }

uint8_t game_ram_read_hook(uint16_t pc, uint16_t addr, uint8_t val) {
    if (!ws_sim_active()) return val;

    /* ---- Sidecar re-arm: SprObject_Rel_XPos reads (any PC) ----
     * Draw code loads its object's rel X right before writing sprites;
     * re-arm the live bias for that slot so the OAM unwrapping always
     * matches the object actually being drawn.  Value returned unchanged
     * — simulation stays vanilla. */
    if (addr >= SMB_WS_REL_BASE && addr < SMB_WS_REL_BASE + SMB_WS_REL_SLOTS) {
        unsigned slot = addr - SMB_WS_REL_BASE;
        if (s_ws_rel_mask & (1u << slot)) {
            g_ws_obj_true_rel  = s_ws_rel16_tab[slot];
            g_ws_obj_rel8      = s_ws_rel8_tab[slot];
            g_ws_obj_ctx_valid = 1;
        }
        return val;
    }

    switch (pc) {

    /* ---- Sidecar bias capture: GetObjRelativePosition ($F171) ----
     * $F179: SBC ScreenLeft_X_Pos, with g_cpu.X = SprObject index for
     * every object class (player 0, enemies 1.., fireballs, misc, ...).
     * Publish the object's true 16-bit screen X; the runner unwraps the
     * OAM X writes of the draw that follows.  Return val unchanged —
     * the game's own 8-bit math stays vanilla. */
    case 0xF179: {
        int world = ((int)g_ram[(0x6D + g_cpu.X) & 0xFF] << 8)
                  |       g_ram[(0x86 + g_cpu.X) & 0xFF];
        int cam   = ((int)g_ram[0x071A] << 8) | g_ram[0x071C];
        int rel   = (int)(int16_t)(uint16_t)(world - cam);
        g_ws_obj_true_rel  = (int16_t)rel;
        g_ws_obj_rel8      = (uint8_t)(rel & 0xFF);
        g_ws_obj_ctx_valid = 1;
        /* g_cpu.Y = rel slot (the STA $03AD,Y follows at $F17C); remember
         * the bias per slot so later rel-var reads can re-arm it. */
        if (g_cpu.Y < SMB_WS_REL_SLOTS) {
            s_ws_rel16_tab[g_cpu.Y] = (int16_t)rel;
            s_ws_rel8_tab[g_cpu.Y]  = (uint8_t)(rel & 0xFF);
            s_ws_rel_mask |= (uint8_t)(1u << g_cpu.Y);
        }
        return val;
    }

    /* ---- Draw-cull: GetXOffscreenBits edge reads (indexed) ----
     * $F1FA: LDA ScreenEdge_X_Pos,y  → addr $071D (right) / $071C (left)
     * $F202: LDA ScreenEdge_PageLoc,y → addr $071B / $071A
     * Widening both edges makes the game's own column-cull algebra treat
     * the margins as on-screen, so sprites there are neither parked at
     * Y=$F8 nor column-suppressed. */
    case 0xF1FA:
        if (addr == 0x071D) return ws_shift_lo(val, +s_ws_right, &s_ws_pend_bits);
        if (addr == 0x071C) return ws_shift_lo(val, -s_ws_left,  &s_ws_pend_bits);
        return val;
    case 0xF202:
        if (addr == 0x071B || addr == 0x071A)
            return ws_shift_hi(val, &s_ws_pend_bits);
        return val;

    /* ---- Despawn: OffscreenBoundsCheck ($D67A) ----
     * Left bound camera-72 shifts left by the left margin; right bound
     * ScreenRight+72 shifts right by the right margin.  The vanilla 72px
     * cushion is preserved on both sides. */
    case 0xD680: return ws_shift_lo(val, -s_ws_left,  &s_ws_pend_despawn);
    case 0xD693: return ws_shift_hi(val, &s_ws_pend_despawn);
    case 0xD69A: return ws_shift_lo(val, +s_ws_right, &s_ws_pend_despawn);
    case 0xD6A1: return ws_shift_hi(val, &s_ws_pend_despawn);

    /* ---- Enemy spawn window: CheckRightBounds ($C164) ----
     * Spawn window is [ScreenRight, ScreenRight+0x30).  Shift both the
     * +0x30 lookahead base ($C164/$C16E) and the raw-edge compare
     * ($C1B6/$C1BB) by the right margin: enemies materialize just past
     * the widened edge instead of popping in mid-margin, and the gap to
     * the +72 despawn bound stays vanilla. */
    case 0xC164: return ws_shift_lo(val, +s_ws_right, &s_ws_pend_spawnb);
    case 0xC16E: return ws_shift_hi(val, &s_ws_pend_spawnb);
    case 0xC1B6: return ws_shift_lo(val, +s_ws_right, &s_ws_pend_spawnc);
    case 0xC1BB: return ws_shift_hi(val, &s_ws_pend_spawnc);

    /* ---- Enemy spawn PLACEMENT reads: serve VANILLA, never widened ----
     * $C5DA/$C5E2  frenzy:  Enemy_X = ScreenRight + 0x20, Enemy_Page = +carry
     * $C73C/$C741  group:   ScreenRight page/X -> temp $02/$03, copied into
     *                        every group member's PageLoc/X_Position.
     * Both compute WHERE an edge-relative enemy is born.  Widening
     * ScreenRight here pushed the spawn up to +right px deeper into the
     * world, sometimes inside a pipe/brick where the enemy has no
     * collision to escape and is stuck forever.  The 16:9 view is still
     * populated by the *eligibility* window reads ($C164/$C1B6, kept
     * widened above); placement must match vanilla so the enemy lands
     * exactly where the level's geometry allows — its 4:3 world position.
     * Verified pure-placement: each read flows only into an Enemy_X /
     * Enemy_PageLoc store, never a spawn-or-cull branch (super-mario-bros
     * _full.c $C5D8-$C5E9 PutAtRightExtent, $C73A-$C744 SetYGp). */
    case 0xC5DA:
    case 0xC5E2:
    case 0xC73C:
    case 0xC741:
        return val;

    /* Every other hooked read — player edge clamp ($B013/$B01C), loop
     * rewind ($C09C/$C0A5), parser gates, victory logic, bounding boxes —
     * stays vanilla by falling through. */
    default:
        return val;
    }
}

/* ---- Watchdog globals (set by watchdog.c, read by debug server) ---- */
int g_watchdog_triggered = 0;
uint64_t g_watchdog_frame = 0;
char g_watchdog_stack_dump[1024] = "";

/* ---- Debug frame record (SMB-specific) ---- */

void game_fill_frame_record(void *record) {
    NESFrameRecord *r = (NESFrameRecord *)record;
    /* Only fields whose smbdis label has been trace-verified for this
     * repo. Previous slots 4/6/7/8 were mislabeled ($001D and $0756
     * were name-swapped, and $075A/$075C/$075E were the wrong bytes
     * for world/level/area_type entirely). Consumers needing physics
     * state, power status, or true world/level should use read_ram
     * against the canonical addresses (see semcomp/SmbRamMap.h). */
    r->game_data[0] = g_ram[0x0770];  /* OperMode */
    r->game_data[1] = g_ram[0x0772];  /* OperMode_Task */
    r->game_data[2] = g_ram[0x0086];  /* Player_X_Position */
    r->game_data[3] = g_ram[0x00CE];  /* Player_Y_Position */
    r->game_data[4] = g_ram[0x0009];  /* FrameCounter */
    r->game_data[5] = g_ram[0x0776];  /* DemoActionTimer */
    /* slots 6..15 left at their zero-initialized state */
}

void game_post_render(uint32_t *framebuf) { (void)framebuf; }

/* ---- Debug command handler (SMB-specific) ---- */

int game_handle_debug_cmd(const char *cmd, int id, const char *json) {
    (void)json;

    if (strcmp(cmd, "smb_state") == 0) {
        /* Trace-verified fields only. The previous version of this
         * command exposed player_size/player_state/world/level/area_type
         * which were either name-swapped ($001D, $0756) or reading the
         * wrong byte entirely ($075A as world, $075C as level, $075E
         * as area_type). Consumers that need physics state, power
         * status, or actual world/level should use the read_ram
         * command against the canonical addresses; the semcomp facade
         * (semcomp/SmbRamMap.h) is the authoritative label source. */
        uint8_t oper_mode   = g_ram[0x0770];
        uint8_t oper_task   = g_ram[0x0772];
        uint8_t player_x    = g_ram[0x0086];
        uint8_t player_y    = g_ram[0x00CE];
        uint8_t score_hi    = g_ram[0x07FC];
        uint8_t score_mid   = g_ram[0x07FD];
        uint8_t score_lo    = g_ram[0x07FE];
        uint8_t lives       = g_ram[0x075A];
        uint8_t frame_ctr   = g_ram[0x0009];

        debug_server_send_fmt(
            "{\"id\":%d,\"cmd\":\"smb_state\","
            "\"oper_mode\":%d,\"oper_task\":%d,"
            "\"player_x\":%d,\"player_y\":%d,"
            "\"score_hi\":%d,\"score_mid\":%d,\"score_lo\":%d,"
            "\"lives\":%d,\"frame_counter\":%d}\n",
            id, oper_mode, oper_task,
            player_x, player_y,
            score_hi, score_mid, score_lo,
            lives, frame_ctr);
        return 1;
    }

    if (strcmp(cmd, "smb_ws_state") == 0) {
        /* Widescreen probe: config, gate, camera, and per-enemy true
         * screen X vs what the sidecar recorded. */
        int cam = ((int)g_ram[0x071A] << 8) | g_ram[0x071C];
        char enemies[512]; int ep = 0;
        enemies[0] = 0;
        for (int i = 0; i < 5; i++) {
            int world = ((int)g_ram[0x6E + i] << 8) | g_ram[0x87 + i];
            ep += snprintf(enemies + ep, sizeof(enemies) - ep,
                "%s{\"slot\":%d,\"flag\":%d,\"id\":%d,\"screen_x\":%d}",
                i ? "," : "", i, g_ram[0x0F + i], g_ram[0x16 + i],
                g_ram[0x0F + i] ? (int)(int16_t)(uint16_t)(world - cam) : 0);
        }
        debug_server_send_fmt(
            "{\"id\":%d,\"cmd\":\"smb_ws_state\","
            "\"enabled\":%d,\"left\":%d,\"right\":%d,"
            "\"eff_left\":%d,\"eff_right\":%d,\"sim_active\":%d,"
            "\"embed_detect\":%u,\"guard_frames\":%u,"
            "\"oper_mode\":%d,\"camera_x\":%d,\"enemies\":[%s]}\n",
            id, s_ws_enabled, s_ws_left, s_ws_right,
            g_ws_eff_left, g_ws_eff_right, ws_sim_active(),
            s_ws_embed_detect, s_ws_guard_frames,
            g_ram[0x0770], cam, enemies);
        return 1;
    }

    if (strcmp(cmd, "smb_demo_state") == 0) {
        uint8_t demo_timer  = g_ram[0x0776];
        uint8_t frame_ctr   = g_ram[0x0009];
        uint8_t oper_mode   = g_ram[0x0770];
        uint8_t oper_task   = g_ram[0x0772];

        debug_server_send_fmt(
            "{\"id\":%d,\"cmd\":\"smb_demo_state\","
            "\"demo_timer\":%d,\"frame_counter\":%d,"
            "\"oper_mode\":%d,\"oper_task\":%d}\n",
            id, demo_timer, frame_ctr,
            oper_mode, oper_task);
        return 1;
    }

    return 0;
}
