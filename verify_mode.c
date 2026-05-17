/*
 * verify_mode.c — Dual-execution verification mode
 *
 * In VERIFY mode: native code runs the game normally. Nestopia runs
 * in the background. After each frame, we compare RAM between the two.
 * Divergences are logged and recorded in the ring buffer.
 *
 * In EMULATED mode: Nestopia drives everything (handled in extras.c).
 * In NATIVE mode: no emulator, just recompiled code.
 */
#include "verify_mode.h"
#include "nes_snapshot.h"
#include "nes_runtime.h"
#include "debug_server.h"

#include <stdio.h>
#include <string.h>

#ifdef ENABLE_NESTOPIA_ORACLE
#include "nestopia_bridge.h"
#endif

RunMode  g_run_mode = RUN_MODE_NATIVE;
static uint64_t s_divergence_count = 0;
static int s_emu_initialized = 0;

/* Always-on divergence ring. Newest at (s_div_ring_total - 1) % SIZE. */
static VerifyDivergence s_div_ring[VERIFY_DIVERGENCE_RING_SIZE];
static uint64_t         s_div_ring_total = 0;

static void push_divergence(uint64_t frame, uint16_t addr,
                            uint8_t native_val, uint8_t emu_val,
                            uint16_t total_diff_count) {
    VerifyDivergence *r = &s_div_ring[s_div_ring_total %
                                      VERIFY_DIVERGENCE_RING_SIZE];
    r->frame            = frame;
    r->first_diff_addr  = addr;
    r->native_val       = native_val;
    r->emu_val          = emu_val;
    r->total_diff_count = total_diff_count;
    s_div_ring_total++;
}

uint64_t verify_mode_divergence_ring_total(void) {
    return s_div_ring_total;
}

int verify_mode_divergence_ring_get(uint64_t i, VerifyDivergence *out) {
    if (!out) return 0;
    if (s_div_ring_total == 0) return 0;
    /* Oldest live entry index = max(0, total - SIZE). */
    uint64_t oldest = (s_div_ring_total > VERIFY_DIVERGENCE_RING_SIZE)
                      ? (s_div_ring_total - VERIFY_DIVERGENCE_RING_SIZE) : 0;
    if (i < oldest || i >= s_div_ring_total) return 0;
    *out = s_div_ring[i % VERIFY_DIVERGENCE_RING_SIZE];
    return 1;
}

void verify_mode_init(const char *rom_path) {
#ifdef ENABLE_NESTOPIA_ORACLE
    if (g_run_mode == RUN_MODE_NATIVE) return;

    int rc = nestopia_bridge_init(rom_path);
    if (rc != 0) {
        fprintf(stderr, "[verify] Nestopia init failed (rc=%d), falling back to native\n", rc);
        g_run_mode = RUN_MODE_NATIVE;
        return;
    }
    s_emu_initialized = 1;
    fprintf(stderr, "[verify] Nestopia oracle initialized (mode=%s)\n",
            g_run_mode == RUN_MODE_VERIFY ? "verify" : "emulated");
#else
    (void)rom_path;
    if (g_run_mode != RUN_MODE_NATIVE) {
        fprintf(stderr, "[verify] Nestopia not compiled in, falling back to native\n");
        g_run_mode = RUN_MODE_NATIVE;
    }
#endif
}

int verify_mode_run_nmi(void) {
    if (g_run_mode == RUN_MODE_NATIVE) {
        func_NMI();
        return 1;
    }

#ifdef ENABLE_NESTOPIA_ORACLE
    if (!s_emu_initialized) {
        func_NMI();
        return 1;
    }

    if (g_run_mode == RUN_MODE_EMULATED) {
        /* Handled by game_run_main in extras.c — shouldn't reach here */
        func_NMI();
        return 1;
    }

    /* VERIFY mode — lockstep comparison.
     *
     * Problem: calling func_NMI() advances the recomp by ONE NMI handler,
     * but its surrounding main-loop coroutine has already executed the
     * entire RESET init chain before the first NMI ever fires.  A single
     * retro_run() on Nestopia advances only ONE frame of emulation —
     * nowhere near enough to catch up at first verify tick.
     *
     * Solution: sync by the ROM's own deterministic frame counter $0009
     * (ticked by every NMI handler on both sides).  After func_NMI(),
     * keep running Nestopia frames until its $0009 matches the recomp's.
     * On the first verify call this catches Nestopia up by dozens of
     * frames; on every later call it's exactly one retro_run (1:1). */

    /* 1. Run native NMI */
    func_NMI();

    /* 2. Drive Nestopia forward until its $0009 matches recomp's $0009. */
    static uint8_t emu_ram[0x800];
    uint8_t  rec_fc      = g_ram[0x0009];
    int      catchup     = 0;
    const int CATCHUP_MAX = 600;   /* ~10 s of wall time */
    nestopia_bridge_run_frame(g_controller1_buttons);
    nestopia_bridge_get_ram(emu_ram);
    while (emu_ram[0x0009] != rec_fc && catchup < CATCHUP_MAX) {
        nestopia_bridge_run_frame(0);
        nestopia_bridge_get_ram(emu_ram);
        catchup++;
    }
    if (catchup > 0) {
        fprintf(stderr, "[verify] sync: catchup=%d frames "
                "(recomp $0009=%u, nestopia now %u)\n",
                catchup, rec_fc, emu_ram[0x0009]);
    }

    /* 4. Compare work RAM */
    int diff_count = 0;
    int first_diff_addr = -1;
    uint8_t first_native = 0, first_emu = 0;

    for (int i = 0; i < 0x0800; i++) {
        if (g_ram[i] != emu_ram[i]) {
            if (diff_count == 0) {
                first_diff_addr = i;
                first_native = g_ram[i];
                first_emu = emu_ram[i];
            }
            diff_count++;
        }
    }

    int passed = (diff_count == 0);

    if (!passed) {
        s_divergence_count++;
        push_divergence(g_frame_count,
                        (uint16_t)first_diff_addr,
                        first_native, first_emu,
                        (uint16_t)diff_count);
        fprintf(stderr, "[verify] DIVERGE frame %llu: %d bytes differ | first: $%04X native=0x%02X emu=0x%02X\n",
                (unsigned long long)g_frame_count, diff_count,
                first_diff_addr, first_native, first_emu);
        /* Full dump on frame 100 (both sides settled), and on frames 0-4
         * for boot-state context. Later frames stay as summary-only. */
        if (g_frame_count < 5 || g_frame_count == 100 || g_frame_count == 500) {
            fprintf(stderr, "  [full dump of diffs at frame %llu]\n",
                    (unsigned long long)g_frame_count);
            int shown = 0;
            for (int i = 0; i < 0x0800 && shown < 128; i++) {
                if (g_ram[i] != emu_ram[i]) {
                    fprintf(stderr, "    $%04X  native=0x%02X  emu=0x%02X\n",
                            i, g_ram[i], emu_ram[i]);
                    shown++;
                }
            }
        }
    }

    return passed;
#else
    func_NMI();
    return 1;
#endif
}

uint64_t verify_mode_get_divergence_count(void) {
    return s_divergence_count;
}
