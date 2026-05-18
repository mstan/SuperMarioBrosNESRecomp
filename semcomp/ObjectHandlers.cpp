// semcomp/ObjectHandlers.cpp — Phase 18 verbatim ports.
#include "semcomp/ObjectHandlers.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

void ObjectHandlers::powerup_obj_handler() {
    (void)state_;
label_BC85:; /* PowerUpObjHandler */
    /* $BC85: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x05; FLAG_NZ(g_cpu.X);
label_BC87:;
    /* $BC87: 86 */ maybe_trigger_vblank(3); nes_write(0x08, g_cpu.X);
label_BC89:;
    /* $BC89: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x23); FLAG_NZ(g_cpu.A);
label_BC8B:;
    /* $BC8B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_BCEA;
label_BC8D:;
    /* $BC8D: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_BC8E:;
    /* $BC8E: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_BCB3;
label_BC90:;
    /* $BC90: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_BC93:;
    /* $BC93: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_BCD8;
label_BC95:;
    /* $BC95: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x39); FLAG_NZ(g_cpu.A);
label_BC97:;
    /* $BC97: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_BCAA;
label_BC99:;
    /* $BC99: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_BC9B:;
    /* $BC9B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_BCAA;
label_BC9D:;
    /* $BC9D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_BC9F:;
    /* $BC9F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_BCD8;
label_BCA1:;
    /* $BCA1: 20 */ maybe_trigger_vblank(6); call_by_address(0xCAF9);
label_BCA4:;
    /* $BCA4: 20 */ maybe_trigger_vblank(6); call_by_address(0xE163);
label_BCA7:;
    /* $BCA7: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBCD8); return;
label_BCAA:; /* ShroomM */
    /* $BCAA: 20 */ maybe_trigger_vblank(6); call_by_address(0xCA77);
label_BCAD:;
    /* $BCAD: 20 */ maybe_trigger_vblank(6); call_by_address(0xDFC1);
label_BCB0:;
    /* $BCB0: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBCD8); return;
label_BCB3:; /* GrowThePowerUp */
    /* $BCB3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_BCB5:;
    /* $BCB5: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_BCB7:;
    /* $BCB7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_BCD2;
label_BCB9:;
    /* $BCB9: C6 */ maybe_trigger_vblank(5); { uint16_t a=0xD4; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BCBB:;
    /* $BCBB: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x23); FLAG_NZ(g_cpu.A);
label_BCBD:;
    /* $BCBD: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x23; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BCBF:;
    /* $BCBF: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_BCC1:;
    /* $BCC1: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_BCD2;
label_BCC3:;
    /* $BCC3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_BCC5:;
    /* $BCC5: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_BCC7:;
    /* $BCC7: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_BCC9:;
    /* $BCC9: 85 */ maybe_trigger_vblank(3); nes_write(0x23, g_cpu.A);
label_BCCB:;
    /* $BCCB: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_BCCC:;
    /* $BCCC: 8D */ maybe_trigger_vblank(4); nes_write(0x03CA, g_cpu.A);
label_BCCF:;
    /* $BCCF: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BCD0:;
    /* $BCD0: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_BCD2:; /* ChkPUSte */
    /* $BCD2: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x23); FLAG_NZ(g_cpu.A);
label_BCD4:;
    /* $BCD4: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_BCD6:;
    /* $BCD6: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_BCEA;
label_BCD8:; /* RunPUSubs */
    /* $BCD8: 20 */ maybe_trigger_vblank(6); call_by_address(0xF152);
label_BCDB:;
    /* $BCDB: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1AF);
label_BCDE:;
    /* $BCDE: 20 */ maybe_trigger_vblank(6); call_by_address(0xE243);
label_BCE1:;
    /* $BCE1: 20 */ maybe_trigger_vblank(6); call_by_address(0xE6D2);
label_BCE4:;
    /* $BCE4: 20 */ maybe_trigger_vblank(6); call_by_address(0xD853);
label_BCE7:;
    /* $BCE7: 20 */ maybe_trigger_vblank(6); call_by_address(0xD67A);
label_BCEA:; /* ExitPUp */
    /* $BCEA: 60 */ maybe_trigger_vblank(6);
}

void ObjectHandlers::fireball_obj_core() {
    (void)state_;
label_B689:; /* FireballObjCore */
    /* $B689: 86 */ maybe_trigger_vblank(3); nes_write(0x08, g_cpu.X);
label_B68B:;
    /* $B68B: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x24 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_B68D:;
    /* $B68D: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_B68E:;
    /* $B68E: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B6F3;
label_B690:;
    /* $B690: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x24 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_B692:;
    /* $B692: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B6F2;
label_B694:;
    /* $B694: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_B695:;
    /* $B695: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B6BE;
label_B697:;
    /* $B697: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x86); FLAG_NZ(g_cpu.A);
label_B699:;
    /* $B699: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_B69B:;
    /* $B69B: 95 */ maybe_trigger_vblank(4); nes_write((0x8D + g_cpu.X) & 0xFF, g_cpu.A);
label_B69D:;
    /* $B69D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x6D); FLAG_NZ(g_cpu.A);
label_B69F:;
    /* $B69F: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_B6A1:;
    /* $B6A1: 95 */ maybe_trigger_vblank(4); nes_write((0x74 + g_cpu.X) & 0xFF, g_cpu.A);
label_B6A3:;
    /* $B6A3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_B6A5:;
    /* $B6A5: 95 */ maybe_trigger_vblank(4); nes_write((0xD5 + g_cpu.X) & 0xFF, g_cpu.A);
label_B6A7:;
    /* $B6A7: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_B6A9:;
    /* $B6A9: 95 */ maybe_trigger_vblank(4); nes_write((0xBC + g_cpu.X) & 0xFF, g_cpu.A);
label_B6AB:;
    /* $B6AB: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x33); FLAG_NZ(g_cpu.Y);
label_B6AD:;
    /* $B6AD: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_B6AE:;
    /* $B6AE: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xB687 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B6B1:;
    /* $B6B1: 95 */ maybe_trigger_vblank(4); nes_write((0x5E + g_cpu.X) & 0xFF, g_cpu.A);
label_B6B3:;
    /* $B6B3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_B6B5:;
    /* $B6B5: 95 */ maybe_trigger_vblank(4); nes_write((0xA6 + g_cpu.X) & 0xFF, g_cpu.A);
label_B6B7:;
    /* $B6B7: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x07; FLAG_NZ(g_cpu.A);
label_B6B9:;
    /* $B6B9: 9D */ maybe_trigger_vblank(5); nes_write((0x04A0 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_B6BC:;
    /* $B6BC: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0x24 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B6BE:; /* RunFB */
    /* $B6BE: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_B6BF:;
    /* $B6BF: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B6C0:;
    /* $B6C0: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x07 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x07); g_cpu.A=r&0xFF; }
label_B6C2:;
    /* $B6C2: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_B6C3:;
    /* $B6C3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x50; FLAG_NZ(g_cpu.A);
label_B6C5:;
    /* $B6C5: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_B6C7:;
    /* $B6C7: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_B6C9:;
    /* $B6C9: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_B6CB:;
    /* $B6CB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B6CD:;
    /* $B6CD: 20 */ maybe_trigger_vblank(6); call_by_address(0xBFD7);
label_B6D0:;
    /* $B6D0: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF0F);
label_B6D3:;
    /* $B6D3: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_B6D5:;
    /* $B6D5: 20 */ maybe_trigger_vblank(6); call_by_address(0xF13B);
label_B6D8:;
    /* $B6D8: 20 */ maybe_trigger_vblank(6); call_by_address(0xF187);
label_B6DB:;
    /* $B6DB: 20 */ maybe_trigger_vblank(6); call_by_address(0xE22D);
label_B6DE:;
    /* $B6DE: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1C8);
label_B6E1:;
    /* $B6E1: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D2); FLAG_NZ(g_cpu.A);
label_B6E4:;
    /* $B6E4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xCC; FLAG_NZ(g_cpu.A);
label_B6E6:;
    /* $B6E6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B6EE;
label_B6E8:;
    /* $B6E8: 20 */ maybe_trigger_vblank(6); call_by_address(0xD6D9);
label_B6EB:;
    /* $B6EB: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xECDE); return;
label_B6EE:; /* EraseFB */
    /* $B6EE: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B6F0:;
    /* $B6F0: 95 */ maybe_trigger_vblank(4); nes_write((0x24 + g_cpu.X) & 0xFF, g_cpu.A);
label_B6F2:; /* NoFBall */
    /* $B6F2: 60 */ maybe_trigger_vblank(6);
    return;
label_B6F3:; /* FireballExplosion */
    /* $B6F3: 20 */ maybe_trigger_vblank(6); call_by_address(0xF13B);
label_B6F6:;
    /* $B6F6: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xED09); return;
}

void ObjectHandlers::coin_block() {
    (void)state_;
label_BB38:; /* CoinBlock */
    /* $BB38: 20 */ maybe_trigger_vblank(6); call_by_address(0xBB84);
label_BB3B:;
    /* $BB3B: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x76 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_BB3D:;
    /* $BB3D: 99 */ maybe_trigger_vblank(5); nes_write((0x007A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_BB40:;
    /* $BB40: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x8F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_BB42:;
    /* $BB42: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x05; FLAG_NZ(g_cpu.A);
label_BB44:;
    /* $BB44: 99 */ maybe_trigger_vblank(5); nes_write((0x0093 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_BB47:;
    /* $BB47: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD7 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_BB49:;
    /* $BB49: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x10; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_BB4B:;
    /* $BB4B: 99 */ maybe_trigger_vblank(5); nes_write((0x00DB + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_BB4E:;
    /* $BB4E: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBB6C); return;
}

}  // namespace smb::semcomp
