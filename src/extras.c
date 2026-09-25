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
#include "game_coop.h"
#include "nes_runtime.h"
#include "nes_video.h"
#include "config.h"
#include "input_script.h"
#include "debug_server.h"
#include "verify_mode.h"
#include "game_voxel.h"
#include "game_widescreen.h"
#include "smb_ws_actors.h"
#include "game_smash64.h"
#include "game_smash64_render.h"
#include "game_link.h"
#include "game_samus.h"
#include "game_sonic.h"
#include "watchdog.h"
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
    const char *env = getenv("NESRECOMP_DEBUG");
    if (s_debug_enabled) return 1;
    if (env && env[0] && strcmp(env, "0") != 0) return 1;
    get_exe_relative_path("debug.ini", path, sizeof(path));
    FILE *f = fopen(path, "r");
    if (f) { fclose(f); return 1; }
    return 0;
}

/* ---- Debug server state ---- */
static int s_tcp_port = 4370;
static int s_debug_server_started = 0;

/* ROM path exposed by runner for verify mode init */
const char *g_rom_path_for_extras = NULL;

static void start_debug_server_once(void) {
    if (s_debug_server_started) return;
    debug_server_init(s_tcp_port);
    s_debug_server_started = 1;
}

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
static int suppress_replaced_sprite(int slot,int x,int y,void *user) {
    (void)user;
    return game_coop_suppress_sprite(slot) || game_smash64_render_suppress_sprite(slot,x,y) || smb_ws_actors_suppress_sprite(slot);
}

uint32_t game_get_expected_crc32(void) { return 0xD445F698u; }

const char *game_get_name(void) { return "Super Mario Bros."; }

void game_on_init(void) {
    watchdog_frame_start();
    /* The package resolver excludes these combinations in the launcher.
       Apply the same rule after trace-only command-line overrides. */
    if (game_coop_enabled()) {
        game_widescreen_set_mod_enabled(0);
        game_voxel_set_mod_enabled(0);
        game_smash64_set_mod_enabled(0, NULL);
        game_link_set_enabled(0, NULL);
        game_samus_set_enabled(0, NULL);
        game_sonic_set_enabled(0, NULL);
        g_nes_config.widescreen = 0;
    }
    game_widescreen_init();
    game_voxel_init();
    game_smash64_init();
    game_smash64_render_init();
    ppu_renderer_set_sprite_suppress(suppress_replaced_sprite,NULL);

    s_debug_enabled = check_debug_ini();

    if (s_debug_enabled) {
        printf("[Debug] debug.ini found — TCP server and verify mode enabled\n");
        start_debug_server_once();

        if (g_run_mode != RUN_MODE_NATIVE && g_rom_path_for_extras) {
            verify_mode_init(g_rom_path_for_extras);
        }
    } else if (g_run_mode != RUN_MODE_NATIVE) {
        /* --verify or --emulated implies debug even without ini */
        s_debug_enabled = 1;
        start_debug_server_once();
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
    game_coop_before_frame();
    game_voxel_update_input();
    /* Player replacement samples input and ticks its controller before NMI,
     * so the fighter's intent for this frame exists before SMB1 runs. */
    game_smash64_update_input(frame_count);
    game_link_update_input(frame_count);
    game_samus_update_input(frame_count);
    game_sonic_update_input(frame_count);
    /* Start timing only after any TCP/debug pause has ended.  Previously the
     * watchdog's zero-initialized timestamp measured process lifetime and
     * eventually blamed an ordinary backward branch (often ReadPortBits). */
    watchdog_frame_start();
    game_widescreen_begin_frame();
}

void game_post_nmi(uint64_t frame_count) {
    (void)frame_count;
    game_widescreen_update();
    game_voxel_update();
    game_smash64_update(frame_count);
    game_link_update(frame_count);
    game_samus_update(frame_count);
    game_sonic_update(frame_count);
    if (s_debug_enabled) {
        debug_server_record_frame();
    }
}

int game_handle_arg(const char *key, const char *val) {
    if (game_coop_arg(key, val)) return 1;
    if (game_widescreen_arg(key, val)) return 1;
    if (strcmp(key, "--tcp-port") == 0 && val) {
        s_tcp_port = atoi(val);
        s_debug_enabled = 1;
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
    return "  --widescreen SPEC   Custom widescreen: fit,16:9,21:9,32:9,off\n"
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
    return game_smash64_ram_read_hook(pc, addr, val);
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

void game_post_render(uint32_t *framebuf) {
    game_voxel_post_render(framebuf);
    game_smash64_render_post_render(framebuf);
    game_link_render_post_render(framebuf);
    game_samus_render_post_render(framebuf);
    game_sonic_render_post_render(framebuf);
    game_coop_render(framebuf);
}

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

    if (game_coop_debug(cmd, id, json)) return 1;
    if (game_widescreen_debug(cmd, id)) return 1;

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
