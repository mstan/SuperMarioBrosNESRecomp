// semcomp/PlayerGraphics.cpp — Phase 17 verbatim ports of player-graphics routines.
//
// Multi-entry-body groups are modeled as anonymous-namespace static helpers,
// each accepting an _entry index, mirroring the recompiler's emit pattern.
// The class methods are thin wrappers that call into the helper with the
// appropriate _entry. All sub-callees stay natural-generated.
#include "semcomp/PlayerGraphics.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {
namespace {

// $F12A RelativePlayerPosition body. Entry 0 starts at $F12A (X=0),
// entry 1 starts at $F12C (skip the X=0 set — caller picked X).
void f12a_body(int _entry) {
    switch (_entry) {
        case 1: goto label_F12C;
    }
label_F12A:; /* RelativePlayerPosition */
    /* $F12A: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_F12C:;
    /* $F12C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_F12E:;
    /* $F12E: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF142); return;
}

// $EFA4 DrawPlayer_Intermediate body. 3 entries.
void efa4_body(int _entry) {
    switch (_entry) {
        case 1: goto label_EFA6;
        case 2: goto label_EFAC;
    }
label_EFA4:; /* DrawPlayer_Intermediate */
    /* $EFA4: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x05; FLAG_NZ(g_cpu.X);
label_EFA6:; /* PIntLoop */
    /* $EFA6: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xEF9E + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EFA9:;
    /* $EFA9: 95 */ maybe_trigger_vblank(4); nes_write((0x02 + g_cpu.X) & 0xFF, g_cpu.A);
label_EFAB:;
    /* $EFAB: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_EFAC:;
    /* $EFAC: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
        maybe_trigger_vblank(2);
        goto label_EFA6;
    }
label_EFAE:;
    /* $EFAE: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xB8; FLAG_NZ(g_cpu.X);
label_EFB0:;
    /* $EFB0: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x04; FLAG_NZ(g_cpu.Y);
label_EFB2:;
    /* $EFB2: 20 */ maybe_trigger_vblank(6); call_by_address(0xEFDC);
label_EFB5:;
    /* $EFB5: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0226); FLAG_NZ(g_cpu.A);
label_EFB8:;
    /* $EFB8: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_EFBA:;
    /* $EFBA: 8D */ maybe_trigger_vblank(4); nes_write(0x0222, g_cpu.A);
label_EFBD:;
    /* $EFBD: 60 */ maybe_trigger_vblank(6);
    return;
}

// $EEE9 PlayerGfxHandler body. 13 entries.
void eee9_body(int _entry) {
    switch (_entry) {
        case 1: goto label_EEF7;
        case 2: goto label_EF85;
        case 3: goto label_EEFC;
        case 4: goto label_EEFE;
        case 5: goto label_EEEE;
        case 6: goto label_EEF0;
        case 7: goto label_EEF1;
        case 8: goto label_EF10;
        case 9: goto label_EF01;
        case 10: goto label_EF42;
        case 11: goto label_EF7A;
        case 12: goto label_EF97;
    }
label_EEE9:; /* PlayerGfxHandler */
    /* $EEE9: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x079E); FLAG_NZ(g_cpu.A);
label_EEEC:;
    /* $EEEC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EEF3;
label_EEEE:;
    /* $EEEE: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_EEF0:;
    /* $EEF0: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EEF1:;
    /* $EEF1: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_EF33;
label_EEF3:; /* CntPl */
    /* $EEF3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0E); FLAG_NZ(g_cpu.A);
label_EEF5:;
    /* $EEF5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0B; g_cpu.C=(g_cpu.A>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_EEF7:;
    /* $EEF7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EF40;
label_EEF9:;
    /* $EEF9: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x070B); FLAG_NZ(g_cpu.A);
label_EEFC:;
    /* $EEFC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EF3A;
label_EEFE:;
    /* $EEFE: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0704); FLAG_NZ(g_cpu.Y);
label_EF01:;
    /* $EF01: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EF34;
label_EF03:;
    /* $EF03: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x1D); FLAG_NZ(g_cpu.A);
label_EF05:;
    /* $EF05: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_EF07:;
    /* $EF07: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EF34;
label_EF09:;
    /* $EF09: 20 */ maybe_trigger_vblank(6); call_by_address(0xEF34);
label_EF0C:;
    /* $EF0C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_EF0E:;
    /* $EF0E: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x04; FLAG_NZ(g_cpu.A);
label_EF10:;
    /* $EF10: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EF33;
label_EF12:;
    /* $EF12: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_EF13:;
    /* $EF13: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06E4); FLAG_NZ(g_cpu.Y);
label_EF16:;
    /* $EF16: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x33); FLAG_NZ(g_cpu.A);
label_EF18:;
    /* $EF18: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EF19:;
    /* $EF19: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_EF1F;
label_EF1B:;
    /* $EF1B: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EF1C:;
    /* $EF1C: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EF1D:;
    /* $EF1D: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EF1E:;
    /* $EF1E: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EF1F:; /* SwimKT */
    /* $EF1F: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0754); FLAG_NZ(g_cpu.A);
label_EF22:;
    /* $EF22: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EF2D;
label_EF24:;
    /* $EF24: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0219 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EF27:;
    /* $EF27: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xEEB5); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_EF2A:;
    /* $EF2A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EF33;
label_EF2C:;
    /* $EF2C: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_EF2D:; /* BigKTS */
    /* $EF2D: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xEEE7 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EF30:;
    /* $EF30: 99 */ maybe_trigger_vblank(5); nes_write((0x0219 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EF33:; /* ExPGH */
    /* $EF33: 60 */ maybe_trigger_vblank(6);
    return;
label_EF34:; /* FindPlayerAction */
    /* $EF34: 20 */ maybe_trigger_vblank(6); call_by_address(0xEFEC);
label_EF37:;
    /* $EF37: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xEF45); return;
label_EF3A:; /* DoChangeSize */
    /* $EF3A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF0B0);
label_EF3D:;
    /* $EF3D: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xEF45); return;
label_EF40:; /* PlayerKilled */
    /* $EF40: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x0E; FLAG_NZ(g_cpu.Y);
label_EF42:;
    /* $EF42: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xEE07 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EF45:; /* PlayerGfxProcessing */
    /* $EF45: 8D */ maybe_trigger_vblank(4); nes_write(0x06D5, g_cpu.A);
label_EF48:;
    /* $EF48: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_EF4A:;
    /* $EF4A: 20 */ maybe_trigger_vblank(6); call_by_address(0xEFBE);
label_EF4D:;
    /* $EF4D: 20 */ maybe_trigger_vblank(6); call_by_address(0xF0E9);
label_EF50:;
    /* $EF50: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0711); FLAG_NZ(g_cpu.A);
label_EF53:;
    /* $EF53: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EF7A;
label_EF55:;
    /* $EF55: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_EF57:;
    /* $EF57: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0781); FLAG_NZ(g_cpu.A);
label_EF5A:;
    /* $EF5A: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0711); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_EF5D:;
    /* $EF5D: 8C */ maybe_trigger_vblank(4); nes_write(0x0711, g_cpu.Y);
label_EF60:;
    /* $EF60: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_EF7A;
label_EF62:;
    /* $EF62: 8D */ maybe_trigger_vblank(4); nes_write(0x0711, g_cpu.A);
label_EF65:;
    /* $EF65: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x07; FLAG_NZ(g_cpu.Y);
label_EF67:;
    /* $EF67: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xEE07 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EF6A:;
    /* $EF6A: 8D */ maybe_trigger_vblank(4); nes_write(0x06D5, g_cpu.A);
label_EF6D:;
    /* $EF6D: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x04; FLAG_NZ(g_cpu.Y);
label_EF6F:;
    /* $EF6F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x57); FLAG_NZ(g_cpu.A);
label_EF71:;
    /* $EF71: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x0C); FLAG_NZ(g_cpu.A);
label_EF73:;
    /* $EF73: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EF76;
label_EF75:;
    /* $EF75: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EF76:; /* SUpdR */
    /* $EF76: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_EF77:;
    /* $EF77: 20 */ maybe_trigger_vblank(6); call_by_address(0xEFBE);
label_EF7A:; /* PlayerOffscreenChk */
    /* $EF7A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D0); FLAG_NZ(g_cpu.A);
label_EF7D:;
    /* $EF7D: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EF7E:;
    /* $EF7E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EF7F:;
    /* $EF7F: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EF80:;
    /* $EF80: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EF81:;
    /* $EF81: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_EF83:;
    /* $EF83: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_EF85:;
    /* $EF85: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06E4); FLAG_NZ(g_cpu.A);
label_EF88:;
    /* $EF88: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_EF89:;
    /* $EF89: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x18 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x18); g_cpu.A=r&0xFF; }
label_EF8B:;
    /* $EF8B: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_EF8C:; /* PROfsLoop */
    /* $EF8C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_EF8E:;
    /* $EF8E: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_EF90:;
    /* $EF90: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_EF95;
label_EF92:;
    /* $EF92: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5C1);
label_EF95:; /* NPROffscr */
    /* $EF95: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_EF96:;
    /* $EF96: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_EF97:;
    /* $EF97: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x08; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_EF99:;
    /* $EF99: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_EF9A:;
    /* $EF9A: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_EF9B:;
    /* $EF9B: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
        maybe_trigger_vblank(2);
        goto label_EF8C;
    }
label_EF9D:;
    /* $EF9D: 60 */ maybe_trigger_vblank(6);
    return;
}

}  // namespace

// ---- Single-entry routines ------------------------------------------------

void PlayerGraphics::get_player_colors() {
    (void)state_;
label_85F1:; /* GetPlayerColors */
    /* $85F1: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x0300); FLAG_NZ(g_cpu.X);
label_85F4:;
    /* $85F4: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_85F6:;
    /* $85F6: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0753); FLAG_NZ(g_cpu.A);
label_85F9:;
    /* $85F9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_85FD;
label_85FB:;
    /* $85FB: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x04; FLAG_NZ(g_cpu.Y);
label_85FD:; /* ChkFiery */
    /* $85FD: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0756); FLAG_NZ(g_cpu.A);
label_8600:;
    /* $8600: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_8602:;
    /* $8602: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_8606;
label_8604:;
    /* $8604: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x08; FLAG_NZ(g_cpu.Y);
label_8606:; /* StartClrGet */
    /* $8606: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_8608:;
    /* $8608: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_860A:; /* ClrGetLoop */
    /* $860A: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x85D7 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_860D:;
    /* $860D: 9D */ maybe_trigger_vblank(5); nes_write((0x0304 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8610:;
    /* $8610: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8611:;
    /* $8611: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_8612:;
    /* $8612: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8614:;
    /* $8614: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
        maybe_trigger_vblank(2);
        goto label_860A;
    }
label_8616:;
    /* $8616: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x0300); FLAG_NZ(g_cpu.X);
label_8619:;
    /* $8619: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0744); FLAG_NZ(g_cpu.Y);
label_861C:;
    /* $861C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_8621;
label_861E:;
    /* $861E: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_8621:; /* SetBGColor */
    /* $8621: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x85CF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8624:;
    /* $8624: 9D */ maybe_trigger_vblank(5); nes_write((0x0304 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8627:;
    /* $8627: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x3F; FLAG_NZ(g_cpu.A);
label_8629:;
    /* $8629: 9D */ maybe_trigger_vblank(5); nes_write((0x0301 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_862C:;
    /* $862C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_862E:;
    /* $862E: 9D */ maybe_trigger_vblank(5); nes_write((0x0302 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8631:;
    /* $8631: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_8633:;
    /* $8633: 9D */ maybe_trigger_vblank(5); nes_write((0x0303 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8636:;
    /* $8636: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8638:;
    /* $8638: 9D */ maybe_trigger_vblank(5); nes_write((0x0308 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_863B:;
    /* $863B: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_863C:;
    /* $863C: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_863D:;
    /* $863D: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x07 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x07); g_cpu.A=r&0xFF; }
label_863F:; /* SetVRAMOffset */
    /* $863F: 8D */ maybe_trigger_vblank(4); nes_write(0x0300, g_cpu.A);
label_8642:;
    /* $8642: 60 */ maybe_trigger_vblank(6);
}

void PlayerGraphics::draw_player_loop() {
    (void)state_;
label_EFDC:; /* DrawPlayerLoop */
    /* $EFDC: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xEE17 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EFDF:;
    /* $EFDF: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_EFE1:;
    /* $EFE1: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xEE18 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EFE4:;
    /* $EFE4: 20 */ maybe_trigger_vblank(6); call_by_address(0xEBB2);
label_EFE7:;
    /* $EFE7: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x07; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_EFE9:;
    /* $EFE9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
        maybe_trigger_vblank(2);
        goto label_EFDC;
    }
label_EFEB:;
    /* $EFEB: 60 */ maybe_trigger_vblank(6);
}

// ---- Multi-entry wrappers --------------------------------------------------

void PlayerGraphics::relative_player_position()      { (void)state_; f12a_body(0); }
void PlayerGraphics::relative_player_position_f12c() { (void)state_; f12a_body(1); }

void PlayerGraphics::draw_player_intermediate()          { (void)state_; efa4_body(0); }
void PlayerGraphics::draw_player_intermediate_pintloop() { (void)state_; efa4_body(1); }
void PlayerGraphics::draw_player_intermediate_efac()     { (void)state_; efa4_body(2); }

void PlayerGraphics::player_gfx_handler()      { (void)state_; eee9_body(0); }
void PlayerGraphics::player_gfx_handler_eef7() { (void)state_; eee9_body(1); }
void PlayerGraphics::player_gfx_handler_ef85() { (void)state_; eee9_body(2); }
void PlayerGraphics::player_gfx_handler_eefc() { (void)state_; eee9_body(3); }
void PlayerGraphics::player_gfx_handler_eefe() { (void)state_; eee9_body(4); }
void PlayerGraphics::player_gfx_handler_eeee() { (void)state_; eee9_body(5); }
void PlayerGraphics::player_gfx_handler_eef0() { (void)state_; eee9_body(6); }
void PlayerGraphics::player_gfx_handler_eef1() { (void)state_; eee9_body(7); }
void PlayerGraphics::player_gfx_handler_ef10() { (void)state_; eee9_body(8); }
void PlayerGraphics::player_gfx_handler_ef01() { (void)state_; eee9_body(9); }
void PlayerGraphics::player_gfx_handler_ef42() { (void)state_; eee9_body(10); }
void PlayerGraphics::player_gfx_handler_ef7a() { (void)state_; eee9_body(11); }
void PlayerGraphics::player_gfx_handler_ef97() { (void)state_; eee9_body(12); }

}  // namespace smb::semcomp
