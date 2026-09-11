/* super-mario-bros_full_bank00_part01.c — PRG bank 0 function bodies (sub-part 1).
 * STANDALONE translation unit — compiled independently (in
 * parallel with every other bank part/sub-part and the
 * umbrella super-mario-bros_full.c). Do not compile as part of another TU or
 * edit directly; the source of truth is the recompiler's
 * code_generator.c. Renamed to drop the _partNN suffix if
 * this bank turned out to fit in a single sub-part. */

#include "super-mario-bros_full_decls.h"

void func_970D_b0(void) { /* ScrollLockObject */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_970D_b0");
#endif
label_970D:; /* ScrollLockObject */
    /* $970D: AD */ nes_cpu_instruction_boundary(0x970D, 4); g_cpu.A = nes_read(0x0723); FLAG_NZ(g_cpu.A);
label_9710:;
    /* $9710: 49 */ nes_cpu_instruction_boundary(0x9710, 2); g_cpu.A ^= 0x01; FLAG_NZ(g_cpu.A);
label_9712:;
    /* $9712: 8D */ nes_cpu_instruction_boundary(0x9712, 4); nes_write(0x0723, g_cpu.A);
label_9715:;
    /* $9715: 60 */ nes_cpu_instruction_boundary(0x9715, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_972B_b0(void) { /* AreaFrenzy */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_972B_b0");
#endif
label_972B:; /* AreaFrenzy */
    /* $972B: A6 */ nes_cpu_instruction_boundary(0x972B, 3); g_cpu.X = nes_read(0x00); FLAG_NZ(g_cpu.X);
label_972D:;
    /* $972D: BD */ nes_cpu_instruction_boundary(0x972D, 4); g_cpu.A = nes_read((0x9720 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9730:;
    /* $9730: A0 */ nes_cpu_instruction_boundary(0x9730, 2); g_cpu.Y = 0x05; FLAG_NZ(g_cpu.Y);
label_9732:; /* FreCompLoop */
    /* $9732: 88 */ nes_cpu_instruction_boundary(0x9732, 2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9733:;
    /* $9733: 30 */ nes_cpu_instruction_boundary(0x9733, 2); if (g_cpu.N) { maybe_trigger_vblank(1); goto label_973C; }
label_9735:;
    /* $9735: D9 */ nes_cpu_instruction_boundary(0x9735, 4); { uint8_t m=nes_read((0x0016 + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_9738:;
    /* $9738: D0 */ nes_cpu_instruction_boundary(0x9738, 2); if (!g_cpu.Z) {
    nes_cpu_instruction_boundary(0x9732, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9732;
    }
label_973A:;
    /* $973A: A9 */ nes_cpu_instruction_boundary(0x973A, 2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_973C:; /* ExitAFrenzy */
    /* $973C: 8D */ nes_cpu_instruction_boundary(0x973C, 4); nes_write(0x06CD, g_cpu.A);
label_973F:;
    /* $973F: 60 */ nes_cpu_instruction_boundary(0x973F, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_9645_b0(void) { /* LoopCmdE */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9645_b0");
#endif
label_9645:; /* LoopCmdE */
    /* $9645: 60 */ nes_cpu_instruction_boundary(0x9645, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_96C5_b0(void) { /* AlterAreaAttributes */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_96C5_b0");
#endif
label_96C5:; /* AlterAreaAttributes */
    /* $96C5: BC */ nes_cpu_instruction_boundary(0x96C5, 4); g_cpu.Y = nes_read((0x072D + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_96C8:;
    /* $96C8: C8 */ nes_cpu_instruction_boundary(0x96C8, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_96C9:;
    /* $96C9: B1 */ nes_cpu_instruction_boundary(0x96C9, 5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_96CB:;
    /* $96CB: 48 */ nes_cpu_instruction_boundary(0x96CB, 3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_96CC:;
    /* $96CC: 29 */ nes_cpu_instruction_boundary(0x96CC, 2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_96CE:;
    /* $96CE: D0 */ nes_cpu_instruction_boundary(0x96CE, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_96E2; }
label_96D0:;
    /* $96D0: 68 */ nes_cpu_instruction_boundary(0x96D0, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_96D1:;
    /* $96D1: 48 */ nes_cpu_instruction_boundary(0x96D1, 3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_96D2:;
    /* $96D2: 29 */ nes_cpu_instruction_boundary(0x96D2, 2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_96D4:;
    /* $96D4: 8D */ nes_cpu_instruction_boundary(0x96D4, 4); nes_write(0x0727, g_cpu.A);
label_96D7:;
    /* $96D7: 68 */ nes_cpu_instruction_boundary(0x96D7, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_96D8:;
    /* $96D8: 29 */ nes_cpu_instruction_boundary(0x96D8, 2); g_cpu.A &= 0x30; FLAG_NZ(g_cpu.A);
label_96DA:;
    /* $96DA: 4A */ nes_cpu_instruction_boundary(0x96DA, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_96DB:;
    /* $96DB: 4A */ nes_cpu_instruction_boundary(0x96DB, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_96DC:;
    /* $96DC: 4A */ nes_cpu_instruction_boundary(0x96DC, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_96DD:;
    /* $96DD: 4A */ nes_cpu_instruction_boundary(0x96DD, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_96DE:;
    /* $96DE: 8D */ nes_cpu_instruction_boundary(0x96DE, 4); nes_write(0x0742, g_cpu.A);
label_96E1:;
    /* $96E1: 60 */ nes_cpu_instruction_boundary(0x96E1, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
label_96E2:; /* Alter2 */
    /* $96E2: 68 */ nes_cpu_instruction_boundary(0x96E2, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_96E3:;
    /* $96E3: 29 */ nes_cpu_instruction_boundary(0x96E3, 2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_96E5:;
    /* $96E5: C9 */ nes_cpu_instruction_boundary(0x96E5, 2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_96E7:;
    /* $96E7: 90 */ nes_cpu_instruction_boundary(0x96E7, 2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_96EE; }
label_96E9:;
    /* $96E9: 8D */ nes_cpu_instruction_boundary(0x96E9, 4); nes_write(0x0744, g_cpu.A);
label_96EC:;
    /* $96EC: A9 */ nes_cpu_instruction_boundary(0x96EC, 2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_96EE:; /* SetFore */
    /* $96EE: 8D */ nes_cpu_instruction_boundary(0x96EE, 4); nes_write(0x0741, g_cpu.A);
label_96F1:;
    /* $96F1: 60 */ nes_cpu_instruction_boundary(0x96F1, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_BFD1_b0(void) { /* RedPTroopaGrav */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BFD1_b0");
#endif
label_BFD1:; /* RedPTroopaGrav */
    /* $BFD1: 20 */ nes_cpu_instruction_boundary(0xBFD1, 6); func_BFD7_b0();
label_BFD4:;
    /* $BFD4: A6 */ nes_cpu_instruction_boundary(0xBFD4, 3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_BFD6:;
    /* $BFD6: 60 */ nes_cpu_instruction_boundary(0xBFD6, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_BF77_b0(void) { /* MoveRedPTroopa */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BF77_b0");
#endif
label_BF77:; /* MoveRedPTroopa */
    /* $BF77: E8 */ nes_cpu_instruction_boundary(0xBF77, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_BF78:;
    /* $BF78: A9 */ nes_cpu_instruction_boundary(0xBF78, 2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_BF7A:;
    /* $BF7A: 85 */ nes_cpu_instruction_boundary(0xBF7A, 3); nes_write(0x00, g_cpu.A);
label_BF7C:;
    /* $BF7C: A9 */ nes_cpu_instruction_boundary(0xBF7C, 2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_BF7E:;
    /* $BF7E: 85 */ nes_cpu_instruction_boundary(0xBF7E, 3); nes_write(0x01, g_cpu.A);
label_BF80:;
    /* $BF80: A9 */ nes_cpu_instruction_boundary(0xBF80, 2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_BF82:;
    /* $BF82: 85 */ nes_cpu_instruction_boundary(0xBF82, 3); nes_write(0x02, g_cpu.A);
label_BF84:;
    /* $BF84: 98 */ nes_cpu_instruction_boundary(0xBF84, 2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_BF85:;
    /* $BF85: 4C */ nes_cpu_instruction_boundary(0xBF85, 3); nes_cpu_instruction_boundary(0xBFD1, 2); func_BFD1_b0(); return;
}

void func_9939_b0(void) { /* GetPipeHeight */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9939_b0");
#endif
label_9939:; /* GetPipeHeight */
    /* $9939: A0 */ nes_cpu_instruction_boundary(0x9939, 2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_993B:;
    /* $993B: 20 */ nes_cpu_instruction_boundary(0x993B, 6); func_9BAF_b0();
label_993E:;
    /* $993E: 20 */ nes_cpu_instruction_boundary(0x993E, 6); func_9BBB_b0();
label_9941:;
    /* $9941: 98 */ nes_cpu_instruction_boundary(0x9941, 2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_9942:;
    /* $9942: 29 */ nes_cpu_instruction_boundary(0x9942, 2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_9944:;
    /* $9944: 85 */ nes_cpu_instruction_boundary(0x9944, 3); nes_write(0x06, g_cpu.A);
label_9946:;
    /* $9946: BC */ nes_cpu_instruction_boundary(0x9946, 4); g_cpu.Y = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_9949:;
    /* $9949: 60 */ nes_cpu_instruction_boundary(0x9949, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_994A_b0(void) { /* FindEmptyEnemySlot */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_994A_b0");
#endif
label_994A:; /* FindEmptyEnemySlot */
    /* $994A: A2 */ nes_cpu_instruction_boundary(0x994A, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_994C:; /* EmptyChkLoop */
    /* $994C: 18 */ nes_cpu_instruction_boundary(0x994C, 2); g_cpu.C = 0;
label_994D:;
    /* $994D: B5 */ nes_cpu_instruction_boundary(0x994D, 4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_994F:;
    /* $994F: F0 */ nes_cpu_instruction_boundary(0x994F, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9956; }
label_9951:;
    /* $9951: E8 */ nes_cpu_instruction_boundary(0x9951, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_9952:;
    /* $9952: E0 */ nes_cpu_instruction_boundary(0x9952, 2); { int r=g_cpu.X-0x05; g_cpu.C=(g_cpu.X>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_9954:;
    /* $9954: D0 */ nes_cpu_instruction_boundary(0x9954, 2); if (!g_cpu.Z) {
    nes_cpu_instruction_boundary(0x994C, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_994C;
    }
label_9956:; /* ExitEmptyChk */
    /* $9956: 60 */ nes_cpu_instruction_boundary(0x9956, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_9BCB_b0(void) { /* GetAreaObjXPosition */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9BCB_b0");
#endif
label_9BCB:; /* GetAreaObjXPosition */
    /* $9BCB: AD */ nes_cpu_instruction_boundary(0x9BCB, 4); g_cpu.A = nes_read(0x0726); FLAG_NZ(g_cpu.A);
label_9BCE:;
    /* $9BCE: 0A */ nes_cpu_instruction_boundary(0x9BCE, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BCF:;
    /* $9BCF: 0A */ nes_cpu_instruction_boundary(0x9BCF, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BD0:;
    /* $9BD0: 0A */ nes_cpu_instruction_boundary(0x9BD0, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BD1:;
    /* $9BD1: 0A */ nes_cpu_instruction_boundary(0x9BD1, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BD2:;
    /* $9BD2: 60 */ nes_cpu_instruction_boundary(0x9BD2, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_9BD3_b0(void) { /* GetAreaObjYPosition */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9BD3_b0");
#endif
label_9BD3:; /* GetAreaObjYPosition */
    /* $9BD3: A5 */ nes_cpu_instruction_boundary(0x9BD3, 3); g_cpu.A = nes_read(0x07); FLAG_NZ(g_cpu.A);
label_9BD5:;
    /* $9BD5: 0A */ nes_cpu_instruction_boundary(0x9BD5, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BD6:;
    /* $9BD6: 0A */ nes_cpu_instruction_boundary(0x9BD6, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BD7:;
    /* $9BD7: 0A */ nes_cpu_instruction_boundary(0x9BD7, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BD8:;
    /* $9BD8: 0A */ nes_cpu_instruction_boundary(0x9BD8, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BD9:;
    /* $9BD9: 18 */ nes_cpu_instruction_boundary(0x9BD9, 2); g_cpu.C = 0;
label_9BDA:;
    /* $9BDA: 69 */ nes_cpu_instruction_boundary(0x9BDA, 2); { uint16_t r = g_cpu.A + 0x20 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x20); g_cpu.A=r&0xFF; }
label_9BDC:;
    /* $9BDC: 60 */ nes_cpu_instruction_boundary(0x9BDC, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_9B7D_b0(void) { /* RenderUnderPart */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9B7D_b0");
#endif
label_9B7D:; /* RenderUnderPart */
    /* $9B7D: 8C */ nes_cpu_instruction_boundary(0x9B7D, 4); nes_write(0x0735, g_cpu.Y);
label_9B80:;
    /* $9B80: BC */ nes_cpu_instruction_boundary(0x9B80, 4); g_cpu.Y = nes_read((0x06A1 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_9B83:;
    /* $9B83: F0 */ nes_cpu_instruction_boundary(0x9B83, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9B9D; }
label_9B85:;
    /* $9B85: C0 */ nes_cpu_instruction_boundary(0x9B85, 2); { int r=g_cpu.Y-0x17; g_cpu.C=(g_cpu.Y>=0x17)?1:0; FLAG_NZ(r&0xFF); }
label_9B87:;
    /* $9B87: F0 */ nes_cpu_instruction_boundary(0x9B87, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9BA0; }
label_9B89:;
    /* $9B89: C0 */ nes_cpu_instruction_boundary(0x9B89, 2); { int r=g_cpu.Y-0x1A; g_cpu.C=(g_cpu.Y>=0x1A)?1:0; FLAG_NZ(r&0xFF); }
label_9B8B:;
    /* $9B8B: F0 */ nes_cpu_instruction_boundary(0x9B8B, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9BA0; }
label_9B8D:;
    /* $9B8D: C0 */ nes_cpu_instruction_boundary(0x9B8D, 2); { int r=g_cpu.Y-0xC0; g_cpu.C=(g_cpu.Y>=0xC0)?1:0; FLAG_NZ(r&0xFF); }
label_9B8F:;
    /* $9B8F: F0 */ nes_cpu_instruction_boundary(0x9B8F, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9B9D; }
label_9B91:;
    /* $9B91: C0 */ nes_cpu_instruction_boundary(0x9B91, 2); { int r=g_cpu.Y-0xC0; g_cpu.C=(g_cpu.Y>=0xC0)?1:0; FLAG_NZ(r&0xFF); }
label_9B93:;
    /* $9B93: B0 */ nes_cpu_instruction_boundary(0x9B93, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_9BA0; }
label_9B95:;
    /* $9B95: C0 */ nes_cpu_instruction_boundary(0x9B95, 2); { int r=g_cpu.Y-0x54; g_cpu.C=(g_cpu.Y>=0x54)?1:0; FLAG_NZ(r&0xFF); }
label_9B97:;
    /* $9B97: D0 */ nes_cpu_instruction_boundary(0x9B97, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_9B9D; }
label_9B99:;
    /* $9B99: C9 */ nes_cpu_instruction_boundary(0x9B99, 2); { int r=g_cpu.A-0x50; g_cpu.C=(g_cpu.A>=0x50)?1:0; FLAG_NZ(r&0xFF); }
label_9B9B:;
    /* $9B9B: F0 */ nes_cpu_instruction_boundary(0x9B9B, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9BA0; }
label_9B9D:; /* DrawThisRow */
    /* $9B9D: 9D */ nes_cpu_instruction_boundary(0x9B9D, 5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9BA0:; /* WaitOneRow */
    /* $9BA0: E8 */ nes_cpu_instruction_boundary(0x9BA0, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_9BA1:;
    /* $9BA1: E0 */ nes_cpu_instruction_boundary(0x9BA1, 2); { int r=g_cpu.X-0x0D; g_cpu.C=(g_cpu.X>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_9BA3:;
    /* $9BA3: B0 */ nes_cpu_instruction_boundary(0x9BA3, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_9BAB; }
label_9BA5:;
    /* $9BA5: AC */ nes_cpu_instruction_boundary(0x9BA5, 4); g_cpu.Y = nes_read(0x0735); FLAG_NZ(g_cpu.Y);
label_9BA8:;
    /* $9BA8: 88 */ nes_cpu_instruction_boundary(0x9BA8, 2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9BA9:;
    /* $9BA9: 10 */ nes_cpu_instruction_boundary(0x9BA9, 2); if (!g_cpu.N) {
    nes_cpu_instruction_boundary(0x9B7D, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9B7D;
    }
label_9BAB:; /* ExitUPartR */
    /* $9BAB: 60 */ nes_cpu_instruction_boundary(0x9BAB, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_974C_b0(void) { /* TreeLedge */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_974C_b0");
#endif
label_974C:; /* TreeLedge */
    /* $974C: 20 */ nes_cpu_instruction_boundary(0x974C, 6); func_9BBB_b0();
label_974F:;
    /* $974F: BD */ nes_cpu_instruction_boundary(0x974F, 4); g_cpu.A = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9752:;
    /* $9752: F0 */ nes_cpu_instruction_boundary(0x9752, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9773; }
label_9754:;
    /* $9754: 10 */ nes_cpu_instruction_boundary(0x9754, 2); if (!g_cpu.N) { maybe_trigger_vblank(1); goto label_9767; }
label_9756:;
    /* $9756: 98 */ nes_cpu_instruction_boundary(0x9756, 2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_9757:;
    /* $9757: 9D */ nes_cpu_instruction_boundary(0x9757, 5); nes_write((0x0730 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_975A:;
    /* $975A: AD */ nes_cpu_instruction_boundary(0x975A, 4); g_cpu.A = nes_read(0x0725); FLAG_NZ(g_cpu.A);
label_975D:;
    /* $975D: 0D */ nes_cpu_instruction_boundary(0x975D, 4); g_cpu.A |= nes_read(0x0726); FLAG_NZ(g_cpu.A);
label_9760:;
    /* $9760: F0 */ nes_cpu_instruction_boundary(0x9760, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9767; }
label_9762:;
    /* $9762: A9 */ nes_cpu_instruction_boundary(0x9762, 2); g_cpu.A = 0x16; FLAG_NZ(g_cpu.A);
label_9764:;
    /* $9764: 4C */ nes_cpu_instruction_boundary(0x9764, 3); nes_cpu_instruction_boundary(0x97B0, 2); func_97B0_b0(); return;
label_9767:; /* MidTreeL */
    /* $9767: A6 */ nes_cpu_instruction_boundary(0x9767, 3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_9769:;
    /* $9769: A9 */ nes_cpu_instruction_boundary(0x9769, 2); g_cpu.A = 0x17; FLAG_NZ(g_cpu.A);
label_976B:;
    /* $976B: 9D */ nes_cpu_instruction_boundary(0x976B, 5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_976E:;
    /* $976E: A9 */ nes_cpu_instruction_boundary(0x976E, 2); g_cpu.A = 0x4C; FLAG_NZ(g_cpu.A);
label_9770:;
    /* $9770: 4C */ nes_cpu_instruction_boundary(0x9770, 3); nes_cpu_instruction_boundary(0x97AA, 2); func_97AA_b0(); return;
label_9773:; /* EndTreeL */
    /* $9773: A9 */ nes_cpu_instruction_boundary(0x9773, 2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_9775:;
    /* $9775: 4C */ nes_cpu_instruction_boundary(0x9775, 3); nes_cpu_instruction_boundary(0x97B0, 2); func_97B0_b0(); return;
}

void func_9778_b0(void) { /* MushroomLedge */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9778_b0");
#endif
label_9778:; /* MushroomLedge */
    /* $9778: 20 */ nes_cpu_instruction_boundary(0x9778, 6); func_9BAC_b0();
label_977B:;
    /* $977B: 84 */ nes_cpu_instruction_boundary(0x977B, 3); nes_write(0x06, g_cpu.Y);
label_977D:;
    /* $977D: 90 */ nes_cpu_instruction_boundary(0x977D, 2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_978B; }
label_977F:;
    /* $977F: BD */ nes_cpu_instruction_boundary(0x977F, 4); g_cpu.A = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9782:;
    /* $9782: 4A */ nes_cpu_instruction_boundary(0x9782, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9783:;
    /* $9783: 9D */ nes_cpu_instruction_boundary(0x9783, 5); nes_write((0x0736 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9786:;
    /* $9786: A9 */ nes_cpu_instruction_boundary(0x9786, 2); g_cpu.A = 0x19; FLAG_NZ(g_cpu.A);
label_9788:;
    /* $9788: 4C */ nes_cpu_instruction_boundary(0x9788, 3); nes_cpu_instruction_boundary(0x97B0, 2); func_97B0_b0(); return;
label_978B:; /* EndMushL */
    /* $978B: A9 */ nes_cpu_instruction_boundary(0x978B, 2); g_cpu.A = 0x1B; FLAG_NZ(g_cpu.A);
label_978D:;
    /* $978D: BC */ nes_cpu_instruction_boundary(0x978D, 4); g_cpu.Y = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_9790:;
    /* $9790: F0 */ nes_cpu_instruction_boundary(0x9790, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_97B0; }
label_9792:;
    /* $9792: BD */ nes_cpu_instruction_boundary(0x9792, 4); g_cpu.A = nes_read((0x0736 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9795:;
    /* $9795: 85 */ nes_cpu_instruction_boundary(0x9795, 3); nes_write(0x06, g_cpu.A);
label_9797:;
    /* $9797: A6 */ nes_cpu_instruction_boundary(0x9797, 3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_9799:;
    /* $9799: A9 */ nes_cpu_instruction_boundary(0x9799, 2); g_cpu.A = 0x1A; FLAG_NZ(g_cpu.A);
label_979B:;
    /* $979B: 9D */ nes_cpu_instruction_boundary(0x979B, 5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_979E:;
    /* $979E: C4 */ nes_cpu_instruction_boundary(0x979E, 3); { uint8_t m=nes_read(0x06); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_97A0:;
    /* $97A0: D0 */ nes_cpu_instruction_boundary(0x97A0, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_97CE; }
label_97A2:;
    /* $97A2: E8 */ nes_cpu_instruction_boundary(0x97A2, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_97A3:;
    /* $97A3: A9 */ nes_cpu_instruction_boundary(0x97A3, 2); g_cpu.A = 0x4F; FLAG_NZ(g_cpu.A);
label_97A5:;
    /* $97A5: 9D */ nes_cpu_instruction_boundary(0x97A5, 5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_97A8:;
    /* $97A8: A9 */ nes_cpu_instruction_boundary(0x97A8, 2); g_cpu.A = 0x50; FLAG_NZ(g_cpu.A);
label_97AA:; /* AllUnder */
    /* $97AA: E8 */ nes_cpu_instruction_boundary(0x97AA, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_97AB:;
    /* $97AB: A0 */ nes_cpu_instruction_boundary(0x97AB, 2); g_cpu.Y = 0x0F; FLAG_NZ(g_cpu.Y);
label_97AD:;
    /* $97AD: 4C */ nes_cpu_instruction_boundary(0x97AD, 3); nes_cpu_instruction_boundary(0x9B7D, 2); func_9B7D_b0(); return;
label_97B0:; /* NoUnder */
    /* $97B0: A6 */ nes_cpu_instruction_boundary(0x97B0, 3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_97B2:;
    /* $97B2: A0 */ nes_cpu_instruction_boundary(0x97B2, 2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_97B4:;
    /* $97B4: 4C */ nes_cpu_instruction_boundary(0x97B4, 3); nes_cpu_instruction_boundary(0x9B7D, 2); func_9B7D_b0(); return;
label_97CE:; /* MushLExit */
    /* $97CE: 60 */ nes_cpu_instruction_boundary(0x97CE, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_9A69_b0(void) { /* BulletBillCannon */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9A69_b0");
#endif
label_9A69:; /* BulletBillCannon */
    /* $9A69: 20 */ nes_cpu_instruction_boundary(0x9A69, 6); func_9BBB_b0();
label_9A6C:;
    /* $9A6C: A6 */ nes_cpu_instruction_boundary(0x9A6C, 3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_9A6E:;
    /* $9A6E: A9 */ nes_cpu_instruction_boundary(0x9A6E, 2); g_cpu.A = 0x64; FLAG_NZ(g_cpu.A);
label_9A70:;
    /* $9A70: 9D */ nes_cpu_instruction_boundary(0x9A70, 5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9A73:;
    /* $9A73: E8 */ nes_cpu_instruction_boundary(0x9A73, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_9A74:;
    /* $9A74: 88 */ nes_cpu_instruction_boundary(0x9A74, 2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9A75:;
    /* $9A75: 30 */ nes_cpu_instruction_boundary(0x9A75, 2); if (g_cpu.N) { maybe_trigger_vblank(1); goto label_9A85; }
label_9A77:;
    /* $9A77: A9 */ nes_cpu_instruction_boundary(0x9A77, 2); g_cpu.A = 0x65; FLAG_NZ(g_cpu.A);
label_9A79:;
    /* $9A79: 9D */ nes_cpu_instruction_boundary(0x9A79, 5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9A7C:;
    /* $9A7C: E8 */ nes_cpu_instruction_boundary(0x9A7C, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_9A7D:;
    /* $9A7D: 88 */ nes_cpu_instruction_boundary(0x9A7D, 2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9A7E:;
    /* $9A7E: 30 */ nes_cpu_instruction_boundary(0x9A7E, 2); if (g_cpu.N) { maybe_trigger_vblank(1); goto label_9A85; }
label_9A80:;
    /* $9A80: A9 */ nes_cpu_instruction_boundary(0x9A80, 2); g_cpu.A = 0x66; FLAG_NZ(g_cpu.A);
label_9A82:;
    /* $9A82: 20 */ nes_cpu_instruction_boundary(0x9A82, 6); func_9B7D_b0();
label_9A85:; /* SetupCannon */
    /* $9A85: AE */ nes_cpu_instruction_boundary(0x9A85, 4); g_cpu.X = nes_read(0x046A); FLAG_NZ(g_cpu.X);
label_9A88:;
    /* $9A88: 20 */ nes_cpu_instruction_boundary(0x9A88, 6); func_9BD3_b0();
label_9A8B:;
    /* $9A8B: 9D */ nes_cpu_instruction_boundary(0x9A8B, 5); nes_write((0x0477 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9A8E:;
    /* $9A8E: AD */ nes_cpu_instruction_boundary(0x9A8E, 4); g_cpu.A = nes_read(0x0725); FLAG_NZ(g_cpu.A);
label_9A91:;
    /* $9A91: 9D */ nes_cpu_instruction_boundary(0x9A91, 5); nes_write((0x046B + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9A94:;
    /* $9A94: 20 */ nes_cpu_instruction_boundary(0x9A94, 6); func_9BCB_b0();
label_9A97:;
    /* $9A97: 9D */ nes_cpu_instruction_boundary(0x9A97, 5); nes_write((0x0471 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9A9A:;
    /* $9A9A: E8 */ nes_cpu_instruction_boundary(0x9A9A, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_9A9B:;
    /* $9A9B: E0 */ nes_cpu_instruction_boundary(0x9A9B, 2); { int r=g_cpu.X-0x06; g_cpu.C=(g_cpu.X>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_9A9D:;
    /* $9A9D: 90 */ nes_cpu_instruction_boundary(0x9A9D, 2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_9AA1; }
label_9A9F:;
    /* $9A9F: A2 */ nes_cpu_instruction_boundary(0x9A9F, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_9AA1:; /* StrCOffset */
    /* $9AA1: 8E */ nes_cpu_instruction_boundary(0x9AA1, 4); nes_write(0x046A, g_cpu.X);
label_9AA4:;
    /* $9AA4: 60 */ nes_cpu_instruction_boundary(0x9AA4, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_BB20_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BB20_b0");
#endif
label_BB20:;
    /* $BB20: 95 */ nes_cpu_instruction_boundary(0xBB20, 4); nes_write((0xDB + g_cpu.X) & 0xFF, g_cpu.A);
label_BB22:;
    /* $BB22: A9 */ nes_cpu_instruction_boundary(0xBB22, 2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_BB24:;
    /* $BB24: 95 */ nes_cpu_instruction_boundary(0xBB24, 4); nes_write((0xC2 + g_cpu.X) & 0xFF, g_cpu.A);
label_BB26:;
    /* $BB26: D0 */ nes_cpu_instruction_boundary(0xBB26, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_BB2B; }
label_BB28:; /* RunAllH */
    /* $BB28: 20 */ nes_cpu_instruction_boundary(0xBB28, 6); func_D7C4();
label_BB2B:; /* RunHSubs */
    /* $BB2B: 20 */ nes_cpu_instruction_boundary(0xBB2B, 6); func_F19B();
label_BB2E:;
    /* $BB2E: 20 */ nes_cpu_instruction_boundary(0xBB2E, 6); func_F148();
label_BB31:;
    /* $BB31: 20 */ nes_cpu_instruction_boundary(0xBB31, 6); func_E236();
label_BB34:;
    /* $BB34: 20 */ nes_cpu_instruction_boundary(0xBB34, 6); func_E4DC();
label_BB37:;
    /* $BB37: 60 */ nes_cpu_instruction_boundary(0xBB37, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_97B0_b0(void) { /* NoUnder */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_97B0_b0");
#endif
label_97B0:; /* NoUnder */
    /* $97B0: A6 */ nes_cpu_instruction_boundary(0x97B0, 3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_97B2:;
    /* $97B2: A0 */ nes_cpu_instruction_boundary(0x97B2, 2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_97B4:;
    /* $97B4: 4C */ nes_cpu_instruction_boundary(0x97B4, 3); nes_cpu_instruction_boundary(0x9B7D, 2); func_9B7D_b0(); return;
}

void func_97AA_b0(void) { /* AllUnder */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_97AA_b0");
#endif
label_97AA:; /* AllUnder */
    /* $97AA: E8 */ nes_cpu_instruction_boundary(0x97AA, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_97AB:;
    /* $97AB: A0 */ nes_cpu_instruction_boundary(0x97AB, 2); g_cpu.Y = 0x0F; FLAG_NZ(g_cpu.Y);
label_97AD:;
    /* $97AD: 4C */ nes_cpu_instruction_boundary(0x97AD, 3); nes_cpu_instruction_boundary(0x9B7D, 2); func_9B7D_b0(); return;
}

void func_9BAC_b0(void) { /* ChkLrgObjLength */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9BAC_b0");
#endif
label_9BAC:; /* ChkLrgObjLength */
    /* $9BAC: 20 */ nes_cpu_instruction_boundary(0x9BAC, 6); func_9BBB_b0();
label_9BAF:; /* ChkLrgObjFixedLength */
    /* $9BAF: BD */ nes_cpu_instruction_boundary(0x9BAF, 4); g_cpu.A = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9BB2:;
    /* $9BB2: 18 */ nes_cpu_instruction_boundary(0x9BB2, 2); g_cpu.C = 0;
label_9BB3:;
    /* $9BB3: 10 */ nes_cpu_instruction_boundary(0x9BB3, 2); if (!g_cpu.N) { maybe_trigger_vblank(1); goto label_9BBA; }
label_9BB5:;
    /* $9BB5: 98 */ nes_cpu_instruction_boundary(0x9BB5, 2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_9BB6:;
    /* $9BB6: 9D */ nes_cpu_instruction_boundary(0x9BB6, 5); nes_write((0x0730 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9BB9:;
    /* $9BB9: 38 */ nes_cpu_instruction_boundary(0x9BB9, 2); g_cpu.C = 1;
label_9BBA:; /* LenSet */
    /* $9BBA: 60 */ nes_cpu_instruction_boundary(0x9BBA, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_9BBB_b0(void) { /* GetLrgObjAttrib */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9BBB_b0");
#endif
label_9BBB:; /* GetLrgObjAttrib */
    /* $9BBB: BC */ nes_cpu_instruction_boundary(0x9BBB, 4); g_cpu.Y = nes_read((0x072D + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_9BBE:;
    /* $9BBE: B1 */ nes_cpu_instruction_boundary(0x9BBE, 5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9BC0:;
    /* $9BC0: 29 */ nes_cpu_instruction_boundary(0x9BC0, 2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_9BC2:;
    /* $9BC2: 85 */ nes_cpu_instruction_boundary(0x9BC2, 3); nes_write(0x07, g_cpu.A);
label_9BC4:;
    /* $9BC4: C8 */ nes_cpu_instruction_boundary(0x9BC4, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9BC5:;
    /* $9BC5: B1 */ nes_cpu_instruction_boundary(0x9BC5, 5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9BC7:;
    /* $9BC7: 29 */ nes_cpu_instruction_boundary(0x9BC7, 2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_9BC9:;
    /* $9BC9: A8 */ nes_cpu_instruction_boundary(0x9BC9, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9BCA:;
    /* $9BCA: 60 */ nes_cpu_instruction_boundary(0x9BCA, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_9BAF_b0(void) { /* ChkLrgObjFixedLength */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9BAF_b0");
#endif
label_9BAF:; /* ChkLrgObjFixedLength */
    /* $9BAF: BD */ nes_cpu_instruction_boundary(0x9BAF, 4); g_cpu.A = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9BB2:;
    /* $9BB2: 18 */ nes_cpu_instruction_boundary(0x9BB2, 2); g_cpu.C = 0;
label_9BB3:;
    /* $9BB3: 10 */ nes_cpu_instruction_boundary(0x9BB3, 2); if (!g_cpu.N) { maybe_trigger_vblank(1); goto label_9BBA; }
label_9BB5:;
    /* $9BB5: 98 */ nes_cpu_instruction_boundary(0x9BB5, 2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_9BB6:;
    /* $9BB6: 9D */ nes_cpu_instruction_boundary(0x9BB6, 5); nes_write((0x0730 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9BB9:;
    /* $9BB9: 38 */ nes_cpu_instruction_boundary(0x9BB9, 2); g_cpu.C = 1;
label_9BBA:; /* LenSet */
    /* $9BBA: 60 */ nes_cpu_instruction_boundary(0x9BBA, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_98B3_b0(void) { /* RenderSidewaysPipe */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_98B3_b0");
#endif
label_98B3:; /* RenderSidewaysPipe */
    /* $98B3: 88 */ nes_cpu_instruction_boundary(0x98B3, 2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_98B4:;
    /* $98B4: 88 */ nes_cpu_instruction_boundary(0x98B4, 2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_98B5:;
    /* $98B5: 84 */ nes_cpu_instruction_boundary(0x98B5, 3); nes_write(0x05, g_cpu.Y);
label_98B7:;
    /* $98B7: BC */ nes_cpu_instruction_boundary(0x98B7, 4); g_cpu.Y = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_98BA:;
    /* $98BA: 84 */ nes_cpu_instruction_boundary(0x98BA, 3); nes_write(0x06, g_cpu.Y);
label_98BC:;
    /* $98BC: A6 */ nes_cpu_instruction_boundary(0x98BC, 3); g_cpu.X = nes_read(0x05); FLAG_NZ(g_cpu.X);
label_98BE:;
    /* $98BE: E8 */ nes_cpu_instruction_boundary(0x98BE, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_98BF:;
    /* $98BF: B9 */ nes_cpu_instruction_boundary(0x98BF, 4); g_cpu.A = nes_read((0x989F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_98C2:;
    /* $98C2: C9 */ nes_cpu_instruction_boundary(0x98C2, 2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_98C4:;
    /* $98C4: F0 */ nes_cpu_instruction_boundary(0x98C4, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_98CE; }
label_98C6:;
    /* $98C6: A2 */ nes_cpu_instruction_boundary(0x98C6, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_98C8:;
    /* $98C8: A4 */ nes_cpu_instruction_boundary(0x98C8, 3); g_cpu.Y = nes_read(0x05); FLAG_NZ(g_cpu.Y);
label_98CA:;
    /* $98CA: 20 */ nes_cpu_instruction_boundary(0x98CA, 6); func_9B7D_b0();
label_98CD:;
    /* $98CD: 18 */ nes_cpu_instruction_boundary(0x98CD, 2); g_cpu.C = 0;
label_98CE:; /* DrawSidePart */
    /* $98CE: A4 */ nes_cpu_instruction_boundary(0x98CE, 3); g_cpu.Y = nes_read(0x06); FLAG_NZ(g_cpu.Y);
label_98D0:;
    /* $98D0: B9 */ nes_cpu_instruction_boundary(0x98D0, 4); g_cpu.A = nes_read((0x98A3 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_98D3:;
    /* $98D3: 9D */ nes_cpu_instruction_boundary(0x98D3, 5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_98D6:;
    /* $98D6: B9 */ nes_cpu_instruction_boundary(0x98D6, 4); g_cpu.A = nes_read((0x98A7 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_98D9:;
    /* $98D9: 9D */ nes_cpu_instruction_boundary(0x98D9, 5); nes_write((0x06A2 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_98DC:;
    /* $98DC: 60 */ nes_cpu_instruction_boundary(0x98DC, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_99E9_b0(void) { /* DrawRope */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_99E9_b0");
#endif
label_99E9:; /* DrawRope */
    /* $99E9: A9 */ nes_cpu_instruction_boundary(0x99E9, 2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_99EB:;
    /* $99EB: 4C */ nes_cpu_instruction_boundary(0x99EB, 3); nes_cpu_instruction_boundary(0x9B7D, 2); func_9B7D_b0(); return;
}

void func_9A44_b0(void) { /* GetRow */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9A44_b0");
#endif
label_9A44:; /* GetRow */
    /* $9A44: 48 */ nes_cpu_instruction_boundary(0x9A44, 3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9A45:;
    /* $9A45: 20 */ nes_cpu_instruction_boundary(0x9A45, 6); func_9BAC_b0();
label_9A48:; /* DrawRow */
    /* $9A48: A6 */ nes_cpu_instruction_boundary(0x9A48, 3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_9A4A:;
    /* $9A4A: A0 */ nes_cpu_instruction_boundary(0x9A4A, 2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_9A4C:;
    /* $9A4C: 68 */ nes_cpu_instruction_boundary(0x9A4C, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9A4D:;
    /* $9A4D: 4C */ nes_cpu_instruction_boundary(0x9A4D, 3); nes_cpu_instruction_boundary(0x9B7D, 2); func_9B7D_b0(); return;
}

void func_9A20_b0(void) { /* ColObj */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9A20_b0");
#endif
label_9A20:; /* ColObj */
    /* $9A20: A0 */ nes_cpu_instruction_boundary(0x9A20, 2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_9A22:;
    /* $9A22: 4C */ nes_cpu_instruction_boundary(0x9A22, 3); nes_cpu_instruction_boundary(0x9B7D, 2); func_9B7D_b0(); return;
}

void func_9A5F_b0(void) { /* GetRow2 */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9A5F_b0");
#endif
label_9A5F:; /* GetRow2 */
    /* $9A5F: 48 */ nes_cpu_instruction_boundary(0x9A5F, 3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9A60:;
    /* $9A60: 20 */ nes_cpu_instruction_boundary(0x9A60, 6); func_9BBB_b0();
label_9A63:;
    /* $9A63: 68 */ nes_cpu_instruction_boundary(0x9A63, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9A64:;
    /* $9A64: A6 */ nes_cpu_instruction_boundary(0x9A64, 3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_9A66:;
    /* $9A66: 4C */ nes_cpu_instruction_boundary(0x9A66, 3); nes_cpu_instruction_boundary(0x9B7D, 2); func_9B7D_b0(); return;
}

void func_9B36_b0(void) { /* GetAreaObjectID */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9B36_b0");
#endif
label_9B36:; /* GetAreaObjectID */
    /* $9B36: A5 */ nes_cpu_instruction_boundary(0x9B36, 3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_9B38:;
    /* $9B38: 38 */ nes_cpu_instruction_boundary(0x9B38, 2); g_cpu.C = 1;
label_9B39:;
    /* $9B39: E9 */ nes_cpu_instruction_boundary(0x9B39, 2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9B3B:;
    /* $9B3B: A8 */ nes_cpu_instruction_boundary(0x9B3B, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9B3C:; /* ExitDecBlock */
    /* $9B3C: 60 */ nes_cpu_instruction_boundary(0x9B3C, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_9B2C_b0(void) { /* DrawQBlk */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9B2C_b0");
#endif
label_9B2C:; /* DrawQBlk */
    /* $9B2C: B9 */ nes_cpu_instruction_boundary(0x9B2C, 4); g_cpu.A = nes_read((0xBDE8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9B2F:;
    /* $9B2F: 48 */ nes_cpu_instruction_boundary(0x9B2F, 3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9B30:;
    /* $9B30: 20 */ nes_cpu_instruction_boundary(0x9B30, 6); func_9BBB_b0();
label_9B33:;
    /* $9B33: 4C */ nes_cpu_instruction_boundary(0x9B33, 3); nes_cpu_instruction_boundary(0x9A48, 2); func_9A48_b0(); return;
}

void func_9A48_b0(void) { /* DrawRow */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9A48_b0");
#endif
label_9A48:; /* DrawRow */
    /* $9A48: A6 */ nes_cpu_instruction_boundary(0x9A48, 3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_9A4A:;
    /* $9A4A: A0 */ nes_cpu_instruction_boundary(0x9A4A, 2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_9A4C:;
    /* $9A4C: 68 */ nes_cpu_instruction_boundary(0x9A4C, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9A4D:;
    /* $9A4D: 4C */ nes_cpu_instruction_boundary(0x9A4D, 3); nes_cpu_instruction_boundary(0x9B7D, 2); func_9B7D_b0(); return;
}

void func_8E04_b0(void) { /* JumpEngine */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_8E04_b0");
#endif
label_8E04:; /* JumpEngine */
    /* $8E04: 0A */ nes_cpu_instruction_boundary(0x8E04, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8E05:;
    /* $8E05: A8 */ nes_cpu_instruction_boundary(0x8E05, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_8E06:;
    /* $8E06: 68 */ nes_cpu_instruction_boundary(0x8E06, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_8E07:;
    /* $8E07: 85 */ nes_cpu_instruction_boundary(0x8E07, 3); nes_write(0x04, g_cpu.A);
label_8E09:;
    /* $8E09: 68 */ nes_cpu_instruction_boundary(0x8E09, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_8E0A:;
    /* $8E0A: 85 */ nes_cpu_instruction_boundary(0x8E0A, 3); nes_write(0x05, g_cpu.A);
label_8E0C:;
    /* $8E0C: C8 */ nes_cpu_instruction_boundary(0x8E0C, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8E0D:;
    /* $8E0D: B1 */ nes_cpu_instruction_boundary(0x8E0D, 5); g_cpu.A = nes_read((nes_read16zp(0x04) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8E0F:;
    /* $8E0F: 85 */ nes_cpu_instruction_boundary(0x8E0F, 3); nes_write(0x06, g_cpu.A);
label_8E11:;
    /* $8E11: C8 */ nes_cpu_instruction_boundary(0x8E11, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8E12:;
    /* $8E12: B1 */ nes_cpu_instruction_boundary(0x8E12, 5); g_cpu.A = nes_read((nes_read16zp(0x04) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8E14:;
    /* $8E14: 85 */ nes_cpu_instruction_boundary(0x8E14, 3); nes_write(0x07, g_cpu.A);
label_8E16:;
    /* $8E16: 6C */ nes_cpu_instruction_boundary(0x8E16, 5); { uint16_t _jt = nes_read16zp(0x06); nes_cpu_instruction_boundary(_jt, 2); call_by_address_tail(_jt, -1); return; }
}

void func_9402_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9402_b0");
#endif
label_9402:;
    /* $9402: 08 */ nes_cpu_instruction_boundary(0x9402, 3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_9403:;
    /* $9403: 95 */ nes_cpu_instruction_boundary(0x9403, 4); nes_write((0xA2 + g_cpu.X) & 0xFF, g_cpu.A);
label_9405:;
    /* $9405: 0C */ nes_cpu_instruction_boundary(0x9405, 4); (void)nes_read(0x00A9); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_9408:; /* ClrMTBuf */
    /* $9408: 9D */ nes_cpu_instruction_boundary(0x9408, 5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_940B:;
    /* $940B: CA */ nes_cpu_instruction_boundary(0x940B, 2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_940C:;
    /* $940C: 10 */ nes_cpu_instruction_boundary(0x940C, 2); if (!g_cpu.N) {
    nes_cpu_instruction_boundary(0x9408, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9408;
    }
label_940E:;
    /* $940E: AC */ nes_cpu_instruction_boundary(0x940E, 4); g_cpu.Y = nes_read(0x0742); FLAG_NZ(g_cpu.Y);
label_9411:;
    /* $9411: F0 */ nes_cpu_instruction_boundary(0x9411, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9455; }
label_9413:;
    /* $9413: AD */ nes_cpu_instruction_boundary(0x9413, 4); g_cpu.A = nes_read(0x0725); FLAG_NZ(g_cpu.A);
label_9416:; /* ThirdP */
    /* $9416: C9 */ nes_cpu_instruction_boundary(0x9416, 2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_9418:;
    /* $9418: 30 */ nes_cpu_instruction_boundary(0x9418, 2); if (g_cpu.N) { maybe_trigger_vblank(1); goto label_941F; }
label_941A:;
    /* $941A: 38 */ nes_cpu_instruction_boundary(0x941A, 2); g_cpu.C = 1;
label_941B:;
    /* $941B: E9 */ nes_cpu_instruction_boundary(0x941B, 2); { uint8_t m=0x03; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_941D:;
    /* $941D: 10 */ nes_cpu_instruction_boundary(0x941D, 2); if (!g_cpu.N) {
    nes_cpu_instruction_boundary(0x9416, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9416;
    }
label_941F:; /* RendBack */
    /* $941F: 0A */ nes_cpu_instruction_boundary(0x941F, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9420:;
    /* $9420: 0A */ nes_cpu_instruction_boundary(0x9420, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9421:;
    /* $9421: 0A */ nes_cpu_instruction_boundary(0x9421, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9422:;
    /* $9422: 0A */ nes_cpu_instruction_boundary(0x9422, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9423:;
    /* $9423: 79 */ nes_cpu_instruction_boundary(0x9423, 4); { uint8_t m=nes_read((0x92F6 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9426:;
    /* $9426: 6D */ nes_cpu_instruction_boundary(0x9426, 4); { uint8_t m=nes_read(0x0726); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9429:;
    /* $9429: AA */ nes_cpu_instruction_boundary(0x9429, 2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_942A:;
    /* $942A: BD */ nes_cpu_instruction_boundary(0x942A, 4); g_cpu.A = nes_read((0x92FA + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_942D:;
    /* $942D: F0 */ nes_cpu_instruction_boundary(0x942D, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9455; }
label_942F:;
    /* $942F: 48 */ nes_cpu_instruction_boundary(0x942F, 3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9430:;
    /* $9430: 29 */ nes_cpu_instruction_boundary(0x9430, 2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_9432:;
    /* $9432: 38 */ nes_cpu_instruction_boundary(0x9432, 2); g_cpu.C = 1;
label_9433:;
    /* $9433: E9 */ nes_cpu_instruction_boundary(0x9433, 2); { uint8_t m=0x01; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9435:;
    /* $9435: 85 */ nes_cpu_instruction_boundary(0x9435, 3); nes_write(0x00, g_cpu.A);
label_9437:;
    /* $9437: 0A */ nes_cpu_instruction_boundary(0x9437, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9438:;
    /* $9438: 65 */ nes_cpu_instruction_boundary(0x9438, 3); { uint8_t m=nes_read(0x00); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_943A:;
    /* $943A: AA */ nes_cpu_instruction_boundary(0x943A, 2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_943B:;
    /* $943B: 68 */ nes_cpu_instruction_boundary(0x943B, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_943C:;
    /* $943C: 4A */ nes_cpu_instruction_boundary(0x943C, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_943D:;
    /* $943D: 4A */ nes_cpu_instruction_boundary(0x943D, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_943E:;
    /* $943E: 4A */ nes_cpu_instruction_boundary(0x943E, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_943F:;
    /* $943F: 4A */ nes_cpu_instruction_boundary(0x943F, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9440:;
    /* $9440: A8 */ nes_cpu_instruction_boundary(0x9440, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9441:;
    /* $9441: A9 */ nes_cpu_instruction_boundary(0x9441, 2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_9443:;
    /* $9443: 85 */ nes_cpu_instruction_boundary(0x9443, 3); nes_write(0x00, g_cpu.A);
label_9445:; /* SceLoop1 */
    /* $9445: BD */ nes_cpu_instruction_boundary(0x9445, 4); g_cpu.A = nes_read((0x938A + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9448:;
    /* $9448: 99 */ nes_cpu_instruction_boundary(0x9448, 5); nes_write((0x06A1 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_944B:;
    /* $944B: E8 */ nes_cpu_instruction_boundary(0x944B, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_944C:;
    /* $944C: C8 */ nes_cpu_instruction_boundary(0x944C, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_944D:;
    /* $944D: C0 */ nes_cpu_instruction_boundary(0x944D, 2); { int r=g_cpu.Y-0x0B; g_cpu.C=(g_cpu.Y>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_944F:;
    /* $944F: F0 */ nes_cpu_instruction_boundary(0x944F, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9455; }
label_9451:;
    /* $9451: C6 */ nes_cpu_instruction_boundary(0x9451, 5); { uint16_t a=0x00; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_9453:;
    /* $9453: D0 */ nes_cpu_instruction_boundary(0x9453, 2); if (!g_cpu.Z) {
    nes_cpu_instruction_boundary(0x9445, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9445;
    }
label_9455:; /* RendFore */
    /* $9455: AE */ nes_cpu_instruction_boundary(0x9455, 4); g_cpu.X = nes_read(0x0741); FLAG_NZ(g_cpu.X);
label_9458:;
    /* $9458: F0 */ nes_cpu_instruction_boundary(0x9458, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_946D; }
label_945A:;
    /* $945A: BC */ nes_cpu_instruction_boundary(0x945A, 4); g_cpu.Y = nes_read((0x93AD + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_945D:;
    /* $945D: A2 */ nes_cpu_instruction_boundary(0x945D, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_945F:; /* SceLoop2 */
    /* $945F: B9 */ nes_cpu_instruction_boundary(0x945F, 4); g_cpu.A = nes_read((0x93B1 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9462:;
    /* $9462: F0 */ nes_cpu_instruction_boundary(0x9462, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9467; }
label_9464:;
    /* $9464: 9D */ nes_cpu_instruction_boundary(0x9464, 5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9467:; /* NoFore */
    /* $9467: C8 */ nes_cpu_instruction_boundary(0x9467, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9468:;
    /* $9468: E8 */ nes_cpu_instruction_boundary(0x9468, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_9469:;
    /* $9469: E0 */ nes_cpu_instruction_boundary(0x9469, 2); { int r=g_cpu.X-0x0D; g_cpu.C=(g_cpu.X>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_946B:;
    /* $946B: D0 */ nes_cpu_instruction_boundary(0x946B, 2); if (!g_cpu.Z) {
    nes_cpu_instruction_boundary(0x945F, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_945F;
    }
label_946D:; /* RendTerr */
    /* $946D: AC */ nes_cpu_instruction_boundary(0x946D, 4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_9470:;
    /* $9470: D0 */ nes_cpu_instruction_boundary(0x9470, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_947E; }
label_9472:;
    /* $9472: AD */ nes_cpu_instruction_boundary(0x9472, 4); g_cpu.A = nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_9475:;
    /* $9475: C9 */ nes_cpu_instruction_boundary(0x9475, 2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_9477:;
    /* $9477: D0 */ nes_cpu_instruction_boundary(0x9477, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_947E; }
label_9479:;
    /* $9479: A9 */ nes_cpu_instruction_boundary(0x9479, 2); g_cpu.A = 0x62; FLAG_NZ(g_cpu.A);
label_947B:;
    /* $947B: 4C */ nes_cpu_instruction_boundary(0x947B, 3); nes_cpu_instruction_boundary(0x9488, 2); func_9488_b0(); return;
label_947E:; /* TerMTile */
    /* $947E: B9 */ nes_cpu_instruction_boundary(0x947E, 4); g_cpu.A = nes_read((0x93D8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9481:;
    /* $9481: AC */ nes_cpu_instruction_boundary(0x9481, 4); g_cpu.Y = nes_read(0x0743); FLAG_NZ(g_cpu.Y);
label_9484:;
    /* $9484: F0 */ nes_cpu_instruction_boundary(0x9484, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9488; }
label_9486:;
    /* $9486: A9 */ nes_cpu_instruction_boundary(0x9486, 2); g_cpu.A = 0x88; FLAG_NZ(g_cpu.A);
label_9488:; /* StoreMT */
    /* $9488: 85 */ nes_cpu_instruction_boundary(0x9488, 3); nes_write(0x07, g_cpu.A);
label_948A:;
    /* $948A: A2 */ nes_cpu_instruction_boundary(0x948A, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_948C:;
    /* $948C: AD */ nes_cpu_instruction_boundary(0x948C, 4); g_cpu.A = nes_read(0x0727); FLAG_NZ(g_cpu.A);
label_948F:;
    /* $948F: 0A */ nes_cpu_instruction_boundary(0x948F, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9490:;
    /* $9490: A8 */ nes_cpu_instruction_boundary(0x9490, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9491:; /* TerrLoop */
    /* $9491: B9 */ nes_cpu_instruction_boundary(0x9491, 4); g_cpu.A = nes_read((0x93DC + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9494:;
    /* $9494: 85 */ nes_cpu_instruction_boundary(0x9494, 3); nes_write(0x00, g_cpu.A);
label_9496:;
    /* $9496: C8 */ nes_cpu_instruction_boundary(0x9496, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9497:;
    /* $9497: 84 */ nes_cpu_instruction_boundary(0x9497, 3); nes_write(0x01, g_cpu.Y);
label_9499:;
    /* $9499: AD */ nes_cpu_instruction_boundary(0x9499, 4); g_cpu.A = nes_read(0x0743); FLAG_NZ(g_cpu.A);
label_949C:;
    /* $949C: F0 */ nes_cpu_instruction_boundary(0x949C, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_94A8; }
label_949E:;
    /* $949E: E0 */ nes_cpu_instruction_boundary(0x949E, 2); { int r=g_cpu.X-0x00; g_cpu.C=(g_cpu.X>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_94A0:;
    /* $94A0: F0 */ nes_cpu_instruction_boundary(0x94A0, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_94A8; }
label_94A2:;
    /* $94A2: A5 */ nes_cpu_instruction_boundary(0x94A2, 3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_94A4:;
    /* $94A4: 29 */ nes_cpu_instruction_boundary(0x94A4, 2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_94A6:;
    /* $94A6: 85 */ nes_cpu_instruction_boundary(0x94A6, 3); nes_write(0x00, g_cpu.A);
label_94A8:; /* NoCloud2 */
    /* $94A8: A0 */ nes_cpu_instruction_boundary(0x94A8, 2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_94AA:; /* TerrBChk */
    /* $94AA: B9 */ nes_cpu_instruction_boundary(0x94AA, 4); g_cpu.A = nes_read((0xC68A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_94AD:;
    /* $94AD: 24 */ nes_cpu_instruction_boundary(0x94AD, 3); { uint8_t m=nes_read(0x00); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_94AF:;
    /* $94AF: F0 */ nes_cpu_instruction_boundary(0x94AF, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_94B6; }
label_94B1:;
    /* $94B1: A5 */ nes_cpu_instruction_boundary(0x94B1, 3); g_cpu.A = nes_read(0x07); FLAG_NZ(g_cpu.A);
label_94B3:;
    /* $94B3: 9D */ nes_cpu_instruction_boundary(0x94B3, 5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_94B6:; /* NextTBit */
    /* $94B6: E8 */ nes_cpu_instruction_boundary(0x94B6, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_94B7:;
    /* $94B7: E0 */ nes_cpu_instruction_boundary(0x94B7, 2); { int r=g_cpu.X-0x0D; g_cpu.C=(g_cpu.X>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_94B9:;
    /* $94B9: F0 */ nes_cpu_instruction_boundary(0x94B9, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_94D3; }
label_94BB:;
    /* $94BB: AD */ nes_cpu_instruction_boundary(0x94BB, 4); g_cpu.A = nes_read(0x074E); FLAG_NZ(g_cpu.A);
label_94BE:;
    /* $94BE: C9 */ nes_cpu_instruction_boundary(0x94BE, 2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_94C0:;
    /* $94C0: D0 */ nes_cpu_instruction_boundary(0x94C0, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_94CA; }
label_94C2:;
    /* $94C2: E0 */ nes_cpu_instruction_boundary(0x94C2, 2); { int r=g_cpu.X-0x0B; g_cpu.C=(g_cpu.X>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_94C4:;
    /* $94C4: D0 */ nes_cpu_instruction_boundary(0x94C4, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_94CA; }
label_94C6:;
    /* $94C6: A9 */ nes_cpu_instruction_boundary(0x94C6, 2); g_cpu.A = 0x54; FLAG_NZ(g_cpu.A);
label_94C8:;
    /* $94C8: 85 */ nes_cpu_instruction_boundary(0x94C8, 3); nes_write(0x07, g_cpu.A);
label_94CA:; /* EndUChk */
    /* $94CA: C8 */ nes_cpu_instruction_boundary(0x94CA, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_94CB:;
    /* $94CB: C0 */ nes_cpu_instruction_boundary(0x94CB, 2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_94CD:;
    /* $94CD: D0 */ nes_cpu_instruction_boundary(0x94CD, 2); if (!g_cpu.Z) {
    nes_cpu_instruction_boundary(0x94AA, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_94AA;
    }
label_94CF:;
    /* $94CF: A4 */ nes_cpu_instruction_boundary(0x94CF, 3); g_cpu.Y = nes_read(0x01); FLAG_NZ(g_cpu.Y);
label_94D1:;
    /* $94D1: D0 */ nes_cpu_instruction_boundary(0x94D1, 2); if (!g_cpu.Z) {
    nes_cpu_instruction_boundary(0x9491, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9491;
    }
label_94D3:; /* RendBBuf */
    /* $94D3: 20 */ nes_cpu_instruction_boundary(0x94D3, 6); func_9508_b0();
label_94D6:;
    /* $94D6: AD */ nes_cpu_instruction_boundary(0x94D6, 4); g_cpu.A = nes_read(0x06A0); FLAG_NZ(g_cpu.A);
label_94D9:;
    /* $94D9: 20 */ nes_cpu_instruction_boundary(0x94D9, 6); func_9BE1_b0();
label_94DC:;
    /* $94DC: A2 */ nes_cpu_instruction_boundary(0x94DC, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_94DE:;
    /* $94DE: A0 */ nes_cpu_instruction_boundary(0x94DE, 2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_94E0:; /* ChkMTLow */
    /* $94E0: 84 */ nes_cpu_instruction_boundary(0x94E0, 3); nes_write(0x00, g_cpu.Y);
label_94E2:;
    /* $94E2: BD */ nes_cpu_instruction_boundary(0x94E2, 4); g_cpu.A = nes_read((0x06A1 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_94E5:;
    /* $94E5: 29 */ nes_cpu_instruction_boundary(0x94E5, 2); g_cpu.A &= 0xC0; FLAG_NZ(g_cpu.A);
label_94E7:;
    /* $94E7: 0A */ nes_cpu_instruction_boundary(0x94E7, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_94E8:;
    /* $94E8: 2A */ nes_cpu_instruction_boundary(0x94E8, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_94E9:;
    /* $94E9: 2A */ nes_cpu_instruction_boundary(0x94E9, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_94EA:;
    /* $94EA: A8 */ nes_cpu_instruction_boundary(0x94EA, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_94EB:;
    /* $94EB: BD */ nes_cpu_instruction_boundary(0x94EB, 4); g_cpu.A = nes_read((0x06A1 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_94EE:;
    /* $94EE: D9 */ nes_cpu_instruction_boundary(0x94EE, 4); { uint8_t m=nes_read((0x9504 + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_94F1:;
    /* $94F1: B0 */ nes_cpu_instruction_boundary(0x94F1, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_94F5; }
label_94F3:;
    /* $94F3: A9 */ nes_cpu_instruction_boundary(0x94F3, 2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_94F5:; /* StrBlock */
    /* $94F5: A4 */ nes_cpu_instruction_boundary(0x94F5, 3); g_cpu.Y = nes_read(0x00); FLAG_NZ(g_cpu.Y);
label_94F7:;
    /* $94F7: 91 */ nes_cpu_instruction_boundary(0x94F7, 6); nes_write((nes_read16zp(0x06) + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_94F9:;
    /* $94F9: 98 */ nes_cpu_instruction_boundary(0x94F9, 2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_94FA:;
    /* $94FA: 18 */ nes_cpu_instruction_boundary(0x94FA, 2); g_cpu.C = 0;
label_94FB:;
    /* $94FB: 69 */ nes_cpu_instruction_boundary(0x94FB, 2); { uint16_t r = g_cpu.A + 0x10 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x10); g_cpu.A=r&0xFF; }
label_94FD:;
    /* $94FD: A8 */ nes_cpu_instruction_boundary(0x94FD, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_94FE:;
    /* $94FE: E8 */ nes_cpu_instruction_boundary(0x94FE, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_94FF:;
    /* $94FF: E0 */ nes_cpu_instruction_boundary(0x94FF, 2); { int r=g_cpu.X-0x0D; g_cpu.C=(g_cpu.X>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_9501:;
    /* $9501: 90 */ nes_cpu_instruction_boundary(0x9501, 2); if (!g_cpu.C) {
    nes_cpu_instruction_boundary(0x94E0, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_94E0;
    }
label_9503:;
    /* $9503: 60 */ nes_cpu_instruction_boundary(0x9503, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_BFB9_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_BFB9_b0");
#endif
label_BFB9:;
    /* $BFB9: 48 */ nes_cpu_instruction_boundary(0xBFB9, 3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_BFBA:;
    /* $BFBA: B4 */ nes_cpu_instruction_boundary(0xBFBA, 4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_BFBC:;
    /* $BFBC: E8 */ nes_cpu_instruction_boundary(0xBFBC, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_BFBD:;
    /* $BFBD: A9 */ nes_cpu_instruction_boundary(0xBFBD, 2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_BFBF:;
    /* $BFBF: C0 */ nes_cpu_instruction_boundary(0xBFBF, 2); { int r=g_cpu.Y-0x29; g_cpu.C=(g_cpu.Y>=0x29)?1:0; FLAG_NZ(r&0xFF); }
label_BFC1:;
    /* $BFC1: D0 */ nes_cpu_instruction_boundary(0xBFC1, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_BFC5; }
label_BFC3:;
    /* $BFC3: A9 */ nes_cpu_instruction_boundary(0xBFC3, 2); g_cpu.A = 0x09; FLAG_NZ(g_cpu.A);
label_BFC5:; /* SetDplSpd */
    /* $BFC5: 85 */ nes_cpu_instruction_boundary(0xBFC5, 3); nes_write(0x00, g_cpu.A);
label_BFC7:;
    /* $BFC7: A9 */ nes_cpu_instruction_boundary(0xBFC7, 2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_BFC9:;
    /* $BFC9: 85 */ nes_cpu_instruction_boundary(0xBFC9, 3); nes_write(0x01, g_cpu.A);
label_BFCB:;
    /* $BFCB: A9 */ nes_cpu_instruction_boundary(0xBFCB, 2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_BFCD:;
    /* $BFCD: 85 */ nes_cpu_instruction_boundary(0xBFCD, 3); nes_write(0x02, g_cpu.A);
label_BFCF:;
    /* $BFCF: 68 */ nes_cpu_instruction_boundary(0xBFCF, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_BFD0:;
    /* $BFD0: A8 */ nes_cpu_instruction_boundary(0xBFD0, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_BFD1:; /* RedPTroopaGrav */
    /* $BFD1: 20 */ nes_cpu_instruction_boundary(0xBFD1, 6); func_BFD7_b0();
label_BFD4:;
    /* $BFD4: A6 */ nes_cpu_instruction_boundary(0xBFD4, 3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_BFD6:;
    /* $BFD6: 60 */ nes_cpu_instruction_boundary(0xBFD6, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_852C_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_852C_b0");
#endif
label_852C:;
    /* $852C: 1E */ nes_cpu_instruction_boundary(0x852C, 7); { uint16_t a=(0xC901 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_852F:;
    /* $852F: 18 */ nes_cpu_instruction_boundary(0x852F, 2); g_cpu.C = 0;
label_8530:;
    /* $8530: 90 */ nes_cpu_instruction_boundary(0x8530, 2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_8537; }
label_8532:;
    /* $8532: E9 */ nes_cpu_instruction_boundary(0x8532, 2); { uint8_t m=0x01; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8534:;
    /* $8534: 9D */ nes_cpu_instruction_boundary(0x8534, 5); nes_write((0x011E + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8537:; /* SetupNumSpr */
    /* $8537: BD */ nes_cpu_instruction_boundary(0x8537, 4); g_cpu.A = nes_read((0x011E + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_853A:;
    /* $853A: E9 */ nes_cpu_instruction_boundary(0x853A, 2); { uint8_t m=0x08; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_853C:;
    /* $853C: 20 */ nes_cpu_instruction_boundary(0x853C, 6); func_E5C1();
label_853F:;
    /* $853F: BD */ nes_cpu_instruction_boundary(0x853F, 4); g_cpu.A = nes_read((0x0117 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8542:;
    /* $8542: 99 */ nes_cpu_instruction_boundary(0x8542, 5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8545:;
    /* $8545: 18 */ nes_cpu_instruction_boundary(0x8545, 2); g_cpu.C = 0;
label_8546:;
    /* $8546: 69 */ nes_cpu_instruction_boundary(0x8546, 2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_8548:;
    /* $8548: 99 */ nes_cpu_instruction_boundary(0x8548, 5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_854B:;
    /* $854B: A9 */ nes_cpu_instruction_boundary(0x854B, 2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_854D:;
    /* $854D: 99 */ nes_cpu_instruction_boundary(0x854D, 5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8550:;
    /* $8550: 99 */ nes_cpu_instruction_boundary(0x8550, 5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8553:;
    /* $8553: BD */ nes_cpu_instruction_boundary(0x8553, 4); g_cpu.A = nes_read((0x0110 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8556:;
    /* $8556: 0A */ nes_cpu_instruction_boundary(0x8556, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8557:;
    /* $8557: AA */ nes_cpu_instruction_boundary(0x8557, 2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_8558:;
    /* $8558: BD */ nes_cpu_instruction_boundary(0x8558, 4); g_cpu.A = nes_read((0x849F + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_855B:;
    /* $855B: 99 */ nes_cpu_instruction_boundary(0x855B, 5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_855E:;
    /* $855E: BD */ nes_cpu_instruction_boundary(0x855E, 4); g_cpu.A = nes_read((0x84A0 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8561:;
    /* $8561: 99 */ nes_cpu_instruction_boundary(0x8561, 5); nes_write((0x0205 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8564:;
    /* $8564: A6 */ nes_cpu_instruction_boundary(0x8564, 3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_8566:;
    /* $8566: 60 */ nes_cpu_instruction_boundary(0x8566, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_8422_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_8422_b0");
#endif
label_8422:;
    /* $8422: 11 */ nes_cpu_instruction_boundary(0x8422, 5); g_cpu.A |= nes_read((nes_read16zp(0xC8) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8424:;
    /* $8424: AD */ nes_cpu_instruction_boundary(0x8424, 4); g_cpu.A = nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_8427:;
    /* $8427: C9 */ nes_cpu_instruction_boundary(0x8427, 2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_8429:;
    /* $8429: F0 */ nes_cpu_instruction_boundary(0x8429, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_8434; }
label_842B:;
    /* $842B: 88 */ nes_cpu_instruction_boundary(0x842B, 2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_842C:;
    /* $842C: C0 */ nes_cpu_instruction_boundary(0x842C, 2); { int r=g_cpu.Y-0x04; g_cpu.C=(g_cpu.Y>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_842E:;
    /* $842E: B0 */ nes_cpu_instruction_boundary(0x842E, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_8456; }
label_8430:;
    /* $8430: C0 */ nes_cpu_instruction_boundary(0x8430, 2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_8432:;
    /* $8432: B0 */ nes_cpu_instruction_boundary(0x8432, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_8443; }
label_8434:; /* EvalForMusic */
    /* $8434: C0 */ nes_cpu_instruction_boundary(0x8434, 2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_8436:;
    /* $8436: D0 */ nes_cpu_instruction_boundary(0x8436, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_843C; }
label_8438:;
    /* $8438: A9 */ nes_cpu_instruction_boundary(0x8438, 2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_843A:;
    /* $843A: 85 */ nes_cpu_instruction_boundary(0x843A, 3); nes_write(0xFC, g_cpu.A);
label_843C:; /* PrintMsg */
    /* $843C: 98 */ nes_cpu_instruction_boundary(0x843C, 2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_843D:;
    /* $843D: 18 */ nes_cpu_instruction_boundary(0x843D, 2); g_cpu.C = 0;
label_843E:;
    /* $843E: 69 */ nes_cpu_instruction_boundary(0x843E, 2); { uint16_t r = g_cpu.A + 0x0C + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0C); g_cpu.A=r&0xFF; }
label_8440:;
    /* $8440: 8D */ nes_cpu_instruction_boundary(0x8440, 4); nes_write(0x0773, g_cpu.A);
label_8443:; /* IncMsgCounter */
    /* $8443: AD */ nes_cpu_instruction_boundary(0x8443, 4); g_cpu.A = nes_read(0x0749); FLAG_NZ(g_cpu.A);
label_8446:;
    /* $8446: 18 */ nes_cpu_instruction_boundary(0x8446, 2); g_cpu.C = 0;
label_8447:;
    /* $8447: 69 */ nes_cpu_instruction_boundary(0x8447, 2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_8449:;
    /* $8449: 8D */ nes_cpu_instruction_boundary(0x8449, 4); nes_write(0x0749, g_cpu.A);
label_844C:;
    /* $844C: AD */ nes_cpu_instruction_boundary(0x844C, 4); g_cpu.A = nes_read(0x0719); FLAG_NZ(g_cpu.A);
label_844F:;
    /* $844F: 69 */ nes_cpu_instruction_boundary(0x844F, 2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_8451:;
    /* $8451: 8D */ nes_cpu_instruction_boundary(0x8451, 4); nes_write(0x0719, g_cpu.A);
label_8454:;
    /* $8454: C9 */ nes_cpu_instruction_boundary(0x8454, 2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_8456:; /* SetEndTimer */
    /* $8456: 90 */ nes_cpu_instruction_boundary(0x8456, 2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_8460; }
label_8458:;
    /* $8458: A9 */ nes_cpu_instruction_boundary(0x8458, 2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_845A:;
    /* $845A: 8D */ nes_cpu_instruction_boundary(0x845A, 4); nes_write(0x07A1, g_cpu.A);
label_845D:; /* IncModeTask_A */
    /* $845D: EE */ nes_cpu_instruction_boundary(0x845D, 6); { uint16_t a=0x0772; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8460:; /* ExitMsgs */
    /* $8460: 60 */ nes_cpu_instruction_boundary(0x8460, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_8224_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_8224_b0");
#endif
label_8224:;
    /* $8224: 04 */ nes_cpu_instruction_boundary(0x8224, 3); (void)nes_read(0xA9); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_8226:;
    /* $8226: F8 */ nes_cpu_instruction_boundary(0x8226, 2); g_cpu.D = 1;
label_8227:; /* SprInitLoop */
    /* $8227: 99 */ nes_cpu_instruction_boundary(0x8227, 5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_822A:;
    /* $822A: C8 */ nes_cpu_instruction_boundary(0x822A, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822B:;
    /* $822B: C8 */ nes_cpu_instruction_boundary(0x822B, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822C:;
    /* $822C: C8 */ nes_cpu_instruction_boundary(0x822C, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822D:;
    /* $822D: C8 */ nes_cpu_instruction_boundary(0x822D, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822E:;
    /* $822E: D0 */ nes_cpu_instruction_boundary(0x822E, 2); if (!g_cpu.Z) {
    nes_cpu_instruction_boundary(0x8227, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8227;
    }
label_8230:;
    /* $8230: 60 */ nes_cpu_instruction_boundary(0x8230, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_85AF_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_85AF_b0");
#endif
label_85AF:;
    /* $85AF: 85 */ nes_cpu_instruction_boundary(0x85AF, 3); nes_write(0x68, g_cpu.A);
label_85B1:;
    /* $85B1: 8D */ nes_cpu_instruction_boundary(0x85B1, 4); nes_write(0x0756, g_cpu.A);
label_85B4:;
    /* $85B4: 68 */ nes_cpu_instruction_boundary(0x85B4, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_85B5:;
    /* $85B5: 8D */ nes_cpu_instruction_boundary(0x85B5, 4); nes_write(0x0744, g_cpu.A);
label_85B8:;
    /* $85B8: 4C */ nes_cpu_instruction_boundary(0x85B8, 3); nes_cpu_instruction_boundary(0x8745, 2); func_8745_b0(); return;
}

void func_85AD_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_85AD_b0");
#endif
label_85AD:;
    /* $85AD: 20 */ nes_cpu_instruction_boundary(0x85AD, 6); func_85F1_b0();
label_85B0:;
    /* $85B0: 68 */ nes_cpu_instruction_boundary(0x85B0, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_85B1:;
    /* $85B1: 8D */ nes_cpu_instruction_boundary(0x85B1, 4); nes_write(0x0756, g_cpu.A);
label_85B4:;
    /* $85B4: 68 */ nes_cpu_instruction_boundary(0x85B4, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_85B5:;
    /* $85B5: 8D */ nes_cpu_instruction_boundary(0x85B5, 4); nes_write(0x0744, g_cpu.A);
label_85B8:;
    /* $85B8: 4C */ nes_cpu_instruction_boundary(0x85B8, 3); nes_cpu_instruction_boundary(0x8745, 2); func_8745_b0(); return;
}

void func_830C_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_830C_b0");
#endif
label_830C:;
    /* $830C: FA */ nes_cpu_instruction_boundary(0x830C, 2); /* NOP */
label_830D:; /* ExitMenu */
    /* $830D: 60 */ nes_cpu_instruction_boundary(0x830D, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_9A99_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9A99_b0");
#endif
label_9A99:;
    /* $9A99: 04 */ nes_cpu_instruction_boundary(0x9A99, 3); (void)nes_read(0xE8); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_9A9B:;
    /* $9A9B: E0 */ nes_cpu_instruction_boundary(0x9A9B, 2); { int r=g_cpu.X-0x06; g_cpu.C=(g_cpu.X>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_9A9D:;
    /* $9A9D: 90 */ nes_cpu_instruction_boundary(0x9A9D, 2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_9AA1; }
label_9A9F:;
    /* $9A9F: A2 */ nes_cpu_instruction_boundary(0x9A9F, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_9AA1:; /* StrCOffset */
    /* $9AA1: 8E */ nes_cpu_instruction_boundary(0x9AA1, 4); nes_write(0x046A, g_cpu.X);
label_9AA4:;
    /* $9AA4: 60 */ nes_cpu_instruction_boundary(0x9AA4, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_909B_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_909B_b0");
#endif
label_909B:;
    /* $909B: 38 */ nes_cpu_instruction_boundary(0x909B, 2); g_cpu.C = 1;
label_909C:;
    /* $909C: 8D */ nes_cpu_instruction_boundary(0x909C, 4); nes_write(0x06E3, g_cpu.A);
label_909F:;
    /* $909F: A9 */ nes_cpu_instruction_boundary(0x909F, 2); g_cpu.A = 0x48; FLAG_NZ(g_cpu.A);
label_90A1:;
    /* $90A1: 8D */ nes_cpu_instruction_boundary(0x90A1, 4); nes_write(0x06E2, g_cpu.A);
label_90A4:;
    /* $90A4: A9 */ nes_cpu_instruction_boundary(0x90A4, 2); g_cpu.A = 0x58; FLAG_NZ(g_cpu.A);
label_90A6:;
    /* $90A6: 8D */ nes_cpu_instruction_boundary(0x90A6, 4); nes_write(0x06E1, g_cpu.A);
label_90A9:;
    /* $90A9: A2 */ nes_cpu_instruction_boundary(0x90A9, 2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_90AB:; /* ShufAmtLoop */
    /* $90AB: BD */ nes_cpu_instruction_boundary(0x90AB, 4); g_cpu.A = nes_read((0x8FBC + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_90AE:;
    /* $90AE: 9D */ nes_cpu_instruction_boundary(0x90AE, 5); nes_write((0x06E4 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_90B1:;
    /* $90B1: CA */ nes_cpu_instruction_boundary(0x90B1, 2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_90B2:;
    /* $90B2: 10 */ nes_cpu_instruction_boundary(0x90B2, 2); if (!g_cpu.N) {
    nes_cpu_instruction_boundary(0x90AB, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_90AB;
    }
label_90B4:;
    /* $90B4: A0 */ nes_cpu_instruction_boundary(0x90B4, 2); g_cpu.Y = 0x03; FLAG_NZ(g_cpu.Y);
label_90B6:; /* ISpr0Loop */
    /* $90B6: B9 */ nes_cpu_instruction_boundary(0x90B6, 4); g_cpu.A = nes_read((0x8FCB + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_90B9:;
    /* $90B9: 99 */ nes_cpu_instruction_boundary(0x90B9, 5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_90BC:;
    /* $90BC: 88 */ nes_cpu_instruction_boundary(0x90BC, 2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_90BD:;
    /* $90BD: 10 */ nes_cpu_instruction_boundary(0x90BD, 2); if (!g_cpu.N) {
    nes_cpu_instruction_boundary(0x90B6, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_90B6;
    }
label_90BF:;
    /* $90BF: 20 */ nes_cpu_instruction_boundary(0x90BF, 6); func_92AF_b0();
label_90C2:;
    /* $90C2: 20 */ nes_cpu_instruction_boundary(0x90C2, 6); func_92AA_b0();
label_90C5:;
    /* $90C5: EE */ nes_cpu_instruction_boundary(0x90C5, 6); { uint16_t a=0x0722; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_90C8:;
    /* $90C8: EE */ nes_cpu_instruction_boundary(0x90C8, 6); { uint16_t a=0x0772; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_90CB:;
    /* $90CB: 60 */ nes_cpu_instruction_boundary(0x90CB, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

void func_B308_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_B308_b0");
#endif
label_B308:;
    /* $B308: 5F */ nes_cpu_instruction_boundary(0xB308, 7); { uint16_t a=(0xAD07 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); g_cpu.A^=v; FLAG_NZ(g_cpu.A); }
label_B30B:;
    /* $B30B: 48 */ nes_cpu_instruction_boundary(0xB30B, 3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_B30C:;
    /* $B30C: 07 */ nes_cpu_instruction_boundary(0xB30C, 5); { uint16_t a=0xD9; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_B30E:;
    /* $B30E: C2 */ nes_cpu_instruction_boundary(0xB30E, 2); /* NOP */
label_B310:;
    /* $B310: 90 */ nes_cpu_instruction_boundary(0xB310, 2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_B315; }
label_B312:;
    /* $B312: EE */ nes_cpu_instruction_boundary(0xB312, 6); { uint16_t a=0x075D; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B315:; /* NextArea */
    /* $B315: EE */ nes_cpu_instruction_boundary(0xB315, 6); { uint16_t a=0x0760; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B318:;
    /* $B318: 20 */ nes_cpu_instruction_boundary(0xB318, 6); func_9C03_b0();
label_B31B:;
    /* $B31B: EE */ nes_cpu_instruction_boundary(0xB31B, 6); { uint16_t a=0x0757; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B31E:;
    /* $B31E: 20 */ nes_cpu_instruction_boundary(0xB31E, 6); func_B213_b0();
label_B321:;
    /* $B321: 8D */ nes_cpu_instruction_boundary(0xB321, 4); nes_write(0x075B, g_cpu.A);
label_B324:;
    /* $B324: A9 */ nes_cpu_instruction_boundary(0xB324, 2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_B326:;
    /* $B326: 85 */ nes_cpu_instruction_boundary(0xB326, 3); nes_write(0xFC, g_cpu.A);
label_B328:; /* ExitNA */
    /* $B328: 60 */ nes_cpu_instruction_boundary(0xB328, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

