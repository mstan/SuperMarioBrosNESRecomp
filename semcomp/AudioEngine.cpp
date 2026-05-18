// semcomp/AudioEngine.cpp — bulk-ported routines (auto-generated).
#include "semcomp/AudioEngine.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

void AudioEngine::square1_sfx_handler() {
    (void)state_;
label_F41B:; /* Square1SfxHandler */
    /* $F41B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFF); FLAG_NZ(g_cpu.Y);
label_F41D:;
    /* $F41D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F43F;
label_F41F:;
    /* $F41F: 84 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.Y);
label_F421:;
    /* $F421: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xF3CD); return; }
label_F423:;
    /* $F423: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F425:;
    /* $F425: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF3D1); return; }
label_F427:;
    /* $F427: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F429:;
    /* $F429: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF3FF); return; }
label_F42B:;
    /* $F42B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F42D:;
    /* $F42D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F45B;
label_F42F:;
    /* $F42F: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F431:;
    /* $F431: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F47D;
label_F433:;
    /* $F433: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F435:;
    /* $F435: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F4B6;
label_F437:;
    /* $F437: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F439:;
    /* $F439: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF3F9); return; }
label_F43B:;
    /* $F43B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F43D:;
    /* $F43D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF3BF); return; }
label_F43F:; /* CheckSfx1Buffer */
    /* $F43F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_F441:;
    /* $F441: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F45A;
label_F443:;
    /* $F443: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xF3DF); return; }
label_F445:;
    /* $F445: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F446:;
    /* $F446: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF3DF); return; }
label_F448:;
    /* $F448: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F449:;
    /* $F449: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF40D); return; }
label_F44B:;
    /* $F44B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F44C:;
    /* $F44C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F469;
label_F44E:;
    /* $F44E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F44F:;
    /* $F44F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F48D;
label_F451:;
    /* $F451: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F452:;
    /* $F452: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F4BB;
label_F454:;
    /* $F454: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F455:;
    /* $F455: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF40D); return; }
label_F457:;
    /* $F457: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F458:;
    /* $F458: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F4A2;
label_F45A:; /* ExS1H */
    /* $F45A: 60 */
    return; /* branch-target RTS */
label_F45B:; /* PlaySwimStomp */
    /* $F45B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_F45D:;
    /* $F45D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_F460:;
    /* $F460: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x9C; FLAG_NZ(g_cpu.Y);
label_F462:;
    /* $F462: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_F464:;
    /* $F464: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_F466:;
    /* $F466: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_F469:; /* ContinueSwimStomp */
    /* $F469: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_F46C:;
    /* $F46C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F46F:;
    /* $F46F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F472:;
    /* $F472: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_F474:;
    /* $F474: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F47B;
label_F476:;
    /* $F476: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9E; FLAG_NZ(g_cpu.A);
label_F478:;
    /* $F478: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_F47B:; /* BranchToDecLength1 */
    /* $F47B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F4A2;
label_F47D:; /* PlaySmackEnemy */
    /* $F47D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_F47F:;
    /* $F47F: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xCB; FLAG_NZ(g_cpu.Y);
label_F481:;
    /* $F481: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_F483:;
    /* $F483: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_F486:;
    /* $F486: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_F488:;
    /* $F488: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_F48B:;
    /* $F48B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F4A2;
label_F48D:; /* ContinueSmackEnemy */
    /* $F48D: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_F490:;
    /* $F490: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_F492:;
    /* $F492: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F49D;
label_F494:;
    /* $F494: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA0; FLAG_NZ(g_cpu.A);
label_F496:;
    /* $F496: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_F499:;
    /* $F499: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9F; FLAG_NZ(g_cpu.A);
label_F49B:;
    /* $F49B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F49F;
label_F49D:; /* SmSpc */
    /* $F49D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_F49F:; /* SmTick */
    /* $F49F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F4A2:; /* DecrementSfx1Length */
    /* $F4A2: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F4A5:;
    /* $F4A5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F4B5;
label_F4A7:; /* StopSquare1Sfx */
    /* $F4A7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_F4A9:;
    /* $F4A9: 86 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.X);
label_F4AB:;
    /* $F4AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_F4AD:;
    /* $F4AD: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_F4B0:;
    /* $F4B0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_F4B2:;
    /* $F4B2: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_F4B5:; /* ExSfx1 */
    /* $F4B5: 60 */ maybe_trigger_vblank(6);
    return;
label_F4B6:; /* PlayPipeDownInj */
    /* $F4B6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_F4B8:;
    /* $F4B8: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_F4BB:; /* ContinuePipeDownInj */
    /* $F4BB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_F4BE:;
    /* $F4BE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F4BF:;
    /* $F4BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F4D1;
label_F4C1:;
    /* $F4C1: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F4C2:;
    /* $F4C2: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F4D1;
label_F4C4:;
    /* $F4C4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_F4C6:;
    /* $F4C6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F4D1;
label_F4C8:;
    /* $F4C8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_F4CA:;
    /* $F4CA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_F4CC:;
    /* $F4CC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_F4CE:;
    /* $F4CE: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_F4D1:; /* NoPDwnL */
    /* $F4D1: 4C */ maybe_trigger_vblank(3); goto label_F4A2;
}

