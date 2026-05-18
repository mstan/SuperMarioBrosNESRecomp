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
#ifdef ENABLE_SEMCOMP
#include "semcomp/Runtime.h"
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
static int s_trainer_enabled = 0;

/* ROM path exposed by runner for verify mode init */
const char *g_rom_path_for_extras = NULL;

/* ---- Minimal JSON arg helpers (mirrors debug_server.c) ---- */

static const char *extras_json_get_str(const char *json, const char *key,
                                       char *out, int out_sz) {
    char pat[128];
    snprintf(pat, sizeof(pat), "\"%s\"", key);
    const char *p = strstr(json, pat);
    if (!p) return NULL;
    p += strlen(pat);
    while (*p == ' ' || *p == ':') p++;
    if (*p == '"') {
        p++;
        int i = 0;
        while (*p && *p != '"' && i < out_sz - 1) out[i++] = *p++;
        out[i] = '\0';
        return out;
    }
    int i = 0;
    while (*p && *p != ',' && *p != '}' && *p != ' ' && i < out_sz - 1)
        out[i++] = *p++;
    out[i] = '\0';
    return out;
}

static int extras_json_get_int(const char *json, const char *key, int def) {
    char buf[64];
    if (!extras_json_get_str(json, key, buf, sizeof(buf))) return def;
    /* Accept decimal, 0xNN, or $NN. */
    if (buf[0] == '$') return (int)strtoul(buf + 1, NULL, 16);
    if (buf[0] == '0' && (buf[1] == 'x' || buf[1] == 'X'))
        return (int)strtoul(buf + 2, NULL, 16);
    return atoi(buf);
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

uint32_t game_get_expected_crc32(void) { return 0xD445F698u; }

const char *game_get_name(void) { return "Super Mario Bros."; }

void game_on_init(void) {
    s_debug_enabled = check_debug_ini();

    /* --trainer implies debug too (the trainer rides on top of the TCP
     * command surface). */
    if (s_trainer_enabled && !s_debug_enabled) {
        s_debug_enabled = 1;
        printf("[Trainer] --trainer implied --debug; TCP server enabled\n");
    }

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

#ifdef ENABLE_SEMCOMP
    semcomp_runtime_init();
    semcomp_runtime_set_trainer_enabled(s_trainer_enabled);
    if (s_trainer_enabled) {
        printf("[Trainer] active — freeze table will be applied post-NMI\n");
    }
#endif
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
#ifdef ENABLE_SEMCOMP
    /* Trainer overlay polls keyboard (F8, arrows, etc.). When the
     * overlay is visible we zero the controller bytes so arrow-key
     * navigation doesn't also move Mario. */
    semcomp_runtime_trainer_ui_tick();
    if (semcomp_runtime_trainer_ui_grabbing_input()) {
        g_controller1_buttons = 0;
    }
#endif
}

void game_post_nmi(uint64_t frame_count) {
    (void)frame_count;
    if (s_debug_enabled) {
        debug_server_record_frame();
    }
#ifdef ENABLE_SEMCOMP
    /* Apply trainer freezes AFTER the game's frame update so the
     * trainer's writes are not stomped by the game's own writes within
     * the same frame. No-op when --trainer was not passed. */
    semcomp_runtime_apply_trainer();
#endif
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
    if (strcmp(key, "--trainer") == 0) {
        s_trainer_enabled = 1;
        return 1;
    }
    return 0;
}

const char *game_arg_usage(void) {
    return "  --tcp-port PORT     TCP debug server port (default 4370)\n"
           "  --verify            Enable dual-execution verify mode (Nestopia oracle)\n"
           "  --emulated          Run purely via Nestopia emulator (no recompiled code)\n"
           "  --trainer           Enable semcomp trainer (freeze/set RAM via TCP;\n"
           "                      tools/trainer.py is the companion REPL)\n";
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

/* ---- Phase 3 replace_func shims ----
 * game.toml's [[replace_func]] suppresses generated bodies for these PCs;
 * the dispatch table and JSR call sites still reference func_XXXX_b0, so we
 * supply the symbol here and forward to the semantic implementation.
 * Unconditional — replace_func runs at recomp time regardless of
 * ENABLE_SEMCOMP, so the symbol must exist. Building with ENABLE_SEMCOMP=OFF
 * yields a deliberate link error against semcomp_runtime_give_coin. */
void func_BBFE_b0(void) { /* GiveOneCoin */
    semcomp_runtime_give_coin();
}

/* BumpBlock $BD9B deferred — sub-handlers MushFlowerBlock / VineBlock
 * live as inner labels in the recompiler's emission and can't be
 * resolved when BumpBlock is replace_func'd. See game.toml comment. */

void func_BC49_b0(void) { /* SetupPowerUp */
    semcomp_runtime_setup_powerup_replacement();
}

void func_8182_b0(void) { /* PauseRoutine */
    semcomp_runtime_pause_tick();
}

void func_8F06_b0(void) { /* PrintStatusBarNumbers */
    semcomp_runtime_print_status_bar_numbers();
}

void func_BC27_b0(void) { /* AddToScore */
    semcomp_runtime_add_to_score();
}

void func_DA11(void) { /* SetupFloateyNumber (no _b0 suffix — fixed bank) */
    semcomp_runtime_setup_floatey_number();
}

void func_C30E(void) { /* InitNormalEnemy (no _b0 suffix — fixed bank) */
    semcomp_runtime_init_normal_enemy();
}

void func_CA77(void) { /* MoveNormalEnemy (no _b0 suffix — fixed bank) */
    semcomp_runtime_move_normal_enemy();
}

void func_B0E6_b0(void) { /* AutoControlPlayer */
    semcomp_runtime_auto_control_player();
}

void func_B329_b0(void) { /* PlayerMovementSubs */
    semcomp_runtime_player_movement_subs();
}

void func_B233_b0(void) { /* PlayerChangeSize */
    semcomp_runtime_player_change_size();
}

void func_B245_b0(void) { /* PlayerInjuryBlink */
    semcomp_runtime_player_injury_blink();
}

void func_B269_b0(void) { /* PlayerDeath */
    semcomp_runtime_player_death();
}

void func_B27D_b0(void) { /* PlayerFireFlower */
    semcomp_runtime_player_fire_flower();
}

void func_B35A_b0(void) { /* OnGroundStateSub */
    semcomp_runtime_on_ground_state_sub();
}

void func_B36D_b0(void) { /* FallingSub */
    semcomp_runtime_falling_sub();
}

void func_B376_b0(void) { /* JumpSwimSub */
    semcomp_runtime_jump_swim_sub();
}

void func_B3CF_b0(void) { /* ClimbingSub */
    semcomp_runtime_climbing_sub();
}

void func_B450_b0(void) { /* PlayerPhysicsSub */
    semcomp_runtime_physics_sub();
}

void func_B200_b0(void) { /* MovePlayerYAxis */
    semcomp_runtime_move_player_y_axis();
}

void func_BF09_b0(void) { /* MovePlayerHorizontally */
    semcomp_runtime_move_player_horizontally();
}

void func_BF4C_b0(void) { /* ExXMove */
    semcomp_runtime_ex_x_move();
}

void func_BF4D_b0(void) { /* MovePlayerVertically */
    semcomp_runtime_move_player_vertically();
}

void func_DC64(void) { /* PlayerBGCollision (no _b0 suffix — fixed bank) */
    semcomp_runtime_player_bg_collision();
}

/* Phase 17 — Player graphics shims. All multi-entry-body entries owned. */
void func_85F1_b0(void) { semcomp_runtime_get_player_colors(); }
void func_EFDC(void)    { semcomp_runtime_draw_player_loop(); }
void func_F12A(void)    { semcomp_runtime_relative_player_position(); }
void func_F12C(void)    { semcomp_runtime_relative_player_position_f12c(); }
void func_EFA4(void)    { semcomp_runtime_draw_player_intermediate(); }
void func_EFA6(void)    { semcomp_runtime_draw_player_intermediate_pintloop(); }
void func_EFAC(void)    { semcomp_runtime_draw_player_intermediate_efac(); }
void func_EEE9(void)    { semcomp_runtime_player_gfx_handler(); }
void func_EEF7(void)    { semcomp_runtime_player_gfx_handler_eef7(); }
void func_EF85(void)    { semcomp_runtime_player_gfx_handler_ef85(); }
void func_EEFC(void)    { semcomp_runtime_player_gfx_handler_eefc(); }
void func_EEFE(void)    { semcomp_runtime_player_gfx_handler_eefe(); }
void func_EEEE(void)    { semcomp_runtime_player_gfx_handler_eeee(); }
void func_EEF0(void)    { semcomp_runtime_player_gfx_handler_eef0(); }
void func_EEF1(void)    { semcomp_runtime_player_gfx_handler_eef1(); }
void func_EF10(void)    { semcomp_runtime_player_gfx_handler_ef10(); }
void func_EF01(void)    { semcomp_runtime_player_gfx_handler_ef01(); }
void func_EF42(void)    { semcomp_runtime_player_gfx_handler_ef42(); }
void func_EF7A(void)    { semcomp_runtime_player_gfx_handler_ef7a(); }
void func_EF97(void)    { semcomp_runtime_player_gfx_handler_ef97(); }

/* Phase 18 — Object handlers. */
void func_BC85_b0(void) { semcomp_runtime_powerup_obj_handler(); }
void func_B689_b0(void) { semcomp_runtime_fireball_obj_core(); }
void func_BB38_b0(void) { semcomp_runtime_coin_block(); }

/* Phase 19 — BumpBlock untangle. */
void func_BD9B_b0(void) { semcomp_runtime_bump_block(); }
void func_BDD2_b0(void) { semcomp_runtime_mush_flower_block(); }
void func_BDDF_b0(void) { semcomp_runtime_vine_block(); }
void func_BDD5_b0(void) { semcomp_runtime_star_block(); }
void func_BDD8_b0(void) { semcomp_runtime_extra_life_mush_block(); }

/* Phase 20 — HUD math untangle. */
void func_8F5F_b0(void) { semcomp_runtime_digits_math_routine(); }
void func_8F68_b0(void) { semcomp_runtime_add_mod_loop(); }
void func_8F75_b0(void) { semcomp_runtime_store_new_d(); }
void func_8F11_b0(void) { semcomp_runtime_output_numbers(); }

/* Phase 21 — Floatey per-frame untangle. */
void func_84C3_b0(void) { semcomp_runtime_floatey_per_frame(); }
void func_8534_b0(void) { semcomp_runtime_floatey_part_8534(); }

/* Phase 22 — Damage chain untangle. */
void func_D92C(void) { semcomp_runtime_injure_player(); }
void func_D931(void) { semcomp_runtime_force_injury(); }

void func_8231_b0(void) { /* TitleScreenMode */
    semcomp_runtime_title_screen_mode();
}

void func_AEDC_b0(void) { /* GameMode */
    semcomp_runtime_game_mode_tick();
}

void func_9218_b0(void) { /* GameOverMode */
    semcomp_runtime_game_over_mode();
}

uint8_t game_ram_read_hook(uint16_t pc, uint16_t addr, uint8_t val) {
    (void)pc; (void)addr; return val;
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
#ifdef ENABLE_SEMCOMP
    if (framebuf) {
        /* Framebuf is g_render_width * 240 ARGB8888 (game_extras.h:79).
         * The overlay positions itself within the left 256px so it stays
         * inside the 4:3 viewport even in widescreen builds. */
        semcomp_runtime_trainer_ui_render(framebuf, g_render_width, 240);
    }
#else
    (void)framebuf;
#endif
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

#ifdef ENABLE_SEMCOMP
    /* ---- Trainer commands (require --trainer) ---- */
    if (strcmp(cmd, "trainer_set") == 0) {
        int addr = extras_json_get_int(json, "addr", -1);
        int val  = extras_json_get_int(json, "val",  -1);
        if (addr < 0 || val < 0) {
            debug_server_send_fmt(
                "{\"id\":%d,\"ok\":false,\"error\":\"trainer_set requires addr,val\"}\n", id);
            return 1;
        }
        int ok = semcomp_runtime_trainer_set((uint16_t)addr, (uint8_t)val);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":%s,\"cmd\":\"trainer_set\",\"addr\":\"0x%04X\",\"val\":%d}\n",
            id, ok ? "true" : "false", addr & 0xFFFF, val & 0xFF);
        return 1;
    }
    if (strcmp(cmd, "trainer_freeze") == 0) {
        int addr = extras_json_get_int(json, "addr", -1);
        int val  = extras_json_get_int(json, "val",  -1);
        if (addr < 0 || val < 0) {
            debug_server_send_fmt(
                "{\"id\":%d,\"ok\":false,\"error\":\"trainer_freeze requires addr,val\"}\n", id);
            return 1;
        }
        int ok = semcomp_runtime_trainer_freeze((uint16_t)addr, (uint8_t)val);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":%s,\"cmd\":\"trainer_freeze\",\"addr\":\"0x%04X\",\"val\":%d,"
            "\"enabled\":%s}\n",
            id, ok ? "true" : "false", addr & 0xFFFF, val & 0xFF,
            semcomp_runtime_trainer_enabled() ? "true" : "false");
        return 1;
    }
    if (strcmp(cmd, "trainer_thaw") == 0) {
        int addr = extras_json_get_int(json, "addr", -1);
        if (addr < 0) {
            debug_server_send_fmt(
                "{\"id\":%d,\"ok\":false,\"error\":\"trainer_thaw requires addr\"}\n", id);
            return 1;
        }
        int ok = semcomp_runtime_trainer_thaw((uint16_t)addr);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":%s,\"cmd\":\"trainer_thaw\",\"addr\":\"0x%04X\"}\n",
            id, ok ? "true" : "false", addr & 0xFFFF);
        return 1;
    }
    if (strcmp(cmd, "trainer_list") == 0) {
        size_t n = semcomp_runtime_trainer_count();
        /* Send a streaming JSON array. Bounded to kMaxFreezeEntries=32. */
        char buf[2048];
        int off = snprintf(buf, sizeof(buf),
            "{\"id\":%d,\"cmd\":\"trainer_list\",\"enabled\":%s,\"count\":%zu,\"entries\":[",
            id, semcomp_runtime_trainer_enabled() ? "true" : "false", n);
        for (size_t i = 0; i < n && off < (int)sizeof(buf) - 64; ++i) {
            off += snprintf(buf + off, sizeof(buf) - off,
                "%s{\"addr\":\"0x%04X\",\"val\":%u}",
                i ? "," : "",
                semcomp_runtime_trainer_entry_addr(i),
                semcomp_runtime_trainer_entry_value(i));
        }
        /* Semantic freezes — one per known facade field. The list is
         * intentionally enumerated rather than auto-generated so each
         * field's addition is explicit in code. */
        off += snprintf(buf + off, sizeof(buf) - off, "],\"semantic\":[");
        int sem_count = 0;
        if (semcomp_runtime_is_mario_power_frozen()) {
            off += snprintf(buf + off, sizeof(buf) - off,
                "%s{\"name\":\"mario.power\",\"val\":%u}",
                sem_count++ ? "," : "",
                semcomp_runtime_frozen_mario_power_value());
        }
        if (semcomp_runtime_is_session_lives_frozen()) {
            off += snprintf(buf + off, sizeof(buf) - off,
                "%s{\"name\":\"session.lives\",\"val\":%u}",
                sem_count++ ? "," : "",
                semcomp_runtime_frozen_session_lives_value());
        }
        if (semcomp_runtime_is_session_coins_frozen()) {
            off += snprintf(buf + off, sizeof(buf) - off,
                "%s{\"name\":\"session.coins\",\"val\":%u}",
                sem_count++ ? "," : "",
                semcomp_runtime_frozen_session_coins_value());
        }
        snprintf(buf + off, sizeof(buf) - off, "]}\n");
        debug_server_send_fmt("%s", buf);
        return 1;
    }
    if (strcmp(cmd, "semcomp_mario") == 0) {
        /* The "via semcomp facade" read path. Compare against read_ram
         * of the same addresses to validate Mario's accessors. */
        debug_server_send_fmt(
            "{\"id\":%d,\"cmd\":\"semcomp_mario\","
            "\"x\":%u,\"y\":%u,\"page\":%u,\"world_x\":%u,"
            "\"x_velocity\":%d,\"y_velocity\":%d,\"x_speed_absolute\":%u,"
            "\"power\":%u,\"physics_state\":%u,\"on_ground\":%s,\"facing\":%u}\n",
            id,
            semcomp_runtime_mario_x(),
            semcomp_runtime_mario_y(),
            semcomp_runtime_mario_page(),
            semcomp_runtime_mario_world_x(),
            (int)semcomp_runtime_mario_x_velocity(),
            (int)semcomp_runtime_mario_y_velocity(),
            semcomp_runtime_mario_x_speed_absolute(),
            semcomp_runtime_mario_power(),
            semcomp_runtime_mario_physics_state(),
            semcomp_runtime_mario_on_ground() ? "true" : "false",
            semcomp_runtime_mario_facing());
        return 1;
    }
    if (strcmp(cmd, "semcomp_level") == 0) {
        debug_server_send_fmt(
            "{\"id\":%d,\"cmd\":\"semcomp_level\","
            "\"world\":%u,\"level\":%u,\"world_level_packed\":%u}\n",
            id,
            semcomp_runtime_level_world(),
            semcomp_runtime_level_level(),
            semcomp_runtime_level_world_level_packed());
        return 1;
    }
    if (strcmp(cmd, "semcomp_session") == 0) {
        debug_server_send_fmt(
            "{\"id\":%d,\"cmd\":\"semcomp_session\","
            "\"lives\":%u,\"coins\":%u}\n",
            id,
            semcomp_runtime_session_lives(),
            semcomp_runtime_session_coins());
        return 1;
    }

    /* ---- Semantic freeze/thaw TCP commands ---- */
    /* These route through C++ semantic methods so coupling logic
     * fires every frame (apply_freezes re-asserts via set_*).  The
     * coupling knowledge lives entirely in the C++ class — callers
     * just name the field. */
    if (strncmp(cmd, "semcomp_freeze_", 15) == 0) {
        int val = extras_json_get_int(json, "val", -1);
        if (val < 0 || val > 255) {
            debug_server_send_fmt(
                "{\"id\":%d,\"ok\":false,\"error\":\"semcomp_freeze_*: val 0-255 required\"}\n", id);
            return 1;
        }
        const char *field = cmd + 15;
        int handled = 1;
        if      (strcmp(field, "mario_power")    == 0) semcomp_runtime_freeze_mario_power((uint8_t)val);
        else if (strcmp(field, "session_lives")  == 0) semcomp_runtime_freeze_session_lives((uint8_t)val);
        else if (strcmp(field, "session_coins")  == 0) semcomp_runtime_freeze_session_coins((uint8_t)val);
        else handled = 0;
        if (handled) {
            debug_server_send_fmt(
                "{\"id\":%d,\"ok\":true,\"cmd\":\"%s\",\"val\":%d}\n", id, cmd, val);
        } else {
            debug_server_send_fmt(
                "{\"id\":%d,\"ok\":false,\"error\":\"unknown semantic field '%s'\"}\n",
                id, field);
        }
        return 1;
    }
    if (strncmp(cmd, "semcomp_thaw_", 13) == 0) {
        const char *field = cmd + 13;
        int handled = 1;
        if      (strcmp(field, "mario_power")    == 0) semcomp_runtime_thaw_mario_power();
        else if (strcmp(field, "session_lives")  == 0) semcomp_runtime_thaw_session_lives();
        else if (strcmp(field, "session_coins")  == 0) semcomp_runtime_thaw_session_coins();
        else handled = 0;
        if (handled) {
            debug_server_send_fmt(
                "{\"id\":%d,\"ok\":true,\"cmd\":\"%s\"}\n", id, cmd);
        } else {
            debug_server_send_fmt(
                "{\"id\":%d,\"ok\":false,\"error\":\"unknown semantic field '%s'\"}\n",
                id, field);
        }
        return 1;
    }

    /* ---- Semantic setter TCP commands ---- */
    /* Each routes through the C++ facade setter so coupled-byte logic
     * fires (e.g. Mario::set_power couples PlayerStatus + PlayerSize).
     * The trainer's trainer_set/freeze remain pure raw writes; these
     * are the explicit semantic alternative the GUI uses by default.
     *
     * The prefix `semcomp_set_*` is byte-tier (val 0..255). Commands that
     * accept a wider range (set_score, set_timer) are handled BELOW with
     * exact-match strcmp — so we skip the prefix block for them, else the
     * 0..255 clamp here would reject their inputs with a bogus
     * "unknown semantic field" error. */
    if (strncmp(cmd, "semcomp_set_", 12) == 0
            && strcmp(cmd, "semcomp_set_score") != 0
            && strcmp(cmd, "semcomp_set_timer") != 0) {
        int val = extras_json_get_int(json, "val", -1);
        if (val < 0 || val > 255) {
            debug_server_send_fmt(
                "{\"id\":%d,\"ok\":false,\"error\":\"semcomp_set_*: val 0-255 required\"}\n", id);
            return 1;
        }
        const char *field = cmd + 12;
        int handled = 1;
        if      (strcmp(field, "mario_x")             == 0) semcomp_runtime_set_mario_x((uint8_t)val);
        else if (strcmp(field, "mario_y")             == 0) semcomp_runtime_set_mario_y((uint8_t)val);
        else if (strcmp(field, "mario_page")          == 0) semcomp_runtime_set_mario_page((uint8_t)val);
        else if (strcmp(field, "mario_power")         == 0) semcomp_runtime_set_mario_power((uint8_t)val);
        else if (strcmp(field, "mario_physics_state") == 0) semcomp_runtime_set_mario_physics_state((uint8_t)val);
        else if (strcmp(field, "mario_facing")        == 0) semcomp_runtime_set_mario_facing((uint8_t)val);
        else if (strcmp(field, "session_lives")       == 0) semcomp_runtime_set_session_lives((uint8_t)val);
        else if (strcmp(field, "session_coins")       == 0) semcomp_runtime_set_session_coins((uint8_t)val);
        else handled = 0;
        if (handled) {
            debug_server_send_fmt(
                "{\"id\":%d,\"ok\":true,\"cmd\":\"%s\",\"val\":%d}\n",
                id, cmd, val);
        } else {
            debug_server_send_fmt(
                "{\"id\":%d,\"ok\":false,\"error\":\"unknown semantic field '%s'\"}\n",
                id, field);
        }
        return 1;
    }

    /* ---- Phase 3 routine replacement commands ----
     * semcomp_routine_list — list registered (replaced) routines with
     *   invocation counts. Useful for confirming a replacement actually
     *   fired during a workload.
     * semcomp_give_coin — directly call the semantic GiveOneCoin
     *   from outside the game's frame path. Equivalent to what a future
     *   replace_func wiring will do at $BBFE call sites; also exposed
     *   independently for trainer use (so set_session_coins-style
     *   helpers can grow into "actually grant a coin" behavior with
     *   full HUD refresh). */
    if (strcmp(cmd, "semcomp_routine_list") == 0) {
        /* debug_server_send_line appends "\n" after every call, so
         * multi-call response building emits one JSON fragment per line.
         * Build the whole response into a local buffer and emit once. */
        char buf[2048];
        int pos = snprintf(buf, sizeof(buf),
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_routine_list\",\"routines\":[",
            id);
        size_t n = semcomp_runtime_routine_count();
        for (size_t i = 0; i < n && pos < (int)sizeof(buf) - 1; i++) {
            uint16_t pc      = semcomp_runtime_routine_entry_pc(i);
            const char *name = semcomp_runtime_routine_entry_name(i);
            uint64_t calls   = semcomp_runtime_routine_entry_invocations(i);
            pos += snprintf(buf + pos, sizeof(buf) - pos,
                "%s{\"pc\":\"0x%04X\",\"name\":\"%s\",\"invocations\":%llu}",
                (i == 0) ? "" : ",", pc, name ? name : "",
                (unsigned long long)calls);
        }
        snprintf(buf + pos, sizeof(buf) - pos, "]}");
        debug_server_send_fmt("%s", buf);
        return 1;
    }
    if (strcmp(cmd, "semcomp_give_coin") == 0) {
        semcomp_runtime_give_coin();
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_give_coin\","
            "\"coin_tally\":%d,\"lives\":%d}\n",
            id, g_ram[0x075E], g_ram[0x075A]);
        return 1;
    }
    if (strcmp(cmd, "semcomp_add_coins") == 0) {
        int n = extras_json_get_int(json, "val", 1);
        if (n < 0)   n = 0;
        if (n > 255) n = 255;
        semcomp_runtime_add_coins((uint8_t)n);
        /* coin_tally echoed here is the LIVE byte at the moment of the
         * response — the trainer's grants drain one per frame (see
         * Runtime.cpp) so it lags by `queued`. Poll semcomp_session for
         * live state, or just wait queued/60 seconds. */
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_add_coins\","
            "\"n\":%d,\"coin_tally\":%d,\"lives\":%d,\"queued\":%u}\n",
            id, n, g_ram[0x075E], g_ram[0x075A],
            (unsigned)semcomp_runtime_pending_coin_grants());
        return 1;
    }
    if (strcmp(cmd, "semcomp_remove_coins") == 0) {
        int n = extras_json_get_int(json, "val", 1);
        if (n < 0)   n = 0;
        if (n > 255) n = 255;
        semcomp_runtime_remove_coins((uint8_t)n);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_remove_coins\","
            "\"n\":%d,\"coin_tally\":%d}\n",
            id, n, g_ram[0x075E]);
        return 1;
    }
    if (strcmp(cmd, "semcomp_add_lives") == 0) {
        int n = extras_json_get_int(json, "val", 1);
        if (n < 0)   n = 0;
        if (n > 255) n = 255;
        semcomp_runtime_add_lives((uint8_t)n);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_add_lives\","
            "\"n\":%d,\"lives\":%d}\n",
            id, n, g_ram[0x075A]);
        return 1;
    }
    if (strcmp(cmd, "semcomp_remove_lives") == 0) {
        int n = extras_json_get_int(json, "val", 1);
        if (n < 0)   n = 0;
        if (n > 255) n = 255;
        semcomp_runtime_remove_lives((uint8_t)n);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_remove_lives\","
            "\"n\":%d,\"lives\":%d}\n",
            id, n, g_ram[0x075A]);
        return 1;
    }
    /* Score has a 10-point quantum in SMB — the last digit is always 0
     * on the HUD because the game only adds multiples of 10 (and 100 /
     * 200 / 400 etc). To keep both TCP arg and GUI input compact, the
     * `val` here is "tens of points": val=5 → 50 points, val=100 →
     * 1000 points. The response echoes the real point delta so callers
     * don't have to unscale. */
    if (strcmp(cmd, "semcomp_set_score") == 0) {
        int v = extras_json_get_int(json, "val", 0);
        if (v < 0)       v = 0;
        if (v > 99999)   v = 99999;       /* 99999 * 10 = 999990, fits 6 digits */
        uint32_t points = (uint32_t)v * 10u;
        semcomp_runtime_set_score(points);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_set_score\","
            "\"val\":%d,\"points\":%u,\"score\":%u}\n",
            id, v, (unsigned)points, (unsigned)semcomp_runtime_get_score());
        return 1;
    }
    if (strcmp(cmd, "semcomp_add_score") == 0) {
        int d = extras_json_get_int(json, "val", 0);
        if (d < -99999) d = -99999;
        if (d >  99999) d =  99999;
        int32_t points_delta = (int32_t)d * 10;
        semcomp_runtime_add_score(points_delta);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_add_score\","
            "\"val\":%d,\"points_delta\":%d,\"score\":%u}\n",
            id, d, (int)points_delta, (unsigned)semcomp_runtime_get_score());
        return 1;
    }
    if (strcmp(cmd, "semcomp_set_timer") == 0) {
        int v = extras_json_get_int(json, "val", 0);
        if (v < 0)   v = 0;
        if (v > 999) v = 999;
        semcomp_runtime_set_timer((uint16_t)v);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_set_timer\",\"val\":%d,"
            "\"timer\":%u}\n",
            id, v, (unsigned)semcomp_runtime_get_timer());
        return 1;
    }
    if (strcmp(cmd, "semcomp_add_timer") == 0) {
        int d = extras_json_get_int(json, "val", 0);
        if (d < -999) d = -999;
        if (d >  999) d =  999;
        semcomp_runtime_add_timer((int16_t)d);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_add_timer\",\"delta\":%d,"
            "\"timer\":%u}\n",
            id, d, (unsigned)semcomp_runtime_get_timer());
        return 1;
    }
    if (strcmp(cmd, "semcomp_give_power_up") == 0) {
        int changed = semcomp_runtime_give_power_up();
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_give_power_up\","
            "\"changed\":%d,\"power\":%d}\n",
            id, changed, g_ram[0x0756]);
        return 1;
    }
    if (strcmp(cmd, "semcomp_take_damage") == 0) {
        int changed = semcomp_runtime_take_damage();
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_take_damage\","
            "\"changed\":%d,\"power\":%d}\n",
            id, changed, g_ram[0x0756]);
        return 1;
    }

    /* ---- Enemy commands (Phase 3+) ----
     * The "enemies" concept is a new semcomp abstraction over SMB's
     * parallel per-byte enemy arrays at $000F+/$0016+/$001E+/... etc.
     * Reads list active slots; bulk verbs invoke the natural in-game
     * KillEnemy ($E18E) / EnemyStomped ($D969) routines via
     * call_by_address with X = slot. */
    if (strcmp(cmd, "semcomp_enemies") == 0) {
        /* List all 5 slots with active state + key fields. Single
         * send_fmt to avoid the debug_server_send_line per-call
         * newline-fragmenting issue. */
        char buf[1024];
        int pos = snprintf(buf, sizeof(buf),
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_enemies\","
            "\"active_count\":%d,\"slots\":[",
            id, semcomp_runtime_enemy_active_count());
        for (int i = 0; i < 5 && pos < (int)sizeof(buf) - 1; i++) {
            int active = semcomp_runtime_enemy_active((uint8_t)i);
            pos += snprintf(buf + pos, sizeof(buf) - pos,
                "%s{\"slot\":%d,\"active\":%s",
                (i == 0) ? "" : ",", i, active ? "true" : "false");
            if (active) {
                pos += snprintf(buf + pos, sizeof(buf) - pos,
                    ",\"id\":%u,\"state\":%u,\"world_x\":%u,\"y\":%u,"
                    "\"x_vel\":%d,\"y_vel\":%d",
                    (unsigned)semcomp_runtime_enemy_id((uint8_t)i),
                    (unsigned)semcomp_runtime_enemy_state((uint8_t)i),
                    (unsigned)semcomp_runtime_enemy_world_x((uint8_t)i),
                    (unsigned)semcomp_runtime_enemy_y((uint8_t)i),
                    (int)semcomp_runtime_enemy_x_velocity((uint8_t)i),
                    (int)semcomp_runtime_enemy_y_velocity((uint8_t)i));
            }
            pos += snprintf(buf + pos, sizeof(buf) - pos, "}");
        }
        snprintf(buf + pos, sizeof(buf) - pos, "]}");
        debug_server_send_fmt("%s", buf);
        return 1;
    }
    if (strcmp(cmd, "semcomp_kill_all_enemies") == 0) {
        int n = semcomp_runtime_kill_all_enemies();
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_kill_all_enemies\","
            "\"killed\":%d}\n", id, n);
        return 1;
    }
    if (strcmp(cmd, "semcomp_stomp_all_enemies") == 0) {
        int n = semcomp_runtime_stomp_all_enemies();
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_stomp_all_enemies\","
            "\"stomped\":%d}\n", id, n);
        return 1;
    }
    if (strcmp(cmd, "semcomp_freeze_enemies") == 0) {
        int n = semcomp_runtime_freeze_enemies();
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_freeze_enemies\","
            "\"frozen\":%d}\n", id, n);
        return 1;
    }
    if (strcmp(cmd, "semcomp_kill_enemy") == 0) {
        int slot = extras_json_get_int(json, "slot", -1);
        if (slot < 0 || slot > 4) {
            debug_server_send_fmt(
                "{\"id\":%d,\"ok\":false,\"error\":\"slot must be 0..4\"}\n", id);
            return 1;
        }
        int n = semcomp_runtime_kill_enemy((uint8_t)slot);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_kill_enemy\","
            "\"slot\":%d,\"killed\":%d}\n", id, slot, n);
        return 1;
    }
    if (strcmp(cmd, "semcomp_stomp_enemy") == 0) {
        int slot = extras_json_get_int(json, "slot", -1);
        if (slot < 0 || slot > 4) {
            debug_server_send_fmt(
                "{\"id\":%d,\"ok\":false,\"error\":\"slot must be 0..4\"}\n", id);
            return 1;
        }
        int n = semcomp_runtime_stomp_enemy((uint8_t)slot);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_stomp_enemy\","
            "\"slot\":%d,\"stomped\":%d}\n", id, slot, n);
        return 1;
    }

    /* ---- Camera (Phase 4) ---- */
    if (strcmp(cmd, "semcomp_camera") == 0) {
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_camera\","
            "\"left_world_x\":%u,\"right_world_x\":%u,\"locked\":%s}\n",
            id,
            (unsigned)semcomp_runtime_camera_left_world_x(),
            (unsigned)semcomp_runtime_camera_right_world_x(),
            semcomp_runtime_camera_is_locked() ? "true" : "false");
        return 1;
    }
    if (strcmp(cmd, "semcomp_camera_lock") == 0) {
        semcomp_runtime_camera_lock();
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_camera_lock\"}\n", id);
        return 1;
    }
    if (strcmp(cmd, "semcomp_camera_unlock") == 0) {
        semcomp_runtime_camera_unlock();
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_camera_unlock\"}\n", id);
        return 1;
    }
    if (strcmp(cmd, "semcomp_camera_set_world_x") == 0) {
        int wx = extras_json_get_int(json, "val", 0);
        if (wx < 0)       wx = 0;
        if (wx > 0xFFFF)  wx = 0xFFFF;
        semcomp_runtime_camera_set_world_x((uint16_t)wx);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_camera_set_world_x\","
            "\"world_x\":%d}\n", id, wx);
        return 1;
    }

    /* ---- World verbs (Phase 4): blocks, power-ups, floateys ---- */
    if (strcmp(cmd, "semcomp_bump_block") == 0) {
        int code = extras_json_get_int(json, "val", 4);  /* 4 = brick */
        if (code < 0 || code > 8) code = 4;
        semcomp_runtime_bump_block_under_mario((uint8_t)code);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_bump_block\","
            "\"block_code\":%d}\n", id, code);
        return 1;
    }
    if (strcmp(cmd, "semcomp_spawn_powerup") == 0) {
        int type = extras_json_get_int(json, "val", 0);  /* 0 = mushroom */
        if (type < 0 || type > 3) type = 0;
        semcomp_runtime_spawn_powerup((uint8_t)type);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_spawn_powerup\","
            "\"type\":%d}\n", id, type);
        return 1;
    }
    if (strcmp(cmd, "semcomp_spawn_floatey") == 0) {
        int idx = extras_json_get_int(json, "val", 0);  /* 0 = 100 pts */
        if (idx < 0) idx = 0;
        if (idx > 9) idx = 9;
        uint8_t used = semcomp_runtime_spawn_floatey((uint8_t)idx);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_spawn_floatey\","
            "\"index\":%u}\n", id, (unsigned)used);
        return 1;
    }

    /* ---- GameMode (Phase 5) ---- */
    if (strcmp(cmd, "semcomp_mode") == 0) {
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_mode\","
            "\"oper_mode\":%u,\"oper_mode_task\":%u,"
            "\"player_ctrl_routine\":%u,\"pause_status\":%u,"
            "\"pause_timer\":%u,\"paused\":%s}\n",
            id,
            (unsigned)semcomp_runtime_mode_oper_mode(),
            (unsigned)semcomp_runtime_mode_oper_mode_task(),
            (unsigned)semcomp_runtime_mode_player_ctrl_routine(),
            (unsigned)semcomp_runtime_mode_pause_status(),
            (unsigned)semcomp_runtime_mode_pause_timer(),
            semcomp_runtime_mode_is_paused() ? "true" : "false");
        return 1;
    }
    if (strcmp(cmd, "semcomp_pause") == 0) {
        semcomp_runtime_mode_set_paused(1);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_pause\","
            "\"paused\":%s}\n",
            id, semcomp_runtime_mode_is_paused() ? "true" : "false");
        return 1;
    }
    if (strcmp(cmd, "semcomp_unpause") == 0) {
        semcomp_runtime_mode_set_paused(0);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_unpause\","
            "\"paused\":%s}\n",
            id, semcomp_runtime_mode_is_paused() ? "true" : "false");
        return 1;
    }
    if (strcmp(cmd, "semcomp_end_level") == 0) {
        semcomp_runtime_mode_end_level();
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_end_level\"}\n", id);
        return 1;
    }
    if (strcmp(cmd, "semcomp_warp_to") == 0) {
        int w = extras_json_get_int(json, "world", 0);
        int l = extras_json_get_int(json, "level", 0);
        if (w < 0) w = 0; if (w > 7) w = 7;
        if (l < 0) l = 0; if (l > 3) l = 3;
        semcomp_runtime_mode_warp_to((uint8_t)w, (uint8_t)l);
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,\"cmd\":\"semcomp_warp_to\","
            "\"world\":%d,\"level\":%d}\n", id, w, l);
        return 1;
    }
