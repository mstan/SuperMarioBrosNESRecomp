/*
 * falcon_harness.c — deterministic trace harness for the ported Captain
 * Falcon locomotion. The M1 deliverable.
 *
 * Runs the state machine outside SMB1 entirely: no SDL, no NES, no PPU, no
 * recompiled 6502. Scripted input in, CSV out. That isolation is the point —
 * when M2 lands and something feels wrong, this tells you whether the
 * controller or the SMB1 adapter is at fault.
 *
 * The traces it emits are a REGRESSION baseline for our own port and scale
 * conversion, not proof against an external oracle. The oracle question is
 * settled differently: every unit in the closure is 100% matched in the
 * decomp, so the ported C is byte-exact to the original game and cannot
 * drift from it. See docs/falcon_movement_dependency.md §1.
 *
 *   falcon_harness <script> [--csv out.csv] [--scale 0.08]
 *
 * Script grammar, one command per line, '#' comments:
 *   frames <n>            advance n frames with the current input held
 *   stick_x <-80..80>     set synthetic stick X
 *   stick_y <-80..80>     set synthetic stick Y
 *   jump down|up          jump button state (edge is derived)
 *   attack down|up        attack button state (edge is derived)
 *   neutral               stick to 0,0 and both buttons up
 *   pos_y <units>         teleport above the floor (+y is up)
 *   host_impose_vy <v>    host imposes a vertical velocity for ONE frame
 *                         (stomp bounce, spring, killed jump), source units
 *   host_launch           host says airborne, cause = LAUNCHED
 *   host_fall             host says airborne, cause = FELL (walked off a ledge)
 *   host_land             host says grounded again
 *   expect_state <NAME>   assert the current state, non-zero exit on failure
 *   expect_attack <0|1>   assert whether a hitbox is active
 *   expect_damage <n>     assert the active hitbox damage
 *   expect_break <0|1>    assert the block-break property
 *   expect_vel_air_y <lo> <hi>  assert takeoff/air velocity is in [lo,hi]
 *   expect_peak_y <lo> <hi>     assert the highest pos_y since reset_peak
 *   reset_peak            start a new peak-height measurement here
 *   roundtrip             serialize/reset/deserialize the fighter in-place
 *   note <text>           annotate the trace
 *
 * expect_state alone cannot see a jump HEIGHT, and height is the whole point of
 * the short hop: a short hop and a full hop are both KNEEBEND then JUMP_F, and
 * a regression that silently full-hops every time passes every state assertion.
 * Hence the two numeric forms.
 *
 * The host_* commands stand in for a host game that keeps its own jump trigger
 * and ledge detection -- which is what SMB1 does. They are the only way to
 * reach the reconciliation branch at the top of falcon_tick; the fighter's own
 * kneebend path never goes through it.
 */
#include "../../mods/smash64/ssb_ported/falcon_locomotion.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Falcon units -> SMB1 pixels. Derived in
 * docs/falcon_movement_dependency.md §8 from his 400-unit collision diamond
 * against SMB1's 16px metatile grid. Overridable so the trace can show what a
 * different scale would do without touching the controller. */
static double g_scale = 0.08;

static FILE *g_csv;
static int   g_failures;
static long  g_frame;
static double g_peak_y;   /* highest pos_y since the last reset_peak */

/* One place to report a numeric assertion, so both forms read identically in
 * the CTest log and a failure prints the value that was actually produced. */
static void check_range(const char *what, double have, const char *arg)
{
    double lo = 0.0, hi = 0.0;

    if (sscanf(arg, "%lf %lf", &lo, &hi) != 2) {
        fprintf(stderr, "FAIL frame %ld: %s needs <lo> <hi>, got '%s'\n",
                g_frame, what, arg);
        g_failures++;
        return;
    }
    if (have < lo || have > hi) {
        fprintf(stderr, "FAIL frame %ld: %s = %.4f, expected [%.4f, %.4f]\n",
                g_frame, what, have, lo, hi);
        g_failures++;
    } else {
        printf("  ok  frame %-5ld %s = %.4f in [%.4f, %.4f]\n",
               g_frame, what, have, lo, hi);
    }
}

static void emit_header(void)
{
    fprintf(g_csv,
        "frame,state,state_name,anim_frame,stick_x,stick_y,jump,attack,"
        "vel_ground_x,vel_air_x,vel_air_y,"
        "req_dx,req_dy,px_dx,px_dy,hit_active,damage,break_blocks,"
        "pos_x,pos_y,lr,grounded,fastfall,tap_x,tap_y,note\n");
}

