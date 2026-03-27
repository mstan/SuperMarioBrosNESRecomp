/*
 * watchdog.c — Frame timeout detection
 *
 * When a frame exceeds WATCHDOG_TIMEOUT_SECS, logs the call stack and
 * forces a VBlank trigger to break out of spin-wait loops. Does NOT
 * longjmp (unsafe from deeply nested generated code).
 */
#include "watchdog.h"
#include "nes_runtime.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef RECOMP_STACK_TRACKING
#include "recomp_stack.h"
#endif

/* Watchdog globals (defined in extras.c, read by debug server) */
extern int g_watchdog_triggered;
extern uint64_t g_watchdog_frame;
extern char g_watchdog_stack_dump[1024];

jmp_buf g_watchdog_jmp;
static clock_t s_frame_start = 0;

void watchdog_frame_start(void) {
    s_frame_start = clock();
}

void watchdog_check(void) {
    /* Call maybe_trigger_vblank() on every backward branch so that tight
     * loops without memory access still get VBlank callbacks. This is the
     * primary mechanism for preventing stuck frames. */
    maybe_trigger_vblank();

    clock_t now = clock();
    double elapsed = (double)(now - s_frame_start) / CLOCKS_PER_SEC;

    if (elapsed > WATCHDOG_TIMEOUT_SECS) {
        /* Only report once per frame to avoid log flooding */
        static uint64_t s_last_reported_frame = (uint64_t)-1;
        if (g_frame_count == s_last_reported_frame) return;
        s_last_reported_frame = g_frame_count;

        fprintf(stderr, "\n=== WATCHDOG: Frame %llu exceeded %.1fs ===\n",
                (unsigned long long)g_frame_count, elapsed);

#ifdef RECOMP_STACK_TRACKING
        fprintf(stderr, "Call stack (most recent first):\n");
        for (int i = g_recomp_stack_top - 1; i >= 0; i--) {
            fprintf(stderr, "  [%d] %s\n", i,
                    g_recomp_stack[i] ? g_recomp_stack[i] : "(null)");
        }
#else
        fprintf(stderr, "(no stack tracking compiled in)\n");
#endif
        fprintf(stderr, "CPU: A=%02X X=%02X Y=%02X S=%02X bank=%d\n",
                g_cpu.A, g_cpu.X, g_cpu.Y, g_cpu.S, g_current_bank);
        fprintf(stderr, "=== Continuing (forced VBlank trigger) ===\n\n");

        /* Set watchdog globals for debug server query */
        g_watchdog_triggered = 1;
        g_watchdog_frame = g_frame_count;
        g_watchdog_stack_dump[0] = '\0';
#ifdef RECOMP_STACK_TRACKING
        {
            int pos = 0;
            for (int i = g_recomp_stack_top - 1; i >= 0 && pos < 1000; i--) {
                pos += snprintf(g_watchdog_stack_dump + pos,
                                sizeof(g_watchdog_stack_dump) - pos,
                                "[%d] %s\n", i,
                                g_recomp_stack[i] ? g_recomp_stack[i] : "(null)");
            }
        }
#endif

        /* Reset the timer so we don't spam */
        s_frame_start = clock();
    }
}