#endif  /* ENABLE_SEMCOMP */

    /* ---- Verify mode divergence ring ----
     * Query the always-on divergence ring populated by verify_mode.c
     * each time a frame's WRAM disagrees with the Nestopia oracle.
     * Optional args: "limit" (max entries to return, default 32),
     * "since" (return only entries from this frame onward).
     * The ring lives independently of ENABLE_SEMCOMP — useful for any
     * --verify run, with or without routine replacements active. */
    if (strcmp(cmd, "verify_diff_ring") == 0) {
        int limit = extras_json_get_int(json, "limit", 32);
        int since = extras_json_get_int(json, "since", 0);
        if (limit < 1) limit = 1;
        if (limit > VERIFY_DIVERGENCE_RING_SIZE) limit = VERIFY_DIVERGENCE_RING_SIZE;

        uint64_t total  = verify_mode_divergence_ring_total();
        uint64_t oldest = (total > (uint64_t)VERIFY_DIVERGENCE_RING_SIZE)
                          ? (total - VERIFY_DIVERGENCE_RING_SIZE) : 0;
        uint64_t start  = (total > (uint64_t)limit) ? (total - (uint64_t)limit) : 0;
        if (start < oldest) start = oldest;

        /* Build single-line response — see semcomp_routine_list note above. */
        char buf[16000];
        int pos = snprintf(buf, sizeof(buf),
            "{\"id\":%d,\"ok\":true,\"cmd\":\"verify_diff_ring\","
            "\"total\":%llu,\"oldest_live\":%llu,\"entries\":[",
            id, (unsigned long long)total, (unsigned long long)oldest);
        int wrote = 0;
        for (uint64_t i = start; i < total && pos < (int)sizeof(buf) - 256; i++) {
            VerifyDivergence d;
            if (!verify_mode_divergence_ring_get(i, &d)) continue;
            if ((int)d.frame < since) continue;
            pos += snprintf(buf + pos, sizeof(buf) - pos,
                "%s{\"idx\":%llu,\"frame\":%llu,\"addr\":\"0x%04X\","
                "\"native\":%d,\"emu\":%d,\"total_diffs\":%d}",
                (wrote == 0) ? "" : ",",
                (unsigned long long)i,
                (unsigned long long)d.frame,
                d.first_diff_addr, d.native_val, d.emu_val, d.total_diff_count);
            wrote++;
        }
        snprintf(buf + pos, sizeof(buf) - pos, "]}");
        debug_server_send_fmt("%s", buf);
        return 1;
    }

    return 0;
}

