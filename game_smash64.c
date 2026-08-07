/*
 * game_smash64.c — SMB1 host adapter for the Smash 64 player replacement mod.
 *
 * ============================== STATUS ==============================
 * SCAFFOLD. The mod package, the dropdown, plugin activation, controller
 * selection, ownership policy and the always-on trace ring are wired end to
 * end. What is NOT wired is the part that would change the game: ownership
 * never rises above SPECTATE, and nothing is written back into SMB1 RAM.
 *
 * Enabling the mod today is observably a no-op on gameplay — by design.
 * SMB1 stays byte-identical while the plumbing is proven, so that when
 * physics does land, any behaviour change is attributable to the physics
 * and not to the scaffolding underneath it.
 * ====================================================================
 *
 * This file is the only place that may know both halves: SMB1's RAM map and
 * the fighter's motion. Everything NES-specific belongs here; the
 * controllers under mods/smash64/characters/ must stay portable.
 */
#include "game_smash64.h"

#include "foreign_controller.h"
#include "nes_runtime.h"

#include <stdio.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/* Scale                                                              */
/*                                                                    */
/* ONE uniform conversion between the fighter's world and SMB1's, so   */
/* the ported constants stay internally authentic. Never retune run    */
/* speed, jump speed, gravity and air acceleration individually to     */
/* make something feel right — that turns a port into a guess.         */
/*                                                                    */
/* Derived in M0 from a stable reference: fighter height against the   */
/* source's platform geometry, versus Mario's height against SMB1's    */
/* 16px metatile grid. Placeholder 1.0 until that measurement exists.  */
/* ------------------------------------------------------------------ */
#define FALCON_TO_SMB1_X   1.0
#define FALCON_TO_SMB1_Y   1.0
#define SMB1_TO_FALCON_X   (1.0 / FALCON_TO_SMB1_X)
#define SMB1_TO_FALCON_Y   (1.0 / FALCON_TO_SMB1_Y)

/* ------------------------------------------------------------------ */
/* SMB1 player state                                                  */
/*                                                                    */
/* Addresses are confirmed against Ghidra before anything reads or     */
/* writes them (framework RULE 0 — no guessing 6502 behaviour), and    */
/* every synchronization write gets recorded in                        */
/* docs/smb1_player_adapter.md. Nothing here is live yet.              */
/* ------------------------------------------------------------------ */

/* TODO(M2): player page/X, player Y, X/Y velocity, facing, ground/air
 * state, size/power state, and the scripted-state discriminators
 * (pipe, death, flagpole, level intro, castle sequence). */

/* ------------------------------------------------------------------ */
/* Mod state                                                          */
/* ------------------------------------------------------------------ */

static int  s_enabled = 0;
static char s_controller_id[96] = {0};
static int  s_selected = 0;      /* the id resolved to a real controller */
static int  s_announced = 0;

/* Rising-edge tracking for the digital -> analog adapter. */
static uint8_t s_prev_buttons = 0;

/* NES pad bits: bit7=A bit6=B bit5=Select bit4=Start
 *               bit3=Up bit2=Down bit1=Left bit0=Right */
#define PAD_A      0x80
#define PAD_B      0x40
#define PAD_UP     0x08
#define PAD_DOWN   0x04
#define PAD_LEFT   0x02
#define PAD_RIGHT  0x01

void game_smash64_set_mod_enabled(int enabled, const char *controller_id) {
    s_enabled = 0;
    s_selected = 0;
    s_announced = 0;
    s_controller_id[0] = '\0';
    nes_foreign_set_ownership(FOREIGN_OWNERSHIP_NATIVE);

    if (!enabled || !controller_id || !controller_id[0]) {
        nes_foreign_select(NULL);
        return;
    }

    snprintf(s_controller_id, sizeof s_controller_id, "%s", controller_id);
    s_selected = nes_foreign_select(s_controller_id);
    if (!s_selected) {
        /* Fail loudly. A silently-ignored character selection is exactly the
         * kind of thing that gets mistaken for "the physics is subtle". */
        fprintf(stderr,
                "[Smash64] No controller registered for '%s' — "
                "player replacement stays OFF\n", s_controller_id);
        return;
    }
    s_enabled = 1;
}

int game_smash64_active(void) {
    return s_enabled && s_selected &&
           nes_foreign_ownership() == FOREIGN_OWNERSHIP_FOREIGN;
}