void AudioEngine::square2_sfx_handler() {
    (void)state_;
label_F57C:; /* Square2SfxHandler */
    /* $F57C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_F57E:;
    /* $F57E: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_F580:;
    /* $F580: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F5E7;
label_F582:;
    /* $F582: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFE); FLAG_NZ(g_cpu.Y);
label_F584:;
    /* $F584: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F5A6;
label_F586:;
    /* $F586: 84 */ maybe_trigger_vblank(3); nes_write(0xF2, g_cpu.Y);
label_F588:;
    /* $F588: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_F5C8;
label_F58A:;
    /* $F58A: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F58C:;
    /* $F58C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF518); return; }
label_F58E:;
    /* $F58E: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F590:;
    /* $F590: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5FC;
label_F592:;
    /* $F592: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F594:;
    /* $F594: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F600;
label_F596:;
    /* $F596: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F598:;
    /* $F598: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF53A); return; }
label_F59A:;
    /* $F59A: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F59C:;
    /* $F59C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF51E); return; }
label_F59E:;
    /* $F59E: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F5A0:;
    /* $F5A0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF552); return; }
label_F5A2:;
    /* $F5A2: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F5A4:;
    /* $F5A4: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5E2;
label_F5A6:; /* CheckSfx2Buffer */
    /* $F5A6: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_F5A8:;
    /* $F5A8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F5C1;
label_F5AA:;
    /* $F5AA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_F5D3;
label_F5AC:;
    /* $F5AC: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5AD:;
    /* $F5AD: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5C2;
label_F5AF:;
    /* $F5AF: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B0:;
    /* $F5B0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F60F;
label_F5B2:;
    /* $F5B2: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B3:;
    /* $F5B3: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F60F;
label_F5B5:;
    /* $F5B5: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B6:;
    /* $F5B6: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF545); return; }
label_F5B8:;
    /* $F5B8: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B9:;
    /* $F5B9: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5C2;
label_F5BB:;
    /* $F5BB: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5BC:;
    /* $F5BC: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF557); return; }
label_F5BE:;
    /* $F5BE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5BF:;
    /* $F5BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5E7;
label_F5C1:; /* ExS2H */
    /* $F5C1: 60 */ maybe_trigger_vblank(6);
    return;
label_F5C2:; /* Cont_CGrab_TTick */
    /* $F5C2: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF52C); return;
label_F5C5:; /* JumpToDecLength2 */
    /* $F5C5: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF568); return;
label_F5C8:; /* PlayBowserFall */
    /* $F5C8: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x38; FLAG_NZ(g_cpu.A);
label_F5CA:;
    /* $F5CA: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F5CD:;
    /* $F5CD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xC4; FLAG_NZ(g_cpu.Y);
label_F5CF:;
    /* $F5CF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_F5D1:; /* BlstSJp */
    /* $F5D1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F5DE;
label_F5D3:; /* ContinueBowserFall */
    /* $F5D3: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F5D6:;
    /* $F5D6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_F5D8:;
    /* $F5D8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xF568); return; }
label_F5DA:;
    /* $F5DA: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xA4; FLAG_NZ(g_cpu.Y);
label_F5DC:;
    /* $F5DC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x5A; FLAG_NZ(g_cpu.A);
label_F5DE:; /* PBFRegs */
    /* $F5DE: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_F5E0:; /* EL_LRegs */
    /* $F5E0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xF565); return; }
label_F5E2:; /* PlayExtraLife */
    /* $F5E2: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x30; FLAG_NZ(g_cpu.A);
label_F5E4:;
    /* $F5E4: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F5E7:; /* ContinueExtraLife */
    /* $F5E7: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F5EA:;
    /* $F5EA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_F5EC:; /* DivLLoop */
    /* $F5EC: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5ED:;
    /* $F5ED: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F5C5;
    }
label_F5EF:;
    /* $F5EF: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_F5F0:;
    /* $F5F0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F5EC;
    }
label_F5F2:;
    /* $F5F2: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F5F3:;
    /* $F5F3: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF4D3 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F5F6:;
    /* $F5F6: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x82; FLAG_NZ(g_cpu.X);
label_F5F8:;
    /* $F5F8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_F5FA:;
    /* $F5FA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F5E0;
    }
label_F5FC:; /* PlayGrowPowerUp */
    /* $F5FC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_F5FE:;
    /* $F5FE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F602;
label_F600:; /* PlayGrowVine */
    /* $F600: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_F602:; /* GrowItemRegs */
    /* $F602: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F605:;
    /* $F605: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x7F; FLAG_NZ(g_cpu.A);
label_F607:;
    /* $F607: 8D */ maybe_trigger_vblank(4); nes_write(0x4005, g_cpu.A);
label_F60A:;
    /* $F60A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F60C:;
    /* $F60C: 8D */ maybe_trigger_vblank(4); nes_write(0x07BE, g_cpu.A);
label_F60F:; /* ContinueGrowItems */
    /* $F60F: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07BE; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F612:;
    /* $F612: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BE); FLAG_NZ(g_cpu.A);
label_F615:;
    /* $F615: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F616:;
    /* $F616: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F617:;
    /* $F617: CC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x07BD); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_F61A:;
    /* $F61A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F628;
label_F61C:;
    /* $F61C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9D; FLAG_NZ(g_cpu.A);
label_F61E:;
    /* $F61E: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_F621:;
    /* $F621: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF4F8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F624:;
    /* $F624: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3A9);
label_F627:;
    /* $F627: 60 */ maybe_trigger_vblank(6);
    return;
label_F628:; /* StopGrowItems */
    /* $F628: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF56D); return;
}

void AudioEngine::sound_engine() {
    sound_engine_body(0);
}

void AudioEngine::at_f2d3() {
    sound_engine_body(1);
}

void AudioEngine::at_f2ea() {
    sound_engine_body(2);
}

void AudioEngine::at_f2f3() {
    sound_engine_body(3);
}

void AudioEngine::at_f329() {
    sound_engine_body(4);
}

void AudioEngine::at_f380() {
    sound_engine_body(5);
}

void AudioEngine::at_f367() {
    sound_engine_body(6);
}

void AudioEngine::no_inc_dac() {
    sound_engine_body(7);
}

void AudioEngine::dump_squ1_regs() {
    dump_squ1_regs_body(0);
}

void AudioEngine::at_f384() {
    dump_squ1_regs_body(1);
}

void AudioEngine::play_squ1_sfx() {
    play_squ1_sfx_body(0);
}

void AudioEngine::at_f38e() {
    play_squ1_sfx_body(1);
}

void AudioEngine::dump_sq2_regs() {
    dump_sq2_regs_body(0);
}

void AudioEngine::at_f3a5() {
    dump_sq2_regs_body(1);
}

void AudioEngine::play_squ2_sfx() {
    play_squ2_sfx_body(0);
}

void AudioEngine::no_p_dwn_l() {
    play_squ2_sfx_body(1);
}

void AudioEngine::at_f410() {
    play_squ2_sfx_body(2);
}

void AudioEngine::at_f4b0() {
    play_squ2_sfx_body(3);
}

void AudioEngine::fps2nd() {
    play_squ2_sfx_body(4);
}

void AudioEngine::dmp_jp_fps() {
    play_squ2_sfx_body(5);
}

void AudioEngine::at_f4be() {
    play_squ2_sfx_body(6);
}

void AudioEngine::at_f4bf() {
    play_squ2_sfx_body(7);
}

void AudioEngine::at_f4a5() {
    play_squ2_sfx_body(8);
}

void AudioEngine::at_f405() {
    play_squ2_sfx_body(9);
}

void AudioEngine::at_f486() {
    play_squ2_sfx_body(10);
}

void AudioEngine::at_f421() {
    play_squ2_sfx_body(11);
}

void AudioEngine::at_f3ee() {
    play_squ2_sfx_body(12);
}

void AudioEngine::at_f490() {
    play_squ2_sfx_body(13);
}

void AudioEngine::at_f462() {
    play_squ2_sfx_body(14);
}

void AudioEngine::at_f4a9() {
    play_squ2_sfx_body(15);
}

void AudioEngine::at_f44c() {
    play_squ2_sfx_body(16);
}

void AudioEngine::play_coin_grab() {
    play_coin_grab_body(0);
}

void AudioEngine::blst_s_jp() {
    play_coin_grab_body(1);
}

void AudioEngine::grow_item_regs() {
    play_coin_grab_body(2);
}

void AudioEngine::n2_tone() {
    play_coin_grab_body(3);
}

void AudioEngine::at_f607() {
    play_coin_grab_body(4);
}

void AudioEngine::at_f621() {
    play_coin_grab_body(5);
}

void AudioEngine::at_f5f6() {
    play_coin_grab_body(6);
}

void AudioEngine::play_grow_power_up() {
    play_coin_grab_body(7);
}

void AudioEngine::at_f624() {
    play_coin_grab_body(8);
}

void AudioEngine::at_f586() {
    play_coin_grab_body(9);
}

void AudioEngine::at_f5b2() {
    play_coin_grab_body(10);
}

void AudioEngine::at_f5f8() {
    play_coin_grab_body(11);
}

void AudioEngine::at_f5ed() {
    play_coin_grab_body(12);
}

void AudioEngine::jump_to_dec_length2() {
    play_coin_grab_body(13);
}

void AudioEngine::el_l_regs() {
    play_coin_grab_body(14);
}

void AudioEngine::at_f5cf() {
    play_coin_grab_body(15);
}

void AudioEngine::div_l_loop() {
    play_coin_grab_body(16);
}

void AudioEngine::at_f5b9() {
    play_coin_grab_body(17);
}

void AudioEngine::at_f605() {
    play_coin_grab_body(18);
}

void AudioEngine::c_grab_t_tick_reg_l() {
    play_coin_grab_body(19);
}

void AudioEngine::at_f617() {
    play_coin_grab_body(20);
}

void AudioEngine::play_brick_shatter() {
    play_brick_shatter_body(0);
}

void AudioEngine::decrement_sfx3_length() {
    play_brick_shatter_body(1);
}

void AudioEngine::at_f644() {
    play_brick_shatter_body(2);
}

void AudioEngine::noise_sfx_handler() {
    noise_sfx_handler_body(0);
}

void AudioEngine::continue_bowser_flame() {
    noise_sfx_handler_body(1);
}

void AudioEngine::at_f679() {
    noise_sfx_handler_body(2);
}

void AudioEngine::at_f68f() {
    noise_sfx_handler_body(3);
}

void AudioEngine::music_handler() {
    music_handler_body(0);
}

void AudioEngine::silent_beat() {
    music_handler_body(1);
}

void AudioEngine::at_f7c3() {
    music_handler_body(2);
}

void AudioEngine::at_f860() {
    music_handler_body(3);
}

void AudioEngine::strong_beat() {
    music_handler_body(4);
}

void AudioEngine::find_event_music_header() {
    music_handler_body(5);
}

void AudioEngine::at_f80d() {
    music_handler_body(6);
}

void AudioEngine::at_f720() {
    music_handler_body(7);
}

void AudioEngine::at_f710() {
    music_handler_body(8);
}

void AudioEngine::at_f6a1() {
    music_handler_body(9);
}

void AudioEngine::at_f8ad() {
    music_handler_body(10);
}

void AudioEngine::at_f829() {
    music_handler_body(11);
}

void AudioEngine::at_f750() {
    music_handler_body(12);
}

void AudioEngine::at_f6fc() {
    music_handler_body(13);
}

void AudioEngine::at_f7a9() {
    music_handler_body(14);
}

void AudioEngine::death_m_alt_reg() {
    music_handler_body(15);
}

void AudioEngine::at_f784() {
    music_handler_body(16);
}

void AudioEngine::at_f885() {
    music_handler_body(17);
}

void AudioEngine::squ2_note_handler() {
    music_handler_body(18);
}

void AudioEngine::at_f7a5() {
    music_handler_body(19);
}

void AudioEngine::at_f7e6() {
    music_handler_body(20);
}

void AudioEngine::at_f7e7() {
    music_handler_body(21);
}

void AudioEngine::at_f8a5() {
    music_handler_body(22);
}

void AudioEngine::at_f7e4() {
    music_handler_body(23);
}

void AudioEngine::misc_squ1_music_tasks() {
    music_handler_body(24);
}

void AudioEngine::skip_ctrl_l() {
    music_handler_body(25);
}

void AudioEngine::load_header() {
    music_handler_body(26);
}

void AudioEngine::fetch_noise_beat_data() {
    music_handler_body(27);
}

void AudioEngine::at_f6b8() {
    music_handler_body(28);
}

void AudioEngine::at_f7fb() {
    music_handler_body(29);
}

void AudioEngine::at_f850() {
    music_handler_body(30);
}

void AudioEngine::at_f88d() {
    music_handler_body(31);
}

void AudioEngine::at_f6b6() {
    music_handler_body(32);
}

void AudioEngine::medi_n() {
    music_handler_body(33);
}

void AudioEngine::at_f862() {
    music_handler_body(34);
}

void AudioEngine::at_f741() {
    music_handler_body(35);
}

void AudioEngine::at_f844() {
    music_handler_body(36);
}

void AudioEngine::at_f807() {
    music_handler_body(37);
}

void AudioEngine::at_f706() {
    music_handler_body(38);
}

void AudioEngine::at_f729() {
    music_handler_body(39);
}

void AudioEngine::alternate_length_handler() {
    alternate_length_handler_body(0);
}

void AudioEngine::at_f8d0() {
    alternate_length_handler_body(1);
}

void AudioEngine::at_f8c9() {
    alternate_length_handler_body(2);
}

void AudioEngine::at_f8ca() {
    alternate_length_handler_body(3);
}

void AudioEngine::at_f8c6() {
    alternate_length_handler_body(4);
}

void AudioEngine::at_f8ce() {
    alternate_length_handler_body(5);
}

void AudioEngine::at_f8c8() {
    alternate_length_handler_body(6);
}

void AudioEngine::load_control_regs() {
    load_control_regs_body(0);
}

void AudioEngine::at_f8f1() {
    load_control_regs_body(1);
}

void AudioEngine::at_f8e7() {
    load_control_regs_body(2);
}

void AudioEngine::load_envelope_data() {
    load_envelope_data_body(0);
}

void AudioEngine::at_f8fb() {
    load_envelope_data_body(1);
}

void AudioEngine::at_f90c() {
    load_envelope_data_body(2);
}

void AudioEngine::at_f903() {
    load_envelope_data_body(3);
}

void AudioEngine::at_f905() {
    load_envelope_data_body(4);
}

void AudioEngine::sound_engine_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F2D3;
        case 2: goto label_F2EA;
        case 3: goto label_F2F3;
        case 4: goto label_F329;
        case 5: goto label_F380;
        case 6: goto label_F367;
        case 7: goto label_F377;
    }
label_F2D0:; /* SoundEngine */
    /* $F2D0: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0770); FLAG_NZ(g_cpu.A);
label_F2D3:;
    /* $F2D3: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F2D9;
label_F2D5:;
    /* $F2D5: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_F2D8:;
    /* $F2D8: 60 */ maybe_trigger_vblank(6);
    return;
label_F2D9:; /* SndOn */
    /* $F2D9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_F2DB:;
    /* $F2DB: 8D */ maybe_trigger_vblank(4); nes_write(0x4017, g_cpu.A);
label_F2DE:;
    /* $F2DE: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0F; FLAG_NZ(g_cpu.A);
label_F2E0:;
    /* $F2E0: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_F2E3:;
    /* $F2E3: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07C6); FLAG_NZ(g_cpu.A);
label_F2E6:;
    /* $F2E6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F2EE;
label_F2E8:;
    /* $F2E8: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xFA); FLAG_NZ(g_cpu.A);
label_F2EA:;
    /* $F2EA: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_F2EC:;
    /* $F2EC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F34B;
label_F2EE:; /* InPause */
    /* $F2EE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B2); FLAG_NZ(g_cpu.A);
label_F2F1:;
    /* $F2F1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F316;
label_F2F3:;
    /* $F2F3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xFA); FLAG_NZ(g_cpu.A);
label_F2F5:;
    /* $F2F5: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F35D;
label_F2F7:;
    /* $F2F7: 8D */ maybe_trigger_vblank(4); nes_write(0x07B2, g_cpu.A);
label_F2FA:;
    /* $F2FA: 8D */ maybe_trigger_vblank(4); nes_write(0x07C6, g_cpu.A);
label_F2FD:;
    /* $F2FD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F2FF:;
    /* $F2FF: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_F302:;
    /* $F302: 85 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.A);
label_F304:;
    /* $F304: 85 */ maybe_trigger_vblank(3); nes_write(0xF2, g_cpu.A);
label_F306:;
    /* $F306: 85 */ maybe_trigger_vblank(3); nes_write(0xF3, g_cpu.A);
label_F308:;
    /* $F308: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0F; FLAG_NZ(g_cpu.A);
label_F30A:;
    /* $F30A: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_F30D:;
    /* $F30D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2A; FLAG_NZ(g_cpu.A);
label_F30F:;
    /* $F30F: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_F312:; /* PTone1F */
    /* $F312: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_F314:;
    /* $F314: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F327;
label_F316:; /* ContPau */
    /* $F316: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_F319:;
    /* $F319: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x24; g_cpu.C=(g_cpu.A>=0x24)?1:0; FLAG_NZ(r&0xFF); }
label_F31B:;
    /* $F31B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F325;
label_F31D:;
    /* $F31D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x1E; g_cpu.C=(g_cpu.A>=0x1E)?1:0; FLAG_NZ(r&0xFF); }
label_F31F:;
    /* $F31F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F312;
    }
label_F321:;
    /* $F321: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x18; g_cpu.C=(g_cpu.A>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_F323:;
    /* $F323: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F32E;
label_F325:; /* PTone2F */
    /* $F325: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x64; FLAG_NZ(g_cpu.A);
label_F327:; /* PTRegC */
    /* $F327: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x84; FLAG_NZ(g_cpu.X);
label_F329:;
    /* $F329: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_F32B:;
    /* $F32B: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_F32E:; /* DecPauC */
    /* $F32E: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F331:;
    /* $F331: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F35D;
label_F333:;
    /* $F333: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F335:;
    /* $F335: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_F338:;
    /* $F338: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B2); FLAG_NZ(g_cpu.A);
label_F33B:;
    /* $F33B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_F33D:;
    /* $F33D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F344;
label_F33F:;
    /* $F33F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F341:;
    /* $F341: 8D */ maybe_trigger_vblank(4); nes_write(0x07C6, g_cpu.A);
label_F344:; /* SkipPIn */
    /* $F344: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F346:;
    /* $F346: 8D */ maybe_trigger_vblank(4); nes_write(0x07B2, g_cpu.A);
label_F349:;
    /* $F349: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F35D;
label_F34B:; /* RunSoundSubroutines */
    /* $F34B: 20 */ maybe_trigger_vblank(6); call_by_address(0xF41B);
label_F34E:;
    /* $F34E: 20 */ maybe_trigger_vblank(6); call_by_address(0xF57C);
label_F351:;
    /* $F351: 20 */ maybe_trigger_vblank(6); call_by_address(0xF667);
label_F354:;
    /* $F354: 20 */ maybe_trigger_vblank(6); call_by_address(0xF694);
label_F357:;
    /* $F357: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F359:;
    /* $F359: 85 */ maybe_trigger_vblank(3); nes_write(0xFB, g_cpu.A);
label_F35B:;
    /* $F35B: 85 */ maybe_trigger_vblank(3); nes_write(0xFC, g_cpu.A);
label_F35D:; /* SkipSoundSubroutines */
    /* $F35D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F35F:;
    /* $F35F: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_F361:;
    /* $F361: 85 */ maybe_trigger_vblank(3); nes_write(0xFE, g_cpu.A);
label_F363:;
    /* $F363: 85 */ maybe_trigger_vblank(3); nes_write(0xFD, g_cpu.A);
label_F365:;
    /* $F365: 85 */ maybe_trigger_vblank(3); nes_write(0xFA, g_cpu.A);
label_F367:;
    /* $F367: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07C0); FLAG_NZ(g_cpu.Y);
label_F36A:;
    /* $F36A: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F36C:;
    /* $F36C: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_F36E:;
    /* $F36E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F377;
label_F370:;
    /* $F370: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07C0; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F373:;
    /* $F373: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x30; g_cpu.C=(g_cpu.Y>=0x30)?1:0; FLAG_NZ(r&0xFF); }
label_F375:;
    /* $F375: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_F37D;
label_F377:; /* NoIncDAC */
    /* $F377: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_F378:;
    /* $F378: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F37D;
label_F37A:;
    /* $F37A: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07C0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F37D:; /* StrWave */
    /* $F37D: 8C */ maybe_trigger_vblank(4); nes_write(0x4011, g_cpu.Y);
label_F380:;
    /* $F380: 60 */ maybe_trigger_vblank(6);
    return;
}

