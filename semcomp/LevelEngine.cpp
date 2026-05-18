// semcomp/LevelEngine.cpp — bulk-ported routines (auto-generated).
#include "semcomp/LevelEngine.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

void LevelEngine::get_background_color() {
    get_background_color_body(0);
}

void LevelEngine::at_862e() {
    get_background_color_body(1);
}

void LevelEngine::write_game_text() {
    write_game_text_body(0);
}

void LevelEngine::at_8887() {
    write_game_text_body(1);
}

void LevelEngine::at_8846() {
    write_game_text_body(2);
}

void LevelEngine::write_block_metatile() {
    write_block_metatile_body(0);
}

void LevelEngine::move_v_offset() {
    write_block_metatile_body(1);
}

void LevelEngine::put_block_metatile() {
    put_block_metatile_body(0);
}

void LevelEngine::rem_bridge() {
    put_block_metatile_body(1);
}

void LevelEngine::at_8a9d() {
    put_block_metatile_body(2);
}

void LevelEngine::get_area_music() {
    get_area_music_body(0);
}

void LevelEngine::at_9100() {
    get_area_music_body(1);
}

void LevelEngine::area_parser_core() {
    area_parser_core_body(0);
}

void LevelEngine::at_9494() {
    area_parser_core_body(1);
}

void LevelEngine::terr_loop() {
    area_parser_core_body(2);
}

void LevelEngine::process_area_data() {
    process_area_data_body(0);
}

void LevelEngine::end_a_parse() {
    process_area_data_body(1);
}

void LevelEngine::decode_area_data() {
    decode_area_data_body(0);
}

void LevelEngine::loop_cmd_e() {
    decode_area_data_body(1);
}

void LevelEngine::at_95df() {
    decode_area_data_body(2);
}

void LevelEngine::area_style_object() {
    area_style_object_body(0);
}

void LevelEngine::at_9792() {
    area_style_object_body(1);
}

void LevelEngine::at_9989() {
    area_style_object_body(2);
}

void LevelEngine::set_hi_max() {
    set_hi_max_body(0);
}

void LevelEngine::set_x_move_amt() {
    set_hi_max_body(1);
}

void LevelEngine::get_background_color_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_862E;
    }
label_85E3:; /* GetBackgroundColor */
    /* $85E3: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0744); FLAG_NZ(g_cpu.Y);
label_85E6:;
    /* $85E6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_85EE;
label_85E8:;
    /* $85E8: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x85C7 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_85EB:;
    /* $85EB: 8D */ maybe_trigger_vblank(4); nes_write(0x0773, g_cpu.A);
label_85EE:; /* NoBGColor */
    /* $85EE: EE */ maybe_trigger_vblank(6); { uint16_t a=0x073C; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
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
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
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
    return;
}

void LevelEngine::write_game_text_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_8887;
        case 2: goto label_8846;
    }
