// semcomp/BgRenderer.cpp — bulk-ported routines (auto-generated).
#include "semcomp/BgRenderer.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

void BgRenderer::set_v_r_a_m_addr__a() {
    (void)state_;
label_85C5:; /* SetVRAMAddr_A */
    /* $85C5: 8E */ maybe_trigger_vblank(4); nes_write(0x0773, g_cpu.X);
label_85C8:; /* NextSubtask */
    /* $85C8: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8745); return;
}

void BgRenderer::set_v_r_a_m_offset() {
    (void)state_;
label_863F:; /* SetVRAMOffset */
    /* $863F: 8D */ maybe_trigger_vblank(4); nes_write(0x0300, g_cpu.A);
label_8642:;
    /* $8642: 60 */ maybe_trigger_vblank(6);
    return;
}

void BgRenderer::set_v_r_a_m_addr__b() {
    (void)state_;
label_864C:; /* SetVRAMAddr_B */
    /* $864C: 8D */ maybe_trigger_vblank(4); nes_write(0x0773, g_cpu.A);
label_864F:; /* NoAltPal */
    /* $864F: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8745); return;
}

void BgRenderer::write_top_status_line() {
    (void)state_;
label_8652:; /* WriteTopStatusLine */
    /* $8652: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8654:;
    /* $8654: 20 */ maybe_trigger_vblank(6); call_by_address(0x8808);
label_8657:;
    /* $8657: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8745); return;
}

void BgRenderer::write_bottom_status_line() {
    (void)state_;
label_865A:; /* WriteBottomStatusLine */
    /* $865A: 20 */ maybe_trigger_vblank(6); call_by_address(0xBC30);
label_865D:;
    /* $865D: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x0300); FLAG_NZ(g_cpu.X);
label_8660:;
    /* $8660: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_8662:;
    /* $8662: 9D */ maybe_trigger_vblank(5); nes_write((0x0301 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8665:;
    /* $8665: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x73; FLAG_NZ(g_cpu.A);
label_8667:;
    /* $8667: 9D */ maybe_trigger_vblank(5); nes_write((0x0302 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_866A:;
    /* $866A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_866C:;
    /* $866C: 9D */ maybe_trigger_vblank(5); nes_write((0x0303 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_866F:;
    /* $866F: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x075F); FLAG_NZ(g_cpu.Y);
label_8672:;
    /* $8672: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8673:;
    /* $8673: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_8674:;
    /* $8674: 9D */ maybe_trigger_vblank(5); nes_write((0x0304 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8677:;
    /* $8677: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_8679:;
    /* $8679: 9D */ maybe_trigger_vblank(5); nes_write((0x0305 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_867C:;
    /* $867C: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x075C); FLAG_NZ(g_cpu.Y);
label_867F:;
    /* $867F: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8680:;
    /* $8680: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_8681:;
    /* $8681: 9D */ maybe_trigger_vblank(5); nes_write((0x0306 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8684:;
    /* $8684: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8686:;
    /* $8686: 9D */ maybe_trigger_vblank(5); nes_write((0x0307 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8689:;
    /* $8689: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_868A:;
    /* $868A: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_868B:;
    /* $868B: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x06 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x06); g_cpu.A=r&0xFF; }
label_868D:;
    /* $868D: 8D */ maybe_trigger_vblank(4); nes_write(0x0300, g_cpu.A);
label_8690:;
    /* $8690: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8745); return;
}

void BgRenderer::write_top_score() {
    (void)state_;
label_8749:; /* WriteTopScore */
    /* $8749: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFA; FLAG_NZ(g_cpu.A);
label_874B:;
    /* $874B: 20 */ maybe_trigger_vblank(6); call_by_address(0xBC36);
label_874E:; /* IncModeTask_B */
    /* $874E: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0772; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8751:;
    /* $8751: 60 */ maybe_trigger_vblank(6);
    return;
}

void BgRenderer::set_v_r_a_m_ctrl() {
    (void)state_;
label_89BD:; /* SetVRAMCtrl */
    /* $89BD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_89BF:;
    /* $89BF: 8D */ maybe_trigger_vblank(4); nes_write(0x0773, g_cpu.A);
label_89C2:;
    /* $89C2: 60 */ maybe_trigger_vblank(6);
    return;
}

void BgRenderer::write_n_t_addr() {
    (void)state_;
label_8E2D:; /* WriteNTAddr */
    /* $8E2D: 8D */ maybe_trigger_vblank(4); nes_write(0x2006, g_cpu.A);
label_8E30:;
    /* $8E30: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8E32:;
    /* $8E32: 8D */ maybe_trigger_vblank(4); nes_write(0x2006, g_cpu.A);
label_8E35:;
    /* $8E35: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x04; FLAG_NZ(g_cpu.X);
label_8E37:;
    /* $8E37: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xC0; FLAG_NZ(g_cpu.Y);
label_8E39:;
    /* $8E39: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x24; FLAG_NZ(g_cpu.A);
label_8E3B:; /* InitNTLoop */
    /* $8E3B: 8D */ maybe_trigger_vblank(4); nes_write(0x2007, g_cpu.A);
label_8E3E:;
    /* $8E3E: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8E3F:;
    /* $8E3F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8E3B;
    }
label_8E41:;
    /* $8E41: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_8E42:;
    /* $8E42: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8E3B;
    }
label_8E44:;
    /* $8E44: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x40; FLAG_NZ(g_cpu.Y);
label_8E46:;
    /* $8E46: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_8E47:;
    /* $8E47: 8D */ maybe_trigger_vblank(4); nes_write(0x0300, g_cpu.A);
label_8E4A:;
    /* $8E4A: 8D */ maybe_trigger_vblank(4); nes_write(0x0301, g_cpu.A);
label_8E4D:; /* InitATLoop */
    /* $8E4D: 8D */ maybe_trigger_vblank(4); nes_write(0x2007, g_cpu.A);
label_8E50:;
    /* $8E50: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8E51:;
    /* $8E51: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8E4D;
    }
label_8E53:;
    /* $8E53: 8D */ maybe_trigger_vblank(4); nes_write(0x073F, g_cpu.A);
label_8E56:;
    /* $8E56: 8D */ maybe_trigger_vblank(4); nes_write(0x0740, g_cpu.A);
label_8E59:;
    /* $8E59: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8EE6); return;
}

void BgRenderer::write_buffer_to_screen() {
    (void)state_;
label_8E92:; /* WriteBufferToScreen */
    /* $8E92: 8D */ maybe_trigger_vblank(4); nes_write(0x2006, g_cpu.A);
label_8E95:;
    /* $8E95: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8E96:;
    /* $8E96: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0x00) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8E98:;
    /* $8E98: 8D */ maybe_trigger_vblank(4); nes_write(0x2006, g_cpu.A);
label_8E9B:;
    /* $8E9B: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8E9C:;
    /* $8E9C: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0x00) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8E9E:;
    /* $8E9E: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8E9F:;
    /* $8E9F: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_8EA0:;
    /* $8EA0: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0778); FLAG_NZ(g_cpu.A);
label_8EA3:;
    /* $8EA3: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x04; FLAG_NZ(g_cpu.A);
label_8EA5:;
    /* $8EA5: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_8EA9;
label_8EA7:;
    /* $8EA7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xFB; FLAG_NZ(g_cpu.A);
label_8EA9:; /* SetupWrites */
    /* $8EA9: 20 */ maybe_trigger_vblank(6); call_by_address(0x8EED);
label_8EAC:;
    /* $8EAC: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_8EAD:;
    /* $8EAD: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8EAE:;
    /* $8EAE: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_8EB3;
label_8EB0:;
    /* $8EB0: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x02; FLAG_NZ(g_cpu.A);
label_8EB2:;
    /* $8EB2: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8EB3:; /* GetLength */
    /* $8EB3: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_8EB4:;
    /* $8EB4: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_8EB5:;
    /* $8EB5: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_8EB6:; /* OutputToVRAM */
    /* $8EB6: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_8EB9;
label_8EB8:;
    /* $8EB8: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8EB9:; /* RepeatByte */
    /* $8EB9: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0x00) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8EBB:;
    /* $8EBB: 8D */ maybe_trigger_vblank(4); nes_write(0x2007, g_cpu.A);
label_8EBE:;
    /* $8EBE: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_8EBF:;
    /* $8EBF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8EB6;
    }
label_8EC1:;
    /* $8EC1: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_8EC2:;
    /* $8EC2: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_8EC3:;
    /* $8EC3: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8EC5:;
    /* $8EC5: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_8EC7:;
    /* $8EC7: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8EC9:;
    /* $8EC9: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x01); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8ECB:;
    /* $8ECB: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_8ECD:;
    /* $8ECD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x3F; FLAG_NZ(g_cpu.A);
label_8ECF:;
    /* $8ECF: 8D */ maybe_trigger_vblank(4); nes_write(0x2006, g_cpu.A);
label_8ED2:;
    /* $8ED2: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8ED4:;
    /* $8ED4: 8D */ maybe_trigger_vblank(4); nes_write(0x2006, g_cpu.A);
label_8ED7:;
    /* $8ED7: 8D */ maybe_trigger_vblank(4); nes_write(0x2006, g_cpu.A);
label_8EDA:;
    /* $8EDA: 8D */ maybe_trigger_vblank(4); nes_write(0x2006, g_cpu.A);
label_8EDD:; /* UpdateScreen */
    /* $8EDD: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x2002); FLAG_NZ(g_cpu.X);
label_8EE0:;
    /* $8EE0: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_8EE2:;
    /* $8EE2: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0x00) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8EE4:;
    /* $8EE4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8E92;
    }
label_8EE6:; /* InitScroll */
    /* $8EE6: 8D */ maybe_trigger_vblank(4); nes_write(0x2005, g_cpu.A);
label_8EE9:;
    /* $8EE9: 8D */ maybe_trigger_vblank(4); nes_write(0x2005, g_cpu.A);
label_8EEC:;
    /* $8EEC: 60 */ maybe_trigger_vblank(6);
    return;
}

void BgRenderer::write_p_p_u_reg1() {
    (void)state_;
label_8EED:; /* WritePPUReg1 */
    /* $8EED: 8D */ maybe_trigger_vblank(4); nes_write(0x2000, g_cpu.A);
label_8EF0:;
    /* $8EF0: 8D */ maybe_trigger_vblank(4); nes_write(0x0778, g_cpu.A);
label_8EF3:;
    /* $8EF3: 60 */ maybe_trigger_vblank(6);
    return;
}

}  // namespace smb::semcomp