void AudioEngine::dump_squ1_regs_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F384;
    }
label_F381:; /* Dump_Squ1_Regs */
    /* $F381: 8C */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.Y);
label_F384:;
    /* $F384: 8E */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.X);
label_F387:;
    /* $F387: 60 */ maybe_trigger_vblank(6);
    return;
}

void AudioEngine::play_squ1_sfx_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F38E;
    }
label_F388:; /* PlaySqu1Sfx */
    /* $F388: 20 */ maybe_trigger_vblank(6); call_by_address(0xF381);
label_F38B:; /* SetFreq_Squ1 */
    /* $F38B: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_F38D:; /* Dump_Freq_Regs */
    /* $F38D: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F38E:;
    /* $F38E: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFF01 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F391:;
    /* $F391: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F39E;
label_F393:;
    /* $F393: 9D */ maybe_trigger_vblank(5); nes_write((0x4002 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_F396:;
    /* $F396: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFF00 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F399:;
    /* $F399: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x08; FLAG_NZ(g_cpu.A);
label_F39B:;
    /* $F39B: 9D */ maybe_trigger_vblank(5); nes_write((0x4003 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_F39E:; /* NoTone */
    /* $F39E: 60 */ maybe_trigger_vblank(6);
    return;
}

void AudioEngine::dump_sq2_regs_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F3A5;
    }
label_F39F:; /* Dump_Sq2_Regs */
    /* $F39F: 8E */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.X);
label_F3A2:;
    /* $F3A2: 8C */ maybe_trigger_vblank(4); nes_write(0x4005, g_cpu.Y);
label_F3A5:;
    /* $F3A5: 60 */ maybe_trigger_vblank(6);
    return;
}

