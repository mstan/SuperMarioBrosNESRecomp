// semcomp/PlayerCollision.cpp — Phase 16 port of $DC64 PlayerBGCollision.
//
// VERBATIM PORT — the body is copied directly from the recompiler's
// generated super-mario-bros_full.c (~413 lines). The recompiler's
// own emission is the canonical 6502 semantics; mirroring it here byte
// for byte is the safest way to take ownership without introducing
// subtle behavioral drift.
//
// All inner labels are reproduced as C++ goto labels with the same names.
// PHA/PLA at $DD06/$DD0C are kept as g_ram[]-based stack ops to match
// the generated code exactly.
#include "semcomp/PlayerCollision.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

void PlayerCollision::player_bg_collision() {
    (void)state_;  // Body uses nes_read/nes_write directly for verbatim fidelity.

label_DC64:; /* PlayerBGCollision */
    /* $DC64: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0716); FLAG_NZ(g_cpu.A);
label_DC67:;
    /* $DC67: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DC97;
label_DC69:;
    /* $DC69: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0E); FLAG_NZ(g_cpu.A);
label_DC6B:;
    /* $DC6B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0B; g_cpu.C=(g_cpu.A>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_DC6D:;
    /* $DC6D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DC97;
label_DC6F:;
    /* $DC6F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_DC71:;
    /* $DC71: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DC97;
label_DC73:;
    /* $DC73: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_DC75:;
    /* $DC75: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0704); FLAG_NZ(g_cpu.Y);
label_DC78:;
    /* $DC78: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DC84;
label_DC7A:;
    /* $DC7A: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x1D); FLAG_NZ(g_cpu.A);
label_DC7C:;
    /* $DC7C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DC82;
label_DC7E:;
    /* $DC7E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_DC80:;
    /* $DC80: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DC86;
label_DC82:; /* SetFallS */
    /* $DC82: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_DC84:; /* SetPSte */
    /* $DC84: 85 */ maybe_trigger_vblank(3); nes_write(0x1D, g_cpu.A);
label_DC86:; /* ChkOnScr */
    /* $DC86: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xB5); FLAG_NZ(g_cpu.A);
label_DC88:;
    /* $DC88: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_DC8A:;
    /* $DC8A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DC97;
label_DC8C:;
    /* $DC8C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_DC8E:;
    /* $DC8E: 8D */ maybe_trigger_vblank(4); nes_write(0x0490, g_cpu.A);
label_DC91:;
    /* $DC91: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_DC93:;
    /* $DC93: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xCF; g_cpu.C=(g_cpu.A>=0xCF)?1:0; FLAG_NZ(r&0xFF); }
label_DC95:;
    /* $DC95: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DC98;
label_DC97:; /* ExPBGCol */
    /* $DC97: 60 */ maybe_trigger_vblank(6);
    return;
label_DC98:; /* ChkCollSize */
    /* $DC98: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_DC9A:;
    /* $DC9A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0714); FLAG_NZ(g_cpu.A);
label_DC9D:;
    /* $DC9D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DCAB;
label_DC9F:;
    /* $DC9F: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0754); FLAG_NZ(g_cpu.A);
label_DCA2:;
    /* $DCA2: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DCAB;
label_DCA4:;
    /* $DCA4: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DCA5:;
    /* $DCA5: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0704); FLAG_NZ(g_cpu.A);
label_DCA8:;
    /* $DCA8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DCAB;
label_DCAA:;
    /* $DCAA: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DCAB:; /* GBBAdr */
    /* $DCAB: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE3AD + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DCAE:;
    /* $DCAE: 85 */ maybe_trigger_vblank(3); nes_write(0xEB, g_cpu.A);
label_DCB0:;
    /* $DCB0: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_DCB1:;
    /* $DCB1: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x0754); FLAG_NZ(g_cpu.X);
label_DCB4:;
    /* $DCB4: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0714); FLAG_NZ(g_cpu.A);
label_DCB7:;
    /* $DCB7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DCBA;
label_DCB9:;
    /* $DCB9: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_DCBA:; /* HeadChk */
    /* $DCBA: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_DCBC:;
    /* $DCBC: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDC62 + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_DCBF:;
    /* $DCBF: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DCF6;
label_DCC1:;
    /* $DCC1: 20 */ maybe_trigger_vblank(6); call_by_address(0xE3E9);
label_DCC4:;
    /* $DCC4: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DCF6;
label_DCC6:;
    /* $DCC6: 20 */ maybe_trigger_vblank(6); call_by_address(0xDFA1);
label_DCC9:;
    /* $DCC9: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DD1A;
label_DCCB:;
    /* $DCCB: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x9F); FLAG_NZ(g_cpu.Y);
label_DCCD:;
    /* $DCCD: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_DCF6;
label_DCCF:;
    /* $DCCF: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x04); FLAG_NZ(g_cpu.Y);
label_DCD1:;
    /* $DCD1: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x04; g_cpu.C=(g_cpu.Y>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_DCD3:;
    /* $DCD3: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DCF6;
label_DCD5:;
    /* $DCD5: 20 */ maybe_trigger_vblank(6); call_by_address(0xDF8F);
label_DCD8:;
    /* $DCD8: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DCEA;
label_DCDA:;
    /* $DCDA: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_DCDD:;
    /* $DCDD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DCF2;
label_DCDF:;
    /* $DCDF: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0784); FLAG_NZ(g_cpu.Y);
label_DCE2:;
    /* $DCE2: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DCF2;
label_DCE4:;
    /* $DCE4: 20 */ maybe_trigger_vblank(6); call_by_address(0xBCED);
label_DCE7:;
    /* $DCE7: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xDCF6); return;
label_DCEA:; /* SolidOrClimb */
    /* $DCEA: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x26; g_cpu.C=(g_cpu.A>=0x26)?1:0; FLAG_NZ(r&0xFF); }
label_DCEC:;
    /* $DCEC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DCF2;
label_DCEE:;
    /* $DCEE: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_DCF0:;
    /* $DCF0: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_DCF2:; /* NYSpd */
    /* $DCF2: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_DCF4:;
    /* $DCF4: 85 */ maybe_trigger_vblank(3); nes_write(0x9F, g_cpu.A);
label_DCF6:; /* DoFootCheck */
    /* $DCF6: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xEB); FLAG_NZ(g_cpu.Y);
label_DCF8:;
    /* $DCF8: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_DCFA:;
    /* $DCFA: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xCF; g_cpu.C=(g_cpu.A>=0xCF)?1:0; FLAG_NZ(r&0xFF); }
label_DCFC:;
    /* $DCFC: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DD5E;
label_DCFE:;
    /* $DCFE: 20 */ maybe_trigger_vblank(6); call_by_address(0xE3E8);
label_DD01:;
    /* $DD01: 20 */ maybe_trigger_vblank(6); call_by_address(0xDFA1);
label_DD04:;
    /* $DD04: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DD1A;
label_DD06:;
    /* $DD06: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_DD07:;
    /* $DD07: 20 */ maybe_trigger_vblank(6); call_by_address(0xE3E8);
label_DD0A:;
    /* $DD0A: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_DD0C:;
    /* $DD0C: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_DD0D:;
    /* $DD0D: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_DD0F:;
    /* $DD0F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DD1D;
label_DD11:;
    /* $DD11: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_DD13:;
    /* $DD13: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DD5E;
label_DD15:;
    /* $DD15: 20 */ maybe_trigger_vblank(6); call_by_address(0xDFA1);
label_DD18:;
    /* $DD18: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DD1D;
label_DD1A:; /* AwardTouchedCoin */
    /* $DD1A: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xDE05); return;
label_DD1D:; /* ChkFootMTile */
    /* $DD1D: 20 */ maybe_trigger_vblank(6); call_by_address(0xDF9A);
label_DD20:;
    /* $DD20: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DD5E;
label_DD22:;
    /* $DD22: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x9F); FLAG_NZ(g_cpu.Y);
label_DD24:;
    /* $DD24: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_DD5E;
label_DD26:;
    /* $DD26: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xC5; g_cpu.C=(g_cpu.A>=0xC5)?1:0; FLAG_NZ(r&0xFF); }
label_DD28:;
    /* $DD28: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DD2D;
label_DD2A:;
    /* $DD2A: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xDE0E); return;
label_DD2D:; /* ContChk */
    /* $DD2D: 20 */ maybe_trigger_vblank(6); call_by_address(0xDEBD);
label_DD30:;
    /* $DD30: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DD5E;
label_DD32:;
    /* $DD32: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x070E); FLAG_NZ(g_cpu.Y);
label_DD35:;
    /* $DD35: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DD5A;
label_DD37:;
    /* $DD37: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x04); FLAG_NZ(g_cpu.Y);
label_DD39:;
    /* $DD39: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x05; g_cpu.C=(g_cpu.Y>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_DD3B:;
    /* $DD3B: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DD44;
label_DD3D:;
    /* $DD3D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x45); FLAG_NZ(g_cpu.A);
label_DD3F:;
    /* $DD3F: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_DD41:;
    /* $DD41: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xDF4B); return;
label_DD44:; /* LandPlyr */
    /* $DD44: 20 */ maybe_trigger_vblank(6); call_by_address(0xDEC4);
label_DD47:;
    /* $DD47: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF0; FLAG_NZ(g_cpu.A);
label_DD49:;
    /* $DD49: 25 */ maybe_trigger_vblank(3); g_cpu.A &= nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_DD4B:;
    /* $DD4B: 85 */ maybe_trigger_vblank(3); nes_write(0xCE, g_cpu.A);
label_DD4D:;
    /* $DD4D: 20 */ maybe_trigger_vblank(6); call_by_address(0xDEE8);
label_DD50:;
    /* $DD50: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DD52:;
    /* $DD52: 85 */ maybe_trigger_vblank(3); nes_write(0x9F, g_cpu.A);
label_DD54:;
    /* $DD54: 8D */ maybe_trigger_vblank(4); nes_write(0x0433, g_cpu.A);
label_DD57:;
    /* $DD57: 8D */ maybe_trigger_vblank(4); nes_write(0x0484, g_cpu.A);
label_DD5A:; /* InitSteP */
    /* $DD5A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DD5C:;
    /* $DD5C: 85 */ maybe_trigger_vblank(3); nes_write(0x1D, g_cpu.A);
label_DD5E:; /* DoPlayerSideCheck */
    /* $DD5E: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xEB); FLAG_NZ(g_cpu.Y);
label_DD60:;
    /* $DD60: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DD61:;
    /* $DD61: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DD62:;
    /* $DD62: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_DD64:;
    /* $DD64: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_DD66:; /* SideCheckLoop */
    /* $DD66: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DD67:;
    /* $DD67: 84 */ maybe_trigger_vblank(3); nes_write(0xEB, g_cpu.Y);
label_DD69:;
    /* $DD69: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_DD6B:;
    /* $DD6B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_DD6D:;
    /* $DD6D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DD85;
label_DD6F:;
    /* $DD6F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xE4; g_cpu.C=(g_cpu.A>=0xE4)?1:0; FLAG_NZ(r&0xFF); }
label_DD71:;
    /* $DD71: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DD9B;
label_DD73:;
    /* $DD73: 20 */ maybe_trigger_vblank(6); call_by_address(0xE3EC);
label_DD76:;
    /* $DD76: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DD85;
label_DD78:;
    /* $DD78: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x1C; g_cpu.C=(g_cpu.A>=0x1C)?1:0; FLAG_NZ(r&0xFF); }
label_DD7A:;
    /* $DD7A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DD85;
label_DD7C:;
    /* $DD7C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x6B; g_cpu.C=(g_cpu.A>=0x6B)?1:0; FLAG_NZ(r&0xFF); }
label_DD7E:;
    /* $DD7E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DD85;
label_DD80:;
    /* $DD80: 20 */ maybe_trigger_vblank(6); call_by_address(0xDF9A);
label_DD83:;
    /* $DD83: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DD9C;
label_DD85:; /* BHalf */
    /* $DD85: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xEB); FLAG_NZ(g_cpu.Y);
label_DD87:;
    /* $DD87: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DD88:;
    /* $DD88: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_DD8A:;
    /* $DD8A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_DD8C:;
    /* $DD8C: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DD9B;
label_DD8E:;
    /* $DD8E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xD0; g_cpu.C=(g_cpu.A>=0xD0)?1:0; FLAG_NZ(r&0xFF); }
label_DD90:;
    /* $DD90: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DD9B;
label_DD92:;
    /* $DD92: 20 */ maybe_trigger_vblank(6); call_by_address(0xE3EC);
label_DD95:;
    /* $DD95: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DD9C;
label_DD97:;
    /* $DD97: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DD99:;
    /* $DD99: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
        maybe_trigger_vblank(2);
        goto label_DD66;
    }
label_DD9B:; /* ExSCH */
    /* $DD9B: 60 */ maybe_trigger_vblank(6);
    return;
label_DD9C:; /* CheckSideMTiles */
    /* $DD9C: 20 */ maybe_trigger_vblank(6); call_by_address(0xDEBD);
label_DD9F:;
    /* $DD9F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DE02;
label_DDA1:;
    /* $DDA1: 20 */ maybe_trigger_vblank(6); call_by_address(0xDF9A);
label_DDA4:;
    /* $DDA4: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DDA9;
label_DDA6:;
    /* $DDA6: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xDE2E); return;
label_DDA9:; /* ContSChk */
    /* $DDA9: 20 */ maybe_trigger_vblank(6); call_by_address(0xDFA1);
label_DDAC:;
    /* $DDAC: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DE05;
label_DDAE:;
    /* $DDAE: 20 */ maybe_trigger_vblank(6); call_by_address(0xDEDD);
label_DDB1:;
    /* $DDB1: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DDBB;
label_DDB3:;
    /* $DDB3: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x070E); FLAG_NZ(g_cpu.A);
label_DDB6:;
    /* $DDB6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DE02;
label_DDB8:;
    /* $DDB8: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xDDFF); return;
label_DDBB:; /* ChkPBtm */
    /* $DDBB: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x1D); FLAG_NZ(g_cpu.Y);
label_DDBD:;
    /* $DDBD: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x00; g_cpu.C=(g_cpu.Y>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_DDBF:;
    /* $DDBF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DDFF;
label_DDC1:;
    /* $DDC1: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x33); FLAG_NZ(g_cpu.Y);
label_DDC3:;
    /* $DDC3: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DDC4:;
    /* $DDC4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DDFF;
label_DDC6:;
    /* $DDC6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x6C; g_cpu.C=(g_cpu.A>=0x6C)?1:0; FLAG_NZ(r&0xFF); }
label_DDC8:;
    /* $DDC8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DDCE;
label_DDCA:;
    /* $DDCA: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x1F; g_cpu.C=(g_cpu.A>=0x1F)?1:0; FLAG_NZ(r&0xFF); }
label_DDCC:;
    /* $DDCC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DDFF;
label_DDCE:; /* PipeDwnS */
    /* $DDCE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03C4); FLAG_NZ(g_cpu.A);
label_DDD1:;
    /* $DDD1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DDD7;
label_DDD3:;
    /* $DDD3: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x10; FLAG_NZ(g_cpu.Y);
label_DDD5:;
    /* $DDD5: 84 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.Y);
label_DDD7:; /* PlyrPipe */
    /* $DDD7: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x20; FLAG_NZ(g_cpu.A);
label_DDD9:;
    /* $DDD9: 8D */ maybe_trigger_vblank(4); nes_write(0x03C4, g_cpu.A);
label_DDDC:;
    /* $DDDC: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x86); FLAG_NZ(g_cpu.A);
label_DDDE:;
    /* $DDDE: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_DDE0:;
    /* $DDE0: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DDF0;
label_DDE2:;
    /* $DDE2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_DDE4:;
    /* $DDE4: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071A); FLAG_NZ(g_cpu.A);
label_DDE7:;
    /* $DDE7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DDEA;
label_DDE9:;
    /* $DDE9: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DDEA:; /* SetCATmr */
    /* $DDEA: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xDE03 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DDED:;
    /* $DDED: 8D */ maybe_trigger_vblank(4); nes_write(0x06DE, g_cpu.A);
label_DDF0:; /* ChkGERtn */
    /* $DDF0: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0E); FLAG_NZ(g_cpu.A);
label_DDF2:;
    /* $DDF2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_DDF4:;
    /* $DDF4: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DE02;
label_DDF6:;
    /* $DDF6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_DDF8:;
    /* $DDF8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DE02;
label_DDFA:;
    /* $DDFA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_DDFC:;
    /* $DDFC: 85 */ maybe_trigger_vblank(3); nes_write(0x0E, g_cpu.A);
label_DDFE:;
    /* $DDFE: 60 */ maybe_trigger_vblank(6);
    return;
label_DDFF:; /* StopPlayerMove */
    /* $DDFF: 20 */ maybe_trigger_vblank(6); call_by_address(0xDF4B);
label_DE02:; /* ExCSM */
    /* $DE02: 60 */ maybe_trigger_vblank(6);
    return;
label_DE03:; /* AreaChangeTimerData */
    /* $DE03: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x34; FLAG_NZ(g_cpu.Y);
label_DE05:; /* HandleCoinMetatile */
    /* $DE05: 20 */ maybe_trigger_vblank(6); call_by_address(0xDE1C);
label_DE08:;
    /* $DE08: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0748; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DE0B:;
    /* $DE0B: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBBFE); return;
}

}  // namespace smb::semcomp
