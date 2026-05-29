// semcomp/RenderEngine.cpp — bulk-ported routines (auto-generated).
#include "semcomp/RenderEngine.h"

#include "semcomp/GameState.h"
#include "semcomp/OamWriter.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

// $F171 GetObjRelativePosition — OWNED to publish per-object identity to the
// OAM emit path (OamWriter). The vanilla body (8-bit screen-relative position
// into $03B8+Y / $03AD+Y) is reproduced EXACTLY — same cycle calls + flag
// semantics — so behavior is byte-identical; we only ADD the identity publish
// at the end. The extra reads carry no emulated CPU cycles and touch only work
// RAM (no MMIO side effects), so NMI timing and CPU state are preserved.
void RenderEngine::get_obj_relative_position() {
    (void)state_;
    /* $F171: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCE + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
    /* $F173: 99 */ maybe_trigger_vblank(5); nes_write((0x03B8 + g_cpu.Y) & 0xFFFF, g_cpu.A);
    /* $F176: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x86 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
    /* $F178: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
    /* $F179: ED */ maybe_trigger_vblank(4); { uint8_t m = nes_read(0x071C); int16_t r = g_cpu.A - m - (1 - g_cpu.C); FLAG_NZC_SUB(r, g_cpu.A, m); g_cpu.A = r & 0xFF; }
    /* $F17C: 99 */ maybe_trigger_vblank(5); nes_write((0x03AD + g_cpu.Y) & 0xFFFF, g_cpu.A);
    /* $F17F: 60 */ maybe_trigger_vblank(6);

    // Publish this object as the owner of the OAM writes its draw is about to
    // make. obj_index (X) + rel_ofs (Y) identify it; rel_x8 is the just-stored
    // 8-bit screen X; screen_x16 is the full signed 16-bit screen X (world -
    // camera), recovered fresh from the same arrays the 8-bit math used.
    const uint8_t obj_index = g_cpu.X;
    const uint8_t rel_ofs   = g_cpu.Y;
    const uint8_t rel_x8    = g_cpu.A;
    const int world_x  = (nes_read((0x6D + obj_index) & 0xFF) << 8) | nes_read((0x86 + obj_index) & 0xFF);
    const int camera_x = (nes_read(0x071A) << 8) | nes_read(0x071C);
    int screen_x16 = world_x - camera_x;
    if (screen_x16 > 32767)  screen_x16 -= 65536;
    if (screen_x16 < -32768) screen_x16 += 65536;
    OamWriter::set_current_owner(obj_index, rel_ofs, static_cast<int16_t>(screen_x16), rel_x8);
}

void RenderEngine::sprite_shuffler() {
    sprite_shuffler_body(0);
}

void RenderEngine::at_8200() {
    sprite_shuffler_body(1);
}

void RenderEngine::set_misc_offset() {
    sprite_shuffler_body(2);
}

void RenderEngine::oper_mode_execution_tree() {
    oper_mode_execution_tree_body(0);
}

void RenderEngine::at_8222() {
    oper_mode_execution_tree_body(1);
}

void RenderEngine::draw_mushroom_icon() {
    draw_mushroom_icon_body(0);
}

void RenderEngine::at_8330() {
    draw_mushroom_icon_body(1);
}

void RenderEngine::player_victory_walk() {
    player_victory_walk_body(0);
}

void RenderEngine::eval_for_music() {
    player_victory_walk_body(1);
}

void RenderEngine::at_8436() {
    player_victory_walk_body(2);
}

void RenderEngine::at_842c() {
    player_victory_walk_body(3);
}

void RenderEngine::at_8404() {
    player_victory_walk_body(4);
}

void RenderEngine::player_end_world() {
    player_end_world_body(0);
}

void RenderEngine::end_exit_one() {
    player_end_world_body(1);
}

void RenderEngine::screen_routines() {
    screen_routines_body(0);
}

void RenderEngine::at_85ad() {
    screen_routines_body(1);
}

void RenderEngine::do_nothing1() {
    do_nothing1_body(0);
}

void RenderEngine::do_nothing2() {
    do_nothing1_body(1);
}

void RenderEngine::scroll_handler() {
    scroll_handler_body(0);
}

void RenderEngine::at_afb1() {
    scroll_handler_body(1);
}

void RenderEngine::run_game_timer() {
    run_game_timer_body(0);
}

void RenderEngine::ex_g_timer() {
    run_game_timer_body(1);
}

void RenderEngine::move_d_enemy_vertically() {
    move_d_enemy_vertically_body(0);
}

void RenderEngine::move_falling_platform() {
    move_d_enemy_vertically_body(1);
}

void RenderEngine::enemy_gfx_handler() {
    enemy_gfx_handler_body(0);
}

void RenderEngine::at_e9a0() {
    enemy_gfx_handler_body(1);
}

void RenderEngine::at_e939() {
    enemy_gfx_handler_body(2);
}

void RenderEngine::at_e9b2() {
    enemy_gfx_handler_body(3);
}

void RenderEngine::at_e96d() {
    enemy_gfx_handler_body(4);
}

void RenderEngine::check_for_goomba() {
    enemy_gfx_handler_body(5);
}

void RenderEngine::at_e998() {
    enemy_gfx_handler_body(6);
}

void RenderEngine::at_eb20() {
    enemy_gfx_handler_body(7);
}

void RenderEngine::at_e96f() {
    enemy_gfx_handler_body(8);
}

void RenderEngine::at_e987() {
    enemy_gfx_handler_body(9);
}

void RenderEngine::at_e9b6() {
    enemy_gfx_handler_body(10);
}

void RenderEngine::at_e9d6() {
    enemy_gfx_handler_body(11);
}

void RenderEngine::at_e908() {
    enemy_gfx_handler_body(12);
}

void RenderEngine::at_eb86() {
    enemy_gfx_handler_body(13);
}

void RenderEngine::at_e921() {
    enemy_gfx_handler_body(14);
}

void RenderEngine::at_eba4() {
    enemy_gfx_handler_body(15);
}

void RenderEngine::at_eb84() {
    enemy_gfx_handler_body(16);
}

void RenderEngine::at_eba6() {
    enemy_gfx_handler_body(17);
}

void RenderEngine::at_eaad() {
    enemy_gfx_handler_body(18);
}

void RenderEngine::at_eae7() {
    enemy_gfx_handler_body(19);
}

void RenderEngine::at_e9eb() {
    enemy_gfx_handler_body(20);
}

void RenderEngine::at_ea3d() {
    enemy_gfx_handler_body(21);
}

void RenderEngine::at_eaba() {
    enemy_gfx_handler_body(22);
}

void RenderEngine::at_e9d0() {
    enemy_gfx_handler_body(23);
}

void RenderEngine::at_e9e0() {
    enemy_gfx_handler_body(24);
}

void RenderEngine::at_e919() {
    enemy_gfx_handler_body(25);
}

void RenderEngine::at_ea20() {
    enemy_gfx_handler_body(26);
}

void RenderEngine::check_bowser_rear() {
    enemy_gfx_handler_body(27);
}

void RenderEngine::at_e960() {
    enemy_gfx_handler_body(28);
}

void RenderEngine::at_e9a4() {
    enemy_gfx_handler_body(29);
}

void RenderEngine::at_ead0() {
    enemy_gfx_handler_body(30);
}

void RenderEngine::at_ea85() {
    enemy_gfx_handler_body(31);
}

void RenderEngine::at_e928() {
    enemy_gfx_handler_body(32);
}

void RenderEngine::at_eb80() {
    enemy_gfx_handler_body(33);
}

void RenderEngine::at_ea32() {
    enemy_gfx_handler_body(34);
}

void RenderEngine::at_e962() {
    enemy_gfx_handler_body(35);
}

void RenderEngine::skip_to_off_scr_chk() {
    enemy_gfx_handler_body(36);
}

void RenderEngine::at_e953() {
    enemy_gfx_handler_body(37);
}

void RenderEngine::at_e9b0() {
    enemy_gfx_handler_body(38);
}

void RenderEngine::at_e9d4() {
    enemy_gfx_handler_body(39);
}

void RenderEngine::at_eb79() {
    enemy_gfx_handler_body(40);
}

void RenderEngine::at_e902() {
    enemy_gfx_handler_body(41);
}

void RenderEngine::draw_bowser() {
    enemy_gfx_handler_body(42);
}

void RenderEngine::at_eae1() {
    enemy_gfx_handler_body(43);
}

void RenderEngine::move_e_spr_row_offscreen() {
    move_e_spr_row_offscreen_body(0);
}

void RenderEngine::at_ebb8() {
    move_e_spr_row_offscreen_body(1);
}

void RenderEngine::at_ebbc() {
    move_e_spr_row_offscreen_body(2);
}

void RenderEngine::move_e_spr_col_offscreen() {
    move_e_spr_col_offscreen_body(0);
}

void RenderEngine::at_ebc6() {
    move_e_spr_col_offscreen_body(1);
}

void RenderEngine::at_ebc2() {
    move_e_spr_col_offscreen_body(2);
}

void RenderEngine::draw_block() {
    draw_block_body(0);
}

void RenderEngine::at_ec20() {
    draw_block_body(1);
}

void RenderEngine::set_b_flip() {
    draw_block_body(2);
}

void RenderEngine::d_blk_loop() {
    draw_block_body(3);
}

void RenderEngine::at_ebec() {
    draw_block_body(4);
}

void RenderEngine::at_ec23() {
    draw_block_body(5);
}

void RenderEngine::at_ebea() {
    draw_block_body(6);
}

void RenderEngine::blk_offscr() {
    draw_block_body(7);
}

void RenderEngine::at_ec00() {
    draw_block_body(8);
}

void RenderEngine::draw_brick_chunks() {
    draw_brick_chunks_body(0);
}

void RenderEngine::at_ec91() {
    draw_brick_chunks_body(1);
}

void RenderEngine::at_ec85() {
    draw_brick_chunks_body(2);
}

void RenderEngine::at_eca5() {
    draw_brick_chunks_body(3);
}

void RenderEngine::d_chunks() {
    draw_brick_chunks_body(4);
}

void RenderEngine::draw_fireball() {
    draw_fireball_body(0);
}

void RenderEngine::at_ecf0() {
    draw_fireball_body(1);
}

void RenderEngine::at_ecf1() {
    draw_fireball_body(2);
}

void RenderEngine::draw_explosion_fireball() {
    draw_explosion_fireball_body(0);
}

void RenderEngine::at_ed20() {
    draw_explosion_fireball_body(1);
}

void RenderEngine::at_ed18() {
    draw_explosion_fireball_body(2);
}

void RenderEngine::at_ed2e() {
    draw_explosion_fireball_body(3);
}

void RenderEngine::draw_small_platform() {
    draw_small_platform_body(0);
}

void RenderEngine::s_ofs2() {
    draw_small_platform_body(1);
}

void RenderEngine::at_ed6f() {
    draw_small_platform_body(2);
}

void RenderEngine::at_edc5() {
    draw_small_platform_body(3);
}

void RenderEngine::at_ed86() {
    draw_small_platform_body(4);
}

void RenderEngine::at_eda6() {
    draw_small_platform_body(5);
}

void RenderEngine::at_edb9() {
    draw_small_platform_body(6);
}

void RenderEngine::at_ed76() {
    draw_small_platform_body(7);
}

void RenderEngine::draw_bubble() {
    draw_bubble_body(0);
}

void RenderEngine::ex_d_bub() {
    draw_bubble_body(1);
}

void RenderEngine::at_ee03() {
    draw_bubble_body(2);
}

void RenderEngine::at_eded() {
    draw_bubble_body(3);
}

void RenderEngine::at_ede3() {
    draw_bubble_body(4);
}

void RenderEngine::at_ede4() {
    draw_bubble_body(5);
}

void RenderEngine::at_ede6() {
    draw_bubble_body(6);
}

void RenderEngine::at_ee01() {
    draw_bubble_body(7);
}

void RenderEngine::render_player_sub() {
    render_player_sub_body(0);
}

void RenderEngine::at_efd1() {
    render_player_sub_body(1);
}

void RenderEngine::at_efdf() {
    render_player_sub_body(2);
}

void RenderEngine::process_player_action() {
    process_player_action_body(0);
}

void RenderEngine::at_f008() {
    process_player_action_body(1);
}

void RenderEngine::at_f041() {
    process_player_action_body(2);
}

void RenderEngine::at_f004() {
    process_player_action_body(3);
}

void RenderEngine::at_f006() {
    process_player_action_body(4);
}

void RenderEngine::at_f012() {
    process_player_action_body(5);
}

void RenderEngine::at_f010() {
    process_player_action_body(6);
}

void RenderEngine::at_f058() {
    process_player_action_body(7);
}

void RenderEngine::at_f02d() {
    process_player_action_body(8);
}

void RenderEngine::at_f001() {
    process_player_action_body(9);
}

void RenderEngine::at_f021() {
    process_player_action_body(10);
}

void RenderEngine::action_walk_run() {
    process_player_action_body(11);
}

void RenderEngine::at_f01f() {
    process_player_action_body(12);
}

void RenderEngine::at_eff0() {
    process_player_action_body(13);
}

void RenderEngine::at_f046() {
    process_player_action_body(14);
}

void RenderEngine::at_f014() {
    process_player_action_body(15);
}

void RenderEngine::at_f00d() {
    process_player_action_body(16);
}

void RenderEngine::at_f030() {
    process_player_action_body(17);
}

void RenderEngine::at_f033() {
    process_player_action_body(18);
}

void RenderEngine::at_f025() {
    process_player_action_body(19);
}

void RenderEngine::action_falling() {
    process_player_action_body(20);
}

void RenderEngine::at_f02b() {
    process_player_action_body(21);
}

void RenderEngine::proc_on_ground_acts() {
    process_player_action_body(22);
}

void RenderEngine::at_f01d() {
    process_player_action_body(23);
}

void RenderEngine::at_f027() {
    process_player_action_body(24);
}

void RenderEngine::at_f05f() {
    process_player_action_body(25);
}

void RenderEngine::at_f060() {
    process_player_action_body(26);
}

void RenderEngine::at_f016() {
    process_player_action_body(27);
}

void RenderEngine::at_effd() {
    process_player_action_body(28);
}

void RenderEngine::at_f048() {
    process_player_action_body(29);
}

void RenderEngine::action_swimming() {
    process_player_action_body(30);
}

void RenderEngine::at_f03e() {
    process_player_action_body(31);
}