void AudioEngine::play_squ2_sfx_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F4D1;
        case 2: goto label_F410;
        case 3: goto label_F4B0;
        case 4: goto label_F3F2;
        case 5: goto label_F3F4;
        case 6: goto label_F4BE;
        case 7: goto label_F4BF;
        case 8: goto label_F4A5;
        case 9: goto label_F405;
        case 10: goto label_F486;
        case 11: goto label_F421;
        case 12: goto label_F3EE;
        case 13: goto label_F490;
        case 14: goto label_F462;
        case 15: goto label_F4A9;
        case 16: goto label_F44C;
    }
label_F3A6:; /* PlaySqu2Sfx */
    /* $F3A6: 20 */ maybe_trigger_vblank(6); call_by_address(0xF39F);
label_F3A9:; /* SetFreq_Squ2 */
    /* $F3A9: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x04; FLAG_NZ(g_cpu.X);
label_F3AB:;
    /* $F3AB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xF38D); return; }
label_F3AD:; /* SetFreq_Tri */
    /* $F3AD: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x08; FLAG_NZ(g_cpu.X);
label_F3AF:;
    /* $F3AF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xF38D); return; }
label_F3B1:; /* SwimStompEnvelopeData */
    /* $F3B1: 9F */ maybe_trigger_vblank(5); /* ILLEGAL $9F — skip 3 */
label_F3B4:;
    /* $F3B4: 96 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.Y) & 0xFF, g_cpu.X);
label_F3B6:;
    /* $F3B6: 94 */ maybe_trigger_vblank(4); nes_write((0x92 + g_cpu.X) & 0xFF, g_cpu.Y);
label_F3B8:;
    /* $F3B8: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { call_by_address(0xF34A); return; }
label_F3BA:;
    /* $F3BA: 9A */ maybe_trigger_vblank(2); g_cpu.S = g_cpu.X;
label_F3BB:;
    /* $F3BB: 97 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.Y) & 0xFF, g_cpu.A & g_cpu.X); /* SAX */
label_F3BD:;
    /* $F3BD: 93 */ maybe_trigger_vblank(6); /* ILLEGAL $93 — skip 2 */
label_F3BF:; /* PlayFlagpoleSlide */
    /* $F3BF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_F3C1:;
    /* $F3C1: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_F3C4:;
    /* $F3C4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x62; FLAG_NZ(g_cpu.A);
label_F3C6:;
    /* $F3C6: 20 */ maybe_trigger_vblank(6); call_by_address(0xF38B);
label_F3C9:;
    /* $F3C9: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x99; FLAG_NZ(g_cpu.X);
label_F3CB:;
    /* $F3CB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F3F2;
label_F3CD:; /* PlaySmallJump */
    /* $F3CD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_F3CF:;
    /* $F3CF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F3D3;
label_F3D1:; /* PlayBigJump */
    /* $F3D1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_F3D3:; /* JumpRegContents */
    /* $F3D3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x82; FLAG_NZ(g_cpu.X);
label_F3D5:;
    /* $F3D5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xA7; FLAG_NZ(g_cpu.Y);
label_F3D7:;
    /* $F3D7: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_F3DA:;
    /* $F3DA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_F3DC:;
    /* $F3DC: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_F3DF:; /* ContinueSndJump */
    /* $F3DF: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_F3E2:;
    /* $F3E2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x25; g_cpu.C=(g_cpu.A>=0x25)?1:0; FLAG_NZ(r&0xFF); }
label_F3E4:;
    /* $F3E4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F3EC;
label_F3E6:;
    /* $F3E6: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x5F; FLAG_NZ(g_cpu.X);
label_F3E8:;
    /* $F3E8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xF6; FLAG_NZ(g_cpu.Y);
label_F3EA:;
    /* $F3EA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F3F4;
label_F3EC:; /* N2Prt */
    /* $F3EC: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_F3EE:;
    /* $F3EE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F419;
label_F3F0:;
    /* $F3F0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x48; FLAG_NZ(g_cpu.X);
label_F3F2:; /* FPS2nd */
    /* $F3F2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xBC; FLAG_NZ(g_cpu.Y);
label_F3F4:; /* DmpJpFPS */
    /* $F3F4: 20 */ maybe_trigger_vblank(6); call_by_address(0xF381);
label_F3F7:;
    /* $F3F7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F419;
label_F3F9:; /* PlayFireballThrow */
    /* $F3F9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_F3FB:;
    /* $F3FB: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x99; FLAG_NZ(g_cpu.Y);
label_F3FD:;
    /* $F3FD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F403;
label_F3FF:; /* PlayBump */
    /* $F3FF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_F401:;
    /* $F401: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_F403:; /* Fthrow */
    /* $F403: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_F405:;
    /* $F405: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_F408:;
    /* $F408: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0C; FLAG_NZ(g_cpu.A);
label_F40A:;
    /* $F40A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_F40D:; /* ContinueBumpThrow */
    /* $F40D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_F410:;
    /* $F410: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_F412:;
    /* $F412: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F419;
label_F414:;
    /* $F414: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xBB; FLAG_NZ(g_cpu.A);
label_F416:;
    /* $F416: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_F419:; /* DecJpFPS */
    /* $F419: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F47B;
label_F41B:; /* Square1SfxHandler */
    /* $F41B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFF); FLAG_NZ(g_cpu.Y);
label_F41D:;
    /* $F41D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F43F;
label_F41F:;
    /* $F41F: 84 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.Y);
label_F421:;
    /* $F421: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F3CD;
    }
label_F423:;
    /* $F423: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F425:;
    /* $F425: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F3D1;
    }
label_F427:;
    /* $F427: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F429:;
    /* $F429: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F3FF;
    }
label_F42B:;
    /* $F42B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F42D:;
    /* $F42D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F45B;
label_F42F:;
    /* $F42F: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F431:;
    /* $F431: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F47D;
label_F433:;
    /* $F433: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F435:;
    /* $F435: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F4B6;
label_F437:;
    /* $F437: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F439:;
    /* $F439: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F3F9;
    }
label_F43B:;
    /* $F43B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F43D:;
    /* $F43D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F3BF;
    }
label_F43F:; /* CheckSfx1Buffer */
    /* $F43F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_F441:;
    /* $F441: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F45A;
label_F443:;
    /* $F443: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F3DF;
    }
label_F445:;
    /* $F445: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F446:;
    /* $F446: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F3DF;
    }
label_F448:;
    /* $F448: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F449:;
    /* $F449: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F40D;
    }
label_F44B:;
    /* $F44B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F44C:;
    /* $F44C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F469;
label_F44E:;
    /* $F44E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F44F:;
    /* $F44F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F48D;
label_F451:;
    /* $F451: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F452:;
    /* $F452: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F4BB;
label_F454:;
    /* $F454: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F455:;
    /* $F455: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F40D;
    }
label_F457:;
    /* $F457: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F458:;
    /* $F458: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F4A2;
label_F45A:; /* ExS1H */
    /* $F45A: 60 */
    return; /* branch-target RTS */
label_F45B:; /* PlaySwimStomp */
    /* $F45B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_F45D:;
    /* $F45D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_F460:;
    /* $F460: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x9C; FLAG_NZ(g_cpu.Y);
label_F462:;
    /* $F462: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_F464:;
    /* $F464: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_F466:;
    /* $F466: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_F469:; /* ContinueSwimStomp */
    /* $F469: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_F46C:;
    /* $F46C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F46F:;
    /* $F46F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F472:;
    /* $F472: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_F474:;
    /* $F474: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F47B;
label_F476:;
    /* $F476: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9E; FLAG_NZ(g_cpu.A);
label_F478:;
    /* $F478: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_F47B:; /* BranchToDecLength1 */
    /* $F47B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F4A2;
label_F47D:; /* PlaySmackEnemy */
    /* $F47D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_F47F:;
    /* $F47F: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xCB; FLAG_NZ(g_cpu.Y);
label_F481:;
    /* $F481: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_F483:;
    /* $F483: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_F486:;
    /* $F486: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_F488:;
    /* $F488: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_F48B:;
    /* $F48B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F4A2;
label_F48D:; /* ContinueSmackEnemy */
    /* $F48D: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_F490:;
    /* $F490: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_F492:;
    /* $F492: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F49D;
label_F494:;
    /* $F494: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA0; FLAG_NZ(g_cpu.A);
label_F496:;
    /* $F496: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_F499:;
    /* $F499: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9F; FLAG_NZ(g_cpu.A);
label_F49B:;
    /* $F49B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F49F;
label_F49D:; /* SmSpc */
    /* $F49D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_F49F:; /* SmTick */
    /* $F49F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F4A2:; /* DecrementSfx1Length */
    /* $F4A2: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F4A5:;
    /* $F4A5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F4B5;
label_F4A7:; /* StopSquare1Sfx */
    /* $F4A7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_F4A9:;
    /* $F4A9: 86 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.X);
label_F4AB:;
    /* $F4AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_F4AD:;
    /* $F4AD: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_F4B0:;
    /* $F4B0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_F4B2:;
    /* $F4B2: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_F4B5:; /* ExSfx1 */
    /* $F4B5: 60 */ maybe_trigger_vblank(6);
    return;
