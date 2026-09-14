/*
 * z80.h -- Zilog Z80 interpreter for the Genesis sound CPU.
 *
 * Complete documented instruction set plus the undocumented behaviour real
 * software leans on (IXH/IXL/IYH/IYL operands, DDCB/FDCB register copies,
 * SLL, ED no-ops, the X/Y flag bits), with per-instruction T-state counts so
 * timing loops written for the hardware (the sound driver's DAC sample-rate
 * loops) run at the right speed. Interrupt mode 1 and 2, NMI and HALT are
 * modelled; the R register counts M1 cycles.
 *
 * Memory and I/O go through the host callbacks. The host advances time by
 * calling z80_step() until its cycle budget is spent.
 */
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Z80 Z80;

typedef uint8_t (*Z80ReadFn)(void *user, uint16_t addr);
typedef void (*Z80WriteFn)(void *user, uint16_t addr, uint8_t value);

struct Z80 {
    uint8_t a, f, b, c, d, e, h, l;
    uint8_t a_, f_, b_, c_, d_, e_, h_, l_;   /* shadow set */
    uint16_t ix, iy, sp, pc;
    uint16_t wz;                                /* MEMPTR */
    uint8_t i, r;
    uint8_t iff1, iff2, im;
    uint8_t halted;
    uint8_t ei_pending;    /* EI: interrupts accepted after the next instruction */
    uint8_t int_line;      /* /INT asserted (level) */
    uint8_t nmi_pending;   /* /NMI edge latched */
    uint8_t int_vector;    /* data bus value for IM 2 (and IM 0 RST) */
    uint64_t cycles;       /* total T-states executed */

    void *user;
    Z80ReadFn read;
    Z80WriteFn write;
    Z80ReadFn in;          /* optional; NULL reads $FF */
    Z80WriteFn out;        /* optional */
};

/* Power-on/reset state (PC=0, SP=$FFFF, interrupts disabled, IM 0). */
void z80_reset(Z80 *z);

/* Execute one instruction, or accept a pending interrupt. Returns T-states. */
int z80_step(Z80 *z);

#ifdef __cplusplus
}
#endif