void RenderEngine::at_f065() {
    process_player_action_body(32);
}

void RenderEngine::at_f018() {
    process_player_action_body(33);
}

void RenderEngine::at_f05d() {
    process_player_action_body(34);
}

void RenderEngine::at_f052() {
    process_player_action_body(35);
}

void RenderEngine::at_f01a() {
    process_player_action_body(36);
}

void RenderEngine::at_f06a() {
    process_player_action_body(37);
}

void RenderEngine::at_f023() {
    process_player_action_body(38);
}

void RenderEngine::at_f039() {
    process_player_action_body(39);
}

void RenderEngine::three_frame_extent() {
    three_frame_extent_body(0);
}

void RenderEngine::at_f090() {
    three_frame_extent_body(1);
}

void RenderEngine::at_f086() {
    three_frame_extent_body(2);
}

void RenderEngine::at_f07d() {
    three_frame_extent_body(3);
}

void RenderEngine::at_f074() {
    three_frame_extent_body(4);
}

void RenderEngine::at_f075() {
    three_frame_extent_body(5);
}

void RenderEngine::at_f080() {
    three_frame_extent_body(6);
}

void RenderEngine::at_f088() {
    three_frame_extent_body(7);
}

void RenderEngine::get_gfx_offset_adder() {
    get_gfx_offset_adder_body(0);
}

void RenderEngine::at_f098() {
    get_gfx_offset_adder_body(1);
}

void RenderEngine::handle_change_size() {
    handle_change_size_body(0);
}

void RenderEngine::at_f0e1() {
    handle_change_size_body(1);
}

void RenderEngine::c_sz_next() {
    handle_change_size_body(2);
}

void RenderEngine::at_f0b9() {
    handle_change_size_body(3);
}

void RenderEngine::at_f0ba() {
    handle_change_size_body(4);
}

void RenderEngine::at_f0c9() {
    handle_change_size_body(5);
}

void RenderEngine::gor_s_log() {
    handle_change_size_body(6);
}

void RenderEngine::at_f0e3() {
    handle_change_size_body(7);
}

void RenderEngine::at_f0de() {
    handle_change_size_body(8);
}

void RenderEngine::at_f0cb() {
    handle_change_size_body(9);
}

void RenderEngine::at_f0d8() {
    handle_change_size_body(10);
}

void RenderEngine::at_f0d9() {
    handle_change_size_body(11);
}

void RenderEngine::at_f0d1() {
    handle_change_size_body(12);
}

void RenderEngine::at_f0c0() {
    handle_change_size_body(13);
}

void RenderEngine::at_f0e8() {
    handle_change_size_body(14);
}

void RenderEngine::at_f0be() {
    handle_change_size_body(15);
}

void RenderEngine::chk_for_player_attrib() {
    chk_for_player_attrib_body(0);
}

void RenderEngine::at_f0f0() {
    chk_for_player_attrib_body(1);
}

void RenderEngine::at_f110() {
    chk_for_player_attrib_body(2);
}

void RenderEngine::at_f0f9() {
    chk_for_player_attrib_body(3);
}

void RenderEngine::at_f0fd() {
    chk_for_player_attrib_body(4);
}

void RenderEngine::at_f0ee() {
    chk_for_player_attrib_body(5);
}

void RenderEngine::at_f0fb() {
    chk_for_player_attrib_body(6);
}

void RenderEngine::at_f0ff() {
    chk_for_player_attrib_body(7);
}

void RenderEngine::at_f0f2() {
    chk_for_player_attrib_body(8);
}

void RenderEngine::at_f0f5() {
    chk_for_player_attrib_body(9);
}

void RenderEngine::at_f11f() {
    chk_for_player_attrib_body(10);
}

void RenderEngine::relative_misc_position() {
    relative_misc_position_body(0);
}

void RenderEngine::at_f14d() {
    relative_misc_position_body(1);
}

void RenderEngine::get_player_offscreen_bits() {
    get_player_offscreen_bits_body(0);
}

void RenderEngine::at_f184() {
    get_player_offscreen_bits_body(1);
}

void RenderEngine::get_misc_offscreen_bits() {
    get_misc_offscreen_bits_body(0);
}

void RenderEngine::at_f19d() {
    get_misc_offscreen_bits_body(1);
}

void RenderEngine::get_proper_obj_offset() {
    get_proper_obj_offset_body(0);
}

void RenderEngine::at_f1a9() {
    get_proper_obj_offset_body(1);
}

void RenderEngine::get_enemy_offscreen_bits() {
    get_enemy_offscreen_bits_body(0);
}

void RenderEngine::at_f1b1() {
    get_enemy_offscreen_bits_body(1);
}

void RenderEngine::get_block_offscreen_bits() {
    get_block_offscreen_bits_body(0);
}

void RenderEngine::at_f1d1() {
    get_block_offscreen_bits_body(1);
}

void RenderEngine::at_f1bd() {
    get_block_offscreen_bits_body(2);
}

void RenderEngine::at_f1bc() {
    get_block_offscreen_bits_body(3);
}

void RenderEngine::at_f1c1() {
    get_block_offscreen_bits_body(4);
}

void RenderEngine::at_f1ce() {
    get_block_offscreen_bits_body(5);
}

void RenderEngine::get_y_offscreen_bits() {
    get_y_offscreen_bits_body(0);
}

void RenderEngine::y_ofs_loop() {
    get_y_offscreen_bits_body(1);
}

void RenderEngine::draw_sprite_object() {
    draw_sprite_object_body(0);
}

void RenderEngine::at_f2bd() {
    draw_sprite_object_body(1);
}

void RenderEngine::at_f285() {
    draw_sprite_object_body(2);
}

void RenderEngine::at_f286() {
    draw_sprite_object_body(3);
}

void RenderEngine::at_f2a5() {
    draw_sprite_object_body(4);
}

void RenderEngine::at_f284() {
    draw_sprite_object_body(5);
}

void RenderEngine::at_f2c8() {
    draw_sprite_object_body(6);
}

void RenderEngine::at_f288() {
    draw_sprite_object_body(7);
}

void RenderEngine::sprite_shuffler_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_8200;
        case 2: goto label_81F9;
    }