static void emit_row(const FalconFighter *f, const FalconInputRaw *in,
                     const FalconMotion *m, const char *note)
{
    fprintf(g_csv,
        "%ld,%d,%s,%.1f,%d,%d,%d,%d,"
        "%.6f,%.6f,%.6f,"
        "%.6f,%.6f,%.6f,%.6f,%d,%d,%d,"
        "%.6f,%.6f,%d,%d,%d,%u,%u,%s\n",
        g_frame, f->state, falcon_state_name(f->state), f->anim_frame,
        in->stick_x, in->stick_y, in->jump_held, in->attack_pressed,
        f->vel_ground_x, f->vel_air_x, f->vel_air_y,
        m->requested_dx, m->requested_dy,
        m->requested_dx * g_scale, m->requested_dy * g_scale,
        m->attack.active, m->attack.damage, m->attack.break_blocks,
        f->pos_x, f->pos_y, f->lr, f->grounded, f->is_fastfall,
        (unsigned)f->tap_stick_x, (unsigned)f->tap_stick_y,
        note ? note : "");
}

/*
 * Flat infinite floor at y = 0. Deliberately the simplest possible world:
 * the harness is testing the controller, not collision. M4 is where geometry
 * gets interesting.
 */
/* Set by host_impose_vy, consumed by the next single frame -- host vertical
 * events are one-frame impulses, exactly as SMB1 delivers them. */
static int    g_impose_pending;
static double g_impose_vy;

static void resolve_flat_floor(FalconFighter *f, const FalconMotion *m,
                               FalconCollision *hit)
{
    memset(hit, 0, sizeof(*hit));
    hit->actual_dx = m->requested_dx;
    hit->actual_dy = m->requested_dy;

    if (g_impose_pending) {
        hit->has_imposed_vy = 1;
        hit->imposed_vy = g_impose_vy;
        g_impose_pending = 0;
    }

    if (f->grounded) {
        hit->grounded = 1;
        hit->actual_dy = 0.0;
    } else if ((f->pos_y + m->requested_dy) <= 0.0) {
        /* Landing: stop exactly on the floor. */
        hit->actual_dy = -f->pos_y;
        hit->grounded = 1;
        hit->hit_floor = 1;
    }
}

