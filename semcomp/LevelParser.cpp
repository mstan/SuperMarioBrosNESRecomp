// semcomp/LevelParser.cpp — bulk-ported routines (auto-generated).
#include "semcomp/LevelParser.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

void LevelParser::get_area_palette() {
    (void)state_;
label_85BF:; /* GetAreaPalette */
    /* $85BF: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_85C2:;
    /* $85C2: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0x85BB + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_85C5:; /* SetVRAMAddr_A */
    /* $85C5: 8E */ maybe_trigger_vblank(4); nes_write(0x0773, g_cpu.X);
label_85C8:; /* NextSubtask */
    /* $85C8: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8745); return;
}

void LevelParser::area_parser_task_control() {
    (void)state_;
label_86E6:; /* AreaParserTaskControl */
    /* $86E6: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0774; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_86E9:; /* TaskLoop */
    /* $86E9: 20 */ maybe_trigger_vblank(6); call_by_address(0x92B0);
label_86EC:;
    /* $86EC: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071F); FLAG_NZ(g_cpu.A);
label_86EF:;
    /* $86EF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_86E9;
    }
label_86F1:;
    /* $86F1: CE */ maybe_trigger_vblank(6); { uint16_t a=0x071E; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_86F4:;
    /* $86F4: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_86F9;
label_86F6:;
    /* $86F6: EE */ maybe_trigger_vblank(6); { uint16_t a=0x073C; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_86F9:; /* OutputCol */
    /* $86F9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_86FB:;
    /* $86FB: 8D */ maybe_trigger_vblank(4); nes_write(0x0773, g_cpu.A);
label_86FE:;
    /* $86FE: 60 */ maybe_trigger_vblank(6);
    return;
}

void LevelParser::render_area_graphics() {
    (void)state_;
label_88AE:; /* RenderAreaGraphics */
    /* $88AE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0726); FLAG_NZ(g_cpu.A);
label_88B1:;
    /* $88B1: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_88B3:;
    /* $88B3: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_88B5:;
    /* $88B5: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0340); FLAG_NZ(g_cpu.Y);
label_88B8:;
    /* $88B8: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_88BA:;
    /* $88BA: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0721); FLAG_NZ(g_cpu.A);
label_88BD:;
    /* $88BD: 99 */ maybe_trigger_vblank(5); nes_write((0x0342 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_88C0:;
    /* $88C0: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0720); FLAG_NZ(g_cpu.A);
label_88C3:;
    /* $88C3: 99 */ maybe_trigger_vblank(5); nes_write((0x0341 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_88C6:;
    /* $88C6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9A; FLAG_NZ(g_cpu.A);
label_88C8:;
    /* $88C8: 99 */ maybe_trigger_vblank(5); nes_write((0x0343 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_88CB:;
    /* $88CB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_88CD:;
    /* $88CD: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_88CF:;
    /* $88CF: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_88D0:; /* DrawMTLoop */
    /* $88D0: 86 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.X);
label_88D2:;
    /* $88D2: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x06A1 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_88D5:;
    /* $88D5: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xC0; FLAG_NZ(g_cpu.A);
label_88D7:;
    /* $88D7: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_88D9:;
    /* $88D9: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_88DA:;
    /* $88DA: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_88DB:;
    /* $88DB: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_88DC:;
    /* $88DC: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_88DD:;
    /* $88DD: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x8B08 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_88E0:;
    /* $88E0: 85 */ maybe_trigger_vblank(3); nes_write(0x06, g_cpu.A);
label_88E2:;
    /* $88E2: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x8B0C + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_88E5:;
    /* $88E5: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_88E7:;
    /* $88E7: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x06A1 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_88EA:;
    /* $88EA: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_88EB:;
    /* $88EB: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_88EC:;
    /* $88EC: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_88EE:;
    /* $88EE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071F); FLAG_NZ(g_cpu.A);
label_88F1:;
    /* $88F1: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_88F3:;
    /* $88F3: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x01; FLAG_NZ(g_cpu.A);
label_88F5:;
    /* $88F5: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_88F6:;
    /* $88F6: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x02); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_88F8:;
    /* $88F8: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_88F9:;
    /* $88F9: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x00); FLAG_NZ(g_cpu.X);
label_88FB:;
    /* $88FB: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0x06) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_88FD:;
    /* $88FD: 9D */ maybe_trigger_vblank(5); nes_write((0x0344 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8900:;
    /* $8900: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8901:;
    /* $8901: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0x06) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8903:;
    /* $8903: 9D */ maybe_trigger_vblank(5); nes_write((0x0345 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8906:;
    /* $8906: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x04); FLAG_NZ(g_cpu.Y);
label_8908:;
    /* $8908: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x05); FLAG_NZ(g_cpu.A);
label_890A:;
    /* $890A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_891A;
label_890C:;
    /* $890C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_890E:;
    /* $890E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_890F:;
    /* $890F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_892A;
label_8911:;
    /* $8911: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x03; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8913:;
    /* $8913: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x03; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8915:;
    /* $8915: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x03; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8917:;
    /* $8917: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8930); return;
label_891A:; /* RightCheck */
    /* $891A: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_891C:;
    /* $891C: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_891D:;
    /* $891D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_892E;
label_891F:;
    /* $891F: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x03; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_8921:;
    /* $8921: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x03; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_8923:;
    /* $8923: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x03; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_8925:;
    /* $8925: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x03; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_8927:;
    /* $8927: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8930); return;
label_892A:; /* LLeft */
    /* $892A: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x03; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_892C:;
    /* $892C: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x03; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_892E:; /* NextMTRow */
    /* $892E: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8930:; /* SetAttrib */
    /* $8930: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03F9 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8933:;
    /* $8933: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x03); FLAG_NZ(g_cpu.A);
label_8935:;
    /* $8935: 99 */ maybe_trigger_vblank(5); nes_write((0x03F9 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8938:;
    /* $8938: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_893A:;
    /* $893A: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_893C:;
    /* $893C: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x01); FLAG_NZ(g_cpu.X);
label_893E:;
    /* $893E: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_893F:;
    /* $893F: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x0D; g_cpu.C=(g_cpu.X>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_8941:;
    /* $8941: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_88D0;
    }
label_8943:;
    /* $8943: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x00); FLAG_NZ(g_cpu.Y);
label_8945:;
    /* $8945: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8946:;
    /* $8946: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8947:;
    /* $8947: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8948:;
    /* $8948: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_894A:;
    /* $894A: 99 */ maybe_trigger_vblank(5); nes_write((0x0341 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_894D:;
    /* $894D: 8C */ maybe_trigger_vblank(4); nes_write(0x0340, g_cpu.Y);
label_8950:;
    /* $8950: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0721; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8953:;
    /* $8953: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0721); FLAG_NZ(g_cpu.A);
label_8956:;
    /* $8956: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x1F; FLAG_NZ(g_cpu.A);
label_8958:;
    /* $8958: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_8967;
label_895A:;
    /* $895A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_895C:;
    /* $895C: 8D */ maybe_trigger_vblank(4); nes_write(0x0721, g_cpu.A);
label_895F:;
    /* $895F: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0720); FLAG_NZ(g_cpu.A);
label_8962:;
    /* $8962: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x04; FLAG_NZ(g_cpu.A);
label_8964:;
    /* $8964: 8D */ maybe_trigger_vblank(4); nes_write(0x0720, g_cpu.A);
label_8967:; /* ExitDrawM */
    /* $8967: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x89BD); return;
}

void LevelParser::initialize_area() {
    (void)state_;
label_8FE4:; /* InitializeArea */
    /* $8FE4: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x4B; FLAG_NZ(g_cpu.Y);
label_8FE6:;
    /* $8FE6: 20 */ maybe_trigger_vblank(6); call_by_address(0x90CC);
label_8FE9:;
    /* $8FE9: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x21; FLAG_NZ(g_cpu.X);
label_8FEB:;
    /* $8FEB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8FED:; /* ClrTimersLoop */
    /* $8FED: 9D */ maybe_trigger_vblank(5); nes_write((0x0780 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8FF0:;
    /* $8FF0: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_8FF1:;
    /* $8FF1: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8FED;
    }
label_8FF3:;
    /* $8FF3: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x075B); FLAG_NZ(g_cpu.A);
label_8FF6:;
    /* $8FF6: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0752); FLAG_NZ(g_cpu.Y);
label_8FF9:;
    /* $8FF9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_8FFE;
label_8FFB:;
    /* $8FFB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0751); FLAG_NZ(g_cpu.A);
label_8FFE:; /* StartPage */
    /* $8FFE: 8D */ maybe_trigger_vblank(4); nes_write(0x071A, g_cpu.A);
label_9001:;
    /* $9001: 8D */ maybe_trigger_vblank(4); nes_write(0x0725, g_cpu.A);
label_9004:;
    /* $9004: 8D */ maybe_trigger_vblank(4); nes_write(0x0728, g_cpu.A);
label_9007:;
    /* $9007: 20 */ maybe_trigger_vblank(6); call_by_address(0xB038);
label_900A:;
    /* $900A: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x20; FLAG_NZ(g_cpu.Y);
label_900C:;
    /* $900C: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_900E:;
    /* $900E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9012;
label_9010:;
    /* $9010: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x24; FLAG_NZ(g_cpu.Y);
label_9012:; /* SetInitNTHigh */
    /* $9012: 8C */ maybe_trigger_vblank(4); nes_write(0x0720, g_cpu.Y);
label_9015:;
    /* $9015: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x80; FLAG_NZ(g_cpu.Y);
label_9017:;
    /* $9017: 8C */ maybe_trigger_vblank(4); nes_write(0x0721, g_cpu.Y);
label_901A:;
    /* $901A: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_901B:;
    /* $901B: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_901C:;
    /* $901C: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_901D:;
    /* $901D: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_901E:;
    /* $901E: 8D */ maybe_trigger_vblank(4); nes_write(0x06A0, g_cpu.A);
label_9021:;
    /* $9021: CE */ maybe_trigger_vblank(6); { uint16_t a=0x0730; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_9024:;
    /* $9024: CE */ maybe_trigger_vblank(6); { uint16_t a=0x0731; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_9027:;
    /* $9027: CE */ maybe_trigger_vblank(6); { uint16_t a=0x0732; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_902A:;
    /* $902A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0B; FLAG_NZ(g_cpu.A);
label_902C:;
    /* $902C: 8D */ maybe_trigger_vblank(4); nes_write(0x071E, g_cpu.A);
label_902F:;
    /* $902F: 20 */ maybe_trigger_vblank(6); call_by_address(0x9C22);
label_9032:;
    /* $9032: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x076A); FLAG_NZ(g_cpu.A);
label_9035:;
    /* $9035: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_9047;
label_9037:;
    /* $9037: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_903A:;
    /* $903A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_903C:;
    /* $903C: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_904A;
label_903E:;
    /* $903E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_9047;
label_9040:;
    /* $9040: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x075C); FLAG_NZ(g_cpu.A);
label_9043:;
    /* $9043: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_9045:;
    /* $9045: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_904A;
label_9047:; /* SetSecHard */
    /* $9047: EE */ maybe_trigger_vblank(6); { uint16_t a=0x06CC; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_904A:; /* CheckHalfway */
    /* $904A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x075B); FLAG_NZ(g_cpu.A);
label_904D:;
    /* $904D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9054;
label_904F:;
    /* $904F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_9051:;
    /* $9051: 8D */ maybe_trigger_vblank(4); nes_write(0x0710, g_cpu.A);
label_9054:; /* DoneInitArea */
    /* $9054: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_9056:;
    /* $9056: 85 */ maybe_trigger_vblank(3); nes_write(0xFB, g_cpu.A);
label_9058:;
    /* $9058: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_905A:;
    /* $905A: 8D */ maybe_trigger_vblank(4); nes_write(0x0774, g_cpu.A);
label_905D:;
    /* $905D: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0772; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_9060:;
    /* $9060: 60 */ maybe_trigger_vblank(6);
    return;
}

void LevelParser::area_parser_task_handler() {
    (void)state_;
label_92B0:; /* AreaParserTaskHandler */
    /* $92B0: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x071F); FLAG_NZ(g_cpu.Y);
label_92B3:;
    /* $92B3: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_92BA;
label_92B5:;
    /* $92B5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x08; FLAG_NZ(g_cpu.Y);
label_92B7:;
    /* $92B7: 8C */ maybe_trigger_vblank(4); nes_write(0x071F, g_cpu.Y);
label_92BA:; /* DoAPTasks */
    /* $92BA: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_92BB:;
    /* $92BB: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_92BC:;
    /* $92BC: 20 */ maybe_trigger_vblank(6); call_by_address(0x92C8);
label_92BF:;
    /* $92BF: CE */ maybe_trigger_vblank(6); { uint16_t a=0x071F; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_92C2:;
    /* $92C2: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_92C7;
label_92C4:;
    /* $92C4: 20 */ maybe_trigger_vblank(6); call_by_address(0x896A);
label_92C7:; /* SkipATRender */
    /* $92C7: 60 */ maybe_trigger_vblank(6);
    return;
}

void LevelParser::area_parser_tasks() {
    (void)state_;
label_92C8:; /* AreaParserTasks */
    /* $92C8: 20 */ maybe_trigger_vblank(6); /* inline_dispatch $8E04: 8 entries (bank=0) */
switch(g_cpu.A) {
  case 0: call_by_address(0x92DB); return;
  case 1: call_by_address(0x88AE); return;
  case 2: call_by_address(0x88AE); return;
  case 3: call_by_address(0x93FC); return;
  case 4: call_by_address(0x92DB); return;
  case 5: call_by_address(0x88AE); return;
  case 6: call_by_address(0x88AE); return;
  case 7: call_by_address(0x93FC); return;
  default: nes_log_inline_miss(0x92C8, g_cpu.A); return;
}
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

void LevelParser::get_area_object_i_d() {
    (void)state_;
label_9B36:; /* GetAreaObjectID */
    /* $9B36: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_9B38:;
    /* $9B38: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_9B39:;
    /* $9B39: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9B3B:;
    /* $9B3B: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9B3C:; /* ExitDecBlock */
    /* $9B3C: 60 */ maybe_trigger_vblank(6);
    return;
}

void LevelParser::get_area_obj_x_position() {
    (void)state_;
label_9BCB:; /* GetAreaObjXPosition */
    /* $9BCB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0726); FLAG_NZ(g_cpu.A);
label_9BCE:;
    /* $9BCE: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BCF:;
    /* $9BCF: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BD0:;
    /* $9BD0: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BD1:;
    /* $9BD1: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BD2:;
    /* $9BD2: 60 */ maybe_trigger_vblank(6);
    return;
}

void LevelParser::get_area_obj_y_position() {
    (void)state_;
label_9BD3:; /* GetAreaObjYPosition */
    /* $9BD3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x07); FLAG_NZ(g_cpu.A);
label_9BD5:;
    /* $9BD5: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BD6:;
    /* $9BD6: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BD7:;
    /* $9BD7: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BD8:;
    /* $9BD8: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9BD9:;
    /* $9BD9: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_9BDA:;
    /* $9BDA: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x20 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x20); g_cpu.A=r&0xFF; }
label_9BDC:;
    /* $9BDC: 60 */ maybe_trigger_vblank(6);
    return;
}

void LevelParser::load_area_pointer() {
    (void)state_;
label_9C03:; /* LoadAreaPointer */
    /* $9C03: 20 */ maybe_trigger_vblank(6); call_by_address(0x9C13);
label_9C06:;
    /* $9C06: 8D */ maybe_trigger_vblank(4); nes_write(0x0750, g_cpu.A);
label_9C09:; /* GetAreaType */
    /* $9C09: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x60; FLAG_NZ(g_cpu.A);
label_9C0B:;
    /* $9C0B: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9C0C:;
    /* $9C0C: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_9C0D:;
    /* $9C0D: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_9C0E:;
    /* $9C0E: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_9C0F:;
    /* $9C0F: 8D */ maybe_trigger_vblank(4); nes_write(0x074E, g_cpu.A);
label_9C12:;
    /* $9C12: 60 */ maybe_trigger_vblank(6);
    return;
}

void LevelParser::get_area_type() {
    (void)state_;
label_9C09:; /* GetAreaType */
    /* $9C09: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x60; FLAG_NZ(g_cpu.A);
label_9C0B:;
    /* $9C0B: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9C0C:;
    /* $9C0C: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_9C0D:;
    /* $9C0D: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_9C0E:;
    /* $9C0E: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_9C0F:;
    /* $9C0F: 8D */ maybe_trigger_vblank(4); nes_write(0x074E, g_cpu.A);
label_9C12:;
    /* $9C12: 60 */ maybe_trigger_vblank(6);
    return;
}

void LevelParser::get_area_data_addrs() {
    (void)state_;
label_9C22:; /* GetAreaDataAddrs */
    /* $9C22: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0750); FLAG_NZ(g_cpu.A);
label_9C25:;
    /* $9C25: 20 */ maybe_trigger_vblank(6); call_by_address(0x9C09);
label_9C28:;
    /* $9C28: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9C29:;
    /* $9C29: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0750); FLAG_NZ(g_cpu.A);
label_9C2C:;
    /* $9C2C: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x1F; FLAG_NZ(g_cpu.A);
label_9C2E:;
    /* $9C2E: 8D */ maybe_trigger_vblank(4); nes_write(0x074F, g_cpu.A);
label_9C31:;
    /* $9C31: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x9CE0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9C34:;
    /* $9C34: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_9C35:;
    /* $9C35: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x074F); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9C38:;
    /* $9C38: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9C39:;
    /* $9C39: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x9CE4 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9C3C:;
    /* $9C3C: 85 */ maybe_trigger_vblank(3); nes_write(0xE9, g_cpu.A);
label_9C3E:;
    /* $9C3E: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x9D06 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9C41:;
    /* $9C41: 85 */ maybe_trigger_vblank(3); nes_write(0xEA, g_cpu.A);
label_9C43:;
    /* $9C43: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_9C46:;
    /* $9C46: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x9D28 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9C49:;
    /* $9C49: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_9C4A:;
    /* $9C4A: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x074F); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9C4D:;
    /* $9C4D: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9C4E:;
    /* $9C4E: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x9D2C + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9C51:;
    /* $9C51: 85 */ maybe_trigger_vblank(3); nes_write(0xE7, g_cpu.A);
label_9C53:;
    /* $9C53: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x9D4E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9C56:;
    /* $9C56: 85 */ maybe_trigger_vblank(3); nes_write(0xE8, g_cpu.A);
label_9C58:;
    /* $9C58: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_9C5A:;
    /* $9C5A: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9C5C:;
    /* $9C5C: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9C5D:;
    /* $9C5D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_9C5F:;
    /* $9C5F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_9C61:;
    /* $9C61: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_9C68;
label_9C63:;
    /* $9C63: 8D */ maybe_trigger_vblank(4); nes_write(0x0744, g_cpu.A);
label_9C66:;
    /* $9C66: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_9C68:; /* StoreFore */
    /* $9C68: 8D */ maybe_trigger_vblank(4); nes_write(0x0741, g_cpu.A);
label_9C6B:;
    /* $9C6B: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9C6C:;
    /* $9C6C: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9C6D:;
    /* $9C6D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x38; FLAG_NZ(g_cpu.A);
label_9C6F:;
    /* $9C6F: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9C70:;
    /* $9C70: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9C71:;
    /* $9C71: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9C72:;
    /* $9C72: 8D */ maybe_trigger_vblank(4); nes_write(0x0710, g_cpu.A);
label_9C75:;
    /* $9C75: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9C76:;
    /* $9C76: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xC0; FLAG_NZ(g_cpu.A);
label_9C78:;
    /* $9C78: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_9C79:;
    /* $9C79: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_9C7A:;
    /* $9C7A: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_9C7B:;
    /* $9C7B: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_9C7C:;
    /* $9C7C: 8D */ maybe_trigger_vblank(4); nes_write(0x0715, g_cpu.A);
label_9C7F:;
    /* $9C7F: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9C80:;
    /* $9C80: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9C82:;
    /* $9C82: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9C83:;
    /* $9C83: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_9C85:;
    /* $9C85: 8D */ maybe_trigger_vblank(4); nes_write(0x0727, g_cpu.A);
label_9C88:;
    /* $9C88: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9C89:;
    /* $9C89: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9C8A:;
    /* $9C8A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x30; FLAG_NZ(g_cpu.A);
label_9C8C:;
    /* $9C8C: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9C8D:;
    /* $9C8D: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9C8E:;
    /* $9C8E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9C8F:;
    /* $9C8F: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9C90:;
    /* $9C90: 8D */ maybe_trigger_vblank(4); nes_write(0x0742, g_cpu.A);
label_9C93:;
    /* $9C93: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9C94:;
    /* $9C94: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xC0; FLAG_NZ(g_cpu.A);
label_9C96:;
    /* $9C96: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_9C97:;
    /* $9C97: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_9C98:;
    /* $9C98: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_9C99:;
    /* $9C99: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_9C9A:;
    /* $9C9A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_9C9C:;
    /* $9C9C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_9CA3;
label_9C9E:;
    /* $9C9E: 8D */ maybe_trigger_vblank(4); nes_write(0x0743, g_cpu.A);
label_9CA1:;
    /* $9CA1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_9CA3:; /* StoreStyle */
    /* $9CA3: 8D */ maybe_trigger_vblank(4); nes_write(0x0733, g_cpu.A);
label_9CA6:;
    /* $9CA6: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xE7); FLAG_NZ(g_cpu.A);
label_9CA8:;
    /* $9CA8: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_9CA9:;
    /* $9CA9: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x02 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x02); g_cpu.A=r&0xFF; }
label_9CAB:;
    /* $9CAB: 85 */ maybe_trigger_vblank(3); nes_write(0xE7, g_cpu.A);
label_9CAD:;
    /* $9CAD: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xE8); FLAG_NZ(g_cpu.A);
label_9CAF:;
    /* $9CAF: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_9CB1:;
    /* $9CB1: 85 */ maybe_trigger_vblank(3); nes_write(0xE8, g_cpu.A);
label_9CB3:;
    /* $9CB3: 60 */ maybe_trigger_vblank(6);
    return;
}

}  // namespace smb::semcomp