/* Phase 24 — Enemies mega (batch 1). */
void func_C2F1(void) { semcomp_runtime_init_goomba(); }
void func_C328(void) { semcomp_runtime_init_hammer_bro(); }
void func_C36B(void) { semcomp_runtime_init_bullet_bill(); }
void func_C375(void) { semcomp_runtime_init_cheep_cheep(); }
void func_C385(void) { semcomp_runtime_init_lakitu(); }
void func_C38A(void) { semcomp_runtime_setup_lakitu(); }
void func_C45C(void) { semcomp_runtime_init_short_firebar(); }
void func_CAE5(void) { semcomp_runtime_move_defeated_enemy(); }
void func_CAF9(void) { semcomp_runtime_move_jumping_enemy(); }
void func_CB89(void) { semcomp_runtime_move_bloober(); }


/* Phase 24 batch 2 — enemies (continued). */
void func_CFEC(void) { semcomp_runtime_bridge_collapse(); }
void func_D071(void) { semcomp_runtime_kill_all_enemies_d071(); }
void func_D065(void) { semcomp_runtime_run_bowser(); }
void func_D00F(void) { semcomp_runtime_move_d_bowser(); }
void func_C998(void) { semcomp_runtime_erase_enemy_object(); }
void func_C363(void) { semcomp_runtime_init_vstf(); }
void func_C226(void) { semcomp_runtime_init_enemy_object(); }
void func_C216(void) { semcomp_runtime_check_frenzy_buffer(); }
void func_C250(void) { semcomp_runtime_check_three_bytes(); }
void func_C71B(void) { semcomp_runtime_handle_group_enemies(); }
void func_C25B(void) { semcomp_runtime_inc_3b(); }
void func_D336(void) { semcomp_runtime_end_area_points(); }
void func_D312(void) { semcomp_runtime_award_game_timer_points(); }


/* Phase 25 — Level parser (batch 1) */
void func_85BF_b0(void) { semcomp_runtime_get_area_palette(); }
void func_86E6_b0(void) { semcomp_runtime_area_parser_task_control(); }
void func_88AE_b0(void) { semcomp_runtime_render_area_graphics(); }
void func_8FE4_b0(void) { semcomp_runtime_initialize_area(); }
void func_92B0_b0(void) { semcomp_runtime_area_parser_task_handler(); }
void func_92C8_b0(void) { semcomp_runtime_area_parser_tasks(); }
void func_9B36_b0(void) { semcomp_runtime_get_area_object_i_d(); }
void func_9BCB_b0(void) { semcomp_runtime_get_area_obj_x_position(); }
void func_9BD3_b0(void) { semcomp_runtime_get_area_obj_y_position(); }
void func_9C03_b0(void) { semcomp_runtime_load_area_pointer(); }
void func_9C09_b0(void) { semcomp_runtime_get_area_type(); }
void func_9C22_b0(void) { semcomp_runtime_get_area_data_addrs(); }

/* Phase 25 — Level parser (batch 1) */

/* Phase 26 — BG renderer + VRAM */
void func_85C5_b0(void) { semcomp_runtime_set_v_r_a_m_addr__a(); }
void func_863F_b0(void) { semcomp_runtime_set_v_r_a_m_offset(); }
void func_864C_b0(void) { semcomp_runtime_set_v_r_a_m_addr__b(); }
void func_8652_b0(void) { semcomp_runtime_write_top_status_line(); }
void func_865A_b0(void) { semcomp_runtime_write_bottom_status_line(); }
void func_8749_b0(void) { semcomp_runtime_write_top_score(); }
void func_89BD_b0(void) { semcomp_runtime_set_v_r_a_m_ctrl(); }
void func_8E2D_b0(void) { semcomp_runtime_write_n_t_addr(); }
void func_8E92_b0(void) { semcomp_runtime_write_buffer_to_screen(); }
void func_8EED_b0(void) { semcomp_runtime_write_p_p_u_reg1(); }

/* Phase 27-30 — Audio */
void func_F1D7(void) { semcomp_runtime_run_offscr_bits_subs(); }
void func_F3BF(void) { semcomp_runtime_play_flagpole_slide(); }
void func_F3CD(void) { semcomp_runtime_play_small_jump(); }
void func_F3D1(void) { semcomp_runtime_play_big_jump(); }
void func_F3F9(void) { semcomp_runtime_play_fireball_throw(); }
void func_F3FF(void) { semcomp_runtime_play_bump(); }
void func_F51E(void) { semcomp_runtime_play_timer_tick(); }
void func_F53A(void) { semcomp_runtime_play_blast(); }
void func_F552(void) { semcomp_runtime_play_power_up_grab(); }
void func_F64D(void) { semcomp_runtime_play_noise_sfx(); }

/* Phase 31 — Misc utilities */
void func_8745_b0(void) { semcomp_runtime_inc_subtask(); }
void func_8220_b0(void) { semcomp_runtime_move_all_sprites_offscreen(); }
void func_8223_b0(void) { semcomp_runtime_move_sprites_offscreen(); }
void func_8643_b0(void) { semcomp_runtime_get_alternate_palette1(); }
void func_DFB0(void) { semcomp_runtime_get_m_tile_attrib(); }
void func_E5B3(void) { semcomp_runtime_move_six_sprites_offscreen(); }
void func_92DB_b0(void) { semcomp_runtime_increment_column_pos(); }
void func_9589_b0(void) { semcomp_runtime_inc_area_obj_offset(); }
void func_874E_b0(void) { semcomp_runtime_inc_mode_task__b(); }

