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

/* ---- game_extras.h implementation ---- */

uint32_t game_get_expected_crc32(void) { return 0xD445F698u; }

const char *game_get_name(void) { return "Super Mario Bros."; }

/*
 * Widescreen offscreen-bits hook: intercept writes to Enemy_OffscreenBits
 * ($03D1) and clear bits for enemies in the widescreen extension region.
 * This makes the game's own sprite drawing code include these enemies in OAM,
 * even though they're beyond the original 256px viewport. The g_oam_wide_x
 * override in the renderer then positions them correctly.
 */
static void offscreen_bits_hook(uint16_t addr, uint8_t old_val, uint8_t new_val) {
    (void)addr; (void)old_val;
    if (!g_widescreen_left && !g_widescreen_right) {
        g_ram[0x03D1] = new_val;
        return;
    }

    int cam_x = (int)g_ram[0x071A] * 256 + (int)g_ram[0x071C];

    /* For each enemy slot (bits 0-4 in the offscreen byte), check if the
     * enemy is within the widescreen region. If so, clear its offscreen bits.
     * The bit layout: each slot uses bits in the upper/lower nibble pattern. */
    uint8_t cleared = new_val;
    for (int i = 0; i < 5; i++) {
        if (g_ram[0x0F + i] == 0) continue; /* slot inactive */
        int world_x = (int)g_ram[0x6E + i] * 256 + (int)g_ram[0x87 + i];
        int screen_x = world_x - cam_x;

        /* If enemy is in the widescreen extension (either side), clear its bits */
        if ((screen_x >= -g_widescreen_left && screen_x < 0) ||
            (screen_x >= 256 && screen_x < 256 + g_widescreen_right + 16)) {
            /* SMB offscreen bits: bit (i) set = slot i is off-screen.
             * The actual bit layout uses both nibbles, but the key bits
             * for the 5 enemy slots are spread across the byte.
             * For simplicity, clear ALL bits — the game recomputes each frame. */
            cleared = 0x00;
            break;
        }
    }
    g_ram[0x03D1] = cleared;
}

