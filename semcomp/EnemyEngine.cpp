// semcomp/EnemyEngine.cpp — bulk-ported routines (auto-generated).
#include "semcomp/EnemyEngine.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

void EnemyEngine::enemies_and_loops_core() {
    enemies_and_loops_core_body(0);
}

void EnemyEngine::at_c058() {
    enemies_and_loops_core_body(1);
}

void EnemyEngine::at_c04e() {
    enemies_and_loops_core_body(2);
}

void EnemyEngine::at_c04d() {
    enemies_and_loops_core_body(3);
}

void EnemyEngine::exec_game_loopback() {
    exec_game_loopback_body(0);
}

void EnemyEngine::at_c0c8() {
    exec_game_loopback_body(1);
}

void EnemyEngine::at_c0a0() {
    exec_game_loopback_body(2);
}

void EnemyEngine::at_c0b7() {
    exec_game_loopback_body(3);
}

void EnemyEngine::at_c0c2() {
    exec_game_loopback_body(4);
}

void EnemyEngine::at_c0a9() {
    exec_game_loopback_body(5);
}

void EnemyEngine::at_c0a8() {
    exec_game_loopback_body(6);
}

void EnemyEngine::proc_loop_command() {
    proc_loop_command_body(0);
}

void EnemyEngine::at_c0e9() {
    proc_loop_command_body(1);
}

void EnemyEngine::at_c0e1() {
    proc_loop_command_body(2);
}

void EnemyEngine::at_c1be() {
    proc_loop_command_body(3);
}

void EnemyEngine::at_c0f0() {
    proc_loop_command_body(4);
}

void EnemyEngine::at_c14d() {
    proc_loop_command_body(5);
}

void EnemyEngine::at_c0cf() {
    proc_loop_command_body(6);
}

void EnemyEngine::at_c18e() {
    proc_loop_command_body(7);
}

void EnemyEngine::at_c1ae() {
    proc_loop_command_body(8);
}

void EnemyEngine::at_c219() {
    proc_loop_command_body(9);
}

void EnemyEngine::find_loop() {
    proc_loop_command_body(10);
}

void EnemyEngine::at_c242() {
    proc_loop_command_body(11);
}

void EnemyEngine::at_c141() {
    proc_loop_command_body(12);
}

void EnemyEngine::at_c124() {
    proc_loop_command_body(13);
}

void EnemyEngine::do_group() {
    proc_loop_command_body(14);
}

void EnemyEngine::at_c20e() {
    proc_loop_command_body(15);
}

void EnemyEngine::at_c21e() {
    proc_loop_command_body(16);
}

void EnemyEngine::at_c213() {
    proc_loop_command_body(17);
}

void EnemyEngine::wrong_chk() {
    proc_loop_command_body(18);
}

void EnemyEngine::inc_m_loop() {
    proc_loop_command_body(19);
}

void EnemyEngine::at_c0d6() {
    proc_loop_command_body(20);
}

void EnemyEngine::at_c0ff() {
    proc_loop_command_body(21);
}

void EnemyEngine::at_c15d() {
    proc_loop_command_body(22);
}

void EnemyEngine::checkpoint_enemy_id() {
    checkpoint_enemy_id_body(0);
}

void EnemyEngine::no_init_code() {
    checkpoint_enemy_id_body(1);
}

void EnemyEngine::init_podoboo() {
    init_podoboo_body(0);
}

void EnemyEngine::at_c304() {
    init_podoboo_body(1);
}

void EnemyEngine::at_c302() {
    init_podoboo_body(2);
}

void EnemyEngine::at_c301() {
    init_podoboo_body(3);
}

void EnemyEngine::init_retainer_obj() {
    init_retainer_obj_body(0);
}

void EnemyEngine::at_c30b() {
    init_retainer_obj_body(1);
}

void EnemyEngine::init_red_koopa() {
    init_red_koopa_body(0);
}

void EnemyEngine::at_c321() {
    init_red_koopa_body(1);
}

void EnemyEngine::init_bloober() {
    init_bloober_body(0);
}

void EnemyEngine::at_c365() {
    init_bloober_body(1);
}

void EnemyEngine::at_c367() {
    init_bloober_body(2);
}

void EnemyEngine::lakitu_and_spiny_handler() {
    lakitu_and_spiny_handler_body(0);
}

void EnemyEngine::chp_chp_ex() {
    lakitu_and_spiny_handler_body(1);
}

void EnemyEngine::at_c40a() {
    lakitu_and_spiny_handler_body(2);
}

void EnemyEngine::at_c3d1() {
    lakitu_and_spiny_handler_body(3);
}

void EnemyEngine::dif_loop() {
    lakitu_and_spiny_handler_body(4);
}

void EnemyEngine::at_c420() {
    lakitu_and_spiny_handler_body(5);
}

void EnemyEngine::chk_no_en() {
    lakitu_and_spiny_handler_body(6);
}

void EnemyEngine::at_c3c4() {
    lakitu_and_spiny_handler_body(7);
}

void EnemyEngine::at_c424() {
    lakitu_and_spiny_handler_body(8);
}

void EnemyEngine::at_c402() {
    lakitu_and_spiny_handler_body(9);
}

void EnemyEngine::at_c3b9() {
    lakitu_and_spiny_handler_body(10);
}

void EnemyEngine::at_c416() {
    lakitu_and_spiny_handler_body(11);
}

void EnemyEngine::at_c40d() {
    lakitu_and_spiny_handler_body(12);
}

void EnemyEngine::at_c412() {
    lakitu_and_spiny_handler_body(13);
}

void EnemyEngine::at_c442() {
    lakitu_and_spiny_handler_body(14);
}

void EnemyEngine::chk_lak() {
    lakitu_and_spiny_handler_body(15);
}

void EnemyEngine::at_c3c1() {
    lakitu_and_spiny_handler_body(16);
}

void EnemyEngine::at_c3fd() {
    lakitu_and_spiny_handler_body(17);
}

void EnemyEngine::init_long_firebar() {
    init_long_firebar_body(0);
}

void EnemyEngine::at_c47d() {
    init_long_firebar_body(1);
}

void EnemyEngine::init_flying_cheep_cheep() {
    init_flying_cheep_cheep_body(0);
}

void EnemyEngine::at_c511() {
    init_flying_cheep_cheep_body(1);
}

void EnemyEngine::at_c500() {
    init_flying_cheep_cheep_body(2);
}

void EnemyEngine::at_c504() {
    init_flying_cheep_cheep_body(3);
}

void EnemyEngine::at_c4ad() {
    init_flying_cheep_cheep_body(4);
}

void EnemyEngine::at_c4fc() {
    init_flying_cheep_cheep_body(5);
}

void EnemyEngine::at_c4fd() {
    init_flying_cheep_cheep_body(6);
}

void EnemyEngine::at_c4ca() {
    init_flying_cheep_cheep_body(7);
}

void EnemyEngine::at_c502() {
    init_flying_cheep_cheep_body(8);
}

void EnemyEngine::at_c508() {
    init_flying_cheep_cheep_body(9);
}

void EnemyEngine::at_c4b0() {
    init_flying_cheep_cheep_body(10);
}

void EnemyEngine::at_c521() {
    init_flying_cheep_cheep_body(11);
}

void EnemyEngine::at_c4d1() {
    init_flying_cheep_cheep_body(12);
}

void EnemyEngine::at_c51f() {
    init_flying_cheep_cheep_body(13);
}

void EnemyEngine::at_c506() {
    init_flying_cheep_cheep_body(14);
}

void EnemyEngine::at_c50c() {
    init_flying_cheep_cheep_body(15);
}

void EnemyEngine::at_c533() {
    init_flying_cheep_cheep_body(16);
}

void EnemyEngine::at_c516() {
    init_flying_cheep_cheep_body(17);
}

void EnemyEngine::at_c518() {
    init_flying_cheep_cheep_body(18);
}

void EnemyEngine::init_bowser() {
    init_bowser_body(0);
}

void EnemyEngine::at_c56d() {
    init_bowser_body(1);
}

void EnemyEngine::at_c54c() {
    init_bowser_body(2);
}

void EnemyEngine::at_c563() {
    init_bowser_body(3);
}

void EnemyEngine::duplicate_enemy_obj() {
    duplicate_enemy_obj_body(0);
}

void EnemyEngine::flm_ex() {
    duplicate_enemy_obj_body(1);
}

void EnemyEngine::at_c588() {
    duplicate_enemy_obj_body(2);
}

void EnemyEngine::at_c586() {
    duplicate_enemy_obj_body(3);
}

void EnemyEngine::init_bowser_flame() {
    init_bowser_flame_body(0);
}

void EnemyEngine::at_c5cf() {
    init_bowser_flame_body(1);
}

void EnemyEngine::at_c604() {
    init_bowser_flame_body(2);
}

void EnemyEngine::set_fr_t() {
    init_bowser_flame_body(3);
}

void EnemyEngine::at_c606() {
    init_bowser_flame_body(4);
}

void EnemyEngine::at_c609() {
    init_bowser_flame_body(5);
}

void EnemyEngine::at_c5c6() {
    init_bowser_flame_body(6);
}

void EnemyEngine::at_c5c7() {
    init_bowser_flame_body(7);
}

void EnemyEngine::at_c5be() {
    init_bowser_flame_body(8);
}

void EnemyEngine::at_c613() {
    init_bowser_flame_body(9);
}

void EnemyEngine::set_mf() {
    init_bowser_flame_body(10);
}

void EnemyEngine::at_c5ad() {
    init_bowser_flame_body(11);
}

void EnemyEngine::at_c624() {
    init_bowser_flame_body(12);
}

void EnemyEngine::bullet_bill_cheep_cheep() {
    bullet_bill_cheep_cheep_body(0);
}

void EnemyEngine::at_c6d7() {
    bullet_bill_cheep_cheep_body(1);
}

void EnemyEngine::at_c6c8() {
    bullet_bill_cheep_cheep_body(2);
}

void EnemyEngine::at_c6b1() {
    bullet_bill_cheep_cheep_body(3);
}

void EnemyEngine::at_c6ec() {
    bullet_bill_cheep_cheep_body(4);
}

void EnemyEngine::set17_id() {
    bullet_bill_cheep_cheep_body(5);
}

void EnemyEngine::at_c74c() {
    bullet_bill_cheep_cheep_body(6);
}

void EnemyEngine::at_c75d() {
    bullet_bill_cheep_cheep_body(7);
}

void EnemyEngine::at_c700() {
    bullet_bill_cheep_cheep_body(8);
}

void EnemyEngine::at_c725() {
    bullet_bill_cheep_cheep_body(9);
}

void EnemyEngine::at_c741() {
    bullet_bill_cheep_cheep_body(10);
}

void EnemyEngine::at_c738() {
    bullet_bill_cheep_cheep_body(11);
}

void EnemyEngine::at_c720() {
    bullet_bill_cheep_cheep_body(12);
}

void EnemyEngine::at_c77a() {
    bullet_bill_cheep_cheep_body(13);
}

void EnemyEngine::cnt_grp() {
    bullet_bill_cheep_cheep_body(14);
}

void EnemyEngine::at_c772() {
    bullet_bill_cheep_cheep_body(15);
}

void EnemyEngine::at_c734() {
    bullet_bill_cheep_cheep_body(16);
}

void EnemyEngine::at_c6ce() {
    bullet_bill_cheep_cheep_body(17);
}

void EnemyEngine::bb_s_loop() {
    bullet_bill_cheep_cheep_body(18);
}

void EnemyEngine::gr_loop() {
    bullet_bill_cheep_cheep_body(19);
}

void EnemyEngine::init_piranha_plant() {
    init_piranha_plant_body(0);
}

void EnemyEngine::at_c78c() {
    init_piranha_plant_body(1);
}

void EnemyEngine::init_enemy_frenzy() {
    init_enemy_frenzy_body(0);
}

void EnemyEngine::at_c7c9() {
    init_enemy_frenzy_body(1);
}

void EnemyEngine::end_frenzy() {
    end_frenzy_body(0);
}

void EnemyEngine::lakitu_chk() {
    end_frenzy_body(1);
}

void EnemyEngine::init_bal_platform() {
    init_bal_platform_body(0);
}

void EnemyEngine::at_c808() {
    init_bal_platform_body(1);
}

void EnemyEngine::at_c805() {
    init_bal_platform_body(2);
}

void EnemyEngine::at_c800() {
    init_bal_platform_body(3);
}

void EnemyEngine::at_c7ef() {
    init_bal_platform_body(4);
}

void EnemyEngine::at_c7f7() {
    init_bal_platform_body(5);
}

void EnemyEngine::at_c7ff() {
    init_bal_platform_body(6);
}

void EnemyEngine::init_hori_platform() {
    init_hori_platform_body(0);
}

void EnemyEngine::at_c80f() {
    init_hori_platform_body(1);
}

void EnemyEngine::at_c80d() {
    init_hori_platform_body(2);
}

void EnemyEngine::init_vert_platform() {
    init_vert_platform_body(0);
}

void EnemyEngine::at_c814() {
    init_vert_platform_body(1);
}

void EnemyEngine::set_yo() {
    init_vert_platform_body(2);
}

void EnemyEngine::at_c816() {
    init_vert_platform_body(3);
}

void EnemyEngine::at_c81b() {
    init_vert_platform_body(4);
}

void EnemyEngine::at_c824() {
    init_vert_platform_body(5);
}

void EnemyEngine::at_c834() {
    init_vert_platform_body(6);
}

void EnemyEngine::at_c81d() {
    init_vert_platform_body(7);
}

void EnemyEngine::at_c818() {
    init_vert_platform_body(8);
}

void EnemyEngine::at_c81a() {
    init_vert_platform_body(9);
}

void EnemyEngine::plat_lift_up() {
    plat_lift_up_body(0);
}

void EnemyEngine::at_c84d() {
    plat_lift_up_body(1);
}

void EnemyEngine::plat_lift_down() {
    plat_lift_down_body(0);
}

void EnemyEngine::at_c859() {
    plat_lift_down_body(1);
}

void EnemyEngine::at_c85c() {
    plat_lift_down_body(2);
}

void EnemyEngine::pos_platform() {
    pos_platform_body(0);
}

void EnemyEngine::at_c87e() {
    pos_platform_body(1);
}

void EnemyEngine::at_c880() {
    pos_platform_body(2);
}

void EnemyEngine::run_enemy_objects_core() {
    run_enemy_objects_core_body(0);
}

void EnemyEngine::no_run_code() {
    run_enemy_objects_core_body(1);
}

void EnemyEngine::at_c888() {
    run_enemy_objects_core_body(2);
}

void EnemyEngine::jmp_eo() {
    run_enemy_objects_core_body(3);
}

void EnemyEngine::at_c88a() {
    run_enemy_objects_core_body(4);
}

void EnemyEngine::run_normal_enemies() {
    run_normal_enemies_body(0);
}

void EnemyEngine::at_c8ff() {
    run_normal_enemies_body(1);
}

void EnemyEngine::skip_move() {
    run_normal_enemies_body(2);
}

void EnemyEngine::at_c8eb() {
    run_normal_enemies_body(3);
}

void EnemyEngine::at_c8e8() {
    run_normal_enemies_body(4);
}

void EnemyEngine::at_c8ee() {
    run_normal_enemies_body(5);
}

void EnemyEngine::at_c8e5() {
    run_normal_enemies_body(6);
}

void EnemyEngine::at_c8f7() {
    run_normal_enemies_body(7);
}

void EnemyEngine::at_c8f1() {
    run_normal_enemies_body(8);
}

void EnemyEngine::enemy_movement_subs() {
    enemy_movement_subs_body(0);
}

void EnemyEngine::no_move_code() {
    enemy_movement_subs_body(1);
}

void EnemyEngine::run_bowser_flame() {
    run_bowser_flame_body(0);
}

void EnemyEngine::at_c938() {
    run_bowser_flame_body(1);
}

void EnemyEngine::at_c93e() {
    run_bowser_flame_body(2);
}

void EnemyEngine::run_firebar_obj() {
    run_firebar_obj_body(0);
}

void EnemyEngine::at_c94a() {
    run_firebar_obj_body(1);
}

void EnemyEngine::run_small_platform() {
    run_small_platform_body(0);
}

void EnemyEngine::at_c959() {
    run_small_platform_body(1);
}

void EnemyEngine::at_c953() {
    run_small_platform_body(2);
}

void EnemyEngine::run_large_platform() {
    run_large_platform_body(0);
}

void EnemyEngine::at_c96b() {
    run_large_platform_body(1);
}

void EnemyEngine::at_c96e() {
    run_large_platform_body(2);
}

void EnemyEngine::at_c97f() {
    run_large_platform_body(3);
}

void EnemyEngine::large_platform_subroutines() {
    large_platform_subroutines_body(0);
}

void EnemyEngine::at_c987() {
    large_platform_subroutines_body(1);
}

void EnemyEngine::at_c9ac() {
    large_platform_subroutines_body(2);
}

void EnemyEngine::move_podoboo() {
    move_podoboo_body(0);
}

void EnemyEngine::at_c9c0() {
    move_podoboo_body(1);
}

void EnemyEngine::at_c9c9() {
    move_podoboo_body(2);
}

void EnemyEngine::at_c9b5() {
    move_podoboo_body(3);
}

void EnemyEngine::pdb_m() {
    move_podoboo_body(4);
}

void EnemyEngine::at_c9c7() {
    move_podoboo_body(5);
}

void EnemyEngine::proc_hammer_bro() {
    proc_hammer_bro_body(0);
}

void EnemyEngine::star_flag_exit() {
    proc_hammer_bro_body(1);
}

void EnemyEngine::no_p_up() {
    proc_hammer_bro_body(2);
}

void EnemyEngine::ex_sfn() {
    proc_hammer_bro_body(3);
}

void EnemyEngine::ex_fl() {
    proc_hammer_bro_body(4);
}

void EnemyEngine::ex_b_gfx_h() {
    proc_hammer_bro_body(5);
}

void EnemyEngine::at_d001() {
    proc_hammer_bro_body(6);
}

void EnemyEngine::at_d007() {
    proc_hammer_bro_body(7);
}

void EnemyEngine::at_d907() {
    proc_hammer_bro_body(8);
}

void EnemyEngine::at_d908() {
    proc_hammer_bro_body(9);
}

void EnemyEngine::at_d0c0() {
    proc_hammer_bro_body(10);
}

void EnemyEngine::at_cea5() {
    proc_hammer_bro_body(11);
}

void EnemyEngine::at_d9cf() {
    proc_hammer_bro_body(12);
}

void EnemyEngine::at_d9ee() {
    proc_hammer_bro_body(13);
}

void EnemyEngine::at_d003() {
    proc_hammer_bro_body(14);
}

void EnemyEngine::at_d9ae() {
    proc_hammer_bro_body(15);
}

void EnemyEngine::at_d98d() {
    proc_hammer_bro_body(16);
}

void EnemyEngine::at_cdad() {
    proc_hammer_bro_body(17);
}

void EnemyEngine::at_cd8e() {
    proc_hammer_bro_body(18);
}

void EnemyEngine::at_c9ea() {
    proc_hammer_bro_body(19);
}

void EnemyEngine::at_d100() {
    proc_hammer_bro_body(20);
}

void EnemyEngine::at_cd87() {
    proc_hammer_bro_body(21);
}

void EnemyEngine::at_cf96() {
    proc_hammer_bro_body(22);
}

void EnemyEngine::at_ccae() {
    proc_hammer_bro_body(23);
}

void EnemyEngine::at_cd4b() {
    proc_hammer_bro_body(24);
}

void EnemyEngine::at_cfb5() {
    proc_hammer_bro_body(25);
}

void EnemyEngine::at_d89d() {
    proc_hammer_bro_body(26);
}

void EnemyEngine::at_d1c8() {
    proc_hammer_bro_body(27);
}

void EnemyEngine::at_d009() {
    proc_hammer_bro_body(28);
}

void EnemyEngine::at_cf76() {
    proc_hammer_bro_body(29);
}

void EnemyEngine::at_d18e() {
    proc_hammer_bro_body(30);
}

void EnemyEngine::at_d94c() {
    proc_hammer_bro_body(31);
}

void EnemyEngine::at_d1ee() {
    proc_hammer_bro_body(32);
}

void EnemyEngine::at_d1ad() {
    proc_hammer_bro_body(33);
}

void EnemyEngine::at_ca05() {
    proc_hammer_bro_body(34);
}

void EnemyEngine::shroom_flower_p_up() {
    proc_hammer_bro_body(35);
}

void EnemyEngine::at_cfb9() {
    proc_hammer_bro_body(36);
}

void EnemyEngine::revive_stunned() {
    proc_hammer_bro_body(37);
}

void EnemyEngine::at_d058() {
    proc_hammer_bro_body(38);
}

void EnemyEngine::at_cf8d() {
    proc_hammer_bro_body(39);
}

void EnemyEngine::at_cf9a() {
    proc_hammer_bro_body(40);
}

void EnemyEngine::at_d920() {
    proc_hammer_bro_body(41);
}

void EnemyEngine::s_pixel_lak() {
    proc_hammer_bro_body(42);
}

void EnemyEngine::at_cb8d() {
    proc_hammer_bro_body(43);
}

void EnemyEngine::at_d7cf() {
    proc_hammer_bro_body(44);
}

void EnemyEngine::at_d031() {
    proc_hammer_bro_body(45);
}

void EnemyEngine::at_d7ae() {
    proc_hammer_bro_body(46);
}

void EnemyEngine::at_d38c() {
    proc_hammer_bro_body(47);
}

void EnemyEngine::at_d38d() {
    proc_hammer_bro_body(48);
}

void EnemyEngine::at_cec2() {
    proc_hammer_bro_body(49);
}

void EnemyEngine::chk_player_near_pipe() {
    proc_hammer_bro_body(50);
}

void EnemyEngine::at_ccd0() {
    proc_hammer_bro_body(51);
}

void EnemyEngine::at_d012() {
    proc_hammer_bro_body(52);
}

void EnemyEngine::at_d660() {
    proc_hammer_bro_body(53);
}

void EnemyEngine::at_cfd7() {
    proc_hammer_bro_body(54);
}

void EnemyEngine::at_d6d0() {
    proc_hammer_bro_body(55);
}

void EnemyEngine::too_far() {
    proc_hammer_bro_body(56);
}

void EnemyEngine::at_d6c8() {
    proc_hammer_bro_body(57);
}

void EnemyEngine::at_d6ca() {
    proc_hammer_bro_body(58);
}

void EnemyEngine::at_d6ba() {
    proc_hammer_bro_body(59);
}

void EnemyEngine::at_d6b8() {
    proc_hammer_bro_body(60);
}

void EnemyEngine::at_d7b8() {
    proc_hammer_bro_body(61);
}

void EnemyEngine::at_d8cb() {
    proc_hammer_bro_body(62);
}

void EnemyEngine::at_cb8a() {
    proc_hammer_bro_body(63);
}

void EnemyEngine::at_cc4b() {
    proc_hammer_bro_body(64);
}

void EnemyEngine::reverse_plant_speed() {
    proc_hammer_bro_body(65);
}

void EnemyEngine::at_d62d() {
    proc_hammer_bro_body(66);
}

void EnemyEngine::at_d00c() {
    proc_hammer_bro_body(67);
}

void EnemyEngine::get_v_adder() {
    proc_hammer_bro_body(68);
}

void EnemyEngine::hammer_bro_jump_l_data() {
    proc_hammer_bro_body(69);
}

void EnemyEngine::at_d041() {
    proc_hammer_bro_body(70);
}

void EnemyEngine::at_d079() {
    proc_hammer_bro_body(71);
}

void EnemyEngine::at_d4b9() {
    proc_hammer_bro_body(72);
}

void EnemyEngine::at_d4ba() {
    proc_hammer_bro_body(73);
}

void EnemyEngine::set_m2() {
    proc_hammer_bro_body(74);
}

void EnemyEngine::at_cff7() {
    proc_hammer_bro_body(75);
}

void EnemyEngine::ex_pf() {
    proc_hammer_bro_body(76);
}

void EnemyEngine::at_d6fa() {
    proc_hammer_bro_body(77);
}

void EnemyEngine::at_d0cb() {
    proc_hammer_bro_body(78);
}

void EnemyEngine::at_d089() {
    proc_hammer_bro_body(79);
}

void EnemyEngine::at_d069() {
    proc_hammer_bro_body(80);
}

void EnemyEngine::at_cec5() {
    proc_hammer_bro_body(81);
}

void EnemyEngine::swim_ccx_move_data() {
    proc_hammer_bro_body(82);
}

void EnemyEngine::at_cc47() {
    proc_hammer_bro_body(83);
}

void EnemyEngine::at_d018() {
    proc_hammer_bro_body(84);
}

void EnemyEngine::at_ce8f() {
    proc_hammer_bro_body(85);
}

void EnemyEngine::at_cfad() {
    proc_hammer_bro_body(86);
}

void EnemyEngine::at_cd06() {
    proc_hammer_bro_body(87);
}

void EnemyEngine::at_cd07() {
    proc_hammer_bro_body(88);
}

void EnemyEngine::at_d0f8() {
    proc_hammer_bro_body(89);
}

void EnemyEngine::at_cea4() {
    proc_hammer_bro_body(90);
}

void EnemyEngine::at_cd3b() {
    proc_hammer_bro_body(91);
}

void EnemyEngine::at_ce33() {
    proc_hammer_bro_body(92);
}

void EnemyEngine::firebar_tbl_offsets() {
    proc_hammer_bro_body(93);
}

void EnemyEngine::at_cd2f() {
    proc_hammer_bro_body(94);
}

void EnemyEngine::firebar_pos_lookup_tbl() {
    proc_hammer_bro_body(95);
}

void EnemyEngine::at_ccc8() {
    proc_hammer_bro_body(96);
}

void EnemyEngine::firebar_mirror_data() {
    proc_hammer_bro_body(97);
}

void EnemyEngine::p_random_subtracter() {
    proc_hammer_bro_body(98);
}

void EnemyEngine::at_ced6() {
    proc_hammer_bro_body(99);
}

void EnemyEngine::at_cedb() {
    proc_hammer_bro_body(100);
}

void EnemyEngine::lakitu_diff_adj() {
    proc_hammer_bro_body(101);
}

void EnemyEngine::at_d599() {
    proc_hammer_bro_body(102);
}

void EnemyEngine::ex_y_pl() {
    proc_hammer_bro_body(103);
}

void EnemyEngine::at_d0a1() {
    proc_hammer_bro_body(104);
}

void EnemyEngine::at_d02e() {
    proc_hammer_bro_body(105);
}

void EnemyEngine::at_ced2() {
    proc_hammer_bro_body(106);
}

void EnemyEngine::bridge_collapse_data() {
    proc_hammer_bro_body(107);
}

void EnemyEngine::at_cfde() {
    proc_hammer_bro_body(108);
}

void EnemyEngine::p_random_range() {
    proc_hammer_bro_body(109);
}

void EnemyEngine::at_d609() {
    proc_hammer_bro_body(110);
}

void EnemyEngine::at_d721() {
    proc_hammer_bro_body(111);
}

void EnemyEngine::at_d01f() {
    proc_hammer_bro_body(112);
}

void EnemyEngine::flame_timer_data() {
    proc_hammer_bro_body(113);
}

void EnemyEngine::at_d991() {
    proc_hammer_bro_body(114);
}

void EnemyEngine::at_d78d() {
    proc_hammer_bro_body(115);
}

void EnemyEngine::at_cd7d() {
    proc_hammer_bro_body(116);
}

void EnemyEngine::star_flag_y_pos_adder() {
    proc_hammer_bro_body(117);
}

void EnemyEngine::at_d2ce() {
    proc_hammer_bro_body(118);
}

void EnemyEngine::at_d5bd() {
    proc_hammer_bro_body(119);
}

void EnemyEngine::star_flag_tile_data() {
    proc_hammer_bro_body(120);
}

void EnemyEngine::at_d17e() {
    proc_hammer_bro_body(121);
}

void EnemyEngine::star_flag_x_pos_adder() {
    proc_hammer_bro_body(122);
}

void EnemyEngine::at_d2d2() {
    proc_hammer_bro_body(123);
}

void EnemyEngine::at_da10() {
    proc_hammer_bro_body(124);
}

void EnemyEngine::at_d5bc() {
    proc_hammer_bro_body(125);
}

void EnemyEngine::at_d52d() {
    proc_hammer_bro_body(126);
}

void EnemyEngine::at_d9d6() {
    proc_hammer_bro_body(127);
}

void EnemyEngine::at_cfd9() {
    proc_hammer_bro_body(128);
}

void EnemyEngine::at_cfda() {
    proc_hammer_bro_body(129);
}

void EnemyEngine::at_d01a() {
    proc_hammer_bro_body(130);
}

void EnemyEngine::at_cff5() {
    proc_hammer_bro_body(131);
}

void EnemyEngine::at_cf79() {
    proc_hammer_bro_body(132);
}

void EnemyEngine::at_d542() {
    proc_hammer_bro_body(133);
}

void EnemyEngine::at_cfb7() {
    proc_hammer_bro_body(134);
}

void EnemyEngine::at_d8be() {
    proc_hammer_bro_body(135);
}

void EnemyEngine::at_ca01() {
    proc_hammer_bro_body(136);
}

void EnemyEngine::at_ce2d() {
    proc_hammer_bro_body(137);
}

void EnemyEngine::at_ce2e() {
    proc_hammer_bro_body(138);
}

void EnemyEngine::bowser_identities() {
    proc_hammer_bro_body(139);
}

void EnemyEngine::at_d81d() {
    proc_hammer_bro_body(140);
}

void EnemyEngine::kicked_shell_x_spd_data() {
    proc_hammer_bro_body(141);
}

void EnemyEngine::kicked_shell_pts_data() {
    proc_hammer_bro_body(142);
}

void EnemyEngine::at_d893() {
    proc_hammer_bro_body(143);
}

void EnemyEngine::at_d966() {
    proc_hammer_bro_body(144);
}

void EnemyEngine::demoted_koopa_x_spd_data() {
    proc_hammer_bro_body(145);
}

void EnemyEngine::at_d852() {
    proc_hammer_bro_body(146);
}

void EnemyEngine::at_d2b9() {
    proc_hammer_bro_body(147);
}

void EnemyEngine::revival_rate_data() {
    proc_hammer_bro_body(148);
}

void EnemyEngine::at_cadd() {
    proc_hammer_bro_body(149);
}

void EnemyEngine::at_d081() {
    proc_hammer_bro_body(150);
}

void EnemyEngine::set_bits_mask() {
    proc_hammer_bro_body(151);
}

void EnemyEngine::at_d024() {
    proc_hammer_bro_body(152);
}

void EnemyEngine::no_col_fb() {
    proc_hammer_bro_body(153);
}

void EnemyEngine::at_ce86() {
    proc_hammer_bro_body(154);
}

void EnemyEngine::at_d0ae() {
    proc_hammer_bro_body(155);
}

void EnemyEngine::at_cfc9() {
    proc_hammer_bro_body(156);
}

void EnemyEngine::at_c9dc() {
    proc_hammer_bro_body(157);
}

void EnemyEngine::at_d0c5() {
    proc_hammer_bro_body(158);
}

void EnemyEngine::at_ce26() {
    proc_hammer_bro_body(159);
}

void EnemyEngine::at_d0e3() {
    proc_hammer_bro_body(160);
}

void EnemyEngine::at_d0e4() {
    proc_hammer_bro_body(161);
}

void EnemyEngine::at_cbd0() {
    proc_hammer_bro_body(162);
}

void EnemyEngine::at_cbd1() {
    proc_hammer_bro_body(163);
}

void EnemyEngine::at_ca03() {
    proc_hammer_bro_body(164);
}

void EnemyEngine::at_c9de() {
    proc_hammer_bro_body(165);
}

void EnemyEngine::at_d027() {
    proc_hammer_bro_body(166);
}

void EnemyEngine::at_d6ae() {
    proc_hammer_bro_body(167);
}

void EnemyEngine::at_d0e1() {
    proc_hammer_bro_body(168);
}

void EnemyEngine::at_c9f9() {
    proc_hammer_bro_body(169);
}

void EnemyEngine::at_c9da() {
    proc_hammer_bro_body(170);
}

void EnemyEngine::at_d61f() {
    proc_hammer_bro_body(171);
}

void EnemyEngine::at_d047() {
    proc_hammer_bro_body(172);
}

void EnemyEngine::skip_iy() {
    proc_hammer_bro_body(173);
}

void EnemyEngine::at_c9e3() {
    proc_hammer_bro_body(174);
}

void EnemyEngine::at_d595() {
    proc_hammer_bro_body(175);
}

void EnemyEngine::at_d12d() {
    proc_hammer_bro_body(176);
}

void EnemyEngine::at_caf1() {
    proc_hammer_bro_body(177);
}

void EnemyEngine::at_d905() {
    proc_hammer_bro_body(178);
}

void EnemyEngine::at_d913() {
    proc_hammer_bro_body(179);
}

void EnemyEngine::at_ceb5() {
    proc_hammer_bro_body(180);
}

void EnemyEngine::at_cc79() {
    proc_hammer_bro_body(181);
}

void EnemyEngine::at_cc7d() {
    proc_hammer_bro_body(182);
}

void EnemyEngine::at_d0be() {
    proc_hammer_bro_body(183);
}

void EnemyEngine::draw_erase_rope() {
    proc_hammer_bro_body(184);
}

void EnemyEngine::at_d603() {
    proc_hammer_bro_body(185);
}

void EnemyEngine::ex_lift_p() {
    proc_hammer_bro_body(186);
}

void EnemyEngine::at_cebe() {
    proc_hammer_bro_body(187);
}

void EnemyEngine::at_ca0d() {
    proc_hammer_bro_body(188);
}

void EnemyEngine::at_d8db() {
    proc_hammer_bro_body(189);
}

void EnemyEngine::at_d8d9() {
    proc_hammer_bro_body(190);
}

void EnemyEngine::at_cdd9() {
    proc_hammer_bro_body(191);
}

void EnemyEngine::at_cecd() {
    proc_hammer_bro_body(192);
}

void EnemyEngine::at_cece() {
    proc_hammer_bro_body(193);
}

void EnemyEngine::at_cecf() {
    proc_hammer_bro_body(194);
}

void EnemyEngine::at_cfcf() {
    proc_hammer_bro_body(195);
}

void EnemyEngine::at_d2d3() {
    proc_hammer_bro_body(196);
}

void EnemyEngine::at_d2d4() {
    proc_hammer_bro_body(197);
}

void EnemyEngine::at_d58a() {
    proc_hammer_bro_body(198);
}

void EnemyEngine::at_d4d6() {
    proc_hammer_bro_body(199);
}

void EnemyEngine::at_d3e3() {
    proc_hammer_bro_body(200);
}

void EnemyEngine::at_d5d2() {
    proc_hammer_bro_body(201);
}

void EnemyEngine::get_pr_cmp() {
    proc_hammer_bro_body(202);
}

void EnemyEngine::at_d7d1() {
    proc_hammer_bro_body(203);
}

void EnemyEngine::at_d7d7() {
    proc_hammer_bro_body(204);
}

void EnemyEngine::at_d7d8() {
    proc_hammer_bro_body(205);
}

void EnemyEngine::at_cabf() {
    proc_hammer_bro_body(206);
}

void EnemyEngine::ex_sw_cc() {
    proc_hammer_bro_body(207);
}

void EnemyEngine::at_cbcd() {
    proc_hammer_bro_body(208);
}

void EnemyEngine::at_cc49() {
    proc_hammer_bro_body(209);
}

void EnemyEngine::at_d29d() {
    proc_hammer_bro_body(210);
}

void EnemyEngine::at_d8d3() {
    proc_hammer_bro_body(211);
}

void EnemyEngine::at_d036() {
    proc_hammer_bro_body(212);
}

void EnemyEngine::at_d033() {
    proc_hammer_bro_body(213);
}

void EnemyEngine::at_d091() {
    proc_hammer_bro_body(214);
}

void EnemyEngine::at_c9ec() {
    proc_hammer_bro_body(215);
}

void EnemyEngine::at_d0b5() {
    proc_hammer_bro_body(216);
}

void EnemyEngine::at_d03c() {
    proc_hammer_bro_body(217);
}

void EnemyEngine::remove_bridge() {
    proc_hammer_bro_body(218);
}

void EnemyEngine::at_d0ec() {
    proc_hammer_bro_body(219);
}

void EnemyEngine::at_d0ed() {
    proc_hammer_bro_body(220);
}

void EnemyEngine::at_cdbd() {
    proc_hammer_bro_body(221);
}

void EnemyEngine::at_ca07() {
    proc_hammer_bro_body(222);
}

void EnemyEngine::at_d4ad() {
    proc_hammer_bro_body(223);
}

void EnemyEngine::at_d4ae() {
    proc_hammer_bro_body(224);
}

void EnemyEngine::at_d903() {
    proc_hammer_bro_body(225);
}

void EnemyEngine::at_d3ad() {
    proc_hammer_bro_body(226);
}

void EnemyEngine::at_d58d() {
    proc_hammer_bro_body(227);
}

void EnemyEngine::at_caa9() {
    proc_hammer_bro_body(228);
}

void EnemyEngine::at_d5af() {
    proc_hammer_bro_body(229);
}

void EnemyEngine::at_d04c() {
    proc_hammer_bro_body(230);
}

void EnemyEngine::at_d0f0() {
    proc_hammer_bro_body(231);
}

void EnemyEngine::at_d5ad() {
    proc_hammer_bro_body(232);
}

void EnemyEngine::at_d0c8() {
    proc_hammer_bro_body(233);
}

void EnemyEngine::at_d099() {
    proc_hammer_bro_body(234);
}

void EnemyEngine::at_c9f1() {
    proc_hammer_bro_body(235);
}

void EnemyEngine::at_c9f3() {
    proc_hammer_bro_body(236);
}

void EnemyEngine::at_d045() {
    proc_hammer_bro_body(237);
}

void EnemyEngine::at_cef4() {
    proc_hammer_bro_body(238);
}

void EnemyEngine::set_v_fbr() {
    proc_hammer_bro_body(239);
}

void EnemyEngine::at_d0f6() {
    proc_hammer_bro_body(240);
}

void EnemyEngine::at_d0f4() {
    proc_hammer_bro_body(241);
}

void EnemyEngine::at_d4b1() {
    proc_hammer_bro_body(242);
}

void EnemyEngine::at_cba0() {
    proc_hammer_bro_body(243);
}

void EnemyEngine::at_ce40() {
    proc_hammer_bro_body(244);
}

void EnemyEngine::no_b_fall() {
    proc_hammer_bro_body(245);
}

void EnemyEngine::at_d9b9() {
    proc_hammer_bro_body(246);
}

void EnemyEngine::at_d6b0() {
    proc_hammer_bro_body(247);
}

void EnemyEngine::at_cad7() {
    proc_hammer_bro_body(248);
}

void EnemyEngine::at_d3b9() {
    proc_hammer_bro_body(249);
}

void EnemyEngine::bowser_control() {
    proc_hammer_bro_body(250);
}

void EnemyEngine::at_cca8() {
    proc_hammer_bro_body(251);
}

void EnemyEngine::at_d0fb() {
    proc_hammer_bro_body(252);
}

void EnemyEngine::at_ca8e() {
    proc_hammer_bro_body(253);
}

void EnemyEngine::at_d03e() {
    proc_hammer_bro_body(254);
}

void EnemyEngine::chk_for_fall() {
    proc_hammer_bro_body(255);
}

void EnemyEngine::at_d0f2() {
    proc_hammer_bro_body(256);
}

void EnemyEngine::move_swimming_cheep_cheep() {
    move_swimming_cheep_cheep_body(0);
}

void EnemyEngine::at_cc4c() {
    move_swimming_cheep_cheep_body(1);
}

void EnemyEngine::player_enemy_collision() {
    player_enemy_collision_body(0);
}

void EnemyEngine::draw_vine() {
    player_enemy_collision_body(1);
}

void EnemyEngine::ex_jc_gfx() {
    player_enemy_collision_body(2);
}

void EnemyEngine::ex_ebg() {
    player_enemy_collision_body(3);
}

void EnemyEngine::at_e539() {
    player_enemy_collision_body(4);
}

void EnemyEngine::at_daae() {
    player_enemy_collision_body(5);
}

void EnemyEngine::at_e6f0() {
    player_enemy_collision_body(6);
}

void EnemyEngine::at_e6f1() {
    player_enemy_collision_body(7);
}

void EnemyEngine::at_da8d() {
    player_enemy_collision_body(8);
}

void EnemyEngine::at_e00f() {
    player_enemy_collision_body(9);
}

void EnemyEngine::at_e0ca() {
    player_enemy_collision_body(10);
}

void EnemyEngine::at_dfc2() {
    player_enemy_collision_body(11);
}

void EnemyEngine::at_e0a1() {
    player_enemy_collision_body(12);
}

void EnemyEngine::at_e03d() {
    player_enemy_collision_body(13);
}

void EnemyEngine::at_e401() {
    player_enemy_collision_body(14);
}

void EnemyEngine::at_dfa9() {
    player_enemy_collision_body(15);
}

void EnemyEngine::at_dfaa() {
    player_enemy_collision_body(16);
}

void EnemyEngine::at_e058() {
    player_enemy_collision_body(17);
}

void EnemyEngine::at_ddae() {
    player_enemy_collision_body(18);
}

void EnemyEngine::at_dd8e() {
    player_enemy_collision_body(19);
}

void EnemyEngine::cont_chk() {
    player_enemy_collision_body(20);
}

void EnemyEngine::at_dd0d() {
    player_enemy_collision_body(21);
}

void EnemyEngine::at_e0e8() {
    player_enemy_collision_body(22);
}

void EnemyEngine::at_db4d() {
    player_enemy_collision_body(23);
}

void EnemyEngine::at_e08e() {
    player_enemy_collision_body(24);
}

void EnemyEngine::at_dfca() {
    player_enemy_collision_body(25);
}

void EnemyEngine::at_e274() {
    player_enemy_collision_body(26);
}

void EnemyEngine::at_e800() {
    player_enemy_collision_body(27);
}

void EnemyEngine::at_decb() {
    player_enemy_collision_body(28);
}

void EnemyEngine::at_df21() {
    player_enemy_collision_body(29);
}

void EnemyEngine::check_for_retainer_obj() {
    player_enemy_collision_body(30);
}

void EnemyEngine::at_e003() {
    player_enemy_collision_body(31);
}

void EnemyEngine::at_e5cf() {
    player_enemy_collision_body(32);
}

void EnemyEngine::at_e5d0() {
    player_enemy_collision_body(33);
}

void EnemyEngine::at_e606() {
    player_enemy_collision_body(34);
}

void EnemyEngine::at_e609() {
    player_enemy_collision_body(35);
}

void EnemyEngine::at_e60a() {
    player_enemy_collision_body(36);
}

void EnemyEngine::at_e605() {
    player_enemy_collision_body(37);
}

void EnemyEngine::at_e6cd() {
    player_enemy_collision_body(38);
}

void EnemyEngine::at_e802() {
    player_enemy_collision_body(39);
}

void EnemyEngine::at_dab9() {
    player_enemy_collision_body(40);
}

void EnemyEngine::at_dc8e() {
    player_enemy_collision_body(41);
}

void EnemyEngine::at_dccd() {
    player_enemy_collision_body(42);
}

void EnemyEngine::no_bump() {
    player_enemy_collision_body(43);
}

void EnemyEngine::at_e603() {
    player_enemy_collision_body(44);
}

void EnemyEngine::at_e8c9() {
    player_enemy_collision_body(45);
}

void EnemyEngine::at_e40d() {
    player_enemy_collision_body(46);
}

void EnemyEngine::at_e029() {
    player_enemy_collision_body(47);
}

void EnemyEngine::at_dc1a() {
    player_enemy_collision_body(48);
}

void EnemyEngine::at_e56f() {
    player_enemy_collision_body(49);
}

void EnemyEngine::at_e818() {
    player_enemy_collision_body(50);
}

void EnemyEngine::at_e857() {
    player_enemy_collision_body(51);
}

void EnemyEngine::at_e858() {
    player_enemy_collision_body(52);
}

void EnemyEngine::at_e1d1() {
    player_enemy_collision_body(53);
}

void EnemyEngine::at_dfc0() {
    player_enemy_collision_body(54);
}

void EnemyEngine::at_daab() {
    player_enemy_collision_body(55);
}

void EnemyEngine::at_dc55() {
    player_enemy_collision_body(56);
}

void EnemyEngine::at_e60d() {
    player_enemy_collision_body(57);
}

void EnemyEngine::at_e60e() {
    player_enemy_collision_body(58);
}

void EnemyEngine::at_dc16() {
    player_enemy_collision_body(59);
}

void EnemyEngine::player_pos_s_plat_data() {
    player_enemy_collision_body(60);
}

void EnemyEngine::block_buffer_adder_data() {
    player_enemy_collision_body(61);
}

void EnemyEngine::pipe_dwn_s() {
    player_enemy_collision_body(62);
}

void EnemyEngine::player_bg_upper_extent() {
    player_enemy_collision_body(63);
}

void EnemyEngine::at_df90() {
    player_enemy_collision_body(64);
}

void EnemyEngine::at_e820() {
    player_enemy_collision_body(65);
}

void EnemyEngine::at_df9b() {
    player_enemy_collision_body(66);
}

void EnemyEngine::at_e4c9() {
    player_enemy_collision_body(67);
}

void EnemyEngine::at_e4ca() {
    player_enemy_collision_body(68);
}

void EnemyEngine::at_de2f() {
    player_enemy_collision_body(69);
}

void EnemyEngine::at_dd20() {
    player_enemy_collision_body(70);
}

void EnemyEngine::area_change_timer_data() {
    player_enemy_collision_body(71);
}

void EnemyEngine::at_de8e() {
    player_enemy_collision_body(72);
}

void EnemyEngine::at_dd07() {
    player_enemy_collision_body(73);
}

void EnemyEngine::flagpole_y_pos_data() {
    player_enemy_collision_body(74);
}

void EnemyEngine::climb_x_pos_adder() {
    player_enemy_collision_body(75);
}

void EnemyEngine::at_db8e() {
    player_enemy_collision_body(76);
}

void EnemyEngine::at_e807() {
    player_enemy_collision_body(77);
}

void EnemyEngine::at_e80a() {
    player_enemy_collision_body(78);
}

void EnemyEngine::at_dfb1() {
    player_enemy_collision_body(79);
}

void EnemyEngine::at_dde0() {
    player_enemy_collision_body(80);
}

void EnemyEngine::solid_m_tile_upper_ext() {
    player_enemy_collision_body(81);
}

void EnemyEngine::climb_m_tile_upper_ext() {
    player_enemy_collision_body(82);
}

void EnemyEngine::at_e090() {
    player_enemy_collision_body(83);
}

void EnemyEngine::enemy_bgc_state_data() {
    player_enemy_collision_body(84);
}

void EnemyEngine::at_e389() {
    player_enemy_collision_body(85);
}

void EnemyEngine::at_e791() {
    player_enemy_collision_body(86);
}

void EnemyEngine::no_c_dir_f() {
    player_enemy_collision_body(87);
}

void EnemyEngine::at_e061() {
    player_enemy_collision_body(88);
}

void EnemyEngine::at_e27d() {
    player_enemy_collision_body(89);
}

void EnemyEngine::at_e1fe() {
    player_enemy_collision_body(90);
}

void EnemyEngine::at_e1ff() {
    player_enemy_collision_body(91);
}

void EnemyEngine::at_e804() {
    player_enemy_collision_body(92);
}

void EnemyEngine::at_dd04() {
    player_enemy_collision_body(93);
}

void EnemyEngine::at_dd2a() {
    player_enemy_collision_body(94);
}

void EnemyEngine::at_dd3b() {
    player_enemy_collision_body(95);
}

void EnemyEngine::at_dd60() {
    player_enemy_collision_body(96);
}

void EnemyEngine::at_dd61() {
    player_enemy_collision_body(97);
}

void EnemyEngine::award_touched_coin() {
    player_enemy_collision_body(98);
}

void EnemyEngine::at_e3f1() {
    player_enemy_collision_body(99);
}

void EnemyEngine::block_buffer_x_adder() {
    player_enemy_collision_body(100);
}

void EnemyEngine::at_e121() {
    player_enemy_collision_body(101);
}

void EnemyEngine::at_e3cd() {
    player_enemy_collision_body(102);
}

void EnemyEngine::at_e1a9() {
    player_enemy_collision_body(103);
}

void EnemyEngine::at_e0a9() {
    player_enemy_collision_body(104);
}

void EnemyEngine::first_spr_y_pos() {
    player_enemy_collision_body(105);
}

void EnemyEngine::at_e4c5() {
    player_enemy_collision_body(106);
}

void EnemyEngine::second_spr_y_pos() {
    player_enemy_collision_body(107);
}

void EnemyEngine::at_e4cd() {
    player_enemy_collision_body(108);
}

void EnemyEngine::first_spr_x_pos() {
    player_enemy_collision_body(109);
}

void EnemyEngine::first_spr_tilenum() {
    player_enemy_collision_body(110);
}

void EnemyEngine::second_spr_tilenum() {
    player_enemy_collision_body(111);
}

void EnemyEngine::flagpole_score_num_tiles() {
    player_enemy_collision_body(112);
}

void EnemyEngine::at_dbd6() {
    player_enemy_collision_body(113);
}

void EnemyEngine::at_dbb5() {
    player_enemy_collision_body(114);
}

void EnemyEngine::power_up_gfx_table() {
    player_enemy_collision_body(115);
}

void EnemyEngine::jumping_coin_tiles() {
    player_enemy_collision_body(116);
}

void EnemyEngine::at_e683() {
    player_enemy_collision_body(117);
}

void EnemyEngine::at_e48d() {
    player_enemy_collision_body(118);
}

void EnemyEngine::at_e4e4() {
    player_enemy_collision_body(119);
}

void EnemyEngine::at_e6c0() {
    player_enemy_collision_body(120);
}

void EnemyEngine::at_dcfc() {
    player_enemy_collision_body(121);
}

void EnemyEngine::at_dcdd() {
    player_enemy_collision_body(122);
}

void EnemyEngine::at_dfdc() {
    player_enemy_collision_body(123);
}

void EnemyEngine::hb_chk() {
    player_enemy_collision_body(124);
}

void EnemyEngine::at_dcdf() {
    player_enemy_collision_body(125);
}

void EnemyEngine::at_dddc() {
    player_enemy_collision_body(126);
}

void EnemyEngine::at_ddde() {
    player_enemy_collision_body(127);
}

void EnemyEngine::at_dedf() {
    player_enemy_collision_body(128);
}

void EnemyEngine::at_da7b() {
    player_enemy_collision_body(129);
}

void EnemyEngine::at_dbda() {
    player_enemy_collision_body(130);
}

void EnemyEngine::at_e3d4() {
    player_enemy_collision_body(131);
}

void EnemyEngine::at_e2e4() {
    player_enemy_collision_body(132);
}

void EnemyEngine::at_e58a() {
    player_enemy_collision_body(133);
}

void EnemyEngine::at_e6e7() {
    player_enemy_collision_body(134);
}

void EnemyEngine::at_e7e9() {
    player_enemy_collision_body(135);
}

void EnemyEngine::jumpspring_frame_offsets() {
    player_enemy_collision_body(136);
}

void EnemyEngine::at_e879() {
    player_enemy_collision_body(137);
}

void EnemyEngine::enemy_gfx_table_offsets() {
    player_enemy_collision_body(138);
}

void EnemyEngine::at_dea3() {
    player_enemy_collision_body(139);
}

void EnemyEngine::next_v_sp() {
    player_enemy_collision_body(140);
}

void EnemyEngine::at_e4a3() {
    player_enemy_collision_body(141);
}

void EnemyEngine::at_e0ea() {
    player_enemy_collision_body(142);
}

void EnemyEngine::at_e67f() {
    player_enemy_collision_body(143);
}

void EnemyEngine::at_e672() {
    player_enemy_collision_body(144);
}

void EnemyEngine::at_e667() {
    player_enemy_collision_body(145);
}

void EnemyEngine::at_e01d() {
    player_enemy_collision_body(146);
}

void EnemyEngine::at_e04e() {
    player_enemy_collision_body(147);
}

void EnemyEngine::at_e646() {
    player_enemy_collision_body(148);
}

void EnemyEngine::enemy_anim_timing_b_mask() {
    player_enemy_collision_body(149);
}

void EnemyEngine::at_e877() {
    player_enemy_collision_body(150);
}

void EnemyEngine::at_e005() {
    player_enemy_collision_body(151);
}

void EnemyEngine::at_e041() {
    player_enemy_collision_body(152);
}

void EnemyEngine::at_e007() {
    player_enemy_collision_body(153);
}

void EnemyEngine::enemy_graphics_table() {
    player_enemy_collision_body(154);
}

void EnemyEngine::at_e57d() {
    player_enemy_collision_body(155);
}

void EnemyEngine::chk2_msb_st() {
    player_enemy_collision_body(156);
}

void EnemyEngine::check_for_bullet_bill_cv() {
    player_enemy_collision_body(157);
}

void EnemyEngine::set_wy_spd() {
    player_enemy_collision_body(158);
}

void EnemyEngine::at_e0ab() {
    player_enemy_collision_body(159);
}

void EnemyEngine::at_e4ad() {
    player_enemy_collision_body(160);
}

void EnemyEngine::at_e7bd() {
    player_enemy_collision_body(161);
}

void EnemyEngine::at_dc20() {
    player_enemy_collision_body(162);
}

void EnemyEngine::at_def0() {
    player_enemy_collision_body(163);
}

void EnemyEngine::at_e8a8() {
    player_enemy_collision_body(164);
}

void EnemyEngine::at_e0d0() {
    player_enemy_collision_body(165);
}

void EnemyEngine::at_dcd1() {
    player_enemy_collision_body(166);
}

void EnemyEngine::p_up_draw_loop() {
    player_enemy_collision_body(167);
}

void EnemyEngine::at_e6fa() {
    player_enemy_collision_body(168);
}

void EnemyEngine::at_e301() {
    player_enemy_collision_body(169);
}

void EnemyEngine::at_ddd5() {
    player_enemy_collision_body(170);
}

void EnemyEngine::at_e3de() {
    player_enemy_collision_body(171);
}

void EnemyEngine::at_dfda() {
    player_enemy_collision_body(172);
}

void EnemyEngine::ex_ste_chk() {
    player_enemy_collision_body(173);
}

void EnemyEngine::at_e763() {
    player_enemy_collision_body(174);
}

void EnemyEngine::at_e1e4() {
    player_enemy_collision_body(175);
}

void EnemyEngine::at_e3e1() {
    player_enemy_collision_body(176);
}

void EnemyEngine::at_e3e2() {
    player_enemy_collision_body(177);
}

void EnemyEngine::at_de1e() {
    player_enemy_collision_body(178);
}

void EnemyEngine::at_e0df() {
    player_enemy_collision_body(179);
}

void EnemyEngine::at_df01() {
    player_enemy_collision_body(180);
}

void EnemyEngine::side_check_loop() {
    player_enemy_collision_body(181);
}

void EnemyEngine::at_e7e6() {
    player_enemy_collision_body(182);
}

void EnemyEngine::at_de59() {
    player_enemy_collision_body(183);
}

void EnemyEngine::at_e850() {
    player_enemy_collision_body(184);
}

void EnemyEngine::at_df77() {
    player_enemy_collision_body(185);
}

void EnemyEngine::at_df71() {
    player_enemy_collision_body(186);
}

void EnemyEngine::at_ddd3() {
    player_enemy_collision_body(187);
}

void EnemyEngine::chk_small_plat_loop() {
    player_enemy_collision_body(188);
}

void EnemyEngine::at_e38b() {
    player_enemy_collision_body(189);
}

void EnemyEngine::sde_c_loop() {
    player_enemy_collision_body(190);
}

void EnemyEngine::at_e3b1() {
    player_enemy_collision_body(191);
}

void EnemyEngine::at_e3ba() {
    player_enemy_collision_body(192);
}

void EnemyEngine::no_h_offscr() {
    player_enemy_collision_body(193);
}

void EnemyEngine::at_e53b() {
    player_enemy_collision_body(194);
}

void EnemyEngine::chk_f_top() {
    player_enemy_collision_body(195);
}

void EnemyEngine::at_dec9() {
    player_enemy_collision_body(196);
}

void EnemyEngine::at_de8a() {
    player_enemy_collision_body(197);
}

void EnemyEngine::at_debf() {
    player_enemy_collision_body(198);
}

void EnemyEngine::at_e629() {
    player_enemy_collision_body(199);
}

void EnemyEngine::at_e6f5() {
    player_enemy_collision_body(200);
}

void EnemyEngine::at_e4bd() {
    player_enemy_collision_body(201);
}

void EnemyEngine::at_e179() {
    player_enemy_collision_body(202);
}

void EnemyEngine::at_e49d() {
    player_enemy_collision_body(203);
}

void EnemyEngine::at_e710() {
    player_enemy_collision_body(204);
}

void EnemyEngine::set_fall_s() {
    player_enemy_collision_body(205);
}

void EnemyEngine::at_e385() {
    player_enemy_collision_body(206);
}

void EnemyEngine::at_dc23() {
    player_enemy_collision_body(207);
}

void EnemyEngine::at_e600() {
    player_enemy_collision_body(208);
}

void EnemyEngine::at_ddbd() {
    player_enemy_collision_body(209);
}

void EnemyEngine::at_e38d() {
    player_enemy_collision_body(210);
}

void EnemyEngine::at_e28d() {
    player_enemy_collision_body(211);
}

void EnemyEngine::at_e7b9() {
    player_enemy_collision_body(212);
}

void EnemyEngine::at_db93() {
    player_enemy_collision_body(213);
}

void EnemyEngine::at_dcb9() {
    player_enemy_collision_body(214);
}

void EnemyEngine::at_dd90() {
    player_enemy_collision_body(215);
}

void EnemyEngine::at_e7b1() {
    player_enemy_collision_body(216);
}

void EnemyEngine::at_dfd0() {
    player_enemy_collision_body(217);
}

void EnemyEngine::at_e59a() {
    player_enemy_collision_body(218);
}

void EnemyEngine::at_e61b() {
    player_enemy_collision_body(219);
}

void EnemyEngine::at_e0b9() {
    player_enemy_collision_body(220);
}

void EnemyEngine::at_e4b9() {
    player_enemy_collision_body(221);
}

void EnemyEngine::at_e7a5() {
    player_enemy_collision_body(222);
}

void EnemyEngine::at_dd76() {
    player_enemy_collision_body(223);
}

void EnemyEngine::at_db04() {
    player_enemy_collision_body(224);
}

void EnemyEngine::at_dd3d() {
    player_enemy_collision_body(225);
}

void EnemyEngine::at_db5c() {
    player_enemy_collision_body(226);
}

void EnemyEngine::at_db0c() {
    player_enemy_collision_body(227);
}

void EnemyEngine::at_de82() {
    player_enemy_collision_body(228);
}

void EnemyEngine::check_left_screen_b_box() {
    player_enemy_collision_body(229);
}

void EnemyEngine::at_e286() {
    player_enemy_collision_body(230);
}

void EnemyEngine::at_e528() {
    player_enemy_collision_body(231);
}

void EnemyEngine::at_db3b() {
    player_enemy_collision_body(232);
}

void EnemyEngine::ex_hc() {
    player_enemy_collision_body(233);
}

void EnemyEngine::at_dece() {
    player_enemy_collision_body(234);
}

void EnemyEngine::at_dba7() {
    player_enemy_collision_body(235);
}

void EnemyEngine::at_e730() {
    player_enemy_collision_body(236);
}

void EnemyEngine::at_e347() {
    player_enemy_collision_body(237);
}

void EnemyEngine::at_db47() {
    player_enemy_collision_body(238);
}

void EnemyEngine::at_e406() {
    player_enemy_collision_body(239);
}

void EnemyEngine::at_e001() {
    player_enemy_collision_body(240);
}

void EnemyEngine::at_e431() {
    player_enemy_collision_body(241);
}

void EnemyEngine::ex_csm() {
    player_enemy_collision_body(242);
}

void EnemyEngine::at_e408() {
    player_enemy_collision_body(243);
}

void EnemyEngine::at_e70a() {
    player_enemy_collision_body(244);
}

void EnemyEngine::at_dd06() {
    player_enemy_collision_body(245);
}

void EnemyEngine::at_de4b() {
    player_enemy_collision_body(246);
}

void EnemyEngine::at_dd0a() {
    player_enemy_collision_body(247);
}

void EnemyEngine::at_e112() {
    player_enemy_collision_body(248);
}

void EnemyEngine::at_df11() {
    player_enemy_collision_body(249);
}

void EnemyEngine::at_e139() {
    player_enemy_collision_body(250);
}

void EnemyEngine::at_e278() {
    player_enemy_collision_body(251);
}

void EnemyEngine::at_dc27() {
    player_enemy_collision_body(252);
}

void EnemyEngine::at_e722() {
    player_enemy_collision_body(253);
}

void EnemyEngine::no_ofs2() {
    player_enemy_collision_body(254);
}

void EnemyEngine::at_e372() {
    player_enemy_collision_body(255);
}

void EnemyEngine::at_e781() {
    player_enemy_collision_body(256);
}

void EnemyEngine::check_for_p_up_collision() {
    check_for_p_up_collision_body(0);
}

void EnemyEngine::at_e8e3() {
    check_for_p_up_collision_body(1);
}

void EnemyEngine::at_e8e5() {
    check_for_p_up_collision_body(2);
}

void EnemyEngine::at_e8fd() {
    check_for_p_up_collision_body(3);
}

void EnemyEngine::check_bowser_gfx_flag() {
    check_for_p_up_collision_body(4);
}

void EnemyEngine::at_e8e9() {
    check_for_p_up_collision_body(5);
}

void EnemyEngine::at_e8fb() {
    check_for_p_up_collision_body(6);
}

void EnemyEngine::at_e8d9() {
    check_for_p_up_collision_body(7);
}

void EnemyEngine::enemy_to_bg_collision_det() {
    enemy_to_bg_collision_det_body(0);
}

void EnemyEngine::at_dfc3() {
    enemy_to_bg_collision_det_body(1);
}

void EnemyEngine::enemies_and_loops_core_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C058;
        case 2: goto label_C04E;
        case 3: goto label_C04D;
    }
label_C047:; /* EnemiesAndLoopsCore */
    /* $C047: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C049:;
    /* $C049: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_C04A:;
    /* $C04A: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_C04B:;
    /* $C04B: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_C05F;
label_C04D:;
    /* $C04D: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_C04E:;
    /* $C04E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C053;
label_C050:;
    /* $C050: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC882); return;
label_C053:; /* ChkAreaTsk */
    /* $C053: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071F); FLAG_NZ(g_cpu.A);
label_C056:;
    /* $C056: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_C058:;
    /* $C058: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_C05A:;
    /* $C05A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C06A;
label_C05C:;
    /* $C05C: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC0CC); return;
label_C05F:; /* ChkBowserF */
    /* $C05F: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_C060:;
    /* $C060: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_C062:;
    /* $C062: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C063:;
    /* $C063: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x000F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C066:;
    /* $C066: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C06A;
label_C068:;
    /* $C068: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_C06A:; /* ExitELCore */
    /* $C06A: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::exec_game_loopback_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C0C8;
        case 2: goto label_C0A0;
        case 3: goto label_C0B7;
        case 4: goto label_C0C2;
        case 5: goto label_C0A9;
        case 6: goto label_C0A8;
    }
label_C08C:; /* ExecGameLoopback */
    /* $C08C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x6D); FLAG_NZ(g_cpu.A);
label_C08E:;
    /* $C08E: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C08F:;
    /* $C08F: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x04; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C091:;
    /* $C091: 85 */ maybe_trigger_vblank(3); nes_write(0x6D, g_cpu.A);
label_C093:;
    /* $C093: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0725); FLAG_NZ(g_cpu.A);
label_C096:;
    /* $C096: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C097:;
    /* $C097: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x04; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C099:;
    /* $C099: 8D */ maybe_trigger_vblank(4); nes_write(0x0725, g_cpu.A);
label_C09C:;
    /* $C09C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071A); FLAG_NZ(g_cpu.A);
label_C09F:;
    /* $C09F: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C0A0:;
    /* $C0A0: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x04; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C0A2:;
    /* $C0A2: 8D */ maybe_trigger_vblank(4); nes_write(0x071A, g_cpu.A);
label_C0A5:;
    /* $C0A5: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071B); FLAG_NZ(g_cpu.A);
label_C0A8:;
    /* $C0A8: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C0A9:;
    /* $C0A9: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x04; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C0AB:;
    /* $C0AB: 8D */ maybe_trigger_vblank(4); nes_write(0x071B, g_cpu.A);
label_C0AE:;
    /* $C0AE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x072A); FLAG_NZ(g_cpu.A);
label_C0B1:;
    /* $C0B1: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C0B2:;
    /* $C0B2: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x04; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C0B4:;
    /* $C0B4: 8D */ maybe_trigger_vblank(4); nes_write(0x072A, g_cpu.A);
label_C0B7:;
    /* $C0B7: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C0B9:;
    /* $C0B9: 8D */ maybe_trigger_vblank(4); nes_write(0x073B, g_cpu.A);
label_C0BC:;
    /* $C0BC: 8D */ maybe_trigger_vblank(4); nes_write(0x072B, g_cpu.A);
label_C0BF:;
    /* $C0BF: 8D */ maybe_trigger_vblank(4); nes_write(0x0739, g_cpu.A);
label_C0C2:;
    /* $C0C2: 8D */ maybe_trigger_vblank(4); nes_write(0x073A, g_cpu.A);
label_C0C5:;
    /* $C0C5: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x9BF8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C0C8:;
    /* $C0C8: 8D */ maybe_trigger_vblank(4); nes_write(0x072C, g_cpu.A);
label_C0CB:;
    /* $C0CB: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::proc_loop_command_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C0E9;
        case 2: goto label_C0E1;
        case 3: goto label_C1BE;
        case 4: goto label_C0F0;
        case 5: goto label_C14D;
        case 6: goto label_C0CF;
        case 7: goto label_C18E;
        case 8: goto label_C1AE;
        case 9: goto label_C219;
        case 10: goto label_C0D8;
        case 11: goto label_C242;
        case 12: goto label_C141;
        case 13: goto label_C124;
        case 14: goto label_C22E;
        case 15: goto label_C20E;
        case 16: goto label_C21E;
        case 17: goto label_C213;
        case 18: goto label_C115;
        case 19: goto label_C102;
        case 20: goto label_C0D6;
        case 21: goto label_C0FF;
        case 22: goto label_C15D;
    }
label_C0CC:; /* ProcLoopCommand */
    /* $C0CC: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0745); FLAG_NZ(g_cpu.A);
label_C0CF:;
    /* $C0CF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C12F;
label_C0D1:;
    /* $C0D1: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0726); FLAG_NZ(g_cpu.A);
label_C0D4:;
    /* $C0D4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C12F;
label_C0D6:;
    /* $C0D6: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x0B; FLAG_NZ(g_cpu.Y);
label_C0D8:; /* FindLoop */
    /* $C0D8: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C0D9:;
    /* $C0D9: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_C12F;
label_C0DB:;
    /* $C0DB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_C0DE:;
    /* $C0DE: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xC06B + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_C0E1:;
    /* $C0E1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C0D8;
    }
label_C0E3:;
    /* $C0E3: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0725); FLAG_NZ(g_cpu.A);
label_C0E6:;
    /* $C0E6: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xC076 + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_C0E9:;
    /* $C0E9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C0D8;
    }
label_C0EB:;
    /* $C0EB: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_C0ED:;
    /* $C0ED: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xC081 + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_C0F0:;
    /* $C0F0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C115;
label_C0F2:;
    /* $C0F2: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x1D); FLAG_NZ(g_cpu.A);
label_C0F4:;
    /* $C0F4: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_C0F6:;
    /* $C0F6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C115;
label_C0F8:;
    /* $C0F8: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_C0FB:;
    /* $C0FB: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_C0FD:;
    /* $C0FD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C122;
label_C0FF:;
    /* $C0FF: EE */ maybe_trigger_vblank(6); { uint16_t a=0x06D9; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C102:; /* IncMLoop */
    /* $C102: EE */ maybe_trigger_vblank(6); { uint16_t a=0x06DA; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C105:;
    /* $C105: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06DA); FLAG_NZ(g_cpu.A);
label_C108:;
    /* $C108: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_C10A:;
    /* $C10A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C12A;
label_C10C:;
    /* $C10C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06D9); FLAG_NZ(g_cpu.A);
label_C10F:;
    /* $C10F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_C111:;
    /* $C111: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C122;
label_C113:;
    /* $C113: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C11C;
label_C115:; /* WrongChk */
    /* $C115: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_C118:;
    /* $C118: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_C11A:;
    /* $C11A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C102;
    }
label_C11C:; /* DoLpBack */
    /* $C11C: 20 */ maybe_trigger_vblank(6); call_by_address(0xC08C);
label_C11F:;
    /* $C11F: 20 */ maybe_trigger_vblank(6); call_by_address(0xD071);
label_C122:; /* InitMLp */
    /* $C122: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C124:;
    /* $C124: 8D */ maybe_trigger_vblank(4); nes_write(0x06DA, g_cpu.A);
label_C127:;
    /* $C127: 8D */ maybe_trigger_vblank(4); nes_write(0x06D9, g_cpu.A);
label_C12A:; /* InitLCmd */
    /* $C12A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C12C:;
    /* $C12C: 8D */ maybe_trigger_vblank(4); nes_write(0x0745, g_cpu.A);
label_C12F:; /* ChkEnemyFrenzy */
    /* $C12F: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06CD); FLAG_NZ(g_cpu.A);
label_C132:;
    /* $C132: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C144;
label_C134:;
    /* $C134: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_C136:;
    /* $C136: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C138:;
    /* $C138: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_C13A:;
    /* $C13A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C13C:;
    /* $C13C: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_C13E:;
    /* $C13E: 8D */ maybe_trigger_vblank(4); nes_write(0x06CD, g_cpu.A);
label_C141:;
    /* $C141: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC226); return;
label_C144:; /* ProcessEnemyData */
    /* $C144: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0739); FLAG_NZ(g_cpu.Y);
label_C147:;
    /* $C147: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE9) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C149:;
    /* $C149: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xFF; g_cpu.C=(g_cpu.A>=0xFF)?1:0; FLAG_NZ(r&0xFF); }
label_C14B:;
    /* $C14B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C150;
label_C14D:;
    /* $C14D: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC216); return;
label_C150:; /* CheckEndofBuffer */
    /* $C150: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_C152:;
    /* $C152: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0E; g_cpu.C=(g_cpu.A>=0x0E)?1:0; FLAG_NZ(r&0xFF); }
label_C154:;
    /* $C154: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C164;
label_C156:;
    /* $C156: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x05; g_cpu.C=(g_cpu.X>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_C158:;
    /* $C158: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_C164;
label_C15A:;
    /* $C15A: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C15B:;
    /* $C15B: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE9) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C15D:;
    /* $C15D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3F; FLAG_NZ(g_cpu.A);
label_C15F:;
    /* $C15F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x2E; g_cpu.C=(g_cpu.A>=0x2E)?1:0; FLAG_NZ(r&0xFF); }
label_C161:;
    /* $C161: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C164;
label_C163:;
    /* $C163: 60 */ maybe_trigger_vblank(6);
    return;
label_C164:; /* CheckRightBounds */
    /* $C164: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071D); FLAG_NZ(g_cpu.A);
label_C167:;
    /* $C167: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C168:;
    /* $C168: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x30 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x30); g_cpu.A=r&0xFF; }
label_C16A:;
    /* $C16A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF0; FLAG_NZ(g_cpu.A);
label_C16C:;
    /* $C16C: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_C16E:;
    /* $C16E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071B); FLAG_NZ(g_cpu.A);
label_C171:;
    /* $C171: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_C173:;
    /* $C173: 85 */ maybe_trigger_vblank(3); nes_write(0x06, g_cpu.A);
label_C175:;
    /* $C175: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0739); FLAG_NZ(g_cpu.Y);
label_C178:;
    /* $C178: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C179:;
    /* $C179: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE9) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C17B:;
    /* $C17B: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_C17C:;
    /* $C17C: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_C189;
label_C17E:;
    /* $C17E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x073B); FLAG_NZ(g_cpu.A);
label_C181:;
    /* $C181: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C189;
label_C183:;
    /* $C183: EE */ maybe_trigger_vblank(6); { uint16_t a=0x073B; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C186:;
    /* $C186: EE */ maybe_trigger_vblank(6); { uint16_t a=0x073A; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C189:; /* CheckPageCtrlRow */
    /* $C189: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C18A:;
    /* $C18A: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE9) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C18C:;
    /* $C18C: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_C18E:;
    /* $C18E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0F; g_cpu.C=(g_cpu.A>=0x0F)?1:0; FLAG_NZ(r&0xFF); }
label_C190:;
    /* $C190: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C1AB;
label_C192:;
    /* $C192: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x073B); FLAG_NZ(g_cpu.A);
label_C195:;
    /* $C195: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C1AB;
label_C197:;
    /* $C197: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C198:;
    /* $C198: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE9) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C19A:;
    /* $C19A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3F; FLAG_NZ(g_cpu.A);
label_C19C:;
    /* $C19C: 8D */ maybe_trigger_vblank(4); nes_write(0x073A, g_cpu.A);
label_C19F:;
    /* $C19F: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0739; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C1A2:;
    /* $C1A2: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0739; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C1A5:;
    /* $C1A5: EE */ maybe_trigger_vblank(6); { uint16_t a=0x073B; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C1A8:;
    /* $C1A8: 4C */ maybe_trigger_vblank(3); goto label_C0CC;
label_C1AB:; /* PositionEnemyObj */
    /* $C1AB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x073A); FLAG_NZ(g_cpu.A);
label_C1AE:;
    /* $C1AE: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_C1B0:;
    /* $C1B0: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE9) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C1B2:;
    /* $C1B2: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF0; FLAG_NZ(g_cpu.A);
label_C1B4:;
    /* $C1B4: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_C1B6:;
    /* $C1B6: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x071D); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_C1B9:;
    /* $C1B9: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C1BB:;
    /* $C1BB: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x071B); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C1BE:;
    /* $C1BE: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_C1CB;
label_C1C0:;
    /* $C1C0: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE9) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C1C2:;
    /* $C1C2: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_C1C4:;
    /* $C1C4: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0E; g_cpu.C=(g_cpu.A>=0x0E)?1:0; FLAG_NZ(r&0xFF); }
label_C1C6:;
    /* $C1C6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C231;
label_C1C8:;
    /* $C1C8: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC250); return;
label_C1CB:; /* CheckRightExtBounds */
    /* $C1CB: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x07); FLAG_NZ(g_cpu.A);
label_C1CD:;
    /* $C1CD: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x87 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_C1CF:;
    /* $C1CF: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x06); FLAG_NZ(g_cpu.A);
label_C1D1:;
    /* $C1D1: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x6E + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C1D3:;
    /* $C1D3: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_C216;
label_C1D5:;
    /* $C1D5: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C1D7:;
    /* $C1D7: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_C1D9:;
    /* $C1D9: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE9) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C1DB:;
    /* $C1DB: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_C1DC:;
    /* $C1DC: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_C1DD:;
    /* $C1DD: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_C1DE:;
    /* $C1DE: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_C1DF:;
    /* $C1DF: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_C1E1:;
    /* $C1E1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xE0; g_cpu.C=(g_cpu.A>=0xE0)?1:0; FLAG_NZ(r&0xFF); }
label_C1E3:;
    /* $C1E3: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C231;
label_C1E5:;
    /* $C1E5: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C1E6:;
    /* $C1E6: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE9) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C1E8:;
    /* $C1E8: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_C1EA:;
    /* $C1EA: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C1F1;
label_C1EC:;
    /* $C1EC: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06CC); FLAG_NZ(g_cpu.A);
label_C1EF:;
    /* $C1EF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C25E;
label_C1F1:; /* CheckForEnemyGroup */
    /* $C1F1: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE9) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C1F3:;
    /* $C1F3: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3F; FLAG_NZ(g_cpu.A);
label_C1F5:;
    /* $C1F5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x37; g_cpu.C=(g_cpu.A>=0x37)?1:0; FLAG_NZ(r&0xFF); }
label_C1F7:;
    /* $C1F7: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_C1FD;
label_C1F9:;
    /* $C1F9: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x3F; g_cpu.C=(g_cpu.A>=0x3F)?1:0; FLAG_NZ(r&0xFF); }
label_C1FB:;
    /* $C1FB: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_C22E;
label_C1FD:; /* BuzzyBeetleMutate */
    /* $C1FD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_C1FF:;
    /* $C1FF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C208;
label_C201:;
    /* $C201: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x076A); FLAG_NZ(g_cpu.Y);
label_C204:;
    /* $C204: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C208;
label_C206:;
    /* $C206: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_C208:; /* StrID */
    /* $C208: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_C20A:;
    /* $C20A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C20C:;
    /* $C20C: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_C20E:;
    /* $C20E: 20 */ maybe_trigger_vblank(6); call_by_address(0xC226);
label_C211:;
    /* $C211: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C213:;
    /* $C213: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C25E;
label_C215:;
    /* $C215: 60 */ maybe_trigger_vblank(6);
    return;
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
label_C22E:; /* DoGroup */
    /* $C22E: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC71B); return;
label_C231:; /* ParseRow0e */
    /* $C231: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C232:;
    /* $C232: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C233:;
    /* $C233: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE9) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C235:;
    /* $C235: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_C236:;
    /* $C236: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_C237:;
    /* $C237: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_C238:;
    /* $C238: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_C239:;
    /* $C239: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_C23A:;
    /* $C23A: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x075F); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_C23D:;
    /* $C23D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C24D;
label_C23F:;
    /* $C23F: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C240:;
    /* $C240: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE9) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C242:;
    /* $C242: 8D */ maybe_trigger_vblank(4); nes_write(0x0750, g_cpu.A);
label_C245:;
    /* $C245: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C246:;
    /* $C246: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xE9) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C248:;
    /* $C248: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x1F; FLAG_NZ(g_cpu.A);
label_C24A:;
    /* $C24A: 8D */ maybe_trigger_vblank(4); nes_write(0x0751, g_cpu.A);
label_C24D:; /* NotUse */
    /* $C24D: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC25B); return;
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

void EnemyEngine::checkpoint_enemy_id_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C2F0;
    }
label_C26C:; /* CheckpointEnemyID */
    /* $C26C: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C26E:;
    /* $C26E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_C270:;
    /* $C270: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_C27F;
label_C272:;
    /* $C272: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C273:;
    /* $C273: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C275:;
    /* $C275: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_C277:;
    /* $C277: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_C279:;
    /* $C279: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C27B:;
    /* $C27B: 9D */ maybe_trigger_vblank(5); nes_write((0x03D8 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C27E:;
    /* $C27E: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_C27F:; /* InitEnemyRoutines */
    /* $C27F: 20 */ maybe_trigger_vblank(6); /* inline_dispatch $8E04: 55 entries (bank=-1) */
switch(g_cpu.A) {
  case 0: call_by_address(0xC30E); return;
  case 1: call_by_address(0xC30E); return;
  case 2: call_by_address(0xC30E); return;
  case 3: call_by_address(0xC31E); return;
  case 4: call_by_address(0xC2F0); return;
  case 5: call_by_address(0xC328); return;
  case 6: call_by_address(0xC2F1); return;
  case 7: call_by_address(0xC342); return;
  case 8: call_by_address(0xC36B); return;
  case 9: call_by_address(0xC2F0); return;
  case 10: call_by_address(0xC375); return;
  case 11: call_by_address(0xC375); return;
  case 12: call_by_address(0xC2F7); return;
  case 13: call_by_address(0xC787); return;
  case 14: call_by_address(0xC7D1); return;
  case 15: call_by_address(0xC34A); return;
  case 16: call_by_address(0xC33D); return;
  case 17: call_by_address(0xC385); return;
  case 18: call_by_address(0xC7A0); return;
  case 19: call_by_address(0xC2F0); return;
  case 20: call_by_address(0xC7A0); return;
  case 21: call_by_address(0xC7A0); return;
  case 22: call_by_address(0xC7A0); return;
  case 23: call_by_address(0xC7A0); return;
  case 24: call_by_address(0xC7B8); return;
  case 25: call_by_address(0xC2F0); return;
  case 26: call_by_address(0xC2F0); return;
  case 27: call_by_address(0xC45C); return;
  case 28: call_by_address(0xC45C); return;
  case 29: call_by_address(0xC45C); return;
  case 30: call_by_address(0xC45C); return;
  case 31: call_by_address(0xC459); return;
  case 32: call_by_address(0xC2F0); return;
  case 33: call_by_address(0xC2F0); return;
  case 34: call_by_address(0xC2F0); return;
  case 35: call_by_address(0xC2F0); return;
  case 36: call_by_address(0xC7DF); return;
  case 37: call_by_address(0xC812); return;
  case 38: call_by_address(0xC83F); return;
  case 39: call_by_address(0xC845); return;
  case 40: call_by_address(0xC80B); return;
  case 41: call_by_address(0xC803); return;
  case 42: call_by_address(0xC80B); return;
  case 43: call_by_address(0xC84B); return;
  case 44: call_by_address(0xC857); return;
  case 45: call_by_address(0xC549); return;
  case 46: call_by_address(0xBC60); return;
  case 47: call_by_address(0xB91E); return;
  case 48: call_by_address(0xC2F0); return;
  case 49: call_by_address(0xC2F0); return;
  case 50: call_by_address(0xC2F0); return;
  case 51: call_by_address(0xC2F0); return;
  case 52: call_by_address(0xC2F0); return;
  case 53: call_by_address(0xC307); return;
  case 54: call_by_address(0xC881); return;
  default: nes_log_inline_miss(0xC27F, g_cpu.A); return;
}
label_C2F0:; /* NoInitCode */
    /* $C2F0: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::init_podoboo_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C304;
        case 2: goto label_C302;
        case 3: goto label_C301;
    }
label_C2F7:; /* InitPodoboo */
    /* $C2F7: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_C2F9:;
    /* $C2F9: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_C2FB:;
    /* $C2FB: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_C2FD:;
    /* $C2FD: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_C2FE:;
    /* $C2FE: 9D */ maybe_trigger_vblank(5); nes_write((0x0796 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C301:;
    /* $C301: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_C302:;
    /* $C302: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_C304:;
    /* $C304: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC346); return;
}

void EnemyEngine::init_retainer_obj_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C30B;
    }
label_C307:; /* InitRetainerObj */
    /* $C307: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xB8; FLAG_NZ(g_cpu.A);
label_C309:;
    /* $C309: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_C30B:;
    /* $C30B: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::init_red_koopa_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C321;
    }
label_C31E:; /* InitRedKoopa */
    /* $C31E: 20 */ maybe_trigger_vblank(6); call_by_address(0xC30E);
label_C321:;
    /* $C321: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C323:;
    /* $C323: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_C325:;
    /* $C325: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::init_bloober_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C365;
        case 2: goto label_C367;
    }
label_C342:; /* InitBloober */
    /* $C342: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C344:;
    /* $C344: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_C346:; /* SmallBBox */
    /* $C346: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x09; FLAG_NZ(g_cpu.A);
label_C348:;
    /* $C348: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C35C;
label_C34A:; /* InitRedPTroopa */
    /* $C34A: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x30; FLAG_NZ(g_cpu.Y);
label_C34C:;
    /* $C34C: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C34E:;
    /* $C34E: 9D */ maybe_trigger_vblank(5); nes_write((0x0401 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C351:;
    /* $C351: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_C355;
label_C353:;
    /* $C353: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xE0; FLAG_NZ(g_cpu.Y);
label_C355:; /* GetCent */
    /* $C355: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_C356:;
    /* $C356: 75 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xCF + g_cpu.X) & 0xFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C358:;
    /* $C358: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_C35A:; /* TallBBox */
    /* $C35A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_C35C:; /* SetBBox */
    /* $C35C: 9D */ maybe_trigger_vblank(5); nes_write((0x049A + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C35F:;
    /* $C35F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_C361:;
    /* $C361: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
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

void EnemyEngine::lakitu_and_spiny_handler_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C44E;
        case 2: goto label_C40A;
        case 3: goto label_C3D1;
        case 4: goto label_C40F;
        case 5: goto label_C420;
        case 6: goto label_C3CA;
        case 7: goto label_C3C4;
        case 8: goto label_C424;
        case 9: goto label_C402;
        case 10: goto label_C3B9;
        case 11: goto label_C416;
        case 12: goto label_C40D;
        case 13: goto label_C412;
        case 14: goto label_C442;
        case 15: goto label_C3B4;
        case 16: goto label_C3C1;
        case 17: goto label_C3FD;
    }
label_C3A4:; /* LakituAndSpinyHandler */
    /* $C3A4: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x078F); FLAG_NZ(g_cpu.A);
label_C3A7:;
    /* $C3A7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C3E5;
label_C3A9:;
    /* $C3A9: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x05; g_cpu.C=(g_cpu.X>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_C3AB:;
    /* $C3AB: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_C3E5;
label_C3AD:;
    /* $C3AD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_C3AF:;
    /* $C3AF: 8D */ maybe_trigger_vblank(4); nes_write(0x078F, g_cpu.A);
label_C3B2:;
    /* $C3B2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x04; FLAG_NZ(g_cpu.Y);
label_C3B4:; /* ChkLak */
    /* $C3B4: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0016 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C3B7:;
    /* $C3B7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_C3B9:;
    /* $C3B9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C3E6;
label_C3BB:;
    /* $C3BB: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C3BC:;
    /* $C3BC: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C3B4;
    }
label_C3BE:;
    /* $C3BE: EE */ maybe_trigger_vblank(6); { uint16_t a=0x06D1; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C3C1:;
    /* $C3C1: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06D1); FLAG_NZ(g_cpu.A);
label_C3C4:;
    /* $C3C4: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_C3C6:;
    /* $C3C6: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_C3E5;
label_C3C8:;
    /* $C3C8: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x04; FLAG_NZ(g_cpu.X);
label_C3CA:; /* ChkNoEn */
    /* $C3CA: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C3CC:;
    /* $C3CC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C3D3;
label_C3CE:;
    /* $C3CE: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_C3CF:;
    /* $C3CF: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C3CA;
    }
label_C3D1:;
    /* $C3D1: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_C3E3;
label_C3D3:; /* CreateL */
    /* $C3D3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C3D5:;
    /* $C3D5: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_C3D7:;
    /* $C3D7: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x11; FLAG_NZ(g_cpu.A);
label_C3D9:;
    /* $C3D9: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_C3DB:;
    /* $C3DB: 20 */ maybe_trigger_vblank(6); call_by_address(0xC38A);
label_C3DE:;
    /* $C3DE: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_C3E0:;
    /* $C3E0: 20 */ maybe_trigger_vblank(6); call_by_address(0xC5D8);
label_C3E3:; /* RetEOfs */
    /* $C3E3: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_C3E5:; /* ExLSHand */
    /* $C3E5: 60 */ maybe_trigger_vblank(6);
    return;
label_C3E6:; /* CreateSpiny */
    /* $C3E6: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_C3E8:;
    /* $C3E8: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x2C; g_cpu.C=(g_cpu.A>=0x2C)?1:0; FLAG_NZ(r&0xFF); }
label_C3EA:;
    /* $C3EA: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C3E5;
    }
label_C3EC:;
    /* $C3EC: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x001E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C3EF:;
    /* $C3EF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C3E5;
    }
label_C3F1:;
    /* $C3F1: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x006E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C3F4:;
    /* $C3F4: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_C3F6:;
    /* $C3F6: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0087 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C3F9:;
    /* $C3F9: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_C3FB:;
    /* $C3FB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C3FD:;
    /* $C3FD: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_C3FF:;
    /* $C3FF: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x00CF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C402:;
    /* $C402: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C403:;
    /* $C403: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x08; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C405:;
    /* $C405: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_C407:;
    /* $C407: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A7 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C40A:;
    /* $C40A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_C40C:;
    /* $C40C: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C40D:;
    /* $C40D: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x02; FLAG_NZ(g_cpu.X);
label_C40F:; /* DifLoop */
    /* $C40F: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC398 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C412:;
    /* $C412: 95 */ maybe_trigger_vblank(4); nes_write((0x01 + g_cpu.X) & 0xFF, g_cpu.A);
label_C414:;
    /* $C414: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C415:;
    /* $C415: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C416:;
    /* $C416: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C417:;
    /* $C417: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C418:;
    /* $C418: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_C419:;
    /* $C419: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C40F;
    }
label_C41B:;
    /* $C41B: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_C41D:;
    /* $C41D: 20 */ maybe_trigger_vblank(6); call_by_address(0xCF6C);
label_C420:;
    /* $C420: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x57); FLAG_NZ(g_cpu.Y);
label_C422:;
    /* $C422: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_C424:;
    /* $C424: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_C434;
label_C426:;
    /* $C426: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C427:;
    /* $C427: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C42A:;
    /* $C42A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_C42C:;
    /* $C42C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C433;
label_C42E:;
    /* $C42E: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_C42F:;
    /* $C42F: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_C431:;
    /* $C431: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C432:;
    /* $C432: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C433:; /* UsePosv */
    /* $C433: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_C434:; /* SetSpSpd */
    /* $C434: 20 */ maybe_trigger_vblank(6); call_by_address(0xC346);
label_C437:;
    /* $C437: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_C439:;
    /* $C439: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_C43B:;
    /* $C43B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_C43D:;
    /* $C43D: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_C440;
label_C43F:;
    /* $C43F: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C440:; /* SpinyRte */
    /* $C440: 94 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.Y);
label_C442:;
    /* $C442: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFD; FLAG_NZ(g_cpu.A);
label_C444:;
    /* $C444: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_C446:;
    /* $C446: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C448:;
    /* $C448: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_C44A:;
    /* $C44A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_C44C:;
    /* $C44C: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_C44E:; /* ChpChpEx */
    /* $C44E: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::init_long_firebar_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C47D;
    }
label_C459:; /* InitLongFirebar */
    /* $C459: 20 */ maybe_trigger_vblank(6); call_by_address(0xC575);
label_C45C:; /* InitShortFirebar */
    /* $C45C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C45E:;
    /* $C45E: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_C460:;
    /* $C460: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C462:;
    /* $C462: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C463:;
    /* $C463: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x1B; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C465:;
    /* $C465: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C466:;
    /* $C466: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC44F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C469:;
    /* $C469: 9D */ maybe_trigger_vblank(5); nes_write((0x0388 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C46C:;
    /* $C46C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC454 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C46F:;
    /* $C46F: 95 */ maybe_trigger_vblank(4); nes_write((0x34 + g_cpu.X) & 0xFF, g_cpu.A);
label_C471:;
    /* $C471: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C473:;
    /* $C473: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C474:;
    /* $C474: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_C476:;
    /* $C476: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_C478:;
    /* $C478: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C47A:;
    /* $C47A: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C47B:;
    /* $C47B: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_C47D:;
    /* $C47D: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_C47F:;
    /* $C47F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C481:;
    /* $C481: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_C483:;
    /* $C483: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_C485:;
    /* $C485: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC7D9); return;
}

void EnemyEngine::init_flying_cheep_cheep_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C511;
        case 2: goto label_C500;
        case 3: goto label_C504;
        case 4: goto label_C4AD;
        case 5: goto label_C4FC;
        case 6: goto label_C4FD;
        case 7: goto label_C4CA;
        case 8: goto label_C502;
        case 9: goto label_C508;
        case 10: goto label_C4B0;
        case 11: goto label_C521;
        case 12: goto label_C4D1;
        case 13: goto label_C51F;
        case 14: goto label_C506;
        case 15: goto label_C50C;
        case 16: goto label_C533;
        case 17: goto label_C516;
        case 18: goto label_C518;
    }
label_C4A8:; /* InitFlyingCheepCheep */
    /* $C4A8: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x078F); FLAG_NZ(g_cpu.A);
label_C4AB:;
    /* $C4AB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xC44E); return; }
label_C4AD:;
    /* $C4AD: 20 */ maybe_trigger_vblank(6); call_by_address(0xC346);
label_C4B0:;
    /* $C4B0: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C4B3:;
    /* $C4B3: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_C4B5:;
    /* $C4B5: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C4B6:;
    /* $C4B6: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC4A4 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C4B9:;
    /* $C4B9: 8D */ maybe_trigger_vblank(4); nes_write(0x078F, g_cpu.A);
label_C4BC:;
    /* $C4BC: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x03; FLAG_NZ(g_cpu.Y);
label_C4BE:;
    /* $C4BE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06CC); FLAG_NZ(g_cpu.A);
label_C4C1:;
    /* $C4C1: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C4C4;
label_C4C3:;
    /* $C4C3: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C4C4:; /* MaxCC */
    /* $C4C4: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_C4C6:;
    /* $C4C6: E4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); int r=g_cpu.X-m; g_cpu.C=(g_cpu.X>=m)?1:0; FLAG_NZ(r&0xFF); }
label_C4C8:;
    /* $C4C8: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xC44E); return; }
label_C4CA:;
    /* $C4CA: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A7 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C4CD:;
    /* $C4CD: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_C4CF:;
    /* $C4CF: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_C4D1:;
    /* $C4D1: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_C4D3:;
    /* $C4D3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFB; FLAG_NZ(g_cpu.A);
label_C4D5:;
    /* $C4D5: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_C4D7:;
    /* $C4D7: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C4D9:;
    /* $C4D9: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x57); FLAG_NZ(g_cpu.Y);
label_C4DB:;
    /* $C4DB: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C4E4;
label_C4DD:;
    /* $C4DD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_C4DF:;
    /* $C4DF: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x19; g_cpu.C=(g_cpu.Y>=0x19)?1:0; FLAG_NZ(r&0xFF); }
label_C4E1:;
    /* $C4E1: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_C4E4;
label_C4E3:;
    /* $C4E3: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_C4E4:; /* GSeed */
    /* $C4E4: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_C4E5:;
    /* $C4E5: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C4E6:;
    /* $C4E6: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C4E8:;
    /* $C4E8: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_C4EA:;
    /* $C4EA: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C4ED:;
    /* $C4ED: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_C4EF:;
    /* $C4EF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C4F8;
label_C4F1:;
    /* $C4F1: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A9 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C4F4:;
    /* $C4F4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_C4F6:;
    /* $C4F6: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_C4F8:; /* RSeed */
    /* $C4F8: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_C4F9:;
    /* $C4F9: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C4FA:;
    /* $C4FA: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x01); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C4FC:;
    /* $C4FC: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C4FD:;
    /* $C4FD: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC498 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C500:;
    /* $C500: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_C502:;
    /* $C502: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C504:;
    /* $C504: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_C506:;
    /* $C506: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x57); FLAG_NZ(g_cpu.A);
label_C508:;
    /* $C508: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C51C;
label_C50A:;
    /* $C50A: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x00); FLAG_NZ(g_cpu.Y);
label_C50C:;
    /* $C50C: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_C50D:;
    /* $C50D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_C50F:;
    /* $C50F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C51C;
label_C511:;
    /* $C511: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C513:;
    /* $C513: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_C515:;
    /* $C515: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C516:;
    /* $C516: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_C518:;
    /* $C518: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_C51A:;
    /* $C51A: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0x46 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C51C:; /* D2XPos1 */
    /* $C51C: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_C51D:;
    /* $C51D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_C51F:;
    /* $C51F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C530;
label_C521:;
    /* $C521: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x86); FLAG_NZ(g_cpu.A);
label_C523:;
    /* $C523: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C524:;
    /* $C524: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xC488 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C527:;
    /* $C527: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_C529:;
    /* $C529: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x6D); FLAG_NZ(g_cpu.A);
label_C52B:;
    /* $C52B: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_C52D:;
    /* $C52D: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC53C); return;
label_C530:; /* D2XPos2 */
    /* $C530: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x86); FLAG_NZ(g_cpu.A);
label_C532:;
    /* $C532: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C533:;
    /* $C533: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xC488 + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C536:;
    /* $C536: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_C538:;
    /* $C538: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x6D); FLAG_NZ(g_cpu.A);
label_C53A:;
    /* $C53A: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C53C:; /* FinCCSt */
    /* $C53C: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_C53E:;
    /* $C53E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C540:;
    /* $C540: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_C542:;
    /* $C542: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_C544:;
    /* $C544: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_C546:;
    /* $C546: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_C548:;
    /* $C548: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::init_bowser_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C56D;
        case 2: goto label_C54C;
        case 3: goto label_C563;
    }
label_C549:; /* InitBowser */
    /* $C549: 20 */ maybe_trigger_vblank(6); call_by_address(0xC575);
label_C54C:;
    /* $C54C: 8E */ maybe_trigger_vblank(4); nes_write(0x0368, g_cpu.X);
label_C54F:;
    /* $C54F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C551:;
    /* $C551: 8D */ maybe_trigger_vblank(4); nes_write(0x0363, g_cpu.A);
label_C554:;
    /* $C554: 8D */ maybe_trigger_vblank(4); nes_write(0x0369, g_cpu.A);
label_C557:;
    /* $C557: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C559:;
    /* $C559: 8D */ maybe_trigger_vblank(4); nes_write(0x0366, g_cpu.A);
label_C55C:;
    /* $C55C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xDF; FLAG_NZ(g_cpu.A);
label_C55E:;
    /* $C55E: 8D */ maybe_trigger_vblank(4); nes_write(0x0790, g_cpu.A);
label_C561:;
    /* $C561: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_C563:;
    /* $C563: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_C565:;
    /* $C565: 8D */ maybe_trigger_vblank(4); nes_write(0x0364, g_cpu.A);
label_C568:;
    /* $C568: 9D */ maybe_trigger_vblank(5); nes_write((0x078A + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C56B:;
    /* $C56B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_C56D:;
    /* $C56D: 8D */ maybe_trigger_vblank(4); nes_write(0x0483, g_cpu.A);
label_C570:;
    /* $C570: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_C571:;
    /* $C571: 8D */ maybe_trigger_vblank(4); nes_write(0x0365, g_cpu.A);
label_C574:;
    /* $C574: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::duplicate_enemy_obj_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C59C;
        case 2: goto label_C588;
        case 3: goto label_C586;
    }
label_C575:; /* DuplicateEnemyObj */
    /* $C575: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xFF; FLAG_NZ(g_cpu.Y);
label_C577:; /* FSLoop */
    /* $C577: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C578:;
    /* $C578: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x000F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C57B:;
    /* $C57B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C577;
    }
label_C57D:;
    /* $C57D: 8C */ maybe_trigger_vblank(4); nes_write(0x06CF, g_cpu.Y);
label_C580:;
    /* $C580: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_C581:;
    /* $C581: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x80; FLAG_NZ(g_cpu.A);
label_C583:;
    /* $C583: 99 */ maybe_trigger_vblank(5); nes_write((0x000F + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_C586:;
    /* $C586: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C588:;
    /* $C588: 99 */ maybe_trigger_vblank(5); nes_write((0x006E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_C58B:;
    /* $C58B: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C58D:;
    /* $C58D: 99 */ maybe_trigger_vblank(5); nes_write((0x0087 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_C590:;
    /* $C590: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C592:;
    /* $C592: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_C594:;
    /* $C594: 99 */ maybe_trigger_vblank(5); nes_write((0x00B6 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_C597:;
    /* $C597: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C599:;
    /* $C599: 99 */ maybe_trigger_vblank(5); nes_write((0x00CF + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_C59C:; /* FlmEx */
    /* $C59C: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::init_bowser_flame_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C5CF;
        case 2: goto label_C604;
        case 3: goto label_C5C9;
        case 4: goto label_C606;
        case 5: goto label_C609;
        case 6: goto label_C5C6;
        case 7: goto label_C5C7;
        case 8: goto label_C5BE;
        case 9: goto label_C613;
        case 10: goto label_C614;
        case 11: goto label_C5AD;
        case 12: goto label_C624;
    }
label_C5A3:; /* InitBowserFlame */
    /* $C5A3: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x078F); FLAG_NZ(g_cpu.A);
label_C5A6:;
    /* $C5A6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xC59C); return; }
label_C5A8:;
    /* $C5A8: 9D */ maybe_trigger_vblank(5); nes_write((0x0434 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C5AB:;
    /* $C5AB: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xFD); FLAG_NZ(g_cpu.A);
label_C5AD:;
    /* $C5AD: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x02; FLAG_NZ(g_cpu.A);
label_C5AF:;
    /* $C5AF: 85 */ maybe_trigger_vblank(3); nes_write(0xFD, g_cpu.A);
label_C5B1:;
    /* $C5B1: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0368); FLAG_NZ(g_cpu.Y);
label_C5B4:;
    /* $C5B4: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0016 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C5B7:;
    /* $C5B7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x2D; g_cpu.C=(g_cpu.A>=0x2D)?1:0; FLAG_NZ(r&0xFF); }
label_C5B9:;
    /* $C5B9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C5EC;
label_C5BB:;
    /* $C5BB: 20 */ maybe_trigger_vblank(6); call_by_address(0xD1D9);
label_C5BE:;
    /* $C5BE: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C5BF:;
    /* $C5BF: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x20 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x20); g_cpu.A=r&0xFF; }
label_C5C1:;
    /* $C5C1: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06CC); FLAG_NZ(g_cpu.Y);
label_C5C4:;
    /* $C5C4: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C5C9;
label_C5C6:;
    /* $C5C6: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C5C7:;
    /* $C5C7: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x10; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C5C9:; /* SetFrT */
    /* $C5C9: 8D */ maybe_trigger_vblank(4); nes_write(0x078F, g_cpu.A);
label_C5CC:;
    /* $C5CC: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A7 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C5CF:;
    /* $C5CF: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_C5D1:;
    /* $C5D1: 9D */ maybe_trigger_vblank(5); nes_write((0x0417 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C5D4:;
    /* $C5D4: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C5D5:;
    /* $C5D5: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC59D + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C5D8:; /* PutAtRightExtent */
    /* $C5D8: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_C5DA:;
    /* $C5DA: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071D); FLAG_NZ(g_cpu.A);
label_C5DD:;
    /* $C5DD: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C5DE:;
    /* $C5DE: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x20 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x20); g_cpu.A=r&0xFF; }
label_C5E0:;
    /* $C5E0: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_C5E2:;
    /* $C5E2: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071B); FLAG_NZ(g_cpu.A);
label_C5E5:;
    /* $C5E5: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_C5E7:;
    /* $C5E7: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_C5E9:;
    /* $C5E9: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC61F); return;
label_C5EC:; /* SpawnFromMouth */
    /* $C5EC: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0087 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C5EF:;
    /* $C5EF: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C5F0:;
    /* $C5F0: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x0E; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C5F2:;
    /* $C5F2: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_C5F4:;
    /* $C5F4: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x006E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C5F7:;
    /* $C5F7: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_C5F9:;
    /* $C5F9: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x00CF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C5FC:;
    /* $C5FC: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C5FD:;
    /* $C5FD: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_C5FF:;
    /* $C5FF: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_C601:;
    /* $C601: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A7 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C604:;
    /* $C604: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_C606:;
    /* $C606: 9D */ maybe_trigger_vblank(5); nes_write((0x0417 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C609:;
    /* $C609: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C60A:;
    /* $C60A: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC59D + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C60D:;
    /* $C60D: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_C60F:;
    /* $C60F: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xCF + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_C611:;
    /* $C611: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_C614;
label_C613:;
    /* $C613: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C614:; /* SetMF */
    /* $C614: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC5A1 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C617:;
    /* $C617: 9D */ maybe_trigger_vblank(5); nes_write((0x0434 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C61A:;
    /* $C61A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C61C:;
    /* $C61C: 8D */ maybe_trigger_vblank(4); nes_write(0x06CB, g_cpu.A);
label_C61F:; /* FinishFlame */
    /* $C61F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_C621:;
    /* $C621: 9D */ maybe_trigger_vblank(5); nes_write((0x049A + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C624:;
    /* $C624: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C626:;
    /* $C626: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_C628:;
    /* $C628: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_C62A:;
    /* $C62A: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_C62B:;
    /* $C62B: 9D */ maybe_trigger_vblank(5); nes_write((0x0401 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C62E:;
    /* $C62E: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_C630:;
    /* $C630: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::bullet_bill_cheep_cheep_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C6D7;
        case 2: goto label_C6C8;
        case 3: goto label_C6B1;
        case 4: goto label_C6EC;
        case 5: goto label_C6C3;
        case 6: goto label_C74C;
        case 7: goto label_C75D;
        case 8: goto label_C700;
        case 9: goto label_C725;
        case 10: goto label_C741;
        case 11: goto label_C738;
        case 12: goto label_C720;
        case 13: goto label_C77A;
        case 14: goto label_C74D;
        case 15: goto label_C772;
        case 16: goto label_C734;
        case 17: goto label_C6CE;
        case 18: goto label_C6FF;
        case 19: goto label_C750;
    }
label_C69C:; /* BulletBillCheepCheep */
    /* $C69C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x078F); FLAG_NZ(g_cpu.A);
label_C69F:;
    /* $C69F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C710;
label_C6A1:;
    /* $C6A1: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x074E); FLAG_NZ(g_cpu.A);
label_C6A4:;
    /* $C6A4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C6FD;
label_C6A6:;
    /* $C6A6: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x03; g_cpu.C=(g_cpu.X>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_C6A8:;
    /* $C6A8: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_C710;
label_C6AA:;
    /* $C6AA: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_C6AC:;
    /* $C6AC: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A7 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C6AF:;
    /* $C6AF: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xAA; g_cpu.C=(g_cpu.A>=0xAA)?1:0; FLAG_NZ(r&0xFF); }
label_C6B1:;
    /* $C6B1: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_C6B4;
label_C6B3:;
    /* $C6B3: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C6B4:; /* ChkW2 */
    /* $C6B4: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x075F); FLAG_NZ(g_cpu.A);
label_C6B7:;
    /* $C6B7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_C6B9:;
    /* $C6B9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C6BC;
label_C6BB:;
    /* $C6BB: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C6BC:; /* Get17ID */
    /* $C6BC: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_C6BD:;
    /* $C6BD: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_C6BF:;
    /* $C6BF: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C6C0:;
    /* $C6C0: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC69A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C6C3:; /* Set17ID */
    /* $C6C3: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_C6C5:;
    /* $C6C5: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06DD); FLAG_NZ(g_cpu.A);
label_C6C8:;
    /* $C6C8: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xFF; g_cpu.C=(g_cpu.A>=0xFF)?1:0; FLAG_NZ(r&0xFF); }
label_C6CA:;
    /* $C6CA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C6D1;
label_C6CC:;
    /* $C6CC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C6CE:;
    /* $C6CE: 8D */ maybe_trigger_vblank(4); nes_write(0x06DD, g_cpu.A);
label_C6D1:; /* GetRBit */
    /* $C6D1: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A7 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C6D4:;
    /* $C6D4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_C6D6:; /* ChkRBit */
    /* $C6D6: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C6D7:;
    /* $C6D7: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC68A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C6DA:;
    /* $C6DA: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x06DD); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_C6DD:;
    /* $C6DD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C6E6;
label_C6DF:;
    /* $C6DF: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C6E0:;
    /* $C6E0: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_C6E1:;
    /* $C6E1: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_C6E3:;
    /* $C6E3: 4C */ maybe_trigger_vblank(3); goto label_C6D6;
label_C6E6:; /* AddFBit */
    /* $C6E6: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x06DD); FLAG_NZ(g_cpu.A);
label_C6E9:;
    /* $C6E9: 8D */ maybe_trigger_vblank(4); nes_write(0x06DD, g_cpu.A);
label_C6EC:;
    /* $C6EC: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC692 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C6EF:;
    /* $C6EF: 20 */ maybe_trigger_vblank(6); call_by_address(0xC5D8);
label_C6F2:;
    /* $C6F2: 9D */ maybe_trigger_vblank(5); nes_write((0x0417 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C6F5:;
    /* $C6F5: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_C6F7:;
    /* $C6F7: 8D */ maybe_trigger_vblank(4); nes_write(0x078F, g_cpu.A);
label_C6FA:;
    /* $C6FA: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC26C); return;
label_C6FD:; /* DoBulletBills */
    /* $C6FD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xFF; FLAG_NZ(g_cpu.Y);
label_C6FF:; /* BB_SLoop */
    /* $C6FF: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C700:;
    /* $C700: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x05; g_cpu.C=(g_cpu.Y>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_C702:;
    /* $C702: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_C711;
label_C704:;
    /* $C704: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x000F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C707:;
    /* $C707: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C6FF;
    }
label_C709:;
    /* $C709: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0016 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C70C:;
    /* $C70C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_C70E:;
    /* $C70E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C6FF;
    }
label_C710:; /* ExF17 */
    /* $C710: 60 */ maybe_trigger_vblank(6);
    return;
label_C711:; /* FireBulletBill */
    /* $C711: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xFE); FLAG_NZ(g_cpu.A);
label_C713:;
    /* $C713: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x08; FLAG_NZ(g_cpu.A);
label_C715:;
    /* $C715: 85 */ maybe_trigger_vblank(3); nes_write(0xFE, g_cpu.A);
label_C717:;
    /* $C717: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_C719:;
    /* $C719: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C6C3;
    }
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

void EnemyEngine::init_piranha_plant_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C78C;
    }
label_C787:; /* InitPiranhaPlant */
    /* $C787: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C789:;
    /* $C789: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_C78B:;
    /* $C78B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_C78C:;
    /* $C78C: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_C78E:;
    /* $C78E: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_C790:;
    /* $C790: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C792:;
    /* $C792: 9D */ maybe_trigger_vblank(5); nes_write((0x0434 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C795:;
    /* $C795: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C796:;
    /* $C796: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x18; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C798:;
    /* $C798: 9D */ maybe_trigger_vblank(5); nes_write((0x0417 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C79B:;
    /* $C79B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x09; FLAG_NZ(g_cpu.A);
label_C79D:;
    /* $C79D: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC7DB); return;
}

void EnemyEngine::init_enemy_frenzy_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C7C9;
    }
label_C7A0:; /* InitEnemyFrenzy */
    /* $C7A0: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C7A2:;
    /* $C7A2: 8D */ maybe_trigger_vblank(4); nes_write(0x06CB, g_cpu.A);
label_C7A5:;
    /* $C7A5: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C7A6:;
    /* $C7A6: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x12; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C7A8:;
    /* $C7A8: 20 */ maybe_trigger_vblank(6); /* inline_dispatch $8E04: 8 entries (bank=-1) */
switch(g_cpu.A) {
  case 0: call_by_address(0xC3A4); return;
  case 1: call_by_address(0xC7B7); return;
  case 2: call_by_address(0xC4A8); return;
  case 3: call_by_address(0xC5A3); return;
  case 4: call_by_address(0xC63D); return;
  case 5: call_by_address(0xC69C); return;
  case 6: call_by_address(0xA060); return;
  case 7: call_by_address(0xB905); return;
  default: nes_log_inline_miss(0xC7A8, g_cpu.A); return;
}
label_C7BB:;
    /* $C7BB: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x00 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C7BD:;
    /* $C7BD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_C7BF:;
    /* $C7BF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C7C6;
label_C7C1:;
    /* $C7C1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C7C3:;
    /* $C7C3: 99 */ maybe_trigger_vblank(5); nes_write((0x001E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_C7C6:; /* NextFSlot */
    /* $C7C6: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C7C7:;
    /* $C7C7: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { call_by_address(0xC7BA); return; }
label_C7C9:;
    /* $C7C9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C7CB:;
    /* $C7CB: 8D */ maybe_trigger_vblank(4); nes_write(0x06CB, g_cpu.A);
label_C7CE:;
    /* $C7CE: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_C7D0:;
    /* $C7D0: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::end_frenzy_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C7BA;
    }
label_C7B8:; /* EndFrenzy */
    /* $C7B8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x05; FLAG_NZ(g_cpu.Y);
label_C7BA:; /* LakituChk */
    /* $C7BA: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0016 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C7BD:;
    /* $C7BD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_C7BF:;
    /* $C7BF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C7C6;
label_C7C1:;
    /* $C7C1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_C7C3:;
    /* $C7C3: 99 */ maybe_trigger_vblank(5); nes_write((0x001E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_C7C6:; /* NextFSlot */
    /* $C7C6: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_C7C7:;
    /* $C7C7: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_C7BA;
    }
label_C7C9:;
    /* $C7C9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C7CB:;
    /* $C7CB: 8D */ maybe_trigger_vblank(4); nes_write(0x06CB, g_cpu.A);
label_C7CE:;
    /* $C7CE: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_C7D0:;
    /* $C7D0: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::init_bal_platform_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C808;
        case 2: goto label_C805;
        case 3: goto label_C800;
        case 4: goto label_C7EF;
        case 5: goto label_C7F7;
        case 6: goto label_C7FF;
    }
label_C7DF:; /* InitBalPlatform */
    /* $C7DF: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0xCF + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C7E1:;
    /* $C7E1: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0xCF + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C7E3:;
    /* $C7E3: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06CC); FLAG_NZ(g_cpu.Y);
label_C7E6:;
    /* $C7E6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C7ED;
label_C7E8:;
    /* $C7E8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_C7EA:;
    /* $C7EA: 20 */ maybe_trigger_vblank(6); call_by_address(0xC871);
label_C7ED:; /* AlignP */
    /* $C7ED: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xFF; FLAG_NZ(g_cpu.Y);
label_C7EF:;
    /* $C7EF: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03A0); FLAG_NZ(g_cpu.A);
label_C7F2:;
    /* $C7F2: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_C7F4:;
    /* $C7F4: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_C7F8;
label_C7F6:;
    /* $C7F6: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_C7F7:;
    /* $C7F7: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C7F8:; /* SetBPA */
    /* $C7F8: 8C */ maybe_trigger_vblank(4); nes_write(0x03A0, g_cpu.Y);
label_C7FB:;
    /* $C7FB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C7FD:;
    /* $C7FD: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_C7FF:;
    /* $C7FF: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_C800:;
    /* $C800: 20 */ maybe_trigger_vblank(6); call_by_address(0xC871);
label_C803:; /* InitDropPlatform */
    /* $C803: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_C805:;
    /* $C805: 9D */ maybe_trigger_vblank(5); nes_write((0x03A2 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C808:;
    /* $C808: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC828); return;
}

void EnemyEngine::init_hori_platform_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C80F;
        case 2: goto label_C80D;
    }
label_C80B:; /* InitHoriPlatform */
    /* $C80B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C80D:;
    /* $C80D: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_C80F:;
    /* $C80F: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC828); return;
}

void EnemyEngine::init_vert_platform_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C814;
        case 2: goto label_C81F;
        case 3: goto label_C816;
        case 4: goto label_C81B;
        case 5: goto label_C824;
        case 6: goto label_C834;
        case 7: goto label_C81D;
        case 8: goto label_C818;
        case 9: goto label_C81A;
    }
label_C812:; /* InitVertPlatform */
    /* $C812: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x40; FLAG_NZ(g_cpu.Y);
label_C814:;
    /* $C814: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C816:;
    /* $C816: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_C81F;
label_C818:;
    /* $C818: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_C81A:;
    /* $C81A: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C81B:;
    /* $C81B: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_C81D:;
    /* $C81D: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xC0; FLAG_NZ(g_cpu.Y);
label_C81F:; /* SetYO */
    /* $C81F: 9D */ maybe_trigger_vblank(5); nes_write((0x0401 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C822:;
    /* $C822: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_C823:;
    /* $C823: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C824:;
    /* $C824: 75 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xCF + g_cpu.X) & 0xFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C826:;
    /* $C826: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_C828:; /* CommonPlatCode */
    /* $C828: 20 */ maybe_trigger_vblank(6); call_by_address(0xC363);
label_C82B:; /* SPBBox */
    /* $C82B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_C82D:;
    /* $C82D: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_C830:;
    /* $C830: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_C832:;
    /* $C832: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C83B;
label_C834:;
    /* $C834: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06CC); FLAG_NZ(g_cpu.Y);
label_C837:;
    /* $C837: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C83B;
label_C839:;
    /* $C839: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_C83B:; /* CasPBB */
    /* $C83B: 9D */ maybe_trigger_vblank(5); nes_write((0x049A + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C83E:;
    /* $C83E: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::plat_lift_up_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C84D;
    }
label_C84B:; /* PlatLiftUp */
    /* $C84B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_C84D:;
    /* $C84D: 9D */ maybe_trigger_vblank(5); nes_write((0x0434 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C850:;
    /* $C850: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_C852:;
    /* $C852: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_C854:;
    /* $C854: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC860); return;
}

void EnemyEngine::plat_lift_down_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C859;
        case 2: goto label_C85C;
    }
label_C857:; /* PlatLiftDown */
    /* $C857: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF0; FLAG_NZ(g_cpu.A);
label_C859:;
    /* $C859: 9D */ maybe_trigger_vblank(5); nes_write((0x0434 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C85C:;
    /* $C85C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C85E:;
    /* $C85E: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_C860:; /* CommonSmallLift */
    /* $C860: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_C862:;
    /* $C862: 20 */ maybe_trigger_vblank(6); call_by_address(0xC871);
label_C865:;
    /* $C865: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_C867:;
    /* $C867: 9D */ maybe_trigger_vblank(5); nes_write((0x049A + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C86A:;
    /* $C86A: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::pos_platform_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C87E;
        case 2: goto label_C880;
    }
label_C871:; /* PosPlatform */
    /* $C871: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C873:;
    /* $C873: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_C874:;
    /* $C874: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xC86B + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C877:;
    /* $C877: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_C879:;
    /* $C879: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C87B:;
    /* $C87B: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xC86E + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C87E:;
    /* $C87E: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_C880:;
    /* $C880: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::run_enemy_objects_core_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C8D6;
        case 2: goto label_C888;
        case 3: goto label_C88F;
        case 4: goto label_C88A;
    }
label_C882:; /* RunEnemyObjectsCore */
    /* $C882: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_C884:;
    /* $C884: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C886:;
    /* $C886: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_C888:;
    /* $C888: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x15; g_cpu.C=(g_cpu.Y>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_C88A:;
    /* $C88A: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_C88F;
label_C88C:;
    /* $C88C: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_C88D:;
    /* $C88D: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x14; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C88F:; /* JmpEO */
    /* $C88F: 20 */ maybe_trigger_vblank(6); /* inline_dispatch $8E04: 34 entries (bank=-1) */
switch(g_cpu.A) {
  case 0: call_by_address(0xC8E0); return;
  case 1: call_by_address(0xC935); return;
  case 2: call_by_address(0xD295); return;
  case 3: call_by_address(0xC8D6); return;
  case 4: call_by_address(0xC8D6); return;
  case 5: call_by_address(0xC8D6); return;
  case 6: call_by_address(0xC8D6); return;
  case 7: call_by_address(0xC947); return;
  case 8: call_by_address(0xC947); return;
  case 9: call_by_address(0xC947); return;
  case 10: call_by_address(0xC947); return;
  case 11: call_by_address(0xC947); return;
  case 12: call_by_address(0xC947); return;
  case 13: call_by_address(0xC947); return;
  case 14: call_by_address(0xC947); return;
  case 15: call_by_address(0xC8D6); return;
  case 16: call_by_address(0xC965); return;
  case 17: call_by_address(0xC965); return;
  case 18: call_by_address(0xC965); return;
  case 19: call_by_address(0xC965); return;
  case 20: call_by_address(0xC965); return;
  case 21: call_by_address(0xC965); return;
  case 22: call_by_address(0xC965); return;
  case 23: call_by_address(0xC94D); return;
  case 24: call_by_address(0xC94D); return;
  case 25: call_by_address(0xD065); return;
  case 26: call_by_address(0xBC85); return;
  case 27: call_by_address(0xB94B); return;
  case 28: call_by_address(0xC8D6); return;
  case 29: call_by_address(0xD2D9); return;
  case 30: call_by_address(0xB8BA); return;
  case 31: call_by_address(0xC8D6); return;
  case 32: call_by_address(0xB7A4); return;
  case 33: call_by_address(0xC8D7); return;
  default: nes_log_inline_miss(0xC88F, g_cpu.A); return;
}
label_C8D6:; /* NoRunCode */
    /* $C8D6: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::run_normal_enemies_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C8FF;
        case 2: goto label_C902;
        case 3: goto label_C8EB;
        case 4: goto label_C8E8;
        case 5: goto label_C8EE;
        case 6: goto label_C8E5;
        case 7: goto label_C8F7;
        case 8: goto label_C8F1;
    }
label_C8E0:; /* RunNormalEnemies */
    /* $C8E0: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_C8E2:;
    /* $C8E2: 9D */ maybe_trigger_vblank(5); nes_write((0x03C5 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C8E5:;
    /* $C8E5: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1AF);
label_C8E8:;
    /* $C8E8: 20 */ maybe_trigger_vblank(6); call_by_address(0xF152);
label_C8EB:;
    /* $C8EB: 20 */ maybe_trigger_vblank(6); call_by_address(0xE87D);
label_C8EE:;
    /* $C8EE: 20 */ maybe_trigger_vblank(6); call_by_address(0xE243);
label_C8F1:;
    /* $C8F1: 20 */ maybe_trigger_vblank(6); call_by_address(0xDFC1);
label_C8F4:;
    /* $C8F4: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA33);
label_C8F7:;
    /* $C8F7: 20 */ maybe_trigger_vblank(6); call_by_address(0xD853);
label_C8FA:;
    /* $C8FA: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x0747); FLAG_NZ(g_cpu.Y);
label_C8FD:;
    /* $C8FD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C902;
label_C8FF:;
    /* $C8FF: 20 */ maybe_trigger_vblank(6); call_by_address(0xC905);
label_C902:; /* SkipMove */
    /* $C902: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD67A); return;
}

void EnemyEngine::enemy_movement_subs_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C934;
    }
label_C905:; /* EnemyMovementSubs */
    /* $C905: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C907:;
    /* $C907: 20 */ maybe_trigger_vblank(6); /* inline_dispatch $8E04: 21 entries (bank=-1) */
switch(g_cpu.A) {
  case 0: call_by_address(0xCA77); return;
  case 1: call_by_address(0xCA77); return;
  case 2: call_by_address(0xCA77); return;
  case 3: call_by_address(0xCA77); return;
  case 4: call_by_address(0xCA77); return;
  case 5: call_by_address(0xC9D8); return;
  case 6: call_by_address(0xCA77); return;
  case 7: call_by_address(0xCB89); return;
  case 8: call_by_address(0xCC36); return;
  case 9: call_by_address(0xC934); return;
  case 10: call_by_address(0xCC4A); return;
  case 11: call_by_address(0xCC4A); return;
  case 12: call_by_address(0xC9B0); return;
  case 13: call_by_address(0xD3B0); return;
  case 14: call_by_address(0xCAF9); return;
  case 15: call_by_address(0xCAFF); return;
  case 16: call_by_address(0xCB25); return;
  case 17: call_by_address(0xCF28); return;
  case 18: call_by_address(0xCA77); return;
  case 19: call_by_address(0xC934); return;
  case 20: call_by_address(0xCEDF); return;
  default: nes_log_inline_miss(0xC907, g_cpu.A); return;
}
label_C934:; /* NoMoveCode */
    /* $C934: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::run_bowser_flame_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C938;
        case 2: goto label_C93E;
    }
label_C935:; /* RunBowserFlame */
    /* $C935: 20 */ maybe_trigger_vblank(6); call_by_address(0xD1EB);
label_C938:;
    /* $C938: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1AF);
label_C93B:;
    /* $C93B: 20 */ maybe_trigger_vblank(6); call_by_address(0xF152);
label_C93E:;
    /* $C93E: 20 */ maybe_trigger_vblank(6); call_by_address(0xE243);
label_C941:;
    /* $C941: 20 */ maybe_trigger_vblank(6); call_by_address(0xD853);
label_C944:;
    /* $C944: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD67A); return;
}

void EnemyEngine::run_firebar_obj_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C94A;
    }
label_C947:; /* RunFirebarObj */
    /* $C947: 20 */ maybe_trigger_vblank(6); call_by_address(0xCD3C);
label_C94A:;
    /* $C94A: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD67A); return;
}

void EnemyEngine::run_small_platform_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C959;
        case 2: goto label_C953;
    }
label_C94D:; /* RunSmallPlatform */
    /* $C94D: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1AF);
label_C950:;
    /* $C950: 20 */ maybe_trigger_vblank(6); call_by_address(0xF152);
label_C953:;
    /* $C953: 20 */ maybe_trigger_vblank(6); call_by_address(0xE24C);
label_C956:;
    /* $C956: 20 */ maybe_trigger_vblank(6); call_by_address(0xDB7B);
label_C959:;
    /* $C959: 20 */ maybe_trigger_vblank(6); call_by_address(0xF152);
label_C95C:;
    /* $C95C: 20 */ maybe_trigger_vblank(6); call_by_address(0xED66);
label_C95F:;
    /* $C95F: 20 */ maybe_trigger_vblank(6); call_by_address(0xD655);
label_C962:;
    /* $C962: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD67A); return;
}

void EnemyEngine::run_large_platform_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C96B;
        case 2: goto label_C96E;
        case 3: goto label_C97F;
    }
label_C965:; /* RunLargePlatform */
    /* $C965: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1AF);
label_C968:;
    /* $C968: 20 */ maybe_trigger_vblank(6); call_by_address(0xF152);
label_C96B:;
    /* $C96B: 20 */ maybe_trigger_vblank(6); call_by_address(0xE273);
label_C96E:;
    /* $C96E: 20 */ maybe_trigger_vblank(6); call_by_address(0xDB45);
label_C971:;
    /* $C971: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_C974:;
    /* $C974: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C979;
label_C976:;
    /* $C976: 20 */ maybe_trigger_vblank(6); call_by_address(0xC982);
label_C979:; /* SkipPT */
    /* $C979: 20 */ maybe_trigger_vblank(6); call_by_address(0xF152);
label_C97C:;
    /* $C97C: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5C8);
label_C97F:;
    /* $C97F: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD67A); return;
}

void EnemyEngine::large_platform_subroutines_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C987;
        case 2: goto label_C9AC;
    }
label_C982:; /* LargePlatformSubroutines */
    /* $C982: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C984:;
    /* $C984: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_C985:;
    /* $C985: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x24; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C987:;
    /* $C987: 20 */ maybe_trigger_vblank(6); /* inline_dispatch $8E04: 7 entries (bank=-1) */
switch(g_cpu.A) {
  case 0: call_by_address(0xD432); return;
  case 1: call_by_address(0xD5D3); return;
  case 2: call_by_address(0xD64F); return;
  case 3: call_by_address(0xD64F); return;
  case 4: call_by_address(0xD607); return;
  case 5: call_by_address(0xD631); return;
  case 6: call_by_address(0xD63D); return;
  default: nes_log_inline_miss(0xC987, g_cpu.A); return;
}
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

void EnemyEngine::move_podoboo_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C9C0;
        case 2: goto label_C9C9;
        case 3: goto label_C9B5;
        case 4: goto label_C9CB;
        case 5: goto label_C9C7;
    }
label_C9B0:; /* MovePodoboo */
    /* $C9B0: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0796 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C9B3:;
    /* $C9B3: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_C9CB;
label_C9B5:;
    /* $C9B5: 20 */ maybe_trigger_vblank(6); call_by_address(0xC2F7);
label_C9B8:;
    /* $C9B8: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C9BB:;
    /* $C9BB: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x80; FLAG_NZ(g_cpu.A);
label_C9BD:;
    /* $C9BD: 9D */ maybe_trigger_vblank(5); nes_write((0x0434 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C9C0:;
    /* $C9C0: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_C9C2:;
    /* $C9C2: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x06; FLAG_NZ(g_cpu.A);
label_C9C4:;
    /* $C9C4: 9D */ maybe_trigger_vblank(5); nes_write((0x0796 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C9C7:;
    /* $C9C7: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF9; FLAG_NZ(g_cpu.A);
label_C9C9:;
    /* $C9C9: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_C9CB:; /* PdbM */
    /* $C9CB: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF92); return;
}

void EnemyEngine::proc_hammer_bro_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_D311;
        case 2: goto label_D84C;
        case 3: goto label_DA24;
        case 4: goto label_D1EA;
        case 5: goto label_D1BB;
        case 6: goto label_D001;
        case 7: goto label_D007;
        case 8: goto label_D907;
        case 9: goto label_D908;
        case 10: goto label_D0C0;
        case 11: goto label_CEA5;
        case 12: goto label_D9CF;
        case 13: goto label_D9EE;
        case 14: goto label_D003;
        case 15: goto label_D9AE;
        case 16: goto label_D98D;
        case 17: goto label_CDAD;
        case 18: goto label_CD8E;
        case 19: goto label_C9EA;
        case 20: goto label_D100;
        case 21: goto label_CD87;
        case 22: goto label_CF96;
        case 23: goto label_CCAE;
        case 24: goto label_CD4B;
        case 25: goto label_CFB5;
        case 26: goto label_D89D;
        case 27: goto label_D1C8;
        case 28: goto label_D009;
        case 29: goto label_CF76;
        case 30: goto label_D18E;
        case 31: goto label_D94C;
        case 32: goto label_D1EE;
        case 33: goto label_D1AD;
        case 34: goto label_CA05;
        case 35: goto label_D820;
        case 36: goto label_CFB9;
        case 37: goto label_CAC8;
        case 38: goto label_D058;
        case 39: goto label_CF8D;
        case 40: goto label_CF9A;
        case 41: goto label_D920;
        case 42: goto label_CFD6;
        case 43: goto label_CB8D;
        case 44: goto label_D7CF;
        case 45: goto label_D031;
        case 46: goto label_D7AE;
        case 47: goto label_D38C;
        case 48: goto label_D38D;
        case 49: goto label_CEC2;
        case 50: goto label_D3CF;
        case 51: goto label_CCD0;
        case 52: goto label_D012;
        case 53: goto label_D660;
        case 54: goto label_CFD7;
        case 55: goto label_D6D0;
        case 56: goto label_D6D2;
        case 57: goto label_D6C8;
        case 58: goto label_D6CA;
        case 59: goto label_D6BA;
        case 60: goto label_D6B8;
        case 61: goto label_D7B8;
        case 62: goto label_D8CB;
        case 63: goto label_CB8A;
        case 64: goto label_CC4B;
        case 65: goto label_D3D5;
        case 66: goto label_D62D;
        case 67: goto label_D00C;
        case 68: goto label_CEBA;
        case 69: goto label_CA10;
        case 70: goto label_D041;
        case 71: goto label_D079;
        case 72: goto label_D4B9;
        case 73: goto label_D4BA;
        case 74: goto label_D005;
        case 75: goto label_CFF7;
        case 76: goto label_D5D0;
        case 77: goto label_D6FA;
        case 78: goto label_D0CB;
        case 79: goto label_D089;
        case 80: goto label_D069;
        case 81: goto label_CEC5;
        case 82: goto label_CC46;
        case 83: goto label_CC47;
        case 84: goto label_D018;
        case 85: goto label_CE8F;
        case 86: goto label_CFAD;
        case 87: goto label_CD06;
        case 88: goto label_CD07;
        case 89: goto label_D0F8;
        case 90: goto label_CEA4;
        case 91: goto label_CD3B;
        case 92: goto label_CE33;
        case 93: goto label_CD2E;
        case 94: goto label_CD2F;
        case 95: goto label_CCC7;
        case 96: goto label_CCC8;
        case 97: goto label_CD2A;
        case 98: goto label_CED5;
        case 99: goto label_CED6;
        case 100: goto label_CEDB;
        case 101: goto label_CF25;
        case 102: goto label_D599;
        case 103: goto label_D606;
        case 104: goto label_D0A1;
        case 105: goto label_D02E;
        case 106: goto label_CED2;
        case 107: goto label_CFDD;
        case 108: goto label_CFDE;
        case 109: goto label_D061;
        case 110: goto label_D609;
        case 111: goto label_D721;
        case 112: goto label_D01F;
        case 113: goto label_D1D1;
        case 114: goto label_D991;
        case 115: goto label_D78D;
        case 116: goto label_CD7D;
        case 117: goto label_D2CD;
        case 118: goto label_D2CE;
        case 119: goto label_D5BD;
        case 120: goto label_D2D5;
        case 121: goto label_D17E;
        case 122: goto label_D2D1;
        case 123: goto label_D2D2;
        case 124: goto label_DA10;
        case 125: goto label_D5BC;
        case 126: goto label_D52D;
        case 127: goto label_D9D6;
        case 128: goto label_CFD9;
        case 129: goto label_CFDA;
        case 130: goto label_D01A;
        case 131: goto label_CFF5;
        case 132: goto label_CF79;
        case 133: goto label_D542;
        case 134: goto label_CFB7;
        case 135: goto label_D8BE;
        case 136: goto label_CA01;
        case 137: goto label_CE2D;
        case 138: goto label_CE2E;
        case 139: goto label_D736;
        case 140: goto label_D81D;
        case 141: goto label_D84F;
        case 142: goto label_D892;
        case 143: goto label_D893;
        case 144: goto label_D966;
        case 145: goto label_D851;
        case 146: goto label_D852;
        case 147: goto label_D2B9;
        case 148: goto label_D9D2;
        case 149: goto label_CADD;
        case 150: goto label_D081;
        case 151: goto label_DA25;
        case 152: goto label_D024;
        case 153: goto label_CE85;
        case 154: goto label_CE86;
        case 155: goto label_D0AE;
        case 156: goto label_CFC9;
        case 157: goto label_C9DC;
        case 158: goto label_D0C5;
        case 159: goto label_CE26;
        case 160: goto label_D0E3;
        case 161: goto label_D0E4;
        case 162: goto label_CBD0;
        case 163: goto label_CBD1;
        case 164: goto label_CA03;
        case 165: goto label_C9DE;
        case 166: goto label_D027;
        case 167: goto label_D6AE;
        case 168: goto label_D0E1;
        case 169: goto label_C9F9;
        case 170: goto label_C9DA;
        case 171: goto label_D61F;
        case 172: goto label_D047;
        case 173: goto label_D5EC;
        case 174: goto label_C9E3;
        case 175: goto label_D595;
        case 176: goto label_D12D;
        case 177: goto label_CAF1;
        case 178: goto label_D905;
        case 179: goto label_D913;
        case 180: goto label_CEB5;
        case 181: goto label_CC79;
        case 182: goto label_CC7D;
        case 183: goto label_D0BE;
        case 184: goto label_D4BD;
        case 185: goto label_D603;
        case 186: goto label_D679;
        case 187: goto label_CEBE;
        case 188: goto label_CA0D;
        case 189: goto label_D8DB;
        case 190: goto label_D8D9;
        case 191: goto label_CDD9;
        case 192: goto label_CECD;
        case 193: goto label_CECE;
        case 194: goto label_CECF;
        case 195: goto label_CFCF;
        case 196: goto label_D2D3;
        case 197: goto label_D2D4;
        case 198: goto label_D58A;
        case 199: goto label_D4D6;
        case 200: goto label_D3E3;
        case 201: goto label_D5D2;
        case 202: goto label_D0D1;
        case 203: goto label_D7D1;
        case 204: goto label_D7D7;
        case 205: goto label_D7D8;
        case 206: goto label_CABF;
        case 207: goto label_CCC6;
        case 208: goto label_CBCD;
        case 209: goto label_CC49;
        case 210: goto label_D29D;
        case 211: goto label_D8D3;
        case 212: goto label_D036;
        case 213: goto label_D033;
        case 214: goto label_D091;
        case 215: goto label_C9EC;
        case 216: goto label_D0B5;
        case 217: goto label_D03C;
        case 218: goto label_D015;
        case 219: goto label_D0EC;
        case 220: goto label_D0ED;
        case 221: goto label_CDBD;
        case 222: goto label_CA07;
        case 223: goto label_D4AD;
        case 224: goto label_D4AE;
        case 225: goto label_D903;
        case 226: goto label_D3AD;
        case 227: goto label_D58D;
        case 228: goto label_CAA9;
        case 229: goto label_D5AF;
        case 230: goto label_D04C;
        case 231: goto label_D0F0;
        case 232: goto label_D5AD;
        case 233: goto label_D0C8;
        case 234: goto label_D099;
        case 235: goto label_C9F1;
        case 236: goto label_C9F3;
        case 237: goto label_D045;
        case 238: goto label_CEF4;
        case 239: goto label_CE03;
        case 240: goto label_D0F6;
        case 241: goto label_D0F4;
        case 242: goto label_D4B1;
        case 243: goto label_CBA0;
        case 244: goto label_CE40;
        case 245: goto label_D05E;
        case 246: goto label_D9B9;
        case 247: goto label_D6B0;
        case 248: goto label_CAD7;
        case 249: goto label_D3B9;
        case 250: goto label_D07F;
        case 251: goto label_CCA8;
        case 252: goto label_D0FB;
        case 253: goto label_CA8E;
        case 254: goto label_D03E;
        case 255: goto label_D44D;
        case 256: goto label_D0F2;
    }
label_C9D8:; /* ProcHammerBro */
    /* $C9D8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C9DA:;
    /* $C9DA: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_C9DC:;
    /* $C9DC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_C9E1;
label_C9DE:;
    /* $C9DE: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xCAE5); return;
label_C9E1:; /* ChkJH */
    /* $C9E1: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x3C + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_C9E3:;
    /* $C9E3: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { call_by_address(0xCA12); return; }
label_C9E5:;
    /* $C9E5: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0x3C + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C9E7:;
    /* $C9E7: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D1); FLAG_NZ(g_cpu.A);
label_C9EA:;
    /* $C9EA: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0C; FLAG_NZ(g_cpu.A);
label_C9EC:;
    /* $C9EC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CA58;
label_C9EE:;
    /* $C9EE: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03A2 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C9F1:;
    /* $C9F1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CA0A;
label_C9F3:;
    /* $C9F3: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06CC); FLAG_NZ(g_cpu.Y);
label_C9F6:;
    /* $C9F6: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC9CE + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_C9F9:;
    /* $C9F9: 9D */ maybe_trigger_vblank(5); nes_write((0x03A2 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_C9FC:;
    /* $C9FC: 20 */ maybe_trigger_vblank(6); call_by_address(0xBA94);
label_C9FF:;
    /* $C9FF: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CA0A;
label_CA01:;
    /* $CA01: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CA03:;
    /* $CA03: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x08; FLAG_NZ(g_cpu.A);
label_CA05:;
    /* $CA05: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_CA07:;
    /* $CA07: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xCA58); return;
label_CA0A:; /* DecHT */
    /* $CA0A: DE */ maybe_trigger_vblank(7); { uint16_t a=(0x03A2 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CA0D:;
    /* $CA0D: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xCA58); return;
label_CA10:; /* HammerBroJumpLData */
    /* $CA10: 20 */ maybe_trigger_vblank(6); call_by_address(0xB537);
label_CA13:;
    /* $CA13: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x0729 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CA16:;
    /* $CA16: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_CA18:;
    /* $CA18: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CA58;
label_CA1A:;
    /* $CA1A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_CA1C:;
    /* $CA1C: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_CA1E:;
    /* $CA1E: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xFA; FLAG_NZ(g_cpu.Y);
label_CA20:;
    /* $CA20: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CA22:;
    /* $CA22: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_CA37;
label_CA24:;
    /* $CA24: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xFD; FLAG_NZ(g_cpu.Y);
label_CA26:;
    /* $CA26: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x70; g_cpu.C=(g_cpu.A>=0x70)?1:0; FLAG_NZ(r&0xFF); }
label_CA28:;
    /* $CA28: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CA2A:;
    /* $CA2A: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CA37;
label_CA2C:;
    /* $CA2C: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CA2E:;
    /* $CA2E: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CA31:;
    /* $CA31: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_CA33:;
    /* $CA33: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CA37;
label_CA35:;
    /* $CA35: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xFA; FLAG_NZ(g_cpu.Y);
label_CA37:; /* SetHJ */
    /* $CA37: 94 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.Y);
label_CA39:;
    /* $CA39: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CA3B:;
    /* $CA3B: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x01; FLAG_NZ(g_cpu.A);
label_CA3D:;
    /* $CA3D: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_CA3F:;
    /* $CA3F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_CA41:;
    /* $CA41: 3D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0x07A9 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CA44:;
    /* $CA44: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_CA45:;
    /* $CA45: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06CC); FLAG_NZ(g_cpu.A);
label_CA48:;
    /* $CA48: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CA4B;
label_CA4A:;
    /* $CA4A: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_CA4B:; /* HJump */
    /* $CA4B: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCA10 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CA4E:;
    /* $CA4E: 9D */ maybe_trigger_vblank(5); nes_write((0x078A + g_cpu.X) & 0xFFFF, g_cpu.A);
label_CA51:;
    /* $CA51: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CA54:;
    /* $CA54: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0xC0; FLAG_NZ(g_cpu.A);
label_CA56:;
    /* $CA56: 95 */ maybe_trigger_vblank(4); nes_write((0x3C + g_cpu.X) & 0xFF, g_cpu.A);
label_CA58:; /* MoveHammerBroXDir */
    /* $CA58: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xFC; FLAG_NZ(g_cpu.Y);
label_CA5A:;
    /* $CA5A: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_CA5C:;
    /* $CA5C: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_CA5E:;
    /* $CA5E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CA62;
label_CA60:;
    /* $CA60: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x04; FLAG_NZ(g_cpu.Y);
label_CA62:; /* Shimmy */
    /* $CA62: 94 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.Y);
label_CA64:;
    /* $CA64: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_CA66:;
    /* $CA66: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_CA69:;
    /* $CA69: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_CA75;
label_CA6B:;
    /* $CA6B: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CA6C:;
    /* $CA6C: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0796 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CA6F:;
    /* $CA6F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CA75;
label_CA71:;
    /* $CA71: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_CA73:;
    /* $CA73: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_CA75:; /* SetShim */
    /* $CA75: 94 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.Y);
label_CA77:; /* MoveNormalEnemy */
    /* $CA77: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_CA79:;
    /* $CA79: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CA7B:;
    /* $CA7B: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_CA7D:;
    /* $CA7D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CA98;
label_CA7F:;
    /* $CA7F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CA81:;
    /* $CA81: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_CA82:;
    /* $CA82: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CAB4;
label_CA84:;
    /* $CA84: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CA86:;
    /* $CA86: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_CA88:;
    /* $CA88: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CAE5;
label_CA8A:;
    /* $CA8A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CA8C:;
    /* $CA8C: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_CA8E:;
    /* $CA8E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CAB4;
label_CA90:;
    /* $CA90: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_CA92:;
    /* $CA92: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CA98;
label_CA94:;
    /* $CA94: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_CA96:;
    /* $CA96: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CAC8;
label_CA98:; /* FallE */
    /* $CA98: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF63);
label_CA9B:;
    /* $CA9B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_CA9D:;
    /* $CA9D: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CA9F:;
    /* $CA9F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_CAA1:;
    /* $CAA1: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CAAF;
label_CAA3:;
    /* $CAA3: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_CAA5:;
    /* $CAA5: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CAB4;
label_CAA7:;
    /* $CAA7: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CAA9:;
    /* $CAA9: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x2E; g_cpu.C=(g_cpu.A>=0x2E)?1:0; FLAG_NZ(r&0xFF); }
label_CAAB:;
    /* $CAAB: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CAB4;
label_CAAD:;
    /* $CAAD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CAB2;
label_CAAF:; /* MEHor */
    /* $CAAF: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF02); return;
label_CAB2:; /* SlowM */
    /* $CAB2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_CAB4:; /* SteadM */
    /* $CAB4: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CAB6:;
    /* $CAB6: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_CAB7:;
    /* $CAB7: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_CABB;
label_CAB9:;
    /* $CAB9: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CABA:;
    /* $CABA: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CABB:; /* AddHS */
    /* $CABB: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CABC:;
    /* $CABC: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xC9D0 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CABF:;
    /* $CABF: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_CAC1:;
    /* $CAC1: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF02);
label_CAC4:;
    /* $CAC4: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_CAC5:;
    /* $CAC5: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_CAC7:;
    /* $CAC7: 60 */ maybe_trigger_vblank(6);
    return;
label_CAC8:; /* ReviveStunned */
    /* $CAC8: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0796 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CACB:;
    /* $CACB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CAEB;
label_CACD:;
    /* $CACD: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_CACF:;
    /* $CACF: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_CAD1:;
    /* $CAD1: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_CAD3:;
    /* $CAD3: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_CAD4:;
    /* $CAD4: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CAD5:;
    /* $CAD5: 94 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.Y);
label_CAD7:;
    /* $CAD7: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CAD8:;
    /* $CAD8: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x076A); FLAG_NZ(g_cpu.A);
label_CADB:;
    /* $CADB: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CADF;
label_CADD:;
    /* $CADD: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CADE:;
    /* $CADE: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CADF:; /* SetRSpd */
    /* $CADF: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC9D4 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CAE2:;
    /* $CAE2: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_CAE4:;
    /* $CAE4: 60 */ maybe_trigger_vblank(6);
    return;
label_CAE5:; /* MoveDefeatedEnemy */
    /* $CAE5: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF63);
label_CAE8:;
    /* $CAE8: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF02); return;
label_CAEB:; /* ChkKillGoomba */
    /* $CAEB: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0E; g_cpu.C=(g_cpu.A>=0x0E)?1:0; FLAG_NZ(r&0xFF); }
label_CAED:;
    /* $CAED: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CAF8;
label_CAEF:;
    /* $CAEF: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CAF1:;
    /* $CAF1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_CAF3:;
    /* $CAF3: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CAF8;
label_CAF5:;
    /* $CAF5: 20 */ maybe_trigger_vblank(6); call_by_address(0xC998);
label_CAF8:; /* NKGmba */
    /* $CAF8: 60 */ maybe_trigger_vblank(6);
    return;
label_CAF9:; /* MoveJumpingEnemy */
    /* $CAF9: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF92);
label_CAFC:;
    /* $CAFC: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF02); return;
label_CAFF:; /* ProcMoveRedPTroopa */
    /* $CAFF: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CB01:;
    /* $CB01: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x0434 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CB04:;
    /* $CB04: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CB19;
label_CB06:;
    /* $CB06: 9D */ maybe_trigger_vblank(5); nes_write((0x0417 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_CB09:;
    /* $CB09: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CB0B:;
    /* $CB0B: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x0401 + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_CB0E:;
    /* $CB0E: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CB19;
label_CB10:;
    /* $CB10: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_CB12:;
    /* $CB12: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_CB14:;
    /* $CB14: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CB18;
label_CB16:;
    /* $CB16: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0xCF + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CB18:; /* NoIncPT */
    /* $CB18: 60 */ maybe_trigger_vblank(6);
    return;
label_CB19:; /* MoveRedPTUpOrDown */
    /* $CB19: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CB1B:;
    /* $CB1B: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x58 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_CB1D:;
    /* $CB1D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CB22;
label_CB1F:;
    /* $CB1F: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF75); return;
label_CB22:; /* MovPTDwn */
    /* $CB22: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF70); return;
label_CB25:; /* MoveFlyGreenPTroopa */
    /* $CB25: 20 */ maybe_trigger_vblank(6); call_by_address(0xCB45);
label_CB28:;
    /* $CB28: 20 */ maybe_trigger_vblank(6); call_by_address(0xCB66);
label_CB2B:;
    /* $CB2B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_CB2D:;
    /* $CB2D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_CB2F:;
    /* $CB2F: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_CB31:;
    /* $CB31: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CB44;
label_CB33:;
    /* $CB33: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_CB35:;
    /* $CB35: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_CB37:;
    /* $CB37: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CB3B;
label_CB39:;
    /* $CB39: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xFF; FLAG_NZ(g_cpu.Y);
label_CB3B:; /* YSway */
    /* $CB3B: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_CB3D:;
    /* $CB3D: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CB3F:;
    /* $CB3F: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CB40:;
    /* $CB40: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CB42:;
    /* $CB42: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_CB44:; /* NoMGPT */
    /* $CB44: 60 */ maybe_trigger_vblank(6);
    return;
label_CB45:; /* XMoveCntr_GreenPTroopa */
    /* $CB45: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x13; FLAG_NZ(g_cpu.A);
label_CB47:; /* XMoveCntr_Platform */
    /* $CB47: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_CB49:;
    /* $CB49: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_CB4B:;
    /* $CB4B: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_CB4D:;
    /* $CB4D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CB5C;
label_CB4F:;
    /* $CB4F: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_CB51:;
    /* $CB51: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CB53:;
    /* $CB53: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CB54:;
    /* $CB54: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CB60;
label_CB56:;
    /* $CB56: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x01); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_CB58:;
    /* $CB58: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CB5D;
label_CB5A:;
    /* $CB5A: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0x58 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CB5C:; /* NoIncXM */
    /* $CB5C: 60 */ maybe_trigger_vblank(6);
    return;
label_CB5D:; /* IncPXM */
    /* $CB5D: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0xA0 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CB5F:;
    /* $CB5F: 60 */ maybe_trigger_vblank(6);
    return;
label_CB60:; /* DecSeXM */
    /* $CB60: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_CB61:;
    /* $CB61: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_CB5D;
    }
label_CB63:;
    /* $CB63: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0x58 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CB65:;
    /* $CB65: 60 */ maybe_trigger_vblank(6);
    return;
label_CB66:; /* MoveWithXMCntrs */
    /* $CB66: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CB68:;
    /* $CB68: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_CB69:;
    /* $CB69: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_CB6B:;
    /* $CB6B: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CB6D:;
    /* $CB6D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_CB6F:;
    /* $CB6F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CB7C;
label_CB71:;
    /* $CB71: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CB73:;
    /* $CB73: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_CB75:;
    /* $CB75: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CB76:;
    /* $CB76: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_CB78:;
    /* $CB78: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_CB7A:;
    /* $CB7A: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_CB7C:; /* XMRight */
    /* $CB7C: 94 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.Y);
label_CB7E:;
    /* $CB7E: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF02);
label_CB81:;
    /* $CB81: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_CB83:;
    /* $CB83: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_CB84:;
    /* $CB84: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_CB86:;
    /* $CB86: 60 */ maybe_trigger_vblank(6);
    return;
label_CB87:; /* BlooberBitmasks */
    /* $CB87: 3F */ maybe_trigger_vblank(7); /* ILLEGAL $3F — skip 3 */
label_CB8A:;
    /* $CB8A: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x2029 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CB8D:;
    /* $CB8D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CBDC;
label_CB8F:;
    /* $CB8F: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06CC); FLAG_NZ(g_cpu.Y);
label_CB92:;
    /* $CB92: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CB95:;
    /* $CB95: 39 */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xCB87 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CB98:;
    /* $CB98: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CBAC;
label_CB9A:;
    /* $CB9A: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_CB9B:;
    /* $CB9B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CB9C:;
    /* $CB9C: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CBA2;
label_CB9E:;
    /* $CB9E: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x45); FLAG_NZ(g_cpu.Y);
label_CBA0:;
    /* $CBA0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CBAA;
label_CBA2:; /* FBLeft */
    /* $CBA2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_CBA4:;
    /* $CBA4: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_CBA7:;
    /* $CBA7: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_CBAA;
label_CBA9:;
    /* $CBA9: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CBAA:; /* SBMDir */
    /* $CBAA: 94 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.Y);
label_CBAC:; /* BlooberSwim */
    /* $CBAC: 20 */ maybe_trigger_vblank(6); call_by_address(0xCBDF);
label_CBAF:;
    /* $CBAF: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CBB1:;
    /* $CBB1: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CBB2:;
    /* $CBB2: FD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x0434 + g_cpu.X) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CBB5:;
    /* $CBB5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_CBB7:;
    /* $CBB7: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CBBB;
label_CBB9:;
    /* $CBB9: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_CBBB:; /* SwimX */
    /* $CBBB: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_CBBD:;
    /* $CBBD: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CBBE:;
    /* $CBBE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CBCE;
label_CBC0:;
    /* $CBC0: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CBC2:;
    /* $CBC2: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CBC3:;
    /* $CBC3: 75 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x58 + g_cpu.X) & 0xFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CBC5:;
    /* $CBC5: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_CBC7:;
    /* $CBC7: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CBC9:;
    /* $CBC9: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_CBCB:;
    /* $CBCB: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_CBCD:;
    /* $CBCD: 60 */ maybe_trigger_vblank(6);
    return;
label_CBCE:; /* LeftSwim */
    /* $CBCE: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CBD0:;
    /* $CBD0: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CBD1:;
    /* $CBD1: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x58 + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CBD3:;
    /* $CBD3: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_CBD5:;
    /* $CBD5: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CBD7:;
    /* $CBD7: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CBD9:;
    /* $CBD9: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_CBDB:;
    /* $CBDB: 60 */ maybe_trigger_vblank(6);
    return;
label_CBDC:; /* MoveDefeatedBloober */
    /* $CBDC: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF8C); return;
label_CBDF:; /* ProcSwimmingB */
    /* $CBDF: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CBE1:;
    /* $CBE1: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_CBE3:;
    /* $CBE3: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CC1C;
label_CBE5:;
    /* $CBE5: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_CBE7:;
    /* $CBE7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_CBE9:;
    /* $CBE9: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_CBEA:;
    /* $CBEA: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CBEC:;
    /* $CBEC: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CBED:;
    /* $CBED: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CC04;
label_CBEF:;
    /* $CBEF: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_CBF0:;
    /* $CBF0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CC03;
label_CBF2:;
    /* $CBF2: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0434 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CBF5:;
    /* $CBF5: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CBF6:;
    /* $CBF6: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_CBF8:;
    /* $CBF8: 9D */ maybe_trigger_vblank(5); nes_write((0x0434 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_CBFB:;
    /* $CBFB: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_CBFD:;
    /* $CBFD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_CBFF:;
    /* $CBFF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CC03;
label_CC01:;
    /* $CC01: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0xA0 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CC03:; /* BSwimE */
    /* $CC03: 60 */ maybe_trigger_vblank(6);
    return;
label_CC04:; /* SlowSwim */
    /* $CC04: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_CC05:;
    /* $CC05: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CC1B;
label_CC07:;
    /* $CC07: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0434 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CC0A:;
    /* $CC0A: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CC0B:;
    /* $CC0B: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x01; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC0D:;
    /* $CC0D: 9D */ maybe_trigger_vblank(5); nes_write((0x0434 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_CC10:;
    /* $CC10: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_CC12:;
    /* $CC12: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CC1B;
label_CC14:;
    /* $CC14: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0xA0 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CC16:;
    /* $CC16: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_CC18:;
    /* $CC18: 9D */ maybe_trigger_vblank(5); nes_write((0x0796 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_CC1B:; /* NoSSw */
    /* $CC1B: 60 */ maybe_trigger_vblank(6);
    return;
label_CC1C:; /* ChkForFloatdown */
    /* $CC1C: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0796 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CC1F:;
    /* $CC1F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CC29;
label_CC21:; /* Floatdown */
    /* $CC21: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_CC23:;
    /* $CC23: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CC24:;
    /* $CC24: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CC28;
label_CC26:;
    /* $CC26: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0xCF + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CC28:; /* NoFD */
    /* $CC28: 60 */ maybe_trigger_vblank(6);
    return;
label_CC29:; /* ChkNearPlayer */
    /* $CC29: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC2B:;
    /* $CC2B: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x10 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x10); g_cpu.A=r&0xFF; }
label_CC2D:;
    /* $CC2D: C5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xCE); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_CC2F:;
    /* $CC2F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_CC21;
    }
label_CC31:;
    /* $CC31: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_CC33:;
    /* $CC33: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_CC35:;
    /* $CC35: 60 */ maybe_trigger_vblank(6);
    return;
label_CC36:; /* MoveBulletBill */
    /* $CC36: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC38:;
    /* $CC38: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_CC3A:;
    /* $CC3A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CC3F;
label_CC3C:;
    /* $CC3C: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF92); return;
label_CC3F:; /* NotDefB */
    /* $CC3F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xE8; FLAG_NZ(g_cpu.A);
label_CC41:;
    /* $CC41: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_CC43:;
    /* $CC43: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF02); return;
label_CC46:; /* SwimCCXMoveData */
    /* $CC46: 40 */ maybe_trigger_vblank(6); /* RTI */ g_cpu.S++; { uint8_t p=g_ram[0x100+g_cpu.S]; g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1; g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; } g_cpu.S++; g_cpu.S++; /* pop PCL, PCH */
    return;
label_CC47:;
    /* $CC47: 80 */ maybe_trigger_vblank(2); /* NOP */
label_CC49:;
    /* $CC49: 04 */ maybe_trigger_vblank(3); (void)nes_read(0xB5); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_CC4B:;
    /* $CC4B: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x2029 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CC4E:;
    /* $CC4E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CC53;
label_CC50:;
    /* $CC50: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF8C); return;
label_CC53:; /* CCSwim */
    /* $CC53: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_CC55:;
    /* $CC55: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC57:;
    /* $CC57: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CC58:;
    /* $CC58: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x0A; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC5A:;
    /* $CC5A: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_CC5B:;
    /* $CC5B: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCC46 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CC5E:;
    /* $CC5E: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_CC60:;
    /* $CC60: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0401 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CC63:;
    /* $CC63: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CC64:;
    /* $CC64: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x02); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC66:;
    /* $CC66: 9D */ maybe_trigger_vblank(5); nes_write((0x0401 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_CC69:;
    /* $CC69: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC6B:;
    /* $CC6B: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC6D:;
    /* $CC6D: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_CC6F:;
    /* $CC6F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC71:;
    /* $CC71: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC73:;
    /* $CC73: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_CC75:;
    /* $CC75: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_CC77:;
    /* $CC77: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_CC79:;
    /* $CC79: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x02; g_cpu.C=(g_cpu.X>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_CC7B:;
    /* $CC7B: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CCC6;
label_CC7D:;
    /* $CC7D: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC7F:;
    /* $CC7F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x10; g_cpu.C=(g_cpu.A>=0x10)?1:0; FLAG_NZ(r&0xFF); }
label_CC81:;
    /* $CC81: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CC99;
label_CC83:;
    /* $CC83: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0417 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CC86:;
    /* $CC86: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CC87:;
    /* $CC87: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x02); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC89:;
    /* $CC89: 9D */ maybe_trigger_vblank(5); nes_write((0x0417 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_CC8C:;
    /* $CC8C: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC8E:;
    /* $CC8E: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x03); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC90:;
    /* $CC90: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_CC92:;
    /* $CC92: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xB6 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC94:;
    /* $CC94: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_CC96:;
    /* $CC96: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xCCAC); return;
label_CC99:; /* CCSwimUpwards */
    /* $CC99: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0417 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CC9C:;
    /* $CC9C: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CC9D:;
    /* $CC9D: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x02); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC9F:;
    /* $CC9F: 9D */ maybe_trigger_vblank(5); nes_write((0x0417 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_CCA2:;
    /* $CCA2: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CCA4:;
    /* $CCA4: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x03); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CCA6:;
    /* $CCA6: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_CCA8:;
    /* $CCA8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xB6 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CCAA:;
    /* $CCAA: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CCAC:; /* ChkSwimYPos */
    /* $CCAC: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_CCAE:;
    /* $CCAE: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_CCB0:;
    /* $CCB0: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CCB2:;
    /* $CCB2: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CCB3:;
    /* $CCB3: FD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x0434 + g_cpu.X) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CCB6:;
    /* $CCB6: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_CCBF;
label_CCB8:;
    /* $CCB8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x10; FLAG_NZ(g_cpu.Y);
label_CCBA:;
    /* $CCBA: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_CCBC:;
    /* $CCBC: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CCBD:;
    /* $CCBD: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_CCBF:; /* YPDiff */
    /* $CCBF: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0F; g_cpu.C=(g_cpu.A>=0x0F)?1:0; FLAG_NZ(r&0xFF); }
label_CCC1:;
    /* $CCC1: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CCC6;
label_CCC3:;
    /* $CCC3: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_CCC4:;
    /* $CCC4: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_CCC6:; /* ExSwCC */
    /* $CCC6: 60 */ maybe_trigger_vblank(6);
    return;
label_CCC7:; /* FirebarPosLookupTbl */
    /* $CCC7: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xCCC7); return;
label_CCC8:;
    /* $CCC8: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x03 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_CCCA:;
    /* $CCCA: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x05); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_CCCC:;
    /* $CCCC: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x07; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CCCE:;
    /* $CCCE: 07 */ maybe_trigger_vblank(5); /* ILLEGAL $07 — skip 2 */
label_CCD0:;
    /* $CCD0: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xCCD0); return;
label_CCD1:;
    /* $CCD1: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_CCD3:;
    /* $CCD3: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x0B; FLAG_NZ(g_cpu.A);
label_CCD5:;
    /* $CCD5: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x0F0E); FLAG_NZ(g_cpu.A);
label_CCD8:;
    /* $CCD8: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_CCDA;
label_CCDA:;
    /* $CCDA: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x09); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_CCDC:;
    /* $CCDC: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x1310); FLAG_NZ(g_cpu.A);
label_CCDF:;
    /* $CCDF: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x17 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CCE1:;
    /* $CCE1: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CCE2:;
    /* $CCE2: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xCCE2); return;
label_CCE3:;
    /* $CCE3: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x0C; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CCE5:;
    /* $CCE5: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_CCE6:;
    /* $CCE6: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x1A + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CCE8:;
    /* $CCE8: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x201F + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CCEB:;
    /* $CCEB: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xCCEB); return;
label_CCEC:;
    /* $CCEC: 07 */ maybe_trigger_vblank(5); /* ILLEGAL $07 — skip 2 */
label_CCEE:;
    /* $CCEE: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x1C + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CCF0:;
    /* $CCF0: 21 */ maybe_trigger_vblank(6); g_cpu.A &= nes_read(nes_read16zp((0x25 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_CCF2:;
    /* $CCF2: 27 */ maybe_trigger_vblank(5); /* ILLEGAL $27 — skip 2 */
label_CCF4:;
    /* $CCF4: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xCCF4); return;
label_CCF5:;
    /* $CCF5: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x12; FLAG_NZ(g_cpu.A);
label_CCF7:;
    /* $CCF7: 1B */ maybe_trigger_vblank(7); /* ILLEGAL $1B — skip 3 */
label_CCFA:;
    /* $CCFA: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x302F); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_CCFD:;
    /* $CCFD: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xCCFD); return;
label_CCFE:;
    /* $CCFE: 0B */ maybe_trigger_vblank(2); /* ILLEGAL $0B — skip 2 */
label_CD00:;
    /* $CD00: 1F */ maybe_trigger_vblank(7); /* ILLEGAL $1F — skip 3 */
label_CD03:;
    /* $CD03: 33 */ maybe_trigger_vblank(8); /* ILLEGAL $33 — skip 2 */
label_CD05:;
    /* $CD05: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CD06:;
    /* $CD06: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xCD06); return;
label_CD07:;
    /* $CD07: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x2418); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_CD0A:;
    /* $CD0A: 2D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read(0x3B35); FLAG_NZ(g_cpu.A);
label_CD0D:;
    /* $CD0D: 3E */ maybe_trigger_vblank(7); { uint16_t a=(0x0040 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CD10:;
    /* $CD10: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x281B; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CD13:;
    /* $CD13: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_CD14:;
    /* $CD14: 3B */ maybe_trigger_vblank(7); /* ILLEGAL $3B — skip 3 */
label_CD17:;
    /* $CD17: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_CD18:;
    /* $CD18: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xCD18); return;
label_CD19:;
    /* $CD19: 0F */ maybe_trigger_vblank(6); /* ILLEGAL $0F — skip 3 */
label_CD1C:;
    /* $CD1C: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CD1D:;
    /* $CD1D: 42 */ maybe_trigger_vblank(2); /* ILLEGAL $42 — skip 1 */
label_CD1E:;
    /* $CD1E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CD1F:;
    /* $CD1F: 4E */ maybe_trigger_vblank(6); { uint16_t a=0x0050; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_CD22:;
    /* $CD22: 11 */ maybe_trigger_vblank(5); g_cpu.A |= nes_read((nes_read16zp(0x22) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CD24:;
    /* $CD24: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x3E) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CD26:;
    /* $CD26: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x51; FLAG_NZ(g_cpu.A);
label_CD28:;
    /* $CD28: 56 */ maybe_trigger_vblank(6); { uint16_t a=(0x58 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_CD2A:; /* FirebarMirrorData */
    /* $CD2A: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x03 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_CD2C:;
    /* $CD2C: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_CD2D:;
    /* $CD2D: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xCD2D); return;
label_CD2E:; /* FirebarTblOffsets */
    /* $CD2E: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xCD2E); return;
label_CD2F:;
    /* $CD2F: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x12; FLAG_NZ(g_cpu.A);
label_CD31:;
    /* $CD31: 1B */ maybe_trigger_vblank(7); /* ILLEGAL $1B — skip 3 */
label_CD34:;
    /* $CD34: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x3F + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CD36:;
    /* $CD36: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_CD37:;
    /* $CD37: 51 */ maybe_trigger_vblank(5); g_cpu.A ^= nes_read((nes_read16zp(0x5A) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CD39:;
    /* $CD39: 63 */ maybe_trigger_vblank(8); /* ILLEGAL $63 — skip 2 */
label_CD3B:;
    /* $CD3B: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CD3C:; /* ProcFirebar */
    /* $CD3C: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1AF);
label_CD3F:;
    /* $CD3F: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D1); FLAG_NZ(g_cpu.A);
label_CD42:;
    /* $CD42: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_CD44:;
    /* $CD44: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CDBA;
label_CD46:;
    /* $CD46: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_CD49:;
    /* $CD49: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CD55;
label_CD4B:;
    /* $CD4B: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0388 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CD4E:;
    /* $CD4E: 20 */ maybe_trigger_vblank(6); call_by_address(0xD410);
label_CD51:;
    /* $CD51: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x1F; FLAG_NZ(g_cpu.A);
label_CD53:;
    /* $CD53: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_CD55:; /* SusFbar */
    /* $CD55: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CD57:;
    /* $CD57: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_CD59:;
    /* $CD59: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x1F; g_cpu.C=(g_cpu.Y>=0x1F)?1:0; FLAG_NZ(r&0xFF); }
label_CD5B:;
    /* $CD5B: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CD6A;
label_CD5D:;
    /* $CD5D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_CD5F:;
    /* $CD5F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CD65;
label_CD61:;
    /* $CD61: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x18; g_cpu.C=(g_cpu.A>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_CD63:;
    /* $CD63: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CD6A;
label_CD65:; /* SkpFSte */
    /* $CD65: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CD66:;
    /* $CD66: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_CD68:;
    /* $CD68: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_CD6A:; /* SetupGFB */
    /* $CD6A: 85 */ maybe_trigger_vblank(3); nes_write(0xEF, g_cpu.A);
label_CD6C:;
    /* $CD6C: 20 */ maybe_trigger_vblank(6); call_by_address(0xF152);
label_CD6F:;
    /* $CD6F: 20 */ maybe_trigger_vblank(6); call_by_address(0xCE8E);
label_CD72:;
    /* $CD72: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_CD75:;
    /* $CD75: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B9); FLAG_NZ(g_cpu.A);
label_CD78:;
    /* $CD78: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_CD7B:;
    /* $CD7B: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_CD7D:;
    /* $CD7D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_CD80:;
    /* $CD80: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_CD83:;
    /* $CD83: 85 */ maybe_trigger_vblank(3); nes_write(0x06, g_cpu.A);
label_CD85:;
    /* $CD85: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_CD87:;
    /* $CD87: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_CD89:;
    /* $CD89: 20 */ maybe_trigger_vblank(6); call_by_address(0xCE08);
label_CD8C:;
    /* $CD8C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x05; FLAG_NZ(g_cpu.Y);
label_CD8E:;
    /* $CD8E: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CD90:;
    /* $CD90: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x1F; g_cpu.C=(g_cpu.A>=0x1F)?1:0; FLAG_NZ(r&0xFF); }
label_CD92:;
    /* $CD92: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CD96;
label_CD94:;
    /* $CD94: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x0B; FLAG_NZ(g_cpu.Y);
label_CD96:; /* SetMFbar */
    /* $CD96: 84 */ maybe_trigger_vblank(3); nes_write(0xED, g_cpu.Y);
label_CD98:;
    /* $CD98: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_CD9A:;
    /* $CD9A: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_CD9C:; /* DrawFbar */
    /* $CD9C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xEF); FLAG_NZ(g_cpu.A);
label_CD9E:;
    /* $CD9E: 20 */ maybe_trigger_vblank(6); call_by_address(0xCE8E);
label_CDA1:;
    /* $CDA1: 20 */ maybe_trigger_vblank(6); call_by_address(0xCDBB);
label_CDA4:;
    /* $CDA4: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_CDA6:;
    /* $CDA6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_CDA8:;
    /* $CDA8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CDB2;
label_CDAA:;
    /* $CDAA: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06CF); FLAG_NZ(g_cpu.Y);
label_CDAD:;
    /* $CDAD: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x06E5 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CDB0:;
    /* $CDB0: 85 */ maybe_trigger_vblank(3); nes_write(0x06, g_cpu.A);
label_CDB2:; /* NextFbar */
    /* $CDB2: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CDB4:;
    /* $CDB4: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_CDB6:;
    /* $CDB6: C5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xED); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_CDB8:;
    /* $CDB8: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_CD9C;
    }
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_CDBA:; /* SkipFBar */
    /* $CDBA: 60 */ maybe_trigger_vblank(6);
    return;
label_CDBB:; /* DrawFirebar_Collision */
    /* $CDBB: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x03); FLAG_NZ(g_cpu.A);
label_CDBD:;
    /* $CDBD: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_CDBF:;
    /* $CDBF: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x06); FLAG_NZ(g_cpu.Y);
label_CDC1:;
    /* $CDC1: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_CDC3:;
    /* $CDC3: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x05; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_CDC5:;
    /* $CDC5: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CDCB;
label_CDC7:;
    /* $CDC7: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_CDC9:;
    /* $CDC9: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_CDCB:; /* AddHA */
    /* $CDCB: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CDCC:;
    /* $CDCC: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x03AE); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CDCF:;
    /* $CDCF: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_CDD2:;
    /* $CDD2: 85 */ maybe_trigger_vblank(3); nes_write(0x06, g_cpu.A);
label_CDD4:;
    /* $CDD4: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x03AE); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_CDD7:;
    /* $CDD7: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CDE2;
label_CDD9:;
    /* $CDD9: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_CDDC:;
    /* $CDDC: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CDDD:;
    /* $CDDD: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x06); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CDDF:;
    /* $CDDF: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xCDE6); return;
label_CDE2:; /* SubtR1 */
    /* $CDE2: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CDE3:;
    /* $CDE3: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x03AE); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CDE6:; /* ChkFOfs */
    /* $CDE6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x59; g_cpu.C=(g_cpu.A>=0x59)?1:0; FLAG_NZ(r&0xFF); }
label_CDE8:;
    /* $CDE8: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CDEE;
label_CDEA:;
    /* $CDEA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_CDEC:;
    /* $CDEC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CE03;
label_CDEE:; /* VAHandl */
    /* $CDEE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B9); FLAG_NZ(g_cpu.A);
label_CDF1:;
    /* $CDF1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xF8; g_cpu.C=(g_cpu.A>=0xF8)?1:0; FLAG_NZ(r&0xFF); }
label_CDF3:;
    /* $CDF3: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CE03;
label_CDF5:;
    /* $CDF5: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_CDF7:;
    /* $CDF7: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x05; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_CDF9:;
    /* $CDF9: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CDFF;
label_CDFB:;
    /* $CDFB: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_CDFD:;
    /* $CDFD: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_CDFF:; /* AddVA */
    /* $CDFF: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CE00:;
    /* $CE00: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x03B9); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CE03:; /* SetVFbr */
    /* $CE03: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_CE06:;
    /* $CE06: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_CE08:; /* FirebarCollision */
    /* $CE08: 20 */ maybe_trigger_vblank(6); call_by_address(0xECED);
label_CE0B:;
    /* $CE0B: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_CE0C:;
    /* $CE0C: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_CE0D:;
    /* $CE0D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x079F); FLAG_NZ(g_cpu.A);
label_CE10:;
    /* $CE10: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_CE13:;
    /* $CE13: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CE85;
label_CE15:;
    /* $CE15: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_CE17:;
    /* $CE17: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xB5); FLAG_NZ(g_cpu.Y);
label_CE19:;
    /* $CE19: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CE1A:;
    /* $CE1A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CE85;
label_CE1C:;
    /* $CE1C: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xCE); FLAG_NZ(g_cpu.Y);
label_CE1E:;
    /* $CE1E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0754); FLAG_NZ(g_cpu.A);
label_CE21:;
    /* $CE21: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CE28;
label_CE23:;
    /* $CE23: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0714); FLAG_NZ(g_cpu.A);
label_CE26:;
    /* $CE26: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CE31;
label_CE28:; /* AdjSm */
    /* $CE28: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x05; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CE2A:;
    /* $CE2A: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x05; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CE2C:;
    /* $CE2C: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_CE2D:;
    /* $CE2D: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CE2E:;
    /* $CE2E: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x18 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x18); g_cpu.A=r&0xFF; }
label_CE30:;
    /* $CE30: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_CE31:; /* BigJp */
    /* $CE31: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_CE32:; /* FBCLoop */
    /* $CE32: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CE33:;
    /* $CE33: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x07); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CE35:;
    /* $CE35: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_CE3C;
label_CE37:;
    /* $CE37: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_CE39:;
    /* $CE39: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CE3A:;
    /* $CE3A: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_CE3C:; /* ChkVFBD */
    /* $CE3C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_CE3E:;
    /* $CE3E: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CE5C;
label_CE40:;
    /* $CE40: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x06); FLAG_NZ(g_cpu.A);
label_CE42:;
    /* $CE42: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xF0; g_cpu.C=(g_cpu.A>=0xF0)?1:0; FLAG_NZ(r&0xFF); }
label_CE44:;
    /* $CE44: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CE5C;
label_CE46:;
    /* $CE46: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0207); FLAG_NZ(g_cpu.A);
label_CE49:;
    /* $CE49: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CE4A:;
    /* $CE4A: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_CE4C:;
    /* $CE4C: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_CE4E:;
    /* $CE4E: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CE4F:;
    /* $CE4F: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x06); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CE51:;
    /* $CE51: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_CE58;
label_CE53:;
    /* $CE53: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_CE55:;
    /* $CE55: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CE56:;
    /* $CE56: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_CE58:; /* ChkFBCl */
    /* $CE58: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_CE5A:;
    /* $CE5A: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CE6F;
label_CE5C:; /* Chk2Ofs */
    /* $CE5C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x05); FLAG_NZ(g_cpu.A);
label_CE5E:;
    /* $CE5E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_CE60:;
    /* $CE60: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CE85;
label_CE62:;
    /* $CE62: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x05); FLAG_NZ(g_cpu.Y);
label_CE64:;
    /* $CE64: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_CE66:;
    /* $CE66: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CE67:;
    /* $CE67: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xCD3A + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CE6A:;
    /* $CE6A: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x05; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CE6C:;
    /* $CE6C: 4C */ maybe_trigger_vblank(3); goto label_CE32;
label_CE6F:; /* ChgSDir */
    /* $CE6F: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x01; FLAG_NZ(g_cpu.X);
label_CE71:;
    /* $CE71: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x04); FLAG_NZ(g_cpu.A);
label_CE73:;
    /* $CE73: C5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x06); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_CE75:;
    /* $CE75: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CE78;
label_CE77:;
    /* $CE77: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_CE78:; /* SetSDir */
    /* $CE78: 86 */ maybe_trigger_vblank(3); nes_write(0x46, g_cpu.X);
label_CE7A:;
    /* $CE7A: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_CE7C:;
    /* $CE7C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_CE7E:;
    /* $CE7E: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_CE7F:;
    /* $CE7F: 20 */ maybe_trigger_vblank(6); call_by_address(0xD92C);
label_CE82:;
    /* $CE82: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_CE83:;
    /* $CE83: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_CE85:; /* NoColFB */
    /* $CE85: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_CE86:;
    /* $CE86: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CE87:;
    /* $CE87: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_CE89:;
    /* $CE89: 85 */ maybe_trigger_vblank(3); nes_write(0x06, g_cpu.A);
label_CE8B:;
    /* $CE8B: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_CE8D:;
    /* $CE8D: 60 */ maybe_trigger_vblank(6);
    return;
label_CE8E:; /* GetFirebarPosition */
    /* $CE8E: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_CE8F:;
    /* $CE8F: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_CE91:;
    /* $CE91: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x09; g_cpu.C=(g_cpu.A>=0x09)?1:0; FLAG_NZ(r&0xFF); }
label_CE93:;
    /* $CE93: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CE9A;
label_CE95:;
    /* $CE95: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x0F; FLAG_NZ(g_cpu.A);
label_CE97:;
    /* $CE97: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CE98:;
    /* $CE98: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_CE9A:; /* GetHAdder */
    /* $CE9A: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_CE9C:;
    /* $CE9C: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x00); FLAG_NZ(g_cpu.Y);
label_CE9E:;
    /* $CE9E: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCD2E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CEA1:;
    /* $CEA1: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CEA2:;
    /* $CEA2: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x01); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CEA4:;
    /* $CEA4: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_CEA5:;
    /* $CEA5: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCCC7 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CEA8:;
    /* $CEA8: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_CEAA:;
    /* $CEAA: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_CEAB:;
    /* $CEAB: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_CEAC:;
    /* $CEAC: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CEAD:;
    /* $CEAD: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_CEAF:;
    /* $CEAF: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_CEB1:;
    /* $CEB1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x09; g_cpu.C=(g_cpu.A>=0x09)?1:0; FLAG_NZ(r&0xFF); }
label_CEB3:;
    /* $CEB3: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CEBA;
label_CEB5:;
    /* $CEB5: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x0F; FLAG_NZ(g_cpu.A);
label_CEB7:;
    /* $CEB7: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CEB8:;
    /* $CEB8: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_CEBA:; /* GetVAdder */
    /* $CEBA: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_CEBC:;
    /* $CEBC: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x00); FLAG_NZ(g_cpu.Y);
label_CEBE:;
    /* $CEBE: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCD2E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CEC1:;
    /* $CEC1: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CEC2:;
    /* $CEC2: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x02); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CEC4:;
    /* $CEC4: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_CEC5:;
    /* $CEC5: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCCC7 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CEC8:;
    /* $CEC8: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_CECA:;
    /* $CECA: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_CECB:;
    /* $CECB: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CECC:;
    /* $CECC: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CECD:;
    /* $CECD: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CECE:;
    /* $CECE: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_CECF:;
    /* $CECF: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCD2A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CED2:;
    /* $CED2: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_CED4:;
    /* $CED4: 60 */ maybe_trigger_vblank(6);
    return;
label_CED5:; /* PRandomSubtracter */
    /* $CED5: F8 */ maybe_trigger_vblank(2); g_cpu.D = 1;
label_CED6:;
    /* $CED6: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x70; FLAG_NZ(g_cpu.Y);
label_CED8:;
    /* $CED8: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x2000 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CEDB:;
    /* $CEDB: 20 */ maybe_trigger_vblank(6); call_by_address(0x0020);
label_CEDE:;
    /* $CEDE: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xCEDE); return;
label_CEDF:; /* MoveFlyingCheepCheep */
    /* $CEDF: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CEE1:;
    /* $CEE1: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_CEE3:;
    /* $CEE3: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CEED;
label_CEE5:;
    /* $CEE5: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_CEE7:;
    /* $CEE7: 9D */ maybe_trigger_vblank(5); nes_write((0x03C5 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_CEEA:;
    /* $CEEA: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF92); return;
label_CEED:; /* FlyCC */
    /* $CEED: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF02);
label_CEF0:;
    /* $CEF0: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x0D; FLAG_NZ(g_cpu.Y);
label_CEF2:;
    /* $CEF2: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_CEF4:;
    /* $CEF4: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF96);
label_CEF7:;
    /* $CEF7: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0434 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CEFA:;
    /* $CEFA: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CEFB:;
    /* $CEFB: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CEFC:;
    /* $CEFC: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CEFD:;
    /* $CEFD: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CEFE:;
    /* $CEFE: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_CEFF:;
    /* $CEFF: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CF01:;
    /* $CF01: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CF02:;
    /* $CF02: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xCED5 + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CF05:;
    /* $CF05: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_CF0C;
label_CF07:;
    /* $CF07: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_CF09:;
    /* $CF09: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CF0A:;
    /* $CF0A: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_CF0C:; /* AddCCF */
    /* $CF0C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_CF0E:;
    /* $CF0E: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_CF1E;
label_CF10:;
    /* $CF10: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0434 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CF13:;
    /* $CF13: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CF14:;
    /* $CF14: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x10 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x10); g_cpu.A=r&0xFF; }
label_CF16:;
    /* $CF16: 9D */ maybe_trigger_vblank(5); nes_write((0x0434 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_CF19:;
    /* $CF19: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CF1A:;
    /* $CF1A: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CF1B:;
    /* $CF1B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CF1C:;
    /* $CF1C: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CF1D:;
    /* $CF1D: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_CF1E:; /* BPGet */
    /* $CF1E: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCEDA + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CF21:;
    /* $CF21: 9D */ maybe_trigger_vblank(5); nes_write((0x03C5 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_CF24:;
    /* $CF24: 60 */ maybe_trigger_vblank(6);
    return;
label_CF25:; /* LakituDiffAdj */
    /* $CF25: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x30 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CF27:;
    /* $CF27: 40 */ maybe_trigger_vblank(6); /* RTI */ g_cpu.S++; { uint8_t p=g_ram[0x100+g_cpu.S]; g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1; g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; } g_cpu.S++; g_cpu.S++; /* pop PCL, PCH */
    return;
label_CF28:; /* MoveLakitu */
    /* $CF28: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CF2A:;
    /* $CF2A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_CF2C:;
    /* $CF2C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CF31;
label_CF2E:;
    /* $CF2E: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF63); return;
label_CF31:; /* ChkLS */
    /* $CF31: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CF33:;
    /* $CF33: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CF40;
label_CF35:;
    /* $CF35: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_CF37:;
    /* $CF37: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_CF39:;
    /* $CF39: 8D */ maybe_trigger_vblank(4); nes_write(0x06CB, g_cpu.A);
label_CF3C:;
    /* $CF3C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_CF3E:;
    /* $CF3E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CF53;
label_CF40:; /* Fr12S */
    /* $CF40: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x12; FLAG_NZ(g_cpu.A);
label_CF42:;
    /* $CF42: 8D */ maybe_trigger_vblank(4); nes_write(0x06CB, g_cpu.A);
label_CF45:;
    /* $CF45: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_CF47:; /* LdLDa */
    /* $CF47: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF25 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CF4A:;
    /* $CF4A: 99 */ maybe_trigger_vblank(5); nes_write((0x0001 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_CF4D:;
    /* $CF4D: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CF4E:;
    /* $CF4E: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_CF47;
    }
label_CF50:;
    /* $CF50: 20 */ maybe_trigger_vblank(6); call_by_address(0xCF6C);
label_CF53:; /* SetLSpd */
    /* $CF53: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_CF55:;
    /* $CF55: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_CF57:;
    /* $CF57: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CF59:;
    /* $CF59: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_CF5B:;
    /* $CF5B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CF67;
label_CF5D:;
    /* $CF5D: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CF5F:;
    /* $CF5F: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_CF61:;
    /* $CF61: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CF62:;
    /* $CF62: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_CF64:;
    /* $CF64: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_CF66:;
    /* $CF66: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CF67:; /* SetLMov */
    /* $CF67: 94 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.Y);
label_CF69:;
    /* $CF69: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF02); return;
label_CF6C:; /* PlayerLakituDiff */
    /* $CF6C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_CF6E:;
    /* $CF6E: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_CF71:;
    /* $CF71: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_CF7D;
label_CF73:;
    /* $CF73: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CF74:;
    /* $CF74: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_CF76:;
    /* $CF76: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_CF78:;
    /* $CF78: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CF79:;
    /* $CF79: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_CF7B:;
    /* $CF7B: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_CF7D:; /* ChkLakDif */
    /* $CF7D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_CF7F:;
    /* $CF7F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x3C; g_cpu.C=(g_cpu.A>=0x3C)?1:0; FLAG_NZ(r&0xFF); }
label_CF81:;
    /* $CF81: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CF9F;
label_CF83:;
    /* $CF83: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x3C; FLAG_NZ(g_cpu.A);
label_CF85:;
    /* $CF85: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_CF87:;
    /* $CF87: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CF89:;
    /* $CF89: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_CF8B:;
    /* $CF8B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CF9F;
label_CF8D:;
    /* $CF8D: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_CF8E:;
    /* $CF8E: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xA0 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_CF90:;
    /* $CF90: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CF9F;
label_CF92:;
    /* $CF92: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CF94:;
    /* $CF94: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CF9C;
label_CF96:;
    /* $CF96: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0x58 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CF98:;
    /* $CF98: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CF9A:;
    /* $CF9A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CFDC;
label_CF9C:; /* SetLMovD */
    /* $CF9C: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_CF9D:;
    /* $CF9D: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_CF9F:; /* ChkPSpeed */
    /* $CF9F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_CFA1:;
    /* $CFA1: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3C; FLAG_NZ(g_cpu.A);
label_CFA3:;
    /* $CFA3: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CFA4:;
    /* $CFA4: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_CFA5:;
    /* $CFA5: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_CFA7:;
    /* $CFA7: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_CFA9:;
    /* $CFA9: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x57); FLAG_NZ(g_cpu.A);
label_CFAB:;
    /* $CFAB: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CFD1;
label_CFAD:;
    /* $CFAD: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0775); FLAG_NZ(g_cpu.A);
label_CFB0:;
    /* $CFB0: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CFD1;
label_CFB2:;
    /* $CFB2: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CFB3:;
    /* $CFB3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x57); FLAG_NZ(g_cpu.A);
label_CFB5:;
    /* $CFB5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x19; g_cpu.C=(g_cpu.A>=0x19)?1:0; FLAG_NZ(r&0xFF); }
label_CFB7:;
    /* $CFB7: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CFC1;
label_CFB9:;
    /* $CFB9: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0775); FLAG_NZ(g_cpu.A);
label_CFBC:;
    /* $CFBC: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_CFBE:;
    /* $CFBE: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CFC1;
label_CFC0:;
    /* $CFC0: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CFC1:; /* ChkSpinyO */
    /* $CFC1: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CFC3:;
    /* $CFC3: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x12; g_cpu.C=(g_cpu.A>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_CFC5:;
    /* $CFC5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CFCB;
label_CFC7:;
    /* $CFC7: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x57); FLAG_NZ(g_cpu.A);
label_CFC9:;
    /* $CFC9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CFD1;
label_CFCB:; /* ChkEmySpd */
    /* $CFCB: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CFCD:;
    /* $CFCD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_CFD1;
label_CFCF:;
    /* $CFCF: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_CFD1:; /* SubDifAdj */
    /* $CFD1: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0001 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CFD4:;
    /* $CFD4: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x00); FLAG_NZ(g_cpu.Y);
label_CFD6:; /* SPixelLak */
    /* $CFD6: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CFD7:;
    /* $CFD7: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x01; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CFD9:;
    /* $CFD9: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_CFDA:;
    /* $CFDA: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_CFD6;
    }
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_CFDC:; /* ExMoveLak */
    /* $CFDC: 60 */ maybe_trigger_vblank(6);
    return;
label_CFDD:; /* BridgeCollapseData */
    /* $CFDD: 1A */ maybe_trigger_vblank(2); /* NOP */
label_CFDE:;
    /* $CFDE: 58 */ maybe_trigger_vblank(2); g_cpu.I = 0;
label_CFDF:;
    /* $CFDF: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_CFE0:;
    /* $CFE0: 96 */ maybe_trigger_vblank(4); nes_write((0x94 + g_cpu.Y) & 0xFF, g_cpu.X);
label_CFE2:;
    /* $CFE2: 92 */ maybe_trigger_vblank(2); /* ILLEGAL $92 — skip 1 */
label_CFE3:;
    /* $CFE3: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_CF73;
    }
label_CFE5:;
    /* $CFE5: 8C */ maybe_trigger_vblank(4); nes_write(0x888A, g_cpu.Y);
label_CFE8:;
    /* $CFE8: 86 */ maybe_trigger_vblank(3); nes_write(0x84, g_cpu.X);
label_CFEA:;
    /* $CFEA: 82 */ maybe_trigger_vblank(2); /* NOP */
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
label_D061:; /* PRandomRange */
    /* $D061: 21 */ maybe_trigger_vblank(6); g_cpu.A &= nes_read(nes_read16zp((0x41 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_D063:;
    /* $D063: 11 */ maybe_trigger_vblank(5); g_cpu.A |= nes_read((nes_read16zp(0x31) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
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
    /* $D06F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D00F;
    }
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
label_D1BC:; /* ProcessBowserHalf */
    /* $D1BC: EE */ maybe_trigger_vblank(6); { uint16_t a=0x036A; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D1BF:;
    /* $D1BF: 20 */ maybe_trigger_vblank(6); call_by_address(0xC8D7);
label_D1C2:;
    /* $D1C2: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D1C4:;
    /* $D1C4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D1BB;
    }
label_D1C6:;
    /* $D1C6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_D1C8:;
    /* $D1C8: 9D */ maybe_trigger_vblank(5); nes_write((0x049A + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D1CB:;
    /* $D1CB: 20 */ maybe_trigger_vblank(6); call_by_address(0xE243);
label_D1CE:;
    /* $D1CE: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD853); return;
label_D1D1:; /* FlameTimerData */
    /* $D1D1: BF */ maybe_trigger_vblank(4); g_cpu.A = g_cpu.X = nes_read((0xBF40 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D1D4:;
    /* $D1D4: BF */ maybe_trigger_vblank(4); g_cpu.A = g_cpu.X = nes_read((0x40BF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D1D7:;
    /* $D1D7: 40 */ maybe_trigger_vblank(6); /* RTI */ g_cpu.S++; { uint8_t p=g_ram[0x100+g_cpu.S]; g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1; g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; } g_cpu.S++; g_cpu.S++; /* pop PCL, PCH */
    return;
label_D1D8:;
    /* $D1D8: BF */ maybe_trigger_vblank(4); g_cpu.A = g_cpu.X = nes_read((0x67AC + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D1DB:;
    /* $D1DB: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_D1DD:;
    /* $D1DD: 67 */ maybe_trigger_vblank(5); /* ILLEGAL $67 — skip 2 */
label_D1DF:;
    /* $D1DF: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0367); FLAG_NZ(g_cpu.A);
label_D1E2:;
    /* $D1E2: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_D1E4:;
    /* $D1E4: 8D */ maybe_trigger_vblank(4); nes_write(0x0367, g_cpu.A);
label_D1E7:;
    /* $D1E7: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD1D1 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D1EA:; /* ExFl */
    /* $D1EA: 60 */ maybe_trigger_vblank(6);
    return;
label_D1EB:; /* ProcBowserFlame */
    /* $D1EB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_D1EE:;
    /* $D1EE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D220;
label_D1F0:;
    /* $D1F0: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_D1F2:;
    /* $D1F2: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06CC); FLAG_NZ(g_cpu.Y);
label_D1F5:;
    /* $D1F5: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D1F9;
label_D1F7:;
    /* $D1F7: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x60; FLAG_NZ(g_cpu.A);
label_D1F9:; /* SFlmX */
    /* $D1F9: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_D1FB:;
    /* $D1FB: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0401 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D1FE:;
    /* $D1FE: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_D1FF:;
    /* $D1FF: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D201:;
    /* $D201: 9D */ maybe_trigger_vblank(5); nes_write((0x0401 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D204:;
    /* $D204: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D206:;
    /* $D206: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x01; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D208:;
    /* $D208: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_D20A:;
    /* $D20A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D20C:;
    /* $D20C: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D20E:;
    /* $D20E: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_D210:;
    /* $D210: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x0417 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_D213:;
    /* $D213: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D215:;
    /* $D215: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xC59D + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D218:;
    /* $D218: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D220;
label_D21A:;
    /* $D21A: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D21B:;
    /* $D21B: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x0434 + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D21E:;
    /* $D21E: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_D220:; /* SetGfxF */
    /* $D220: 20 */ maybe_trigger_vblank(6); call_by_address(0xF152);
label_D223:;
    /* $D223: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D225:;
    /* $D225: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D1EA;
    }
label_D227:;
    /* $D227: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x51; FLAG_NZ(g_cpu.A);
label_D229:;
    /* $D229: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_D22B:;
    /* $D22B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_D22D:;
    /* $D22D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_D22F:;
    /* $D22F: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_D231:;
    /* $D231: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D235;
label_D233:;
    /* $D233: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x82; FLAG_NZ(g_cpu.Y);
label_D235:; /* FlmeAt */
    /* $D235: 84 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.Y);
label_D237:;
    /* $D237: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_D23A:;
    /* $D23A: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_D23C:; /* DrawFlameLoop */
    /* $D23C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B9); FLAG_NZ(g_cpu.A);
label_D23F:;
    /* $D23F: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D242:;
    /* $D242: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_D244:;
    /* $D244: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D247:;
    /* $D247: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D249:;
    /* $D249: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_D24B:;
    /* $D24B: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D24E:;
    /* $D24E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_D251:;
    /* $D251: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D254:;
    /* $D254: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D255:;
    /* $D255: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_D257:;
    /* $D257: 8D */ maybe_trigger_vblank(4); nes_write(0x03AE, g_cpu.A);
label_D25A:;
    /* $D25A: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D25B:;
    /* $D25B: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D25C:;
    /* $D25C: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D25D:;
    /* $D25D: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D25E:;
    /* $D25E: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_D25F:;
    /* $D25F: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x03; g_cpu.C=(g_cpu.X>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_D261:;
    /* $D261: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D23C;
    }
label_D263:;
    /* $D263: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D265:;
    /* $D265: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1AF);
label_D268:;
    /* $D268: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_D26B:;
    /* $D26B: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D1); FLAG_NZ(g_cpu.A);
label_D26E:;
    /* $D26E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_D26F:;
    /* $D26F: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_D270:;
    /* $D270: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D277;
label_D272:;
    /* $D272: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_D274:;
    /* $D274: 99 */ maybe_trigger_vblank(5); nes_write((0x020C + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D277:; /* M3FOfs */
    /* $D277: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_D278:;
    /* $D278: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_D279:;
    /* $D279: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_D27A:;
    /* $D27A: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D281;
label_D27C:;
    /* $D27C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_D27E:;
    /* $D27E: 99 */ maybe_trigger_vblank(5); nes_write((0x0208 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D281:; /* M2FOfs */
    /* $D281: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_D282:;
    /* $D282: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_D283:;
    /* $D283: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_D284:;
    /* $D284: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D28B;
label_D286:;
    /* $D286: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_D288:;
    /* $D288: 99 */ maybe_trigger_vblank(5); nes_write((0x0204 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D28B:; /* M1FOfs */
    /* $D28B: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_D28C:;
    /* $D28C: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_D28D:;
    /* $D28D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D294;
label_D28F:;
    /* $D28F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_D291:;
    /* $D291: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D294:; /* ExFlmeD */
    /* $D294: 60 */ maybe_trigger_vblank(6);
    return;
label_D295:; /* RunFireworks */
    /* $D295: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0xA0 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D297:;
    /* $D297: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D2A5;
label_D299:;
    /* $D299: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_D29B:;
    /* $D29B: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_D29D:;
    /* $D29D: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0x58 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D29F:;
    /* $D29F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D2A1:;
    /* $D2A1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_D2A3:;
    /* $D2A3: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D2BD;
label_D2A5:; /* SetupExpl */
    /* $D2A5: 20 */ maybe_trigger_vblank(6); call_by_address(0xF152);
label_D2A8:;
    /* $D2A8: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B9); FLAG_NZ(g_cpu.A);
label_D2AB:;
    /* $D2AB: 8D */ maybe_trigger_vblank(4); nes_write(0x03BA, g_cpu.A);
label_D2AE:;
    /* $D2AE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_D2B1:;
    /* $D2B1: 8D */ maybe_trigger_vblank(4); nes_write(0x03AF, g_cpu.A);
label_D2B4:;
    /* $D2B4: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_D2B7:;
    /* $D2B7: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D2B9:;
    /* $D2B9: 20 */ maybe_trigger_vblank(6); call_by_address(0xED17);
label_D2BC:;
    /* $D2BC: 60 */ maybe_trigger_vblank(6);
    return;
label_D2BD:; /* FireworksSoundScore */
    /* $D2BD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_D2BF:;
    /* $D2BF: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_D2C1:;
    /* $D2C1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_D2C3:;
    /* $D2C3: 85 */ maybe_trigger_vblank(3); nes_write(0xFE, g_cpu.A);
label_D2C5:;
    /* $D2C5: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_D2C7:;
    /* $D2C7: 8D */ maybe_trigger_vblank(4); nes_write(0x0138, g_cpu.A);
label_D2CA:;
    /* $D2CA: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD336); return;
label_D2CD:; /* StarFlagYPosAdder */
    /* $D2CD: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xD2CD); return;
label_D2CE:;
    /* $D2CE: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xD2CE); return;
label_D2CF:;
    /* $D2CF: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_D2D0:;
    /* $D2D0: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_D2D1:; /* StarFlagXPosAdder */
    /* $D2D1: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xD2D1); return;
label_D2D2:;
    /* $D2D2: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_D2D3:;
    /* $D2D3: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xD2D3); return;
label_D2D4:;
    /* $D2D4: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_D2D5:; /* StarFlagTileData */
    /* $D2D5: 54 */ maybe_trigger_vblank(4); (void)nes_read((0x55 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_D2D7:;
    /* $D2D7: 56 */ maybe_trigger_vblank(6); { uint16_t a=(0x57 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_D2D9:; /* RunStarFlagObj */
    /* $D2D9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_D2DB:;
    /* $D2DB: 8D */ maybe_trigger_vblank(4); nes_write(0x06CB, g_cpu.A);
label_D2DE:;
    /* $D2DE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0746); FLAG_NZ(g_cpu.A);
label_D2E1:;
    /* $D2E1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_D2E3:;
    /* $D2E3: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D311;
label_D2E5:;
    /* $D2E5: 20 */ maybe_trigger_vblank(6); /* inline_dispatch $8E04: 5 entries (bank=-1) */
switch(g_cpu.A) {
  case 0: call_by_address(0xD311); return;
  case 1: call_by_address(0xD2F2); return;
  case 2: call_by_address(0xD312); return;
  case 3: call_by_address(0xD34E); return;
  case 4: call_by_address(0xD3A2); return;
  default: nes_log_inline_miss(0xD2E5, g_cpu.A); return;
}
label_D2F2:; /* GameTimerFireworks */
    /* $D2F2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x05; FLAG_NZ(g_cpu.Y);
label_D2F4:;
    /* $D2F4: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07FA); FLAG_NZ(g_cpu.A);
label_D2F7:;
    /* $D2F7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_D2F9:;
    /* $D2F9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D309;
label_D2FB:;
    /* $D2FB: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x03; FLAG_NZ(g_cpu.Y);
label_D2FD:;
    /* $D2FD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_D2FF:;
    /* $D2FF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D309;
label_D301:;
    /* $D301: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_D303:;
    /* $D303: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_D305:;
    /* $D305: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D309;
label_D307:;
    /* $D307: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_D309:; /* SetFWC */
    /* $D309: 8D */ maybe_trigger_vblank(4); nes_write(0x06D7, g_cpu.A);
label_D30C:;
    /* $D30C: 94 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.Y);
label_D30E:; /* IncrementSFTask1 */
    /* $D30E: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0746; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D311:; /* StarFlagExit */
    /* $D311: 60 */ maybe_trigger_vblank(6);
    return;
label_D312:; /* AwardGameTimerPoints */
    /* $D312: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07F8); FLAG_NZ(g_cpu.A);
label_D315:;
    /* $D315: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x07F9); FLAG_NZ(g_cpu.A);
label_D318:;
    /* $D318: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x07FA); FLAG_NZ(g_cpu.A);
label_D31B:;
    /* $D31B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D30E;
    }
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
label_D34E:; /* RaiseFlagSetoffFWorks */
    /* $D34E: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D350:;
    /* $D350: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x72; g_cpu.C=(g_cpu.A>=0x72)?1:0; FLAG_NZ(r&0xFF); }
label_D352:;
    /* $D352: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D359;
label_D354:;
    /* $D354: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0xCF + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D356:;
    /* $D356: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD365); return;
label_D359:; /* SetoffF */
    /* $D359: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06D7); FLAG_NZ(g_cpu.A);
label_D35C:;
    /* $D35C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D396;
label_D35E:;
    /* $D35E: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D396;
label_D360:;
    /* $D360: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x16; FLAG_NZ(g_cpu.A);
label_D362:;
    /* $D362: 8D */ maybe_trigger_vblank(4); nes_write(0x06CB, g_cpu.A);
label_D365:; /* DrawStarFlag */
    /* $D365: 20 */ maybe_trigger_vblank(6); call_by_address(0xF152);
label_D368:;
    /* $D368: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_D36B:;
    /* $D36B: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_D36D:; /* DSFLoop */
    /* $D36D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B9); FLAG_NZ(g_cpu.A);
label_D370:;
    /* $D370: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D371:;
    /* $D371: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xD2CD + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D374:;
    /* $D374: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D377:;
    /* $D377: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD2D5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D37A:;
    /* $D37A: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D37D:;
    /* $D37D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x22; FLAG_NZ(g_cpu.A);
label_D37F:;
    /* $D37F: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D382:;
    /* $D382: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_D385:;
    /* $D385: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D386:;
    /* $D386: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xD2D1 + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D389:;
    /* $D389: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D38C:;
    /* $D38C: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D38D:;
    /* $D38D: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D38E:;
    /* $D38E: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D38F:;
    /* $D38F: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_D390:;
    /* $D390: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_D391:;
    /* $D391: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D36D;
    }
label_D393:;
    /* $D393: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D395:;
    /* $D395: 60 */ maybe_trigger_vblank(6);
    return;
label_D396:; /* DrawFlagSetTimer */
    /* $D396: 20 */ maybe_trigger_vblank(6); call_by_address(0xD365);
label_D399:;
    /* $D399: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_D39B:;
    /* $D39B: 9D */ maybe_trigger_vblank(5); nes_write((0x0796 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D39E:; /* IncrementSFTask2 */
    /* $D39E: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0746; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D3A1:;
    /* $D3A1: 60 */ maybe_trigger_vblank(6);
    return;
label_D3A2:; /* DelayToAreaEnd */
    /* $D3A2: 20 */ maybe_trigger_vblank(6); call_by_address(0xD365);
label_D3A5:;
    /* $D3A5: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0796 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D3A8:;
    /* $D3A8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D3AF;
label_D3AA:;
    /* $D3AA: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_D3AD:;
    /* $D3AD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D39E;
    }
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D3AF:; /* StarFlagExit2 */
    /* $D3AF: 60 */ maybe_trigger_vblank(6);
    return;
label_D3B0:; /* MovePiranhaPlant */
    /* $D3B0: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D3B2:;
    /* $D3B2: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D40A;
label_D3B4:;
    /* $D3B4: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x078A + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D3B7:;
    /* $D3B7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D40A;
label_D3B9:;
    /* $D3B9: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D3BB:;
    /* $D3BB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D3E0;
label_D3BD:;
    /* $D3BD: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D3BF:;
    /* $D3BF: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D3D5;
label_D3C1:;
    /* $D3C1: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_D3C4:;
    /* $D3C4: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_D3CF;
label_D3C6:;
    /* $D3C6: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_D3C8:;
    /* $D3C8: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_D3CA:;
    /* $D3CA: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D3CB:;
    /* $D3CB: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_D3CD:;
    /* $D3CD: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_D3CF:; /* ChkPlayerNearPipe */
    /* $D3CF: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_D3D1:;
    /* $D3D1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x21; g_cpu.C=(g_cpu.A>=0x21)?1:0; FLAG_NZ(r&0xFF); }
label_D3D3:;
    /* $D3D3: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D40A;
label_D3D5:; /* ReversePlantSpeed */
    /* $D3D5: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D3D7:;
    /* $D3D7: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_D3D9:;
    /* $D3D9: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D3DA:;
    /* $D3DA: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_D3DC:;
    /* $D3DC: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_D3DE:;
    /* $D3DE: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0xA0 + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D3E0:; /* SetupToMovePPlant */
    /* $D3E0: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0434 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D3E3:;
    /* $D3E3: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_D3E5:;
    /* $D3E5: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_D3EA;
label_D3E7:;
    /* $D3E7: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0417 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D3EA:; /* RiseFallPiranhaPlant */
    /* $D3EA: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_D3EC:;
    /* $D3EC: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_D3EE:;
    /* $D3EE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_D3EF:;
    /* $D3EF: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D40A;
label_D3F1:;
    /* $D3F1: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_D3F4:;
    /* $D3F4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D40A;
label_D3F6:;
    /* $D3F6: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D3F8:;
    /* $D3F8: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D3F9:;
    /* $D3F9: 75 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x58 + g_cpu.X) & 0xFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D3FB:;
    /* $D3FB: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_D3FD:;
    /* $D3FD: C5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D3FF:;
    /* $D3FF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D40A;
label_D401:;
    /* $D401: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_D403:;
    /* $D403: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_D405:;
    /* $D405: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_D407:;
    /* $D407: 9D */ maybe_trigger_vblank(5); nes_write((0x078A + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D40A:; /* PutinPipe */
    /* $D40A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_D40C:;
    /* $D40C: 9D */ maybe_trigger_vblank(5); nes_write((0x03C5 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D40F:;
    /* $D40F: 60 */ maybe_trigger_vblank(6);
    return;
label_D410:; /* FirebarSpin */
    /* $D410: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_D412:;
    /* $D412: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x34 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D414:;
    /* $D414: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D424;
label_D416:;
    /* $D416: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x18; FLAG_NZ(g_cpu.Y);
label_D418:;
    /* $D418: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D41A:;
    /* $D41A: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D41B:;
    /* $D41B: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x07); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D41D:;
    /* $D41D: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_D41F:;
    /* $D41F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D421:;
    /* $D421: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_D423:;
    /* $D423: 60 */ maybe_trigger_vblank(6);
    return;
label_D424:; /* SpinCounterClockwise */
    /* $D424: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x08; FLAG_NZ(g_cpu.Y);
label_D426:;
    /* $D426: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D428:;
    /* $D428: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_D429:;
    /* $D429: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x07); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D42B:;
    /* $D42B: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_D42D:;
    /* $D42D: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D42F:;
    /* $D42F: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D431:;
    /* $D431: 60 */ maybe_trigger_vblank(6);
    return;
label_D432:; /* BalancePlatform */
    /* $D432: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xB6 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D434:;
    /* $D434: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_D436:;
    /* $D436: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D43B;
label_D438:;
    /* $D438: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC998); return;
label_D43B:; /* DoBPl */
    /* $D43B: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D43D:;
    /* $D43D: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_D440;
label_D43F:;
    /* $D43F: 60 */ maybe_trigger_vblank(6);
    return;
label_D440:; /* CheckBalPlatform */
    /* $D440: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_D441:;
    /* $D441: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03A2 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D444:;
    /* $D444: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_D446:;
    /* $D446: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D448:;
    /* $D448: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D44D;
label_D44A:;
    /* $D44A: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD5BB); return;
label_D44D:; /* ChkForFall */
    /* $D44D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2D; FLAG_NZ(g_cpu.A);
label_D44F:;
    /* $D44F: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xCF + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D451:;
    /* $D451: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D462;
label_D453:;
    /* $D453: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D455:;
    /* $D455: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D45F;
label_D457:;
    /* $D457: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D458:;
    /* $D458: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x02 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x02); g_cpu.A=r&0xFF; }
label_D45A:;
    /* $D45A: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_D45C:;
    /* $D45C: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD5B1); return;
label_D45F:; /* MakePlatformFall */
    /* $D45F: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD598); return;
label_D462:; /* ChkOtherForFall */
    /* $D462: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x00CF + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D465:;
    /* $D465: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D474;
label_D467:;
    /* $D467: E4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); int r=g_cpu.X-m; g_cpu.C=(g_cpu.X>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D469:;
    /* $D469: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D45F;
    }
label_D46B:;
    /* $D46B: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D46C:;
    /* $D46C: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x02 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x02); g_cpu.A=r&0xFF; }
label_D46E:;
    /* $D46E: 99 */ maybe_trigger_vblank(5); nes_write((0x00CF + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D471:;
    /* $D471: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD5B1); return;
label_D474:; /* ChkToMoveBalPlat */
    /* $D474: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D476:;
    /* $D476: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_D477:;
    /* $D477: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03A2 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D47A:;
    /* $D47A: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_D494;
label_D47C:;
    /* $D47C: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0434 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D47F:;
    /* $D47F: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D480:;
    /* $D480: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x05 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x05); g_cpu.A=r&0xFF; }
label_D482:;
    /* $D482: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_D484:;
    /* $D484: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D486:;
    /* $D486: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_D488:;
    /* $D488: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D4A4;
label_D48A:;
    /* $D48A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D498;
label_D48C:;
    /* $D48C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_D48E:;
    /* $D48E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0B; g_cpu.C=(g_cpu.A>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_D490:;
    /* $D490: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D49E;
label_D492:;
    /* $D492: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D498;
label_D494:; /* ColFlg */
    /* $D494: C5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x08); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D496:;
    /* $D496: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D4A4;
label_D498:; /* PlatUp */
    /* $D498: 20 */ maybe_trigger_vblank(6); call_by_address(0xBFB7);
label_D49B:;
    /* $D49B: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD4A7); return;
label_D49E:; /* PlatSt */
    /* $D49E: 20 */ maybe_trigger_vblank(6); call_by_address(0xD5B1);
label_D4A1:;
    /* $D4A1: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD4A7); return;
label_D4A4:; /* PlatDn */
    /* $D4A4: 20 */ maybe_trigger_vblank(6); call_by_address(0xBFB4);
label_D4A7:; /* DoOtherPlatform */
    /* $D4A7: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_D4A9:;
    /* $D4A9: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_D4AA:;
    /* $D4AA: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_D4AB:;
    /* $D4AB: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xCF + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D4AD:;
    /* $D4AD: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D4AE:;
    /* $D4AE: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x00CF + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D4B1:;
    /* $D4B1: 99 */ maybe_trigger_vblank(5); nes_write((0x00CF + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D4B4:;
    /* $D4B4: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03A2 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D4B7:;
    /* $D4B7: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D4BD;
label_D4B9:;
    /* $D4B9: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_D4BA:;
    /* $D4BA: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC21);
label_D4BD:; /* DrawEraseRope */
    /* $D4BD: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x08); FLAG_NZ(g_cpu.Y);
label_D4BF:;
    /* $D4BF: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x00A0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D4C2:;
    /* $D4C2: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x0434 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D4C5:;
    /* $D4C5: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D53E;
label_D4C7:;
    /* $D4C7: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x0300); FLAG_NZ(g_cpu.X);
label_D4CA:;
    /* $D4CA: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x20; g_cpu.C=(g_cpu.X>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_D4CC:;
    /* $D4CC: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D53E;
label_D4CE:;
    /* $D4CE: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x00A0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D4D1:;
    /* $D4D1: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_D4D2:;
    /* $D4D2: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_D4D3:;
    /* $D4D3: 20 */ maybe_trigger_vblank(6); call_by_address(0xD541);
label_D4D6:;
    /* $D4D6: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_D4D8:;
    /* $D4D8: 9D */ maybe_trigger_vblank(5); nes_write((0x0301 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D4DB:;
    /* $D4DB: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_D4DD:;
    /* $D4DD: 9D */ maybe_trigger_vblank(5); nes_write((0x0302 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D4E0:;
    /* $D4E0: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_D4E2:;
    /* $D4E2: 9D */ maybe_trigger_vblank(5); nes_write((0x0303 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D4E5:;
    /* $D4E5: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x00A0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D4E8:;
    /* $D4E8: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D4F7;
label_D4EA:;
    /* $D4EA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA2; FLAG_NZ(g_cpu.A);
label_D4EC:;
    /* $D4EC: 9D */ maybe_trigger_vblank(5); nes_write((0x0304 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D4EF:;
    /* $D4EF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA3; FLAG_NZ(g_cpu.A);
label_D4F1:;
    /* $D4F1: 9D */ maybe_trigger_vblank(5); nes_write((0x0305 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D4F4:;
    /* $D4F4: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD4FF); return;
label_D4F7:; /* EraseR1 */
    /* $D4F7: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x24; FLAG_NZ(g_cpu.A);
label_D4F9:;
    /* $D4F9: 9D */ maybe_trigger_vblank(5); nes_write((0x0304 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D4FC:;
    /* $D4FC: 9D */ maybe_trigger_vblank(5); nes_write((0x0305 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D4FF:; /* OtherRope */
    /* $D4FF: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x001E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D502:;
    /* $D502: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_D503:;
    /* $D503: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_D504:;
    /* $D504: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_D506:;
    /* $D506: 20 */ maybe_trigger_vblank(6); call_by_address(0xD541);
label_D509:;
    /* $D509: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_D50B:;
    /* $D50B: 9D */ maybe_trigger_vblank(5); nes_write((0x0306 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D50E:;
    /* $D50E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_D510:;
    /* $D510: 9D */ maybe_trigger_vblank(5); nes_write((0x0307 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D513:;
    /* $D513: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_D515:;
    /* $D515: 9D */ maybe_trigger_vblank(5); nes_write((0x0308 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D518:;
    /* $D518: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_D519:;
    /* $D519: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_D528;
label_D51B:;
    /* $D51B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA2; FLAG_NZ(g_cpu.A);
label_D51D:;
    /* $D51D: 9D */ maybe_trigger_vblank(5); nes_write((0x0309 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D520:;
    /* $D520: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA3; FLAG_NZ(g_cpu.A);
label_D522:;
    /* $D522: 9D */ maybe_trigger_vblank(5); nes_write((0x030A + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D525:;
    /* $D525: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD530); return;
label_D528:; /* EraseR2 */
    /* $D528: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x24; FLAG_NZ(g_cpu.A);
label_D52A:;
    /* $D52A: 9D */ maybe_trigger_vblank(5); nes_write((0x0309 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D52D:;
    /* $D52D: 9D */ maybe_trigger_vblank(5); nes_write((0x030A + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D530:; /* EndRp */
    /* $D530: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_D532:;
    /* $D532: 9D */ maybe_trigger_vblank(5); nes_write((0x030B + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D535:;
    /* $D535: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0300); FLAG_NZ(g_cpu.A);
label_D538:;
    /* $D538: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D539:;
    /* $D539: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x0A + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0A); g_cpu.A=r&0xFF; }
label_D53B:;
    /* $D53B: 8D */ maybe_trigger_vblank(4); nes_write(0x0300, g_cpu.A);
label_D53E:; /* ExitRp */
    /* $D53E: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D540:;
    /* $D540: 60 */ maybe_trigger_vblank(6);
    return;
label_D541:; /* SetupPlatformRope */
    /* $D541: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_D542:;
    /* $D542: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0087 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D545:;
    /* $D545: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D546:;
    /* $D546: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_D548:;
    /* $D548: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x06CC); FLAG_NZ(g_cpu.X);
label_D54B:;
    /* $D54B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D550;
label_D54D:;
    /* $D54D: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D54E:;
    /* $D54E: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x10 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x10); g_cpu.A=r&0xFF; }
label_D550:; /* GetLRp */
    /* $D550: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_D551:;
    /* $D551: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x006E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D554:;
    /* $D554: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_D556:;
    /* $D556: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_D558:;
    /* $D558: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_D559:;
    /* $D559: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF0; FLAG_NZ(g_cpu.A);
label_D55B:;
    /* $D55B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_D55C:;
    /* $D55C: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_D55D:;
    /* $D55D: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_D55E:;
    /* $D55E: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_D560:;
    /* $D560: B6 */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xCF + g_cpu.Y) & 0xFF); FLAG_NZ(g_cpu.X);
label_D562:;
    /* $D562: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_D563:;
    /* $D563: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_D56A;
label_D565:;
    /* $D565: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_D566:;
    /* $D566: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D567:;
    /* $D567: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_D569:;
    /* $D569: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_D56A:; /* GetHRp */
    /* $D56A: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_D56B:;
    /* $D56B: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x0300); FLAG_NZ(g_cpu.X);
label_D56E:;
    /* $D56E: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D56F:;
    /* $D56F: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_D570:;
    /* $D570: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_D571:;
    /* $D571: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_D572:;
    /* $D572: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_D574:;
    /* $D574: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x20; FLAG_NZ(g_cpu.A);
label_D576:;
    /* $D576: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_D578:;
    /* $D578: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_D57A:;
    /* $D57A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_D57C:;
    /* $D57C: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D57D:;
    /* $D57D: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D57E:;
    /* $D57E: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x01); FLAG_NZ(g_cpu.A);
label_D580:;
    /* $D580: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_D582:;
    /* $D582: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_D583:;
    /* $D583: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xE0; FLAG_NZ(g_cpu.A);
label_D585:;
    /* $D585: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D586:;
    /* $D586: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D588:;
    /* $D588: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_D58A:;
    /* $D58A: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x00CF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D58D:;
    /* $D58D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xE8; g_cpu.C=(g_cpu.A>=0xE8)?1:0; FLAG_NZ(r&0xFF); }
label_D58F:;
    /* $D58F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D597;
label_D591:;
    /* $D591: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_D593:;
    /* $D593: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xBF; FLAG_NZ(g_cpu.A);
label_D595:;
    /* $D595: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D597:; /* ExPRp */
    /* $D597: 60 */ maybe_trigger_vblank(6);
    return;
label_D598:; /* InitPlatformFall */
    /* $D598: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_D599:;
    /* $D599: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_D59A:;
    /* $D59A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1AF);
label_D59D:;
    /* $D59D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_D59F:;
    /* $D59F: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_D5A2:;
    /* $D5A2: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AD); FLAG_NZ(g_cpu.A);
label_D5A5:;
    /* $D5A5: 9D */ maybe_trigger_vblank(5); nes_write((0x0117 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D5A8:;
    /* $D5A8: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_D5AA:;
    /* $D5AA: 9D */ maybe_trigger_vblank(5); nes_write((0x011E + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D5AD:;
    /* $D5AD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_D5AF:;
    /* $D5AF: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_D5B1:; /* StopPlatforms */
    /* $D5B1: 20 */ maybe_trigger_vblank(6); call_by_address(0xC363);
label_D5B4:;
    /* $D5B4: 99 */ maybe_trigger_vblank(5); nes_write((0x00A0 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D5B7:;
    /* $D5B7: 99 */ maybe_trigger_vblank(5); nes_write((0x0434 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_D5BA:;
    /* $D5BA: 60 */ maybe_trigger_vblank(6);
    return;
label_D5BB:; /* PlatformFall */
    /* $D5BB: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_D5BC:;
    /* $D5BC: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_D5BD:;
    /* $D5BD: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF6B);
label_D5C0:;
    /* $D5C0: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_D5C1:;
    /* $D5C1: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_D5C2:;
    /* $D5C2: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF6B);
label_D5C5:;
    /* $D5C5: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D5C7:;
    /* $D5C7: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03A2 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D5CA:;
    /* $D5CA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D5D0;
label_D5CC:;
    /* $D5CC: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_D5CD:;
    /* $D5CD: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC21);
label_D5D0:; /* ExPF */
    /* $D5D0: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D5D2:;
    /* $D5D2: 60 */ maybe_trigger_vblank(6);
    return;
label_D5D3:; /* YMovingPlatform */
    /* $D5D3: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D5D5:;
    /* $D5D5: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x0434 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D5D8:;
    /* $D5D8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D5EF;
label_D5DA:;
    /* $D5DA: 9D */ maybe_trigger_vblank(5); nes_write((0x0417 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D5DD:;
    /* $D5DD: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D5DF:;
    /* $D5DF: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x0401 + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D5E2:;
    /* $D5E2: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D5EF;
label_D5E4:;
    /* $D5E4: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_D5E6:;
    /* $D5E6: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_D5E8:;
    /* $D5E8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D5EC;
label_D5EA:;
    /* $D5EA: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0xCF + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D5EC:; /* SkipIY */
    /* $D5EC: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD5FE); return;
label_D5EF:; /* ChkYCenterPos */
    /* $D5EF: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D5F1:;
    /* $D5F1: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x58 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D5F3:;
    /* $D5F3: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D5FB;
label_D5F5:;
    /* $D5F5: 20 */ maybe_trigger_vblank(6); call_by_address(0xBFB7);
label_D5F8:;
    /* $D5F8: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD5FE); return;
label_D5FB:; /* YMDown */
    /* $D5FB: 20 */ maybe_trigger_vblank(6); call_by_address(0xBFB4);
label_D5FE:; /* ChkYPCollision */
    /* $D5FE: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03A2 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D601:;
    /* $D601: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D606;
label_D603:;
    /* $D603: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC21);
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D606:; /* ExYPl */
    /* $D606: 60 */ maybe_trigger_vblank(6);
    return;
label_D607:; /* XMovingPlatform */
    /* $D607: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_D609:;
    /* $D609: 20 */ maybe_trigger_vblank(6); call_by_address(0xCB47);
label_D60C:;
    /* $D60C: 20 */ maybe_trigger_vblank(6); call_by_address(0xCB66);
label_D60F:;
    /* $D60F: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03A2 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D612:;
    /* $D612: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D630;
label_D614:; /* PositionPlayerOnHPlat */
    /* $D614: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x86); FLAG_NZ(g_cpu.A);
label_D616:;
    /* $D616: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D617:;
    /* $D617: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D619:;
    /* $D619: 85 */ maybe_trigger_vblank(3); nes_write(0x86, g_cpu.A);
label_D61B:;
    /* $D61B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x6D); FLAG_NZ(g_cpu.A);
label_D61D:;
    /* $D61D: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x00); FLAG_NZ(g_cpu.Y);
label_D61F:;
    /* $D61F: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D626;
label_D621:;
    /* $D621: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_D623:;
    /* $D623: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD628); return;
label_D626:; /* PPHSubt */
    /* $D626: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D628:; /* SetPVar */
    /* $D628: 85 */ maybe_trigger_vblank(3); nes_write(0x6D, g_cpu.A);
label_D62A:;
    /* $D62A: 8C */ maybe_trigger_vblank(4); nes_write(0x03A1, g_cpu.Y);
label_D62D:;
    /* $D62D: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC21);
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D630:; /* ExXMP */
    /* $D630: 60 */ maybe_trigger_vblank(6);
    return;
label_D631:; /* DropPlatform */
    /* $D631: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03A2 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D634:;
    /* $D634: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D63C;
label_D636:;
    /* $D636: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF88);
label_D639:;
    /* $D639: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC21);
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D63C:; /* ExDPl */
    /* $D63C: 60 */ maybe_trigger_vblank(6);
    return;
label_D63D:; /* RightPlatform */
    /* $D63D: 20 */ maybe_trigger_vblank(6); call_by_address(0xBF02);
label_D640:;
    /* $D640: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_D642:;
    /* $D642: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03A2 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D645:;
    /* $D645: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D64E;
label_D647:;
    /* $D647: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_D649:;
    /* $D649: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_D64B:;
    /* $D64B: 20 */ maybe_trigger_vblank(6); call_by_address(0xD614);
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D64E:; /* ExRPl */
    /* $D64E: 60 */ maybe_trigger_vblank(6);
    return;
label_D64F:; /* MoveLargeLiftPlat */
    /* $D64F: 20 */ maybe_trigger_vblank(6); call_by_address(0xD65B);
label_D652:;
    /* $D652: 4C */ maybe_trigger_vblank(3); goto label_D5FE;
label_D655:; /* MoveSmallPlatform */
    /* $D655: 20 */ maybe_trigger_vblank(6); call_by_address(0xD65B);
label_D658:;
    /* $D658: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD671); return;
label_D65B:; /* MoveLiftPlatforms */
    /* $D65B: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_D65E:;
    /* $D65E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D679;
label_D660:;
    /* $D660: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0417 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D663:;
    /* $D663: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D664:;
    /* $D664: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x0434 + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D667:;
    /* $D667: 9D */ maybe_trigger_vblank(5); nes_write((0x0417 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D66A:;
    /* $D66A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D66C:;
    /* $D66C: 75 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xA0 + g_cpu.X) & 0xFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D66E:;
    /* $D66E: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_D670:;
    /* $D670: 60 */ maybe_trigger_vblank(6);
    return;
label_D671:; /* ChkSmallPlatCollision */
    /* $D671: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03A2 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D674:;
    /* $D674: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D679;
label_D676:;
    /* $D676: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC19);
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D679:; /* ExLiftP */
    /* $D679: 60 */ maybe_trigger_vblank(6);
    return;
label_D67A:; /* OffscreenBoundsCheck */
    /* $D67A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D67C:;
    /* $D67C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x14; g_cpu.C=(g_cpu.A>=0x14)?1:0; FLAG_NZ(r&0xFF); }
label_D67E:;
    /* $D67E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D6D5;
label_D680:;
    /* $D680: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071C); FLAG_NZ(g_cpu.A);
label_D683:;
    /* $D683: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_D685:;
    /* $D685: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x05; g_cpu.C=(g_cpu.Y>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_D687:;
    /* $D687: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D68D;
label_D689:;
    /* $D689: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0D; g_cpu.C=(g_cpu.Y>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_D68B:;
    /* $D68B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D68F;
label_D68D:; /* LimitB */
    /* $D68D: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x38 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x38); g_cpu.A=r&0xFF; }
label_D68F:; /* ExtendLB */
    /* $D68F: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x48; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D691:;
    /* $D691: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_D693:;
    /* $D693: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071A); FLAG_NZ(g_cpu.A);
label_D696:;
    /* $D696: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D698:;
    /* $D698: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_D69A:;
    /* $D69A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071D); FLAG_NZ(g_cpu.A);
label_D69D:;
    /* $D69D: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x48 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x48); g_cpu.A=r&0xFF; }
label_D69F:;
    /* $D69F: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_D6A1:;
    /* $D6A1: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071B); FLAG_NZ(g_cpu.A);
label_D6A4:;
    /* $D6A4: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_D6A6:;
    /* $D6A6: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_D6A8:;
    /* $D6A8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D6AA:;
    /* $D6AA: C5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x01); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D6AC:;
    /* $D6AC: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D6AE:;
    /* $D6AE: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D6B0:;
    /* $D6B0: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D6D2;
label_D6B2:;
    /* $D6B2: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D6B4:;
    /* $D6B4: C5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x03); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D6B6:;
    /* $D6B6: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D6B8:;
    /* $D6B8: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x02); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D6BA:;
    /* $D6BA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D6D5;
label_D6BC:;
    /* $D6BC: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D6BE:;
    /* $D6BE: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_D6C0:;
    /* $D6C0: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D6D5;
label_D6C2:;
    /* $D6C2: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0D; g_cpu.C=(g_cpu.Y>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_D6C4:;
    /* $D6C4: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D6D5;
label_D6C6:;
    /* $D6C6: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x30; g_cpu.C=(g_cpu.Y>=0x30)?1:0; FLAG_NZ(r&0xFF); }
label_D6C8:;
    /* $D6C8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D6D5;
label_D6CA:;
    /* $D6CA: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x31; g_cpu.C=(g_cpu.Y>=0x31)?1:0; FLAG_NZ(r&0xFF); }
label_D6CC:;
    /* $D6CC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D6D5;
label_D6CE:;
    /* $D6CE: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x32; g_cpu.C=(g_cpu.Y>=0x32)?1:0; FLAG_NZ(r&0xFF); }
label_D6D0:;
    /* $D6D0: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D6D5;
label_D6D2:; /* TooFar */
    /* $D6D2: 20 */ maybe_trigger_vblank(6); call_by_address(0xC998);
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D6D5:; /* ExScrnBd */
    /* $D6D5: 60 */ maybe_trigger_vblank(6);
    return;
label_D6D6:;
    /* $D6D6: FF */ maybe_trigger_vblank(7); /* ILLEGAL $FF — skip 3 */
label_D6D9:; /* FireballEnemyCollision */
    /* $D6D9: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x24 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D6DB:;
    /* $D6DB: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D733;
label_D6DD:;
    /* $D6DD: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D6DE:;
    /* $D6DE: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D733;
label_D6E0:;
    /* $D6E0: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_D6E2:;
    /* $D6E2: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_D6E3:;
    /* $D6E3: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D733;
label_D6E5:;
    /* $D6E5: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_D6E6:;
    /* $D6E6: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D6E7:;
    /* $D6E7: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D6E8:;
    /* $D6E8: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D6E9:;
    /* $D6E9: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x1C + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x1C); g_cpu.A=r&0xFF; }
label_D6EB:;
    /* $D6EB: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_D6EC:;
    /* $D6EC: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x04; FLAG_NZ(g_cpu.X);
label_D6EE:; /* FireballEnemyCDLoop */
    /* $D6EE: 86 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.X);
label_D6F0:;
    /* $D6F0: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_D6F1:;
    /* $D6F1: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_D6F2:;
    /* $D6F2: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D6F4:;
    /* $D6F4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_D6F6:;
    /* $D6F6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D72C;
label_D6F8:;
    /* $D6F8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D6FA:;
    /* $D6FA: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D72C;
label_D6FC:;
    /* $D6FC: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D6FE:;
    /* $D6FE: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x24; g_cpu.C=(g_cpu.A>=0x24)?1:0; FLAG_NZ(r&0xFF); }
label_D700:;
    /* $D700: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D706;
label_D702:;
    /* $D702: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x2B; g_cpu.C=(g_cpu.A>=0x2B)?1:0; FLAG_NZ(r&0xFF); }
label_D704:;
    /* $D704: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D72C;
label_D706:; /* GoombaDie */
    /* $D706: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_D708:;
    /* $D708: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D710;
label_D70A:;
    /* $D70A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D70C:;
    /* $D70C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_D70E:;
    /* $D70E: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D72C;
label_D710:; /* NotGoomba */
    /* $D710: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D713:;
    /* $D713: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D72C;
label_D715:;
    /* $D715: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_D716:;
    /* $D716: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D717:;
    /* $D717: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D718:;
    /* $D718: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D719:;
    /* $D719: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_D71B:;
    /* $D71B: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_D71C:;
    /* $D71C: 20 */ maybe_trigger_vblank(6); call_by_address(0xE327);
label_D71F:;
    /* $D71F: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D721:;
    /* $D721: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D72C;
label_D723:;
    /* $D723: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_D725:;
    /* $D725: 95 */ maybe_trigger_vblank(4); nes_write((0x24 + g_cpu.X) & 0xFF, g_cpu.A);
label_D727:;
    /* $D727: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x01); FLAG_NZ(g_cpu.X);
label_D729:;
    /* $D729: 20 */ maybe_trigger_vblank(6); call_by_address(0xD73E);
label_D72C:; /* NoFToECol */
    /* $D72C: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_D72D:;
    /* $D72D: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_D72E:;
    /* $D72E: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x01); FLAG_NZ(g_cpu.X);
label_D730:;
    /* $D730: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_D731:;
    /* $D731: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D6EE;
    }
label_D733:; /* ExitFBallEnemy */
    /* $D733: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D735:;
    /* $D735: 60 */ maybe_trigger_vblank(6);
    return;
label_D736:; /* BowserIdentities */
    /* $D736: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D738:;
    /* $D738: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_D739:;
    /* $D739: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_D73A:;
    /* $D73A: 11 */ maybe_trigger_vblank(5); g_cpu.A |= nes_read((nes_read16zp(0x07) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D73C:;
    /* $D73C: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x2D); FLAG_NZ(g_cpu.A);
label_D73E:; /* HandleEnemyFBallCol */
    /* $D73E: 20 */ maybe_trigger_vblank(6); call_by_address(0xF152);
label_D741:;
    /* $D741: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x01); FLAG_NZ(g_cpu.X);
label_D743:;
    /* $D743: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D745:;
    /* $D745: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_D752;
label_D747:;
    /* $D747: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_D749:;
    /* $D749: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_D74A:;
    /* $D74A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D74C:;
    /* $D74C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x2D; g_cpu.C=(g_cpu.A>=0x2D)?1:0; FLAG_NZ(r&0xFF); }
label_D74E:;
    /* $D74E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D75C;
label_D750:;
    /* $D750: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x01); FLAG_NZ(g_cpu.X);
label_D752:; /* ChkBuzzyBeetle */
    /* $D752: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D754:;
    /* $D754: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_D756:;
    /* $D756: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D7C3;
label_D758:;
    /* $D758: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x2D; g_cpu.C=(g_cpu.A>=0x2D)?1:0; FLAG_NZ(r&0xFF); }
label_D75A:;
    /* $D75A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D789;
label_D75C:; /* HurtBowser */
    /* $D75C: CE */ maybe_trigger_vblank(6); { uint16_t a=0x0483; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D75F:;
    /* $D75F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D7C3;
label_D761:;
    /* $D761: 20 */ maybe_trigger_vblank(6); call_by_address(0xC363);
label_D764:;
    /* $D764: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_D766:;
    /* $D766: 8D */ maybe_trigger_vblank(4); nes_write(0x06CB, g_cpu.A);
label_D769:;
    /* $D769: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFE; FLAG_NZ(g_cpu.A);
label_D76B:;
    /* $D76B: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_D76D:;
    /* $D76D: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x075F); FLAG_NZ(g_cpu.Y);
label_D770:;
    /* $D770: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD736 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D773:;
    /* $D773: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_D775:;
    /* $D775: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_D777:;
    /* $D777: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_D779:;
    /* $D779: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D77D;
label_D77B:;
    /* $D77B: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x03; FLAG_NZ(g_cpu.A);
label_D77D:; /* SetDBSte */
    /* $D77D: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_D77F:;
    /* $D77F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_D781:;
    /* $D781: 85 */ maybe_trigger_vblank(3); nes_write(0xFE, g_cpu.A);
label_D783:;
    /* $D783: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x01); FLAG_NZ(g_cpu.X);
label_D785:;
    /* $D785: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x09; FLAG_NZ(g_cpu.A);
label_D787:;
    /* $D787: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D7BC;
label_D789:; /* ChkOtherEnemies */
    /* $D789: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_D78B:;
    /* $D78B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D7C3;
label_D78D:;
    /* $D78D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0C; g_cpu.C=(g_cpu.A>=0x0C)?1:0; FLAG_NZ(r&0xFF); }
label_D78F:;
    /* $D78F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D7C3;
label_D791:;
    /* $D791: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_D793:;
    /* $D793: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D7C3;
label_D795:; /* ShellOrBlockDefeat */
    /* $D795: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D797:;
    /* $D797: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_D799:;
    /* $D799: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D7A1;
label_D79B:;
    /* $D79B: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D79D:;
    /* $D79D: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x18 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x18); g_cpu.A=r&0xFF; }
label_D79F:;
    /* $D79F: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_D7A1:; /* StnE */
    /* $D7A1: 20 */ maybe_trigger_vblank(6); call_by_address(0xE01B);
label_D7A4:;
    /* $D7A4: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D7A6:;
    /* $D7A6: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x1F; FLAG_NZ(g_cpu.A);
label_D7A8:;
    /* $D7A8: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x20; FLAG_NZ(g_cpu.A);
label_D7AA:;
    /* $D7AA: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_D7AC:;
    /* $D7AC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_D7AE:;
    /* $D7AE: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_D7B0:;
    /* $D7B0: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x05; g_cpu.C=(g_cpu.Y>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_D7B2:;
    /* $D7B2: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D7B6;
label_D7B4:;
    /* $D7B4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_D7B6:; /* GoombaPoints */
    /* $D7B6: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_D7B8:;
    /* $D7B8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D7BC;
label_D7BA:;
    /* $D7BA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_D7BC:; /* EnemySmackScore */
    /* $D7BC: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_D7BF:;
    /* $D7BF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_D7C1:;
    /* $D7C1: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D7C3:; /* ExHCF */
    /* $D7C3: 60 */ maybe_trigger_vblank(6);
    return;
label_D7C4:; /* PlayerHammerCollision */
    /* $D7C4: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_D7C6:;
    /* $D7C6: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_D7C7:;
    /* $D7C7: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D7FF;
label_D7C9:;
    /* $D7C9: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_D7CC:;
    /* $D7CC: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x03D6); FLAG_NZ(g_cpu.A);
label_D7CF:;
    /* $D7CF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D7FF;
label_D7D1:;
    /* $D7D1: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_D7D2:;
    /* $D7D2: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D7D3:;
    /* $D7D3: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D7D4:;
    /* $D7D4: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D7D5:;
    /* $D7D5: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x24 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x24); g_cpu.A=r&0xFF; }
label_D7D7:;
    /* $D7D7: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_D7D8:;
    /* $D7D8: 20 */ maybe_trigger_vblank(6); call_by_address(0xE325);
label_D7DB:;
    /* $D7DB: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D7DD:;
    /* $D7DD: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D7FA;
label_D7DF:;
    /* $D7DF: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x06BE + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D7E2:;
    /* $D7E2: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D7FF;
label_D7E4:;
    /* $D7E4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_D7E6:;
    /* $D7E6: 9D */ maybe_trigger_vblank(5); nes_write((0x06BE + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D7E9:;
    /* $D7E9: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x64 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D7EB:;
    /* $D7EB: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_D7ED:;
    /* $D7ED: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D7EE:;
    /* $D7EE: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_D7F0:;
    /* $D7F0: 95 */ maybe_trigger_vblank(4); nes_write((0x64 + g_cpu.X) & 0xFF, g_cpu.A);
label_D7F2:;
    /* $D7F2: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x079F); FLAG_NZ(g_cpu.A);
label_D7F5:;
    /* $D7F5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D7FF;
label_D7F7:;
    /* $D7F7: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD92C); return;
label_D7FA:; /* ClHCol */
    /* $D7FA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_D7FC:;
    /* $D7FC: 9D */ maybe_trigger_vblank(5); nes_write((0x06BE + g_cpu.X) & 0xFFFF, g_cpu.A);
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D7FF:; /* ExPHC */
    /* $D7FF: 60 */ maybe_trigger_vblank(6);
    return;
label_D800:; /* HandlePowerUpCollision */
    /* $D800: 20 */ maybe_trigger_vblank(6); call_by_address(0xC998);
label_D803:;
    /* $D803: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_D805:;
    /* $D805: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_D808:;
    /* $D808: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_D80A:;
    /* $D80A: 85 */ maybe_trigger_vblank(3); nes_write(0xFE, g_cpu.A);
label_D80C:;
    /* $D80C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x39); FLAG_NZ(g_cpu.A);
label_D80E:;
    /* $D80E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_D810:;
    /* $D810: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D820;
label_D812:;
    /* $D812: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_D814:;
    /* $D814: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D83A;
label_D816:;
    /* $D816: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x23; FLAG_NZ(g_cpu.A);
label_D818:;
    /* $D818: 8D */ maybe_trigger_vblank(4); nes_write(0x079F, g_cpu.A);
label_D81B:;
    /* $D81B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_D81D:;
    /* $D81D: 85 */ maybe_trigger_vblank(3); nes_write(0xFB, g_cpu.A);
label_D81F:;
    /* $D81F: 60 */ maybe_trigger_vblank(6);
    return;
label_D820:; /* Shroom_Flower_PUp */
    /* $D820: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0756); FLAG_NZ(g_cpu.A);
label_D823:;
    /* $D823: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D840;
label_D825:;
    /* $D825: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_D827:;
    /* $D827: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D84C;
label_D829:;
    /* $D829: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D82B:;
    /* $D82B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_D82D:;
    /* $D82D: 8D */ maybe_trigger_vblank(4); nes_write(0x0756, g_cpu.A);
label_D830:;
    /* $D830: 20 */ maybe_trigger_vblank(6); call_by_address(0x85F1);
label_D833:;
    /* $D833: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D835:;
    /* $D835: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0C; FLAG_NZ(g_cpu.A);
label_D837:;
    /* $D837: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD847); return;
label_D83A:; /* SetFor1Up */
    /* $D83A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0B; FLAG_NZ(g_cpu.A);
label_D83C:;
    /* $D83C: 9D */ maybe_trigger_vblank(5); nes_write((0x0110 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D83F:;
    /* $D83F: 60 */ maybe_trigger_vblank(6);
    return;
label_D840:; /* UpToSuper */
    /* $D840: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_D842:;
    /* $D842: 8D */ maybe_trigger_vblank(4); nes_write(0x0756, g_cpu.A);
label_D845:;
    /* $D845: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x09; FLAG_NZ(g_cpu.A);
label_D847:; /* UpToFiery */
    /* $D847: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_D849:;
    /* $D849: 20 */ maybe_trigger_vblank(6); call_by_address(0xD948);
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D84C:; /* NoPUp */
    /* $D84C: 60 */ maybe_trigger_vblank(6);
    return;
label_D84D:; /* ResidualXSpdData */
    /* $D84D: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D84E:;
    /* $D84E: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_D84F:; /* KickedShellXSpdData */
    /* $D84F: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xD821); return; }
label_D851:; /* DemotedKoopaXSpdData */
    /* $D851: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_D852:;
    /* $D852: F8 */ maybe_trigger_vblank(2); g_cpu.D = 1;
label_D853:; /* PlayerEnemyCollision */
    /* $D853: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_D855:;
    /* $D855: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_D856:;
    /* $D856: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D84C;
    }
label_D858:;
    /* $D858: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC41);
label_D85B:;
    /* $D85B: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D880;
label_D85D:;
    /* $D85D: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D860:;
    /* $D860: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D880;
label_D862:;
    /* $D862: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0E); FLAG_NZ(g_cpu.A);
label_D864:;
    /* $D864: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_D866:;
    /* $D866: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D880;
label_D868:;
    /* $D868: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D86A:;
    /* $D86A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_D86C:;
    /* $D86C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D880;
label_D86E:;
    /* $D86E: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC52);
label_D871:;
    /* $D871: 20 */ maybe_trigger_vblank(6); call_by_address(0xE325);
label_D874:;
    /* $D874: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D876:;
    /* $D876: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D881;
label_D878:;
    /* $D878: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D87B:;
    /* $D87B: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xFE; FLAG_NZ(g_cpu.A);
label_D87D:;
    /* $D87D: 9D */ maybe_trigger_vblank(5); nes_write((0x0491 + g_cpu.X) & 0xFFFF, g_cpu.A);
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D880:; /* NoPECol */
    /* $D880: 60 */ maybe_trigger_vblank(6);
    return;
label_D881:; /* CheckForPUpCollision */
    /* $D881: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_D883:;
    /* $D883: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x2E; g_cpu.C=(g_cpu.Y>=0x2E)?1:0; FLAG_NZ(r&0xFF); }
label_D885:;
    /* $D885: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D88A;
label_D887:;
    /* $D887: 4C */ maybe_trigger_vblank(3); goto label_D800;
label_D88A:; /* EColl */
    /* $D88A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x079F); FLAG_NZ(g_cpu.A);
label_D88D:;
    /* $D88D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D895;
label_D88F:;
    /* $D88F: 4C */ maybe_trigger_vblank(3); goto label_D795;
label_D892:; /* KickedShellPtsData */
    /* $D892: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D893:;
    /* $D893: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D895:; /* HandlePECollisions */
    /* $D895: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D898:;
    /* $D898: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_D89A:;
    /* $D89A: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x03D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D89D:;
    /* $D89D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D8F8;
label_D89F:;
    /* $D89F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_D8A1:;
    /* $D8A1: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x0491 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D8A4:;
    /* $D8A4: 9D */ maybe_trigger_vblank(5); nes_write((0x0491 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D8A7:;
    /* $D8A7: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x12; g_cpu.C=(g_cpu.Y>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_D8A9:;
    /* $D8A9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D8F9;
label_D8AB:;
    /* $D8AB: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0D; g_cpu.C=(g_cpu.Y>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_D8AD:;
    /* $D8AD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D92C;
label_D8AF:;
    /* $D8AF: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0C; g_cpu.C=(g_cpu.Y>=0x0C)?1:0; FLAG_NZ(r&0xFF); }
label_D8B1:;
    /* $D8B1: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D92C;
label_D8B3:;
    /* $D8B3: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x33; g_cpu.C=(g_cpu.Y>=0x33)?1:0; FLAG_NZ(r&0xFF); }
label_D8B5:;
    /* $D8B5: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D8F9;
label_D8B7:;
    /* $D8B7: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x15; g_cpu.C=(g_cpu.Y>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_D8B9:;
    /* $D8B9: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D92C;
label_D8BB:;
    /* $D8BB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x074E); FLAG_NZ(g_cpu.A);
label_D8BE:;
    /* $D8BE: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D92C;
label_D8C0:;
    /* $D8C0: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D8C2:;
    /* $D8C2: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D8C3:;
    /* $D8C3: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D8F9;
label_D8C5:;
    /* $D8C5: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D8C7:;
    /* $D8C7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_D8C9:;
    /* $D8C9: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_D8CB:;
    /* $D8CB: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D8F9;
label_D8CD:;
    /* $D8CD: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D8CF:;
    /* $D8CF: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_D8D1:;
    /* $D8D1: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D8F8;
label_D8D3:;
    /* $D8D3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_D8D5:;
    /* $D8D5: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_D8D7:;
    /* $D8D7: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D8D9:;
    /* $D8D9: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x80; FLAG_NZ(g_cpu.A);
label_D8DB:;
    /* $D8DB: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_D8DD:;
    /* $D8DD: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA05);
label_D8E0:;
    /* $D8E0: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD84F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D8E3:;
    /* $D8E3: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_D8E5:;
    /* $D8E5: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_D8E7:;
    /* $D8E7: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D8E8:;
    /* $D8E8: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0484); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D8EB:;
    /* $D8EB: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x0796 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_D8EE:;
    /* $D8EE: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_D8F0:;
    /* $D8F0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D8F5;
label_D8F2:;
    /* $D8F2: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD892 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D8F5:; /* KSPts */
    /* $D8F5: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_D8F8:; /* ExPEC */
    /* $D8F8: 60 */ maybe_trigger_vblank(6);
    return;
label_D8F9:; /* ChkForPlayerInjury */
    /* $D8F9: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x9F); FLAG_NZ(g_cpu.A);
label_D8FB:;
    /* $D8FB: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D8FF;
label_D8FD:;
    /* $D8FD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xD969); return; }
label_D8FF:; /* ChkInj */
    /* $D8FF: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D901:;
    /* $D901: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_D903:;
    /* $D903: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D90E;
label_D905:;
    /* $D905: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_D907:;
    /* $D907: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D908:;
    /* $D908: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x0C + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0C); g_cpu.A=r&0xFF; }
label_D90A:;
    /* $D90A: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xCF + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D90C:;
    /* $D90C: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { call_by_address(0xD969); return; }
label_D90E:; /* ChkETmrs */
    /* $D90E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0791); FLAG_NZ(g_cpu.A);
label_D911:;
    /* $D911: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xD969); return; }
label_D913:;
    /* $D913: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x079E); FLAG_NZ(g_cpu.A);
label_D916:;
    /* $D916: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D955;
label_D918:;
    /* $D918: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AD); FLAG_NZ(g_cpu.A);
label_D91B:;
    /* $D91B: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x03AE); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D91E:;
    /* $D91E: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D923;
label_D920:;
    /* $D920: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD9F6); return;
label_D923:; /* TInjE */
    /* $D923: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D925:;
    /* $D925: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_D927:;
    /* $D927: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D92C;
label_D929:;
    /* $D929: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD9FF); return;
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
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D946;
    }
label_D965:; /* StompedEnemyPtsData */
    /* $D965: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_D966:;
    /* $D966: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x05; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D968:;
    /* $D968: 06 */ maybe_trigger_vblank(5); { uint16_t a=0xB5; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D96A:;
    /* $D96A: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0xC9 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D96C:;
    /* $D96C: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_D96D:;
    /* $D96D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
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
    /* $D9CF: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD9F1); return;
label_D9D2:; /* RevivalRateData */
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
label_D9F6:; /* ChkEnemyFaceRight */
    /* $D9F6: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D9F8:;
    /* $D9F8: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_D9FA:;
    /* $D9FA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D9FF;
label_D9FC:;
    /* $D9FC: 4C */ maybe_trigger_vblank(3); goto label_D92C;
label_D9FF:; /* LInj */
    /* $D9FF: 20 */ maybe_trigger_vblank(6); call_by_address(0xDB1C);
label_DA02:;
    /* $DA02: 4C */ maybe_trigger_vblank(3); goto label_D92C;
label_DA05:; /* EnemyFacePlayer */
    /* $DA05: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_DA07:;
    /* $DA07: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_DA0A:;
    /* $DA0A: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_DA0D;
label_DA0C:;
    /* $DA0C: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DA0D:; /* SFcRt */
    /* $DA0D: 94 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.Y);
label_DA0F:;
    /* $DA0F: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DA10:;
    /* $DA10: 60 */ maybe_trigger_vblank(6);
    return;
label_DA11:; /* SetupFloateyNumber */
    /* $DA11: 9D */ maybe_trigger_vblank(5); nes_write((0x0110 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DA14:;
    /* $DA14: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x30; FLAG_NZ(g_cpu.A);
label_DA16:;
    /* $DA16: 9D */ maybe_trigger_vblank(5); nes_write((0x012C + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DA19:;
    /* $DA19: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DA1B:;
    /* $DA1B: 9D */ maybe_trigger_vblank(5); nes_write((0x011E + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DA1E:;
    /* $DA1E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_DA21:;
    /* $DA21: 9D */ maybe_trigger_vblank(5); nes_write((0x0117 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DA24:; /* ExSFN */
    /* $DA24: 60 */ maybe_trigger_vblank(6);
    return;
label_DA25:; /* SetBitsMask */
    /* $DA25: 80 */ maybe_trigger_vblank(2); /* NOP */
label_DA27:;
    /* $DA27: 20 */ maybe_trigger_vblank(6); call_by_address(0x0810);
label_DA2A:;
    /* $DA2A: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x02); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_DA2C:; /* ClearBitsMask */
    /* $DA2C: 7F */ maybe_trigger_vblank(7); /* ILLEGAL $7F — skip 3 */
label_DA2F:;
    /* $DA2F: EF */ maybe_trigger_vblank(6); /* ILLEGAL $EF — skip 3 */
label_DA32:;
    /* $DA32: FD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x09A5 + g_cpu.X) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DA35:;
    /* $DA35: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_DA36:;
    /* $DA36: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DA24;
    }
label_DA38:;
    /* $DA38: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x074E); FLAG_NZ(g_cpu.A);
label_DA3B:;
    /* $DA3B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DA24;
    }
label_DA3D:;
    /* $DA3D: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DA3F:;
    /* $DA3F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_DA41:;
    /* $DA41: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xDAB1); return; }
label_DA43:;
    /* $DA43: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_DA45:;
    /* $DA45: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { call_by_address(0xDAB1); return; }
label_DA47:;
    /* $DA47: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_DA49:;
    /* $DA49: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { call_by_address(0xDAB1); return; }
label_DA4B:;
    /* $DA4B: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA4E:;
    /* $DA4E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xDAB1); return; }
label_DA50:;
    /* $DA50: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC52);
label_DA53:;
    /* $DA53: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_DA54:;
    /* $DA54: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xDAB1); return; }
label_DA56:; /* ECLoop */
    /* $DA56: 86 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.X);
label_DA58:;
    /* $DA58: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_DA59:;
    /* $DA59: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_DA5A:;
    /* $DA5A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DA5C:;
    /* $DA5C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { call_by_address(0xDAAA); return; }
label_DA5E:;
    /* $DA5E: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DA60:;
    /* $DA60: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_DA62:;
    /* $DA62: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xDAAA); return; }
label_DA64:;
    /* $DA64: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_DA66:;
    /* $DA66: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { call_by_address(0xDAAA); return; }
label_DA68:;
    /* $DA68: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_DA6A:;
    /* $DA6A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { call_by_address(0xDAAA); return; }
label_DA6C:;
    /* $DA6C: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA6F:;
    /* $DA6F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xDAAA); return; }
label_DA71:;
    /* $DA71: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_DA72:;
    /* $DA72: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
}

void EnemyEngine::move_swimming_cheep_cheep_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_CC4C;
    }
label_CC4A:; /* MoveSwimmingCheepCheep */
    /* $CC4A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC4C:;
    /* $CC4C: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_CC4E:;
    /* $CC4E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_CC53;
label_CC50:;
    /* $CC50: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xBF8C); return;
label_CC53:; /* CCSwim */
    /* $CC53: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_CC55:;
    /* $CC55: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC57:;
    /* $CC57: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CC58:;
    /* $CC58: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x0A; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC5A:;
    /* $CC5A: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_CC5B:;
    /* $CC5B: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCC46 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CC5E:;
    /* $CC5E: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_CC60:;
    /* $CC60: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0401 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CC63:;
    /* $CC63: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CC64:;
    /* $CC64: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x02); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC66:;
    /* $CC66: 9D */ maybe_trigger_vblank(5); nes_write((0x0401 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_CC69:;
    /* $CC69: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC6B:;
    /* $CC6B: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC6D:;
    /* $CC6D: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_CC6F:;
    /* $CC6F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC71:;
    /* $CC71: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC73:;
    /* $CC73: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_CC75:;
    /* $CC75: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_CC77:;
    /* $CC77: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_CC79:;
    /* $CC79: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x02; g_cpu.C=(g_cpu.X>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_CC7B:;
    /* $CC7B: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CCC6;
label_CC7D:;
    /* $CC7D: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC7F:;
    /* $CC7F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x10; g_cpu.C=(g_cpu.A>=0x10)?1:0; FLAG_NZ(r&0xFF); }
label_CC81:;
    /* $CC81: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CC99;
label_CC83:;
    /* $CC83: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0417 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CC86:;
    /* $CC86: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CC87:;
    /* $CC87: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x02); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC89:;
    /* $CC89: 9D */ maybe_trigger_vblank(5); nes_write((0x0417 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_CC8C:;
    /* $CC8C: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC8E:;
    /* $CC8E: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x03); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC90:;
    /* $CC90: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_CC92:;
    /* $CC92: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xB6 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CC94:;
    /* $CC94: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_CC96:;
    /* $CC96: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xCCAC); return;
label_CC99:; /* CCSwimUpwards */
    /* $CC99: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0417 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_CC9C:;
    /* $CC9C: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CC9D:;
    /* $CC9D: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x02); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CC9F:;
    /* $CC9F: 9D */ maybe_trigger_vblank(5); nes_write((0x0417 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_CCA2:;
    /* $CCA2: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CCA4:;
    /* $CCA4: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x03); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CCA6:;
    /* $CCA6: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_CCA8:;
    /* $CCA8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xB6 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CCAA:;
    /* $CCAA: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CCAC:; /* ChkSwimYPos */
    /* $CCAC: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_CCAE:;
    /* $CCAE: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_CCB0:;
    /* $CCB0: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_CCB2:;
    /* $CCB2: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_CCB3:;
    /* $CCB3: FD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x0434 + g_cpu.X) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_CCB6:;
    /* $CCB6: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_CCBF;
label_CCB8:;
    /* $CCB8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x10; FLAG_NZ(g_cpu.Y);
label_CCBA:;
    /* $CCBA: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_CCBC:;
    /* $CCBC: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_CCBD:;
    /* $CCBD: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_CCBF:; /* YPDiff */
    /* $CCBF: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0F; g_cpu.C=(g_cpu.A>=0x0F)?1:0; FLAG_NZ(r&0xFF); }
label_CCC1:;
    /* $CCC1: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_CCC6;
label_CCC3:;
    /* $CCC3: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_CCC4:;
    /* $CCC4: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_CCC6:; /* ExSwCC */
    /* $CCC6: 60 */ maybe_trigger_vblank(6);
    return;
}

void EnemyEngine::player_enemy_collision_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_E435;
        case 2: goto label_E6BD;
        case 3: goto label_DFB8;
        case 4: goto label_E539;
        case 5: goto label_DAAE;
        case 6: goto label_E6F0;
        case 7: goto label_E6F1;
        case 8: goto label_DA8D;
        case 9: goto label_E00F;
        case 10: goto label_E0CA;
        case 11: goto label_DFC2;
        case 12: goto label_E0A1;
        case 13: goto label_E03D;
        case 14: goto label_E401;
        case 15: goto label_DFA9;
        case 16: goto label_DFAA;
        case 17: goto label_E058;
        case 18: goto label_DDAE;
        case 19: goto label_DD8E;
        case 20: goto label_DD2D;
        case 21: goto label_DD0D;
        case 22: goto label_E0E8;
        case 23: goto label_DB4D;
        case 24: goto label_E08E;
        case 25: goto label_DFCA;
        case 26: goto label_E274;
        case 27: goto label_E800;
        case 28: goto label_DECB;
        case 29: goto label_DF21;
        case 30: goto label_E8A9;
        case 31: goto label_E003;
        case 32: goto label_E5CF;
        case 33: goto label_E5D0;
        case 34: goto label_E606;
        case 35: goto label_E609;
        case 36: goto label_E60A;
        case 37: goto label_E605;
        case 38: goto label_E6CD;
        case 39: goto label_E802;
        case 40: goto label_DAB9;
        case 41: goto label_DC8E;
        case 42: goto label_DCCD;
        case 43: goto label_E131;
        case 44: goto label_E603;
        case 45: goto label_E8C9;
        case 46: goto label_E40D;
        case 47: goto label_E029;
        case 48: goto label_DC1A;
        case 49: goto label_E56F;
        case 50: goto label_E818;
        case 51: goto label_E857;
        case 52: goto label_E858;
        case 53: goto label_E1D1;
        case 54: goto label_DFC0;
        case 55: goto label_DAAB;
        case 56: goto label_DC55;
        case 57: goto label_E60D;
        case 58: goto label_E60E;
        case 59: goto label_DC16;
        case 60: goto label_DC17;
        case 61: goto label_E3AD;
        case 62: goto label_DDCE;
        case 63: goto label_DC62;
        case 64: goto label_DF90;
        case 65: goto label_E820;
        case 66: goto label_DF9B;
        case 67: goto label_E4C9;
        case 68: goto label_E4CA;
        case 69: goto label_DE2F;
        case 70: goto label_DD20;
        case 71: goto label_DE03;
        case 72: goto label_DE8E;
        case 73: goto label_DD07;
        case 74: goto label_DE29;
        case 75: goto label_DE25;
        case 76: goto label_DB8E;
        case 77: goto label_E807;
        case 78: goto label_E80A;
        case 79: goto label_DFB1;
        case 80: goto label_DDE0;
        case 81: goto label_DF8B;
        case 82: goto label_DF96;
        case 83: goto label_E090;
        case 84: goto label_DFB9;
        case 85: goto label_E389;
        case 86: goto label_E791;
        case 87: goto label_E060;
        case 88: goto label_E061;
        case 89: goto label_E27D;
        case 90: goto label_E1FE;
        case 91: goto label_E1FF;
        case 92: goto label_E804;
        case 93: goto label_DD04;
        case 94: goto label_DD2A;
        case 95: goto label_DD3B;
        case 96: goto label_DD60;
        case 97: goto label_DD61;
        case 98: goto label_DD1A;
        case 99: goto label_E3F1;
        case 100: goto label_E3B0;
        case 101: goto label_E121;
        case 102: goto label_E3CD;
        case 103: goto label_E1A9;
        case 104: goto label_E0A9;
        case 105: goto label_E4C4;
        case 106: goto label_E4C5;
        case 107: goto label_E4CC;
        case 108: goto label_E4CD;
        case 109: goto label_E4C0;
        case 110: goto label_E4D0;
        case 111: goto label_E4D4;
        case 112: goto label_E541;
        case 113: goto label_DBD6;
        case 114: goto label_DBB5;
        case 115: goto label_E6BE;
        case 116: goto label_E682;
        case 117: goto label_E683;
        case 118: goto label_E48D;
        case 119: goto label_E4E4;
        case 120: goto label_E6C0;
        case 121: goto label_DCFC;
        case 122: goto label_DCDD;
        case 123: goto label_DFDC;
        case 124: goto label_DFDF;
        case 125: goto label_DCDF;
        case 126: goto label_DDDC;
        case 127: goto label_DDDE;
        case 128: goto label_DEDF;
        case 129: goto label_DA7B;
        case 130: goto label_DBDA;
        case 131: goto label_E3D4;
        case 132: goto label_E2E4;
        case 133: goto label_E58A;
        case 134: goto label_E6E7;
        case 135: goto label_E7E9;
        case 136: goto label_E878;
        case 137: goto label_E879;
        case 138: goto label_E840;
        case 139: goto label_DEA3;
        case 140: goto label_E4A2;
        case 141: goto label_E4A3;
        case 142: goto label_E0EA;
        case 143: goto label_E67F;
        case 144: goto label_E672;
        case 145: goto label_E667;
        case 146: goto label_E01D;
        case 147: goto label_E04E;
        case 148: goto label_E646;
        case 149: goto label_E876;
        case 150: goto label_E877;
        case 151: goto label_E005;
        case 152: goto label_E041;
        case 153: goto label_E007;
        case 154: goto label_E73E;
        case 155: goto label_E57D;
        case 156: goto label_E0EC;
        case 157: goto label_E8BE;
        case 158: goto label_E048;
        case 159: goto label_E0AB;
        case 160: goto label_E4AD;
        case 161: goto label_E7BD;
        case 162: goto label_DC20;
        case 163: goto label_DEF0;
        case 164: goto label_E8A8;
        case 165: goto label_E0D0;
        case 166: goto label_DCD1;
        case 167: goto label_E6F7;
        case 168: goto label_E6FA;
        case 169: goto label_E301;
        case 170: goto label_DDD5;
        case 171: goto label_E3DE;
        case 172: goto label_DFDA;
        case 173: goto label_E0A4;
        case 174: goto label_E763;
        case 175: goto label_E1E4;
        case 176: goto label_E3E1;
        case 177: goto label_E3E2;
        case 178: goto label_DE1E;
        case 179: goto label_E0DF;
        case 180: goto label_DF01;
        case 181: goto label_DD66;
        case 182: goto label_E7E6;
        case 183: goto label_DE59;
        case 184: goto label_E850;
        case 185: goto label_DF77;
        case 186: goto label_DF71;
        case 187: goto label_DDD3;
        case 188: goto label_DB8C;
        case 189: goto label_E38B;
        case 190: goto label_E10A;
        case 191: goto label_E3B1;
        case 192: goto label_E3BA;
        case 193: goto label_E540;
        case 194: goto label_E53B;
        case 195: goto label_E492;
        case 196: goto label_DEC9;
        case 197: goto label_DE8A;
        case 198: goto label_DEBF;
        case 199: goto label_E629;
        case 200: goto label_E6F5;
        case 201: goto label_E4BD;
        case 202: goto label_E179;
        case 203: goto label_E49D;
        case 204: goto label_E710;
        case 205: goto label_DC82;
        case 206: goto label_E385;
        case 207: goto label_DC23;
        case 208: goto label_E600;
        case 209: goto label_DDBD;
        case 210: goto label_E38D;
        case 211: goto label_E28D;
        case 212: goto label_E7B9;
        case 213: goto label_DB93;
        case 214: goto label_DCB9;
        case 215: goto label_DD90;
        case 216: goto label_E7B1;
        case 217: goto label_DFD0;
        case 218: goto label_E59A;
        case 219: goto label_E61B;
        case 220: goto label_E0B9;
        case 221: goto label_E4B9;
        case 222: goto label_E7A5;
        case 223: goto label_DD76;
        case 224: goto label_DB04;
        case 225: goto label_DD3D;
        case 226: goto label_DB5C;
        case 227: goto label_DB0C;
        case 228: goto label_DE82;
        case 229: goto label_E30C;
        case 230: goto label_E286;
        case 231: goto label_E528;
        case 232: goto label_DB3B;
        case 233: goto label_DE38;
        case 234: goto label_DECE;
        case 235: goto label_DBA7;
        case 236: goto label_E730;
        case 237: goto label_E347;
        case 238: goto label_DB47;
        case 239: goto label_E406;
        case 240: goto label_E001;
        case 241: goto label_E431;
        case 242: goto label_DE02;
        case 243: goto label_E408;
        case 244: goto label_E70A;
        case 245: goto label_DD06;
        case 246: goto label_DE4B;
        case 247: goto label_DD0A;
        case 248: goto label_E112;
        case 249: goto label_DF11;
        case 250: goto label_E139;
        case 251: goto label_E278;
        case 252: goto label_DC27;
        case 253: goto label_E722;
        case 254: goto label_E322;
        case 255: goto label_E372;
        case 256: goto label_E781;
    }
label_D853:; /* PlayerEnemyCollision */
    /* $D853: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_D855:;
    /* $D855: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_D856:;
    /* $D856: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xD84C); return; }
label_D858:;
    /* $D858: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC41);
label_D85B:;
    /* $D85B: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D880;
label_D85D:;
    /* $D85D: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D860:;
    /* $D860: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D880;
label_D862:;
    /* $D862: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0E); FLAG_NZ(g_cpu.A);
label_D864:;
    /* $D864: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_D866:;
    /* $D866: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D880;
label_D868:;
    /* $D868: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D86A:;
    /* $D86A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_D86C:;
    /* $D86C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D880;
label_D86E:;
    /* $D86E: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC52);
label_D871:;
    /* $D871: 20 */ maybe_trigger_vblank(6); call_by_address(0xE325);
label_D874:;
    /* $D874: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_D876:;
    /* $D876: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D881;
label_D878:;
    /* $D878: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D87B:;
    /* $D87B: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xFE; FLAG_NZ(g_cpu.A);
label_D87D:;
    /* $D87D: 9D */ maybe_trigger_vblank(5); nes_write((0x0491 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D880:; /* NoPECol */
    /* $D880: 60 */ maybe_trigger_vblank(6);
    return;
label_D881:; /* CheckForPUpCollision */
    /* $D881: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_D883:;
    /* $D883: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x2E; g_cpu.C=(g_cpu.Y>=0x2E)?1:0; FLAG_NZ(r&0xFF); }
label_D885:;
    /* $D885: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D88A;
label_D887:;
    /* $D887: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD800); return;
label_D88A:; /* EColl */
    /* $D88A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x079F); FLAG_NZ(g_cpu.A);
label_D88D:;
    /* $D88D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D895;
label_D88F:;
    /* $D88F: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD795); return;
label_D892:; /* KickedShellPtsData */
    /* $D892: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D893:;
    /* $D893: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D895:; /* HandlePECollisions */
    /* $D895: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D898:;
    /* $D898: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_D89A:;
    /* $D89A: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x03D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D89D:;
    /* $D89D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D8F8;
label_D89F:;
    /* $D89F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_D8A1:;
    /* $D8A1: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x0491 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D8A4:;
    /* $D8A4: 9D */ maybe_trigger_vblank(5); nes_write((0x0491 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D8A7:;
    /* $D8A7: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x12; g_cpu.C=(g_cpu.Y>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_D8A9:;
    /* $D8A9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D8F9;
label_D8AB:;
    /* $D8AB: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0D; g_cpu.C=(g_cpu.Y>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_D8AD:;
    /* $D8AD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D92C;
label_D8AF:;
    /* $D8AF: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0C; g_cpu.C=(g_cpu.Y>=0x0C)?1:0; FLAG_NZ(r&0xFF); }
label_D8B1:;
    /* $D8B1: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D92C;
label_D8B3:;
    /* $D8B3: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x33; g_cpu.C=(g_cpu.Y>=0x33)?1:0; FLAG_NZ(r&0xFF); }
label_D8B5:;
    /* $D8B5: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D8F9;
label_D8B7:;
    /* $D8B7: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x15; g_cpu.C=(g_cpu.Y>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_D8B9:;
    /* $D8B9: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D92C;
label_D8BB:;
    /* $D8BB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x074E); FLAG_NZ(g_cpu.A);
label_D8BE:;
    /* $D8BE: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D92C;
label_D8C0:;
    /* $D8C0: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D8C2:;
    /* $D8C2: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D8C3:;
    /* $D8C3: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D8F9;
label_D8C5:;
    /* $D8C5: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D8C7:;
    /* $D8C7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_D8C9:;
    /* $D8C9: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_D8CB:;
    /* $D8CB: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D8F9;
label_D8CD:;
    /* $D8CD: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D8CF:;
    /* $D8CF: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_D8D1:;
    /* $D8D1: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D8F8;
label_D8D3:;
    /* $D8D3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_D8D5:;
    /* $D8D5: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_D8D7:;
    /* $D8D7: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D8D9:;
    /* $D8D9: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x80; FLAG_NZ(g_cpu.A);
label_D8DB:;
    /* $D8DB: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_D8DD:;
    /* $D8DD: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA05);
label_D8E0:;
    /* $D8E0: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD84F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D8E3:;
    /* $D8E3: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_D8E5:;
    /* $D8E5: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_D8E7:;
    /* $D8E7: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D8E8:;
    /* $D8E8: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0484); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D8EB:;
    /* $D8EB: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x0796 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_D8EE:;
    /* $D8EE: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_D8F0:;
    /* $D8F0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D8F5;
label_D8F2:;
    /* $D8F2: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD892 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D8F5:; /* KSPts */
    /* $D8F5: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_D8F8:; /* ExPEC */
    /* $D8F8: 60 */ maybe_trigger_vblank(6);
    return;
label_D8F9:; /* ChkForPlayerInjury */
    /* $D8F9: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x9F); FLAG_NZ(g_cpu.A);
label_D8FB:;
    /* $D8FB: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D8FF;
label_D8FD:;
    /* $D8FD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xD969); return; }
label_D8FF:; /* ChkInj */
    /* $D8FF: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D901:;
    /* $D901: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_D903:;
    /* $D903: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D90E;
label_D905:;
    /* $D905: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_D907:;
    /* $D907: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D908:;
    /* $D908: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x0C + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0C); g_cpu.A=r&0xFF; }
label_D90A:;
    /* $D90A: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xCF + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D90C:;
    /* $D90C: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { call_by_address(0xD969); return; }
label_D90E:; /* ChkETmrs */
    /* $D90E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0791); FLAG_NZ(g_cpu.A);
label_D911:;
    /* $D911: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xD969); return; }
label_D913:;
    /* $D913: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x079E); FLAG_NZ(g_cpu.A);
label_D916:;
    /* $D916: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D955;
label_D918:;
    /* $D918: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AD); FLAG_NZ(g_cpu.A);
label_D91B:;
    /* $D91B: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x03AE); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D91E:;
    /* $D91E: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D923;
label_D920:;
    /* $D920: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD9F6); return;
label_D923:; /* TInjE */
    /* $D923: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D925:;
    /* $D925: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_D927:;
    /* $D927: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D92C;
label_D929:;
    /* $D929: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD9FF); return;
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
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D946;
    }
label_D965:; /* StompedEnemyPtsData */
    /* $D965: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_D966:;
    /* $D966: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x05; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D968:;
    /* $D968: 06 */ maybe_trigger_vblank(5); { uint16_t a=0xB5; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D96A:;
    /* $D96A: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0xC9 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D96C:;
    /* $D96C: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_D96D:;
    /* $D96D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
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
    /* $D9CF: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD9F1); return;
label_D9D2:; /* RevivalRateData */
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
label_D9F6:; /* ChkEnemyFaceRight */
    /* $D9F6: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D9F8:;
    /* $D9F8: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_D9FA:;
    /* $D9FA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D9FF;
label_D9FC:;
    /* $D9FC: 4C */ maybe_trigger_vblank(3); goto label_D92C;
label_D9FF:; /* LInj */
    /* $D9FF: 20 */ maybe_trigger_vblank(6); call_by_address(0xDB1C);
label_DA02:;
    /* $DA02: 4C */ maybe_trigger_vblank(3); goto label_D92C;
label_DA05:; /* EnemyFacePlayer */
    /* $DA05: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_DA07:;
    /* $DA07: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_DA0A:;
    /* $DA0A: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_DA0D;
label_DA0C:;
    /* $DA0C: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DA0D:; /* SFcRt */
    /* $DA0D: 94 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.Y);
label_DA0F:;
    /* $DA0F: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DA10:;
    /* $DA10: 60 */ maybe_trigger_vblank(6);
    return;
label_DA11:; /* SetupFloateyNumber */
    /* $DA11: 9D */ maybe_trigger_vblank(5); nes_write((0x0110 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DA14:;
    /* $DA14: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x30; FLAG_NZ(g_cpu.A);
label_DA16:;
    /* $DA16: 9D */ maybe_trigger_vblank(5); nes_write((0x012C + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DA19:;
    /* $DA19: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DA1B:;
    /* $DA1B: 9D */ maybe_trigger_vblank(5); nes_write((0x011E + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DA1E:;
    /* $DA1E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_DA21:;
    /* $DA21: 9D */ maybe_trigger_vblank(5); nes_write((0x0117 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DA24:; /* ExSFN */
    /* $DA24: 60 */ maybe_trigger_vblank(6);
    return;
label_DA25:; /* SetBitsMask */
    /* $DA25: 80 */ maybe_trigger_vblank(2); /* NOP */
label_DA27:;
    /* $DA27: 20 */ maybe_trigger_vblank(6); call_by_address(0x0810);
label_DA2A:;
    /* $DA2A: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x02); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_DA2C:; /* ClearBitsMask */
    /* $DA2C: 7F */ maybe_trigger_vblank(7); /* ILLEGAL $7F — skip 3 */
label_DA2F:;
    /* $DA2F: EF */ maybe_trigger_vblank(6); /* ILLEGAL $EF — skip 3 */
label_DA32:;
    /* $DA32: FD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x09A5 + g_cpu.X) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DA35:;
    /* $DA35: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_DA36:;
    /* $DA36: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DA24;
    }
label_DA38:;
    /* $DA38: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x074E); FLAG_NZ(g_cpu.A);
label_DA3B:;
    /* $DA3B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DA24;
    }
label_DA3D:;
    /* $DA3D: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DA3F:;
    /* $DA3F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_DA41:;
    /* $DA41: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DAB1;
label_DA43:;
    /* $DA43: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_DA45:;
    /* $DA45: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DAB1;
label_DA47:;
    /* $DA47: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_DA49:;
    /* $DA49: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DAB1;
label_DA4B:;
    /* $DA4B: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA4E:;
    /* $DA4E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DAB1;
label_DA50:;
    /* $DA50: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC52);
label_DA53:;
    /* $DA53: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_DA54:;
    /* $DA54: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_DAB1;
label_DA56:; /* ECLoop */
    /* $DA56: 86 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.X);
label_DA58:;
    /* $DA58: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_DA59:;
    /* $DA59: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_DA5A:;
    /* $DA5A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DA5C:;
    /* $DA5C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DAAA;
label_DA5E:;
    /* $DA5E: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DA60:;
    /* $DA60: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_DA62:;
    /* $DA62: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DAAA;
label_DA64:;
    /* $DA64: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_DA66:;
    /* $DA66: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DAAA;
label_DA68:;
    /* $DA68: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_DA6A:;
    /* $DA6A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DAAA;
label_DA6C:;
    /* $DA6C: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA6F:;
    /* $DA6F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DAAA;
label_DA71:;
    /* $DA71: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_DA72:;
    /* $DA72: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DA73:;
    /* $DA73: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DA74:;
    /* $DA74: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DA75:;
    /* $DA75: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_DA77:;
    /* $DA77: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_DA78:;
    /* $DA78: 20 */ maybe_trigger_vblank(6); call_by_address(0xE327);
label_DA7B:;
    /* $DA7B: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DA7D:;
    /* $DA7D: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x01); FLAG_NZ(g_cpu.Y);
label_DA7F:;
    /* $DA7F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DAA1;
label_DA81:;
    /* $DA81: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DA83:;
    /* $DA83: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x001E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA86:;
    /* $DA86: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x80; FLAG_NZ(g_cpu.A);
label_DA88:;
    /* $DA88: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DA9B;
label_DA8A:;
    /* $DA8A: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA8D:;
    /* $DA8D: 3D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xDA25 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA90:;
    /* $DA90: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DAAA;
label_DA92:;
    /* $DA92: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA95:;
    /* $DA95: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0xDA25 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA98:;
    /* $DA98: 99 */ maybe_trigger_vblank(5); nes_write((0x0491 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_DA9B:; /* YesEC */
    /* $DA9B: 20 */ maybe_trigger_vblank(6); call_by_address(0xDAB4);
label_DA9E:;
    /* $DA9E: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xDAAA); return;
label_DAA1:; /* NoEnemyCollision */
    /* $DAA1: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DAA4:;
    /* $DAA4: 3D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xDA2C + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DAA7:;
    /* $DAA7: 99 */ maybe_trigger_vblank(5); nes_write((0x0491 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_DAAA:; /* ReadyNextEnemy */
    /* $DAAA: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_DAAB:;
    /* $DAAB: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_DAAC:;
    /* $DAAC: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x01); FLAG_NZ(g_cpu.X);
label_DAAE:;
    /* $DAAE: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_DAAF:;
    /* $DAAF: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DA56;
    }
label_DAB1:; /* ExitECRoutine */
    /* $DAB1: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DAB3:;
    /* $DAB3: 60 */ maybe_trigger_vblank(6);
    return;
label_DAB4:; /* ProcEnemyCollisions */
    /* $DAB4: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x001E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DAB7:;
    /* $DAB7: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DAB9:;
    /* $DAB9: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_DABB:;
    /* $DABB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DAF0;
label_DABD:;
    /* $DABD: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DABF:;
    /* $DABF: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_DAC1:;
    /* $DAC1: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DAF1;
label_DAC3:;
    /* $DAC3: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DAC5:;
    /* $DAC5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_DAC7:;
    /* $DAC7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DAF0;
label_DAC9:;
    /* $DAC9: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x001E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DACC:;
    /* $DACC: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DACD:;
    /* $DACD: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DAD9;
label_DACF:;
    /* $DACF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_DAD1:;
    /* $DAD1: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_DAD4:;
    /* $DAD4: 20 */ maybe_trigger_vblank(6); call_by_address(0xD795);
label_DAD7:;
    /* $DAD7: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x01); FLAG_NZ(g_cpu.Y);
label_DAD9:; /* ShellCollisions */
    /* $DAD9: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_DADA:;
    /* $DADA: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_DADB:;
    /* $DADB: 20 */ maybe_trigger_vblank(6); call_by_address(0xD795);
label_DADE:;
    /* $DADE: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DAE0:;
    /* $DAE0: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0125 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DAE3:;
    /* $DAE3: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DAE4:;
    /* $DAE4: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_DAE6:;
    /* $DAE6: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x01); FLAG_NZ(g_cpu.X);
label_DAE8:;
    /* $DAE8: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_DAEB:;
    /* $DAEB: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DAED:;
    /* $DAED: FE */ maybe_trigger_vblank(7); { uint16_t a=(0x0125 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DAF0:; /* ExitProcessEColl */
    /* $DAF0: 60 */ maybe_trigger_vblank(6);
    return;
label_DAF1:; /* ProcSecondEnemyColl */
    /* $DAF1: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x001E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DAF4:;
    /* $DAF4: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_DAF6:;
    /* $DAF6: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DB15;
label_DAF8:;
    /* $DAF8: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0016 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DAFB:;
    /* $DAFB: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_DAFD:;
    /* $DAFD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DAF0;
    }
label_DAFF:;
    /* $DAFF: 20 */ maybe_trigger_vblank(6); call_by_address(0xD795);
label_DB02:;
    /* $DB02: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x01); FLAG_NZ(g_cpu.Y);
label_DB04:;
    /* $DB04: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0125 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DB07:;
    /* $DB07: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DB08:;
    /* $DB08: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_DB0A:;
    /* $DB0A: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DB0C:;
    /* $DB0C: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_DB0F:;
    /* $DB0F: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x01); FLAG_NZ(g_cpu.X);
label_DB11:;
    /* $DB11: FE */ maybe_trigger_vblank(7); { uint16_t a=(0x0125 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DB14:;
    /* $DB14: 60 */ maybe_trigger_vblank(6);
    return;
label_DB15:; /* MoveEOfs */
    /* $DB15: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_DB16:;
    /* $DB16: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_DB17:;
    /* $DB17: 20 */ maybe_trigger_vblank(6); call_by_address(0xDB1C);
label_DB1A:;
    /* $DB1A: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DB1C:; /* EnemyTurnAround */
    /* $DB1C: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DB1E:;
    /* $DB1E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_DB20:;
    /* $DB20: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DB44;
label_DB22:;
    /* $DB22: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_DB24:;
    /* $DB24: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DB44;
label_DB26:;
    /* $DB26: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_DB28:;
    /* $DB28: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DB44;
label_DB2A:;
    /* $DB2A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x12; g_cpu.C=(g_cpu.A>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_DB2C:;
    /* $DB2C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DB36;
label_DB2E:;
    /* $DB2E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0E; g_cpu.C=(g_cpu.A>=0x0E)?1:0; FLAG_NZ(r&0xFF); }
label_DB30:;
    /* $DB30: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DB36;
label_DB32:;
    /* $DB32: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_DB34:;
    /* $DB34: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DB44;
label_DB36:; /* RXSpd */
    /* $DB36: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DB38:;
    /* $DB38: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_DB3A:;
    /* $DB3A: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_DB3B:;
    /* $DB3B: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DB3C:;
    /* $DB3C: 94 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.Y);
label_DB3E:;
    /* $DB3E: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DB40:;
    /* $DB40: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x03; FLAG_NZ(g_cpu.A);
label_DB42:;
    /* $DB42: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_DB44:; /* ExTA */
    /* $DB44: 60 */ maybe_trigger_vblank(6);
    return;
label_DB45:; /* LargePlatformCollision */
    /* $DB45: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_DB47:;
    /* $DB47: 9D */ maybe_trigger_vblank(5); nes_write((0x03A2 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DB4A:;
    /* $DB4A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_DB4D:;
    /* $DB4D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DB78;
label_DB4F:;
    /* $DB4F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DB51:;
    /* $DB51: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_DB78;
label_DB53:;
    /* $DB53: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DB55:;
    /* $DB55: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x24; g_cpu.C=(g_cpu.A>=0x24)?1:0; FLAG_NZ(r&0xFF); }
label_DB57:;
    /* $DB57: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DB5F;
label_DB59:;
    /* $DB59: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DB5B:;
    /* $DB5B: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_DB5C:;
    /* $DB5C: 20 */ maybe_trigger_vblank(6); call_by_address(0xDB5F);
label_DB5F:; /* ChkForPlayerC_LargeP */
    /* $DB5F: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC41);
label_DB62:;
    /* $DB62: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DB78;
label_DB64:;
    /* $DB64: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_DB65:;
    /* $DB65: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC54);
label_DB68:;
    /* $DB68: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DB6A:;
    /* $DB6A: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_DB6C:;
    /* $DB6C: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_DB6D:;
    /* $DB6D: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_DB6E:;
    /* $DB6E: 20 */ maybe_trigger_vblank(6); call_by_address(0xE325);
label_DB71:;
    /* $DB71: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_DB72:;
    /* $DB72: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_DB73:;
    /* $DB73: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DB78;
label_DB75:;
    /* $DB75: 20 */ maybe_trigger_vblank(6); call_by_address(0xDBBC);
label_DB78:; /* ExLPC */
    /* $DB78: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DB7A:;
    /* $DB7A: 60 */ maybe_trigger_vblank(6);
    return;
label_DB7B:; /* SmallPlatformCollision */
    /* $DB7B: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_DB7E:;
    /* $DB7E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DBB7;
label_DB80:;
    /* $DB80: 9D */ maybe_trigger_vblank(5); nes_write((0x03A2 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DB83:;
    /* $DB83: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC41);
label_DB86:;
    /* $DB86: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DBB7;
label_DB88:;
    /* $DB88: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_DB8A:;
    /* $DB8A: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_DB8C:; /* ChkSmallPlatLoop */
    /* $DB8C: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DB8E:;
    /* $DB8E: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC52);
label_DB91:;
    /* $DB91: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_DB93:;
    /* $DB93: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DBB7;
label_DB95:;
    /* $DB95: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AD + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DB98:;
    /* $DB98: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_DB9A:;
    /* $DB9A: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DBA1;
label_DB9C:;
    /* $DB9C: 20 */ maybe_trigger_vblank(6); call_by_address(0xE325);
label_DB9F:;
    /* $DB9F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DBBA;
label_DBA1:; /* MoveBoundBox */
    /* $DBA1: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AD + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DBA4:;
    /* $DBA4: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DBA5:;
    /* $DBA5: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x80 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x80); g_cpu.A=r&0xFF; }
label_DBA7:;
    /* $DBA7: 99 */ maybe_trigger_vblank(5); nes_write((0x04AD + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_DBAA:;
    /* $DBAA: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DBAD:;
    /* $DBAD: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DBAE:;
    /* $DBAE: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x80 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x80); g_cpu.A=r&0xFF; }
label_DBB0:;
    /* $DBB0: 99 */ maybe_trigger_vblank(5); nes_write((0x04AF + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_DBB3:;
    /* $DBB3: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DBB5:;
    /* $DBB5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DB8C;
    }
label_DBB7:; /* ExSPC */
    /* $DBB7: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DBB9:;
    /* $DBB9: 60 */ maybe_trigger_vblank(6);
    return;
label_DBBA:; /* ProcSPlatCollisions */
    /* $DBBA: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DBBC:; /* ProcLPlatCollisions */
    /* $DBBC: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DBBF:;
    /* $DBBF: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_DBC0:;
    /* $DBC0: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x04AD); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DBC3:;
    /* $DBC3: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_DBC5:;
    /* $DBC5: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DBCF;
label_DBC7:;
    /* $DBC7: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x9F); FLAG_NZ(g_cpu.A);
label_DBC9:;
    /* $DBC9: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_DBCF;
label_DBCB:;
    /* $DBCB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_DBCD:;
    /* $DBCD: 85 */ maybe_trigger_vblank(3); nes_write(0x9F, g_cpu.A);
label_DBCF:; /* ChkForTopCollision */
    /* $DBCF: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x04AF); FLAG_NZ(g_cpu.A);
label_DBD2:;
    /* $DBD2: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_DBD3:;
    /* $DBD3: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AD + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DBD6:;
    /* $DBD6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_DBD8:;
    /* $DBD8: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DBF5;
label_DBDA:;
    /* $DBDA: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x9F); FLAG_NZ(g_cpu.A);
label_DBDC:;
    /* $DBDC: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_DBF5;
label_DBDE:;
    /* $DBDE: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_DBE0:;
    /* $DBE0: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_DBE2:;
    /* $DBE2: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x2B; g_cpu.C=(g_cpu.Y>=0x2B)?1:0; FLAG_NZ(r&0xFF); }
label_DBE4:;
    /* $DBE4: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DBEB;
label_DBE6:;
    /* $DBE6: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x2C; g_cpu.C=(g_cpu.Y>=0x2C)?1:0; FLAG_NZ(r&0xFF); }
label_DBE8:;
    /* $DBE8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DBEB;
label_DBEA:;
    /* $DBEA: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_DBEB:; /* SetCollisionFlag */
    /* $DBEB: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DBED:;
    /* $DBED: 9D */ maybe_trigger_vblank(5); nes_write((0x03A2 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DBF0:;
    /* $DBF0: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DBF2:;
    /* $DBF2: 85 */ maybe_trigger_vblank(3); nes_write(0x1D, g_cpu.A);
label_DBF4:;
    /* $DBF4: 60 */ maybe_trigger_vblank(6);
    return;
label_DBF5:; /* PlatformSideCollisions */
    /* $DBF5: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_DBF7:;
    /* $DBF7: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_DBF9:;
    /* $DBF9: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x04AE); FLAG_NZ(g_cpu.A);
label_DBFC:;
    /* $DBFC: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_DBFD:;
    /* $DBFD: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DC00:;
    /* $DC00: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_DC02:;
    /* $DC02: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DC11;
label_DC04:;
    /* $DC04: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DC06:;
    /* $DC06: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AE + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DC09:;
    /* $DC09: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DC0A:;
    /* $DC0A: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x04AC); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DC0D:;
    /* $DC0D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x09; g_cpu.C=(g_cpu.A>=0x09)?1:0; FLAG_NZ(r&0xFF); }
label_DC0F:;
    /* $DC0F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DC14;
label_DC11:; /* SideC */
    /* $DC11: 20 */ maybe_trigger_vblank(6); call_by_address(0xDF4B);
label_DC14:; /* NoSideC */
    /* $DC14: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DC16:;
    /* $DC16: 60 */ maybe_trigger_vblank(6);
    return;
label_DC17:; /* PlayerPosSPlatData */
    /* $DC17: 80 */ maybe_trigger_vblank(2); /* NOP */
label_DC19:; /* PositionPlayerOnS_Plat */
    /* $DC19: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_DC1A:;
    /* $DC1A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DC1C:;
    /* $DC1C: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DC1D:;
    /* $DC1D: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDC16 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DC20:;
    /* $DC20: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xCFB5); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_DC23:;
    /* $DC23: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x0E); FLAG_NZ(g_cpu.Y);
label_DC25:;
    /* $DC25: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0B; g_cpu.C=(g_cpu.Y>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_DC27:;
    /* $DC27: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DC40;
label_DC29:;
    /* $DC29: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0xB6 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_DC2B:;
    /* $DC2B: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x01; g_cpu.C=(g_cpu.Y>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_DC2D:;
    /* $DC2D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DC40;
label_DC2F:;
    /* $DC2F: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_DC30:;
    /* $DC30: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x20; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DC32:;
    /* $DC32: 85 */ maybe_trigger_vblank(3); nes_write(0xCE, g_cpu.A);
label_DC34:;
    /* $DC34: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_DC35:;
    /* $DC35: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DC37:;
    /* $DC37: 85 */ maybe_trigger_vblank(3); nes_write(0xB5, g_cpu.A);
label_DC39:;
    /* $DC39: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DC3B:;
    /* $DC3B: 85 */ maybe_trigger_vblank(3); nes_write(0x9F, g_cpu.A);
label_DC3D:;
    /* $DC3D: 8D */ maybe_trigger_vblank(4); nes_write(0x0433, g_cpu.A);
label_DC40:; /* ExPlPos */
    /* $DC40: 60 */ maybe_trigger_vblank(6);
    return;
label_DC41:; /* CheckPlayerVertical */
    /* $DC41: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D0); FLAG_NZ(g_cpu.A);
label_DC44:;
    /* $DC44: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xF0; g_cpu.C=(g_cpu.A>=0xF0)?1:0; FLAG_NZ(r&0xFF); }
label_DC46:;
    /* $DC46: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DC51;
label_DC48:;
    /* $DC48: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xB5); FLAG_NZ(g_cpu.Y);
label_DC4A:;
    /* $DC4A: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DC4B:;
    /* $DC4B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DC51;
label_DC4D:;
    /* $DC4D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_DC4F:;
    /* $DC4F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xD0; g_cpu.C=(g_cpu.A>=0xD0)?1:0; FLAG_NZ(r&0xFF); }
label_DC51:; /* ExCPV */
    /* $DC51: 60 */ maybe_trigger_vblank(6);
    return;
label_DC52:; /* GetEnemyBoundBoxOfs */
    /* $DC52: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x08); FLAG_NZ(g_cpu.A);
label_DC54:; /* GetEnemyBoundBoxOfsArg */
    /* $DC54: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DC55:;
    /* $DC55: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DC56:;
    /* $DC56: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DC57:;
    /* $DC57: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_DC59:;
    /* $DC59: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_DC5A:;
    /* $DC5A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D1); FLAG_NZ(g_cpu.A);
label_DC5D:;
    /* $DC5D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_DC5F:;
    /* $DC5F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0F; g_cpu.C=(g_cpu.A>=0x0F)?1:0; FLAG_NZ(r&0xFF); }
label_DC61:;
    /* $DC61: 60 */ maybe_trigger_vblank(6);
    return;
label_DC62:; /* PlayerBGUpperExtent */
    /* $DC62: 20 */ maybe_trigger_vblank(6); call_by_address(0xAD10);
label_DC65:;
    /* $DC65: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x07 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
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
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
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
label_DE0E:; /* HandleAxeMetatile */
    /* $DE0E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DE10:;
    /* $DE10: 8D */ maybe_trigger_vblank(4); nes_write(0x0772, g_cpu.A);
label_DE13:;
    /* $DE13: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_DE15:;
    /* $DE15: 8D */ maybe_trigger_vblank(4); nes_write(0x0770, g_cpu.A);
label_DE18:;
    /* $DE18: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_DE1A:;
    /* $DE1A: 85 */ maybe_trigger_vblank(3); nes_write(0x57, g_cpu.A);
label_DE1C:; /* ErACM */
    /* $DE1C: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x02); FLAG_NZ(g_cpu.Y);
label_DE1E:;
    /* $DE1E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DE20:;
    /* $DE20: 91 */ maybe_trigger_vblank(6); nes_write((nes_read16zp(0x06) + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_DE22:;
    /* $DE22: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8A4D); return;
label_DE25:; /* ClimbXPosAdder */
    /* $DE25: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xFF07 + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DE28:;
    /* $DE28: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xDE28); return;
label_DE29:; /* FlagpoleYPosData */
    /* $DE29: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DE2A:;
    /* $DE2A: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_DE2B:;
    /* $DE2B: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) goto label_DE95;
label_DE2D:;
    /* $DE2D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DDD3;
    }
label_DE2F:;
    /* $DE2F: 04 */ maybe_trigger_vblank(3); (void)nes_read(0xC0); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_DE31:;
    /* $DE31: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x90; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DE33:;
    /* $DE33: 04 */ maybe_trigger_vblank(3); (void)nes_read(0xC0); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_DE35:;
    /* $DE35: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DE36:;
    /* $DE36: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DE39;
label_DE38:; /* ExHC */
    /* $DE38: 60 */ maybe_trigger_vblank(6);
    return;
label_DE39:; /* ChkForFlagpole */
    /* $DE39: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x24; g_cpu.C=(g_cpu.A>=0x24)?1:0; FLAG_NZ(r&0xFF); }
label_DE3B:;
    /* $DE3B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DE41;
label_DE3D:;
    /* $DE3D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x25; g_cpu.C=(g_cpu.A>=0x25)?1:0; FLAG_NZ(r&0xFF); }
label_DE3F:;
    /* $DE3F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DE7A;
label_DE41:; /* FlagpoleCollision */
    /* $DE41: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0E); FLAG_NZ(g_cpu.A);
label_DE43:;
    /* $DE43: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_DE45:;
    /* $DE45: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DE88;
label_DE47:;
    /* $DE47: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_DE49:;
    /* $DE49: 85 */ maybe_trigger_vblank(3); nes_write(0x33, g_cpu.A);
label_DE4B:;
    /* $DE4B: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0723; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DE4E:;
    /* $DE4E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0E); FLAG_NZ(g_cpu.A);
label_DE50:;
    /* $DE50: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_DE52:;
    /* $DE52: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DE73;
label_DE54:;
    /* $DE54: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x33; FLAG_NZ(g_cpu.A);
label_DE56:;
    /* $DE56: 20 */ maybe_trigger_vblank(6); call_by_address(0x9716);
label_DE59:;
    /* $DE59: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_DE5B:;
    /* $DE5B: 85 */ maybe_trigger_vblank(3); nes_write(0xFC, g_cpu.A);
label_DE5D:;
    /* $DE5D: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_DE5E:;
    /* $DE5E: 8D */ maybe_trigger_vblank(4); nes_write(0x0713, g_cpu.A);
label_DE61:;
    /* $DE61: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x04; FLAG_NZ(g_cpu.X);
label_DE63:;
    /* $DE63: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_DE65:;
    /* $DE65: 8D */ maybe_trigger_vblank(4); nes_write(0x070F, g_cpu.A);
label_DE68:; /* ChkFlagpoleYPosLoop */
    /* $DE68: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDE29 + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_DE6B:;
    /* $DE6B: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DE70;
label_DE6D:;
    /* $DE6D: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_DE6E:;
    /* $DE6E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DE68;
    }
label_DE70:; /* MtchF */
    /* $DE70: 8E */ maybe_trigger_vblank(4); nes_write(0x010F, g_cpu.X);
label_DE73:; /* RunFR */
    /* $DE73: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_DE75:;
    /* $DE75: 85 */ maybe_trigger_vblank(3); nes_write(0x0E, g_cpu.A);
label_DE77:;
    /* $DE77: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xDE88); return;
label_DE7A:; /* VineCollision */
    /* $DE7A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x26; g_cpu.C=(g_cpu.A>=0x26)?1:0; FLAG_NZ(r&0xFF); }
label_DE7C:;
    /* $DE7C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DE88;
label_DE7E:;
    /* $DE7E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_DE80:;
    /* $DE80: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_DE82:;
    /* $DE82: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DE88;
label_DE84:;
    /* $DE84: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_DE86:;
    /* $DE86: 85 */ maybe_trigger_vblank(3); nes_write(0x0E, g_cpu.A);
label_DE88:; /* PutPlayerOnVine */
    /* $DE88: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_DE8A:;
    /* $DE8A: 85 */ maybe_trigger_vblank(3); nes_write(0x1D, g_cpu.A);
label_DE8C:;
    /* $DE8C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DE8E:;
    /* $DE8E: 85 */ maybe_trigger_vblank(3); nes_write(0x57, g_cpu.A);
label_DE90:;
    /* $DE90: 8D */ maybe_trigger_vblank(4); nes_write(0x0705, g_cpu.A);
label_DE93:;
    /* $DE93: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x86); FLAG_NZ(g_cpu.A);
label_DE95:;
    /* $DE95: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_DE96:;
    /* $DE96: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x071C); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DE99:;
    /* $DE99: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x10; g_cpu.C=(g_cpu.A>=0x10)?1:0; FLAG_NZ(r&0xFF); }
label_DE9B:;
    /* $DE9B: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DEA1;
label_DE9D:;
    /* $DE9D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_DE9F:;
    /* $DE9F: 85 */ maybe_trigger_vblank(3); nes_write(0x33, g_cpu.A);
label_DEA1:; /* SetVXPl */
    /* $DEA1: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x33); FLAG_NZ(g_cpu.Y);
label_DEA3:;
    /* $DEA3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x06); FLAG_NZ(g_cpu.A);
label_DEA5:;
    /* $DEA5: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DEA6:;
    /* $DEA6: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DEA7:;
    /* $DEA7: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DEA8:;
    /* $DEA8: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DEA9:;
    /* $DEA9: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DEAA:;
    /* $DEAA: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDE24 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DEAD:;
    /* $DEAD: 85 */ maybe_trigger_vblank(3); nes_write(0x86, g_cpu.A);
label_DEAF:;
    /* $DEAF: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x06); FLAG_NZ(g_cpu.A);
label_DEB1:;
    /* $DEB1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DEBC;
label_DEB3:;
    /* $DEB3: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071B); FLAG_NZ(g_cpu.A);
label_DEB6:;
    /* $DEB6: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DEB7:;
    /* $DEB7: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDE26 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DEBA:;
    /* $DEBA: 85 */ maybe_trigger_vblank(3); nes_write(0x6D, g_cpu.A);
label_DEBC:; /* ExPVne */
    /* $DEBC: 60 */ maybe_trigger_vblank(6);
    return;
label_DEBD:; /* ChkInvisibleMTiles */
    /* $DEBD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x5F; g_cpu.C=(g_cpu.A>=0x5F)?1:0; FLAG_NZ(r&0xFF); }
label_DEBF:;
    /* $DEBF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DEC3;
label_DEC1:;
    /* $DEC1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x60; g_cpu.C=(g_cpu.A>=0x60)?1:0; FLAG_NZ(r&0xFF); }
label_DEC3:; /* ExCInvT */
    /* $DEC3: 60 */ maybe_trigger_vblank(6);
    return;
label_DEC4:; /* ChkForLandJumpSpring */
    /* $DEC4: 20 */ maybe_trigger_vblank(6); call_by_address(0xDEDD);
label_DEC7:;
    /* $DEC7: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DEDC;
label_DEC9:;
    /* $DEC9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x70; FLAG_NZ(g_cpu.A);
label_DECB:;
    /* $DECB: 8D */ maybe_trigger_vblank(4); nes_write(0x0709, g_cpu.A);
label_DECE:;
    /* $DECE: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF9; FLAG_NZ(g_cpu.A);
label_DED0:;
    /* $DED0: 8D */ maybe_trigger_vblank(4); nes_write(0x06DB, g_cpu.A);
label_DED3:;
    /* $DED3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_DED5:;
    /* $DED5: 8D */ maybe_trigger_vblank(4); nes_write(0x0786, g_cpu.A);
label_DED8:;
    /* $DED8: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_DED9:;
    /* $DED9: 8D */ maybe_trigger_vblank(4); nes_write(0x070E, g_cpu.A);
label_DEDC:; /* ExCJSp */
    /* $DEDC: 60 */ maybe_trigger_vblank(6);
    return;
label_DEDD:; /* ChkJumpspringMetatiles */
    /* $DEDD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x67; g_cpu.C=(g_cpu.A>=0x67)?1:0; FLAG_NZ(r&0xFF); }
label_DEDF:;
    /* $DEDF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DEE6;
label_DEE1:;
    /* $DEE1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x68; g_cpu.C=(g_cpu.A>=0x68)?1:0; FLAG_NZ(r&0xFF); }
label_DEE3:;
    /* $DEE3: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DEE4:;
    /* $DEE4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DEE7;
label_DEE6:; /* JSFnd */
    /* $DEE6: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_DEE7:; /* NoJSFnd */
    /* $DEE7: 60 */ maybe_trigger_vblank(6);
    return;
label_DEE8:; /* HandlePipeEntry */
    /* $DEE8: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0B); FLAG_NZ(g_cpu.A);
label_DEEA:;
    /* $DEEA: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x04; FLAG_NZ(g_cpu.A);
label_DEEC:;
    /* $DEEC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DF4A;
label_DEEE:;
    /* $DEEE: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_DEF0:;
    /* $DEF0: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_DEF2:;
    /* $DEF2: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DF4A;
label_DEF4:;
    /* $DEF4: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_DEF6:;
    /* $DEF6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x10; g_cpu.C=(g_cpu.A>=0x10)?1:0; FLAG_NZ(r&0xFF); }
label_DEF8:;
    /* $DEF8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DF4A;
label_DEFA:;
    /* $DEFA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x30; FLAG_NZ(g_cpu.A);
label_DEFC:;
    /* $DEFC: 8D */ maybe_trigger_vblank(4); nes_write(0x06DE, g_cpu.A);
label_DEFF:;
    /* $DEFF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_DF01:;
    /* $DF01: 85 */ maybe_trigger_vblank(3); nes_write(0x0E, g_cpu.A);
label_DF03:;
    /* $DF03: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_DF05:;
    /* $DF05: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_DF07:;
    /* $DF07: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_DF09:;
    /* $DF09: 8D */ maybe_trigger_vblank(4); nes_write(0x03C4, g_cpu.A);
label_DF0C:;
    /* $DF0C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06D6); FLAG_NZ(g_cpu.A);
label_DF0F:;
    /* $DF0F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DF4A;
label_DF11:;
    /* $DF11: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_DF13:;
    /* $DF13: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DF14:;
    /* $DF14: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DF15:;
    /* $DF15: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_DF16:;
    /* $DF16: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x86); FLAG_NZ(g_cpu.A);
label_DF18:;
    /* $DF18: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x60; g_cpu.C=(g_cpu.A>=0x60)?1:0; FLAG_NZ(r&0xFF); }
label_DF1A:;
    /* $DF1A: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DF22;
label_DF1C:;
    /* $DF1C: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_DF1D:;
    /* $DF1D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xA0; g_cpu.C=(g_cpu.A>=0xA0)?1:0; FLAG_NZ(r&0xFF); }
label_DF1F:;
    /* $DF1F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DF22;
label_DF21:;
    /* $DF21: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_DF22:; /* GetWNum */
    /* $DF22: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x87F2 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_DF25:;
    /* $DF25: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DF26:;
    /* $DF26: 8C */ maybe_trigger_vblank(4); nes_write(0x075F, g_cpu.Y);
label_DF29:;
    /* $DF29: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0x9CB4 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_DF2C:;
    /* $DF2C: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x9CBC + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DF2F:;
    /* $DF2F: 8D */ maybe_trigger_vblank(4); nes_write(0x0750, g_cpu.A);
label_DF32:;
    /* $DF32: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_DF34:;
    /* $DF34: 85 */ maybe_trigger_vblank(3); nes_write(0xFC, g_cpu.A);
label_DF36:;
    /* $DF36: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DF38:;
    /* $DF38: 8D */ maybe_trigger_vblank(4); nes_write(0x0751, g_cpu.A);
label_DF3B:;
    /* $DF3B: 8D */ maybe_trigger_vblank(4); nes_write(0x0760, g_cpu.A);
label_DF3E:;
    /* $DF3E: 8D */ maybe_trigger_vblank(4); nes_write(0x075C, g_cpu.A);
label_DF41:;
    /* $DF41: 8D */ maybe_trigger_vblank(4); nes_write(0x0752, g_cpu.A);
label_DF44:;
    /* $DF44: EE */ maybe_trigger_vblank(6); { uint16_t a=0x075D; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DF47:;
    /* $DF47: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0757; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DF4A:; /* ExPipeE */
    /* $DF4A: 60 */ maybe_trigger_vblank(6);
    return;
label_DF4B:; /* ImpedePlayerMove */
    /* $DF4B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DF4D:;
    /* $DF4D: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x57); FLAG_NZ(g_cpu.Y);
label_DF4F:;
    /* $DF4F: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x00); FLAG_NZ(g_cpu.X);
label_DF51:;
    /* $DF51: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_DF52:;
    /* $DF52: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DF5E;
label_DF54:;
    /* $DF54: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_DF55:;
    /* $DF55: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x00; g_cpu.C=(g_cpu.Y>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_DF57:;
    /* $DF57: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_DF81;
label_DF59:;
    /* $DF59: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_DF5B:;
    /* $DF5B: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xDF66); return;
label_DF5E:; /* RImpd */
    /* $DF5E: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x02; FLAG_NZ(g_cpu.X);
label_DF60:;
    /* $DF60: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x01; g_cpu.C=(g_cpu.Y>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_DF62:;
    /* $DF62: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_DF81;
label_DF64:;
    /* $DF64: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_DF66:; /* NXSpd */
    /* $DF66: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x10; FLAG_NZ(g_cpu.Y);
label_DF68:;
    /* $DF68: 8C */ maybe_trigger_vblank(4); nes_write(0x0785, g_cpu.Y);
label_DF6B:;
    /* $DF6B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_DF6D:;
    /* $DF6D: 84 */ maybe_trigger_vblank(3); nes_write(0x57, g_cpu.Y);
label_DF6F:;
    /* $DF6F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_DF71:;
    /* $DF71: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_DF74;
label_DF73:;
    /* $DF73: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DF74:; /* PlatF */
    /* $DF74: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_DF76:;
    /* $DF76: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DF77:;
    /* $DF77: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x86); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DF79:;
    /* $DF79: 85 */ maybe_trigger_vblank(3); nes_write(0x86, g_cpu.A);
label_DF7B:;
    /* $DF7B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x6D); FLAG_NZ(g_cpu.A);
label_DF7D:;
    /* $DF7D: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DF7F:;
    /* $DF7F: 85 */ maybe_trigger_vblank(3); nes_write(0x6D, g_cpu.A);
label_DF81:; /* ExIPM */
    /* $DF81: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_DF82:;
    /* $DF82: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_DF84:;
    /* $DF84: 2D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read(0x0490); FLAG_NZ(g_cpu.A);
label_DF87:;
    /* $DF87: 8D */ maybe_trigger_vblank(4); nes_write(0x0490, g_cpu.A);
label_DF8A:;
    /* $DF8A: 60 */ maybe_trigger_vblank(6);
    return;
label_DF8B:; /* SolidMTileUpperExt */
    /* $DF8B: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_DFEE;
label_DF8D:;
    /* $DF8D: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DF8E:;
    /* $DF8E: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x20); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_DF90:;
    /* $DF90: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DF71;
    }
label_DF92:;
    /* $DF92: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDF8B + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_DF95:;
    /* $DF95: 60 */ maybe_trigger_vblank(6);
    return;
label_DF96:; /* ClimbMTileUpperExt */
    /* $DF96: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x6D); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_DF98:;
    /* $DF98: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_DF99:;
    /* $DF99: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DF9B:;
    /* $DF9B: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xDF7C); return; }
label_DF9D:;
    /* $DF9D: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDF96 + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_DFA0:;
    /* $DFA0: 60 */ maybe_trigger_vblank(6);
    return;
label_DFA1:; /* CheckForCoinMTiles */
    /* $DFA1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xC2; g_cpu.C=(g_cpu.A>=0xC2)?1:0; FLAG_NZ(r&0xFF); }
label_DFA3:;
    /* $DFA3: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DFAB;
label_DFA5:;
    /* $DFA5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xC3; g_cpu.C=(g_cpu.A>=0xC3)?1:0; FLAG_NZ(r&0xFF); }
label_DFA7:;
    /* $DFA7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DFAB;
label_DFA9:;
    /* $DFA9: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DFAA:;
    /* $DFAA: 60 */ maybe_trigger_vblank(6);
    return;
label_DFAB:; /* CoinSd */
    /* $DFAB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_DFAD:;
    /* $DFAD: 85 */ maybe_trigger_vblank(3); nes_write(0xFE, g_cpu.A);
label_DFAF:;
    /* $DFAF: 60 */ maybe_trigger_vblank(6);
    return;
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
label_DFB9:; /* EnemyBGCStateData */
    /* $DFB9: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x01 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_DFBB:;
    /* $DFBB: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_DFBC:;
    /* $DFBC: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_DFBD:;
    /* $DFBD: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_DFBE:;
    /* $DFBE: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x10); FLAG_NZ(g_cpu.A);
label_DFC0:;
    /* $DFC0: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DF77;
    }
label_DFC2:;
    /* $DFC2: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x2029 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DFC5:;
    /* $DFC5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DFB8;
    }
label_DFC7:;
    /* $DFC7: 20 */ maybe_trigger_vblank(6); call_by_address(0xE15B);
label_DFCA:;
    /* $DFCA: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DFB8;
    }
label_DFCC:;
    /* $DFCC: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_DFCE:;
    /* $DFCE: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x12; g_cpu.C=(g_cpu.Y>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_DFD0:;
    /* $DFD0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DFD8;
label_DFD2:;
    /* $DFD2: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DFD4:;
    /* $DFD4: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x25; g_cpu.C=(g_cpu.A>=0x25)?1:0; FLAG_NZ(r&0xFF); }
label_DFD6:;
    /* $DFD6: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DFB8;
    }
label_DFD8:; /* DoIDCheckBGColl */
    /* $DFD8: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0E; g_cpu.C=(g_cpu.Y>=0x0E)?1:0; FLAG_NZ(r&0xFF); }
label_DFDA:;
    /* $DFDA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DFDF;
label_DFDC:;
    /* $DFDC: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE163); return;
label_DFDF:; /* HBChk */
    /* $DFDF: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x05; g_cpu.C=(g_cpu.Y>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_DFE1:;
    /* $DFE1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DFE6;
label_DFE3:;
    /* $DFE3: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE185); return;
label_DFE6:; /* CInvu */
    /* $DFE6: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x12; g_cpu.C=(g_cpu.Y>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_DFE8:;
    /* $DFE8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DFF2;
label_DFEA:;
    /* $DFEA: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x2E; g_cpu.C=(g_cpu.Y>=0x2E)?1:0; FLAG_NZ(r&0xFF); }
label_DFEC:;
    /* $DFEC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DFF2;
label_DFEE:;
    /* $DFEE: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x07; g_cpu.C=(g_cpu.Y>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_DFF0:;
    /* $DFF0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E066;
label_DFF2:; /* YesIn */
    /* $DFF2: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1AE);
label_DFF5:;
    /* $DFF5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DFFA;
label_DFF7:; /* NoEToBGCollision */
    /* $DFF7: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE0E2); return;
label_DFFA:; /* HandleEToBGCollision */
    /* $DFFA: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1B5);
label_DFFD:;
    /* $DFFD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DFF7;
    }
label_DFFF:;
    /* $DFFF: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x23; g_cpu.C=(g_cpu.A>=0x23)?1:0; FLAG_NZ(r&0xFF); }
label_E001:;
    /* $E001: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E067;
label_E003:;
    /* $E003: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x02); FLAG_NZ(g_cpu.Y);
label_E005:;
    /* $E005: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E007:;
    /* $E007: 91 */ maybe_trigger_vblank(6); nes_write((nes_read16zp(0x06) + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E009:;
    /* $E009: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E00B:;
    /* $E00B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_E00D:;
    /* $E00D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E01B;
label_E00F:;
    /* $E00F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_E011:;
    /* $E011: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E016;
label_E013:;
    /* $E013: 20 */ maybe_trigger_vblank(6); call_by_address(0xE18E);
label_E016:; /* GiveOEPoints */
    /* $E016: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E018:;
    /* $E018: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_E01B:; /* ChkToStunEnemies */
    /* $E01B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x09; g_cpu.C=(g_cpu.A>=0x09)?1:0; FLAG_NZ(r&0xFF); }
label_E01D:;
    /* $E01D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E02F;
label_E01F:;
    /* $E01F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_E021:;
    /* $E021: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E02F;
label_E023:;
    /* $E023: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0A; g_cpu.C=(g_cpu.A>=0x0A)?1:0; FLAG_NZ(r&0xFF); }
label_E025:;
    /* $E025: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E02B;
label_E027:;
    /* $E027: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_E029:;
    /* $E029: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E02F;
label_E02B:; /* Demote */
    /* $E02B: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_E02D:;
    /* $E02D: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_E02F:; /* SetStun */
    /* $E02F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E031:;
    /* $E031: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF0; FLAG_NZ(g_cpu.A);
label_E033:;
    /* $E033: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x02; FLAG_NZ(g_cpu.A);
label_E035:;
    /* $E035: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E037:;
    /* $E037: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0xCF + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E039:;
    /* $E039: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0xCF + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E03B:;
    /* $E03B: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E03D:;
    /* $E03D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_E03F:;
    /* $E03F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E048;
label_E041:;
    /* $E041: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFD; FLAG_NZ(g_cpu.A);
label_E043:;
    /* $E043: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_E046:;
    /* $E046: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E04A;
label_E048:; /* SetWYSpd */
    /* $E048: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_E04A:; /* SetNotW */
    /* $E04A: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_E04C:;
    /* $E04C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_E04E:;
    /* $E04E: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_E051:;
    /* $E051: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_E054;
label_E053:;
    /* $E053: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E054:; /* ChkBBill */
    /* $E054: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E056:;
    /* $E056: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x33; g_cpu.C=(g_cpu.A>=0x33)?1:0; FLAG_NZ(r&0xFF); }
label_E058:;
    /* $E058: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E060;
label_E05A:;
    /* $E05A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_E05C:;
    /* $E05C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E060;
label_E05E:;
    /* $E05E: 94 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.Y);
label_E060:; /* NoCDirF */
    /* $E060: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E061:;
    /* $E061: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xDFBF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E064:;
    /* $E064: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_E066:; /* ExEBGChk */
    /* $E066: 60 */ maybe_trigger_vblank(6);
    return;
label_E067:; /* LandEnemyProperly */
    /* $E067: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x04); FLAG_NZ(g_cpu.A);
label_E069:;
    /* $E069: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_E06A:;
    /* $E06A: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x08; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E06C:;
    /* $E06C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E06E:;
    /* $E06E: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E0E2;
label_E070:;
    /* $E070: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E072:;
    /* $E072: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_E074:;
    /* $E074: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0CD;
label_E076:;
    /* $E076: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E078:;
    /* $E078: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E079:;
    /* $E079: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E07E;
label_E07B:; /* SChkA */
    /* $E07B: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE0FE); return;
label_E07E:; /* ChkLandedEnemyState */
    /* $E07E: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E080:;
    /* $E080: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E07B;
    }
label_E082:;
    /* $E082: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E084:;
    /* $E084: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E0A5;
label_E086:;
    /* $E086: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_E088:;
    /* $E088: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E0A4;
label_E08A:;
    /* $E08A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E08C:;
    /* $E08C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_E08E:;
    /* $E08E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0A5;
label_E090:;
    /* $E090: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_E092:;
    /* $E092: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_E094:;
    /* $E094: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x12; g_cpu.C=(g_cpu.Y>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_E096:;
    /* $E096: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E09A;
label_E098:;
    /* $E098: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E09A:; /* SetForStn */
    /* $E09A: 9D */ maybe_trigger_vblank(5); nes_write((0x0796 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_E09D:;
    /* $E09D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_E09F:;
    /* $E09F: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E0A1:;
    /* $E0A1: 20 */ maybe_trigger_vblank(6); call_by_address(0xE14F);
label_E0A4:; /* ExSteChk */
    /* $E0A4: 60 */ maybe_trigger_vblank(6);
    return;
label_E0A5:; /* ProcEnemyDirection */
    /* $E0A5: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0A7:;
    /* $E0A7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_E0A9:;
    /* $E0A9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E0CD;
label_E0AB:;
    /* $E0AB: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x12; g_cpu.C=(g_cpu.A>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_E0AD:;
    /* $E0AD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0BD;
label_E0AF:;
    /* $E0AF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E0B1:;
    /* $E0B1: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_E0B3:;
    /* $E0B3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_E0B5:;
    /* $E0B5: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_E0B7:;
    /* $E0B7: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_E0B9:;
    /* $E0B9: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_E0BB:;
    /* $E0BB: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E0CD;
label_E0BD:; /* InvtD */
    /* $E0BD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_E0BF:;
    /* $E0BF: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_E0C2:;
    /* $E0C2: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_E0C5;
label_E0C4:;
    /* $E0C4: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E0C5:; /* CNwCDir */
    /* $E0C5: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_E0C6:;
    /* $E0C6: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x46 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E0C8:;
    /* $E0C8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0CD;
label_E0CA:;
    /* $E0CA: 20 */ maybe_trigger_vblank(6); call_by_address(0xE124);
label_E0CD:; /* LandEnemyInitState */
    /* $E0CD: 20 */ maybe_trigger_vblank(6); call_by_address(0xE14F);
label_E0D0:;
    /* $E0D0: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0D2:;
    /* $E0D2: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x80; FLAG_NZ(g_cpu.A);
label_E0D4:;
    /* $E0D4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0DB;
label_E0D6:;
    /* $E0D6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E0D8:;
    /* $E0D8: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E0DA:;
    /* $E0DA: 60 */ maybe_trigger_vblank(6);
    return;
label_E0DB:; /* NMovShellFallBit */
    /* $E0DB: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0DD:;
    /* $E0DD: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xBF; FLAG_NZ(g_cpu.A);
label_E0DF:;
    /* $E0DF: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E0E1:;
    /* $E0E1: 60 */ maybe_trigger_vblank(6);
    return;
label_E0E2:; /* ChkForRedKoopa */
    /* $E0E2: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0E4:;
    /* $E0E4: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_E0E6:;
    /* $E0E6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0EC;
label_E0E8:;
    /* $E0E8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0EA:;
    /* $E0EA: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E124;
label_E0EC:; /* Chk2MSBSt */
    /* $E0EC: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0EE:;
    /* $E0EE: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_E0EF:;
    /* $E0EF: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E0F0:;
    /* $E0F0: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E0F9;
label_E0F2:;
    /* $E0F2: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0F4:;
    /* $E0F4: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_E0F6:;
    /* $E0F6: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE0FC); return;
label_E0F9:; /* GetSteFromD */
    /* $E0F9: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xDFB9 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E0FC:; /* SetD6Ste */
    /* $E0FC: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E0FE:; /* DoEnemySideCheck */
    /* $E0FE: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E100:;
    /* $E100: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_E102:;
    /* $E102: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E123;
label_E104:;
    /* $E104: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x16; FLAG_NZ(g_cpu.Y);
label_E106:;
    /* $E106: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E108:;
    /* $E108: 85 */ maybe_trigger_vblank(3); nes_write(0xEB, g_cpu.A);
label_E10A:; /* SdeCLoop */
    /* $E10A: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xEB); FLAG_NZ(g_cpu.A);
label_E10C:;
    /* $E10C: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x46 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E10E:;
    /* $E10E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E11C;
label_E110:;
    /* $E110: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E112:;
    /* $E112: 20 */ maybe_trigger_vblank(6); call_by_address(0xE388);
label_E115:;
    /* $E115: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E11C;
label_E117:;
    /* $E117: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1B5);
label_E11A:;
    /* $E11A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E124;
label_E11C:; /* NextSdeC */
    /* $E11C: C6 */ maybe_trigger_vblank(5); { uint16_t a=0xEB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E11E:;
    /* $E11E: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E11F:;
    /* $E11F: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x18; g_cpu.C=(g_cpu.Y>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_E121:;
    /* $E121: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E10A;
    }
label_E123:; /* ExESdeC */
    /* $E123: 60 */ maybe_trigger_vblank(6);
    return;
label_E124:; /* ChkForBump_HammerBroJ */
    /* $E124: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x05; g_cpu.C=(g_cpu.X>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E126:;
    /* $E126: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E131;
label_E128:;
    /* $E128: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E12A:;
    /* $E12A: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E12B:;
    /* $E12B: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E131;
label_E12D:;
    /* $E12D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E12F:;
    /* $E12F: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_E131:; /* NoBump */
    /* $E131: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E133:;
    /* $E133: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E135:;
    /* $E135: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E140;
label_E137:;
    /* $E137: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E139:;
    /* $E139: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_E13B:;
    /* $E13B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xFA; FLAG_NZ(g_cpu.Y);
label_E13D:;
    /* $E13D: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xCA37); return;
label_E140:; /* InvEnemyDir */
    /* $E140: 4C */ maybe_trigger_vblank(3); goto label_DB36;
label_E143:; /* PlayerEnemyDiff */
    /* $E143: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E145:;
    /* $E145: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_E146:;
    /* $E146: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x86); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E148:;
    /* $E148: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_E14A:;
    /* $E14A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E14C:;
    /* $E14C: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x6D); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E14E:;
    /* $E14E: 60 */ maybe_trigger_vblank(6);
    return;
label_E14F:; /* EnemyLanding */
    /* $E14F: 20 */ maybe_trigger_vblank(6); call_by_address(0xC363);
label_E152:;
    /* $E152: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E154:;
    /* $E154: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF0; FLAG_NZ(g_cpu.A);
label_E156:;
    /* $E156: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x08; FLAG_NZ(g_cpu.A);
label_E158:;
    /* $E158: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_E15A:;
    /* $E15A: 60 */ maybe_trigger_vblank(6);
    return;
label_E15B:; /* SubtEnemyYPos */
    /* $E15B: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E15D:;
    /* $E15D: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E15E:;
    /* $E15E: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x3E + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x3E); g_cpu.A=r&0xFF; }
label_E160:;
    /* $E160: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x44; g_cpu.C=(g_cpu.A>=0x44)?1:0; FLAG_NZ(r&0xFF); }
label_E162:;
    /* $E162: 60 */ maybe_trigger_vblank(6);
    return;
label_E163:; /* EnemyJump */
    /* $E163: 20 */ maybe_trigger_vblank(6); call_by_address(0xE15B);
label_E166:;
    /* $E166: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E182;
label_E168:;
    /* $E168: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E16A:;
    /* $E16A: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E16B:;
    /* $E16B: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x02 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x02); g_cpu.A=r&0xFF; }
label_E16D:;
    /* $E16D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_E16F:;
    /* $E16F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E182;
label_E171:;
    /* $E171: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1AE);
label_E174:;
    /* $E174: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E182;
label_E176:;
    /* $E176: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1B5);
label_E179:;
    /* $E179: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E182;
label_E17B:;
    /* $E17B: 20 */ maybe_trigger_vblank(6); call_by_address(0xE14F);
label_E17E:;
    /* $E17E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFD; FLAG_NZ(g_cpu.A);
label_E180:;
    /* $E180: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_E182:; /* DoSide */
    /* $E182: 4C */ maybe_trigger_vblank(3); goto label_E0FE;
label_E185:; /* HammerBroBGColl */
    /* $E185: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1AE);
label_E188:;
    /* $E188: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E1A7;
label_E18A:;
    /* $E18A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x23; g_cpu.C=(g_cpu.A>=0x23)?1:0; FLAG_NZ(r&0xFF); }
label_E18C:;
    /* $E18C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E196;
label_E18E:; /* KillEnemyAboveBlock */
    /* $E18E: 20 */ maybe_trigger_vblank(6); call_by_address(0xD795);
label_E191:;
    /* $E191: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFC; FLAG_NZ(g_cpu.A);
label_E193:;
    /* $E193: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_E195:;
    /* $E195: 60 */ maybe_trigger_vblank(6);
    return;
label_E196:; /* UnderHammerBro */
    /* $E196: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x078A + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E199:;
    /* $E199: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E1A7;
label_E19B:;
    /* $E19B: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E19D:;
    /* $E19D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x88; FLAG_NZ(g_cpu.A);
label_E19F:;
    /* $E19F: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E1A1:;
    /* $E1A1: 20 */ maybe_trigger_vblank(6); call_by_address(0xE14F);
label_E1A4:;
    /* $E1A4: 4C */ maybe_trigger_vblank(3); goto label_E0FE;
label_E1A7:; /* NoUnderHammerBro */
    /* $E1A7: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E1A9:;
    /* $E1A9: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x01; FLAG_NZ(g_cpu.A);
label_E1AB:;
    /* $E1AB: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E1AD:;
    /* $E1AD: 60 */ maybe_trigger_vblank(6);
    return;
label_E1AE:; /* ChkUnderEnemy */
    /* $E1AE: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E1B0:;
    /* $E1B0: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x15; FLAG_NZ(g_cpu.Y);
label_E1B2:;
    /* $E1B2: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE388); return;
label_E1B5:; /* ChkForNonSolids */
    /* $E1B5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x26; g_cpu.C=(g_cpu.A>=0x26)?1:0; FLAG_NZ(r&0xFF); }
label_E1B7:;
    /* $E1B7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E1C7;
label_E1B9:;
    /* $E1B9: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xC2; g_cpu.C=(g_cpu.A>=0xC2)?1:0; FLAG_NZ(r&0xFF); }
label_E1BB:;
    /* $E1BB: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E1C7;
label_E1BD:;
    /* $E1BD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xC3; g_cpu.C=(g_cpu.A>=0xC3)?1:0; FLAG_NZ(r&0xFF); }
label_E1BF:;
    /* $E1BF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E1C7;
label_E1C1:;
    /* $E1C1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x5F; g_cpu.C=(g_cpu.A>=0x5F)?1:0; FLAG_NZ(r&0xFF); }
label_E1C3:;
    /* $E1C3: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E1C7;
label_E1C5:;
    /* $E1C5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x60; g_cpu.C=(g_cpu.A>=0x60)?1:0; FLAG_NZ(r&0xFF); }
label_E1C7:; /* NSFnd */
    /* $E1C7: 60 */ maybe_trigger_vblank(6);
    return;
label_E1C8:; /* FireballBGCollision */
    /* $E1C8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD5 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E1CA:;
    /* $E1CA: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x18; g_cpu.C=(g_cpu.A>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_E1CC:;
    /* $E1CC: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E1EF;
label_E1CE:;
    /* $E1CE: 20 */ maybe_trigger_vblank(6); call_by_address(0xE39C);
label_E1D1:;
    /* $E1D1: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E1EF;
label_E1D3:;
    /* $E1D3: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1B5);
label_E1D6:;
    /* $E1D6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E1EF;
label_E1D8:;
    /* $E1D8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA6 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E1DA:;
    /* $E1DA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_E1F4;
label_E1DC:;
    /* $E1DC: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x3A + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E1DE:;
    /* $E1DE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E1F4;
label_E1E0:;
    /* $E1E0: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFD; FLAG_NZ(g_cpu.A);
label_E1E2:;
    /* $E1E2: 95 */ maybe_trigger_vblank(4); nes_write((0xA6 + g_cpu.X) & 0xFF, g_cpu.A);
label_E1E4:;
    /* $E1E4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E1E6:;
    /* $E1E6: 95 */ maybe_trigger_vblank(4); nes_write((0x3A + g_cpu.X) & 0xFF, g_cpu.A);
label_E1E8:;
    /* $E1E8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD5 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E1EA:;
    /* $E1EA: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF8; FLAG_NZ(g_cpu.A);
label_E1EC:;
    /* $E1EC: 95 */ maybe_trigger_vblank(4); nes_write((0xD5 + g_cpu.X) & 0xFF, g_cpu.A);
label_E1EE:;
    /* $E1EE: 60 */ maybe_trigger_vblank(6);
    return;
label_E1EF:; /* ClearBounceFlag */
    /* $E1EF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E1F1:;
    /* $E1F1: 95 */ maybe_trigger_vblank(4); nes_write((0x3A + g_cpu.X) & 0xFF, g_cpu.A);
label_E1F3:;
    /* $E1F3: 60 */ maybe_trigger_vblank(6);
    return;
label_E1F4:; /* InitFireballExplode */
    /* $E1F4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_E1F6:;
    /* $E1F6: 95 */ maybe_trigger_vblank(4); nes_write((0x24 + g_cpu.X) & 0xFF, g_cpu.A);
label_E1F8:;
    /* $E1F8: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E1FA:;
    /* $E1FA: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_E1FC:;
    /* $E1FC: 60 */ maybe_trigger_vblank(6);
    return;
label_E1FD:; /* BoundBoxCtrlData */
    /* $E1FD: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E1FE:;
    /* $E1FE: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E1FF:;
    /* $E1FF: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x0320; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E202:;
    /* $E202: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x0D + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E204:;
    /* $E204: 20 */ maybe_trigger_vblank(6); call_by_address(0x1402);
label_E207:;
    /* $E207: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x0220; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E20A:;
    /* $E20A: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x0E; FLAG_NZ(g_cpu.A);
label_E20C:;
    /* $E20C: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x00 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E20E:;
    /* $E20E: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE20E); return;
label_E20F:;
    /* $E20F: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E210:;
    /* $E210: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E212:;
    /* $E212: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE212); return;
label_E213:;
    /* $E213: 20 */ maybe_trigger_vblank(6); call_by_address(0x000D);
label_E216:;
    /* $E216: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE216); return;
label_E217:;
    /* $E217: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_E226;
label_E219:;
    /* $E219: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE219); return;
label_E21A:;
    /* $E21A: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE21A); return;
label_E21B:;
    /* $E21B: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E21C:;
    /* $E21C: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E21D:;
    /* $E21D: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E21F:;
    /* $E21F: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E220:;
    /* $E220: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E221:;
    /* $E221: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E223:;
    /* $E223: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x0014); FLAG_NZ(g_cpu.A);
label_E226:;
    /* $E226: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E227:;
    /* $E227: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { call_by_address(0xE23E); return; }
label_E229:;
    /* $E229: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E22B:;
    /* $E22B: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x8A1C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E22E:;
    /* $E22E: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E22F:;
    /* $E22F: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x07 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x07); g_cpu.A=r&0xFF; }
label_E231:;
    /* $E231: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E232:;
    /* $E232: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_E234:;
    /* $E234: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E23D;
label_E236:; /* GetMiscBoundBox */
    /* $E236: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E237:;
    /* $E237: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E238:;
    /* $E238: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x09 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x09); g_cpu.A=r&0xFF; }
label_E23A:;
    /* $E23A: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E23B:;
    /* $E23B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x06; FLAG_NZ(g_cpu.Y);
label_E23D:; /* FBallB */
    /* $E23D: 20 */ maybe_trigger_vblank(6); call_by_address(0xE29C);
label_E240:;
    /* $E240: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE2DE); return;
label_E243:; /* GetEnemyBoundBox */
    /* $E243: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x48; FLAG_NZ(g_cpu.Y);
label_E245:;
    /* $E245: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_E247:;
    /* $E247: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x44; FLAG_NZ(g_cpu.Y);
label_E249:;
    /* $E249: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE252); return;
label_E24C:; /* SmallPlatformBoundBox */
    /* $E24C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x08; FLAG_NZ(g_cpu.Y);
label_E24E:;
    /* $E24E: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_E250:;
    /* $E250: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x04; FLAG_NZ(g_cpu.Y);
label_E252:; /* GetMaskedOffScrBits */
    /* $E252: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E254:;
    /* $E254: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_E255:;
    /* $E255: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x071C); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E258:;
    /* $E258: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_E25A:;
    /* $E25A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E25C:;
    /* $E25C: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x071A); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E25F:;
    /* $E25F: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_E267;
label_E261:;
    /* $E261: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x01); FLAG_NZ(g_cpu.A);
label_E263:;
    /* $E263: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E267;
label_E265:;
    /* $E265: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x00); FLAG_NZ(g_cpu.Y);
label_E267:; /* CMBits */
    /* $E267: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_E268:;
    /* $E268: 2D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read(0x03D1); FLAG_NZ(g_cpu.A);
label_E26B:;
    /* $E26B: 9D */ maybe_trigger_vblank(5); nes_write((0x03D8 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_E26E:;
    /* $E26E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E289;
label_E270:;
    /* $E270: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE27C); return;
label_E273:; /* LargePlatformBoundBox */
    /* $E273: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_E274:;
    /* $E274: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1F6);
label_E277:;
    /* $E277: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_E278:;
    /* $E278: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xFE; g_cpu.C=(g_cpu.A>=0xFE)?1:0; FLAG_NZ(r&0xFF); }
label_E27A:;
    /* $E27A: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E289;
label_E27C:; /* SetupEOffsetFBBox */
    /* $E27C: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E27D:;
    /* $E27D: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E27E:;
    /* $E27E: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_E280:;
    /* $E280: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E281:;
    /* $E281: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_E283:;
    /* $E283: 20 */ maybe_trigger_vblank(6); call_by_address(0xE29C);
label_E286:;
    /* $E286: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE2DE); return;
label_E289:; /* MoveBoundBoxOffscreen */
    /* $E289: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E28A:;
    /* $E28A: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E28B:;
    /* $E28B: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E28C:;
    /* $E28C: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_E28D:;
    /* $E28D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_E28F:;
    /* $E28F: 99 */ maybe_trigger_vblank(5); nes_write((0x04B0 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E292:;
    /* $E292: 99 */ maybe_trigger_vblank(5); nes_write((0x04B1 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E295:;
    /* $E295: 99 */ maybe_trigger_vblank(5); nes_write((0x04B2 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E298:;
    /* $E298: 99 */ maybe_trigger_vblank(5); nes_write((0x04B3 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E29B:;
    /* $E29B: 60 */ maybe_trigger_vblank(6);
    return;
label_E29C:; /* BoundingBoxCore */
    /* $E29C: 86 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.X);
label_E29E:;
    /* $E29E: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03B8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E2A1:;
    /* $E2A1: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_E2A3:;
    /* $E2A3: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03AD + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E2A6:;
    /* $E2A6: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_E2A8:;
    /* $E2A8: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E2A9:;
    /* $E2A9: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E2AA:;
    /* $E2AA: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E2AB:;
    /* $E2AB: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E2AC:;
    /* $E2AC: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_E2AD:;
    /* $E2AD: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0499 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E2B0:;
    /* $E2B0: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E2B1:;
    /* $E2B1: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E2B2:;
    /* $E2B2: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E2B3:;
    /* $E2B3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_E2B5:;
    /* $E2B5: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E2B6:;
    /* $E2B6: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE1FD + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E2B9:;
    /* $E2B9: 99 */ maybe_trigger_vblank(5); nes_write((0x04AC + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E2BC:;
    /* $E2BC: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_E2BE:;
    /* $E2BE: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E2BF:;
    /* $E2BF: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE1FF + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E2C2:;
    /* $E2C2: 99 */ maybe_trigger_vblank(5); nes_write((0x04AE + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E2C5:;
    /* $E2C5: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_E2C6:;
    /* $E2C6: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E2C7:;
    /* $E2C7: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_E2C9:;
    /* $E2C9: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E2CA:;
    /* $E2CA: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE1FD + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E2CD:;
    /* $E2CD: 99 */ maybe_trigger_vblank(5); nes_write((0x04AC + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E2D0:;
    /* $E2D0: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_E2D2:;
    /* $E2D2: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E2D3:;
    /* $E2D3: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE1FF + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E2D6:;
    /* $E2D6: 99 */ maybe_trigger_vblank(5); nes_write((0x04AE + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E2D9:;
    /* $E2D9: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E2DA:;
    /* $E2DA: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_E2DB:;
    /* $E2DB: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x00); FLAG_NZ(g_cpu.X);
label_E2DD:;
    /* $E2DD: 60 */ maybe_trigger_vblank(6);
    return;
label_E2DE:; /* CheckRightScreenBBox */
    /* $E2DE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071C); FLAG_NZ(g_cpu.A);
label_E2E1:;
    /* $E2E1: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E2E2:;
    /* $E2E2: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x80 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x80); g_cpu.A=r&0xFF; }
label_E2E4:;
    /* $E2E4: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_E2E6:;
    /* $E2E6: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071A); FLAG_NZ(g_cpu.A);
label_E2E9:;
    /* $E2E9: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_E2EB:;
    /* $E2EB: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_E2ED:;
    /* $E2ED: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x86 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E2EF:;
    /* $E2EF: C5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x02); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E2F1:;
    /* $E2F1: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6D + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E2F3:;
    /* $E2F3: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x01); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E2F5:;
    /* $E2F5: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E30C;
label_E2F7:;
    /* $E2F7: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AE + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E2FA:;
    /* $E2FA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_E309;
label_E2FC:;
    /* $E2FC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_E2FE:;
    /* $E2FE: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0x04AC + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_E301:;
    /* $E301: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_E306;
label_E303:;
    /* $E303: 99 */ maybe_trigger_vblank(5); nes_write((0x04AC + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E306:; /* SORte */
    /* $E306: 99 */ maybe_trigger_vblank(5); nes_write((0x04AE + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E309:; /* NoOfs */
    /* $E309: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E30B:;
    /* $E30B: 60 */ maybe_trigger_vblank(6);
    return;
label_E30C:; /* CheckLeftScreenBBox */
    /* $E30C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AC + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E30F:;
    /* $E30F: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_E322;
label_E311:;
    /* $E311: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xA0; g_cpu.C=(g_cpu.A>=0xA0)?1:0; FLAG_NZ(r&0xFF); }
label_E313:;
    /* $E313: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E322;
label_E315:;
    /* $E315: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E317:;
    /* $E317: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0x04AE + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_E31A:;
    /* $E31A: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_E31F;
label_E31C:;
    /* $E31C: 99 */ maybe_trigger_vblank(5); nes_write((0x04AE + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E31F:; /* SOLft */
    /* $E31F: 99 */ maybe_trigger_vblank(5); nes_write((0x04AC + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E322:; /* NoOfs2 */
    /* $E322: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E324:;
    /* $E324: 60 */ maybe_trigger_vblank(6);
    return;
label_E325:; /* PlayerCollisionCore */
    /* $E325: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_E327:; /* SprObjectCollisionCore */
    /* $E327: 84 */ maybe_trigger_vblank(3); nes_write(0x06, g_cpu.Y);
label_E329:;
    /* $E329: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E32B:;
    /* $E32B: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_E32D:; /* CollisionCoreLoop */
    /* $E32D: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AC + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E330:;
    /* $E330: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E333:;
    /* $E333: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E35F;
label_E335:;
    /* $E335: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AE + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E338:;
    /* $E338: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E34C;
label_E33A:;
    /* $E33A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E37E;
label_E33C:;
    /* $E33C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AE + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E33F:;
    /* $E33F: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E342:;
    /* $E342: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E37E;
label_E344:;
    /* $E344: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E347:;
    /* $E347: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E37E;
label_E349:;
    /* $E349: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x06); FLAG_NZ(g_cpu.Y);
label_E34B:;
    /* $E34B: 60 */ maybe_trigger_vblank(6);
    return;
label_E34C:; /* SecondBoxVerticalChk */
    /* $E34C: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AE + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E34F:;
    /* $E34F: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E352:;
    /* $E352: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E37E;
label_E354:;
    /* $E354: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AE + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E357:;
    /* $E357: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E35A:;
    /* $E35A: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E37E;
label_E35C:;
    /* $E35C: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x06); FLAG_NZ(g_cpu.Y);
label_E35E:;
    /* $E35E: 60 */ maybe_trigger_vblank(6);
    return;
label_E35F:; /* FirstBoxGreater */
    /* $E35F: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E362:;
    /* $E362: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E37E;
label_E364:;
    /* $E364: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AE + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E367:;
    /* $E367: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E37E;
label_E369:;
    /* $E369: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E37E;
label_E36B:;
    /* $E36B: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AE + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E36E:;
    /* $E36E: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E37A;
label_E370:;
    /* $E370: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E37A;
label_E372:;
    /* $E372: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AE + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E375:;
    /* $E375: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E378:;
    /* $E378: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E37E;
label_E37A:; /* NoCollisionFound */
    /* $E37A: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E37B:;
    /* $E37B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x06); FLAG_NZ(g_cpu.Y);
label_E37D:;
    /* $E37D: 60 */ maybe_trigger_vblank(6);
    return;
label_E37E:; /* CollisionFound */
    /* $E37E: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_E37F:;
    /* $E37F: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E380:;
    /* $E380: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x07; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E382:;
    /* $E382: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E32D;
    }
label_E384:;
    /* $E384: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_E385:;
    /* $E385: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x06); FLAG_NZ(g_cpu.Y);
label_E387:;
    /* $E387: 60 */ maybe_trigger_vblank(6);
    return;
label_E388:; /* BlockBufferChk_Enemy */
    /* $E388: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E389:;
    /* $E389: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E38A:;
    /* $E38A: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E38B:;
    /* $E38B: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_E38D:;
    /* $E38D: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E38E:;
    /* $E38E: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E38F:;
    /* $E38F: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE3A5); return;
label_E392:; /* ResidualMiscObjectCode */
    /* $E392: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E393:;
    /* $E393: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E394:;
    /* $E394: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x0D + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0D); g_cpu.A=r&0xFF; }
label_E396:;
    /* $E396: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E397:;
    /* $E397: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x1B; FLAG_NZ(g_cpu.Y);
label_E399:;
    /* $E399: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE3A3); return;
label_E39C:; /* BlockBufferChk_FBall */
    /* $E39C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x1A; FLAG_NZ(g_cpu.Y);
label_E39E:;
    /* $E39E: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E39F:;
    /* $E39F: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3A0:;
    /* $E3A0: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x07 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x07); g_cpu.A=r&0xFF; }
label_E3A2:;
    /* $E3A2: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E3A3:; /* ResJmpM */
    /* $E3A3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E3A5:; /* BBChk_E */
    /* $E3A5: 20 */ maybe_trigger_vblank(6); call_by_address(0xE3F0);
label_E3A8:;
    /* $E3A8: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E3AA:;
    /* $E3AA: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_E3AC:;
    /* $E3AC: 60 */ maybe_trigger_vblank(6);
    return;
label_E3AD:; /* BlockBufferAdderData */
    /* $E3AD: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE3AD); return;
label_E3AE:;
    /* $E3AE: 07 */ maybe_trigger_vblank(5); /* ILLEGAL $07 — skip 2 */
label_E3B0:; /* BlockBuffer_X_Adder */
    /* $E3B0: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E3B1:;
    /* $E3B1: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E3B3:;
    /* $E3B3: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E3B4:;
    /* $E3B4: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E3B5:;
    /* $E3B5: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x080D); FLAG_NZ(g_cpu.A);
label_E3B8:;
    /* $E3B8: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E3BA:;
    /* $E3BA: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E3BB:;
    /* $E3BB: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E3BC:;
    /* $E3BC: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x080D); FLAG_NZ(g_cpu.A);
label_E3BF:;
    /* $E3BF: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E3C1:;
    /* $E3C1: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E3C2:;
    /* $E3C2: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E3C3:;
    /* $E3C3: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x080D); FLAG_NZ(g_cpu.A);
label_E3C6:;
    /* $E3C6: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE3C6); return;
label_E3C7:;
    /* $E3C7: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_E3CD;
label_E3C9:;
    /* $E3C9: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x04 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E3CB:;
    /* $E3CB: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E3CD:;
    /* $E3CD: 20 */ maybe_trigger_vblank(6); call_by_address(0x0820);
label_E3D0:;
    /* $E3D0: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3D1:;
    /* $E3D1: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E3D2:;
    /* $E3D2: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3D3:;
    /* $E3D3: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E3D4:;
    /* $E3D4: 20 */ maybe_trigger_vblank(6); call_by_address(0x0820);
label_E3D7:;
    /* $E3D7: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3D8:;
    /* $E3D8: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E3D9:;
    /* $E3D9: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3DA:;
    /* $E3DA: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_E3DB:;
    /* $E3DB: 20 */ maybe_trigger_vblank(6); call_by_address(0x1820);
label_E3DE:;
    /* $E3DE: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3DF:;
    /* $E3DF: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3E0:;
    /* $E3E0: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3E1:;
    /* $E3E1: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3E2:;
    /* $E3E2: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x14 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E3E4:;
    /* $E3E4: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x06; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E3E6:;
    /* $E3E6: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E3E7:;
    /* $E3E7: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E3B1;
    }
label_E3E9:; /* BlockBufferColli_Head */
    /* $E3E9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E3EB:;
    /* $E3EB: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x01A9); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_E3EE:;
    /* $E3EE: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_E3F0:; /* BlockBufferCollision */
    /* $E3F0: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E3F1:;
    /* $E3F1: 84 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.Y);
label_E3F3:;
    /* $E3F3: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E3F6:;
    /* $E3F6: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3F7:;
    /* $E3F7: 75 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x86 + g_cpu.X) & 0xFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E3F9:;
    /* $E3F9: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_E3FB:;
    /* $E3FB: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6D + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E3FD:;
    /* $E3FD: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_E3FF:;
    /* $E3FF: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_E401:;
    /* $E401: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E402:;
    /* $E402: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x05); FLAG_NZ(g_cpu.A);
label_E404:;
    /* $E404: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_E405:;
    /* $E405: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E406:;
    /* $E406: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E407:;
    /* $E407: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E408:;
    /* $E408: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BE1);
label_E40B:;
    /* $E40B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x04); FLAG_NZ(g_cpu.Y);
label_E40D:;
    /* $E40D: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCE + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E40F:;
    /* $E40F: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E410:;
    /* $E410: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE3CC + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E413:;
    /* $E413: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF0; FLAG_NZ(g_cpu.A);
label_E415:;
    /* $E415: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_E416:;
    /* $E416: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x20; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E418:;
    /* $E418: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_E41A:;
    /* $E41A: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_E41B:;
    /* $E41B: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0x06) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E41D:;
    /* $E41D: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_E41F:;
    /* $E41F: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x04); FLAG_NZ(g_cpu.Y);
label_E421:;
    /* $E421: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E422:;
    /* $E422: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E429;
label_E424:;
    /* $E424: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCE + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E426:;
    /* $E426: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE42B); return;
label_E429:; /* RetXC */
    /* $E429: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x86 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E42B:; /* RetYC */
    /* $E42B: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_E42D:;
    /* $E42D: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_E42F:;
    /* $E42F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x03); FLAG_NZ(g_cpu.A);
label_E431:;
    /* $E431: 60 */ maybe_trigger_vblank(6);
    return;
label_E432:;
    /* $E432: FF */ maybe_trigger_vblank(7); /* ILLEGAL $FF — skip 3 */
label_E435:; /* DrawVine */
    /* $E435: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_E437:;
    /* $E437: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B9); FLAG_NZ(g_cpu.A);
label_E43A:;
    /* $E43A: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E43B:;
    /* $E43B: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE433 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E43E:;
    /* $E43E: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0x039A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_E441:;
    /* $E441: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E444:;
    /* $E444: 84 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.Y);
label_E446:;
    /* $E446: 20 */ maybe_trigger_vblank(6); call_by_address(0xE4AE);
label_E449:;
    /* $E449: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_E44C:;
    /* $E44C: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E44F:;
    /* $E44F: 99 */ maybe_trigger_vblank(5); nes_write((0x020B + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E452:;
    /* $E452: 99 */ maybe_trigger_vblank(5); nes_write((0x0213 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E455:;
    /* $E455: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E456:;
    /* $E456: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x06 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x06); g_cpu.A=r&0xFF; }
label_E458:;
    /* $E458: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E45B:;
    /* $E45B: 99 */ maybe_trigger_vblank(5); nes_write((0x020F + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E45E:;
    /* $E45E: 99 */ maybe_trigger_vblank(5); nes_write((0x0217 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E461:;
    /* $E461: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x21; FLAG_NZ(g_cpu.A);
label_E463:;
    /* $E463: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E466:;
    /* $E466: 99 */ maybe_trigger_vblank(5); nes_write((0x020A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E469:;
    /* $E469: 99 */ maybe_trigger_vblank(5); nes_write((0x0212 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E46C:;
    /* $E46C: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_E46E:;
    /* $E46E: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E471:;
    /* $E471: 99 */ maybe_trigger_vblank(5); nes_write((0x020E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E474:;
    /* $E474: 99 */ maybe_trigger_vblank(5); nes_write((0x0216 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E477:;
    /* $E477: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x05; FLAG_NZ(g_cpu.X);
label_E479:; /* VineTL */
    /* $E479: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xE1; FLAG_NZ(g_cpu.A);
label_E47B:;
    /* $E47B: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E47E:;
    /* $E47E: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E47F:;
    /* $E47F: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E480:;
    /* $E480: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E481:;
    /* $E481: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E482:;
    /* $E482: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_E483:;
    /* $E483: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E479;
    }
label_E485:;
    /* $E485: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x02); FLAG_NZ(g_cpu.Y);
label_E487:;
    /* $E487: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_E489:;
    /* $E489: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E490;
label_E48B:;
    /* $E48B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xE0; FLAG_NZ(g_cpu.A);
label_E48D:;
    /* $E48D: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E490:; /* SkpVTop */
    /* $E490: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_E492:; /* ChkFTop */
    /* $E492: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x039D); FLAG_NZ(g_cpu.A);
label_E495:;
    /* $E495: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_E496:;
    /* $E496: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x0200 + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E499:;
    /* $E499: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x64; g_cpu.C=(g_cpu.A>=0x64)?1:0; FLAG_NZ(r&0xFF); }
label_E49B:;
    /* $E49B: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E4A2;
label_E49D:;
    /* $E49D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E49F:;
    /* $E49F: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E4A2:; /* NextVSp */
    /* $E4A2: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4A3:;
    /* $E4A3: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4A4:;
    /* $E4A4: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4A5:;
    /* $E4A5: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4A6:;
    /* $E4A6: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_E4A7:;
    /* $E4A7: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x06; g_cpu.C=(g_cpu.X>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_E4A9:;
    /* $E4A9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E492;
    }
label_E4AB:;
    /* $E4AB: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x00); FLAG_NZ(g_cpu.Y);
label_E4AD:;
    /* $E4AD: 60 */ maybe_trigger_vblank(6);
    return;
label_E4AE:; /* SixSpriteStacker */
    /* $E4AE: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x06; FLAG_NZ(g_cpu.X);
label_E4B0:; /* StkLp */
    /* $E4B0: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E4B3:;
    /* $E4B3: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E4B4:;
    /* $E4B4: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_E4B6:;
    /* $E4B6: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4B7:;
    /* $E4B7: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4B8:;
    /* $E4B8: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4B9:;
    /* $E4B9: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4BA:;
    /* $E4BA: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_E4BB:;
    /* $E4BB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E4B0;
    }
label_E4BD:;
    /* $E4BD: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x02); FLAG_NZ(g_cpu.Y);
label_E4BF:;
    /* $E4BF: 60 */ maybe_trigger_vblank(6);
    return;
label_E4C0:; /* FirstSprXPos */
    /* $E4C0: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E4C2:;
    /* $E4C2: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E4C4:; /* FirstSprYPos */
    /* $E4C4: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE4C4); return;
label_E4C5:;
    /* $E4C5: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E4C7:;
    /* $E4C7: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E4C9:;
    /* $E4C9: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E4CA:;
    /* $E4CA: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE4CA); return;
label_E4CB:;
    /* $E4CB: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E4CC:; /* SecondSprYPos */
    /* $E4CC: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E4CD:;
    /* $E4CD: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE4CD); return;
label_E4CE:;
    /* $E4CE: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E4CF:;
    /* $E4CF: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE4CF); return;
label_E4D0:; /* FirstSprTilenum */
    /* $E4D0: 80 */ maybe_trigger_vblank(2); /* NOP */
label_E4D2:;
    /* $E4D2: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x83 + g_cpu.X) & 0xFF), g_cpu.A);
label_E4D4:; /* SecondSprTilenum */
    /* $E4D4: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x83 + g_cpu.X) & 0xFF), g_cpu.A);
label_E4D6:;
    /* $E4D6: 80 */ maybe_trigger_vblank(2); /* NOP */
label_E4D8:; /* HammerSprAttrib */
    /* $E4D8: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E4DA:;
    /* $E4DA: C3 */ maybe_trigger_vblank(8); /* ILLEGAL $C3 — skip 2 */
label_E4DC:; /* DrawHammer */
    /* $E4DC: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06F3 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E4DF:;
    /* $E4DF: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_E4E2:;
    /* $E4E2: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E4EC;
label_E4E4:;
    /* $E4E4: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x2A + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E4E6:;
    /* $E4E6: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x7F; FLAG_NZ(g_cpu.A);
label_E4E8:;
    /* $E4E8: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_E4EA:;
    /* $E4EA: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E4F0;
label_E4EC:; /* ForceHPose */
    /* $E4EC: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_E4EE:;
    /* $E4EE: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E4F7;
label_E4F0:; /* GetHPose */
    /* $E4F0: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_E4F2:;
    /* $E4F2: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E4F3:;
    /* $E4F3: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E4F4:;
    /* $E4F4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_E4F6:;
    /* $E4F6: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E4F7:; /* RenderH */
    /* $E4F7: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03BE); FLAG_NZ(g_cpu.A);
label_E4FA:;
    /* $E4FA: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E4FB:;
    /* $E4FB: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE4C4 + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E4FE:;
    /* $E4FE: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E501:;
    /* $E501: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E502:;
    /* $E502: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE4CC + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E505:;
    /* $E505: 99 */ maybe_trigger_vblank(5); nes_write((0x0204 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E508:;
    /* $E508: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B3); FLAG_NZ(g_cpu.A);
label_E50B:;
    /* $E50B: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E50C:;
    /* $E50C: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE4C0 + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E50F:;
    /* $E50F: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E512:;
    /* $E512: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E513:;
    /* $E513: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE4C8 + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E516:;
    /* $E516: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E519:;
    /* $E519: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE4D0 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E51C:;
    /* $E51C: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E51F:;
    /* $E51F: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE4D4 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E522:;
    /* $E522: 99 */ maybe_trigger_vblank(5); nes_write((0x0205 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E525:;
    /* $E525: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE4D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E528:;
    /* $E528: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E52B:;
    /* $E52B: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E52E:;
    /* $E52E: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E530:;
    /* $E530: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D6); FLAG_NZ(g_cpu.A);
label_E533:;
    /* $E533: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xFC; FLAG_NZ(g_cpu.A);
label_E535:;
    /* $E535: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E540;
label_E537:;
    /* $E537: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E539:;
    /* $E539: 95 */ maybe_trigger_vblank(4); nes_write((0x2A + g_cpu.X) & 0xFF, g_cpu.A);
label_E53B:;
    /* $E53B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E53D:;
    /* $E53D: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5C1);
label_E540:; /* NoHOffscr */
    /* $E540: 60 */ maybe_trigger_vblank(6);
    return;
label_E541:; /* FlagpoleScoreNumTiles */
    /* $E541: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xF750 + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E544:;
    /* $E544: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E540;
    }
label_E546:;
    /* $E546: FB */ maybe_trigger_vblank(7); /* ILLEGAL $FB — skip 3 */
label_E549:;
    /* $E549: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0xFB + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E54B:; /* FlagpoleGfxHandler */
    /* $E54B: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E54E:;
    /* $E54E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_E551:;
    /* $E551: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E554:;
    /* $E554: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E555:;
    /* $E555: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_E557:;
    /* $E557: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E55A:;
    /* $E55A: 99 */ maybe_trigger_vblank(5); nes_write((0x020B + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E55D:;
    /* $E55D: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E55E:;
    /* $E55E: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x0C + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0C); g_cpu.A=r&0xFF; }
label_E560:;
    /* $E560: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_E562:;
    /* $E562: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E564:;
    /* $E564: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5C1);
label_E567:;
    /* $E567: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_E569:;
    /* $E569: 99 */ maybe_trigger_vblank(5); nes_write((0x0208 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E56C:;
    /* $E56C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x010D); FLAG_NZ(g_cpu.A);
label_E56F:;
    /* $E56F: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_E571:;
    /* $E571: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E573:;
    /* $E573: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_E575:;
    /* $E575: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_E577:;
    /* $E577: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E57A:;
    /* $E57A: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E57D:;
    /* $E57D: 99 */ maybe_trigger_vblank(5); nes_write((0x020A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E580:;
    /* $E580: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x7E; FLAG_NZ(g_cpu.A);
label_E582:;
    /* $E582: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E585:;
    /* $E585: 99 */ maybe_trigger_vblank(5); nes_write((0x0209 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E588:;
    /* $E588: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x7F; FLAG_NZ(g_cpu.A);
label_E58A:;
    /* $E58A: 99 */ maybe_trigger_vblank(5); nes_write((0x0205 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E58D:;
    /* $E58D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x070F); FLAG_NZ(g_cpu.A);
label_E590:;
    /* $E590: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E5A7;
label_E592:;
    /* $E592: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_E593:;
    /* $E593: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E594:;
    /* $E594: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x0C + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0C); g_cpu.A=r&0xFF; }
label_E596:;
    /* $E596: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_E597:;
    /* $E597: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x010F); FLAG_NZ(g_cpu.A);
label_E59A:;
    /* $E59A: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E59B:;
    /* $E59B: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E59C:;
    /* $E59C: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE541 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E59F:;
    /* $E59F: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_E5A1:;
    /* $E5A1: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE542 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E5A4:;
    /* $E5A4: 20 */ maybe_trigger_vblank(6); call_by_address(0xEBB2);
label_E5A7:; /* ChkFlagOffscreen */
    /* $E5A7: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E5A9:;
    /* $E5A9: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E5AC:;
    /* $E5AC: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D1); FLAG_NZ(g_cpu.A);
label_E5AF:;
    /* $E5AF: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0E; FLAG_NZ(g_cpu.A);
label_E5B1:;
    /* $E5B1: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E5C7;
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
label_E5C8:; /* DrawLargePlatform */
    /* $E5C8: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E5CB:;
    /* $E5CB: 84 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.Y);
label_E5CD:;
    /* $E5CD: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E5CE:;
    /* $E5CE: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E5CF:;
    /* $E5CF: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E5D0:;
    /* $E5D0: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_E5D3:;
    /* $E5D3: 20 */ maybe_trigger_vblank(6); call_by_address(0xE4AE);
label_E5D6:;
    /* $E5D6: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E5D8:;
    /* $E5D8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E5DA:;
    /* $E5DA: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5BB);
label_E5DD:;
    /* $E5DD: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_E5E0:;
    /* $E5E0: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_E5E2:;
    /* $E5E2: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E5E9;
label_E5E4:;
    /* $E5E4: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06CC); FLAG_NZ(g_cpu.Y);
label_E5E7:;
    /* $E5E7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E5EB;
label_E5E9:; /* ShrinkPlatform */
    /* $E5E9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E5EB:; /* SetLast2Platform */
    /* $E5EB: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E5EE:;
    /* $E5EE: 99 */ maybe_trigger_vblank(5); nes_write((0x0210 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E5F1:;
    /* $E5F1: 99 */ maybe_trigger_vblank(5); nes_write((0x0214 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E5F4:;
    /* $E5F4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x5B; FLAG_NZ(g_cpu.A);
label_E5F6:;
    /* $E5F6: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x0743); FLAG_NZ(g_cpu.X);
label_E5F9:;
    /* $E5F9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E5FD;
label_E5FB:;
    /* $E5FB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x75; FLAG_NZ(g_cpu.A);
label_E5FD:; /* SetPlatformTilenum */
    /* $E5FD: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E5FF:;
    /* $E5FF: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E600:;
    /* $E600: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5B5);
label_E603:;
    /* $E603: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E605:;
    /* $E605: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E606:;
    /* $E606: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5B5);
label_E609:;
    /* $E609: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_E60A:;
    /* $E60A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1F6);
label_E60D:;
    /* $E60D: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_E60E:;
    /* $E60E: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E611:;
    /* $E611: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E612:;
    /* $E612: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E613:;
    /* $E613: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E61A;
label_E615:;
    /* $E615: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E617:;
    /* $E617: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E61A:; /* SChk2 */
    /* $E61A: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E61B:;
    /* $E61B: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E61C:;
    /* $E61C: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E61D:;
    /* $E61D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E624;
label_E61F:;
    /* $E61F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E621:;
    /* $E621: 99 */ maybe_trigger_vblank(5); nes_write((0x0204 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E624:; /* SChk3 */
    /* $E624: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E625:;
    /* $E625: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E626:;
    /* $E626: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E627:;
    /* $E627: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E62E;
label_E629:;
    /* $E629: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E62B:;
    /* $E62B: 99 */ maybe_trigger_vblank(5); nes_write((0x0208 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E62E:; /* SChk4 */
    /* $E62E: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E62F:;
    /* $E62F: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E630:;
    /* $E630: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E631:;
    /* $E631: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E638;
label_E633:;
    /* $E633: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E635:;
    /* $E635: 99 */ maybe_trigger_vblank(5); nes_write((0x020C + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E638:; /* SChk5 */
    /* $E638: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E639:;
    /* $E639: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E63A:;
    /* $E63A: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E63B:;
    /* $E63B: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E642;
label_E63D:;
    /* $E63D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E63F:;
    /* $E63F: 99 */ maybe_trigger_vblank(5); nes_write((0x0210 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E642:; /* SChk6 */
    /* $E642: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E643:;
    /* $E643: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E644:;
    /* $E644: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E64B;
label_E646:;
    /* $E646: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E648:;
    /* $E648: 99 */ maybe_trigger_vblank(5); nes_write((0x0214 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E64B:; /* SLChk */
    /* $E64B: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D1); FLAG_NZ(g_cpu.A);
label_E64E:;
    /* $E64E: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E64F:;
    /* $E64F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E654;
label_E651:;
    /* $E651: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5B3);
label_E654:; /* ExDLPl */
    /* $E654: 60 */ maybe_trigger_vblank(6);
    return;
label_E655:; /* DrawFloateyNumber_Coin */
    /* $E655: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_E657:;
    /* $E657: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E658:;
    /* $E658: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E65C;
label_E65A:;
    /* $E65A: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0xDB + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E65C:; /* NotRsNum */
    /* $E65C: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xDB + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E65E:;
    /* $E65E: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5C1);
label_E661:;
    /* $E661: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B3); FLAG_NZ(g_cpu.A);
label_E664:;
    /* $E664: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E667:;
    /* $E667: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E668:;
    /* $E668: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_E66A:;
    /* $E66A: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E66D:;
    /* $E66D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E66F:;
    /* $E66F: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E672:;
    /* $E672: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E675:;
    /* $E675: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF7; FLAG_NZ(g_cpu.A);
label_E677:;
    /* $E677: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E67A:;
    /* $E67A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFB; FLAG_NZ(g_cpu.A);
label_E67C:;
    /* $E67C: 99 */ maybe_trigger_vblank(5); nes_write((0x0205 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E67F:;
    /* $E67F: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE6BD); return;
label_E682:; /* JumpingCoinTiles */
    /* $E682: 60 */ maybe_trigger_vblank(6);
    return;
label_E683:;
    /* $E683: 61 */ maybe_trigger_vblank(6); { uint8_t m=nes_read(nes_read16zp((0x62 + g_cpu.X) & 0xFF)); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E685:;
    /* $E685: 63 */ maybe_trigger_vblank(8); /* ILLEGAL $63 — skip 2 */
label_E687:;
    /* $E687: F3 */ maybe_trigger_vblank(8); /* ILLEGAL $F3 — skip 2 */
label_E689:;
    /* $E689: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x2A + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E68B:;
    /* $E68B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_E68D:;
    /* $E68D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E655;
    }
label_E68F:;
    /* $E68F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xDB + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E691:;
    /* $E691: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E694:;
    /* $E694: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E695:;
    /* $E695: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_E697:;
    /* $E697: 99 */ maybe_trigger_vblank(5); nes_write((0x0204 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E69A:;
    /* $E69A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B3); FLAG_NZ(g_cpu.A);
label_E69D:;
    /* $E69D: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E6A0:;
    /* $E6A0: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E6A3:;
    /* $E6A3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_E6A5:;
    /* $E6A5: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E6A6:;
    /* $E6A6: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_E6A8:;
    /* $E6A8: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E6A9:;
    /* $E6A9: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE682 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E6AC:;
    /* $E6AC: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E6AD:;
    /* $E6AD: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5C1);
label_E6B0:;
    /* $E6B0: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E6B1:;
    /* $E6B1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E6B3:;
    /* $E6B3: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E6B6:;
    /* $E6B6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x82; FLAG_NZ(g_cpu.A);
label_E6B8:;
    /* $E6B8: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E6BB:;
    /* $E6BB: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E6BD:; /* ExJCGfx */
    /* $E6BD: 60 */ maybe_trigger_vblank(6);
    return;
label_E6BE:; /* PowerUpGfxTable */
    /* $E6BE: 76 */ maybe_trigger_vblank(6); { uint16_t a=(0x77 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E6C0:;
    /* $E6C0: 78 */ maybe_trigger_vblank(2); g_cpu.I = 1;
label_E6C1:;
    /* $E6C1: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xD6D6 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E6C4:;
    /* $E6C4: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x8DD9 + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E6C7:;
    /* $E6C7: 8D */ maybe_trigger_vblank(4); nes_write(0xE4E4, g_cpu.A);
label_E6CA:;
    /* $E6CA: 76 */ maybe_trigger_vblank(6); { uint16_t a=(0x77 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E6CC:;
    /* $E6CC: 78 */ maybe_trigger_vblank(2); g_cpu.I = 1;
label_E6CD:;
    /* $E6CD: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x0102 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E6D0:;
    /* $E6D0: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E6D1:;
    /* $E6D1: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0xAC + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_E6D3:;
    /* $E6D3: EA */ maybe_trigger_vblank(2); /* NOP */
label_E6D4:;
    /* $E6D4: 06 */ maybe_trigger_vblank(5); { uint16_t a=0xAD; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E6D6:;
    /* $E6D6: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1803 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E6D9:;
    /* $E6D9: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_E6DB:;
    /* $E6DB: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_E6DD:;
    /* $E6DD: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_E6E0:;
    /* $E6E0: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_E6E2:;
    /* $E6E2: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x39); FLAG_NZ(g_cpu.X);
label_E6E4:;
    /* $E6E4: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE6CE + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E6E7:;
    /* $E6E7: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x03CA); FLAG_NZ(g_cpu.A);
label_E6EA:;
    /* $E6EA: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_E6EC:;
    /* $E6EC: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E6ED:;
    /* $E6ED: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E6EE:;
    /* $E6EE: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E6EF:;
    /* $E6EF: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E6F0:;
    /* $E6F0: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E6F1:;
    /* $E6F1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E6F3:;
    /* $E6F3: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_E6F5:;
    /* $E6F5: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_E6F7:; /* PUpDrawLoop */
    /* $E6F7: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE6BE + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E6FA:;
    /* $E6FA: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_E6FC:;
    /* $E6FC: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE6BF + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E6FF:;
    /* $E6FF: 20 */ maybe_trigger_vblank(6); call_by_address(0xEBB2);
label_E702:;
    /* $E702: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x07; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E704:;
    /* $E704: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E6F7;
    }
label_E706:;
    /* $E706: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06EA); FLAG_NZ(g_cpu.Y);
label_E709:;
    /* $E709: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E70A:;
    /* $E70A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E73B;
label_E70C:;
    /* $E70C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_E70E:;
    /* $E70E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E73B;
label_E710:;
    /* $E710: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_E712:;
    /* $E712: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_E714:;
    /* $E714: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E715:;
    /* $E715: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_E717:;
    /* $E717: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x03CA); FLAG_NZ(g_cpu.A);
label_E71A:;
    /* $E71A: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E71D:;
    /* $E71D: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E720:;
    /* $E720: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x00); FLAG_NZ(g_cpu.X);
label_E722:;
    /* $E722: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_E723:;
    /* $E723: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E72B;
label_E725:;
    /* $E725: 99 */ maybe_trigger_vblank(5); nes_write((0x020A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E728:;
    /* $E728: 99 */ maybe_trigger_vblank(5); nes_write((0x020E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E72B:; /* FlipPUpRightSide */
    /* $E72B: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0206 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E72E:;
    /* $E72E: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_E730:;
    /* $E730: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E733:;
    /* $E733: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x020E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E736:;
    /* $E736: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_E738:;
    /* $E738: 99 */ maybe_trigger_vblank(5); nes_write((0x020E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E73B:; /* PUpOfs */
    /* $E73B: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xEB64); return;
label_E73E:; /* EnemyGraphicsTable */
    /* $E73E: FC */ maybe_trigger_vblank(4); (void)nes_read((0xAAFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E741:;
    /* $E741: AB */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X = 0xAC; FLAG_NZ(g_cpu.A);
label_E743:;
    /* $E743: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0xFCFC); FLAG_NZ(g_cpu.A);
label_E746:;
    /* $E746: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0xB0AF); FLAG_NZ(g_cpu.X);
label_E749:;
    /* $E749: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xFC) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E74B:;
    /* $E74B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xA6); FLAG_NZ(g_cpu.A);
label_E74D:;
    /* $E74D: A7 */ maybe_trigger_vblank(3); g_cpu.A = g_cpu.X = nes_read(0xA8); FLAG_NZ(g_cpu.A);
label_E74F:;
    /* $E74F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFC; FLAG_NZ(g_cpu.A);
label_E751:;
    /* $E751: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xA1; FLAG_NZ(g_cpu.Y);
label_E753:;
    /* $E753: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xA3; FLAG_NZ(g_cpu.X);
label_E755:;
    /* $E755: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x69); FLAG_NZ(g_cpu.Y);
label_E757:;
    /* $E757: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x6A); FLAG_NZ(g_cpu.A);
label_E759:;
    /* $E759: A7 */ maybe_trigger_vblank(3); g_cpu.A = g_cpu.X = nes_read(0xA8); FLAG_NZ(g_cpu.A);
label_E75B:;
    /* $E75B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x6B; FLAG_NZ(g_cpu.A);
label_E75D:;
    /* $E75D: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x6C; FLAG_NZ(g_cpu.Y);
label_E75F:;
    /* $E75F: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xA3; FLAG_NZ(g_cpu.X);
label_E761:;
    /* $E761: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFC); FLAG_NZ(g_cpu.Y);
label_E763:;
    /* $E763: FC */ maybe_trigger_vblank(4); (void)nes_read((0x9796 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E766:;
    /* $E766: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_E767:;
    /* $E767: 99 */ maybe_trigger_vblank(5); nes_write((0xFCFC + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E76A:;
    /* $E76A: 9A */ maybe_trigger_vblank(2); g_cpu.S = g_cpu.X;
label_E76B:;
    /* $E76B: 9B */ maybe_trigger_vblank(5); /* ILLEGAL $9B — skip 3 */
label_E76E:;
    /* $E76E: FC */ maybe_trigger_vblank(4); (void)nes_read((0x8FFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E771:;
    /* $E771: 8E */ maybe_trigger_vblank(4); nes_write(0x8F8E, g_cpu.X);
label_E774:;
    /* $E774: FC */ maybe_trigger_vblank(4); (void)nes_read((0x95FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E777:;
    /* $E777: 94 */ maybe_trigger_vblank(4); nes_write((0x94 + g_cpu.X) & 0xFF, g_cpu.Y);
label_E779:;
    /* $E779: 95 */ maybe_trigger_vblank(4); nes_write((0xFC + g_cpu.X) & 0xFF, g_cpu.A);
label_E77B:;
    /* $E77B: FC */ maybe_trigger_vblank(4); (void)nes_read((0xDCDC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E77E:;
    /* $E77E: DF */ maybe_trigger_vblank(7); /* ILLEGAL $DF — skip 3 */
label_E781:;
    /* $E781: DC */ maybe_trigger_vblank(4); (void)nes_read((0xDDDD + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E784:;
    /* $E784: DE */ maybe_trigger_vblank(7); { uint16_t a=(0xFCDE + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E787:;
    /* $E787: FC */ maybe_trigger_vblank(4); (void)nes_read((0xB3B2 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E78A:;
    /* $E78A: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0xB5 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_E78C:;
    /* $E78C: FC */ maybe_trigger_vblank(4); (void)nes_read((0xB6FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E78F:;
    /* $E78F: B3 */ maybe_trigger_vblank(5); g_cpu.A = g_cpu.X = nes_read((nes_read16zp(0xB7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E791:;
    /* $E791: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFC + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E793:;
    /* $E793: FC */ maybe_trigger_vblank(4); (void)nes_read((0x7170 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E796:;
    /* $E796: 72 */ maybe_trigger_vblank(2); /* ILLEGAL $72 — skip 1 */
label_E797:;
    /* $E797: 73 */ maybe_trigger_vblank(8); /* ILLEGAL $73 — skip 2 */
label_E799:;
    /* $E799: FC */ maybe_trigger_vblank(4); (void)nes_read((0x6E6E + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E79C:;
    /* $E79C: 6F */ maybe_trigger_vblank(6); /* ILLEGAL $6F — skip 3 */
label_E79F:;
    /* $E79F: FC */ maybe_trigger_vblank(4); (void)nes_read((0x6D6D + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7A2:;
    /* $E7A2: 6F */ maybe_trigger_vblank(6); /* ILLEGAL $6F — skip 3 */
label_E7A5:;
    /* $E7A5: FC */ maybe_trigger_vblank(4); (void)nes_read((0x6F6F + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7A8:;
    /* $E7A8: 6E */ maybe_trigger_vblank(6); { uint16_t a=0xFC6E; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E7AB:;
    /* $E7AB: FC */ maybe_trigger_vblank(4); (void)nes_read((0x6F6F + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7AE:;
    /* $E7AE: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xFC6D); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7B1:;
    /* $E7B1: FC */ maybe_trigger_vblank(4); (void)nes_read((0xF4F4 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7B4:;
    /* $E7B4: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xF5 + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7B6:;
    /* $E7B6: FC */ maybe_trigger_vblank(4); (void)nes_read((0xF4FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7B9:;
    /* $E7B9: F4 */ maybe_trigger_vblank(4); (void)nes_read((0xF5 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7BB:;
    /* $E7BB: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xFC + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7BD:;
    /* $E7BD: FC */ maybe_trigger_vblank(4); (void)nes_read((0xF5F5 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7C0:;
    /* $E7C0: F4 */ maybe_trigger_vblank(4); (void)nes_read((0xF4 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7C2:;
    /* $E7C2: FC */ maybe_trigger_vblank(4); (void)nes_read((0xF5FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7C5:;
    /* $E7C5: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xF4 + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7C7:;
    /* $E7C7: F4 */ maybe_trigger_vblank(4); (void)nes_read((0xFC + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7C9:;
    /* $E7C9: FC */ maybe_trigger_vblank(4); (void)nes_read((0xFCFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7CC:;
    /* $E7CC: EF */ maybe_trigger_vblank(6); /* ILLEGAL $EF — skip 3 */
label_E7CF:;
    /* $E7CF: B8 */ maybe_trigger_vblank(2); g_cpu.V = 0;
label_E7D0:;
    /* $E7D0: BB */ maybe_trigger_vblank(4); /* ILLEGAL $BB — skip 3 */
label_E7D3:;
    /* $E7D3: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0xFCFC + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E7D6:;
    /* $E7D6: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xBCBD + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E7D9:;
    /* $E7D9: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x7B7A + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E7DC:;
    /* $E7DC: DA */ maybe_trigger_vblank(2); /* NOP */
label_E7DD:;
    /* $E7DD: DB */ maybe_trigger_vblank(7); /* ILLEGAL $DB — skip 3 */
label_E7E0:;
    /* $E7E0: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xCECD); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E7E3:;
    /* $E7E3: CE */ maybe_trigger_vblank(6); { uint16_t a=0xCFCF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E7E6:;
    /* $E7E6: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xD17C + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7E9:;
    /* $E7E9: 8C */ maybe_trigger_vblank(4); nes_write(0xD2D3, g_cpu.Y);
label_E7EC:;
    /* $E7EC: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x897C + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7EF:;
    /* $E7EF: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E7F0:;
    /* $E7F0: 8B */ maybe_trigger_vblank(2); /* ILLEGAL $8B — skip 2 */
label_E7F2:;
    /* $E7F2: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xD4 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E7F4:;
    /* $E7F4: E3 */ maybe_trigger_vblank(8); /* ILLEGAL $E3 — skip 2 */
label_E7F6:;
    /* $E7F6: D3 */ maybe_trigger_vblank(8); /* ILLEGAL $D3 — skip 2 */
label_E7F8:;
    /* $E7F8: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xD4 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E7FA:;
    /* $E7FA: E3 */ maybe_trigger_vblank(8); /* ILLEGAL $E3 — skip 2 */
label_E7FC:;
    /* $E7FC: 8B */ maybe_trigger_vblank(2); /* ILLEGAL $8B — skip 2 */
label_E7FE:;
    /* $E7FE: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xE5); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E800:;
    /* $E800: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xE6; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E802:;
    /* $E802: EB */ maybe_trigger_vblank(2); { uint8_t m=0xEB; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E804:;
    /* $E804: EC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xEDEC); int r=g_cpu.X-m; g_cpu.C=(g_cpu.X>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E807:;
    /* $E807: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xEEEE); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E80A:;
    /* $E80A: FC */ maybe_trigger_vblank(4); (void)nes_read((0xD0FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E80D:;
    /* $E80D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E7E6;
    }
label_E80F:;
    /* $E80F: D7 */ maybe_trigger_vblank(6); /* ILLEGAL $D7 — skip 2 */
label_E811:;
    /* $E811: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xC0C1 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_E814:;
    /* $E814: C2 */ maybe_trigger_vblank(2); /* NOP */
label_E816:;
    /* $E816: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xC3); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E818:;
    /* $E818: C6 */ maybe_trigger_vblank(5); { uint16_t a=0xC5; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E81A:;
    /* $E81A: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E81B:;
    /* $E81B: C7 */ maybe_trigger_vblank(5); /* ILLEGAL $C7 — skip 2 */
label_E81D:;
    /* $E81D: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xC9CA + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_E820:;
    /* $E820: C2 */ maybe_trigger_vblank(2); /* NOP */
label_E822:;
    /* $E822: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xC3); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E824:;
    /* $E824: C6 */ maybe_trigger_vblank(5); { uint16_t a=0xC5; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E826:;
    /* $E826: CC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xFCCB); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E829:;
    /* $E829: FC */ maybe_trigger_vblank(4); (void)nes_read((0xE7E8 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E82C:;
    /* $E82C: EA */ maybe_trigger_vblank(2); /* NOP */
label_E82D:;
    /* $E82D: E9 */ maybe_trigger_vblank(2); { uint8_t m=0xF2; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E82F:;
    /* $E82F: F2 */ maybe_trigger_vblank(2); /* ILLEGAL $F2 — skip 1 */
label_E830:;
    /* $E830: F3 */ maybe_trigger_vblank(8); /* ILLEGAL $F3 — skip 2 */
label_E832:;
    /* $E832: F2 */ maybe_trigger_vblank(2); /* ILLEGAL $F2 — skip 1 */
label_E833:;
    /* $E833: F2 */ maybe_trigger_vblank(2); /* ILLEGAL $F2 — skip 1 */
label_E834:;
    /* $E834: F1 */ maybe_trigger_vblank(5); { uint8_t m=nes_read((nes_read16zp(0xF1) + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E836:;
    /* $E836: F1 */ maybe_trigger_vblank(5); { uint8_t m=nes_read((nes_read16zp(0xF1) + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E838:;
    /* $E838: FC */ maybe_trigger_vblank(4); (void)nes_read((0xF0FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E83B:;
    /* $E83B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { call_by_address(0xE839); return; }
label_E83D:;
    /* $E83D: FC */ maybe_trigger_vblank(4); (void)nes_read((0xFCFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E840:; /* EnemyGfxTableOffsets */
    /* $E840: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x000C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E843:;
    /* $E843: 0C */ maybe_trigger_vblank(4); (void)nes_read(0xA80C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E846:;
    /* $E846: 54 */ maybe_trigger_vblank(4); (void)nes_read((0x3C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E848:;
    /* $E848: EA */ maybe_trigger_vblank(2); /* NOP */
label_E849:;
    /* $E849: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E84A:;
    /* $E84A: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E84B:;
    /* $E84B: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E84C:;
    /* $E84C: CC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x18C0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E84F:;
    /* $E84F: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E850:;
    /* $E850: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E851:;
    /* $E851: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E877;
label_E853:;
    /* $E853: FF */ maybe_trigger_vblank(7); /* ILLEGAL $FF — skip 3 */
label_E856:;
    /* $E856: D2 */ maybe_trigger_vblank(2); /* ILLEGAL $D2 — skip 1 */
label_E857:;
    /* $E857: D8 */ maybe_trigger_vblank(2); g_cpu.D = 0;
label_E858:;
    /* $E858: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E850;
    }
label_E85A:;
    /* $E85A: FC */ maybe_trigger_vblank(4); (void)nes_read((0x0201 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E85D:;
    /* $E85D: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E85F:;
    /* $E85F: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x01 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_E861:;
    /* $E861: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E863:;
    /* $E863: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E865:;
    /* $E865: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x02 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_E867:;
    /* $E867: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E868:;
    /* $E868: 21 */ maybe_trigger_vblank(6); g_cpu.A &= nes_read(nes_read16zp((0x01 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_E86A:;
    /* $E86A: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E86B:;
    /* $E86B: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x01 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_E86D:;
    /* $E86D: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E86E:;
    /* $E86E: FF */ maybe_trigger_vblank(7); /* ILLEGAL $FF — skip 3 */
label_E871:;
    /* $E871: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x01 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_E873:;
    /* $E873: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E874:;
    /* $E874: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E875:;
    /* $E875: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E876:; /* EnemyAnimTimingBMask */
    /* $E876: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E877:;
    /* $E877: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E878:; /* JumpspringFrameOffsets */
    /* $E878: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E879:;
    /* $E879: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x191A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E87C:;
    /* $E87C: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
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
    /* $E8C0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xE8D5); return; }
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
}

void EnemyEngine::check_for_p_up_collision_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_E8E3;
        case 2: goto label_E8E5;
        case 3: goto label_E8FD;
        case 4: goto label_E8F2;
        case 5: goto label_E8E9;
        case 6: goto label_E8FB;
        case 7: goto label_E8D9;
    }
label_D881:; /* CheckForPUpCollision */
    /* $D881: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_D883:;
    /* $D883: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x2E; g_cpu.C=(g_cpu.Y>=0x2E)?1:0; FLAG_NZ(r&0xFF); }
label_D885:;
    /* $D885: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D88A;
label_D887:;
    /* $D887: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD800); return;
label_D88A:; /* EColl */
    /* $D88A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x079F); FLAG_NZ(g_cpu.A);
label_D88D:;
    /* $D88D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D895;
label_D88F:;
    /* $D88F: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD795); return;
label_D892:; /* KickedShellPtsData */
    /* $D892: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D893:;
    /* $D893: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D895:; /* HandlePECollisions */
    /* $D895: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D898:;
    /* $D898: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_D89A:;
    /* $D89A: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x03D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D89D:;
    /* $D89D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D8F8;
label_D89F:;
    /* $D89F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_D8A1:;
    /* $D8A1: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x0491 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D8A4:;
    /* $D8A4: 9D */ maybe_trigger_vblank(5); nes_write((0x0491 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_D8A7:;
    /* $D8A7: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x12; g_cpu.C=(g_cpu.Y>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_D8A9:;
    /* $D8A9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D8F9;
label_D8AB:;
    /* $D8AB: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0D; g_cpu.C=(g_cpu.Y>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_D8AD:;
    /* $D8AD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D92C;
label_D8AF:;
    /* $D8AF: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0C; g_cpu.C=(g_cpu.Y>=0x0C)?1:0; FLAG_NZ(r&0xFF); }
label_D8B1:;
    /* $D8B1: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D92C;
label_D8B3:;
    /* $D8B3: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x33; g_cpu.C=(g_cpu.Y>=0x33)?1:0; FLAG_NZ(r&0xFF); }
label_D8B5:;
    /* $D8B5: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D8F9;
label_D8B7:;
    /* $D8B7: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x15; g_cpu.C=(g_cpu.Y>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_D8B9:;
    /* $D8B9: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D92C;
label_D8BB:;
    /* $D8BB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x074E); FLAG_NZ(g_cpu.A);
label_D8BE:;
    /* $D8BE: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D92C;
label_D8C0:;
    /* $D8C0: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D8C2:;
    /* $D8C2: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_D8C3:;
    /* $D8C3: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D8F9;
label_D8C5:;
    /* $D8C5: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D8C7:;
    /* $D8C7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_D8C9:;
    /* $D8C9: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_D8CB:;
    /* $D8CB: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D8F9;
label_D8CD:;
    /* $D8CD: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D8CF:;
    /* $D8CF: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_D8D1:;
    /* $D8D1: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_D8F8;
label_D8D3:;
    /* $D8D3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_D8D5:;
    /* $D8D5: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_D8D7:;
    /* $D8D7: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D8D9:;
    /* $D8D9: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x80; FLAG_NZ(g_cpu.A);
label_D8DB:;
    /* $D8DB: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_D8DD:;
    /* $D8DD: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA05);
label_D8E0:;
    /* $D8E0: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD84F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D8E3:;
    /* $D8E3: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_D8E5:;
    /* $D8E5: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_D8E7:;
    /* $D8E7: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D8E8:;
    /* $D8E8: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0484); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_D8EB:;
    /* $D8EB: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x0796 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_D8EE:;
    /* $D8EE: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_D8F0:;
    /* $D8F0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_D8F5;
label_D8F2:;
    /* $D8F2: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD892 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_D8F5:; /* KSPts */
    /* $D8F5: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_D8F8:; /* ExPEC */
    /* $D8F8: 60 */ maybe_trigger_vblank(6);
    return;
label_D8F9:; /* ChkForPlayerInjury */
    /* $D8F9: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x9F); FLAG_NZ(g_cpu.A);
label_D8FB:;
    /* $D8FB: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_D8FF;
label_D8FD:;
    /* $D8FD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xD969); return; }
label_D8FF:; /* ChkInj */
    /* $D8FF: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D901:;
    /* $D901: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_D903:;
    /* $D903: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D90E;
label_D905:;
    /* $D905: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_D907:;
    /* $D907: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_D908:;
    /* $D908: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x0C + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0C); g_cpu.A=r&0xFF; }
label_D90A:;
    /* $D90A: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xCF + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D90C:;
    /* $D90C: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { call_by_address(0xD969); return; }
label_D90E:; /* ChkETmrs */
    /* $D90E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0791); FLAG_NZ(g_cpu.A);
label_D911:;
    /* $D911: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xD969); return; }
label_D913:;
    /* $D913: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x079E); FLAG_NZ(g_cpu.A);
label_D916:;
    /* $D916: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D955;
label_D918:;
    /* $D918: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AD); FLAG_NZ(g_cpu.A);
label_D91B:;
    /* $D91B: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x03AE); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_D91E:;
    /* $D91E: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_D923;
label_D920:;
    /* $D920: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD9F6); return;
label_D923:; /* TInjE */
    /* $D923: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D925:;
    /* $D925: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_D927:;
    /* $D927: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D92C;
label_D929:;
    /* $D929: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD9FF); return;
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
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_D946;
    }
label_D965:; /* StompedEnemyPtsData */
    /* $D965: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_D966:;
    /* $D966: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x05; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D968:;
    /* $D968: 06 */ maybe_trigger_vblank(5); { uint16_t a=0xB5; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D96A:;
    /* $D96A: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0xC9 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_D96C:;
    /* $D96C: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_D96D:;
    /* $D96D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
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
    /* $D9CF: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xD9F1); return;
label_D9D2:; /* RevivalRateData */
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
label_D9F6:; /* ChkEnemyFaceRight */
    /* $D9F6: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D9F8:;
    /* $D9F8: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_D9FA:;
    /* $D9FA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_D9FF;
label_D9FC:;
    /* $D9FC: 4C */ maybe_trigger_vblank(3); goto label_D92C;
label_D9FF:; /* LInj */
    /* $D9FF: 20 */ maybe_trigger_vblank(6); call_by_address(0xDB1C);
label_DA02:;
    /* $DA02: 4C */ maybe_trigger_vblank(3); goto label_D92C;
label_DA05:; /* EnemyFacePlayer */
    /* $DA05: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_DA07:;
    /* $DA07: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_DA0A:;
    /* $DA0A: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_DA0D;
label_DA0C:;
    /* $DA0C: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DA0D:; /* SFcRt */
    /* $DA0D: 94 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.Y);
label_DA0F:;
    /* $DA0F: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DA10:;
    /* $DA10: 60 */ maybe_trigger_vblank(6);
    return;
label_DA11:; /* SetupFloateyNumber */
    /* $DA11: 9D */ maybe_trigger_vblank(5); nes_write((0x0110 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DA14:;
    /* $DA14: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x30; FLAG_NZ(g_cpu.A);
label_DA16:;
    /* $DA16: 9D */ maybe_trigger_vblank(5); nes_write((0x012C + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DA19:;
    /* $DA19: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DA1B:;
    /* $DA1B: 9D */ maybe_trigger_vblank(5); nes_write((0x011E + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DA1E:;
    /* $DA1E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_DA21:;
    /* $DA21: 9D */ maybe_trigger_vblank(5); nes_write((0x0117 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DA24:; /* ExSFN */
    /* $DA24: 60 */ maybe_trigger_vblank(6);
    return;
label_DA25:; /* SetBitsMask */
    /* $DA25: 80 */ maybe_trigger_vblank(2); /* NOP */
label_DA27:;
    /* $DA27: 20 */ maybe_trigger_vblank(6); call_by_address(0x0810);
label_DA2A:;
    /* $DA2A: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x02); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_DA2C:; /* ClearBitsMask */
    /* $DA2C: 7F */ maybe_trigger_vblank(7); /* ILLEGAL $7F — skip 3 */
label_DA2F:;
    /* $DA2F: EF */ maybe_trigger_vblank(6); /* ILLEGAL $EF — skip 3 */
label_DA32:;
    /* $DA32: FD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x09A5 + g_cpu.X) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DA35:;
    /* $DA35: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_DA36:;
    /* $DA36: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DA24;
    }
label_DA38:;
    /* $DA38: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x074E); FLAG_NZ(g_cpu.A);
label_DA3B:;
    /* $DA3B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DA24;
    }
label_DA3D:;
    /* $DA3D: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DA3F:;
    /* $DA3F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_DA41:;
    /* $DA41: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DAB1;
label_DA43:;
    /* $DA43: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_DA45:;
    /* $DA45: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DAB1;
label_DA47:;
    /* $DA47: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_DA49:;
    /* $DA49: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DAB1;
label_DA4B:;
    /* $DA4B: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA4E:;
    /* $DA4E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DAB1;
label_DA50:;
    /* $DA50: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC52);
label_DA53:;
    /* $DA53: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_DA54:;
    /* $DA54: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_DAB1;
label_DA56:; /* ECLoop */
    /* $DA56: 86 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.X);
label_DA58:;
    /* $DA58: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_DA59:;
    /* $DA59: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_DA5A:;
    /* $DA5A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DA5C:;
    /* $DA5C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DAAA;
label_DA5E:;
    /* $DA5E: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DA60:;
    /* $DA60: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_DA62:;
    /* $DA62: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DAAA;
label_DA64:;
    /* $DA64: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_DA66:;
    /* $DA66: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DAAA;
label_DA68:;
    /* $DA68: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_DA6A:;
    /* $DA6A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DAAA;
label_DA6C:;
    /* $DA6C: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA6F:;
    /* $DA6F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DAAA;
label_DA71:;
    /* $DA71: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_DA72:;
    /* $DA72: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DA73:;
    /* $DA73: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DA74:;
    /* $DA74: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DA75:;
    /* $DA75: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_DA77:;
    /* $DA77: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_DA78:;
    /* $DA78: 20 */ maybe_trigger_vblank(6); call_by_address(0xE327);
label_DA7B:;
    /* $DA7B: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DA7D:;
    /* $DA7D: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x01); FLAG_NZ(g_cpu.Y);
label_DA7F:;
    /* $DA7F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DAA1;
label_DA81:;
    /* $DA81: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DA83:;
    /* $DA83: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x001E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA86:;
    /* $DA86: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x80; FLAG_NZ(g_cpu.A);
label_DA88:;
    /* $DA88: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DA9B;
label_DA8A:;
    /* $DA8A: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA8D:;
    /* $DA8D: 3D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xDA25 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA90:;
    /* $DA90: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DAAA;
label_DA92:;
    /* $DA92: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA95:;
    /* $DA95: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0xDA25 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DA98:;
    /* $DA98: 99 */ maybe_trigger_vblank(5); nes_write((0x0491 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_DA9B:; /* YesEC */
    /* $DA9B: 20 */ maybe_trigger_vblank(6); call_by_address(0xDAB4);
label_DA9E:;
    /* $DA9E: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xDAAA); return;
label_DAA1:; /* NoEnemyCollision */
    /* $DAA1: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DAA4:;
    /* $DAA4: 3D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xDA2C + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DAA7:;
    /* $DAA7: 99 */ maybe_trigger_vblank(5); nes_write((0x0491 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_DAAA:; /* ReadyNextEnemy */
    /* $DAAA: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_DAAB:;
    /* $DAAB: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_DAAC:;
    /* $DAAC: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x01); FLAG_NZ(g_cpu.X);
label_DAAE:;
    /* $DAAE: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_DAAF:;
    /* $DAAF: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DA56;
    }
label_DAB1:; /* ExitECRoutine */
    /* $DAB1: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DAB3:;
    /* $DAB3: 60 */ maybe_trigger_vblank(6);
    return;
label_DAB4:; /* ProcEnemyCollisions */
    /* $DAB4: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x001E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DAB7:;
    /* $DAB7: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DAB9:;
    /* $DAB9: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_DABB:;
    /* $DABB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DAF0;
label_DABD:;
    /* $DABD: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DABF:;
    /* $DABF: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_DAC1:;
    /* $DAC1: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DAF1;
label_DAC3:;
    /* $DAC3: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DAC5:;
    /* $DAC5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_DAC7:;
    /* $DAC7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DAF0;
label_DAC9:;
    /* $DAC9: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x001E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DACC:;
    /* $DACC: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DACD:;
    /* $DACD: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DAD9;
label_DACF:;
    /* $DACF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_DAD1:;
    /* $DAD1: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_DAD4:;
    /* $DAD4: 20 */ maybe_trigger_vblank(6); call_by_address(0xD795);
label_DAD7:;
    /* $DAD7: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x01); FLAG_NZ(g_cpu.Y);
label_DAD9:; /* ShellCollisions */
    /* $DAD9: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_DADA:;
    /* $DADA: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_DADB:;
    /* $DADB: 20 */ maybe_trigger_vblank(6); call_by_address(0xD795);
label_DADE:;
    /* $DADE: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DAE0:;
    /* $DAE0: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0125 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DAE3:;
    /* $DAE3: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DAE4:;
    /* $DAE4: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_DAE6:;
    /* $DAE6: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x01); FLAG_NZ(g_cpu.X);
label_DAE8:;
    /* $DAE8: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_DAEB:;
    /* $DAEB: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DAED:;
    /* $DAED: FE */ maybe_trigger_vblank(7); { uint16_t a=(0x0125 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DAF0:; /* ExitProcessEColl */
    /* $DAF0: 60 */ maybe_trigger_vblank(6);
    return;
label_DAF1:; /* ProcSecondEnemyColl */
    /* $DAF1: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x001E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DAF4:;
    /* $DAF4: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_DAF6:;
    /* $DAF6: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DB15;
label_DAF8:;
    /* $DAF8: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0016 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DAFB:;
    /* $DAFB: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_DAFD:;
    /* $DAFD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DAF0;
    }
label_DAFF:;
    /* $DAFF: 20 */ maybe_trigger_vblank(6); call_by_address(0xD795);
label_DB02:;
    /* $DB02: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x01); FLAG_NZ(g_cpu.Y);
label_DB04:;
    /* $DB04: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0125 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DB07:;
    /* $DB07: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DB08:;
    /* $DB08: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_DB0A:;
    /* $DB0A: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DB0C:;
    /* $DB0C: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_DB0F:;
    /* $DB0F: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x01); FLAG_NZ(g_cpu.X);
label_DB11:;
    /* $DB11: FE */ maybe_trigger_vblank(7); { uint16_t a=(0x0125 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DB14:;
    /* $DB14: 60 */ maybe_trigger_vblank(6);
    return;
label_DB15:; /* MoveEOfs */
    /* $DB15: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_DB16:;
    /* $DB16: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_DB17:;
    /* $DB17: 20 */ maybe_trigger_vblank(6); call_by_address(0xDB1C);
label_DB1A:;
    /* $DB1A: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DB1C:; /* EnemyTurnAround */
    /* $DB1C: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DB1E:;
    /* $DB1E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_DB20:;
    /* $DB20: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DB44;
label_DB22:;
    /* $DB22: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_DB24:;
    /* $DB24: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DB44;
label_DB26:;
    /* $DB26: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_DB28:;
    /* $DB28: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DB44;
label_DB2A:;
    /* $DB2A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x12; g_cpu.C=(g_cpu.A>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_DB2C:;
    /* $DB2C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DB36;
label_DB2E:;
    /* $DB2E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0E; g_cpu.C=(g_cpu.A>=0x0E)?1:0; FLAG_NZ(r&0xFF); }
label_DB30:;
    /* $DB30: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DB36;
label_DB32:;
    /* $DB32: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_DB34:;
    /* $DB34: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DB44;
label_DB36:; /* RXSpd */
    /* $DB36: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x58 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DB38:;
    /* $DB38: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_DB3A:;
    /* $DB3A: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_DB3B:;
    /* $DB3B: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DB3C:;
    /* $DB3C: 94 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.Y);
label_DB3E:;
    /* $DB3E: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x46 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DB40:;
    /* $DB40: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0x03; FLAG_NZ(g_cpu.A);
label_DB42:;
    /* $DB42: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_DB44:; /* ExTA */
    /* $DB44: 60 */ maybe_trigger_vblank(6);
    return;
label_DB45:; /* LargePlatformCollision */
    /* $DB45: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_DB47:;
    /* $DB47: 9D */ maybe_trigger_vblank(5); nes_write((0x03A2 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DB4A:;
    /* $DB4A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_DB4D:;
    /* $DB4D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DB78;
label_DB4F:;
    /* $DB4F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DB51:;
    /* $DB51: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_DB78;
label_DB53:;
    /* $DB53: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DB55:;
    /* $DB55: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x24; g_cpu.C=(g_cpu.A>=0x24)?1:0; FLAG_NZ(r&0xFF); }
label_DB57:;
    /* $DB57: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DB5F;
label_DB59:;
    /* $DB59: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DB5B:;
    /* $DB5B: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_DB5C:;
    /* $DB5C: 20 */ maybe_trigger_vblank(6); call_by_address(0xDB5F);
label_DB5F:; /* ChkForPlayerC_LargeP */
    /* $DB5F: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC41);
label_DB62:;
    /* $DB62: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DB78;
label_DB64:;
    /* $DB64: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_DB65:;
    /* $DB65: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC54);
label_DB68:;
    /* $DB68: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DB6A:;
    /* $DB6A: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_DB6C:;
    /* $DB6C: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_DB6D:;
    /* $DB6D: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_DB6E:;
    /* $DB6E: 20 */ maybe_trigger_vblank(6); call_by_address(0xE325);
label_DB71:;
    /* $DB71: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_DB72:;
    /* $DB72: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_DB73:;
    /* $DB73: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DB78;
label_DB75:;
    /* $DB75: 20 */ maybe_trigger_vblank(6); call_by_address(0xDBBC);
label_DB78:; /* ExLPC */
    /* $DB78: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DB7A:;
    /* $DB7A: 60 */ maybe_trigger_vblank(6);
    return;
label_DB7B:; /* SmallPlatformCollision */
    /* $DB7B: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_DB7E:;
    /* $DB7E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DBB7;
label_DB80:;
    /* $DB80: 9D */ maybe_trigger_vblank(5); nes_write((0x03A2 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DB83:;
    /* $DB83: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC41);
label_DB86:;
    /* $DB86: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DBB7;
label_DB88:;
    /* $DB88: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_DB8A:;
    /* $DB8A: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_DB8C:; /* ChkSmallPlatLoop */
    /* $DB8C: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DB8E:;
    /* $DB8E: 20 */ maybe_trigger_vblank(6); call_by_address(0xDC52);
label_DB91:;
    /* $DB91: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_DB93:;
    /* $DB93: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DBB7;
label_DB95:;
    /* $DB95: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AD + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DB98:;
    /* $DB98: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_DB9A:;
    /* $DB9A: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DBA1;
label_DB9C:;
    /* $DB9C: 20 */ maybe_trigger_vblank(6); call_by_address(0xE325);
label_DB9F:;
    /* $DB9F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DBBA;
label_DBA1:; /* MoveBoundBox */
    /* $DBA1: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AD + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DBA4:;
    /* $DBA4: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DBA5:;
    /* $DBA5: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x80 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x80); g_cpu.A=r&0xFF; }
label_DBA7:;
    /* $DBA7: 99 */ maybe_trigger_vblank(5); nes_write((0x04AD + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_DBAA:;
    /* $DBAA: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DBAD:;
    /* $DBAD: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DBAE:;
    /* $DBAE: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x80 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x80); g_cpu.A=r&0xFF; }
label_DBB0:;
    /* $DBB0: 99 */ maybe_trigger_vblank(5); nes_write((0x04AF + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_DBB3:;
    /* $DBB3: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DBB5:;
    /* $DBB5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DB8C;
    }
label_DBB7:; /* ExSPC */
    /* $DBB7: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DBB9:;
    /* $DBB9: 60 */ maybe_trigger_vblank(6);
    return;
label_DBBA:; /* ProcSPlatCollisions */
    /* $DBBA: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DBBC:; /* ProcLPlatCollisions */
    /* $DBBC: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DBBF:;
    /* $DBBF: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_DBC0:;
    /* $DBC0: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x04AD); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DBC3:;
    /* $DBC3: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_DBC5:;
    /* $DBC5: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DBCF;
label_DBC7:;
    /* $DBC7: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x9F); FLAG_NZ(g_cpu.A);
label_DBC9:;
    /* $DBC9: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_DBCF;
label_DBCB:;
    /* $DBCB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_DBCD:;
    /* $DBCD: 85 */ maybe_trigger_vblank(3); nes_write(0x9F, g_cpu.A);
label_DBCF:; /* ChkForTopCollision */
    /* $DBCF: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x04AF); FLAG_NZ(g_cpu.A);
label_DBD2:;
    /* $DBD2: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_DBD3:;
    /* $DBD3: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AD + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DBD6:;
    /* $DBD6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_DBD8:;
    /* $DBD8: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DBF5;
label_DBDA:;
    /* $DBDA: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x9F); FLAG_NZ(g_cpu.A);
label_DBDC:;
    /* $DBDC: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_DBF5;
label_DBDE:;
    /* $DBDE: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_DBE0:;
    /* $DBE0: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_DBE2:;
    /* $DBE2: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x2B; g_cpu.C=(g_cpu.Y>=0x2B)?1:0; FLAG_NZ(r&0xFF); }
label_DBE4:;
    /* $DBE4: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DBEB;
label_DBE6:;
    /* $DBE6: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x2C; g_cpu.C=(g_cpu.Y>=0x2C)?1:0; FLAG_NZ(r&0xFF); }
label_DBE8:;
    /* $DBE8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DBEB;
label_DBEA:;
    /* $DBEA: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_DBEB:; /* SetCollisionFlag */
    /* $DBEB: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DBED:;
    /* $DBED: 9D */ maybe_trigger_vblank(5); nes_write((0x03A2 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_DBF0:;
    /* $DBF0: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DBF2:;
    /* $DBF2: 85 */ maybe_trigger_vblank(3); nes_write(0x1D, g_cpu.A);
label_DBF4:;
    /* $DBF4: 60 */ maybe_trigger_vblank(6);
    return;
label_DBF5:; /* PlatformSideCollisions */
    /* $DBF5: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_DBF7:;
    /* $DBF7: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_DBF9:;
    /* $DBF9: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x04AE); FLAG_NZ(g_cpu.A);
label_DBFC:;
    /* $DBFC: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_DBFD:;
    /* $DBFD: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DC00:;
    /* $DC00: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_DC02:;
    /* $DC02: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DC11;
label_DC04:;
    /* $DC04: E6 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DC06:;
    /* $DC06: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AE + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DC09:;
    /* $DC09: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DC0A:;
    /* $DC0A: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x04AC); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DC0D:;
    /* $DC0D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x09; g_cpu.C=(g_cpu.A>=0x09)?1:0; FLAG_NZ(r&0xFF); }
label_DC0F:;
    /* $DC0F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DC14;
label_DC11:; /* SideC */
    /* $DC11: 20 */ maybe_trigger_vblank(6); call_by_address(0xDF4B);
label_DC14:; /* NoSideC */
    /* $DC14: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_DC16:;
    /* $DC16: 60 */ maybe_trigger_vblank(6);
    return;
label_DC17:; /* PlayerPosSPlatData */
    /* $DC17: 80 */ maybe_trigger_vblank(2); /* NOP */
label_DC19:; /* PositionPlayerOnS_Plat */
    /* $DC19: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_DC1A:;
    /* $DC1A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DC1C:;
    /* $DC1C: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DC1D:;
    /* $DC1D: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDC16 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DC20:;
    /* $DC20: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xCFB5); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_DC23:;
    /* $DC23: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x0E); FLAG_NZ(g_cpu.Y);
label_DC25:;
    /* $DC25: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0B; g_cpu.C=(g_cpu.Y>=0x0B)?1:0; FLAG_NZ(r&0xFF); }
label_DC27:;
    /* $DC27: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DC40;
label_DC29:;
    /* $DC29: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0xB6 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_DC2B:;
    /* $DC2B: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x01; g_cpu.C=(g_cpu.Y>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_DC2D:;
    /* $DC2D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DC40;
label_DC2F:;
    /* $DC2F: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_DC30:;
    /* $DC30: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x20; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DC32:;
    /* $DC32: 85 */ maybe_trigger_vblank(3); nes_write(0xCE, g_cpu.A);
label_DC34:;
    /* $DC34: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_DC35:;
    /* $DC35: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DC37:;
    /* $DC37: 85 */ maybe_trigger_vblank(3); nes_write(0xB5, g_cpu.A);
label_DC39:;
    /* $DC39: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DC3B:;
    /* $DC3B: 85 */ maybe_trigger_vblank(3); nes_write(0x9F, g_cpu.A);
label_DC3D:;
    /* $DC3D: 8D */ maybe_trigger_vblank(4); nes_write(0x0433, g_cpu.A);
label_DC40:; /* ExPlPos */
    /* $DC40: 60 */ maybe_trigger_vblank(6);
    return;
label_DC41:; /* CheckPlayerVertical */
    /* $DC41: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D0); FLAG_NZ(g_cpu.A);
label_DC44:;
    /* $DC44: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xF0; g_cpu.C=(g_cpu.A>=0xF0)?1:0; FLAG_NZ(r&0xFF); }
label_DC46:;
    /* $DC46: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DC51;
label_DC48:;
    /* $DC48: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xB5); FLAG_NZ(g_cpu.Y);
label_DC4A:;
    /* $DC4A: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DC4B:;
    /* $DC4B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DC51;
label_DC4D:;
    /* $DC4D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_DC4F:;
    /* $DC4F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xD0; g_cpu.C=(g_cpu.A>=0xD0)?1:0; FLAG_NZ(r&0xFF); }
label_DC51:; /* ExCPV */
    /* $DC51: 60 */ maybe_trigger_vblank(6);
    return;
label_DC52:; /* GetEnemyBoundBoxOfs */
    /* $DC52: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x08); FLAG_NZ(g_cpu.A);
label_DC54:; /* GetEnemyBoundBoxOfsArg */
    /* $DC54: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DC55:;
    /* $DC55: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DC56:;
    /* $DC56: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DC57:;
    /* $DC57: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_DC59:;
    /* $DC59: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_DC5A:;
    /* $DC5A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D1); FLAG_NZ(g_cpu.A);
label_DC5D:;
    /* $DC5D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_DC5F:;
    /* $DC5F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0F; g_cpu.C=(g_cpu.A>=0x0F)?1:0; FLAG_NZ(r&0xFF); }
label_DC61:;
    /* $DC61: 60 */ maybe_trigger_vblank(6);
    return;
label_DC62:; /* PlayerBGUpperExtent */
    /* $DC62: 20 */ maybe_trigger_vblank(6); call_by_address(0xAD10);
label_DC65:;
    /* $DC65: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x07 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
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
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
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
label_DE0E:; /* HandleAxeMetatile */
    /* $DE0E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DE10:;
    /* $DE10: 8D */ maybe_trigger_vblank(4); nes_write(0x0772, g_cpu.A);
label_DE13:;
    /* $DE13: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_DE15:;
    /* $DE15: 8D */ maybe_trigger_vblank(4); nes_write(0x0770, g_cpu.A);
label_DE18:;
    /* $DE18: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_DE1A:;
    /* $DE1A: 85 */ maybe_trigger_vblank(3); nes_write(0x57, g_cpu.A);
label_DE1C:; /* ErACM */
    /* $DE1C: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x02); FLAG_NZ(g_cpu.Y);
label_DE1E:;
    /* $DE1E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DE20:;
    /* $DE20: 91 */ maybe_trigger_vblank(6); nes_write((nes_read16zp(0x06) + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_DE22:;
    /* $DE22: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x8A4D); return;
label_DE25:; /* ClimbXPosAdder */
    /* $DE25: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xFF07 + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DE28:;
    /* $DE28: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xDE28); return;
label_DE29:; /* FlagpoleYPosData */
    /* $DE29: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DE2A:;
    /* $DE2A: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_DE2B:;
    /* $DE2B: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) goto label_DE95;
label_DE2D:;
    /* $DE2D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DDD3;
    }
label_DE2F:;
    /* $DE2F: 04 */ maybe_trigger_vblank(3); (void)nes_read(0xC0); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_DE31:;
    /* $DE31: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x90; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DE33:;
    /* $DE33: 04 */ maybe_trigger_vblank(3); (void)nes_read(0xC0); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_DE35:;
    /* $DE35: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DE36:;
    /* $DE36: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DE39;
label_DE38:; /* ExHC */
    /* $DE38: 60 */ maybe_trigger_vblank(6);
    return;
label_DE39:; /* ChkForFlagpole */
    /* $DE39: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x24; g_cpu.C=(g_cpu.A>=0x24)?1:0; FLAG_NZ(r&0xFF); }
label_DE3B:;
    /* $DE3B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DE41;
label_DE3D:;
    /* $DE3D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x25; g_cpu.C=(g_cpu.A>=0x25)?1:0; FLAG_NZ(r&0xFF); }
label_DE3F:;
    /* $DE3F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DE7A;
label_DE41:; /* FlagpoleCollision */
    /* $DE41: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0E); FLAG_NZ(g_cpu.A);
label_DE43:;
    /* $DE43: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_DE45:;
    /* $DE45: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DE88;
label_DE47:;
    /* $DE47: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_DE49:;
    /* $DE49: 85 */ maybe_trigger_vblank(3); nes_write(0x33, g_cpu.A);
label_DE4B:;
    /* $DE4B: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0723; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DE4E:;
    /* $DE4E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0E); FLAG_NZ(g_cpu.A);
label_DE50:;
    /* $DE50: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_DE52:;
    /* $DE52: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DE73;
label_DE54:;
    /* $DE54: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x33; FLAG_NZ(g_cpu.A);
label_DE56:;
    /* $DE56: 20 */ maybe_trigger_vblank(6); call_by_address(0x9716);
label_DE59:;
    /* $DE59: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_DE5B:;
    /* $DE5B: 85 */ maybe_trigger_vblank(3); nes_write(0xFC, g_cpu.A);
label_DE5D:;
    /* $DE5D: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_DE5E:;
    /* $DE5E: 8D */ maybe_trigger_vblank(4); nes_write(0x0713, g_cpu.A);
label_DE61:;
    /* $DE61: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x04; FLAG_NZ(g_cpu.X);
label_DE63:;
    /* $DE63: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_DE65:;
    /* $DE65: 8D */ maybe_trigger_vblank(4); nes_write(0x070F, g_cpu.A);
label_DE68:; /* ChkFlagpoleYPosLoop */
    /* $DE68: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDE29 + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_DE6B:;
    /* $DE6B: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DE70;
label_DE6D:;
    /* $DE6D: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_DE6E:;
    /* $DE6E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DE68;
    }
label_DE70:; /* MtchF */
    /* $DE70: 8E */ maybe_trigger_vblank(4); nes_write(0x010F, g_cpu.X);
label_DE73:; /* RunFR */
    /* $DE73: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_DE75:;
    /* $DE75: 85 */ maybe_trigger_vblank(3); nes_write(0x0E, g_cpu.A);
label_DE77:;
    /* $DE77: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xDE88); return;
label_DE7A:; /* VineCollision */
    /* $DE7A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x26; g_cpu.C=(g_cpu.A>=0x26)?1:0; FLAG_NZ(r&0xFF); }
label_DE7C:;
    /* $DE7C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DE88;
label_DE7E:;
    /* $DE7E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_DE80:;
    /* $DE80: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_DE82:;
    /* $DE82: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DE88;
label_DE84:;
    /* $DE84: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_DE86:;
    /* $DE86: 85 */ maybe_trigger_vblank(3); nes_write(0x0E, g_cpu.A);
label_DE88:; /* PutPlayerOnVine */
    /* $DE88: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_DE8A:;
    /* $DE8A: 85 */ maybe_trigger_vblank(3); nes_write(0x1D, g_cpu.A);
label_DE8C:;
    /* $DE8C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DE8E:;
    /* $DE8E: 85 */ maybe_trigger_vblank(3); nes_write(0x57, g_cpu.A);
label_DE90:;
    /* $DE90: 8D */ maybe_trigger_vblank(4); nes_write(0x0705, g_cpu.A);
label_DE93:;
    /* $DE93: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x86); FLAG_NZ(g_cpu.A);
label_DE95:;
    /* $DE95: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_DE96:;
    /* $DE96: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x071C); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DE99:;
    /* $DE99: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x10; g_cpu.C=(g_cpu.A>=0x10)?1:0; FLAG_NZ(r&0xFF); }
label_DE9B:;
    /* $DE9B: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_DEA1;
label_DE9D:;
    /* $DE9D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_DE9F:;
    /* $DE9F: 85 */ maybe_trigger_vblank(3); nes_write(0x33, g_cpu.A);
label_DEA1:; /* SetVXPl */
    /* $DEA1: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x33); FLAG_NZ(g_cpu.Y);
label_DEA3:;
    /* $DEA3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x06); FLAG_NZ(g_cpu.A);
label_DEA5:;
    /* $DEA5: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DEA6:;
    /* $DEA6: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DEA7:;
    /* $DEA7: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DEA8:;
    /* $DEA8: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DEA9:;
    /* $DEA9: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DEAA:;
    /* $DEAA: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDE24 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DEAD:;
    /* $DEAD: 85 */ maybe_trigger_vblank(3); nes_write(0x86, g_cpu.A);
label_DEAF:;
    /* $DEAF: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x06); FLAG_NZ(g_cpu.A);
label_DEB1:;
    /* $DEB1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DEBC;
label_DEB3:;
    /* $DEB3: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071B); FLAG_NZ(g_cpu.A);
label_DEB6:;
    /* $DEB6: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DEB7:;
    /* $DEB7: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDE26 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DEBA:;
    /* $DEBA: 85 */ maybe_trigger_vblank(3); nes_write(0x6D, g_cpu.A);
label_DEBC:; /* ExPVne */
    /* $DEBC: 60 */ maybe_trigger_vblank(6);
    return;
label_DEBD:; /* ChkInvisibleMTiles */
    /* $DEBD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x5F; g_cpu.C=(g_cpu.A>=0x5F)?1:0; FLAG_NZ(r&0xFF); }
label_DEBF:;
    /* $DEBF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DEC3;
label_DEC1:;
    /* $DEC1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x60; g_cpu.C=(g_cpu.A>=0x60)?1:0; FLAG_NZ(r&0xFF); }
label_DEC3:; /* ExCInvT */
    /* $DEC3: 60 */ maybe_trigger_vblank(6);
    return;
label_DEC4:; /* ChkForLandJumpSpring */
    /* $DEC4: 20 */ maybe_trigger_vblank(6); call_by_address(0xDEDD);
label_DEC7:;
    /* $DEC7: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DEDC;
label_DEC9:;
    /* $DEC9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x70; FLAG_NZ(g_cpu.A);
label_DECB:;
    /* $DECB: 8D */ maybe_trigger_vblank(4); nes_write(0x0709, g_cpu.A);
label_DECE:;
    /* $DECE: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF9; FLAG_NZ(g_cpu.A);
label_DED0:;
    /* $DED0: 8D */ maybe_trigger_vblank(4); nes_write(0x06DB, g_cpu.A);
label_DED3:;
    /* $DED3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_DED5:;
    /* $DED5: 8D */ maybe_trigger_vblank(4); nes_write(0x0786, g_cpu.A);
label_DED8:;
    /* $DED8: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_DED9:;
    /* $DED9: 8D */ maybe_trigger_vblank(4); nes_write(0x070E, g_cpu.A);
label_DEDC:; /* ExCJSp */
    /* $DEDC: 60 */ maybe_trigger_vblank(6);
    return;
label_DEDD:; /* ChkJumpspringMetatiles */
    /* $DEDD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x67; g_cpu.C=(g_cpu.A>=0x67)?1:0; FLAG_NZ(r&0xFF); }
label_DEDF:;
    /* $DEDF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DEE6;
label_DEE1:;
    /* $DEE1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x68; g_cpu.C=(g_cpu.A>=0x68)?1:0; FLAG_NZ(r&0xFF); }
label_DEE3:;
    /* $DEE3: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DEE4:;
    /* $DEE4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DEE7;
label_DEE6:; /* JSFnd */
    /* $DEE6: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_DEE7:; /* NoJSFnd */
    /* $DEE7: 60 */ maybe_trigger_vblank(6);
    return;
label_DEE8:; /* HandlePipeEntry */
    /* $DEE8: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x0B); FLAG_NZ(g_cpu.A);
label_DEEA:;
    /* $DEEA: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x04; FLAG_NZ(g_cpu.A);
label_DEEC:;
    /* $DEEC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DF4A;
label_DEEE:;
    /* $DEEE: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_DEF0:;
    /* $DEF0: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_DEF2:;
    /* $DEF2: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DF4A;
label_DEF4:;
    /* $DEF4: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_DEF6:;
    /* $DEF6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x10; g_cpu.C=(g_cpu.A>=0x10)?1:0; FLAG_NZ(r&0xFF); }
label_DEF8:;
    /* $DEF8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DF4A;
label_DEFA:;
    /* $DEFA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x30; FLAG_NZ(g_cpu.A);
label_DEFC:;
    /* $DEFC: 8D */ maybe_trigger_vblank(4); nes_write(0x06DE, g_cpu.A);
label_DEFF:;
    /* $DEFF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_DF01:;
    /* $DF01: 85 */ maybe_trigger_vblank(3); nes_write(0x0E, g_cpu.A);
label_DF03:;
    /* $DF03: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_DF05:;
    /* $DF05: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_DF07:;
    /* $DF07: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_DF09:;
    /* $DF09: 8D */ maybe_trigger_vblank(4); nes_write(0x03C4, g_cpu.A);
label_DF0C:;
    /* $DF0C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06D6); FLAG_NZ(g_cpu.A);
label_DF0F:;
    /* $DF0F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DF4A;
label_DF11:;
    /* $DF11: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_DF13:;
    /* $DF13: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DF14:;
    /* $DF14: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_DF15:;
    /* $DF15: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_DF16:;
    /* $DF16: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x86); FLAG_NZ(g_cpu.A);
label_DF18:;
    /* $DF18: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x60; g_cpu.C=(g_cpu.A>=0x60)?1:0; FLAG_NZ(r&0xFF); }
label_DF1A:;
    /* $DF1A: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DF22;
label_DF1C:;
    /* $DF1C: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_DF1D:;
    /* $DF1D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xA0; g_cpu.C=(g_cpu.A>=0xA0)?1:0; FLAG_NZ(r&0xFF); }
label_DF1F:;
    /* $DF1F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_DF22;
label_DF21:;
    /* $DF21: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_DF22:; /* GetWNum */
    /* $DF22: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x87F2 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_DF25:;
    /* $DF25: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DF26:;
    /* $DF26: 8C */ maybe_trigger_vblank(4); nes_write(0x075F, g_cpu.Y);
label_DF29:;
    /* $DF29: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0x9CB4 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_DF2C:;
    /* $DF2C: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x9CBC + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_DF2F:;
    /* $DF2F: 8D */ maybe_trigger_vblank(4); nes_write(0x0750, g_cpu.A);
label_DF32:;
    /* $DF32: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_DF34:;
    /* $DF34: 85 */ maybe_trigger_vblank(3); nes_write(0xFC, g_cpu.A);
label_DF36:;
    /* $DF36: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DF38:;
    /* $DF38: 8D */ maybe_trigger_vblank(4); nes_write(0x0751, g_cpu.A);
label_DF3B:;
    /* $DF3B: 8D */ maybe_trigger_vblank(4); nes_write(0x0760, g_cpu.A);
label_DF3E:;
    /* $DF3E: 8D */ maybe_trigger_vblank(4); nes_write(0x075C, g_cpu.A);
label_DF41:;
    /* $DF41: 8D */ maybe_trigger_vblank(4); nes_write(0x0752, g_cpu.A);
label_DF44:;
    /* $DF44: EE */ maybe_trigger_vblank(6); { uint16_t a=0x075D; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DF47:;
    /* $DF47: EE */ maybe_trigger_vblank(6); { uint16_t a=0x0757; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DF4A:; /* ExPipeE */
    /* $DF4A: 60 */ maybe_trigger_vblank(6);
    return;
label_DF4B:; /* ImpedePlayerMove */
    /* $DF4B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_DF4D:;
    /* $DF4D: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x57); FLAG_NZ(g_cpu.Y);
label_DF4F:;
    /* $DF4F: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x00); FLAG_NZ(g_cpu.X);
label_DF51:;
    /* $DF51: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_DF52:;
    /* $DF52: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DF5E;
label_DF54:;
    /* $DF54: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_DF55:;
    /* $DF55: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x00; g_cpu.C=(g_cpu.Y>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_DF57:;
    /* $DF57: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_DF81;
label_DF59:;
    /* $DF59: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_DF5B:;
    /* $DF5B: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xDF66); return;
label_DF5E:; /* RImpd */
    /* $DF5E: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x02; FLAG_NZ(g_cpu.X);
label_DF60:;
    /* $DF60: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x01; g_cpu.C=(g_cpu.Y>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_DF62:;
    /* $DF62: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_DF81;
label_DF64:;
    /* $DF64: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_DF66:; /* NXSpd */
    /* $DF66: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x10; FLAG_NZ(g_cpu.Y);
label_DF68:;
    /* $DF68: 8C */ maybe_trigger_vblank(4); nes_write(0x0785, g_cpu.Y);
label_DF6B:;
    /* $DF6B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_DF6D:;
    /* $DF6D: 84 */ maybe_trigger_vblank(3); nes_write(0x57, g_cpu.Y);
label_DF6F:;
    /* $DF6F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_DF71:;
    /* $DF71: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_DF74;
label_DF73:;
    /* $DF73: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DF74:; /* PlatF */
    /* $DF74: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_DF76:;
    /* $DF76: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DF77:;
    /* $DF77: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x86); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DF79:;
    /* $DF79: 85 */ maybe_trigger_vblank(3); nes_write(0x86, g_cpu.A);
label_DF7B:;
    /* $DF7B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x6D); FLAG_NZ(g_cpu.A);
label_DF7D:;
    /* $DF7D: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x00); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_DF7F:;
    /* $DF7F: 85 */ maybe_trigger_vblank(3); nes_write(0x6D, g_cpu.A);
label_DF81:; /* ExIPM */
    /* $DF81: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_DF82:;
    /* $DF82: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_DF84:;
    /* $DF84: 2D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read(0x0490); FLAG_NZ(g_cpu.A);
label_DF87:;
    /* $DF87: 8D */ maybe_trigger_vblank(4); nes_write(0x0490, g_cpu.A);
label_DF8A:;
    /* $DF8A: 60 */ maybe_trigger_vblank(6);
    return;
label_DF8B:; /* SolidMTileUpperExt */
    /* $DF8B: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_DFEE;
label_DF8D:;
    /* $DF8D: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_DF8E:;
    /* $DF8E: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x20); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_DF90:;
    /* $DF90: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DF71;
    }
label_DF92:;
    /* $DF92: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDF8B + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_DF95:;
    /* $DF95: 60 */ maybe_trigger_vblank(6);
    return;
label_DF96:; /* ClimbMTileUpperExt */
    /* $DF96: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x6D); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_DF98:;
    /* $DF98: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_DF99:;
    /* $DF99: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DF9B:;
    /* $DF9B: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xDF7C); return; }
label_DF9D:;
    /* $DF9D: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDF96 + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_DFA0:;
    /* $DFA0: 60 */ maybe_trigger_vblank(6);
    return;
label_DFA1:; /* CheckForCoinMTiles */
    /* $DFA1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xC2; g_cpu.C=(g_cpu.A>=0xC2)?1:0; FLAG_NZ(r&0xFF); }
label_DFA3:;
    /* $DFA3: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DFAB;
label_DFA5:;
    /* $DFA5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xC3; g_cpu.C=(g_cpu.A>=0xC3)?1:0; FLAG_NZ(r&0xFF); }
label_DFA7:;
    /* $DFA7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DFAB;
label_DFA9:;
    /* $DFA9: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_DFAA:;
    /* $DFAA: 60 */ maybe_trigger_vblank(6);
    return;
label_DFAB:; /* CoinSd */
    /* $DFAB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_DFAD:;
    /* $DFAD: 85 */ maybe_trigger_vblank(3); nes_write(0xFE, g_cpu.A);
label_DFAF:;
    /* $DFAF: 60 */ maybe_trigger_vblank(6);
    return;
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
label_DFB9:; /* EnemyBGCStateData */
    /* $DFB9: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x01 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_DFBB:;
    /* $DFBB: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_DFBC:;
    /* $DFBC: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_DFBD:;
    /* $DFBD: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_DFBE:;
    /* $DFBE: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x10); FLAG_NZ(g_cpu.A);
label_DFC0:;
    /* $DFC0: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DF77;
    }
label_DFC2:;
    /* $DFC2: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x2029 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_DFC5:;
    /* $DFC5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DFB8;
    }
label_DFC7:;
    /* $DFC7: 20 */ maybe_trigger_vblank(6); call_by_address(0xE15B);
label_DFCA:;
    /* $DFCA: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DFB8;
    }
label_DFCC:;
    /* $DFCC: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_DFCE:;
    /* $DFCE: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x12; g_cpu.C=(g_cpu.Y>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_DFD0:;
    /* $DFD0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DFD8;
label_DFD2:;
    /* $DFD2: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DFD4:;
    /* $DFD4: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x25; g_cpu.C=(g_cpu.A>=0x25)?1:0; FLAG_NZ(r&0xFF); }
label_DFD6:;
    /* $DFD6: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DFB8;
    }
label_DFD8:; /* DoIDCheckBGColl */
    /* $DFD8: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0E; g_cpu.C=(g_cpu.Y>=0x0E)?1:0; FLAG_NZ(r&0xFF); }
label_DFDA:;
    /* $DFDA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DFDF;
label_DFDC:;
    /* $DFDC: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE163); return;
label_DFDF:; /* HBChk */
    /* $DFDF: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x05; g_cpu.C=(g_cpu.Y>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_DFE1:;
    /* $DFE1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DFE6;
label_DFE3:;
    /* $DFE3: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE185); return;
label_DFE6:; /* CInvu */
    /* $DFE6: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x12; g_cpu.C=(g_cpu.Y>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_DFE8:;
    /* $DFE8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DFF2;
label_DFEA:;
    /* $DFEA: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x2E; g_cpu.C=(g_cpu.Y>=0x2E)?1:0; FLAG_NZ(r&0xFF); }
label_DFEC:;
    /* $DFEC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DFF2;
label_DFEE:;
    /* $DFEE: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x07; g_cpu.C=(g_cpu.Y>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_DFF0:;
    /* $DFF0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E066;
label_DFF2:; /* YesIn */
    /* $DFF2: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1AE);
label_DFF5:;
    /* $DFF5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DFFA;
label_DFF7:; /* NoEToBGCollision */
    /* $DFF7: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE0E2); return;
label_DFFA:; /* HandleEToBGCollision */
    /* $DFFA: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1B5);
label_DFFD:;
    /* $DFFD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DFF7;
    }
label_DFFF:;
    /* $DFFF: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x23; g_cpu.C=(g_cpu.A>=0x23)?1:0; FLAG_NZ(r&0xFF); }
label_E001:;
    /* $E001: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E067;
label_E003:;
    /* $E003: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x02); FLAG_NZ(g_cpu.Y);
label_E005:;
    /* $E005: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E007:;
    /* $E007: 91 */ maybe_trigger_vblank(6); nes_write((nes_read16zp(0x06) + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E009:;
    /* $E009: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E00B:;
    /* $E00B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_E00D:;
    /* $E00D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E01B;
label_E00F:;
    /* $E00F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_E011:;
    /* $E011: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E016;
label_E013:;
    /* $E013: 20 */ maybe_trigger_vblank(6); call_by_address(0xE18E);
label_E016:; /* GiveOEPoints */
    /* $E016: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E018:;
    /* $E018: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_E01B:; /* ChkToStunEnemies */
    /* $E01B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x09; g_cpu.C=(g_cpu.A>=0x09)?1:0; FLAG_NZ(r&0xFF); }
label_E01D:;
    /* $E01D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E02F;
label_E01F:;
    /* $E01F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_E021:;
    /* $E021: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E02F;
label_E023:;
    /* $E023: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0A; g_cpu.C=(g_cpu.A>=0x0A)?1:0; FLAG_NZ(r&0xFF); }
label_E025:;
    /* $E025: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E02B;
label_E027:;
    /* $E027: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_E029:;
    /* $E029: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E02F;
label_E02B:; /* Demote */
    /* $E02B: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_E02D:;
    /* $E02D: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_E02F:; /* SetStun */
    /* $E02F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E031:;
    /* $E031: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF0; FLAG_NZ(g_cpu.A);
label_E033:;
    /* $E033: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x02; FLAG_NZ(g_cpu.A);
label_E035:;
    /* $E035: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E037:;
    /* $E037: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0xCF + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E039:;
    /* $E039: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0xCF + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E03B:;
    /* $E03B: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E03D:;
    /* $E03D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_E03F:;
    /* $E03F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E048;
label_E041:;
    /* $E041: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFD; FLAG_NZ(g_cpu.A);
label_E043:;
    /* $E043: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_E046:;
    /* $E046: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E04A;
label_E048:; /* SetWYSpd */
    /* $E048: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_E04A:; /* SetNotW */
    /* $E04A: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_E04C:;
    /* $E04C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_E04E:;
    /* $E04E: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_E051:;
    /* $E051: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_E054;
label_E053:;
    /* $E053: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E054:; /* ChkBBill */
    /* $E054: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E056:;
    /* $E056: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x33; g_cpu.C=(g_cpu.A>=0x33)?1:0; FLAG_NZ(r&0xFF); }
label_E058:;
    /* $E058: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E060;
label_E05A:;
    /* $E05A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_E05C:;
    /* $E05C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E060;
label_E05E:;
    /* $E05E: 94 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.Y);
label_E060:; /* NoCDirF */
    /* $E060: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E061:;
    /* $E061: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xDFBF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E064:;
    /* $E064: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_E066:; /* ExEBGChk */
    /* $E066: 60 */ maybe_trigger_vblank(6);
    return;
label_E067:; /* LandEnemyProperly */
    /* $E067: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x04); FLAG_NZ(g_cpu.A);
label_E069:;
    /* $E069: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_E06A:;
    /* $E06A: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x08; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E06C:;
    /* $E06C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E06E:;
    /* $E06E: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E0E2;
label_E070:;
    /* $E070: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E072:;
    /* $E072: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_E074:;
    /* $E074: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0CD;
label_E076:;
    /* $E076: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E078:;
    /* $E078: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E079:;
    /* $E079: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E07E;
label_E07B:; /* SChkA */
    /* $E07B: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE0FE); return;
label_E07E:; /* ChkLandedEnemyState */
    /* $E07E: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E080:;
    /* $E080: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E07B;
    }
label_E082:;
    /* $E082: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E084:;
    /* $E084: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E0A5;
label_E086:;
    /* $E086: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_E088:;
    /* $E088: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E0A4;
label_E08A:;
    /* $E08A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E08C:;
    /* $E08C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_E08E:;
    /* $E08E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0A5;
label_E090:;
    /* $E090: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_E092:;
    /* $E092: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_E094:;
    /* $E094: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x12; g_cpu.C=(g_cpu.Y>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_E096:;
    /* $E096: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E09A;
label_E098:;
    /* $E098: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E09A:; /* SetForStn */
    /* $E09A: 9D */ maybe_trigger_vblank(5); nes_write((0x0796 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_E09D:;
    /* $E09D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_E09F:;
    /* $E09F: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E0A1:;
    /* $E0A1: 20 */ maybe_trigger_vblank(6); call_by_address(0xE14F);
label_E0A4:; /* ExSteChk */
    /* $E0A4: 60 */ maybe_trigger_vblank(6);
    return;
label_E0A5:; /* ProcEnemyDirection */
    /* $E0A5: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0A7:;
    /* $E0A7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_E0A9:;
    /* $E0A9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E0CD;
label_E0AB:;
    /* $E0AB: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x12; g_cpu.C=(g_cpu.A>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_E0AD:;
    /* $E0AD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0BD;
label_E0AF:;
    /* $E0AF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E0B1:;
    /* $E0B1: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_E0B3:;
    /* $E0B3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_E0B5:;
    /* $E0B5: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_E0B7:;
    /* $E0B7: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_E0B9:;
    /* $E0B9: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_E0BB:;
    /* $E0BB: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E0CD;
label_E0BD:; /* InvtD */
    /* $E0BD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_E0BF:;
    /* $E0BF: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_E0C2:;
    /* $E0C2: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_E0C5;
label_E0C4:;
    /* $E0C4: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E0C5:; /* CNwCDir */
    /* $E0C5: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_E0C6:;
    /* $E0C6: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x46 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E0C8:;
    /* $E0C8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0CD;
label_E0CA:;
    /* $E0CA: 20 */ maybe_trigger_vblank(6); call_by_address(0xE124);
label_E0CD:; /* LandEnemyInitState */
    /* $E0CD: 20 */ maybe_trigger_vblank(6); call_by_address(0xE14F);
label_E0D0:;
    /* $E0D0: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0D2:;
    /* $E0D2: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x80; FLAG_NZ(g_cpu.A);
label_E0D4:;
    /* $E0D4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0DB;
label_E0D6:;
    /* $E0D6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E0D8:;
    /* $E0D8: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E0DA:;
    /* $E0DA: 60 */ maybe_trigger_vblank(6);
    return;
label_E0DB:; /* NMovShellFallBit */
    /* $E0DB: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0DD:;
    /* $E0DD: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xBF; FLAG_NZ(g_cpu.A);
label_E0DF:;
    /* $E0DF: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E0E1:;
    /* $E0E1: 60 */ maybe_trigger_vblank(6);
    return;
label_E0E2:; /* ChkForRedKoopa */
    /* $E0E2: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0E4:;
    /* $E0E4: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_E0E6:;
    /* $E0E6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0EC;
label_E0E8:;
    /* $E0E8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0EA:;
    /* $E0EA: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E124;
label_E0EC:; /* Chk2MSBSt */
    /* $E0EC: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0EE:;
    /* $E0EE: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_E0EF:;
    /* $E0EF: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E0F0:;
    /* $E0F0: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E0F9;
label_E0F2:;
    /* $E0F2: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0F4:;
    /* $E0F4: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_E0F6:;
    /* $E0F6: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE0FC); return;
label_E0F9:; /* GetSteFromD */
    /* $E0F9: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xDFB9 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E0FC:; /* SetD6Ste */
    /* $E0FC: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E0FE:; /* DoEnemySideCheck */
    /* $E0FE: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E100:;
    /* $E100: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_E102:;
    /* $E102: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E123;
label_E104:;
    /* $E104: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x16; FLAG_NZ(g_cpu.Y);
label_E106:;
    /* $E106: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E108:;
    /* $E108: 85 */ maybe_trigger_vblank(3); nes_write(0xEB, g_cpu.A);
label_E10A:; /* SdeCLoop */
    /* $E10A: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xEB); FLAG_NZ(g_cpu.A);
label_E10C:;
    /* $E10C: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x46 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E10E:;
    /* $E10E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E11C;
label_E110:;
    /* $E110: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E112:;
    /* $E112: 20 */ maybe_trigger_vblank(6); call_by_address(0xE388);
label_E115:;
    /* $E115: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E11C;
label_E117:;
    /* $E117: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1B5);
label_E11A:;
    /* $E11A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E124;
label_E11C:; /* NextSdeC */
    /* $E11C: C6 */ maybe_trigger_vblank(5); { uint16_t a=0xEB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E11E:;
    /* $E11E: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E11F:;
    /* $E11F: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x18; g_cpu.C=(g_cpu.Y>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_E121:;
    /* $E121: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E10A;
    }
label_E123:; /* ExESdeC */
    /* $E123: 60 */ maybe_trigger_vblank(6);
    return;
label_E124:; /* ChkForBump_HammerBroJ */
    /* $E124: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x05; g_cpu.C=(g_cpu.X>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E126:;
    /* $E126: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E131;
label_E128:;
    /* $E128: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E12A:;
    /* $E12A: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E12B:;
    /* $E12B: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E131;
label_E12D:;
    /* $E12D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E12F:;
    /* $E12F: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_E131:; /* NoBump */
    /* $E131: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E133:;
    /* $E133: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E135:;
    /* $E135: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E140;
label_E137:;
    /* $E137: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E139:;
    /* $E139: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_E13B:;
    /* $E13B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xFA; FLAG_NZ(g_cpu.Y);
label_E13D:;
    /* $E13D: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xCA37); return;
label_E140:; /* InvEnemyDir */
    /* $E140: 4C */ maybe_trigger_vblank(3); goto label_DB36;
label_E143:; /* PlayerEnemyDiff */
    /* $E143: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E145:;
    /* $E145: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_E146:;
    /* $E146: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x86); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E148:;
    /* $E148: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_E14A:;
    /* $E14A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E14C:;
    /* $E14C: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x6D); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E14E:;
    /* $E14E: 60 */ maybe_trigger_vblank(6);
    return;
label_E14F:; /* EnemyLanding */
    /* $E14F: 20 */ maybe_trigger_vblank(6); call_by_address(0xC363);
label_E152:;
    /* $E152: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E154:;
    /* $E154: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF0; FLAG_NZ(g_cpu.A);
label_E156:;
    /* $E156: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x08; FLAG_NZ(g_cpu.A);
label_E158:;
    /* $E158: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_E15A:;
    /* $E15A: 60 */ maybe_trigger_vblank(6);
    return;
label_E15B:; /* SubtEnemyYPos */
    /* $E15B: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E15D:;
    /* $E15D: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E15E:;
    /* $E15E: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x3E + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x3E); g_cpu.A=r&0xFF; }
label_E160:;
    /* $E160: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x44; g_cpu.C=(g_cpu.A>=0x44)?1:0; FLAG_NZ(r&0xFF); }
label_E162:;
    /* $E162: 60 */ maybe_trigger_vblank(6);
    return;
label_E163:; /* EnemyJump */
    /* $E163: 20 */ maybe_trigger_vblank(6); call_by_address(0xE15B);
label_E166:;
    /* $E166: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E182;
label_E168:;
    /* $E168: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA0 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E16A:;
    /* $E16A: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E16B:;
    /* $E16B: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x02 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x02); g_cpu.A=r&0xFF; }
label_E16D:;
    /* $E16D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_E16F:;
    /* $E16F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E182;
label_E171:;
    /* $E171: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1AE);
label_E174:;
    /* $E174: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E182;
label_E176:;
    /* $E176: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1B5);
label_E179:;
    /* $E179: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E182;
label_E17B:;
    /* $E17B: 20 */ maybe_trigger_vblank(6); call_by_address(0xE14F);
label_E17E:;
    /* $E17E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFD; FLAG_NZ(g_cpu.A);
label_E180:;
    /* $E180: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_E182:; /* DoSide */
    /* $E182: 4C */ maybe_trigger_vblank(3); goto label_E0FE;
label_E185:; /* HammerBroBGColl */
    /* $E185: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1AE);
label_E188:;
    /* $E188: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E1A7;
label_E18A:;
    /* $E18A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x23; g_cpu.C=(g_cpu.A>=0x23)?1:0; FLAG_NZ(r&0xFF); }
label_E18C:;
    /* $E18C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E196;
label_E18E:; /* KillEnemyAboveBlock */
    /* $E18E: 20 */ maybe_trigger_vblank(6); call_by_address(0xD795);
label_E191:;
    /* $E191: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFC; FLAG_NZ(g_cpu.A);
label_E193:;
    /* $E193: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_E195:;
    /* $E195: 60 */ maybe_trigger_vblank(6);
    return;
label_E196:; /* UnderHammerBro */
    /* $E196: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x078A + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E199:;
    /* $E199: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E1A7;
label_E19B:;
    /* $E19B: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E19D:;
    /* $E19D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x88; FLAG_NZ(g_cpu.A);
label_E19F:;
    /* $E19F: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E1A1:;
    /* $E1A1: 20 */ maybe_trigger_vblank(6); call_by_address(0xE14F);
label_E1A4:;
    /* $E1A4: 4C */ maybe_trigger_vblank(3); goto label_E0FE;
label_E1A7:; /* NoUnderHammerBro */
    /* $E1A7: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E1A9:;
    /* $E1A9: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x01; FLAG_NZ(g_cpu.A);
label_E1AB:;
    /* $E1AB: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E1AD:;
    /* $E1AD: 60 */ maybe_trigger_vblank(6);
    return;
label_E1AE:; /* ChkUnderEnemy */
    /* $E1AE: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E1B0:;
    /* $E1B0: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x15; FLAG_NZ(g_cpu.Y);
label_E1B2:;
    /* $E1B2: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE388); return;
label_E1B5:; /* ChkForNonSolids */
    /* $E1B5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x26; g_cpu.C=(g_cpu.A>=0x26)?1:0; FLAG_NZ(r&0xFF); }
label_E1B7:;
    /* $E1B7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E1C7;
label_E1B9:;
    /* $E1B9: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xC2; g_cpu.C=(g_cpu.A>=0xC2)?1:0; FLAG_NZ(r&0xFF); }
label_E1BB:;
    /* $E1BB: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E1C7;
label_E1BD:;
    /* $E1BD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xC3; g_cpu.C=(g_cpu.A>=0xC3)?1:0; FLAG_NZ(r&0xFF); }
label_E1BF:;
    /* $E1BF: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E1C7;
label_E1C1:;
    /* $E1C1: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x5F; g_cpu.C=(g_cpu.A>=0x5F)?1:0; FLAG_NZ(r&0xFF); }
label_E1C3:;
    /* $E1C3: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E1C7;
label_E1C5:;
    /* $E1C5: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x60; g_cpu.C=(g_cpu.A>=0x60)?1:0; FLAG_NZ(r&0xFF); }
label_E1C7:; /* NSFnd */
    /* $E1C7: 60 */ maybe_trigger_vblank(6);
    return;
label_E1C8:; /* FireballBGCollision */
    /* $E1C8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD5 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E1CA:;
    /* $E1CA: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x18; g_cpu.C=(g_cpu.A>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_E1CC:;
    /* $E1CC: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E1EF;
label_E1CE:;
    /* $E1CE: 20 */ maybe_trigger_vblank(6); call_by_address(0xE39C);
label_E1D1:;
    /* $E1D1: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E1EF;
label_E1D3:;
    /* $E1D3: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1B5);
label_E1D6:;
    /* $E1D6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E1EF;
label_E1D8:;
    /* $E1D8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xA6 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E1DA:;
    /* $E1DA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_E1F4;
label_E1DC:;
    /* $E1DC: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x3A + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E1DE:;
    /* $E1DE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E1F4;
label_E1E0:;
    /* $E1E0: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFD; FLAG_NZ(g_cpu.A);
label_E1E2:;
    /* $E1E2: 95 */ maybe_trigger_vblank(4); nes_write((0xA6 + g_cpu.X) & 0xFF, g_cpu.A);
label_E1E4:;
    /* $E1E4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E1E6:;
    /* $E1E6: 95 */ maybe_trigger_vblank(4); nes_write((0x3A + g_cpu.X) & 0xFF, g_cpu.A);
label_E1E8:;
    /* $E1E8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xD5 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E1EA:;
    /* $E1EA: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF8; FLAG_NZ(g_cpu.A);
label_E1EC:;
    /* $E1EC: 95 */ maybe_trigger_vblank(4); nes_write((0xD5 + g_cpu.X) & 0xFF, g_cpu.A);
label_E1EE:;
    /* $E1EE: 60 */ maybe_trigger_vblank(6);
    return;
label_E1EF:; /* ClearBounceFlag */
    /* $E1EF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E1F1:;
    /* $E1F1: 95 */ maybe_trigger_vblank(4); nes_write((0x3A + g_cpu.X) & 0xFF, g_cpu.A);
label_E1F3:;
    /* $E1F3: 60 */ maybe_trigger_vblank(6);
    return;
label_E1F4:; /* InitFireballExplode */
    /* $E1F4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_E1F6:;
    /* $E1F6: 95 */ maybe_trigger_vblank(4); nes_write((0x24 + g_cpu.X) & 0xFF, g_cpu.A);
label_E1F8:;
    /* $E1F8: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E1FA:;
    /* $E1FA: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_E1FC:;
    /* $E1FC: 60 */ maybe_trigger_vblank(6);
    return;
label_E1FD:; /* BoundBoxCtrlData */
    /* $E1FD: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E1FE:;
    /* $E1FE: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E1FF:;
    /* $E1FF: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x0320; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E202:;
    /* $E202: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x0D + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E204:;
    /* $E204: 20 */ maybe_trigger_vblank(6); call_by_address(0x1402);
label_E207:;
    /* $E207: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x0220; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E20A:;
    /* $E20A: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x0E; FLAG_NZ(g_cpu.A);
label_E20C:;
    /* $E20C: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x00 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E20E:;
    /* $E20E: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE20E); return;
label_E20F:;
    /* $E20F: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E210:;
    /* $E210: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E212:;
    /* $E212: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE212); return;
label_E213:;
    /* $E213: 20 */ maybe_trigger_vblank(6); call_by_address(0x000D);
label_E216:;
    /* $E216: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE216); return;
label_E217:;
    /* $E217: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_E226;
label_E219:;
    /* $E219: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE219); return;
label_E21A:;
    /* $E21A: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE21A); return;
label_E21B:;
    /* $E21B: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E21C:;
    /* $E21C: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E21D:;
    /* $E21D: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E21F:;
    /* $E21F: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E220:;
    /* $E220: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E221:;
    /* $E221: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E223:;
    /* $E223: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x0014); FLAG_NZ(g_cpu.A);
label_E226:;
    /* $E226: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E227:;
    /* $E227: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { call_by_address(0xE23E); return; }
label_E229:;
    /* $E229: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E22B:;
    /* $E22B: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x8A1C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E22E:;
    /* $E22E: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E22F:;
    /* $E22F: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x07 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x07); g_cpu.A=r&0xFF; }
label_E231:;
    /* $E231: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E232:;
    /* $E232: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_E234:;
    /* $E234: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E23D;
label_E236:; /* GetMiscBoundBox */
    /* $E236: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E237:;
    /* $E237: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E238:;
    /* $E238: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x09 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x09); g_cpu.A=r&0xFF; }
label_E23A:;
    /* $E23A: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E23B:;
    /* $E23B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x06; FLAG_NZ(g_cpu.Y);
label_E23D:; /* FBallB */
    /* $E23D: 20 */ maybe_trigger_vblank(6); call_by_address(0xE29C);
label_E240:;
    /* $E240: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE2DE); return;
label_E243:; /* GetEnemyBoundBox */
    /* $E243: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x48; FLAG_NZ(g_cpu.Y);
label_E245:;
    /* $E245: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_E247:;
    /* $E247: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x44; FLAG_NZ(g_cpu.Y);
label_E249:;
    /* $E249: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE252); return;
label_E24C:; /* SmallPlatformBoundBox */
    /* $E24C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x08; FLAG_NZ(g_cpu.Y);
label_E24E:;
    /* $E24E: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_E250:;
    /* $E250: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x04; FLAG_NZ(g_cpu.Y);
label_E252:; /* GetMaskedOffScrBits */
    /* $E252: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x87 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E254:;
    /* $E254: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_E255:;
    /* $E255: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x071C); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E258:;
    /* $E258: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_E25A:;
    /* $E25A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E25C:;
    /* $E25C: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x071A); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E25F:;
    /* $E25F: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_E267;
label_E261:;
    /* $E261: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x01); FLAG_NZ(g_cpu.A);
label_E263:;
    /* $E263: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E267;
label_E265:;
    /* $E265: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x00); FLAG_NZ(g_cpu.Y);
label_E267:; /* CMBits */
    /* $E267: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_E268:;
    /* $E268: 2D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read(0x03D1); FLAG_NZ(g_cpu.A);
label_E26B:;
    /* $E26B: 9D */ maybe_trigger_vblank(5); nes_write((0x03D8 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_E26E:;
    /* $E26E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E289;
label_E270:;
    /* $E270: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE27C); return;
label_E273:; /* LargePlatformBoundBox */
    /* $E273: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_E274:;
    /* $E274: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1F6);
label_E277:;
    /* $E277: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_E278:;
    /* $E278: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xFE; g_cpu.C=(g_cpu.A>=0xFE)?1:0; FLAG_NZ(r&0xFF); }
label_E27A:;
    /* $E27A: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E289;
label_E27C:; /* SetupEOffsetFBBox */
    /* $E27C: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E27D:;
    /* $E27D: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E27E:;
    /* $E27E: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_E280:;
    /* $E280: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E281:;
    /* $E281: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_E283:;
    /* $E283: 20 */ maybe_trigger_vblank(6); call_by_address(0xE29C);
label_E286:;
    /* $E286: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE2DE); return;
label_E289:; /* MoveBoundBoxOffscreen */
    /* $E289: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E28A:;
    /* $E28A: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E28B:;
    /* $E28B: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E28C:;
    /* $E28C: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_E28D:;
    /* $E28D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_E28F:;
    /* $E28F: 99 */ maybe_trigger_vblank(5); nes_write((0x04B0 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E292:;
    /* $E292: 99 */ maybe_trigger_vblank(5); nes_write((0x04B1 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E295:;
    /* $E295: 99 */ maybe_trigger_vblank(5); nes_write((0x04B2 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E298:;
    /* $E298: 99 */ maybe_trigger_vblank(5); nes_write((0x04B3 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E29B:;
    /* $E29B: 60 */ maybe_trigger_vblank(6);
    return;
label_E29C:; /* BoundingBoxCore */
    /* $E29C: 86 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.X);
label_E29E:;
    /* $E29E: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03B8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E2A1:;
    /* $E2A1: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_E2A3:;
    /* $E2A3: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03AD + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E2A6:;
    /* $E2A6: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_E2A8:;
    /* $E2A8: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E2A9:;
    /* $E2A9: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E2AA:;
    /* $E2AA: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E2AB:;
    /* $E2AB: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E2AC:;
    /* $E2AC: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_E2AD:;
    /* $E2AD: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0499 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E2B0:;
    /* $E2B0: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E2B1:;
    /* $E2B1: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E2B2:;
    /* $E2B2: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E2B3:;
    /* $E2B3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_E2B5:;
    /* $E2B5: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E2B6:;
    /* $E2B6: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE1FD + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E2B9:;
    /* $E2B9: 99 */ maybe_trigger_vblank(5); nes_write((0x04AC + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E2BC:;
    /* $E2BC: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_E2BE:;
    /* $E2BE: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E2BF:;
    /* $E2BF: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE1FF + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E2C2:;
    /* $E2C2: 99 */ maybe_trigger_vblank(5); nes_write((0x04AE + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E2C5:;
    /* $E2C5: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_E2C6:;
    /* $E2C6: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E2C7:;
    /* $E2C7: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_E2C9:;
    /* $E2C9: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E2CA:;
    /* $E2CA: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE1FD + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E2CD:;
    /* $E2CD: 99 */ maybe_trigger_vblank(5); nes_write((0x04AC + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E2D0:;
    /* $E2D0: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_E2D2:;
    /* $E2D2: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E2D3:;
    /* $E2D3: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE1FF + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E2D6:;
    /* $E2D6: 99 */ maybe_trigger_vblank(5); nes_write((0x04AE + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E2D9:;
    /* $E2D9: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E2DA:;
    /* $E2DA: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_E2DB:;
    /* $E2DB: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x00); FLAG_NZ(g_cpu.X);
label_E2DD:;
    /* $E2DD: 60 */ maybe_trigger_vblank(6);
    return;
label_E2DE:; /* CheckRightScreenBBox */
    /* $E2DE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071C); FLAG_NZ(g_cpu.A);
label_E2E1:;
    /* $E2E1: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E2E2:;
    /* $E2E2: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x80 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x80); g_cpu.A=r&0xFF; }
label_E2E4:;
    /* $E2E4: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_E2E6:;
    /* $E2E6: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x071A); FLAG_NZ(g_cpu.A);
label_E2E9:;
    /* $E2E9: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_E2EB:;
    /* $E2EB: 85 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.A);
label_E2ED:;
    /* $E2ED: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x86 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E2EF:;
    /* $E2EF: C5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x02); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E2F1:;
    /* $E2F1: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6D + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E2F3:;
    /* $E2F3: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x01); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E2F5:;
    /* $E2F5: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E30C;
label_E2F7:;
    /* $E2F7: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AE + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E2FA:;
    /* $E2FA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_E309;
label_E2FC:;
    /* $E2FC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_E2FE:;
    /* $E2FE: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0x04AC + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_E301:;
    /* $E301: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_E306;
label_E303:;
    /* $E303: 99 */ maybe_trigger_vblank(5); nes_write((0x04AC + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E306:; /* SORte */
    /* $E306: 99 */ maybe_trigger_vblank(5); nes_write((0x04AE + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E309:; /* NoOfs */
    /* $E309: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E30B:;
    /* $E30B: 60 */ maybe_trigger_vblank(6);
    return;
label_E30C:; /* CheckLeftScreenBBox */
    /* $E30C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AC + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E30F:;
    /* $E30F: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_E322;
label_E311:;
    /* $E311: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xA0; g_cpu.C=(g_cpu.A>=0xA0)?1:0; FLAG_NZ(r&0xFF); }
label_E313:;
    /* $E313: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E322;
label_E315:;
    /* $E315: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E317:;
    /* $E317: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0x04AE + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_E31A:;
    /* $E31A: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_E31F;
label_E31C:;
    /* $E31C: 99 */ maybe_trigger_vblank(5); nes_write((0x04AE + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E31F:; /* SOLft */
    /* $E31F: 99 */ maybe_trigger_vblank(5); nes_write((0x04AC + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E322:; /* NoOfs2 */
    /* $E322: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E324:;
    /* $E324: 60 */ maybe_trigger_vblank(6);
    return;
label_E325:; /* PlayerCollisionCore */
    /* $E325: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_E327:; /* SprObjectCollisionCore */
    /* $E327: 84 */ maybe_trigger_vblank(3); nes_write(0x06, g_cpu.Y);
label_E329:;
    /* $E329: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E32B:;
    /* $E32B: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_E32D:; /* CollisionCoreLoop */
    /* $E32D: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AC + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E330:;
    /* $E330: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E333:;
    /* $E333: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E35F;
label_E335:;
    /* $E335: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AE + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E338:;
    /* $E338: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E34C;
label_E33A:;
    /* $E33A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E37E;
label_E33C:;
    /* $E33C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AE + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E33F:;
    /* $E33F: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E342:;
    /* $E342: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E37E;
label_E344:;
    /* $E344: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E347:;
    /* $E347: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E37E;
label_E349:;
    /* $E349: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x06); FLAG_NZ(g_cpu.Y);
label_E34B:;
    /* $E34B: 60 */ maybe_trigger_vblank(6);
    return;
label_E34C:; /* SecondBoxVerticalChk */
    /* $E34C: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AE + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E34F:;
    /* $E34F: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E352:;
    /* $E352: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E37E;
label_E354:;
    /* $E354: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AE + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E357:;
    /* $E357: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E35A:;
    /* $E35A: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E37E;
label_E35C:;
    /* $E35C: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x06); FLAG_NZ(g_cpu.Y);
label_E35E:;
    /* $E35E: 60 */ maybe_trigger_vblank(6);
    return;
label_E35F:; /* FirstBoxGreater */
    /* $E35F: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E362:;
    /* $E362: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E37E;
label_E364:;
    /* $E364: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AE + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E367:;
    /* $E367: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E37E;
label_E369:;
    /* $E369: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E37E;
label_E36B:;
    /* $E36B: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AE + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E36E:;
    /* $E36E: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E37A;
label_E370:;
    /* $E370: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E37A;
label_E372:;
    /* $E372: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x04AE + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E375:;
    /* $E375: DD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x04AC + g_cpu.X) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E378:;
    /* $E378: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E37E;
label_E37A:; /* NoCollisionFound */
    /* $E37A: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E37B:;
    /* $E37B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x06); FLAG_NZ(g_cpu.Y);
label_E37D:;
    /* $E37D: 60 */ maybe_trigger_vblank(6);
    return;
label_E37E:; /* CollisionFound */
    /* $E37E: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_E37F:;
    /* $E37F: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E380:;
    /* $E380: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x07; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E382:;
    /* $E382: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E32D;
    }
label_E384:;
    /* $E384: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_E385:;
    /* $E385: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x06); FLAG_NZ(g_cpu.Y);
label_E387:;
    /* $E387: 60 */ maybe_trigger_vblank(6);
    return;
label_E388:; /* BlockBufferChk_Enemy */
    /* $E388: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E389:;
    /* $E389: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E38A:;
    /* $E38A: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E38B:;
    /* $E38B: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x01 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x01); g_cpu.A=r&0xFF; }
label_E38D:;
    /* $E38D: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E38E:;
    /* $E38E: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E38F:;
    /* $E38F: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE3A5); return;
label_E392:; /* ResidualMiscObjectCode */
    /* $E392: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E393:;
    /* $E393: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E394:;
    /* $E394: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x0D + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0D); g_cpu.A=r&0xFF; }
label_E396:;
    /* $E396: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E397:;
    /* $E397: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x1B; FLAG_NZ(g_cpu.Y);
label_E399:;
    /* $E399: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE3A3); return;
label_E39C:; /* BlockBufferChk_FBall */
    /* $E39C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x1A; FLAG_NZ(g_cpu.Y);
label_E39E:;
    /* $E39E: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E39F:;
    /* $E39F: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3A0:;
    /* $E3A0: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x07 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x07); g_cpu.A=r&0xFF; }
label_E3A2:;
    /* $E3A2: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E3A3:; /* ResJmpM */
    /* $E3A3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E3A5:; /* BBChk_E */
    /* $E3A5: 20 */ maybe_trigger_vblank(6); call_by_address(0xE3F0);
label_E3A8:;
    /* $E3A8: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E3AA:;
    /* $E3AA: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_E3AC:;
    /* $E3AC: 60 */ maybe_trigger_vblank(6);
    return;
label_E3AD:; /* BlockBufferAdderData */
    /* $E3AD: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE3AD); return;
label_E3AE:;
    /* $E3AE: 07 */ maybe_trigger_vblank(5); /* ILLEGAL $07 — skip 2 */
label_E3B0:; /* BlockBuffer_X_Adder */
    /* $E3B0: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E3B1:;
    /* $E3B1: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E3B3:;
    /* $E3B3: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E3B4:;
    /* $E3B4: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E3B5:;
    /* $E3B5: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x080D); FLAG_NZ(g_cpu.A);
label_E3B8:;
    /* $E3B8: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E3BA:;
    /* $E3BA: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E3BB:;
    /* $E3BB: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E3BC:;
    /* $E3BC: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x080D); FLAG_NZ(g_cpu.A);
label_E3BF:;
    /* $E3BF: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E3C1:;
    /* $E3C1: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E3C2:;
    /* $E3C2: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E3C3:;
    /* $E3C3: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x080D); FLAG_NZ(g_cpu.A);
label_E3C6:;
    /* $E3C6: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE3C6); return;
label_E3C7:;
    /* $E3C7: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_E3CD;
label_E3C9:;
    /* $E3C9: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x04 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E3CB:;
    /* $E3CB: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E3CD:;
    /* $E3CD: 20 */ maybe_trigger_vblank(6); call_by_address(0x0820);
label_E3D0:;
    /* $E3D0: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3D1:;
    /* $E3D1: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E3D2:;
    /* $E3D2: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3D3:;
    /* $E3D3: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E3D4:;
    /* $E3D4: 20 */ maybe_trigger_vblank(6); call_by_address(0x0820);
label_E3D7:;
    /* $E3D7: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3D8:;
    /* $E3D8: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E3D9:;
    /* $E3D9: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3DA:;
    /* $E3DA: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_E3DB:;
    /* $E3DB: 20 */ maybe_trigger_vblank(6); call_by_address(0x1820);
label_E3DE:;
    /* $E3DE: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3DF:;
    /* $E3DF: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3E0:;
    /* $E3E0: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3E1:;
    /* $E3E1: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3E2:;
    /* $E3E2: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x14 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E3E4:;
    /* $E3E4: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x06; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E3E6:;
    /* $E3E6: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E3E7:;
    /* $E3E7: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E3B1;
    }
label_E3E9:; /* BlockBufferColli_Head */
    /* $E3E9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E3EB:;
    /* $E3EB: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x01A9); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_E3EE:;
    /* $E3EE: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_E3F0:; /* BlockBufferCollision */
    /* $E3F0: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E3F1:;
    /* $E3F1: 84 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.Y);
label_E3F3:;
    /* $E3F3: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E3F6:;
    /* $E3F6: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E3F7:;
    /* $E3F7: 75 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x86 + g_cpu.X) & 0xFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E3F9:;
    /* $E3F9: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_E3FB:;
    /* $E3FB: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x6D + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E3FD:;
    /* $E3FD: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_E3FF:;
    /* $E3FF: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_E401:;
    /* $E401: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E402:;
    /* $E402: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x05); FLAG_NZ(g_cpu.A);
label_E404:;
    /* $E404: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_E405:;
    /* $E405: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E406:;
    /* $E406: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E407:;
    /* $E407: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E408:;
    /* $E408: 20 */ maybe_trigger_vblank(6); call_by_address(0x9BE1);
label_E40B:;
    /* $E40B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x04); FLAG_NZ(g_cpu.Y);
label_E40D:;
    /* $E40D: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCE + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E40F:;
    /* $E40F: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E410:;
    /* $E410: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE3CC + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E413:;
    /* $E413: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF0; FLAG_NZ(g_cpu.A);
label_E415:;
    /* $E415: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_E416:;
    /* $E416: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x20; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E418:;
    /* $E418: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_E41A:;
    /* $E41A: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_E41B:;
    /* $E41B: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0x06) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E41D:;
    /* $E41D: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_E41F:;
    /* $E41F: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x04); FLAG_NZ(g_cpu.Y);
label_E421:;
    /* $E421: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E422:;
    /* $E422: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E429;
label_E424:;
    /* $E424: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCE + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E426:;
    /* $E426: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE42B); return;
label_E429:; /* RetXC */
    /* $E429: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x86 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E42B:; /* RetYC */
    /* $E42B: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0F; FLAG_NZ(g_cpu.A);
label_E42D:;
    /* $E42D: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_E42F:;
    /* $E42F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x03); FLAG_NZ(g_cpu.A);
label_E431:;
    /* $E431: 60 */ maybe_trigger_vblank(6);
    return;
label_E432:;
    /* $E432: FF */ maybe_trigger_vblank(7); /* ILLEGAL $FF — skip 3 */
label_E435:; /* DrawVine */
    /* $E435: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_E437:;
    /* $E437: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B9); FLAG_NZ(g_cpu.A);
label_E43A:;
    /* $E43A: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E43B:;
    /* $E43B: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE433 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E43E:;
    /* $E43E: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0x039A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_E441:;
    /* $E441: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E444:;
    /* $E444: 84 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.Y);
label_E446:;
    /* $E446: 20 */ maybe_trigger_vblank(6); call_by_address(0xE4AE);
label_E449:;
    /* $E449: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_E44C:;
    /* $E44C: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E44F:;
    /* $E44F: 99 */ maybe_trigger_vblank(5); nes_write((0x020B + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E452:;
    /* $E452: 99 */ maybe_trigger_vblank(5); nes_write((0x0213 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E455:;
    /* $E455: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E456:;
    /* $E456: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x06 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x06); g_cpu.A=r&0xFF; }
label_E458:;
    /* $E458: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E45B:;
    /* $E45B: 99 */ maybe_trigger_vblank(5); nes_write((0x020F + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E45E:;
    /* $E45E: 99 */ maybe_trigger_vblank(5); nes_write((0x0217 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E461:;
    /* $E461: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x21; FLAG_NZ(g_cpu.A);
label_E463:;
    /* $E463: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E466:;
    /* $E466: 99 */ maybe_trigger_vblank(5); nes_write((0x020A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E469:;
    /* $E469: 99 */ maybe_trigger_vblank(5); nes_write((0x0212 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E46C:;
    /* $E46C: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_E46E:;
    /* $E46E: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E471:;
    /* $E471: 99 */ maybe_trigger_vblank(5); nes_write((0x020E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E474:;
    /* $E474: 99 */ maybe_trigger_vblank(5); nes_write((0x0216 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E477:;
    /* $E477: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x05; FLAG_NZ(g_cpu.X);
label_E479:; /* VineTL */
    /* $E479: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xE1; FLAG_NZ(g_cpu.A);
label_E47B:;
    /* $E47B: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E47E:;
    /* $E47E: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E47F:;
    /* $E47F: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E480:;
    /* $E480: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E481:;
    /* $E481: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E482:;
    /* $E482: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_E483:;
    /* $E483: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E479;
    }
label_E485:;
    /* $E485: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x02); FLAG_NZ(g_cpu.Y);
label_E487:;
    /* $E487: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_E489:;
    /* $E489: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E490;
label_E48B:;
    /* $E48B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xE0; FLAG_NZ(g_cpu.A);
label_E48D:;
    /* $E48D: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E490:; /* SkpVTop */
    /* $E490: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_E492:; /* ChkFTop */
    /* $E492: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x039D); FLAG_NZ(g_cpu.A);
label_E495:;
    /* $E495: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_E496:;
    /* $E496: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x0200 + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E499:;
    /* $E499: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x64; g_cpu.C=(g_cpu.A>=0x64)?1:0; FLAG_NZ(r&0xFF); }
label_E49B:;
    /* $E49B: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E4A2;
label_E49D:;
    /* $E49D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E49F:;
    /* $E49F: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E4A2:; /* NextVSp */
    /* $E4A2: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4A3:;
    /* $E4A3: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4A4:;
    /* $E4A4: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4A5:;
    /* $E4A5: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4A6:;
    /* $E4A6: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_E4A7:;
    /* $E4A7: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x06; g_cpu.C=(g_cpu.X>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_E4A9:;
    /* $E4A9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E492;
    }
label_E4AB:;
    /* $E4AB: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x00); FLAG_NZ(g_cpu.Y);
label_E4AD:;
    /* $E4AD: 60 */ maybe_trigger_vblank(6);
    return;
label_E4AE:; /* SixSpriteStacker */
    /* $E4AE: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x06; FLAG_NZ(g_cpu.X);
label_E4B0:; /* StkLp */
    /* $E4B0: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E4B3:;
    /* $E4B3: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E4B4:;
    /* $E4B4: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_E4B6:;
    /* $E4B6: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4B7:;
    /* $E4B7: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4B8:;
    /* $E4B8: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4B9:;
    /* $E4B9: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E4BA:;
    /* $E4BA: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_E4BB:;
    /* $E4BB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E4B0;
    }
label_E4BD:;
    /* $E4BD: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x02); FLAG_NZ(g_cpu.Y);
label_E4BF:;
    /* $E4BF: 60 */ maybe_trigger_vblank(6);
    return;
label_E4C0:; /* FirstSprXPos */
    /* $E4C0: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E4C2:;
    /* $E4C2: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E4C4:; /* FirstSprYPos */
    /* $E4C4: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE4C4); return;
label_E4C5:;
    /* $E4C5: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E4C7:;
    /* $E4C7: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E4C9:;
    /* $E4C9: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E4CA:;
    /* $E4CA: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE4CA); return;
label_E4CB:;
    /* $E4CB: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E4CC:; /* SecondSprYPos */
    /* $E4CC: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E4CD:;
    /* $E4CD: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE4CD); return;
label_E4CE:;
    /* $E4CE: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E4CF:;
    /* $E4CF: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE4CF); return;
label_E4D0:; /* FirstSprTilenum */
    /* $E4D0: 80 */ maybe_trigger_vblank(2); /* NOP */
label_E4D2:;
    /* $E4D2: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x83 + g_cpu.X) & 0xFF), g_cpu.A);
label_E4D4:; /* SecondSprTilenum */
    /* $E4D4: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x83 + g_cpu.X) & 0xFF), g_cpu.A);
label_E4D6:;
    /* $E4D6: 80 */ maybe_trigger_vblank(2); /* NOP */
label_E4D8:; /* HammerSprAttrib */
    /* $E4D8: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E4DA:;
    /* $E4DA: C3 */ maybe_trigger_vblank(8); /* ILLEGAL $C3 — skip 2 */
label_E4DC:; /* DrawHammer */
    /* $E4DC: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06F3 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E4DF:;
    /* $E4DF: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x0747); FLAG_NZ(g_cpu.A);
label_E4E2:;
    /* $E4E2: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E4EC;
label_E4E4:;
    /* $E4E4: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x2A + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E4E6:;
    /* $E4E6: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x7F; FLAG_NZ(g_cpu.A);
label_E4E8:;
    /* $E4E8: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_E4EA:;
    /* $E4EA: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E4F0;
label_E4EC:; /* ForceHPose */
    /* $E4EC: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_E4EE:;
    /* $E4EE: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E4F7;
label_E4F0:; /* GetHPose */
    /* $E4F0: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_E4F2:;
    /* $E4F2: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E4F3:;
    /* $E4F3: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E4F4:;
    /* $E4F4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_E4F6:;
    /* $E4F6: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E4F7:; /* RenderH */
    /* $E4F7: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03BE); FLAG_NZ(g_cpu.A);
label_E4FA:;
    /* $E4FA: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E4FB:;
    /* $E4FB: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE4C4 + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E4FE:;
    /* $E4FE: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E501:;
    /* $E501: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E502:;
    /* $E502: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE4CC + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E505:;
    /* $E505: 99 */ maybe_trigger_vblank(5); nes_write((0x0204 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E508:;
    /* $E508: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B3); FLAG_NZ(g_cpu.A);
label_E50B:;
    /* $E50B: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E50C:;
    /* $E50C: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE4C0 + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E50F:;
    /* $E50F: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E512:;
    /* $E512: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E513:;
    /* $E513: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE4C8 + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E516:;
    /* $E516: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E519:;
    /* $E519: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE4D0 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E51C:;
    /* $E51C: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E51F:;
    /* $E51F: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE4D4 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E522:;
    /* $E522: 99 */ maybe_trigger_vblank(5); nes_write((0x0205 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E525:;
    /* $E525: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE4D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E528:;
    /* $E528: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E52B:;
    /* $E52B: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E52E:;
    /* $E52E: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E530:;
    /* $E530: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D6); FLAG_NZ(g_cpu.A);
label_E533:;
    /* $E533: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xFC; FLAG_NZ(g_cpu.A);
label_E535:;
    /* $E535: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E540;
label_E537:;
    /* $E537: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E539:;
    /* $E539: 95 */ maybe_trigger_vblank(4); nes_write((0x2A + g_cpu.X) & 0xFF, g_cpu.A);
label_E53B:;
    /* $E53B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E53D:;
    /* $E53D: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5C1);
label_E540:; /* NoHOffscr */
    /* $E540: 60 */ maybe_trigger_vblank(6);
    return;
label_E541:; /* FlagpoleScoreNumTiles */
    /* $E541: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xF750 + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E544:;
    /* $E544: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E540;
    }
label_E546:;
    /* $E546: FB */ maybe_trigger_vblank(7); /* ILLEGAL $FB — skip 3 */
label_E549:;
    /* $E549: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0xFB + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E54B:; /* FlagpoleGfxHandler */
    /* $E54B: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E54E:;
    /* $E54E: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_E551:;
    /* $E551: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E554:;
    /* $E554: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E555:;
    /* $E555: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_E557:;
    /* $E557: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E55A:;
    /* $E55A: 99 */ maybe_trigger_vblank(5); nes_write((0x020B + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E55D:;
    /* $E55D: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E55E:;
    /* $E55E: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x0C + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0C); g_cpu.A=r&0xFF; }
label_E560:;
    /* $E560: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_E562:;
    /* $E562: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E564:;
    /* $E564: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5C1);
label_E567:;
    /* $E567: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_E569:;
    /* $E569: 99 */ maybe_trigger_vblank(5); nes_write((0x0208 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E56C:;
    /* $E56C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x010D); FLAG_NZ(g_cpu.A);
label_E56F:;
    /* $E56F: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_E571:;
    /* $E571: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E573:;
    /* $E573: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_E575:;
    /* $E575: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_E577:;
    /* $E577: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E57A:;
    /* $E57A: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E57D:;
    /* $E57D: 99 */ maybe_trigger_vblank(5); nes_write((0x020A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E580:;
    /* $E580: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x7E; FLAG_NZ(g_cpu.A);
label_E582:;
    /* $E582: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E585:;
    /* $E585: 99 */ maybe_trigger_vblank(5); nes_write((0x0209 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E588:;
    /* $E588: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x7F; FLAG_NZ(g_cpu.A);
label_E58A:;
    /* $E58A: 99 */ maybe_trigger_vblank(5); nes_write((0x0205 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E58D:;
    /* $E58D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x070F); FLAG_NZ(g_cpu.A);
label_E590:;
    /* $E590: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E5A7;
label_E592:;
    /* $E592: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_E593:;
    /* $E593: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E594:;
    /* $E594: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x0C + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x0C); g_cpu.A=r&0xFF; }
label_E596:;
    /* $E596: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_E597:;
    /* $E597: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x010F); FLAG_NZ(g_cpu.A);
label_E59A:;
    /* $E59A: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E59B:;
    /* $E59B: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E59C:;
    /* $E59C: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE541 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E59F:;
    /* $E59F: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_E5A1:;
    /* $E5A1: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE542 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E5A4:;
    /* $E5A4: 20 */ maybe_trigger_vblank(6); call_by_address(0xEBB2);
label_E5A7:; /* ChkFlagOffscreen */
    /* $E5A7: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E5A9:;
    /* $E5A9: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E5AC:;
    /* $E5AC: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D1); FLAG_NZ(g_cpu.A);
label_E5AF:;
    /* $E5AF: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0E; FLAG_NZ(g_cpu.A);
label_E5B1:;
    /* $E5B1: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E5C7;
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
label_E5C8:; /* DrawLargePlatform */
    /* $E5C8: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E5CB:;
    /* $E5CB: 84 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.Y);
label_E5CD:;
    /* $E5CD: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E5CE:;
    /* $E5CE: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E5CF:;
    /* $E5CF: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E5D0:;
    /* $E5D0: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_E5D3:;
    /* $E5D3: 20 */ maybe_trigger_vblank(6); call_by_address(0xE4AE);
label_E5D6:;
    /* $E5D6: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E5D8:;
    /* $E5D8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E5DA:;
    /* $E5DA: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5BB);
label_E5DD:;
    /* $E5DD: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_E5E0:;
    /* $E5E0: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x03; g_cpu.C=(g_cpu.Y>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_E5E2:;
    /* $E5E2: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E5E9;
label_E5E4:;
    /* $E5E4: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06CC); FLAG_NZ(g_cpu.Y);
label_E5E7:;
    /* $E5E7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E5EB;
label_E5E9:; /* ShrinkPlatform */
    /* $E5E9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E5EB:; /* SetLast2Platform */
    /* $E5EB: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E5EE:;
    /* $E5EE: 99 */ maybe_trigger_vblank(5); nes_write((0x0210 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E5F1:;
    /* $E5F1: 99 */ maybe_trigger_vblank(5); nes_write((0x0214 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E5F4:;
    /* $E5F4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x5B; FLAG_NZ(g_cpu.A);
label_E5F6:;
    /* $E5F6: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x0743); FLAG_NZ(g_cpu.X);
label_E5F9:;
    /* $E5F9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E5FD;
label_E5FB:;
    /* $E5FB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x75; FLAG_NZ(g_cpu.A);
label_E5FD:; /* SetPlatformTilenum */
    /* $E5FD: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E5FF:;
    /* $E5FF: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E600:;
    /* $E600: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5B5);
label_E603:;
    /* $E603: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E605:;
    /* $E605: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E606:;
    /* $E606: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5B5);
label_E609:;
    /* $E609: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_E60A:;
    /* $E60A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF1F6);
label_E60D:;
    /* $E60D: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_E60E:;
    /* $E60E: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x06E5 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E611:;
    /* $E611: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E612:;
    /* $E612: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E613:;
    /* $E613: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E61A;
label_E615:;
    /* $E615: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E617:;
    /* $E617: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E61A:; /* SChk2 */
    /* $E61A: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E61B:;
    /* $E61B: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E61C:;
    /* $E61C: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E61D:;
    /* $E61D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E624;
label_E61F:;
    /* $E61F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E621:;
    /* $E621: 99 */ maybe_trigger_vblank(5); nes_write((0x0204 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E624:; /* SChk3 */
    /* $E624: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E625:;
    /* $E625: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E626:;
    /* $E626: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E627:;
    /* $E627: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E62E;
label_E629:;
    /* $E629: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E62B:;
    /* $E62B: 99 */ maybe_trigger_vblank(5); nes_write((0x0208 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E62E:; /* SChk4 */
    /* $E62E: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E62F:;
    /* $E62F: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E630:;
    /* $E630: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E631:;
    /* $E631: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E638;
label_E633:;
    /* $E633: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E635:;
    /* $E635: 99 */ maybe_trigger_vblank(5); nes_write((0x020C + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E638:; /* SChk5 */
    /* $E638: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E639:;
    /* $E639: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E63A:;
    /* $E63A: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E63B:;
    /* $E63B: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E642;
label_E63D:;
    /* $E63D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E63F:;
    /* $E63F: 99 */ maybe_trigger_vblank(5); nes_write((0x0210 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E642:; /* SChk6 */
    /* $E642: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E643:;
    /* $E643: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E644:;
    /* $E644: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E64B;
label_E646:;
    /* $E646: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF8; FLAG_NZ(g_cpu.A);
label_E648:;
    /* $E648: 99 */ maybe_trigger_vblank(5); nes_write((0x0214 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E64B:; /* SLChk */
    /* $E64B: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03D1); FLAG_NZ(g_cpu.A);
label_E64E:;
    /* $E64E: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E64F:;
    /* $E64F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E654;
label_E651:;
    /* $E651: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5B3);
label_E654:; /* ExDLPl */
    /* $E654: 60 */ maybe_trigger_vblank(6);
    return;
label_E655:; /* DrawFloateyNumber_Coin */
    /* $E655: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_E657:;
    /* $E657: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E658:;
    /* $E658: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E65C;
label_E65A:;
    /* $E65A: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0xDB + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E65C:; /* NotRsNum */
    /* $E65C: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xDB + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E65E:;
    /* $E65E: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5C1);
label_E661:;
    /* $E661: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B3); FLAG_NZ(g_cpu.A);
label_E664:;
    /* $E664: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E667:;
    /* $E667: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E668:;
    /* $E668: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_E66A:;
    /* $E66A: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E66D:;
    /* $E66D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E66F:;
    /* $E66F: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E672:;
    /* $E672: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E675:;
    /* $E675: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF7; FLAG_NZ(g_cpu.A);
label_E677:;
    /* $E677: 99 */ maybe_trigger_vblank(5); nes_write((0x0201 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E67A:;
    /* $E67A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFB; FLAG_NZ(g_cpu.A);
label_E67C:;
    /* $E67C: 99 */ maybe_trigger_vblank(5); nes_write((0x0205 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E67F:;
    /* $E67F: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE6BD); return;
label_E682:; /* JumpingCoinTiles */
    /* $E682: 60 */ maybe_trigger_vblank(6);
    return;
label_E683:;
    /* $E683: 61 */ maybe_trigger_vblank(6); { uint8_t m=nes_read(nes_read16zp((0x62 + g_cpu.X) & 0xFF)); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E685:;
    /* $E685: 63 */ maybe_trigger_vblank(8); /* ILLEGAL $63 — skip 2 */
label_E687:;
    /* $E687: F3 */ maybe_trigger_vblank(8); /* ILLEGAL $F3 — skip 2 */
label_E689:;
    /* $E689: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x2A + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E68B:;
    /* $E68B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_E68D:;
    /* $E68D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E655;
    }
label_E68F:;
    /* $E68F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xDB + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E691:;
    /* $E691: 99 */ maybe_trigger_vblank(5); nes_write((0x0200 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E694:;
    /* $E694: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E695:;
    /* $E695: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_E697:;
    /* $E697: 99 */ maybe_trigger_vblank(5); nes_write((0x0204 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E69A:;
    /* $E69A: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03B3); FLAG_NZ(g_cpu.A);
label_E69D:;
    /* $E69D: 99 */ maybe_trigger_vblank(5); nes_write((0x0203 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E6A0:;
    /* $E6A0: 99 */ maybe_trigger_vblank(5); nes_write((0x0207 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E6A3:;
    /* $E6A3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_E6A5:;
    /* $E6A5: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E6A6:;
    /* $E6A6: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_E6A8:;
    /* $E6A8: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E6A9:;
    /* $E6A9: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE682 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E6AC:;
    /* $E6AC: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E6AD:;
    /* $E6AD: 20 */ maybe_trigger_vblank(6); call_by_address(0xE5C1);
label_E6B0:;
    /* $E6B0: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E6B1:;
    /* $E6B1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E6B3:;
    /* $E6B3: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E6B6:;
    /* $E6B6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x82; FLAG_NZ(g_cpu.A);
label_E6B8:;
    /* $E6B8: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E6BB:;
    /* $E6BB: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_E6BD:; /* ExJCGfx */
    /* $E6BD: 60 */ maybe_trigger_vblank(6);
    return;
label_E6BE:; /* PowerUpGfxTable */
    /* $E6BE: 76 */ maybe_trigger_vblank(6); { uint16_t a=(0x77 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E6C0:;
    /* $E6C0: 78 */ maybe_trigger_vblank(2); g_cpu.I = 1;
label_E6C1:;
    /* $E6C1: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xD6D6 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E6C4:;
    /* $E6C4: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x8DD9 + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E6C7:;
    /* $E6C7: 8D */ maybe_trigger_vblank(4); nes_write(0xE4E4, g_cpu.A);
label_E6CA:;
    /* $E6CA: 76 */ maybe_trigger_vblank(6); { uint16_t a=(0x77 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E6CC:;
    /* $E6CC: 78 */ maybe_trigger_vblank(2); g_cpu.I = 1;
label_E6CD:;
    /* $E6CD: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x0102 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E6D0:;
    /* $E6D0: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E6D1:;
    /* $E6D1: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0xAC + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_E6D3:;
    /* $E6D3: EA */ maybe_trigger_vblank(2); /* NOP */
label_E6D4:;
    /* $E6D4: 06 */ maybe_trigger_vblank(5); { uint16_t a=0xAD; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E6D6:;
    /* $E6D6: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1803 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E6D9:;
    /* $E6D9: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x08 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x08); g_cpu.A=r&0xFF; }
label_E6DB:;
    /* $E6DB: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_E6DD:;
    /* $E6DD: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x03AE); FLAG_NZ(g_cpu.A);
label_E6E0:;
    /* $E6E0: 85 */ maybe_trigger_vblank(3); nes_write(0x05, g_cpu.A);
label_E6E2:;
    /* $E6E2: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x39); FLAG_NZ(g_cpu.X);
label_E6E4:;
    /* $E6E4: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE6CE + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E6E7:;
    /* $E6E7: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x03CA); FLAG_NZ(g_cpu.A);
label_E6EA:;
    /* $E6EA: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_E6EC:;
    /* $E6EC: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_E6ED:;
    /* $E6ED: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E6EE:;
    /* $E6EE: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E6EF:;
    /* $E6EF: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E6F0:;
    /* $E6F0: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_E6F1:;
    /* $E6F1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E6F3:;
    /* $E6F3: 85 */ maybe_trigger_vblank(3); nes_write(0x07, g_cpu.A);
label_E6F5:;
    /* $E6F5: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_E6F7:; /* PUpDrawLoop */
    /* $E6F7: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE6BE + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E6FA:;
    /* $E6FA: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_E6FC:;
    /* $E6FC: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xE6BF + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E6FF:;
    /* $E6FF: 20 */ maybe_trigger_vblank(6); call_by_address(0xEBB2);
label_E702:;
    /* $E702: C6 */ maybe_trigger_vblank(5); { uint16_t a=0x07; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E704:;
    /* $E704: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E6F7;
    }
label_E706:;
    /* $E706: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x06EA); FLAG_NZ(g_cpu.Y);
label_E709:;
    /* $E709: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_E70A:;
    /* $E70A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E73B;
label_E70C:;
    /* $E70C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_E70E:;
    /* $E70E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E73B;
label_E710:;
    /* $E710: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_E712:;
    /* $E712: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_E714:;
    /* $E714: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_E715:;
    /* $E715: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_E717:;
    /* $E717: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x03CA); FLAG_NZ(g_cpu.A);
label_E71A:;
    /* $E71A: 99 */ maybe_trigger_vblank(5); nes_write((0x0202 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E71D:;
    /* $E71D: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E720:;
    /* $E720: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x00); FLAG_NZ(g_cpu.X);
label_E722:;
    /* $E722: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_E723:;
    /* $E723: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E72B;
label_E725:;
    /* $E725: 99 */ maybe_trigger_vblank(5); nes_write((0x020A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E728:;
    /* $E728: 99 */ maybe_trigger_vblank(5); nes_write((0x020E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E72B:; /* FlipPUpRightSide */
    /* $E72B: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0206 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E72E:;
    /* $E72E: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_E730:;
    /* $E730: 99 */ maybe_trigger_vblank(5); nes_write((0x0206 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E733:;
    /* $E733: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x020E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E736:;
    /* $E736: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_E738:;
    /* $E738: 99 */ maybe_trigger_vblank(5); nes_write((0x020E + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E73B:; /* PUpOfs */
    /* $E73B: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xEB64); return;
label_E73E:; /* EnemyGraphicsTable */
    /* $E73E: FC */ maybe_trigger_vblank(4); (void)nes_read((0xAAFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E741:;
    /* $E741: AB */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X = 0xAC; FLAG_NZ(g_cpu.A);
label_E743:;
    /* $E743: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0xFCFC); FLAG_NZ(g_cpu.A);
label_E746:;
    /* $E746: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0xB0AF); FLAG_NZ(g_cpu.X);
label_E749:;
    /* $E749: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xFC) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E74B:;
    /* $E74B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xA6); FLAG_NZ(g_cpu.A);
label_E74D:;
    /* $E74D: A7 */ maybe_trigger_vblank(3); g_cpu.A = g_cpu.X = nes_read(0xA8); FLAG_NZ(g_cpu.A);
label_E74F:;
    /* $E74F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFC; FLAG_NZ(g_cpu.A);
label_E751:;
    /* $E751: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xA1; FLAG_NZ(g_cpu.Y);
label_E753:;
    /* $E753: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xA3; FLAG_NZ(g_cpu.X);
label_E755:;
    /* $E755: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x69); FLAG_NZ(g_cpu.Y);
label_E757:;
    /* $E757: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x6A); FLAG_NZ(g_cpu.A);
label_E759:;
    /* $E759: A7 */ maybe_trigger_vblank(3); g_cpu.A = g_cpu.X = nes_read(0xA8); FLAG_NZ(g_cpu.A);
label_E75B:;
    /* $E75B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x6B; FLAG_NZ(g_cpu.A);
label_E75D:;
    /* $E75D: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x6C; FLAG_NZ(g_cpu.Y);
label_E75F:;
    /* $E75F: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xA3; FLAG_NZ(g_cpu.X);
label_E761:;
    /* $E761: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFC); FLAG_NZ(g_cpu.Y);
label_E763:;
    /* $E763: FC */ maybe_trigger_vblank(4); (void)nes_read((0x9796 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E766:;
    /* $E766: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_E767:;
    /* $E767: 99 */ maybe_trigger_vblank(5); nes_write((0xFCFC + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E76A:;
    /* $E76A: 9A */ maybe_trigger_vblank(2); g_cpu.S = g_cpu.X;
label_E76B:;
    /* $E76B: 9B */ maybe_trigger_vblank(5); /* ILLEGAL $9B — skip 3 */
label_E76E:;
    /* $E76E: FC */ maybe_trigger_vblank(4); (void)nes_read((0x8FFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E771:;
    /* $E771: 8E */ maybe_trigger_vblank(4); nes_write(0x8F8E, g_cpu.X);
label_E774:;
    /* $E774: FC */ maybe_trigger_vblank(4); (void)nes_read((0x95FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E777:;
    /* $E777: 94 */ maybe_trigger_vblank(4); nes_write((0x94 + g_cpu.X) & 0xFF, g_cpu.Y);
label_E779:;
    /* $E779: 95 */ maybe_trigger_vblank(4); nes_write((0xFC + g_cpu.X) & 0xFF, g_cpu.A);
label_E77B:;
    /* $E77B: FC */ maybe_trigger_vblank(4); (void)nes_read((0xDCDC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E77E:;
    /* $E77E: DF */ maybe_trigger_vblank(7); /* ILLEGAL $DF — skip 3 */
label_E781:;
    /* $E781: DC */ maybe_trigger_vblank(4); (void)nes_read((0xDDDD + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E784:;
    /* $E784: DE */ maybe_trigger_vblank(7); { uint16_t a=(0xFCDE + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E787:;
    /* $E787: FC */ maybe_trigger_vblank(4); (void)nes_read((0xB3B2 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E78A:;
    /* $E78A: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0xB5 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_E78C:;
    /* $E78C: FC */ maybe_trigger_vblank(4); (void)nes_read((0xB6FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E78F:;
    /* $E78F: B3 */ maybe_trigger_vblank(5); g_cpu.A = g_cpu.X = nes_read((nes_read16zp(0xB7) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E791:;
    /* $E791: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFC + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E793:;
    /* $E793: FC */ maybe_trigger_vblank(4); (void)nes_read((0x7170 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E796:;
    /* $E796: 72 */ maybe_trigger_vblank(2); /* ILLEGAL $72 — skip 1 */
label_E797:;
    /* $E797: 73 */ maybe_trigger_vblank(8); /* ILLEGAL $73 — skip 2 */
label_E799:;
    /* $E799: FC */ maybe_trigger_vblank(4); (void)nes_read((0x6E6E + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E79C:;
    /* $E79C: 6F */ maybe_trigger_vblank(6); /* ILLEGAL $6F — skip 3 */
label_E79F:;
    /* $E79F: FC */ maybe_trigger_vblank(4); (void)nes_read((0x6D6D + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7A2:;
    /* $E7A2: 6F */ maybe_trigger_vblank(6); /* ILLEGAL $6F — skip 3 */
label_E7A5:;
    /* $E7A5: FC */ maybe_trigger_vblank(4); (void)nes_read((0x6F6F + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7A8:;
    /* $E7A8: 6E */ maybe_trigger_vblank(6); { uint16_t a=0xFC6E; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E7AB:;
    /* $E7AB: FC */ maybe_trigger_vblank(4); (void)nes_read((0x6F6F + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7AE:;
    /* $E7AE: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xFC6D); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7B1:;
    /* $E7B1: FC */ maybe_trigger_vblank(4); (void)nes_read((0xF4F4 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7B4:;
    /* $E7B4: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xF5 + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7B6:;
    /* $E7B6: FC */ maybe_trigger_vblank(4); (void)nes_read((0xF4FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7B9:;
    /* $E7B9: F4 */ maybe_trigger_vblank(4); (void)nes_read((0xF5 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7BB:;
    /* $E7BB: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xFC + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7BD:;
    /* $E7BD: FC */ maybe_trigger_vblank(4); (void)nes_read((0xF5F5 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7C0:;
    /* $E7C0: F4 */ maybe_trigger_vblank(4); (void)nes_read((0xF4 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7C2:;
    /* $E7C2: FC */ maybe_trigger_vblank(4); (void)nes_read((0xF5FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7C5:;
    /* $E7C5: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xF4 + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7C7:;
    /* $E7C7: F4 */ maybe_trigger_vblank(4); (void)nes_read((0xFC + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7C9:;
    /* $E7C9: FC */ maybe_trigger_vblank(4); (void)nes_read((0xFCFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7CC:;
    /* $E7CC: EF */ maybe_trigger_vblank(6); /* ILLEGAL $EF — skip 3 */
label_E7CF:;
    /* $E7CF: B8 */ maybe_trigger_vblank(2); g_cpu.V = 0;
label_E7D0:;
    /* $E7D0: BB */ maybe_trigger_vblank(4); /* ILLEGAL $BB — skip 3 */
label_E7D3:;
    /* $E7D3: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0xFCFC + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E7D6:;
    /* $E7D6: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xBCBD + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E7D9:;
    /* $E7D9: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x7B7A + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E7DC:;
    /* $E7DC: DA */ maybe_trigger_vblank(2); /* NOP */
label_E7DD:;
    /* $E7DD: DB */ maybe_trigger_vblank(7); /* ILLEGAL $DB — skip 3 */
label_E7E0:;
    /* $E7E0: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xCECD); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E7E3:;
    /* $E7E3: CE */ maybe_trigger_vblank(6); { uint16_t a=0xCFCF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E7E6:;
    /* $E7E6: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xD17C + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7E9:;
    /* $E7E9: 8C */ maybe_trigger_vblank(4); nes_write(0xD2D3, g_cpu.Y);
label_E7EC:;
    /* $E7EC: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x897C + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7EF:;
    /* $E7EF: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E7F0:;
    /* $E7F0: 8B */ maybe_trigger_vblank(2); /* ILLEGAL $8B — skip 2 */
label_E7F2:;
    /* $E7F2: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xD4 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E7F4:;
    /* $E7F4: E3 */ maybe_trigger_vblank(8); /* ILLEGAL $E3 — skip 2 */
label_E7F6:;
    /* $E7F6: D3 */ maybe_trigger_vblank(8); /* ILLEGAL $D3 — skip 2 */
label_E7F8:;
    /* $E7F8: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xD4 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E7FA:;
    /* $E7FA: E3 */ maybe_trigger_vblank(8); /* ILLEGAL $E3 — skip 2 */
label_E7FC:;
    /* $E7FC: 8B */ maybe_trigger_vblank(2); /* ILLEGAL $8B — skip 2 */
label_E7FE:;
    /* $E7FE: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xE5); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E800:;
    /* $E800: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xE6; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E802:;
    /* $E802: EB */ maybe_trigger_vblank(2); { uint8_t m=0xEB; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E804:;
    /* $E804: EC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xEDEC); int r=g_cpu.X-m; g_cpu.C=(g_cpu.X>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E807:;
    /* $E807: ED */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xEEEE); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E80A:;
    /* $E80A: FC */ maybe_trigger_vblank(4); (void)nes_read((0xD0FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E80D:;
    /* $E80D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E7E6;
    }
label_E80F:;
    /* $E80F: D7 */ maybe_trigger_vblank(6); /* ILLEGAL $D7 — skip 2 */
label_E811:;
    /* $E811: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xC0C1 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_E814:;
    /* $E814: C2 */ maybe_trigger_vblank(2); /* NOP */
label_E816:;
    /* $E816: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xC3); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E818:;
    /* $E818: C6 */ maybe_trigger_vblank(5); { uint16_t a=0xC5; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E81A:;
    /* $E81A: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E81B:;
    /* $E81B: C7 */ maybe_trigger_vblank(5); /* ILLEGAL $C7 — skip 2 */
label_E81D:;
    /* $E81D: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xC9CA + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_E820:;
    /* $E820: C2 */ maybe_trigger_vblank(2); /* NOP */
label_E822:;
    /* $E822: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xC3); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E824:;
    /* $E824: C6 */ maybe_trigger_vblank(5); { uint16_t a=0xC5; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E826:;
    /* $E826: CC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xFCCB); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E829:;
    /* $E829: FC */ maybe_trigger_vblank(4); (void)nes_read((0xE7E8 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E82C:;
    /* $E82C: EA */ maybe_trigger_vblank(2); /* NOP */
label_E82D:;
    /* $E82D: E9 */ maybe_trigger_vblank(2); { uint8_t m=0xF2; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E82F:;
    /* $E82F: F2 */ maybe_trigger_vblank(2); /* ILLEGAL $F2 — skip 1 */
label_E830:;
    /* $E830: F3 */ maybe_trigger_vblank(8); /* ILLEGAL $F3 — skip 2 */
label_E832:;
    /* $E832: F2 */ maybe_trigger_vblank(2); /* ILLEGAL $F2 — skip 1 */
label_E833:;
    /* $E833: F2 */ maybe_trigger_vblank(2); /* ILLEGAL $F2 — skip 1 */
label_E834:;
    /* $E834: F1 */ maybe_trigger_vblank(5); { uint8_t m=nes_read((nes_read16zp(0xF1) + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E836:;
    /* $E836: F1 */ maybe_trigger_vblank(5); { uint8_t m=nes_read((nes_read16zp(0xF1) + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E838:;
    /* $E838: FC */ maybe_trigger_vblank(4); (void)nes_read((0xF0FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E83B:;
    /* $E83B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { call_by_address(0xE839); return; }
label_E83D:;
    /* $E83D: FC */ maybe_trigger_vblank(4); (void)nes_read((0xFCFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E840:; /* EnemyGfxTableOffsets */
    /* $E840: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x000C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E843:;
    /* $E843: 0C */ maybe_trigger_vblank(4); (void)nes_read(0xA80C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E846:;
    /* $E846: 54 */ maybe_trigger_vblank(4); (void)nes_read((0x3C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E848:;
    /* $E848: EA */ maybe_trigger_vblank(2); /* NOP */
label_E849:;
    /* $E849: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E84A:;
    /* $E84A: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E84B:;
    /* $E84B: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E84C:;
    /* $E84C: CC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x18C0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E84F:;
    /* $E84F: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E850:;
    /* $E850: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E851:;
    /* $E851: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E877;
label_E853:;
    /* $E853: FF */ maybe_trigger_vblank(7); /* ILLEGAL $FF — skip 3 */
label_E856:;
    /* $E856: D2 */ maybe_trigger_vblank(2); /* ILLEGAL $D2 — skip 1 */
label_E857:;
    /* $E857: D8 */ maybe_trigger_vblank(2); g_cpu.D = 0;
label_E858:;
    /* $E858: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E850;
    }
label_E85A:;
    /* $E85A: FC */ maybe_trigger_vblank(4); (void)nes_read((0x0201 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E85D:;
    /* $E85D: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E85F:;
    /* $E85F: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x01 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_E861:;
    /* $E861: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E863:;
    /* $E863: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_E865:;
    /* $E865: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x02 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_E867:;
    /* $E867: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E868:;
    /* $E868: 21 */ maybe_trigger_vblank(6); g_cpu.A &= nes_read(nes_read16zp((0x01 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_E86A:;
    /* $E86A: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E86B:;
    /* $E86B: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x01 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_E86D:;
    /* $E86D: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E86E:;
    /* $E86E: FF */ maybe_trigger_vblank(7); /* ILLEGAL $FF — skip 3 */
label_E871:;
    /* $E871: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x01 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_E873:;
    /* $E873: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E874:;
    /* $E874: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E875:;
    /* $E875: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_E876:; /* EnemyAnimTimingBMask */
    /* $E876: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_E877:;
    /* $E877: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E878:; /* JumpspringFrameOffsets */
    /* $E878: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_E879:;
    /* $E879: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x191A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E87C:;
    /* $E87C: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
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
    /* $E8F5: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { call_by_address(0xE900); return; }
label_E8F7:;
    /* $E8F7: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x16; FLAG_NZ(g_cpu.Y);
label_E8F9:;
    /* $E8F9: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_E8FB:;
    /* $E8FB: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) { call_by_address(0xE8FE); return; }
label_E8FD:;
    /* $E8FD: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
}

void EnemyEngine::enemy_to_bg_collision_det_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_DFC3;
    }
label_DFC1:; /* EnemyToBGCollisionDet */
    /* $DFC1: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DFC3:;
    /* $DFC3: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x20; FLAG_NZ(g_cpu.A);
label_DFC5:;
    /* $DFC5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xDFB8); return; }
label_DFC7:;
    /* $DFC7: 20 */ maybe_trigger_vblank(6); call_by_address(0xE15B);
label_DFCA:;
    /* $DFCA: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { call_by_address(0xDFB8); return; }
label_DFCC:;
    /* $DFCC: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_DFCE:;
    /* $DFCE: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x12; g_cpu.C=(g_cpu.Y>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_DFD0:;
    /* $DFD0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DFD8;
label_DFD2:;
    /* $DFD2: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_DFD4:;
    /* $DFD4: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x25; g_cpu.C=(g_cpu.A>=0x25)?1:0; FLAG_NZ(r&0xFF); }
label_DFD6:;
    /* $DFD6: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { call_by_address(0xDFB8); return; }
label_DFD8:; /* DoIDCheckBGColl */
    /* $DFD8: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x0E; g_cpu.C=(g_cpu.Y>=0x0E)?1:0; FLAG_NZ(r&0xFF); }
label_DFDA:;
    /* $DFDA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DFDF;
label_DFDC:;
    /* $DFDC: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE163); return;
label_DFDF:; /* HBChk */
    /* $DFDF: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x05; g_cpu.C=(g_cpu.Y>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_DFE1:;
    /* $DFE1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DFE6;
label_DFE3:;
    /* $DFE3: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE185); return;
label_DFE6:; /* CInvu */
    /* $DFE6: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x12; g_cpu.C=(g_cpu.Y>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_DFE8:;
    /* $DFE8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DFF2;
label_DFEA:;
    /* $DFEA: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x2E; g_cpu.C=(g_cpu.Y>=0x2E)?1:0; FLAG_NZ(r&0xFF); }
label_DFEC:;
    /* $DFEC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_DFF2;
label_DFEE:;
    /* $DFEE: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x07; g_cpu.C=(g_cpu.Y>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_DFF0:;
    /* $DFF0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E066;
label_DFF2:; /* YesIn */
    /* $DFF2: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1AE);
label_DFF5:;
    /* $DFF5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_DFFA;
label_DFF7:; /* NoEToBGCollision */
    /* $DFF7: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE0E2); return;
label_DFFA:; /* HandleEToBGCollision */
    /* $DFFA: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1B5);
label_DFFD:;
    /* $DFFD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_DFF7;
    }
label_DFFF:;
    /* $DFFF: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x23; g_cpu.C=(g_cpu.A>=0x23)?1:0; FLAG_NZ(r&0xFF); }
label_E001:;
    /* $E001: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E067;
label_E003:;
    /* $E003: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x02); FLAG_NZ(g_cpu.Y);
label_E005:;
    /* $E005: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E007:;
    /* $E007: 91 */ maybe_trigger_vblank(6); nes_write((nes_read16zp(0x06) + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_E009:;
    /* $E009: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E00B:;
    /* $E00B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_E00D:;
    /* $E00D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E01B;
label_E00F:;
    /* $E00F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_E011:;
    /* $E011: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E016;
label_E013:;
    /* $E013: 20 */ maybe_trigger_vblank(6); call_by_address(0xE18E);
label_E016:; /* GiveOEPoints */
    /* $E016: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E018:;
    /* $E018: 20 */ maybe_trigger_vblank(6); call_by_address(0xDA11);
label_E01B:; /* ChkToStunEnemies */
    /* $E01B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x09; g_cpu.C=(g_cpu.A>=0x09)?1:0; FLAG_NZ(r&0xFF); }
label_E01D:;
    /* $E01D: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E02F;
label_E01F:;
    /* $E01F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_E021:;
    /* $E021: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E02F;
label_E023:;
    /* $E023: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0A; g_cpu.C=(g_cpu.A>=0x0A)?1:0; FLAG_NZ(r&0xFF); }
label_E025:;
    /* $E025: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E02B;
label_E027:;
    /* $E027: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_E029:;
    /* $E029: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E02F;
label_E02B:; /* Demote */
    /* $E02B: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x01; FLAG_NZ(g_cpu.A);
label_E02D:;
    /* $E02D: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_E02F:; /* SetStun */
    /* $E02F: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E031:;
    /* $E031: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF0; FLAG_NZ(g_cpu.A);
label_E033:;
    /* $E033: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x02; FLAG_NZ(g_cpu.A);
label_E035:;
    /* $E035: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E037:;
    /* $E037: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0xCF + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E039:;
    /* $E039: D6 */ maybe_trigger_vblank(6); { uint16_t a=(0xCF + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E03B:;
    /* $E03B: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E03D:;
    /* $E03D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_E03F:;
    /* $E03F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E048;
label_E041:;
    /* $E041: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFD; FLAG_NZ(g_cpu.A);
label_E043:;
    /* $E043: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x074E); FLAG_NZ(g_cpu.Y);
label_E046:;
    /* $E046: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E04A;
label_E048:; /* SetWYSpd */
    /* $E048: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_E04A:; /* SetNotW */
    /* $E04A: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_E04C:;
    /* $E04C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_E04E:;
    /* $E04E: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_E051:;
    /* $E051: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_E054;
label_E053:;
    /* $E053: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E054:; /* ChkBBill */
    /* $E054: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E056:;
    /* $E056: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x33; g_cpu.C=(g_cpu.A>=0x33)?1:0; FLAG_NZ(r&0xFF); }
label_E058:;
    /* $E058: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E060;
label_E05A:;
    /* $E05A: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_E05C:;
    /* $E05C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E060;
label_E05E:;
    /* $E05E: 94 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.Y);
label_E060:; /* NoCDirF */
    /* $E060: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E061:;
    /* $E061: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xDFBF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E064:;
    /* $E064: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_E066:; /* ExEBGChk */
    /* $E066: 60 */ maybe_trigger_vblank(6);
    return;
label_E067:; /* LandEnemyProperly */
    /* $E067: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x04); FLAG_NZ(g_cpu.A);
label_E069:;
    /* $E069: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_E06A:;
    /* $E06A: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x08; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E06C:;
    /* $E06C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E06E:;
    /* $E06E: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E0E2;
label_E070:;
    /* $E070: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E072:;
    /* $E072: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_E074:;
    /* $E074: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0CD;
label_E076:;
    /* $E076: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E078:;
    /* $E078: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E079:;
    /* $E079: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E07E;
label_E07B:; /* SChkA */
    /* $E07B: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE0FE); return;
label_E07E:; /* ChkLandedEnemyState */
    /* $E07E: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E080:;
    /* $E080: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E07B;
    }
label_E082:;
    /* $E082: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E084:;
    /* $E084: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E0A5;
label_E086:;
    /* $E086: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_E088:;
    /* $E088: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_E0A4;
label_E08A:;
    /* $E08A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E08C:;
    /* $E08C: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_E08E:;
    /* $E08E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0A5;
label_E090:;
    /* $E090: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_E092:;
    /* $E092: B4 */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.Y);
label_E094:;
    /* $E094: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x12; g_cpu.C=(g_cpu.Y>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_E096:;
    /* $E096: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E09A;
label_E098:;
    /* $E098: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E09A:; /* SetForStn */
    /* $E09A: 9D */ maybe_trigger_vblank(5); nes_write((0x0796 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_E09D:;
    /* $E09D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x03; FLAG_NZ(g_cpu.A);
label_E09F:;
    /* $E09F: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E0A1:;
    /* $E0A1: 20 */ maybe_trigger_vblank(6); call_by_address(0xE14F);
label_E0A4:; /* ExSteChk */
    /* $E0A4: 60 */ maybe_trigger_vblank(6);
    return;
label_E0A5:; /* ProcEnemyDirection */
    /* $E0A5: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0A7:;
    /* $E0A7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_E0A9:;
    /* $E0A9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E0CD;
label_E0AB:;
    /* $E0AB: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x12; g_cpu.C=(g_cpu.A>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_E0AD:;
    /* $E0AD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0BD;
label_E0AF:;
    /* $E0AF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E0B1:;
    /* $E0B1: 95 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.A);
label_E0B3:;
    /* $E0B3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_E0B5:;
    /* $E0B5: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_E0B7:;
    /* $E0B7: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x09); FLAG_NZ(g_cpu.A);
label_E0B9:;
    /* $E0B9: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_E0BB:;
    /* $E0BB: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E0CD;
label_E0BD:; /* InvtD */
    /* $E0BD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x01; FLAG_NZ(g_cpu.Y);
label_E0BF:;
    /* $E0BF: 20 */ maybe_trigger_vblank(6); call_by_address(0xE143);
label_E0C2:;
    /* $E0C2: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_E0C5;
label_E0C4:;
    /* $E0C4: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E0C5:; /* CNwCDir */
    /* $E0C5: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_E0C6:;
    /* $E0C6: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x46 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E0C8:;
    /* $E0C8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0CD;
label_E0CA:;
    /* $E0CA: 20 */ maybe_trigger_vblank(6); call_by_address(0xE124);
label_E0CD:; /* LandEnemyInitState */
    /* $E0CD: 20 */ maybe_trigger_vblank(6); call_by_address(0xE14F);
label_E0D0:;
    /* $E0D0: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0D2:;
    /* $E0D2: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x80; FLAG_NZ(g_cpu.A);
label_E0D4:;
    /* $E0D4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0DB;
label_E0D6:;
    /* $E0D6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E0D8:;
    /* $E0D8: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E0DA:;
    /* $E0DA: 60 */ maybe_trigger_vblank(6);
    return;
label_E0DB:; /* NMovShellFallBit */
    /* $E0DB: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0DD:;
    /* $E0DD: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xBF; FLAG_NZ(g_cpu.A);
label_E0DF:;
    /* $E0DF: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E0E1:;
    /* $E0E1: 60 */ maybe_trigger_vblank(6);
    return;
label_E0E2:; /* ChkForRedKoopa */
    /* $E0E2: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0E4:;
    /* $E0E4: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x03; g_cpu.C=(g_cpu.A>=0x03)?1:0; FLAG_NZ(r&0xFF); }
label_E0E6:;
    /* $E0E6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E0EC;
label_E0E8:;
    /* $E0E8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0EA:;
    /* $E0EA: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E124;
label_E0EC:; /* Chk2MSBSt */
    /* $E0EC: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0EE:;
    /* $E0EE: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_E0EF:;
    /* $E0EF: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E0F0:;
    /* $E0F0: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E0F9;
label_E0F2:;
    /* $E0F2: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E0F4:;
    /* $E0F4: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x40; FLAG_NZ(g_cpu.A);
label_E0F6:;
    /* $E0F6: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE0FC); return;
label_E0F9:; /* GetSteFromD */
    /* $E0F9: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xDFB9 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E0FC:; /* SetD6Ste */
    /* $E0FC: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_E0FE:; /* DoEnemySideCheck */
    /* $E0FE: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E100:;
    /* $E100: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_E102:;
    /* $E102: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E123;
label_E104:;
    /* $E104: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x16; FLAG_NZ(g_cpu.Y);
label_E106:;
    /* $E106: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E108:;
    /* $E108: 85 */ maybe_trigger_vblank(3); nes_write(0xEB, g_cpu.A);
label_E10A:; /* SdeCLoop */
    /* $E10A: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xEB); FLAG_NZ(g_cpu.A);
label_E10C:;
    /* $E10C: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x46 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_E10E:;
    /* $E10E: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E11C;
label_E110:;
    /* $E110: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_E112:;
    /* $E112: 20 */ maybe_trigger_vblank(6); call_by_address(0xE388);
label_E115:;
    /* $E115: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E11C;
label_E117:;
    /* $E117: 20 */ maybe_trigger_vblank(6); call_by_address(0xE1B5);
label_E11A:;
    /* $E11A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E124;
label_E11C:; /* NextSdeC */
    /* $E11C: C6 */ maybe_trigger_vblank(5); { uint16_t a=0xEB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E11E:;
    /* $E11E: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_E11F:;
    /* $E11F: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x18; g_cpu.C=(g_cpu.Y>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_E121:;
    /* $E121: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_E10A;
    }
label_E123:; /* ExESdeC */
    /* $E123: 60 */ maybe_trigger_vblank(6);
    return;
label_E124:; /* ChkForBump_HammerBroJ */
    /* $E124: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x05; g_cpu.C=(g_cpu.X>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E126:;
    /* $E126: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_E131;
label_E128:;
    /* $E128: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E12A:;
    /* $E12A: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_E12B:;
    /* $E12B: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_E131;
label_E12D:;
    /* $E12D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x02; FLAG_NZ(g_cpu.A);
label_E12F:;
    /* $E12F: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_E131:; /* NoBump */
    /* $E131: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_E133:;
    /* $E133: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x05; g_cpu.C=(g_cpu.A>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_E135:;
    /* $E135: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_E140;
label_E137:;
    /* $E137: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_E139:;
    /* $E139: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_E13B:;
    /* $E13B: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xFA; FLAG_NZ(g_cpu.Y);
label_E13D:;
    /* $E13D: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xCA37); return;
label_E140:; /* InvEnemyDir */
    /* $E140: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xDB36); return;
}

}  // namespace smb::semcomp