label_F4B6:; /* PlayPipeDownInj */
    /* $F4B6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_F4B8:;
    /* $F4B8: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_F4BB:; /* ContinuePipeDownInj */
    /* $F4BB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_F4BE:;
    /* $F4BE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F4BF:;
    /* $F4BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F4D1;
label_F4C1:;
    /* $F4C1: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F4C2:;
    /* $F4C2: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F4D1;
label_F4C4:;
    /* $F4C4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_F4C6:;
    /* $F4C6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F4D1;
label_F4C8:;
    /* $F4C8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_F4CA:;
    /* $F4CA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_F4CC:;
    /* $F4CC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_F4CE:;
    /* $F4CE: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_F4D1:; /* NoPDwnL */
    /* $F4D1: 4C */ maybe_trigger_vblank(3); goto label_F4A2;
}

void AudioEngine::play_coin_grab_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F5D1;
        case 2: goto label_F602;
        case 3: goto label_F538;
        case 4: goto label_F607;
        case 5: goto label_F621;
        case 6: goto label_F5F6;
        case 7: goto label_F5FC;
        case 8: goto label_F624;
        case 9: goto label_F586;
        case 10: goto label_F5B2;
        case 11: goto label_F5F8;
        case 12: goto label_F5ED;
        case 13: goto label_F5C5;
        case 14: goto label_F5E0;
        case 15: goto label_F5CF;
        case 16: goto label_F5EC;
        case 17: goto label_F5B9;
        case 18: goto label_F605;
        case 19: goto label_F522;
        case 20: goto label_F617;
    }
label_F518:; /* PlayCoinGrab */
    /* $F518: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x35; FLAG_NZ(g_cpu.A);
label_F51A:;
    /* $F51A: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x8D; FLAG_NZ(g_cpu.X);
label_F51C:;
    /* $F51C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F522;
label_F51E:; /* PlayTimerTick */
    /* $F51E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_F520:;
    /* $F520: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x98; FLAG_NZ(g_cpu.X);
label_F522:; /* CGrab_TTickRegL */
    /* $F522: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F525:;
    /* $F525: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_F527:;
    /* $F527: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x42; FLAG_NZ(g_cpu.A);
label_F529:;
    /* $F529: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3A6);
label_F52C:; /* ContinueCGrabTTick */
    /* $F52C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F52F:;
    /* $F52F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x30; g_cpu.C=(g_cpu.A>=0x30)?1:0; FLAG_NZ(r&0xFF); }
label_F531:;
    /* $F531: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F538;
label_F533:;
    /* $F533: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x54; FLAG_NZ(g_cpu.A);
label_F535:;
    /* $F535: 8D */ maybe_trigger_vblank(4); nes_write(0x4006, g_cpu.A);
label_F538:; /* N2Tone */
    /* $F538: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F568;
label_F53A:; /* PlayBlast */
    /* $F53A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_F53C:;
    /* $F53C: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F53F:;
    /* $F53F: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x94; FLAG_NZ(g_cpu.Y);
label_F541:;
    /* $F541: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x5E; FLAG_NZ(g_cpu.A);
label_F543:;
    /* $F543: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F550;
label_F545:; /* ContinueBlast */
    /* $F545: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F548:;
    /* $F548: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x18; g_cpu.C=(g_cpu.A>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_F54A:;
    /* $F54A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F568;
label_F54C:;
    /* $F54C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_F54E:;
    /* $F54E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_F550:; /* SBlasJ */
    /* $F550: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F5D1;
label_F552:; /* PlayPowerUpGrab */
    /* $F552: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x36; FLAG_NZ(g_cpu.A);
label_F554:;
    /* $F554: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F557:; /* ContinuePowerUpGrab */
    /* $F557: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F55A:;
    /* $F55A: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F55B:;
    /* $F55B: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F568;
label_F55D:;
    /* $F55D: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F55E:;
    /* $F55E: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF4D9 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F561:;
    /* $F561: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x5D; FLAG_NZ(g_cpu.X);
label_F563:;
    /* $F563: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_F565:; /* LoadSqu2Regs */
    /* $F565: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3A6);
label_F568:; /* DecrementSfx2Length */
    /* $F568: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BD; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F56B:;
    /* $F56B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F57B;
label_F56D:; /* EmptySfx2Buffer */
    /* $F56D: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_F56F:;
    /* $F56F: 86 */ maybe_trigger_vblank(3); nes_write(0xF2, g_cpu.X);
label_F571:; /* StopSquare2Sfx */
    /* $F571: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0D; FLAG_NZ(g_cpu.X);
label_F573:;
    /* $F573: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_F576:;
    /* $F576: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_F578:;
    /* $F578: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_F57B:; /* ExSfx2 */
    /* $F57B: 60 */ maybe_trigger_vblank(6);
    return;
label_F57C:; /* Square2SfxHandler */
    /* $F57C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_F57E:;
    /* $F57E: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_F580:;
    /* $F580: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F5E7;
label_F582:;
    /* $F582: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFE); FLAG_NZ(g_cpu.Y);
label_F584:;
    /* $F584: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F5A6;
label_F586:;
    /* $F586: 84 */ maybe_trigger_vblank(3); nes_write(0xF2, g_cpu.Y);
label_F588:;
    /* $F588: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_F5C8;
label_F58A:;
    /* $F58A: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F58C:;
    /* $F58C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F518;
    }
label_F58E:;
    /* $F58E: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F590:;
    /* $F590: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5FC;
label_F592:;
    /* $F592: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F594:;
    /* $F594: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F600;
label_F596:;
    /* $F596: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F598:;
    /* $F598: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F53A;
    }
label_F59A:;
    /* $F59A: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F59C:;
    /* $F59C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F51E;
    }
label_F59E:;
    /* $F59E: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F5A0:;
    /* $F5A0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F552;
    }
label_F5A2:;
    /* $F5A2: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F5A4:;
    /* $F5A4: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5E2;
label_F5A6:; /* CheckSfx2Buffer */
    /* $F5A6: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_F5A8:;
    /* $F5A8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F5C1;
label_F5AA:;
    /* $F5AA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_F5D3;
label_F5AC:;
    /* $F5AC: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5AD:;
    /* $F5AD: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5C2;
label_F5AF:;
    /* $F5AF: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B0:;
    /* $F5B0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F60F;
label_F5B2:;
    /* $F5B2: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B3:;
    /* $F5B3: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F60F;
label_F5B5:;
    /* $F5B5: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B6:;
    /* $F5B6: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F545;
    }
label_F5B8:;
    /* $F5B8: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B9:;
    /* $F5B9: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5C2;
label_F5BB:;
    /* $F5BB: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5BC:;
    /* $F5BC: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F557;
    }
label_F5BE:;
    /* $F5BE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5BF:;
    /* $F5BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5E7;
label_F5C1:; /* ExS2H */
    /* $F5C1: 60 */ maybe_trigger_vblank(6);
    return;
label_F5C2:; /* Cont_CGrab_TTick */
    /* $F5C2: 4C */ maybe_trigger_vblank(3); goto label_F52C;
label_F5C5:; /* JumpToDecLength2 */
    /* $F5C5: 4C */ maybe_trigger_vblank(3); goto label_F568;
label_F5C8:; /* PlayBowserFall */
    /* $F5C8: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x38; FLAG_NZ(g_cpu.A);
label_F5CA:;
    /* $F5CA: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F5CD:;
    /* $F5CD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xC4; FLAG_NZ(g_cpu.Y);
label_F5CF:;
    /* $F5CF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_F5D1:; /* BlstSJp */
    /* $F5D1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F5DE;
label_F5D3:; /* ContinueBowserFall */
    /* $F5D3: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F5D6:;
    /* $F5D6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_F5D8:;
    /* $F5D8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F568;
    }
label_F5DA:;
    /* $F5DA: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xA4; FLAG_NZ(g_cpu.Y);
label_F5DC:;
    /* $F5DC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x5A; FLAG_NZ(g_cpu.A);
label_F5DE:; /* PBFRegs */
    /* $F5DE: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_F5E0:; /* EL_LRegs */
    /* $F5E0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F565;
    }
label_F5E2:; /* PlayExtraLife */
    /* $F5E2: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x30; FLAG_NZ(g_cpu.A);
label_F5E4:;
    /* $F5E4: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F5E7:; /* ContinueExtraLife */
    /* $F5E7: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F5EA:;
    /* $F5EA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_F5EC:; /* DivLLoop */
    /* $F5EC: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5ED:;
    /* $F5ED: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F5C5;
    }
label_F5EF:;
    /* $F5EF: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_F5F0:;
    /* $F5F0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F5EC;
    }
label_F5F2:;
    /* $F5F2: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F5F3:;
    /* $F5F3: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF4D3 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F5F6:;
    /* $F5F6: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x82; FLAG_NZ(g_cpu.X);
label_F5F8:;
    /* $F5F8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_F5FA:;
    /* $F5FA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F5E0;
    }
label_F5FC:; /* PlayGrowPowerUp */
    /* $F5FC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_F5FE:;
    /* $F5FE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F602;
label_F600:; /* PlayGrowVine */
    /* $F600: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_F602:; /* GrowItemRegs */
    /* $F602: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F605:;
    /* $F605: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x7F; FLAG_NZ(g_cpu.A);
label_F607:;
    /* $F607: 8D */ maybe_trigger_vblank(4); nes_write(0x4005, g_cpu.A);
label_F60A:;
    /* $F60A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F60C:;
    /* $F60C: 8D */ maybe_trigger_vblank(4); nes_write(0x07BE, g_cpu.A);
