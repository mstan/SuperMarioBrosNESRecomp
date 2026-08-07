/* super-mario-bros_full_bank00_part01.c — PRG bank 0 function bodies (sub-part 1).
 * STANDALONE translation unit — compiled independently (in
 * parallel with every other bank part/sub-part and the
 * umbrella super-mario-bros_full.c). Do not compile as part of another TU or
 * edit directly; the source of truth is the recompiler's
 * code_generator.c. Renamed to drop the _partNN suffix if
 * this bank turned out to fit in a single sub-part. */

#include "super-mario-bros_full_decls.h"

void func_9BBB_b0(void) { /* GetLrgObjAttrib */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9BBB_b0");
#endif
label_9BBB:; /* GetLrgObjAttrib */
    /* $9BBB: BC */ nes_instruction_boundary(0x9BBB, 4); g_cpu.Y = nes_read((0x072D + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_9BBE:;
    /* $9BBE: B1 */ nes_instruction_boundary(0x9BBE, 5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9BC0:;
    /* $9BC0: 29 */ nes_instruction_boundary(0x9BC0, 2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_9BC2:;
    /* $9BC2: 85 */ nes_instruction_boundary(0x9BC2, 3); nes_write(0x07, g_cpu.A);
label_9BC4:;
    /* $9BC4: C8 */ nes_instruction_boundary(0x9BC4, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9BC5:;
    /* $9BC5: B1 */ nes_instruction_boundary(0x9BC5, 5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9BC7:;
    /* $9BC7: 29 */ nes_instruction_boundary(0x9BC7, 2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_9BC9:;
    /* $9BC9: A8 */ nes_instruction_boundary(0x9BC9, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9BCA:;
    /* $9BCA: 60 */ nes_instruction_boundary(0x9BCA, 6); 
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
    /* $9BAF: BD */ nes_instruction_boundary(0x9BAF, 4); g_cpu.A = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9BB2:;
    /* $9BB2: 18 */ nes_instruction_boundary(0x9BB2, 2); g_cpu.C = 0;
label_9BB3:;
    /* $9BB3: 10 */ nes_instruction_boundary(0x9BB3, 2); if (!g_cpu.N) { maybe_trigger_vblank(1); goto label_9BBA; }
label_9BB5:;
    /* $9BB5: 98 */ nes_instruction_boundary(0x9BB5, 2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_9BB6:;
    /* $9BB6: 9D */ nes_instruction_boundary(0x9BB6, 5); nes_write((0x0730 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9BB9:;
    /* $9BB9: 38 */ nes_instruction_boundary(0x9BB9, 2); g_cpu.C = 1;
label_9BBA:; /* LenSet */
    /* $9BBA: 60 */ nes_instruction_boundary(0x9BBA, 6); 
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
    /* $98B3: 88 */ nes_instruction_boundary(0x98B3, 2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_98B4:;
    /* $98B4: 88 */ nes_instruction_boundary(0x98B4, 2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_98B5:;
    /* $98B5: 84 */ nes_instruction_boundary(0x98B5, 3); nes_write(0x05, g_cpu.Y);
label_98B7:;
    /* $98B7: BC */ nes_instruction_boundary(0x98B7, 4); g_cpu.Y = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_98BA:;
    /* $98BA: 84 */ nes_instruction_boundary(0x98BA, 3); nes_write(0x06, g_cpu.Y);
label_98BC:;
    /* $98BC: A6 */ nes_instruction_boundary(0x98BC, 3); g_cpu.X = nes_read(0x05); FLAG_NZ(g_cpu.X);
label_98BE:;
    /* $98BE: E8 */ nes_instruction_boundary(0x98BE, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_98BF:;
    /* $98BF: B9 */ nes_instruction_boundary(0x98BF, 4); g_cpu.A = nes_read((0x989F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_98C2:;
    /* $98C2: C9 */ nes_instruction_boundary(0x98C2, 2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_98C4:;
    /* $98C4: F0 */ nes_instruction_boundary(0x98C4, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_98CE; }
label_98C6:;
    /* $98C6: A2 */ nes_instruction_boundary(0x98C6, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_98C8:;
    /* $98C8: A4 */ nes_instruction_boundary(0x98C8, 3); g_cpu.Y = nes_read(0x05); FLAG_NZ(g_cpu.Y);
label_98CA:;
    /* $98CA: 20 */ nes_instruction_boundary(0x98CA, 6); func_9B7D_b0();
label_98CD:;
    /* $98CD: 18 */ nes_instruction_boundary(0x98CD, 2); g_cpu.C = 0;
label_98CE:; /* DrawSidePart */
    /* $98CE: A4 */ nes_instruction_boundary(0x98CE, 3); g_cpu.Y = nes_read(0x06); FLAG_NZ(g_cpu.Y);
label_98D0:;
    /* $98D0: B9 */ nes_instruction_boundary(0x98D0, 4); g_cpu.A = nes_read((0x98A3 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_98D3:;
    /* $98D3: 9D */ nes_instruction_boundary(0x98D3, 5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_98D6:;
    /* $98D6: B9 */ nes_instruction_boundary(0x98D6, 4); g_cpu.A = nes_read((0x98A7 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_98D9:;
    /* $98D9: 9D */ nes_instruction_boundary(0x98D9, 5); nes_write((0x06A2 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_98DC:;
    /* $98DC: 60 */ nes_instruction_boundary(0x98DC, 6); 
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
    /* $99E9: A9 */ nes_instruction_boundary(0x99E9, 2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_99EB:;
    /* $99EB: 4C */ nes_instruction_boundary(0x99EB, 3); nes_cpu_instruction_boundary(0x9B7D, 2); func_9B7D_b0(); return;
}

void func_9A44_b0(void) { /* GetRow */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9A44_b0");
#endif
label_9A44:; /* GetRow */
    /* $9A44: 48 */ nes_instruction_boundary(0x9A44, 3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9A45:;
    /* $9A45: 20 */ nes_instruction_boundary(0x9A45, 6); func_9BAC_b0();
label_9A48:; /* DrawRow */
    /* $9A48: A6 */ nes_instruction_boundary(0x9A48, 3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_9A4A:;
    /* $9A4A: A0 */ nes_instruction_boundary(0x9A4A, 2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_9A4C:;
    /* $9A4C: 68 */ nes_instruction_boundary(0x9A4C, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9A4D:;
    /* $9A4D: 4C */ nes_instruction_boundary(0x9A4D, 3); nes_cpu_instruction_boundary(0x9B7D, 2); func_9B7D_b0(); return;
}

void func_9A20_b0(void) { /* ColObj */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9A20_b0");
#endif
label_9A20:; /* ColObj */
    /* $9A20: A0 */ nes_instruction_boundary(0x9A20, 2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_9A22:;
    /* $9A22: 4C */ nes_instruction_boundary(0x9A22, 3); nes_cpu_instruction_boundary(0x9B7D, 2); func_9B7D_b0(); return;
}

void func_9A5F_b0(void) { /* GetRow2 */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9A5F_b0");
#endif
label_9A5F:; /* GetRow2 */
    /* $9A5F: 48 */ nes_instruction_boundary(0x9A5F, 3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9A60:;
    /* $9A60: 20 */ nes_instruction_boundary(0x9A60, 6); func_9BBB_b0();
label_9A63:;
    /* $9A63: 68 */ nes_instruction_boundary(0x9A63, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9A64:;
    /* $9A64: A6 */ nes_instruction_boundary(0x9A64, 3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_9A66:;
    /* $9A66: 4C */ nes_instruction_boundary(0x9A66, 3); nes_cpu_instruction_boundary(0x9B7D, 2); func_9B7D_b0(); return;
}

void func_9B36_b0(void) { /* GetAreaObjectID */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9B36_b0");
#endif
label_9B36:; /* GetAreaObjectID */
    /* $9B36: A5 */ nes_instruction_boundary(0x9B36, 3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_9B38:;
    /* $9B38: 38 */ nes_instruction_boundary(0x9B38, 2); g_cpu.C = 1;
label_9B39:;
    /* $9B39: E9 */ nes_instruction_boundary(0x9B39, 2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9B3B:;
    /* $9B3B: A8 */ nes_instruction_boundary(0x9B3B, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9B3C:; /* ExitDecBlock */
    /* $9B3C: 60 */ nes_instruction_boundary(0x9B3C, 6); 
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
    /* $9B2C: B9 */ nes_instruction_boundary(0x9B2C, 4); g_cpu.A = nes_read((0xBDE8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9B2F:;
    /* $9B2F: 48 */ nes_instruction_boundary(0x9B2F, 3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9B30:;
    /* $9B30: 20 */ nes_instruction_boundary(0x9B30, 6); func_9BBB_b0();
label_9B33:;
    /* $9B33: 4C */ nes_instruction_boundary(0x9B33, 3); nes_cpu_instruction_boundary(0x9A48, 2); func_9A48_b0(); return;
}

void func_9A48_b0(void) { /* DrawRow */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9A48_b0");
#endif
label_9A48:; /* DrawRow */
    /* $9A48: A6 */ nes_instruction_boundary(0x9A48, 3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_9A4A:;
    /* $9A4A: A0 */ nes_instruction_boundary(0x9A4A, 2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_9A4C:;
    /* $9A4C: 68 */ nes_instruction_boundary(0x9A4C, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9A4D:;
    /* $9A4D: 4C */ nes_instruction_boundary(0x9A4D, 3); nes_cpu_instruction_boundary(0x9B7D, 2); func_9B7D_b0(); return;
}

void func_8E04_b0(void) { /* JumpEngine */
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_8E04_b0");
#endif
label_8E04:; /* JumpEngine */
    /* $8E04: 0A */ nes_instruction_boundary(0x8E04, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8E05:;
    /* $8E05: A8 */ nes_instruction_boundary(0x8E05, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_8E06:;
    /* $8E06: 68 */ nes_instruction_boundary(0x8E06, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_8E07:;
    /* $8E07: 85 */ nes_instruction_boundary(0x8E07, 3); nes_write(0x04, g_cpu.A);
label_8E09:;
    /* $8E09: 68 */ nes_instruction_boundary(0x8E09, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_8E0A:;
    /* $8E0A: 85 */ nes_instruction_boundary(0x8E0A, 3); nes_write(0x05, g_cpu.A);
label_8E0C:;
    /* $8E0C: C8 */ nes_instruction_boundary(0x8E0C, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8E0D:;
    /* $8E0D: B1 */ nes_instruction_boundary(0x8E0D, 5); g_cpu.A = nes_read((nes_read16zp(0x04) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8E0F:;
    /* $8E0F: 85 */ nes_instruction_boundary(0x8E0F, 3); nes_write(0x06, g_cpu.A);
label_8E11:;
    /* $8E11: C8 */ nes_instruction_boundary(0x8E11, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8E12:;
    /* $8E12: B1 */ nes_instruction_boundary(0x8E12, 5); g_cpu.A = nes_read((nes_read16zp(0x04) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8E14:;
    /* $8E14: 85 */ nes_instruction_boundary(0x8E14, 3); nes_write(0x07, g_cpu.A);
label_8E16:;
    /* $8E16: 6C */ nes_instruction_boundary(0x8E16, 5); { uint16_t _jt = nes_read16zp(0x06); nes_cpu_instruction_boundary(_jt, 2); call_by_address_tail(_jt, -1); return; }
}

void func_9402_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_9402_b0");
#endif
label_9402:;
    /* $9402: 08 */ nes_instruction_boundary(0x9402, 3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_9403:;
    /* $9403: 95 */ nes_instruction_boundary(0x9403, 4); nes_write((0xA2 + g_cpu.X) & 0xFF, g_cpu.A);
label_9405:;
    /* $9405: 0C */ nes_instruction_boundary(0x9405, 4); (void)nes_read(0x00A9); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_9408:; /* ClrMTBuf */
    /* $9408: 9D */ nes_instruction_boundary(0x9408, 5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_940B:;
    /* $940B: CA */ nes_instruction_boundary(0x940B, 2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_940C:;
    /* $940C: 10 */ nes_instruction_boundary(0x940C, 2); if (!g_cpu.N) {
    nes_instruction_boundary(0x9408, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9408;
    }
label_940E:;
    /* $940E: AC */ nes_instruction_boundary(0x940E, 4); g_cpu.Y = nes_read(0x0742); FLAG_NZ(g_cpu.Y);
label_9411:;
    /* $9411: F0 */ nes_instruction_boundary(0x9411, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9455; }
label_9413:;
    /* $9413: AD */ nes_instruction_boundary(0x9413, 4); g_cpu.A = nes_read(0x0725); FLAG_NZ(g_cpu.A);
label_9416:; /* ThirdP */
    /* $9416: C9 */ nes_instruction_boundary(0x9416, 2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_9418:;
    /* $9418: 30 */ nes_instruction_boundary(0x9418, 2); if (g_cpu.N) { maybe_trigger_vblank(1); goto label_941F; }
label_941A:;
    /* $941A: 38 */ nes_instruction_boundary(0x941A, 2); g_cpu.C = 1;
label_941B:;
    /* $941B: E9 */ nes_instruction_boundary(0x941B, 2); { uint8_t m=0x03; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_941D:;
    /* $941D: 10 */ nes_instruction_boundary(0x941D, 2); if (!g_cpu.N) {
    nes_instruction_boundary(0x9416, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9416;
    }
label_941F:; /* RendBack */
    /* $941F: 0A */ nes_instruction_boundary(0x941F, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9420:;
    /* $9420: 0A */ nes_instruction_boundary(0x9420, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9421:;
    /* $9421: 0A */ nes_instruction_boundary(0x9421, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9422:;
    /* $9422: 0A */ nes_instruction_boundary(0x9422, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9423:;
    /* $9423: 79 */ nes_instruction_boundary(0x9423, 4); { uint8_t m=nes_read((0x92F6 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9426:;
    /* $9426: 6D */ nes_instruction_boundary(0x9426, 4); { uint8_t m=nes_read(0x0726); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9429:;
    /* $9429: AA */ nes_instruction_boundary(0x9429, 2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_942A:;
    /* $942A: BD */ nes_instruction_boundary(0x942A, 4); g_cpu.A = nes_read((0x92FA + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_942D:;
    /* $942D: F0 */ nes_instruction_boundary(0x942D, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9455; }
label_942F:;
    /* $942F: 48 */ nes_instruction_boundary(0x942F, 3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9430:;
    /* $9430: 29 */ nes_instruction_boundary(0x9430, 2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_9432:;
    /* $9432: 38 */ nes_instruction_boundary(0x9432, 2); g_cpu.C = 1;
label_9433:;
    /* $9433: E9 */ nes_instruction_boundary(0x9433, 2); { uint8_t m=0x01; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9435:;
    /* $9435: 85 */ nes_instruction_boundary(0x9435, 3); nes_write(0x00, g_cpu.A);
label_9437:;
    /* $9437: 0A */ nes_instruction_boundary(0x9437, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9438:;
    /* $9438: 65 */ nes_instruction_boundary(0x9438, 3); { uint8_t m=nes_read(0x00); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_943A:;
    /* $943A: AA */ nes_instruction_boundary(0x943A, 2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_943B:;
    /* $943B: 68 */ nes_instruction_boundary(0x943B, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_943C:;
    /* $943C: 4A */ nes_instruction_boundary(0x943C, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_943D:;
    /* $943D: 4A */ nes_instruction_boundary(0x943D, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_943E:;
    /* $943E: 4A */ nes_instruction_boundary(0x943E, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_943F:;
    /* $943F: 4A */ nes_instruction_boundary(0x943F, 2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9440:;
    /* $9440: A8 */ nes_instruction_boundary(0x9440, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9441:;
    /* $9441: A9 */ nes_instruction_boundary(0x9441, 2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_9443:;
    /* $9443: 85 */ nes_instruction_boundary(0x9443, 3); nes_write(0x00, g_cpu.A);
label_9445:; /* SceLoop1 */
    /* $9445: BD */ nes_instruction_boundary(0x9445, 4); g_cpu.A = nes_read((0x938A + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9448:;
    /* $9448: 99 */ nes_instruction_boundary(0x9448, 5); nes_write((0x06A1 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_944B:;
    /* $944B: E8 */ nes_instruction_boundary(0x944B, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_944C:;
    /* $944C: C8 */ nes_instruction_boundary(0x944C, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_944D:;
    /* $944D: C0 */ nes_instruction_boundary(0x944D, 2); { int r=g_cpu.Y-0x0B; g_cpu.C=(g_cpu.Y>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_944F:;
    /* $944F: F0 */ nes_instruction_boundary(0x944F, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9455; }
label_9451:;
    /* $9451: C6 */ nes_instruction_boundary(0x9451, 5); { uint16_t a=0x00; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_9453:;
    /* $9453: D0 */ nes_instruction_boundary(0x9453, 2); if (!g_cpu.Z) {
    nes_instruction_boundary(0x9445, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9445;
    }
label_9455:; /* RendFore */
    /* $9455: AE */ nes_instruction_boundary(0x9455, 4); g_cpu.X = nes_read(0x0741); FLAG_NZ(g_cpu.X);
label_9458:;
    /* $9458: F0 */ nes_instruction_boundary(0x9458, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_946D; }
label_945A:;
    /* $945A: BC */ nes_instruction_boundary(0x945A, 4); g_cpu.Y = nes_read((0x93AD + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_945D:;
    /* $945D: A2 */ nes_instruction_boundary(0x945D, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_945F:; /* SceLoop2 */
    /* $945F: B9 */ nes_instruction_boundary(0x945F, 4); g_cpu.A = nes_read((0x93B1 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9462:;
    /* $9462: F0 */ nes_instruction_boundary(0x9462, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9467; }
label_9464:;
    /* $9464: 9D */ nes_instruction_boundary(0x9464, 5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9467:; /* NoFore */
    /* $9467: C8 */ nes_instruction_boundary(0x9467, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9468:;
    /* $9468: E8 */ nes_instruction_boundary(0x9468, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_9469:;
    /* $9469: E0 */ nes_instruction_boundary(0x9469, 2); { int r=g_cpu.X-0x0D; g_cpu.C=(g_cpu.X>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_946B:;
    /* $946B: D0 */ nes_instruction_boundary(0x946B, 2); if (!g_cpu.Z) {
    nes_instruction_boundary(0x945F, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_945F;
    }
label_946D:; /* RendTerr */
    /* $946D: AC */ nes_instruction_boundary(0x946D, 4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_9470:;
    /* $9470: D0 */ nes_instruction_boundary(0x9470, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_947E; }
label_9472:;
    /* $9472: AD */ nes_instruction_boundary(0x9472, 4); g_cpu.A = nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_9475:;
    /* $9475: C9 */ nes_instruction_boundary(0x9475, 2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_9477:;
    /* $9477: D0 */ nes_instruction_boundary(0x9477, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_947E; }
label_9479:;
    /* $9479: A9 */ nes_instruction_boundary(0x9479, 2); g_cpu.A = 0x62; FLAG_NZ(g_cpu.A);
label_947B:;
    /* $947B: 4C */ nes_instruction_boundary(0x947B, 3); nes_cpu_instruction_boundary(0x9488, 2); func_9488_b0(); return;
label_947E:; /* TerMTile */
    /* $947E: B9 */ nes_instruction_boundary(0x947E, 4); g_cpu.A = nes_read((0x93D8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9481:;
    /* $9481: AC */ nes_instruction_boundary(0x9481, 4); g_cpu.Y = nes_read(0x0743); FLAG_NZ(g_cpu.Y);
label_9484:;
    /* $9484: F0 */ nes_instruction_boundary(0x9484, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_9488; }
label_9486:;
    /* $9486: A9 */ nes_instruction_boundary(0x9486, 2); g_cpu.A = 0x88; FLAG_NZ(g_cpu.A);
label_9488:; /* StoreMT */
    /* $9488: 85 */ nes_instruction_boundary(0x9488, 3); nes_write(0x07, g_cpu.A);
label_948A:;
    /* $948A: A2 */ nes_instruction_boundary(0x948A, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_948C:;
    /* $948C: AD */ nes_instruction_boundary(0x948C, 4); g_cpu.A = nes_read(0x0727); FLAG_NZ(g_cpu.A);
label_948F:;
    /* $948F: 0A */ nes_instruction_boundary(0x948F, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9490:;
    /* $9490: A8 */ nes_instruction_boundary(0x9490, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9491:; /* TerrLoop */
    /* $9491: B9 */ nes_instruction_boundary(0x9491, 4); g_cpu.A = nes_read((0x93DC + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9494:;
    /* $9494: 85 */ nes_instruction_boundary(0x9494, 3); nes_write(0x00, g_cpu.A);
label_9496:;
    /* $9496: C8 */ nes_instruction_boundary(0x9496, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9497:;
    /* $9497: 84 */ nes_instruction_boundary(0x9497, 3); nes_write(0x01, g_cpu.Y);
label_9499:;
    /* $9499: AD */ nes_instruction_boundary(0x9499, 4); g_cpu.A = nes_read(0x0743); FLAG_NZ(g_cpu.A);
label_949C:;
    /* $949C: F0 */ nes_instruction_boundary(0x949C, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_94A8; }
label_949E:;
    /* $949E: E0 */ nes_instruction_boundary(0x949E, 2); { int r=g_cpu.X-0x00; g_cpu.C=(g_cpu.X>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_94A0:;
    /* $94A0: F0 */ nes_instruction_boundary(0x94A0, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_94A8; }
label_94A2:;
    /* $94A2: A5 */ nes_instruction_boundary(0x94A2, 3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_94A4:;
    /* $94A4: 29 */ nes_instruction_boundary(0x94A4, 2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_94A6:;
    /* $94A6: 85 */ nes_instruction_boundary(0x94A6, 3); nes_write(0x00, g_cpu.A);
label_94A8:; /* NoCloud2 */
    /* $94A8: A0 */ nes_instruction_boundary(0x94A8, 2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_94AA:; /* TerrBChk */
    /* $94AA: B9 */ nes_instruction_boundary(0x94AA, 4); g_cpu.A = nes_read((0xC68A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_94AD:;
    /* $94AD: 24 */ nes_instruction_boundary(0x94AD, 3); { uint8_t m=nes_read(0x00); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_94AF:;
    /* $94AF: F0 */ nes_instruction_boundary(0x94AF, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_94B6; }
label_94B1:;
    /* $94B1: A5 */ nes_instruction_boundary(0x94B1, 3); g_cpu.A = nes_read(0x07); FLAG_NZ(g_cpu.A);
label_94B3:;
    /* $94B3: 9D */ nes_instruction_boundary(0x94B3, 5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_94B6:; /* NextTBit */
    /* $94B6: E8 */ nes_instruction_boundary(0x94B6, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_94B7:;
    /* $94B7: E0 */ nes_instruction_boundary(0x94B7, 2); { int r=g_cpu.X-0x0D; g_cpu.C=(g_cpu.X>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_94B9:;
    /* $94B9: F0 */ nes_instruction_boundary(0x94B9, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_94D3; }
label_94BB:;
    /* $94BB: AD */ nes_instruction_boundary(0x94BB, 4); g_cpu.A = nes_read(0x074E); FLAG_NZ(g_cpu.A);
label_94BE:;
    /* $94BE: C9 */ nes_instruction_boundary(0x94BE, 2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_94C0:;
    /* $94C0: D0 */ nes_instruction_boundary(0x94C0, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_94CA; }
label_94C2:;
    /* $94C2: E0 */ nes_instruction_boundary(0x94C2, 2); { int r=g_cpu.X-0x0B; g_cpu.C=(g_cpu.X>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_94C4:;
    /* $94C4: D0 */ nes_instruction_boundary(0x94C4, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_94CA; }
label_94C6:;
    /* $94C6: A9 */ nes_instruction_boundary(0x94C6, 2); g_cpu.A = 0x54; FLAG_NZ(g_cpu.A);
label_94C8:;
    /* $94C8: 85 */ nes_instruction_boundary(0x94C8, 3); nes_write(0x07, g_cpu.A);
label_94CA:; /* EndUChk */
    /* $94CA: C8 */ nes_instruction_boundary(0x94CA, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_94CB:;
    /* $94CB: C0 */ nes_instruction_boundary(0x94CB, 2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_94CD:;
    /* $94CD: D0 */ nes_instruction_boundary(0x94CD, 2); if (!g_cpu.Z) {
    nes_instruction_boundary(0x94AA, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_94AA;
    }
label_94CF:;
    /* $94CF: A4 */ nes_instruction_boundary(0x94CF, 3); g_cpu.Y = nes_read(0x01); FLAG_NZ(g_cpu.Y);
label_94D1:;
    /* $94D1: D0 */ nes_instruction_boundary(0x94D1, 2); if (!g_cpu.Z) {
    nes_instruction_boundary(0x9491, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9491;
    }
label_94D3:; /* RendBBuf */
    /* $94D3: 20 */ nes_instruction_boundary(0x94D3, 6); func_9508_b0();
label_94D6:;
    /* $94D6: AD */ nes_instruction_boundary(0x94D6, 4); g_cpu.A = nes_read(0x06A0); FLAG_NZ(g_cpu.A);
label_94D9:;
    /* $94D9: 20 */ nes_instruction_boundary(0x94D9, 6); func_9BE1_b0();
label_94DC:;
    /* $94DC: A2 */ nes_instruction_boundary(0x94DC, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_94DE:;
    /* $94DE: A0 */ nes_instruction_boundary(0x94DE, 2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_94E0:; /* ChkMTLow */
    /* $94E0: 84 */ nes_instruction_boundary(0x94E0, 3); nes_write(0x00, g_cpu.Y);
label_94E2:;
    /* $94E2: BD */ nes_instruction_boundary(0x94E2, 4); g_cpu.A = nes_read((0x06A1 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_94E5:;
    /* $94E5: 29 */ nes_instruction_boundary(0x94E5, 2); g_cpu.A &= 0xC0; FLAG_NZ(g_cpu.A);
label_94E7:;
    /* $94E7: 0A */ nes_instruction_boundary(0x94E7, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_94E8:;
    /* $94E8: 2A */ nes_instruction_boundary(0x94E8, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_94E9:;
    /* $94E9: 2A */ nes_instruction_boundary(0x94E9, 2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_94EA:;
    /* $94EA: A8 */ nes_instruction_boundary(0x94EA, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_94EB:;
    /* $94EB: BD */ nes_instruction_boundary(0x94EB, 4); g_cpu.A = nes_read((0x06A1 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_94EE:;
    /* $94EE: D9 */ nes_instruction_boundary(0x94EE, 4); { uint8_t m=nes_read((0x9504 + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_94F1:;
    /* $94F1: B0 */ nes_instruction_boundary(0x94F1, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_94F5; }
label_94F3:;
    /* $94F3: A9 */ nes_instruction_boundary(0x94F3, 2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_94F5:; /* StrBlock */
    /* $94F5: A4 */ nes_instruction_boundary(0x94F5, 3); g_cpu.Y = nes_read(0x00); FLAG_NZ(g_cpu.Y);
label_94F7:;
    /* $94F7: 91 */ nes_instruction_boundary(0x94F7, 6); nes_write((nes_read16zp(0x06) + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_94F9:;
    /* $94F9: 98 */ nes_instruction_boundary(0x94F9, 2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_94FA:;
    /* $94FA: 18 */ nes_instruction_boundary(0x94FA, 2); g_cpu.C = 0;
label_94FB:;
    /* $94FB: 69 */ nes_instruction_boundary(0x94FB, 2); { uint16_t r = g_cpu.A + 0x10 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x10); g_cpu.A=r&0xFF; }
label_94FD:;
    /* $94FD: A8 */ nes_instruction_boundary(0x94FD, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_94FE:;
    /* $94FE: E8 */ nes_instruction_boundary(0x94FE, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_94FF:;
    /* $94FF: E0 */ nes_instruction_boundary(0x94FF, 2); { int r=g_cpu.X-0x0D; g_cpu.C=(g_cpu.X>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_9501:;
    /* $9501: 90 */ nes_instruction_boundary(0x9501, 2); if (!g_cpu.C) {
    nes_instruction_boundary(0x94E0, 2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_94E0;
    }
label_9503:;
    /* $9503: 60 */ nes_instruction_boundary(0x9503, 6); 
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
    /* $BFB9: 48 */ nes_instruction_boundary(0xBFB9, 3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_BFBA:;
    /* $BFBA: B4 */ nes_instruction_boundary(0xBFBA, 4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_BFBC:;
    /* $BFBC: E8 */ nes_instruction_boundary(0xBFBC, 2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_BFBD:;
    /* $BFBD: A9 */ nes_instruction_boundary(0xBFBD, 2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_BFBF:;
    /* $BFBF: C0 */ nes_instruction_boundary(0xBFBF, 2); { int r=g_cpu.Y-0x29; g_cpu.C=(g_cpu.Y>=0x29)?1:0; FLAG_NZ(r&0xFF); }
label_BFC1:;
    /* $BFC1: D0 */ nes_instruction_boundary(0xBFC1, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_BFC5; }
label_BFC3:;
    /* $BFC3: A9 */ nes_instruction_boundary(0xBFC3, 2); g_cpu.A = 0x09; FLAG_NZ(g_cpu.A);
label_BFC5:; /* SetDplSpd */
    /* $BFC5: 85 */ nes_instruction_boundary(0xBFC5, 3); nes_write(0x00, g_cpu.A);
label_BFC7:;
    /* $BFC7: A9 */ nes_instruction_boundary(0xBFC7, 2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_BFC9:;
    /* $BFC9: 85 */ nes_instruction_boundary(0xBFC9, 3); nes_write(0x01, g_cpu.A);
label_BFCB:;
    /* $BFCB: A9 */ nes_instruction_boundary(0xBFCB, 2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_BFCD:;
    /* $BFCD: 85 */ nes_instruction_boundary(0xBFCD, 3); nes_write(0x02, g_cpu.A);
label_BFCF:;
    /* $BFCF: 68 */ nes_instruction_boundary(0xBFCF, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_BFD0:;
    /* $BFD0: A8 */ nes_instruction_boundary(0xBFD0, 2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_BFD1:; /* RedPTroopaGrav */
    /* $BFD1: 20 */ nes_instruction_boundary(0xBFD1, 6); func_BFD7_b0();
label_BFD4:;
    /* $BFD4: A6 */ nes_instruction_boundary(0xBFD4, 3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_BFD6:;
    /* $BFD6: 60 */ nes_instruction_boundary(0xBFD6, 6); 
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
    /* $852C: 1E */ nes_instruction_boundary(0x852C, 7); { uint16_t a=(0xC901 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_852F:;
    /* $852F: 18 */ nes_instruction_boundary(0x852F, 2); g_cpu.C = 0;
label_8530:;
    /* $8530: 90 */ nes_instruction_boundary(0x8530, 2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_8537; }
label_8532:;
    /* $8532: E9 */ nes_instruction_boundary(0x8532, 2); { uint8_t m=0x01; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8534:;
    /* $8534: 9D */ nes_instruction_boundary(0x8534, 5); nes_write((0x011E + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8537:; /* SetupNumSpr */
    /* $8537: BD */ nes_instruction_boundary(0x8537, 4); g_cpu.A = nes_read((0x011E + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_853A:;
    /* $853A: E9 */ nes_instruction_boundary(0x853A, 2); { uint8_t m=0x08; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_853C:;
    /* $853C: 20 */ nes_instruction_boundary(0x853C, 6); func_E5C1();
label_853F:;
    /* $853F: BD */ nes_instruction_boundary(0x853F, 4); g_cpu.A = nes_read((0x0117 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8542:;
    /* $8542: 99 */ nes_instruction_boundary(0x8542, 5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8545:;
    /* $8545: 18 */ nes_instruction_boundary(0x8545, 2); g_cpu.C = 0;
label_8546:;
    /* $8546: 69 */ nes_instruction_boundary(0x8546, 2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_8548:;
    /* $8548: 99 */ nes_instruction_boundary(0x8548, 5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_854B:;
    /* $854B: A9 */ nes_instruction_boundary(0x854B, 2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_854D:;
    /* $854D: 99 */ nes_instruction_boundary(0x854D, 5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8550:;
    /* $8550: 99 */ nes_instruction_boundary(0x8550, 5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8553:;
    /* $8553: BD */ nes_instruction_boundary(0x8553, 4); g_cpu.A = nes_read((0x0110 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8556:;
    /* $8556: 0A */ nes_instruction_boundary(0x8556, 2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8557:;
    /* $8557: AA */ nes_instruction_boundary(0x8557, 2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_8558:;
    /* $8558: BD */ nes_instruction_boundary(0x8558, 4); g_cpu.A = nes_read((0x849F + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_855B:;
    /* $855B: 99 */ nes_instruction_boundary(0x855B, 5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_855E:;
    /* $855E: BD */ nes_instruction_boundary(0x855E, 4); g_cpu.A = nes_read((0x84A0 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8561:;
    /* $8561: 99 */ nes_instruction_boundary(0x8561, 5); nes_write((0x0205 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8564:;
    /* $8564: A6 */ nes_instruction_boundary(0x8564, 3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_8566:;
    /* $8566: 60 */ nes_instruction_boundary(0x8566, 6); 
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
    /* $8422: 11 */ nes_instruction_boundary(0x8422, 5); g_cpu.A |= nes_read((nes_read16zp(0xC8) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8424:;
    /* $8424: AD */ nes_instruction_boundary(0x8424, 4); g_cpu.A = nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_8427:;
    /* $8427: C9 */ nes_instruction_boundary(0x8427, 2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_8429:;
    /* $8429: F0 */ nes_instruction_boundary(0x8429, 2); if (g_cpu.Z) { maybe_trigger_vblank(1); goto label_8434; }
label_842B:;
    /* $842B: 88 */ nes_instruction_boundary(0x842B, 2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_842C:;
    /* $842C: C0 */ nes_instruction_boundary(0x842C, 2); { int r=g_cpu.Y-0x04; g_cpu.C=(g_cpu.Y>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_842E:;
    /* $842E: B0 */ nes_instruction_boundary(0x842E, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_8456; }
label_8430:;
    /* $8430: C0 */ nes_instruction_boundary(0x8430, 2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_8432:;
    /* $8432: B0 */ nes_instruction_boundary(0x8432, 2); if (g_cpu.C) { maybe_trigger_vblank(1); goto label_8443; }
label_8434:; /* EvalForMusic */
    /* $8434: C0 */ nes_instruction_boundary(0x8434, 2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_8436:;
    /* $8436: D0 */ nes_instruction_boundary(0x8436, 2); if (!g_cpu.Z) { maybe_trigger_vblank(1); goto label_843C; }
label_8438:;
    /* $8438: A9 */ nes_instruction_boundary(0x8438, 2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_843A:;
    /* $843A: 85 */ nes_instruction_boundary(0x843A, 3); nes_write(0xFC, g_cpu.A);
label_843C:; /* PrintMsg */
    /* $843C: 98 */ nes_instruction_boundary(0x843C, 2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_843D:;
    /* $843D: 18 */ nes_instruction_boundary(0x843D, 2); g_cpu.C = 0;
label_843E:;
    /* $843E: 69 */ nes_instruction_boundary(0x843E, 2); { uint16_t r = g_cpu.A + 0x0C + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0C); g_cpu.A=r&0xFF; }
label_8440:;
    /* $8440: 8D */ nes_instruction_boundary(0x8440, 4); nes_write(0x0773, g_cpu.A);
label_8443:; /* IncMsgCounter */
    /* $8443: AD */ nes_instruction_boundary(0x8443, 4); g_cpu.A = nes_read(0x0749); FLAG_NZ(g_cpu.A);
label_8446:;
    /* $8446: 18 */ nes_instruction_boundary(0x8446, 2); g_cpu.C = 0;
label_8447:;
    /* $8447: 69 */ nes_instruction_boundary(0x8447, 2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_8449:;
    /* $8449: 8D */ nes_instruction_boundary(0x8449, 4); nes_write(0x0749, g_cpu.A);
label_844C:;
    /* $844C: AD */ nes_instruction_boundary(0x844C, 4); g_cpu.A = nes_read(0x0719); FLAG_NZ(g_cpu.A);
label_844F:;
    /* $844F: 69 */ nes_instruction_boundary(0x844F, 2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_8451:;
    /* $8451: 8D */ nes_instruction_boundary(0x8451, 4); nes_write(0x0719, g_cpu.A);
label_8454:;
    /* $8454: C9 */ nes_instruction_boundary(0x8454, 2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_8456:; /* SetEndTimer */
    /* $8456: 90 */ nes_instruction_boundary(0x8456, 2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_8460; }
label_8458:;
    /* $8458: A9 */ nes_instruction_boundary(0x8458, 2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_845A:;
    /* $845A: 8D */ nes_instruction_boundary(0x845A, 4); nes_write(0x07A1, g_cpu.A);
label_845D:; /* IncModeTask_A */
    /* $845D: EE */ nes_instruction_boundary(0x845D, 6); { uint16_t a=0x0772; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8460:; /* ExitMsgs */
    /* $8460: 60 */ nes_instruction_boundary(0x8460, 6); 
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
    /* $8224: 04 */ nes_instruction_boundary(0x8224, 3); (void)nes_read(0xA9); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_8226:;
    /* $8226: F8 */ nes_instruction_boundary(0x8226, 2); g_cpu.D = 1;
label_8227:; /* SprInitLoop */
    /* $8227: 99 */ nes_instruction_boundary(0x8227, 5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_822A:;
    /* $822A: C8 */ nes_instruction_boundary(0x822A, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822B:;
    /* $822B: C8 */ nes_instruction_boundary(0x822B, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822C:;
    /* $822C: C8 */ nes_instruction_boundary(0x822C, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822D:;
    /* $822D: C8 */ nes_instruction_boundary(0x822D, 2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822E:;
    /* $822E: D0 */ nes_instruction_boundary(0x822E, 2); if (!g_cpu.Z) {
    nes_instruction_boundary(0x8227, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8227;
    }
label_8230:;
    /* $8230: 60 */ nes_instruction_boundary(0x8230, 6); 
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
    /* $85AF: 85 */ nes_instruction_boundary(0x85AF, 3); nes_write(0x68, g_cpu.A);
label_85B1:;
    /* $85B1: 8D */ nes_instruction_boundary(0x85B1, 4); nes_write(0x0756, g_cpu.A);
label_85B4:;
    /* $85B4: 68 */ nes_instruction_boundary(0x85B4, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_85B5:;
    /* $85B5: 8D */ nes_instruction_boundary(0x85B5, 4); nes_write(0x0744, g_cpu.A);
label_85B8:;
    /* $85B8: 4C */ nes_instruction_boundary(0x85B8, 3); nes_cpu_instruction_boundary(0x8745, 2); func_8745_b0(); return;
}

void func_85AD_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_85AD_b0");
#endif
label_85AD:;
    /* $85AD: 20 */ nes_instruction_boundary(0x85AD, 6); func_85F1_b0();
label_85B0:;
    /* $85B0: 68 */ nes_instruction_boundary(0x85B0, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_85B1:;
    /* $85B1: 8D */ nes_instruction_boundary(0x85B1, 4); nes_write(0x0756, g_cpu.A);
label_85B4:;
    /* $85B4: 68 */ nes_instruction_boundary(0x85B4, 4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_85B5:;
    /* $85B5: 8D */ nes_instruction_boundary(0x85B5, 4); nes_write(0x0744, g_cpu.A);
label_85B8:;
    /* $85B8: 4C */ nes_instruction_boundary(0x85B8, 3); nes_cpu_instruction_boundary(0x8745, 2); func_8745_b0(); return;
}

void func_830C_b0(void) {
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_push("func_830C_b0");
#endif
label_830C:;
    /* $830C: FA */ nes_instruction_boundary(0x830C, 2); /* NOP */
label_830D:; /* ExitMenu */
    /* $830D: 60 */ nes_instruction_boundary(0x830D, 6); 
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
    /* $9A99: 04 */ nes_instruction_boundary(0x9A99, 3); (void)nes_read(0xE8); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_9A9B:;
    /* $9A9B: E0 */ nes_instruction_boundary(0x9A9B, 2); { int r=g_cpu.X-0x06; g_cpu.C=(g_cpu.X>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_9A9D:;
    /* $9A9D: 90 */ nes_instruction_boundary(0x9A9D, 2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_9AA1; }
label_9A9F:;
    /* $9A9F: A2 */ nes_instruction_boundary(0x9A9F, 2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_9AA1:; /* StrCOffset */
    /* $9AA1: 8E */ nes_instruction_boundary(0x9AA1, 4); nes_write(0x046A, g_cpu.X);
label_9AA4:;
    /* $9AA4: 60 */ nes_instruction_boundary(0x9AA4, 6); 
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
    /* $909B: 38 */ nes_instruction_boundary(0x909B, 2); g_cpu.C = 1;
label_909C:;
    /* $909C: 8D */ nes_instruction_boundary(0x909C, 4); nes_write(0x06E3, g_cpu.A);
label_909F:;
    /* $909F: A9 */ nes_instruction_boundary(0x909F, 2); g_cpu.A = 0x48; FLAG_NZ(g_cpu.A);
label_90A1:;
    /* $90A1: 8D */ nes_instruction_boundary(0x90A1, 4); nes_write(0x06E2, g_cpu.A);
label_90A4:;
    /* $90A4: A9 */ nes_instruction_boundary(0x90A4, 2); g_cpu.A = 0x58; FLAG_NZ(g_cpu.A);
label_90A6:;
    /* $90A6: 8D */ nes_instruction_boundary(0x90A6, 4); nes_write(0x06E1, g_cpu.A);
label_90A9:;
    /* $90A9: A2 */ nes_instruction_boundary(0x90A9, 2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_90AB:; /* ShufAmtLoop */
    /* $90AB: BD */ nes_instruction_boundary(0x90AB, 4); g_cpu.A = nes_read((0x8FBC + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_90AE:;
    /* $90AE: 9D */ nes_instruction_boundary(0x90AE, 5); nes_write((0x06E4 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_90B1:;
    /* $90B1: CA */ nes_instruction_boundary(0x90B1, 2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_90B2:;
    /* $90B2: 10 */ nes_instruction_boundary(0x90B2, 2); if (!g_cpu.N) {
    nes_instruction_boundary(0x90AB, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_90AB;
    }
label_90B4:;
    /* $90B4: A0 */ nes_instruction_boundary(0x90B4, 2); g_cpu.Y = 0x03; FLAG_NZ(g_cpu.Y);
label_90B6:; /* ISpr0Loop */
    /* $90B6: B9 */ nes_instruction_boundary(0x90B6, 4); g_cpu.A = nes_read((0x8FCB + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_90B9:;
    /* $90B9: 99 */ nes_instruction_boundary(0x90B9, 5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_90BC:;
    /* $90BC: 88 */ nes_instruction_boundary(0x90BC, 2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_90BD:;
    /* $90BD: 10 */ nes_instruction_boundary(0x90BD, 2); if (!g_cpu.N) {
    nes_instruction_boundary(0x90B6, 1);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_90B6;
    }
label_90BF:;
    /* $90BF: 20 */ nes_instruction_boundary(0x90BF, 6); func_92AF_b0();
label_90C2:;
    /* $90C2: 20 */ nes_instruction_boundary(0x90C2, 6); func_92AA_b0();
label_90C5:;
    /* $90C5: EE */ nes_instruction_boundary(0x90C5, 6); { uint16_t a=0x0722; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_90C8:;
    /* $90C8: EE */ nes_instruction_boundary(0x90C8, 6); { uint16_t a=0x0772; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_90CB:;
    /* $90CB: 60 */ nes_instruction_boundary(0x90CB, 6); 
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
    /* $B308: 5F */ nes_instruction_boundary(0xB308, 7); { uint16_t a=(0xAD07 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); g_cpu.A^=v; FLAG_NZ(g_cpu.A); }
label_B30B:;
    /* $B30B: 48 */ nes_instruction_boundary(0xB30B, 3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_B30C:;
    /* $B30C: 07 */ nes_instruction_boundary(0xB30C, 5); { uint16_t a=0xD9; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); g_cpu.A|=v; FLAG_NZ(g_cpu.A); }
label_B30E:;
    /* $B30E: C2 */ nes_instruction_boundary(0xB30E, 2); /* NOP */
label_B310:;
    /* $B310: 90 */ nes_instruction_boundary(0xB310, 2); if (!g_cpu.C) { maybe_trigger_vblank(1); goto label_B315; }
label_B312:;
    /* $B312: EE */ nes_instruction_boundary(0xB312, 6); { uint16_t a=0x075D; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B315:; /* NextArea */
    /* $B315: EE */ nes_instruction_boundary(0xB315, 6); { uint16_t a=0x0760; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B318:;
    /* $B318: 20 */ nes_instruction_boundary(0xB318, 6); func_9C03_b0();
label_B31B:;
    /* $B31B: EE */ nes_instruction_boundary(0xB31B, 6); { uint16_t a=0x0757; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B31E:;
    /* $B31E: 20 */ nes_instruction_boundary(0xB31E, 6); func_B213_b0();
label_B321:;
    /* $B321: 8D */ nes_instruction_boundary(0xB321, 4); nes_write(0x075B, g_cpu.A);
label_B324:;
    /* $B324: A9 */ nes_instruction_boundary(0xB324, 2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_B326:;
    /* $B326: 85 */ nes_instruction_boundary(0xB326, 3); nes_write(0xFC, g_cpu.A);
label_B328:; /* ExitNA */
    /* $B328: 60 */ nes_instruction_boundary(0xB328, 6); 
#ifdef RECOMP_STACK_TRACKING
    recomp_stack_pop();
#endif
    return;
}

