// semcomp/DamageChain.cpp — Phase 22 verbatim port of damage chain.
#include "semcomp/DamageChain.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {
namespace {

// Shared body for $D92C/$D931. Entry 0 enters at $D92C (gate check first),
// entry 1 enters at $D931 (skip the gate).
void damage_body(int _entry) {
    switch (_entry) {
        case 1: goto label_D931;
    }
label_D92C:; /* InjurePlayer */
    /* $D92C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x079E); FLAG_NZ(g_cpu.A);
label_D92F:;
    /* $D92F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D955;
label_D931:; /* ForceInjury */
    /* $D931: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x0756); FLAG_NZ(g_cpu.X);
label_D934:;
    /* $D934: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D958;
label_D936:;
    /* $D936: 8D */ maybe_trigger_vblank(4); nes_write(0x0756, g_cpu.A);
label_D939:;
    /* $D939: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_D93B:;
    /* $D93B: 8D */ maybe_trigger_vblank(4); nes_write(0x079E, g_cpu.A);
label_D93E:;
    /* $D93E: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D93F:;
    /* $D93F: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_D941:;
    /* $D941: 20 */ maybe_trigger_vblank(6); call_by_address(0x85F1);
label_D944:;
    /* $D944: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_D946:; /* SetKRout */
    /* $D946: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_D948:; /* SetPRout */
    /* $D948: 85 */ maybe_trigger_vblank(3); nes_write(0x0E, g_cpu.A);
label_D94A:;
    /* $D94A: 84 */ maybe_trigger_vblank(3); nes_write(0x1D, g_cpu.Y);
label_D94C:;
    /* $D94C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xFF; FLAG_NZ(g_cpu.Y);
label_D94E:;
    /* $D94E: 8C */ maybe_trigger_vblank(4); nes_write(0x0747, g_cpu.Y);
label_D951:;
    /* $D951: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D952:;
    /* $D952: 8C */ maybe_trigger_vblank(4); nes_write(0x0775, g_cpu.Y);
label_D955:; /* ExInjColRoutines */
    /* $D955: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D957:;
    /* $D957: 60 */ maybe_trigger_vblank(6);
    return;
label_D958:; /* KillPlayer */
    /* $D958: 86 */ maybe_trigger_vblank(3); nes_write(0x57, g_cpu.X);
label_D95A:;
    /* $D95A: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_D95B:;
    /* $D95B: 86 */ maybe_trigger_vblank(3); nes_write(0xFC, g_cpu.X);
label_D95D:;
    /* $D95D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFC; FLAG_NZ(g_cpu.A);
label_D95F:;
    /* $D95F: 85 */ maybe_trigger_vblank(3); nes_write(0x9F, g_cpu.A);
label_D961:;
    /* $D961: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0B; FLAG_NZ(g_cpu.A);
label_D963:;
    /* $D963: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
        maybe_trigger_vblank(2);
        goto label_D946;
    }
label_D965:; /* StompedEnemyPtsData */
    /* $D965: 02 */ maybe_trigger_vblank(2);
label_D966:;
    /* $D966: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x05; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D968:;
    /* $D968: 06 */ maybe_trigger_vblank(5); { uint16_t a=0xB5; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D96A:;
    /* $D96A: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0xC9 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D96C:;
    /* $D96C: 12 */ maybe_trigger_vblank(2);
label_D96D:;
    /* $D96D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
        maybe_trigger_vblank(2);
        goto label_D92C;
    }
label_D96F:;
    /* $D96F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_D971:;
    /* $D971: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_D973:;
    /* $D973: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D975:;
    /* $D975: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_D977:;
    /* $D977: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x14; g_cpu.C=(g_cpu.A>=0x14)?1:0; FLAG_NZ(r&0xFF); }
label_D979:;
    /* $D979: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D996;
label_D97B:;
    /* $D97B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_D97D:;
    /* $D97D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D996;
label_D97F:;
    /* $D97F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x33; g_cpu.C=(g_cpu.A>=0x33)?1:0; FLAG_NZ(r&0xFF); }
label_D981:;
    /* $D981: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D996;
label_D983:;
    /* $D983: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0C; g_cpu.C=(g_cpu.A>=0x0C)?1:0; FLAG_NZ(r&0xFF); }
label_D985:;
    /* $D985: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D996;
label_D987:;
    /* $D987: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D988:;
    /* $D988: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_D98A:;
    /* $D98A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D996;
label_D98C:;
    /* $D98C: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D98D:;
    /* $D98D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_D98F:;
    /* $D98F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D996;
label_D991:;
    /* $D991: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D992:;
    /* $D992: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_D994:;
    /* $D994: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D9B3;
label_D996:; /* EnemyStompedPts */
    /* $D996: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD965 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D999:;
    /* $D999: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_D99C:;
    /* $D99C: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D99E:;
    /* $D99E: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_D99F:;
    /* $D99F: 20 */ maybe_trigger_vblank(6); call_by_address(0xE02F);
label_D9A2:;
    /* $D9A2: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_D9A3:;
    /* $D9A3: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_D9A5:;
    /* $D9A5: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_D9A7:;
    /* $D9A7: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_D9A9:;
    /* $D9A9: 20 */ maybe_trigger_vblank(6); call_by_address(0xC363);
label_D9AC:;
    /* $D9AC: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_D9AE:;
    /* $D9AE: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFD; FLAG_NZ(g_cpu.A);
label_D9B0:;
    /* $D9B0: 85 */ maybe_trigger_vblank(3); nes_write(0x9F, g_cpu.A);
label_D9B2:;
    /* $D9B2: 60 */ maybe_trigger_vblank(6);
    return;
label_D9B3:; /* ChkForDemoteKoopa */
    /* $D9B3: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x09; g_cpu.C=(g_cpu.A>=0x09)?1:0; FLAG_NZ(r&0xFF); }
label_D9B5:;
    /* $D9B5: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D9D4;
label_D9B7:;
    /* $D9B7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_D9B9:;
    /* $D9B9: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_D9BB:;
    /* $D9BB: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_D9BD:;
    /* $D9BD: 94 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.Y);
label_D9BF:;
    /* $D9BF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_D9C1:;
    /* $D9C1: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_D9C4:;
    /* $D9C4: 20 */ maybe_trigger_vblank(6); call_by_address(0xC363);
label_D9C7:;
    /* $D9C7: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA05);
label_D9CA:;
    /* $D9CA: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD851 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D9CD:;
    /* $D9CD: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_D9CF:;
    /* $D9CF: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); goto label_D9F1;
label_D9D2:;
    /* $D9D2: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_D9DF;
label_D9D4:; /* HandleStompedShellE */
    /* $D9D4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_D9D6:;
    /* $D9D6: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_D9D8:;
    /* $D9D8: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0484; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D9DB:;
    /* $D9DB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0484); FLAG_NZ(g_cpu.A);
label_D9DE:;
    /* $D9DE: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D9DF:;
    /* $D9DF: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0791); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D9E2:;
    /* $D9E2: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_D9E5:;
    /* $D9E5: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0791; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D9E8:;
    /* $D9E8: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x076A); FLAG_NZ(g_cpu.Y);
label_D9EB:;
    /* $D9EB: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD9D2 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D9EE:;
    /* $D9EE: 9D */ maybe_trigger_vblank(5); nes_write((0x0796 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D9F1:; /* SBnce */
    /* $D9F1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFC; FLAG_NZ(g_cpu.A);
label_D9F3:;
    /* $D9F3: 85 */ maybe_trigger_vblank(3); nes_write(0x9F, g_cpu.A);
label_D9F5:;
    /* $D9F5: 60 */ maybe_trigger_vblank(6);
    return;
}

}  // namespace

void DamageChain::injure_player() { (void)state_; damage_body(0); }
void DamageChain::force_injury()  { (void)state_; damage_body(1); }

}  // namespace smb::semcomp
