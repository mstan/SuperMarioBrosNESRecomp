// semcomp/cpu_flags.h — 6502 flag-update macros for verbatim ports.
//
// The recompiler emits these macros inline in the generated .c file
// (super-mario-bros_full.c, private to that translation unit). When
// we port a routine verbatim into semcomp, we re-define the same
// macros here so the pasted body compiles unchanged.
//
// MUST match super-mario-bros_full.c (see lines 13-19 there) exactly.
#pragma once

#ifdef __cplusplus
extern "C" {
#endif
// watchdog_check is referenced inside #ifdef WATCHDOG_ENABLED blocks emitted
// by the recompiler. When WATCHDOG_ENABLED is defined by the build, semcomp
// translation units need this extern declaration to find the symbol (which
// is defined in watchdog.c at the project root).
void watchdog_check(void);
#ifdef __cplusplus
}
#endif

#define FLAG_NZ(v) do { g_cpu.N=((v)>>7)&1; g_cpu.Z=((v)==0)?1:0; } while(0)

#define FLAG_NZC_ADD(r,a,b) do { uint16_t _r=(r); g_cpu.C=(_r>0xFF)?1:0;        \
    g_cpu.N=((_r>>7)&1); g_cpu.Z=((_r&0xFF)==0)?1:0;                            \
    g_cpu.V=(~((a)^(b))&((a)^_r)&0x80)?1:0; } while(0)

#define FLAG_NZC_SUB(r,a,b) do { int16_t _r=(r); g_cpu.C=(_r>=0)?1:0;            \
    g_cpu.N=((_r&0xFF)>>7); g_cpu.Z=((_r&0xFF)==0)?1:0;                          \
    g_cpu.V=(((a)^(b))&((a)^_r)&0x80)?1:0; } while(0)