void game_smash64_init(void) {
    if (!s_enabled) return;
    const ForeignController *ctl = nes_foreign_active();
    printf("[Smash64] Player replacement armed: %s (%s)\n",
           ctl && ctl->name ? ctl->name : "?", s_controller_id);
    /* ASCII only: the Windows console codepage mangles non-ASCII here. */
    printf("[Smash64] Locomotion is not implemented yet - SMB1 physics is "
           "unchanged. Movement traces: TCP 'ftring', or "
           "NESRECOMP_FTRING_DUMP=<path>.\n");
}

/* ------------------------------------------------------------------ */
/* Ownership                                                          */
/* ------------------------------------------------------------------ */

/*
 * SMB1 runs scripted player sequences — pipe entry/exit, death, the
 * flagpole, level intros, castle walks — that expect their own state
 * transitions. Those must stay native, so the fighter takes over only
 * during ordinary controllable play. Blanket-suppressing the player update
 * is never correct.
 *
 * M2 makes this real by reading SMB1's gameplay-mode and player-state
 * discriminators. Until then the adapter deliberately declines control, so
 * the scaffold cannot alter the game.
 */
static ForeignOwnership decide_ownership(void) {
    if (!s_enabled || !s_selected) return FOREIGN_OWNERSHIP_NATIVE;
    /* TODO(M2): return FOREIGN during ordinary play, SCRIPTED during pipe,
     * death, flagpole and intro sequences. */
    return FOREIGN_OWNERSHIP_NATIVE;
}

/* ------------------------------------------------------------------ */
/* Input                                                              */
/* ------------------------------------------------------------------ */

/*
 * SMB1's pad is digital; Smash 64 distinguishes walk from dash from run by
 * stick magnitude and timing. Full-deflection values are the starting
 * point, not the destination: the adapter keeps synthetic magnitudes so
 * partial-tilt behaviour stays reachable later (a run modifier, a tap-dash
 * detector, or a real analog stick through the pad layer).
 *
 * Transitions that pure digital input cannot reach are recorded in
 * docs/smb1_player_adapter.md rather than quietly dropped.
 */
static void sample_input(ForeignInput *out) {
    const uint8_t b = g_controller1_buttons;
    const uint8_t pressed = (uint8_t)(b & ~s_prev_buttons);

    memset(out, 0, sizeof *out);
    out->raw_buttons = b;

    const int left  = (b & PAD_LEFT)  != 0;
    const int right = (b & PAD_RIGHT) != 0;
    const int up    = (b & PAD_UP)    != 0;
    const int down  = (b & PAD_DOWN)  != 0;

    /* Opposing directions cancel, matching how the pad hardware is read. */
    out->stick_x = (float)((right ? 1 : 0) - (left ? 1 : 0));
    out->stick_y = (float)((up ? 1 : 0) - (down ? 1 : 0));

    out->jump_held      = (b & PAD_A) != 0;
    out->jump_pressed   = (pressed & PAD_A) != 0;
    out->down_pressed   = (pressed & PAD_DOWN) != 0;
    out->attack_pressed = (pressed & PAD_B) != 0;

    s_prev_buttons = b;
}

/* ------------------------------------------------------------------ */
/* Per-frame                                                          */
/* ------------------------------------------------------------------ */

void game_smash64_update_input(uint64_t frame_count) {
    if (!s_enabled || !s_selected) return;

    nes_foreign_set_ownership(decide_ownership());

    ForeignInput input;
    sample_input(&input);

    ForeignMoveResult move;
    if (!nes_foreign_tick(frame_count, &input, &move)) {
        /* Native or scripted ownership: SMB1 moves the player itself. The
         * tick above still recorded a trace row, so the ring shows the
         * handoff instead of a gap. */
        return;
    }

    /* TODO(M2/M3): sweep move.requested_dx/dy against SMB1's tiles via
     * nes_foreign_sweep(), then nes_foreign_resolve() with the outcome. */
    (void)move;
}

void game_smash64_update(uint64_t frame_count) {
    (void)frame_count;
    if (!s_enabled || !s_selected) return;

    if (!s_announced) {
        s_announced = 1;
        printf("[Smash64] Controller ticking; ownership=%d\n",
               (int)nes_foreign_ownership());
    }

    /* TODO(M2): project host state into SMB1's page+pixel coordinates and
     * write back only the variables SMB1 must observe, then report them:
     *     nes_foreign_trace_note_native(player_x, player_y);
     * Every such write gets documented in docs/smb1_player_adapter.md. */
}