label_F60F:; /* ContinueGrowItems */
    /* $F60F: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07BE; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F612:;
    /* $F612: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BE); FLAG_NZ(g_cpu.A);
label_F615:;
    /* $F615: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F616:;
    /* $F616: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F617:;
    /* $F617: CC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x07BD); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_F61A:;
    /* $F61A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F628;
label_F61C:;
    /* $F61C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9D; FLAG_NZ(g_cpu.A);
label_F61E:;
    /* $F61E: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_F621:;
    /* $F621: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF4F8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F624:;
    /* $F624: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3A9);
label_F627:;
    /* $F627: 60 */ maybe_trigger_vblank(6);
    return;
label_F628:; /* StopGrowItems */
    /* $F628: 4C */ maybe_trigger_vblank(3); goto label_F56D;
}

void AudioEngine::play_brick_shatter_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F658;
        case 2: goto label_F644;
    }
label_F63B:; /* PlayBrickShatter */
    /* $F63B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_F63D:;
    /* $F63D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BF, g_cpu.A);
label_F640:; /* ContinueBrickShatter */
    /* $F640: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BF); FLAG_NZ(g_cpu.A);
label_F643:;
    /* $F643: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F644:;
    /* $F644: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_F658;
label_F646:;
    /* $F646: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F647:;
    /* $F647: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xF62B + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_F64A:;
    /* $F64A: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFFEA + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F64D:; /* PlayNoiseSfx */
    /* $F64D: 8D */ maybe_trigger_vblank(4); nes_write(0x400C, g_cpu.A);
label_F650:;
    /* $F650: 8E */ maybe_trigger_vblank(4); nes_write(0x400E, g_cpu.X);
label_F653:;
    /* $F653: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_F655:;
    /* $F655: 8D */ maybe_trigger_vblank(4); nes_write(0x400F, g_cpu.A);
label_F658:; /* DecrementSfx3Length */
    /* $F658: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F65B:;
    /* $F65B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F666;
label_F65D:;
    /* $F65D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF0; FLAG_NZ(g_cpu.A);
label_F65F:;
    /* $F65F: 8D */ maybe_trigger_vblank(4); nes_write(0x400C, g_cpu.A);
label_F662:;
    /* $F662: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F664:;
    /* $F664: 85 */ maybe_trigger_vblank(3); nes_write(0xF3, g_cpu.A);
label_F666:; /* ExSfx3 */
    /* $F666: 60 */ maybe_trigger_vblank(6);
    return;
}

void AudioEngine::noise_sfx_handler_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F685;
        case 2: goto label_F679;
        case 3: goto label_F68F;
    }
label_F667:; /* NoiseSfxHandler */
    /* $F667: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFD); FLAG_NZ(g_cpu.Y);
label_F669:;
    /* $F669: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F675;
label_F66B:;
    /* $F66B: 84 */ maybe_trigger_vblank(3); nes_write(0xF3, g_cpu.Y);
label_F66D:;
    /* $F66D: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFD; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F66F:;
    /* $F66F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF63B); return; }
label_F671:;
    /* $F671: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFD; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F673:;
    /* $F673: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F680;
label_F675:; /* CheckNoiseBuffer */
    /* $F675: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF3); FLAG_NZ(g_cpu.A);
label_F677:;
    /* $F677: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F67F;
label_F679:;
    /* $F679: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F67A:;
    /* $F67A: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF640); return; }
label_F67C:;
    /* $F67C: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F67D:;
    /* $F67D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F685;
label_F67F:; /* ExNH */
    /* $F67F: 60 */ maybe_trigger_vblank(6);
    return;
label_F680:; /* PlayBowserFlame */
    /* $F680: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_F682:;
    /* $F682: 8D */ maybe_trigger_vblank(4); nes_write(0x07BF, g_cpu.A);
label_F685:; /* ContinueBowserFlame */
    /* $F685: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BF); FLAG_NZ(g_cpu.A);
label_F688:;
    /* $F688: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F689:;
    /* $F689: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F68A:;
    /* $F68A: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_F68C:;
    /* $F68C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFFC9 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F68F:;
    /* $F68F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xF64D); return; }
label_F691:; /* ContinueMusic */
    /* $F691: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF73A); return;
}

void AudioEngine::music_handler_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F8B9;
        case 2: goto label_F7C3;
        case 3: goto label_F860;
        case 4: goto label_F8A9;
        case 5: goto label_F6F1;
        case 6: goto label_F80D;
        case 7: goto label_F720;
        case 8: goto label_F710;
        case 9: goto label_F6A1;
        case 10: goto label_F8AD;
        case 11: goto label_F829;
        case 12: goto label_F750;
        case 13: goto label_F6FC;
        case 14: goto label_F7A9;
        case 15: goto label_F810;
        case 16: goto label_F784;
        case 17: goto label_F885;
        case 18: goto label_F786;
        case 19: goto label_F7A5;
        case 20: goto label_F7E6;
        case 21: goto label_F7E7;
        case 22: goto label_F8A5;
        case 23: goto label_F7E4;
        case 24: goto label_F7F7;
        case 25: goto label_F7F1;
        case 26: goto label_F6F5;
        case 27: goto label_F878;
        case 28: goto label_F6B8;
        case 29: goto label_F7FB;
        case 30: goto label_F850;
        case 31: goto label_F88D;
        case 32: goto label_F6B6;
        case 33: goto label_F864;
        case 34: goto label_F862;
        case 35: goto label_F741;
        case 36: goto label_F844;
        case 37: goto label_F807;
        case 38: goto label_F706;
        case 39: goto label_F729;
    }
label_F694:; /* MusicHandler */
    /* $F694: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xFC); FLAG_NZ(g_cpu.A);
label_F696:;
    /* $F696: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6A4;
label_F698:;
    /* $F698: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xFB); FLAG_NZ(g_cpu.A);
label_F69A:;
    /* $F69A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6C8;
label_F69C:;
    /* $F69C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F69F:;
    /* $F69F: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F6A1:;
    /* $F6A1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xF691); return; }
label_F6A3:;
    /* $F6A3: 60 */ maybe_trigger_vblank(6);
    return;
label_F6A4:; /* LoadEventMusic */
    /* $F6A4: 8D */ maybe_trigger_vblank(4); nes_write(0x07B1, g_cpu.A);
label_F6A7:;
    /* $F6A7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_F6A9:;
    /* $F6A9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6B1;
label_F6AB:;
    /* $F6AB: 20 */ maybe_trigger_vblank(6); call_by_address(0xF4A7);
label_F6AE:;
    /* $F6AE: 20 */ maybe_trigger_vblank(6); call_by_address(0xF571);
label_F6B1:; /* NoStopSfx */
    /* $F6B1: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0xF4); FLAG_NZ(g_cpu.X);
label_F6B3:;
    /* $F6B3: 8E */ maybe_trigger_vblank(4); nes_write(0x07C5, g_cpu.X);
label_F6B6:;
    /* $F6B6: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_F6B8:;
    /* $F6B8: 8C */ maybe_trigger_vblank(4); nes_write(0x07C4, g_cpu.Y);
label_F6BB:;
    /* $F6BB: 84 */ maybe_trigger_vblank(3); nes_write(0xF4, g_cpu.Y);
label_F6BD:;
    /* $F6BD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x40; g_cpu.C=(g_cpu.A>=0x40)?1:0; FLAG_NZ(r&0xFF); }
label_F6BF:;
    /* $F6BF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6F1;
label_F6C1:;
    /* $F6C1: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x08; FLAG_NZ(g_cpu.X);
label_F6C3:;
    /* $F6C3: 8E */ maybe_trigger_vblank(4); nes_write(0x07C4, g_cpu.X);
label_F6C6:;
    /* $F6C6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6F1;
label_F6C8:; /* LoadAreaMusic */
    /* $F6C8: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_F6CA:;
    /* $F6CA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6CF;
label_F6CC:;
    /* $F6CC: 20 */ maybe_trigger_vblank(6); call_by_address(0xF4A7);
label_F6CF:; /* NoStop1 */
    /* $F6CF: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x10; FLAG_NZ(g_cpu.Y);
label_F6D1:; /* GMLoopB */
    /* $F6D1: 8C */ maybe_trigger_vblank(4); nes_write(0x07C7, g_cpu.Y);
label_F6D4:; /* HandleAreaMusicLoopB */
    /* $F6D4: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_F6D6:;
    /* $F6D6: 8C */ maybe_trigger_vblank(4); nes_write(0x07B1, g_cpu.Y);
label_F6D9:;
    /* $F6D9: 85 */ maybe_trigger_vblank(3); nes_write(0xF4, g_cpu.A);
label_F6DB:;
    /* $F6DB: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_F6DD:;
    /* $F6DD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6ED;
label_F6DF:;
    /* $F6DF: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07C7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F6E2:;
    /* $F6E2: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07C7); FLAG_NZ(g_cpu.Y);
label_F6E5:;
    /* $F6E5: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x32; g_cpu.C=(g_cpu.Y>=0x32)?1:0; FLAG_NZ(r&0xFF); }
label_F6E7:;
    /* $F6E7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6F5;
label_F6E9:;
    /* $F6E9: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x11; FLAG_NZ(g_cpu.Y);
label_F6EB:;
    /* $F6EB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F6D1;
    }
label_F6ED:; /* FindAreaMusicHeader */
    /* $F6ED: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x08; FLAG_NZ(g_cpu.Y);
label_F6EF:;
    /* $F6EF: 84 */ maybe_trigger_vblank(3); nes_write(0xF7, g_cpu.Y);