label_81C6:; /* SpriteShuffler */
    /* $81C6: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_81C9:;
    /* $81C9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_81CB:;
    /* $81CB: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_81CD:;
    /* $81CD: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_81CF:; /* ShuffleLoop */
    /* $81CF: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x06E4 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_81D2:;
    /* $81D2: C5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_81D4:;
    /* $81D4: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_81E5;
label_81D6:;
    /* $81D6: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06E0); FLAG_NZ(g_cpu.Y);
label_81D9:;
    /* $81D9: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_81DA:;
    /* $81DA: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x06E1 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_81DD:;
    /* $81DD: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_81E2;
label_81DF:;
    /* $81DF: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_81E0:;
    /* $81E0: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_81E2:; /* StrSprOffset */
    /* $81E2: 9D */ maybe_trigger_vblank(5); nes_write((0x06E4 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_81E5:; /* NextSprOffset */
    /* $81E5: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_81E6:;
    /* $81E6: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_81CF;
    }
label_81E8:;
    /* $81E8: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x06E0); FLAG_NZ(g_cpu.X);
label_81EB:;
    /* $81EB: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_81EC:;
    /* $81EC: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x03; g_cpu.C=(g_cpu.X>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_81EE:;
    /* $81EE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_81F2;
label_81F0:;
    /* $81F0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_81F2:; /* SetAmtOffset */
    /* $81F2: 8E */ maybe_trigger_vblank(4); nes_write(0x06E0, g_cpu.X);
label_81F5:;
    /* $81F5: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x08; FLAG_NZ(g_cpu.X);
label_81F7:;
    /* $81F7: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_81F9:; /* SetMiscOffset */
    /* $81F9: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x06E9 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_81FC:;
    /* $81FC: 9D */ maybe_trigger_vblank(5); nes_write((0x06F1 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_81FF:;
    /* $81FF: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8200:;
    /* $8200: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_8202:;
    /* $8202: 9D */ maybe_trigger_vblank(5); nes_write((0x06F2 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_8205:;
    /* $8205: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8206:;
    /* $8206: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_8208:;
    /* $8208: 9D */ maybe_trigger_vblank(5); nes_write((0x06F3 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_820B:;
    /* $820B: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_820C:;
    /* $820C: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_820D:;
    /* $820D: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_820E:;
    /* $820E: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_820F:;
    /* $820F: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_81F9;
    }
label_8211:;
    /* $8211: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::oper_mode_execution_tree_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_8222;
    }
label_8212:; /* OperModeExecutionTree */
    /* $8212: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0770); FLAG_NZ(g_cpu.A);
label_8215:;
    /* $8215: 20 */ maybe_trigger_vblank(6); /* inline_dispatch $8E04: 4 entries (bank=0) */
switch(g_cpu.A) {
  case 0: call_by_address(0x8231); return;
  case 1: call_by_address(0xAEDC); return;
  case 2: call_by_address(0x838B); return;
  case 3: call_by_address(0x9218); return;
  default: nes_log_inline_miss(0x8215, g_cpu.A); return;
}
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

void RenderEngine::draw_mushroom_icon_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_8330;
    }
label_8325:; /* DrawMushroomIcon */
    /* $8325: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x07; FLAG_NZ(g_cpu.Y);
label_8327:; /* IconDataRead */
    /* $8327: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x831D + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_832A:;
    /* $832A: 99 */ maybe_trigger_vblank(5); nes_write((0x0300 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_832D:;
    /* $832D: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_832E:;
    /* $832E: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8327;
    }
label_8330:;
    /* $8330: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x077A); FLAG_NZ(g_cpu.A);
label_8333:;
    /* $8333: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_833F;
label_8335:;
    /* $8335: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x24; FLAG_NZ(g_cpu.A);
label_8337:;
    /* $8337: 8D */ maybe_trigger_vblank(4); nes_write(0x0304, g_cpu.A);
label_833A:;
    /* $833A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xCE; FLAG_NZ(g_cpu.A);
label_833C:;
    /* $833C: 8D */ maybe_trigger_vblank(4); nes_write(0x0306, g_cpu.A);
label_833F:; /* ExitIcon */
    /* $833F: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::player_victory_walk_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_8434;
        case 2: goto label_8436;
        case 3: goto label_842C;
        case 4: goto label_8404;
    }
label_83BD:; /* PlayerVictoryWalk */
    /* $83BD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_83BF:;
    /* $83BF: 84 */ maybe_trigger_vblank(3); nes_write(0x35, g_cpu.Y);
label_83C1:;
    /* $83C1: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x6D); FLAG_NZ(g_cpu.A);
label_83C3:;
    /* $83C3: C5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x34); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_83C5:;
    /* $83C5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_83CD;
label_83C7:;
    /* $83C7: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x86); FLAG_NZ(g_cpu.A);
label_83C9:;
    /* $83C9: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x60; g_cpu.C=(g_cpu.A>=0x60)?1:0; FLAG_NZ(r&0xFF); }
label_83CB:;
    /* $83CB: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_83D0;
label_83CD:; /* PerformWalk */
    /* $83CD: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x35; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_83CF:;
    /* $83CF: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_83D0:; /* DontWalk */
    /* $83D0: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_83D1:;
    /* $83D1: 20 */ maybe_trigger_vblank(6); call_by_address(0xB0E6);
label_83D4:;
    /* $83D4: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071A); FLAG_NZ(g_cpu.A);
label_83D7:;
    /* $83D7: C5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x34); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_83D9:;
    /* $83D9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_83F1;
label_83DB:;
    /* $83DB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0768); FLAG_NZ(g_cpu.A);
label_83DE:;
    /* $83DE: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_83DF:;
    /* $83DF: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x80 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x80); g_cpu.A=r&0xFF; }
label_83E1:;
    /* $83E1: 8D */ maybe_trigger_vblank(4); nes_write(0x0768, g_cpu.A);
label_83E4:;
    /* $83E4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_83E6:;
    /* $83E6: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_83E8:;
    /* $83E8: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_83E9:;
    /* $83E9: 20 */ maybe_trigger_vblank(6); call_by_address(0xAFC4);
label_83EC:;
    /* $83EC: 20 */ maybe_trigger_vblank(6); call_by_address(0xAF6F);
label_83EF:;
    /* $83EF: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x35; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_83F1:; /* ExitVWalk */
    /* $83F1: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x35); FLAG_NZ(g_cpu.A);
label_83F3:;
    /* $83F3: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_845D;
label_83F5:;
    /* $83F5: 60 */ maybe_trigger_vblank(6);
    return;
label_83F6:; /* PrintVictoryMessages */
    /* $83F6: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0749); FLAG_NZ(g_cpu.A);
label_83F9:;
    /* $83F9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_8443;
label_83FB:;
    /* $83FB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0719); FLAG_NZ(g_cpu.A);
label_83FE:;
    /* $83FE: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_8418;
label_8400:;
    /* $8400: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x09; g_cpu.C=(g_cpu.A>=0x09)?1:0; FLAG_NZ(r&0xFF); }
label_8402:;
    /* $8402: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_8443;
label_8404:;
    /* $8404: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x075F); FLAG_NZ(g_cpu.Y);
label_8407:;
    /* $8407: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x07; g_cpu.C=(g_cpu.Y>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_8409:;
    /* $8409: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_8414;
label_840B:;
    /* $840B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_840D:;
    /* $840D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_8443;
label_840F:;
    /* $840F: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x01; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8411:;
    /* $8411: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8418); return;
label_8414:; /* MRetainerMsg */
    /* $8414: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_8416:;
    /* $8416: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_8443;
label_8418:; /* ThankPlayer */
    /* $8418: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_8419:;
    /* $8419: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_8423;
label_841B:;
    /* $841B: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0753); FLAG_NZ(g_cpu.A);
label_841E:;
    /* $841E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_8434;
label_8420:;
    /* $8420: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8421:;
    /* $8421: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_8434;
label_8423:; /* SecondPartMsg */
    /* $8423: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8424:;
    /* $8424: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_8427:;
    /* $8427: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_8429:;
    /* $8429: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_8434;
label_842B:;
    /* $842B: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_842C:;
    /* $842C: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x04; g_cpu.C=(g_cpu.Y>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_842E:;
    /* $842E: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_8456;
label_8430:;
    /* $8430: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_8432:;
    /* $8432: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_8443;
label_8434:; /* EvalForMusic */
    /* $8434: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_8436:;
    /* $8436: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_843C;
label_8438:;
    /* $8438: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_843A:;
    /* $843A: 85 */ maybe_trigger_vblank(3); nes_write(0xFC, g_cpu.A);
label_843C:; /* PrintMsg */
    /* $843C: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_843D:;
    /* $843D: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_843E:;
    /* $843E: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x0C + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0C); g_cpu.A=r&0xFF; }
label_8440:;
    /* $8440: 8D */ maybe_trigger_vblank(4); nes_write(0x0773, g_cpu.A);
label_8443:; /* IncMsgCounter */
    /* $8443: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0749); FLAG_NZ(g_cpu.A);
label_8446:;
    /* $8446: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8447:;
    /* $8447: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_8449:;
    /* $8449: 8D */ maybe_trigger_vblank(4); nes_write(0x0749, g_cpu.A);
label_844C:;
    /* $844C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0719); FLAG_NZ(g_cpu.A);
label_844F:;
    /* $844F: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_8451:;
    /* $8451: 8D */ maybe_trigger_vblank(4); nes_write(0x0719, g_cpu.A);
label_8454:;
    /* $8454: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_8456:; /* SetEndTimer */
    /* $8456: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_8460;
label_8458:;
    /* $8458: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_845A:;
    /* $845A: 8D */ maybe_trigger_vblank(4); nes_write(0x07A1, g_cpu.A);
label_845D:; /* IncModeTask_A */
    /* $845D: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0772; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8460:; /* ExitMsgs */
    /* $8460: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::player_end_world_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_8486;
    }
label_8461:; /* PlayerEndWorld */
    /* $8461: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07A1); FLAG_NZ(g_cpu.A);
label_8464:;
    /* $8464: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_8486;
label_8466:;
    /* $8466: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x075F); FLAG_NZ(g_cpu.Y);
label_8469:;
    /* $8469: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x07; g_cpu.C=(g_cpu.Y>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_846B:;
    /* $846B: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_8487;
label_846D:;
    /* $846D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_846F:;
    /* $846F: 8D */ maybe_trigger_vblank(4); nes_write(0x0760, g_cpu.A);
label_8472:;
    /* $8472: 8D */ maybe_trigger_vblank(4); nes_write(0x075C, g_cpu.A);
label_8475:;
    /* $8475: 8D */ maybe_trigger_vblank(4); nes_write(0x0772, g_cpu.A);
label_8478:;
    /* $8478: EE */ maybe_trigger_vblank(6); { uint16_t a=0x075F; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_847B:;
    /* $847B: 20 */ maybe_trigger_vblank(6); call_by_address(0x9C03);
label_847E:;
    /* $847E: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0757; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8481:;
    /* $8481: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_8483:;
    /* $8483: 8D */ maybe_trigger_vblank(4); nes_write(0x0770, g_cpu.A);
label_8486:; /* EndExitOne */
    /* $8486: 60 */ maybe_trigger_vblank(6);
    return;
label_8487:; /* EndChkBButton */
    /* $8487: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06FC); FLAG_NZ(g_cpu.A);
label_848A:;
    /* $848A: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x06FD); FLAG_NZ(g_cpu.A);
label_848D:;
    /* $848D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_848F:;
    /* $848F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_849E;
label_8491:;
    /* $8491: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_8493:;
    /* $8493: 8D */ maybe_trigger_vblank(4); nes_write(0x07FC, g_cpu.A);
label_8496:;
    /* $8496: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_8498:;
    /* $8498: 8D */ maybe_trigger_vblank(4); nes_write(0x075A, g_cpu.A);
label_849B:;
    /* $849B: 20 */ maybe_trigger_vblank(6); call_by_address(0x9248);
label_849E:; /* EndExitTwo */
    /* $849E: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::screen_routines_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_85AD;
    }
label_8567:; /* ScreenRoutines */
    /* $8567: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x073C); FLAG_NZ(g_cpu.A);
label_856A:;
    /* $856A: 20 */ maybe_trigger_vblank(6); /* inline_dispatch $8E04: 15 entries (bank=0) */
switch(g_cpu.A) {
  case 0: call_by_address(0x858B); return;
  case 1: call_by_address(0x859B); return;
  case 2: call_by_address(0x8652); return;
  case 3: call_by_address(0x865A); return;
  case 4: call_by_address(0x8693); return;
  case 5: call_by_address(0x889D); return;
  case 6: call_by_address(0x86A8); return;
  case 7: call_by_address(0x889D); return;
  case 8: call_by_address(0x86E6); return;
  case 9: call_by_address(0x85BF); return;
  case 10: call_by_address(0x85E3); return;
  case 11: call_by_address(0x8643); return;
  case 12: call_by_address(0x86FF); return;
  case 13: call_by_address(0x8732); return;
  case 14: call_by_address(0x8749); return;
  default: nes_log_inline_miss(0x856A, g_cpu.A); return;
}
label_858B:; /* InitScreen */
    /* $858B: 20 */ maybe_trigger_vblank(6); call_by_address(0x8220);
label_858E:;
    /* $858E: 20 */ maybe_trigger_vblank(6); call_by_address(0x8E19);
label_8591:;
    /* $8591: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0770); FLAG_NZ(g_cpu.A);
label_8594:;
    /* $8594: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_85C8;
label_8596:;
    /* $8596: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_8598:;
    /* $8598: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x85C5); return;
label_859B:; /* SetupIntermediate */
    /* $859B: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0744); FLAG_NZ(g_cpu.A);
label_859E:;
    /* $859E: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_859F:;
    /* $859F: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0756); FLAG_NZ(g_cpu.A);
label_85A2:;
    /* $85A2: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_85A3:;
    /* $85A3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_85A5:;
    /* $85A5: 8D */ maybe_trigger_vblank(4); nes_write(0x0756, g_cpu.A);
label_85A8:;
    /* $85A8: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_85AA:;
    /* $85AA: 8D */ maybe_trigger_vblank(4); nes_write(0x0744, g_cpu.A);
label_85AD:;
    /* $85AD: 20 */ maybe_trigger_vblank(6); call_by_address(0x85F1);
label_85B0:;
    /* $85B0: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_85B1:;
    /* $85B1: 8D */ maybe_trigger_vblank(4); nes_write(0x0756, g_cpu.A);
label_85B4:;
    /* $85B4: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_85B5:;
    /* $85B5: 8D */ maybe_trigger_vblank(4); nes_write(0x0744, g_cpu.A);
label_85B8:;
    /* $85B8: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8745); return;
label_85BB:; /* AreaPalette */
    /* $85BB: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x02 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_85BD:;
    /* $85BD: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_85BF:; /* GetAreaPalette */
    /* $85BF: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_85C2:;
    /* $85C2: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0x85BB + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_85C5:; /* SetVRAMAddr_A */
    /* $85C5: 8E */ maybe_trigger_vblank(4); nes_write(0x0773, g_cpu.X);
label_85C8:; /* NextSubtask */
    /* $85C8: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8745); return;
}

void RenderEngine::do_nothing1_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_92AF;
    }
label_92AA:; /* DoNothing1 */
    /* $92AA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_92AC:;
    /* $92AC: 8D */ maybe_trigger_vblank(4); nes_write(0x06C9, g_cpu.A);
label_92AF:; /* DoNothing2 */
    /* $92AF: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::scroll_handler_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_AFB1;
    }
label_AF93:; /* ScrollHandler */
    /* $AF93: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06FF); FLAG_NZ(g_cpu.A);
label_AF96:;
    /* $AF96: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_AF97:;
    /* $AF97: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x03A1); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_AF9A:;
    /* $AF9A: 8D */ maybe_trigger_vblank(4); nes_write(0x06FF, g_cpu.A);
label_AF9D:;
    /* $AF9D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0723); FLAG_NZ(g_cpu.A);
label_AFA0:;
    /* $AFA0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_AFFB;
label_AFA2:;
    /* $AFA2: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0755); FLAG_NZ(g_cpu.A);
label_AFA5:;
    /* $AFA5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x50; g_cpu.C=(g_cpu.A>=0x50)?1:0; FLAG_NZ(r&0xFF); }
label_AFA7:;
    /* $AFA7: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_AFFB;
label_AFA9:;
    /* $AFA9: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0785); FLAG_NZ(g_cpu.A);
label_AFAC:;
    /* $AFAC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_AFFB;
label_AFAE:;
    /* $AFAE: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06FF); FLAG_NZ(g_cpu.Y);
label_AFB1:;
    /* $AFB1: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_AFB2:;
    /* $AFB2: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_AFFB;
label_AFB4:;
    /* $AFB4: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_AFB5:;
    /* $AFB5: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x02; g_cpu.C=(g_cpu.Y>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_AFB7:;
    /* $AFB7: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_AFBA;
label_AFB9:;
    /* $AFB9: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_AFBA:; /* ChkNearMid */
    /* $AFBA: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0755); FLAG_NZ(g_cpu.A);
label_AFBD:;
    /* $AFBD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x70; g_cpu.C=(g_cpu.A>=0x70)?1:0; FLAG_NZ(r&0xFF); }
label_AFBF:;
    /* $AFBF: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_AFC4;
label_AFC1:;
    /* $AFC1: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06FF); FLAG_NZ(g_cpu.Y);
label_AFC4:; /* ScrollScreen */
    /* $AFC4: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_AFC5:;
    /* $AFC5: 8D */ maybe_trigger_vblank(4); nes_write(0x0775, g_cpu.A);
label_AFC8:;
    /* $AFC8: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_AFC9:;
    /* $AFC9: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x073D); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_AFCC:;
    /* $AFCC: 8D */ maybe_trigger_vblank(4); nes_write(0x073D, g_cpu.A);
label_AFCF:;
    /* $AFCF: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_AFD0:;
    /* $AFD0: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_AFD1:;
    /* $AFD1: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x071C); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_AFD4:;
    /* $AFD4: 8D */ maybe_trigger_vblank(4); nes_write(0x071C, g_cpu.A);
label_AFD7:;
    /* $AFD7: 8D */ maybe_trigger_vblank(4); nes_write(0x073F, g_cpu.A);
label_AFDA:;
    /* $AFDA: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071A); FLAG_NZ(g_cpu.A);
label_AFDD:;
    /* $AFDD: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_AFDF:;
    /* $AFDF: 8D */ maybe_trigger_vblank(4); nes_write(0x071A, g_cpu.A);
label_AFE2:;
    /* $AFE2: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_AFE4:;
    /* $AFE4: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_AFE6:;
    /* $AFE6: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0778); FLAG_NZ(g_cpu.A);
label_AFE9:;
    /* $AFE9: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xFE; FLAG_NZ(g_cpu.A);
label_AFEB:;
    /* $AFEB: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x00); FLAG_NZ(g_cpu.A);
label_AFED:;
    /* $AFED: 8D */ maybe_trigger_vblank(4); nes_write(0x0778, g_cpu.A);
label_AFF0:;
    /* $AFF0: 20 */ maybe_trigger_vblank(6); call_by_address(0xB038);
label_AFF3:;
    /* $AFF3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_AFF5:;
    /* $AFF5: 8D */ maybe_trigger_vblank(4); nes_write(0x0795, g_cpu.A);
label_AFF8:;
    /* $AFF8: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xB000); return;
label_AFFB:; /* InitScrlAmt */
    /* $AFFB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_AFFD:;
    /* $AFFD: 8D */ maybe_trigger_vblank(4); nes_write(0x0775, g_cpu.A);
label_B000:; /* ChkPOffscr */
    /* $B000: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B002:;
    /* $B002: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1F6);
label_B005:;
    /* $B005: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_B007:;
    /* $B007: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_B009:;
    /* $B009: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_B00A:;
    /* $B00A: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B013;
label_B00C:;
    /* $B00C: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_B00D:;
    /* $B00D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_B00F:;
    /* $B00F: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_B011:;
    /* $B011: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B02E;
label_B013:; /* KeepOnscr */
    /* $B013: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x071C + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B016:;
    /* $B016: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_B017:;
    /* $B017: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xB034 + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_B01A:;
    /* $B01A: 85 */ maybe_trigger_vblank(3); nes_write(0x86, g_cpu.A);
label_B01C:;
    /* $B01C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x071A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B01F:;
    /* $B01F: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_B021:;
    /* $B021: 85 */ maybe_trigger_vblank(3); nes_write(0x6D, g_cpu.A);
label_B023:;
    /* $B023: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0C); FLAG_NZ(g_cpu.A);
label_B025:;
    /* $B025: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xB036 + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_B028:;
    /* $B028: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B02E;
label_B02A:;
    /* $B02A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B02C:;
    /* $B02C: 85 */ maybe_trigger_vblank(3); nes_write(0x57, g_cpu.A);
label_B02E:; /* InitPlatScrl */
    /* $B02E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B030:;
    /* $B030: 8D */ maybe_trigger_vblank(4); nes_write(0x03A1, g_cpu.A);
label_B033:;
    /* $B033: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::run_game_timer_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_B7A3;
    }
label_B74F:; /* RunGameTimer */
    /* $B74F: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0770); FLAG_NZ(g_cpu.A);
label_B752:;
    /* $B752: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B7A3;
label_B754:;
    /* $B754: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0E); FLAG_NZ(g_cpu.A);
label_B756:;
    /* $B756: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_B758:;
    /* $B758: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_B7A3;
label_B75A:;
    /* $B75A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0B; g_cpu.C=(g_cpu.A>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_B75C:;
    /* $B75C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B7A3;
label_B75E:;
    /* $B75E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xB5); FLAG_NZ(g_cpu.A);
label_B760:;
    /* $B760: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_B762:;
    /* $B762: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B7A3;
label_B764:;
    /* $B764: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0787); FLAG_NZ(g_cpu.A);
label_B767:;
    /* $B767: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B7A3;
label_B769:;
    /* $B769: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07F8); FLAG_NZ(g_cpu.A);
label_B76C:;
    /* $B76C: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x07F9); FLAG_NZ(g_cpu.A);
label_B76F:;
    /* $B76F: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x07FA); FLAG_NZ(g_cpu.A);
label_B772:;
    /* $B772: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B79A;
label_B774:;
    /* $B774: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07F8); FLAG_NZ(g_cpu.Y);
label_B777:;
    /* $B777: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_B778:;
    /* $B778: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B786;
label_B77A:;
    /* $B77A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07F9); FLAG_NZ(g_cpu.A);
label_B77D:;
    /* $B77D: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x07FA); FLAG_NZ(g_cpu.A);
label_B780:;
    /* $B780: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B786;
label_B782:;
    /* $B782: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_B784:;
    /* $B784: 85 */ maybe_trigger_vblank(3); nes_write(0xFC, g_cpu.A);
label_B786:; /* ResGTCtrl */
    /* $B786: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_B788:;
    /* $B788: 8D */ maybe_trigger_vblank(4); nes_write(0x0787, g_cpu.A);
label_B78B:;
    /* $B78B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x23; FLAG_NZ(g_cpu.Y);
label_B78D:;
    /* $B78D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_B78F:;
    /* $B78F: 8D */ maybe_trigger_vblank(4); nes_write(0x0139, g_cpu.A);
label_B792:;
    /* $B792: 20 */ maybe_trigger_vblank(6); call_by_address(0x8F5F);
label_B795:;
    /* $B795: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA4; FLAG_NZ(g_cpu.A);
label_B797:;
    /* $B797: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8F06); return;
label_B79A:; /* TimeUpOn */
    /* $B79A: 8D */ maybe_trigger_vblank(4); nes_write(0x0756, g_cpu.A);
label_B79D:;
    /* $B79D: 20 */ maybe_trigger_vblank(6); call_by_address(0xD931);
label_B7A0:;
    /* $B7A0: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0759; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B7A3:; /* ExGTimer */
    /* $B7A3: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::move_d_enemy_vertically_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_BF6B;
    }
label_BF63:; /* MoveD_EnemyVertically */
    /* $BF63: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x3D; FLAG_NZ(g_cpu.Y);
label_BF65:;
    /* $BF65: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_BF67:;
    /* $BF67: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_BF69:;
    /* $BF69: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_BF6D;
label_BF6B:; /* MoveFallingPlatform */
    /* $BF6B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x20; FLAG_NZ(g_cpu.Y);
label_BF6D:; /* ContVMove */
    /* $BF6D: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF94); return;
}

void RenderEngine::enemy_gfx_handler_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_E9A0;
        case 2: goto label_E939;
        case 3: goto label_E9B2;
        case 4: goto label_E96D;
        case 5: goto label_E900;
        case 6: goto label_E998;
        case 7: goto label_EB20;
        case 8: goto label_E96F;
        case 9: goto label_E987;
        case 10: goto label_E9B6;
        case 11: goto label_E9D6;
        case 12: goto label_E908;
        case 13: goto label_EB86;
        case 14: goto label_E921;
        case 15: goto label_EBA4;
        case 16: goto label_EB84;
        case 17: goto label_EBA6;
        case 18: goto label_EAAD;
        case 19: goto label_EAE7;
        case 20: goto label_E9EB;
        case 21: goto label_EA3D;
        case 22: goto label_EABA;
        case 23: goto label_E9D0;
        case 24: goto label_E9E0;
        case 25: goto label_E919;
        case 26: goto label_EA20;
        case 27: goto label_E94C;
        case 28: goto label_E960;
        case 29: goto label_E9A4;
        case 30: goto label_EAD0;
        case 31: goto label_EA85;
        case 32: goto label_E928;
        case 33: goto label_EB80;
        case 34: goto label_EA32;
        case 35: goto label_E962;
        case 36: goto label_EA61;
        case 37: goto label_E953;
        case 38: goto label_E9B0;
        case 39: goto label_E9D4;
        case 40: goto label_EB79;
        case 41: goto label_E902;
        case 42: goto label_E949;
        case 43: goto label_EAE1;
    }
label_E87D:; /* EnemyGfxHandler */
    /* $E87D: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E87F:;
    /* $E87F: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_E881:;
    /* $E881: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_E884:;
    /* $E884: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_E886:;
    /* $E886: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E889:;
    /* $E889: 84 */ maybe_trigger_vblank(3); nes_write(0xEB, g_cpu.Y);
label_E88B:;
    /* $E88B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E88D:;
    /* $E88D: 8D */ maybe_trigger_vblank(4); nes_write(0x0109, g_cpu.A);
label_E890:;
    /* $E890: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E892:;
    /* $E892: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_E894:;
    /* $E894: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03C5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E897:;
    /* $E897: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_E899:;
    /* $E899: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E89B:;
    /* $E89B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_E89D:;
    /* $E89D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E8A9;
label_E89F:;
    /* $E89F: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_E8A1:;
    /* $E8A1: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_E8A9;
label_E8A3:;
    /* $E8A3: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x078A + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E8A6:;
    /* $E8A6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E8A9;
label_E8A8:;
    /* $E8A8: 60 */ maybe_trigger_vblank(6);
    return;
label_E8A9:; /* CheckForRetainerObj */
    /* $E8A9: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E8AB:;
    /* $E8AB: 85 */ maybe_trigger_vblank(3); nes_write(0xED, g_cpu.A);
label_E8AD:;
    /* $E8AD: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x1F; FLAG_NZ(g_cpu.A);
label_E8AF:;
    /* $E8AF: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_E8B0:;
    /* $E8B0: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E8B2:;
    /* $E8B2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x35; g_cpu.C=(g_cpu.A>=0x35)?1:0; FLAG_NZ(r&0xFF); }
label_E8B4:;
    /* $E8B4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E8BE;
label_E8B6:;
    /* $E8B6: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_E8B8:;
    /* $E8B8: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E8BA:;
    /* $E8BA: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_E8BC:;
    /* $E8BC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x15; FLAG_NZ(g_cpu.A);
label_E8BE:; /* CheckForBulletBillCV */
    /* $E8BE: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x33; g_cpu.C=(g_cpu.A>=0x33)?1:0; FLAG_NZ(r&0xFF); }
label_E8C0:;
    /* $E8C0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E8D5;
label_E8C2:;
    /* $E8C2: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x02; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E8C4:;
    /* $E8C4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_E8C6:;
    /* $E8C6: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x078A + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E8C9:;
    /* $E8C9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E8CD;
label_E8CB:;
    /* $E8CB: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x20; FLAG_NZ(g_cpu.A);
label_E8CD:; /* SBBAt */
    /* $E8CD: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_E8CF:;
    /* $E8CF: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_E8D1:;
    /* $E8D1: 84 */ maybe_trigger_vblank(3); nes_write(0xED, g_cpu.Y);
label_E8D3:;
    /* $E8D3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_E8D5:; /* CheckForJumpspring */
    /* $E8D5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x32; g_cpu.C=(g_cpu.A>=0x32)?1:0; FLAG_NZ(r&0xFF); }
label_E8D7:;
    /* $E8D7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E8E1;
label_E8D9:;
    /* $E8D9: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x03; FLAG_NZ(g_cpu.Y);
label_E8DB:;
    /* $E8DB: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x070E); FLAG_NZ(g_cpu.X);
label_E8DE:;
    /* $E8DE: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE878 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E8E1:; /* CheckForPodoboo */
    /* $E8E1: 85 */ maybe_trigger_vblank(3); nes_write(0xEF, g_cpu.A);
label_E8E3:;
    /* $E8E3: 84 */ maybe_trigger_vblank(3); nes_write(0xEC, g_cpu.Y);
label_E8E5:;
    /* $E8E5: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E8E7:;
    /* $E8E7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0C; g_cpu.C=(g_cpu.A>=0x0C)?1:0; FLAG_NZ(r&0xFF); }
label_E8E9:;
    /* $E8E9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E8F2;
label_E8EB:;
    /* $E8EB: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E8ED:;
    /* $E8ED: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_E8F2;
label_E8EF:;
    /* $E8EF: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0109; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E8F2:; /* CheckBowserGfxFlag */
    /* $E8F2: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x036A); FLAG_NZ(g_cpu.A);
label_E8F5:;
    /* $E8F5: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E900;
label_E8F7:;
    /* $E8F7: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x16; FLAG_NZ(g_cpu.Y);
label_E8F9:;
    /* $E8F9: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_E8FB:;
    /* $E8FB: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E8FE;
label_E8FD:;
    /* $E8FD: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E8FE:; /* SBwsrGfxOfs */
    /* $E8FE: 84 */ maybe_trigger_vblank(3); nes_write(0xEF, g_cpu.Y);
label_E900:; /* CheckForGoomba */
    /* $E900: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xEF); FLAG_NZ(g_cpu.Y);
label_E902:;
    /* $E902: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_E904:;
    /* $E904: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E923;
label_E906:;
    /* $E906: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E908:;
    /* $E908: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_E90A:;
    /* $E90A: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E910;
label_E90C:;
    /* $E90C: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x04; FLAG_NZ(g_cpu.X);
label_E90E:;
    /* $E90E: 86 */ maybe_trigger_vblank(3); nes_write(0xEC, g_cpu.X);
label_E910:; /* GmbaAnim */
    /* $E910: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_E912:;
    /* $E912: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_E915:;
    /* $E915: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E923;
label_E917:;
    /* $E917: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_E919:;
    /* $E919: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_E91B:;
    /* $E91B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E923;
label_E91D:;
    /* $E91D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x03); FLAG_NZ(g_cpu.A);
label_E91F:;
    /* $E91F: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x03; FLAG_NZ(g_cpu.A);
label_E921:;
    /* $E921: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_E923:; /* CheckBowserFront */
    /* $E923: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE85B + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E926:;
    /* $E926: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x04); FLAG_NZ(g_cpu.A);
label_E928:;
    /* $E928: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_E92A:;
    /* $E92A: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE840 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E92D:;
    /* $E92D: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E92E:;
    /* $E92E: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xEC); FLAG_NZ(g_cpu.Y);
label_E930:;
    /* $E930: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x036A); FLAG_NZ(g_cpu.A);
label_E933:;
    /* $E933: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E965;
label_E935:;
    /* $E935: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_E937:;
    /* $E937: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E94C;
label_E939:;
    /* $E939: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0363); FLAG_NZ(g_cpu.A);
label_E93C:;
    /* $E93C: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_E940;
label_E93E:;
    /* $E93E: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xDE; FLAG_NZ(g_cpu.X);
label_E940:; /* ChkFrontSte */
    /* $E940: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xED); FLAG_NZ(g_cpu.A);
label_E942:;
    /* $E942: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_E944:;
    /* $E944: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E949;
label_E946:; /* FlipBowserOver */
    /* $E946: 8E */ maybe_trigger_vblank(4); nes_write(0x0109, g_cpu.X);
label_E949:; /* DrawBowser */
    /* $E949: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xEA4B); return;
label_E94C:; /* CheckBowserRear */
    /* $E94C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0363); FLAG_NZ(g_cpu.A);
label_E94F:;
    /* $E94F: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_E951:;
    /* $E951: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E955;
label_E953:;
    /* $E953: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xE4; FLAG_NZ(g_cpu.X);
label_E955:; /* ChkRearSte */
    /* $E955: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xED); FLAG_NZ(g_cpu.A);
label_E957:;
    /* $E957: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_E959:;
    /* $E959: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E949;
    }
label_E95B:;
    /* $E95B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_E95D:;
    /* $E95D: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_E95E:;
    /* $E95E: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x10; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E960:;
    /* $E960: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_E962:;
    /* $E962: 4C */ maybe_trigger_vblank(3); goto label_E946;
label_E965:; /* CheckForSpiny */
    /* $E965: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x24; g_cpu.C=(g_cpu.X>=0x24)?1:0; FLAG_NZ(r&0xFF); }
label_E967:;
    /* $E967: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E97A;
label_E969:;
    /* $E969: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x05; g_cpu.C=(g_cpu.Y>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E96B:;
    /* $E96B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E977;
label_E96D:;
    /* $E96D: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x30; FLAG_NZ(g_cpu.X);
label_E96F:;
    /* $E96F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E971:;
    /* $E971: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_E973:;
    /* $E973: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_E975:;
    /* $E975: 85 */ maybe_trigger_vblank(3); nes_write(0xEC, g_cpu.A);
label_E977:; /* NotEgg */
    /* $E977: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE9CA); return;
label_E97A:; /* CheckForLakitu */
    /* $E97A: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x90; g_cpu.C=(g_cpu.X>=0x90)?1:0; FLAG_NZ(r&0xFF); }
label_E97C:;
    /* $E97C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E990;
label_E97E:;
    /* $E97E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xED); FLAG_NZ(g_cpu.A);
label_E980:;
    /* $E980: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_E982:;
    /* $E982: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E98D;
label_E984:;
    /* $E984: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x078F); FLAG_NZ(g_cpu.A);
label_E987:;
    /* $E987: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x10; g_cpu.C=(g_cpu.A>=0x10)?1:0; FLAG_NZ(r&0xFF); }
label_E989:;
    /* $E989: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E98D;
label_E98B:;
    /* $E98B: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x96; FLAG_NZ(g_cpu.X);
label_E98D:; /* NoLAFr */
    /* $E98D: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xEA37); return;
label_E990:; /* CheckUpsideDownShell */
    /* $E990: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xEF); FLAG_NZ(g_cpu.A);
label_E992:;
    /* $E992: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_E994:;
    /* $E994: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E9A6;
label_E996:;
    /* $E996: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x02; g_cpu.C=(g_cpu.Y>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_E998:;
    /* $E998: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E9A6;
label_E99A:;
    /* $E99A: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x5A; FLAG_NZ(g_cpu.X);
label_E99C:;
    /* $E99C: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xEF); FLAG_NZ(g_cpu.Y);
label_E99E:;
    /* $E99E: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x02; g_cpu.C=(g_cpu.Y>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_E9A0:;
    /* $E9A0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E9A6;
label_E9A2:;
    /* $E9A2: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x7E; FLAG_NZ(g_cpu.X);
label_E9A4:;
    /* $E9A4: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x02; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E9A6:; /* CheckRightSideUpShell */
    /* $E9A6: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xEC); FLAG_NZ(g_cpu.A);
label_E9A8:;
    /* $E9A8: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_E9AA:;
    /* $E9AA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E9CA;
label_E9AC:;
    /* $E9AC: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x72; FLAG_NZ(g_cpu.X);
label_E9AE:;
    /* $E9AE: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x02; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E9B0:;
    /* $E9B0: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xEF); FLAG_NZ(g_cpu.Y);
label_E9B2:;
    /* $E9B2: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x02; g_cpu.C=(g_cpu.Y>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_E9B4:;
    /* $E9B4: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E9BA;
label_E9B6:;
    /* $E9B6: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x66; FLAG_NZ(g_cpu.X);
label_E9B8:;
    /* $E9B8: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x02; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E9BA:; /* CheckForDefdGoomba */
    /* $E9BA: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_E9BC:;
    /* $E9BC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E9CA;
label_E9BE:;
    /* $E9BE: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x54; FLAG_NZ(g_cpu.X);
label_E9C0:;
    /* $E9C0: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xED); FLAG_NZ(g_cpu.A);
label_E9C2:;
    /* $E9C2: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_E9C4:;
    /* $E9C4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E9CA;
label_E9C6:;
    /* $E9C6: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x8A; FLAG_NZ(g_cpu.X);
label_E9C8:;
    /* $E9C8: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x02; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E9CA:; /* CheckForHammerBro */
    /* $E9CA: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x08); FLAG_NZ(g_cpu.Y);
label_E9CC:;
    /* $E9CC: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xEF); FLAG_NZ(g_cpu.A);
label_E9CE:;
    /* $E9CE: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E9D0:;
    /* $E9D0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E9DE;
label_E9D2:;
    /* $E9D2: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xED); FLAG_NZ(g_cpu.A);
label_E9D4:;
    /* $E9D4: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E9FA;
label_E9D6:;
    /* $E9D6: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_E9D8:;
    /* $E9D8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EA37;
label_E9DA:;
    /* $E9DA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xB4; FLAG_NZ(g_cpu.X);
label_E9DC:;
    /* $E9DC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E9FA;
label_E9DE:; /* CheckForBloober */
    /* $E9DE: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x48; g_cpu.C=(g_cpu.X>=0x48)?1:0; FLAG_NZ(r&0xFF); }
label_E9E0:;
    /* $E9E0: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E9FA;
label_E9E2:;
    /* $E9E2: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0796 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E9E5:;
    /* $E9E5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E9E7:;
    /* $E9E7: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_EA37;
label_E9E9:;
    /* $E9E9: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x3C; g_cpu.C=(g_cpu.X>=0x3C)?1:0; FLAG_NZ(r&0xFF); }
label_E9EB:;
    /* $E9EB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E9FA;
label_E9ED:;
    /* $E9ED: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_E9EF:;
    /* $E9EF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EA37;
label_E9F1:;
    /* $E9F1: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x02; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E9F3:;
    /* $E9F3: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x02; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E9F5:;
    /* $E9F5: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x02; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E9F7:;
    /* $E9F7: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xEA29); return;
label_E9FA:; /* CheckToAnimateEnemy */
    /* $E9FA: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xEF); FLAG_NZ(g_cpu.A);
label_E9FC:;
    /* $E9FC: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_E9FE:;
    /* $E9FE: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EA37;
label_EA00:;
    /* $EA00: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_EA02:;
    /* $EA02: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EA37;
label_EA04:;
    /* $EA04: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0C; g_cpu.C=(g_cpu.A>=0x0C)?1:0; FLAG_NZ(r&0xFF); }
label_EA06:;
    /* $EA06: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EA37;
label_EA08:;
    /* $EA08: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x18; g_cpu.C=(g_cpu.A>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_EA0A:;
    /* $EA0A: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_EA37;
label_EA0C:;
    /* $EA0C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_EA0E:;
    /* $EA0E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_EA10:;
    /* $EA10: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EA22;
label_EA12:;
    /* $EA12: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EA13:;
    /* $EA13: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_EA16:;
    /* $EA16: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_EA18:;
    /* $EA18: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_EA37;
label_EA1A:;
    /* $EA1A: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xA2; FLAG_NZ(g_cpu.X);
label_EA1C:;
    /* $EA1C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_EA1E:;
    /* $EA1E: 85 */ maybe_trigger_vblank(3); nes_write(0xEC, g_cpu.A);
label_EA20:;
    /* $EA20: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EA37;
label_EA22:; /* CheckForSecondFrame */
    /* $EA22: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_EA24:;
    /* $EA24: 39 */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xE876 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EA27:;
    /* $EA27: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EA37;
label_EA29:; /* CheckAnimationStop */
    /* $EA29: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xED); FLAG_NZ(g_cpu.A);
label_EA2B:;
    /* $EA2B: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xA0; FLAG_NZ(g_cpu.A);
label_EA2D:;
    /* $EA2D: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_EA30:;
    /* $EA30: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EA37;
label_EA32:;
    /* $EA32: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_EA33:;
    /* $EA33: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_EA34:;
    /* $EA34: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x06 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x06); g_cpu.A=r&0xFF; }
label_EA36:;
    /* $EA36: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_EA37:; /* CheckDefeatedState */
    /* $EA37: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xED); FLAG_NZ(g_cpu.A);
label_EA39:;
    /* $EA39: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_EA3B:;
    /* $EA3B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EA4B;
label_EA3D:;
    /* $EA3D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xEF); FLAG_NZ(g_cpu.A);
label_EA3F:;
    /* $EA3F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_EA41:;
    /* $EA41: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_EA4B;
label_EA43:;
    /* $EA43: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_EA45:;
    /* $EA45: 8C */ maybe_trigger_vblank(4); nes_write(0x0109, g_cpu.Y);
label_EA48:;
    /* $EA48: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EA49:;
    /* $EA49: 84 */ maybe_trigger_vblank(3); nes_write(0xEC, g_cpu.Y);
label_EA4B:; /* DrawEnemyObject */
    /* $EA4B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xEB); FLAG_NZ(g_cpu.Y);
label_EA4D:;
    /* $EA4D: 20 */ maybe_trigger_vblank(6); call_by_address(0xEBAA);
label_EA50:;
    /* $EA50: 20 */ maybe_trigger_vblank(6); call_by_address(0xEBAA);
label_EA53:;
    /* $EA53: 20 */ maybe_trigger_vblank(6); call_by_address(0xEBAA);
label_EA56:;
    /* $EA56: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_EA58:;
    /* $EA58: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_EA5B:;
    /* $EA5B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xEF); FLAG_NZ(g_cpu.A);
label_EA5D:;
    /* $EA5D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_EA5F:;
    /* $EA5F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EA64;
label_EA61:; /* SkipToOffScrChk */
    /* $EA61: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xEB64); return;
label_EA64:; /* CheckForVerticalFlip */
    /* $EA64: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0109); FLAG_NZ(g_cpu.A);
label_EA67:;
    /* $EA67: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EAA6;
label_EA69:;
    /* $EA69: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0202 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EA6C:;
    /* $EA6C: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x80; FLAG_NZ(g_cpu.A);
label_EA6E:;
    /* $EA6E: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EA6F:;
    /* $EA6F: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EA70:;
    /* $EA70: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5B5);
label_EA73:;
    /* $EA73: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EA74:;
    /* $EA74: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EA75:;
    /* $EA75: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_EA76:;
    /* $EA76: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_EA77:;
    /* $EA77: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xEF); FLAG_NZ(g_cpu.A);
label_EA79:;
    /* $EA79: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_EA7B:;
    /* $EA7B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EA8A;
label_EA7D:;
    /* $EA7D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_EA7F:;
    /* $EA7F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EA8A;
label_EA81:;
    /* $EA81: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_EA83:;
    /* $EA83: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_EA8A;
label_EA85:;
    /* $EA85: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_EA86:;
    /* $EA86: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_EA87:;
    /* $EA87: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_EA89:;
    /* $EA89: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_EA8A:; /* FlipEnemyVertically */
    /* $EA8A: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0201 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EA8D:;
    /* $EA8D: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_EA8E:;
    /* $EA8E: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0205 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EA91:;
    /* $EA91: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_EA92:;
    /* $EA92: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0211 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EA95:;
    /* $EA95: 9D */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_EA98:;
    /* $EA98: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0215 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EA9B:;
    /* $EA9B: 9D */ maybe_trigger_vblank(5); nes_write((0x0205 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_EA9E:;
    /* $EA9E: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_EA9F:;
    /* $EA9F: 99 */ maybe_trigger_vblank(5); nes_write((0x0215 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EAA2:;
    /* $EAA2: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_EAA3:;
    /* $EAA3: 99 */ maybe_trigger_vblank(5); nes_write((0x0211 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EAA6:; /* CheckForESymmetry */
    /* $EAA6: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x036A); FLAG_NZ(g_cpu.A);
label_EAA9:;
    /* $EAA9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_EA61;
    }
label_EAAB:;
    /* $EAAB: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xEF); FLAG_NZ(g_cpu.A);
label_EAAD:;
    /* $EAAD: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0xEC); FLAG_NZ(g_cpu.X);
label_EAAF:;
    /* $EAAF: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_EAB1:;
    /* $EAB1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EAB6;
label_EAB3:;
    /* $EAB3: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xEB64); return;
label_EAB6:; /* ContES */
    /* $EAB6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_EAB8:;
    /* $EAB8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EAD7;
label_EABA:;
    /* $EABA: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_EABC:;
    /* $EABC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EAD7;
label_EABE:;
    /* $EABE: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0C; g_cpu.C=(g_cpu.A>=0x0C)?1:0; FLAG_NZ(r&0xFF); }
label_EAC0:;
    /* $EAC0: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EAD7;
label_EAC2:;
    /* $EAC2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x12; g_cpu.C=(g_cpu.A>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_EAC4:;
    /* $EAC4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EACA;
label_EAC6:;
    /* $EAC6: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x05; g_cpu.C=(g_cpu.X>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_EAC8:;
    /* $EAC8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EB12;
label_EACA:; /* ESRtnr */
    /* $EACA: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_EACC:;
    /* $EACC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EAD3;
label_EACE:;
    /* $EACE: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x42; FLAG_NZ(g_cpu.A);
label_EAD0:;
    /* $EAD0: 99 */ maybe_trigger_vblank(5); nes_write((0x0216 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EAD3:; /* SpnySC */
    /* $EAD3: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x02; g_cpu.C=(g_cpu.X>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_EAD5:;
    /* $EAD5: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_EB12;
label_EAD7:; /* MirrorEnemyGfx */
    /* $EAD7: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x036A); FLAG_NZ(g_cpu.A);
label_EADA:;
    /* $EADA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EB12;
label_EADC:;
    /* $EADC: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0202 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EADF:;
    /* $EADF: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xA3; FLAG_NZ(g_cpu.A);
label_EAE1:;
    /* $EAE1: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EAE4:;
    /* $EAE4: 99 */ maybe_trigger_vblank(5); nes_write((0x020A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EAE7:;
    /* $EAE7: 99 */ maybe_trigger_vblank(5); nes_write((0x0212 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EAEA:;
    /* $EAEA: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_EAEC:;
    /* $EAEC: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x05; g_cpu.C=(g_cpu.X>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_EAEE:;
    /* $EAEE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EAF2;
label_EAF0:;
    /* $EAF0: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x80; FLAG_NZ(g_cpu.A);
label_EAF2:; /* EggExc */
    /* $EAF2: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EAF5:;
    /* $EAF5: 99 */ maybe_trigger_vblank(5); nes_write((0x020E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EAF8:;
    /* $EAF8: 99 */ maybe_trigger_vblank(5); nes_write((0x0216 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EAFB:;
    /* $EAFB: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x04; g_cpu.C=(g_cpu.X>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_EAFD:;
    /* $EAFD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EB12;
label_EAFF:;
    /* $EAFF: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x020A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EB02:;
    /* $EB02: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x80; FLAG_NZ(g_cpu.A);
label_EB04:;
    /* $EB04: 99 */ maybe_trigger_vblank(5); nes_write((0x020A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EB07:;
    /* $EB07: 99 */ maybe_trigger_vblank(5); nes_write((0x0212 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EB0A:;
    /* $EB0A: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_EB0C:;
    /* $EB0C: 99 */ maybe_trigger_vblank(5); nes_write((0x020E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EB0F:;
    /* $EB0F: 99 */ maybe_trigger_vblank(5); nes_write((0x0216 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EB12:; /* CheckToMirrorLakitu */
    /* $EB12: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xEF); FLAG_NZ(g_cpu.A);
label_EB14:;
    /* $EB14: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_EB16:;
    /* $EB16: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EB4E;
label_EB18:;
    /* $EB18: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0109); FLAG_NZ(g_cpu.A);
label_EB1B:;
    /* $EB1B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EB3E;
label_EB1D:;
    /* $EB1D: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0212 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EB20:;
    /* $EB20: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x81; FLAG_NZ(g_cpu.A);
label_EB22:;
    /* $EB22: 99 */ maybe_trigger_vblank(5); nes_write((0x0212 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EB25:;
    /* $EB25: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0216 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EB28:;
    /* $EB28: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x41; FLAG_NZ(g_cpu.A);
label_EB2A:;
    /* $EB2A: 99 */ maybe_trigger_vblank(5); nes_write((0x0216 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EB2D:;
    /* $EB2D: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x078F); FLAG_NZ(g_cpu.X);
label_EB30:;
    /* $EB30: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x10; g_cpu.C=(g_cpu.X>=0x10)?1:0; FLAG_NZ(r&0xFF); }
label_EB32:;
    /* $EB32: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_EB64;
label_EB34:;
    /* $EB34: 99 */ maybe_trigger_vblank(5); nes_write((0x020E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EB37:;
    /* $EB37: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x81; FLAG_NZ(g_cpu.A);
label_EB39:;
    /* $EB39: 99 */ maybe_trigger_vblank(5); nes_write((0x020A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EB3C:;
    /* $EB3C: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_EB64;
label_EB3E:; /* NVFLak */
    /* $EB3E: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0202 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EB41:;
    /* $EB41: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x81; FLAG_NZ(g_cpu.A);
label_EB43:;
    /* $EB43: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EB46:;
    /* $EB46: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0206 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EB49:;
    /* $EB49: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x41; FLAG_NZ(g_cpu.A);
label_EB4B:;
    /* $EB4B: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EB4E:; /* CheckToMirrorJSpring */
    /* $EB4E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xEF); FLAG_NZ(g_cpu.A);
label_EB50:;
    /* $EB50: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x18; g_cpu.C=(g_cpu.A>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_EB52:;
    /* $EB52: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_EB64;
label_EB54:;
    /* $EB54: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x82; FLAG_NZ(g_cpu.A);
label_EB56:;
    /* $EB56: 99 */ maybe_trigger_vblank(5); nes_write((0x020A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EB59:;
    /* $EB59: 99 */ maybe_trigger_vblank(5); nes_write((0x0212 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EB5C:;
    /* $EB5C: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_EB5E:;
    /* $EB5E: 99 */ maybe_trigger_vblank(5); nes_write((0x020E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EB61:;
    /* $EB61: 99 */ maybe_trigger_vblank(5); nes_write((0x0216 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EB64:; /* SprObjectOffscrChk */
    /* $EB64: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_EB66:;
    /* $EB66: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D1); FLAG_NZ(g_cpu.A);
label_EB69:;
    /* $EB69: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EB6A:;
    /* $EB6A: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EB6B:;
    /* $EB6B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EB6C:;
    /* $EB6C: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_EB6D:;
    /* $EB6D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_EB74;
label_EB6F:;
    /* $EB6F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_EB71:;
    /* $EB71: 20 */ maybe_trigger_vblank(6); call_by_address(0xEBC1);
label_EB74:; /* LcChk */
    /* $EB74: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_EB75:;
    /* $EB75: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EB76:;
    /* $EB76: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_EB77:;
    /* $EB77: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_EB7E;
label_EB79:;
    /* $EB79: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_EB7B:;
    /* $EB7B: 20 */ maybe_trigger_vblank(6); call_by_address(0xEBC1);
label_EB7E:; /* Row3C */
    /* $EB7E: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_EB7F:;
    /* $EB7F: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EB80:;
    /* $EB80: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EB81:;
    /* $EB81: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_EB82:;
    /* $EB82: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_EB89;
label_EB84:;
    /* $EB84: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_EB86:;
    /* $EB86: 20 */ maybe_trigger_vblank(6); call_by_address(0xEBB7);
label_EB89:; /* Row23C */
    /* $EB89: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_EB8A:;
    /* $EB8A: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EB8B:;
    /* $EB8B: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_EB8C:;
    /* $EB8C: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_EB93;
label_EB8E:;
    /* $EB8E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_EB90:;
    /* $EB90: 20 */ maybe_trigger_vblank(6); call_by_address(0xEBB7);
label_EB93:; /* AllRowC */
    /* $EB93: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_EB94:;
    /* $EB94: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EB95:;
    /* $EB95: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_EBA9;
label_EB97:;
    /* $EB97: 20 */ maybe_trigger_vblank(6); call_by_address(0xEBB7);
label_EB9A:;
    /* $EB9A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_EB9C:;
    /* $EB9C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0C; g_cpu.C=(g_cpu.A>=0x0C)?1:0; FLAG_NZ(r&0xFF); }
label_EB9E:;
    /* $EB9E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EBA9;
label_EBA0:;
    /* $EBA0: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xB6 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_EBA2:;
    /* $EBA2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_EBA4:;
    /* $EBA4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EBA9;
label_EBA6:;
    /* $EBA6: 20 */ maybe_trigger_vblank(6); call_by_address(0xC998);
label_EBA9:; /* ExEGHandler */
    /* $EBA9: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::move_e_spr_row_offscreen_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_EBB8;
        case 2: goto label_EBBC;
    }
label_EBB7:; /* MoveESprRowOffscreen */
    /* $EBB7: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_EBB8:;
    /* $EBB8: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x06E5 + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_EBBB:;
    /* $EBBB: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_EBBC:;
    /* $EBBC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_EBBE:;
    /* $EBBE: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE5C1); return;
}

void RenderEngine::move_e_spr_col_offscreen_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_EBC6;
        case 2: goto label_EBC2;
    }
label_EBC1:; /* MoveESprColOffscreen */
    /* $EBC1: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_EBC2:;
    /* $EBC2: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x06E5 + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_EBC5:;
    /* $EBC5: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_EBC6:;
    /* $EBC6: 20 */ maybe_trigger_vblank(6); call_by_address(0xEC4A);
label_EBC9:;
    /* $EBC9: 99 */ maybe_trigger_vblank(5); nes_write((0x0210 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EBCC:;
    /* $EBCC: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::draw_block_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_EC20;
        case 2: goto label_EC21;
        case 3: goto label_EBE7;
        case 4: goto label_EBEC;
        case 5: goto label_EC23;
        case 6: goto label_EBEA;
        case 7: goto label_EC35;
        case 8: goto label_EC00;
    }
label_EBD1:; /* DrawBlock */
    /* $EBD1: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03BC); FLAG_NZ(g_cpu.A);
label_EBD4:;
    /* $EBD4: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_EBD6:;
    /* $EBD6: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B1); FLAG_NZ(g_cpu.A);
label_EBD9:;
    /* $EBD9: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_EBDB:;
    /* $EBDB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_EBDD:;
    /* $EBDD: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_EBDF:;
    /* $EBDF: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EBE0:;
    /* $EBE0: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_EBE2:;
    /* $EBE2: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06EC + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_EBE5:;
    /* $EBE5: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_EBE7:; /* DBlkLoop */
    /* $EBE7: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xEBCD + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EBEA:;
    /* $EBEA: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_EBEC:;
    /* $EBEC: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xEBCE + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EBEF:;
    /* $EBEF: 20 */ maybe_trigger_vblank(6); call_by_address(0xEBB2);
label_EBF2:;
    /* $EBF2: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x04; g_cpu.C=(g_cpu.X>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_EBF4:;
    /* $EBF4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_EBE7;
    }
label_EBF6:;
    /* $EBF6: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_EBF8:;
    /* $EBF8: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06EC + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_EBFB:;
    /* $EBFB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x074E); FLAG_NZ(g_cpu.A);
label_EBFE:;
    /* $EBFE: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_EC00:;
    /* $EC00: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EC0A;
label_EC02:;
    /* $EC02: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x86; FLAG_NZ(g_cpu.A);
label_EC04:;
    /* $EC04: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EC07:;
    /* $EC07: 99 */ maybe_trigger_vblank(5); nes_write((0x0205 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EC0A:; /* ChkRep */
    /* $EC0A: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03E8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EC0D:;
    /* $EC0D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xC4; g_cpu.C=(g_cpu.A>=0xC4)?1:0; FLAG_NZ(r&0xFF); }
label_EC0F:;
    /* $EC0F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EC35;
label_EC11:;
    /* $EC11: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x87; FLAG_NZ(g_cpu.A);
label_EC13:;
    /* $EC13: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EC14:;
    /* $EC14: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5BB);
label_EC17:;
    /* $EC17: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EC18:;
    /* $EC18: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_EC1A:;
    /* $EC1A: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x074E); FLAG_NZ(g_cpu.X);
label_EC1D:;
    /* $EC1D: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_EC1E:;
    /* $EC1E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EC21;
label_EC20:;
    /* $EC20: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_EC21:; /* SetBFlip */
    /* $EC21: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_EC23:;
    /* $EC23: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EC26:;
    /* $EC26: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_EC28:;
    /* $EC28: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EC2B:;
    /* $EC2B: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x80; FLAG_NZ(g_cpu.A);
label_EC2D:;
    /* $EC2D: 99 */ maybe_trigger_vblank(5); nes_write((0x020E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EC30:;
    /* $EC30: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x83; FLAG_NZ(g_cpu.A);
label_EC32:;
    /* $EC32: 99 */ maybe_trigger_vblank(5); nes_write((0x020A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EC35:; /* BlkOffscr */
    /* $EC35: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D4); FLAG_NZ(g_cpu.A);
label_EC38:;
    /* $EC38: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_EC39:;
    /* $EC39: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x04; FLAG_NZ(g_cpu.A);
label_EC3B:;
    /* $EC3B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EC45;
label_EC3D:;
    /* $EC3D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_EC3F:;
    /* $EC3F: 99 */ maybe_trigger_vblank(5); nes_write((0x0204 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EC42:;
    /* $EC42: 99 */ maybe_trigger_vblank(5); nes_write((0x020C + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EC45:; /* PullOfsB */
    /* $EC45: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_EC46:; /* ChkLeftCo */
    /* $EC46: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_EC48:;
    /* $EC48: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EC52;
label_EC4A:; /* MoveColOffscreen */
    /* $EC4A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_EC4C:;
    /* $EC4C: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EC4F:;
    /* $EC4F: 99 */ maybe_trigger_vblank(5); nes_write((0x0208 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EC52:; /* ExDBlk */
    /* $EC52: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::draw_brick_chunks_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_EC91;
        case 2: goto label_EC85;
        case 3: goto label_ECA5;
        case 4: goto label_EC65;
    }
label_EC53:; /* DrawBrickChunks */
    /* $EC53: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_EC55:;
    /* $EC55: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_EC57:;
    /* $EC57: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x75; FLAG_NZ(g_cpu.A);
label_EC59:;
    /* $EC59: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x0E); FLAG_NZ(g_cpu.Y);
label_EC5B:;
    /* $EC5B: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x05; g_cpu.C=(g_cpu.Y>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_EC5D:;
    /* $EC5D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EC65;
label_EC5F:;
    /* $EC5F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_EC61:;
    /* $EC61: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_EC63:;
    /* $EC63: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x84; FLAG_NZ(g_cpu.A);
label_EC65:; /* DChunks */
    /* $EC65: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06EC + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_EC68:;
    /* $EC68: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EC69:;
    /* $EC69: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5BB);
label_EC6C:;
    /* $EC6C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_EC6E:;
    /* $EC6E: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_EC6F:;
    /* $EC6F: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_EC70:;
    /* $EC70: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_EC71:;
    /* $EC71: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_EC72:;
    /* $EC72: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xC0; FLAG_NZ(g_cpu.A);
label_EC74:;
    /* $EC74: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x00); FLAG_NZ(g_cpu.A);
label_EC76:;
    /* $EC76: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EC77:;
    /* $EC77: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5BB);
label_EC7A:;
    /* $EC7A: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EC7B:;
    /* $EC7B: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EC7C:;
    /* $EC7C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03BC); FLAG_NZ(g_cpu.A);
label_EC7F:;
    /* $EC7F: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5C1);
label_EC82:;
    /* $EC82: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B1); FLAG_NZ(g_cpu.A);
label_EC85:;
    /* $EC85: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EC88:;
    /* $EC88: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03F1 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EC8B:;
    /* $EC8B: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_EC8C:;
    /* $EC8C: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x071C); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_EC8F:;
    /* $EC8F: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_EC91:;
    /* $EC91: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_EC92:;
    /* $EC92: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x03B1); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_EC95:;
    /* $EC95: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_EC97:;
    /* $EC97: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x06 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x06); g_cpu.A=r&0xFF; }
label_EC99:;
    /* $EC99: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EC9C:;
    /* $EC9C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03BD); FLAG_NZ(g_cpu.A);
label_EC9F:;
    /* $EC9F: 99 */ maybe_trigger_vblank(5); nes_write((0x0208 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ECA2:;
    /* $ECA2: 99 */ maybe_trigger_vblank(5); nes_write((0x020C + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ECA5:;
    /* $ECA5: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B2); FLAG_NZ(g_cpu.A);
label_ECA8:;
    /* $ECA8: 99 */ maybe_trigger_vblank(5); nes_write((0x020B + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ECAB:;
    /* $ECAB: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_ECAD:;
    /* $ECAD: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_ECAE:;
    /* $ECAE: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x03B2); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_ECB1:;
    /* $ECB1: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_ECB3:;
    /* $ECB3: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x06 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x06); g_cpu.A=r&0xFF; }
label_ECB5:;
    /* $ECB5: 99 */ maybe_trigger_vblank(5); nes_write((0x020F + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ECB8:;
    /* $ECB8: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D4); FLAG_NZ(g_cpu.A);
label_ECBB:;
    /* $ECBB: 20 */ maybe_trigger_vblank(6); call_by_address(0xEC46);
label_ECBE:;
    /* $ECBE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D4); FLAG_NZ(g_cpu.A);
label_ECC1:;
    /* $ECC1: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_ECC2:;
    /* $ECC2: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_ECC9;
label_ECC4:;
    /* $ECC4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_ECC6:;
    /* $ECC6: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5C1);
label_ECC9:; /* ChnkOfs */
    /* $ECC9: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_ECCB:;
    /* $ECCB: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_ECDD;
label_ECCD:;
    /* $ECCD: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0203 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_ECD0:;
    /* $ECD0: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x0207 + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_ECD3:;
    /* $ECD3: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_ECDD;
label_ECD5:;
    /* $ECD5: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_ECD7:;
    /* $ECD7: 99 */ maybe_trigger_vblank(5); nes_write((0x0204 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ECDA:;
    /* $ECDA: 99 */ maybe_trigger_vblank(5); nes_write((0x020C + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ECDD:; /* ExBCDr */
    /* $ECDD: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::draw_fireball_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_ECF0;
        case 2: goto label_ECF1;
    }
label_ECDE:; /* DrawFireball */
    /* $ECDE: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06F1 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_ECE1:;
    /* $ECE1: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03BA); FLAG_NZ(g_cpu.A);
label_ECE4:;
    /* $ECE4: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ECE7:;
    /* $ECE7: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AF); FLAG_NZ(g_cpu.A);
label_ECEA:;
    /* $ECEA: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ECED:; /* DrawFirebar */
    /* $ECED: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_ECEF:;
    /* $ECEF: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_ECF0:;
    /* $ECF0: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_ECF1:;
    /* $ECF1: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_ECF2:;
    /* $ECF2: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_ECF4:;
    /* $ECF4: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x64; FLAG_NZ(g_cpu.A);
label_ECF6:;
    /* $ECF6: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ECF9:;
    /* $ECF9: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_ECFA:;
    /* $ECFA: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_ECFB:;
    /* $ECFB: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_ECFC:;
    /* $ECFC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_ECFE:;
    /* $ECFE: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_ED02;
label_ED00:;
    /* $ED00: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0xC0; FLAG_NZ(g_cpu.A);
label_ED02:; /* FireA */
    /* $ED02: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED05:;
    /* $ED05: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::draw_explosion_fireball_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_ED20;
        case 2: goto label_ED18;
        case 3: goto label_ED2E;
    }
label_ED09:; /* DrawExplosion_Fireball */
    /* $ED09: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06EC + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_ED0C:;
    /* $ED0C: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x24 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_ED0E:;
    /* $ED0E: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0x24 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_ED10:;
    /* $ED10: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_ED11:;
    /* $ED11: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_ED13:;
    /* $ED13: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_ED15:;
    /* $ED15: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_ED61;
label_ED17:; /* DrawExplosion_Fireworks */
    /* $ED17: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_ED18:;
    /* $ED18: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xED06 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_ED1B:;
    /* $ED1B: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_ED1C:;
    /* $ED1C: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5BB);
label_ED1F:;
    /* $ED1F: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_ED20:;
    /* $ED20: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_ED22:;
    /* $ED22: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03BA); FLAG_NZ(g_cpu.A);
label_ED25:;
    /* $ED25: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_ED26:;
    /* $ED26: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x04; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_ED28:;
    /* $ED28: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED2B:;
    /* $ED2B: 99 */ maybe_trigger_vblank(5); nes_write((0x0208 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED2E:;
    /* $ED2E: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_ED2F:;
    /* $ED2F: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_ED31:;
    /* $ED31: 99 */ maybe_trigger_vblank(5); nes_write((0x0204 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED34:;
    /* $ED34: 99 */ maybe_trigger_vblank(5); nes_write((0x020C + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED37:;
    /* $ED37: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AF); FLAG_NZ(g_cpu.A);
label_ED3A:;
    /* $ED3A: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_ED3B:;
    /* $ED3B: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x04; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_ED3D:;
    /* $ED3D: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED40:;
    /* $ED40: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED43:;
    /* $ED43: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_ED44:;
    /* $ED44: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_ED46:;
    /* $ED46: 99 */ maybe_trigger_vblank(5); nes_write((0x020B + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED49:;
    /* $ED49: 99 */ maybe_trigger_vblank(5); nes_write((0x020F + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED4C:;
    /* $ED4C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_ED4E:;
    /* $ED4E: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED51:;
    /* $ED51: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x82; FLAG_NZ(g_cpu.A);
label_ED53:;
    /* $ED53: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED56:;
    /* $ED56: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x42; FLAG_NZ(g_cpu.A);
label_ED58:;
    /* $ED58: 99 */ maybe_trigger_vblank(5); nes_write((0x020A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED5B:;
    /* $ED5B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xC2; FLAG_NZ(g_cpu.A);
label_ED5D:;
    /* $ED5D: 99 */ maybe_trigger_vblank(5); nes_write((0x020E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED60:;
    /* $ED60: 60 */ maybe_trigger_vblank(6);
    return;
label_ED61:; /* KillFireBall */
    /* $ED61: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_ED63:;
    /* $ED63: 95 */ maybe_trigger_vblank(4); nes_write((0x24 + g_cpu.X) & 0xFF, g_cpu.A);
label_ED65:;
    /* $ED65: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::draw_small_platform_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_EDD1;
        case 2: goto label_ED6F;
        case 3: goto label_EDC5;
        case 4: goto label_ED86;
        case 5: goto label_EDA6;
        case 6: goto label_EDB9;
        case 7: goto label_ED76;
    }
label_ED66:; /* DrawSmallPlatform */
    /* $ED66: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_ED69:;
    /* $ED69: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x5B; FLAG_NZ(g_cpu.A);
label_ED6B:;
    /* $ED6B: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_ED6C:;
    /* $ED6C: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5B5);
label_ED6F:;
    /* $ED6F: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_ED70:;
    /* $ED70: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_ED72:;
    /* $ED72: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5B5);
label_ED75:;
    /* $ED75: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_ED76:;
    /* $ED76: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_ED77:;
    /* $ED77: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_ED7A:;
    /* $ED7A: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED7D:;
    /* $ED7D: 99 */ maybe_trigger_vblank(5); nes_write((0x020F + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED80:;
    /* $ED80: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_ED81:;
    /* $ED81: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_ED83:;
    /* $ED83: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED86:;
    /* $ED86: 99 */ maybe_trigger_vblank(5); nes_write((0x0213 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED89:;
    /* $ED89: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_ED8A:;
    /* $ED8A: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_ED8C:;
    /* $ED8C: 99 */ maybe_trigger_vblank(5); nes_write((0x020B + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED8F:;
    /* $ED8F: 99 */ maybe_trigger_vblank(5); nes_write((0x0217 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_ED92:;
    /* $ED92: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_ED94:;
    /* $ED94: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_ED95:;
    /* $ED95: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_ED96:;
    /* $ED96: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x20; g_cpu.C=(g_cpu.X>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_ED98:;
    /* $ED98: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_ED9C;
label_ED9A:;
    /* $ED9A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_ED9C:; /* TopSP */
    /* $ED9C: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5BE);
label_ED9F:;
    /* $ED9F: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_EDA0:;
    /* $EDA0: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_EDA1:;
    /* $EDA1: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x80 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x80); g_cpu.A=r&0xFF; }
label_EDA3:;
    /* $EDA3: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_EDA4:;
    /* $EDA4: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x20; g_cpu.C=(g_cpu.X>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_EDA6:;
    /* $EDA6: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_EDAA;
label_EDA8:;
    /* $EDA8: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_EDAA:; /* BotSP */
    /* $EDAA: 99 */ maybe_trigger_vblank(5); nes_write((0x020C + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EDAD:;
    /* $EDAD: 99 */ maybe_trigger_vblank(5); nes_write((0x0210 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EDB0:;
    /* $EDB0: 99 */ maybe_trigger_vblank(5); nes_write((0x0214 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EDB3:;
    /* $EDB3: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D1); FLAG_NZ(g_cpu.A);
label_EDB6:;
    /* $EDB6: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_EDB7:;
    /* $EDB7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_EDB9:;
    /* $EDB9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EDC3;
label_EDBB:;
    /* $EDBB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_EDBD:;
    /* $EDBD: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EDC0:;
    /* $EDC0: 99 */ maybe_trigger_vblank(5); nes_write((0x020C + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EDC3:; /* SOfs */
    /* $EDC3: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_EDC4:;
    /* $EDC4: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_EDC5:;
    /* $EDC5: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x04; FLAG_NZ(g_cpu.A);
label_EDC7:;
    /* $EDC7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EDD1;
label_EDC9:;
    /* $EDC9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_EDCB:;
    /* $EDCB: 99 */ maybe_trigger_vblank(5); nes_write((0x0204 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EDCE:;
    /* $EDCE: 99 */ maybe_trigger_vblank(5); nes_write((0x0210 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EDD1:; /* SOfs2 */
    /* $EDD1: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_EDD2:;
    /* $EDD2: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_EDD4:;
    /* $EDD4: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_EDDE;
label_EDD6:;
    /* $EDD6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_EDD8:;
    /* $EDD8: 99 */ maybe_trigger_vblank(5); nes_write((0x0208 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EDDB:;
    /* $EDDB: 99 */ maybe_trigger_vblank(5); nes_write((0x0214 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EDDE:; /* ExSPl */
    /* $EDDE: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_EDE0:;
    /* $EDE0: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::draw_bubble_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_EE06;
        case 2: goto label_EE03;
        case 3: goto label_EDED;
        case 4: goto label_EDE3;
        case 5: goto label_EDE4;
        case 6: goto label_EDE6;
        case 7: goto label_EE01;
    }
label_EDE1:; /* DrawBubble */
    /* $EDE1: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xB5); FLAG_NZ(g_cpu.Y);
label_EDE3:;
    /* $EDE3: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_EDE4:;
    /* $EDE4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EE06;
label_EDE6:;
    /* $EDE6: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D3); FLAG_NZ(g_cpu.A);
label_EDE9:;
    /* $EDE9: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_EDEB:;
    /* $EDEB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_EE06;
label_EDED:;
    /* $EDED: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06EE + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_EDF0:;
    /* $EDF0: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B0); FLAG_NZ(g_cpu.A);
label_EDF3:;
    /* $EDF3: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EDF6:;
    /* $EDF6: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03BB); FLAG_NZ(g_cpu.A);
label_EDF9:;
    /* $EDF9: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EDFC:;
    /* $EDFC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x74; FLAG_NZ(g_cpu.A);
label_EDFE:;
    /* $EDFE: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EE01:;
    /* $EE01: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_EE03:;
    /* $EE03: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EE06:; /* ExDBub */
    /* $EE06: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::render_player_sub_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_EFD1;
        case 2: goto label_EFDF;
    }
label_EFBE:; /* RenderPlayerSub */
    /* $EFBE: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_EFC0:;
    /* $EFC0: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AD); FLAG_NZ(g_cpu.A);
label_EFC3:;
    /* $EFC3: 8D */ maybe_trigger_vblank(4); nes_write(0x0755, g_cpu.A);
label_EFC6:;
    /* $EFC6: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_EFC8:;
    /* $EFC8: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B8); FLAG_NZ(g_cpu.A);
label_EFCB:;
    /* $EFCB: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_EFCD:;
    /* $EFCD: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x33); FLAG_NZ(g_cpu.A);
label_EFCF:;
    /* $EFCF: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_EFD1:;
    /* $EFD1: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03C4); FLAG_NZ(g_cpu.A);
label_EFD4:;
    /* $EFD4: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_EFD6:;
    /* $EFD6: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x06D5); FLAG_NZ(g_cpu.X);
label_EFD9:;
    /* $EFD9: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06E4); FLAG_NZ(g_cpu.Y);
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
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_EFDC;
    }
label_EFEB:;
    /* $EFEB: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::process_player_action_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F008;
        case 2: goto label_F041;
        case 3: goto label_F004;
        case 4: goto label_F006;
        case 5: goto label_F012;
        case 6: goto label_F010;
        case 7: goto label_F058;
        case 8: goto label_F02D;
        case 9: goto label_F001;
        case 10: goto label_F021;
        case 11: goto label_F03C;
        case 12: goto label_F01F;
        case 13: goto label_EFF0;
        case 14: goto label_F046;
        case 15: goto label_F014;
        case 16: goto label_F00D;
        case 17: goto label_F030;
        case 18: goto label_F033;
        case 19: goto label_F025;
        case 20: goto label_F034;
        case 21: goto label_F02B;
        case 22: goto label_F00B;
        case 23: goto label_F01D;
        case 24: goto label_F027;
        case 25: goto label_F05F;
        case 26: goto label_F060;
        case 27: goto label_F016;
        case 28: goto label_EFFD;
        case 29: goto label_F048;
        case 30: goto label_F050;
        case 31: goto label_F03E;
        case 32: goto label_F065;
        case 33: goto label_F018;
        case 34: goto label_F05D;
        case 35: goto label_F052;
        case 36: goto label_F01A;
        case 37: goto label_F06A;
        case 38: goto label_F023;
        case 39: goto label_F039;
    }
label_EFEC:; /* ProcessPlayerAction */
    /* $EFEC: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x1D); FLAG_NZ(g_cpu.A);
label_EFEE:;
    /* $EFEE: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_EFF0:;
    /* $EFF0: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F044;
label_EFF2:;
    /* $EFF2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_EFF4:;
    /* $EFF4: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F034;
label_EFF6:;
    /* $EFF6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_EFF8:;
    /* $EFF8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F00B;
label_EFFA:;
    /* $EFFA: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0704); FLAG_NZ(g_cpu.A);
label_EFFD:;
    /* $EFFD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F050;
label_EFFF:;
    /* $EFFF: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x06; FLAG_NZ(g_cpu.Y);
label_F001:;
    /* $F001: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0714); FLAG_NZ(g_cpu.A);
label_F004:;
    /* $F004: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F028;
label_F006:;
    /* $F006: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_F008:;
    /* $F008: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF028); return;
label_F00B:; /* ProcOnGroundActs */
    /* $F00B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x06; FLAG_NZ(g_cpu.Y);
label_F00D:;
    /* $F00D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0714); FLAG_NZ(g_cpu.A);
label_F010:;
    /* $F010: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F028;
label_F012:;
    /* $F012: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_F014:;
    /* $F014: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x57); FLAG_NZ(g_cpu.A);
label_F016:;
    /* $F016: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x0C); FLAG_NZ(g_cpu.A);
label_F018:;
    /* $F018: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F028;
label_F01A:;
    /* $F01A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0700); FLAG_NZ(g_cpu.A);
label_F01D:;
    /* $F01D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x09; g_cpu.C=(g_cpu.A>=0x09)?1:0; FLAG_NZ(r&0xFF); }
label_F01F:;
    /* $F01F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_F03C;
label_F021:;
    /* $F021: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x45); FLAG_NZ(g_cpu.A);
label_F023:;
    /* $F023: 25 */ maybe_trigger_vblank(3); g_cpu.A &= nes_read(0x33); FLAG_NZ(g_cpu.A);
label_F025:;
    /* $F025: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F03C;
label_F027:;
    /* $F027: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_F028:; /* NonAnimatedActs */
    /* $F028: 20 */ maybe_trigger_vblank(6); call_by_address(0xF091);
label_F02B:;
    /* $F02B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F02D:;
    /* $F02D: 8D */ maybe_trigger_vblank(4); nes_write(0x070D, g_cpu.A);
label_F030:;
    /* $F030: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xEE07 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F033:;
    /* $F033: 60 */ maybe_trigger_vblank(6);
    return;
label_F034:; /* ActionFalling */
    /* $F034: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x04; FLAG_NZ(g_cpu.Y);
label_F036:;
    /* $F036: 20 */ maybe_trigger_vblank(6); call_by_address(0xF091);
label_F039:;
    /* $F039: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF062); return;
label_F03C:; /* ActionWalkRun */
    /* $F03C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x04; FLAG_NZ(g_cpu.Y);
label_F03E:;
    /* $F03E: 20 */ maybe_trigger_vblank(6); call_by_address(0xF091);
label_F041:;
    /* $F041: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF068); return;
label_F044:; /* ActionClimbing */
    /* $F044: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x05; FLAG_NZ(g_cpu.Y);
label_F046:;
    /* $F046: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x9F); FLAG_NZ(g_cpu.A);
label_F048:;
    /* $F048: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F028;
    }
label_F04A:;
    /* $F04A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF091);
label_F04D:;
    /* $F04D: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF06D); return;
label_F050:; /* ActionSwimming */
    /* $F050: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_F052:;
    /* $F052: 20 */ maybe_trigger_vblank(6); call_by_address(0xF091);
label_F055:;
    /* $F055: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0782); FLAG_NZ(g_cpu.A);
label_F058:;
    /* $F058: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x070D); FLAG_NZ(g_cpu.A);
label_F05B:;
    /* $F05B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F068;
label_F05D:;
    /* $F05D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0A); FLAG_NZ(g_cpu.A);
label_F05F:;
    /* $F05F: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_F060:;
    /* $F060: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F068;
label_F062:; /* GetCurrentAnimOffset */
    /* $F062: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x070D); FLAG_NZ(g_cpu.A);
label_F065:;
    /* $F065: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF0D0); return;
label_F068:; /* FourFrameExtent */
    /* $F068: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_F06A:;
    /* $F06A: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF06F); return;
}

void RenderEngine::three_frame_extent_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F090;
        case 2: goto label_F086;
        case 3: goto label_F07D;
        case 4: goto label_F074;
        case 5: goto label_F075;
        case 6: goto label_F080;
        case 7: goto label_F088;
    }
label_F06D:; /* ThreeFrameExtent */
    /* $F06D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_F06F:; /* AnimationControl */
    /* $F06F: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_F071:;
    /* $F071: 20 */ maybe_trigger_vblank(6); call_by_address(0xF062);
label_F074:;
    /* $F074: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_F075:;
    /* $F075: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0781); FLAG_NZ(g_cpu.A);
label_F078:;
    /* $F078: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F08F;
label_F07A:;
    /* $F07A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x070C); FLAG_NZ(g_cpu.A);
label_F07D:;
    /* $F07D: 8D */ maybe_trigger_vblank(4); nes_write(0x0781, g_cpu.A);
label_F080:;
    /* $F080: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x070D); FLAG_NZ(g_cpu.A);
label_F083:;
    /* $F083: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F084:;
    /* $F084: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_F086:;
    /* $F086: C5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_F088:;
    /* $F088: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_F08C;
label_F08A:;
    /* $F08A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F08C:; /* SetAnimC */
    /* $F08C: 8D */ maybe_trigger_vblank(4); nes_write(0x070D, g_cpu.A);
label_F08F:; /* ExAnimC */
    /* $F08F: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_F090:;
    /* $F090: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::get_gfx_offset_adder_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F098;
    }
label_F091:; /* GetGfxOffsetAdder */
    /* $F091: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0754); FLAG_NZ(g_cpu.A);
label_F094:;
    /* $F094: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F09B;
label_F096:;
    /* $F096: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_F097:;
    /* $F097: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F098:;
    /* $F098: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_F09A:;
    /* $F09A: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F09B:; /* SzOfs */
    /* $F09B: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::handle_change_size_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F0E1;
        case 2: goto label_F0C3;
        case 3: goto label_F0B9;
        case 4: goto label_F0BA;
        case 5: goto label_F0C9;
        case 6: goto label_F0C6;
        case 7: goto label_F0E3;
        case 8: goto label_F0DE;
        case 9: goto label_F0CB;
        case 10: goto label_F0D8;
        case 11: goto label_F0D9;
        case 12: goto label_F0D1;
        case 13: goto label_F0C0;
        case 14: goto label_F0E8;
        case 15: goto label_F0BE;
    }
label_F0B0:; /* HandleChangeSize */
    /* $F0B0: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x070D); FLAG_NZ(g_cpu.Y);
label_F0B3:;
    /* $F0B3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_F0B5:;
    /* $F0B5: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_F0B7:;
    /* $F0B7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F0C6;
label_F0B9:;
    /* $F0B9: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_F0BA:;
    /* $F0BA: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0A; g_cpu.C=(g_cpu.Y>=0x0A)?1:0; FLAG_NZ(r&0xFF); }
label_F0BC:;
    /* $F0BC: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_F0C3;
label_F0BE:;
    /* $F0BE: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_F0C0:;
    /* $F0C0: 8C */ maybe_trigger_vblank(4); nes_write(0x070B, g_cpu.Y);
label_F0C3:; /* CSzNext */
    /* $F0C3: 8C */ maybe_trigger_vblank(4); nes_write(0x070D, g_cpu.Y);
label_F0C6:; /* GorSLog */
    /* $F0C6: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0754); FLAG_NZ(g_cpu.A);
label_F0C9:;
    /* $F0C9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F0D7;
label_F0CB:;
    /* $F0CB: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF09C + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F0CE:;
    /* $F0CE: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x0F; FLAG_NZ(g_cpu.Y);
label_F0D0:; /* GetOffsetFromAnimCtrl */
    /* $F0D0: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_F0D1:;
    /* $F0D1: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_F0D2:;
    /* $F0D2: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_F0D3:;
    /* $F0D3: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xEE07 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_F0D6:;
    /* $F0D6: 60 */ maybe_trigger_vblank(6);
    return;
label_F0D7:; /* ShrinkPlayer */
    /* $F0D7: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_F0D8:;
    /* $F0D8: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F0D9:;
    /* $F0D9: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x0A + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0A); g_cpu.A=r&0xFF; }
label_F0DB:;
    /* $F0DB: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_F0DC:;
    /* $F0DC: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x09; FLAG_NZ(g_cpu.Y);
label_F0DE:;
    /* $F0DE: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF09C + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F0E1:;
    /* $F0E1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F0E5;
label_F0E3:;
    /* $F0E3: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_F0E5:; /* ShrPlF */
    /* $F0E5: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xEE07 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F0E8:;
    /* $F0E8: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::chk_for_player_attrib_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F0F0;
        case 2: goto label_F110;
        case 3: goto label_F0F9;
        case 4: goto label_F0FD;
        case 5: goto label_F0EE;
        case 6: goto label_F0FB;
        case 7: goto label_F0FF;
        case 8: goto label_F0F2;
        case 9: goto label_F0F5;
        case 10: goto label_F11F;
    }
label_F0E9:; /* ChkForPlayerAttrib */
    /* $F0E9: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06E4); FLAG_NZ(g_cpu.Y);
label_F0EC:;
    /* $F0EC: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0E); FLAG_NZ(g_cpu.A);
label_F0EE:;
    /* $F0EE: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0B; g_cpu.C=(g_cpu.A>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_F0F0:;
    /* $F0F0: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F105;
label_F0F2:;
    /* $F0F2: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06D5); FLAG_NZ(g_cpu.A);
label_F0F5:;
    /* $F0F5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x50; g_cpu.C=(g_cpu.A>=0x50)?1:0; FLAG_NZ(r&0xFF); }
label_F0F7:;
    /* $F0F7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F117;
label_F0F9:;
    /* $F0F9: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xB8; g_cpu.C=(g_cpu.A>=0xB8)?1:0; FLAG_NZ(r&0xFF); }
label_F0FB:;
    /* $F0FB: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F117;
label_F0FD:;
    /* $F0FD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xC0; g_cpu.C=(g_cpu.A>=0xC0)?1:0; FLAG_NZ(r&0xFF); }
label_F0FF:;
    /* $F0FF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F117;
label_F101:;
    /* $F101: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xC8; g_cpu.C=(g_cpu.A>=0xC8)?1:0; FLAG_NZ(r&0xFF); }
label_F103:;
    /* $F103: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F129;
label_F105:; /* KilledAtt */
    /* $F105: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0212 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F108:;
    /* $F108: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3F; FLAG_NZ(g_cpu.A);
label_F10A:;
    /* $F10A: 99 */ maybe_trigger_vblank(5); nes_write((0x0212 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F10D:;
    /* $F10D: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0216 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F110:;
    /* $F110: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3F; FLAG_NZ(g_cpu.A);
label_F112:;
    /* $F112: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_F114:;
    /* $F114: 99 */ maybe_trigger_vblank(5); nes_write((0x0216 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F117:; /* C_S_IGAtt */
    /* $F117: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x021A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F11A:;
    /* $F11A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3F; FLAG_NZ(g_cpu.A);
label_F11C:;
    /* $F11C: 99 */ maybe_trigger_vblank(5); nes_write((0x021A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F11F:;
    /* $F11F: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x021E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F122:;
    /* $F122: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3F; FLAG_NZ(g_cpu.A);
label_F124:;
    /* $F124: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_F126:;
    /* $F126: 99 */ maybe_trigger_vblank(5); nes_write((0x021E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F129:; /* ExPlyrAt */
    /* $F129: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::relative_misc_position_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F14D;
    }
label_F148:; /* RelativeMiscPosition */
    /* $F148: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_F14A:;
    /* $F14A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1A8);
label_F14D:;
    /* $F14D: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x06; FLAG_NZ(g_cpu.Y);
label_F14F:;
    /* $F14F: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF142); return;
}

void RenderEngine::get_player_offscreen_bits_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F184;
    }
label_F180:; /* GetPlayerOffscreenBits */
    /* $F180: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_F182:;
    /* $F182: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_F184:;
    /* $F184: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF1C0); return;
}

void RenderEngine::get_misc_offscreen_bits_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F19D;
    }
label_F19B:; /* GetMiscOffscreenBits */
    /* $F19B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_F19D:;
    /* $F19D: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1A8);
label_F1A0:;
    /* $F1A0: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x06; FLAG_NZ(g_cpu.Y);
label_F1A2:;
    /* $F1A2: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF1C0); return;
}

void RenderEngine::get_proper_obj_offset_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F1A9;
    }
label_F1A8:; /* GetProperObjOffset */
    /* $F1A8: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F1A9:;
    /* $F1A9: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F1AA:;
    /* $F1AA: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xF1A5 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_F1AD:;
    /* $F1AD: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_F1AE:;
    /* $F1AE: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::get_enemy_offscreen_bits_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F1B1;
    }
label_F1AF:; /* GetEnemyOffscreenBits */
    /* $F1AF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_F1B1:;
    /* $F1B1: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_F1B3:;
    /* $F1B3: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF1BA); return;
}

void RenderEngine::get_block_offscreen_bits_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F1D1;
        case 2: goto label_F1BD;
        case 3: goto label_F1BC;
        case 4: goto label_F1C1;
        case 5: goto label_F1CE;
    }
label_F1B6:; /* GetBlockOffscreenBits */
    /* $F1B6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x09; FLAG_NZ(g_cpu.A);
label_F1B8:;
    /* $F1B8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x04; FLAG_NZ(g_cpu.Y);
label_F1BA:; /* SetOffscrBitsOffset */
    /* $F1BA: 86 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.X);
label_F1BC:;
    /* $F1BC: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F1BD:;
    /* $F1BD: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_F1BF:;
    /* $F1BF: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_F1C0:; /* GetOffScreenBitsSet */
    /* $F1C0: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_F1C1:;
    /* $F1C1: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_F1C2:;
    /* $F1C2: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1D7);
label_F1C5:;
    /* $F1C5: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_F1C6:;
    /* $F1C6: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_F1C7:;
    /* $F1C7: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_F1C8:;
    /* $F1C8: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_F1C9:;
    /* $F1C9: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x00); FLAG_NZ(g_cpu.A);
label_F1CB:;
    /* $F1CB: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_F1CD:;
    /* $F1CD: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_F1CE:;
    /* $F1CE: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F1CF:;
    /* $F1CF: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_F1D1:;
    /* $F1D1: 99 */ maybe_trigger_vblank(5); nes_write((0x03D0 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F1D4:;
    /* $F1D4: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_F1D6:;
    /* $F1D6: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::get_y_offscreen_bits_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F23D;
    }
label_F239:; /* GetYOffscreenBits */
    /* $F239: 86 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.X);
label_F23B:;
    /* $F23B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_F23D:; /* YOfsLoop */
    /* $F23D: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF237 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F240:;
    /* $F240: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_F241:;
    /* $F241: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xCE + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_F243:;
    /* $F243: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_F245:;
    /* $F245: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_F247:;
    /* $F247: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xB5 + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_F249:;
    /* $F249: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xF234 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_F24C:;
    /* $F24C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_F24E:;
    /* $F24E: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_F260;
label_F250:;
    /* $F250: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xF235 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_F253:;
    /* $F253: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_F255:;
    /* $F255: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_F260;
label_F257:;
    /* $F257: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_F259:;
    /* $F259: 85 */ maybe_trigger_vblank(3); nes_write(0x06, g_cpu.A);
label_F25B:;
    /* $F25B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_F25D:;
    /* $F25D: 20 */ maybe_trigger_vblank(6); call_by_address(0xF26D);
label_F260:; /* YLdBData */
    /* $F260: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF22B + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F263:;
    /* $F263: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x04); FLAG_NZ(g_cpu.X);
label_F265:;
    /* $F265: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_F267:;
    /* $F267: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F26C;
label_F269:;
    /* $F269: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_F26A:;
    /* $F26A: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F23D;
    }
label_F26C:; /* ExYOfsBS */
    /* $F26C: 60 */ maybe_trigger_vblank(6);
    return;
}

void RenderEngine::draw_sprite_object_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F2BD;
        case 2: goto label_F285;
        case 3: goto label_F286;
        case 4: goto label_F2A5;
        case 5: goto label_F284;
        case 6: goto label_F2C8;
        case 7: goto label_F288;
    }
label_F282:; /* DrawSpriteObject */
    /* $F282: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x03); FLAG_NZ(g_cpu.A);
label_F284:;
    /* $F284: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F285:;
    /* $F285: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F286:;
    /* $F286: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_F288:;
    /* $F288: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_F296;
label_F28A:;
    /* $F28A: 99 */ maybe_trigger_vblank(5); nes_write((0x0205 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F28D:;
    /* $F28D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_F28F:;
    /* $F28F: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F292:;
    /* $F292: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_F294:;
    /* $F294: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F2A0;
label_F296:; /* NoHFlip */
    /* $F296: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F299:;
    /* $F299: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_F29B:;
    /* $F29B: 99 */ maybe_trigger_vblank(5); nes_write((0x0205 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F29E:;
    /* $F29E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F2A0:; /* SetHFAt */
    /* $F2A0: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x04); FLAG_NZ(g_cpu.A);
label_F2A2:;
    /* $F2A2: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F2A5:;
    /* $F2A5: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F2A8:;
    /* $F2A8: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_F2AA:;
    /* $F2AA: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F2AD:;
    /* $F2AD: 99 */ maybe_trigger_vblank(5); nes_write((0x0204 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F2B0:;
    /* $F2B0: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x05); FLAG_NZ(g_cpu.A);
label_F2B2:;
    /* $F2B2: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F2B5:;
    /* $F2B5: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F2B6:;
    /* $F2B6: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_F2B8:;
    /* $F2B8: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_F2BB:;
    /* $F2BB: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_F2BD:;
    /* $F2BD: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F2BE:;
    /* $F2BE: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_F2C0:;
    /* $F2C0: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_F2C2:;
    /* $F2C2: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_F2C3:;
    /* $F2C3: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F2C4:;
    /* $F2C4: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_F2C6:;
    /* $F2C6: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F2C7:;
    /* $F2C7: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_F2C8:;
    /* $F2C8: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_F2C9:;
    /* $F2C9: 60 */ maybe_trigger_vblank(6);
    return;
}

}  // namespace smb::semcomp
