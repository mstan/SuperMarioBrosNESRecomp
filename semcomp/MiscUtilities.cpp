// semcomp/MiscUtilities.cpp — bulk-ported routines (auto-generated).
#include "semcomp/MiscUtilities.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

void MiscUtilities::inc_subtask() {
    (void)state_;
label_8745:; /* IncSubtask */
    /* $8745: EE */ maybe_trigger_vblank(6); { uint16_t a=0x073C; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8748:;
    /* $8748: 60 */ maybe_trigger_vblank(6);
    return;
}

void MiscUtilities::move_all_sprites_offscreen() {
    (void)state_;
label_8220:; /* MoveAllSpritesOffscreen */
    /* $8220: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_8222:;
    /* $8222: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x04A0); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_8225:;
    /* $8225: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_8227:; /* SprInitLoop */
    /* $8227: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_822A:;
    /* $822A: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822B:;
    /* $822B: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822C:;
    /* $822C: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822D:;
    /* $822D: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822E:;
    /* $822E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8227;
    }
label_8230:;
    /* $8230: 60 */ maybe_trigger_vblank(6);
    return;
}

void MiscUtilities::move_sprites_offscreen() {
    (void)state_;
label_8223:; /* MoveSpritesOffscreen */
    /* $8223: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x04; FLAG_NZ(g_cpu.Y);
label_8225:;
    /* $8225: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_8227:; /* SprInitLoop */
    /* $8227: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_822A:;
    /* $822A: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822B:;
    /* $822B: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822C:;
    /* $822C: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822D:;
    /* $822D: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_822E:;
    /* $822E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8227;
    }
label_8230:;
    /* $8230: 60 */ maybe_trigger_vblank(6);
    return;
}

void MiscUtilities::get_alternate_palette1() {
    (void)state_;
label_8643:; /* GetAlternatePalette1 */
    /* $8643: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0733); FLAG_NZ(g_cpu.A);
label_8646:;
    /* $8646: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_8648:;
    /* $8648: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_864F;
label_864A:;
    /* $864A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0B; FLAG_NZ(g_cpu.A);
label_864C:; /* SetVRAMAddr_B */
    /* $864C: 8D */ maybe_trigger_vblank(4); nes_write(0x0773, g_cpu.A);
label_864F:; /* NoAltPal */
    /* $864F: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8745); return;
}

void MiscUtilities::get_m_tile_attrib() {
    (void)state_;
label_DFB0:; /* GetMTileAttrib */
    /* $DFB0: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_DFB1:;
    /* $DFB1: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xC0; FLAG_NZ(g_cpu.A);
label_DFB3:;
    /* $DFB3: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DFB4:;
    /* $DFB4: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_DFB5:;
    /* $DFB5: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_DFB6:;
    /* $DFB6: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_DFB7:;
    /* $DFB7: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_DFB8:; /* ExEBG */
    /* $DFB8: 60 */ maybe_trigger_vblank(6);
    return;
}

void MiscUtilities::move_six_sprites_offscreen() {
    (void)state_;
label_E5B3:; /* MoveSixSpritesOffscreen */
    /* $E5B3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E5B5:; /* DumpSixSpr */
    /* $E5B5: 99 */ maybe_trigger_vblank(5); nes_write((0x0214 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E5B8:;
    /* $E5B8: 99 */ maybe_trigger_vblank(5); nes_write((0x0210 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E5BB:; /* DumpFourSpr */
    /* $E5BB: 99 */ maybe_trigger_vblank(5); nes_write((0x020C + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E5BE:; /* DumpThreeSpr */
    /* $E5BE: 99 */ maybe_trigger_vblank(5); nes_write((0x0208 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E5C1:; /* DumpTwoSpr */
    /* $E5C1: 99 */ maybe_trigger_vblank(5); nes_write((0x0204 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E5C4:;
    /* $E5C4: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E5C7:; /* ExitDumpSpr */
    /* $E5C7: 60 */ maybe_trigger_vblank(6);
    return;
}

void MiscUtilities::increment_column_pos() {
    (void)state_;
label_92DB:; /* IncrementColumnPos */
    /* $92DB: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0726; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_92DE:;
    /* $92DE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0726); FLAG_NZ(g_cpu.A);
label_92E1:;
    /* $92E1: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_92E3:;
    /* $92E3: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_92EB;
label_92E5:;
    /* $92E5: 8D */ maybe_trigger_vblank(4); nes_write(0x0726, g_cpu.A);
label_92E8:;
    /* $92E8: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0725; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_92EB:; /* NoColWrap */
    /* $92EB: EE */ maybe_trigger_vblank(6); { uint16_t a=0x06A0; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_92EE:;
    /* $92EE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06A0); FLAG_NZ(g_cpu.A);
label_92F1:;
    /* $92F1: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x1F; FLAG_NZ(g_cpu.A);
label_92F3:;
    /* $92F3: 8D */ maybe_trigger_vblank(4); nes_write(0x06A0, g_cpu.A);
label_92F6:;
    /* $92F6: 60 */ maybe_trigger_vblank(6);
    return;
}

void MiscUtilities::inc_area_obj_offset() {
    (void)state_;
label_9589:; /* IncAreaObjOffset */
    /* $9589: EE */ maybe_trigger_vblank(6); { uint16_t a=0x072C; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_958C:;
    /* $958C: EE */ maybe_trigger_vblank(6); { uint16_t a=0x072C; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_958F:;
    /* $958F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_9591:;
    /* $9591: 8D */ maybe_trigger_vblank(4); nes_write(0x072B, g_cpu.A);
label_9594:;
    /* $9594: 60 */ maybe_trigger_vblank(6);
    return;
}

void MiscUtilities::inc_mode_task__b() {
    (void)state_;
label_874E:; /* IncModeTask_B */
    /* $874E: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0772; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8751:;
    /* $8751: 60 */ maybe_trigger_vblank(6);
    return;
}

}  // namespace smb::semcomp