label_F6F1:; /* FindEventMusicHeader */
    /* $F6F1: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_F6F2:;
    /* $F6F2: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F6F3:;
    /* $F6F3: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F6F1;
    }
label_F6F5:; /* LoadHeader */
    /* $F6F5: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90C + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F6F8:;
    /* $F6F8: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F6F9:;
    /* $F6F9: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90D + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F6FC:;
    /* $F6FC: 85 */ maybe_trigger_vblank(3); nes_write(0xF0, g_cpu.A);
label_F6FE:;
    /* $F6FE: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F701:;
    /* $F701: 85 */ maybe_trigger_vblank(3); nes_write(0xF5, g_cpu.A);
label_F703:;
    /* $F703: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F706:;
    /* $F706: 85 */ maybe_trigger_vblank(3); nes_write(0xF6, g_cpu.A);
label_F708:;
    /* $F708: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF910 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F70B:;
    /* $F70B: 85 */ maybe_trigger_vblank(3); nes_write(0xF9, g_cpu.A);
label_F70D:;
    /* $F70D: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF911 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F710:;
    /* $F710: 85 */ maybe_trigger_vblank(3); nes_write(0xF8, g_cpu.A);
label_F712:;
    /* $F712: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF912 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F715:;
    /* $F715: 8D */ maybe_trigger_vblank(4); nes_write(0x07B0, g_cpu.A);
label_F718:;
    /* $F718: 8D */ maybe_trigger_vblank(4); nes_write(0x07C1, g_cpu.A);
label_F71B:;
    /* $F71B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_F71D:;
    /* $F71D: 8D */ maybe_trigger_vblank(4); nes_write(0x07B4, g_cpu.A);
label_F720:;
    /* $F720: 8D */ maybe_trigger_vblank(4); nes_write(0x07B6, g_cpu.A);
label_F723:;
    /* $F723: 8D */ maybe_trigger_vblank(4); nes_write(0x07B9, g_cpu.A);
label_F726:;
    /* $F726: 8D */ maybe_trigger_vblank(4); nes_write(0x07BA, g_cpu.A);
label_F729:;
    /* $F729: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F72B:;
    /* $F72B: 85 */ maybe_trigger_vblank(3); nes_write(0xF7, g_cpu.A);
label_F72D:;
    /* $F72D: 8D */ maybe_trigger_vblank(4); nes_write(0x07CA, g_cpu.A);
label_F730:;
    /* $F730: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0B; FLAG_NZ(g_cpu.A);
label_F732:;
    /* $F732: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_F735:;
    /* $F735: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0F; FLAG_NZ(g_cpu.A);
label_F737:;
    /* $F737: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_F73A:; /* HandleSquare2Music */
    /* $F73A: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B4; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F73D:;
    /* $F73D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F79E;
label_F73F:;
    /* $F73F: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF7); FLAG_NZ(g_cpu.Y);
label_F741:;
    /* $F741: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F743:;
    /* $F743: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F745:;
    /* $F745: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F74B;
label_F747:;
    /* $F747: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_F786;
label_F749:;
    /* $F749: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F77A;
label_F74B:; /* EndOfMusicData */
    /* $F74B: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F74E:;
    /* $F74E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x40; g_cpu.C=(g_cpu.A>=0x40)?1:0; FLAG_NZ(r&0xFF); }
label_F750:;
    /* $F750: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F757;
label_F752:;
    /* $F752: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07C5); FLAG_NZ(g_cpu.A);
label_F755:;
    /* $F755: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F774;
label_F757:; /* NotTRO */
    /* $F757: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x04; FLAG_NZ(g_cpu.A);
label_F759:;
    /* $F759: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F777;
label_F75B:;
    /* $F75B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F75D:;
    /* $F75D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x5F; FLAG_NZ(g_cpu.A);
label_F75F:;
    /* $F75F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F774;
label_F761:;
    /* $F761: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F763:;
    /* $F763: 85 */ maybe_trigger_vblank(3); nes_write(0xF4, g_cpu.A);
label_F765:;
    /* $F765: 8D */ maybe_trigger_vblank(4); nes_write(0x07B1, g_cpu.A);
label_F768:;
    /* $F768: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_F76B:;
    /* $F76B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_F76D:;
    /* $F76D: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F770:;
    /* $F770: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_F773:;
    /* $F773: 60 */ maybe_trigger_vblank(6);
    return;
label_F774:; /* MusicLoopBack */
    /* $F774: 4C */ maybe_trigger_vblank(3); goto label_F6D4;
label_F777:; /* VictoryMLoopBack */
    /* $F777: 4C */ maybe_trigger_vblank(3); goto label_F6A4;
label_F77A:; /* Squ2LengthHandler */
    /* $F77A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8CB);
label_F77D:;
    /* $F77D: 8D */ maybe_trigger_vblank(4); nes_write(0x07B3, g_cpu.A);
label_F780:;
    /* $F780: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF7); FLAG_NZ(g_cpu.Y);
label_F782:;
    /* $F782: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F784:;
    /* $F784: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F786:; /* Squ2NoteHandler */
    /* $F786: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0xF2); FLAG_NZ(g_cpu.X);
label_F788:;
    /* $F788: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F798;
label_F78A:;
    /* $F78A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3A9);
label_F78D:;
    /* $F78D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F792;
label_F78F:;
    /* $F78F: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8D8);
label_F792:; /* Rest */
    /* $F792: 8D */ maybe_trigger_vblank(4); nes_write(0x07B5, g_cpu.A);
label_F795:;
    /* $F795: 20 */ maybe_trigger_vblank(6); call_by_address(0xF39F);
label_F798:; /* SkipFqL1 */
    /* $F798: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B3); FLAG_NZ(g_cpu.A);
label_F79B:;
    /* $F79B: 8D */ maybe_trigger_vblank(4); nes_write(0x07B4, g_cpu.A);
label_F79E:; /* MiscSqu2MusicTasks */
    /* $F79E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_F7A0:;
    /* $F7A0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F7BC;
label_F7A2:;
    /* $F7A2: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F7A5:;
    /* $F7A5: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x91; FLAG_NZ(g_cpu.A);
label_F7A7:;
    /* $F7A7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F7BC;
label_F7A9:;
    /* $F7A9: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B5); FLAG_NZ(g_cpu.Y);
label_F7AC:;
    /* $F7AC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F7B1;
label_F7AE:;
    /* $F7AE: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B5; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F7B1:; /* NoDecEnv1 */
    /* $F7B1: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8F4);
label_F7B4:;
    /* $F7B4: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_F7B7:;
    /* $F7B7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x7F; FLAG_NZ(g_cpu.X);
label_F7B9:;
    /* $F7B9: 8E */ maybe_trigger_vblank(4); nes_write(0x4005, g_cpu.X);
label_F7BC:; /* HandleSquare1Music */
    /* $F7BC: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF8); FLAG_NZ(g_cpu.Y);
label_F7BE:;
    /* $F7BE: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F81A;
label_F7C0:;
    /* $F7C0: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B6; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F7C3:;
    /* $F7C3: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F7F7;
label_F7C5:; /* FetchSqu1MusicData */
    /* $F7C5: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF8); FLAG_NZ(g_cpu.Y);
label_F7C7:;
    /* $F7C7: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF8; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F7C9:;
    /* $F7C9: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F7CB:;
    /* $F7CB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F7DC;
label_F7CD:;
    /* $F7CD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x83; FLAG_NZ(g_cpu.A);
label_F7CF:;
    /* $F7CF: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F7D2:;
    /* $F7D2: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x94; FLAG_NZ(g_cpu.A);
label_F7D4:;
    /* $F7D4: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_F7D7:;
    /* $F7D7: 8D */ maybe_trigger_vblank(4); nes_write(0x07CA, g_cpu.A);
label_F7DA:;
    /* $F7DA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F7C5;
    }
label_F7DC:; /* Squ1NoteHandler */
    /* $F7DC: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8C5);
label_F7DF:;
    /* $F7DF: 8D */ maybe_trigger_vblank(4); nes_write(0x07B6, g_cpu.A);
label_F7E2:;
    /* $F7E2: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF1); FLAG_NZ(g_cpu.Y);
label_F7E4:;
    /* $F7E4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F81A;
label_F7E6:;
    /* $F7E6: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F7E7:;
    /* $F7E7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3E; FLAG_NZ(g_cpu.A);
label_F7E9:;
    /* $F7E9: 20 */ maybe_trigger_vblank(6); call_by_address(0xF38B);
label_F7EC:;
    /* $F7EC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F7F1;
label_F7EE:;
    /* $F7EE: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8D8);
label_F7F1:; /* SkipCtrlL */
    /* $F7F1: 8D */ maybe_trigger_vblank(4); nes_write(0x07B7, g_cpu.A);
label_F7F4:;
    /* $F7F4: 20 */ maybe_trigger_vblank(6); call_by_address(0xF381);