/* Phase 32 - AudioEngine bulk-port (116 entries across 12 multi-entry bodies + 2 single-entry) */
void func_F41B(void) { semcomp_runtime_square1_sfx_handler(); }
void func_F57C(void) { semcomp_runtime_square2_sfx_handler(); }
void func_F2D0(void) { semcomp_runtime_sound_engine(); }
void func_F2D3(void) { semcomp_runtime_at_f2d3(); }
void func_F2EA(void) { semcomp_runtime_at_f2ea(); }
void func_F2F3(void) { semcomp_runtime_at_f2f3(); }
void func_F329(void) { semcomp_runtime_at_f329(); }
void func_F380(void) { semcomp_runtime_at_f380(); }
void func_F367(void) { semcomp_runtime_at_f367(); }
void func_F377(void) { semcomp_runtime_no_inc_dac(); }
void func_F381(void) { semcomp_runtime_dump_squ1_regs(); }
void func_F384(void) { semcomp_runtime_at_f384(); }
void func_F388(void) { semcomp_runtime_play_squ1_sfx(); }
void func_F38E(void) { semcomp_runtime_at_f38e(); }
void func_F39F(void) { semcomp_runtime_dump_sq2_regs(); }
void func_F3A5(void) { semcomp_runtime_at_f3a5(); }
void func_F3A6(void) { semcomp_runtime_play_squ2_sfx(); }
void func_F4D1(void) { semcomp_runtime_no_p_dwn_l(); }
void func_F410(void) { semcomp_runtime_at_f410(); }
void func_F4B0(void) { semcomp_runtime_at_f4b0(); }
void func_F3F2(void) { semcomp_runtime_fps2nd(); }
void func_F3F4(void) { semcomp_runtime_dmp_jp_fps(); }
void func_F4BE(void) { semcomp_runtime_at_f4be(); }
void func_F4BF(void) { semcomp_runtime_at_f4bf(); }
void func_F4A5(void) { semcomp_runtime_at_f4a5(); }
void func_F405(void) { semcomp_runtime_at_f405(); }
void func_F486(void) { semcomp_runtime_at_f486(); }
void func_F421(void) { semcomp_runtime_at_f421(); }
void func_F3EE(void) { semcomp_runtime_at_f3ee(); }
void func_F490(void) { semcomp_runtime_at_f490(); }
void func_F462(void) { semcomp_runtime_at_f462(); }
void func_F4A9(void) { semcomp_runtime_at_f4a9(); }
void func_F44C(void) { semcomp_runtime_at_f44c(); }
void func_F518(void) { semcomp_runtime_play_coin_grab(); }
void func_F5D1(void) { semcomp_runtime_blst_s_jp(); }
void func_F602(void) { semcomp_runtime_grow_item_regs(); }
void func_F538(void) { semcomp_runtime_n2_tone(); }
void func_F607(void) { semcomp_runtime_at_f607(); }
void func_F621(void) { semcomp_runtime_at_f621(); }
void func_F5F6(void) { semcomp_runtime_at_f5f6(); }
void func_F5FC(void) { semcomp_runtime_play_grow_power_up(); }
void func_F624(void) { semcomp_runtime_at_f624(); }
void func_F586(void) { semcomp_runtime_at_f586(); }
void func_F5B2(void) { semcomp_runtime_at_f5b2(); }
void func_F5F8(void) { semcomp_runtime_at_f5f8(); }
void func_F5ED(void) { semcomp_runtime_at_f5ed(); }
void func_F5C5(void) { semcomp_runtime_jump_to_dec_length2(); }
void func_F5E0(void) { semcomp_runtime_el_l_regs(); }
void func_F5CF(void) { semcomp_runtime_at_f5cf(); }
void func_F5EC(void) { semcomp_runtime_div_l_loop(); }
void func_F5B9(void) { semcomp_runtime_at_f5b9(); }
void func_F605(void) { semcomp_runtime_at_f605(); }
void func_F522(void) { semcomp_runtime_c_grab_t_tick_reg_l(); }
void func_F617(void) { semcomp_runtime_at_f617(); }
void func_F63B(void) { semcomp_runtime_play_brick_shatter(); }
void func_F658(void) { semcomp_runtime_decrement_sfx3_length(); }
void func_F644(void) { semcomp_runtime_at_f644(); }
void func_F667(void) { semcomp_runtime_noise_sfx_handler(); }
void func_F685(void) { semcomp_runtime_continue_bowser_flame(); }
void func_F679(void) { semcomp_runtime_at_f679(); }
void func_F68F(void) { semcomp_runtime_at_f68f(); }
void func_F694(void) { semcomp_runtime_music_handler(); }
void func_F8B9(void) { semcomp_runtime_silent_beat(); }
void func_F7C3(void) { semcomp_runtime_at_f7c3(); }
void func_F860(void) { semcomp_runtime_at_f860(); }
void func_F8A9(void) { semcomp_runtime_strong_beat(); }
void func_F6F1(void) { semcomp_runtime_find_event_music_header(); }
void func_F80D(void) { semcomp_runtime_at_f80d(); }
void func_F720(void) { semcomp_runtime_at_f720(); }
void func_F710(void) { semcomp_runtime_at_f710(); }
void func_F6A1(void) { semcomp_runtime_at_f6a1(); }
void func_F8AD(void) { semcomp_runtime_at_f8ad(); }
void func_F829(void) { semcomp_runtime_at_f829(); }
void func_F750(void) { semcomp_runtime_at_f750(); }
void func_F6FC(void) { semcomp_runtime_at_f6fc(); }
void func_F7A9(void) { semcomp_runtime_at_f7a9(); }
void func_F810(void) { semcomp_runtime_death_m_alt_reg(); }
void func_F784(void) { semcomp_runtime_at_f784(); }
void func_F885(void) { semcomp_runtime_at_f885(); }
void func_F786(void) { semcomp_runtime_squ2_note_handler(); }
void func_F7A5(void) { semcomp_runtime_at_f7a5(); }
void func_F7E6(void) { semcomp_runtime_at_f7e6(); }
void func_F7E7(void) { semcomp_runtime_at_f7e7(); }
void func_F8A5(void) { semcomp_runtime_at_f8a5(); }
void func_F7E4(void) { semcomp_runtime_at_f7e4(); }
void func_F7F7(void) { semcomp_runtime_misc_squ1_music_tasks(); }
void func_F7F1(void) { semcomp_runtime_skip_ctrl_l(); }
void func_F6F5(void) { semcomp_runtime_load_header(); }
void func_F878(void) { semcomp_runtime_fetch_noise_beat_data(); }
void func_F6B8(void) { semcomp_runtime_at_f6b8(); }
void func_F7FB(void) { semcomp_runtime_at_f7fb(); }
void func_F850(void) { semcomp_runtime_at_f850(); }
void func_F88D(void) { semcomp_runtime_at_f88d(); }
void func_F6B6(void) { semcomp_runtime_at_f6b6(); }
void func_F864(void) { semcomp_runtime_medi_n(); }
void func_F862(void) { semcomp_runtime_at_f862(); }
void func_F741(void) { semcomp_runtime_at_f741(); }
void func_F844(void) { semcomp_runtime_at_f844(); }
void func_F807(void) { semcomp_runtime_at_f807(); }
void func_F706(void) { semcomp_runtime_at_f706(); }
void func_F729(void) { semcomp_runtime_at_f729(); }
void func_F8C5(void) { semcomp_runtime_alternate_length_handler(); }
void func_F8D0(void) { semcomp_runtime_at_f8d0(); }
void func_F8C9(void) { semcomp_runtime_at_f8c9(); }
void func_F8CA(void) { semcomp_runtime_at_f8ca(); }
void func_F8C6(void) { semcomp_runtime_at_f8c6(); }
void func_F8CE(void) { semcomp_runtime_at_f8ce(); }
void func_F8C8(void) { semcomp_runtime_at_f8c8(); }
void func_F8D8(void) { semcomp_runtime_load_control_regs(); }
void func_F8F1(void) { semcomp_runtime_at_f8f1(); }
void func_F8E7(void) { semcomp_runtime_at_f8e7(); }
void func_F8F4(void) { semcomp_runtime_load_envelope_data(); }
void func_F8FB(void) { semcomp_runtime_at_f8fb(); }
void func_F90C(void) { semcomp_runtime_at_f90c(); }
void func_F903(void) { semcomp_runtime_at_f903(); }
void func_F905(void) { semcomp_runtime_at_f905(); }