label_8808:; /* WriteGameText */
    /* $8808: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_8809:;
    /* $8809: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_880A:;
    /* $880A: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_880B:;
    /* $880B: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x04; g_cpu.C=(g_cpu.Y>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_880D:;
    /* $880D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_881B;
label_880F:;
    /* $880F: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_8811:;
    /* $8811: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_8815;
label_8813:;
    /* $8813: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x08; FLAG_NZ(g_cpu.Y);
label_8815:; /* Chk2Players */
    /* $8815: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x077A); FLAG_NZ(g_cpu.A);
label_8818:;
    /* $8818: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_881B;
label_881A:;
    /* $881A: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_881B:; /* LdGameText */
    /* $881B: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0x87FE + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_881E:;
    /* $881E: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_8820:; /* GameTextLoop */
    /* $8820: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x8752 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8823:;
    /* $8823: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xFF; g_cpu.C=(g_cpu.A>=0xFF)?1:0; FLAG_NZ(r&0xFF); }
label_8825:;
    /* $8825: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_882E;
label_8827:;
    /* $8827: 99 */ maybe_trigger_vblank(5); nes_write((0x0301 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_882A:;
    /* $882A: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_882B:;
    /* $882B: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_882C:;
    /* $882C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8820;
    }
label_882E:; /* EndGameText */
    /* $882E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8830:;
    /* $8830: 99 */ maybe_trigger_vblank(5); nes_write((0x0301 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8833:;
    /* $8833: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_8834:;
    /* $8834: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_8835:;
    /* $8835: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_8837:;
    /* $8837: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_8882;
label_8839:;
    /* $8839: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_883A:;
    /* $883A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_885F;
label_883C:;
    /* $883C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x075A); FLAG_NZ(g_cpu.A);
label_883F:;
    /* $883F: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8840:;
    /* $8840: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_8842:;
    /* $8842: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0A; g_cpu.C=(g_cpu.A>=0x0A)?1:0; FLAG_NZ(r&0xFF); }
label_8844:;
    /* $8844: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_884D;
label_8846:;
    /* $8846: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x0A; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8848:;
    /* $8848: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x9F; FLAG_NZ(g_cpu.Y);
label_884A:;
    /* $884A: 8C */ maybe_trigger_vblank(4); nes_write(0x0308, g_cpu.Y);
label_884D:; /* PutLives */
    /* $884D: 8D */ maybe_trigger_vblank(4); nes_write(0x0309, g_cpu.A);
label_8850:;
    /* $8850: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x075F); FLAG_NZ(g_cpu.Y);
label_8853:;
    /* $8853: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8854:;
    /* $8854: 8C */ maybe_trigger_vblank(4); nes_write(0x0314, g_cpu.Y);
label_8857:;
    /* $8857: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x075C); FLAG_NZ(g_cpu.Y);
label_885A:;
    /* $885A: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_885B:;
    /* $885B: 8C */ maybe_trigger_vblank(4); nes_write(0x0316, g_cpu.Y);
label_885E:;
    /* $885E: 60 */ maybe_trigger_vblank(6);
    return;
label_885F:; /* CheckPlayerName */
    /* $885F: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x077A); FLAG_NZ(g_cpu.A);
label_8862:;
    /* $8862: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_8881;
label_8864:;
    /* $8864: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0753); FLAG_NZ(g_cpu.A);
label_8867:;
    /* $8867: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_8868:;
    /* $8868: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_8873;
label_886A:;
    /* $886A: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0770); FLAG_NZ(g_cpu.Y);
label_886D:;
    /* $886D: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_886F:;
    /* $886F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_8873;
label_8871:;
    /* $8871: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x01; FLAG_NZ(g_cpu.A);
label_8873:; /* ChkLuigi */
    /* $8873: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_8874:;
    /* $8874: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_8881;
label_8876:;
    /* $8876: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x04; FLAG_NZ(g_cpu.Y);
label_8878:; /* NameLoop */
    /* $8878: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87ED + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_887B:;
    /* $887B: 99 */ maybe_trigger_vblank(5); nes_write((0x0304 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_887E:;
    /* $887E: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_887F:;
    /* $887F: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8878;
    }
label_8881:; /* ExitChkName */
    /* $8881: 60 */ maybe_trigger_vblank(6);
    return;
label_8882:; /* PrintWarpZoneNumbers */
    /* $8882: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x04; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8884:;
    /* $8884: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8885:;
    /* $8885: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8886:;
    /* $8886: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_8887:;
    /* $8887: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_8889:; /* WarpNumLoop */
    /* $8889: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87F2 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_888C:;
    /* $888C: 99 */ maybe_trigger_vblank(5); nes_write((0x031C + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_888F:;
    /* $888F: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_8890:;
    /* $8890: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8891:;
    /* $8891: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8892:;
    /* $8892: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8893:;
    /* $8893: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8894:;
    /* $8894: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0C; g_cpu.C=(g_cpu.Y>=0x0C)?1:0; FLAG_NZ(r&0xFF); }
label_8896:;
    /* $8896: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8889;
    }
label_8898:;
    /* $8898: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2C; FLAG_NZ(g_cpu.A);
label_889A:;
    /* $889A: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x863F); return;
}

void LevelEngine::write_block_metatile_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_8A8F;
    }
label_8A6D:; /* WriteBlockMetatile */
    /* $8A6D: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x03; FLAG_NZ(g_cpu.Y);
label_8A6F:;
    /* $8A6F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_8A71:;
    /* $8A71: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_8A87;
label_8A73:;
    /* $8A73: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_8A75:;
    /* $8A75: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x58; g_cpu.C=(g_cpu.A>=0x58)?1:0; FLAG_NZ(r&0xFF); }
label_8A77:;
    /* $8A77: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_8A87;
label_8A79:;
    /* $8A79: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x51; g_cpu.C=(g_cpu.A>=0x51)?1:0; FLAG_NZ(r&0xFF); }
label_8A7B:;
    /* $8A7B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_8A87;
label_8A7D:;
    /* $8A7D: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8A7E:;
    /* $8A7E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x5D; g_cpu.C=(g_cpu.A>=0x5D)?1:0; FLAG_NZ(r&0xFF); }
label_8A80:;
    /* $8A80: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_8A87;
label_8A82:;
    /* $8A82: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x52; g_cpu.C=(g_cpu.A>=0x52)?1:0; FLAG_NZ(r&0xFF); }
label_8A84:;
    /* $8A84: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_8A87;
label_8A86:;
    /* $8A86: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8A87:; /* UseBOffset */
    /* $8A87: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_8A88:;
    /* $8A88: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0300); FLAG_NZ(g_cpu.Y);
label_8A8B:;
    /* $8A8B: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8A8C:;
    /* $8A8C: 20 */ maybe_trigger_vblank(6); call_by_address(0x8A97);
label_8A8F:; /* MoveVOffset */
    /* $8A8F: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8A90:;
    /* $8A90: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_8A91:;
    /* $8A91: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8A92:;
    /* $8A92: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x0A + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0A); g_cpu.A=r&0xFF; }
label_8A94:;
    /* $8A94: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x863F); return;
}

void LevelEngine::put_block_metatile_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_8ACD;
        case 2: goto label_8A9D;
    }
label_8A97:; /* PutBlockMetatile */
    /* $8A97: 86 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.X);
label_8A99:;
    /* $8A99: 84 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.Y);
label_8A9B:;
    /* $8A9B: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8A9C:;
    /* $8A9C: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8A9D:;
    /* $8A9D: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_8A9E:;
    /* $8A9E: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x20; FLAG_NZ(g_cpu.Y);
label_8AA0:;
    /* $8AA0: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x06); FLAG_NZ(g_cpu.A);
label_8AA2:;
    /* $8AA2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xD0; g_cpu.C=(g_cpu.A>=0xD0)?1:0; FLAG_NZ(r&0xFF); }
label_8AA4:;
    /* $8AA4: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_8AA8;
label_8AA6:;
    /* $8AA6: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x24; FLAG_NZ(g_cpu.Y);
label_8AA8:; /* SaveHAdder */
    /* $8AA8: 84 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.Y);
label_8AAA:;
    /* $8AAA: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_8AAC:;
    /* $8AAC: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8AAD:;
    /* $8AAD: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_8AAF:;
    /* $8AAF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8AB1:;
    /* $8AB1: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_8AB3:;
    /* $8AB3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_8AB5:;
    /* $8AB5: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8AB6:;
    /* $8AB6: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x20 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x20); g_cpu.A=r&0xFF; }
label_8AB8:;
    /* $8AB8: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8AB9:;
    /* $8AB9: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x05; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8ABB:;
    /* $8ABB: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_8ABC:;
    /* $8ABC: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x05; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8ABE:;
    /* $8ABE: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x04); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8AC0:;
    /* $8AC0: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_8AC2:;
    /* $8AC2: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x05); FLAG_NZ(g_cpu.A);
label_8AC4:;
    /* $8AC4: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_8AC6:;
    /* $8AC6: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8AC7:;
    /* $8AC7: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x03); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8AC9:;
    /* $8AC9: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_8ACB:;
    /* $8ACB: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x01); FLAG_NZ(g_cpu.Y);
label_8ACD:; /* RemBridge */
    /* $8ACD: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x8A39 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8AD0:;
    /* $8AD0: 99 */ maybe_trigger_vblank(5); nes_write((0x0303 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8AD3:;
    /* $8AD3: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x8A3A + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8AD6:;
    /* $8AD6: 99 */ maybe_trigger_vblank(5); nes_write((0x0304 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8AD9:;
    /* $8AD9: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x8A3B + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8ADC:;
    /* $8ADC: 99 */ maybe_trigger_vblank(5); nes_write((0x0308 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8ADF:;
    /* $8ADF: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x8A3C + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8AE2:;
    /* $8AE2: 99 */ maybe_trigger_vblank(5); nes_write((0x0309 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8AE5:;
    /* $8AE5: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x04); FLAG_NZ(g_cpu.A);
label_8AE7:;
    /* $8AE7: 99 */ maybe_trigger_vblank(5); nes_write((0x0301 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8AEA:;
    /* $8AEA: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8AEB:;
    /* $8AEB: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x20 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x20); g_cpu.A=r&0xFF; }
label_8AED:;
    /* $8AED: 99 */ maybe_trigger_vblank(5); nes_write((0x0306 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8AF0:;
    /* $8AF0: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x05); FLAG_NZ(g_cpu.A);
label_8AF2:;
    /* $8AF2: 99 */ maybe_trigger_vblank(5); nes_write((0x0300 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8AF5:;
    /* $8AF5: 99 */ maybe_trigger_vblank(5); nes_write((0x0305 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8AF8:;
    /* $8AF8: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_8AFA:;
    /* $8AFA: 99 */ maybe_trigger_vblank(5); nes_write((0x0302 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8AFD:;
    /* $8AFD: 99 */ maybe_trigger_vblank(5); nes_write((0x0307 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8B00:;
    /* $8B00: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_8B02:;
    /* $8B02: 99 */ maybe_trigger_vblank(5); nes_write((0x030A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_8B05:;
    /* $8B05: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x00); FLAG_NZ(g_cpu.X);
label_8B07:;
    /* $8B07: 60 */ maybe_trigger_vblank(6);
    return;
}

void LevelEngine::get_area_music_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_9100;
    }
label_90ED:; /* GetAreaMusic */
    /* $90ED: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0770); FLAG_NZ(g_cpu.A);
label_90F0:;
    /* $90F0: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9115;
label_90F2:;
    /* $90F2: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0752); FLAG_NZ(g_cpu.A);
label_90F5:;
    /* $90F5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_90F7:;
    /* $90F7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9106;
label_90F9:;
    /* $90F9: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x05; FLAG_NZ(g_cpu.Y);
label_90FB:;
    /* $90FB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0710); FLAG_NZ(g_cpu.A);
label_90FE:;
    /* $90FE: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_9100:;
    /* $9100: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9110;
label_9102:;
    /* $9102: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_9104:;
    /* $9104: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9110;
label_9106:; /* ChkAreaType */
    /* $9106: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_9109:;
    /* $9109: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0743); FLAG_NZ(g_cpu.A);
label_910C:;
    /* $910C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9110;
label_910E:;
    /* $910E: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x04; FLAG_NZ(g_cpu.Y);
label_9110:; /* StoreMusic */
    /* $9110: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x90E7 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9113:;
    /* $9113: 85 */ maybe_trigger_vblank(3); nes_write(0xFB, g_cpu.A);
label_9115:; /* ExitGetM */
    /* $9115: 60 */ maybe_trigger_vblank(6);
    return;
}

void LevelEngine::area_parser_core_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_9494;
        case 2: goto label_9491;
    }
label_93FC:; /* AreaParserCore */
    /* $93FC: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0728); FLAG_NZ(g_cpu.A);
label_93FF:;
    /* $93FF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9404;
label_9401:;
    /* $9401: 20 */ maybe_trigger_vblank(6); call_by_address(0x9508);
label_9404:; /* RenderSceneryTerrain */
    /* $9404: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0C; FLAG_NZ(g_cpu.X);
label_9406:;
    /* $9406: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_9408:; /* ClrMTBuf */
    /* $9408: 9D */ maybe_trigger_vblank(5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_940B:;
    /* $940B: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_940C:;
    /* $940C: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9408;
    }
label_940E:;
    /* $940E: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0742); FLAG_NZ(g_cpu.Y);
label_9411:;
    /* $9411: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9455;
label_9413:;
    /* $9413: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0725); FLAG_NZ(g_cpu.A);
label_9416:; /* ThirdP */
    /* $9416: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_9418:;
    /* $9418: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_941F;
label_941A:;
    /* $941A: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_941B:;
    /* $941B: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x03; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_941D:;
    /* $941D: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9416;
    }
label_941F:; /* RendBack */
    /* $941F: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9420:;
    /* $9420: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9421:;
    /* $9421: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9422:;
    /* $9422: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9423:;
    /* $9423: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x92F6 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9426:;
    /* $9426: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0726); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9429:;
    /* $9429: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_942A:;
    /* $942A: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x92FA + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_942D:;
    /* $942D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9455;
label_942F:;
    /* $942F: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9430:;
    /* $9430: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_9432:;
    /* $9432: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_9433:;
    /* $9433: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x01; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9435:;
    /* $9435: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_9437:;
    /* $9437: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9438:;
    /* $9438: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_943A:;
    /* $943A: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_943B:;
    /* $943B: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_943C:;
    /* $943C: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_943D:;
    /* $943D: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_943E:;
    /* $943E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_943F:;
    /* $943F: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9440:;
    /* $9440: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9441:;
    /* $9441: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_9443:;
    /* $9443: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_9445:; /* SceLoop1 */
    /* $9445: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x938A + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9448:;
    /* $9448: 99 */ maybe_trigger_vblank(5); nes_write((0x06A1 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_944B:;
    /* $944B: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_944C:;
    /* $944C: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_944D:;
    /* $944D: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0B; g_cpu.C=(g_cpu.Y>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_944F:;
    /* $944F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9455;
label_9451:;
    /* $9451: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_9453:;
    /* $9453: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9445;
    }
label_9455:; /* RendFore */
    /* $9455: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x0741); FLAG_NZ(g_cpu.X);
label_9458:;
    /* $9458: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_946D;
label_945A:;
    /* $945A: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x93AD + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_945D:;
    /* $945D: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_945F:; /* SceLoop2 */
    /* $945F: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x93B1 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9462:;
    /* $9462: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9467;
label_9464:;
    /* $9464: 9D */ maybe_trigger_vblank(5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9467:; /* NoFore */
    /* $9467: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9468:;
    /* $9468: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_9469:;
    /* $9469: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x0D; g_cpu.C=(g_cpu.X>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_946B:;
    /* $946B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_945F;
    }
label_946D:; /* RendTerr */
    /* $946D: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_9470:;
    /* $9470: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_947E;
label_9472:;
    /* $9472: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_9475:;
    /* $9475: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_9477:;
    /* $9477: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_947E;
label_9479:;
    /* $9479: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x62; FLAG_NZ(g_cpu.A);
label_947B:;
    /* $947B: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x9488); return;
label_947E:; /* TerMTile */
    /* $947E: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x93D8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9481:;
    /* $9481: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0743); FLAG_NZ(g_cpu.Y);
label_9484:;
    /* $9484: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9488;
label_9486:;
    /* $9486: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x88; FLAG_NZ(g_cpu.A);
label_9488:; /* StoreMT */
    /* $9488: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_948A:;
    /* $948A: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_948C:;
    /* $948C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0727); FLAG_NZ(g_cpu.A);
label_948F:;
    /* $948F: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9490:;
    /* $9490: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9491:; /* TerrLoop */
    /* $9491: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x93DC + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9494:;
    /* $9494: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_9496:;
    /* $9496: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9497:;
    /* $9497: 84 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.Y);
label_9499:;
    /* $9499: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0743); FLAG_NZ(g_cpu.A);
label_949C:;
    /* $949C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_94A8;
label_949E:;
    /* $949E: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x00; g_cpu.C=(g_cpu.X>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_94A0:;
    /* $94A0: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_94A8;
label_94A2:;
    /* $94A2: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_94A4:;
    /* $94A4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_94A6:;
    /* $94A6: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_94A8:; /* NoCloud2 */
    /* $94A8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_94AA:; /* TerrBChk */
    /* $94AA: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC68A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_94AD:;
    /* $94AD: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_94AF:;
    /* $94AF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_94B6;
label_94B1:;
    /* $94B1: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x07); FLAG_NZ(g_cpu.A);
label_94B3:;
    /* $94B3: 9D */ maybe_trigger_vblank(5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_94B6:; /* NextTBit */
    /* $94B6: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_94B7:;
    /* $94B7: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x0D; g_cpu.C=(g_cpu.X>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_94B9:;
    /* $94B9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_94D3;
label_94BB:;
    /* $94BB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x074E); FLAG_NZ(g_cpu.A);
label_94BE:;
    /* $94BE: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_94C0:;
    /* $94C0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_94CA;
label_94C2:;
    /* $94C2: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x0B; g_cpu.C=(g_cpu.X>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_94C4:;
    /* $94C4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_94CA;
label_94C6:;
    /* $94C6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x54; FLAG_NZ(g_cpu.A);
label_94C8:;
    /* $94C8: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_94CA:; /* EndUChk */
    /* $94CA: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_94CB:;
    /* $94CB: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_94CD:;
    /* $94CD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_94AA;
    }
label_94CF:;
    /* $94CF: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x01); FLAG_NZ(g_cpu.Y);
label_94D1:;
    /* $94D1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9491;
    }
label_94D3:; /* RendBBuf */
    /* $94D3: 20 */ maybe_trigger_vblank(6); call_by_address(0x9508);
label_94D6:;
    /* $94D6: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06A0); FLAG_NZ(g_cpu.A);
label_94D9:;
    /* $94D9: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BE1);
label_94DC:;
    /* $94DC: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_94DE:;
    /* $94DE: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_94E0:; /* ChkMTLow */
    /* $94E0: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_94E2:;
    /* $94E2: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x06A1 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_94E5:;
    /* $94E5: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xC0; FLAG_NZ(g_cpu.A);
label_94E7:;
    /* $94E7: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_94E8:;
    /* $94E8: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_94E9:;
    /* $94E9: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_94EA:;
    /* $94EA: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_94EB:;
    /* $94EB: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x06A1 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_94EE:;
    /* $94EE: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x9504 + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_94F1:;
    /* $94F1: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_94F5;
label_94F3:;
    /* $94F3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_94F5:; /* StrBlock */
    /* $94F5: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x00); FLAG_NZ(g_cpu.Y);
label_94F7:;
    /* $94F7: 91 */ maybe_trigger_vblank(6); nes_write((nes_read16zp(0x06) + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_94F9:;
    /* $94F9: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_94FA:;
    /* $94FA: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_94FB:;
    /* $94FB: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x10 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x10); g_cpu.A=r&0xFF; }
label_94FD:;
    /* $94FD: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_94FE:;
    /* $94FE: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_94FF:;
    /* $94FF: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x0D; g_cpu.C=(g_cpu.X>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_9501:;
    /* $9501: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_94E0;
    }
label_9503:;
    /* $9503: 60 */ maybe_trigger_vblank(6);
    return;
}

void LevelEngine::process_area_data_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_9588;
    }
label_9508:; /* ProcessAreaData */
    /* $9508: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x02; FLAG_NZ(g_cpu.X);
label_950A:; /* ProcADLoop */
    /* $950A: 86 */ maybe_trigger_vblank(3); nes_write(0x08, g_cpu.X);
label_950C:;
    /* $950C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_950E:;
    /* $950E: 8D */ maybe_trigger_vblank(4); nes_write(0x0729, g_cpu.A);
label_9511:;
    /* $9511: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x072C); FLAG_NZ(g_cpu.Y);
label_9514:;
    /* $9514: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9516:;
    /* $9516: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xFD; g_cpu.C=(g_cpu.A>=0xFD)?1:0; FLAG_NZ(r&0xFF); }
label_9518:;
    /* $9518: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9565;
label_951A:;
    /* $951A: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_951D:;
    /* $951D: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_9565;
label_951F:;
    /* $951F: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9520:;
    /* $9520: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9522:;
    /* $9522: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9523:;
    /* $9523: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_9530;
label_9525:;
    /* $9525: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x072B); FLAG_NZ(g_cpu.A);
label_9528:;
    /* $9528: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_9530;
label_952A:;
    /* $952A: EE */ maybe_trigger_vblank(6); { uint16_t a=0x072B; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_952D:;
    /* $952D: EE */ maybe_trigger_vblank(6); { uint16_t a=0x072A; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_9530:; /* Chk1Row13 */
    /* $9530: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9531:;
    /* $9531: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9533:;
    /* $9533: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_9535:;
    /* $9535: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_9537:;
    /* $9537: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_9554;
label_9539:;
    /* $9539: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_953A:;
    /* $953A: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_953C:;
    /* $953C: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_953D:;
    /* $953D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_953F:;
    /* $953F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_955D;
label_9541:;
    /* $9541: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x072B); FLAG_NZ(g_cpu.A);
label_9544:;
    /* $9544: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_955D;
label_9546:;
    /* $9546: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9547:;
    /* $9547: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9549:;
    /* $9549: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x1F; FLAG_NZ(g_cpu.A);
label_954B:;
    /* $954B: 8D */ maybe_trigger_vblank(4); nes_write(0x072A, g_cpu.A);
label_954E:;
    /* $954E: EE */ maybe_trigger_vblank(6); { uint16_t a=0x072B; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_9551:;
    /* $9551: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x956E); return;
label_9554:; /* Chk1Row14 */
    /* $9554: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0E; g_cpu.C=(g_cpu.A>=0x0E)?1:0; FLAG_NZ(r&0xFF); }
label_9556:;
    /* $9556: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_955D;
label_9558:;
    /* $9558: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0728); FLAG_NZ(g_cpu.A);
label_955B:;
    /* $955B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_9565;
label_955D:; /* CheckRear */
    /* $955D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x072A); FLAG_NZ(g_cpu.A);
label_9560:;
    /* $9560: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0725); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_9563:;
    /* $9563: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_956B;
label_9565:; /* RdyDecode */
    /* $9565: 20 */ maybe_trigger_vblank(6); call_by_address(0x9595);
label_9568:;
    /* $9568: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x9571); return;
label_956B:; /* SetBehind */
    /* $956B: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0729; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_956E:; /* NextAObj */
    /* $956E: 20 */ maybe_trigger_vblank(6); call_by_address(0x9589);
label_9571:; /* ChkLength */
    /* $9571: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_9573:;
    /* $9573: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9576:;
    /* $9576: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_957B;
label_9578:;
    /* $9578: DE */ maybe_trigger_vblank(7); { uint16_t a=(0x0730 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_957B:; /* ProcLoopb */
    /* $957B: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_957C:;
    /* $957C: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_950A;
    }
label_957E:;
    /* $957E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0729); FLAG_NZ(g_cpu.A);
label_9581:;
    /* $9581: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9508;
    }
label_9583:;
    /* $9583: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0728); FLAG_NZ(g_cpu.A);
label_9586:;
    /* $9586: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9508;
    }
label_9588:; /* EndAParse */
    /* $9588: 60 */ maybe_trigger_vblank(6);
    return;
}

void LevelEngine::decode_area_data_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_9645;
        case 2: goto label_95DF;
    }
label_9595:; /* DecodeAreaData */
    /* $9595: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9598:;
    /* $9598: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_959D;
label_959A:;
    /* $959A: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x072D + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_959D:; /* Chk1stB */
    /* $959D: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x10; FLAG_NZ(g_cpu.X);
label_959F:;
    /* $959F: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_95A1:;
    /* $95A1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xFD; g_cpu.C=(g_cpu.A>=0xFD)?1:0; FLAG_NZ(r&0xFF); }
label_95A3:;
    /* $95A3: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { call_by_address(0x9588); return; }
label_95A5:;
    /* $95A5: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_95A7:;
    /* $95A7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0F; g_cpu.C=(g_cpu.A>=0x0F)?1:0; FLAG_NZ(r&0xFF); }
label_95A9:;
    /* $95A9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_95B3;
label_95AB:;
    /* $95AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x08; FLAG_NZ(g_cpu.X);
label_95AD:;
    /* $95AD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0C; g_cpu.C=(g_cpu.A>=0x0C)?1:0; FLAG_NZ(r&0xFF); }
label_95AF:;
    /* $95AF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_95B3;
label_95B1:;
    /* $95B1: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_95B3:; /* ChkRow14 */
    /* $95B3: 86 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.X);
label_95B5:;
    /* $95B5: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_95B7:;
    /* $95B7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0E; g_cpu.C=(g_cpu.A>=0x0E)?1:0; FLAG_NZ(r&0xFF); }
label_95B9:;
    /* $95B9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_95C3;
label_95BB:;
    /* $95BB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_95BD:;
    /* $95BD: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_95BF:;
    /* $95BF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2E; FLAG_NZ(g_cpu.A);
label_95C1:;
    /* $95C1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_9616;
label_95C3:; /* ChkRow13 */
    /* $95C3: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_95C5:;
    /* $95C5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_95E2;
label_95C7:;
    /* $95C7: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x22; FLAG_NZ(g_cpu.A);
label_95C9:;
    /* $95C9: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_95CB:;
    /* $95CB: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_95CC:;
    /* $95CC: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_95CE:;
    /* $95CE: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_95D0:;
    /* $95D0: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9635;
label_95D2:;
    /* $95D2: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_95D4:;
    /* $95D4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x7F; FLAG_NZ(g_cpu.A);
label_95D6:;
    /* $95D6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x4B; g_cpu.C=(g_cpu.A>=0x4B)?1:0; FLAG_NZ(r&0xFF); }
label_95D8:;
    /* $95D8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_95DD;
label_95DA:;
    /* $95DA: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0745; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_95DD:; /* Mask2MSB */
    /* $95DD: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3F; FLAG_NZ(g_cpu.A);
label_95DF:;
    /* $95DF: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x9616); return;
label_95E2:; /* ChkSRows */
    /* $95E2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0C; g_cpu.C=(g_cpu.A>=0x0C)?1:0; FLAG_NZ(r&0xFF); }
label_95E4:;
    /* $95E4: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_960D;
label_95E6:;
    /* $95E6: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_95E7:;
    /* $95E7: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_95E9:;
    /* $95E9: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x70; FLAG_NZ(g_cpu.A);
label_95EB:;
    /* $95EB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_95F8;
label_95ED:;
    /* $95ED: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x16; FLAG_NZ(g_cpu.A);
label_95EF:;
    /* $95EF: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_95F1:;
    /* $95F1: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_95F3:;
    /* $95F3: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_95F5:;
    /* $95F5: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x9616); return;
label_95F8:; /* LrgObj */
    /* $95F8: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_95FA:;
    /* $95FA: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x70; g_cpu.C=(g_cpu.A>=0x70)?1:0; FLAG_NZ(r&0xFF); }
label_95FC:;
    /* $95FC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_9608;
label_95FE:;
    /* $95FE: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9600:;
    /* $9600: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_9602:;
    /* $9602: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9608;
label_9604:;
    /* $9604: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_9606:;
    /* $9606: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_9608:; /* NotWPipe */
    /* $9608: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_960A:;
    /* $960A: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x9612); return;
label_960D:; /* SpecObj */
    /* $960D: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_960E:;
    /* $960E: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9610:;
    /* $9610: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x70; FLAG_NZ(g_cpu.A);
label_9612:; /* MoveAOId */
    /* $9612: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9613:;
    /* $9613: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9614:;
    /* $9614: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9615:;
    /* $9615: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9616:; /* NormObj */
    /* $9616: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_9618:;
    /* $9618: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_961B:;
    /* $961B: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_965F;
label_961D:;
    /* $961D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x072A); FLAG_NZ(g_cpu.A);
label_9620:;
    /* $9620: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0725); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_9623:;
    /* $9623: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9636;
label_9625:;
    /* $9625: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x072C); FLAG_NZ(g_cpu.Y);
label_9628:;
    /* $9628: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_962A:;
    /* $962A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_962C:;
    /* $962C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0E; g_cpu.C=(g_cpu.A>=0x0E)?1:0; FLAG_NZ(r&0xFF); }
label_962E:;
    /* $962E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_9635;
label_9630:;
    /* $9630: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0728); FLAG_NZ(g_cpu.A);
label_9633:;
    /* $9633: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_9656;
label_9635:; /* LeavePar */
    /* $9635: 60 */ maybe_trigger_vblank(6);
    return;
label_9636:; /* InitRear */
    /* $9636: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0728); FLAG_NZ(g_cpu.A);
label_9639:;
    /* $9639: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9646;
label_963B:;
    /* $963B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_963D:;
    /* $963D: 8D */ maybe_trigger_vblank(4); nes_write(0x0728, g_cpu.A);
label_9640:;
    /* $9640: 8D */ maybe_trigger_vblank(4); nes_write(0x0729, g_cpu.A);
label_9643:;
    /* $9643: 85 */ maybe_trigger_vblank(3); nes_write(0x08, g_cpu.A);
label_9645:; /* LoopCmdE */
    /* $9645: 60 */ maybe_trigger_vblank(6);
    return;
label_9646:; /* BackColC */
    /* $9646: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x072C); FLAG_NZ(g_cpu.Y);
label_9649:;
    /* $9649: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_964B:;
    /* $964B: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF0; FLAG_NZ(g_cpu.A);
label_964D:;
    /* $964D: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_964E:;
    /* $964E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_964F:;
    /* $964F: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9650:;
    /* $9650: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9651:;
    /* $9651: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0726); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_9654:;
    /* $9654: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9635;
    }
label_9656:; /* StrAObj */
    /* $9656: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x072C); FLAG_NZ(g_cpu.A);
label_9659:;
    /* $9659: 9D */ maybe_trigger_vblank(5); nes_write((0x072D + g_cpu.X) & 0xFFFF, g_cpu.A);
label_965C:;
    /* $965C: 20 */ maybe_trigger_vblank(6); call_by_address(0x9589);
label_965F:; /* RunAObj */
    /* $965F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_9661:;
    /* $9661: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_9662:;
    /* $9662: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x07); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_9664:;
    /* $9664: 20 */ maybe_trigger_vblank(6); /* inline_dispatch $8E04: 47 entries (bank=0) */
switch(g_cpu.A) {
  case 0: call_by_address(0x98E5); return;
  case 1: call_by_address(0x9740); return;
  case 2: call_by_address(0x9A2E); return;
  case 3: call_by_address(0x9A3E); return;
  case 4: call_by_address(0x99F2); return;
  case 5: call_by_address(0x9A50); return;
  case 6: call_by_address(0x9A59); return;
  case 7: call_by_address(0x98E5); return;
  case 8: call_by_address(0x9B41); return;
  case 9: call_by_address(0x97BA); return;
  case 10: call_by_address(0x9979); return;
  case 11: call_by_address(0x997C); return;
  case 12: call_by_address(0x997F); return;
  case 13: call_by_address(0x9957); return;
  case 14: call_by_address(0x9968); return;
  case 15: call_by_address(0x996B); return;
  case 16: call_by_address(0x99D0); return;
  case 17: call_by_address(0x99D7); return;
  case 18: call_by_address(0x9806); return;
  case 19: call_by_address(0x9AB7); return;
  case 20: call_by_address(0x98AB); return;
  case 21: call_by_address(0x9994); return;
  case 22: call_by_address(0x9B0E); return;
  case 23: call_by_address(0x9B0E); return;
  case 24: call_by_address(0x9B0E); return;
  case 25: call_by_address(0x9B01); return;
  case 26: call_by_address(0x9B19); return;
  case 27: call_by_address(0x9B19); return;
  case 28: call_by_address(0x9B19); return;
  case 29: call_by_address(0x9B14); return;
  case 30: call_by_address(0x9B19); return;
  case 31: call_by_address(0x986F); return;
  case 32: call_by_address(0x9A19); return;
  case 33: call_by_address(0x9AD3); return;
  case 34: call_by_address(0x9882); return;
  case 35: call_by_address(0x999E); return;
  case 36: call_by_address(0x9A09); return;
  case 37: call_by_address(0x9A0E); return;
  case 38: call_by_address(0x9A01); return;
  case 39: call_by_address(0x96F2); return;
  case 40: call_by_address(0x970D); return;
  case 41: call_by_address(0x970D); return;
  case 42: call_by_address(0x972B); return;
  case 43: call_by_address(0x972B); return;
  case 44: call_by_address(0x972B); return;
  case 45: call_by_address(0x9645); return;
  case 46: call_by_address(0x96C5); return;
  default: nes_log_inline_miss(0x9664, g_cpu.A); return;
}
label_96C5:; /* AlterAreaAttributes */
    /* $96C5: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x072D + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_96C8:;
    /* $96C8: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_96C9:;
    /* $96C9: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_96CB:;
    /* $96CB: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_96CC:;
    /* $96CC: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_96CE:;
    /* $96CE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_96E2;
label_96D0:;
    /* $96D0: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_96D1:;
    /* $96D1: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_96D2:;
    /* $96D2: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_96D4:;
    /* $96D4: 8D */ maybe_trigger_vblank(4); nes_write(0x0727, g_cpu.A);
label_96D7:;
    /* $96D7: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_96D8:;
    /* $96D8: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x30; FLAG_NZ(g_cpu.A);
label_96DA:;
    /* $96DA: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_96DB:;
    /* $96DB: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_96DC:;
    /* $96DC: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_96DD:;
    /* $96DD: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_96DE:;
    /* $96DE: 8D */ maybe_trigger_vblank(4); nes_write(0x0742, g_cpu.A);
label_96E1:;
    /* $96E1: 60 */ maybe_trigger_vblank(6);
    return;
label_96E2:; /* Alter2 */
    /* $96E2: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_96E3:;
    /* $96E3: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_96E5:;
    /* $96E5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_96E7:;
    /* $96E7: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_96EE;
label_96E9:;
    /* $96E9: 8D */ maybe_trigger_vblank(4); nes_write(0x0744, g_cpu.A);
label_96EC:;
    /* $96EC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_96EE:; /* SetFore */
    /* $96EE: 8D */ maybe_trigger_vblank(4); nes_write(0x0741, g_cpu.A);
label_96F1:;
    /* $96F1: 60 */ maybe_trigger_vblank(6);
    return;
}

void LevelEngine::area_style_object_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_9792;
        case 2: goto label_9989;
    }
label_9740:; /* AreaStyleObject */
    /* $9740: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0733); FLAG_NZ(g_cpu.A);
label_9743:;
    /* $9743: 20 */ maybe_trigger_vblank(6); /* inline_dispatch $8E04: 5 entries (bank=0) */
switch(g_cpu.A) {
  case 0: call_by_address(0x974C); return;
  case 1: call_by_address(0x9778); return;
  case 2: call_by_address(0x9A69); return;
  case 3: call_by_address(0xBB20); return;
  case 4: call_by_address(0xBD9B); return;
  default: nes_log_inline_miss(0x9743, g_cpu.A); return;
}
label_9750:;
    /* $9750: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0x9759); return; }
label_9752:;
    /* $9752: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9773;
label_9754:;
    /* $9754: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_9767;
label_9756:;
    /* $9756: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_9757:;
    /* $9757: 9D */ maybe_trigger_vblank(5); nes_write((0x0730 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_975A:;
    /* $975A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0725); FLAG_NZ(g_cpu.A);
label_975D:;
    /* $975D: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x0726); FLAG_NZ(g_cpu.A);
label_9760:;
    /* $9760: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9767;
label_9762:;
    /* $9762: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x16; FLAG_NZ(g_cpu.A);
label_9764:;
    /* $9764: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x97B0); return;
label_9767:; /* MidTreeL */
    /* $9767: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_9769:;
    /* $9769: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x17; FLAG_NZ(g_cpu.A);
label_976B:;
    /* $976B: 9D */ maybe_trigger_vblank(5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_976E:;
    /* $976E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x4C; FLAG_NZ(g_cpu.A);
label_9770:;
    /* $9770: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x97AA); return;
label_9773:; /* EndTreeL */
    /* $9773: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_9775:;
    /* $9775: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x97B0); return;
label_9778:; /* MushroomLedge */
    /* $9778: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BAC);
label_977B:;
    /* $977B: 84 */ maybe_trigger_vblank(3); nes_write(0x06, g_cpu.Y);
label_977D:;
    /* $977D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_978B;
label_977F:;
    /* $977F: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9782:;
    /* $9782: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_9783:;
    /* $9783: 9D */ maybe_trigger_vblank(5); nes_write((0x0736 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9786:;
    /* $9786: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x19; FLAG_NZ(g_cpu.A);
label_9788:;
    /* $9788: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x97B0); return;
label_978B:; /* EndMushL */
    /* $978B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1B; FLAG_NZ(g_cpu.A);
label_978D:;
    /* $978D: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_9790:;
    /* $9790: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_97B0;
label_9792:;
    /* $9792: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0736 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9795:;
    /* $9795: 85 */ maybe_trigger_vblank(3); nes_write(0x06, g_cpu.A);
label_9797:;
    /* $9797: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_9799:;
    /* $9799: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1A; FLAG_NZ(g_cpu.A);
label_979B:;
    /* $979B: 9D */ maybe_trigger_vblank(5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_979E:;
    /* $979E: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x06); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_97A0:;
    /* $97A0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_97CE;
label_97A2:;
    /* $97A2: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_97A3:;
    /* $97A3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x4F; FLAG_NZ(g_cpu.A);
label_97A5:;
    /* $97A5: 9D */ maybe_trigger_vblank(5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_97A8:;
    /* $97A8: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x50; FLAG_NZ(g_cpu.A);
label_97AA:; /* AllUnder */
    /* $97AA: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_97AB:;
    /* $97AB: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x0F; FLAG_NZ(g_cpu.Y);
label_97AD:;
    /* $97AD: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x9B7D); return;
label_97B0:; /* NoUnder */
    /* $97B0: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_97B2:;
    /* $97B2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_97B4:;
    /* $97B4: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x9B7D); return;
label_97B7:; /* PulleyRopeMetatiles */
    /* $97B7: 42 */ maybe_trigger_vblank(2); /* ILLEGAL $42 — skip 1 */
label_97B8:;
    /* $97B8: 41 */ maybe_trigger_vblank(6); g_cpu.A ^= nes_read(nes_read16zp((0x43 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_97BA:; /* PulleyRopeObject */
    /* $97BA: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BAC);
label_97BD:;
    /* $97BD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_97BF:;
    /* $97BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_97C8;
label_97C1:;
    /* $97C1: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_97C2:;
    /* $97C2: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_97C5:;
    /* $97C5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_97C8;
label_97C7:;
    /* $97C7: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_97C8:; /* RenderPul */
    /* $97C8: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x97B7 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_97CB:;
    /* $97CB: 8D */ maybe_trigger_vblank(4); nes_write(0x06A1, g_cpu.A);
label_97CE:; /* MushLExit */
    /* $97CE: 60 */ maybe_trigger_vblank(6);
    return;
label_97CF:; /* CastleMetatiles */
    /* $97CF: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0x97CF); return;
label_97D0:;
    /* $97D0: 45 */ maybe_trigger_vblank(3); g_cpu.A ^= nes_read(0x45); FLAG_NZ(g_cpu.A);
label_97D2:;
    /* $97D2: 45 */ maybe_trigger_vblank(3); g_cpu.A ^= nes_read(0x00); FLAG_NZ(g_cpu.A);
label_97D4:;
    /* $97D4: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0x97D4); return;
label_97D5:;
    /* $97D5: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_97D6:;
    /* $97D6: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_97D8:;
    /* $97D8: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0x97D8); return;
label_97D9:;
    /* $97D9: 45 */ maybe_trigger_vblank(3); g_cpu.A ^= nes_read(0x49); FLAG_NZ(g_cpu.A);
label_97DB:;
    /* $97DB: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x49; FLAG_NZ(g_cpu.A);
label_97DD:;
    /* $97DD: 45 */ maybe_trigger_vblank(3); g_cpu.A ^= nes_read(0x47); FLAG_NZ(g_cpu.A);
label_97DF:;
    /* $97DF: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_97E1:;
    /* $97E1: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_97E3:;
    /* $97E3: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_97E5:;
    /* $97E5: 4B */ maybe_trigger_vblank(2); /* ILLEGAL $4B — skip 2 */
label_97E7:;
    /* $97E7: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_97E9:;
    /* $97E9: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x49; FLAG_NZ(g_cpu.A);
label_97EB:;
    /* $97EB: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x49; FLAG_NZ(g_cpu.A);
label_97ED:;
    /* $97ED: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_97EF:;
    /* $97EF: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_97F1:;
    /* $97F1: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_97F3:;
    /* $97F3: 4B */ maybe_trigger_vblank(2); /* ILLEGAL $4B — skip 2 */
label_97F5:;
    /* $97F5: 4B */ maybe_trigger_vblank(2); /* ILLEGAL $4B — skip 2 */
label_97F7:;
    /* $97F7: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_97F9:;
    /* $97F9: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_97FB:;
    /* $97FB: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_97FD:;
    /* $97FD: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_97FF:;
    /* $97FF: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_9801:;
    /* $9801: 4B */ maybe_trigger_vblank(2); /* ILLEGAL $4B — skip 2 */
label_9803:;
    /* $9803: 4B */ maybe_trigger_vblank(2); /* ILLEGAL $4B — skip 2 */
label_9805:;
    /* $9805: 4B */ maybe_trigger_vblank(2); /* ILLEGAL $4B — skip 2 */
label_9807:;
    /* $9807: BB */ maybe_trigger_vblank(4); /* ILLEGAL $BB — skip 3 */
label_980A:;
    /* $980A: 07 */ maybe_trigger_vblank(5); /* ILLEGAL $07 — skip 2 */
label_980C:;
    /* $980C: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x20); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_980E:;
    /* $980E: AF */ maybe_trigger_vblank(4); g_cpu.A = g_cpu.X = nes_read(0x8A9B); FLAG_NZ(g_cpu.A);
label_9811:;
    /* $9811: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9812:;
    /* $9812: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_9815:;
    /* $9815: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_9817:;
    /* $9817: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0B; FLAG_NZ(g_cpu.A);
label_9819:;
    /* $9819: 85 */ maybe_trigger_vblank(3); nes_write(0x06, g_cpu.A);
label_981B:; /* CRendLoop */
    /* $981B: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x97CF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_981E:;
    /* $981E: 9D */ maybe_trigger_vblank(5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9821:;
    /* $9821: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_9822:;
    /* $9822: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x06); FLAG_NZ(g_cpu.A);
label_9824:;
    /* $9824: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_982D;
label_9826:;
    /* $9826: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9827:;
    /* $9827: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9828:;
    /* $9828: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9829:;
    /* $9829: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_982A:;
    /* $982A: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_982B:;
    /* $982B: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x06; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_982D:; /* ChkCFloor */
    /* $982D: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x0B; g_cpu.C=(g_cpu.X>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_982F:;
    /* $982F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_981B;
    }
label_9831:;
    /* $9831: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9832:;
    /* $9832: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_9833:;
    /* $9833: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0725); FLAG_NZ(g_cpu.A);
label_9836:;
    /* $9836: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_986E;
label_9838:;
    /* $9838: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_983B:;
    /* $983B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_983D:;
    /* $983D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9869;
label_983F:;
    /* $983F: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x07); FLAG_NZ(g_cpu.Y);
label_9841:;
    /* $9841: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_9847;
label_9843:;
    /* $9843: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_9845:;
    /* $9845: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9869;
label_9847:; /* NotTall */
    /* $9847: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_9849:;
    /* $9849: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_986E;
label_984B:;
    /* $984B: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BCB);
label_984E:;
    /* $984E: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_984F:;
    /* $984F: 20 */ maybe_trigger_vblank(6); call_by_address(0x994A);
label_9852:;
    /* $9852: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9853:;
    /* $9853: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_9855:;
    /* $9855: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0725); FLAG_NZ(g_cpu.A);
label_9858:;
    /* $9858: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_985A:;
    /* $985A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_985C:;
    /* $985C: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_985E:;
    /* $985E: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_9860:;
    /* $9860: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_9862:;
    /* $9862: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_9864:;
    /* $9864: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x31; FLAG_NZ(g_cpu.A);
label_9866:;
    /* $9866: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_9868:;
    /* $9868: 60 */ maybe_trigger_vblank(6);
    return;
label_9869:; /* PlayerStop */
    /* $9869: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x52; FLAG_NZ(g_cpu.Y);
label_986B:;
    /* $986B: 8C */ maybe_trigger_vblank(4); nes_write(0x06AB, g_cpu.Y);
label_986E:; /* ExitCastle */
    /* $986E: 60 */ maybe_trigger_vblank(6);
    return;
label_986F:; /* WaterPipe */
    /* $986F: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BBB);
label_9872:;
    /* $9872: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_9875:;
    /* $9875: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_9877:;
    /* $9877: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x6B; FLAG_NZ(g_cpu.A);
label_9879:;
    /* $9879: 9D */ maybe_trigger_vblank(5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_987C:;
    /* $987C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x6C; FLAG_NZ(g_cpu.A);
label_987E:;
    /* $987E: 9D */ maybe_trigger_vblank(5); nes_write((0x06A2 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9881:;
    /* $9881: 60 */ maybe_trigger_vblank(6);
    return;
label_9882:; /* IntroPipe */
    /* $9882: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x03; FLAG_NZ(g_cpu.Y);
label_9884:;
    /* $9884: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BAF);
label_9887:;
    /* $9887: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x0A; FLAG_NZ(g_cpu.Y);
label_9889:;
    /* $9889: 20 */ maybe_trigger_vblank(6); call_by_address(0x98B3);
label_988C:;
    /* $988C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_989E;
label_988E:;
    /* $988E: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x06; FLAG_NZ(g_cpu.X);
label_9890:; /* VPipeSectLoop */
    /* $9890: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_9892:;
    /* $9892: 9D */ maybe_trigger_vblank(5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9895:;
    /* $9895: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_9896:;
    /* $9896: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9890;
    }
label_9898:;
    /* $9898: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x98DD + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_989B:;
    /* $989B: 8D */ maybe_trigger_vblank(4); nes_write(0x06A8, g_cpu.A);
label_989E:; /* NoBlankP */
    /* $989E: 60 */ maybe_trigger_vblank(6);
    return;
label_989F:; /* SidePipeShaftData */
    /* $989F: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x14 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_98A1:;
    /* $98A1: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0x98A1); return;
label_98A2:;
    /* $98A2: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0x98A2); return;
label_98A3:; /* SidePipeTopPart */
    /* $98A3: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_98A5:;
    /* $98A5: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x151C + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_98A8:;
    /* $98A8: 21 */ maybe_trigger_vblank(6); g_cpu.A &= nes_read(nes_read16zp((0x20 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_98AA:;
    /* $98AA: 1F */ maybe_trigger_vblank(7); /* ILLEGAL $1F — skip 3 */
label_98AD:;
    /* $98AD: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BAF);
label_98B0:;
    /* $98B0: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BBB);
label_98B3:; /* RenderSidewaysPipe */
    /* $98B3: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_98B4:;
    /* $98B4: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_98B5:;
    /* $98B5: 84 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.Y);
label_98B7:;
    /* $98B7: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_98BA:;
    /* $98BA: 84 */ maybe_trigger_vblank(3); nes_write(0x06, g_cpu.Y);
label_98BC:;
    /* $98BC: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x05); FLAG_NZ(g_cpu.X);
label_98BE:;
    /* $98BE: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_98BF:;
    /* $98BF: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x989F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_98C2:;
    /* $98C2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_98C4:;
    /* $98C4: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_98CE;
label_98C6:;
    /* $98C6: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_98C8:;
    /* $98C8: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x05); FLAG_NZ(g_cpu.Y);
label_98CA:;
    /* $98CA: 20 */ maybe_trigger_vblank(6); call_by_address(0x9B7D);
label_98CD:;
    /* $98CD: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_98CE:; /* DrawSidePart */
    /* $98CE: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x06); FLAG_NZ(g_cpu.Y);
label_98D0:;
    /* $98D0: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x98A3 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_98D3:;
    /* $98D3: 9D */ maybe_trigger_vblank(5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_98D6:;
    /* $98D6: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x98A7 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_98D9:;
    /* $98D9: 9D */ maybe_trigger_vblank(5); nes_write((0x06A2 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_98DC:;
    /* $98DC: 60 */ maybe_trigger_vblank(6);
    return;
label_98DD:; /* VerticalPipeData */
    /* $98DD: 11 */ maybe_trigger_vblank(5); g_cpu.A |= nes_read((nes_read16zp(0x10) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_98DF:;
    /* $98DF: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x14 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_98E1:;
    /* $98E1: 13 */ maybe_trigger_vblank(8); /* ILLEGAL $13 — skip 2 */
label_98E3:;
    /* $98E3: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x14 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_98E5:; /* VerticalPipe */
    /* $98E5: 20 */ maybe_trigger_vblank(6); call_by_address(0x9939);
label_98E8:;
    /* $98E8: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_98EA:;
    /* $98EA: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_98F0;
label_98EC:;
    /* $98EC: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_98ED:;
    /* $98ED: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_98EE:;
    /* $98EE: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_98EF:;
    /* $98EF: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_98F0:; /* WarpPipe */
    /* $98F0: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_98F1:;
    /* $98F1: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_98F2:;
    /* $98F2: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0760); FLAG_NZ(g_cpu.A);
label_98F5:;
    /* $98F5: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_98F8:;
    /* $98F8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9925;
label_98FA:;
    /* $98FA: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_98FD:;
    /* $98FD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9925;
label_98FF:;
    /* $98FF: 20 */ maybe_trigger_vblank(6); call_by_address(0x994A);
label_9902:;
    /* $9902: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_9925;
label_9904:;
    /* $9904: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BCB);
label_9907:;
    /* $9907: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_9908:;
    /* $9908: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_990A:;
    /* $990A: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_990C:;
    /* $990C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0725); FLAG_NZ(g_cpu.A);
label_990F:;
    /* $990F: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_9911:;
    /* $9911: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_9913:;
    /* $9913: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_9915:;
    /* $9915: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_9917:;
    /* $9917: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_9919:;
    /* $9919: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BD3);
label_991C:;
    /* $991C: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_991E:;
    /* $991E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0D; FLAG_NZ(g_cpu.A);
label_9920:;
    /* $9920: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_9922:;
    /* $9922: 20 */ maybe_trigger_vblank(6); call_by_address(0xC787);
label_9925:; /* DrawPipe */
    /* $9925: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9926:;
    /* $9926: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9927:;
    /* $9927: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x07); FLAG_NZ(g_cpu.X);
label_9929:;
    /* $9929: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x98DD + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_992C:;
    /* $992C: 9D */ maybe_trigger_vblank(5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_992F:;
    /* $992F: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_9930:;
    /* $9930: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x98DF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9933:;
    /* $9933: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x06); FLAG_NZ(g_cpu.Y);
label_9935:;
    /* $9935: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_9936:;
    /* $9936: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x9B7D); return;
label_9939:; /* GetPipeHeight */
    /* $9939: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_993B:;
    /* $993B: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BAF);
label_993E:;
    /* $993E: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BBB);
label_9941:;
    /* $9941: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_9942:;
    /* $9942: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_9944:;
    /* $9944: 85 */ maybe_trigger_vblank(3); nes_write(0x06, g_cpu.A);
label_9946:;
    /* $9946: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x0730 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_9949:;
    /* $9949: 60 */ maybe_trigger_vblank(6);
    return;
label_994A:; /* FindEmptyEnemySlot */
    /* $994A: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_994C:; /* EmptyChkLoop */
    /* $994C: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_994D:;
    /* $994D: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_994F:;
    /* $994F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9956;
label_9951:;
    /* $9951: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_9952:;
    /* $9952: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x05; g_cpu.C=(g_cpu.X>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_9954:;
    /* $9954: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_994C;
    }
label_9956:; /* ExitEmptyChk */
    /* $9956: 60 */ maybe_trigger_vblank(6);
    return;
label_9957:; /* Hole_Water */
    /* $9957: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BAC);
label_995A:;
    /* $995A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x86; FLAG_NZ(g_cpu.A);
label_995C:;
    /* $995C: 8D */ maybe_trigger_vblank(4); nes_write(0x06AB, g_cpu.A);
label_995F:;
    /* $995F: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0B; FLAG_NZ(g_cpu.X);
label_9961:;
    /* $9961: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_9963:;
    /* $9963: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x87; FLAG_NZ(g_cpu.A);
label_9965:;
    /* $9965: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x9B7D); return;
label_9968:; /* QuestionBlockRow_High */
    /* $9968: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_996A:;
    /* $996A: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x07A9); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_996D:;
    /* $996D: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_996E:;
    /* $996E: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BAC);
label_9971:;
    /* $9971: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9972:;
    /* $9972: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_9973:;
    /* $9973: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xC0; FLAG_NZ(g_cpu.A);
label_9975:;
    /* $9975: 9D */ maybe_trigger_vblank(5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_9978:;
    /* $9978: 60 */ maybe_trigger_vblank(6);
    return;
label_9979:; /* Bridge_High */
    /* $9979: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_997B:;
    /* $997B: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x07A9); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_997E:;
    /* $997E: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x09A9); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_9981:;
    /* $9981: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9982:;
    /* $9982: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BAC);
label_9985:;
    /* $9985: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9986:;
    /* $9986: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_9987:;
    /* $9987: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0B; FLAG_NZ(g_cpu.A);
label_9989:;
    /* $9989: 9D */ maybe_trigger_vblank(5); nes_write((0x06A1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_998C:;
    /* $998C: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_998D:;
    /* $998D: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_998F:;
    /* $998F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x63; FLAG_NZ(g_cpu.A);
label_9991:;
    /* $9991: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x9B7D); return;
}

void LevelEngine::set_hi_max_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_BF96;
    }
label_BF94:; /* SetHiMax */
    /* $BF94: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_BF96:; /* SetXMoveAmt */
    /* $BF96: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_BF98:;
    /* $BF98: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_BF99:;
    /* $BF99: 20 */ maybe_trigger_vblank(6); call_by_address(0xBFAD);
label_BF9C:;
    /* $BF9C: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_BF9E:;
    /* $BF9E: 60 */ maybe_trigger_vblank(6);
    return;
}

}  // namespace smb::semcomp