static int run_script(const char *path)
{
    FalconFighter f;
    FalconInputRaw in;
    FalconMotion m;
    FalconCollision hit;
    char line[512];
    char pending_note[256];
    FILE *fp = fopen(path, "r");
    int jump_was_down = 0;
    int attack_is_down = 0;
    int attack_was_down = 0;

    if (!fp) { fprintf(stderr, "cannot open script: %s\n", path); return 2; }

    falcon_reset(&f);
    memset(&in, 0, sizeof(in));
    memset(&m, 0, sizeof(m));
    pending_note[0] = '\0';

    while (fgets(line, sizeof(line), fp)) {
        char *p = line;
        char cmd[64] = {0};
        char arg[128] = {0};

        while (*p == ' ' || *p == '\t') p++;
        if (*p == '#' || *p == '\n' || *p == '\r' || *p == '\0') continue;
        if (sscanf(p, "%63s %127[^\n\r]", cmd, arg) < 1) continue;

        if (!strcmp(cmd, "stick_x")) {
            in.stick_x = atoi(arg);
        } else if (!strcmp(cmd, "stick_y")) {
            in.stick_y = atoi(arg);
        } else if (!strcmp(cmd, "jump")) {
            in.jump_held = !strncmp(arg, "down", 4);
        } else if (!strcmp(cmd, "attack")) {
            attack_is_down = !strncmp(arg, "down", 4);
        } else if (!strcmp(cmd, "neutral")) {
            in.stick_x = in.stick_y = 0;
            in.jump_held = 0;
            attack_is_down = 0;
        } else if (!strcmp(cmd, "pos_y")) {
            /* Place the fighter above the flat floor, so a host-driven fall has
             * somewhere to fall from. +y is up in this world. */
            f.pos_y = atof(arg);
        } else if (!strcmp(cmd, "host_launch")) {
            /*
             * Simulate a host that owns its own jump trigger: it reports the
             * fighter airborne, with the cause set to LAUNCHED. This is exactly
             * what the SMB1 adapter does when InitJS sets Player_State = 1, and
             * it is the only way the reconciliation path in falcon_tick gets
             * exercised -- the fighter's own kneebend path never reaches it.
             */
            f.grounded = 0;
            f.host_air_cause = 1;   /* FOREIGN_AIR_LAUNCHED */
        } else if (!strcmp(cmd, "host_fall")) {
            /* Host walked us off a ledge: airborne, no impulse. */
            f.grounded = 0;
            f.host_air_cause = 2;   /* FOREIGN_AIR_FELL */
        } else if (!strcmp(cmd, "host_land")) {
            /* Host reports we are standing on something again. */
            f.grounded = 1;
            f.host_air_cause = 0;   /* FOREIGN_AIR_NONE */
        } else if (!strcmp(cmd, "note")) {
            snprintf(pending_note, sizeof(pending_note), "%s", arg);
        } else if (!strcmp(cmd, "expect_state")) {
            const char *have = falcon_state_name(f.state);
            char want[64] = {0};
            sscanf(arg, "%63s", want);
            if (strcmp(have, want) != 0) {
                fprintf(stderr,
                        "FAIL frame %ld: expected state %s, got %s\n",
                        g_frame, want, have);
                g_failures++;
            } else {
                printf("  ok  frame %-5ld state == %s\n", g_frame, want);
            }
        } else if (!strcmp(cmd, "expect_attack")) {
            check_range("attack_active", (double)m.attack.active, arg);
        } else if (!strcmp(cmd, "expect_damage")) {
            check_range("attack_damage", (double)m.attack.damage, arg);
        } else if (!strcmp(cmd, "expect_break")) {
            check_range("attack_break_blocks",
                        (double)m.attack.break_blocks, arg);
        } else if (!strcmp(cmd, "host_impose_vy")) {
            /*
             * Stand in for a host that launches the character for reasons the
             * fighter has no model of. SMB1 does this by storing its own
             * Player_Y_Speed -- a stomp bounce, a jumpspring, a shattered
             * brick, or a jump killed against a block -- and it is a ONE-FRAME
             * impulse, not a sustained state.
             */
            g_impose_pending = 1;
            g_impose_vy = atof(arg);
        } else if (!strcmp(cmd, "expect_vel_air_y")) {
            check_range("vel_air_y", f.vel_air_y, arg);
        } else if (!strcmp(cmd, "expect_peak_y")) {
            check_range("peak_y", g_peak_y, arg);
        } else if (!strcmp(cmd, "reset_peak")) {
            g_peak_y = f.pos_y;
        } else if (!strcmp(cmd, "roundtrip")) {
            FalconFighter before = f;
            uint8_t blob[1 + sizeof(FalconFighter)];
            int len = falcon_serialize(&f, blob, (int)sizeof(blob));
            falcon_reset(&f);
            if (len < 0 || !falcon_deserialize(&f, blob, len) ||
                memcmp(&before, &f, sizeof(f)) != 0) {
                fprintf(stderr, "FAIL frame %ld: fighter save roundtrip\n",
                        g_frame);
                g_failures++;
            } else {
                printf("  ok  frame %-5ld fighter save roundtrip\n", g_frame);
            }
        } else if (!strcmp(cmd, "frames")) {
            int n = atoi(arg), i;
            for (i = 0; i < n; i++) {
                /* Derive the button edge the way a real pad layer would. */
                in.jump_pressed = (in.jump_held && !jump_was_down);
                jump_was_down = in.jump_held;
                in.attack_pressed = (attack_is_down && !attack_was_down);
                attack_was_down = attack_is_down;

                falcon_tick(&f, &in, &m);
                resolve_flat_floor(&f, &m, &hit);
                falcon_resolve(&f, &hit);

                if (f.pos_y > g_peak_y) g_peak_y = f.pos_y;

                emit_row(&f, &in, &m, pending_note);
                pending_note[0] = '\0';
                g_frame++;
            }
        } else {
            fprintf(stderr, "unknown command: %s\n", cmd);
            g_failures++;
        }
    }
    fclose(fp);
    return 0;
}

int main(int argc, char **argv)
{
    const char *script = NULL;
    const char *csv = NULL;
    int i, rc;

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--csv") && i + 1 < argc)        csv = argv[++i];
        else if (!strcmp(argv[i], "--scale") && i + 1 < argc) g_scale = atof(argv[++i]);
        else script = argv[i];
    }
    if (!script) {
        fprintf(stderr,
            "usage: falcon_harness <script> [--csv out.csv] [--scale 0.08]\n");
        return 2;
    }

    g_csv = csv ? fopen(csv, "w") : stdout;
    if (!g_csv) { fprintf(stderr, "cannot write %s\n", csv); return 2; }

    printf("falcon_harness: %s (scale %.4f px/unit)\n", script, g_scale);
    emit_header();
    rc = run_script(script);
    if (g_csv != stdout) fclose(g_csv);

    if (rc) return rc;
    if (g_failures) {
        printf("FAILED: %d assertion(s)\n", g_failures);
        return 1;
    }
    printf("PASS (%ld frames)\n", g_frame);
    return 0;
}