/* Phase 33 - EnemyEngine bulk-port (38 multi-entry bodies, 724 entries) */
void func_C047(void) { semcomp_runtime_enemies_and_loops_core(); }
void func_C058(void) { semcomp_runtime_at_c058(); }
void func_C04E(void) { semcomp_runtime_at_c04e(); }
void func_C04D(void) { semcomp_runtime_at_c04d(); }
void func_C08C(void) { semcomp_runtime_exec_game_loopback(); }
void func_C0C8(void) { semcomp_runtime_at_c0c8(); }
void func_C0A0(void) { semcomp_runtime_at_c0a0(); }
void func_C0B7(void) { semcomp_runtime_at_c0b7(); }
void func_C0C2(void) { semcomp_runtime_at_c0c2(); }
void func_C0A9(void) { semcomp_runtime_at_c0a9(); }
void func_C0A8(void) { semcomp_runtime_at_c0a8(); }
void func_C0CC(void) { semcomp_runtime_proc_loop_command(); }
void func_C0E9(void) { semcomp_runtime_at_c0e9(); }
void func_C0E1(void) { semcomp_runtime_at_c0e1(); }
void func_C1BE(void) { semcomp_runtime_at_c1be(); }
void func_C0F0(void) { semcomp_runtime_at_c0f0(); }
void func_C14D(void) { semcomp_runtime_at_c14d(); }
void func_C0CF(void) { semcomp_runtime_at_c0cf(); }
void func_C18E(void) { semcomp_runtime_at_c18e(); }
void func_C1AE(void) { semcomp_runtime_at_c1ae(); }
void func_C219(void) { semcomp_runtime_at_c219(); }
void func_C0D8(void) { semcomp_runtime_find_loop(); }
void func_C242(void) { semcomp_runtime_at_c242(); }
void func_C141(void) { semcomp_runtime_at_c141(); }
void func_C124(void) { semcomp_runtime_at_c124(); }
void func_C22E(void) { semcomp_runtime_do_group(); }
void func_C20E(void) { semcomp_runtime_at_c20e(); }
void func_C21E(void) { semcomp_runtime_at_c21e(); }
void func_C213(void) { semcomp_runtime_at_c213(); }
void func_C115(void) { semcomp_runtime_wrong_chk(); }
void func_C102(void) { semcomp_runtime_inc_m_loop(); }
void func_C0D6(void) { semcomp_runtime_at_c0d6(); }
void func_C0FF(void) { semcomp_runtime_at_c0ff(); }
void func_C15D(void) { semcomp_runtime_at_c15d(); }
void func_C26C(void) { semcomp_runtime_checkpoint_enemy_id(); }
void func_C2F0(void) { semcomp_runtime_no_init_code(); }
void func_C2F7(void) { semcomp_runtime_init_podoboo(); }
void func_C304(void) { semcomp_runtime_at_c304(); }
void func_C302(void) { semcomp_runtime_at_c302(); }
void func_C301(void) { semcomp_runtime_at_c301(); }
void func_C307(void) { semcomp_runtime_init_retainer_obj(); }
void func_C30B(void) { semcomp_runtime_at_c30b(); }
void func_C31E(void) { semcomp_runtime_init_red_koopa(); }
void func_C321(void) { semcomp_runtime_at_c321(); }
void func_C342(void) { semcomp_runtime_init_bloober(); }
void func_C365(void) { semcomp_runtime_at_c365(); }
void func_C367(void) { semcomp_runtime_at_c367(); }
void func_C3A4(void) { semcomp_runtime_lakitu_and_spiny_handler(); }
void func_C44E(void) { semcomp_runtime_chp_chp_ex(); }
void func_C40A(void) { semcomp_runtime_at_c40a(); }
void func_C3D1(void) { semcomp_runtime_at_c3d1(); }
void func_C40F(void) { semcomp_runtime_dif_loop(); }
void func_C420(void) { semcomp_runtime_at_c420(); }
void func_C3CA(void) { semcomp_runtime_chk_no_en(); }
void func_C3C4(void) { semcomp_runtime_at_c3c4(); }
void func_C424(void) { semcomp_runtime_at_c424(); }
void func_C402(void) { semcomp_runtime_at_c402(); }
void func_C3B9(void) { semcomp_runtime_at_c3b9(); }
void func_C416(void) { semcomp_runtime_at_c416(); }
void func_C40D(void) { semcomp_runtime_at_c40d(); }
void func_C412(void) { semcomp_runtime_at_c412(); }
void func_C442(void) { semcomp_runtime_at_c442(); }
void func_C3B4(void) { semcomp_runtime_chk_lak(); }
void func_C3C1(void) { semcomp_runtime_at_c3c1(); }
void func_C3FD(void) { semcomp_runtime_at_c3fd(); }
void func_C459(void) { semcomp_runtime_init_long_firebar(); }
void func_C47D(void) { semcomp_runtime_at_c47d(); }
void func_C4A8(void) { semcomp_runtime_init_flying_cheep_cheep(); }
void func_C511(void) { semcomp_runtime_at_c511(); }
void func_C500(void) { semcomp_runtime_at_c500(); }
void func_C504(void) { semcomp_runtime_at_c504(); }
void func_C4AD(void) { semcomp_runtime_at_c4ad(); }
void func_C4FC(void) { semcomp_runtime_at_c4fc(); }
void func_C4FD(void) { semcomp_runtime_at_c4fd(); }
void func_C4CA(void) { semcomp_runtime_at_c4ca(); }
void func_C502(void) { semcomp_runtime_at_c502(); }
void func_C508(void) { semcomp_runtime_at_c508(); }
void func_C4B0(void) { semcomp_runtime_at_c4b0(); }
void func_C521(void) { semcomp_runtime_at_c521(); }
void func_C4D1(void) { semcomp_runtime_at_c4d1(); }
void func_C51F(void) { semcomp_runtime_at_c51f(); }
void func_C506(void) { semcomp_runtime_at_c506(); }
void func_C50C(void) { semcomp_runtime_at_c50c(); }
void func_C533(void) { semcomp_runtime_at_c533(); }
void func_C516(void) { semcomp_runtime_at_c516(); }
void func_C518(void) { semcomp_runtime_at_c518(); }
void func_C549(void) { semcomp_runtime_init_bowser(); }
void func_C56D(void) { semcomp_runtime_at_c56d(); }
void func_C54C(void) { semcomp_runtime_at_c54c(); }
void func_C563(void) { semcomp_runtime_at_c563(); }
void func_C575(void) { semcomp_runtime_duplicate_enemy_obj(); }
void func_C59C(void) { semcomp_runtime_flm_ex(); }
void func_C588(void) { semcomp_runtime_at_c588(); }
void func_C586(void) { semcomp_runtime_at_c586(); }
void func_C5A3(void) { semcomp_runtime_init_bowser_flame(); }
void func_C5CF(void) { semcomp_runtime_at_c5cf(); }
void func_C604(void) { semcomp_runtime_at_c604(); }
void func_C5C9(void) { semcomp_runtime_set_fr_t(); }
void func_C606(void) { semcomp_runtime_at_c606(); }
void func_C609(void) { semcomp_runtime_at_c609(); }
void func_C5C6(void) { semcomp_runtime_at_c5c6(); }
void func_C5C7(void) { semcomp_runtime_at_c5c7(); }
void func_C5BE(void) { semcomp_runtime_at_c5be(); }
void func_C613(void) { semcomp_runtime_at_c613(); }
void func_C614(void) { semcomp_runtime_set_mf(); }
void func_C5AD(void) { semcomp_runtime_at_c5ad(); }
void func_C624(void) { semcomp_runtime_at_c624(); }
void func_C69C(void) { semcomp_runtime_bullet_bill_cheep_cheep(); }
void func_C6D7(void) { semcomp_runtime_at_c6d7(); }
void func_C6C8(void) { semcomp_runtime_at_c6c8(); }
void func_C6B1(void) { semcomp_runtime_at_c6b1(); }
void func_C6EC(void) { semcomp_runtime_at_c6ec(); }
void func_C6C3(void) { semcomp_runtime_set17_id(); }
void func_C74C(void) { semcomp_runtime_at_c74c(); }
void func_C75D(void) { semcomp_runtime_at_c75d(); }
void func_C700(void) { semcomp_runtime_at_c700(); }
void func_C725(void) { semcomp_runtime_at_c725(); }
void func_C741(void) { semcomp_runtime_at_c741(); }
void func_C738(void) { semcomp_runtime_at_c738(); }
void func_C720(void) { semcomp_runtime_at_c720(); }
void func_C77A(void) { semcomp_runtime_at_c77a(); }
void func_C74D(void) { semcomp_runtime_cnt_grp(); }
void func_C772(void) { semcomp_runtime_at_c772(); }
void func_C734(void) { semcomp_runtime_at_c734(); }
void func_C6CE(void) { semcomp_runtime_at_c6ce(); }
void func_C6FF(void) { semcomp_runtime_bb_s_loop(); }
void func_C750(void) { semcomp_runtime_gr_loop(); }
void func_C787(void) { semcomp_runtime_init_piranha_plant(); }
void func_C78C(void) { semcomp_runtime_at_c78c(); }
void func_C7A0(void) { semcomp_runtime_init_enemy_frenzy(); }
void func_C7C9(void) { semcomp_runtime_at_c7c9(); }
void func_C7B8(void) { semcomp_runtime_end_frenzy(); }
void func_C7BA(void) { semcomp_runtime_lakitu_chk(); }
void func_C7DF(void) { semcomp_runtime_init_bal_platform(); }
void func_C808(void) { semcomp_runtime_at_c808(); }
void func_C805(void) { semcomp_runtime_at_c805(); }
void func_C800(void) { semcomp_runtime_at_c800(); }
void func_C7EF(void) { semcomp_runtime_at_c7ef(); }
void func_C7F7(void) { semcomp_runtime_at_c7f7(); }
void func_C7FF(void) { semcomp_runtime_at_c7ff(); }
void func_C80B(void) { semcomp_runtime_init_hori_platform(); }
void func_C80F(void) { semcomp_runtime_at_c80f(); }
void func_C80D(void) { semcomp_runtime_at_c80d(); }
void func_C812(void) { semcomp_runtime_init_vert_platform(); }
void func_C814(void) { semcomp_runtime_at_c814(); }
void func_C81F(void) { semcomp_runtime_set_yo(); }
void func_C816(void) { semcomp_runtime_at_c816(); }
void func_C81B(void) { semcomp_runtime_at_c81b(); }
void func_C824(void) { semcomp_runtime_at_c824(); }
void func_C834(void) { semcomp_runtime_at_c834(); }
void func_C81D(void) { semcomp_runtime_at_c81d(); }
void func_C818(void) { semcomp_runtime_at_c818(); }
void func_C81A(void) { semcomp_runtime_at_c81a(); }
void func_C84B(void) { semcomp_runtime_plat_lift_up(); }
void func_C84D(void) { semcomp_runtime_at_c84d(); }
void func_C857(void) { semcomp_runtime_plat_lift_down(); }
void func_C859(void) { semcomp_runtime_at_c859(); }
void func_C85C(void) { semcomp_runtime_at_c85c(); }
void func_C871(void) { semcomp_runtime_pos_platform(); }
void func_C87E(void) { semcomp_runtime_at_c87e(); }
void func_C880(void) { semcomp_runtime_at_c880(); }
void func_C882(void) { semcomp_runtime_run_enemy_objects_core(); }
void func_C8D6(void) { semcomp_runtime_no_run_code(); }
void func_C888(void) { semcomp_runtime_at_c888(); }
void func_C88F(void) { semcomp_runtime_jmp_eo(); }
void func_C88A(void) { semcomp_runtime_at_c88a(); }
void func_C8E0(void) { semcomp_runtime_run_normal_enemies(); }
void func_C8FF(void) { semcomp_runtime_at_c8ff(); }
void func_C902(void) { semcomp_runtime_skip_move(); }
void func_C8EB(void) { semcomp_runtime_at_c8eb(); }
void func_C8E8(void) { semcomp_runtime_at_c8e8(); }
void func_C8EE(void) { semcomp_runtime_at_c8ee(); }
void func_C8E5(void) { semcomp_runtime_at_c8e5(); }
void func_C8F7(void) { semcomp_runtime_at_c8f7(); }
void func_C8F1(void) { semcomp_runtime_at_c8f1(); }
void func_C905(void) { semcomp_runtime_enemy_movement_subs(); }
void func_C934(void) { semcomp_runtime_no_move_code(); }
void func_C935(void) { semcomp_runtime_run_bowser_flame(); }
void func_C938(void) { semcomp_runtime_at_c938(); }
void func_C93E(void) { semcomp_runtime_at_c93e(); }
void func_C947(void) { semcomp_runtime_run_firebar_obj(); }
void func_C94A(void) { semcomp_runtime_at_c94a(); }
void func_C94D(void) { semcomp_runtime_run_small_platform(); }
void func_C959(void) { semcomp_runtime_at_c959(); }
void func_C953(void) { semcomp_runtime_at_c953(); }
void func_C965(void) { semcomp_runtime_run_large_platform(); }
void func_C96B(void) { semcomp_runtime_at_c96b(); }
void func_C96E(void) { semcomp_runtime_at_c96e(); }
void func_C97F(void) { semcomp_runtime_at_c97f(); }
void func_C982(void) { semcomp_runtime_large_platform_subroutines(); }
void func_C987(void) { semcomp_runtime_at_c987(); }
void func_C9AC(void) { semcomp_runtime_at_c9ac(); }
void func_C9B0(void) { semcomp_runtime_move_podoboo(); }
void func_C9C0(void) { semcomp_runtime_at_c9c0(); }
void func_C9C9(void) { semcomp_runtime_at_c9c9(); }
void func_C9B5(void) { semcomp_runtime_at_c9b5(); }
void func_C9CB(void) { semcomp_runtime_pdb_m(); }
void func_C9C7(void) { semcomp_runtime_at_c9c7(); }
void func_C9D8(void) { semcomp_runtime_proc_hammer_bro(); }
void func_D311(void) { semcomp_runtime_star_flag_exit(); }
void func_D84C(void) { semcomp_runtime_no_p_up(); }
void func_DA24(void) { semcomp_runtime_ex_sfn(); }
void func_D1EA(void) { semcomp_runtime_ex_fl(); }
void func_D1BB(void) { semcomp_runtime_ex_b_gfx_h(); }
void func_D001(void) { semcomp_runtime_at_d001(); }
void func_D007(void) { semcomp_runtime_at_d007(); }
void func_D907(void) { semcomp_runtime_at_d907(); }
void func_D908(void) { semcomp_runtime_at_d908(); }
void func_D0C0(void) { semcomp_runtime_at_d0c0(); }
void func_CEA5(void) { semcomp_runtime_at_cea5(); }
void func_D9CF(void) { semcomp_runtime_at_d9cf(); }
void func_D9EE(void) { semcomp_runtime_at_d9ee(); }
void func_D003(void) { semcomp_runtime_at_d003(); }
void func_D9AE(void) { semcomp_runtime_at_d9ae(); }
void func_D98D(void) { semcomp_runtime_at_d98d(); }
void func_CDAD(void) { semcomp_runtime_at_cdad(); }
void func_CD8E(void) { semcomp_runtime_at_cd8e(); }
void func_C9EA(void) { semcomp_runtime_at_c9ea(); }
void func_D100(void) { semcomp_runtime_at_d100(); }
void func_CD87(void) { semcomp_runtime_at_cd87(); }
void func_CF96(void) { semcomp_runtime_at_cf96(); }
void func_CCAE(void) { semcomp_runtime_at_ccae(); }
void func_CD4B(void) { semcomp_runtime_at_cd4b(); }
void func_CFB5(void) { semcomp_runtime_at_cfb5(); }
void func_D89D(void) { semcomp_runtime_at_d89d(); }
void func_D1C8(void) { semcomp_runtime_at_d1c8(); }
void func_D009(void) { semcomp_runtime_at_d009(); }
void func_CF76(void) { semcomp_runtime_at_cf76(); }
void func_D18E(void) { semcomp_runtime_at_d18e(); }
void func_D94C(void) { semcomp_runtime_at_d94c(); }
void func_D1EE(void) { semcomp_runtime_at_d1ee(); }
void func_D1AD(void) { semcomp_runtime_at_d1ad(); }
void func_CA05(void) { semcomp_runtime_at_ca05(); }
void func_D820(void) { semcomp_runtime_shroom_flower_p_up(); }
void func_CFB9(void) { semcomp_runtime_at_cfb9(); }
void func_CAC8(void) { semcomp_runtime_revive_stunned(); }
void func_D058(void) { semcomp_runtime_at_d058(); }
void func_CF8D(void) { semcomp_runtime_at_cf8d(); }
void func_CF9A(void) { semcomp_runtime_at_cf9a(); }
void func_D920(void) { semcomp_runtime_at_d920(); }
void func_CFD6(void) { semcomp_runtime_s_pixel_lak(); }
void func_CB8D(void) { semcomp_runtime_at_cb8d(); }
void func_D7CF(void) { semcomp_runtime_at_d7cf(); }
void func_D031(void) { semcomp_runtime_at_d031(); }
void func_D7AE(void) { semcomp_runtime_at_d7ae(); }
void func_D38C(void) { semcomp_runtime_at_d38c(); }
void func_D38D(void) { semcomp_runtime_at_d38d(); }
void func_CEC2(void) { semcomp_runtime_at_cec2(); }
void func_D3CF(void) { semcomp_runtime_chk_player_near_pipe(); }
void func_CCD0(void) { semcomp_runtime_at_ccd0(); }
void func_D012(void) { semcomp_runtime_at_d012(); }
void func_D660(void) { semcomp_runtime_at_d660(); }
void func_CFD7(void) { semcomp_runtime_at_cfd7(); }
void func_D6D0(void) { semcomp_runtime_at_d6d0(); }
void func_D6D2(void) { semcomp_runtime_too_far(); }
void func_D6C8(void) { semcomp_runtime_at_d6c8(); }
void func_D6CA(void) { semcomp_runtime_at_d6ca(); }
void func_D6BA(void) { semcomp_runtime_at_d6ba(); }
void func_D6B8(void) { semcomp_runtime_at_d6b8(); }
void func_D7B8(void) { semcomp_runtime_at_d7b8(); }
void func_D8CB(void) { semcomp_runtime_at_d8cb(); }
void func_CB8A(void) { semcomp_runtime_at_cb8a(); }
void func_CC4B(void) { semcomp_runtime_at_cc4b(); }
void func_D3D5(void) { semcomp_runtime_reverse_plant_speed(); }
void func_D62D(void) { semcomp_runtime_at_d62d(); }
void func_D00C(void) { semcomp_runtime_at_d00c(); }
void func_CEBA(void) { semcomp_runtime_get_v_adder(); }
void func_CA10(void) { semcomp_runtime_hammer_bro_jump_l_data(); }
void func_D041(void) { semcomp_runtime_at_d041(); }
void func_D079(void) { semcomp_runtime_at_d079(); }
void func_D4B9(void) { semcomp_runtime_at_d4b9(); }
void func_D4BA(void) { semcomp_runtime_at_d4ba(); }
void func_D005(void) { semcomp_runtime_set_m2(); }
void func_CFF7(void) { semcomp_runtime_at_cff7(); }
void func_D5D0(void) { semcomp_runtime_ex_pf(); }
void func_D6FA(void) { semcomp_runtime_at_d6fa(); }
void func_D0CB(void) { semcomp_runtime_at_d0cb(); }
void func_D089(void) { semcomp_runtime_at_d089(); }
void func_D069(void) { semcomp_runtime_at_d069(); }
void func_CEC5(void) { semcomp_runtime_at_cec5(); }
void func_CC46(void) { semcomp_runtime_swim_ccx_move_data(); }
void func_CC47(void) { semcomp_runtime_at_cc47(); }
void func_D018(void) { semcomp_runtime_at_d018(); }
void func_CE8F(void) { semcomp_runtime_at_ce8f(); }
void func_CFAD(void) { semcomp_runtime_at_cfad(); }
void func_CD06(void) { semcomp_runtime_at_cd06(); }
void func_CD07(void) { semcomp_runtime_at_cd07(); }
void func_D0F8(void) { semcomp_runtime_at_d0f8(); }
void func_CEA4(void) { semcomp_runtime_at_cea4(); }
void func_CD3B(void) { semcomp_runtime_at_cd3b(); }
void func_CE33(void) { semcomp_runtime_at_ce33(); }
void func_CD2E(void) { semcomp_runtime_firebar_tbl_offsets(); }
void func_CD2F(void) { semcomp_runtime_at_cd2f(); }
void func_CCC7(void) { semcomp_runtime_firebar_pos_lookup_tbl(); }
void func_CCC8(void) { semcomp_runtime_at_ccc8(); }
void func_CD2A(void) { semcomp_runtime_firebar_mirror_data(); }
void func_CED5(void) { semcomp_runtime_p_random_subtracter(); }
void func_CED6(void) { semcomp_runtime_at_ced6(); }
void func_CEDB(void) { semcomp_runtime_at_cedb(); }
void func_CF25(void) { semcomp_runtime_lakitu_diff_adj(); }
void func_D599(void) { semcomp_runtime_at_d599(); }
void func_D606(void) { semcomp_runtime_ex_y_pl(); }
void func_D0A1(void) { semcomp_runtime_at_d0a1(); }
void func_D02E(void) { semcomp_runtime_at_d02e(); }
void func_CED2(void) { semcomp_runtime_at_ced2(); }
void func_CFDD(void) { semcomp_runtime_bridge_collapse_data(); }
void func_CFDE(void) { semcomp_runtime_at_cfde(); }
void func_D061(void) { semcomp_runtime_p_random_range(); }
void func_D609(void) { semcomp_runtime_at_d609(); }
void func_D721(void) { semcomp_runtime_at_d721(); }
void func_D01F(void) { semcomp_runtime_at_d01f(); }
void func_D1D1(void) { semcomp_runtime_flame_timer_data(); }
void func_D991(void) { semcomp_runtime_at_d991(); }
void func_D78D(void) { semcomp_runtime_at_d78d(); }
void func_CD7D(void) { semcomp_runtime_at_cd7d(); }
void func_D2CD(void) { semcomp_runtime_star_flag_y_pos_adder(); }
void func_D2CE(void) { semcomp_runtime_at_d2ce(); }
void func_D5BD(void) { semcomp_runtime_at_d5bd(); }
void func_D2D5(void) { semcomp_runtime_star_flag_tile_data(); }
void func_D17E(void) { semcomp_runtime_at_d17e(); }
void func_D2D1(void) { semcomp_runtime_star_flag_x_pos_adder(); }
void func_D2D2(void) { semcomp_runtime_at_d2d2(); }
void func_DA10(void) { semcomp_runtime_at_da10(); }
void func_D5BC(void) { semcomp_runtime_at_d5bc(); }
void func_D52D(void) { semcomp_runtime_at_d52d(); }
void func_D9D6(void) { semcomp_runtime_at_d9d6(); }
void func_CFD9(void) { semcomp_runtime_at_cfd9(); }
void func_CFDA(void) { semcomp_runtime_at_cfda(); }
void func_D01A(void) { semcomp_runtime_at_d01a(); }
void func_CFF5(void) { semcomp_runtime_at_cff5(); }
void func_CF79(void) { semcomp_runtime_at_cf79(); }
void func_D542(void) { semcomp_runtime_at_d542(); }
void func_CFB7(void) { semcomp_runtime_at_cfb7(); }
void func_D8BE(void) { semcomp_runtime_at_d8be(); }
void func_CA01(void) { semcomp_runtime_at_ca01(); }
void func_CE2D(void) { semcomp_runtime_at_ce2d(); }
void func_CE2E(void) { semcomp_runtime_at_ce2e(); }
void func_D736(void) { semcomp_runtime_bowser_identities(); }
void func_D81D(void) { semcomp_runtime_at_d81d(); }
void func_D84F(void) { semcomp_runtime_kicked_shell_x_spd_data(); }
void func_D892(void) { semcomp_runtime_kicked_shell_pts_data(); }
void func_D893(void) { semcomp_runtime_at_d893(); }
void func_D966(void) { semcomp_runtime_at_d966(); }
void func_D851(void) { semcomp_runtime_demoted_koopa_x_spd_data(); }
void func_D852(void) { semcomp_runtime_at_d852(); }
void func_D2B9(void) { semcomp_runtime_at_d2b9(); }
void func_D9D2(void) { semcomp_runtime_revival_rate_data(); }
void func_CADD(void) { semcomp_runtime_at_cadd(); }
void func_D081(void) { semcomp_runtime_at_d081(); }
void func_DA25(void) { semcomp_runtime_set_bits_mask(); }
void func_D024(void) { semcomp_runtime_at_d024(); }
void func_CE85(void) { semcomp_runtime_no_col_fb(); }
void func_CE86(void) { semcomp_runtime_at_ce86(); }
void func_D0AE(void) { semcomp_runtime_at_d0ae(); }
void func_CFC9(void) { semcomp_runtime_at_cfc9(); }
void func_C9DC(void) { semcomp_runtime_at_c9dc(); }
void func_D0C5(void) { semcomp_runtime_at_d0c5(); }
void func_CE26(void) { semcomp_runtime_at_ce26(); }
void func_D0E3(void) { semcomp_runtime_at_d0e3(); }
void func_D0E4(void) { semcomp_runtime_at_d0e4(); }
void func_CBD0(void) { semcomp_runtime_at_cbd0(); }
void func_CBD1(void) { semcomp_runtime_at_cbd1(); }
void func_CA03(void) { semcomp_runtime_at_ca03(); }
void func_C9DE(void) { semcomp_runtime_at_c9de(); }
void func_D027(void) { semcomp_runtime_at_d027(); }
void func_D6AE(void) { semcomp_runtime_at_d6ae(); }
void func_D0E1(void) { semcomp_runtime_at_d0e1(); }
void func_C9F9(void) { semcomp_runtime_at_c9f9(); }
void func_C9DA(void) { semcomp_runtime_at_c9da(); }
void func_D61F(void) { semcomp_runtime_at_d61f(); }
void func_D047(void) { semcomp_runtime_at_d047(); }
void func_D5EC(void) { semcomp_runtime_skip_iy(); }
void func_C9E3(void) { semcomp_runtime_at_c9e3(); }
void func_D595(void) { semcomp_runtime_at_d595(); }
void func_D12D(void) { semcomp_runtime_at_d12d(); }
void func_CAF1(void) { semcomp_runtime_at_caf1(); }
void func_D905(void) { semcomp_runtime_at_d905(); }
void func_D913(void) { semcomp_runtime_at_d913(); }
void func_CEB5(void) { semcomp_runtime_at_ceb5(); }
void func_CC79(void) { semcomp_runtime_at_cc79(); }
void func_CC7D(void) { semcomp_runtime_at_cc7d(); }
void func_D0BE(void) { semcomp_runtime_at_d0be(); }
void func_D4BD(void) { semcomp_runtime_draw_erase_rope(); }
void func_D603(void) { semcomp_runtime_at_d603(); }
void func_D679(void) { semcomp_runtime_ex_lift_p(); }
void func_CEBE(void) { semcomp_runtime_at_cebe(); }
void func_CA0D(void) { semcomp_runtime_at_ca0d(); }
void func_D8DB(void) { semcomp_runtime_at_d8db(); }
void func_D8D9(void) { semcomp_runtime_at_d8d9(); }
void func_CDD9(void) { semcomp_runtime_at_cdd9(); }
void func_CECD(void) { semcomp_runtime_at_cecd(); }
void func_CECE(void) { semcomp_runtime_at_cece(); }
void func_CECF(void) { semcomp_runtime_at_cecf(); }
void func_CFCF(void) { semcomp_runtime_at_cfcf(); }
void func_D2D3(void) { semcomp_runtime_at_d2d3(); }
void func_D2D4(void) { semcomp_runtime_at_d2d4(); }
void func_D58A(void) { semcomp_runtime_at_d58a(); }
void func_D4D6(void) { semcomp_runtime_at_d4d6(); }
void func_D3E3(void) { semcomp_runtime_at_d3e3(); }
void func_D5D2(void) { semcomp_runtime_at_d5d2(); }
void func_D0D1(void) { semcomp_runtime_get_pr_cmp(); }
void func_D7D1(void) { semcomp_runtime_at_d7d1(); }
void func_D7D7(void) { semcomp_runtime_at_d7d7(); }
void func_D7D8(void) { semcomp_runtime_at_d7d8(); }
void func_CABF(void) { semcomp_runtime_at_cabf(); }
void func_CCC6(void) { semcomp_runtime_ex_sw_cc(); }
void func_CBCD(void) { semcomp_runtime_at_cbcd(); }
void func_CC49(void) { semcomp_runtime_at_cc49(); }
void func_D29D(void) { semcomp_runtime_at_d29d(); }
void func_D8D3(void) { semcomp_runtime_at_d8d3(); }
void func_D036(void) { semcomp_runtime_at_d036(); }
void func_D033(void) { semcomp_runtime_at_d033(); }
void func_D091(void) { semcomp_runtime_at_d091(); }
void func_C9EC(void) { semcomp_runtime_at_c9ec(); }
void func_D0B5(void) { semcomp_runtime_at_d0b5(); }
void func_D03C(void) { semcomp_runtime_at_d03c(); }
void func_D015(void) { semcomp_runtime_remove_bridge(); }
void func_D0EC(void) { semcomp_runtime_at_d0ec(); }
void func_D0ED(void) { semcomp_runtime_at_d0ed(); }
void func_CDBD(void) { semcomp_runtime_at_cdbd(); }
void func_CA07(void) { semcomp_runtime_at_ca07(); }
void func_D4AD(void) { semcomp_runtime_at_d4ad(); }
void func_D4AE(void) { semcomp_runtime_at_d4ae(); }
void func_D903(void) { semcomp_runtime_at_d903(); }
void func_D3AD(void) { semcomp_runtime_at_d3ad(); }
void func_D58D(void) { semcomp_runtime_at_d58d(); }
void func_CAA9(void) { semcomp_runtime_at_caa9(); }
void func_D5AF(void) { semcomp_runtime_at_d5af(); }
void func_D04C(void) { semcomp_runtime_at_d04c(); }
void func_D0F0(void) { semcomp_runtime_at_d0f0(); }
void func_D5AD(void) { semcomp_runtime_at_d5ad(); }
void func_D0C8(void) { semcomp_runtime_at_d0c8(); }
void func_D099(void) { semcomp_runtime_at_d099(); }
void func_C9F1(void) { semcomp_runtime_at_c9f1(); }
void func_C9F3(void) { semcomp_runtime_at_c9f3(); }
void func_D045(void) { semcomp_runtime_at_d045(); }
void func_CEF4(void) { semcomp_runtime_at_cef4(); }
void func_CE03(void) { semcomp_runtime_set_v_fbr(); }
void func_D0F6(void) { semcomp_runtime_at_d0f6(); }
void func_D0F4(void) { semcomp_runtime_at_d0f4(); }
void func_D4B1(void) { semcomp_runtime_at_d4b1(); }
void func_CBA0(void) { semcomp_runtime_at_cba0(); }
void func_CE40(void) { semcomp_runtime_at_ce40(); }
void func_D05E(void) { semcomp_runtime_no_b_fall(); }
void func_D9B9(void) { semcomp_runtime_at_d9b9(); }
void func_D6B0(void) { semcomp_runtime_at_d6b0(); }
void func_CAD7(void) { semcomp_runtime_at_cad7(); }
void func_D3B9(void) { semcomp_runtime_at_d3b9(); }
void func_D07F(void) { semcomp_runtime_bowser_control(); }
void func_CCA8(void) { semcomp_runtime_at_cca8(); }
void func_D0FB(void) { semcomp_runtime_at_d0fb(); }
void func_CA8E(void) { semcomp_runtime_at_ca8e(); }
void func_D03E(void) { semcomp_runtime_at_d03e(); }
void func_D44D(void) { semcomp_runtime_chk_for_fall(); }
void func_D0F2(void) { semcomp_runtime_at_d0f2(); }
void func_CC4A(void) { semcomp_runtime_move_swimming_cheep_cheep(); }
void func_CC4C(void) { semcomp_runtime_at_cc4c(); }
void func_D853(void) { semcomp_runtime_player_enemy_collision(); }
void func_E435(void) { semcomp_runtime_draw_vine(); }
void func_E6BD(void) { semcomp_runtime_ex_jc_gfx(); }
void func_DFB8(void) { semcomp_runtime_ex_ebg(); }
void func_E539(void) { semcomp_runtime_at_e539(); }
void func_DAAE(void) { semcomp_runtime_at_daae(); }
void func_E6F0(void) { semcomp_runtime_at_e6f0(); }
void func_E6F1(void) { semcomp_runtime_at_e6f1(); }
void func_DA8D(void) { semcomp_runtime_at_da8d(); }
void func_E00F(void) { semcomp_runtime_at_e00f(); }
void func_E0CA(void) { semcomp_runtime_at_e0ca(); }
void func_DFC2(void) { semcomp_runtime_at_dfc2(); }
void func_E0A1(void) { semcomp_runtime_at_e0a1(); }
void func_E03D(void) { semcomp_runtime_at_e03d(); }
void func_E401(void) { semcomp_runtime_at_e401(); }
void func_DFA9(void) { semcomp_runtime_at_dfa9(); }
void func_DFAA(void) { semcomp_runtime_at_dfaa(); }
void func_E058(void) { semcomp_runtime_at_e058(); }
void func_DDAE(void) { semcomp_runtime_at_ddae(); }
void func_DD8E(void) { semcomp_runtime_at_dd8e(); }
void func_DD2D(void) { semcomp_runtime_cont_chk(); }
void func_DD0D(void) { semcomp_runtime_at_dd0d(); }
void func_E0E8(void) { semcomp_runtime_at_e0e8(); }
void func_DB4D(void) { semcomp_runtime_at_db4d(); }
void func_E08E(void) { semcomp_runtime_at_e08e(); }
void func_DFCA(void) { semcomp_runtime_at_dfca(); }
void func_E274(void) { semcomp_runtime_at_e274(); }
void func_E800(void) { semcomp_runtime_at_e800(); }
void func_DECB(void) { semcomp_runtime_at_decb(); }
void func_DF21(void) { semcomp_runtime_at_df21(); }
void func_E8A9(void) { semcomp_runtime_check_for_retainer_obj(); }
void func_E003(void) { semcomp_runtime_at_e003(); }
void func_E5CF(void) { semcomp_runtime_at_e5cf(); }
void func_E5D0(void) { semcomp_runtime_at_e5d0(); }
void func_E606(void) { semcomp_runtime_at_e606(); }
void func_E609(void) { semcomp_runtime_at_e609(); }
void func_E60A(void) { semcomp_runtime_at_e60a(); }
void func_E605(void) { semcomp_runtime_at_e605(); }
void func_E6CD(void) { semcomp_runtime_at_e6cd(); }
void func_E802(void) { semcomp_runtime_at_e802(); }
void func_DAB9(void) { semcomp_runtime_at_dab9(); }
void func_DC8E(void) { semcomp_runtime_at_dc8e(); }
void func_DCCD(void) { semcomp_runtime_at_dccd(); }
void func_E131(void) { semcomp_runtime_no_bump(); }
void func_E603(void) { semcomp_runtime_at_e603(); }
void func_E8C9(void) { semcomp_runtime_at_e8c9(); }
void func_E40D(void) { semcomp_runtime_at_e40d(); }
void func_E029(void) { semcomp_runtime_at_e029(); }
void func_DC1A(void) { semcomp_runtime_at_dc1a(); }
void func_E56F(void) { semcomp_runtime_at_e56f(); }
void func_E818(void) { semcomp_runtime_at_e818(); }
void func_E857(void) { semcomp_runtime_at_e857(); }
void func_E858(void) { semcomp_runtime_at_e858(); }
void func_E1D1(void) { semcomp_runtime_at_e1d1(); }
void func_DFC0(void) { semcomp_runtime_at_dfc0(); }
void func_DAAB(void) { semcomp_runtime_at_daab(); }
void func_DC55(void) { semcomp_runtime_at_dc55(); }
void func_E60D(void) { semcomp_runtime_at_e60d(); }
void func_E60E(void) { semcomp_runtime_at_e60e(); }
void func_DC16(void) { semcomp_runtime_at_dc16(); }
void func_DC17(void) { semcomp_runtime_player_pos_s_plat_data(); }
void func_E3AD(void) { semcomp_runtime_block_buffer_adder_data(); }
void func_DDCE(void) { semcomp_runtime_pipe_dwn_s(); }
void func_DC62(void) { semcomp_runtime_player_bg_upper_extent(); }
void func_DF90(void) { semcomp_runtime_at_df90(); }
void func_E820(void) { semcomp_runtime_at_e820(); }
void func_DF9B(void) { semcomp_runtime_at_df9b(); }
void func_E4C9(void) { semcomp_runtime_at_e4c9(); }
void func_E4CA(void) { semcomp_runtime_at_e4ca(); }
void func_DE2F(void) { semcomp_runtime_at_de2f(); }
void func_DD20(void) { semcomp_runtime_at_dd20(); }
void func_DE03(void) { semcomp_runtime_area_change_timer_data(); }
void func_DE8E(void) { semcomp_runtime_at_de8e(); }
void func_DD07(void) { semcomp_runtime_at_dd07(); }
void func_DE29(void) { semcomp_runtime_flagpole_y_pos_data(); }
void func_DE25(void) { semcomp_runtime_climb_x_pos_adder(); }
void func_DB8E(void) { semcomp_runtime_at_db8e(); }
void func_E807(void) { semcomp_runtime_at_e807(); }
void func_E80A(void) { semcomp_runtime_at_e80a(); }
void func_DFB1(void) { semcomp_runtime_at_dfb1(); }
void func_DDE0(void) { semcomp_runtime_at_dde0(); }
void func_DF8B(void) { semcomp_runtime_solid_m_tile_upper_ext(); }
void func_DF96(void) { semcomp_runtime_climb_m_tile_upper_ext(); }
void func_E090(void) { semcomp_runtime_at_e090(); }
void func_DFB9(void) { semcomp_runtime_enemy_bgc_state_data(); }
void func_E389(void) { semcomp_runtime_at_e389(); }
void func_E791(void) { semcomp_runtime_at_e791(); }
void func_E060(void) { semcomp_runtime_no_c_dir_f(); }
void func_E061(void) { semcomp_runtime_at_e061(); }
void func_E27D(void) { semcomp_runtime_at_e27d(); }
void func_E1FE(void) { semcomp_runtime_at_e1fe(); }
void func_E1FF(void) { semcomp_runtime_at_e1ff(); }
void func_E804(void) { semcomp_runtime_at_e804(); }
void func_DD04(void) { semcomp_runtime_at_dd04(); }
void func_DD2A(void) { semcomp_runtime_at_dd2a(); }
void func_DD3B(void) { semcomp_runtime_at_dd3b(); }
void func_DD60(void) { semcomp_runtime_at_dd60(); }
void func_DD61(void) { semcomp_runtime_at_dd61(); }
void func_DD1A(void) { semcomp_runtime_award_touched_coin(); }
void func_E3F1(void) { semcomp_runtime_at_e3f1(); }
void func_E3B0(void) { semcomp_runtime_block_buffer_x_adder(); }
void func_E121(void) { semcomp_runtime_at_e121(); }
void func_E3CD(void) { semcomp_runtime_at_e3cd(); }
void func_E1A9(void) { semcomp_runtime_at_e1a9(); }
void func_E0A9(void) { semcomp_runtime_at_e0a9(); }
void func_E4C4(void) { semcomp_runtime_first_spr_y_pos(); }
void func_E4C5(void) { semcomp_runtime_at_e4c5(); }
void func_E4CC(void) { semcomp_runtime_second_spr_y_pos(); }
void func_E4CD(void) { semcomp_runtime_at_e4cd(); }
void func_E4C0(void) { semcomp_runtime_first_spr_x_pos(); }
void func_E4D0(void) { semcomp_runtime_first_spr_tilenum(); }
void func_E4D4(void) { semcomp_runtime_second_spr_tilenum(); }
void func_E541(void) { semcomp_runtime_flagpole_score_num_tiles(); }
void func_DBD6(void) { semcomp_runtime_at_dbd6(); }
void func_DBB5(void) { semcomp_runtime_at_dbb5(); }
void func_E6BE(void) { semcomp_runtime_power_up_gfx_table(); }
void func_E682(void) { semcomp_runtime_jumping_coin_tiles(); }
void func_E683(void) { semcomp_runtime_at_e683(); }
void func_E48D(void) { semcomp_runtime_at_e48d(); }
void func_E4E4(void) { semcomp_runtime_at_e4e4(); }
void func_E6C0(void) { semcomp_runtime_at_e6c0(); }
void func_DCFC(void) { semcomp_runtime_at_dcfc(); }
void func_DCDD(void) { semcomp_runtime_at_dcdd(); }
void func_DFDC(void) { semcomp_runtime_at_dfdc(); }
void func_DFDF(void) { semcomp_runtime_hb_chk(); }
void func_DCDF(void) { semcomp_runtime_at_dcdf(); }
void func_DDDC(void) { semcomp_runtime_at_dddc(); }
void func_DDDE(void) { semcomp_runtime_at_ddde(); }
void func_DEDF(void) { semcomp_runtime_at_dedf(); }
void func_DA7B(void) { semcomp_runtime_at_da7b(); }
void func_DBDA(void) { semcomp_runtime_at_dbda(); }
void func_E3D4(void) { semcomp_runtime_at_e3d4(); }
void func_E2E4(void) { semcomp_runtime_at_e2e4(); }
void func_E58A(void) { semcomp_runtime_at_e58a(); }
void func_E6E7(void) { semcomp_runtime_at_e6e7(); }
void func_E7E9(void) { semcomp_runtime_at_e7e9(); }
void func_E878(void) { semcomp_runtime_jumpspring_frame_offsets(); }
void func_E879(void) { semcomp_runtime_at_e879(); }
void func_E840(void) { semcomp_runtime_enemy_gfx_table_offsets(); }
void func_DEA3(void) { semcomp_runtime_at_dea3(); }
void func_E4A2(void) { semcomp_runtime_next_v_sp(); }
void func_E4A3(void) { semcomp_runtime_at_e4a3(); }
void func_E0EA(void) { semcomp_runtime_at_e0ea(); }
void func_E67F(void) { semcomp_runtime_at_e67f(); }
void func_E672(void) { semcomp_runtime_at_e672(); }
void func_E667(void) { semcomp_runtime_at_e667(); }
void func_E01D(void) { semcomp_runtime_at_e01d(); }
void func_E04E(void) { semcomp_runtime_at_e04e(); }
void func_E646(void) { semcomp_runtime_at_e646(); }
void func_E876(void) { semcomp_runtime_enemy_anim_timing_b_mask(); }
void func_E877(void) { semcomp_runtime_at_e877(); }
void func_E005(void) { semcomp_runtime_at_e005(); }
void func_E041(void) { semcomp_runtime_at_e041(); }
void func_E007(void) { semcomp_runtime_at_e007(); }
void func_E73E(void) { semcomp_runtime_enemy_graphics_table(); }
void func_E57D(void) { semcomp_runtime_at_e57d(); }
void func_E0EC(void) { semcomp_runtime_chk2_msb_st(); }
void func_E8BE(void) { semcomp_runtime_check_for_bullet_bill_cv(); }
void func_E048(void) { semcomp_runtime_set_wy_spd(); }
void func_E0AB(void) { semcomp_runtime_at_e0ab(); }
void func_E4AD(void) { semcomp_runtime_at_e4ad(); }
void func_E7BD(void) { semcomp_runtime_at_e7bd(); }
void func_DC20(void) { semcomp_runtime_at_dc20(); }
void func_DEF0(void) { semcomp_runtime_at_def0(); }
void func_E8A8(void) { semcomp_runtime_at_e8a8(); }
void func_E0D0(void) { semcomp_runtime_at_e0d0(); }
void func_DCD1(void) { semcomp_runtime_at_dcd1(); }
void func_E6F7(void) { semcomp_runtime_p_up_draw_loop(); }
void func_E6FA(void) { semcomp_runtime_at_e6fa(); }
void func_E301(void) { semcomp_runtime_at_e301(); }
void func_DDD5(void) { semcomp_runtime_at_ddd5(); }
void func_E3DE(void) { semcomp_runtime_at_e3de(); }
void func_DFDA(void) { semcomp_runtime_at_dfda(); }
void func_E0A4(void) { semcomp_runtime_ex_ste_chk(); }
void func_E763(void) { semcomp_runtime_at_e763(); }
void func_E1E4(void) { semcomp_runtime_at_e1e4(); }
void func_E3E1(void) { semcomp_runtime_at_e3e1(); }
void func_E3E2(void) { semcomp_runtime_at_e3e2(); }
void func_DE1E(void) { semcomp_runtime_at_de1e(); }
void func_E0DF(void) { semcomp_runtime_at_e0df(); }
void func_DF01(void) { semcomp_runtime_at_df01(); }
void func_DD66(void) { semcomp_runtime_side_check_loop(); }
void func_E7E6(void) { semcomp_runtime_at_e7e6(); }
void func_DE59(void) { semcomp_runtime_at_de59(); }
void func_E850(void) { semcomp_runtime_at_e850(); }
void func_DF77(void) { semcomp_runtime_at_df77(); }
void func_DF71(void) { semcomp_runtime_at_df71(); }
void func_DDD3(void) { semcomp_runtime_at_ddd3(); }
void func_DB8C(void) { semcomp_runtime_chk_small_plat_loop(); }
void func_E38B(void) { semcomp_runtime_at_e38b(); }
void func_E10A(void) { semcomp_runtime_sde_c_loop(); }
void func_E3B1(void) { semcomp_runtime_at_e3b1(); }
void func_E3BA(void) { semcomp_runtime_at_e3ba(); }
void func_E540(void) { semcomp_runtime_no_h_offscr(); }
void func_E53B(void) { semcomp_runtime_at_e53b(); }
void func_E492(void) { semcomp_runtime_chk_f_top(); }
void func_DEC9(void) { semcomp_runtime_at_dec9(); }
void func_DE8A(void) { semcomp_runtime_at_de8a(); }
void func_DEBF(void) { semcomp_runtime_at_debf(); }
void func_E629(void) { semcomp_runtime_at_e629(); }
void func_E6F5(void) { semcomp_runtime_at_e6f5(); }
void func_E4BD(void) { semcomp_runtime_at_e4bd(); }
void func_E179(void) { semcomp_runtime_at_e179(); }
void func_E49D(void) { semcomp_runtime_at_e49d(); }
void func_E710(void) { semcomp_runtime_at_e710(); }
void func_DC82(void) { semcomp_runtime_set_fall_s(); }
void func_E385(void) { semcomp_runtime_at_e385(); }
void func_DC23(void) { semcomp_runtime_at_dc23(); }
void func_E600(void) { semcomp_runtime_at_e600(); }
void func_DDBD(void) { semcomp_runtime_at_ddbd(); }
void func_E38D(void) { semcomp_runtime_at_e38d(); }
void func_E28D(void) { semcomp_runtime_at_e28d(); }
void func_E7B9(void) { semcomp_runtime_at_e7b9(); }
void func_DB93(void) { semcomp_runtime_at_db93(); }
void func_DCB9(void) { semcomp_runtime_at_dcb9(); }
void func_DD90(void) { semcomp_runtime_at_dd90(); }
void func_E7B1(void) { semcomp_runtime_at_e7b1(); }
void func_DFD0(void) { semcomp_runtime_at_dfd0(); }
void func_E59A(void) { semcomp_runtime_at_e59a(); }
void func_E61B(void) { semcomp_runtime_at_e61b(); }
void func_E0B9(void) { semcomp_runtime_at_e0b9(); }
void func_E4B9(void) { semcomp_runtime_at_e4b9(); }
void func_E7A5(void) { semcomp_runtime_at_e7a5(); }
void func_DD76(void) { semcomp_runtime_at_dd76(); }
void func_DB04(void) { semcomp_runtime_at_db04(); }
void func_DD3D(void) { semcomp_runtime_at_dd3d(); }
void func_DB5C(void) { semcomp_runtime_at_db5c(); }
void func_DB0C(void) { semcomp_runtime_at_db0c(); }
void func_DE82(void) { semcomp_runtime_at_de82(); }
void func_E30C(void) { semcomp_runtime_check_left_screen_b_box(); }
void func_E286(void) { semcomp_runtime_at_e286(); }
void func_E528(void) { semcomp_runtime_at_e528(); }
void func_DB3B(void) { semcomp_runtime_at_db3b(); }
void func_DE38(void) { semcomp_runtime_ex_hc(); }
void func_DECE(void) { semcomp_runtime_at_dece(); }
void func_DBA7(void) { semcomp_runtime_at_dba7(); }
void func_E730(void) { semcomp_runtime_at_e730(); }
void func_E347(void) { semcomp_runtime_at_e347(); }
void func_DB47(void) { semcomp_runtime_at_db47(); }
void func_E406(void) { semcomp_runtime_at_e406(); }
void func_E001(void) { semcomp_runtime_at_e001(); }
void func_E431(void) { semcomp_runtime_at_e431(); }
void func_DE02(void) { semcomp_runtime_ex_csm(); }
void func_E408(void) { semcomp_runtime_at_e408(); }
void func_E70A(void) { semcomp_runtime_at_e70a(); }
void func_DD06(void) { semcomp_runtime_at_dd06(); }
void func_DE4B(void) { semcomp_runtime_at_de4b(); }
void func_DD0A(void) { semcomp_runtime_at_dd0a(); }
void func_E112(void) { semcomp_runtime_at_e112(); }
void func_DF11(void) { semcomp_runtime_at_df11(); }
void func_E139(void) { semcomp_runtime_at_e139(); }
void func_E278(void) { semcomp_runtime_at_e278(); }
void func_DC27(void) { semcomp_runtime_at_dc27(); }
void func_E722(void) { semcomp_runtime_at_e722(); }
void func_E322(void) { semcomp_runtime_no_ofs2(); }
void func_E372(void) { semcomp_runtime_at_e372(); }
void func_E781(void) { semcomp_runtime_at_e781(); }
void func_D881(void) { semcomp_runtime_check_for_p_up_collision(); }
void func_E8E3(void) { semcomp_runtime_at_e8e3(); }
void func_E8E5(void) { semcomp_runtime_at_e8e5(); }
void func_E8FD(void) { semcomp_runtime_at_e8fd(); }
void func_E8F2(void) { semcomp_runtime_check_bowser_gfx_flag(); }
void func_E8E9(void) { semcomp_runtime_at_e8e9(); }
void func_E8FB(void) { semcomp_runtime_at_e8fb(); }
void func_E8D9(void) { semcomp_runtime_at_e8d9(); }
void func_DFC1(void) { semcomp_runtime_enemy_to_bg_collision_det(); }
void func_DFC3(void) { semcomp_runtime_at_dfc3(); }