void game_on_init(void) {
    /* ---- Widescreen: expand BG render to 480px ---- */
    /* SMB uses vertical mirroring (two side-by-side nametables = 512px).
     * The game writes new nametable columns 98-117px ahead of the 256px
     * right edge. Right extension capped at 96px to stay within this
     * proven write-ahead distance. Left extension is 128px.
     * Total: 480px (128 + 256 + 96). See WIDESCREEN.md for analysis.
     *
     * TODO: shadow area parser execution to support arbitrary width.
     * Requires correct VRAM buffer format parsing. See WIDESCREEN.md. */
    g_widescreen_left  = 128;
    g_widescreen_right = 96;
    g_render_width     = 256 + g_widescreen_left + g_widescreen_right;

    /* Hook Enemy_OffscreenBits writes to extend visibility into widescreen */
    g_write_bp_addr = 0x03D1;
    g_write_bp_callback = offscreen_bits_hook;
    g_write_bp_block = 1;  /* we write the value ourselves */

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

/*
 * Widescreen sprite positioning — compute true screen X for enemy sprites.
 *
 * The game calculates sprite X with 8-bit math, truncating positions beyond
 * 0-255. We recompute the true screen X from enemy world coordinates and
 * store it in g_oam_wide_x[] so the renderer can place sprites correctly
 * in the widescreen extension regions.
 *
 * SMB RAM layout used:
 *   $000F+i  Enemy_Flag (5 enemy slots, i=0..4)
 *   $006E+i  Enemy_PageLoc
 *   $0087+i  Enemy_X_Position
 *   $06E5+i  Enemy_SprDataOffset (OAM byte offset for this enemy's sprites)
 *   $071A    ScreenLeft_PageLoc
 *   $071C    ScreenLeft_X_Pos
 *   Player uses similar addresses at fixed offsets (slot index implicit).
 */
/* DISABLED — OAM slot mapping is unreliable, causes flickering/ghosts.
 * See session handoff for analysis of what went wrong and what to try next. */
static void compute_widescreen_sprite_x(void) {
    (void)0; /* no-op for now */
}

void game_post_nmi(uint64_t frame_count) {
    (void)frame_count;
    if (s_debug_enabled) {
        debug_server_record_frame();
        debug_server_check_watchpoints();
    }
    compute_widescreen_sprite_x();
}

int game_handle_arg(const char *key, const char *val) {
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
    return "  --tcp-port PORT     TCP debug server port (default 4370)\n"
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
            debug_server_check_watchpoints();

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

/*
 * Widescreen enemy lifecycle hooks.
 *
 * Problem: the game's spawn lookahead and offscreen bounds are sized for a
 * 256px viewport.  With widescreen (128L + 256C + 96R = 480px), enemies
 * pop in/out visibly at the extended edges.
 *
 * Solution: at the SPECIFIC PCs that compute spawn/despawn boundaries,
 * shift the screen-edge values so the 6502 math produces wider thresholds.
 * All other reads of these addresses return the original value unchanged.
 *
 * The 16-bit screen position is read in two parts (X low, Page high).
 * When we shift X, overflow/underflow must carry to the subsequent Page read.
 * We pass this via s_ws_extra_carry (set by X hook, consumed by Page hook).
 *
 * Decision PCs (from lifecycle analysis):
 *   Spawn lookahead:   $C164 reads $071D, $C16E reads $071B
 *   Despawn left:      $D680 reads $071C, $D693 reads $071A
 *   Despawn right:     $D69A reads $071D, $D6A1 reads $071B
 */
static int8_t s_ws_extra_carry = 0;  /* +1 carry or -1 borrow from X hook */

uint8_t game_ram_read_hook(uint16_t pc, uint16_t addr, uint8_t val) {
    if (!g_widescreen_right && !g_widescreen_left)
        return val;

    switch (addr) {
    case 0x071D: /* ScreenRight_X_Pos */
        /* NOTE: spawn lookahead ($C164) intentionally NOT hooked.
         * Widening the spawn lookahead causes enemies to start their AI
         * too early — they walk into pipes and wrong positions before
         * the screen reaches them. Spawn timing must stay original. */
        if (pc == 0xD69A) {
            /* Despawn right bound: keep enemies alive further right */
            uint16_t wide = (uint16_t)val + g_widescreen_right;
            s_ws_extra_carry = (wide > 0xFF) ? 1 : 0;
            return (uint8_t)(wide & 0xFF);
        }
        break;

    case 0x071B: /* ScreenRight_PageLoc */
        if (pc == 0xD6A1) {
            /* Page follow-up for despawn right bound */
            uint8_t ret = val + s_ws_extra_carry;
            s_ws_extra_carry = 0;
            return ret;
        }
        break;

    case 0x071C: /* ScreenLeft_X_Pos */
        if (pc == 0xD680) {
            /* Despawn left bound: shift left edge further left */
            int16_t wide = (int16_t)val - g_widescreen_left;
            s_ws_extra_carry = (wide < 0) ? -1 : 0;
            return (uint8_t)(wide & 0xFF);
        }
        break;

    case 0x071A: /* ScreenLeft_PageLoc */
        if (pc == 0xD693) {
            /* Page follow-up for despawn left bound */
            uint8_t ret = val + s_ws_extra_carry;  /* -1 borrow or 0 */
            s_ws_extra_carry = 0;
            return ret;
        }
        break;
    }

    return val;
}

/* ---- Watchdog globals (set by watchdog.c, read by debug server) ---- */
int g_watchdog_triggered = 0;
uint64_t g_watchdog_frame = 0;
char g_watchdog_stack_dump[1024] = "";

/* ---- Debug frame record (SMB-specific) ---- */

void game_fill_frame_record(void *record) {
    NESFrameRecord *r = (NESFrameRecord *)record;
    r->game_data[0] = g_ram[0x0770];  /* OperMode */
    r->game_data[1] = g_ram[0x0772];  /* OperMode_Task */
    r->game_data[2] = g_ram[0x0086];  /* Player_X_Position */
    r->game_data[3] = g_ram[0x00CE];  /* Player_Y_Position */
    r->game_data[4] = g_ram[0x001D];  /* PlayerSize (0=big, 1=small) */
    r->game_data[5] = g_ram[0x0009];  /* FrameCounter */
    r->game_data[6] = g_ram[0x0756];  /* Player_State */
    r->game_data[7] = g_ram[0x075A];  /* WorldNumber */
    r->game_data[8] = g_ram[0x075C];  /* LevelNumber */
    r->game_data[9] = g_ram[0x0776];  /* DemoActionTimer */
}

void game_post_render(uint32_t *framebuf) { (void)framebuf; }

/* ---- Debug command handler (SMB-specific) ---- */

int game_handle_debug_cmd(const char *cmd, int id, const char *json) {
    (void)json;

    if (strcmp(cmd, "smb_state") == 0) {
        uint8_t oper_mode   = g_ram[0x0770];
        uint8_t oper_task   = g_ram[0x0772];
        uint8_t world       = g_ram[0x075A];
        uint8_t level       = g_ram[0x075C];
        uint8_t player_x    = g_ram[0x0086];
        uint8_t player_y    = g_ram[0x00CE];
        uint8_t player_size = g_ram[0x001D];
        uint8_t player_state = g_ram[0x0756];
        uint8_t area_type   = g_ram[0x075E];
        uint8_t score_hi    = g_ram[0x07FC];
        uint8_t score_mid   = g_ram[0x07FD];
        uint8_t score_lo    = g_ram[0x07FE];
        uint8_t lives       = g_ram[0x075A];
        uint8_t frame_ctr   = g_ram[0x0009];

        debug_server_send_fmt(
            "{\"id\":%d,\"cmd\":\"smb_state\","
            "\"oper_mode\":%d,\"oper_task\":%d,"
            "\"world\":%d,\"level\":%d,"
            "\"player_x\":%d,\"player_y\":%d,"
            "\"player_size\":%d,\"player_state\":%d,"
            "\"area_type\":%d,"
            "\"score_hi\":%d,\"score_mid\":%d,\"score_lo\":%d,"
            "\"lives\":%d,\"frame_counter\":%d}\n",
            id, oper_mode, oper_task,
            world, level,
            player_x, player_y,
            player_size, player_state,
            area_type,
            score_hi, score_mid, score_lo,
            lives, frame_ctr);
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