label_F7F7:; /* MiscSqu1MusicTasks */
    /* $F7F7: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_F7F9:;
    /* $F7F9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F81A;
label_F7FB:;
    /* $F7FB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F7FE:;
    /* $F7FE: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x91; FLAG_NZ(g_cpu.A);
label_F800:;
    /* $F800: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F810;
label_F802:;
    /* $F802: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B7); FLAG_NZ(g_cpu.Y);
label_F805:;
    /* $F805: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F80A;
label_F807:;
    /* $F807: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B7; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F80A:; /* NoDecEnv2 */
    /* $F80A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8F4);
label_F80D:;
    /* $F80D: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F810:; /* DeathMAltReg */
    /* $F810: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07CA); FLAG_NZ(g_cpu.A);
label_F813:;
    /* $F813: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F817;
label_F815:;
    /* $F815: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x7F; FLAG_NZ(g_cpu.A);
label_F817:; /* DoAltLoad */
    /* $F817: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_F81A:; /* HandleTriangleMusic */
    /* $F81A: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF9); FLAG_NZ(g_cpu.A);
label_F81C:;
    /* $F81C: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B9; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F81F:;
    /* $F81F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F86D;
label_F821:;
    /* $F821: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF9); FLAG_NZ(g_cpu.Y);
label_F823:;
    /* $F823: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF9; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F825:;
    /* $F825: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F827:;
    /* $F827: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F86A;
label_F829:;
    /* $F829: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_F83E;
label_F82B:;
    /* $F82B: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8CB);
label_F82E:;
    /* $F82E: 8D */ maybe_trigger_vblank(4); nes_write(0x07B8, g_cpu.A);
label_F831:;
    /* $F831: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1F; FLAG_NZ(g_cpu.A);
label_F833:;
    /* $F833: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_F836:;
    /* $F836: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF9); FLAG_NZ(g_cpu.Y);
label_F838:;
    /* $F838: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF9; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F83A:;
    /* $F83A: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F83C:;
    /* $F83C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F86A;
label_F83E:; /* TriNoteHandler */
    /* $F83E: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3AD);
label_F841:;
    /* $F841: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x07B8); FLAG_NZ(g_cpu.X);
label_F844:;
    /* $F844: 8E */ maybe_trigger_vblank(4); nes_write(0x07B9, g_cpu.X);
label_F847:;
    /* $F847: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F84A:;
    /* $F84A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x6E; FLAG_NZ(g_cpu.A);
label_F84C:;
    /* $F84C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F854;
label_F84E:;
    /* $F84E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F850:;
    /* $F850: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0A; FLAG_NZ(g_cpu.A);
label_F852:;
    /* $F852: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F86D;
label_F854:; /* NotDOrD4 */
    /* $F854: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F855:;
    /* $F855: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x12; g_cpu.C=(g_cpu.A>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_F857:;
    /* $F857: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F868;
label_F859:;
    /* $F859: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F85C:;
    /* $F85C: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_F85E:;
    /* $F85E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F864;
label_F860:;
    /* $F860: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0F; FLAG_NZ(g_cpu.A);
label_F862:;
    /* $F862: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F86A;
label_F864:; /* MediN */
    /* $F864: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1F; FLAG_NZ(g_cpu.A);
label_F866:;
    /* $F866: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F86A;
label_F868:; /* LongN */
    /* $F868: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_F86A:; /* LoadTriCtrlReg */
    /* $F86A: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_F86D:; /* HandleNoiseMusic */
    /* $F86D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F86F:;
    /* $F86F: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF3; FLAG_NZ(g_cpu.A);
label_F871:;
    /* $F871: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8C4;
label_F873:;
    /* $F873: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BA; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F876:;
    /* $F876: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8C4;
label_F878:; /* FetchNoiseBeatData */
    /* $F878: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B0); FLAG_NZ(g_cpu.Y);
label_F87B:;
    /* $F87B: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07B0; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F87E:;
    /* $F87E: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F880:;
    /* $F880: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F88A;
label_F882:;
    /* $F882: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07C1); FLAG_NZ(g_cpu.A);
label_F885:;
    /* $F885: 8D */ maybe_trigger_vblank(4); nes_write(0x07B0, g_cpu.A);
label_F888:;
    /* $F888: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F878;
    }
label_F88A:; /* NoiseBeatHandler */
    /* $F88A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8C5);
label_F88D:;
    /* $F88D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BA, g_cpu.A);
label_F890:;
    /* $F890: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F891:;
    /* $F891: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3E; FLAG_NZ(g_cpu.A);
label_F893:;
    /* $F893: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8B9;
label_F895:;
    /* $F895: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x30; g_cpu.C=(g_cpu.A>=0x30)?1:0; FLAG_NZ(r&0xFF); }
label_F897:;
    /* $F897: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8B1;
label_F899:;
    /* $F899: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_F89B:;
    /* $F89B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8A9;
label_F89D:;
    /* $F89D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x10; FLAG_NZ(g_cpu.A);
label_F89F:;
    /* $F89F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8B9;
label_F8A1:;
    /* $F8A1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_F8A3:;
    /* $F8A3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_F8A5:;
    /* $F8A5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x18; FLAG_NZ(g_cpu.Y);
label_F8A7:;
    /* $F8A7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8BB;
label_F8A9:; /* StrongBeat */
    /* $F8A9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_F8AB:;
    /* $F8AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0C; FLAG_NZ(g_cpu.X);
label_F8AD:;
    /* $F8AD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x18; FLAG_NZ(g_cpu.Y);
label_F8AF:;
    /* $F8AF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8BB;
label_F8B1:; /* LongBeat */
    /* $F8B1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_F8B3:;
    /* $F8B3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_F8B5:;
    /* $F8B5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x58; FLAG_NZ(g_cpu.Y);
label_F8B7:;
    /* $F8B7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8BB;
label_F8B9:; /* SilentBeat */
    /* $F8B9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_F8BB:; /* PlayBeat */
    /* $F8BB: 8D */ maybe_trigger_vblank(4); nes_write(0x400C, g_cpu.A);
label_F8BE:;
    /* $F8BE: 8E */ maybe_trigger_vblank(4); nes_write(0x400E, g_cpu.X);
label_F8C1:;
    /* $F8C1: 8C */ maybe_trigger_vblank(4); nes_write(0x400F, g_cpu.Y);
label_F8C4:; /* ExitMusicHandler */
    /* $F8C4: 60 */ maybe_trigger_vblank(6);
    return;
}

void AudioEngine::alternate_length_handler_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F8D0;
        case 2: goto label_F8C9;
        case 3: goto label_F8CA;
        case 4: goto label_F8C6;
        case 5: goto label_F8CE;
        case 6: goto label_F8C8;
    }
label_F8C5:; /* AlternateLengthHandler */
    /* $F8C5: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_F8C6:;
    /* $F8C6: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_F8C7:;
    /* $F8C7: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F8C8:;
    /* $F8C8: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_F8C9:;
    /* $F8C9: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_F8CA:;
    /* $F8CA: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_F8CB:; /* ProcessLengthData */
    /* $F8CB: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_F8CD:;
    /* $F8CD: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F8CE:;
    /* $F8CE: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xF0); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_F8D0:;
    /* $F8D0: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x07C4); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_F8D3:;
    /* $F8D3: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F8D4:;
    /* $F8D4: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFF66 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F8D7:;
    /* $F8D7: 60 */ maybe_trigger_vblank(6);
    return;
}

void AudioEngine::load_control_regs_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F8F1;
        case 2: goto label_F8E7;
    }
label_F8D8:; /* LoadControlRegs */
    /* $F8D8: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F8DB:;
    /* $F8DB: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_F8DD:;
    /* $F8DD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8E3;
label_F8DF:;
    /* $F8DF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_F8E1:;
    /* $F8E1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8EF;
label_F8E3:; /* NotECstlM */
    /* $F8E3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F8E5:;
    /* $F8E5: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x7D; FLAG_NZ(g_cpu.A);
label_F8E7:;
    /* $F8E7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8ED;
label_F8E9:;
    /* $F8E9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_F8EB:;
    /* $F8EB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8EF;
label_F8ED:; /* WaterMus */
    /* $F8ED: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_F8EF:; /* AllMus */
    /* $F8EF: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x82; FLAG_NZ(g_cpu.X);
label_F8F1:;
    /* $F8F1: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_F8F3:;
    /* $F8F3: 60 */ maybe_trigger_vblank(6);
    return;
}

void AudioEngine::load_envelope_data_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F8FB;
        case 2: goto label_F90C;
        case 3: goto label_F903;
        case 4: goto label_F905;
    }
label_F8F4:; /* LoadEnvelopeData */
    /* $F8F4: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F8F7:;
    /* $F8F7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_F8F9:;
    /* $F8F9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8FF;
label_F8FB:;
    /* $F8FB: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFF96 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F8FE:;
    /* $F8FE: 60 */ maybe_trigger_vblank(6);
    return;
label_F8FF:; /* LoadUsualEnvData */
    /* $F8FF: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F901:;
    /* $F901: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x7D; FLAG_NZ(g_cpu.A);
label_F903:;
    /* $F903: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F909;
label_F905:;
    /* $F905: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFF9A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F908:;
    /* $F908: 60 */ maybe_trigger_vblank(6);
    return;
label_F909:; /* LoadWaterEventMusEnvData */
    /* $F909: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFFA2 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F90C:;
    /* $F90C: 60 */ maybe_trigger_vblank(6);
    return;
}

}  // namespace smb::semcomp
