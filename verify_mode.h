/*
 * verify_mode.h — Dual-execution verification mode
 *
 * Runs both FCEUX oracle and native recompiled code each frame,
 * comparing results to detect divergences.
 */
#pragma once
#include <stdint.h>

typedef enum {
    RUN_MODE_NATIVE   = 0,  /* Pure recompiled code (default) */
    RUN_MODE_VERIFY   = 1,  /* Both paths, compare results */
    RUN_MODE_EMULATED = 2,  /* Pure FCEUX oracle, no recompiled code */
} RunMode;

/* Current run mode (set via --verify or --emulated CLI flags). */
extern RunMode g_run_mode;

/* Initialize verify mode. Call after FCEUX bridge init.
 * rom_path is needed to load the ROM into FCEUX. */
void verify_mode_init(const char *rom_path);

/* Run one NMI frame through the current mode.
 * In NATIVE mode: calls func_NMI() directly.
 * In VERIFY mode: snapshots → FCEUX NMI → snapshot → restore → native NMI → compare.
 * In EMULATED mode: calls FCEUX frame runner.
 * Returns 1 if verify passed (or not in verify mode), 0 if divergence detected. */
int verify_mode_run_nmi(void);

/* Get the number of divergences detected so far. */
uint64_t verify_mode_get_divergence_count(void);

/* ---- Divergence ring buffer ---------------------------------------------
 * Always-on ring of recent divergence events. The current frame's first
 * mismatched WRAM byte (with optional summary of how many total bytes
 * diverged that frame) is pushed when verify_mode_run_nmi detects a diff.
 *
 * Ring size is fixed at 256 entries — newest entries overwrite oldest.
 * Phase 3: the routine-replacement framework queries this via the TCP
 * `verify_diff_ring` command to attribute divergences to the routine
 * under test. The ring records every diff, not just diffs that occur
 * during a specific routine's window — per the global ring-buffer rule,
 * "always-on, query the window of interest."
 *
 * A divergence is recorded each frame the WRAMs disagree; if the same
 * disagreement persists across N frames, you get N ring entries (same
 * addr/values, different frame numbers).
 */
typedef struct {
    uint64_t frame;          /* g_frame_count at the time of the diff */
    uint16_t first_diff_addr;
    uint8_t  native_val;     /* recomp side */
    uint8_t  emu_val;        /* Nestopia oracle side */
    uint16_t total_diff_count; /* total mismatched bytes in this frame */
} VerifyDivergence;

#define VERIFY_DIVERGENCE_RING_SIZE 256

/* Number of divergence records ever pushed (monotonic). To read the most
 * recent N, scan backwards from this count modulo VERIFY_DIVERGENCE_RING_SIZE. */
uint64_t verify_mode_divergence_ring_total(void);

/* Read entry i, where i is interpreted modulo the ring. Returns 1 on
 * success, 0 if the ring is empty or i is older than the oldest live entry.
 * Caller should pre-clamp i against verify_mode_divergence_ring_total(). */
int verify_mode_divergence_ring_get(uint64_t i, VerifyDivergence *out);
