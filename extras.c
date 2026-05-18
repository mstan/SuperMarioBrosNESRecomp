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

