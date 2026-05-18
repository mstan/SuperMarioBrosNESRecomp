// semcomp/EnemyHandlers2.cpp — bulk-ported routines (auto-generated).
#include "semcomp/EnemyHandlers2.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

void EnemyHandlers2::bridge_collapse() {
    (void)state_;
label_CFEC:; /* BridgeCollapse */
    /* $CFEC: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x0368); FLAG_NZ(g_cpu.X);
label_CFEF:;
    /* $CFEF: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CFF1:;
    /* $CFF1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x2D; g_cpu.C=(g_cpu.A>=0x2D)?1:0; FLAG_NZ(r&0xFF); }
label_CFF3:;
    /* $CFF3: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D005;
label_CFF5:;
    /* $CFF5: 86 */ maybe_trigger_vblank(3); nes_write(0x08, g_cpu.X);
label_CFF7:;
    /* $CFF7: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CFF9:;
    /* $CFF9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D015;
label_CFFB:;
    /* $CFFB: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_CFFD:;
    /* $CFFD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D005;
label_CFFF:;
    /* $CFFF: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D001:;
    /* $D001: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xE0; g_cpu.C=(g_cpu.A>=0xE0)?1:0; FLAG_NZ(r&0xFF); }
label_D003:;
    /* $D003: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D00F;
label_D005:; /* SetM2 */
    /* $D005: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_D007:;
    /* $D007: 85 */ maybe_trigger_vblank(3); nes_write(0xFC, g_cpu.A);
label_D009:;
    /* $D009: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0772; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D00C:;
    /* $D00C: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD071); return;
label_D00F:; /* MoveD_Bowser */
    /* $D00F: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF8C);
label_D012:;
    /* $D012: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD17B); return;
label_D015:; /* RemoveBridge */
    /* $D015: CE */ maybe_trigger_vblank(6); { uint16_t a=0x0364; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D018:;
    /* $D018: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D05E;
label_D01A:;
    /* $D01A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_D01C:;
    /* $D01C: 8D */ maybe_trigger_vblank(4); nes_write(0x0364, g_cpu.A);
label_D01F:;
    /* $D01F: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0363); FLAG_NZ(g_cpu.A);
label_D022:;
    /* $D022: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x01; FLAG_NZ(g_cpu.A);
label_D024:;
    /* $D024: 8D */ maybe_trigger_vblank(4); nes_write(0x0363, g_cpu.A);
label_D027:;
    /* $D027: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x22; FLAG_NZ(g_cpu.A);
label_D029:;
    /* $D029: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_D02B:;
    /* $D02B: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0369); FLAG_NZ(g_cpu.Y);
label_D02E:;
    /* $D02E: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCFDD + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D031:;
    /* $D031: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_D033:;
    /* $D033: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0300); FLAG_NZ(g_cpu.Y);
label_D036:;
    /* $D036: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D037:;
    /* $D037: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0C; FLAG_NZ(g_cpu.X);
label_D039:;
    /* $D039: 20 */ maybe_trigger_vblank(6); call_by_address(0x8ACD);
label_D03C:;
    /* $D03C: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D03E:;
    /* $D03E: 20 */ maybe_trigger_vblank(6); call_by_address(0x8A8F);
label_D041:;
    /* $D041: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_D043:;
    /* $D043: 85 */ maybe_trigger_vblank(3); nes_write(0xFE, g_cpu.A);
label_D045:;
    /* $D045: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_D047:;
    /* $D047: 85 */ maybe_trigger_vblank(3); nes_write(0xFD, g_cpu.A);
label_D049:;
    /* $D049: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0369; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D04C:;
    /* $D04C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0369); FLAG_NZ(g_cpu.A);
label_D04F:;
    /* $D04F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0F; g_cpu.C=(g_cpu.A>=0x0F)?1:0; FLAG_NZ(r&0xFF); }
label_D051:;
    /* $D051: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D05E;
label_D053:;
    /* $D053: 20 */ maybe_trigger_vblank(6); call_by_address(0xC363);
label_D056:;
    /* $D056: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_D058:;
    /* $D058: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_D05A:;
    /* $D05A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_D05C:;
    /* $D05C: 85 */ maybe_trigger_vblank(3); nes_write(0xFE, g_cpu.A);
label_D05E:; /* NoBFall */
    /* $D05E: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD17B); return;
}

void EnemyHandlers2::kill_all_enemies_d071() {
    (void)state_;
label_D071:; /* KillAllEnemies */
    /* $D071: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x04; FLAG_NZ(g_cpu.X);
label_D073:; /* KillLoop */
    /* $D073: 20 */ maybe_trigger_vblank(6); call_by_address(0xC998);
label_D076:;
    /* $D076: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_D077:;
    /* $D077: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D073;
    }
label_D079:;
    /* $D079: 8D */ maybe_trigger_vblank(4); nes_write(0x06CB, g_cpu.A);
label_D07C:;
    /* $D07C: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D07E:;
    /* $D07E: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyHandlers2::run_bowser() {
    (void)state_;
label_D065:; /* RunBowser */
    /* $D065: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D067:;
    /* $D067: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_D069:;
    /* $D069: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D07F;
label_D06B:;
    /* $D06B: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D06D:;
    /* $D06D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xE0; g_cpu.C=(g_cpu.A>=0xE0)?1:0; FLAG_NZ(r&0xFF); }
label_D06F:;
    /* $D06F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { call_by_address(0xD00F); return; }
label_D071:; /* KillAllEnemies */
    /* $D071: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x04; FLAG_NZ(g_cpu.X);
label_D073:; /* KillLoop */
    /* $D073: 20 */ maybe_trigger_vblank(6); call_by_address(0xC998);
label_D076:;
    /* $D076: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_D077:;
    /* $D077: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D073;
    }
label_D079:;
    /* $D079: 8D */ maybe_trigger_vblank(4); nes_write(0x06CB, g_cpu.A);
label_D07C:;
    /* $D07C: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D07E:;
    /* $D07E: 60 */ maybe_trigger_vblank(6);
    return;
label_D07F:; /* BowserControl */
    /* $D07F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_D081:;
    /* $D081: 8D */ maybe_trigger_vblank(4); nes_write(0x06CB, g_cpu.A);
label_D084:;
    /* $D084: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_D087:;
    /* $D087: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D08C;
label_D089:;
    /* $D089: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD139); return;
label_D08C:; /* ChkMouth */
    /* $D08C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0363); FLAG_NZ(g_cpu.A);
label_D08F:;
    /* $D08F: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_D094;
label_D091:;
    /* $D091: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD10F); return;
label_D094:; /* FeetTmr */
    /* $D094: CE */ maybe_trigger_vblank(6); { uint16_t a=0x0364; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D097:;
    /* $D097: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D0A6;
label_D099:;
    /* $D099: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_D09B:;
    /* $D09B: 8D */ maybe_trigger_vblank(4); nes_write(0x0364, g_cpu.A);
label_D09E:;
    /* $D09E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0363); FLAG_NZ(g_cpu.A);
label_D0A1:;
    /* $D0A1: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x01; FLAG_NZ(g_cpu.A);
label_D0A3:;
    /* $D0A3: 8D */ maybe_trigger_vblank(4); nes_write(0x0363, g_cpu.A);
label_D0A6:; /* ResetMDr */
    /* $D0A6: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_D0A8:;
    /* $D0A8: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_D0AA:;
    /* $D0AA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D0B0;
label_D0AC:;
    /* $D0AC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_D0AE:;
    /* $D0AE: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_D0B0:; /* B_FaceP */
    /* $D0B0: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x078A + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D0B3:;
    /* $D0B3: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D0D1;
label_D0B5:;
    /* $D0B5: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_D0B8:;
    /* $D0B8: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_D0D1;
label_D0BA:;
    /* $D0BA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_D0BC:;
    /* $D0BC: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_D0BE:;
    /* $D0BE: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_D0C0:;
    /* $D0C0: 8D */ maybe_trigger_vblank(4); nes_write(0x0365, g_cpu.A);
label_D0C3:;
    /* $D0C3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_D0C5:;
    /* $D0C5: 9D */ maybe_trigger_vblank(5); nes_write((0x078A + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D0C8:;
    /* $D0C8: 8D */ maybe_trigger_vblank(4); nes_write(0x0790, g_cpu.A);
label_D0CB:;
    /* $D0CB: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D0CD:;
    /* $D0CD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xC8; g_cpu.C=(g_cpu.A>=0xC8)?1:0; FLAG_NZ(r&0xFF); }
label_D0CF:;
    /* $D0CF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D10F;
label_D0D1:; /* GetPRCmp */
    /* $D0D1: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_D0D3:;
    /* $D0D3: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_D0D5:;
    /* $D0D5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D10F;
label_D0D7:;
    /* $D0D7: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D0D9:;
    /* $D0D9: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0366); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D0DC:;
    /* $D0DC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D0EA;
label_D0DE:;
    /* $D0DE: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A7 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D0E1:;
    /* $D0E1: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_D0E3:;
    /* $D0E3: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_D0E4:;
    /* $D0E4: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD061 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D0E7:;
    /* $D0E7: 8D */ maybe_trigger_vblank(4); nes_write(0x06DC, g_cpu.A);
label_D0EA:; /* GetDToO */
    /* $D0EA: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D0EC:;
    /* $D0EC: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D0ED:;
    /* $D0ED: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0365); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D0F0:;
    /* $D0F0: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_D0F2:;
    /* $D0F2: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_D0F4:;
    /* $D0F4: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x01; g_cpu.C=(g_cpu.Y>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_D0F6:;
    /* $D0F6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D10F;
label_D0F8:;
    /* $D0F8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xFF; FLAG_NZ(g_cpu.Y);
label_D0FA:;
    /* $D0FA: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_D0FB:;
    /* $D0FB: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0366); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D0FE:;
    /* $D0FE: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_D107;
label_D100:;
    /* $D100: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_D102:;
    /* $D102: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D103:;
    /* $D103: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_D105:;
    /* $D105: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_D107:; /* CompDToO */
    /* $D107: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x06DC); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D10A:;
    /* $D10A: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D10F;
label_D10C:;
    /* $D10C: 8C */ maybe_trigger_vblank(4); nes_write(0x0365, g_cpu.Y);
label_D10F:; /* HammerChk */
    /* $D10F: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x078A + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D112:;
    /* $D112: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D13C;
label_D114:;
    /* $D114: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF8C);
label_D117:;
    /* $D117: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_D11A:;
    /* $D11A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_D11C:;
    /* $D11C: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D127;
label_D11E:;
    /* $D11E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_D120:;
    /* $D120: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_D122:;
    /* $D122: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D127;
label_D124:;
    /* $D124: 20 */ maybe_trigger_vblank(6); call_by_address(0xBA94);
label_D127:; /* SetHmrTmr */
    /* $D127: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D129:;
    /* $D129: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x80; g_cpu.C=(g_cpu.A>=0x80)?1:0; FLAG_NZ(r&0xFF); }
label_D12B:;
    /* $D12B: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D149;
label_D12D:;
    /* $D12D: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A7 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D130:;
    /* $D130: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_D132:;
    /* $D132: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_D133:;
    /* $D133: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD061 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D136:;
    /* $D136: 9D */ maybe_trigger_vblank(5); nes_write((0x078A + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D139:; /* SkipToFB */
    /* $D139: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD149); return;
label_D13C:; /* MakeBJump */
    /* $D13C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_D13E:;
    /* $D13E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D149;
label_D140:;
    /* $D140: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0xCF + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D142:;
    /* $D142: 20 */ maybe_trigger_vblank(6); call_by_address(0xC363);
label_D145:;
    /* $D145: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFE; FLAG_NZ(g_cpu.A);
label_D147:;
    /* $D147: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_D149:; /* ChkFireB */
    /* $D149: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_D14C:;
    /* $D14C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_D14E:;
    /* $D14E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D154;
label_D150:;
    /* $D150: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_D152:;
    /* $D152: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D17B;
label_D154:; /* SpawnFBr */
    /* $D154: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0790); FLAG_NZ(g_cpu.A);
label_D157:;
    /* $D157: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D17B;
label_D159:;
    /* $D159: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_D15B:;
    /* $D15B: 8D */ maybe_trigger_vblank(4); nes_write(0x0790, g_cpu.A);
label_D15E:;
    /* $D15E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0363); FLAG_NZ(g_cpu.A);
label_D161:;
    /* $D161: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x80; FLAG_NZ(g_cpu.A);
label_D163:;
    /* $D163: 8D */ maybe_trigger_vblank(4); nes_write(0x0363, g_cpu.A);
label_D166:;
    /* $D166: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D149;
    }
label_D168:;
    /* $D168: 20 */ maybe_trigger_vblank(6); call_by_address(0xD1D9);
label_D16B:;
    /* $D16B: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06CC); FLAG_NZ(g_cpu.Y);
label_D16E:;
    /* $D16E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D173;
label_D170:;
    /* $D170: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_D171:;
    /* $D171: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x10; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D173:; /* SetFBTmr */
    /* $D173: 8D */ maybe_trigger_vblank(4); nes_write(0x0790, g_cpu.A);
label_D176:;
    /* $D176: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x15; FLAG_NZ(g_cpu.A);
label_D178:;
    /* $D178: 8D */ maybe_trigger_vblank(4); nes_write(0x06CB, g_cpu.A);
label_D17B:; /* BowserGfxHandler */
    /* $D17B: 20 */ maybe_trigger_vblank(6); call_by_address(0xD1BC);
label_D17E:;
    /* $D17E: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x10; FLAG_NZ(g_cpu.Y);
label_D180:;
    /* $D180: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D182:;
    /* $D182: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_D183:;
    /* $D183: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D187;
label_D185:;
    /* $D185: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xF0; FLAG_NZ(g_cpu.Y);
label_D187:; /* CopyFToR */
    /* $D187: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_D188:;
    /* $D188: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D189:;
    /* $D189: 75 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x87 + g_cpu.X) & 0xFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D18B:;
    /* $D18B: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06CF); FLAG_NZ(g_cpu.Y);
label_D18E:;
    /* $D18E: 99 */ maybe_trigger_vblank(5); nes_write((0x0087 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D191:;
    /* $D191: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D193:;
    /* $D193: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D194:;
    /* $D194: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_D196:;
    /* $D196: 99 */ maybe_trigger_vblank(5); nes_write((0x00CF + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D199:;
    /* $D199: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D19B:;
    /* $D19B: 99 */ maybe_trigger_vblank(5); nes_write((0x001E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D19E:;
    /* $D19E: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D1A0:;
    /* $D1A0: 99 */ maybe_trigger_vblank(5); nes_write((0x0046 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D1A3:;
    /* $D1A3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x08); FLAG_NZ(g_cpu.A);
label_D1A5:;
    /* $D1A5: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_D1A6:;
    /* $D1A6: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x06CF); FLAG_NZ(g_cpu.X);
label_D1A9:;
    /* $D1A9: 86 */ maybe_trigger_vblank(3); nes_write(0x08, g_cpu.X);
label_D1AB:;
    /* $D1AB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2D; FLAG_NZ(g_cpu.A);
label_D1AD:;
    /* $D1AD: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_D1AF:;
    /* $D1AF: 20 */ maybe_trigger_vblank(6); call_by_address(0xD1BC);
label_D1B2:;
    /* $D1B2: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_D1B3:;
    /* $D1B3: 85 */ maybe_trigger_vblank(3); nes_write(0x08, g_cpu.A);
label_D1B5:;
    /* $D1B5: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_D1B6:;
    /* $D1B6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_D1B8:;
    /* $D1B8: 8D */ maybe_trigger_vblank(4); nes_write(0x036A, g_cpu.A);
label_D1BB:; /* ExBGfxH */
    /* $D1BB: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyHandlers2::move_d_bowser() {
    (void)state_;
label_D00F:; /* MoveD_Bowser */
    /* $D00F: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF8C);
label_D012:;
    /* $D012: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD17B); return;
}

void EnemyHandlers2::erase_enemy_object() {
    (void)state_;
label_C998:; /* EraseEnemyObject */
    /* $C998: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C99A:;
    /* $C99A: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_C99C:;
    /* $C99C: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_C99E:;
    /* $C99E: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_C9A0:;
    /* $C9A0: 9D */ maybe_trigger_vblank(5); nes_write((0x0110 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C9A3:;
    /* $C9A3: 9D */ maybe_trigger_vblank(5); nes_write((0x0796 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C9A6:;
    /* $C9A6: 9D */ maybe_trigger_vblank(5); nes_write((0x0125 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C9A9:;
    /* $C9A9: 9D */ maybe_trigger_vblank(5); nes_write((0x03C5 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C9AC:;
    /* $C9AC: 9D */ maybe_trigger_vblank(5); nes_write((0x078A + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C9AF:;
    /* $C9AF: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyHandlers2::init_vstf() {
    (void)state_;
label_C363:; /* InitVStf */
    /* $C363: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C365:;
    /* $C365: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_C367:;
    /* $C367: 9D */ maybe_trigger_vblank(5); nes_write((0x0434 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C36A:;
    /* $C36A: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyHandlers2::init_enemy_object() {
    (void)state_;
label_C226:; /* InitEnemyObject */
    /* $C226: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C228:;
    /* $C228: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_C22A:;
    /* $C22A: 20 */ maybe_trigger_vblank(6); call_by_address(0xC26C);
label_C22D:; /* ExEPar */
    /* $C22D: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyHandlers2::check_frenzy_buffer() {
    (void)state_;
label_C216:; /* CheckFrenzyBuffer */
    /* $C216: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06CB); FLAG_NZ(g_cpu.A);
label_C219:;
    /* $C219: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C224;
label_C21B:;
    /* $C21B: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0398); FLAG_NZ(g_cpu.A);
label_C21E:;
    /* $C21E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_C220:;
    /* $C220: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C22D;
label_C222:;
    /* $C222: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_C224:; /* StrFre */
    /* $C224: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_C226:; /* InitEnemyObject */
    /* $C226: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C228:;
    /* $C228: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_C22A:;
    /* $C22A: 20 */ maybe_trigger_vblank(6); call_by_address(0xC26C);
label_C22D:; /* ExEPar */
    /* $C22D: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyHandlers2::check_three_bytes() {
    (void)state_;
label_C250:; /* CheckThreeBytes */
    /* $C250: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0739); FLAG_NZ(g_cpu.Y);
label_C253:;
    /* $C253: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE9) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C255:;
    /* $C255: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_C257:;
    /* $C257: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0E; g_cpu.C=(g_cpu.A>=0x0E)?1:0; FLAG_NZ(r&0xFF); }
label_C259:;
    /* $C259: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C25E;
label_C25B:; /* Inc3B */
    /* $C25B: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0739; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C25E:; /* Inc2B */
    /* $C25E: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0739; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C261:;
    /* $C261: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0739; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C264:;
    /* $C264: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C266:;
    /* $C266: 8D */ maybe_trigger_vblank(4); nes_write(0x073B, g_cpu.A);
label_C269:;
    /* $C269: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_C26B:;
    /* $C26B: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyHandlers2::handle_group_enemies() {
    (void)state_;
label_C71B:; /* HandleGroupEnemies */
    /* $C71B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_C71D:;
    /* $C71D: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C71E:;
    /* $C71E: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x37; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C720:;
    /* $C720: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_C721:;
    /* $C721: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_C723:;
    /* $C723: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_C730;
label_C725:;
    /* $C725: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_C726:;
    /* $C726: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x06; FLAG_NZ(g_cpu.Y);
label_C728:;
    /* $C728: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x076A); FLAG_NZ(g_cpu.A);
label_C72B:;
    /* $C72B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C72F;
label_C72D:;
    /* $C72D: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_C72F:; /* PullID */
    /* $C72F: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_C730:; /* SnglID */
    /* $C730: 84 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.Y);
label_C732:;
    /* $C732: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xB0; FLAG_NZ(g_cpu.Y);
label_C734:;
    /* $C734: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_C736:;
    /* $C736: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C73A;
label_C738:;
    /* $C738: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x70; FLAG_NZ(g_cpu.Y);
label_C73A:; /* SetYGp */
    /* $C73A: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_C73C:;
    /* $C73C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071B); FLAG_NZ(g_cpu.A);
label_C73F:;
    /* $C73F: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_C741:;
    /* $C741: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071D); FLAG_NZ(g_cpu.A);
label_C744:;
    /* $C744: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_C746:;
    /* $C746: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_C748:;
    /* $C748: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_C749:;
    /* $C749: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_C74A:;
    /* $C74A: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_C74D;
label_C74C:;
    /* $C74C: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C74D:; /* CntGrp */
    /* $C74D: 8C */ maybe_trigger_vblank(4); nes_write(0x06D3, g_cpu.Y);
label_C750:; /* GrLoop */
    /* $C750: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xFF; FLAG_NZ(g_cpu.X);
label_C752:; /* GSltLp */
    /* $C752: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_C753:;
    /* $C753: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x05; g_cpu.C=(g_cpu.X>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_C755:;
    /* $C755: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_C784;
label_C757:;
    /* $C757: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C759:;
    /* $C759: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C752;
    }
label_C75B:;
    /* $C75B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_C75D:;
    /* $C75D: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_C75F:;
    /* $C75F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_C761:;
    /* $C761: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_C763:;
    /* $C763: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x03); FLAG_NZ(g_cpu.A);
label_C765:;
    /* $C765: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_C767:;
    /* $C767: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C768:;
    /* $C768: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x18 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x18); g_cpu.A=r&0xFF; }
label_C76A:;
    /* $C76A: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_C76C:;
    /* $C76C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_C76E:;
    /* $C76E: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_C770:;
    /* $C770: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_C772:;
    /* $C772: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_C774:;
    /* $C774: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_C776:;
    /* $C776: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C778:;
    /* $C778: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_C77A:;
    /* $C77A: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_C77C:;
    /* $C77C: 20 */ maybe_trigger_vblank(6); call_by_address(0xC26C);
label_C77F:;
    /* $C77F: CE */ maybe_trigger_vblank(6); { uint16_t a=0x06D3; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C782:;
    /* $C782: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C750;
    }
label_C784:; /* NextED */
    /* $C784: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC25E); return;
}

void EnemyHandlers2::inc_3b() {
    (void)state_;
label_C25B:; /* Inc3B */
    /* $C25B: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0739; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C25E:; /* Inc2B */
    /* $C25E: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0739; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C261:;
    /* $C261: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0739; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C264:;
    /* $C264: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C266:;
    /* $C266: 8D */ maybe_trigger_vblank(4); nes_write(0x073B, g_cpu.A);
label_C269:;
    /* $C269: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_C26B:;
    /* $C26B: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyHandlers2::end_area_points() {
    (void)state_;
label_D336:; /* EndAreaPoints */
    /* $D336: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x0B; FLAG_NZ(g_cpu.Y);
label_D338:;
    /* $D338: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0753); FLAG_NZ(g_cpu.A);
label_D33B:;
    /* $D33B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D33F;
label_D33D:;
    /* $D33D: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x11; FLAG_NZ(g_cpu.Y);
label_D33F:; /* ELPGive */
    /* $D33F: 20 */ maybe_trigger_vblank(6); call_by_address(0x8F5F);
label_D342:;
    /* $D342: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0753); FLAG_NZ(g_cpu.A);
label_D345:;
    /* $D345: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D346:;
    /* $D346: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D347:;
    /* $D347: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D348:;
    /* $D348: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D349:;
    /* $D349: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x04; FLAG_NZ(g_cpu.A);
label_D34B:;
    /* $D34B: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBC36); return;
}

void EnemyHandlers2::award_game_timer_points() {
    (void)state_;
label_D312:; /* AwardGameTimerPoints */
    /* $D312: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07F8); FLAG_NZ(g_cpu.A);
label_D315:;
    /* $D315: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x07F9); FLAG_NZ(g_cpu.A);
label_D318:;
    /* $D318: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x07FA); FLAG_NZ(g_cpu.A);
label_D31B:;
    /* $D31B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { call_by_address(0xD30E); return; }
label_D31D:;
    /* $D31D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_D31F:;
    /* $D31F: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x04; FLAG_NZ(g_cpu.A);
label_D321:;
    /* $D321: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D327;
label_D323:;
    /* $D323: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_D325:;
    /* $D325: 85 */ maybe_trigger_vblank(3); nes_write(0xFE, g_cpu.A);
label_D327:; /* NoTTick */
    /* $D327: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x23; FLAG_NZ(g_cpu.Y);
label_D329:;
    /* $D329: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_D32B:;
    /* $D32B: 8D */ maybe_trigger_vblank(4); nes_write(0x0139, g_cpu.A);
label_D32E:;
    /* $D32E: 20 */ maybe_trigger_vblank(6); call_by_address(0x8F5F);
label_D331:;
    /* $D331: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_D333:;
    /* $D333: 8D */ maybe_trigger_vblank(4); nes_write(0x0139, g_cpu.A);
label_D336:; /* EndAreaPoints */
    /* $D336: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x0B; FLAG_NZ(g_cpu.Y);
label_D338:;
    /* $D338: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0753); FLAG_NZ(g_cpu.A);
label_D33B:;
    /* $D33B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D33F;
label_D33D:;
    /* $D33D: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x11; FLAG_NZ(g_cpu.Y);
label_D33F:; /* ELPGive */
    /* $D33F: 20 */ maybe_trigger_vblank(6); call_by_address(0x8F5F);
label_D342:;
    /* $D342: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0753); FLAG_NZ(g_cpu.A);
label_D345:;
    /* $D345: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D346:;
    /* $D346: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D347:;
    /* $D347: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D348:;
    /* $D348: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D349:;
    /* $D349: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x04; FLAG_NZ(g_cpu.A);
label_D34B:;
    /* $D34B: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBC36); return;
}

}  // namespace smb::semcomp
