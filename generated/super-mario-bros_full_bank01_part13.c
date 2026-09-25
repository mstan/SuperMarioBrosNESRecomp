/* super-mario-bros_full_bank01_part13.c — PRG bank 1 function bodies (sub-part 13).
 * STANDALONE translation unit — compiled independently (in
 * parallel with every other bank part/sub-part and the
 * umbrella super-mario-bros_full.c). Do not compile as part of another TU or
 * edit directly; the source of truth is the recompiler's
 * code_generator.c. Renamed to drop the _partNN suffix if
 * this bank turned out to fit in a single sub-part. */

#include "super-mario-bros_full_decls.h"

void func_F50C_body(int _entry) {
    switch (_entry) {
        case 1: goto label_F5D1;
        case 2: goto label_F602;
        case 3: goto label_F538;
        case 4: goto label_F607;
        case 5: goto label_F621;
        case 6: goto label_F5F6;
        case 7: goto label_F5FC;
        case 8: goto label_F586;
        case 9: goto label_F5B2;
        case 10: goto label_F5F8;
        case 11: goto label_F5ED;
        case 12: goto label_F5E0;
        case 13: goto label_F5CF;
        case 14: goto label_F5EC;
        case 15: goto label_F5B9;
        case 16: goto label_F605;
    }
label_F50C:;
    /* $F50C: 1E */ nes_cpu_instruction_boundary(0xF50C, 7); { uint16_t a=(0x2C04 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F50F:;
    /* $F50F: 2E */ nes_cpu_instruction_boundary(0xF50F, 6); { uint16_t a=0x0420; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F512:;
    /* $F512: 2E */ nes_cpu_instruction_boundary(0xF512, 6); { uint16_t a=0x2230; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F515:;
    /* $F515: 04 */ nes_cpu_instruction_boundary(0xF515, 3); (void)nes_read(0x30); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F517:;
    /* $F517: 32 */ nes_cpu_instruction_boundary(0xF517, 2); /* ILLEGAL $32 — skip 1 */
label_F518:; /* PlayCoinGrab */
    /* $F518: A9 */ nes_cpu_instruction_boundary(0xF518, 2); g_cpu.A = 0x35; FLAG_NZ(g_cpu.A);
label_F51A:;
    /* $F51A: A2 */ nes_cpu_instruction_boundary(0xF51A, 2); g_cpu.X = 0x8D; FLAG_NZ(g_cpu.X);
label_F51C:;
    /* $F51C: D0 */ nes_cpu_instruction_boundary(0xF51C, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F522; }
label_F51E:; /* PlayTimerTick */
    /* $F51E: A9 */ nes_cpu_instruction_boundary(0xF51E, 2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_F520:;
    /* $F520: A2 */ nes_cpu_instruction_boundary(0xF520, 2); g_cpu.X = 0x98; FLAG_NZ(g_cpu.X);
label_F522:; /* CGrab_TTickRegL */
    /* $F522: 8D */ nes_cpu_instruction_boundary(0xF522, 4); nes_write(0x07BD, g_cpu.A);
label_F525:;
    /* $F525: A0 */ nes_cpu_instruction_boundary(0xF525, 2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_F527:;
    /* $F527: A9 */ nes_cpu_instruction_boundary(0xF527, 2); g_cpu.A = 0x42; FLAG_NZ(g_cpu.A);
label_F529:;
    /* $F529: 20 */ nes_cpu_instruction_boundary(0xF529, 6); func_F3A6();
label_F52C:; /* ContinueCGrabTTick */
    /* $F52C: AD */ nes_cpu_instruction_boundary(0xF52C, 4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F52F:;
    /* $F52F: C9 */ nes_cpu_instruction_boundary(0xF52F, 2); { int r=g_cpu.A-0x30; g_cpu.C=(g_cpu.A>=0x30)?1:0; FLAG_NZ(r&0xFF); }
label_F531:;
    /* $F531: D0 */ nes_cpu_instruction_boundary(0xF531, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F538; }
label_F533:;
    /* $F533: A9 */ nes_cpu_instruction_boundary(0xF533, 2); g_cpu.A = 0x54; FLAG_NZ(g_cpu.A);
label_F535:;
    /* $F535: 8D */ nes_cpu_instruction_boundary(0xF535, 4); nes_write(0x4006, g_cpu.A);
label_F538:; /* N2Tone */
    /* $F538: D0 */ nes_cpu_instruction_boundary(0xF538, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F568; }
label_F53A:; /* PlayBlast */
    /* $F53A: A9 */ nes_cpu_instruction_boundary(0xF53A, 2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_F53C:;
    /* $F53C: 8D */ nes_cpu_instruction_boundary(0xF53C, 4); nes_write(0x07BD, g_cpu.A);
label_F53F:;
    /* $F53F: A0 */ nes_cpu_instruction_boundary(0xF53F, 2); g_cpu.Y = 0x94; FLAG_NZ(g_cpu.Y);
label_F541:;
    /* $F541: A9 */ nes_cpu_instruction_boundary(0xF541, 2); g_cpu.A = 0x5E; FLAG_NZ(g_cpu.A);
label_F543:;
    /* $F543: D0 */ nes_cpu_instruction_boundary(0xF543, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F550; }
label_F545:; /* ContinueBlast */
    /* $F545: AD */ nes_cpu_instruction_boundary(0xF545, 4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F548:;
    /* $F548: C9 */ nes_cpu_instruction_boundary(0xF548, 2); { int r=g_cpu.A-0x18; g_cpu.C=(g_cpu.A>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_F54A:;
    /* $F54A: D0 */ nes_cpu_instruction_boundary(0xF54A, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F568; }
label_F54C:;
    /* $F54C: A0 */ nes_cpu_instruction_boundary(0xF54C, 2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_F54E:;
    /* $F54E: A9 */ nes_cpu_instruction_boundary(0xF54E, 2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_F550:; /* SBlasJ */
    /* $F550: D0 */ nes_cpu_instruction_boundary(0xF550, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F5D1; }
label_F552:; /* PlayPowerUpGrab */
    /* $F552: A9 */ nes_cpu_instruction_boundary(0xF552, 2); g_cpu.A = 0x36; FLAG_NZ(g_cpu.A);
label_F554:;
    /* $F554: 8D */ nes_cpu_instruction_boundary(0xF554, 4); nes_write(0x07BD, g_cpu.A);
label_F557:; /* ContinuePowerUpGrab */
    /* $F557: AD */ nes_cpu_instruction_boundary(0xF557, 4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F55A:;
    /* $F55A: 4A */ nes_cpu_instruction_boundary(0xF55A, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F55B:;
    /* $F55B: B0 */ nes_cpu_instruction_boundary(0xF55B, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_F568; }
label_F55D:;
    /* $F55D: A8 */ nes_cpu_instruction_boundary(0xF55D, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F55E:;
    /* $F55E: B9 */ nes_cpu_instruction_boundary(0xF55E, 4); g_cpu.A = nes_read((0xF4D9 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F561:;
    /* $F561: A2 */ nes_cpu_instruction_boundary(0xF561, 2); g_cpu.X = 0x5D; FLAG_NZ(g_cpu.X);
label_F563:;
    /* $F563: A0 */ nes_cpu_instruction_boundary(0xF563, 2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_F565:; /* LoadSqu2Regs */
    /* $F565: 20 */ nes_cpu_instruction_boundary(0xF565, 6); func_F3A6();
label_F568:; /* DecrementSfx2Length */
    /* $F568: CE */ nes_cpu_instruction_boundary(0xF568, 6); { uint16_t a=0x07BD; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F56B:;
    /* $F56B: D0 */ nes_cpu_instruction_boundary(0xF56B, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F57B; }
label_F56D:; /* EmptySfx2Buffer */
    /* $F56D: A2 */ nes_cpu_instruction_boundary(0xF56D, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_F56F:;
    /* $F56F: 86 */ nes_cpu_instruction_boundary(0xF56F, 3); nes_write(0xF2, g_cpu.X);
label_F571:; /* StopSquare2Sfx */
    /* $F571: A2 */ nes_cpu_instruction_boundary(0xF571, 2); g_cpu.X = 0x0D; FLAG_NZ(g_cpu.X);
label_F573:;
    /* $F573: 8E */ nes_cpu_instruction_boundary(0xF573, 4); nes_write(0x4015, g_cpu.X);
label_F576:;
    /* $F576: A2 */ nes_cpu_instruction_boundary(0xF576, 2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_F578:;
    /* $F578: 8E */ nes_cpu_instruction_boundary(0xF578, 4); nes_write(0x4015, g_cpu.X);
label_F57B:; /* ExSfx2 */
    /* $F57B: 60 */ nes_cpu_instruction_boundary(0xF57B, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_F57C:; /* Square2SfxHandler */
    /* $F57C: A5 */ nes_cpu_instruction_boundary(0xF57C, 3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_F57E:;
    /* $F57E: 29 */ nes_cpu_instruction_boundary(0xF57E, 2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_F580:;
    /* $F580: D0 */ nes_cpu_instruction_boundary(0xF580, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F5E7; }
label_F582:;
    /* $F582: A4 */ nes_cpu_instruction_boundary(0xF582, 3); g_cpu.Y = nes_read(0xFE); FLAG_NZ(g_cpu.Y);
label_F584:;
    /* $F584: F0 */ nes_cpu_instruction_boundary(0xF584, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F5A6; }
label_F586:;
    /* $F586: 84 */ nes_cpu_instruction_boundary(0xF586, 3); nes_write(0xF2, g_cpu.Y);
label_F588:;
    /* $F588: 30 */ nes_cpu_instruction_boundary(0xF588, 2); if (g_cpu.N) { maybe_trigger_vblank(1); goto label_F5C8; }
label_F58A:;
    /* $F58A: 46 */ nes_cpu_instruction_boundary(0xF58A, 5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F58C:;
    /* $F58C: B0 */ nes_cpu_instruction_boundary(0xF58C, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xF518, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F518;
    }
label_F58E:;
    /* $F58E: 46 */ nes_cpu_instruction_boundary(0xF58E, 5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F590:;
    /* $F590: B0 */ nes_cpu_instruction_boundary(0xF590, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_F5FC; }
label_F592:;
    /* $F592: 46 */ nes_cpu_instruction_boundary(0xF592, 5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F594:;
    /* $F594: B0 */ nes_cpu_instruction_boundary(0xF594, 2); if (g_cpu.C) { maybe_trigger_vblank(2); goto label_F600; }
label_F596:;
    /* $F596: 46 */ nes_cpu_instruction_boundary(0xF596, 5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F598:;
    /* $F598: B0 */ nes_cpu_instruction_boundary(0xF598, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xF53A, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F53A;
    }
label_F59A:;
    /* $F59A: 46 */ nes_cpu_instruction_boundary(0xF59A, 5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F59C:;
    /* $F59C: B0 */ nes_cpu_instruction_boundary(0xF59C, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xF51E, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F51E;
    }
label_F59E:;
    /* $F59E: 46 */ nes_cpu_instruction_boundary(0xF59E, 5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F5A0:;
    /* $F5A0: B0 */ nes_cpu_instruction_boundary(0xF5A0, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xF552, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F552;
    }
label_F5A2:;
    /* $F5A2: 46 */ nes_cpu_instruction_boundary(0xF5A2, 5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F5A4:;
    /* $F5A4: B0 */ nes_cpu_instruction_boundary(0xF5A4, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_F5E2; }
label_F5A6:; /* CheckSfx2Buffer */
    /* $F5A6: A5 */ nes_cpu_instruction_boundary(0xF5A6, 3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_F5A8:;
    /* $F5A8: F0 */ nes_cpu_instruction_boundary(0xF5A8, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F5C1; }
label_F5AA:;
    /* $F5AA: 30 */ nes_cpu_instruction_boundary(0xF5AA, 2); if (g_cpu.N) { maybe_trigger_vblank(1); goto label_F5D3; }
label_F5AC:;
    /* $F5AC: 4A */ nes_cpu_instruction_boundary(0xF5AC, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5AD:;
    /* $F5AD: B0 */ nes_cpu_instruction_boundary(0xF5AD, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_F5C2; }
label_F5AF:;
    /* $F5AF: 4A */ nes_cpu_instruction_boundary(0xF5AF, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B0:;
    /* $F5B0: B0 */ nes_cpu_instruction_boundary(0xF5B0, 2); if (g_cpu.C) { maybe_trigger_vblank(2); goto label_F60F; }
label_F5B2:;
    /* $F5B2: 4A */ nes_cpu_instruction_boundary(0xF5B2, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B3:;
    /* $F5B3: B0 */ nes_cpu_instruction_boundary(0xF5B3, 2); if (g_cpu.C) { maybe_trigger_vblank(2); goto label_F60F; }
label_F5B5:;
    /* $F5B5: 4A */ nes_cpu_instruction_boundary(0xF5B5, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B6:;
    /* $F5B6: B0 */ nes_cpu_instruction_boundary(0xF5B6, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xF545, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F545;
    }
label_F5B8:;
    /* $F5B8: 4A */ nes_cpu_instruction_boundary(0xF5B8, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B9:;
    /* $F5B9: B0 */ nes_cpu_instruction_boundary(0xF5B9, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_F5C2; }
label_F5BB:;
    /* $F5BB: 4A */ nes_cpu_instruction_boundary(0xF5BB, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5BC:;
    /* $F5BC: B0 */ nes_cpu_instruction_boundary(0xF5BC, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xF557, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F557;
    }
label_F5BE:;
    /* $F5BE: 4A */ nes_cpu_instruction_boundary(0xF5BE, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5BF:;
    /* $F5BF: B0 */ nes_cpu_instruction_boundary(0xF5BF, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_F5E7; }
label_F5C1:; /* ExS2H */
    /* $F5C1: 60 */ nes_cpu_instruction_boundary(0xF5C1, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_F5C2:; /* Cont_CGrab_TTick */
    /* $F5C2: 4C */ nes_cpu_instruction_boundary(0xF5C2, 3); goto label_F52C;
label_F5C8:; /* PlayBowserFall */
    /* $F5C8: A9 */ nes_cpu_instruction_boundary(0xF5C8, 2); g_cpu.A = 0x38; FLAG_NZ(g_cpu.A);
label_F5CA:;
    /* $F5CA: 8D */ nes_cpu_instruction_boundary(0xF5CA, 4); nes_write(0x07BD, g_cpu.A);
label_F5CD:;
    /* $F5CD: A0 */ nes_cpu_instruction_boundary(0xF5CD, 2); g_cpu.Y = 0xC4; FLAG_NZ(g_cpu.Y);
label_F5CF:;
    /* $F5CF: A9 */ nes_cpu_instruction_boundary(0xF5CF, 2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_F5D1:; /* BlstSJp */
    /* $F5D1: D0 */ nes_cpu_instruction_boundary(0xF5D1, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F5DE; }
label_F5D3:; /* ContinueBowserFall */
    /* $F5D3: AD */ nes_cpu_instruction_boundary(0xF5D3, 4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F5D6:;
    /* $F5D6: C9 */ nes_cpu_instruction_boundary(0xF5D6, 2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_F5D8:;
    /* $F5D8: D0 */ nes_cpu_instruction_boundary(0xF5D8, 2); if (!g_cpu.Z) {
    nes_cpu_instruction_boundary(0xF568, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F568;
    }
label_F5DA:;
    /* $F5DA: A0 */ nes_cpu_instruction_boundary(0xF5DA, 2); g_cpu.Y = 0xA4; FLAG_NZ(g_cpu.Y);
label_F5DC:;
    /* $F5DC: A9 */ nes_cpu_instruction_boundary(0xF5DC, 2); g_cpu.A = 0x5A; FLAG_NZ(g_cpu.A);
label_F5DE:; /* PBFRegs */
    /* $F5DE: A2 */ nes_cpu_instruction_boundary(0xF5DE, 2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_F5E0:; /* EL_LRegs */
    /* $F5E0: D0 */ nes_cpu_instruction_boundary(0xF5E0, 2); if (!g_cpu.Z) {
    nes_cpu_instruction_boundary(0xF565, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F565;
    }
label_F5E2:; /* PlayExtraLife */
    /* $F5E2: A9 */ nes_cpu_instruction_boundary(0xF5E2, 2); g_cpu.A = 0x30; FLAG_NZ(g_cpu.A);
label_F5E4:;
    /* $F5E4: 8D */ nes_cpu_instruction_boundary(0xF5E4, 4); nes_write(0x07BD, g_cpu.A);
label_F5E7:; /* ContinueExtraLife */
    /* $F5E7: AD */ nes_cpu_instruction_boundary(0xF5E7, 4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F5EA:;
    /* $F5EA: A2 */ nes_cpu_instruction_boundary(0xF5EA, 2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_F5EC:; /* DivLLoop */
    /* $F5EC: 4A */ nes_cpu_instruction_boundary(0xF5EC, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5ED:;
    /* $F5ED: B0 */ nes_cpu_instruction_boundary(0xF5ED, 2); if (g_cpu.C) { maybe_trigger_vblank(1); call_by_address(0xF5C5); return; }
label_F5EF:;
    /* $F5EF: CA */ nes_cpu_instruction_boundary(0xF5EF, 2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_F5F0:;
    /* $F5F0: D0 */ nes_cpu_instruction_boundary(0xF5F0, 2); if (!g_cpu.Z) {
    nes_cpu_instruction_boundary(0xF5EC, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F5EC;
    }
label_F5F2:;
    /* $F5F2: A8 */ nes_cpu_instruction_boundary(0xF5F2, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F5F3:;
    /* $F5F3: B9 */ nes_cpu_instruction_boundary(0xF5F3, 4); g_cpu.A = nes_read((0xF4D3 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F5F6:;
    /* $F5F6: A2 */ nes_cpu_instruction_boundary(0xF5F6, 2); g_cpu.X = 0x82; FLAG_NZ(g_cpu.X);
label_F5F8:;
    /* $F5F8: A0 */ nes_cpu_instruction_boundary(0xF5F8, 2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_F5FA:;
    /* $F5FA: D0 */ nes_cpu_instruction_boundary(0xF5FA, 2); if (!g_cpu.Z) {
    nes_cpu_instruction_boundary(0xF5E0, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F5E0;
    }
label_F5FC:; /* PlayGrowPowerUp */
    /* $F5FC: A9 */ nes_cpu_instruction_boundary(0xF5FC, 2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_F5FE:;
    /* $F5FE: D0 */ nes_cpu_instruction_boundary(0xF5FE, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_F602; }
label_F600:; /* PlayGrowVine */
    /* $F600: A9 */ nes_cpu_instruction_boundary(0xF600, 2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_F602:; /* GrowItemRegs */
    /* $F602: 8D */ nes_cpu_instruction_boundary(0xF602, 4); nes_write(0x07BD, g_cpu.A);
label_F605:;
    /* $F605: A9 */ nes_cpu_instruction_boundary(0xF605, 2); g_cpu.A = 0x7F; FLAG_NZ(g_cpu.A);
label_F607:;
    /* $F607: 8D */ nes_cpu_instruction_boundary(0xF607, 4); nes_write(0x4005, g_cpu.A);
label_F60A:;
    /* $F60A: A9 */ nes_cpu_instruction_boundary(0xF60A, 2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F60C:;
    /* $F60C: 8D */ nes_cpu_instruction_boundary(0xF60C, 4); nes_write(0x07BE, g_cpu.A);
label_F60F:; /* ContinueGrowItems */
    /* $F60F: EE */ nes_cpu_instruction_boundary(0xF60F, 6); { uint16_t a=0x07BE; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F612:;
    /* $F612: AD */ nes_cpu_instruction_boundary(0xF612, 4); g_cpu.A = nes_read(0x07BE); FLAG_NZ(g_cpu.A);
label_F615:;
    /* $F615: 4A */ nes_cpu_instruction_boundary(0xF615, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F616:;
    /* $F616: A8 */ nes_cpu_instruction_boundary(0xF616, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F617:;
    /* $F617: CC */ nes_cpu_instruction_boundary(0xF617, 4); { uint8_t m=nes_read(0x07BD); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_F61A:;
    /* $F61A: F0 */ nes_cpu_instruction_boundary(0xF61A, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_F628; }
label_F61C:;
    /* $F61C: A9 */ nes_cpu_instruction_boundary(0xF61C, 2); g_cpu.A = 0x9D; FLAG_NZ(g_cpu.A);
label_F61E:;
    /* $F61E: 8D */ nes_cpu_instruction_boundary(0xF61E, 4); nes_write(0x4004, g_cpu.A);
label_F621:;
    /* $F621: B9 */ nes_cpu_instruction_boundary(0xF621, 4); g_cpu.A = nes_read((0xF4F8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F624:;
    /* $F624: 20 */ nes_cpu_instruction_boundary(0xF624, 6); func_F3A9();
label_F627:;
    /* $F627: 60 */ nes_cpu_instruction_boundary(0xF627, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_F628:; /* StopGrowItems */
    /* $F628: 4C */ nes_cpu_instruction_boundary(0xF628, 3); goto label_F56D;
}

void func_F50C(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F50C");
#endif
    func_F50C_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F5D1(void) { /* BlstSJp */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F5D1");
#endif
    func_F50C_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F602(void) { /* GrowItemRegs */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F602");
#endif
    func_F50C_body(2);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F538(void) { /* N2Tone */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F538");
#endif
    func_F50C_body(3);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F607(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F607");
#endif
    func_F50C_body(4);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F621(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F621");
#endif
    func_F50C_body(5);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F5F6(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F5F6");
#endif
    func_F50C_body(6);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F5FC(void) { /* PlayGrowPowerUp */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F5FC");
#endif
    func_F50C_body(7);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F586(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F586");
#endif
    func_F50C_body(8);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F5B2(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F5B2");
#endif
    func_F50C_body(9);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F5F8(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F5F8");
#endif
    func_F50C_body(10);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F5ED(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F5ED");
#endif
    func_F50C_body(11);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F5E0(void) { /* EL_LRegs */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F5E0");
#endif
    func_F50C_body(12);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F5CF(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F5CF");
#endif
    func_F50C_body(13);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F5EC(void) { /* DivLLoop */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F5EC");
#endif
    func_F50C_body(14);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F5B9(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F5B9");
#endif
    func_F50C_body(15);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_F605(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_F605");
#endif
    func_F50C_body(16);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_BD0C_b1_body(int _entry) {
    switch (_entry) {
        case 1: goto label_BD35;
        case 2: goto label_BEDB;
    }
label_BD0C:;
    /* $BD0C: 30 */ nes_cpu_instruction_boundary(0xBD0C, 2); if (g_cpu.N) { maybe_trigger_vblank(1); call_by_address(0xBD3E); return; }
label_BD0E:;
    /* $BD0E: 30 */ nes_cpu_instruction_boundary(0xBD0E, 2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xBC90); return; }
label_BD10:;
    /* $BD10: 2C */ nes_cpu_instruction_boundary(0xBD10, 4); { uint8_t m=nes_read(0x1482); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD13:;
    /* $BD13: 2C */ nes_cpu_instruction_boundary(0xBD13, 4); { uint8_t m=nes_read(0x2662); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD16:;
    /* $BD16: 10 */ nes_cpu_instruction_boundary(0xBD16, 2); if (!g_cpu.N) { maybe_trigger_vblank(1); goto label_BD40; }
label_BD18:;
    /* $BD18: 80 */ nes_cpu_instruction_boundary(0xBD18, 2); /* NOP */
label_BD1A:; /* ChkBrick */
    /* $BD1A: 82 */ nes_cpu_instruction_boundary(0xBD1A, 2); /* NOP */
label_BD1C:;
    /* $BD1C: 2C */ nes_cpu_instruction_boundary(0xBD1C, 4); { uint8_t m=nes_read(0x2662); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD1F:;
    /* $BD1F: 10 */ nes_cpu_instruction_boundary(0xBD1F, 2); if (!g_cpu.N) { maybe_trigger_vblank(1); call_by_address(0xBD49); return; }
label_BD21:;
    /* $BD21: 80 */ nes_cpu_instruction_boundary(0xBD21, 2); /* NOP */
label_BD23:;
    /* $BD23: 82 */ nes_cpu_instruction_boundary(0xBD23, 2); /* NOP */
label_BD25:;
    /* $BD25: 1E */ nes_cpu_instruction_boundary(0xBD25, 7); { uint16_t a=(0x185E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD28:;
    /* $BD28: 60 */ nes_cpu_instruction_boundary(0xBD28, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_BD29:;
    /* $BD29: 1A */ nes_cpu_instruction_boundary(0xBD29, 2); /* NOP */
label_BD2A:;
    /* $BD2A: 80 */ nes_cpu_instruction_boundary(0xBD2A, 2); /* NOP */
label_BD2C:; /* StartBTmr */
    /* $BD2C: 82 */ nes_cpu_instruction_boundary(0xBD2C, 2); /* NOP */
label_BD2E:;
    /* $BD2E: 1E */ nes_cpu_instruction_boundary(0xBD2E, 7); { uint16_t a=(0x185E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD31:;
    /* $BD31: 60 */ nes_cpu_instruction_boundary(0xBD31, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_BD32:;
    /* $BD32: 1A */ nes_cpu_instruction_boundary(0xBD32, 2); /* NOP */
label_BD33:;
    /* $BD33: 86 */ nes_cpu_instruction_boundary(0xBD33, 3); nes_write(0x04, g_cpu.X);
label_BD35:;
    /* $BD35: 83 */ nes_cpu_instruction_boundary(0xBD35, 6); nes_write(nes_read16zp((0x1A + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_BD37:;
    /* $BD37: 18 */ nes_cpu_instruction_boundary(0xBD37, 2); g_cpu.C = 0;
label_BD38:;
    /* $BD38: 16 */ nes_cpu_instruction_boundary(0xBD38, 6); { uint16_t a=(0x84 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD3A:;
    /* $BD3A: 14 */ nes_cpu_instruction_boundary(0xBD3A, 4); (void)nes_read((0x1A + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD3C:;
    /* $BD3C: 18 */ nes_cpu_instruction_boundary(0xBD3C, 2); g_cpu.C = 0;
label_BD3D:;
    /* $BD3D: 0E */ nes_cpu_instruction_boundary(0xBD3D, 6); { uint16_t a=0x160C; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD40:; /* PutOldMT */
    /* $BD40: 83 */ nes_cpu_instruction_boundary(0xBD40, 6); nes_write(nes_read16zp((0x14 + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_BD42:;
    /* $BD42: 20 */ nes_cpu_instruction_boundary(0xBD42, 6); nes_dispatch_call(0x1C1E, -1);
label_BD45:;
    /* $BD45: 28 */ nes_cpu_instruction_boundary(0xBD45, 4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BD46:;
    /* $BD46: 26 */ nes_cpu_instruction_boundary(0xBD46, 5); { uint16_t a=0x87; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD48:;
    /* $BD48: 24 */ nes_cpu_instruction_boundary(0xBD48, 3); { uint8_t m=nes_read(0x1A); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD4A:;
    /* $BD4A: 12 */ nes_cpu_instruction_boundary(0xBD4A, 2); /* ILLEGAL $12 — skip 1 */
label_BD4B:;
    /* $BD4B: 10 */ nes_cpu_instruction_boundary(0xBD4B, 2); if (!g_cpu.N) { maybe_trigger_vblank(1); goto label_BDAF; }
label_BD4D:;
    /* $BD4D: 0E */ nes_cpu_instruction_boundary(0xBD4D, 6); { uint16_t a=0x0480; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD50:;
    /* $BD50: 04 */ nes_cpu_instruction_boundary(0xBD50, 3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD52:;
    /* $BD52: 82 */ nes_cpu_instruction_boundary(0xBD52, 2); /* NOP */
label_BD54:;
    /* $BD54: 1C */ nes_cpu_instruction_boundary(0xBD54, 4); (void)nes_read((0x2220 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD57:;
    /* $BD57: 26 */ nes_cpu_instruction_boundary(0xBD57, 5); { uint16_t a=0x28; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD59:;
    /* $BD59: 81 */ nes_cpu_instruction_boundary(0xBD59, 6); nes_write(nes_read16zp((0x2A + g_cpu.X) & 0xFF), g_cpu.A);
label_BD5B:;
    /* $BD5B: 2A */ nes_cpu_instruction_boundary(0xBD5B, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BD5C:;
    /* $BD5C: 2A */ nes_cpu_instruction_boundary(0xBD5C, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BD5D:;
    /* $BD5D: 04 */ nes_cpu_instruction_boundary(0xBD5D, 3); (void)nes_read(0x2A); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD5F:;
    /* $BD5F: 04 */ nes_cpu_instruction_boundary(0xBD5F, 3); (void)nes_read(0x83); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD61:; /* SmallBP */
    /* $BD61: 2A */ nes_cpu_instruction_boundary(0xBD61, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BD62:; /* BigBP */
    /* $BD62: 82 */ nes_cpu_instruction_boundary(0xBD62, 2); /* NOP */
label_BD64:;
    /* $BD64: 86 */ nes_cpu_instruction_boundary(0xBD64, 3); nes_write(0x34, g_cpu.X);
label_BD66:;
    /* $BD66: 32 */ nes_cpu_instruction_boundary(0xBD66, 2); /* ILLEGAL $32 — skip 1 */
label_BD67:;
    /* $BD67: 34 */ nes_cpu_instruction_boundary(0xBD67, 4); (void)nes_read((0x81 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD69:;
    /* $BD69: 04 */ nes_cpu_instruction_boundary(0xBD69, 3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD6B:;
    /* $BD6B: 26 */ nes_cpu_instruction_boundary(0xBD6B, 5); { uint16_t a=0x2A; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD6D:;
    /* $BD6D: 2C */ nes_cpu_instruction_boundary(0xBD6D, 4); { uint8_t m=nes_read(0x8630); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD70:;
    /* $BD70: 34 */ nes_cpu_instruction_boundary(0xBD70, 4); (void)nes_read((0x83 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD72:;
    /* $BD72: 32 */ nes_cpu_instruction_boundary(0xBD72, 2); /* ILLEGAL $32 — skip 1 */
label_BD73:;
    /* $BD73: 82 */ nes_cpu_instruction_boundary(0xBD73, 2); /* NOP */
label_BD75:;
    /* $BD75: 84 */ nes_cpu_instruction_boundary(0xBD75, 3); nes_write(0x34, g_cpu.Y);
label_BD77:;
    /* $BD77: 85 */ nes_cpu_instruction_boundary(0xBD77, 3); nes_write(0x04, g_cpu.A);
label_BD79:;
    /* $BD79: 81 */ nes_cpu_instruction_boundary(0xBD79, 6); nes_write(nes_read16zp((0x22 + g_cpu.X) & 0xFF), g_cpu.A);
label_BD7B:; /* InvOBit */
    /* $BD7B: 86 */ nes_cpu_instruction_boundary(0xBD7B, 3); nes_write(0x30, g_cpu.X);
label_BD7D:;
    /* $BD7D: 2E */ nes_cpu_instruction_boundary(0xBD7D, 6); { uint16_t a=0x8130; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD80:;
    /* $BD80: 04 */ nes_cpu_instruction_boundary(0xBD80, 3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD82:;
    /* $BD82: 26 */ nes_cpu_instruction_boundary(0xBD82, 5); { uint16_t a=0x2A; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD84:; /* InitBlock_XY_Pos */
    /* $BD84: 2C */ nes_cpu_instruction_boundary(0xBD84, 4); { uint8_t m=nes_read(0x862E); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD87:;
    /* $BD87: 30 */ nes_cpu_instruction_boundary(0xBD87, 2); if (g_cpu.N) {
    nes_cpu_instruction_boundary(0xBD0C, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BD0C;
    }
label_BD89:;
    /* $BD89: 22 */ nes_cpu_instruction_boundary(0xBD89, 2); /* ILLEGAL $22 — skip 1 */
label_BD8A:;
    /* $BD8A: 82 */ nes_cpu_instruction_boundary(0xBD8A, 2); /* NOP */
label_BD8C:;
    /* $BD8C: 84 */ nes_cpu_instruction_boundary(0xBD8C, 3); nes_write(0x34, g_cpu.Y);
label_BD8E:;
    /* $BD8E: 85 */ nes_cpu_instruction_boundary(0xBD8E, 3); nes_write(0x04, g_cpu.A);
label_BD90:;
    /* $BD90: 81 */ nes_cpu_instruction_boundary(0xBD90, 6); nes_write(nes_read16zp((0x22 + g_cpu.X) & 0xFF), g_cpu.A);
label_BD92:;
    /* $BD92: 86 */ nes_cpu_instruction_boundary(0xBD92, 3); nes_write(0x3A, g_cpu.X);
label_BD94:;
    /* $BD94: 3A */ nes_cpu_instruction_boundary(0xBD94, 2); /* NOP */
label_BD95:;
    /* $BD95: 3A */ nes_cpu_instruction_boundary(0xBD95, 2); /* NOP */
label_BD96:;
    /* $BD96: 82 */ nes_cpu_instruction_boundary(0xBD96, 2); /* NOP */
label_BD98:;
    /* $BD98: 81 */ nes_cpu_instruction_boundary(0xBD98, 6); nes_write(nes_read16zp((0x40 + g_cpu.X) & 0xFF), g_cpu.A);
label_BD9A:;
    /* $BD9A: 82 */ nes_cpu_instruction_boundary(0xBD9A, 2); /* NOP */
label_BD9C:;
    /* $BD9C: 81 */ nes_cpu_instruction_boundary(0xBD9C, 6); nes_write(nes_read16zp((0x3A + g_cpu.X) & 0xFF), g_cpu.A);
label_BD9E:;
    /* $BD9E: 86 */ nes_cpu_instruction_boundary(0xBD9E, 3); nes_write(0x36, g_cpu.X);
label_BDA0:;
    /* $BDA0: 36 */ nes_cpu_instruction_boundary(0xBDA0, 6); { uint16_t a=(0x36 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BDA2:;
    /* $BDA2: 82 */ nes_cpu_instruction_boundary(0xBDA2, 2); /* NOP */
label_BDA4:;
    /* $BDA4: 81 */ nes_cpu_instruction_boundary(0xBDA4, 6); nes_write(nes_read16zp((0x3A + g_cpu.X) & 0xFF), g_cpu.A);
label_BDA6:;
    /* $BDA6: 82 */ nes_cpu_instruction_boundary(0xBDA6, 2); /* NOP */
label_BDA8:;
    /* $BDA8: 81 */ nes_cpu_instruction_boundary(0xBDA8, 6); nes_write(nes_read16zp((0x36 + g_cpu.X) & 0xFF), g_cpu.A);
label_BDAA:;
    /* $BDAA: 86 */ nes_cpu_instruction_boundary(0xBDAA, 3); nes_write(0x34, g_cpu.X);
label_BDAC:;
    /* $BDAC: 82 */ nes_cpu_instruction_boundary(0xBDAC, 2); /* NOP */
label_BDAE:;
    /* $BDAE: 2A */ nes_cpu_instruction_boundary(0xBDAE, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BDAF:;
    /* $BDAF: 36 */ nes_cpu_instruction_boundary(0xBDAF, 6); { uint16_t a=(0x81 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BDB1:;
    /* $BDB1: 34 */ nes_cpu_instruction_boundary(0xBDB1, 4); (void)nes_read((0x34 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BDB3:;
    /* $BDB3: 85 */ nes_cpu_instruction_boundary(0xBDB3, 3); nes_write(0x34, g_cpu.A);
label_BDB5:;
    /* $BDB5: 81 */ nes_cpu_instruction_boundary(0xBDB5, 6); nes_write(nes_read16zp((0x2A + g_cpu.X) & 0xFF), g_cpu.A);
label_BDB7:;
    /* $BDB7: 86 */ nes_cpu_instruction_boundary(0xBDB7, 3); nes_write(0x2C, g_cpu.X);
label_BDB9:;
    /* $BDB9: 00 */ nes_cpu_instruction_boundary(0xBDB9, 7); nes_brk_executed(0xBDB9); return;
label_BDBA:;
    /* $BDBA: 84 */ nes_cpu_instruction_boundary(0xBDBA, 3); nes_write(0x90, g_cpu.Y);
label_BDBC:;
    /* $BDBC: B0 */ nes_cpu_instruction_boundary(0xBDBC, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xBD42, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BD42;
    }
label_BDBE:;
    /* $BDBE: 50 */ nes_cpu_instruction_boundary(0xBDBE, 2); if (!g_cpu.V) { maybe_trigger_vblank(2); call_by_address(0xBE10); return; }
label_BDC0:;
    /* $BDC0: B0 */ nes_cpu_instruction_boundary(0xBDC0, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_BDC2; }
label_BDC2:;
    /* $BDC2: 98 */ nes_cpu_instruction_boundary(0xBDC2, 2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_BDC3:;
    /* $BDC3: 96 */ nes_cpu_instruction_boundary(0xBDC3, 4); nes_write((0x94 + g_cpu.Y) & 0xFF, g_cpu.X);
label_BDC5:;
    /* $BDC5: 92 */ nes_cpu_instruction_boundary(0xBDC5, 2); /* ILLEGAL $92 — skip 1 */
label_BDC6:;
    /* $BDC6: 94 */ nes_cpu_instruction_boundary(0xBDC6, 4); nes_write((0x96 + g_cpu.X) & 0xFF, g_cpu.Y);
label_BDC8:;
    /* $BDC8: 58 */ nes_cpu_instruction_boundary(0xBDC8, 2); g_cpu.I = 0;
label_BDC9:;
    /* $BDC9: 58 */ nes_cpu_instruction_boundary(0xBDC9, 2); g_cpu.I = 0;
label_BDCA:;
    /* $BDCA: 58 */ nes_cpu_instruction_boundary(0xBDCA, 2); g_cpu.I = 0;
label_BDCB:;
    /* $BDCB: 44 */ nes_cpu_instruction_boundary(0xBDCB, 3); (void)nes_read(0x5C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BDCD:;
    /* $BDCD: 44 */ nes_cpu_instruction_boundary(0xBDCD, 3); (void)nes_read(0x9F); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BDCF:;
    /* $BDCF: A3 */ nes_cpu_instruction_boundary(0xBDCF, 6); g_cpu.A = g_cpu.X = nes_read(nes_read16zp((0xA1 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BDD1:;
    /* $BDD1: A3 */ nes_cpu_instruction_boundary(0xBDD1, 6); g_cpu.A = g_cpu.X = nes_read(nes_read16zp((0x85 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BDD3:;
    /* $BDD3: A3 */ nes_cpu_instruction_boundary(0xBDD3, 6); g_cpu.A = g_cpu.X = nes_read(nes_read16zp((0xE0 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BDD5:; /* StarBlock */
    /* $BDD5: A6 */ nes_cpu_instruction_boundary(0xBDD5, 3); g_cpu.X = nes_read(0x23); FLAG_NZ(g_cpu.X);
label_BDD7:;
    /* $BDD7: C4 */ nes_cpu_instruction_boundary(0xBDD7, 3); { uint8_t m=nes_read(0x9F); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_BDD9:;
    /* $BDD9: 9D */ nes_cpu_instruction_boundary(0xBDD9, 5); nes_write((0x859F + g_cpu.X) & 0xFFFF, g_cpu.A);
label_BDDC:;
    /* $BDDC: 9F */ nes_cpu_instruction_boundary(0xBDDC, 5); /* ILLEGAL $9F — skip 3 */
label_BDDF:; /* VineBlock */
    /* $BDDF: 23 */ nes_cpu_instruction_boundary(0xBDDF, 8); { uint16_t a=nes_read16zp((0xC4 + g_cpu.X) & 0xFF); uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); g_cpu.A&=v; FLAG_NZ(g_cpu.A); }
label_BDE1:;
    /* $BDE1: B5 */ nes_cpu_instruction_boundary(0xBDE1, 4); g_cpu.A = nes_read((0xB1 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_BDE3:;
    /* $BDE3: AF */ nes_cpu_instruction_boundary(0xBDE3, 4); g_cpu.A = g_cpu.X = nes_read(0xB185); FLAG_NZ(g_cpu.A);
label_BDE6:;
    /* $BDE6: AF */ nes_cpu_instruction_boundary(0xBDE6, 4); g_cpu.A = g_cpu.X = nes_read(0x85AD); FLAG_NZ(g_cpu.A);
label_BDE9:;
    /* $BDE9: 95 */ nes_cpu_instruction_boundary(0xBDE9, 4); nes_write((0x9E + g_cpu.X) & 0xFF, g_cpu.A);
label_BDEB:;
    /* $BDEB: A2 */ nes_cpu_instruction_boundary(0xBDEB, 2); g_cpu.X = 0xAA; FLAG_NZ(g_cpu.X);
label_BDED:;
    /* $BDED: 6A */ nes_cpu_instruction_boundary(0xBDED, 2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_BDEE:;
    /* $BDEE: 6A */ nes_cpu_instruction_boundary(0xBDEE, 2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_BDEF:;
    /* $BDEF: 6B */ nes_cpu_instruction_boundary(0xBDEF, 2); { g_cpu.A &= 0x5E; uint8_t c=g_cpu.C; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); g_cpu.C=(g_cpu.A>>6)&1; g_cpu.V=(((g_cpu.A>>6)&1)^((g_cpu.A>>5)&1)); }
label_BDF1:;
    /* $BDF1: 9D */ nes_cpu_instruction_boundary(0xBDF1, 5); nes_write((0x0484 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_BDF4:;
    /* $BDF4: 04 */ nes_cpu_instruction_boundary(0xBDF4, 3); (void)nes_read(0x82); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BDF6:; /* BlockBumpedChk */
    /* $BDF6: 22 */ nes_cpu_instruction_boundary(0xBDF6, 2); /* ILLEGAL $22 — skip 1 */
label_BDF7:;
    /* $BDF7: 86 */ nes_cpu_instruction_boundary(0xBDF7, 3); nes_write(0x22, g_cpu.X);
label_BDF9:;
    /* $BDF9: 82 */ nes_cpu_instruction_boundary(0xBDF9, 2); /* NOP */
label_BDFB:;
    /* $BDFB: 22 */ nes_cpu_instruction_boundary(0xBDFB, 2); /* ILLEGAL $22 — skip 1 */
label_BDFC:;
    /* $BDFC: 2C */ nes_cpu_instruction_boundary(0xBDFC, 4); { uint8_t m=nes_read(0x2212); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BDFF:;
    /* $BDFF: 2A */ nes_cpu_instruction_boundary(0xBDFF, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE00:;
    /* $BE00: 14 */ nes_cpu_instruction_boundary(0xBE00, 4); (void)nes_read((0x22 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE02:; /* BrickShatter */
    /* $BE02: 2C */ nes_cpu_instruction_boundary(0xBE02, 4); { uint8_t m=nes_read(0x221C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE05:;
    /* $BE05: 2C */ nes_cpu_instruction_boundary(0xBE05, 4); { uint8_t m=nes_read(0x2214); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE08:;
    /* $BE08: 2C */ nes_cpu_instruction_boundary(0xBE08, 4); { uint8_t m=nes_read(0x2212); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE0B:;
    /* $BE0B: 2A */ nes_cpu_instruction_boundary(0xBE0B, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE0C:;
    /* $BE0C: 14 */ nes_cpu_instruction_boundary(0xBE0C, 4); (void)nes_read((0x22 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE0E:;
    /* $BE0E: 2C */ nes_cpu_instruction_boundary(0xBE0E, 4); { uint8_t m=nes_read(0x221C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE11:;
    /* $BE11: 2C */ nes_cpu_instruction_boundary(0xBE11, 4); { uint8_t m=nes_read(0x2218); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE14:;
    /* $BE14: 2A */ nes_cpu_instruction_boundary(0xBE14, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE15:;
    /* $BE15: 16 */ nes_cpu_instruction_boundary(0xBE15, 6); { uint16_t a=(0x20 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE17:;
    /* $BE17: 28 */ nes_cpu_instruction_boundary(0xBE17, 4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BE18:;
    /* $BE18: 18 */ nes_cpu_instruction_boundary(0xBE18, 2); g_cpu.C = 0;
label_BE19:;
    /* $BE19: 22 */ nes_cpu_instruction_boundary(0xBE19, 2); /* ILLEGAL $22 — skip 1 */
label_BE1A:;
    /* $BE1A: 2A */ nes_cpu_instruction_boundary(0xBE1A, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE1B:;
    /* $BE1B: 12 */ nes_cpu_instruction_boundary(0xBE1B, 2); /* ILLEGAL $12 — skip 1 */
label_BE1C:;
    /* $BE1C: 22 */ nes_cpu_instruction_boundary(0xBE1C, 2); /* ILLEGAL $22 — skip 1 */
label_BE1D:;
    /* $BE1D: 2A */ nes_cpu_instruction_boundary(0xBE1D, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE1E:;
    /* $BE1E: 18 */ nes_cpu_instruction_boundary(0xBE1E, 2); g_cpu.C = 0;
label_BE1F:; /* CheckTopOfBlock */
    /* $BE1F: 22 */ nes_cpu_instruction_boundary(0xBE1F, 2); /* ILLEGAL $22 — skip 1 */
label_BE20:;
    /* $BE20: 2A */ nes_cpu_instruction_boundary(0xBE20, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE21:;
    /* $BE21: 12 */ nes_cpu_instruction_boundary(0xBE21, 2); /* ILLEGAL $12 — skip 1 */
label_BE22:;
    /* $BE22: 22 */ nes_cpu_instruction_boundary(0xBE22, 2); /* ILLEGAL $22 — skip 1 */
label_BE23:;
    /* $BE23: 2A */ nes_cpu_instruction_boundary(0xBE23, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE24:;
    /* $BE24: 14 */ nes_cpu_instruction_boundary(0xBE24, 4); (void)nes_read((0x22 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE26:;
    /* $BE26: 2C */ nes_cpu_instruction_boundary(0xBE26, 4); { uint8_t m=nes_read(0x220C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE29:;
    /* $BE29: 2C */ nes_cpu_instruction_boundary(0xBE29, 4); { uint8_t m=nes_read(0x2214); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE2C:;
    /* $BE2C: 34 */ nes_cpu_instruction_boundary(0xBE2C, 4); (void)nes_read((0x12 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE2E:;
    /* $BE2E: 22 */ nes_cpu_instruction_boundary(0xBE2E, 2); /* ILLEGAL $22 — skip 1 */
label_BE2F:;
    /* $BE2F: 30 */ nes_cpu_instruction_boundary(0xBE2F, 2); if (g_cpu.N) { maybe_trigger_vblank(1); goto label_BE41; }
label_BE31:;
    /* $BE31: 22 */ nes_cpu_instruction_boundary(0xBE31, 2); /* ILLEGAL $22 — skip 1 */
label_BE32:;
    /* $BE32: 2E */ nes_cpu_instruction_boundary(0xBE32, 6); { uint16_t a=0x2216; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE35:;
    /* $BE35: 34 */ nes_cpu_instruction_boundary(0xBE35, 4); (void)nes_read((0x18 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE37:;
    /* $BE37: 26 */ nes_cpu_instruction_boundary(0xBE37, 5); { uint16_t a=0x36; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE39:;
    /* $BE39: 16 */ nes_cpu_instruction_boundary(0xBE39, 6); { uint16_t a=(0x26 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE3B:;
    /* $BE3B: 36 */ nes_cpu_instruction_boundary(0xBE3B, 6); { uint16_t a=(0x14 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE3D:;
    /* $BE3D: 26 */ nes_cpu_instruction_boundary(0xBE3D, 5); { uint16_t a=0x36; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE3F:;
    /* $BE3F: 12 */ nes_cpu_instruction_boundary(0xBE3F, 2); /* ILLEGAL $12 — skip 1 */
label_BE40:; /* TopEx */
    /* $BE40: 22 */ nes_cpu_instruction_boundary(0xBE40, 2); /* ILLEGAL $22 — skip 1 */
label_BE41:; /* SpawnBrickChunks */
    /* $BE41: 36 */ nes_cpu_instruction_boundary(0xBE41, 6); { uint16_t a=(0x5C + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE43:;
    /* $BE43: 22 */ nes_cpu_instruction_boundary(0xBE43, 2); /* ILLEGAL $22 — skip 1 */
label_BE44:;
    /* $BE44: 34 */ nes_cpu_instruction_boundary(0xBE44, 4); (void)nes_read((0x0C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE46:;
    /* $BE46: 22 */ nes_cpu_instruction_boundary(0xBE46, 2); /* ILLEGAL $22 — skip 1 */
label_BE47:;
    /* $BE47: 22 */ nes_cpu_instruction_boundary(0xBE47, 2); /* ILLEGAL $22 — skip 1 */
label_BE48:;
    /* $BE48: 81 */ nes_cpu_instruction_boundary(0xBE48, 6); nes_write(nes_read16zp((0x1E + g_cpu.X) & 0xFF), g_cpu.A);
label_BE4A:;
    /* $BE4A: 1E */ nes_cpu_instruction_boundary(0xBE4A, 7); { uint16_t a=(0x1E85 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE4D:;
    /* $BE4D: 81 */ nes_cpu_instruction_boundary(0xBE4D, 6); nes_write(nes_read16zp((0x12 + g_cpu.X) & 0xFF), g_cpu.A);
label_BE4F:;
    /* $BE4F: 86 */ nes_cpu_instruction_boundary(0xBE4F, 3); nes_write(0x14, g_cpu.X);
label_BE51:;
    /* $BE51: 81 */ nes_cpu_instruction_boundary(0xBE51, 6); nes_write(nes_read16zp((0x2C + g_cpu.X) & 0xFF), g_cpu.A);
label_BE53:;
    /* $BE53: 22 */ nes_cpu_instruction_boundary(0xBE53, 2); /* ILLEGAL $22 — skip 1 */
label_BE54:;
    /* $BE54: 1C */ nes_cpu_instruction_boundary(0xBE54, 4); (void)nes_read((0x222C + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE57:;
    /* $BE57: 1C */ nes_cpu_instruction_boundary(0xBE57, 4); (void)nes_read((0x2C85 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE5A:;
    /* $BE5A: 04 */ nes_cpu_instruction_boundary(0xBE5A, 3); (void)nes_read(0x81); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE5C:;
    /* $BE5C: 2E */ nes_cpu_instruction_boundary(0xBE5C, 6); { uint16_t a=0x1E24; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE5F:;
    /* $BE5F: 2E */ nes_cpu_instruction_boundary(0xBE5F, 6); { uint16_t a=0x1E24; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE62:;
    /* $BE62: 85 */ nes_cpu_instruction_boundary(0xBE62, 3); nes_write(0x2E, g_cpu.A);
label_BE64:;
    /* $BE64: 04 */ nes_cpu_instruction_boundary(0xBE64, 3); (void)nes_read(0x81); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE66:;
    /* $BE66: 32 */ nes_cpu_instruction_boundary(0xBE66, 2); /* ILLEGAL $32 — skip 1 */
label_BE67:;
    /* $BE67: 28 */ nes_cpu_instruction_boundary(0xBE67, 4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BE68:;
    /* $BE68: 22 */ nes_cpu_instruction_boundary(0xBE68, 2); /* ILLEGAL $22 — skip 1 */
label_BE69:;
    /* $BE69: 32 */ nes_cpu_instruction_boundary(0xBE69, 2); /* ILLEGAL $32 — skip 1 */
label_BE6A:;
    /* $BE6A: 28 */ nes_cpu_instruction_boundary(0xBE6A, 4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BE6B:;
    /* $BE6B: 22 */ nes_cpu_instruction_boundary(0xBE6B, 2); /* ILLEGAL $22 — skip 1 */
label_BE6C:;
    /* $BE6C: 85 */ nes_cpu_instruction_boundary(0xBE6C, 3); nes_write(0x32, g_cpu.A);
label_BE6E:;
    /* $BE6E: 87 */ nes_cpu_instruction_boundary(0xBE6E, 3); nes_write(0x36, g_cpu.A & g_cpu.X); /* SAX */
label_BE70:; /* BlockObjectsCore */
    /* $BE70: 36 */ nes_cpu_instruction_boundary(0xBE70, 6); { uint16_t a=(0x36 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE72:;
    /* $BE72: 84 */ nes_cpu_instruction_boundary(0xBE72, 3); nes_write(0x3A, g_cpu.Y);
label_BE74:;
    /* $BE74: 00 */ nes_cpu_instruction_boundary(0xBE74, 7); nes_brk_executed(0xBE74); return;
label_BE75:;
    /* $BE75: 5C */ nes_cpu_instruction_boundary(0xBE75, 4); (void)nes_read((0x4C54 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE78:;
    /* $BE78: 5C */ nes_cpu_instruction_boundary(0xBE78, 4); (void)nes_read((0x4C54 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE7B:;
    /* $BE7B: 5C */ nes_cpu_instruction_boundary(0xBE7B, 4); (void)nes_read((0x1C1C + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE7E:;
    /* $BE7E: 5C */ nes_cpu_instruction_boundary(0xBE7E, 4); (void)nes_read((0x5C5C + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE81:;
    /* $BE81: 5C */ nes_cpu_instruction_boundary(0xBE81, 4); (void)nes_read((0x565E + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE84:;
    /* $BE84: 4E */ nes_cpu_instruction_boundary(0xBE84, 6); { uint16_t a=0x565E; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BE87:;
    /* $BE87: 4E */ nes_cpu_instruction_boundary(0xBE87, 6); { uint16_t a=0x1E5E; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BE8A:;
    /* $BE8A: 1E */ nes_cpu_instruction_boundary(0xBE8A, 7); { uint16_t a=(0x5E5E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE8D:;
    /* $BE8D: 5E */ nes_cpu_instruction_boundary(0xBE8D, 7); { uint16_t a=(0x625E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BE90:;
    /* $BE90: 5A */ nes_cpu_instruction_boundary(0xBE90, 2); /* NOP */
label_BE91:;
    /* $BE91: 50 */ nes_cpu_instruction_boundary(0xBE91, 2); if (!g_cpu.V) { maybe_trigger_vblank(1); goto label_BEF5; }
label_BE93:;
    /* $BE93: 5A */ nes_cpu_instruction_boundary(0xBE93, 2); /* NOP */
label_BE94:;
    /* $BE94: 50 */ nes_cpu_instruction_boundary(0xBE94, 2); if (!g_cpu.V) { maybe_trigger_vblank(1); call_by_address(0xBEF8); return; }
label_BE96:;
    /* $BE96: 22 */ nes_cpu_instruction_boundary(0xBE96, 2); /* ILLEGAL $22 — skip 1 */
label_BE97:;
    /* $BE97: 22 */ nes_cpu_instruction_boundary(0xBE97, 2); /* ILLEGAL $22 — skip 1 */
label_BE98:;
    /* $BE98: 62 */ nes_cpu_instruction_boundary(0xBE98, 2); /* ILLEGAL $62 — skip 1 */
label_BE99:;
    /* $BE99: E7 */ nes_cpu_instruction_boundary(0xBE99, 5); { uint16_t a=0xE7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_BE9B:;
    /* $BE9B: E7 */ nes_cpu_instruction_boundary(0xBE9B, 5); { uint16_t a=0x2B; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_BE9D:;
    /* $BE9D: 86 */ nes_cpu_instruction_boundary(0xBE9D, 3); nes_write(0x14, g_cpu.X);
label_BE9F:;
    /* $BE9F: 81 */ nes_cpu_instruction_boundary(0xBE9F, 6); nes_write(nes_read16zp((0x14 + g_cpu.X) & 0xFF), g_cpu.A);
label_BEA1:;
    /* $BEA1: 80 */ nes_cpu_instruction_boundary(0xBEA1, 2); /* NOP */
label_BEA3:;
    /* $BEA3: 14 */ nes_cpu_instruction_boundary(0xBEA3, 4); (void)nes_read((0x81 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEA5:;
    /* $BEA5: 14 */ nes_cpu_instruction_boundary(0xBEA5, 4); (void)nes_read((0x14 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEA7:;
    /* $BEA7: 14 */ nes_cpu_instruction_boundary(0xBEA7, 4); (void)nes_read((0x14 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEA9:;
    /* $BEA9: 86 */ nes_cpu_instruction_boundary(0xBEA9, 3); nes_write(0x16, g_cpu.X);
label_BEAB:;
    /* $BEAB: 81 */ nes_cpu_instruction_boundary(0xBEAB, 6); nes_write(nes_read16zp((0x16 + g_cpu.X) & 0xFF), g_cpu.A);
label_BEAD:;
    /* $BEAD: 80 */ nes_cpu_instruction_boundary(0xBEAD, 2); /* NOP */
label_BEAF:;
    /* $BEAF: 16 */ nes_cpu_instruction_boundary(0xBEAF, 6); { uint16_t a=(0x81 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEB1:;
    /* $BEB1: 16 */ nes_cpu_instruction_boundary(0xBEB1, 6); { uint16_t a=(0x16 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEB3:; /* BouncingBlockHandler */
    /* $BEB3: 16 */ nes_cpu_instruction_boundary(0xBEB3, 6); { uint16_t a=(0x16 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEB5:;
    /* $BEB5: 81 */ nes_cpu_instruction_boundary(0xBEB5, 6); nes_write(nes_read16zp((0x28 + g_cpu.X) & 0xFF), g_cpu.A);
label_BEB7:;
    /* $BEB7: 22 */ nes_cpu_instruction_boundary(0xBEB7, 2); /* ILLEGAL $22 — skip 1 */
label_BEB8:;
    /* $BEB8: 1A */ nes_cpu_instruction_boundary(0xBEB8, 2); /* NOP */
label_BEB9:;
    /* $BEB9: 28 */ nes_cpu_instruction_boundary(0xBEB9, 4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BEBA:;
    /* $BEBA: 22 */ nes_cpu_instruction_boundary(0xBEBA, 2); /* ILLEGAL $22 — skip 1 */
label_BEBB:;
    /* $BEBB: 1A */ nes_cpu_instruction_boundary(0xBEBB, 2); /* NOP */
label_BEBC:;
    /* $BEBC: 28 */ nes_cpu_instruction_boundary(0xBEBC, 4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BEBD:;
    /* $BEBD: 80 */ nes_cpu_instruction_boundary(0xBEBD, 2); /* NOP */
label_BEBF:;
    /* $BEBF: 28 */ nes_cpu_instruction_boundary(0xBEBF, 4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BEC0:;
    /* $BEC0: 81 */ nes_cpu_instruction_boundary(0xBEC0, 6); nes_write(nes_read16zp((0x28 + g_cpu.X) & 0xFF), g_cpu.A);
label_BEC2:;
    /* $BEC2: 87 */ nes_cpu_instruction_boundary(0xBEC2, 3); nes_write(0x2C, g_cpu.A & g_cpu.X); /* SAX */
label_BEC4:;
    /* $BEC4: 2C */ nes_cpu_instruction_boundary(0xBEC4, 4); { uint8_t m=nes_read(0x842C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BEC7:;
    /* $BEC7: 30 */ nes_cpu_instruction_boundary(0xBEC7, 2); if (g_cpu.N) { maybe_trigger_vblank(1); call_by_address(0xBE4C); return; }
label_BEC9:;
    /* $BEC9: 04 */ nes_cpu_instruction_boundary(0xBEC9, 3); (void)nes_read(0x84); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BECB:;
    /* $BECB: 0C */ nes_cpu_instruction_boundary(0xBECB, 4); (void)nes_read(0x6283); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BECE:;
    /* $BECE: 10 */ nes_cpu_instruction_boundary(0xBECE, 2); if (!g_cpu.N) {
    nes_cpu_instruction_boundary(0xBE54, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BE54;
    }
label_BED0:;
    /* $BED0: 12 */ nes_cpu_instruction_boundary(0xBED0, 2); /* ILLEGAL $12 — skip 1 */
label_BED1:; /* UpdSte */
    /* $BED1: 83 */ nes_cpu_instruction_boundary(0xBED1, 6); nes_write(nes_read16zp((0x1C + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_BED3:;
    /* $BED3: 22 */ nes_cpu_instruction_boundary(0xBED3, 2); /* ILLEGAL $22 — skip 1 */
label_BED4:; /* BlockObjMT_Updater */
    /* $BED4: 1E */ nes_cpu_instruction_boundary(0xBED4, 7); { uint16_t a=(0x2622 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BED7:;
    /* $BED7: 18 */ nes_cpu_instruction_boundary(0xBED7, 2); g_cpu.C = 0;
label_BED8:;
    /* $BED8: 1E */ nes_cpu_instruction_boundary(0xBED8, 7); { uint16_t a=(0x1C04 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEDB:;
    /* $BEDB: 00 */ nes_cpu_instruction_boundary(0xBEDB, 7); nes_brk_executed(0xBEDB); return;
label_BEDC:;
    /* $BEDC: E3 */ nes_cpu_instruction_boundary(0xBEDC, 8); { uint16_t a=nes_read16zp((0xE1 + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_BEDE:;
    /* $BEDE: E3 */ nes_cpu_instruction_boundary(0xBEDE, 8); { uint16_t a=nes_read16zp((0x1D + g_cpu.X) & 0xFF); uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_BEE0:;
    /* $BEE0: DE */ nes_cpu_instruction_boundary(0xBEE0, 7); { uint16_t a=(0x23E0 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEE3:;
    /* $BEE3: EC */ nes_cpu_instruction_boundary(0xBEE3, 4); { uint8_t m=nes_read(0x7475); int r=g_cpu.X-m; g_cpu.C=(g_cpu.X>=m)?1:0; FLAG_NZ(r&0xFF); }
label_BEE6:;
    /* $BEE6: F0 */ nes_cpu_instruction_boundary(0xBEE6, 2); if (g_cpu.Z) {
    nes_cpu_instruction_boundary(0xBEDC, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BEDC;
    }
label_BEE8:;
    /* $BEE8: F6 */ nes_cpu_instruction_boundary(0xBEE8, 6); { uint16_t a=(0xEA + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEEA:;
    /* $BEEA: 31 */ nes_cpu_instruction_boundary(0xBEEA, 5); g_cpu.A &= nes_read((nes_read16zp(0x2D) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BEEC:;
    /* $BEEC: 83 */ nes_cpu_instruction_boundary(0xBEEC, 6); nes_write(nes_read16zp((0x12 + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_BEEE:;
    /* $BEEE: 14 */ nes_cpu_instruction_boundary(0xBEEE, 4); (void)nes_read((0x04 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEF0:;
    /* $BEF0: 18 */ nes_cpu_instruction_boundary(0xBEF0, 2); g_cpu.C = 0;
label_BEF1:;
    /* $BEF1: 1A */ nes_cpu_instruction_boundary(0xBEF1, 2); /* NOP */
label_BEF2:;
    /* $BEF2: 1C */ nes_cpu_instruction_boundary(0xBEF2, 4); (void)nes_read((0x2614 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEF5:;
    /* $BEF5: 22 */ nes_cpu_instruction_boundary(0xBEF5, 2); /* ILLEGAL $22 — skip 1 */
label_BEF6:;
    /* $BEF6: 1E */ nes_cpu_instruction_boundary(0xBEF6, 7); { uint16_t a=(0x181C + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEF9:;
    /* $BEF9: 1E */ nes_cpu_instruction_boundary(0xBEF9, 7); { uint16_t a=(0x0C22 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEFC:;
    /* $BEFC: 14 */ nes_cpu_instruction_boundary(0xBEFC, 4); (void)nes_read((0xFF + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEFE:; /* NextBUpd */
    /* $BEFE: FF */ nes_cpu_instruction_boundary(0xBEFE, 7); { uint16_t a=(0x00FF + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); int16_t r=g_cpu.A-v-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_BF01:;
    /* $BF01: 88 */ nes_cpu_instruction_boundary(0xBF01, 2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_BF02:; /* MoveEnemyHorizontally */
    /* $BF02: 00 */ nes_cpu_instruction_boundary(0xBF02, 7); nes_brk_executed(0xBF02); return;
label_BF03:; return;
label_BF06:; return;
label_BF07:; return;
label_BF09:; return;
label_BF0B:; return;
label_BF0E:; return;
label_BF0F:; return;
label_BF10:; return;
label_BF12:; return;
label_BF14:; return;
label_BF16:; return;
label_BF18:; return;
label_BF1A:; return;
label_BF1C:; return;
label_BF1E:; return;
label_BF20:; return;
label_BF22:; return;
label_BF24:; return;
label_BF26:; return;
label_BF27:; return;
label_BF2A:; return;
label_BF2B:; return;
label_BF2D:; return;
label_BF2F:; return;
label_BF31:; return;
label_BF34:; return;
label_BF35:; return;
label_BF37:; return;
label_BF39:; return;
label_BF3B:; return;
label_BF3E:; return;
label_BF3F:; return;
label_BF41:; return;
label_BF44:; return;
label_BF45:; return;
label_BF47:; return;
label_BF49:; return;
label_BF4C:; return;
label_BF4D:; return;
label_BF4F:; return;
label_BF51:; return;
label_BF53:; return;
label_BF56:; return;
label_BF57:; return;
label_BF58:; return;
label_BF59:; return;
label_BF5B:; return;
label_BF5D:; return;
label_BF5F:; return;
label_BF62:; return;
label_BF64:; return;
label_BF65:; return;
label_BF66:; return;
label_BF68:; return;
label_BF6A:; return;
label_BF6C:; return;
label_BF6F:; return;
label_BF70:; return;
label_BF72:; return;
label_BF73:; return;
label_BF74:; return;
label_BF76:; return;
label_BF78:; return;
label_BF7B:; return;
label_BF7C:; return;
label_BF7E:; return;
label_BF80:; return;
label_BF82:; return;
label_BF83:; return;
label_BF86:; return;
label_BF88:; return;
label_BF8A:; return;
label_BF8D:; return;
label_BF8E:; return;
label_BF8F:; return;
label_BF91:; return;
label_BF92:; return;
label_BF94:; return;
label_BF97:; return;
label_BF9A:; return;
label_BF9C:; return;
label_BF9E:; return;
label_BFA0:; return;
label_BFA2:; return;
label_BFA4:; return;
label_BFA5:; return;
label_BFA6:; return;
label_BFA8:; return;
label_BFAA:; return;
label_BFAC:; return;
label_BFAE:; return;
label_BFB0:; return;
label_BFB2:; return;
label_BFB4:; return;
label_BFB6:; return;
label_BFB8:; return;
label_BFBA:; return;
label_BFBC:; return;
label_BFBE:; return;
label_BFC0:; return;
label_BFC2:; return;
label_BFC4:; return;
label_BFC6:; return;
label_BFC8:; return;
label_BFCA:; return;
label_BFCC:; return;
label_BFCE:; return;
label_BFD0:; return;
label_BFD3:; return;
label_BFD4:; return;
label_BFD7:; return;
label_BFDA:; return;
label_BFDD:; return;
label_BFE0:; return;
label_BFE3:; return;
label_BFE6:; return;
label_BFE7:; return;
label_BFE8:; return;
label_BFEA:; return;
label_BFEC:; return;
label_BFEE:; return;
label_BFF0:; return;
label_BFF3:; return;
label_BFF4:; return;
label_BFF7:; return;
label_BFFA:; return;
label_BFFC:; return;
label_BFFD:; return;
label_BFFF:; return;
label_C002:; return;
label_C004:; return;
label_C006:; return;
label_C008:; return;
label_C00B:; return;
label_C00D:; return;
label_C00F:; return;
label_C011:; return;
label_C013:; return;
label_C015:; return;
label_C018:; return;
label_C019:; return;
label_C01B:; return;
label_C01D:; return;
label_C01F:; return;
label_C020:; return;
label_C021:; return;
label_C023:; return;
label_C026:; return;
label_C027:; return;
label_C029:; return;
label_C02C:; return;
label_C02E:; return;
label_C030:; return;
label_C032:; return;
label_C034:; return;
label_C036:; return;
label_C039:; return;
label_C03B:; return;
label_C03D:; return;
label_C03F:; return;
label_C041:; return;
label_C043:; return;
label_C046:; return;
label_C047:; return;
label_C049:; return;
label_C04A:; return;
label_C04B:; return;
label_C04D:; return;
label_C04E:; return;
label_C050:; return;
label_C053:; return;
label_C056:; return;
label_C058:; return;
label_C05A:; return;
label_C05C:; return;
label_C05F:; return;
label_C060:; return;
label_C062:; return;
label_C063:; return;
label_C066:; return;
label_C068:; return;
label_C06A:; return;
label_C06B:; return;
label_C06D:; return;
label_C06F:; return;
label_C071:; return;
label_C073:; return;
label_C075:; return;
label_C077:; return;
label_C079:; return;
label_C07B:; return;
label_C07C:; return;
label_C07E:; return;
label_C080:; return;
label_C082:; return;
label_C084:; return;
label_C086:; return;
label_C087:; return;
label_C089:; return;
label_C08B:; return;
label_C08D:; return;
label_C090:; return;
label_C092:; return;
label_C095:; return;
label_C097:; return;
label_C099:; return;
label_C09C:; return;
label_C09F:; return;
label_C0A0:; return;
label_C0A2:; return;
label_C0A5:; return;
label_C0A8:; return;
label_C0A9:; return;
label_C0AB:; return;
label_C0AE:; return;
label_C0B1:; return;
label_C0B2:; return;
label_C0B4:; return;
label_C0B7:; return;
label_C0B9:; return;
label_C0BC:; return;
label_C0BF:; return;
label_C0C2:; return;
label_C0C5:; return;
label_C0C8:; return;
label_C0CB:; return;
label_C0CC:; return;
label_C0CF:; return;
label_C0D1:; return;
label_C0D4:; return;
label_C0D6:; return;
label_C0D8:; return;
label_C0D9:; return;
label_C0DB:; return;
label_C0DE:; return;
label_C0E1:; return;
label_C0E3:; return;
label_C0E6:; return;
label_C0E9:; return;
label_C0EB:; return;
label_C0ED:; return;
label_C0F0:; return;
label_C0F2:; return;
label_C0F4:; return;
label_C0F6:; return;
label_C0F8:; return;
label_C0FB:; return;
label_C0FD:; return;
label_C0FF:; return;
label_C102:; return;
label_C105:; return;
label_C108:; return;
label_C10A:; return;
label_C10C:; return;
label_C10F:; return;
label_C111:; return;
label_C113:; return;
label_C115:; return;
label_C118:; return;
label_C11A:; return;
label_C11C:; return;
label_C11F:; return;
label_C122:; return;
label_C124:; return;
label_C127:; return;
label_C12A:; return;
label_C12C:; return;
label_C12F:; return;
label_C132:; return;
label_C134:; return;
label_C136:; return;
label_C138:; return;
label_C13A:; return;
label_C13C:; return;
label_C13E:; return;
label_C141:; return;
label_C144:; return;
label_C147:; return;
label_C149:; return;
label_C14B:; return;
label_C14D:; return;
label_C150:; return;
label_C152:; return;
label_C154:; return;
label_C156:; return;
label_C158:; return;
label_C15A:; return;
label_C15B:; return;
label_C15D:; return;
label_C15F:; return;
label_C161:; return;
label_C163:; return;
label_C164:; return;
label_C167:; return;
label_C168:; return;
label_C16A:; return;
label_C16C:; return;
label_C16E:; return;
label_C171:; return;
label_C173:; return;
label_C175:; return;
label_C178:; return;
label_C179:; return;
label_C17B:; return;
label_C17C:; return;
label_C17E:; return;
label_C181:; return;
label_C183:; return;
label_C186:; return;
label_C189:; return;
label_C18A:; return;
label_C18C:; return;
label_C18E:; return;
label_C190:; return;
label_C192:; return;
label_C195:; return;
label_C197:; return;
label_C198:; return;
label_C19A:; return;
label_C19C:; return;
label_C19F:; return;
label_C1A2:; return;
label_C1A5:; return;
label_C1A8:; return;
label_C1AB:; return;
label_C1AE:; return;
label_C1B0:; return;
label_C1B2:; return;
label_C1B4:; return;
label_C1B6:; return;
label_C1B9:; return;
label_C1BB:; return;
label_C1BE:; return;
label_C1C0:; return;
label_C1C2:; return;
label_C1C4:; return;
label_C1C6:; return;
label_C1C8:; return;
label_C1CB:; return;
label_C1CD:; return;
label_C1CF:; return;
label_C1D1:; return;
label_C1D3:; return;
label_C1D5:; return;
label_C1D7:; return;
label_C1D9:; return;
label_C1DB:; return;
label_C1DC:; return;
label_C1DD:; return;
label_C1DE:; return;
label_C1DF:; return;
label_C1E1:; return;
label_C1E3:; return;
label_C1E5:; return;
label_C1E6:; return;
label_C1E8:; return;
label_C1EA:; return;
label_C1EC:; return;
label_C1EF:; return;
label_C1F1:; return;
label_C1F3:; return;
label_C1F5:; return;
label_C1F7:; return;
label_C1F9:; return;
label_C1FB:; return;
label_C1FD:; return;
label_C1FF:; return;
label_C201:; return;
label_C204:; return;
label_C206:; return;
label_C208:; return;
label_C20A:; return;
label_C20C:; return;
label_C20E:; return;
label_C211:; return;
label_C213:; return;
label_C215:; return;
label_C216:; return;
label_C219:; return;
label_C21B:; return;
label_C21E:; return;
label_C220:; return;
label_C222:; return;
label_C224:; return;
label_C226:; return;
label_C228:; return;
label_C22A:; return;
label_C22D:; return;
label_C22E:; return;
label_C231:; return;
label_C232:; return;
label_C233:; return;
label_C235:; return;
label_C236:; return;
label_C237:; return;
label_C238:; return;
label_C239:; return;
label_C23A:; return;
label_C23D:; return;
label_C23F:; return;
label_C240:; return;
label_C242:; return;
label_C245:; return;
label_C246:; return;
label_C248:; return;
label_C24A:; return;
label_C24D:; return;
label_C25E:; return;
label_C261:; return;
label_C264:; return;
label_C266:; return;
label_C269:; return;
label_C26B:; return;
label_C26C:; return;
label_C26E:; return;
label_C270:; return;
label_C272:; return;
label_C273:; return;
label_C275:; return;
label_C277:; return;
label_C279:; return;
label_C27B:; return;
label_C27E:; return;
label_C27F:; return;
label_C2F0:; return;
label_C2F1:; return;
label_C2F4:; return;
label_C2F7:; return;
label_C2F9:; return;
label_C2FB:; return;
label_C2FD:; return;
label_C2FE:; return;
label_C301:; return;
label_C302:; return;
label_C304:; return;
label_C307:; return;
label_C309:; return;
label_C30B:; return;
label_C30C:; return;
label_C30D:; return;
label_C30F:; return;
label_C311:; return;
label_C312:; return;
label_C314:; return;
label_C316:; return;
label_C319:; return;
label_C31B:; return;
label_C31E:; return;
label_C321:; return;
label_C323:; return;
label_C325:; return;
label_C326:; return;
label_C328:; return;
label_C32A:; return;
label_C32D:; return;
label_C32F:; return;
label_C332:; return;
label_C335:; return;
label_C338:; return;
label_C33A:; return;
label_C33D:; return;
label_C33F:; return;
label_C342:; return;
label_C344:; return;
label_C346:; return;
label_C348:; return;
label_C34A:; return;
label_C34C:; return;
label_C34E:; return;
label_C351:; return;
label_C353:; return;
label_C355:; return;
label_C356:; return;
label_C358:; return;
label_C35A:; return;
label_C35C:; return;
label_C35F:; return;
label_C361:; return;
label_C363:; return;
label_C365:; return;
label_C367:; return;
label_C36A:; return;
label_C36B:; return;
label_C36D:; return;
label_C36F:; return;
label_C371:; return;
label_C374:; return;
label_C375:; return;
label_C378:; return;
label_C37B:; return;
label_C37D:; return;
label_C37F:; return;
label_C381:; return;
label_C384:; return;
label_C385:; return;
label_C388:; return;
label_C38A:; return;
label_C38C:; return;
label_C38F:; return;
label_C392:; return;
label_C395:; return;
label_C398:; return;
label_C39A:; return;
label_C39B:; return;
label_C39C:; return;
label_C39F:; return;
label_C3A1:; return;
label_C3A3:; return;
label_C3A5:; return;
label_C3A8:; return;
label_C3AB:; return;
label_C3AD:; return;
label_C3AF:; return;
label_C3B2:; return;
label_C3B4:; return;
label_C3B7:; return;
label_C3B9:; return;
label_C3BB:; return;
label_C3BC:; return;
label_C3BE:; return;
label_C3C1:; return;
label_C3C4:; return;
label_C3C6:; return;
label_C3C8:; return;
label_C3CA:; return;
label_C3CC:; return;
label_C3CE:; return;
label_C3CF:; return;
label_C3D1:; return;
label_C3D3:; return;
label_C3D5:; return;
label_C3D7:; return;
label_C3D9:; return;
label_C3DB:; return;
label_C3DE:; return;
label_C3E0:; return;
label_C3E3:; return;
label_C3E5:; return;
label_C3E6:; return;
label_C3E8:; return;
label_C3EA:; return;
label_C3EC:; return;
label_C3EF:; return;
label_C3F1:; return;
label_C3F4:; return;
label_C3F6:; return;
label_C3F9:; return;
label_C3FB:; return;
label_C3FD:; return;
label_C3FF:; return;
label_C402:; return;
label_C403:; return;
label_C405:; return;
label_C407:; return;
label_C40A:; return;
label_C40C:; return;
label_C40D:; return;
label_C40F:; return;
label_C412:; return;
label_C414:; return;
label_C415:; return;
label_C416:; return;
label_C417:; return;
label_C418:; return;
label_C419:; return;
label_C41B:; return;
label_C41D:; return;
label_C420:; return;
label_C422:; return;
label_C424:; return;
label_C426:; return;
label_C427:; return;
label_C42A:; return;
label_C42C:; return;
label_C42E:; return;
label_C42F:; return;
label_C431:; return;
label_C432:; return;
label_C433:; return;
label_C434:; return;
label_C437:; return;
label_C439:; return;
label_C43B:; return;
label_C43D:; return;
label_C43F:; return;
label_C440:; return;
label_C442:; return;
label_C444:; return;
label_C446:; return;
label_C448:; return;
label_C44A:; return;
label_C44C:; return;
label_C44E:; return;
label_C44F:; return;
label_C450:; return;
label_C451:; return;
label_C452:; return;
label_C453:; return;
label_C454:; return;
label_C455:; return;
label_C456:; return;
label_C458:; return;
label_C459:; return;
label_C45C:; return;
label_C45E:; return;
label_C460:; return;
label_C462:; return;
label_C463:; return;
label_C465:; return;
label_C466:; return;
label_C469:; return;
label_C46C:; return;
label_C46F:; return;
label_C471:; return;
label_C473:; return;
label_C474:; return;
label_C476:; return;
label_C478:; return;
label_C47A:; return;
label_C47B:; return;
label_C47D:; return;
label_C47F:; return;
label_C481:; return;
label_C483:; return;
label_C485:; return;
label_C488:; return;
label_C48A:; return;
label_C48B:; return;
label_C48D:; return;
label_C48F:; return;
label_C491:; return;
label_C492:; return;
label_C494:; return;
label_C496:; return;
label_C498:; return;
label_C49B:; return;
label_C49E:; return;
label_C4A0:; return;
label_C4A3:; return;
label_C4A5:; return;
label_C4A6:; return;
label_C4A9:; return;
label_C4AC:; return;
label_C4AE:; return;
label_C4B0:; return;
label_C4B3:; return;
label_C4B5:; return;
label_C4B6:; return;
label_C4B9:; return;
label_C4BC:; return;
label_C4BE:; return;
label_C4C1:; return;
label_C4C3:; return;
label_C4C4:; return;
label_C4C6:; return;
label_C4C8:; return;
label_C4CA:; return;
label_C4CD:; return;
label_C4CF:; return;
label_C4D1:; return;
label_C4D3:; return;
label_C4D5:; return;
label_C4D7:; return;
label_C4D9:; return;
label_C4DB:; return;
label_C4DD:; return;
label_C4DF:; return;
label_C4E1:; return;
label_C4E3:; return;
label_C4E4:; return;
label_C4E5:; return;
label_C4E6:; return;
label_C4E8:; return;
label_C4EA:; return;
label_C4ED:; return;
label_C4EF:; return;
label_C4F1:; return;
label_C4F4:; return;
label_C4F6:; return;
label_C4F8:; return;
label_C4F9:; return;
label_C4FA:; return;
label_C4FC:; return;
label_C4FD:; return;
label_C500:; return;
label_C502:; return;
label_C504:; return;
label_C506:; return;
label_C508:; return;
label_C50A:; return;
label_C50C:; return;
label_C50D:; return;
label_C50F:; return;
label_C511:; return;
label_C513:; return;
label_C515:; return;
label_C516:; return;
label_C518:; return;
label_C51A:; return;
label_C51C:; return;
label_C51D:; return;
label_C51F:; return;
label_C521:; return;
label_C523:; return;
label_C524:; return;
label_C527:; return;
label_C529:; return;
label_C52B:; return;
label_C52D:; return;
label_C530:; return;
label_C532:; return;
label_C533:; return;
label_C536:; return;
label_C538:; return;
label_C53A:; return;
label_C53C:; return;
label_C53E:; return;
label_C540:; return;
label_C542:; return;
label_C544:; return;
label_C546:; return;
label_C548:; return;
label_C549:; return;
label_C54C:; return;
label_C54F:; return;
label_C551:; return;
label_C554:; return;
label_C557:; return;
label_C559:; return;
label_C55C:; return;
label_C55E:; return;
label_C561:; return;
label_C563:; return;
label_C565:; return;
label_C568:; return;
label_C56B:; return;
label_C56D:; return;
label_C570:; return;
label_C571:; return;
label_C574:; return;
label_C575:; return;
label_C577:; return;
label_C578:; return;
label_C57B:; return;
label_C57D:; return;
label_C580:; return;
label_C581:; return;
label_C583:; return;
label_C586:; return;
label_C588:; return;
label_C58B:; return;
label_C58D:; return;
label_C590:; return;
label_C592:; return;
label_C594:; return;
label_C597:; return;
label_C599:; return;
label_C59C:; return;
label_C59D:; return;
label_C59F:; return;
label_C5A1:; return;
label_C5A4:; return;
label_C5A7:; return;
label_C5A9:; return;
label_C5AB:; return;
label_C5AD:; return;
label_C5AF:; return;
label_C5B1:; return;
label_C5B4:; return;
label_C5B7:; return;
label_C5B9:; return;
label_C5BB:; return;
label_C5BE:; return;
label_C5BF:; return;
label_C5C1:; return;
label_C5C4:; return;
label_C5C6:; return;
label_C5C7:; return;
label_C5C9:; return;
label_C5CC:; return;
label_C5CF:; return;
label_C5D1:; return;
label_C5D4:; return;
label_C5D5:; return;
label_C5D8:; return;
label_C5DA:; return;
label_C5DD:; return;
label_C5DE:; return;
label_C5E0:; return;
label_C5E2:; return;
label_C5E5:; return;
label_C5E7:; return;
label_C5E9:; return;
label_C5EC:; return;
label_C5EF:; return;
label_C5F0:; return;
label_C5F2:; return;
label_C5F4:; return;
label_C5F7:; return;
label_C5F9:; return;
label_C5FC:; return;
label_C5FD:; return;
label_C5FF:; return;
label_C601:; return;
label_C604:; return;
label_C606:; return;
label_C609:; return;
label_C60A:; return;
label_C60D:; return;
label_C60F:; return;
label_C611:; return;
label_C613:; return;
label_C614:; return;
label_C617:; return;
label_C61A:; return;
label_C61C:; return;
label_C61F:; return;
label_C621:; return;
label_C624:; return;
label_C626:; return;
label_C628:; return;
label_C62A:; return;
label_C62B:; return;
label_C62E:; return;
label_C630:; return;
label_C631:; return;
label_C632:; return;
label_C634:; return;
label_C635:; return;
label_C636:; return;
label_C639:; return;
label_C63B:; return;
label_C63C:; return;
label_C63E:; return;
label_C641:; return;
label_C643:; return;
label_C646:; return;
label_C648:; return;
label_C64A:; return;
label_C64C:; return;
label_C64D:; return;
label_C650:; return;
label_C652:; return;
label_C654:; return;
label_C657:; return;
label_C658:; return;
label_C65A:; return;
label_C65B:; return;
label_C65E:; return;
label_C660:; return;
label_C662:; return;
label_C665:; return;
label_C666:; return;
label_C669:; return;
label_C66A:; return;
label_C66B:; return;
label_C66C:; return;
label_C66F:; return;
label_C671:; return;
label_C673:; return;
label_C675:; return;
label_C677:; return;
label_C67A:; return;
label_C67C:; return;
label_C67E:; return;
label_C680:; return;
label_C682:; return;
label_C683:; return;
label_C685:; return;
label_C687:; return;
label_C689:; return;
label_C68A:; return;
label_C68C:; return;
label_C68E:; return;
label_C690:; return;
label_C691:; return;
label_C693:; return;
label_C695:; return;
label_C697:; return;
label_C698:; return;
label_C69A:; return;
label_C69B:; return;
label_C69D:; return;
label_C6A0:; return;
label_C6A3:; return;
label_C6A5:; return;
label_C6A7:; return;
label_C6A9:; return;
label_C6AB:; return;
label_C6AC:; return;
label_C6AF:; return;
label_C6B1:; return;
label_C6B3:; return;
label_C6B4:; return;
label_C6B7:; return;
label_C6B9:; return;
label_C6BB:; return;
label_C6BC:; return;
label_C6BD:; return;
label_C6BF:; return;
label_C6C0:; return;
label_C6C3:; return;
label_C6C5:; return;
label_C6C8:; return;
label_C6CA:; return;
label_C6CC:; return;
label_C6CE:; return;
label_C6D1:; return;
label_C6D4:; return;
label_C6D6:; return;
label_C6D7:; return;
label_C6DA:; return;
label_C6DD:; return;
label_C6DF:; return;
label_C6E0:; return;
label_C6E1:; return;
label_C6E3:; return;
label_C6E6:; return;
label_C6E9:; return;
label_C6EC:; return;
label_C6EF:; return;
label_C6F2:; return;
label_C6F5:; return;
label_C6F7:; return;
label_C6FA:; return;
label_C6FD:; return;
label_C6FF:; return;
label_C700:; return;
label_C702:; return;
label_C704:; return;
label_C707:; return;
label_C709:; return;
label_C70C:; return;
label_C70E:; return;
label_C710:; return;
label_C711:; return;
label_C713:; return;
label_C715:; return;
label_C717:; return;
label_C719:; return;
label_C71B:; return;
label_C71D:; return;
label_C71E:; return;
label_C720:; return;
label_C721:; return;
label_C723:; return;
label_C725:; return;
label_C726:; return;
label_C728:; return;
label_C72B:; return;
label_C72D:; return;
label_C72F:; return;
label_C730:; return;
label_C732:; return;
label_C734:; return;
label_C736:; return;
label_C738:; return;
label_C73A:; return;
label_C73C:; return;
label_C73F:; return;
label_C741:; return;
label_C744:; return;
label_C746:; return;
label_C748:; return;
label_C749:; return;
label_C74A:; return;
label_C74C:; return;
label_C74D:; return;
label_C750:; return;
label_C752:; return;
label_C753:; return;
label_C755:; return;
label_C757:; return;
label_C759:; return;
label_C75B:; return;
label_C75D:; return;
label_C75F:; return;
label_C761:; return;
label_C763:; return;
label_C765:; return;
label_C767:; return;
label_C768:; return;
label_C76A:; return;
label_C76C:; return;
label_C76E:; return;
label_C770:; return;
label_C772:; return;
label_C774:; return;
label_C776:; return;
label_C778:; return;
label_C77A:; return;
label_C77C:; return;
label_C77F:; return;
label_C782:; return;
label_C784:; return;
label_C787:; return;
label_C789:; return;
label_C78B:; return;
label_C78C:; return;
label_C78E:; return;
label_C790:; return;
label_C792:; return;
label_C795:; return;
label_C796:; return;
label_C798:; return;
label_C79B:; return;
label_C79D:; return;
label_C7A0:; return;
label_C7A2:; return;
label_C7A5:; return;
label_C7A6:; return;
label_C7A8:; return;
label_C7BB:; return;
label_C7BD:; return;
label_C7BF:; return;
label_C7C1:; return;
label_C7C3:; return;
label_C7C6:; return;
label_C7C7:; return;
label_C7C9:; return;
label_C7CB:; return;
label_C7CE:; return;
label_C7D0:; return;
label_C7D1:; return;
label_C7D3:; return;
label_C7D5:; return;
label_C7D7:; return;
label_C7D9:; return;
label_C7DB:; return;
label_C7DE:; return;
label_C7DF:; return;
label_C7E1:; return;
label_C7E3:; return;
label_C7E6:; return;
label_C7E8:; return;
label_C7EA:; return;
label_C7ED:; return;
label_C7EF:; return;
label_C7F2:; return;
label_C7F4:; return;
label_C7F6:; return;
label_C7F7:; return;
label_C7F8:; return;
label_C7FB:; return;
label_C7FD:; return;
label_C7FF:; return;
label_C800:; return;
label_C803:; return;
label_C805:; return;
label_C808:; return;
label_C80B:; return;
label_C80D:; return;
label_C80F:; return;
label_C812:; return;
label_C814:; return;
label_C816:; return;
label_C818:; return;
label_C81A:; return;
label_C81B:; return;
label_C81D:; return;
label_C81F:; return;
label_C822:; return;
label_C823:; return;
label_C824:; return;
label_C826:; return;
label_C828:; return;
label_C82B:; return;
label_C82D:; return;
label_C830:; return;
label_C832:; return;
label_C834:; return;
label_C837:; return;
label_C839:; return;
label_C83B:; return;
label_C83E:; return;
label_C83F:; return;
label_C842:; return;
label_C845:; return;
label_C848:; return;
label_C84B:; return;
label_C84D:; return;
label_C850:; return;
label_C852:; return;
label_C854:; return;
label_C857:; return;
label_C859:; return;
label_C85C:; return;
label_C85E:; return;
label_C860:; return;
label_C862:; return;
label_C865:; return;
label_C867:; return;
label_C86A:; return;
label_C86B:; return;
label_C86C:; return;
label_C86F:; return;
label_C870:; return;
label_C873:; return;
label_C874:; return;
label_C877:; return;
label_C879:; return;
label_C87B:; return;
label_C87E:; return;
label_C880:; return;
label_C881:; return;
label_C882:; return;
label_C884:; return;
label_C886:; return;
label_C888:; return;
label_C88A:; return;
label_C88C:; return;
label_C88D:; return;
label_C88F:; return;
label_C8D6:; return;
label_C8D7:; return;
label_C8DA:; return;
label_C8DD:; return;
label_C8E0:; return;
label_C8E2:; return;
label_C8E5:; return;
label_C8E8:; return;
label_C8EB:; return;
label_C8EE:; return;
label_C8F1:; return;
label_C8F4:; return;
label_C8F7:; return;
label_C8FA:; return;
label_C8FD:; return;
label_C8FF:; return;
label_C902:; return;
label_C905:; return;
label_C907:; return;
label_C934:; return;
label_C935:; return;
label_C938:; return;
label_C93B:; return;
label_C93E:; return;
label_C941:; return;
label_C944:; return;
label_C947:; return;
label_C94A:; return;
label_C94D:; return;
label_C950:; return;
label_C953:; return;
label_C956:; return;
label_C959:; return;
label_C95C:; return;
label_C95F:; return;
label_C962:; return;
label_C965:; return;
label_C968:; return;
label_C96B:; return;
label_C96E:; return;
label_C971:; return;
label_C974:; return;
label_C976:; return;
label_C979:; return;
label_C97C:; return;
label_C97F:; return;
label_C982:; return;
label_C984:; return;
label_C985:; return;
label_C987:; return;
label_C998:; return;
label_C99A:; return;
label_C99C:; return;
label_C99E:; return;
label_C9A0:; return;
label_C9A3:; return;
label_C9A6:; return;
label_C9A9:; return;
label_C9AC:; return;
label_C9AF:; return;
label_C9B0:; return;
label_C9B3:; return;
label_C9B5:; return;
label_C9B8:; return;
label_C9BB:; return;
label_C9BD:; return;
label_C9C0:; return;
label_C9C2:; return;
label_C9C4:; return;
label_C9C7:; return;
label_C9C9:; return;
label_C9CB:; return;
label_C9CE:; return;
label_C9D0:; return;
label_C9D1:; return;
label_C9D2:; return;
label_C9D3:; return;
label_C9D4:; return;
label_C9D5:; return;
label_C9D6:; return;
label_C9D9:; return;
label_C9DC:; return;
label_C9DE:; return;
label_C9E1:; return;
label_C9E3:; return;
label_C9E5:; return;
label_C9E7:; return;
label_C9EA:; return;
label_C9EC:; return;
label_C9EE:; return;
label_C9F1:; return;
label_C9F3:; return;
label_C9F6:; return;
label_C9F9:; return;
label_C9FC:; return;
label_C9FF:; return;
label_CA01:; return;
label_CA03:; return;
label_CA05:; return;
label_CA07:; return;
label_CA0A:; return;
label_CA0D:; return;
label_CA12:; return;
label_CA14:; return;
label_CA16:; return;
label_CA18:; return;
label_CA1A:; return;
label_CA1C:; return;
label_CA1E:; return;
label_CA20:; return;
label_CA22:; return;
label_CA24:; return;
label_CA26:; return;
label_CA28:; return;
label_CA2A:; return;
label_CA2C:; return;
label_CA2E:; return;
label_CA31:; return;
label_CA33:; return;
label_CA35:; return;
label_CA37:; return;
label_CA39:; return;
label_CA3B:; return;
label_CA3D:; return;
label_CA3F:; return;
label_CA41:; return;
label_CA44:; return;
label_CA45:; return;
label_CA48:; return;
label_CA4A:; return;
label_CA4B:; return;
label_CA4E:; return;
label_CA51:; return;
label_CA54:; return;
label_CA56:; return;
label_CA58:; return;
label_CA5A:; return;
label_CA5C:; return;
label_CA5E:; return;
label_CA60:; return;
label_CA62:; return;
label_CA64:; return;
label_CA66:; return;
label_CA69:; return;
label_CA6B:; return;
label_CA6C:; return;
label_CA6F:; return;
label_CA71:; return;
label_CA73:; return;
label_CA75:; return;
label_CA77:; return;
label_CA79:; return;
label_CA7B:; return;
label_CA7D:; return;
label_CA7F:; return;
label_CA81:; return;
label_CA82:; return;
label_CA84:; return;
label_CA86:; return;
label_CA88:; return;
label_CA8A:; return;
label_CA8C:; return;
label_CA8E:; return;
label_CA90:; return;
label_CA92:; return;
label_CA94:; return;
label_CA96:; return;
label_CA98:; return;
label_CA9B:; return;
label_CA9D:; return;
label_CA9F:; return;
label_CAA1:; return;
label_CAA3:; return;
label_CAA5:; return;
label_CAA7:; return;
label_CAA9:; return;
label_CAAB:; return;
label_CAAD:; return;
label_CAAF:; return;
label_CAB2:; return;
label_CAB4:; return;
label_CAB6:; return;
label_CAB7:; return;
label_CAB9:; return;
label_CABA:; return;
label_CABB:; return;
label_CABC:; return;
label_CABF:; return;
label_CAC1:; return;
label_CAC4:; return;
label_CAC5:; return;
label_CAC7:; return;
label_CAC8:; return;
label_CACB:; return;
label_CACD:; return;
label_CACF:; return;
label_CAD1:; return;
label_CAD3:; return;
label_CAD4:; return;
label_CAD5:; return;
label_CAD7:; return;
label_CAD8:; return;
label_CADB:; return;
label_CADD:; return;
label_CADE:; return;
label_CADF:; return;
label_CAE2:; return;
label_CAE4:; return;
label_CAE5:; return;
label_CAE8:; return;
label_CAEB:; return;
label_CAED:; return;
label_CAEF:; return;
label_CAF1:; return;
label_CAF3:; return;
label_CAF5:; return;
label_CAF8:; return;
label_CAF9:; return;
label_CAFC:; return;
label_CAFF:; return;
label_CB01:; return;
label_CB04:; return;
label_CB06:; return;
label_CB09:; return;
label_CB0B:; return;
label_CB0E:; return;
label_CB10:; return;
label_CB12:; return;
label_CB14:; return;
label_CB16:; return;
label_CB18:; return;
label_CB19:; return;
label_CB1B:; return;
label_CB1D:; return;
label_CB1F:; return;
label_CB22:; return;
label_CB25:; return;
label_CB28:; return;
label_CB2B:; return;
label_CB2D:; return;
label_CB2F:; return;
label_CB31:; return;
label_CB33:; return;
label_CB35:; return;
label_CB37:; return;
label_CB39:; return;
label_CB3B:; return;
label_CB3D:; return;
label_CB3F:; return;
label_CB40:; return;
label_CB42:; return;
label_CB44:; return;
label_CB45:; return;
label_CB47:; return;
label_CB49:; return;
label_CB4B:; return;
label_CB4D:; return;
label_CB4F:; return;
label_CB51:; return;
label_CB53:; return;
label_CB54:; return;
label_CB56:; return;
label_CB58:; return;
label_CB5A:; return;
label_CB5C:; return;
label_CB5D:; return;
label_CB5F:; return;
label_CB60:; return;
label_CB61:; return;
label_CB63:; return;
label_CB65:; return;
label_CB66:; return;
label_CB68:; return;
label_CB69:; return;
label_CB6B:; return;
label_CB6D:; return;
label_CB6F:; return;
label_CB71:; return;
label_CB73:; return;
label_CB75:; return;
label_CB76:; return;
label_CB78:; return;
label_CB7A:; return;
label_CB7C:; return;
label_CB7E:; return;
label_CB81:; return;
label_CB83:; return;
label_CB84:; return;
label_CB86:; return;
label_CB87:; return;
label_CB8A:; return;
label_CB8D:; return;
label_CB8F:; return;
label_CB92:; return;
label_CB95:; return;
label_CB98:; return;
label_CB9A:; return;
label_CB9B:; return;
label_CB9C:; return;
label_CB9E:; return;
label_CBA0:; return;
label_CBA2:; return;
label_CBA4:; return;
label_CBA7:; return;
label_CBA9:; return;
label_CBAA:; return;
label_CBAC:; return;
label_CBAF:; return;
label_CBB1:; return;
label_CBB2:; return;
label_CBB5:; return;
label_CBB7:; return;
label_CBB9:; return;
label_CBBB:; return;
label_CBBD:; return;
label_CBBE:; return;
label_CBC0:; return;
label_CBC2:; return;
label_CBC3:; return;
label_CBC5:; return;
label_CBC7:; return;
label_CBC9:; return;
label_CBCB:; return;
label_CBCD:; return;
label_CBCE:; return;
label_CBD0:; return;
label_CBD1:; return;
label_CBD3:; return;
label_CBD5:; return;
label_CBD7:; return;
label_CBD9:; return;
label_CBDB:; return;
label_CBDC:; return;
label_CBDF:; return;
label_CBE1:; return;
label_CBE3:; return;
label_CBE5:; return;
label_CBE7:; return;
label_CBE9:; return;
label_CBEA:; return;
label_CBEC:; return;
label_CBED:; return;
label_CBEF:; return;
label_CBF0:; return;
label_CBF2:; return;
label_CBF5:; return;
label_CBF6:; return;
label_CBF8:; return;
label_CBFB:; return;
label_CBFD:; return;
label_CBFF:; return;
label_CC01:; return;
label_CC03:; return;
label_CC04:; return;
label_CC05:; return;
label_CC07:; return;
label_CC0A:; return;
label_CC0B:; return;
label_CC0D:; return;
label_CC10:; return;
label_CC12:; return;
label_CC14:; return;
label_CC16:; return;
label_CC18:; return;
label_CC1B:; return;
label_CC1C:; return;
label_CC1F:; return;
label_CC21:; return;
label_CC23:; return;
label_CC24:; return;
label_CC26:; return;
label_CC28:; return;
label_CC29:; return;
label_CC2B:; return;
label_CC2D:; return;
label_CC2F:; return;
label_CC31:; return;
label_CC33:; return;
label_CC35:; return;
label_CC36:; return;
label_CC38:; return;
label_CC3A:; return;
label_CC3C:; return;
label_CC3F:; return;
label_CC41:; return;
label_CC43:; return;
label_CC46:; return;
label_CC47:; return;
label_CC49:; return;
label_CC4B:; return;
label_CC4E:; return;
label_CC50:; return;
label_CC53:; return;
label_CC55:; return;
label_CC57:; return;
label_CC58:; return;
label_CC5A:; return;
label_CC5B:; return;
label_CC5E:; return;
label_CC60:; return;
label_CC63:; return;
label_CC64:; return;
label_CC66:; return;
label_CC69:; return;
label_CC6B:; return;
label_CC6D:; return;
label_CC6F:; return;
label_CC71:; return;
label_CC73:; return;
label_CC75:; return;
label_CC77:; return;
label_CC79:; return;
label_CC7B:; return;
label_CC7D:; return;
label_CC7F:; return;
label_CC81:; return;
label_CC83:; return;
label_CC86:; return;
label_CC87:; return;
label_CC89:; return;
label_CC8C:; return;
label_CC8E:; return;
label_CC90:; return;
label_CC92:; return;
label_CC94:; return;
label_CC96:; return;
label_CC99:; return;
label_CC9C:; return;
label_CC9D:; return;
label_CC9F:; return;
label_CCA2:; return;
label_CCA4:; return;
label_CCA6:; return;
label_CCA8:; return;
label_CCAA:; return;
label_CCAC:; return;
label_CCAE:; return;
label_CCB0:; return;
label_CCB2:; return;
label_CCB3:; return;
label_CCB6:; return;
label_CCB8:; return;
label_CCBA:; return;
label_CCBC:; return;
label_CCBD:; return;
label_CCBF:; return;
label_CCC1:; return;
label_CCC3:; return;
label_CCC4:; return;
label_CCC6:; return;
label_CCC7:; return;
label_CCC8:; return;
label_CCCA:; return;
label_CCCC:; return;
label_CCCE:; return;
label_CCD0:; return;
label_CCD1:; return;
label_CCD3:; return;
label_CCD5:; return;
label_CCD8:; return;
label_CCDA:; return;
label_CCDC:; return;
label_CCDF:; return;
label_CCE1:; return;
label_CCE2:; return;
label_CCE3:; return;
label_CCE5:; return;
label_CCE6:; return;
label_CCE8:; return;
label_CCEB:; return;
label_CCEC:; return;
label_CCEE:; return;
label_CCF0:; return;
label_CCF2:; return;
label_CCF4:; return;
label_CCF5:; return;
label_CCF7:; return;
label_CCFA:; return;
label_CCFD:; return;
label_CCFE:; return;
label_CD00:; return;
label_CD03:; return;
label_CD05:; return;
label_CD06:; return;
label_CD07:; return;
label_CD0A:; return;
label_CD0D:; return;
label_CD10:; return;
label_CD13:; return;
label_CD14:; return;
label_CD17:; return;
label_CD18:; return;
label_CD19:; return;
label_CD1C:; return;
label_CD1D:; return;
label_CD1E:; return;
label_CD1F:; return;
label_CD22:; return;
label_CD24:; return;
label_CD26:; return;
label_CD28:; return;
label_CD2A:; return;
label_CD2C:; return;
label_CD2D:; return;
label_CD2E:; return;
label_CD2F:; return;
label_CD31:; return;
label_CD34:; return;
label_CD36:; return;
label_CD37:; return;
label_CD39:; return;
label_CD3B:; return;
label_CD3C:; return;
label_CD3F:; return;
label_CD42:; return;
label_CD44:; return;
label_CD46:; return;
label_CD49:; return;
label_CD4B:; return;
label_CD4E:; return;
label_CD51:; return;
label_CD53:; return;
label_CD55:; return;
label_CD57:; return;
label_CD59:; return;
label_CD5B:; return;
label_CD5D:; return;
label_CD5F:; return;
label_CD61:; return;
label_CD63:; return;
label_CD65:; return;
label_CD66:; return;
label_CD68:; return;
label_CD6A:; return;
label_CD6C:; return;
label_CD6F:; return;
label_CD72:; return;
label_CD75:; return;
label_CD78:; return;
label_CD7B:; return;
label_CD7D:; return;
label_CD80:; return;
label_CD83:; return;
label_CD85:; return;
label_CD87:; return;
label_CD89:; return;
label_CD8C:; return;
label_CD8E:; return;
label_CD90:; return;
label_CD92:; return;
label_CD94:; return;
label_CD96:; return;
label_CD98:; return;
label_CD9A:; return;
label_CD9C:; return;
label_CD9E:; return;
label_CDA1:; return;
label_CDA4:; return;
label_CDA6:; return;
label_CDA8:; return;
label_CDAA:; return;
label_CDAD:; return;
label_CDB0:; return;
label_CDB2:; return;
label_CDB4:; return;
label_CDB6:; return;
label_CDB8:; return;
label_CDBA:; return;
label_CDBB:; return;
label_CDBD:; return;
label_CDBF:; return;
label_CDC1:; return;
label_CDC3:; return;
label_CDC5:; return;
label_CDC7:; return;
label_CDC9:; return;
label_CDCB:; return;
label_CDCC:; return;
label_CDCF:; return;
label_CDD2:; return;
label_CDD4:; return;
label_CDD7:; return;
label_CDD9:; return;
label_CDDC:; return;
label_CDDD:; return;
label_CDDF:; return;
label_CDE2:; return;
label_CDE3:; return;
label_CDE6:; return;
label_CDE8:; return;
label_CDEA:; return;
label_CDEC:; return;
label_CDEE:; return;
label_CDF1:; return;
label_CDF3:; return;
label_CDF5:; return;
label_CDF7:; return;
label_CDF9:; return;
label_CDFB:; return;
label_CDFD:; return;
label_CDFF:; return;
label_CE00:; return;
label_CE03:; return;
label_CE06:; return;
label_CE08:; return;
label_CE0B:; return;
label_CE0C:; return;
label_CE0D:; return;
label_CE10:; return;
label_CE13:; return;
label_CE15:; return;
label_CE17:; return;
label_CE19:; return;
label_CE1A:; return;
label_CE1C:; return;
label_CE1E:; return;
label_CE21:; return;
label_CE23:; return;
label_CE26:; return;
label_CE28:; return;
label_CE2A:; return;
label_CE2C:; return;
label_CE2D:; return;
label_CE2E:; return;
label_CE30:; return;
label_CE31:; return;
label_CE32:; return;
label_CE33:; return;
label_CE35:; return;
label_CE37:; return;
label_CE39:; return;
label_CE3A:; return;
label_CE3C:; return;
label_CE3E:; return;
label_CE40:; return;
label_CE42:; return;
label_CE44:; return;
label_CE46:; return;
label_CE49:; return;
label_CE4A:; return;
label_CE4C:; return;
label_CE4E:; return;
label_CE4F:; return;
label_CE51:; return;
label_CE53:; return;
label_CE55:; return;
label_CE56:; return;
label_CE58:; return;
label_CE5A:; return;
label_CE5C:; return;
label_CE5E:; return;
label_CE60:; return;
label_CE62:; return;
label_CE64:; return;
label_CE66:; return;
label_CE67:; return;
label_CE6A:; return;
label_CE6C:; return;
label_CE6F:; return;
label_CE71:; return;
label_CE73:; return;
label_CE75:; return;
label_CE77:; return;
label_CE78:; return;
label_CE7A:; return;
label_CE7C:; return;
label_CE7E:; return;
label_CE7F:; return;
label_CE82:; return;
}

void func_BD0C_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BD0C_b1");
#endif
    func_BD0C_b1_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_BD35_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BD35_b1");
#endif
    func_BD0C_b1_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_BEDB_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BEDB_b1");
#endif
    func_BD0C_b1_body(2);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_EF8C_body(int _entry) { /* PROfsLoop */
    switch (_entry) {
        case 1: goto label_EF97;
    }
label_EF8C:; /* PROfsLoop */
    /* $EF8C: A9 */ nes_cpu_instruction_boundary(0xEF8C, 2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_EF8E:;
    /* $EF8E: 46 */ nes_cpu_instruction_boundary(0xEF8E, 5); { uint16_t a=0x00; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_EF90:;
    /* $EF90: 90 */ nes_cpu_instruction_boundary(0xEF90, 2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_EF95; }
label_EF92:;
    /* $EF92: 20 */ nes_cpu_instruction_boundary(0xEF92, 6); func_E5C1();
label_EF95:; /* NPROffscr */
    /* $EF95: 98 */ nes_cpu_instruction_boundary(0xEF95, 2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_EF96:;
    /* $EF96: 38 */ nes_cpu_instruction_boundary(0xEF96, 2); g_cpu.C = 1;
label_EF97:;
    /* $EF97: E9 */ nes_cpu_instruction_boundary(0xEF97, 2); { uint8_t m=0x08; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_EF99:;
    /* $EF99: A8 */ nes_cpu_instruction_boundary(0xEF99, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_EF9A:;
    /* $EF9A: CA */ nes_cpu_instruction_boundary(0xEF9A, 2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_EF9B:;
    /* $EF9B: 10 */ nes_cpu_instruction_boundary(0xEF9B, 2); if (!g_cpu.N) {
    nes_cpu_instruction_boundary(0xEF8C, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_EF8C;
    }
label_EF9D:;
    /* $EF9D: 60 */ nes_cpu_instruction_boundary(0xEF9D, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_EF8C(void) { /* PROfsLoop */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_EF8C");
#endif
    func_EF8C_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_EF97(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_EF97");
#endif
    func_EF8C_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_824E_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_824E_b1");
#endif
label_824E:;
    /* $824E: 5B */ nes_cpu_instruction_boundary(0x824E, 7); { uint16_t a=(0xACC2 + g_cpu.Y) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); g_cpu.A^=v; FLAG_NZ(g_cpu.A); }
label_8251:;
    /* $8251: 39 */ nes_cpu_instruction_boundary(0x8251, 4); g_cpu.A &= nes_read((0xB107 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8254:;
    /* $8254: E9 */ nes_cpu_instruction_boundary(0x8254, 2); { uint8_t m=0x29; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8256:;
    /* $8256: 0F */ nes_cpu_instruction_boundary(0x8256, 6); { uint16_t a=0x0EC9; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_8259:;
    /* $8259: D0 */ nes_cpu_instruction_boundary(0x8259, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_825E; }
label_825B:;
    /* $825B: EE */ nes_cpu_instruction_boundary(0x825B, 6); { uint16_t a=0x0739; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_825E:;
    /* $825E: EE */ nes_cpu_instruction_boundary(0x825E, 6); { uint16_t a=0x0739; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8261:;
    /* $8261: EE */ nes_cpu_instruction_boundary(0x8261, 6); { uint16_t a=0x0739; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8264:;
    /* $8264: A9 */ nes_cpu_instruction_boundary(0x8264, 2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8266:;
    /* $8266: 8D */ nes_cpu_instruction_boundary(0x8266, 4); nes_write(0x073B, g_cpu.A);
label_8269:;
    /* $8269: A6 */ nes_cpu_instruction_boundary(0x8269, 3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_826B:;
    /* $826B: 60 */ nes_cpu_instruction_boundary(0x826B, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_BA80_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BA80_b1");
#endif
label_BA80:;
    /* $BA80: 04 */ nes_cpu_instruction_boundary(0xBA80, 3); (void)nes_read(0x64); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA82:;
    /* $BA82: 86 */ nes_cpu_instruction_boundary(0xBA82, 3); nes_write(0x64, g_cpu.X);
label_BA84:;
    /* $BA84: 00 */ nes_cpu_instruction_boundary(0xBA84, 7); nes_brk_executed(0xBA84); return;
}

void func_BA84_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BA84_b1");
#endif
label_BA84:;
    /* $BA84: 00 */ nes_cpu_instruction_boundary(0xBA84, 7); nes_brk_executed(0xBA84); return;
}

void func_BA69_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BA69_b1");
#endif
label_BA69:;
    /* $BA69: 85 */ nes_cpu_instruction_boundary(0xBA69, 3); nes_write(0x14, g_cpu.A);
label_BA6B:;
    /* $BA6B: 22 */ nes_cpu_instruction_boundary(0xBA6B, 2); /* ILLEGAL $22 — skip 1 */
label_BA6C:;
    /* $BA6C: 84 */ nes_cpu_instruction_boundary(0xBA6C, 3); nes_write(0x2C, g_cpu.Y);
label_BA6E:;
    /* $BA6E: 85 */ nes_cpu_instruction_boundary(0xBA6E, 3); nes_write(0x1E, g_cpu.A);
label_BA70:;
    /* $BA70: 82 */ nes_cpu_instruction_boundary(0xBA70, 2); /* NOP */
label_BA72:;
    /* $BA72: 84 */ nes_cpu_instruction_boundary(0xBA72, 3); nes_write(0x2C, g_cpu.Y);
label_BA74:;
    /* $BA74: 1E */ nes_cpu_instruction_boundary(0xBA74, 7); { uint16_t a=(0x0484 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA77:;
    /* $BA77: 82 */ nes_cpu_instruction_boundary(0xBA77, 2); /* NOP */
label_BA79:;
    /* $BA79: 38 */ nes_cpu_instruction_boundary(0xBA79, 2); g_cpu.C = 1;
label_BA7A:;
    /* $BA7A: 36 */ nes_cpu_instruction_boundary(0xBA7A, 6); { uint16_t a=(0x32 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA7C:;
    /* $BA7C: 04 */ nes_cpu_instruction_boundary(0xBA7C, 3); (void)nes_read(0x34); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA7E:;
    /* $BA7E: 04 */ nes_cpu_instruction_boundary(0xBA7E, 3); (void)nes_read(0x64); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA80:;
    /* $BA80: 04 */ nes_cpu_instruction_boundary(0xBA80, 3); (void)nes_read(0x64); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA82:;
    /* $BA82: 86 */ nes_cpu_instruction_boundary(0xBA82, 3); nes_write(0x64, g_cpu.X);
label_BA84:;
    /* $BA84: 00 */ nes_cpu_instruction_boundary(0xBA84, 7); nes_brk_executed(0xBA84); return;
}

void func_BAB4_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BAB4_b1");
#endif
label_BAB4:;
    /* $BAB4: 82 */ nes_cpu_instruction_boundary(0xBAB4, 2); /* NOP */
label_BAB6:;
    /* $BAB6: 84 */ nes_cpu_instruction_boundary(0xBAB6, 3); nes_write(0x22, g_cpu.Y);
label_BAB8:;
    /* $BAB8: 14 */ nes_cpu_instruction_boundary(0xBAB8, 4); (void)nes_read((0x21 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BABA:;
    /* $BABA: D0 */ nes_cpu_instruction_boundary(0xBABA, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); call_by_address(0xBA80); return; }
label_BABC:;
    /* $BABC: D0 */ nes_cpu_instruction_boundary(0xBABC, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_BAEF; }
label_BABE:;
    /* $BABE: D0 */ nes_cpu_instruction_boundary(0xBABE, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); call_by_address(0xBA84); return; }
label_BAC0:;
    /* $BAC0: D0 */ nes_cpu_instruction_boundary(0xBAC0, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_BAC2; }
label_BAC2:;
    /* $BAC2: 82 */ nes_cpu_instruction_boundary(0xBAC2, 2); /* NOP */
label_BAC4:;
    /* $BAC4: 84 */ nes_cpu_instruction_boundary(0xBAC4, 3); nes_write(0x2C, g_cpu.Y);
label_BAC6:;
    /* $BAC6: 2C */ nes_cpu_instruction_boundary(0xBAC6, 4); { uint8_t m=nes_read(0x2C82); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BAC9:;
    /* $BAC9: 30 */ nes_cpu_instruction_boundary(0xBAC9, 2); if (g_cpu.N) { maybe_trigger_vblank(1); goto label_BACF; }
label_BACB:;
    /* $BACB: 34 */ nes_cpu_instruction_boundary(0xBACB, 4); (void)nes_read((0x2C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BACD:;
    /* $BACD: 04 */ nes_cpu_instruction_boundary(0xBACD, 3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BACF:;
    /* $BACF: 86 */ nes_cpu_instruction_boundary(0xBACF, 3); nes_write(0x22, g_cpu.X);
label_BAD1:;
    /* $BAD1: 00 */ nes_cpu_instruction_boundary(0xBAD1, 7); nes_brk_executed(0xBAD1); return;
label_BAD2:;
    /* $BAD2: A4 */ nes_cpu_instruction_boundary(0xBAD2, 3); g_cpu.Y = nes_read(0x25); FLAG_NZ(g_cpu.Y);
label_BAD4:;
    /* $BAD4: 25 */ nes_cpu_instruction_boundary(0xBAD4, 3); g_cpu.A &= nes_read(0xA4); FLAG_NZ(g_cpu.A);
label_BAD6:;
    /* $BAD6: 29 */ nes_cpu_instruction_boundary(0xBAD6, 2); g_cpu.A &= 0xA2; FLAG_NZ(g_cpu.A);
label_BAD8:;
    /* $BAD8: 1D */ nes_cpu_instruction_boundary(0xBAD8, 4); g_cpu.A |= nes_read((0x959C + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BADB:;
    /* $BADB: 82 */ nes_cpu_instruction_boundary(0xBADB, 2); /* NOP */
label_BADD:;
    /* $BADD: 2C */ nes_cpu_instruction_boundary(0xBADD, 4); { uint8_t m=nes_read(0x2C04); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BAE0:;
    /* $BAE0: 04 */ nes_cpu_instruction_boundary(0xBAE0, 3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAE2:;
    /* $BAE2: 30 */ nes_cpu_instruction_boundary(0xBAE2, 2); if (g_cpu.N) { maybe_trigger_vblank(1); call_by_address(0xBA69); return; }
label_BAE4:;
    /* $BAE4: 34 */ nes_cpu_instruction_boundary(0xBAE4, 4); (void)nes_read((0x04 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAE6:;
    /* $BAE6: 04 */ nes_cpu_instruction_boundary(0xBAE6, 3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAE8:;
    /* $BAE8: A4 */ nes_cpu_instruction_boundary(0xBAE8, 3); g_cpu.Y = nes_read(0x25); FLAG_NZ(g_cpu.Y);
label_BAEA:;
    /* $BAEA: 25 */ nes_cpu_instruction_boundary(0xBAEA, 3); g_cpu.A &= nes_read(0xA4); FLAG_NZ(g_cpu.A);
label_BAEC:;
    /* $BAEC: A8 */ nes_cpu_instruction_boundary(0xBAEC, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_BAED:;
    /* $BAED: 63 */ nes_cpu_instruction_boundary(0xBAED, 8); { uint16_t a=nes_read16zp((0x04 + g_cpu.X) & 0xFF); uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); uint16_t r=g_cpu.A+v+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,v); g_cpu.A=r&0xFF; }
label_BAEF:;
    /* $BAEF: 85 */ nes_cpu_instruction_boundary(0xBAEF, 3); nes_write(0x0E, g_cpu.A);
label_BAF1:;
    /* $BAF1: 1A */ nes_cpu_instruction_boundary(0xBAF1, 2); /* NOP */
label_BAF2:;
    /* $BAF2: 84 */ nes_cpu_instruction_boundary(0xBAF2, 3); nes_write(0x24, g_cpu.Y);
label_BAF4:;
    /* $BAF4: 85 */ nes_cpu_instruction_boundary(0xBAF4, 3); nes_write(0x22, g_cpu.A);
label_BAF6:;
    /* $BAF6: 14 */ nes_cpu_instruction_boundary(0xBAF6, 4); (void)nes_read((0x84 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAF8:;
    /* $BAF8: 0C */ nes_cpu_instruction_boundary(0xBAF8, 4); (void)nes_read(0x3482); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAFB:;
    /* $BAFB: 84 */ nes_cpu_instruction_boundary(0xBAFB, 3); nes_write(0x34, g_cpu.Y);
label_BAFD:;
    /* $BAFD: 34 */ nes_cpu_instruction_boundary(0xBAFD, 4); (void)nes_read((0x82 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAFF:;
    /* $BAFF: 2C */ nes_cpu_instruction_boundary(0xBAFF, 4); { uint8_t m=nes_read(0x3484); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BB02:;
    /* $BB02: 86 */ nes_cpu_instruction_boundary(0xBB02, 3); nes_write(0x3A, g_cpu.X);
label_BB04:;
    /* $BB04: 04 */ nes_cpu_instruction_boundary(0xBB04, 3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BB06:;
    /* $BB06: A0 */ nes_cpu_instruction_boundary(0xBB06, 2); g_cpu.Y = 0x21; FLAG_NZ(g_cpu.Y);
label_BB08:;
    /* $BB08: 21 */ nes_cpu_instruction_boundary(0xBB08, 6); g_cpu.A &= nes_read(nes_read16zp((0xA0 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BB0A:;
    /* $BB0A: 21 */ nes_cpu_instruction_boundary(0xBB0A, 6); g_cpu.A &= nes_read(nes_read16zp((0x2B + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BB0C:;
    /* $BB0C: 05 */ nes_cpu_instruction_boundary(0xBB0C, 3); g_cpu.A |= nes_read(0xA3); FLAG_NZ(g_cpu.A);
label_BB0E:;
    /* $BB0E: 82 */ nes_cpu_instruction_boundary(0xBB0E, 2); /* NOP */
label_BB10:;
    /* $BB10: 84 */ nes_cpu_instruction_boundary(0xBB10, 3); nes_write(0x18, g_cpu.Y);
label_BB12:;
    /* $BB12: 18 */ nes_cpu_instruction_boundary(0xBB12, 2); g_cpu.C = 0;
label_BB13:;
    /* $BB13: 82 */ nes_cpu_instruction_boundary(0xBB13, 2); /* NOP */
label_BB15:;
    /* $BB15: 18 */ nes_cpu_instruction_boundary(0xBB15, 2); g_cpu.C = 0;
label_BB16:;
    /* $BB16: 04 */ nes_cpu_instruction_boundary(0xBB16, 3); (void)nes_read(0x86); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BB18:;
    /* $BB18: 3A */ nes_cpu_instruction_boundary(0xBB18, 2); /* NOP */
label_BB19:;
    /* $BB19: 22 */ nes_cpu_instruction_boundary(0xBB19, 2); /* ILLEGAL $22 — skip 1 */
label_BB1A:;
    /* $BB1A: 31 */ nes_cpu_instruction_boundary(0xBB1A, 5); g_cpu.A &= nes_read((nes_read16zp(0x90) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB1C:;
    /* $BB1C: 31 */ nes_cpu_instruction_boundary(0xBB1C, 5); g_cpu.A &= nes_read((nes_read16zp(0x90) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB1E:;
    /* $BB1E: 31 */ nes_cpu_instruction_boundary(0xBB1E, 5); g_cpu.A &= nes_read((nes_read16zp(0x71) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB20:;
    /* $BB20: 31 */ nes_cpu_instruction_boundary(0xBB20, 5); g_cpu.A &= nes_read((nes_read16zp(0x90) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB22:;
    /* $BB22: 90 */ nes_cpu_instruction_boundary(0xBB22, 2); if (!g_cpu.C) {
    nes_cpu_instruction_boundary(0xBAB4, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BAB4;
    }
label_BB24:;
    /* $BB24: 00 */ nes_cpu_instruction_boundary(0xBB24, 7); nes_brk_executed(0xBB24); return;
}

void func_BC87_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BC87_b1");
#endif
label_BC87:;
    /* $BC87: 84 */ nes_cpu_instruction_boundary(0xBC87, 3); nes_write(0x36, g_cpu.Y);
label_BC89:;
    /* $BC89: 00 */ nes_cpu_instruction_boundary(0xBC89, 7); nes_brk_executed(0xBC89); return;
}

void func_C468_body(int _entry) {
    switch (_entry) {
        case 1: goto label_C46D;
    }
label_C468:;
    /* $C468: C4 */ nes_cpu_instruction_boundary(0xC468, 3); { uint8_t m=nes_read(0x9D); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_C46A:;
    /* $C46A: 88 */ nes_cpu_instruction_boundary(0xC46A, 2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C46B:;
    /* $C46B: 03 */ nes_cpu_instruction_boundary(0xC46B, 8); { uint16_t a=nes_read16zp((0xB9 + g_cpu.X) & 0xFF); uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_C46D:;
    /* $C46D: 54 */ nes_cpu_instruction_boundary(0xC46D, 4); (void)nes_read((0xC4 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_C46F:;
    /* $C46F: 95 */ nes_cpu_instruction_boundary(0xC46F, 4); nes_write((0x34 + g_cpu.X) & 0xFF, g_cpu.A);
label_C471:;
    /* $C471: B5 */ nes_cpu_instruction_boundary(0xC471, 4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C473:;
    /* $C473: 18 */ nes_cpu_instruction_boundary(0xC473, 2); g_cpu.C = 0;
label_C474:;
    /* $C474: 69 */ nes_cpu_instruction_boundary(0xC474, 2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_C476:;
    /* $C476: 95 */ nes_cpu_instruction_boundary(0xC476, 4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_C478:;
    /* $C478: B5 */ nes_cpu_instruction_boundary(0xC478, 4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C47A:;
    /* $C47A: 18 */ nes_cpu_instruction_boundary(0xC47A, 2); g_cpu.C = 0;
label_C47B:;
    /* $C47B: 69 */ nes_cpu_instruction_boundary(0xC47B, 2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_C47D:;
    /* $C47D: 95 */ nes_cpu_instruction_boundary(0xC47D, 4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_C47F:;
    /* $C47F: B5 */ nes_cpu_instruction_boundary(0xC47F, 4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C481:;
    /* $C481: 69 */ nes_cpu_instruction_boundary(0xC481, 2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_C483:;
    /* $C483: 95 */ nes_cpu_instruction_boundary(0xC483, 4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_C485:;
    /* $C485: 4C */ nes_cpu_instruction_boundary(0xC485, 3); nes_cpu_instruction_boundary(0xC7D9, 2); func_C7D9(); return;
}

void func_C468(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_C468");
#endif
    func_C468_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_C46D(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_C46D");
#endif
    func_C468_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_BC90_b1_body(int _entry) {
    switch (_entry) {
        case 1: goto label_BC9E;
    }
label_BC90:;
    /* $BC90: 66 */ nes_cpu_instruction_boundary(0xBC90, 5); { uint16_t a=0xA6; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BC92:;
    /* $BC92: 4A */ nes_cpu_instruction_boundary(0xBC92, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_BC93:;
    /* $BC93: A8 */ nes_cpu_instruction_boundary(0xBC93, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_BC94:;
    /* $BC94: 68 */ nes_cpu_instruction_boundary(0xBC94, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_BC95:;
    /* $BC95: A8 */ nes_cpu_instruction_boundary(0xBC95, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_BC96:;
    /* $BC96: 6A */ nes_cpu_instruction_boundary(0xBC96, 2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_BC97:;
    /* $BC97: 44 */ nes_cpu_instruction_boundary(0xBC97, 3); (void)nes_read(0x2B); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC99:;
    /* $BC99: 81 */ nes_cpu_instruction_boundary(0xBC99, 6); nes_write(nes_read16zp((0x2A + g_cpu.X) & 0xFF), g_cpu.A);
label_BC9B:;
    /* $BC9B: 42 */ nes_cpu_instruction_boundary(0xBC9B, 2); /* ILLEGAL $42 — skip 1 */
label_BC9C:;
    /* $BC9C: 04 */ nes_cpu_instruction_boundary(0xBC9C, 3); (void)nes_read(0x42); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC9E:;
    /* $BC9E: 42 */ nes_cpu_instruction_boundary(0xBC9E, 2); /* ILLEGAL $42 — skip 1 */
label_BC9F:;
    /* $BC9F: 04 */ nes_cpu_instruction_boundary(0xBC9F, 3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCA1:;
    /* $BCA1: 64 */ nes_cpu_instruction_boundary(0xBCA1, 3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCA3:;
    /* $BCA3: 64 */ nes_cpu_instruction_boundary(0xBCA3, 3); (void)nes_read(0x64); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCA5:;
    /* $BCA5: 04 */ nes_cpu_instruction_boundary(0xBCA5, 3); (void)nes_read(0x2E); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCA7:;
    /* $BCA7: 46 */ nes_cpu_instruction_boundary(0xBCA7, 5); { uint16_t a=0x04; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BCA9:;
    /* $BCA9: 46 */ nes_cpu_instruction_boundary(0xBCA9, 5); { uint16_t a=0x46; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BCAB:;
    /* $BCAB: 04 */ nes_cpu_instruction_boundary(0xBCAB, 3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCAD:;
    /* $BCAD: 04 */ nes_cpu_instruction_boundary(0xBCAD, 3); (void)nes_read(0x84); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCAF:;
    /* $BCAF: 22 */ nes_cpu_instruction_boundary(0xBCAF, 2); /* ILLEGAL $22 — skip 1 */
label_BCB0:;
    /* $BCB0: 87 */ nes_cpu_instruction_boundary(0xBCB0, 3); nes_write(0x04, g_cpu.A & g_cpu.X); /* SAX */
label_BCB2:;
    /* $BCB2: 06 */ nes_cpu_instruction_boundary(0xBCB2, 5); { uint16_t a=0x0C; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BCB4:;
    /* $BCB4: 14 */ nes_cpu_instruction_boundary(0xBCB4, 4); (void)nes_read((0x1C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCB6:;
    /* $BCB6: 22 */ nes_cpu_instruction_boundary(0xBCB6, 2); /* ILLEGAL $22 — skip 1 */
label_BCB7:;
    /* $BCB7: 86 */ nes_cpu_instruction_boundary(0xBCB7, 3); nes_write(0x2C, g_cpu.X);
label_BCB9:;
    /* $BCB9: 22 */ nes_cpu_instruction_boundary(0xBCB9, 2); /* ILLEGAL $22 — skip 1 */
label_BCBA:;
    /* $BCBA: 87 */ nes_cpu_instruction_boundary(0xBCBA, 3); nes_write(0x04, g_cpu.A & g_cpu.X); /* SAX */
label_BCBC:;
    /* $BCBC: 60 */ nes_cpu_instruction_boundary(0xBCBC, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_BC90_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BC90_b1");
#endif
    func_BC90_b1_body(0);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_BC9E_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BC9E_b1");
#endif
    func_BC90_b1_body(1);
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
}

void func_B3CD_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B3CD_b1");
#endif
label_B3CD:;
    /* $B3CD: A9 */ nes_cpu_instruction_boundary(0xB3CD, 2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B3CF:; /* ClimbingSub */
    /* $B3CF: D0 */ nes_cpu_instruction_boundary(0xB3CF, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3D3; }
label_B3D1:;
    /* $B3D1: A9 */ nes_cpu_instruction_boundary(0xB3D1, 2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_B3D3:;
    /* $B3D3: A2 */ nes_cpu_instruction_boundary(0xB3D3, 2); g_cpu.X = 0x82; FLAG_NZ(g_cpu.X);
label_B3D5:;
    /* $B3D5: A0 */ nes_cpu_instruction_boundary(0xB3D5, 2); g_cpu.Y = 0xA7; FLAG_NZ(g_cpu.Y);
label_B3D7:;
    /* $B3D7: 20 */ nes_cpu_instruction_boundary(0xB3D7, 6); func_F388();
label_B3DA:;
    /* $B3DA: A9 */ nes_cpu_instruction_boundary(0xB3DA, 2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B3DC:;
    /* $B3DC: 8D */ nes_cpu_instruction_boundary(0xB3DC, 4); nes_write(0x07BB, g_cpu.A);
label_B3DF:;
    /* $B3DF: AD */ nes_cpu_instruction_boundary(0xB3DF, 4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B3E2:;
    /* $B3E2: C9 */ nes_cpu_instruction_boundary(0xB3E2, 2); { int r=g_cpu.A-0x25; g_cpu.C=(g_cpu.A>=0x25)?1:0; FLAG_NZ(r&0xFF); }
label_B3E4:;
    /* $B3E4: D0 */ nes_cpu_instruction_boundary(0xB3E4, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3EC; }
label_B3E6:;
    /* $B3E6: A2 */ nes_cpu_instruction_boundary(0xB3E6, 2); g_cpu.X = 0x5F; FLAG_NZ(g_cpu.X);
label_B3E8:;
    /* $B3E8: A0 */ nes_cpu_instruction_boundary(0xB3E8, 2); g_cpu.Y = 0xF6; FLAG_NZ(g_cpu.Y);
label_B3EA:;
    /* $B3EA: D0 */ nes_cpu_instruction_boundary(0xB3EA, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3F4; }
label_B3EC:;
    /* $B3EC: C9 */ nes_cpu_instruction_boundary(0xB3EC, 2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_B3EE:;
    /* $B3EE: D0 */ nes_cpu_instruction_boundary(0xB3EE, 2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B419; }
label_B3F0:;
    /* $B3F0: A2 */ nes_cpu_instruction_boundary(0xB3F0, 2); g_cpu.X = 0x48; FLAG_NZ(g_cpu.X);
label_B3F2:;
    /* $B3F2: A0 */ nes_cpu_instruction_boundary(0xB3F2, 2); g_cpu.Y = 0xBC; FLAG_NZ(g_cpu.Y);
label_B3F4:;
    /* $B3F4: 20 */ nes_cpu_instruction_boundary(0xB3F4, 6); func_F381();
label_B3F7:;
    /* $B3F7: D0 */ nes_cpu_instruction_boundary(0xB3F7, 2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B419; }
label_B3F9:;
    /* $B3F9: A9 */ nes_cpu_instruction_boundary(0xB3F9, 2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_B3FB:;
    /* $B3FB: A0 */ nes_cpu_instruction_boundary(0xB3FB, 2); g_cpu.Y = 0x99; FLAG_NZ(g_cpu.Y);
label_B3FD:;
    /* $B3FD: D0 */ nes_cpu_instruction_boundary(0xB3FD, 2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B403; }
label_B3FF:;
    /* $B3FF: A9 */ nes_cpu_instruction_boundary(0xB3FF, 2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_B401:;
    /* $B401: A0 */ nes_cpu_instruction_boundary(0xB401, 2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_B403:;
    /* $B403: A2 */ nes_cpu_instruction_boundary(0xB403, 2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B405:;
    /* $B405: 8D */ nes_cpu_instruction_boundary(0xB405, 4); nes_write(0x07BB, g_cpu.A);
label_B408:;
    /* $B408: A9 */ nes_cpu_instruction_boundary(0xB408, 2); g_cpu.A = 0x0C; FLAG_NZ(g_cpu.A);
label_B40A:; /* CSetFDir */
    /* $B40A: 20 */ nes_cpu_instruction_boundary(0xB40A, 6); func_F388();
label_B40D:;
    /* $B40D: AD */ nes_cpu_instruction_boundary(0xB40D, 4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B410:;
    /* $B410: C9 */ nes_cpu_instruction_boundary(0xB410, 2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B412:;
    /* $B412: D0 */ nes_cpu_instruction_boundary(0xB412, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B419; }
label_B414:;
    /* $B414: A9 */ nes_cpu_instruction_boundary(0xB414, 2); g_cpu.A = 0xBB; FLAG_NZ(g_cpu.A);
label_B416:;
    /* $B416: 8D */ nes_cpu_instruction_boundary(0xB416, 4); nes_write(0x4001, g_cpu.A);
label_B419:;
    /* $B419: D0 */ nes_cpu_instruction_boundary(0xB419, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B41B:;
    /* $B41B: A4 */ nes_cpu_instruction_boundary(0xB41B, 3); g_cpu.Y = nes_read(0xFF); FLAG_NZ(g_cpu.Y);
label_B41D:;
    /* $B41D: F0 */ nes_cpu_instruction_boundary(0xB41D, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B43F; }
label_B41F:; /* ExitCSub */
    /* $B41F: 84 */ nes_cpu_instruction_boundary(0xB41F, 3); nes_write(0xF1, g_cpu.Y);
label_B421:;
    /* $B421: 30 */ nes_cpu_instruction_boundary(0xB421, 2); if (g_cpu.N) {
    nes_cpu_instruction_boundary(0xB3CD, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3CD;
    }
label_B423:;
    /* $B423: 46 */ nes_cpu_instruction_boundary(0xB423, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B425:;
    /* $B425: B0 */ nes_cpu_instruction_boundary(0xB425, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB3D1, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3D1;
    }
label_B427:;
    /* $B427: 46 */ nes_cpu_instruction_boundary(0xB427, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B429:;
    /* $B429: B0 */ nes_cpu_instruction_boundary(0xB429, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB3FF, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3FF;
    }
label_B42B:; /* FallMForceData */
    /* $B42B: 46 */ nes_cpu_instruction_boundary(0xB42B, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B42D:;
    /* $B42D: B0 */ nes_cpu_instruction_boundary(0xB42D, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B45B; }
label_B42F:;
    /* $B42F: 46 */ nes_cpu_instruction_boundary(0xB42F, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B431:;
    /* $B431: B0 */ nes_cpu_instruction_boundary(0xB431, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B47D; }
label_B433:;
    /* $B433: 46 */ nes_cpu_instruction_boundary(0xB433, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B435:;
    /* $B435: B0 */ nes_cpu_instruction_boundary(0xB435, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4B6; }
label_B437:;
    /* $B437: 46 */ nes_cpu_instruction_boundary(0xB437, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B439:; /* InitMForceData */
    /* $B439: B0 */ nes_cpu_instruction_boundary(0xB439, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB3F9, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3F9;
    }
label_B43B:;
    /* $B43B: 46 */ nes_cpu_instruction_boundary(0xB43B, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B43D:;
    /* $B43D: B0 */ nes_cpu_instruction_boundary(0xB43D, 2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3BF); return; }
label_B43F:;
    /* $B43F: A5 */ nes_cpu_instruction_boundary(0xB43F, 3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_B441:;
    /* $B441: F0 */ nes_cpu_instruction_boundary(0xB441, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B45A; }
label_B443:; /* MaxRightXSpdData */
    /* $B443: 30 */ nes_cpu_instruction_boundary(0xB443, 2); if (g_cpu.N) {
    nes_cpu_instruction_boundary(0xB3DF, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3DF;
    }
label_B445:;
    /* $B445: 4A */ nes_cpu_instruction_boundary(0xB445, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B446:;
    /* $B446: B0 */ nes_cpu_instruction_boundary(0xB446, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB3DF, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3DF;
    }
label_B448:;
    /* $B448: 4A */ nes_cpu_instruction_boundary(0xB448, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B449:;
    /* $B449: B0 */ nes_cpu_instruction_boundary(0xB449, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB40D, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B44B:;
    /* $B44B: 4A */ nes_cpu_instruction_boundary(0xB44B, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44C:;
    /* $B44C: B0 */ nes_cpu_instruction_boundary(0xB44C, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B469; }
label_B44E:;
    /* $B44E: 4A */ nes_cpu_instruction_boundary(0xB44E, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44F:;
    /* $B44F: B0 */ nes_cpu_instruction_boundary(0xB44F, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B48D; }
label_B451:;
    /* $B451: 4A */ nes_cpu_instruction_boundary(0xB451, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B452:;
    /* $B452: B0 */ nes_cpu_instruction_boundary(0xB452, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4BB; }
label_B454:;
    /* $B454: 4A */ nes_cpu_instruction_boundary(0xB454, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B455:;
    /* $B455: B0 */ nes_cpu_instruction_boundary(0xB455, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB40D, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B457:;
    /* $B457: 4A */ nes_cpu_instruction_boundary(0xB457, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B458:;
    /* $B458: B0 */ nes_cpu_instruction_boundary(0xB458, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B45A:;
    /* $B45A: 60 */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return; /* branch-target RTS */
label_B45B:;
    /* $B45B: A9 */ nes_cpu_instruction_boundary(0xB45B, 2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B45D:;
    /* $B45D: 8D */ nes_cpu_instruction_boundary(0xB45D, 4); nes_write(0x07BB, g_cpu.A);
label_B460:;
    /* $B460: A0 */ nes_cpu_instruction_boundary(0xB460, 2); g_cpu.Y = 0x9C; FLAG_NZ(g_cpu.Y);
label_B462:;
    /* $B462: A2 */ nes_cpu_instruction_boundary(0xB462, 2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B464:;
    /* $B464: A9 */ nes_cpu_instruction_boundary(0xB464, 2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B466:;
    /* $B466: 20 */ nes_cpu_instruction_boundary(0xB466, 6); func_F388();
label_B469:;
    /* $B469: AC */ nes_cpu_instruction_boundary(0xB469, 4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B46C:;
    /* $B46C: B9 */ nes_cpu_instruction_boundary(0xB46C, 4); g_cpu.A = nes_read((0xF3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B46F:;
    /* $B46F: 8D */ nes_cpu_instruction_boundary(0xB46F, 4); nes_write(0x4000, g_cpu.A);
label_B472:;
    /* $B472: C0 */ nes_cpu_instruction_boundary(0xB472, 2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B474:;
    /* $B474: D0 */ nes_cpu_instruction_boundary(0xB474, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B476:;
    /* $B476: A9 */ nes_cpu_instruction_boundary(0xB476, 2); g_cpu.A = 0x9E; FLAG_NZ(g_cpu.A);
label_B478:;
    /* $B478: 8D */ nes_cpu_instruction_boundary(0xB478, 4); nes_write(0x4002, g_cpu.A);
label_B47B:;
    /* $B47B: D0 */ nes_cpu_instruction_boundary(0xB47B, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B47D:;
    /* $B47D: A9 */ nes_cpu_instruction_boundary(0xB47D, 2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B47F:;
    /* $B47F: A0 */ nes_cpu_instruction_boundary(0xB47F, 2); g_cpu.Y = 0xCB; FLAG_NZ(g_cpu.Y);
label_B481:;
    /* $B481: A2 */ nes_cpu_instruction_boundary(0xB481, 2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_B483:;
    /* $B483: 8D */ nes_cpu_instruction_boundary(0xB483, 4); nes_write(0x07BB, g_cpu.A);
label_B486:;
    /* $B486: A9 */ nes_cpu_instruction_boundary(0xB486, 2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B488:; /* NoJump */
    /* $B488: 20 */ nes_cpu_instruction_boundary(0xB488, 6); func_F388();
label_B48B:; /* ProcJumping */
    /* $B48B: D0 */ nes_cpu_instruction_boundary(0xB48B, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B48D:;
    /* $B48D: AC */ nes_cpu_instruction_boundary(0xB48D, 4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B490:;
    /* $B490: C0 */ nes_cpu_instruction_boundary(0xB490, 2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_B492:;
    /* $B492: D0 */ nes_cpu_instruction_boundary(0xB492, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49D; }
label_B494:;
    /* $B494: A9 */ nes_cpu_instruction_boundary(0xB494, 2); g_cpu.A = 0xA0; FLAG_NZ(g_cpu.A);
label_B496:;
    /* $B496: 8D */ nes_cpu_instruction_boundary(0xB496, 4); nes_write(0x4002, g_cpu.A);
label_B499:;
    /* $B499: A9 */ nes_cpu_instruction_boundary(0xB499, 2); g_cpu.A = 0x9F; FLAG_NZ(g_cpu.A);
label_B49B:;
    /* $B49B: D0 */ nes_cpu_instruction_boundary(0xB49B, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49F; }
label_B49D:;
    /* $B49D: A9 */ nes_cpu_instruction_boundary(0xB49D, 2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_B49F:;
    /* $B49F: 8D */ nes_cpu_instruction_boundary(0xB49F, 4); nes_write(0x4000, g_cpu.A);
label_B4A2:;
    /* $B4A2: CE */ nes_cpu_instruction_boundary(0xB4A2, 6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B4A5:;
    /* $B4A5: D0 */ nes_cpu_instruction_boundary(0xB4A5, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4B5; }
label_B4A7:;
    /* $B4A7: A2 */ nes_cpu_instruction_boundary(0xB4A7, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B4A9:;
    /* $B4A9: 86 */ nes_cpu_instruction_boundary(0xB4A9, 3); nes_write(0xF1, g_cpu.X);
label_B4AB:;
    /* $B4AB: A2 */ nes_cpu_instruction_boundary(0xB4AB, 2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_B4AD:;
    /* $B4AD: 8E */ nes_cpu_instruction_boundary(0xB4AD, 4); nes_write(0x4015, g_cpu.X);
label_B4B0:;
    /* $B4B0: A2 */ nes_cpu_instruction_boundary(0xB4B0, 2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B4B2:;
    /* $B4B2: 8E */ nes_cpu_instruction_boundary(0xB4B2, 4); nes_write(0x4015, g_cpu.X);
label_B4B5:;
    /* $B4B5: 60 */ nes_cpu_instruction_boundary(0xB4B5, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_B4B6:;
    /* $B4B6: A9 */ nes_cpu_instruction_boundary(0xB4B6, 2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_B4B8:;
    /* $B4B8: 8D */ nes_cpu_instruction_boundary(0xB4B8, 4); nes_write(0x07BB, g_cpu.A);
label_B4BB:;
    /* $B4BB: AD */ nes_cpu_instruction_boundary(0xB4BB, 4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B4BE:;
    /* $B4BE: 4A */ nes_cpu_instruction_boundary(0xB4BE, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4BF:;
    /* $B4BF: B0 */ nes_cpu_instruction_boundary(0xB4BF, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C1:;
    /* $B4C1: 4A */ nes_cpu_instruction_boundary(0xB4C1, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4C2:;
    /* $B4C2: B0 */ nes_cpu_instruction_boundary(0xB4C2, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C4:;
    /* $B4C4: 29 */ nes_cpu_instruction_boundary(0xB4C4, 2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_B4C6:;
    /* $B4C6: F0 */ nes_cpu_instruction_boundary(0xB4C6, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C8:;
    /* $B4C8: A0 */ nes_cpu_instruction_boundary(0xB4C8, 2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_B4CA:;
    /* $B4CA: A2 */ nes_cpu_instruction_boundary(0xB4CA, 2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_B4CC:;
    /* $B4CC: A9 */ nes_cpu_instruction_boundary(0xB4CC, 2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_B4CE:;
    /* $B4CE: 20 */ nes_cpu_instruction_boundary(0xB4CE, 6); func_F388();
label_B4D1:;
    /* $B4D1: 4C */ nes_cpu_instruction_boundary(0xB4D1, 3); nes_cpu_instruction_boundary(0xF4A2, 2); func_F4A2(); return;
}

void func_B3D1_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B3D1_b1");
#endif
label_B3D1:;
    /* $B3D1: A9 */ nes_cpu_instruction_boundary(0xB3D1, 2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_B3D3:;
    /* $B3D3: A2 */ nes_cpu_instruction_boundary(0xB3D3, 2); g_cpu.X = 0x82; FLAG_NZ(g_cpu.X);
label_B3D5:;
    /* $B3D5: A0 */ nes_cpu_instruction_boundary(0xB3D5, 2); g_cpu.Y = 0xA7; FLAG_NZ(g_cpu.Y);
label_B3D7:;
    /* $B3D7: 20 */ nes_cpu_instruction_boundary(0xB3D7, 6); func_F388();
label_B3DA:;
    /* $B3DA: A9 */ nes_cpu_instruction_boundary(0xB3DA, 2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B3DC:;
    /* $B3DC: 8D */ nes_cpu_instruction_boundary(0xB3DC, 4); nes_write(0x07BB, g_cpu.A);
label_B3DF:;
    /* $B3DF: AD */ nes_cpu_instruction_boundary(0xB3DF, 4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B3E2:;
    /* $B3E2: C9 */ nes_cpu_instruction_boundary(0xB3E2, 2); { int r=g_cpu.A-0x25; g_cpu.C=(g_cpu.A>=0x25)?1:0; FLAG_NZ(r&0xFF); }
label_B3E4:;
    /* $B3E4: D0 */ nes_cpu_instruction_boundary(0xB3E4, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3EC; }
label_B3E6:;
    /* $B3E6: A2 */ nes_cpu_instruction_boundary(0xB3E6, 2); g_cpu.X = 0x5F; FLAG_NZ(g_cpu.X);
label_B3E8:;
    /* $B3E8: A0 */ nes_cpu_instruction_boundary(0xB3E8, 2); g_cpu.Y = 0xF6; FLAG_NZ(g_cpu.Y);
label_B3EA:;
    /* $B3EA: D0 */ nes_cpu_instruction_boundary(0xB3EA, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B3F4; }
label_B3EC:;
    /* $B3EC: C9 */ nes_cpu_instruction_boundary(0xB3EC, 2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_B3EE:;
    /* $B3EE: D0 */ nes_cpu_instruction_boundary(0xB3EE, 2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B419; }
label_B3F0:;
    /* $B3F0: A2 */ nes_cpu_instruction_boundary(0xB3F0, 2); g_cpu.X = 0x48; FLAG_NZ(g_cpu.X);
label_B3F2:;
    /* $B3F2: A0 */ nes_cpu_instruction_boundary(0xB3F2, 2); g_cpu.Y = 0xBC; FLAG_NZ(g_cpu.Y);
label_B3F4:;
    /* $B3F4: 20 */ nes_cpu_instruction_boundary(0xB3F4, 6); func_F381();
label_B3F7:;
    /* $B3F7: D0 */ nes_cpu_instruction_boundary(0xB3F7, 2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B419; }
label_B3F9:;
    /* $B3F9: A9 */ nes_cpu_instruction_boundary(0xB3F9, 2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_B3FB:;
    /* $B3FB: A0 */ nes_cpu_instruction_boundary(0xB3FB, 2); g_cpu.Y = 0x99; FLAG_NZ(g_cpu.Y);
label_B3FD:;
    /* $B3FD: D0 */ nes_cpu_instruction_boundary(0xB3FD, 2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B403; }
label_B3FF:;
    /* $B3FF: A9 */ nes_cpu_instruction_boundary(0xB3FF, 2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_B401:;
    /* $B401: A0 */ nes_cpu_instruction_boundary(0xB401, 2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_B403:;
    /* $B403: A2 */ nes_cpu_instruction_boundary(0xB403, 2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B405:;
    /* $B405: 8D */ nes_cpu_instruction_boundary(0xB405, 4); nes_write(0x07BB, g_cpu.A);
label_B408:;
    /* $B408: A9 */ nes_cpu_instruction_boundary(0xB408, 2); g_cpu.A = 0x0C; FLAG_NZ(g_cpu.A);
label_B40A:; /* CSetFDir */
    /* $B40A: 20 */ nes_cpu_instruction_boundary(0xB40A, 6); func_F388();
label_B40D:;
    /* $B40D: AD */ nes_cpu_instruction_boundary(0xB40D, 4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B410:;
    /* $B410: C9 */ nes_cpu_instruction_boundary(0xB410, 2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B412:;
    /* $B412: D0 */ nes_cpu_instruction_boundary(0xB412, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B419; }
label_B414:;
    /* $B414: A9 */ nes_cpu_instruction_boundary(0xB414, 2); g_cpu.A = 0xBB; FLAG_NZ(g_cpu.A);
label_B416:;
    /* $B416: 8D */ nes_cpu_instruction_boundary(0xB416, 4); nes_write(0x4001, g_cpu.A);
label_B419:;
    /* $B419: D0 */ nes_cpu_instruction_boundary(0xB419, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B41B:;
    /* $B41B: A4 */ nes_cpu_instruction_boundary(0xB41B, 3); g_cpu.Y = nes_read(0xFF); FLAG_NZ(g_cpu.Y);
label_B41D:;
    /* $B41D: F0 */ nes_cpu_instruction_boundary(0xB41D, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B43F; }
label_B41F:; /* ExitCSub */
    /* $B41F: 84 */ nes_cpu_instruction_boundary(0xB41F, 3); nes_write(0xF1, g_cpu.Y);
label_B421:;
    /* $B421: 30 */ nes_cpu_instruction_boundary(0xB421, 2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xB3CD); return; }
label_B423:;
    /* $B423: 46 */ nes_cpu_instruction_boundary(0xB423, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B425:;
    /* $B425: B0 */ nes_cpu_instruction_boundary(0xB425, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB3D1, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3D1;
    }
label_B427:;
    /* $B427: 46 */ nes_cpu_instruction_boundary(0xB427, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B429:;
    /* $B429: B0 */ nes_cpu_instruction_boundary(0xB429, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB3FF, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3FF;
    }
label_B42B:; /* FallMForceData */
    /* $B42B: 46 */ nes_cpu_instruction_boundary(0xB42B, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B42D:;
    /* $B42D: B0 */ nes_cpu_instruction_boundary(0xB42D, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B45B; }
label_B42F:;
    /* $B42F: 46 */ nes_cpu_instruction_boundary(0xB42F, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B431:;
    /* $B431: B0 */ nes_cpu_instruction_boundary(0xB431, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B47D; }
label_B433:;
    /* $B433: 46 */ nes_cpu_instruction_boundary(0xB433, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B435:;
    /* $B435: B0 */ nes_cpu_instruction_boundary(0xB435, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4B6; }
label_B437:;
    /* $B437: 46 */ nes_cpu_instruction_boundary(0xB437, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B439:; /* InitMForceData */
    /* $B439: B0 */ nes_cpu_instruction_boundary(0xB439, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB3F9, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3F9;
    }
label_B43B:;
    /* $B43B: 46 */ nes_cpu_instruction_boundary(0xB43B, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B43D:;
    /* $B43D: B0 */ nes_cpu_instruction_boundary(0xB43D, 2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3BF); return; }
label_B43F:;
    /* $B43F: A5 */ nes_cpu_instruction_boundary(0xB43F, 3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_B441:;
    /* $B441: F0 */ nes_cpu_instruction_boundary(0xB441, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B45A; }
label_B443:; /* MaxRightXSpdData */
    /* $B443: 30 */ nes_cpu_instruction_boundary(0xB443, 2); if (g_cpu.N) {
    nes_cpu_instruction_boundary(0xB3DF, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3DF;
    }
label_B445:;
    /* $B445: 4A */ nes_cpu_instruction_boundary(0xB445, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B446:;
    /* $B446: B0 */ nes_cpu_instruction_boundary(0xB446, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB3DF, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3DF;
    }
label_B448:;
    /* $B448: 4A */ nes_cpu_instruction_boundary(0xB448, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B449:;
    /* $B449: B0 */ nes_cpu_instruction_boundary(0xB449, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB40D, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B44B:;
    /* $B44B: 4A */ nes_cpu_instruction_boundary(0xB44B, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44C:;
    /* $B44C: B0 */ nes_cpu_instruction_boundary(0xB44C, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B469; }
label_B44E:;
    /* $B44E: 4A */ nes_cpu_instruction_boundary(0xB44E, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44F:;
    /* $B44F: B0 */ nes_cpu_instruction_boundary(0xB44F, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B48D; }
label_B451:;
    /* $B451: 4A */ nes_cpu_instruction_boundary(0xB451, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B452:;
    /* $B452: B0 */ nes_cpu_instruction_boundary(0xB452, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4BB; }
label_B454:;
    /* $B454: 4A */ nes_cpu_instruction_boundary(0xB454, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B455:;
    /* $B455: B0 */ nes_cpu_instruction_boundary(0xB455, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB40D, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B457:;
    /* $B457: 4A */ nes_cpu_instruction_boundary(0xB457, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B458:;
    /* $B458: B0 */ nes_cpu_instruction_boundary(0xB458, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B45A:;
    /* $B45A: 60 */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return; /* branch-target RTS */
label_B45B:;
    /* $B45B: A9 */ nes_cpu_instruction_boundary(0xB45B, 2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B45D:;
    /* $B45D: 8D */ nes_cpu_instruction_boundary(0xB45D, 4); nes_write(0x07BB, g_cpu.A);
label_B460:;
    /* $B460: A0 */ nes_cpu_instruction_boundary(0xB460, 2); g_cpu.Y = 0x9C; FLAG_NZ(g_cpu.Y);
label_B462:;
    /* $B462: A2 */ nes_cpu_instruction_boundary(0xB462, 2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B464:;
    /* $B464: A9 */ nes_cpu_instruction_boundary(0xB464, 2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B466:;
    /* $B466: 20 */ nes_cpu_instruction_boundary(0xB466, 6); func_F388();
label_B469:;
    /* $B469: AC */ nes_cpu_instruction_boundary(0xB469, 4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B46C:;
    /* $B46C: B9 */ nes_cpu_instruction_boundary(0xB46C, 4); g_cpu.A = nes_read((0xF3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B46F:;
    /* $B46F: 8D */ nes_cpu_instruction_boundary(0xB46F, 4); nes_write(0x4000, g_cpu.A);
label_B472:;
    /* $B472: C0 */ nes_cpu_instruction_boundary(0xB472, 2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B474:;
    /* $B474: D0 */ nes_cpu_instruction_boundary(0xB474, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B476:;
    /* $B476: A9 */ nes_cpu_instruction_boundary(0xB476, 2); g_cpu.A = 0x9E; FLAG_NZ(g_cpu.A);
label_B478:;
    /* $B478: 8D */ nes_cpu_instruction_boundary(0xB478, 4); nes_write(0x4002, g_cpu.A);
label_B47B:;
    /* $B47B: D0 */ nes_cpu_instruction_boundary(0xB47B, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B47D:;
    /* $B47D: A9 */ nes_cpu_instruction_boundary(0xB47D, 2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B47F:;
    /* $B47F: A0 */ nes_cpu_instruction_boundary(0xB47F, 2); g_cpu.Y = 0xCB; FLAG_NZ(g_cpu.Y);
label_B481:;
    /* $B481: A2 */ nes_cpu_instruction_boundary(0xB481, 2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_B483:;
    /* $B483: 8D */ nes_cpu_instruction_boundary(0xB483, 4); nes_write(0x07BB, g_cpu.A);
label_B486:;
    /* $B486: A9 */ nes_cpu_instruction_boundary(0xB486, 2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B488:; /* NoJump */
    /* $B488: 20 */ nes_cpu_instruction_boundary(0xB488, 6); func_F388();
label_B48B:; /* ProcJumping */
    /* $B48B: D0 */ nes_cpu_instruction_boundary(0xB48B, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B48D:;
    /* $B48D: AC */ nes_cpu_instruction_boundary(0xB48D, 4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B490:;
    /* $B490: C0 */ nes_cpu_instruction_boundary(0xB490, 2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_B492:;
    /* $B492: D0 */ nes_cpu_instruction_boundary(0xB492, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49D; }
label_B494:;
    /* $B494: A9 */ nes_cpu_instruction_boundary(0xB494, 2); g_cpu.A = 0xA0; FLAG_NZ(g_cpu.A);
label_B496:;
    /* $B496: 8D */ nes_cpu_instruction_boundary(0xB496, 4); nes_write(0x4002, g_cpu.A);
label_B499:;
    /* $B499: A9 */ nes_cpu_instruction_boundary(0xB499, 2); g_cpu.A = 0x9F; FLAG_NZ(g_cpu.A);
label_B49B:;
    /* $B49B: D0 */ nes_cpu_instruction_boundary(0xB49B, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49F; }
label_B49D:;
    /* $B49D: A9 */ nes_cpu_instruction_boundary(0xB49D, 2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_B49F:;
    /* $B49F: 8D */ nes_cpu_instruction_boundary(0xB49F, 4); nes_write(0x4000, g_cpu.A);
label_B4A2:;
    /* $B4A2: CE */ nes_cpu_instruction_boundary(0xB4A2, 6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B4A5:;
    /* $B4A5: D0 */ nes_cpu_instruction_boundary(0xB4A5, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4B5; }
label_B4A7:;
    /* $B4A7: A2 */ nes_cpu_instruction_boundary(0xB4A7, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B4A9:;
    /* $B4A9: 86 */ nes_cpu_instruction_boundary(0xB4A9, 3); nes_write(0xF1, g_cpu.X);
label_B4AB:;
    /* $B4AB: A2 */ nes_cpu_instruction_boundary(0xB4AB, 2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_B4AD:;
    /* $B4AD: 8E */ nes_cpu_instruction_boundary(0xB4AD, 4); nes_write(0x4015, g_cpu.X);
label_B4B0:;
    /* $B4B0: A2 */ nes_cpu_instruction_boundary(0xB4B0, 2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B4B2:;
    /* $B4B2: 8E */ nes_cpu_instruction_boundary(0xB4B2, 4); nes_write(0x4015, g_cpu.X);
label_B4B5:;
    /* $B4B5: 60 */ nes_cpu_instruction_boundary(0xB4B5, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_B4B6:;
    /* $B4B6: A9 */ nes_cpu_instruction_boundary(0xB4B6, 2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_B4B8:;
    /* $B4B8: 8D */ nes_cpu_instruction_boundary(0xB4B8, 4); nes_write(0x07BB, g_cpu.A);
label_B4BB:;
    /* $B4BB: AD */ nes_cpu_instruction_boundary(0xB4BB, 4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B4BE:;
    /* $B4BE: 4A */ nes_cpu_instruction_boundary(0xB4BE, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4BF:;
    /* $B4BF: B0 */ nes_cpu_instruction_boundary(0xB4BF, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C1:;
    /* $B4C1: 4A */ nes_cpu_instruction_boundary(0xB4C1, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4C2:;
    /* $B4C2: B0 */ nes_cpu_instruction_boundary(0xB4C2, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C4:;
    /* $B4C4: 29 */ nes_cpu_instruction_boundary(0xB4C4, 2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_B4C6:;
    /* $B4C6: F0 */ nes_cpu_instruction_boundary(0xB4C6, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C8:;
    /* $B4C8: A0 */ nes_cpu_instruction_boundary(0xB4C8, 2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_B4CA:;
    /* $B4CA: A2 */ nes_cpu_instruction_boundary(0xB4CA, 2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_B4CC:;
    /* $B4CC: A9 */ nes_cpu_instruction_boundary(0xB4CC, 2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_B4CE:;
    /* $B4CE: 20 */ nes_cpu_instruction_boundary(0xB4CE, 6); func_F388();
label_B4D1:;
    /* $B4D1: 4C */ nes_cpu_instruction_boundary(0xB4D1, 3); nes_cpu_instruction_boundary(0xF4A2, 2); func_F4A2(); return;
}

void func_B3FF_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B3FF_b1");
#endif
label_B3FF:;
    /* $B3FF: A9 */ nes_cpu_instruction_boundary(0xB3FF, 2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_B401:;
    /* $B401: A0 */ nes_cpu_instruction_boundary(0xB401, 2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_B403:;
    /* $B403: A2 */ nes_cpu_instruction_boundary(0xB403, 2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B405:;
    /* $B405: 8D */ nes_cpu_instruction_boundary(0xB405, 4); nes_write(0x07BB, g_cpu.A);
label_B408:;
    /* $B408: A9 */ nes_cpu_instruction_boundary(0xB408, 2); g_cpu.A = 0x0C; FLAG_NZ(g_cpu.A);
label_B40A:; /* CSetFDir */
    /* $B40A: 20 */ nes_cpu_instruction_boundary(0xB40A, 6); func_F388();
label_B40D:;
    /* $B40D: AD */ nes_cpu_instruction_boundary(0xB40D, 4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B410:;
    /* $B410: C9 */ nes_cpu_instruction_boundary(0xB410, 2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B412:;
    /* $B412: D0 */ nes_cpu_instruction_boundary(0xB412, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B419; }
label_B414:;
    /* $B414: A9 */ nes_cpu_instruction_boundary(0xB414, 2); g_cpu.A = 0xBB; FLAG_NZ(g_cpu.A);
label_B416:;
    /* $B416: 8D */ nes_cpu_instruction_boundary(0xB416, 4); nes_write(0x4001, g_cpu.A);
label_B419:;
    /* $B419: D0 */ nes_cpu_instruction_boundary(0xB419, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B41B:;
    /* $B41B: A4 */ nes_cpu_instruction_boundary(0xB41B, 3); g_cpu.Y = nes_read(0xFF); FLAG_NZ(g_cpu.Y);
label_B41D:;
    /* $B41D: F0 */ nes_cpu_instruction_boundary(0xB41D, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B43F; }
label_B41F:; /* ExitCSub */
    /* $B41F: 84 */ nes_cpu_instruction_boundary(0xB41F, 3); nes_write(0xF1, g_cpu.Y);
label_B421:;
    /* $B421: 30 */ nes_cpu_instruction_boundary(0xB421, 2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xB3CD); return; }
label_B423:;
    /* $B423: 46 */ nes_cpu_instruction_boundary(0xB423, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B425:;
    /* $B425: B0 */ nes_cpu_instruction_boundary(0xB425, 2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3D1); return; }
label_B427:;
    /* $B427: 46 */ nes_cpu_instruction_boundary(0xB427, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B429:;
    /* $B429: B0 */ nes_cpu_instruction_boundary(0xB429, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB3FF, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3FF;
    }
label_B42B:; /* FallMForceData */
    /* $B42B: 46 */ nes_cpu_instruction_boundary(0xB42B, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B42D:;
    /* $B42D: B0 */ nes_cpu_instruction_boundary(0xB42D, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B45B; }
label_B42F:;
    /* $B42F: 46 */ nes_cpu_instruction_boundary(0xB42F, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B431:;
    /* $B431: B0 */ nes_cpu_instruction_boundary(0xB431, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B47D; }
label_B433:;
    /* $B433: 46 */ nes_cpu_instruction_boundary(0xB433, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B435:;
    /* $B435: B0 */ nes_cpu_instruction_boundary(0xB435, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4B6; }
label_B437:;
    /* $B437: 46 */ nes_cpu_instruction_boundary(0xB437, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B439:; /* InitMForceData */
    /* $B439: B0 */ nes_cpu_instruction_boundary(0xB439, 2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3F9); return; }
label_B43B:;
    /* $B43B: 46 */ nes_cpu_instruction_boundary(0xB43B, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B43D:;
    /* $B43D: B0 */ nes_cpu_instruction_boundary(0xB43D, 2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3BF); return; }
label_B43F:;
    /* $B43F: A5 */ nes_cpu_instruction_boundary(0xB43F, 3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_B441:;
    /* $B441: F0 */ nes_cpu_instruction_boundary(0xB441, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B45A; }
label_B443:; /* MaxRightXSpdData */
    /* $B443: 30 */ nes_cpu_instruction_boundary(0xB443, 2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xB3DF); return; }
label_B445:;
    /* $B445: 4A */ nes_cpu_instruction_boundary(0xB445, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B446:;
    /* $B446: B0 */ nes_cpu_instruction_boundary(0xB446, 2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3DF); return; }
label_B448:;
    /* $B448: 4A */ nes_cpu_instruction_boundary(0xB448, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B449:;
    /* $B449: B0 */ nes_cpu_instruction_boundary(0xB449, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB40D, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B44B:;
    /* $B44B: 4A */ nes_cpu_instruction_boundary(0xB44B, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44C:;
    /* $B44C: B0 */ nes_cpu_instruction_boundary(0xB44C, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B469; }
label_B44E:;
    /* $B44E: 4A */ nes_cpu_instruction_boundary(0xB44E, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44F:;
    /* $B44F: B0 */ nes_cpu_instruction_boundary(0xB44F, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B48D; }
label_B451:;
    /* $B451: 4A */ nes_cpu_instruction_boundary(0xB451, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B452:;
    /* $B452: B0 */ nes_cpu_instruction_boundary(0xB452, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4BB; }
label_B454:;
    /* $B454: 4A */ nes_cpu_instruction_boundary(0xB454, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B455:;
    /* $B455: B0 */ nes_cpu_instruction_boundary(0xB455, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB40D, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B457:;
    /* $B457: 4A */ nes_cpu_instruction_boundary(0xB457, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B458:;
    /* $B458: B0 */ nes_cpu_instruction_boundary(0xB458, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B45A:;
    /* $B45A: 60 */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return; /* branch-target RTS */
label_B45B:;
    /* $B45B: A9 */ nes_cpu_instruction_boundary(0xB45B, 2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B45D:;
    /* $B45D: 8D */ nes_cpu_instruction_boundary(0xB45D, 4); nes_write(0x07BB, g_cpu.A);
label_B460:;
    /* $B460: A0 */ nes_cpu_instruction_boundary(0xB460, 2); g_cpu.Y = 0x9C; FLAG_NZ(g_cpu.Y);
label_B462:;
    /* $B462: A2 */ nes_cpu_instruction_boundary(0xB462, 2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B464:;
    /* $B464: A9 */ nes_cpu_instruction_boundary(0xB464, 2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B466:;
    /* $B466: 20 */ nes_cpu_instruction_boundary(0xB466, 6); func_F388();
label_B469:;
    /* $B469: AC */ nes_cpu_instruction_boundary(0xB469, 4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B46C:;
    /* $B46C: B9 */ nes_cpu_instruction_boundary(0xB46C, 4); g_cpu.A = nes_read((0xF3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B46F:;
    /* $B46F: 8D */ nes_cpu_instruction_boundary(0xB46F, 4); nes_write(0x4000, g_cpu.A);
label_B472:;
    /* $B472: C0 */ nes_cpu_instruction_boundary(0xB472, 2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B474:;
    /* $B474: D0 */ nes_cpu_instruction_boundary(0xB474, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B476:;
    /* $B476: A9 */ nes_cpu_instruction_boundary(0xB476, 2); g_cpu.A = 0x9E; FLAG_NZ(g_cpu.A);
label_B478:;
    /* $B478: 8D */ nes_cpu_instruction_boundary(0xB478, 4); nes_write(0x4002, g_cpu.A);
label_B47B:;
    /* $B47B: D0 */ nes_cpu_instruction_boundary(0xB47B, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B47D:;
    /* $B47D: A9 */ nes_cpu_instruction_boundary(0xB47D, 2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B47F:;
    /* $B47F: A0 */ nes_cpu_instruction_boundary(0xB47F, 2); g_cpu.Y = 0xCB; FLAG_NZ(g_cpu.Y);
label_B481:;
    /* $B481: A2 */ nes_cpu_instruction_boundary(0xB481, 2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_B483:;
    /* $B483: 8D */ nes_cpu_instruction_boundary(0xB483, 4); nes_write(0x07BB, g_cpu.A);
label_B486:;
    /* $B486: A9 */ nes_cpu_instruction_boundary(0xB486, 2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B488:; /* NoJump */
    /* $B488: 20 */ nes_cpu_instruction_boundary(0xB488, 6); func_F388();
label_B48B:; /* ProcJumping */
    /* $B48B: D0 */ nes_cpu_instruction_boundary(0xB48B, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B48D:;
    /* $B48D: AC */ nes_cpu_instruction_boundary(0xB48D, 4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B490:;
    /* $B490: C0 */ nes_cpu_instruction_boundary(0xB490, 2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_B492:;
    /* $B492: D0 */ nes_cpu_instruction_boundary(0xB492, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49D; }
label_B494:;
    /* $B494: A9 */ nes_cpu_instruction_boundary(0xB494, 2); g_cpu.A = 0xA0; FLAG_NZ(g_cpu.A);
label_B496:;
    /* $B496: 8D */ nes_cpu_instruction_boundary(0xB496, 4); nes_write(0x4002, g_cpu.A);
label_B499:;
    /* $B499: A9 */ nes_cpu_instruction_boundary(0xB499, 2); g_cpu.A = 0x9F; FLAG_NZ(g_cpu.A);
label_B49B:;
    /* $B49B: D0 */ nes_cpu_instruction_boundary(0xB49B, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49F; }
label_B49D:;
    /* $B49D: A9 */ nes_cpu_instruction_boundary(0xB49D, 2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_B49F:;
    /* $B49F: 8D */ nes_cpu_instruction_boundary(0xB49F, 4); nes_write(0x4000, g_cpu.A);
label_B4A2:;
    /* $B4A2: CE */ nes_cpu_instruction_boundary(0xB4A2, 6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B4A5:;
    /* $B4A5: D0 */ nes_cpu_instruction_boundary(0xB4A5, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4B5; }
label_B4A7:;
    /* $B4A7: A2 */ nes_cpu_instruction_boundary(0xB4A7, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B4A9:;
    /* $B4A9: 86 */ nes_cpu_instruction_boundary(0xB4A9, 3); nes_write(0xF1, g_cpu.X);
label_B4AB:;
    /* $B4AB: A2 */ nes_cpu_instruction_boundary(0xB4AB, 2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_B4AD:;
    /* $B4AD: 8E */ nes_cpu_instruction_boundary(0xB4AD, 4); nes_write(0x4015, g_cpu.X);
label_B4B0:;
    /* $B4B0: A2 */ nes_cpu_instruction_boundary(0xB4B0, 2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B4B2:;
    /* $B4B2: 8E */ nes_cpu_instruction_boundary(0xB4B2, 4); nes_write(0x4015, g_cpu.X);
label_B4B5:;
    /* $B4B5: 60 */ nes_cpu_instruction_boundary(0xB4B5, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_B4B6:;
    /* $B4B6: A9 */ nes_cpu_instruction_boundary(0xB4B6, 2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_B4B8:;
    /* $B4B8: 8D */ nes_cpu_instruction_boundary(0xB4B8, 4); nes_write(0x07BB, g_cpu.A);
label_B4BB:;
    /* $B4BB: AD */ nes_cpu_instruction_boundary(0xB4BB, 4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B4BE:;
    /* $B4BE: 4A */ nes_cpu_instruction_boundary(0xB4BE, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4BF:;
    /* $B4BF: B0 */ nes_cpu_instruction_boundary(0xB4BF, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C1:;
    /* $B4C1: 4A */ nes_cpu_instruction_boundary(0xB4C1, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4C2:;
    /* $B4C2: B0 */ nes_cpu_instruction_boundary(0xB4C2, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C4:;
    /* $B4C4: 29 */ nes_cpu_instruction_boundary(0xB4C4, 2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_B4C6:;
    /* $B4C6: F0 */ nes_cpu_instruction_boundary(0xB4C6, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C8:;
    /* $B4C8: A0 */ nes_cpu_instruction_boundary(0xB4C8, 2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_B4CA:;
    /* $B4CA: A2 */ nes_cpu_instruction_boundary(0xB4CA, 2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_B4CC:;
    /* $B4CC: A9 */ nes_cpu_instruction_boundary(0xB4CC, 2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_B4CE:;
    /* $B4CE: 20 */ nes_cpu_instruction_boundary(0xB4CE, 6); func_F388();
label_B4D1:;
    /* $B4D1: 4C */ nes_cpu_instruction_boundary(0xB4D1, 3); nes_cpu_instruction_boundary(0xF4A2, 2); func_F4A2(); return;
}

void func_B3F9_b1(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B3F9_b1");
#endif
label_B3F9:;
    /* $B3F9: A9 */ nes_cpu_instruction_boundary(0xB3F9, 2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_B3FB:;
    /* $B3FB: A0 */ nes_cpu_instruction_boundary(0xB3FB, 2); g_cpu.Y = 0x99; FLAG_NZ(g_cpu.Y);
label_B3FD:;
    /* $B3FD: D0 */ nes_cpu_instruction_boundary(0xB3FD, 2); if (!g_cpu.Z) { maybe_trigger_vblank(2); goto label_B403; }
label_B3FF:;
    /* $B3FF: A9 */ nes_cpu_instruction_boundary(0xB3FF, 2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_B401:;
    /* $B401: A0 */ nes_cpu_instruction_boundary(0xB401, 2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_B403:;
    /* $B403: A2 */ nes_cpu_instruction_boundary(0xB403, 2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B405:;
    /* $B405: 8D */ nes_cpu_instruction_boundary(0xB405, 4); nes_write(0x07BB, g_cpu.A);
label_B408:;
    /* $B408: A9 */ nes_cpu_instruction_boundary(0xB408, 2); g_cpu.A = 0x0C; FLAG_NZ(g_cpu.A);
label_B40A:; /* CSetFDir */
    /* $B40A: 20 */ nes_cpu_instruction_boundary(0xB40A, 6); func_F388();
label_B40D:;
    /* $B40D: AD */ nes_cpu_instruction_boundary(0xB40D, 4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B410:;
    /* $B410: C9 */ nes_cpu_instruction_boundary(0xB410, 2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B412:;
    /* $B412: D0 */ nes_cpu_instruction_boundary(0xB412, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B419; }
label_B414:;
    /* $B414: A9 */ nes_cpu_instruction_boundary(0xB414, 2); g_cpu.A = 0xBB; FLAG_NZ(g_cpu.A);
label_B416:;
    /* $B416: 8D */ nes_cpu_instruction_boundary(0xB416, 4); nes_write(0x4001, g_cpu.A);
label_B419:;
    /* $B419: D0 */ nes_cpu_instruction_boundary(0xB419, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B41B:;
    /* $B41B: A4 */ nes_cpu_instruction_boundary(0xB41B, 3); g_cpu.Y = nes_read(0xFF); FLAG_NZ(g_cpu.Y);
label_B41D:;
    /* $B41D: F0 */ nes_cpu_instruction_boundary(0xB41D, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B43F; }
label_B41F:; /* ExitCSub */
    /* $B41F: 84 */ nes_cpu_instruction_boundary(0xB41F, 3); nes_write(0xF1, g_cpu.Y);
label_B421:;
    /* $B421: 30 */ nes_cpu_instruction_boundary(0xB421, 2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xB3CD); return; }
label_B423:;
    /* $B423: 46 */ nes_cpu_instruction_boundary(0xB423, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B425:;
    /* $B425: B0 */ nes_cpu_instruction_boundary(0xB425, 2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3D1); return; }
label_B427:;
    /* $B427: 46 */ nes_cpu_instruction_boundary(0xB427, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B429:;
    /* $B429: B0 */ nes_cpu_instruction_boundary(0xB429, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB3FF, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3FF;
    }
label_B42B:; /* FallMForceData */
    /* $B42B: 46 */ nes_cpu_instruction_boundary(0xB42B, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B42D:;
    /* $B42D: B0 */ nes_cpu_instruction_boundary(0xB42D, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B45B; }
label_B42F:;
    /* $B42F: 46 */ nes_cpu_instruction_boundary(0xB42F, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B431:;
    /* $B431: B0 */ nes_cpu_instruction_boundary(0xB431, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B47D; }
label_B433:;
    /* $B433: 46 */ nes_cpu_instruction_boundary(0xB433, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B435:;
    /* $B435: B0 */ nes_cpu_instruction_boundary(0xB435, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4B6; }
label_B437:;
    /* $B437: 46 */ nes_cpu_instruction_boundary(0xB437, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B439:; /* InitMForceData */
    /* $B439: B0 */ nes_cpu_instruction_boundary(0xB439, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB3F9, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3F9;
    }
label_B43B:;
    /* $B43B: 46 */ nes_cpu_instruction_boundary(0xB43B, 5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B43D:;
    /* $B43D: B0 */ nes_cpu_instruction_boundary(0xB43D, 2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3BF); return; }
label_B43F:;
    /* $B43F: A5 */ nes_cpu_instruction_boundary(0xB43F, 3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_B441:;
    /* $B441: F0 */ nes_cpu_instruction_boundary(0xB441, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B45A; }
label_B443:; /* MaxRightXSpdData */
    /* $B443: 30 */ nes_cpu_instruction_boundary(0xB443, 2); if (g_cpu.N) { maybe_trigger_vblank(2); call_by_address(0xB3DF); return; }
label_B445:;
    /* $B445: 4A */ nes_cpu_instruction_boundary(0xB445, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B446:;
    /* $B446: B0 */ nes_cpu_instruction_boundary(0xB446, 2); if (g_cpu.C) { maybe_trigger_vblank(2); call_by_address(0xB3DF); return; }
label_B448:;
    /* $B448: 4A */ nes_cpu_instruction_boundary(0xB448, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B449:;
    /* $B449: B0 */ nes_cpu_instruction_boundary(0xB449, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB40D, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B44B:;
    /* $B44B: 4A */ nes_cpu_instruction_boundary(0xB44B, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44C:;
    /* $B44C: B0 */ nes_cpu_instruction_boundary(0xB44C, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B469; }
label_B44E:;
    /* $B44E: 4A */ nes_cpu_instruction_boundary(0xB44E, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44F:;
    /* $B44F: B0 */ nes_cpu_instruction_boundary(0xB44F, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B48D; }
label_B451:;
    /* $B451: 4A */ nes_cpu_instruction_boundary(0xB451, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B452:;
    /* $B452: B0 */ nes_cpu_instruction_boundary(0xB452, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4BB; }
label_B454:;
    /* $B454: 4A */ nes_cpu_instruction_boundary(0xB454, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B455:;
    /* $B455: B0 */ nes_cpu_instruction_boundary(0xB455, 2); if (g_cpu.C) {
    nes_cpu_instruction_boundary(0xB40D, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B457:;
    /* $B457: 4A */ nes_cpu_instruction_boundary(0xB457, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B458:;
    /* $B458: B0 */ nes_cpu_instruction_boundary(0xB458, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B45A:;
    /* $B45A: 60 */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return; /* branch-target RTS */
label_B45B:;
    /* $B45B: A9 */ nes_cpu_instruction_boundary(0xB45B, 2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B45D:;
    /* $B45D: 8D */ nes_cpu_instruction_boundary(0xB45D, 4); nes_write(0x07BB, g_cpu.A);
label_B460:;
    /* $B460: A0 */ nes_cpu_instruction_boundary(0xB460, 2); g_cpu.Y = 0x9C; FLAG_NZ(g_cpu.Y);
label_B462:;
    /* $B462: A2 */ nes_cpu_instruction_boundary(0xB462, 2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B464:;
    /* $B464: A9 */ nes_cpu_instruction_boundary(0xB464, 2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B466:;
    /* $B466: 20 */ nes_cpu_instruction_boundary(0xB466, 6); func_F388();
label_B469:;
    /* $B469: AC */ nes_cpu_instruction_boundary(0xB469, 4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B46C:;
    /* $B46C: B9 */ nes_cpu_instruction_boundary(0xB46C, 4); g_cpu.A = nes_read((0xF3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B46F:;
    /* $B46F: 8D */ nes_cpu_instruction_boundary(0xB46F, 4); nes_write(0x4000, g_cpu.A);
label_B472:;
    /* $B472: C0 */ nes_cpu_instruction_boundary(0xB472, 2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B474:;
    /* $B474: D0 */ nes_cpu_instruction_boundary(0xB474, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B47B; }
label_B476:;
    /* $B476: A9 */ nes_cpu_instruction_boundary(0xB476, 2); g_cpu.A = 0x9E; FLAG_NZ(g_cpu.A);
label_B478:;
    /* $B478: 8D */ nes_cpu_instruction_boundary(0xB478, 4); nes_write(0x4002, g_cpu.A);
label_B47B:;
    /* $B47B: D0 */ nes_cpu_instruction_boundary(0xB47B, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B47D:;
    /* $B47D: A9 */ nes_cpu_instruction_boundary(0xB47D, 2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B47F:;
    /* $B47F: A0 */ nes_cpu_instruction_boundary(0xB47F, 2); g_cpu.Y = 0xCB; FLAG_NZ(g_cpu.Y);
label_B481:;
    /* $B481: A2 */ nes_cpu_instruction_boundary(0xB481, 2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_B483:;
    /* $B483: 8D */ nes_cpu_instruction_boundary(0xB483, 4); nes_write(0x07BB, g_cpu.A);
label_B486:;
    /* $B486: A9 */ nes_cpu_instruction_boundary(0xB486, 2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B488:; /* NoJump */
    /* $B488: 20 */ nes_cpu_instruction_boundary(0xB488, 6); func_F388();
label_B48B:; /* ProcJumping */
    /* $B48B: D0 */ nes_cpu_instruction_boundary(0xB48B, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4A2; }
label_B48D:;
    /* $B48D: AC */ nes_cpu_instruction_boundary(0xB48D, 4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B490:;
    /* $B490: C0 */ nes_cpu_instruction_boundary(0xB490, 2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_B492:;
    /* $B492: D0 */ nes_cpu_instruction_boundary(0xB492, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49D; }
label_B494:;
    /* $B494: A9 */ nes_cpu_instruction_boundary(0xB494, 2); g_cpu.A = 0xA0; FLAG_NZ(g_cpu.A);
label_B496:;
    /* $B496: 8D */ nes_cpu_instruction_boundary(0xB496, 4); nes_write(0x4002, g_cpu.A);
label_B499:;
    /* $B499: A9 */ nes_cpu_instruction_boundary(0xB499, 2); g_cpu.A = 0x9F; FLAG_NZ(g_cpu.A);
label_B49B:;
    /* $B49B: D0 */ nes_cpu_instruction_boundary(0xB49B, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B49F; }
label_B49D:;
    /* $B49D: A9 */ nes_cpu_instruction_boundary(0xB49D, 2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_B49F:;
    /* $B49F: 8D */ nes_cpu_instruction_boundary(0xB49F, 4); nes_write(0x4000, g_cpu.A);
label_B4A2:;
    /* $B4A2: CE */ nes_cpu_instruction_boundary(0xB4A2, 6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B4A5:;
    /* $B4A5: D0 */ nes_cpu_instruction_boundary(0xB4A5, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4B5; }
label_B4A7:;
    /* $B4A7: A2 */ nes_cpu_instruction_boundary(0xB4A7, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B4A9:;
    /* $B4A9: 86 */ nes_cpu_instruction_boundary(0xB4A9, 3); nes_write(0xF1, g_cpu.X);
label_B4AB:;
    /* $B4AB: A2 */ nes_cpu_instruction_boundary(0xB4AB, 2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_B4AD:;
    /* $B4AD: 8E */ nes_cpu_instruction_boundary(0xB4AD, 4); nes_write(0x4015, g_cpu.X);
label_B4B0:;
    /* $B4B0: A2 */ nes_cpu_instruction_boundary(0xB4B0, 2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B4B2:;
    /* $B4B2: 8E */ nes_cpu_instruction_boundary(0xB4B2, 4); nes_write(0x4015, g_cpu.X);
label_B4B5:;
    /* $B4B5: 60 */ nes_cpu_instruction_boundary(0xB4B5, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_B4B6:;
    /* $B4B6: A9 */ nes_cpu_instruction_boundary(0xB4B6, 2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_B4B8:;
    /* $B4B8: 8D */ nes_cpu_instruction_boundary(0xB4B8, 4); nes_write(0x07BB, g_cpu.A);
label_B4BB:;
    /* $B4BB: AD */ nes_cpu_instruction_boundary(0xB4BB, 4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B4BE:;
    /* $B4BE: 4A */ nes_cpu_instruction_boundary(0xB4BE, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4BF:;
    /* $B4BF: B0 */ nes_cpu_instruction_boundary(0xB4BF, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C1:;
    /* $B4C1: 4A */ nes_cpu_instruction_boundary(0xB4C1, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4C2:;
    /* $B4C2: B0 */ nes_cpu_instruction_boundary(0xB4C2, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C4:;
    /* $B4C4: 29 */ nes_cpu_instruction_boundary(0xB4C4, 2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_B4C6:;
    /* $B4C6: F0 */ nes_cpu_instruction_boundary(0xB4C6, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_B4D1; }
label_B4C8:;
    /* $B4C8: A0 */ nes_cpu_instruction_boundary(0xB4C8, 2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_B4CA:;
    /* $B4CA: A2 */ nes_cpu_instruction_boundary(0xB4CA, 2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_B4CC:;
    /* $B4CC: A9 */ nes_cpu_instruction_boundary(0xB4CC, 2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_B4CE:;
    /* $B4CE: 20 */ nes_cpu_instruction_boundary(0xB4CE, 6); func_F388();
label_B4D1:;
    /* $B4D1: 4C */ nes_cpu_instruction_boundary(0xB4D1, 3); nes_cpu_instruction_boundary(0xF4A2, 2); func_F4A2(); return;
}

