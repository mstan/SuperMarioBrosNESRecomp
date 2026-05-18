// semcomp/SoundEngine.cpp — bulk-ported routines (auto-generated).
#include "semcomp/SoundEngine.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

void SoundEngine::run_offscr_bits_subs() {
    (void)state_;
label_F1D7:; /* RunOffscrBitsSubs */
    /* $F1D7: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1F6);
label_F1DA:;
    /* $F1DA: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F1DB:;
    /* $F1DB: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F1DC:;
    /* $F1DC: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F1DD:;
    /* $F1DD: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F1DE:;
    /* $F1DE: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_F1E0:;
    /* $F1E0: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF239); return;
}

void SoundEngine::play_flagpole_slide() {
    (void)state_;
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

void SoundEngine::play_small_jump() {
    (void)state_;
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
    /* $F43D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF3BF); return; }
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

void SoundEngine::play_big_jump() {
    (void)state_;
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
    /* $F421: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xF3CD); return; }
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
    /* $F43D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF3BF); return; }
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

void SoundEngine::play_fireball_throw() {
    (void)state_;
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
    /* $F421: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xF3CD); return; }
label_F423:;
    /* $F423: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F425:;
    /* $F425: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF3D1); return; }
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

void SoundEngine::play_bump() {
    (void)state_;
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
    /* $F421: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xF3CD); return; }
label_F423:;
    /* $F423: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F425:;
    /* $F425: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF3D1); return; }
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

void SoundEngine::play_timer_tick() {
    (void)state_;
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

void SoundEngine::play_blast() {
    (void)state_;
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
    /* $F59C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xF51E); return; }
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
    /* $F5C2: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF52C); return;
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

void SoundEngine::play_power_up_grab() {
    (void)state_;
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
}

void SoundEngine::play_noise_sfx() {
    (void)state_;
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

}  // namespace smb::semcomp