/* Phase 34 - LevelEngine bulk-port (10 multi-entry bodies, 25 entries) */
void func_85E3_b0(void) { semcomp_runtime_get_background_color(); }
void func_862E_b0(void) { semcomp_runtime_at_862e(); }
void func_8808_b0(void) { semcomp_runtime_write_game_text(); }
void func_8887_b0(void) { semcomp_runtime_at_8887(); }
void func_8846_b0(void) { semcomp_runtime_at_8846(); }
void func_8A6D_b0(void) { semcomp_runtime_write_block_metatile(); }
void func_8A8F_b0(void) { semcomp_runtime_move_v_offset(); }
void func_8A97_b0(void) { semcomp_runtime_put_block_metatile(); }
void func_8ACD_b0(void) { semcomp_runtime_rem_bridge(); }
void func_8A9D_b0(void) { semcomp_runtime_at_8a9d(); }
void func_90ED_b0(void) { semcomp_runtime_get_area_music(); }
void func_9100_b0(void) { semcomp_runtime_at_9100(); }
void func_93FC_b0(void) { semcomp_runtime_area_parser_core(); }
void func_9494_b0(void) { semcomp_runtime_at_9494(); }
void func_9491_b0(void) { semcomp_runtime_terr_loop(); }
void func_9508_b0(void) { semcomp_runtime_process_area_data(); }
void func_9588_b0(void) { semcomp_runtime_end_a_parse(); }
void func_9595_b0(void) { semcomp_runtime_decode_area_data(); }
void func_9645_b0(void) { semcomp_runtime_loop_cmd_e(); }
void func_95DF_b0(void) { semcomp_runtime_at_95df(); }
void func_9740_b0(void) { semcomp_runtime_area_style_object(); }
void func_9792_b0(void) { semcomp_runtime_at_9792(); }
void func_9989_b0(void) { semcomp_runtime_at_9989(); }
void func_BF94_b0(void) { semcomp_runtime_set_hi_max(); }
void func_BF96_b0(void) { semcomp_runtime_set_x_move_amt(); }

