/* super-mario-bros_full_bank01_part13.c — PRG bank 1 function bodies (sub-part 13).
 * STANDALONE translation unit — compiled independently (in
 * parallel with every other bank part/sub-part and the
 * umbrella super-mario-bros_full.c). Do not compile as part of another TU or
 * edit directly; the source of truth is the recompiler's
 * code_generator.c. Renamed to drop the _partNN suffix if
 * this bank turned out to fit in a single sub-part. */

#include "super-mario-bros_full_decls.h"

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