/* Phase 35 - RenderEngine bulk-port (33 bodies, 217 entries) */
void func_81C6_b0(void) { semcomp_runtime_sprite_shuffler(); }
void func_8200_b0(void) { semcomp_runtime_at_8200(); }
void func_81F9_b0(void) { semcomp_runtime_set_misc_offset(); }
void func_8212_b0(void) { semcomp_runtime_oper_mode_execution_tree(); }
void func_8222_b0(void) { semcomp_runtime_at_8222(); }
void func_8325_b0(void) { semcomp_runtime_draw_mushroom_icon(); }
void func_8330_b0(void) { semcomp_runtime_at_8330(); }
void func_83BD_b0(void) { semcomp_runtime_player_victory_walk(); }
void func_8434_b0(void) { semcomp_runtime_eval_for_music(); }
void func_8436_b0(void) { semcomp_runtime_at_8436(); }
void func_842C_b0(void) { semcomp_runtime_at_842c(); }
void func_8404_b0(void) { semcomp_runtime_at_8404(); }
void func_8461_b0(void) { semcomp_runtime_player_end_world(); }
void func_8486_b0(void) { semcomp_runtime_end_exit_one(); }
void func_8567_b0(void) { semcomp_runtime_screen_routines(); }
void func_85AD_b0(void) { semcomp_runtime_at_85ad(); }
void func_92AA_b0(void) { semcomp_runtime_do_nothing1(); }
void func_92AF_b0(void) { semcomp_runtime_do_nothing2(); }
void func_AF93_b0(void) { semcomp_runtime_scroll_handler(); }
void func_AFB1_b0(void) { semcomp_runtime_at_afb1(); }
void func_B74F_b0(void) { semcomp_runtime_run_game_timer(); }
void func_B7A3_b0(void) { semcomp_runtime_ex_g_timer(); }
void func_BF63_b0(void) { semcomp_runtime_move_d_enemy_vertically(); }
void func_BF6B_b0(void) { semcomp_runtime_move_falling_platform(); }
void func_E87D(void) { semcomp_runtime_enemy_gfx_handler(); }
void func_E9A0(void) { semcomp_runtime_at_e9a0(); }
void func_E939(void) { semcomp_runtime_at_e939(); }
void func_E9B2(void) { semcomp_runtime_at_e9b2(); }
void func_E96D(void) { semcomp_runtime_at_e96d(); }
void func_E900(void) { semcomp_runtime_check_for_goomba(); }
void func_E998(void) { semcomp_runtime_at_e998(); }
void func_EB20(void) { semcomp_runtime_at_eb20(); }
void func_E96F(void) { semcomp_runtime_at_e96f(); }
void func_E987(void) { semcomp_runtime_at_e987(); }
void func_E9B6(void) { semcomp_runtime_at_e9b6(); }
void func_E9D6(void) { semcomp_runtime_at_e9d6(); }
void func_E908(void) { semcomp_runtime_at_e908(); }
void func_EB86(void) { semcomp_runtime_at_eb86(); }
void func_E921(void) { semcomp_runtime_at_e921(); }
void func_EBA4(void) { semcomp_runtime_at_eba4(); }
void func_EB84(void) { semcomp_runtime_at_eb84(); }
void func_EBA6(void) { semcomp_runtime_at_eba6(); }
void func_EAAD(void) { semcomp_runtime_at_eaad(); }
void func_EAE7(void) { semcomp_runtime_at_eae7(); }
void func_E9EB(void) { semcomp_runtime_at_e9eb(); }
void func_EA3D(void) { semcomp_runtime_at_ea3d(); }
void func_EABA(void) { semcomp_runtime_at_eaba(); }
void func_E9D0(void) { semcomp_runtime_at_e9d0(); }
void func_E9E0(void) { semcomp_runtime_at_e9e0(); }
void func_E919(void) { semcomp_runtime_at_e919(); }
void func_EA20(void) { semcomp_runtime_at_ea20(); }
void func_E94C(void) { semcomp_runtime_check_bowser_rear(); }
void func_E960(void) { semcomp_runtime_at_e960(); }
void func_E9A4(void) { semcomp_runtime_at_e9a4(); }
void func_EAD0(void) { semcomp_runtime_at_ead0(); }
void func_EA85(void) { semcomp_runtime_at_ea85(); }
void func_E928(void) { semcomp_runtime_at_e928(); }
void func_EB80(void) { semcomp_runtime_at_eb80(); }
void func_EA32(void) { semcomp_runtime_at_ea32(); }
void func_E962(void) { semcomp_runtime_at_e962(); }
void func_EA61(void) { semcomp_runtime_skip_to_off_scr_chk(); }
void func_E953(void) { semcomp_runtime_at_e953(); }
void func_E9B0(void) { semcomp_runtime_at_e9b0(); }
void func_E9D4(void) { semcomp_runtime_at_e9d4(); }
void func_EB79(void) { semcomp_runtime_at_eb79(); }
void func_E902(void) { semcomp_runtime_at_e902(); }
void func_E949(void) { semcomp_runtime_draw_bowser(); }
void func_EAE1(void) { semcomp_runtime_at_eae1(); }
void func_EBB7(void) { semcomp_runtime_move_e_spr_row_offscreen(); }
void func_EBB8(void) { semcomp_runtime_at_ebb8(); }
void func_EBBC(void) { semcomp_runtime_at_ebbc(); }
void func_EBC1(void) { semcomp_runtime_move_e_spr_col_offscreen(); }
void func_EBC6(void) { semcomp_runtime_at_ebc6(); }
void func_EBC2(void) { semcomp_runtime_at_ebc2(); }
void func_EBD1(void) { semcomp_runtime_draw_block(); }
void func_EC20(void) { semcomp_runtime_at_ec20(); }
void func_EC21(void) { semcomp_runtime_set_b_flip(); }
void func_EBE7(void) { semcomp_runtime_d_blk_loop(); }
void func_EBEC(void) { semcomp_runtime_at_ebec(); }
void func_EC23(void) { semcomp_runtime_at_ec23(); }
void func_EBEA(void) { semcomp_runtime_at_ebea(); }
void func_EC35(void) { semcomp_runtime_blk_offscr(); }
void func_EC00(void) { semcomp_runtime_at_ec00(); }
void func_EC53(void) { semcomp_runtime_draw_brick_chunks(); }
void func_EC91(void) { semcomp_runtime_at_ec91(); }
void func_EC85(void) { semcomp_runtime_at_ec85(); }
void func_ECA5(void) { semcomp_runtime_at_eca5(); }
void func_EC65(void) { semcomp_runtime_d_chunks(); }
void func_ECDE(void) { semcomp_runtime_draw_fireball(); }
void func_ECF0(void) { semcomp_runtime_at_ecf0(); }
void func_ECF1(void) { semcomp_runtime_at_ecf1(); }
void func_ED09(void) { semcomp_runtime_draw_explosion_fireball(); }
void func_ED20(void) { semcomp_runtime_at_ed20(); }
void func_ED18(void) { semcomp_runtime_at_ed18(); }
void func_ED2E(void) { semcomp_runtime_at_ed2e(); }
void func_ED66(void) { semcomp_runtime_draw_small_platform(); }
void func_EDD1(void) { semcomp_runtime_s_ofs2(); }
void func_ED6F(void) { semcomp_runtime_at_ed6f(); }
void func_EDC5(void) { semcomp_runtime_at_edc5(); }
void func_ED86(void) { semcomp_runtime_at_ed86(); }
void func_EDA6(void) { semcomp_runtime_at_eda6(); }
void func_EDB9(void) { semcomp_runtime_at_edb9(); }
void func_ED76(void) { semcomp_runtime_at_ed76(); }
void func_EDE1(void) { semcomp_runtime_draw_bubble(); }
void func_EE06(void) { semcomp_runtime_ex_d_bub(); }
void func_EE03(void) { semcomp_runtime_at_ee03(); }
void func_EDED(void) { semcomp_runtime_at_eded(); }
void func_EDE3(void) { semcomp_runtime_at_ede3(); }
void func_EDE4(void) { semcomp_runtime_at_ede4(); }
void func_EDE6(void) { semcomp_runtime_at_ede6(); }
void func_EE01(void) { semcomp_runtime_at_ee01(); }
void func_EFBE(void) { semcomp_runtime_render_player_sub(); }
void func_EFD1(void) { semcomp_runtime_at_efd1(); }
void func_EFDF(void) { semcomp_runtime_at_efdf(); }
void func_EFEC(void) { semcomp_runtime_process_player_action(); }
void func_F008(void) { semcomp_runtime_at_f008(); }
void func_F041(void) { semcomp_runtime_at_f041(); }
void func_F004(void) { semcomp_runtime_at_f004(); }
void func_F006(void) { semcomp_runtime_at_f006(); }
void func_F012(void) { semcomp_runtime_at_f012(); }
void func_F010(void) { semcomp_runtime_at_f010(); }
void func_F058(void) { semcomp_runtime_at_f058(); }
void func_F02D(void) { semcomp_runtime_at_f02d(); }
void func_F001(void) { semcomp_runtime_at_f001(); }
void func_F021(void) { semcomp_runtime_at_f021(); }
void func_F03C(void) { semcomp_runtime_action_walk_run(); }
void func_F01F(void) { semcomp_runtime_at_f01f(); }
void func_EFF0(void) { semcomp_runtime_at_eff0(); }
void func_F046(void) { semcomp_runtime_at_f046(); }
void func_F014(void) { semcomp_runtime_at_f014(); }
void func_F00D(void) { semcomp_runtime_at_f00d(); }
void func_F030(void) { semcomp_runtime_at_f030(); }
void func_F033(void) { semcomp_runtime_at_f033(); }
void func_F025(void) { semcomp_runtime_at_f025(); }
void func_F034(void) { semcomp_runtime_action_falling(); }
void func_F02B(void) { semcomp_runtime_at_f02b(); }
void func_F00B(void) { semcomp_runtime_proc_on_ground_acts(); }
void func_F01D(void) { semcomp_runtime_at_f01d(); }
void func_F027(void) { semcomp_runtime_at_f027(); }
void func_F05F(void) { semcomp_runtime_at_f05f(); }
void func_F060(void) { semcomp_runtime_at_f060(); }
void func_F016(void) { semcomp_runtime_at_f016(); }
void func_EFFD(void) { semcomp_runtime_at_effd(); }
void func_F048(void) { semcomp_runtime_at_f048(); }
void func_F050(void) { semcomp_runtime_action_swimming(); }
void func_F03E(void) { semcomp_runtime_at_f03e(); }
void func_F065(void) { semcomp_runtime_at_f065(); }
void func_F018(void) { semcomp_runtime_at_f018(); }
void func_F05D(void) { semcomp_runtime_at_f05d(); }
void func_F052(void) { semcomp_runtime_at_f052(); }
void func_F01A(void) { semcomp_runtime_at_f01a(); }
void func_F06A(void) { semcomp_runtime_at_f06a(); }
void func_F023(void) { semcomp_runtime_at_f023(); }
void func_F039(void) { semcomp_runtime_at_f039(); }
void func_F06D(void) { semcomp_runtime_three_frame_extent(); }
void func_F090(void) { semcomp_runtime_at_f090(); }
void func_F086(void) { semcomp_runtime_at_f086(); }
void func_F07D(void) { semcomp_runtime_at_f07d(); }
void func_F074(void) { semcomp_runtime_at_f074(); }
void func_F075(void) { semcomp_runtime_at_f075(); }
void func_F080(void) { semcomp_runtime_at_f080(); }
void func_F088(void) { semcomp_runtime_at_f088(); }
void func_F091(void) { semcomp_runtime_get_gfx_offset_adder(); }
void func_F098(void) { semcomp_runtime_at_f098(); }
void func_F0B0(void) { semcomp_runtime_handle_change_size(); }
void func_F0E1(void) { semcomp_runtime_at_f0e1(); }
void func_F0C3(void) { semcomp_runtime_c_sz_next(); }
void func_F0B9(void) { semcomp_runtime_at_f0b9(); }
void func_F0BA(void) { semcomp_runtime_at_f0ba(); }
void func_F0C9(void) { semcomp_runtime_at_f0c9(); }
void func_F0C6(void) { semcomp_runtime_gor_s_log(); }
void func_F0E3(void) { semcomp_runtime_at_f0e3(); }
void func_F0DE(void) { semcomp_runtime_at_f0de(); }
void func_F0CB(void) { semcomp_runtime_at_f0cb(); }
void func_F0D8(void) { semcomp_runtime_at_f0d8(); }
void func_F0D9(void) { semcomp_runtime_at_f0d9(); }
void func_F0D1(void) { semcomp_runtime_at_f0d1(); }
void func_F0C0(void) { semcomp_runtime_at_f0c0(); }
void func_F0E8(void) { semcomp_runtime_at_f0e8(); }
void func_F0BE(void) { semcomp_runtime_at_f0be(); }
void func_F0E9(void) { semcomp_runtime_chk_for_player_attrib(); }
void func_F0F0(void) { semcomp_runtime_at_f0f0(); }
void func_F110(void) { semcomp_runtime_at_f110(); }
void func_F0F9(void) { semcomp_runtime_at_f0f9(); }
void func_F0FD(void) { semcomp_runtime_at_f0fd(); }
void func_F0EE(void) { semcomp_runtime_at_f0ee(); }
void func_F0FB(void) { semcomp_runtime_at_f0fb(); }
void func_F0FF(void) { semcomp_runtime_at_f0ff(); }
void func_F0F2(void) { semcomp_runtime_at_f0f2(); }
void func_F0F5(void) { semcomp_runtime_at_f0f5(); }
void func_F11F(void) { semcomp_runtime_at_f11f(); }
void func_F148(void) { semcomp_runtime_relative_misc_position(); }
void func_F14D(void) { semcomp_runtime_at_f14d(); }
void func_F180(void) { semcomp_runtime_get_player_offscreen_bits(); }
void func_F184(void) { semcomp_runtime_at_f184(); }
void func_F19B(void) { semcomp_runtime_get_misc_offscreen_bits(); }
void func_F19D(void) { semcomp_runtime_at_f19d(); }
void func_F1A8(void) { semcomp_runtime_get_proper_obj_offset(); }
void func_F1A9(void) { semcomp_runtime_at_f1a9(); }
void func_F1AF(void) { semcomp_runtime_get_enemy_offscreen_bits(); }
void func_F1B1(void) { semcomp_runtime_at_f1b1(); }
void func_F1B6(void) { semcomp_runtime_get_block_offscreen_bits(); }
void func_F1D1(void) { semcomp_runtime_at_f1d1(); }
void func_F1BD(void) { semcomp_runtime_at_f1bd(); }
void func_F1BC(void) { semcomp_runtime_at_f1bc(); }
void func_F1C1(void) { semcomp_runtime_at_f1c1(); }
void func_F1CE(void) { semcomp_runtime_at_f1ce(); }
void func_F239(void) { semcomp_runtime_get_y_offscreen_bits(); }
void func_F23D(void) { semcomp_runtime_y_ofs_loop(); }
void func_F282(void) { semcomp_runtime_draw_sprite_object(); }
void func_F2BD(void) { semcomp_runtime_at_f2bd(); }
void func_F285(void) { semcomp_runtime_at_f285(); }
void func_F286(void) { semcomp_runtime_at_f286(); }
void func_F2A5(void) { semcomp_runtime_at_f2a5(); }
void func_F284(void) { semcomp_runtime_at_f284(); }
void func_F2C8(void) { semcomp_runtime_at_f2c8(); }
void func_F288(void) { semcomp_runtime_at_f288(); }
