// semcomp/FinalBodies.cpp — bulk-ported routines (auto-generated).
#include "semcomp/FinalBodies.h"

#include "semcomp/GameState.h"
#include "semcomp/cpu_flags.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

void FinalBodies::bank_switch_8286() {
    bank_switch_8286_body(0);
}

void FinalBodies::at_82bd() {
    bank_switch_8286_body(1);
}

void FinalBodies::bank_switch_838_e() {
    bank_switch_838_e_body(0);
}

void FinalBodies::at_8426() {
    bank_switch_838_e_body(1);
}

void FinalBodies::bank_switch_8653() {
    bank_switch_8653_body(0);
}

void FinalBodies::at_8660() {
    bank_switch_8653_body(1);
}

void FinalBodies::bank_switch_8750() {
    bank_switch_8750_body(0);
}

void FinalBodies::at_8759() {
    bank_switch_8750_body(1);
}

void FinalBodies::bank_switch_9_a56() {
    bank_switch_9_a56_body(0);
}

void FinalBodies::at_9a5c() {
    bank_switch_9_a56_body(1);
}

void FinalBodies::at_9a9b() {
    bank_switch_9_a56_body(2);
}

void FinalBodies::bank_switch_b2_ce() {
    bank_switch_b2_ce_body(0);
}

void FinalBodies::at_b396() {
    bank_switch_b2_ce_body(1);
}

void FinalBodies::at_b5c8() {
    bank_switch_b2_ce_body(2);
}

void FinalBodies::at_b67c() {
    bank_switch_b2_ce_body(3);
}

void FinalBodies::bank_switch_b976() {
    bank_switch_b976_body(0);
}

void FinalBodies::at_bfc6() {
    bank_switch_b976_body(1);
}

void FinalBodies::at_b9a9() {
    bank_switch_b976_body(2);
}

void FinalBodies::at_bb33() {
    bank_switch_b976_body(3);
}

void FinalBodies::at_bb48() {
    bank_switch_b976_body(4);
}

void FinalBodies::at_bc57() {
    bank_switch_b976_body(5);
}

void FinalBodies::at_bc9e() {
    bank_switch_b976_body(6);
}

void FinalBodies::at_bd35() {
    bank_switch_b976_body(7);
}

void FinalBodies::at_bd8c() {
    bank_switch_b976_body(8);
}

void FinalBodies::at_bedb() {
    bank_switch_b976_body(9);
}

void FinalBodies::body_c11_e() {
    body_c11_e_body(0);
}

void FinalBodies::at_c120() {
    body_c11_e_body(1);
}

void FinalBodies::body_c4_ce() {
    body_c4_ce_body(0);
}

void FinalBodies::at_c4d0() {
    body_c4_ce_body(1);
}

void FinalBodies::body_c8_dc() {
    body_c8_dc_body(0);
}

void FinalBodies::at_c8e1() {
    body_c8_dc_body(1);
}

void FinalBodies::body_c923() {
    body_c923_body(0);
}

void FinalBodies::at_c927() {
    body_c923_body(1);
}

void FinalBodies::at_c930() {
    body_c923_body(2);
}

void FinalBodies::body_c9_f0() {
    body_c9_f0_body(0);
}

void FinalBodies::at_c9fa() {
    body_c9_f0_body(1);
}

void FinalBodies::at_c9f4() {
    body_c9_f0_body(2);
}

void FinalBodies::at_c9f2() {
    body_c9_f0_body(3);
}

void FinalBodies::body_ca47() {
    body_ca47_body(0);
}

void FinalBodies::at_ca49() {
    body_ca47_body(1);
}

void FinalBodies::body_d0_c7() {
    body_d0_c7_body(0);
}

void FinalBodies::at_d0c9() {
    body_d0_c7_body(1);
}

void FinalBodies::body_d3_d2() {
    body_d3_d2_body(0);
}

void FinalBodies::at_d3d4() {
    body_d3_d2_body(1);
}

void FinalBodies::body_e1_ac() {
    body_e1_ac_body(0);
}

void FinalBodies::at_e1af() {
    body_e1_ac_body(1);
}

void FinalBodies::body_e23_e() {
    body_e23_e_body(0);
}

void FinalBodies::at_e244() {
    body_e23_e_body(1);
}

void FinalBodies::body_e7_b3() {
    body_e7_b3_body(0);
}

void FinalBodies::at_e7d1() {
    body_e7_b3_body(1);
}

void FinalBodies::at_e7de() {
    body_e7_b3_body(2);
}

void FinalBodies::body_ee5_b() {
    body_ee5_b_body(0);
}

void FinalBodies::at_ee61() {
    body_ee5_b_body(1);
}

void FinalBodies::at_eeb6() {
    body_ee5_b_body(2);
}

void FinalBodies::at_eed1() {
    body_ee5_b_body(3);
}

void FinalBodies::body_f4_c0() {
    body_f4_c0_body(0);
}

void FinalBodies::at_f507() {
    body_f4_c0_body(1);
}

void FinalBodies::at_f4f9() {
    body_f4_c0_body(2);
}

void FinalBodies::at_f911() {
    body_f4_c0_body(3);
}

void FinalBodies::at_f938() {
    body_f4_c0_body(4);
}

void FinalBodies::music_header_data() {
    body_f4_c0_body(5);
}

void FinalBodies::at_f4f1() {
    body_f4_c0_body(6);
}

void FinalBodies::victory_mus_hdr() {
    body_f4_c0_body(7);
}

void FinalBodies::at_f4fd() {
    body_f4_c0_body(8);
}

void FinalBodies::at_f4f4() {
    body_f4_c0_body(9);
}

void FinalBodies::at_f508() {
    body_f4_c0_body(10);
}

void FinalBodies::at_f501() {
    body_f4_c0_body(11);
}

void FinalBodies::extra_life_freq_data() {
    body_f4_c0_body(12);
}

void FinalBodies::brick_shatter_freq_data() {
    body_f4_c0_body(13);
}

void FinalBodies::at_f90f() {
    body_f4_c0_body(14);
}

void FinalBodies::at_f919() {
    body_f4_c0_body(15);
}

void FinalBodies::at_f92b() {
    body_f4_c0_body(16);
}

void FinalBodies::at_f96d() {
    body_f4_c0_body(17);
}

void FinalBodies::at_f914() {
    body_f4_c0_body(18);
}

void FinalBodies::body_f693() {
    body_f693_body(0);
}

void FinalBodies::at_f695() {
    body_f693_body(1);
}

void FinalBodies::ground_level_part1_hdr() {
    ground_level_part1_hdr_body(0);
}

void FinalBodies::at_ffaa() {
    ground_level_part1_hdr_body(1);
}

void FinalBodies::bowser_flame_env_data() {
    ground_level_part1_hdr_body(2);
}

void FinalBodies::at_f990() {
    ground_level_part1_hdr_body(3);
}

void FinalBodies::at_f991() {
    ground_level_part1_hdr_body(4);
}

void FinalBodies::at_fdaa() {
    ground_level_part1_hdr_body(5);
}

void FinalBodies::at_fbaa() {
    ground_level_part1_hdr_body(6);
}

void FinalBodies::at_ffa0() {
    ground_level_part1_hdr_body(7);
}

void FinalBodies::at_fad1() {
    ground_level_part1_hdr_body(8);
}

void FinalBodies::at_fda6() {
    ground_level_part1_hdr_body(9);
}

void FinalBodies::at_fea5() {
    ground_level_part1_hdr_body(10);
}

void FinalBodies::water_event_mus_env_data() {
    ground_level_part1_hdr_body(11);
}

void FinalBodies::at_ff01() {
    ground_level_part1_hdr_body(12);
}

void FinalBodies::at_f9a9() {
    ground_level_part1_hdr_body(13);
}

void FinalBodies::at_faa1() {
    ground_level_part1_hdr_body(14);
}

void FinalBodies::at_fda0() {
    ground_level_part1_hdr_body(15);
}

void FinalBodies::at_fca1() {
    ground_level_part1_hdr_body(16);
}

void FinalBodies::at_faf1() {
    ground_level_part1_hdr_body(17);
}

void FinalBodies::at_fd38() {
    ground_level_part1_hdr_body(18);
}

void FinalBodies::at_fa10() {
    ground_level_part1_hdr_body(19);
}

void FinalBodies::at_fc86() {
    ground_level_part1_hdr_body(20);
}

void FinalBodies::at_fea9() {
    ground_level_part1_hdr_body(21);
}

void FinalBodies::at_faad() {
    ground_level_part1_hdr_body(22);
}

void FinalBodies::at_fa0e() {
    ground_level_part1_hdr_body(23);
}

void FinalBodies::at_ff4c() {
    ground_level_part1_hdr_body(24);
}

void FinalBodies::at_ff4d() {
    ground_level_part1_hdr_body(25);
}

void FinalBodies::at_fe4d() {
    ground_level_part1_hdr_body(26);
}

void FinalBodies::at_ff86() {
    ground_level_part1_hdr_body(27);
}

void FinalBodies::at_fe29() {
    ground_level_part1_hdr_body(28);
}

void FinalBodies::at_fca9() {
    ground_level_part1_hdr_body(29);
}

void FinalBodies::at_fbf7() {
    ground_level_part1_hdr_body(30);
}

void FinalBodies::at_fdfc() {
    ground_level_part1_hdr_body(31);
}

void FinalBodies::at_fe08() {
    ground_level_part1_hdr_body(32);
}

void FinalBodies::at_fe02() {
    ground_level_part1_hdr_body(33);
}

void FinalBodies::at_ff07() {
    ground_level_part1_hdr_body(34);
}

void FinalBodies::at_f9f0() {
    ground_level_part1_hdr_body(35);
}

void FinalBodies::at_fc4c() {
    ground_level_part1_hdr_body(36);
}

void FinalBodies::at_fec9() {
    ground_level_part1_hdr_body(37);
}

void FinalBodies::at_fd7d() {
    ground_level_part1_hdr_body(38);
}

void FinalBodies::at_ff7e() {
    ground_level_part1_hdr_body(39);
}

void FinalBodies::at_fc29() {
    ground_level_part1_hdr_body(40);
}

void FinalBodies::at_fa50() {
    ground_level_part1_hdr_body(41);
}

void FinalBodies::at_fbfa() {
    ground_level_part1_hdr_body(42);
}

void FinalBodies::at_fbf9() {
    ground_level_part1_hdr_body(43);
}

void FinalBodies::at_fcfd() {
    ground_level_part1_hdr_body(44);
}

void FinalBodies::at_fcad() {
    ground_level_part1_hdr_body(45);
}

void FinalBodies::at_fcb2() {
    ground_level_part1_hdr_body(46);
}

void FinalBodies::at_fca5() {
    ground_level_part1_hdr_body(47);
}

void FinalBodies::at_fc99() {
    ground_level_part1_hdr_body(48);
}

void FinalBodies::at_fc8f() {
    ground_level_part1_hdr_body(49);
}

void FinalBodies::at_fc95() {
    ground_level_part1_hdr_body(50);
}

void FinalBodies::at_fc96() {
    ground_level_part1_hdr_body(51);
}

void FinalBodies::at_fc74() {
    ground_level_part1_hdr_body(52);
}

void FinalBodies::at_fc70() {
    ground_level_part1_hdr_body(53);
}

void FinalBodies::at_fc6e() {
    ground_level_part1_hdr_body(54);
}

void FinalBodies::at_fcf6() {
    ground_level_part1_hdr_body(55);
}

void FinalBodies::at_fcf4() {
    ground_level_part1_hdr_body(56);
}

void FinalBodies::at_fcbc() {
    ground_level_part1_hdr_body(57);
}

void FinalBodies::at_fcbd() {
    ground_level_part1_hdr_body(58);
}

void FinalBodies::at_fcef() {
    ground_level_part1_hdr_body(59);
}

void FinalBodies::at_fcc2() {
    ground_level_part1_hdr_body(60);
}

void FinalBodies::at_fccc() {
    ground_level_part1_hdr_body(61);
}

void FinalBodies::at_fcf1() {
    ground_level_part1_hdr_body(62);
}

void FinalBodies::at_ff24() {
    ground_level_part1_hdr_body(63);
}

void FinalBodies::at_ff02() {
    ground_level_part1_hdr_body(64);
}

void FinalBodies::at_fc0f() {
    ground_level_part1_hdr_body(65);
}

void FinalBodies::at_fc36() {
    ground_level_part1_hdr_body(66);
}

void FinalBodies::at_fc39() {
    ground_level_part1_hdr_body(67);
}

void FinalBodies::at_fc40() {
    ground_level_part1_hdr_body(68);
}

void FinalBodies::at_fc41() {
    ground_level_part1_hdr_body(69);
}

void FinalBodies::at_fc43() {
    ground_level_part1_hdr_body(70);
}

void FinalBodies::at_fc44() {
    ground_level_part1_hdr_body(71);
}

void FinalBodies::at_fc47() {
    ground_level_part1_hdr_body(72);
}

void FinalBodies::at_fc4a() {
    ground_level_part1_hdr_body(73);
}

void FinalBodies::at_fc91() {
    ground_level_part1_hdr_body(74);
}

void FinalBodies::at_fc93() {
    ground_level_part1_hdr_body(75);
}

void FinalBodies::at_fc94() {
    ground_level_part1_hdr_body(76);
}

void FinalBodies::at_fc9f() {
    ground_level_part1_hdr_body(77);
}

void FinalBodies::at_fc50() {
    ground_level_part1_hdr_body(78);
}

void FinalBodies::at_fcf9() {
    ground_level_part1_hdr_body(79);
}

void FinalBodies::at_fefc() {
    ground_level_part1_hdr_body(80);
}

void FinalBodies::at_faa5() {
    ground_level_part1_hdr_body(81);
}

void FinalBodies::at_fa85() {
    ground_level_part1_hdr_body(82);
}

void FinalBodies::at_ff47() {
    ground_level_part1_hdr_body(83);
}

void FinalBodies::brick_shatter_env_data() {
    ground_level_part1_hdr_body(84);
}

void FinalBodies::at_fda4() {
    ground_level_part1_hdr_body(85);
}

void FinalBodies::at_fd46() {
    ground_level_part1_hdr_body(86);
}

void FinalBodies::at_fba6() {
    ground_level_part1_hdr_body(87);
}

void FinalBodies::ground_level_part4_b_hdr() {
    ground_level_part1_hdr_body(88);
}

void FinalBodies::at_f9a4() {
    ground_level_part1_hdr_body(89);
}

void FinalBodies::at_f9e6() {
    ground_level_part1_hdr_body(90);
}

void FinalBodies::music_length_lookup_tbl() {
    ground_level_part1_hdr_body(91);
}

void FinalBodies::at_ff97() {
    ground_level_part1_hdr_body(92);
}

void FinalBodies::area_music_env_data() {
    ground_level_part1_hdr_body(93);
}

void FinalBodies::time_run_out_mus_data() {
    ground_level_part1_hdr_body(94);
}

void FinalBodies::at_fcc5() {
    ground_level_part1_hdr_body(95);
}

void FinalBodies::silence_data() {
    ground_level_part1_hdr_body(96);
}

void FinalBodies::at_fa1d() {
    ground_level_part1_hdr_body(97);
}

void FinalBodies::castle_mus_data() {
    ground_level_part1_hdr_body(98);
}

void FinalBodies::water_mus_data() {
    ground_level_part1_hdr_body(99);
}

void FinalBodies::end_of_castle_mus_data() {
    ground_level_part1_hdr_body(100);
}

void FinalBodies::ground_m_p1_data() {
    ground_level_part1_hdr_body(101);
}

void FinalBodies::ground_m_p2_a_data() {
    ground_level_part1_hdr_body(102);
}

void FinalBodies::ground_m_p2_c_data() {
    ground_level_part1_hdr_body(103);
}

void FinalBodies::ground_m_p3_a_data() {
    ground_level_part1_hdr_body(104);
}

void FinalBodies::ground_m_p3_b_data() {
    ground_level_part1_hdr_body(105);
}

void FinalBodies::ground_m_p4_a_data() {
    ground_level_part1_hdr_body(106);
}

void FinalBodies::ground_m_p4_b_data() {
    ground_level_part1_hdr_body(107);
}

void FinalBodies::ground_m_p4_c_data() {
    ground_level_part1_hdr_body(108);
}

void FinalBodies::death_mus_data() {
    ground_level_part1_hdr_body(109);
}

void FinalBodies::at_ffc0() {
    ground_level_part1_hdr_body(110);
}

void FinalBodies::at_ff14() {
    ground_level_part1_hdr_body(111);
}

void FinalBodies::at_fe00() {
    ground_level_part1_hdr_body(112);
}

void FinalBodies::at_ff35() {
    ground_level_part1_hdr_body(113);
}

void FinalBodies::at_fe54() {
    ground_level_part1_hdr_body(114);
}

void FinalBodies::at_fa80() {
    ground_level_part1_hdr_body(115);
}

void FinalBodies::at_fa84() {
    ground_level_part1_hdr_body(116);
}

void FinalBodies::at_fd0c() {
    ground_level_part1_hdr_body(117);
}

void FinalBodies::at_fafb() {
    ground_level_part1_hdr_body(118);
}

void FinalBodies::at_fd50() {
    ground_level_part1_hdr_body(119);
}

void FinalBodies::at_faa9() {
    ground_level_part1_hdr_body(120);
}

void FinalBodies::at_ffba() {
    ground_level_part1_hdr_body(121);
}

void FinalBodies::at_f9bd() {
    ground_level_part1_hdr_body(122);
}

void FinalBodies::at_fb29() {
    ground_level_part1_hdr_body(123);
}

void FinalBodies::at_ff18() {
    ground_level_part1_hdr_body(124);
}

void FinalBodies::at_fa8d() {
    ground_level_part1_hdr_body(125);
}

void FinalBodies::at_fc88() {
    ground_level_part1_hdr_body(126);
}

void FinalBodies::at_fdc9() {
    ground_level_part1_hdr_body(127);
}

void FinalBodies::at_fe05() {
    ground_level_part1_hdr_body(128);
}

void FinalBodies::at_fb82() {
    ground_level_part1_hdr_body(129);
}

void FinalBodies::at_ffbc() {
    ground_level_part1_hdr_body(130);
}

void FinalBodies::at_fb0e() {
    ground_level_part1_hdr_body(131);
}

void FinalBodies::at_ffb4() {
    ground_level_part1_hdr_body(132);
}

void FinalBodies::at_fa07() {
    ground_level_part1_hdr_body(133);
}

void FinalBodies::at_fe0b() {
    ground_level_part1_hdr_body(134);
}

void FinalBodies::at_fa12() {
    ground_level_part1_hdr_body(135);
}

void FinalBodies::at_fe87() {
    ground_level_part1_hdr_body(136);
}

void FinalBodies::at_fc00() {
    ground_level_part1_hdr_body(137);
}

void FinalBodies::at_fc62() {
    ground_level_part1_hdr_body(138);
}

void FinalBodies::at_fc15() {
    ground_level_part1_hdr_body(139);
}

void FinalBodies::at_fc21() {
    ground_level_part1_hdr_body(140);
}

void FinalBodies::at_fc26() {
    ground_level_part1_hdr_body(141);
}

void FinalBodies::at_fa42() {
    ground_level_part1_hdr_body(142);
}

void FinalBodies::at_ffac() {
    ground_level_part1_hdr_body(143);
}

void FinalBodies::at_fc84() {
    ground_level_part1_hdr_body(144);
}

void FinalBodies::at_fc04() {
    ground_level_part1_hdr_body(145);
}

void FinalBodies::at_fc09() {
    ground_level_part1_hdr_body(146);
}

void FinalBodies::at_fbfc() {
    ground_level_part1_hdr_body(147);
}

void FinalBodies::at_ff20() {
    ground_level_part1_hdr_body(148);
}

void FinalBodies::at_fabc() {
    ground_level_part1_hdr_body(149);
}

void FinalBodies::at_f99e() {
    ground_level_part1_hdr_body(150);
}

void FinalBodies::at_f9df() {
    ground_level_part1_hdr_body(151);
}

void FinalBodies::at_fb2b() {
    ground_level_part1_hdr_body(152);
}

void FinalBodies::bank_switch_8286_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_82BD;
    }
label_8286:;
    /* $8286: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x1EC3; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8289:;
    /* $8289: C3 */ maybe_trigger_vblank(8); /* ILLEGAL $C3 — skip 2 */
label_828B:;
    /* $828B: C2 */ maybe_trigger_vblank(2); /* NOP */
label_828D:;
    /* $828D: C3 */ maybe_trigger_vblank(8); /* ILLEGAL $C3 — skip 2 */
label_828F:;
    /* $828F: C2 */ maybe_trigger_vblank(2); /* NOP */
label_8291:;
    /* $8291: C3 */ maybe_trigger_vblank(8); /* ILLEGAL $C3 — skip 2 */
label_8293:;
    /* $8293: C3 */ maybe_trigger_vblank(8); /* ILLEGAL $C3 — skip 2 */
label_8295:;
    /* $8295: C2 */ maybe_trigger_vblank(2); /* NOP */
label_8297:;
    /* $8297: C3 */ maybe_trigger_vblank(8); /* ILLEGAL $C3 — skip 2 */
label_8299:;
    /* $8299: C3 */ maybe_trigger_vblank(8); /* ILLEGAL $C3 — skip 2 */
label_829B:;
    /* $829B: C2 */ maybe_trigger_vblank(2); /* NOP */
label_829D:;
    /* $829D: C7 */ maybe_trigger_vblank(5); /* ILLEGAL $C7 — skip 2 */
label_829F:;
    /* $829F: C7 */ maybe_trigger_vblank(5); /* ILLEGAL $C7 — skip 2 */
label_82A1:;
    /* $82A1: C3 */ maybe_trigger_vblank(8); /* ILLEGAL $C3 — skip 2 */
label_82A3:;
    /* $82A3: C3 */ maybe_trigger_vblank(8); /* ILLEGAL $C3 — skip 2 */
label_82A5:;
    /* $82A5: C3 */ maybe_trigger_vblank(8); /* ILLEGAL $C3 — skip 2 */
label_82A7:;
    /* $82A7: C7 */ maybe_trigger_vblank(5); /* ILLEGAL $C7 — skip 2 */
label_82A9:; /* UpdateShroom */
    /* $82A9: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82AB:;
    /* $82AB: C7 */ maybe_trigger_vblank(5); /* ILLEGAL $C7 — skip 2 */
label_82AD:;
    /* $82AD: C7 */ maybe_trigger_vblank(5); /* ILLEGAL $C7 — skip 2 */
label_82AF:;
    /* $82AF: C7 */ maybe_trigger_vblank(5); /* ILLEGAL $C7 — skip 2 */
label_82B1:;
    /* $82B1: C7 */ maybe_trigger_vblank(5); /* ILLEGAL $C7 — skip 2 */
label_82B3:;
    /* $82B3: C7 */ maybe_trigger_vblank(5); /* ILLEGAL $C7 — skip 2 */
label_82B5:;
    /* $82B5: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82B7:;
    /* $82B7: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82B9:;
    /* $82B9: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BB:; /* NullJoypad */
    /* $82BB: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BD:;
    /* $82BD: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x5C); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82BF:;
    /* $82BF: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x59); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82C1:;
    /* $82C1: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xF0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_82C3:;
    /* $82C3: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C5:;
    /* $82C5: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C7:;
    /* $82C7: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82C9:; /* ResetTitle */
    /* $82C9: C2 */ maybe_trigger_vblank(2); /* NOP */
label_82CB:;
    /* $82CB: C7 */ maybe_trigger_vblank(5); /* ILLEGAL $C7 — skip 2 */
label_82CD:;
    /* $82CD: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_82CE:;
    /* $82CE: 3F */ maybe_trigger_vblank(7); /* ILLEGAL $3F — skip 3 */
label_82D1:;
    /* $82D1: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_82D2:;
    /* $82D2: 0B */ maybe_trigger_vblank(2); /* ILLEGAL $0B — skip 2 */
label_82D4:;
    /* $82D4: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_82D6:;
    /* $82D6: 0B */ maybe_trigger_vblank(2); /* ILLEGAL $0B — skip 2 */
label_82D8:; /* ChkContinue */
    /* $82D8: 4B */ maybe_trigger_vblank(2); /* ILLEGAL $4B — skip 2 */
label_82DA:;
    /* $82DA: 57 */ maybe_trigger_vblank(6); /* ILLEGAL $57 — skip 2 */
label_82DC:;
    /* $82DC: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xC5; FLAG_NZ(g_cpu.A);
label_82DE:;
    /* $82DE: 60 */ maybe_trigger_vblank(6);
    return;
}

void FinalBodies::bank_switch_838_e_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_8426;
    }
label_838E:;
    /* $838E: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8390:;
    /* $8390: 3D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0x4CC3 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8393:;
    /* $8393: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x4CC7 + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_8396:;
    /* $8396: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_8397:;
    /* $8397: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x26; g_cpu.C=(g_cpu.A>=0x26)?1:0; FLAG_NZ(r&0xFF); }
label_8399:;
    /* $8399: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x3832); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_839C:;
    /* $839C: 20 */ maybe_trigger_vblank(6); call_by_address(0x2422);
label_839F:;
    /* $839F: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x13; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_83A1:;
    /* $83A1: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x15 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_83A3:;
    /* $83A3: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0xAD + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_83A5:;
    /* $83A5: 8F */ maybe_trigger_vblank(4); nes_write(0xD007, g_cpu.A & g_cpu.X); /* SAX */
label_83A8:;
    /* $83A8: 3C */ maybe_trigger_vblank(4); (void)nes_read((0x05E0 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_83AB:;
    /* $83AB: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_83E5;
label_83AD:;
    /* $83AD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x80; FLAG_NZ(g_cpu.A);
label_83AF:;
    /* $83AF: 8D */ maybe_trigger_vblank(4); nes_write(0x078F, g_cpu.A);
label_83B2:;
    /* $83B2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x04; FLAG_NZ(g_cpu.Y);
label_83B4:;
    /* $83B4: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0016 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_83B7:;
    /* $83B7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_83B9:;
    /* $83B9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_83E6;
label_83BB:;
    /* $83BB: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_83BC:;
    /* $83BC: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_83B4;
    }
label_83BE:;
    /* $83BE: EE */ maybe_trigger_vblank(6); { uint16_t a=0x06D1; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_83C1:;
    /* $83C1: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06D1); FLAG_NZ(g_cpu.A);
label_83C4:;
    /* $83C4: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x07; g_cpu.C=(g_cpu.A>=0x07)?1:0; FLAG_NZ(r&0xFF); }
label_83C6:;
    /* $83C6: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_83E5;
label_83C8:;
    /* $83C8: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x04; FLAG_NZ(g_cpu.X);
label_83CA:;
    /* $83CA: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_83CC:;
    /* $83CC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_83D3;
label_83CE:;
    /* $83CE: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_83CF:;
    /* $83CF: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_83CA;
    }
label_83D1:;
    /* $83D1: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_83E3;
label_83D3:;
    /* $83D3: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_83D5:;
    /* $83D5: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_83D7:;
    /* $83D7: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x11; FLAG_NZ(g_cpu.A);
label_83D9:;
    /* $83D9: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_83DB:;
    /* $83DB: 20 */ maybe_trigger_vblank(6); call_by_address(0xC38A);
label_83DE:;
    /* $83DE: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_83E0:;
    /* $83E0: 20 */ maybe_trigger_vblank(6); call_by_address(0xC5D8);
label_83E3:;
    /* $83E3: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_83E5:;
    /* $83E5: 60 */ maybe_trigger_vblank(6);
    return;
label_83E6:;
    /* $83E6: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xCE); FLAG_NZ(g_cpu.A);
label_83E8:;
    /* $83E8: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x2C; g_cpu.C=(g_cpu.A>=0x2C)?1:0; FLAG_NZ(r&0xFF); }
label_83EA:;
    /* $83EA: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_83E5;
    }
label_83EC:;
    /* $83EC: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x001E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_83EF:;
    /* $83EF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_83E5;
    }
label_83F1:; /* ExitVWalk */
    /* $83F1: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x006E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_83F4:;
    /* $83F4: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_83F6:; /* PrintVictoryMessages */
    /* $83F6: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0087 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_83F9:;
    /* $83F9: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_83FB:;
    /* $83FB: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_83FD:;
    /* $83FD: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_83FF:;
    /* $83FF: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x00CF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8402:;
    /* $8402: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_8403:;
    /* $8403: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x08; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8405:;
    /* $8405: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_8407:;
    /* $8407: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A7 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_840A:;
    /* $840A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_840C:;
    /* $840C: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_840D:;
    /* $840D: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x02; FLAG_NZ(g_cpu.X);
label_840F:;
    /* $840F: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC398 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8412:;
    /* $8412: 95 */ maybe_trigger_vblank(4); nes_write((0x01 + g_cpu.X) & 0xFF, g_cpu.A);
label_8414:; /* MRetainerMsg */
    /* $8414: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8415:;
    /* $8415: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8416:;
    /* $8416: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8417:;
    /* $8417: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8418:; /* ThankPlayer */
    /* $8418: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_8419:;
    /* $8419: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_840F;
    }
label_841B:;
    /* $841B: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_841D:;
    /* $841D: 20 */ maybe_trigger_vblank(6); call_by_address(0xCF6C);
label_8420:;
    /* $8420: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x57); FLAG_NZ(g_cpu.Y);
label_8422:;
    /* $8422: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_8424:;
    /* $8424: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_8434;
label_8426:;
    /* $8426: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_8427:;
    /* $8427: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x07A8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_842A:;
    /* $842A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_842C:;
    /* $842C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_8433;
label_842E:;
    /* $842E: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_842F:;
    /* $842F: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFF; FLAG_NZ(g_cpu.A);
label_8431:;
    /* $8431: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_8432:;
    /* $8432: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8433:;
    /* $8433: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_8434:; /* EvalForMusic */
    /* $8434: 20 */ maybe_trigger_vblank(6); call_by_address(0xC346);
label_8437:;
    /* $8437: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x02; FLAG_NZ(g_cpu.Y);
label_8439:;
    /* $8439: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_843B:;
    /* $843B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_843D:;
    /* $843D: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_8440;
label_843F:;
    /* $843F: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_8440:;
    /* $8440: 94 */ maybe_trigger_vblank(4); nes_write((0x46 + g_cpu.X) & 0xFF, g_cpu.Y);
label_8442:;
    /* $8442: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFD; FLAG_NZ(g_cpu.A);
label_8444:;
    /* $8444: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_8446:;
    /* $8446: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_8448:;
    /* $8448: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_844A:;
    /* $844A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_844C:;
    /* $844C: 95 */ maybe_trigger_vblank(4); nes_write((0x1E + g_cpu.X) & 0xFF, g_cpu.A);
label_844E:;
    /* $844E: 60 */ maybe_trigger_vblank(6);
    return;
}

void FinalBodies::bank_switch_8653_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_8660;
    }
label_8653:;
    /* $8653: F8 */ maybe_trigger_vblank(2); g_cpu.D = 1;
label_8654:;
    /* $8654: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0087 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_8657:;
    /* $8657: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_8658:;
    /* $8658: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x30; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_865A:; /* WriteBottomStatusLine */
    /* $865A: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_865B:;
    /* $865B: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x006E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_865E:;
    /* $865E: E9 */ maybe_trigger_vblank(2); { uint8_t m=0x00; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8660:;
    /* $8660: 85 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.A);
label_8662:;
    /* $8662: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x06D7); FLAG_NZ(g_cpu.A);
label_8665:;
    /* $8665: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8666:;
    /* $8666: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x001E + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_8669:;
    /* $8669: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_866A:;
    /* $866A: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_866B:;
    /* $866B: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_866C:;
    /* $866C: 79 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xC631 + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_866F:;
    /* $866F: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_8671:;
    /* $8671: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_8673:;
    /* $8673: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_8675:;
    /* $8675: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_8677:;
    /* $8677: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xC637 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_867A:;
    /* $867A: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_867C:;
    /* $867C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_867E:;
    /* $867E: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_8680:;
    /* $8680: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_8682:;
    /* $8682: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_8683:;
    /* $8683: 95 */ maybe_trigger_vblank(4); nes_write((0x58 + g_cpu.X) & 0xFF, g_cpu.A);
label_8685:;
    /* $8685: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_8687:;
    /* $8687: 95 */ maybe_trigger_vblank(4); nes_write((0xA0 + g_cpu.X) & 0xFF, g_cpu.A);
label_8689:;
    /* $8689: 60 */ maybe_trigger_vblank(6);
    return;
}

void FinalBodies::bank_switch_8750_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_8759;
    }
label_8750:;
    /* $8750: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xFF; FLAG_NZ(g_cpu.X);
label_8752:; /* TopStatusBarLine */
    /* $8752: E8 */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X+1)&0xFF; FLAG_NZ(g_cpu.X);
label_8753:;
    /* $8753: E0 */ maybe_trigger_vblank(2); { int r=g_cpu.X-0x05; g_cpu.C=(g_cpu.X>=0x05)?1:0; FLAG_NZ(r&0xFF); }
label_8755:;
    /* $8755: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_8784;
label_8757:;
    /* $8757: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_8759:;
    /* $8759: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8752;
    }
label_875B:;
    /* $875B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x01); FLAG_NZ(g_cpu.A);
label_875D:;
    /* $875D: 95 */ maybe_trigger_vblank(4); nes_write((0x16 + g_cpu.X) & 0xFF, g_cpu.A);
label_875F:;
    /* $875F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_8761:;
    /* $8761: 95 */ maybe_trigger_vblank(4); nes_write((0x6E + g_cpu.X) & 0xFF, g_cpu.A);
label_8763:;
    /* $8763: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x03); FLAG_NZ(g_cpu.A);
label_8765:;
    /* $8765: 95 */ maybe_trigger_vblank(4); nes_write((0x87 + g_cpu.X) & 0xFF, g_cpu.A);
label_8767:;
    /* $8767: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_8768:;
    /* $8768: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x18 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x18); g_cpu.A=r&0xFF; }
label_876A:;
    /* $876A: 85 */ maybe_trigger_vblank(3); nes_write(0x03, g_cpu.A);
label_876C:;
    /* $876C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x02); FLAG_NZ(g_cpu.A);
label_876E:;
    /* $876E: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x00 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x00); g_cpu.A=r&0xFF; }
label_8770:;
    /* $8770: 85 */ maybe_trigger_vblank(3); nes_write(0x02, g_cpu.A);
label_8772:;
    /* $8772: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x00); FLAG_NZ(g_cpu.A);
label_8774:;
    /* $8774: 95 */ maybe_trigger_vblank(4); nes_write((0xCF + g_cpu.X) & 0xFF, g_cpu.A);
label_8776:;
    /* $8776: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_8778:;
    /* $8778: 95 */ maybe_trigger_vblank(4); nes_write((0xB6 + g_cpu.X) & 0xFF, g_cpu.A);
label_877A:;
    /* $877A: 95 */ maybe_trigger_vblank(4); nes_write((0x0F + g_cpu.X) & 0xFF, g_cpu.A);
label_877C:;
    /* $877C: 20 */ maybe_trigger_vblank(6); call_by_address(0xC26C);
label_877F:;
    /* $877F: CE */ maybe_trigger_vblank(6); { uint16_t a=0x06D3; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_8782:;
    /* $8782: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_8750;
    }
label_8784:;
    /* $8784: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC25E); return;
}

void FinalBodies::bank_switch_9_a56_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_9A5C;
        case 2: goto label_9A9B;
    }
label_9A56:;
    /* $9A56: 86 */ maybe_trigger_vblank(3); nes_write(0x01, g_cpu.X);
label_9A58:;
    /* $9A58: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_9A59:; /* ColumnOfSolidBlocks */
    /* $9A59: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_9A5A:;
    /* $9A5A: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0F + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_9A5C:;
    /* $9A5C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9AAA;
label_9A5E:;
    /* $9A5E: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_9A60:;
    /* $9A60: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x15; g_cpu.C=(g_cpu.A>=0x15)?1:0; FLAG_NZ(r&0xFF); }
label_9A62:;
    /* $9A62: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_9AAA;
label_9A64:;
    /* $9A64: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x11; g_cpu.C=(g_cpu.A>=0x11)?1:0; FLAG_NZ(r&0xFF); }
label_9A66:;
    /* $9A66: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9AAA;
label_9A68:;
    /* $9A68: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x0D; g_cpu.C=(g_cpu.A>=0x0D)?1:0; FLAG_NZ(r&0xFF); }
label_9A6A:;
    /* $9A6A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_9AAA;
label_9A6C:;
    /* $9A6C: BD */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x03D8 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9A6F:;
    /* $9A6F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_9AAA;
label_9A71:;
    /* $9A71: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_9A72:;
    /* $9A72: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9A73:;
    /* $9A73: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_9A74:;
    /* $9A74: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_9A75:;
    /* $9A75: 69 */ maybe_trigger_vblank(2); { uint16_t r = g_cpu.A + 0x04 + g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,0x04); g_cpu.A=r&0xFF; }
label_9A77:;
    /* $9A77: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_9A78:;
    /* $9A78: 20 */ maybe_trigger_vblank(6); call_by_address(0xE327);
label_9A7B:;
    /* $9A7B: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_9A7D:;
    /* $9A7D: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x01); FLAG_NZ(g_cpu.Y);
label_9A7F:;
    /* $9A7F: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_9AA1;
label_9A81:;
    /* $9A81: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x1E + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_9A83:;
    /* $9A83: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x001E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9A86:;
    /* $9A86: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x80; FLAG_NZ(g_cpu.A);
label_9A88:;
    /* $9A88: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_9A9B;
label_9A8A:;
    /* $9A8A: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9A8D:;
    /* $9A8D: 3D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xDA25 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9A90:;
    /* $9A90: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_9AAA;
label_9A92:;
    /* $9A92: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9A95:;
    /* $9A95: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0xDA25 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9A98:;
    /* $9A98: 99 */ maybe_trigger_vblank(5); nes_write((0x0491 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_9A9B:;
    /* $9A9B: 20 */ maybe_trigger_vblank(6); call_by_address(0xDAB4);
label_9A9E:;
    /* $9A9E: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xDAAA); return;
label_9AA1:; /* StrCOffset */
    /* $9AA1: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0x0491 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9AA4:;
    /* $9AA4: 3D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xDA2C + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_9AA7:;
    /* $9AA7: 99 */ maybe_trigger_vblank(5); nes_write((0x0491 + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_9AAA:;
    /* $9AAA: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_9AAB:;
    /* $9AAB: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_9AAC:;
    /* $9AAC: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x01); FLAG_NZ(g_cpu.X);
label_9AAE:; /* StaircaseRowData */
    /* $9AAE: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_9AAF:;
    /* $9AAF: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_9A56;
    }
label_9AB1:;
    /* $9AB1: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x08); FLAG_NZ(g_cpu.X);
label_9AB3:;
    /* $9AB3: 60 */ maybe_trigger_vblank(6);
    return;
}

void FinalBodies::bank_switch_b2_ce_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_B396;
        case 2: goto label_B5C8;
        case 3: goto label_B67C;
    }
label_B2CE:;
    /* $B2CE: FF */ maybe_trigger_vblank(7); /* ILLEGAL $FF — skip 3 */
label_B2D1:;
    /* $B2D1: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) { call_by_address(0xB2DA); return; }
label_B2D3:;
    /* $B2D3: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B2D9;
label_B2D5:;
    /* $B2D5: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_B2D8:;
    /* $B2D8: 60 */ maybe_trigger_vblank(6);
    return;
label_B2D9:;
    /* $B2D9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_B2DB:;
    /* $B2DB: 8D */ maybe_trigger_vblank(4); nes_write(0x4017, g_cpu.A);
label_B2DE:;
    /* $B2DE: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0F; FLAG_NZ(g_cpu.A);
label_B2E0:;
    /* $B2E0: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_B2E3:; /* ChkStop */
    /* $B2E3: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07C6); FLAG_NZ(g_cpu.A);
label_B2E6:;
    /* $B2E6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B2EE;
label_B2E8:;
    /* $B2E8: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xFA); FLAG_NZ(g_cpu.A);
label_B2EA:;
    /* $B2EA: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_B2EC:;
    /* $B2EC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B34B;
label_B2EE:;
    /* $B2EE: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B2); FLAG_NZ(g_cpu.A);
label_B2F1:; /* InCastle */
    /* $B2F1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B316;
label_B2F3:;
    /* $B2F3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xFA); FLAG_NZ(g_cpu.A);
label_B2F5:;
    /* $B2F5: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B35D;
label_B2F7:;
    /* $B2F7: 8D */ maybe_trigger_vblank(4); nes_write(0x07B2, g_cpu.A);
label_B2FA:;
    /* $B2FA: 8D */ maybe_trigger_vblank(4); nes_write(0x07C6, g_cpu.A);
label_B2FD:;
    /* $B2FD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B2FF:;
    /* $B2FF: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_B302:;
    /* $B302: 85 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.A);
label_B304:;
    /* $B304: 85 */ maybe_trigger_vblank(3); nes_write(0xF2, g_cpu.A);
label_B306:;
    /* $B306: 85 */ maybe_trigger_vblank(3); nes_write(0xF3, g_cpu.A);
label_B308:;
    /* $B308: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0F; FLAG_NZ(g_cpu.A);
label_B30A:;
    /* $B30A: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_B30D:;
    /* $B30D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2A; FLAG_NZ(g_cpu.A);
label_B30F:;
    /* $B30F: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B312:;
    /* $B312: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_B314:;
    /* $B314: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B327;
label_B316:;
    /* $B316: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B319:;
    /* $B319: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x24; g_cpu.C=(g_cpu.A>=0x24)?1:0; FLAG_NZ(r&0xFF); }
label_B31B:;
    /* $B31B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B325;
label_B31D:;
    /* $B31D: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x1E; g_cpu.C=(g_cpu.A>=0x1E)?1:0; FLAG_NZ(r&0xFF); }
label_B31F:;
    /* $B31F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B312;
    }
label_B321:;
    /* $B321: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x18; g_cpu.C=(g_cpu.A>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_B323:;
    /* $B323: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B32E;
label_B325:;
    /* $B325: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x64; FLAG_NZ(g_cpu.A);
label_B327:;
    /* $B327: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x84; FLAG_NZ(g_cpu.X);
label_B329:; /* PlayerMovementSubs */
    /* $B329: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_B32B:;
    /* $B32B: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_B32E:;
    /* $B32E: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B331:;
    /* $B331: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B35D;
label_B333:;
    /* $B333: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B335:;
    /* $B335: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_B338:; /* SetCrouch */
    /* $B338: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B2); FLAG_NZ(g_cpu.A);
label_B33B:; /* ProcMove */
    /* $B33B: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x02; g_cpu.C=(g_cpu.A>=0x02)?1:0; FLAG_NZ(r&0xFF); }
label_B33D:;
    /* $B33D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B344;
label_B33F:;
    /* $B33F: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B341:;
    /* $B341: 8D */ maybe_trigger_vblank(4); nes_write(0x07C6, g_cpu.A);
label_B344:;
    /* $B344: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B346:;
    /* $B346: 8D */ maybe_trigger_vblank(4); nes_write(0x07B2, g_cpu.A);
label_B349:;
    /* $B349: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B35D;
label_B34B:;
    /* $B34B: 20 */ maybe_trigger_vblank(6); call_by_address(0xF41B);
label_B34E:; /* MoveSubs */
    /* $B34E: 20 */ maybe_trigger_vblank(6); call_by_address(0xF57C);
label_B351:;
    /* $B351: 20 */ maybe_trigger_vblank(6); call_by_address(0xF667);
label_B354:;
    /* $B354: 20 */ maybe_trigger_vblank(6); call_by_address(0xF694);
label_B357:;
    /* $B357: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B359:; /* NoMoveSub */
    /* $B359: 85 */ maybe_trigger_vblank(3); nes_write(0xFB, g_cpu.A);
label_B35B:;
    /* $B35B: 85 */ maybe_trigger_vblank(3); nes_write(0xFC, g_cpu.A);
label_B35D:;
    /* $B35D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B35F:;
    /* $B35F: 85 */ maybe_trigger_vblank(3); nes_write(0xFF, g_cpu.A);
label_B361:;
    /* $B361: 85 */ maybe_trigger_vblank(3); nes_write(0xFE, g_cpu.A);
label_B363:; /* GndMove */
    /* $B363: 85 */ maybe_trigger_vblank(3); nes_write(0xFD, g_cpu.A);
label_B365:;
    /* $B365: 85 */ maybe_trigger_vblank(3); nes_write(0xFA, g_cpu.A);
label_B367:;
    /* $B367: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07C0); FLAG_NZ(g_cpu.Y);
label_B36A:;
    /* $B36A: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_B36C:;
    /* $B36C: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x03; FLAG_NZ(g_cpu.A);
label_B36E:;
    /* $B36E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B377;
label_B370:;
    /* $B370: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07C0; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B373:;
    /* $B373: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x30; g_cpu.C=(g_cpu.Y>=0x30)?1:0; FLAG_NZ(r&0xFF); }
label_B375:;
    /* $B375: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_B37D;
label_B377:;
    /* $B377: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_B378:;
    /* $B378: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B37D;
label_B37A:;
    /* $B37A: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07C0; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B37D:;
    /* $B37D: 8C */ maybe_trigger_vblank(4); nes_write(0x4011, g_cpu.Y);
label_B380:;
    /* $B380: 60 */ maybe_trigger_vblank(6);
    return;
label_B381:;
    /* $B381: 8C */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.Y);
label_B384:;
    /* $B384: 8E */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.X);
label_B387:;
    /* $B387: 60 */ maybe_trigger_vblank(6);
    return;
label_B388:;
    /* $B388: 20 */ maybe_trigger_vblank(6); call_by_address(0xF381);
label_B38B:;
    /* $B38B: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B38D:; /* DumpFall */
    /* $B38D: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_B38E:;
    /* $B38E: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFF01 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B391:;
    /* $B391: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B39E;
label_B393:; /* ProcSwim */
    /* $B393: 9D */ maybe_trigger_vblank(5); nes_write((0x4002 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_B396:;
    /* $B396: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFF00 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B399:;
    /* $B399: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x08; FLAG_NZ(g_cpu.A);
label_B39B:;
    /* $B39B: 9D */ maybe_trigger_vblank(5); nes_write((0x4003 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_B39E:;
    /* $B39E: 60 */ maybe_trigger_vblank(6);
    return;
label_B39F:;
    /* $B39F: 8E */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.X);
label_B3A2:;
    /* $B3A2: 8C */ maybe_trigger_vblank(4); nes_write(0x4005, g_cpu.Y);
label_B3A5:;
    /* $B3A5: 60 */ maybe_trigger_vblank(6);
    return;
label_B3A6:; /* LRWater */
    /* $B3A6: 20 */ maybe_trigger_vblank(6); call_by_address(0xF39F);
label_B3A9:;
    /* $B3A9: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x04; FLAG_NZ(g_cpu.X);
label_B3AB:;
    /* $B3AB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B38D;
    }
label_B3AD:;
    /* $B3AD: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x08; FLAG_NZ(g_cpu.X);
label_B3AF:;
    /* $B3AF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B38D;
    }
label_B3B1:;
    /* $B3B1: 9F */ maybe_trigger_vblank(5); /* ILLEGAL $9F — skip 3 */
label_B3B4:;
    /* $B3B4: 96 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.Y) & 0xFF, g_cpu.X);
label_B3B6:;
    /* $B3B6: 94 */ maybe_trigger_vblank(4); nes_write((0x92 + g_cpu.X) & 0xFF, g_cpu.Y);
label_B3B8:;
    /* $B3B8: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { call_by_address(0xB34A); return; }
label_B3BA:;
    /* $B3BA: 9A */ maybe_trigger_vblank(2); g_cpu.S = g_cpu.X;
label_B3BB:;
    /* $B3BB: 97 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.Y) & 0xFF, g_cpu.A & g_cpu.X); /* SAX */
label_B3BD:;
    /* $B3BD: 93 */ maybe_trigger_vblank(6); /* ILLEGAL $93 — skip 2 */
label_B3BF:;
    /* $B3BF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_B3C1:;
    /* $B3C1: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B3C4:; /* ExitMov1 */
    /* $B3C4: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x62; FLAG_NZ(g_cpu.A);
label_B3C6:;
    /* $B3C6: 20 */ maybe_trigger_vblank(6); call_by_address(0xF38B);
label_B3C9:;
    /* $B3C9: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x99; FLAG_NZ(g_cpu.X);
label_B3CB:; /* ClimbAdderHigh */
    /* $B3CB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B3F2;
label_B3CD:;
    /* $B3CD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B3CF:; /* ClimbingSub */
    /* $B3CF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B3D3;
label_B3D1:;
    /* $B3D1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_B3D3:;
    /* $B3D3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x82; FLAG_NZ(g_cpu.X);
label_B3D5:;
    /* $B3D5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xA7; FLAG_NZ(g_cpu.Y);
label_B3D7:;
    /* $B3D7: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_B3DA:;
    /* $B3DA: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B3DC:;
    /* $B3DC: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B3DF:;
    /* $B3DF: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B3E2:;
    /* $B3E2: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x25; g_cpu.C=(g_cpu.A>=0x25)?1:0; FLAG_NZ(r&0xFF); }
label_B3E4:;
    /* $B3E4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B3EC;
label_B3E6:;
    /* $B3E6: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x5F; FLAG_NZ(g_cpu.X);
label_B3E8:;
    /* $B3E8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xF6; FLAG_NZ(g_cpu.Y);
label_B3EA:;
    /* $B3EA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B3F4;
label_B3EC:;
    /* $B3EC: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_B3EE:;
    /* $B3EE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B419;
label_B3F0:;
    /* $B3F0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x48; FLAG_NZ(g_cpu.X);
label_B3F2:;
    /* $B3F2: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xBC; FLAG_NZ(g_cpu.Y);
label_B3F4:;
    /* $B3F4: 20 */ maybe_trigger_vblank(6); call_by_address(0xF381);
label_B3F7:;
    /* $B3F7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B419;
label_B3F9:;
    /* $B3F9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x05; FLAG_NZ(g_cpu.A);
label_B3FB:;
    /* $B3FB: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x99; FLAG_NZ(g_cpu.Y);
label_B3FD:;
    /* $B3FD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B403;
label_B3FF:;
    /* $B3FF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0A; FLAG_NZ(g_cpu.A);
label_B401:;
    /* $B401: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_B403:;
    /* $B403: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B405:;
    /* $B405: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B408:;
    /* $B408: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0C; FLAG_NZ(g_cpu.A);
label_B40A:; /* CSetFDir */
    /* $B40A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_B40D:;
    /* $B40D: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B410:;
    /* $B410: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x06; g_cpu.C=(g_cpu.A>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B412:;
    /* $B412: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B419;
label_B414:;
    /* $B414: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xBB; FLAG_NZ(g_cpu.A);
label_B416:;
    /* $B416: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_B419:;
    /* $B419: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B47B;
label_B41B:;
    /* $B41B: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFF); FLAG_NZ(g_cpu.Y);
label_B41D:;
    /* $B41D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B43F;
label_B41F:; /* ExitCSub */
    /* $B41F: 84 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.Y);
label_B421:;
    /* $B421: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3CD;
    }
label_B423:;
    /* $B423: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B425:;
    /* $B425: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3D1;
    }
label_B427:;
    /* $B427: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B429:;
    /* $B429: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3FF;
    }
label_B42B:; /* FallMForceData */
    /* $B42B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B42D:;
    /* $B42D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B45B;
label_B42F:;
    /* $B42F: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B431:;
    /* $B431: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B47D;
label_B433:;
    /* $B433: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B435:;
    /* $B435: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B4B6;
label_B437:;
    /* $B437: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B439:; /* InitMForceData */
    /* $B439: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3F9;
    }
label_B43B:;
    /* $B43B: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B43D:;
    /* $B43D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3BF;
    }
label_B43F:;
    /* $B43F: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_B441:;
    /* $B441: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B45A;
label_B443:; /* MaxRightXSpdData */
    /* $B443: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3DF;
    }
label_B445:;
    /* $B445: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B446:;
    /* $B446: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B3DF;
    }
label_B448:;
    /* $B448: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B449:;
    /* $B449: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B44B:;
    /* $B44B: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44C:;
    /* $B44C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B469;
label_B44E:;
    /* $B44E: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B44F:;
    /* $B44F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B48D;
label_B451:;
    /* $B451: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B452:;
    /* $B452: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B4BB;
label_B454:;
    /* $B454: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B455:;
    /* $B455: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B40D;
    }
label_B457:;
    /* $B457: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B458:;
    /* $B458: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B4A2;
label_B45A:;
    /* $B45A: 60 */
    return; /* branch-target RTS */
label_B45B:;
    /* $B45B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B45D:;
    /* $B45D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B460:;
    /* $B460: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x9C; FLAG_NZ(g_cpu.Y);
label_B462:;
    /* $B462: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9E; FLAG_NZ(g_cpu.X);
label_B464:;
    /* $B464: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x26; FLAG_NZ(g_cpu.A);
label_B466:;
    /* $B466: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_B469:;
    /* $B469: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B46C:;
    /* $B46C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF3B0 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B46F:;
    /* $B46F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B472:;
    /* $B472: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x06; g_cpu.C=(g_cpu.Y>=0x06)?1:0; FLAG_NZ(r&0xFF); }
label_B474:;
    /* $B474: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B47B;
label_B476:;
    /* $B476: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9E; FLAG_NZ(g_cpu.A);
label_B478:;
    /* $B478: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B47B:;
    /* $B47B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B4A2;
label_B47D:;
    /* $B47D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0E; FLAG_NZ(g_cpu.A);
label_B47F:;
    /* $B47F: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xCB; FLAG_NZ(g_cpu.Y);
label_B481:;
    /* $B481: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_B483:;
    /* $B483: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B486:;
    /* $B486: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_B488:; /* NoJump */
    /* $B488: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_B48B:; /* ProcJumping */
    /* $B48B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B4A2;
label_B48D:;
    /* $B48D: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07BB); FLAG_NZ(g_cpu.Y);
label_B490:;
    /* $B490: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x08; g_cpu.C=(g_cpu.Y>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_B492:;
    /* $B492: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B49D;
label_B494:;
    /* $B494: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xA0; FLAG_NZ(g_cpu.A);
label_B496:;
    /* $B496: 8D */ maybe_trigger_vblank(4); nes_write(0x4002, g_cpu.A);
label_B499:;
    /* $B499: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9F; FLAG_NZ(g_cpu.A);
label_B49B:;
    /* $B49B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B49F;
label_B49D:;
    /* $B49D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_B49F:;
    /* $B49F: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_B4A2:;
    /* $B4A2: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BB; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B4A5:;
    /* $B4A5: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B4B5;
label_B4A7:;
    /* $B4A7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B4A9:;
    /* $B4A9: 86 */ maybe_trigger_vblank(3); nes_write(0xF1, g_cpu.X);
label_B4AB:;
    /* $B4AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0E; FLAG_NZ(g_cpu.X);
label_B4AD:;
    /* $B4AD: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B0:;
    /* $B4B0: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B4B2:;
    /* $B4B2: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B4B5:;
    /* $B4B5: 60 */ maybe_trigger_vblank(6);
    return;
label_B4B6:;
    /* $B4B6: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x2F; FLAG_NZ(g_cpu.A);
label_B4B8:;
    /* $B4B8: 8D */ maybe_trigger_vblank(4); nes_write(0x07BB, g_cpu.A);
label_B4BB:;
    /* $B4BB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BB); FLAG_NZ(g_cpu.A);
label_B4BE:;
    /* $B4BE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4BF:;
    /* $B4BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B4D1;
label_B4C1:;
    /* $B4C1: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4C2:;
    /* $B4C2: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B4D1;
label_B4C4:;
    /* $B4C4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_B4C6:;
    /* $B4C6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B4D1;
label_B4C8:;
    /* $B4C8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_B4CA:;
    /* $B4CA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_B4CC:;
    /* $B4CC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_B4CE:;
    /* $B4CE: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_B4D1:;
    /* $B4D1: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF4A2); return;
label_B4D4:;
    /* $B4D4: 58 */ maybe_trigger_vblank(2); g_cpu.I = 0;
label_B4D5:;
    /* $B4D5: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_B4D6:;
    /* $B4D6: 54 */ maybe_trigger_vblank(4); (void)nes_read((0x56 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B4D8:;
    /* $B4D8: 4E */ maybe_trigger_vblank(6); { uint16_t a=0x4C44; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B4DB:;
    /* $B4DB: 52 */ maybe_trigger_vblank(2); /* ILLEGAL $52 — skip 1 */
label_B4DC:;
    /* $B4DC: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x3E48); return;
label_B4DF:;
    /* $B4DF: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x3E + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B4E1:;
    /* $B4E1: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x30 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B4E3:;
    /* $B4E3: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_B4E4:; /* GetYPhy */
    /* $B4E4: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B4E5:;
    /* $B4E5: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) goto label_B531;
label_B4E7:;
    /* $B4E7: 64 */ maybe_trigger_vblank(3); (void)nes_read(0x3C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B4E9:;
    /* $B4E9: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_B4EA:;
    /* $B4EA: 3C */ maybe_trigger_vblank(4); (void)nes_read((0x2C32 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B4ED:;
    /* $B4ED: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x3A); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B4EF:;
    /* $B4EF: 64 */ maybe_trigger_vblank(3); (void)nes_read(0x3A); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B4F1:;
    /* $B4F1: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x2C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B4F3:;
    /* $B4F3: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_B4F4:;
    /* $B4F4: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x1C22); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B4F7:;
    /* $B4F7: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x14 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B4F9:;
    /* $B4F9: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B4FB:;
    /* $B4FB: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x16); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B4FD:;
    /* $B4FD: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x24); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B4FF:;
    /* $B4FF: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x18; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B501:;
    /* $B501: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B503:;
    /* $B503: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_B504:;
    /* $B504: 1A */ maybe_trigger_vblank(2); /* NOP */
label_B505:;
    /* $B505: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x28); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B507:;
    /* $B507: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_B508:;
    /* $B508: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2A04 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B50B:;
    /* $B50B: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x041E); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B50E:;
    /* $B50E: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x202E); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B511:; /* PJumpSnd */
    /* $B511: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2E); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B513:;
    /* $B513: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xB537); return; }
label_B515:;
    /* $B515: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x30); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B517:;
    /* $B517: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_B518:;
    /* $B518: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x35; FLAG_NZ(g_cpu.A);
label_B51A:; /* SJumpSnd */
    /* $B51A: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x8D; FLAG_NZ(g_cpu.X);
label_B51C:; /* X_Physics */
    /* $B51C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B522;
label_B51E:;
    /* $B51E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_B520:;
    /* $B520: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x98; FLAG_NZ(g_cpu.X);
label_B522:;
    /* $B522: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_B525:;
    /* $B525: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_B527:;
    /* $B527: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x42; FLAG_NZ(g_cpu.A);
label_B529:;
    /* $B529: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3A6);
label_B52C:;
    /* $B52C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_B52F:;
    /* $B52F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x30; g_cpu.C=(g_cpu.A>=0x30)?1:0; FLAG_NZ(r&0xFF); }
label_B531:;
    /* $B531: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B538;
label_B533:;
    /* $B533: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x54; FLAG_NZ(g_cpu.A);
label_B535:;
    /* $B535: 8D */ maybe_trigger_vblank(4); nes_write(0x4006, g_cpu.A);
label_B538:;
    /* $B538: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B568;
label_B53A:;
    /* $B53A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_B53C:;
    /* $B53C: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_B53F:;
    /* $B53F: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x94; FLAG_NZ(g_cpu.Y);
label_B541:;
    /* $B541: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x5E; FLAG_NZ(g_cpu.A);
label_B543:;
    /* $B543: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B550;
label_B545:; /* ChkRFast */
    /* $B545: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_B548:;
    /* $B548: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x18; g_cpu.C=(g_cpu.A>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_B54A:;
    /* $B54A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B568;
label_B54C:;
    /* $B54C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_B54E:;
    /* $B54E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_B550:;
    /* $B550: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B5D1;
label_B552:;
    /* $B552: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x36; FLAG_NZ(g_cpu.A);
label_B554:; /* FastXSp */
    /* $B554: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_B557:;
    /* $B557: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_B55A:;
    /* $B55A: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B55B:;
    /* $B55B: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B568;
label_B55D:;
    /* $B55D: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_B55E:; /* GetXPhy */
    /* $B55E: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF4D9 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B561:;
    /* $B561: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x5D; FLAG_NZ(g_cpu.X);
label_B563:;
    /* $B563: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_B565:;
    /* $B565: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3A6);
label_B568:;
    /* $B568: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BD; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B56B:;
    /* $B56B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B57B;
label_B56D:;
    /* $B56D: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_B56F:;
    /* $B56F: 86 */ maybe_trigger_vblank(3); nes_write(0xF2, g_cpu.X);
label_B571:;
    /* $B571: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0D; FLAG_NZ(g_cpu.X);
label_B573:;
    /* $B573: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B576:;
    /* $B576: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B578:;
    /* $B578: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_B57B:;
    /* $B57B: 60 */ maybe_trigger_vblank(6);
    return;
label_B57C:;
    /* $B57C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_B57E:;
    /* $B57E: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_B580:;
    /* $B580: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B5E7;
label_B582:;
    /* $B582: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFE); FLAG_NZ(g_cpu.Y);
label_B584:;
    /* $B584: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B5A6;
label_B586:;
    /* $B586: 84 */ maybe_trigger_vblank(3); nes_write(0xF2, g_cpu.Y);
label_B588:;
    /* $B588: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_B5C8;
label_B58A:;
    /* $B58A: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B58C:; /* PlayerAnimTmrData */
    /* $B58C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B518;
    }
label_B58E:;
    /* $B58E: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B590:;
    /* $B590: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B5FC;
label_B592:;
    /* $B592: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B594:;
    /* $B594: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B600;
label_B596:;
    /* $B596: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B598:;
    /* $B598: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B53A;
    }
label_B59A:;
    /* $B59A: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B59C:;
    /* $B59C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B51E;
    }
label_B59E:; /* ChkSkid */
    /* $B59E: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B5A0:;
    /* $B5A0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B552;
    }
label_B5A2:;
    /* $B5A2: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B5A4:;
    /* $B5A4: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B5E2;
label_B5A6:;
    /* $B5A6: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_B5A8:;
    /* $B5A8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B5C1;
label_B5AA:;
    /* $B5AA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_B5D3;
label_B5AC:;
    /* $B5AC: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B5AD:; /* SetRunSpd */
    /* $B5AD: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B5C2;
label_B5AF:;
    /* $B5AF: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B5B0:;
    /* $B5B0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B60F;
label_B5B2:;
    /* $B5B2: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B5B3:; /* ProcSkid */
    /* $B5B3: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B60F;
label_B5B5:;
    /* $B5B5: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B5B6:;
    /* $B5B6: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B545;
    }
label_B5B8:;
    /* $B5B8: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B5B9:;
    /* $B5B9: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B5C2;
label_B5BB:;
    /* $B5BB: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B5BC:;
    /* $B5BC: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B557;
    }
label_B5BE:;
    /* $B5BE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B5BF:;
    /* $B5BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B5E7;
label_B5C1:;
    /* $B5C1: 60 */ maybe_trigger_vblank(6);
    return;
label_B5C2:;
    /* $B5C2: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF52C); return;
label_B5C5:; /* SetAnimSpd */
    /* $B5C5: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF568); return;
label_B5C8:;
    /* $B5C8: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x38; FLAG_NZ(g_cpu.A);
label_B5CA:;
    /* $B5CA: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_B5CD:;
    /* $B5CD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xC4; FLAG_NZ(g_cpu.Y);
label_B5CF:;
    /* $B5CF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_B5D1:;
    /* $B5D1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B5DE;
label_B5D3:;
    /* $B5D3: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_B5D6:;
    /* $B5D6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_B5D8:;
    /* $B5D8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B568;
    }
label_B5DA:;
    /* $B5DA: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xA4; FLAG_NZ(g_cpu.Y);
label_B5DC:;
    /* $B5DC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x5A; FLAG_NZ(g_cpu.A);
label_B5DE:; /* LeftFrict */
    /* $B5DE: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_B5E0:;
    /* $B5E0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B565;
    }
label_B5E2:;
    /* $B5E2: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x30; FLAG_NZ(g_cpu.A);
label_B5E4:;
    /* $B5E4: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_B5E7:;
    /* $B5E7: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_B5EA:;
    /* $B5EA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_B5EC:;
    /* $B5EC: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B5ED:;
    /* $B5ED: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B5C5;
    }
label_B5EF:;
    /* $B5EF: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_B5F0:;
    /* $B5F0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B5EC;
    }
label_B5F2:;
    /* $B5F2: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_B5F3:;
    /* $B5F3: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF4D3 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B5F6:;
    /* $B5F6: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x82; FLAG_NZ(g_cpu.X);
label_B5F8:;
    /* $B5F8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_B5FA:;
    /* $B5FA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B5E0;
    }
label_B5FC:; /* RghtFrict */
    /* $B5FC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_B5FE:;
    /* $B5FE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B602;
label_B600:;
    /* $B600: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_B602:;
    /* $B602: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_B605:;
    /* $B605: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x7F; FLAG_NZ(g_cpu.A);
label_B607:;
    /* $B607: 8D */ maybe_trigger_vblank(4); nes_write(0x4005, g_cpu.A);
label_B60A:;
    /* $B60A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B60C:;
    /* $B60C: 8D */ maybe_trigger_vblank(4); nes_write(0x07BE, g_cpu.A);
label_B60F:;
    /* $B60F: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07BE; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B612:;
    /* $B612: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BE); FLAG_NZ(g_cpu.A);
label_B615:;
    /* $B615: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B616:;
    /* $B616: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_B617:; /* XSpdSign */
    /* $B617: CC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x07BD); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_B61A:;
    /* $B61A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B628;
label_B61C:;
    /* $B61C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9D; FLAG_NZ(g_cpu.A);
label_B61E:;
    /* $B61E: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_B621:;
    /* $B621: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF4F8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B624:; /* ProcFireball_Bubble */
    /* $B624: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3A9);
label_B627:;
    /* $B627: 60 */ maybe_trigger_vblank(6);
    return;
label_B628:;
    /* $B628: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF56D); return;
label_B62B:;
    /* $B62B: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x0E + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_B62D:;
    /* $B62D: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x0B0D; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B630:;
    /* $B630: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x0C; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B632:;
    /* $B632: 0F */ maybe_trigger_vblank(6); /* ILLEGAL $0F — skip 3 */
label_B635:;
    /* $B635: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_B637:;
    /* $B637: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_B638:;
    /* $B638: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x0C06); FLAG_NZ(g_cpu.A);
label_B63B:;
    /* $B63B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_B63D:;
    /* $B63D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BF, g_cpu.A);
label_B640:;
    /* $B640: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BF); FLAG_NZ(g_cpu.A);
label_B643:;
    /* $B643: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B644:;
    /* $B644: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_B658;
label_B646:;
    /* $B646: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_B647:;
    /* $B647: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xF62B + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_B64A:;
    /* $B64A: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFFEA + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B64D:;
    /* $B64D: 8D */ maybe_trigger_vblank(4); nes_write(0x400C, g_cpu.A);
label_B650:;
    /* $B650: 8E */ maybe_trigger_vblank(4); nes_write(0x400E, g_cpu.X);
label_B653:;
    /* $B653: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_B655:;
    /* $B655: 8D */ maybe_trigger_vblank(4); nes_write(0x400F, g_cpu.A);
label_B658:;
    /* $B658: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B65B:;
    /* $B65B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_B666;
label_B65D:;
    /* $B65D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF0; FLAG_NZ(g_cpu.A);
label_B65F:;
    /* $B65F: 8D */ maybe_trigger_vblank(4); nes_write(0x400C, g_cpu.A);
label_B662:;
    /* $B662: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_B664:; /* ProcFireballs */
    /* $B664: 85 */ maybe_trigger_vblank(3); nes_write(0xF3, g_cpu.A);
label_B666:;
    /* $B666: 60 */ maybe_trigger_vblank(6);
    return;
label_B667:;
    /* $B667: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFD); FLAG_NZ(g_cpu.Y);
label_B669:;
    /* $B669: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B675;
label_B66B:;
    /* $B66B: 84 */ maybe_trigger_vblank(3); nes_write(0xF3, g_cpu.Y);
label_B66D:;
    /* $B66D: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFD; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B66F:;
    /* $B66F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B63B;
    }
label_B671:;
    /* $B671: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFD; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_B673:;
    /* $B673: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B680;
label_B675:; /* BublLoop */
    /* $B675: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF3); FLAG_NZ(g_cpu.A);
label_B677:;
    /* $B677: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_B67F;
label_B679:;
    /* $B679: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B67A:;
    /* $B67A: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B640;
    }
label_B67C:;
    /* $B67C: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B67D:;
    /* $B67D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_B685;
label_B67F:;
    /* $B67F: 60 */ maybe_trigger_vblank(6);
    return;
label_B680:;
    /* $B680: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_B682:;
    /* $B682: 8D */ maybe_trigger_vblank(4); nes_write(0x07BF, g_cpu.A);
label_B685:;
    /* $B685: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BF); FLAG_NZ(g_cpu.A);
label_B688:;
    /* $B688: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_B689:; /* FireballObjCore */
    /* $B689: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_B68A:;
    /* $B68A: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_B68C:;
    /* $B68C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFFC9 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B68F:;
    /* $B68F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B64D;
    }
label_B691:;
    /* $B691: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF73A); return;
}

void FinalBodies::bank_switch_b976_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_BFC6;
        case 2: goto label_B9A9;
        case 3: goto label_BB33;
        case 4: goto label_BB48;
        case 5: goto label_BC57;
        case 6: goto label_BC9E;
        case 7: goto label_BD35;
        case 8: goto label_BD8C;
        case 9: goto label_BEDB;
    }
label_B976:;
    /* $B976: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B977:;
    /* $B977: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0xFA + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_B979:; /* VDrawLoop */
    /* $B979: 2D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read(0xB81C); FLAG_NZ(g_cpu.A);
label_B97C:;
    /* $B97C: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B97D:;
    /* $B97D: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFA; FLAG_NZ(g_cpu.A);
label_B97F:;
    /* $B97F: 20 */ maybe_trigger_vblank(6); call_by_address(0x7012);
label_B982:;
    /* $B982: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B983:;
    /* $B983: 75 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xFA + g_cpu.X) & 0xFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_B985:;
    /* $B985: 1B */ maybe_trigger_vblank(7); /* ILLEGAL $1B — skip 3 */
label_B988:;
    /* $B988: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B989:;
    /* $B989: 9D */ maybe_trigger_vblank(5); nes_write((0x11FA + g_cpu.X) & 0xFFFF, g_cpu.A);
label_B98C:;
    /* $B98C: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_B98D:;
    /* $B98D: 1C */ maybe_trigger_vblank(4); (void)nes_read((0xC218 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B990:;
    /* $B990: FA */ maybe_trigger_vblank(2); /* NOP */
label_B991:;
    /* $B991: 2D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read(0x5810); FLAG_NZ(g_cpu.A);
label_B994:;
    /* $B994: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B995:;
    /* $B995: DB */ maybe_trigger_vblank(7); /* ILLEGAL $DB — skip 3 */
label_B998:;
    /* $B998: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x183F); FLAG_NZ(g_cpu.A);
label_B99B:;
    /* $B99B: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x15FA + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_B99E:;
    /* $B99E: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x1821); FLAG_NZ(g_cpu.A);
label_B9A1:;
    /* $B9A1: 25 */ maybe_trigger_vblank(3); g_cpu.A &= nes_read(0xFB); FLAG_NZ(g_cpu.A);
label_B9A3:;
    /* $B9A3: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B9A4:;
    /* $B9A4: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_BA20;
label_B9A6:;
    /* $B9A6: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B9A7:;
    /* $B9A7: 4B */ maybe_trigger_vblank(2); /* ILLEGAL $4B — skip 2 */
label_B9A9:;
    /* $B9A9: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x540F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B9AC:;
    /* $B9AC: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B9AD:;
    /* $B9AD: 74 */ maybe_trigger_vblank(4); (void)nes_read((0xFB + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B9AF:;
    /* $B9AF: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x2B12 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_B9B2:;
    /* $B9B2: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_B9B3:;
    /* $B9B3: 72 */ maybe_trigger_vblank(2); /* ILLEGAL $72 — skip 1 */
label_B9B4:;
    /* $B9B4: FB */ maybe_trigger_vblank(7); /* ILLEGAL $FB — skip 3 */
label_B9B7:; /* ExitVH */
    /* $B9B7: 2D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read(0x2C84); FLAG_NZ(g_cpu.A);
label_B9BA:; /* CannonBitmasks */
    /* $B9BA: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x822C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B9BD:;
    /* $B9BD: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B9BF:;
    /* $B9BF: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x85); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B9C1:;
    /* $B9C1: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2C84); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B9C4:;
    /* $B9C4: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2A2A); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B9C7:;
    /* $B9C7: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_B9C8:;
    /* $B9C8: 82 */ maybe_trigger_vblank(2); /* NOP */
label_B9CA:;
    /* $B9CA: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_B9CB:;
    /* $B9CB: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x85); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B9CD:;
    /* $B9CD: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_B9CE:;
    /* $B9CE: 84 */ maybe_trigger_vblank(3); nes_write(0x2A, g_cpu.Y);
label_B9D0:;
    /* $B9D0: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_B9D1:;
    /* $B9D1: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xB9D1); return;
label_B9D2:;
    /* $B9D2: 1F */ maybe_trigger_vblank(7); /* ILLEGAL $1F — skip 3 */
label_B9D5:;
    /* $B9D5: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_B9D6:;
    /* $B9D6: 1F */ maybe_trigger_vblank(7); /* ILLEGAL $1F — skip 3 */
label_B9D9:;
    /* $B9D9: 9E */ maybe_trigger_vblank(5); /* ILLEGAL $9E — skip 3 */
label_B9DC:;
    /* $B9DC: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x1D1D + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B9DF:;
    /* $B9DF: 94 */ maybe_trigger_vblank(4); nes_write((0x1D + g_cpu.X) & 0xFF, g_cpu.Y);
label_B9E1:;
    /* $B9E1: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x9C94 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B9E4:;
    /* $B9E4: 94 */ maybe_trigger_vblank(4); nes_write((0x1D + g_cpu.X) & 0xFF, g_cpu.Y);
label_B9E6:;
    /* $B9E6: 86 */ maybe_trigger_vblank(3); nes_write(0x18, g_cpu.X);
label_B9E8:;
    /* $B9E8: 85 */ maybe_trigger_vblank(3); nes_write(0x26, g_cpu.A);
label_B9EA:;
    /* $B9EA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xB970); return; }
label_B9EC:;
    /* $B9EC: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B9EE:;
    /* $B9EE: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_B976;
    }
label_B9F0:;
    /* $B9F0: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x85 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_B9F2:;
    /* $B9F2: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_B9F3:;
    /* $B9F3: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0484); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B9F6:;
    /* $B9F6: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_B9F7:;
    /* $B9F7: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xD021); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_B9FA:;
    /* $B9FA: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xD0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_B9FC:;
    /* $B9FC: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0xD0) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_B9FE:;
    /* $B9FE: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xD0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_BA00:;
    /* $BA00: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBA00); return;
label_BA01:;
    /* $BA01: 85 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.A);
label_BA03:;
    /* $BA03: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BA04:;
    /* $BA04: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2684 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA07:;
    /* $BA07: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BA08:;
    /* $BA08: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BA0A:;
    /* $BA0A: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA0C:;
    /* $BA0C: 87 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A & g_cpu.X); /* SAX */
label_BA0E:;
    /* $BA0E: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x3A + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA10:;
    /* $BA10: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BA12:;
    /* $BA12: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x36); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA14:;
    /* $BA14: 84 */ maybe_trigger_vblank(3); nes_write(0x3A, g_cpu.Y);
label_BA16:;
    /* $BA16: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x82 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA18:;
    /* $BA18: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x8530); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BA1B:;
    /* $BA1B: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BA1C:;
    /* $BA1C: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBA1C); return;
label_BA1D:;
    /* $BA1D: 5D */ maybe_trigger_vblank(4); g_cpu.A ^= nes_read((0x4D55 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BA20:;
    /* $BA20: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x19 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_BA22:;
    /* $BA22: 96 */ maybe_trigger_vblank(4); nes_write((0x15 + g_cpu.Y) & 0xFF, g_cpu.X);
label_BA24:;
    /* $BA24: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE3 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_BA26:;
    /* $BA26: EB */ maybe_trigger_vblank(2); { uint8_t m=0x2D; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_BA28:;
    /* $BA28: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x2B); FLAG_NZ(g_cpu.X);
label_BA2A:;
    /* $BA2A: 27 */ maybe_trigger_vblank(5); /* ILLEGAL $27 — skip 2 */
label_BA2C:;
    /* $BA2C: 9E */ maybe_trigger_vblank(5); /* ILLEGAL $9E — skip 3 */
label_BA2F:;
    /* $BA2F: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BA30:; /* ExCannon */
    /* $BA30: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x8414 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA33:; /* BulletBillHandler */
    /* $BA33: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x8222 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA36:;
    /* $BA36: 20 */ maybe_trigger_vblank(6); call_by_address(0x041E);
label_BA39:;
    /* $BA39: 87 */ maybe_trigger_vblank(3); nes_write(0x1C, g_cpu.A & g_cpu.X); /* SAX */
label_BA3B:;
    /* $BA3B: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x8234); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BA3E:;
    /* $BA3E: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x04 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA40:;
    /* $BA40: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xBA76); return; }
label_BA42:;
    /* $BA42: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA44:;
    /* $BA44: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA46:;
    /* $BA46: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BA47:;
    /* $BA47: 85 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A);
label_BA49:;
    /* $BA49: 84 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.Y);
label_BA4B:;
    /* $BA4B: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BA4D:; /* SetupBB */
    /* $BA4D: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_BA4E:;
    /* $BA4E: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x32 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA50:;
    /* $BA50: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x34); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA52:;
    /* $BA52: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x24); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA54:;
    /* $BA54: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x2C; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA56:;
    /* $BA56: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA58:;
    /* $BA58: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0030); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BA5B:;
    /* $BA5B: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xB4); FLAG_NZ(g_cpu.A);
label_BA5D:;
    /* $BA5D: B2 */ maybe_trigger_vblank(2); /* ILLEGAL $B2 — skip 1 */
label_BA5E:;
    /* $BA5E: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xBA8B); return; }
label_BA60:;
    /* $BA60: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x9C84); FLAG_NZ(g_cpu.Y);
label_BA63:;
    /* $BA63: 9E */ maybe_trigger_vblank(5); /* ILLEGAL $9E — skip 3 */
label_BA66:;
    /* $BA66: 94 */ maybe_trigger_vblank(4); nes_write((0x9C + g_cpu.X) & 0xFF, g_cpu.Y);
label_BA68:;
    /* $BA68: 9E */ maybe_trigger_vblank(5); /* ILLEGAL $9E — skip 3 */
label_BA6B:;
    /* $BA6B: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BA6C:;
    /* $BA6C: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_BA6E:;
    /* $BA6E: 85 */ maybe_trigger_vblank(3); nes_write(0x1E, g_cpu.A);
label_BA70:;
    /* $BA70: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BA72:;
    /* $BA72: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_BA74:;
    /* $BA74: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x0484 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA77:;
    /* $BA77: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BA79:;
    /* $BA79: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_BA7A:;
    /* $BA7A: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x32 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BA7C:;
    /* $BA7C: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x34); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA7E:;
    /* $BA7E: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x64); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA80:;
    /* $BA80: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x64); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA82:;
    /* $BA82: 86 */ maybe_trigger_vblank(3); nes_write(0x64, g_cpu.X);
label_BA84:;
    /* $BA84: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBA84); return;
label_BA85:; /* KillBB */
    /* $BA85: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xB4); FLAG_NZ(g_cpu.A);
label_BA87:;
    /* $BA87: B2 */ maybe_trigger_vblank(2); /* ILLEGAL $B2 — skip 1 */
label_BA88:;
    /* $BA88: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xBAB5); return; }
label_BA8A:;
    /* $BA8A: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x3784); FLAG_NZ(g_cpu.Y);
label_BA8D:;
    /* $BA8D: B6 */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xB6 + g_cpu.Y) & 0xFF); FLAG_NZ(g_cpu.X);
label_BA8F:;
    /* $BA8F: 45 */ maybe_trigger_vblank(3); g_cpu.A ^= nes_read(0x85); FLAG_NZ(g_cpu.A);
label_BA91:;
    /* $BA91: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x1C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BA93:;
    /* $BA93: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BA95:;
    /* $BA95: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_BA97:;
    /* $BA97: 4E */ maybe_trigger_vblank(6); { uint16_t a=0x4E82; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BA9A:;
    /* $BA9A: 84 */ maybe_trigger_vblank(3); nes_write(0x4E, g_cpu.Y);
label_BA9C:;
    /* $BA9C: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BA9D:;
    /* $BA9D: 84 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.Y);
label_BA9F:;
    /* $BA9F: 85 */ maybe_trigger_vblank(3); nes_write(0x32, g_cpu.A);
label_BAA1:;
    /* $BAA1: 85 */ maybe_trigger_vblank(3); nes_write(0x30, g_cpu.A);
label_BAA3:;
    /* $BAA3: 86 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.X);
label_BAA5:;
    /* $BAA5: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAA7:;
    /* $BAA7: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xA4); FLAG_NZ(g_cpu.A);
label_BAA9:;
    /* $BAA9: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x9E); FLAG_NZ(g_cpu.A);
label_BAAB:;
    /* $BAAB: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x9D); FLAG_NZ(g_cpu.A);
label_BAAD:;
    /* $BAAD: 85 */ maybe_trigger_vblank(3); nes_write(0x84, g_cpu.A);
label_BAAF:;
    /* $BAAF: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x85 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAB1:;
    /* $BAB1: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x28); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BAB3:;
    /* $BAB3: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2282); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BAB6:;
    /* $BAB6: 84 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.Y);
label_BAB8:;
    /* $BAB8: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x21 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BABA:;
    /* $BABA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BA80;
    }
label_BABC:;
    /* $BABC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_BAEF;
label_BABE:;
    /* $BABE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BA84;
    }
label_BAC0:;
    /* $BAC0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_BAC2;
label_BAC2:;
    /* $BAC2: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BAC4:;
    /* $BAC4: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_BAC6:;
    /* $BAC6: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2C82); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BAC9:;
    /* $BAC9: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_BACF;
label_BACB:;
    /* $BACB: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x2C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BACD:;
    /* $BACD: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BACF:;
    /* $BACF: 86 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.X);
label_BAD1:;
    /* $BAD1: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBAD1); return;
label_BAD2:;
    /* $BAD2: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x25); FLAG_NZ(g_cpu.Y);
label_BAD4:;
    /* $BAD4: 25 */ maybe_trigger_vblank(3); g_cpu.A &= nes_read(0xA4); FLAG_NZ(g_cpu.A);
label_BAD6:;
    /* $BAD6: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xA2; FLAG_NZ(g_cpu.A);
label_BAD8:;
    /* $BAD8: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x959C + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BADB:;
    /* $BADB: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BADD:;
    /* $BADD: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2C04); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BAE0:;
    /* $BAE0: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAE2:;
    /* $BAE2: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xBA69); return; }
label_BAE4:;
    /* $BAE4: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x04 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAE6:;
    /* $BAE6: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAE8:;
    /* $BAE8: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x25); FLAG_NZ(g_cpu.Y);
label_BAEA:;
    /* $BAEA: 25 */ maybe_trigger_vblank(3); g_cpu.A &= nes_read(0xA4); FLAG_NZ(g_cpu.A);
label_BAEC:;
    /* $BAEC: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_BAED:;
    /* $BAED: 63 */ maybe_trigger_vblank(8); /* ILLEGAL $63 — skip 2 */
label_BAEF:;
    /* $BAEF: 85 */ maybe_trigger_vblank(3); nes_write(0x0E, g_cpu.A);
label_BAF1:;
    /* $BAF1: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BAF2:;
    /* $BAF2: 84 */ maybe_trigger_vblank(3); nes_write(0x24, g_cpu.Y);
label_BAF4:;
    /* $BAF4: 85 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A);
label_BAF6:;
    /* $BAF6: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x84 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAF8:;
    /* $BAF8: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x3482); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAFB:;
    /* $BAFB: 84 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.Y);
label_BAFD:;
    /* $BAFD: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x82 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BAFF:;
    /* $BAFF: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x3484); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BB02:;
    /* $BB02: 86 */ maybe_trigger_vblank(3); nes_write(0x3A, g_cpu.X);
label_BB04:;
    /* $BB04: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BB06:;
    /* $BB06: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x21; FLAG_NZ(g_cpu.Y);
label_BB08:;
    /* $BB08: 21 */ maybe_trigger_vblank(6); g_cpu.A &= nes_read(nes_read16zp((0xA0 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BB0A:;
    /* $BB0A: 21 */ maybe_trigger_vblank(6); g_cpu.A &= nes_read(nes_read16zp((0x2B + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BB0C:;
    /* $BB0C: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xA3); FLAG_NZ(g_cpu.A);
label_BB0E:;
    /* $BB0E: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB10:;
    /* $BB10: 84 */ maybe_trigger_vblank(3); nes_write(0x18, g_cpu.Y);
label_BB12:;
    /* $BB12: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BB13:;
    /* $BB13: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB15:;
    /* $BB15: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BB16:;
    /* $BB16: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x86); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BB18:;
    /* $BB18: 3A */ maybe_trigger_vblank(2); /* NOP */
label_BB19:;
    /* $BB19: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BB1A:;
    /* $BB1A: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x90) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB1C:;
    /* $BB1C: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x90) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB1E:;
    /* $BB1E: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x71) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB20:;
    /* $BB20: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x90) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB22:;
    /* $BB22: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { call_by_address(0xBAB4); return; }
label_BB24:;
    /* $BB24: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBB24); return;
label_BB25:;
    /* $BB25: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB27:;
    /* $BB27: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_BB29:;
    /* $BB29: 85 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A);
label_BB2B:; /* RunHSubs */
    /* $BB2B: 84 */ maybe_trigger_vblank(3); nes_write(0x24, g_cpu.Y);
label_BB2D:;
    /* $BB2D: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB2F:;
    /* $BB2F: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x04 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB31:;
    /* $BB31: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x86 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB33:;
    /* $BB33: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB35:;
    /* $BB35: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x5D27); FLAG_NZ(g_cpu.Y);
label_BB38:; /* CoinBlock */
    /* $BB38: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x2D9E + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB3B:;
    /* $BB3B: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x859F); FLAG_NZ(g_cpu.Y);
label_BB3E:;
    /* $BB3E: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x82 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BB40:;
    /* $BB40: 20 */ maybe_trigger_vblank(6); call_by_address(0x2284);
label_BB43:;
    /* $BB43: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x1E1E); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BB46:;
    /* $BB46: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB48:;
    /* $BB48: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x041E); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BB4B:;
    /* $BB4B: 87 */ maybe_trigger_vblank(3); nes_write(0x2A, g_cpu.A & g_cpu.X); /* SAX */
label_BB4D:;
    /* $BB4D: 40 */ maybe_trigger_vblank(6); /* RTI */ g_cpu.S++; { uint8_t p=g_ram[0x100+g_cpu.S]; g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1; g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; } g_cpu.S++; g_cpu.S++; /* pop PCL, PCH */
    return;
label_BB4E:;
    /* $BB4E: 40 */ maybe_trigger_vblank(6); /* RTI */ g_cpu.S++; { uint8_t p=g_ram[0x100+g_cpu.S]; g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1; g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; } g_cpu.S++; g_cpu.S++; /* pop PCL, PCH */
    return;
label_BB4F:;
    /* $BB4F: 40 */ maybe_trigger_vblank(6); /* RTI */ g_cpu.S++; { uint8_t p=g_ram[0x100+g_cpu.S]; g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1; g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; } g_cpu.S++; g_cpu.S++; /* pop PCL, PCH */
    return;
label_BB50:;
    /* $BB50: 3A */ maybe_trigger_vblank(2); /* NOP */
label_BB51:; /* SetupJumpCoin */
    /* $BB51: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x82 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB53:;
    /* $BB53: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x2C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BB55:;
    /* $BB55: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BB57:;
    /* $BB57: 86 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.X);
label_BB59:;
    /* $BB59: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBB59); return;
label_BB5A:;
    /* $BB5A: E3 */ maybe_trigger_vblank(8); /* ILLEGAL $E3 — skip 2 */
label_BB5C:;
    /* $BB5C: F7 */ maybe_trigger_vblank(6); /* ILLEGAL $F7 — skip 2 */
label_BB5E:;
    /* $BB5E: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xF1 + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_BB60:;
    /* $BB60: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x9E27); FLAG_NZ(g_cpu.Y);
label_BB63:;
    /* $BB63: 9D */ maybe_trigger_vblank(5); nes_write((0x1885 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_BB66:;
    /* $BB66: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB68:;
    /* $BB68: 84 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.Y);
label_BB6A:;
    /* $BB6A: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BB6B:;
    /* $BB6B: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BB6C:; /* JCoinC */
    /* $BB6C: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BB6D:;
    /* $BB6D: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB6F:;
    /* $BB6F: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0422); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BB72:;
    /* $BB72: 86 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.X);
label_BB74:;
    /* $BB74: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB76:;
    /* $BB76: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x04 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB78:;
    /* $BB78: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x87 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB7A:;
    /* $BB7A: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x34 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB7C:;
    /* $BB7C: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BB04;
    }
label_BB7E:;
    /* $BB7E: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0004); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BB81:;
    /* $BB81: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBB81); return;
label_BB82:;
    /* $BB82: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_BB83:;
    /* $BB83: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_BB84:; /* FindEmptyMiscSlot */
    /* $BB84: 6C */ maybe_trigger_vblank(5); { uint16_t _jt = nes_read16_jmpbug(0xA245); maybe_trigger_vblank(2); call_by_address(_jt); return; }
label_BB87:;
    /* $BB87: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0xB0) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB89:;
    /* $BB89: F1 */ maybe_trigger_vblank(5); { uint8_t m=nes_read((nes_read16zp(0xED) + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_BB8B:;
    /* $BB8B: EB */ maybe_trigger_vblank(2); { uint8_t m=0xA2; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_BB8D:;
    /* $BB8D: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x959C + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BB90:;
    /* $BB90: 86 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.X);
label_BB92:; /* UseMiscS */
    /* $BB92: 85 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A);
label_BB94:;
    /* $BB94: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BB96:; /* MiscObjectsCore */
    /* $BB96: 87 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A & g_cpu.X); /* SAX */
label_BB98:; /* MiscLoop */
    /* $BB98: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x2A; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BB9A:;
    /* $BB9A: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_BB9C:;
    /* $BB9C: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BB9D:;
    /* $BB9D: 86 */ maybe_trigger_vblank(3); nes_write(0x14, g_cpu.X);
label_BB9F:;
    /* $BB9F: 51 */ maybe_trigger_vblank(5); g_cpu.A ^= nes_read((nes_read16zp(0x90) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BBA1:;
    /* $BBA1: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x11) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BBA3:;
    /* $BBA3: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBBA3); return;
label_BBA4:;
    /* $BBA4: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BBA6:;
    /* $BBA6: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBA7:; /* ProcJumpCoin */
    /* $BBA7: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BBA8:;
    /* $BBA8: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x22; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BBAA:;
    /* $BBAA: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x22); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BBAC:;
    /* $BBAC: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x22; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BBAE:;
    /* $BBAE: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBAF:;
    /* $BBAF: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BBB0:;
    /* $BBB0: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BBB1:;
    /* $BBB1: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BBB2:;
    /* $BBB2: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBB3:;
    /* $BBB3: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BBB4:;
    /* $BBB4: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x22; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BBB6:;
    /* $BBB6: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBB7:;
    /* $BBB7: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BBB8:;
    /* $BBB8: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x22; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BBBA:;
    /* $BBBA: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x22); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BBBC:;
    /* $BBBC: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x22; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BBBE:;
    /* $BBBE: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBBF:;
    /* $BBBF: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BBC0:;
    /* $BBC0: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BBC1:;
    /* $BBC1: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BBC2:;
    /* $BBC2: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBC3:;
    /* $BBC3: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BBC4:;
    /* $BBC4: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BBC6:;
    /* $BBC6: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BBC8:;
    /* $BBC8: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x20); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BBCA:;
    /* $BBCA: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BBCC:;
    /* $BBCC: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBCD:;
    /* $BBCD: 20 */ maybe_trigger_vblank(6); call_by_address(0x2026);
label_BBD0:;
    /* $BBD0: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBD1:;
    /* $BBD1: 20 */ maybe_trigger_vblank(6); call_by_address(0x2026);
label_BBD4:;
    /* $BBD4: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x20); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BBD6:;
    /* $BBD6: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BBD8:;
    /* $BBD8: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x20); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BBDA:;
    /* $BBDA: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BBDC:;
    /* $BBDC: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBDD:;
    /* $BBDD: 20 */ maybe_trigger_vblank(6); call_by_address(0x2026);
label_BBE0:;
    /* $BBE0: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBE1:;
    /* $BBE1: 20 */ maybe_trigger_vblank(6); call_by_address(0x2026);
label_BBE4:;
    /* $BBE4: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x28); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BBE6:;
    /* $BBE6: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xBC10); return; }
label_BBE8:; /* RunJCSubs */
    /* $BBE8: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_BBE9:;
    /* $BBE9: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBEA:;
    /* $BBEA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_BC14;
label_BBEC:;
    /* $BBEC: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x3028; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BBEF:;
    /* $BBEF: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBF0:;
    /* $BBF0: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x2C28; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BBF3:;
    /* $BBF3: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBF4:; /* MiscLoopBack */
    /* $BBF4: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x3028; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BBF7:;
    /* $BBF7: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBF8:; /* CoinTallyOffsets */
    /* $BBF8: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_BBF9:;
    /* $BBF9: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BBFA:; /* ScoreOffsets */
    /* $BBFA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_BC24;
label_BBFC:; /* StatusBarNybbles */
    /* $BBFC: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x3028; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BBFF:;
    /* $BBFF: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BC00:;
    /* $BC00: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x2C28; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BC03:;
    /* $BC03: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BC04:;
    /* $BC04: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x0400; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BC07:;
    /* $BC07: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) { call_by_address(0xBC77); return; }
label_BC09:;
    /* $BC09: 6C */ maybe_trigger_vblank(5); { uint16_t _jt = nes_read16_jmpbug(0x706E); maybe_trigger_vblank(2); call_by_address(_jt); return; }
label_BC0C:;
    /* $BC0C: 72 */ maybe_trigger_vblank(2); /* ILLEGAL $72 — skip 1 */
label_BC0D:;
    /* $BC0D: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) goto label_BC7D;
label_BC0F:;
    /* $BC0F: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) { call_by_address(0xBC7F); return; }
label_BC11:;
    /* $BC11: 6C */ maybe_trigger_vblank(5); { uint16_t _jt = nes_read16_jmpbug(0x706E); maybe_trigger_vblank(2); call_by_address(_jt); return; }
label_BC14:;
    /* $BC14: 72 */ maybe_trigger_vblank(2); /* ILLEGAL $72 — skip 1 */
label_BC15:;
    /* $BC15: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) { call_by_address(0xBC85); return; }
label_BC17:;
    /* $BC17: 6E */ maybe_trigger_vblank(6); { uint16_t a=0x6E6C; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BC1A:;
    /* $BC1A: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) goto label_BC8A;
label_BC1C:;
    /* $BC1C: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) goto label_BC8C;
label_BC1E:;
    /* $BC1E: 6C */ maybe_trigger_vblank(5); { uint16_t _jt = nes_read16_jmpbug(0x6C6E); maybe_trigger_vblank(2); call_by_address(_jt); return; }
label_BC21:;
    /* $BC21: 6E */ maybe_trigger_vblank(6); { uint16_t a=0x6E70; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BC24:;
    /* $BC24: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) goto label_BC94;
label_BC26:;
    /* $BC26: 6C */ maybe_trigger_vblank(5); { uint16_t _jt = nes_read16_jmpbug(0x7876); maybe_trigger_vblank(2); call_by_address(_jt); return; }
label_BC29:;
    /* $BC29: 76 */ maybe_trigger_vblank(6); { uint16_t a=(0x74 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BC2B:;
    /* $BC2B: 76 */ maybe_trigger_vblank(6); { uint16_t a=(0x74 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BC2D:;
    /* $BC2D: 72 */ maybe_trigger_vblank(2); /* ILLEGAL $72 — skip 1 */
label_BC2E:;
    /* $BC2E: 74 */ maybe_trigger_vblank(4); (void)nes_read((0x76 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC30:; /* GetSBNybbles */
    /* $BC30: 78 */ maybe_trigger_vblank(2); g_cpu.I = 1;
label_BC31:;
    /* $BC31: 76 */ maybe_trigger_vblank(6); { uint16_t a=(0x74 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BC33:;
    /* $BC33: 76 */ maybe_trigger_vblank(6); { uint16_t a=(0x74 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BC35:;
    /* $BC35: 72 */ maybe_trigger_vblank(2); /* ILLEGAL $72 — skip 1 */
label_BC36:; /* UpdateNumber */
    /* $BC36: 74 */ maybe_trigger_vblank(4); (void)nes_read((0x84 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC38:;
    /* $BC38: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BC39:;
    /* $BC39: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x18 + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_BC3B:;
    /* $BC3B: 20 */ maybe_trigger_vblank(6); call_by_address(0x1E84);
label_BC3E:;
    /* $BC3E: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x1C + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_BC40:;
    /* $BC40: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BC41:;
    /* $BC41: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x1C; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BC43:;
    /* $BC43: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BC44:;
    /* $BC44: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2C82 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC47:;
    /* $BC47: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC49:; /* SetupPowerUp */
    /* $BC49: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BC4A:;
    /* $BC4A: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC4C:;
    /* $BC4C: 84 */ maybe_trigger_vblank(3); nes_write(0x1C, g_cpu.Y);
label_BC4E:;
    /* $BC4E: 87 */ maybe_trigger_vblank(3); nes_write(0x26, g_cpu.A & g_cpu.X); /* SAX */
label_BC50:;
    /* $BC50: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BC51:;
    /* $BC51: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x84; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BC53:;
    /* $BC53: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x28); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BC55:;
    /* $BC55: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x80); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BC57:;
    /* $BC57: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BC58:;
    /* $BC58: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBC58); return;
label_BC59:;
    /* $BC59: 9C */ maybe_trigger_vblank(5); /* ILLEGAL $9C — skip 3 */
label_BC5C:;
    /* $BC5C: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x0D); FLAG_NZ(g_cpu.A);
label_BC5E:;
    /* $BC5E: 9F */ maybe_trigger_vblank(5); /* ILLEGAL $9F — skip 3 */
label_BC61:;
    /* $BC61: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_BC62:;
    /* $BC62: 9D */ maybe_trigger_vblank(5); nes_write((0x2282 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_BC65:;
    /* $BC65: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC67:;
    /* $BC67: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x0404 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC6A:;
    /* $BC6A: 84 */ maybe_trigger_vblank(3); nes_write(0x14, g_cpu.Y);
label_BC6C:;
    /* $BC6C: 86 */ maybe_trigger_vblank(3); nes_write(0x1E, g_cpu.X);
label_BC6E:;
    /* $BC6E: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BC70:;
    /* $BC70: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BC72:;
    /* $BC72: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x1C + g_cpu.X) & 0xFF), g_cpu.A);
label_BC74:;
    /* $BC74: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_BC7A;
label_BC76:;
    /* $BC76: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xBCA8); return; }
label_BC78:;
    /* $BC78: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x1E); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC7A:;
    /* $BC7A: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_BC7B:; /* PutBehind */
    /* $BC7B: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x32); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC7D:;
    /* $BC7D: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_BC7E:;
    /* $BC7E: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x20); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC80:;
    /* $BC80: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x04 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC82:;
    /* $BC82: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x34 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC84:;
    /* $BC84: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x36); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC86:;
    /* $BC86: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x84); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC88:;
    /* $BC88: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x00 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BC8A:;
    /* $BC8A: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xA4; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BC8C:;
    /* $BC8C: 64 */ maybe_trigger_vblank(3); (void)nes_read(0xA4); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC8E:;
    /* $BC8E: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_BC8F:;
    /* $BC8F: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x66); FLAG_NZ(g_cpu.X);
label_BC91:;
    /* $BC91: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x4A); FLAG_NZ(g_cpu.X);
label_BC93:;
    /* $BC93: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_BC94:;
    /* $BC94: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_BC95:;
    /* $BC95: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_BC96:;
    /* $BC96: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_BC97:;
    /* $BC97: 44 */ maybe_trigger_vblank(3); (void)nes_read(0x2B); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC99:;
    /* $BC99: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x2A + g_cpu.X) & 0xFF), g_cpu.A);
label_BC9B:;
    /* $BC9B: 42 */ maybe_trigger_vblank(2); /* ILLEGAL $42 — skip 1 */
label_BC9C:;
    /* $BC9C: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x42); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BC9E:;
    /* $BC9E: 42 */ maybe_trigger_vblank(2); /* ILLEGAL $42 — skip 1 */
label_BC9F:;
    /* $BC9F: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCA1:;
    /* $BCA1: 64 */ maybe_trigger_vblank(3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCA3:;
    /* $BCA3: 64 */ maybe_trigger_vblank(3); (void)nes_read(0x64); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCA5:;
    /* $BCA5: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2E); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCA7:;
    /* $BCA7: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BCA9:;
    /* $BCA9: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x46; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BCAB:;
    /* $BCAB: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCAD:;
    /* $BCAD: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x84); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCAF:;
    /* $BCAF: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BCB0:;
    /* $BCB0: 87 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A & g_cpu.X); /* SAX */
label_BCB2:;
    /* $BCB2: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x0C; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BCB4:;
    /* $BCB4: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x1C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCB6:;
    /* $BCB6: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BCB7:;
    /* $BCB7: 86 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.X);
label_BCB9:;
    /* $BCB9: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BCBA:;
    /* $BCBA: 87 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A & g_cpu.X); /* SAX */
label_BCBC:;
    /* $BCBC: 60 */ maybe_trigger_vblank(6);
    return;
label_BCBD:;
    /* $BCBD: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x1A14; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BCC0:;
    /* $BCC0: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x86); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BCC2:;
    /* $BCC2: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x8724); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BCC5:;
    /* $BCC5: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x08); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCC7:;
    /* $BCC7: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { call_by_address(0xBCE1); return; }
label_BCC9:;
    /* $BCC9: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x8628 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BCCC:;
    /* $BCCC: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xBCFE); return; }
label_BCCE:;
    /* $BCCE: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BCD0:;
    /* $BCD0: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBCD0); return;
label_BCD1:;
    /* $BCD1: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xDDD5); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_BCD4:;
    /* $BCD4: E3 */ maybe_trigger_vblank(8); /* ILLEGAL $E3 — skip 2 */
label_BCD6:;
    /* $BCD6: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xBB + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_BCD8:; /* RunPUSubs */
    /* $BCD8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_BCDA:;
    /* $BCDA: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDB + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_BCDC:;
    /* $BCDC: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xED); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_BCDE:;
    /* $BCDE: F3 */ maybe_trigger_vblank(8); /* ILLEGAL $F3 — skip 2 */
label_BCE0:;
    /* $BCE0: B3 */ maybe_trigger_vblank(5); g_cpu.A = g_cpu.X = nes_read((nes_read16zp(0xD1) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BCE2:;
    /* $BCE2: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE9DF + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_BCE5:;
    /* $BCE5: F1 */ maybe_trigger_vblank(5); { uint8_t m=nes_read((nes_read16zp(0xF7) + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_BCE7:;
    /* $BCE7: BF */ maybe_trigger_vblank(4); g_cpu.A = g_cpu.X = nes_read((0xFFFF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BCEA:; /* ExitPUp */
    /* $BCEA: FF */ maybe_trigger_vblank(7); /* ILLEGAL $FF — skip 3 */
label_BCED:; /* PlayerHeadCollision */
    /* $BCED: 86 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.X);
label_BCEF:;
    /* $BCEF: 87 */ maybe_trigger_vblank(3); nes_write(0x14, g_cpu.A & g_cpu.X); /* SAX */
label_BCF1:;
    /* $BCF1: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x8622 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCF4:;
    /* $BCF4: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x84 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCF6:;
    /* $BCF6: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0404); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BCF9:;
    /* $BCF9: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x87); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCFB:;
    /* $BCFB: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x1A + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BCFD:;
    /* $BCFD: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x86); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BCFF:;
    /* $BCFF: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_BD00:;
    /* $BD00: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_BD02:;
    /* $BD02: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x86); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD04:;
    /* $BD04: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x87); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD06:;
    /* $BD06: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BD07:;
    /* $BD07: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x8628 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD0A:;
    /* $BD0A: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x87 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD0C:;
    /* $BD0C: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xBD3E); return; }
label_BD0E:;
    /* $BD0E: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xBC90); return; }
label_BD10:;
    /* $BD10: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x1482); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD13:;
    /* $BD13: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2662); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD16:;
    /* $BD16: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_BD40;
label_BD18:;
    /* $BD18: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BD1A:; /* ChkBrick */
    /* $BD1A: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD1C:;
    /* $BD1C: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2662); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD1F:;
    /* $BD1F: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { call_by_address(0xBD49); return; }
label_BD21:;
    /* $BD21: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BD23:;
    /* $BD23: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD25:;
    /* $BD25: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x185E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD28:;
    /* $BD28: 60 */ maybe_trigger_vblank(6);
    return;
label_BD29:;
    /* $BD29: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BD2A:;
    /* $BD2A: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BD2C:; /* StartBTmr */
    /* $BD2C: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD2E:;
    /* $BD2E: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x185E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD31:;
    /* $BD31: 60 */ maybe_trigger_vblank(6);
    return;
label_BD32:;
    /* $BD32: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BD33:;
    /* $BD33: 86 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.X);
label_BD35:;
    /* $BD35: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x1A + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_BD37:;
    /* $BD37: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BD38:;
    /* $BD38: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x84 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD3A:;
    /* $BD3A: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x1A + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD3C:;
    /* $BD3C: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BD3D:;
    /* $BD3D: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x160C; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD40:; /* PutOldMT */
    /* $BD40: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x14 + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_BD42:;
    /* $BD42: 20 */ maybe_trigger_vblank(6); call_by_address(0x1C1E);
label_BD45:;
    /* $BD45: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BD46:;
    /* $BD46: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x87; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD48:;
    /* $BD48: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x1A); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD4A:;
    /* $BD4A: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_BD4B:;
    /* $BD4B: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_BDAF;
label_BD4D:;
    /* $BD4D: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x0480; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD50:;
    /* $BD50: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD52:;
    /* $BD52: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD54:;
    /* $BD54: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2220 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD57:;
    /* $BD57: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x28; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD59:;
    /* $BD59: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x2A + g_cpu.X) & 0xFF), g_cpu.A);
label_BD5B:;
    /* $BD5B: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BD5C:;
    /* $BD5C: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BD5D:;
    /* $BD5D: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2A); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD5F:;
    /* $BD5F: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x83); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD61:; /* SmallBP */
    /* $BD61: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BD62:; /* BigBP */
    /* $BD62: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD64:;
    /* $BD64: 86 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.X);
label_BD66:;
    /* $BD66: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_BD67:;
    /* $BD67: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x81 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD69:;
    /* $BD69: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD6B:;
    /* $BD6B: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x2A; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD6D:;
    /* $BD6D: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x8630); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD70:;
    /* $BD70: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x83 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD72:;
    /* $BD72: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_BD73:;
    /* $BD73: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD75:;
    /* $BD75: 84 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.Y);
label_BD77:;
    /* $BD77: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_BD79:;
    /* $BD79: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x22 + g_cpu.X) & 0xFF), g_cpu.A);
label_BD7B:; /* InvOBit */
    /* $BD7B: 86 */ maybe_trigger_vblank(3); nes_write(0x30, g_cpu.X);
label_BD7D:;
    /* $BD7D: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x8130; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD80:;
    /* $BD80: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BD82:;
    /* $BD82: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x2A; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BD84:; /* InitBlock_XY_Pos */
    /* $BD84: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x862E); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BD87:;
    /* $BD87: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BD0C;
    }
label_BD89:;
    /* $BD89: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BD8A:;
    /* $BD8A: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD8C:;
    /* $BD8C: 84 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.Y);
label_BD8E:;
    /* $BD8E: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_BD90:;
    /* $BD90: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x22 + g_cpu.X) & 0xFF), g_cpu.A);
label_BD92:;
    /* $BD92: 86 */ maybe_trigger_vblank(3); nes_write(0x3A, g_cpu.X);
label_BD94:;
    /* $BD94: 3A */ maybe_trigger_vblank(2); /* NOP */
label_BD95:;
    /* $BD95: 3A */ maybe_trigger_vblank(2); /* NOP */
label_BD96:;
    /* $BD96: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD98:;
    /* $BD98: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x40 + g_cpu.X) & 0xFF), g_cpu.A);
label_BD9A:;
    /* $BD9A: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BD9C:;
    /* $BD9C: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x3A + g_cpu.X) & 0xFF), g_cpu.A);
label_BD9E:;
    /* $BD9E: 86 */ maybe_trigger_vblank(3); nes_write(0x36, g_cpu.X);
label_BDA0:;
    /* $BDA0: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x36 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BDA2:;
    /* $BDA2: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BDA4:;
    /* $BDA4: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x3A + g_cpu.X) & 0xFF), g_cpu.A);
label_BDA6:;
    /* $BDA6: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BDA8:;
    /* $BDA8: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x36 + g_cpu.X) & 0xFF), g_cpu.A);
label_BDAA:;
    /* $BDAA: 86 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.X);
label_BDAC:;
    /* $BDAC: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BDAE:;
    /* $BDAE: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BDAF:;
    /* $BDAF: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x81 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BDB1:;
    /* $BDB1: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x34 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BDB3:;
    /* $BDB3: 85 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.A);
label_BDB5:;
    /* $BDB5: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x2A + g_cpu.X) & 0xFF), g_cpu.A);
label_BDB7:;
    /* $BDB7: 86 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.X);
label_BDB9:;
    /* $BDB9: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBDB9); return;
label_BDBA:;
    /* $BDBA: 84 */ maybe_trigger_vblank(3); nes_write(0x90, g_cpu.Y);
label_BDBC:;
    /* $BDBC: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BD42;
    }
label_BDBE:;
    /* $BDBE: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) { call_by_address(0xBE10); return; }
label_BDC0:;
    /* $BDC0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_BDC2;
label_BDC2:;
    /* $BDC2: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_BDC3:;
    /* $BDC3: 96 */ maybe_trigger_vblank(4); nes_write((0x94 + g_cpu.Y) & 0xFF, g_cpu.X);
label_BDC5:;
    /* $BDC5: 92 */ maybe_trigger_vblank(2); /* ILLEGAL $92 — skip 1 */
label_BDC6:;
    /* $BDC6: 94 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.X) & 0xFF, g_cpu.Y);
label_BDC8:;
    /* $BDC8: 58 */ maybe_trigger_vblank(2); g_cpu.I = 0;
label_BDC9:;
    /* $BDC9: 58 */ maybe_trigger_vblank(2); g_cpu.I = 0;
label_BDCA:;
    /* $BDCA: 58 */ maybe_trigger_vblank(2); g_cpu.I = 0;
label_BDCB:;
    /* $BDCB: 44 */ maybe_trigger_vblank(3); (void)nes_read(0x5C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BDCD:;
    /* $BDCD: 44 */ maybe_trigger_vblank(3); (void)nes_read(0x9F); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BDCF:;
    /* $BDCF: A3 */ maybe_trigger_vblank(6); g_cpu.A = g_cpu.X = nes_read(nes_read16zp((0xA1 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BDD1:;
    /* $BDD1: A3 */ maybe_trigger_vblank(6); g_cpu.A = g_cpu.X = nes_read(nes_read16zp((0x85 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BDD3:;
    /* $BDD3: A3 */ maybe_trigger_vblank(6); g_cpu.A = g_cpu.X = nes_read(nes_read16zp((0xE0 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BDD5:; /* StarBlock */
    /* $BDD5: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x23); FLAG_NZ(g_cpu.X);
label_BDD7:;
    /* $BDD7: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x9F); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_BDD9:;
    /* $BDD9: 9D */ maybe_trigger_vblank(5); nes_write((0x859F + g_cpu.X) & 0xFFFF, g_cpu.A);
label_BDDC:;
    /* $BDDC: 9F */ maybe_trigger_vblank(5); /* ILLEGAL $9F — skip 3 */
label_BDDF:; /* VineBlock */
    /* $BDDF: 23 */ maybe_trigger_vblank(8); /* ILLEGAL $23 — skip 2 */
label_BDE1:;
    /* $BDE1: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xB1 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_BDE3:;
    /* $BDE3: AF */ maybe_trigger_vblank(4); g_cpu.A = g_cpu.X = nes_read(0xB185); FLAG_NZ(g_cpu.A);
label_BDE6:;
    /* $BDE6: AF */ maybe_trigger_vblank(4); g_cpu.A = g_cpu.X = nes_read(0x85AD); FLAG_NZ(g_cpu.A);
label_BDE9:;
    /* $BDE9: 95 */ maybe_trigger_vblank(4); nes_write((0x9E + g_cpu.X) & 0xFF, g_cpu.A);
label_BDEB:;
    /* $BDEB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xAA; FLAG_NZ(g_cpu.X);
label_BDED:;
    /* $BDED: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_BDEE:;
    /* $BDEE: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_BDEF:;
    /* $BDEF: 6B */ maybe_trigger_vblank(2); /* ILLEGAL $6B — skip 2 */
label_BDF1:;
    /* $BDF1: 9D */ maybe_trigger_vblank(5); nes_write((0x0484 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_BDF4:;
    /* $BDF4: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x82); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BDF6:; /* BlockBumpedChk */
    /* $BDF6: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BDF7:;
    /* $BDF7: 86 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.X);
label_BDF9:;
    /* $BDF9: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BDFB:;
    /* $BDFB: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BDFC:;
    /* $BDFC: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2212); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BDFF:;
    /* $BDFF: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE00:;
    /* $BE00: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x22 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE02:; /* BrickShatter */
    /* $BE02: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x221C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE05:;
    /* $BE05: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2214); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE08:;
    /* $BE08: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2212); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE0B:;
    /* $BE0B: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE0C:;
    /* $BE0C: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x22 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE0E:;
    /* $BE0E: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x221C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE11:;
    /* $BE11: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2218); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE14:;
    /* $BE14: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE15:;
    /* $BE15: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x20 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE17:;
    /* $BE17: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BE18:;
    /* $BE18: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BE19:;
    /* $BE19: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE1A:;
    /* $BE1A: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE1B:;
    /* $BE1B: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_BE1C:;
    /* $BE1C: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE1D:;
    /* $BE1D: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE1E:;
    /* $BE1E: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BE1F:; /* CheckTopOfBlock */
    /* $BE1F: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE20:;
    /* $BE20: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE21:;
    /* $BE21: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_BE22:;
    /* $BE22: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE23:;
    /* $BE23: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BE24:;
    /* $BE24: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x22 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE26:;
    /* $BE26: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x220C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE29:;
    /* $BE29: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2214); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BE2C:;
    /* $BE2C: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x12 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE2E:;
    /* $BE2E: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE2F:;
    /* $BE2F: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_BE41;
label_BE31:;
    /* $BE31: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE32:;
    /* $BE32: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x2216; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE35:;
    /* $BE35: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x18 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE37:;
    /* $BE37: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x36; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE39:;
    /* $BE39: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x26 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE3B:;
    /* $BE3B: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x14 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE3D:;
    /* $BE3D: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x36; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE3F:;
    /* $BE3F: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_BE40:; /* TopEx */
    /* $BE40: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE41:; /* SpawnBrickChunks */
    /* $BE41: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x5C + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE43:;
    /* $BE43: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE44:;
    /* $BE44: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x0C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE46:;
    /* $BE46: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE47:;
    /* $BE47: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE48:;
    /* $BE48: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x1E + g_cpu.X) & 0xFF), g_cpu.A);
label_BE4A:;
    /* $BE4A: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1E85 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE4D:;
    /* $BE4D: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x12 + g_cpu.X) & 0xFF), g_cpu.A);
label_BE4F:;
    /* $BE4F: 86 */ maybe_trigger_vblank(3); nes_write(0x14, g_cpu.X);
label_BE51:;
    /* $BE51: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x2C + g_cpu.X) & 0xFF), g_cpu.A);
label_BE53:;
    /* $BE53: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE54:;
    /* $BE54: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x222C + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE57:;
    /* $BE57: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2C85 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE5A:;
    /* $BE5A: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x81); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE5C:;
    /* $BE5C: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x1E24; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE5F:;
    /* $BE5F: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x1E24; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE62:;
    /* $BE62: 85 */ maybe_trigger_vblank(3); nes_write(0x2E, g_cpu.A);
label_BE64:;
    /* $BE64: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x81); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE66:;
    /* $BE66: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_BE67:;
    /* $BE67: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BE68:;
    /* $BE68: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE69:;
    /* $BE69: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_BE6A:;
    /* $BE6A: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BE6B:;
    /* $BE6B: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE6C:;
    /* $BE6C: 85 */ maybe_trigger_vblank(3); nes_write(0x32, g_cpu.A);
label_BE6E:;
    /* $BE6E: 87 */ maybe_trigger_vblank(3); nes_write(0x36, g_cpu.A & g_cpu.X); /* SAX */
label_BE70:; /* BlockObjectsCore */
    /* $BE70: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x36 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE72:;
    /* $BE72: 84 */ maybe_trigger_vblank(3); nes_write(0x3A, g_cpu.Y);
label_BE74:;
    /* $BE74: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBE74); return;
label_BE75:;
    /* $BE75: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x4C54 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE78:;
    /* $BE78: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x4C54 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE7B:;
    /* $BE7B: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x1C1C + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE7E:;
    /* $BE7E: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x5C5C + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE81:;
    /* $BE81: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x565E + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BE84:;
    /* $BE84: 4E */ maybe_trigger_vblank(6); { uint16_t a=0x565E; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BE87:;
    /* $BE87: 4E */ maybe_trigger_vblank(6); { uint16_t a=0x1E5E; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BE8A:;
    /* $BE8A: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x5E5E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BE8D:;
    /* $BE8D: 5E */ maybe_trigger_vblank(7); { uint16_t a=(0x625E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_BE90:;
    /* $BE90: 5A */ maybe_trigger_vblank(2); /* NOP */
label_BE91:;
    /* $BE91: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) goto label_BEF5;
label_BE93:;
    /* $BE93: 5A */ maybe_trigger_vblank(2); /* NOP */
label_BE94:;
    /* $BE94: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) { call_by_address(0xBEF8); return; }
label_BE96:;
    /* $BE96: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE97:;
    /* $BE97: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BE98:;
    /* $BE98: 62 */ maybe_trigger_vblank(2); /* ILLEGAL $62 — skip 1 */
label_BE99:;
    /* $BE99: E7 */ maybe_trigger_vblank(5); /* ILLEGAL $E7 — skip 2 */
label_BE9B:;
    /* $BE9B: E7 */ maybe_trigger_vblank(5); /* ILLEGAL $E7 — skip 2 */
label_BE9D:;
    /* $BE9D: 86 */ maybe_trigger_vblank(3); nes_write(0x14, g_cpu.X);
label_BE9F:;
    /* $BE9F: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x14 + g_cpu.X) & 0xFF), g_cpu.A);
label_BEA1:;
    /* $BEA1: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BEA3:;
    /* $BEA3: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x81 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEA5:;
    /* $BEA5: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x14 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEA7:;
    /* $BEA7: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x14 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEA9:;
    /* $BEA9: 86 */ maybe_trigger_vblank(3); nes_write(0x16, g_cpu.X);
label_BEAB:;
    /* $BEAB: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x16 + g_cpu.X) & 0xFF), g_cpu.A);
label_BEAD:;
    /* $BEAD: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BEAF:;
    /* $BEAF: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x81 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEB1:;
    /* $BEB1: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x16 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEB3:; /* BouncingBlockHandler */
    /* $BEB3: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x16 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEB5:;
    /* $BEB5: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x28 + g_cpu.X) & 0xFF), g_cpu.A);
label_BEB7:;
    /* $BEB7: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BEB8:;
    /* $BEB8: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BEB9:;
    /* $BEB9: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BEBA:;
    /* $BEBA: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BEBB:;
    /* $BEBB: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BEBC:;
    /* $BEBC: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BEBD:;
    /* $BEBD: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BEBF:;
    /* $BEBF: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_BEC0:;
    /* $BEC0: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x28 + g_cpu.X) & 0xFF), g_cpu.A);
label_BEC2:;
    /* $BEC2: 87 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.A & g_cpu.X); /* SAX */
label_BEC4:;
    /* $BEC4: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x842C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BEC7:;
    /* $BEC7: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xBE4C); return; }
label_BEC9:;
    /* $BEC9: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x84); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BECB:;
    /* $BECB: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x6283); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BECE:;
    /* $BECE: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BE54;
    }
label_BED0:;
    /* $BED0: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_BED1:; /* UpdSte */
    /* $BED1: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x1C + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_BED3:;
    /* $BED3: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BED4:; /* BlockObjMT_Updater */
    /* $BED4: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x2622 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BED7:;
    /* $BED7: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BED8:;
    /* $BED8: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1C04 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEDB:;
    /* $BEDB: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBEDB); return;
label_BEDC:;
    /* $BEDC: E3 */ maybe_trigger_vblank(8); /* ILLEGAL $E3 — skip 2 */
label_BEDE:;
    /* $BEDE: E3 */ maybe_trigger_vblank(8); /* ILLEGAL $E3 — skip 2 */
label_BEE0:;
    /* $BEE0: DE */ maybe_trigger_vblank(7); { uint16_t a=(0x23E0 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEE3:;
    /* $BEE3: EC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x7475); int r=g_cpu.X-m; g_cpu.C=(g_cpu.X>=m)?1:0; FLAG_NZ(r&0xFF); }
label_BEE6:;
    /* $BEE6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BEDC;
    }
label_BEE8:;
    /* $BEE8: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0xEA + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEEA:;
    /* $BEEA: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x2D) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BEEC:;
    /* $BEEC: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x12 + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_BEEE:;
    /* $BEEE: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x04 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEF0:;
    /* $BEF0: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BEF1:;
    /* $BEF1: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BEF2:;
    /* $BEF2: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2614 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEF5:;
    /* $BEF5: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_BEF6:;
    /* $BEF6: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x181C + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEF9:;
    /* $BEF9: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x0C22 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BEFC:;
    /* $BEFC: 14 */ maybe_trigger_vblank(4); (void)nes_read((0xFF + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BEFE:; /* NextBUpd */
    /* $BEFE: FF */ maybe_trigger_vblank(7); /* ILLEGAL $FF — skip 3 */
label_BF01:;
    /* $BF01: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_BF02:; /* MoveEnemyHorizontally */
    /* $BF02: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBF02); return;
label_BF03:;
    /* $BF03: 2F */ maybe_trigger_vblank(6); /* ILLEGAL $2F — skip 3 */
label_BF06:;
    /* $BF06: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_BF07:;
    /* $BF07: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x02); FLAG_NZ(g_cpu.X);
label_BF09:; /* MovePlayerHorizontally */
    /* $BF09: 80 */ maybe_trigger_vblank(2); /* NOP */
label_BF0B:;
    /* $BF0B: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x3A02 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BF0E:;
    /* $BF0E: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_BF0F:; /* MoveObjectHorizontally */
    /* $BF0F: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BF10:;
    /* $BF10: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0xDF + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BF12:;
    /* $BF12: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0xC4 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BF14:;
    /* $BF14: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0xAB + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BF16:;
    /* $BF16: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x93 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BF18:;
    /* $BF18: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x7C + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BF1A:;
    /* $BF1A: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x67 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BF1C:;
    /* $BF1C: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x53 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BF1E:;
    /* $BF1E: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x40 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BF20:;
    /* $BF20: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x2E + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BF22:;
    /* $BF22: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x1D + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BF24:;
    /* $BF24: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x0D + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BF26:;
    /* $BF26: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBF26); return;
label_BF27:;
    /* $BF27: FE */ maybe_trigger_vblank(7); { uint16_t a=(0xEF00 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BF2A:;
    /* $BF2A: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBF2A); return;
label_BF2B:;
    /* $BF2B: E2 */ maybe_trigger_vblank(2); /* NOP */
label_BF2D:;
    /* $BF2D: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x00 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_BF2F:;
    /* $BF2F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_BF31:;
    /* $BF31: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xB300 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_BF34:;
    /* $BF34: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBF34); return;
label_BF35:;
    /* $BF35: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_BF37:;
    /* $BF37: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_BF39:;
    /* $BF39: 97 */ maybe_trigger_vblank(4); nes_write((0x00 + g_cpu.Y) & 0xFF, g_cpu.A & g_cpu.X); /* SAX */
label_BF3B:;
    /* $BF3B: 8E */ maybe_trigger_vblank(4); nes_write(0x8600, g_cpu.X);
label_BF3E:;
    /* $BF3E: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBF3E); return;
label_BF3F:;
    /* $BF3F: 77 */ maybe_trigger_vblank(6); /* ILLEGAL $77 — skip 2 */
label_BF41:;
    /* $BF41: 7E */ maybe_trigger_vblank(7); { uint16_t a=(0x7100 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BF44:;
    /* $BF44: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBF44); return;
label_BF45:;
    /* $BF45: 54 */ maybe_trigger_vblank(4); (void)nes_read((0x00 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BF47:;
    /* $BF47: 64 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BF49:;
    /* $BF49: 5F */ maybe_trigger_vblank(7); /* ILLEGAL $5F — skip 3 */
label_BF4C:; /* ExXMove */
    /* $BF4C: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBF4C); return;
label_BF4D:; /* MovePlayerVertically */
    /* $BF4D: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) goto label_BF4F;
label_BF4F:;
    /* $BF4F: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_BF51:;
    /* $BF51: 43 */ maybe_trigger_vblank(8); /* ILLEGAL $43 — skip 2 */
label_BF53:;
    /* $BF53: 3B */ maybe_trigger_vblank(7); /* ILLEGAL $3B — skip 3 */
label_BF56:;
    /* $BF56: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBF56); return;
label_BF57:;
    /* $BF57: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_BF58:;
    /* $BF58: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBF58); return;
label_BF59:; /* NoJSChk */
    /* $BF59: 23 */ maybe_trigger_vblank(8); /* ILLEGAL $23 — skip 2 */
label_BF5B:;
    /* $BF5B: 75 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x03 + g_cpu.X) & 0xFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_BF5D:;
    /* $BF5D: 57 */ maybe_trigger_vblank(6); /* ILLEGAL $57 — skip 2 */
label_BF5F:;
    /* $BF5F: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xCF02 + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_BF62:;
    /* $BF62: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0xFC + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BF64:;
    /* $BF64: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBF64); return;
label_BF65:;
    /* $BF65: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_BF66:;
    /* $BF66: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x0A); FLAG_NZ(g_cpu.A);
label_BF68:;
    /* $BF68: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x28 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BF6A:;
    /* $BF6A: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) goto label_BF8A;
label_BF6C:;
    /* $BF6C: 3C */ maybe_trigger_vblank(4); (void)nes_read((0x0402 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BF6F:;
    /* $BF6F: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_BF70:; /* MoveRedPTroopaDown */
    /* $BF70: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_BF92;
label_BF72:;
    /* $BF72: 40 */ maybe_trigger_vblank(6); /* RTI */ g_cpu.S++; { uint8_t p=g_ram[0x100+g_cpu.S]; g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1; g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; } g_cpu.S++; g_cpu.S++; /* pop PCL, PCH */
    return;
label_BF73:;
    /* $BF73: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BF74:;
    /* $BF74: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_BF82;
label_BF76:;
    /* $BF76: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_BF78:;
    /* $BF78: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x3018); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BF7B:;
    /* $BF7B: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_BF7C:;
    /* $BF7C: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x08); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BF7E:;
    /* $BF7E: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x03 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BF80:;
    /* $BF80: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x06; FLAG_NZ(g_cpu.A);
label_BF82:;
    /* $BF82: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_BF83:;
    /* $BF83: 1B */ maybe_trigger_vblank(7); /* ILLEGAL $1B — skip 3 */
label_BF86:;
    /* $BF86: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x02); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_BF88:; /* MoveDropPlatform */
    /* $BF88: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BF8A:;
    /* $BF8A: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x1812); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BF8D:;
    /* $BF8D: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_BF8E:; /* SetMdMax */
    /* $BF8E: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_BF8F:;
    /* $BF8F: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x03 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_BF91:;
    /* $BF91: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_BF92:; /* MoveJ_EnemyVertically */
    /* $BF92: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x09; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BF94:; /* SetHiMax */
    /* $BF94: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x9804); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BF97:;
    /* $BF97: 99 */ maybe_trigger_vblank(5); nes_write((0x9B9A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_BF9A:;
    /* $BF9A: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { call_by_address(0xBF30); return; }
label_BF9C:;
    /* $BF9C: 94 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.X) & 0xFF, g_cpu.Y);
label_BF9E:;
    /* $BF9E: 95 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.X) & 0xFF, g_cpu.A);
label_BFA0:;
    /* $BFA0: 97 */ maybe_trigger_vblank(4); nes_write((0x98 + g_cpu.Y) & 0xFF, g_cpu.A & g_cpu.X); /* SAX */
label_BFA2:;
    /* $BFA2: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_BF35;
    }
label_BFA4:; /* ImposeGravityBlock */
    /* $BFA4: 92 */ maybe_trigger_vblank(2); /* ILLEGAL $92 — skip 1 */
label_BFA5:;
    /* $BFA5: 92 */ maybe_trigger_vblank(2); /* ILLEGAL $92 — skip 1 */
label_BFA6:;
    /* $BFA6: 93 */ maybe_trigger_vblank(6); /* ILLEGAL $93 — skip 2 */
label_BFA8:;
    /* $BFA8: 93 */ maybe_trigger_vblank(6); /* ILLEGAL $93 — skip 2 */
label_BFAA:;
    /* $BFAA: 94 */ maybe_trigger_vblank(4); nes_write((0x94 + g_cpu.X) & 0xFF, g_cpu.Y);
label_BFAC:;
    /* $BFAC: 94 */ maybe_trigger_vblank(4); nes_write((0x94 + g_cpu.X) & 0xFF, g_cpu.Y);
label_BFAE:;
    /* $BFAE: 94 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.X) & 0xFF, g_cpu.Y);
label_BFB0:;
    /* $BFB0: 95 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.X) & 0xFF, g_cpu.A);
label_BFB2:;
    /* $BFB2: 95 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.X) & 0xFF, g_cpu.A);
label_BFB4:; /* MovePlatformDown */
    /* $BFB4: 95 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.X) & 0xFF, g_cpu.A);
label_BFB6:;
    /* $BFB6: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_BFB8:;
    /* $BFB8: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_BFBA:;
    /* $BFBA: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_BFBC:;
    /* $BFBC: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_BFBE:;
    /* $BFBE: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_BFC0:;
    /* $BFC0: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_BFC2:;
    /* $BFC2: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_BFC4:;
    /* $BFC4: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_BFC6:;
    /* $BFC6: 95 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.X) & 0xFF, g_cpu.A);
label_BFC8:;
    /* $BFC8: 94 */ maybe_trigger_vblank(4); nes_write((0x93 + g_cpu.X) & 0xFF, g_cpu.Y);
label_BFCA:;
    /* $BFCA: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_BFCC:;
    /* $BFCC: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x17 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFCE:;
    /* $BFCE: 17 */ maybe_trigger_vblank(6); /* ILLEGAL $17 — skip 2 */
label_BFD0:;
    /* $BFD0: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x1A19 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BFD3:;
    /* $BFD3: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BFD4:;
    /* $BFD4: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x1D1D + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BFD7:; /* ImposeGravity */
    /* $BFD7: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1F1E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFDA:;
    /* $BFDA: 1F */ maybe_trigger_vblank(7); /* ILLEGAL $1F — skip 3 */
label_BFDD:;
    /* $BFDD: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1C1D + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFE0:;
    /* $BFE0: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1F1F + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFE3:;
    /* $BFE3: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1C1D + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFE6:;
    /* $BFE6: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BFE7:;
    /* $BFE7: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_BFE8:;
    /* $BFE8: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x14 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFEA:;
    /* $BFEA: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_BFEC:;
    /* $BFEC: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x17 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFEE:;
    /* $BFEE: 17 */ maybe_trigger_vblank(6); /* ILLEGAL $17 — skip 2 */
label_BFF0:;
    /* $BFF0: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x1A19 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_BFF3:;
    /* $BFF3: 1A */ maybe_trigger_vblank(2); /* NOP */
label_BFF4:;
    /* $BFF4: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x1D1D + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_BFF7:;
    /* $BFF7: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1F1E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_BFFA:;
    /* $BFFA: 82 */ maybe_trigger_vblank(2); /* NOP */
label_BFFC:;
    /* $BFFC: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xBFFC); return;
}

void FinalBodies::body_c11_e_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C120;
    }
label_C11E:;
    /* $C11E: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x20; g_cpu.C=(g_cpu.Y>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_C120:;
    /* $C120: 71 */ maybe_trigger_vblank(5); { uint8_t m=nes_read((nes_read16zp(0xD0) + g_cpu.Y) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
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
    /* $C1A8: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xC0CC); return;
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

void FinalBodies::body_c4_ce_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C4D0;
    }
label_C4CE:;
    /* $C4CE: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_C4D0:;
    /* $C4D0: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xC4D0); return;
}

void FinalBodies::body_c8_dc_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C8E1;
    }
label_C8DC:;
    /* $C8DC: F1 */ maybe_trigger_vblank(5); { uint8_t m=nes_read((nes_read16zp(0x4C) + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C8DE:;
    /* $C8DE: 7D */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xA9E8 + g_cpu.X) & 0xFFFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_C8E1:;
    /* $C8E1: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xC8E1); return;
}

void FinalBodies::body_c923_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C927;
        case 2: goto label_C930;
    }
label_C923:;
    /* $C923: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0xB0; g_cpu.C=(g_cpu.A>=0xB0)?1:0; FLAG_NZ(r&0xFF); }
label_C925:;
    /* $C925: D3 */ maybe_trigger_vblank(8); /* ILLEGAL $D3 — skip 2 */
label_C927:;
    /* $C927: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_C928:;
    /* $C928: FF */ maybe_trigger_vblank(7); /* ILLEGAL $FF — skip 3 */
label_C92B:;
    /* $C92B: CB */ maybe_trigger_vblank(2); /* ILLEGAL $CB — skip 2 */
label_C92D:;
    /* $C92D: CF */ maybe_trigger_vblank(6); /* ILLEGAL $CF — skip 3 */
label_C930:;
    /* $C930: 34 */ maybe_trigger_vblank(4); (void)nes_read((0xC9 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_C932:;
    /* $C932: DF */ maybe_trigger_vblank(7); /* ILLEGAL $DF — skip 3 */
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

void FinalBodies::body_c9_f0_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_C9FA;
        case 2: goto label_C9F4;
        case 3: goto label_C9F2;
    }
label_C9F0:;
    /* $C9F0: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_C9F2:;
    /* $C9F2: 17 */ maybe_trigger_vblank(6); /* ILLEGAL $17 — skip 2 */
label_C9F4:;
    /* $C9F4: CC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xB906); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_C9F7:;
    /* $C9F7: CE */ maybe_trigger_vblank(6); { uint16_t a=0x9DC9; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_C9FA:;
    /* $C9FA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
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
}

void FinalBodies::body_ca47_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_CA49;
    }
label_CA47:;
    /* $CA47: 06 */ maybe_trigger_vblank(5); { uint16_t a=0xD0; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_CA49:;
    /* $CA49: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0xA8 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
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
}

void FinalBodies::body_d0_c7_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_D0C9;
    }
label_D0C7:;
    /* $D0C7: 07 */ maybe_trigger_vblank(5); /* ILLEGAL $07 — skip 2 */
label_D0C9:;
    /* $D0C9: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { call_by_address(0xD0D2); return; }
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
}

void FinalBodies::body_d3_d2_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_D3D4;
    }
label_D3D2:;
    /* $D3D2: 21 */ maybe_trigger_vblank(6); g_cpu.A &= nes_read(nes_read16zp((0x90 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_D3D4:;
    /* $D3D4: 35 */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xB5 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_D3D6:;
    /* $D3D6: 58 */ maybe_trigger_vblank(2); g_cpu.I = 0;
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
}

void FinalBodies::body_e1_ac_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_E1AF;
    }
label_E1AC:;
    /* $E1AC: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0xA960 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E1AF:;
    /* $E1AF: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xE1AF); return;
}

void FinalBodies::body_e23_e_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_E244;
    }
label_E23E:;
    /* $E23E: 9C */ maybe_trigger_vblank(5); /* ILLEGAL $9C — skip 3 */
label_E241:;
    /* $E241: DE */ maybe_trigger_vblank(7); { uint16_t a=(0xA0E2 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_E244:;
    /* $E244: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_E245:;
    /* $E245: 84 */ maybe_trigger_vblank(3); nes_write(0x00, g_cpu.Y);
label_E247:;
    /* $E247: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x44; FLAG_NZ(g_cpu.Y);
label_E249:;
    /* $E249: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xE252); return;
}

void FinalBodies::body_e7_b3_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_E7D1;
        case 2: goto label_E7DE;
    }
label_E7B3:;
    /* $E7B3: F4 */ maybe_trigger_vblank(4); (void)nes_read((0xF5 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7B5:;
    /* $E7B5: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xFC + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7B7:;
    /* $E7B7: FC */ maybe_trigger_vblank(4); (void)nes_read((0xF4F4 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7BA:;
    /* $E7BA: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xF5 + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7BC:;
    /* $E7BC: FC */ maybe_trigger_vblank(4); (void)nes_read((0xF5FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7BF:;
    /* $E7BF: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xF4 + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_E7C1:;
    /* $E7C1: F4 */ maybe_trigger_vblank(4); (void)nes_read((0xFC + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7C3:;
    /* $E7C3: FC */ maybe_trigger_vblank(4); (void)nes_read((0xF5F5 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7C6:;
    /* $E7C6: F4 */ maybe_trigger_vblank(4); (void)nes_read((0xF4 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7C8:;
    /* $E7C8: FC */ maybe_trigger_vblank(4); (void)nes_read((0xFCFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7CB:;
    /* $E7CB: FC */ maybe_trigger_vblank(4); (void)nes_read((0xEFEF + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7CE:;
    /* $E7CE: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xBBB8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_E7D1:;
    /* $E7D1: BA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.S; FLAG_NZ(g_cpu.X);
label_E7D2:;
    /* $E7D2: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0xFCBC + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E7D5:;
    /* $E7D5: FC */ maybe_trigger_vblank(4); (void)nes_read((0xBDBD + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_E7D8:;
    /* $E7D8: BC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read((0x7ABC + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.Y);
label_E7DB:;
    /* $E7DB: 7B */ maybe_trigger_vblank(7); /* ILLEGAL $7B — skip 3 */
label_E7DE:;
    /* $E7DE: D8 */ maybe_trigger_vblank(2); g_cpu.D = 0;
label_E7DF:;
    /* $E7DF: D8 */ maybe_trigger_vblank(2); g_cpu.D = 0;
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
    { g_cpu.S++; uint8_t _lo=g_ram[0x100+g_cpu.S]; g_cpu.S++; uint8_t _hi=g_ram[0x100+g_cpu.S]; call_by_address(((uint16_t)_hi<<8|_lo)+1); }
    return;
label_EBA9:; /* ExEGHandler */
    /* $EBA9: 60 */ maybe_trigger_vblank(6);
    return;
}

void FinalBodies::body_ee5_b_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_EE61;
        case 2: goto label_EEB6;
        case 3: goto label_EED1;
    }
label_EE5B:;
    /* $EE5B: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_EE5C:;
    /* $EE5C: 2B */ maybe_trigger_vblank(2); /* ILLEGAL $2B — skip 2 */
label_EE5E:;
    /* $EE5E: 5D */ maybe_trigger_vblank(4); g_cpu.A ^= nes_read((0x0908 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EE61:;
    /* $EE61: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_EE62:;
    /* $EE62: 0B */ maybe_trigger_vblank(2); /* ILLEGAL $0B — skip 2 */
label_EE64:;
    /* $EE64: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x5F5E); FLAG_NZ(g_cpu.A);
label_EE67:;
    /* $EE67: FC */ maybe_trigger_vblank(4); (void)nes_read((0x08FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EE6A:;
    /* $EE6A: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x58; FLAG_NZ(g_cpu.A);
label_EE6C:;
    /* $EE6C: 59 */ maybe_trigger_vblank(4); g_cpu.A ^= nes_read((0x5A5A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EE6F:;
    /* $EE6F: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_EE70:;
    /* $EE70: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x28; FLAG_NZ(g_cpu.A);
label_EE72:;
    /* $EE72: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x2A; FLAG_NZ(g_cpu.A);
label_EE74:;
    /* $EE74: 2B */ maybe_trigger_vblank(2); /* ILLEGAL $2B — skip 2 */
label_EE76:;
    /* $EE76: 0F */ maybe_trigger_vblank(6); /* ILLEGAL $0F — skip 3 */
label_EE79:;
    /* $EE79: FC */ maybe_trigger_vblank(4); (void)nes_read((0x32FC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EE7C:;
    /* $EE7C: 33 */ maybe_trigger_vblank(8); /* ILLEGAL $33 — skip 2 */
label_EE7E:;
    /* $EE7E: 35 */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xFC + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_EE80:;
    /* $EE80: FC */ maybe_trigger_vblank(4); (void)nes_read((0xFCFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EE83:;
    /* $EE83: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x37 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_EE85:;
    /* $EE85: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_EE86:;
    /* $EE86: 39 */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0xFCFC + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_EE89:;
    /* $EE89: FC */ maybe_trigger_vblank(4); (void)nes_read((0x3AFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EE8C:;
    /* $EE8C: 37 */ maybe_trigger_vblank(6); /* ILLEGAL $37 — skip 2 */
label_EE8E:;
    /* $EE8E: 3C */ maybe_trigger_vblank(4); (void)nes_read((0xFCFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EE91:;
    /* $EE91: FC */ maybe_trigger_vblank(4); (void)nes_read((0x3DFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EE94:;
    /* $EE94: 3E */ maybe_trigger_vblank(7); { uint16_t a=(0x403F + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_EE97:;
    /* $EE97: FC */ maybe_trigger_vblank(4); (void)nes_read((0xFCFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EE9A:;
    /* $EE9A: FC */ maybe_trigger_vblank(4); (void)nes_read((0x4132 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EE9D:;
    /* $EE9D: 42 */ maybe_trigger_vblank(2); /* ILLEGAL $42 — skip 1 */
label_EE9E:;
    /* $EE9E: 43 */ maybe_trigger_vblank(8); /* ILLEGAL $43 — skip 2 */
label_EEA0:;
    /* $EEA0: FC */ maybe_trigger_vblank(4); (void)nes_read((0xFCFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EEA3:;
    /* $EEA3: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_EEA4:;
    /* $EEA4: 33 */ maybe_trigger_vblank(8); /* ILLEGAL $33 — skip 2 */
label_EEA6:;
    /* $EEA6: 45 */ maybe_trigger_vblank(3); g_cpu.A ^= nes_read(0xFC); FLAG_NZ(g_cpu.A);
label_EEA8:;
    /* $EEA8: FC */ maybe_trigger_vblank(4); (void)nes_read((0xFCFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EEAB:;
    /* $EEAB: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_EEAC:;
    /* $EEAC: 33 */ maybe_trigger_vblank(8); /* ILLEGAL $33 — skip 2 */
label_EEAE:;
    /* $EEAE: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_EEB0:;
    /* $EEB0: FC */ maybe_trigger_vblank(4); (void)nes_read((0xFCFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EEB3:;
    /* $EEB3: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_EEB4:;
    /* $EEB4: 33 */ maybe_trigger_vblank(8); /* ILLEGAL $33 — skip 2 */
label_EEB6:;
    /* $EEB6: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFC; FLAG_NZ(g_cpu.A);
label_EEB8:;
    /* $EEB8: FC */ maybe_trigger_vblank(4); (void)nes_read((0xFCFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EEBB:;
    /* $EEBB: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_EEBC:;
    /* $EEBC: 33 */ maybe_trigger_vblank(8); /* ILLEGAL $33 — skip 2 */
label_EEBE:;
    /* $EEBE: 91 */ maybe_trigger_vblank(6); nes_write((nes_read16zp(0xFC) + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_EEC0:;
    /* $EEC0: FC */ maybe_trigger_vblank(4); (void)nes_read((0xFCFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EEC3:;
    /* $EEC3: 3A */ maybe_trigger_vblank(2); /* NOP */
label_EEC4:;
    /* $EEC4: 37 */ maybe_trigger_vblank(6); /* ILLEGAL $37 — skip 2 */
label_EEC6:;
    /* $EEC6: 93 */ maybe_trigger_vblank(6); /* ILLEGAL $93 — skip 2 */
label_EEC8:;
    /* $EEC8: FC */ maybe_trigger_vblank(4); (void)nes_read((0xFCFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EECB:;
    /* $EECB: 9E */ maybe_trigger_vblank(5); /* ILLEGAL $9E — skip 3 */
label_EECE:;
    /* $EECE: 9F */ maybe_trigger_vblank(5); /* ILLEGAL $9F — skip 3 */
label_EED1:;
    /* $EED1: FC */ maybe_trigger_vblank(4); (void)nes_read((0x3AFC + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_EED4:;
    /* $EED4: 37 */ maybe_trigger_vblank(6); /* ILLEGAL $37 — skip 2 */
label_EED6:;
    /* $EED6: 4F */ maybe_trigger_vblank(6); /* ILLEGAL $4F — skip 3 */
label_EED9:;
    /* $EED9: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xEED9); return;
}

void FinalBodies::body_f4_c0_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F507;
        case 2: goto label_F4F9;
        case 3: goto label_F911;
        case 4: goto label_F938;
        case 5: goto label_F90D;
        case 6: goto label_F4F1;
        case 7: goto label_F961;
        case 8: goto label_F4FD;
        case 9: goto label_F4F4;
        case 10: goto label_F508;
        case 11: goto label_F501;
        case 12: goto label_F4D4;
        case 13: goto label_F62B;
        case 14: goto label_F90F;
        case 15: goto label_F919;
        case 16: goto label_F92B;
        case 17: goto label_F96D;
        case 18: goto label_F914;
    }
label_F4C0:;
    /* $F4C0: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { call_by_address(0xF50C); return; }
label_F4C2:;
    /* $F4C2: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F4D1;
label_F4C4:;
    /* $F4C4: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x02; FLAG_NZ(g_cpu.A);
label_F4C6:;
    /* $F4C6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F4D1;
label_F4C8:;
    /* $F4C8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x91; FLAG_NZ(g_cpu.Y);
label_F4CA:;
    /* $F4CA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9A; FLAG_NZ(g_cpu.X);
label_F4CC:;
    /* $F4CC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x44; FLAG_NZ(g_cpu.A);
label_F4CE:;
    /* $F4CE: 20 */ maybe_trigger_vblank(6); call_by_address(0xF388);
label_F4D1:; /* NoPDwnL */
    /* $F4D1: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF4A2); return;
label_F4D4:; /* ExtraLifeFreqData */
    /* $F4D4: 58 */ maybe_trigger_vblank(2); g_cpu.I = 0;
label_F4D5:;
    /* $F4D5: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_F4D6:;
    /* $F4D6: 54 */ maybe_trigger_vblank(4); (void)nes_read((0x56 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F4D8:;
    /* $F4D8: 4E */ maybe_trigger_vblank(6); { uint16_t a=0x4C44; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F4DB:;
    /* $F4DB: 52 */ maybe_trigger_vblank(2); /* ILLEGAL $52 — skip 1 */
label_F4DC:;
    /* $F4DC: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x3E48); return;
label_F4DF:;
    /* $F4DF: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x3E + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F4E1:;
    /* $F4E1: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x30 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F4E3:;
    /* $F4E3: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_F4E4:;
    /* $F4E4: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F4E5:;
    /* $F4E5: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) goto label_F531;
label_F4E7:;
    /* $F4E7: 64 */ maybe_trigger_vblank(3); (void)nes_read(0x3C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F4E9:;
    /* $F4E9: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_F4EA:;
    /* $F4EA: 3C */ maybe_trigger_vblank(4); (void)nes_read((0x2C32 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F4ED:;
    /* $F4ED: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x3A); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_F4EF:;
    /* $F4EF: 64 */ maybe_trigger_vblank(3); (void)nes_read(0x3A); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F4F1:;
    /* $F4F1: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x2C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F4F3:;
    /* $F4F3: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_F4F4:;
    /* $F4F4: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x1C22); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_F4F7:;
    /* $F4F7: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x14 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F4F9:;
    /* $F4F9: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F4FB:;
    /* $F4FB: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x16); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_F4FD:;
    /* $F4FD: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x24); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F4FF:;
    /* $F4FF: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x18; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F501:;
    /* $F501: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F503:;
    /* $F503: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_F504:;
    /* $F504: 1A */ maybe_trigger_vblank(2); /* NOP */
label_F505:;
    /* $F505: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x28); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F507:;
    /* $F507: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_F508:;
    /* $F508: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2A04 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F50B:;
    /* $F50B: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x041E); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_F50E:;
    /* $F50E: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x202E); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_F511:;
    /* $F511: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2E); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F513:;
    /* $F513: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xF537); return; }
label_F515:;
    /* $F515: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x30); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F517:;
    /* $F517: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_F518:; /* PlayCoinGrab */
    /* $F518: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x35; FLAG_NZ(g_cpu.A);
label_F51A:;
    /* $F51A: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x8D; FLAG_NZ(g_cpu.X);
label_F51C:;
    /* $F51C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F522;
label_F51E:; /* PlayTimerTick */
    /* $F51E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x06; FLAG_NZ(g_cpu.A);
label_F520:;
    /* $F520: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x98; FLAG_NZ(g_cpu.X);
label_F522:; /* CGrab_TTickRegL */
    /* $F522: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F525:;
    /* $F525: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_F527:;
    /* $F527: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x42; FLAG_NZ(g_cpu.A);
label_F529:;
    /* $F529: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3A6);
label_F52C:; /* ContinueCGrabTTick */
    /* $F52C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F52F:;
    /* $F52F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x30; g_cpu.C=(g_cpu.A>=0x30)?1:0; FLAG_NZ(r&0xFF); }
label_F531:;
    /* $F531: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F538;
label_F533:;
    /* $F533: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x54; FLAG_NZ(g_cpu.A);
label_F535:;
    /* $F535: 8D */ maybe_trigger_vblank(4); nes_write(0x4006, g_cpu.A);
label_F538:; /* N2Tone */
    /* $F538: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F568;
label_F53A:; /* PlayBlast */
    /* $F53A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_F53C:;
    /* $F53C: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F53F:;
    /* $F53F: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x94; FLAG_NZ(g_cpu.Y);
label_F541:;
    /* $F541: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x5E; FLAG_NZ(g_cpu.A);
label_F543:;
    /* $F543: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F550;
label_F545:; /* ContinueBlast */
    /* $F545: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F548:;
    /* $F548: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x18; g_cpu.C=(g_cpu.A>=0x18)?1:0; FLAG_NZ(r&0xFF); }
label_F54A:;
    /* $F54A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F568;
label_F54C:;
    /* $F54C: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x93; FLAG_NZ(g_cpu.Y);
label_F54E:;
    /* $F54E: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_F550:; /* SBlasJ */
    /* $F550: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F5D1;
label_F552:; /* PlayPowerUpGrab */
    /* $F552: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x36; FLAG_NZ(g_cpu.A);
label_F554:;
    /* $F554: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F557:; /* ContinuePowerUpGrab */
    /* $F557: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F55A:;
    /* $F55A: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F55B:;
    /* $F55B: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F568;
label_F55D:;
    /* $F55D: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F55E:;
    /* $F55E: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF4D9 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F561:;
    /* $F561: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x5D; FLAG_NZ(g_cpu.X);
label_F563:;
    /* $F563: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_F565:; /* LoadSqu2Regs */
    /* $F565: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3A6);
label_F568:; /* DecrementSfx2Length */
    /* $F568: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BD; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F56B:;
    /* $F56B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F57B;
label_F56D:; /* EmptySfx2Buffer */
    /* $F56D: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x00; FLAG_NZ(g_cpu.X);
label_F56F:;
    /* $F56F: 86 */ maybe_trigger_vblank(3); nes_write(0xF2, g_cpu.X);
label_F571:; /* StopSquare2Sfx */
    /* $F571: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0D; FLAG_NZ(g_cpu.X);
label_F573:;
    /* $F573: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_F576:;
    /* $F576: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_F578:;
    /* $F578: 8E */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.X);
label_F57B:; /* ExSfx2 */
    /* $F57B: 60 */ maybe_trigger_vblank(6);
    return;
label_F57C:; /* Square2SfxHandler */
    /* $F57C: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_F57E:;
    /* $F57E: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x40; FLAG_NZ(g_cpu.A);
label_F580:;
    /* $F580: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F5E7;
label_F582:;
    /* $F582: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFE); FLAG_NZ(g_cpu.Y);
label_F584:;
    /* $F584: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F5A6;
label_F586:;
    /* $F586: 84 */ maybe_trigger_vblank(3); nes_write(0xF2, g_cpu.Y);
label_F588:;
    /* $F588: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_F5C8;
label_F58A:;
    /* $F58A: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F58C:;
    /* $F58C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F518;
    }
label_F58E:;
    /* $F58E: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F590:;
    /* $F590: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5FC;
label_F592:;
    /* $F592: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F594:;
    /* $F594: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F600;
label_F596:;
    /* $F596: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F598:;
    /* $F598: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F53A;
    }
label_F59A:;
    /* $F59A: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F59C:;
    /* $F59C: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F51E;
    }
label_F59E:;
    /* $F59E: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F5A0:;
    /* $F5A0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F552;
    }
label_F5A2:;
    /* $F5A2: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFE; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F5A4:;
    /* $F5A4: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5E2;
label_F5A6:; /* CheckSfx2Buffer */
    /* $F5A6: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_F5A8:;
    /* $F5A8: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F5C1;
label_F5AA:;
    /* $F5AA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_F5D3;
label_F5AC:;
    /* $F5AC: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5AD:;
    /* $F5AD: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5C2;
label_F5AF:;
    /* $F5AF: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B0:;
    /* $F5B0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F60F;
label_F5B2:;
    /* $F5B2: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B3:;
    /* $F5B3: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F60F;
label_F5B5:;
    /* $F5B5: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B6:;
    /* $F5B6: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F545;
    }
label_F5B8:;
    /* $F5B8: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5B9:;
    /* $F5B9: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5C2;
label_F5BB:;
    /* $F5BB: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5BC:;
    /* $F5BC: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F557;
    }
label_F5BE:;
    /* $F5BE: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5BF:;
    /* $F5BF: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F5E7;
label_F5C1:; /* ExS2H */
    /* $F5C1: 60 */ maybe_trigger_vblank(6);
    return;
label_F5C2:; /* Cont_CGrab_TTick */
    /* $F5C2: 4C */ maybe_trigger_vblank(3); goto label_F52C;
label_F5C5:; /* JumpToDecLength2 */
    /* $F5C5: 4C */ maybe_trigger_vblank(3); goto label_F568;
label_F5C8:; /* PlayBowserFall */
    /* $F5C8: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x38; FLAG_NZ(g_cpu.A);
label_F5CA:;
    /* $F5CA: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F5CD:;
    /* $F5CD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xC4; FLAG_NZ(g_cpu.Y);
label_F5CF:;
    /* $F5CF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_F5D1:; /* BlstSJp */
    /* $F5D1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F5DE;
label_F5D3:; /* ContinueBowserFall */
    /* $F5D3: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F5D6:;
    /* $F5D6: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x08; g_cpu.C=(g_cpu.A>=0x08)?1:0; FLAG_NZ(r&0xFF); }
label_F5D8:;
    /* $F5D8: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F568;
    }
label_F5DA:;
    /* $F5DA: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0xA4; FLAG_NZ(g_cpu.Y);
label_F5DC:;
    /* $F5DC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x5A; FLAG_NZ(g_cpu.A);
label_F5DE:; /* PBFRegs */
    /* $F5DE: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x9F; FLAG_NZ(g_cpu.X);
label_F5E0:; /* EL_LRegs */
    /* $F5E0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F565;
    }
label_F5E2:; /* PlayExtraLife */
    /* $F5E2: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x30; FLAG_NZ(g_cpu.A);
label_F5E4:;
    /* $F5E4: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F5E7:; /* ContinueExtraLife */
    /* $F5E7: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BD); FLAG_NZ(g_cpu.A);
label_F5EA:;
    /* $F5EA: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_F5EC:; /* DivLLoop */
    /* $F5EC: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F5ED:;
    /* $F5ED: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F5C5;
    }
label_F5EF:;
    /* $F5EF: CA */ maybe_trigger_vblank(2); g_cpu.X = (g_cpu.X-1)&0xFF; FLAG_NZ(g_cpu.X);
label_F5F0:;
    /* $F5F0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F5EC;
    }
label_F5F2:;
    /* $F5F2: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F5F3:;
    /* $F5F3: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF4D3 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F5F6:;
    /* $F5F6: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x82; FLAG_NZ(g_cpu.X);
label_F5F8:;
    /* $F5F8: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_F5FA:;
    /* $F5FA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F5E0;
    }
label_F5FC:; /* PlayGrowPowerUp */
    /* $F5FC: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_F5FE:;
    /* $F5FE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F602;
label_F600:; /* PlayGrowVine */
    /* $F600: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_F602:; /* GrowItemRegs */
    /* $F602: 8D */ maybe_trigger_vblank(4); nes_write(0x07BD, g_cpu.A);
label_F605:;
    /* $F605: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x7F; FLAG_NZ(g_cpu.A);
label_F607:;
    /* $F607: 8D */ maybe_trigger_vblank(4); nes_write(0x4005, g_cpu.A);
label_F60A:;
    /* $F60A: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F60C:;
    /* $F60C: 8D */ maybe_trigger_vblank(4); nes_write(0x07BE, g_cpu.A);
label_F60F:; /* ContinueGrowItems */
    /* $F60F: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07BE; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F612:;
    /* $F612: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BE); FLAG_NZ(g_cpu.A);
label_F615:;
    /* $F615: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F616:;
    /* $F616: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F617:;
    /* $F617: CC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x07BD); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_F61A:;
    /* $F61A: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F628;
label_F61C:;
    /* $F61C: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x9D; FLAG_NZ(g_cpu.A);
label_F61E:;
    /* $F61E: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_F621:;
    /* $F621: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF4F8 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F624:;
    /* $F624: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3A9);
label_F627:;
    /* $F627: 60 */ maybe_trigger_vblank(6);
    return;
label_F628:; /* StopGrowItems */
    /* $F628: 4C */ maybe_trigger_vblank(3); goto label_F56D;
label_F62B:; /* BrickShatterFreqData */
    /* $F62B: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x0E + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_F62D:;
    /* $F62D: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x0B0D; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F630:;
    /* $F630: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x0C; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F632:;
    /* $F632: 0F */ maybe_trigger_vblank(6); /* ILLEGAL $0F — skip 3 */
label_F635:;
    /* $F635: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_F637:;
    /* $F637: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_F638:;
    /* $F638: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x0C06); FLAG_NZ(g_cpu.A);
label_F63B:; /* PlayBrickShatter */
    /* $F63B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x20; FLAG_NZ(g_cpu.A);
label_F63D:;
    /* $F63D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BF, g_cpu.A);
label_F640:; /* ContinueBrickShatter */
    /* $F640: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BF); FLAG_NZ(g_cpu.A);
label_F643:;
    /* $F643: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F644:;
    /* $F644: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) goto label_F658;
label_F646:;
    /* $F646: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F647:;
    /* $F647: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xF62B + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_F64A:;
    /* $F64A: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFFEA + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F64D:; /* PlayNoiseSfx */
    /* $F64D: 8D */ maybe_trigger_vblank(4); nes_write(0x400C, g_cpu.A);
label_F650:;
    /* $F650: 8E */ maybe_trigger_vblank(4); nes_write(0x400E, g_cpu.X);
label_F653:;
    /* $F653: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x18; FLAG_NZ(g_cpu.A);
label_F655:;
    /* $F655: 8D */ maybe_trigger_vblank(4); nes_write(0x400F, g_cpu.A);
label_F658:; /* DecrementSfx3Length */
    /* $F658: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F65B:;
    /* $F65B: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F666;
label_F65D:;
    /* $F65D: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xF0; FLAG_NZ(g_cpu.A);
label_F65F:;
    /* $F65F: 8D */ maybe_trigger_vblank(4); nes_write(0x400C, g_cpu.A);
label_F662:;
    /* $F662: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F664:;
    /* $F664: 85 */ maybe_trigger_vblank(3); nes_write(0xF3, g_cpu.A);
label_F666:; /* ExSfx3 */
    /* $F666: 60 */ maybe_trigger_vblank(6);
    return;
label_F667:; /* NoiseSfxHandler */
    /* $F667: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFD); FLAG_NZ(g_cpu.Y);
label_F669:;
    /* $F669: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F675;
label_F66B:;
    /* $F66B: 84 */ maybe_trigger_vblank(3); nes_write(0xF3, g_cpu.Y);
label_F66D:;
    /* $F66D: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFD; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F66F:;
    /* $F66F: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F63B;
    }
label_F671:;
    /* $F671: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xFD; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F673:;
    /* $F673: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F680;
label_F675:; /* CheckNoiseBuffer */
    /* $F675: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF3); FLAG_NZ(g_cpu.A);
label_F677:;
    /* $F677: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F67F;
label_F679:;
    /* $F679: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F67A:;
    /* $F67A: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F640;
    }
label_F67C:;
    /* $F67C: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F67D:;
    /* $F67D: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F685;
label_F67F:; /* ExNH */
    /* $F67F: 60 */ maybe_trigger_vblank(6);
    return;
label_F680:; /* PlayBowserFlame */
    /* $F680: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x40; FLAG_NZ(g_cpu.A);
label_F682:;
    /* $F682: 8D */ maybe_trigger_vblank(4); nes_write(0x07BF, g_cpu.A);
label_F685:; /* ContinueBowserFlame */
    /* $F685: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07BF); FLAG_NZ(g_cpu.A);
label_F688:;
    /* $F688: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F689:;
    /* $F689: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F68A:;
    /* $F68A: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0F; FLAG_NZ(g_cpu.X);
label_F68C:;
    /* $F68C: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFFC9 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F68F:;
    /* $F68F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F64D;
    }
label_F691:; /* ContinueMusic */
    /* $F691: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0xF73A); return;
label_F694:; /* MusicHandler */
    /* $F694: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xFC); FLAG_NZ(g_cpu.A);
label_F696:;
    /* $F696: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6A4;
label_F698:;
    /* $F698: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xFB); FLAG_NZ(g_cpu.A);
label_F69A:;
    /* $F69A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6C8;
label_F69C:;
    /* $F69C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F69F:;
    /* $F69F: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F6A1:;
    /* $F6A1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F691;
    }
label_F6A3:;
    /* $F6A3: 60 */ maybe_trigger_vblank(6);
    return;
label_F6A4:; /* LoadEventMusic */
    /* $F6A4: 8D */ maybe_trigger_vblank(4); nes_write(0x07B1, g_cpu.A);
label_F6A7:;
    /* $F6A7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_F6A9:;
    /* $F6A9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6B1;
label_F6AB:;
    /* $F6AB: 20 */ maybe_trigger_vblank(6); call_by_address(0xF4A7);
label_F6AE:;
    /* $F6AE: 20 */ maybe_trigger_vblank(6); call_by_address(0xF571);
label_F6B1:; /* NoStopSfx */
    /* $F6B1: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0xF4); FLAG_NZ(g_cpu.X);
label_F6B3:;
    /* $F6B3: 8E */ maybe_trigger_vblank(4); nes_write(0x07C5, g_cpu.X);
label_F6B6:;
    /* $F6B6: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_F6B8:;
    /* $F6B8: 8C */ maybe_trigger_vblank(4); nes_write(0x07C4, g_cpu.Y);
label_F6BB:;
    /* $F6BB: 84 */ maybe_trigger_vblank(3); nes_write(0xF4, g_cpu.Y);
label_F6BD:;
    /* $F6BD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x40; g_cpu.C=(g_cpu.A>=0x40)?1:0; FLAG_NZ(r&0xFF); }
label_F6BF:;
    /* $F6BF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6F1;
label_F6C1:;
    /* $F6C1: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x08; FLAG_NZ(g_cpu.X);
label_F6C3:;
    /* $F6C3: 8E */ maybe_trigger_vblank(4); nes_write(0x07C4, g_cpu.X);
label_F6C6:;
    /* $F6C6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6F1;
label_F6C8:; /* LoadAreaMusic */
    /* $F6C8: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_F6CA:;
    /* $F6CA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6CF;
label_F6CC:;
    /* $F6CC: 20 */ maybe_trigger_vblank(6); call_by_address(0xF4A7);
label_F6CF:; /* NoStop1 */
    /* $F6CF: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x10; FLAG_NZ(g_cpu.Y);
label_F6D1:; /* GMLoopB */
    /* $F6D1: 8C */ maybe_trigger_vblank(4); nes_write(0x07C7, g_cpu.Y);
label_F6D4:; /* HandleAreaMusicLoopB */
    /* $F6D4: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_F6D6:;
    /* $F6D6: 8C */ maybe_trigger_vblank(4); nes_write(0x07B1, g_cpu.Y);
label_F6D9:;
    /* $F6D9: 85 */ maybe_trigger_vblank(3); nes_write(0xF4, g_cpu.A);
label_F6DB:;
    /* $F6DB: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_F6DD:;
    /* $F6DD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6ED;
label_F6DF:;
    /* $F6DF: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07C7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F6E2:;
    /* $F6E2: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07C7); FLAG_NZ(g_cpu.Y);
label_F6E5:;
    /* $F6E5: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x32; g_cpu.C=(g_cpu.Y>=0x32)?1:0; FLAG_NZ(r&0xFF); }
label_F6E7:;
    /* $F6E7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6F5;
label_F6E9:;
    /* $F6E9: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x11; FLAG_NZ(g_cpu.Y);
label_F6EB:;
    /* $F6EB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F6D1;
    }
label_F6ED:; /* FindAreaMusicHeader */
    /* $F6ED: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x08; FLAG_NZ(g_cpu.Y);
label_F6EF:;
    /* $F6EF: 84 */ maybe_trigger_vblank(3); nes_write(0xF7, g_cpu.Y);
label_F6F1:; /* FindEventMusicHeader */
    /* $F6F1: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_F6F2:;
    /* $F6F2: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F6F3:;
    /* $F6F3: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F6F1;
    }
label_F6F5:; /* LoadHeader */
    /* $F6F5: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90C + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F6F8:;
    /* $F6F8: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F6F9:;
    /* $F6F9: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90D + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F6FC:;
    /* $F6FC: 85 */ maybe_trigger_vblank(3); nes_write(0xF0, g_cpu.A);
label_F6FE:;
    /* $F6FE: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F701:;
    /* $F701: 85 */ maybe_trigger_vblank(3); nes_write(0xF5, g_cpu.A);
label_F703:;
    /* $F703: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F706:;
    /* $F706: 85 */ maybe_trigger_vblank(3); nes_write(0xF6, g_cpu.A);
label_F708:;
    /* $F708: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF910 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F70B:;
    /* $F70B: 85 */ maybe_trigger_vblank(3); nes_write(0xF9, g_cpu.A);
label_F70D:;
    /* $F70D: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF911 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F710:;
    /* $F710: 85 */ maybe_trigger_vblank(3); nes_write(0xF8, g_cpu.A);
label_F712:;
    /* $F712: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF912 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F715:;
    /* $F715: 8D */ maybe_trigger_vblank(4); nes_write(0x07B0, g_cpu.A);
label_F718:;
    /* $F718: 8D */ maybe_trigger_vblank(4); nes_write(0x07C1, g_cpu.A);
label_F71B:;
    /* $F71B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_F71D:;
    /* $F71D: 8D */ maybe_trigger_vblank(4); nes_write(0x07B4, g_cpu.A);
label_F720:;
    /* $F720: 8D */ maybe_trigger_vblank(4); nes_write(0x07B6, g_cpu.A);
label_F723:;
    /* $F723: 8D */ maybe_trigger_vblank(4); nes_write(0x07B9, g_cpu.A);
label_F726:;
    /* $F726: 8D */ maybe_trigger_vblank(4); nes_write(0x07BA, g_cpu.A);
label_F729:;
    /* $F729: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F72B:;
    /* $F72B: 85 */ maybe_trigger_vblank(3); nes_write(0xF7, g_cpu.A);
label_F72D:;
    /* $F72D: 8D */ maybe_trigger_vblank(4); nes_write(0x07CA, g_cpu.A);
label_F730:;
    /* $F730: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0B; FLAG_NZ(g_cpu.A);
label_F732:;
    /* $F732: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_F735:;
    /* $F735: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0F; FLAG_NZ(g_cpu.A);
label_F737:;
    /* $F737: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_F73A:; /* HandleSquare2Music */
    /* $F73A: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B4; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F73D:;
    /* $F73D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F79E;
label_F73F:;
    /* $F73F: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF7); FLAG_NZ(g_cpu.Y);
label_F741:;
    /* $F741: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F743:;
    /* $F743: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F745:;
    /* $F745: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F74B;
label_F747:;
    /* $F747: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_F786;
label_F749:;
    /* $F749: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F77A;
label_F74B:; /* EndOfMusicData */
    /* $F74B: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F74E:;
    /* $F74E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x40; g_cpu.C=(g_cpu.A>=0x40)?1:0; FLAG_NZ(r&0xFF); }
label_F750:;
    /* $F750: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F757;
label_F752:;
    /* $F752: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07C5); FLAG_NZ(g_cpu.A);
label_F755:;
    /* $F755: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F774;
label_F757:; /* NotTRO */
    /* $F757: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x04; FLAG_NZ(g_cpu.A);
label_F759:;
    /* $F759: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F777;
label_F75B:;
    /* $F75B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F75D:;
    /* $F75D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x5F; FLAG_NZ(g_cpu.A);
label_F75F:;
    /* $F75F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F774;
label_F761:;
    /* $F761: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F763:;
    /* $F763: 85 */ maybe_trigger_vblank(3); nes_write(0xF4, g_cpu.A);
label_F765:;
    /* $F765: 8D */ maybe_trigger_vblank(4); nes_write(0x07B1, g_cpu.A);
label_F768:;
    /* $F768: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_F76B:;
    /* $F76B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_F76D:;
    /* $F76D: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F770:;
    /* $F770: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_F773:;
    /* $F773: 60 */ maybe_trigger_vblank(6);
    return;
label_F774:; /* MusicLoopBack */
    /* $F774: 4C */ maybe_trigger_vblank(3); goto label_F6D4;
label_F777:; /* VictoryMLoopBack */
    /* $F777: 4C */ maybe_trigger_vblank(3); goto label_F6A4;
label_F77A:; /* Squ2LengthHandler */
    /* $F77A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8CB);
label_F77D:;
    /* $F77D: 8D */ maybe_trigger_vblank(4); nes_write(0x07B3, g_cpu.A);
label_F780:;
    /* $F780: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF7); FLAG_NZ(g_cpu.Y);
label_F782:;
    /* $F782: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F784:;
    /* $F784: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F786:; /* Squ2NoteHandler */
    /* $F786: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0xF2); FLAG_NZ(g_cpu.X);
label_F788:;
    /* $F788: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F798;
label_F78A:;
    /* $F78A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3A9);
label_F78D:;
    /* $F78D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F792;
label_F78F:;
    /* $F78F: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8D8);
label_F792:; /* Rest */
    /* $F792: 8D */ maybe_trigger_vblank(4); nes_write(0x07B5, g_cpu.A);
label_F795:;
    /* $F795: 20 */ maybe_trigger_vblank(6); call_by_address(0xF39F);
label_F798:; /* SkipFqL1 */
    /* $F798: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B3); FLAG_NZ(g_cpu.A);
label_F79B:;
    /* $F79B: 8D */ maybe_trigger_vblank(4); nes_write(0x07B4, g_cpu.A);
label_F79E:; /* MiscSqu2MusicTasks */
    /* $F79E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_F7A0:;
    /* $F7A0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F7BC;
label_F7A2:;
    /* $F7A2: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F7A5:;
    /* $F7A5: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x91; FLAG_NZ(g_cpu.A);
label_F7A7:;
    /* $F7A7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F7BC;
label_F7A9:;
    /* $F7A9: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B5); FLAG_NZ(g_cpu.Y);
label_F7AC:;
    /* $F7AC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F7B1;
label_F7AE:;
    /* $F7AE: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B5; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F7B1:; /* NoDecEnv1 */
    /* $F7B1: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8F4);
label_F7B4:;
    /* $F7B4: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_F7B7:;
    /* $F7B7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x7F; FLAG_NZ(g_cpu.X);
label_F7B9:;
    /* $F7B9: 8E */ maybe_trigger_vblank(4); nes_write(0x4005, g_cpu.X);
label_F7BC:; /* HandleSquare1Music */
    /* $F7BC: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF8); FLAG_NZ(g_cpu.Y);
label_F7BE:;
    /* $F7BE: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F81A;
label_F7C0:;
    /* $F7C0: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B6; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F7C3:;
    /* $F7C3: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F7F7;
label_F7C5:; /* FetchSqu1MusicData */
    /* $F7C5: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF8); FLAG_NZ(g_cpu.Y);
label_F7C7:;
    /* $F7C7: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF8; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F7C9:;
    /* $F7C9: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F7CB:;
    /* $F7CB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F7DC;
label_F7CD:;
    /* $F7CD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x83; FLAG_NZ(g_cpu.A);
label_F7CF:;
    /* $F7CF: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F7D2:;
    /* $F7D2: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x94; FLAG_NZ(g_cpu.A);
label_F7D4:;
    /* $F7D4: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_F7D7:;
    /* $F7D7: 8D */ maybe_trigger_vblank(4); nes_write(0x07CA, g_cpu.A);
label_F7DA:;
    /* $F7DA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F7C5;
    }
label_F7DC:; /* Squ1NoteHandler */
    /* $F7DC: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8C5);
label_F7DF:;
    /* $F7DF: 8D */ maybe_trigger_vblank(4); nes_write(0x07B6, g_cpu.A);
label_F7E2:;
    /* $F7E2: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF1); FLAG_NZ(g_cpu.Y);
label_F7E4:;
    /* $F7E4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F81A;
label_F7E6:;
    /* $F7E6: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F7E7:;
    /* $F7E7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3E; FLAG_NZ(g_cpu.A);
label_F7E9:;
    /* $F7E9: 20 */ maybe_trigger_vblank(6); call_by_address(0xF38B);
label_F7EC:;
    /* $F7EC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F7F1;
label_F7EE:;
    /* $F7EE: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8D8);
label_F7F1:; /* SkipCtrlL */
    /* $F7F1: 8D */ maybe_trigger_vblank(4); nes_write(0x07B7, g_cpu.A);
label_F7F4:;
    /* $F7F4: 20 */ maybe_trigger_vblank(6); call_by_address(0xF381);
label_F7F7:; /* MiscSqu1MusicTasks */
    /* $F7F7: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_F7F9:;
    /* $F7F9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F81A;
label_F7FB:;
    /* $F7FB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F7FE:;
    /* $F7FE: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x91; FLAG_NZ(g_cpu.A);
label_F800:;
    /* $F800: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F810;
label_F802:;
    /* $F802: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B7); FLAG_NZ(g_cpu.Y);
label_F805:;
    /* $F805: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F80A;
label_F807:;
    /* $F807: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B7; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F80A:; /* NoDecEnv2 */
    /* $F80A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8F4);
label_F80D:;
    /* $F80D: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F810:; /* DeathMAltReg */
    /* $F810: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07CA); FLAG_NZ(g_cpu.A);
label_F813:;
    /* $F813: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F817;
label_F815:;
    /* $F815: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x7F; FLAG_NZ(g_cpu.A);
label_F817:; /* DoAltLoad */
    /* $F817: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_F81A:; /* HandleTriangleMusic */
    /* $F81A: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF9); FLAG_NZ(g_cpu.A);
label_F81C:;
    /* $F81C: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B9; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F81F:;
    /* $F81F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F86D;
label_F821:;
    /* $F821: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF9); FLAG_NZ(g_cpu.Y);
label_F823:;
    /* $F823: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF9; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F825:;
    /* $F825: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F827:;
    /* $F827: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F86A;
label_F829:;
    /* $F829: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_F83E;
label_F82B:;
    /* $F82B: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8CB);
label_F82E:;
    /* $F82E: 8D */ maybe_trigger_vblank(4); nes_write(0x07B8, g_cpu.A);
label_F831:;
    /* $F831: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1F; FLAG_NZ(g_cpu.A);
label_F833:;
    /* $F833: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_F836:;
    /* $F836: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF9); FLAG_NZ(g_cpu.Y);
label_F838:;
    /* $F838: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF9; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F83A:;
    /* $F83A: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F83C:;
    /* $F83C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F86A;
label_F83E:; /* TriNoteHandler */
    /* $F83E: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3AD);
label_F841:;
    /* $F841: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x07B8); FLAG_NZ(g_cpu.X);
label_F844:;
    /* $F844: 8E */ maybe_trigger_vblank(4); nes_write(0x07B9, g_cpu.X);
label_F847:;
    /* $F847: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F84A:;
    /* $F84A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x6E; FLAG_NZ(g_cpu.A);
label_F84C:;
    /* $F84C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F854;
label_F84E:;
    /* $F84E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F850:;
    /* $F850: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0A; FLAG_NZ(g_cpu.A);
label_F852:;
    /* $F852: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F86D;
label_F854:; /* NotDOrD4 */
    /* $F854: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F855:;
    /* $F855: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x12; g_cpu.C=(g_cpu.A>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_F857:;
    /* $F857: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F868;
label_F859:;
    /* $F859: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F85C:;
    /* $F85C: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_F85E:;
    /* $F85E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F864;
label_F860:;
    /* $F860: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0F; FLAG_NZ(g_cpu.A);
label_F862:;
    /* $F862: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F86A;
label_F864:; /* MediN */
    /* $F864: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1F; FLAG_NZ(g_cpu.A);
label_F866:;
    /* $F866: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F86A;
label_F868:; /* LongN */
    /* $F868: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_F86A:; /* LoadTriCtrlReg */
    /* $F86A: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_F86D:; /* HandleNoiseMusic */
    /* $F86D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F86F:;
    /* $F86F: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF3; FLAG_NZ(g_cpu.A);
label_F871:;
    /* $F871: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8C4;
label_F873:;
    /* $F873: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BA; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F876:;
    /* $F876: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8C4;
label_F878:; /* FetchNoiseBeatData */
    /* $F878: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B0); FLAG_NZ(g_cpu.Y);
label_F87B:;
    /* $F87B: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07B0; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F87E:;
    /* $F87E: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F880:;
    /* $F880: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F88A;
label_F882:;
    /* $F882: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07C1); FLAG_NZ(g_cpu.A);
label_F885:;
    /* $F885: 8D */ maybe_trigger_vblank(4); nes_write(0x07B0, g_cpu.A);
label_F888:;
    /* $F888: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F878;
    }
label_F88A:; /* NoiseBeatHandler */
    /* $F88A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8C5);
label_F88D:;
    /* $F88D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BA, g_cpu.A);
label_F890:;
    /* $F890: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F891:;
    /* $F891: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3E; FLAG_NZ(g_cpu.A);
label_F893:;
    /* $F893: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8B9;
label_F895:;
    /* $F895: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x30; g_cpu.C=(g_cpu.A>=0x30)?1:0; FLAG_NZ(r&0xFF); }
label_F897:;
    /* $F897: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8B1;
label_F899:;
    /* $F899: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_F89B:;
    /* $F89B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8A9;
label_F89D:;
    /* $F89D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x10; FLAG_NZ(g_cpu.A);
label_F89F:;
    /* $F89F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8B9;
label_F8A1:;
    /* $F8A1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_F8A3:;
    /* $F8A3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_F8A5:;
    /* $F8A5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x18; FLAG_NZ(g_cpu.Y);
label_F8A7:;
    /* $F8A7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8BB;
label_F8A9:; /* StrongBeat */
    /* $F8A9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_F8AB:;
    /* $F8AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0C; FLAG_NZ(g_cpu.X);
label_F8AD:;
    /* $F8AD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x18; FLAG_NZ(g_cpu.Y);
label_F8AF:;
    /* $F8AF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8BB;
label_F8B1:; /* LongBeat */
    /* $F8B1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_F8B3:;
    /* $F8B3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_F8B5:;
    /* $F8B5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x58; FLAG_NZ(g_cpu.Y);
label_F8B7:;
    /* $F8B7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8BB;
label_F8B9:; /* SilentBeat */
    /* $F8B9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_F8BB:; /* PlayBeat */
    /* $F8BB: 8D */ maybe_trigger_vblank(4); nes_write(0x400C, g_cpu.A);
label_F8BE:;
    /* $F8BE: 8E */ maybe_trigger_vblank(4); nes_write(0x400E, g_cpu.X);
label_F8C1:;
    /* $F8C1: 8C */ maybe_trigger_vblank(4); nes_write(0x400F, g_cpu.Y);
label_F8C4:; /* ExitMusicHandler */
    /* $F8C4: 60 */ maybe_trigger_vblank(6);
    return;
label_F8C5:; /* AlternateLengthHandler */
    /* $F8C5: AA */ maybe_trigger_vblank(2); g_cpu.X = g_cpu.A; FLAG_NZ(g_cpu.X);
label_F8C6:;
    /* $F8C6: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_F8C7:;
    /* $F8C7: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F8C8:;
    /* $F8C8: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_F8C9:;
    /* $F8C9: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_F8CA:;
    /* $F8CA: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_F8CB:; /* ProcessLengthData */
    /* $F8CB: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x07; FLAG_NZ(g_cpu.A);
label_F8CD:;
    /* $F8CD: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F8CE:;
    /* $F8CE: 65 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xF0); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_F8D0:;
    /* $F8D0: 6D */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x07C4); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_F8D3:;
    /* $F8D3: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F8D4:;
    /* $F8D4: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFF66 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F8D7:;
    /* $F8D7: 60 */ maybe_trigger_vblank(6);
    return;
label_F8D8:; /* LoadControlRegs */
    /* $F8D8: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F8DB:;
    /* $F8DB: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_F8DD:;
    /* $F8DD: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8E3;
label_F8DF:;
    /* $F8DF: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x04; FLAG_NZ(g_cpu.A);
label_F8E1:;
    /* $F8E1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8EF;
label_F8E3:; /* NotECstlM */
    /* $F8E3: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F8E5:;
    /* $F8E5: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x7D; FLAG_NZ(g_cpu.A);
label_F8E7:;
    /* $F8E7: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8ED;
label_F8E9:;
    /* $F8E9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x08; FLAG_NZ(g_cpu.A);
label_F8EB:;
    /* $F8EB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8EF;
label_F8ED:; /* WaterMus */
    /* $F8ED: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x28; FLAG_NZ(g_cpu.A);
label_F8EF:; /* AllMus */
    /* $F8EF: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x82; FLAG_NZ(g_cpu.X);
label_F8F1:;
    /* $F8F1: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x7F; FLAG_NZ(g_cpu.Y);
label_F8F3:;
    /* $F8F3: 60 */ maybe_trigger_vblank(6);
    return;
label_F8F4:; /* LoadEnvelopeData */
    /* $F8F4: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F8F7:;
    /* $F8F7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_F8F9:;
    /* $F8F9: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8FF;
label_F8FB:;
    /* $F8FB: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFF96 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F8FE:;
    /* $F8FE: 60 */ maybe_trigger_vblank(6);
    return;
label_F8FF:; /* LoadUsualEnvData */
    /* $F8FF: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F901:;
    /* $F901: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x7D; FLAG_NZ(g_cpu.A);
label_F903:;
    /* $F903: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F909;
label_F905:;
    /* $F905: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFF9A + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F908:;
    /* $F908: 60 */ maybe_trigger_vblank(6);
    return;
label_F909:; /* LoadWaterEventMusEnvData */
    /* $F909: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xFFA2 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F90C:;
    /* $F90C: 60 */ maybe_trigger_vblank(6);
    return;
label_F90D:; /* MusicHeaderData */
    /* $F90D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0x59); FLAG_NZ(g_cpu.A);
label_F90F:;
    /* $F90F: 54 */ maybe_trigger_vblank(4); (void)nes_read((0x64 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F911:;
    /* $F911: 59 */ maybe_trigger_vblank(4); g_cpu.A ^= nes_read((0x313C + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F914:;
    /* $F914: 4B */ maybe_trigger_vblank(2); /* ILLEGAL $4B — skip 2 */
label_F916:;
    /* $F916: 5E */ maybe_trigger_vblank(7); { uint16_t a=(0x4F46 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_F919:;
    /* $F919: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x8D + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F91B:;
    /* $F91B: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x4B + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F91D:;
    /* $F91D: 8D */ maybe_trigger_vblank(4); nes_write(0x6969, g_cpu.A);
label_F920:;
    /* $F920: 6F */ maybe_trigger_vblank(6); /* ILLEGAL $6F — skip 3 */
label_F923:;
    /* $F923: 7B */ maybe_trigger_vblank(7); /* ILLEGAL $7B — skip 3 */
label_F926:;
    /* $F926: 6F */ maybe_trigger_vblank(6); /* ILLEGAL $6F — skip 3 */
label_F929:;
    /* $F929: 87 */ maybe_trigger_vblank(3); nes_write(0x81, g_cpu.A & g_cpu.X); /* SAX */
label_F92B:;
    /* $F92B: 8D */ maybe_trigger_vblank(4); nes_write(0x6969, g_cpu.A);
label_F92E:;
    /* $F92E: 93 */ maybe_trigger_vblank(6); /* ILLEGAL $93 — skip 2 */
label_F930:;
    /* $F930: 93 */ maybe_trigger_vblank(6); /* ILLEGAL $93 — skip 2 */
label_F932:;
    /* $F932: 93 */ maybe_trigger_vblank(6); /* ILLEGAL $93 — skip 2 */
label_F934:;
    /* $F934: 93 */ maybe_trigger_vblank(6); /* ILLEGAL $93 — skip 2 */
label_F936:;
    /* $F936: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x87 + g_cpu.X) & 0xFF), g_cpu.A);
label_F938:;
    /* $F938: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x8D + g_cpu.X) & 0xFF), g_cpu.A);
label_F93A:;
    /* $F93A: 93 */ maybe_trigger_vblank(6); /* ILLEGAL $93 — skip 2 */
label_F93C:;
    /* $F93C: 93 */ maybe_trigger_vblank(6); /* ILLEGAL $93 — skip 2 */
label_F93E:; /* TimeRunningOutHdr */
    /* $F93E: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_F93F:;
    /* $F93F: 72 */ maybe_trigger_vblank(2); /* ILLEGAL $72 — skip 1 */
label_F940:;
    /* $F940: FC */ maybe_trigger_vblank(4); (void)nes_read((0x1827 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F943:; /* Star_CloudHdr */
    /* $F943: 20 */ maybe_trigger_vblank(6); call_by_address(0xF9B8);
label_F946:;
    /* $F946: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x401A; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F949:; /* EndOfLevelMusHdr */
    /* $F949: 20 */ maybe_trigger_vblank(6); call_by_address(0xFCB0);
label_F94C:;
    /* $F94C: 3D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read((0x2021 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F94F:;
    /* $F94F: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xFC); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_F951:;
    /* $F951: 3F */ maybe_trigger_vblank(7); /* ILLEGAL $3F — skip 3 */
label_F954:;
    /* $F954: 11 */ maybe_trigger_vblank(5); g_cpu.A |= nes_read((nes_read16zp(0xFD) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F956:;
    /* $F956: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xF956); return;
label_F957:;
    /* $F957: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xF957); return;
label_F958:; /* SilenceHdr */
    /* $F958: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_F959:;
    /* $F959: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x00FA + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F95C:; /* CastleMusHdr */
    /* $F95C: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xF95C); return;
label_F95D:;
    /* $F95D: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xFB); FLAG_NZ(g_cpu.Y);
label_F95F:;
    /* $F95F: 93 */ maybe_trigger_vblank(6); /* ILLEGAL $93 — skip 2 */
label_F961:; /* VictoryMusHdr */
    /* $F961: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F92B;
    }
label_F963:;
    /* $F963: FE */ maybe_trigger_vblank(7); { uint16_t a=(0x1424 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F966:; /* GameOverMusHdr */
    /* $F966: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F967:;
    /* $F967: 45 */ maybe_trigger_vblank(3); g_cpu.A ^= nes_read(0xFC); FLAG_NZ(g_cpu.A);
label_F969:;
    /* $F969: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x0814 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F96C:;
    /* $F96C: 52 */ maybe_trigger_vblank(2); /* ILLEGAL $52 — skip 1 */
label_F96D:;
    /* $F96D: FD */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x70A0 + g_cpu.X) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_F970:;
    /* $F970: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_F971:; /* WinCastleMusHdr */
    /* $F971: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_F972:;
    /* $F972: 51 */ maybe_trigger_vblank(5); g_cpu.A ^= nes_read((nes_read16zp(0xFE) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F974:;
    /* $F974: 4C */ maybe_trigger_vblank(3); maybe_trigger_vblank(2); call_by_address(0x1824); return;
}

void FinalBodies::body_f693_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_F695;
    }
label_F693:;
    /* $F693: F7 */ maybe_trigger_vblank(6); /* ILLEGAL $F7 — skip 2 */
label_F695:;
    /* $F695: FC */ maybe_trigger_vblank(4); (void)nes_read((0x0CD0 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F698:;
    /* $F698: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xFB); FLAG_NZ(g_cpu.A);
label_F69A:;
    /* $F69A: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6C8;
label_F69C:;
    /* $F69C: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F69F:;
    /* $F69F: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F6A1:;
    /* $F6A1: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) { call_by_address(0xF691); return; }
label_F6A3:;
    /* $F6A3: 60 */ maybe_trigger_vblank(6);
    return;
label_F6A4:; /* LoadEventMusic */
    /* $F6A4: 8D */ maybe_trigger_vblank(4); nes_write(0x07B1, g_cpu.A);
label_F6A7:;
    /* $F6A7: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_F6A9:;
    /* $F6A9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6B1;
label_F6AB:;
    /* $F6AB: 20 */ maybe_trigger_vblank(6); call_by_address(0xF4A7);
label_F6AE:;
    /* $F6AE: 20 */ maybe_trigger_vblank(6); call_by_address(0xF571);
label_F6B1:; /* NoStopSfx */
    /* $F6B1: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0xF4); FLAG_NZ(g_cpu.X);
label_F6B3:;
    /* $F6B3: 8E */ maybe_trigger_vblank(4); nes_write(0x07C5, g_cpu.X);
label_F6B6:;
    /* $F6B6: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_F6B8:;
    /* $F6B8: 8C */ maybe_trigger_vblank(4); nes_write(0x07C4, g_cpu.Y);
label_F6BB:;
    /* $F6BB: 84 */ maybe_trigger_vblank(3); nes_write(0xF4, g_cpu.Y);
label_F6BD:;
    /* $F6BD: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x40; g_cpu.C=(g_cpu.A>=0x40)?1:0; FLAG_NZ(r&0xFF); }
label_F6BF:;
    /* $F6BF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6F1;
label_F6C1:;
    /* $F6C1: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x08; FLAG_NZ(g_cpu.X);
label_F6C3:;
    /* $F6C3: 8E */ maybe_trigger_vblank(4); nes_write(0x07C4, g_cpu.X);
label_F6C6:;
    /* $F6C6: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6F1;
label_F6C8:; /* LoadAreaMusic */
    /* $F6C8: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x04; g_cpu.C=(g_cpu.A>=0x04)?1:0; FLAG_NZ(r&0xFF); }
label_F6CA:;
    /* $F6CA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6CF;
label_F6CC:;
    /* $F6CC: 20 */ maybe_trigger_vblank(6); call_by_address(0xF4A7);
label_F6CF:; /* NoStop1 */
    /* $F6CF: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x10; FLAG_NZ(g_cpu.Y);
label_F6D1:; /* GMLoopB */
    /* $F6D1: 8C */ maybe_trigger_vblank(4); nes_write(0x07C7, g_cpu.Y);
label_F6D4:; /* HandleAreaMusicLoopB */
    /* $F6D4: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_F6D6:;
    /* $F6D6: 8C */ maybe_trigger_vblank(4); nes_write(0x07B1, g_cpu.Y);
label_F6D9:;
    /* $F6D9: 85 */ maybe_trigger_vblank(3); nes_write(0xF4, g_cpu.A);
label_F6DB:;
    /* $F6DB: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x01; g_cpu.C=(g_cpu.A>=0x01)?1:0; FLAG_NZ(r&0xFF); }
label_F6DD:;
    /* $F6DD: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6ED;
label_F6DF:;
    /* $F6DF: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07C7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F6E2:;
    /* $F6E2: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07C7); FLAG_NZ(g_cpu.Y);
label_F6E5:;
    /* $F6E5: C0 */ maybe_trigger_vblank(2); { int r=g_cpu.Y-0x32; g_cpu.C=(g_cpu.Y>=0x32)?1:0; FLAG_NZ(r&0xFF); }
label_F6E7:;
    /* $F6E7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F6F5;
label_F6E9:;
    /* $F6E9: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x11; FLAG_NZ(g_cpu.Y);
label_F6EB:;
    /* $F6EB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F6D1;
    }
label_F6ED:; /* FindAreaMusicHeader */
    /* $F6ED: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x08; FLAG_NZ(g_cpu.Y);
label_F6EF:;
    /* $F6EF: 84 */ maybe_trigger_vblank(3); nes_write(0xF7, g_cpu.Y);
label_F6F1:; /* FindEventMusicHeader */
    /* $F6F1: C8 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y+1)&0xFF; FLAG_NZ(g_cpu.Y);
label_F6F2:;
    /* $F6F2: 4A */ maybe_trigger_vblank(2); g_cpu.C = g_cpu.A&1; g_cpu.A >>= 1; FLAG_NZ(g_cpu.A);
label_F6F3:;
    /* $F6F3: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F6F1;
    }
label_F6F5:; /* LoadHeader */
    /* $F6F5: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90C + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F6F8:;
    /* $F6F8: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_F6F9:;
    /* $F6F9: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90D + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F6FC:;
    /* $F6FC: 85 */ maybe_trigger_vblank(3); nes_write(0xF0, g_cpu.A);
label_F6FE:;
    /* $F6FE: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90E + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F701:;
    /* $F701: 85 */ maybe_trigger_vblank(3); nes_write(0xF5, g_cpu.A);
label_F703:;
    /* $F703: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF90F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F706:;
    /* $F706: 85 */ maybe_trigger_vblank(3); nes_write(0xF6, g_cpu.A);
label_F708:;
    /* $F708: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF910 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F70B:;
    /* $F70B: 85 */ maybe_trigger_vblank(3); nes_write(0xF9, g_cpu.A);
label_F70D:;
    /* $F70D: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF911 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F710:;
    /* $F710: 85 */ maybe_trigger_vblank(3); nes_write(0xF8, g_cpu.A);
label_F712:;
    /* $F712: B9 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xF912 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F715:;
    /* $F715: 8D */ maybe_trigger_vblank(4); nes_write(0x07B0, g_cpu.A);
label_F718:;
    /* $F718: 8D */ maybe_trigger_vblank(4); nes_write(0x07C1, g_cpu.A);
label_F71B:;
    /* $F71B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x01; FLAG_NZ(g_cpu.A);
label_F71D:;
    /* $F71D: 8D */ maybe_trigger_vblank(4); nes_write(0x07B4, g_cpu.A);
label_F720:;
    /* $F720: 8D */ maybe_trigger_vblank(4); nes_write(0x07B6, g_cpu.A);
label_F723:;
    /* $F723: 8D */ maybe_trigger_vblank(4); nes_write(0x07B9, g_cpu.A);
label_F726:;
    /* $F726: 8D */ maybe_trigger_vblank(4); nes_write(0x07BA, g_cpu.A);
label_F729:;
    /* $F729: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F72B:;
    /* $F72B: 85 */ maybe_trigger_vblank(3); nes_write(0xF7, g_cpu.A);
label_F72D:;
    /* $F72D: 8D */ maybe_trigger_vblank(4); nes_write(0x07CA, g_cpu.A);
label_F730:;
    /* $F730: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0B; FLAG_NZ(g_cpu.A);
label_F732:;
    /* $F732: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_F735:;
    /* $F735: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0F; FLAG_NZ(g_cpu.A);
label_F737:;
    /* $F737: 8D */ maybe_trigger_vblank(4); nes_write(0x4015, g_cpu.A);
label_F73A:; /* HandleSquare2Music */
    /* $F73A: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B4; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F73D:;
    /* $F73D: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F79E;
label_F73F:;
    /* $F73F: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF7); FLAG_NZ(g_cpu.Y);
label_F741:;
    /* $F741: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F743:;
    /* $F743: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F745:;
    /* $F745: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F74B;
label_F747:;
    /* $F747: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_F786;
label_F749:;
    /* $F749: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F77A;
label_F74B:; /* EndOfMusicData */
    /* $F74B: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F74E:;
    /* $F74E: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x40; g_cpu.C=(g_cpu.A>=0x40)?1:0; FLAG_NZ(r&0xFF); }
label_F750:;
    /* $F750: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F757;
label_F752:;
    /* $F752: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07C5); FLAG_NZ(g_cpu.A);
label_F755:;
    /* $F755: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F774;
label_F757:; /* NotTRO */
    /* $F757: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x04; FLAG_NZ(g_cpu.A);
label_F759:;
    /* $F759: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F777;
label_F75B:;
    /* $F75B: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F75D:;
    /* $F75D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x5F; FLAG_NZ(g_cpu.A);
label_F75F:;
    /* $F75F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F774;
label_F761:;
    /* $F761: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_F763:;
    /* $F763: 85 */ maybe_trigger_vblank(3); nes_write(0xF4, g_cpu.A);
label_F765:;
    /* $F765: 8D */ maybe_trigger_vblank(4); nes_write(0x07B1, g_cpu.A);
label_F768:;
    /* $F768: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_F76B:;
    /* $F76B: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x90; FLAG_NZ(g_cpu.A);
label_F76D:;
    /* $F76D: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F770:;
    /* $F770: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_F773:;
    /* $F773: 60 */ maybe_trigger_vblank(6);
    return;
label_F774:; /* MusicLoopBack */
    /* $F774: 4C */ maybe_trigger_vblank(3); goto label_F6D4;
label_F777:; /* VictoryMLoopBack */
    /* $F777: 4C */ maybe_trigger_vblank(3); goto label_F6A4;
label_F77A:; /* Squ2LengthHandler */
    /* $F77A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8CB);
label_F77D:;
    /* $F77D: 8D */ maybe_trigger_vblank(4); nes_write(0x07B3, g_cpu.A);
label_F780:;
    /* $F780: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF7); FLAG_NZ(g_cpu.Y);
label_F782:;
    /* $F782: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF7; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F784:;
    /* $F784: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F786:; /* Squ2NoteHandler */
    /* $F786: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0xF2); FLAG_NZ(g_cpu.X);
label_F788:;
    /* $F788: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F798;
label_F78A:;
    /* $F78A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3A9);
label_F78D:;
    /* $F78D: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F792;
label_F78F:;
    /* $F78F: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8D8);
label_F792:; /* Rest */
    /* $F792: 8D */ maybe_trigger_vblank(4); nes_write(0x07B5, g_cpu.A);
label_F795:;
    /* $F795: 20 */ maybe_trigger_vblank(6); call_by_address(0xF39F);
label_F798:; /* SkipFqL1 */
    /* $F798: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B3); FLAG_NZ(g_cpu.A);
label_F79B:;
    /* $F79B: 8D */ maybe_trigger_vblank(4); nes_write(0x07B4, g_cpu.A);
label_F79E:; /* MiscSqu2MusicTasks */
    /* $F79E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF2); FLAG_NZ(g_cpu.A);
label_F7A0:;
    /* $F7A0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F7BC;
label_F7A2:;
    /* $F7A2: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F7A5:;
    /* $F7A5: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x91; FLAG_NZ(g_cpu.A);
label_F7A7:;
    /* $F7A7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F7BC;
label_F7A9:;
    /* $F7A9: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B5); FLAG_NZ(g_cpu.Y);
label_F7AC:;
    /* $F7AC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F7B1;
label_F7AE:;
    /* $F7AE: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B5; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F7B1:; /* NoDecEnv1 */
    /* $F7B1: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8F4);
label_F7B4:;
    /* $F7B4: 8D */ maybe_trigger_vblank(4); nes_write(0x4004, g_cpu.A);
label_F7B7:;
    /* $F7B7: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x7F; FLAG_NZ(g_cpu.X);
label_F7B9:;
    /* $F7B9: 8E */ maybe_trigger_vblank(4); nes_write(0x4005, g_cpu.X);
label_F7BC:; /* HandleSquare1Music */
    /* $F7BC: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF8); FLAG_NZ(g_cpu.Y);
label_F7BE:;
    /* $F7BE: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F81A;
label_F7C0:;
    /* $F7C0: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B6; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F7C3:;
    /* $F7C3: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F7F7;
label_F7C5:; /* FetchSqu1MusicData */
    /* $F7C5: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF8); FLAG_NZ(g_cpu.Y);
label_F7C7:;
    /* $F7C7: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF8; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F7C9:;
    /* $F7C9: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F7CB:;
    /* $F7CB: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F7DC;
label_F7CD:;
    /* $F7CD: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x83; FLAG_NZ(g_cpu.A);
label_F7CF:;
    /* $F7CF: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F7D2:;
    /* $F7D2: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x94; FLAG_NZ(g_cpu.A);
label_F7D4:;
    /* $F7D4: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_F7D7:;
    /* $F7D7: 8D */ maybe_trigger_vblank(4); nes_write(0x07CA, g_cpu.A);
label_F7DA:;
    /* $F7DA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F7C5;
    }
label_F7DC:; /* Squ1NoteHandler */
    /* $F7DC: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8C5);
label_F7DF:;
    /* $F7DF: 8D */ maybe_trigger_vblank(4); nes_write(0x07B6, g_cpu.A);
label_F7E2:;
    /* $F7E2: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF1); FLAG_NZ(g_cpu.Y);
label_F7E4:;
    /* $F7E4: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F81A;
label_F7E6:;
    /* $F7E6: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F7E7:;
    /* $F7E7: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3E; FLAG_NZ(g_cpu.A);
label_F7E9:;
    /* $F7E9: 20 */ maybe_trigger_vblank(6); call_by_address(0xF38B);
label_F7EC:;
    /* $F7EC: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F7F1;
label_F7EE:;
    /* $F7EE: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8D8);
label_F7F1:; /* SkipCtrlL */
    /* $F7F1: 8D */ maybe_trigger_vblank(4); nes_write(0x07B7, g_cpu.A);
label_F7F4:;
    /* $F7F4: 20 */ maybe_trigger_vblank(6); call_by_address(0xF381);
label_F7F7:; /* MiscSqu1MusicTasks */
    /* $F7F7: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF1); FLAG_NZ(g_cpu.A);
label_F7F9:;
    /* $F7F9: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F81A;
label_F7FB:;
    /* $F7FB: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F7FE:;
    /* $F7FE: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x91; FLAG_NZ(g_cpu.A);
label_F800:;
    /* $F800: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F810;
label_F802:;
    /* $F802: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B7); FLAG_NZ(g_cpu.Y);
label_F805:;
    /* $F805: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F80A;
label_F807:;
    /* $F807: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B7; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F80A:; /* NoDecEnv2 */
    /* $F80A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8F4);
label_F80D:;
    /* $F80D: 8D */ maybe_trigger_vblank(4); nes_write(0x4000, g_cpu.A);
label_F810:; /* DeathMAltReg */
    /* $F810: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07CA); FLAG_NZ(g_cpu.A);
label_F813:;
    /* $F813: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F817;
label_F815:;
    /* $F815: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x7F; FLAG_NZ(g_cpu.A);
label_F817:; /* DoAltLoad */
    /* $F817: 8D */ maybe_trigger_vblank(4); nes_write(0x4001, g_cpu.A);
label_F81A:; /* HandleTriangleMusic */
    /* $F81A: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF9); FLAG_NZ(g_cpu.A);
label_F81C:;
    /* $F81C: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07B9; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F81F:;
    /* $F81F: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F86D;
label_F821:;
    /* $F821: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF9); FLAG_NZ(g_cpu.Y);
label_F823:;
    /* $F823: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF9; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F825:;
    /* $F825: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F827:;
    /* $F827: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F86A;
label_F829:;
    /* $F829: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_F83E;
label_F82B:;
    /* $F82B: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8CB);
label_F82E:;
    /* $F82E: 8D */ maybe_trigger_vblank(4); nes_write(0x07B8, g_cpu.A);
label_F831:;
    /* $F831: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1F; FLAG_NZ(g_cpu.A);
label_F833:;
    /* $F833: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_F836:;
    /* $F836: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0xF9); FLAG_NZ(g_cpu.Y);
label_F838:;
    /* $F838: E6 */ maybe_trigger_vblank(5); { uint16_t a=0xF9; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F83A:;
    /* $F83A: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F83C:;
    /* $F83C: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F86A;
label_F83E:; /* TriNoteHandler */
    /* $F83E: 20 */ maybe_trigger_vblank(6); call_by_address(0xF3AD);
label_F841:;
    /* $F841: AE */ maybe_trigger_vblank(4); g_cpu.X = nes_read(0x07B8); FLAG_NZ(g_cpu.X);
label_F844:;
    /* $F844: 8E */ maybe_trigger_vblank(4); nes_write(0x07B9, g_cpu.X);
label_F847:;
    /* $F847: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F84A:;
    /* $F84A: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x6E; FLAG_NZ(g_cpu.A);
label_F84C:;
    /* $F84C: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F854;
label_F84E:;
    /* $F84E: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F850:;
    /* $F850: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x0A; FLAG_NZ(g_cpu.A);
label_F852:;
    /* $F852: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F86D;
label_F854:; /* NotDOrD4 */
    /* $F854: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F855:;
    /* $F855: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x12; g_cpu.C=(g_cpu.A>=0x12)?1:0; FLAG_NZ(r&0xFF); }
label_F857:;
    /* $F857: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_F868;
label_F859:;
    /* $F859: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07B1); FLAG_NZ(g_cpu.A);
label_F85C:;
    /* $F85C: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x08; FLAG_NZ(g_cpu.A);
label_F85E:;
    /* $F85E: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F864;
label_F860:;
    /* $F860: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x0F; FLAG_NZ(g_cpu.A);
label_F862:;
    /* $F862: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F86A;
label_F864:; /* MediN */
    /* $F864: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1F; FLAG_NZ(g_cpu.A);
label_F866:;
    /* $F866: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F86A;
label_F868:; /* LongN */
    /* $F868: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0xFF; FLAG_NZ(g_cpu.A);
label_F86A:; /* LoadTriCtrlReg */
    /* $F86A: 8D */ maybe_trigger_vblank(4); nes_write(0x4008, g_cpu.A);
label_F86D:; /* HandleNoiseMusic */
    /* $F86D: A5 */ maybe_trigger_vblank(3); g_cpu.A = nes_read(0xF4); FLAG_NZ(g_cpu.A);
label_F86F:;
    /* $F86F: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xF3; FLAG_NZ(g_cpu.A);
label_F871:;
    /* $F871: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8C4;
label_F873:;
    /* $F873: CE */ maybe_trigger_vblank(6); { uint16_t a=0x07BA; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F876:;
    /* $F876: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8C4;
label_F878:; /* FetchNoiseBeatData */
    /* $F878: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x07B0); FLAG_NZ(g_cpu.Y);
label_F87B:;
    /* $F87B: EE */ maybe_trigger_vblank(6); { uint16_t a=0x07B0; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F87E:;
    /* $F87E: B1 */ maybe_trigger_vblank(5); g_cpu.A = nes_read((nes_read16zp(0xF5) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F880:;
    /* $F880: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F88A;
label_F882:;
    /* $F882: AD */ maybe_trigger_vblank(4); g_cpu.A = nes_read(0x07C1); FLAG_NZ(g_cpu.A);
label_F885:;
    /* $F885: 8D */ maybe_trigger_vblank(4); nes_write(0x07B0, g_cpu.A);
label_F888:;
    /* $F888: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F878;
    }
label_F88A:; /* NoiseBeatHandler */
    /* $F88A: 20 */ maybe_trigger_vblank(6); call_by_address(0xF8C5);
label_F88D:;
    /* $F88D: 8D */ maybe_trigger_vblank(4); nes_write(0x07BA, g_cpu.A);
label_F890:;
    /* $F890: 8A */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.X; FLAG_NZ(g_cpu.A);
label_F891:;
    /* $F891: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x3E; FLAG_NZ(g_cpu.A);
label_F893:;
    /* $F893: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8B9;
label_F895:;
    /* $F895: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x30; g_cpu.C=(g_cpu.A>=0x30)?1:0; FLAG_NZ(r&0xFF); }
label_F897:;
    /* $F897: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8B1;
label_F899:;
    /* $F899: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x20; g_cpu.C=(g_cpu.A>=0x20)?1:0; FLAG_NZ(r&0xFF); }
label_F89B:;
    /* $F89B: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8A9;
label_F89D:;
    /* $F89D: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0x10; FLAG_NZ(g_cpu.A);
label_F89F:;
    /* $F89F: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) goto label_F8B9;
label_F8A1:;
    /* $F8A1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_F8A3:;
    /* $F8A3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_F8A5:;
    /* $F8A5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x18; FLAG_NZ(g_cpu.Y);
label_F8A7:;
    /* $F8A7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8BB;
label_F8A9:; /* StrongBeat */
    /* $F8A9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_F8AB:;
    /* $F8AB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x0C; FLAG_NZ(g_cpu.X);
label_F8AD:;
    /* $F8AD: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x18; FLAG_NZ(g_cpu.Y);
label_F8AF:;
    /* $F8AF: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8BB;
label_F8B1:; /* LongBeat */
    /* $F8B1: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x1C; FLAG_NZ(g_cpu.A);
label_F8B3:;
    /* $F8B3: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0x03; FLAG_NZ(g_cpu.X);
label_F8B5:;
    /* $F8B5: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x58; FLAG_NZ(g_cpu.Y);
label_F8B7:;
    /* $F8B7: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_F8BB;
label_F8B9:; /* SilentBeat */
    /* $F8B9: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x10; FLAG_NZ(g_cpu.A);
label_F8BB:; /* PlayBeat */
    /* $F8BB: 8D */ maybe_trigger_vblank(4); nes_write(0x400C, g_cpu.A);
label_F8BE:;
    /* $F8BE: 8E */ maybe_trigger_vblank(4); nes_write(0x400E, g_cpu.X);
label_F8C1:;
    /* $F8C1: 8C */ maybe_trigger_vblank(4); nes_write(0x400F, g_cpu.Y);
label_F8C4:; /* ExitMusicHandler */
    /* $F8C4: 60 */ maybe_trigger_vblank(6);
    return;
}

void FinalBodies::ground_level_part1_hdr_body(int _entry) {
    (void)state_;
    switch (_entry) {
        case 1: goto label_FFAA;
        case 2: goto label_FFCA;
        case 3: goto label_F990;
        case 4: goto label_F991;
        case 5: goto label_FDAA;
        case 6: goto label_FBAA;
        case 7: goto label_FFA0;
        case 8: goto label_FAD1;
        case 9: goto label_FDA6;
        case 10: goto label_FEA5;
        case 11: goto label_FFA2;
        case 12: goto label_FF01;
        case 13: goto label_F9A9;
        case 14: goto label_FAA1;
        case 15: goto label_FDA0;
        case 16: goto label_FCA1;
        case 17: goto label_FAF1;
        case 18: goto label_FD38;
        case 19: goto label_FA10;
        case 20: goto label_FC86;
        case 21: goto label_FEA9;
        case 22: goto label_FAAD;
        case 23: goto label_FA0E;
        case 24: goto label_FF4C;
        case 25: goto label_FF4D;
        case 26: goto label_FE4D;
        case 27: goto label_FF86;
        case 28: goto label_FE29;
        case 29: goto label_FCA9;
        case 30: goto label_FBF7;
        case 31: goto label_FDFC;
        case 32: goto label_FE08;
        case 33: goto label_FE02;
        case 34: goto label_FF07;
        case 35: goto label_F9F0;
        case 36: goto label_FC4C;
        case 37: goto label_FEC9;
        case 38: goto label_FD7D;
        case 39: goto label_FF7E;
        case 40: goto label_FC29;
        case 41: goto label_FA50;
        case 42: goto label_FBFA;
        case 43: goto label_FBF9;
        case 44: goto label_FCFD;
        case 45: goto label_FCAD;
        case 46: goto label_FCB2;
        case 47: goto label_FCA5;
        case 48: goto label_FC99;
        case 49: goto label_FC8F;
        case 50: goto label_FC95;
        case 51: goto label_FC96;
        case 52: goto label_FC74;
        case 53: goto label_FC70;
        case 54: goto label_FC6E;
        case 55: goto label_FCF6;
        case 56: goto label_FCF4;
        case 57: goto label_FCBC;
        case 58: goto label_FCBD;
        case 59: goto label_FCEF;
        case 60: goto label_FCC2;
        case 61: goto label_FCCC;
        case 62: goto label_FCF1;
        case 63: goto label_FF24;
        case 64: goto label_FF02;
        case 65: goto label_FC0F;
        case 66: goto label_FC36;
        case 67: goto label_FC39;
        case 68: goto label_FC40;
        case 69: goto label_FC41;
        case 70: goto label_FC43;
        case 71: goto label_FC44;
        case 72: goto label_FC47;
        case 73: goto label_FC4A;
        case 74: goto label_FC91;
        case 75: goto label_FC93;
        case 76: goto label_FC94;
        case 77: goto label_FC9F;
        case 78: goto label_FC50;
        case 79: goto label_FCF9;
        case 80: goto label_FEFC;
        case 81: goto label_FAA5;
        case 82: goto label_FA85;
        case 83: goto label_FF47;
        case 84: goto label_FFEA;
        case 85: goto label_FDA4;
        case 86: goto label_FD46;
        case 87: goto label_FBA6;
        case 88: goto label_F9A6;
        case 89: goto label_F9A4;
        case 90: goto label_F9E6;
        case 91: goto label_FF66;
        case 92: goto label_FF97;
        case 93: goto label_FF9A;
        case 94: goto label_FC72;
        case 95: goto label_FCC5;
        case 96: goto label_FA1C;
        case 97: goto label_FA1D;
        case 98: goto label_FBA4;
        case 99: goto label_FD52;
        case 100: goto label_FE51;
        case 101: goto label_FA01;
        case 102: goto label_FA49;
        case 103: goto label_FA9D;
        case 104: goto label_FAC2;
        case 105: goto label_FADB;
        case 106: goto label_FB25;
        case 107: goto label_FB4B;
        case 108: goto label_FB74;
        case 109: goto label_FB72;
        case 110: goto label_FFC0;
        case 111: goto label_FF14;
        case 112: goto label_FE00;
        case 113: goto label_FF35;
        case 114: goto label_FE54;
        case 115: goto label_FA80;
        case 116: goto label_FA84;
        case 117: goto label_FD0C;
        case 118: goto label_FAFB;
        case 119: goto label_FD50;
        case 120: goto label_FAA9;
        case 121: goto label_FFBA;
        case 122: goto label_F9BD;
        case 123: goto label_FB29;
        case 124: goto label_FF18;
        case 125: goto label_FA8D;
        case 126: goto label_FC88;
        case 127: goto label_FDC9;
        case 128: goto label_FE05;
        case 129: goto label_FB82;
        case 130: goto label_FFBC;
        case 131: goto label_FB0E;
        case 132: goto label_FFB4;
        case 133: goto label_FA07;
        case 134: goto label_FE0B;
        case 135: goto label_FA12;
        case 136: goto label_FE87;
        case 137: goto label_FC00;
        case 138: goto label_FC62;
        case 139: goto label_FC15;
        case 140: goto label_FC21;
        case 141: goto label_FC26;
        case 142: goto label_FA42;
        case 143: goto label_FFAC;
        case 144: goto label_FC84;
        case 145: goto label_FC04;
        case 146: goto label_FC09;
        case 147: goto label_FBFC;
        case 148: goto label_FF20;
        case 149: goto label_FABC;
        case 150: goto label_F99E;
        case 151: goto label_F9DF;
        case 152: goto label_FB2B;
    }
label_F976:; /* GroundLevelPart1Hdr */
    /* $F976: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F977:;
    /* $F977: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0xFA + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_F979:;
    /* $F979: 2D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read(0xB81C); FLAG_NZ(g_cpu.A);
label_F97C:; /* GroundLevelPart2AHdr */
    /* $F97C: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F97D:;
    /* $F97D: 49 */ maybe_trigger_vblank(2); g_cpu.A ^= 0xFA; FLAG_NZ(g_cpu.A);
label_F97F:;
    /* $F97F: 20 */ maybe_trigger_vblank(6); call_by_address(0x7012);
label_F982:; /* GroundLevelPart2BHdr */
    /* $F982: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F983:;
    /* $F983: 75 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xFA + g_cpu.X) & 0xFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_F985:;
    /* $F985: 1B */ maybe_trigger_vblank(7); /* ILLEGAL $1B — skip 3 */
label_F988:; /* GroundLevelPart2CHdr */
    /* $F988: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F989:;
    /* $F989: 9D */ maybe_trigger_vblank(5); nes_write((0x11FA + g_cpu.X) & 0xFFFF, g_cpu.A);
label_F98C:;
    /* $F98C: 0A */ maybe_trigger_vblank(2); g_cpu.C = (g_cpu.A>>7)&1; g_cpu.A = (g_cpu.A<<1)&0xFF; FLAG_NZ(g_cpu.A);
label_F98D:;
    /* $F98D: 1C */ maybe_trigger_vblank(4); (void)nes_read((0xC218 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F990:;
    /* $F990: FA */ maybe_trigger_vblank(2); /* NOP */
label_F991:;
    /* $F991: 2D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read(0x5810); FLAG_NZ(g_cpu.A);
label_F994:; /* GroundLevelPart3BHdr */
    /* $F994: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F995:;
    /* $F995: DB */ maybe_trigger_vblank(7); /* ILLEGAL $DB — skip 3 */
label_F998:;
    /* $F998: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x183F); FLAG_NZ(g_cpu.A);
label_F99B:;
    /* $F99B: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x15FA + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_F99E:;
    /* $F99E: 0D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read(0x1821); FLAG_NZ(g_cpu.A);
label_F9A1:;
    /* $F9A1: 25 */ maybe_trigger_vblank(3); g_cpu.A &= nes_read(0xFB); FLAG_NZ(g_cpu.A);
label_F9A3:;
    /* $F9A3: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F9A4:;
    /* $F9A4: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_FA20;
label_F9A6:; /* GroundLevelPart4BHdr */
    /* $F9A6: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F9A7:;
    /* $F9A7: 4B */ maybe_trigger_vblank(2); /* ILLEGAL $4B — skip 2 */
label_F9A9:;
    /* $F9A9: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x540F + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F9AC:; /* GroundLevelPart4CHdr */
    /* $F9AC: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F9AD:;
    /* $F9AD: 74 */ maybe_trigger_vblank(4); (void)nes_read((0xFB + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F9AF:;
    /* $F9AF: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x2B12 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_F9B2:; /* DeathMusHdr */
    /* $F9B2: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_F9B3:;
    /* $F9B3: 72 */ maybe_trigger_vblank(2); /* ILLEGAL $72 — skip 1 */
label_F9B4:;
    /* $F9B4: FB */ maybe_trigger_vblank(7); /* ILLEGAL $FB — skip 3 */
label_F9B7:;
    /* $F9B7: 2D */ maybe_trigger_vblank(4); g_cpu.A &= nes_read(0x2C84); FLAG_NZ(g_cpu.A);
label_F9BA:;
    /* $F9BA: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x822C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_F9BD:;
    /* $F9BD: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F9BF:;
    /* $F9BF: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x85); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F9C1:;
    /* $F9C1: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2C84); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_F9C4:;
    /* $F9C4: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2A2A); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_F9C7:;
    /* $F9C7: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_F9C8:;
    /* $F9C8: 82 */ maybe_trigger_vblank(2); /* NOP */
label_F9CA:;
    /* $F9CA: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_F9CB:;
    /* $F9CB: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x85); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F9CD:;
    /* $F9CD: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_F9CE:;
    /* $F9CE: 84 */ maybe_trigger_vblank(3); nes_write(0x2A, g_cpu.Y);
label_F9D0:;
    /* $F9D0: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_F9D1:;
    /* $F9D1: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xF9D1); return;
label_F9D2:;
    /* $F9D2: 1F */ maybe_trigger_vblank(7); /* ILLEGAL $1F — skip 3 */
label_F9D5:;
    /* $F9D5: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_F9D6:;
    /* $F9D6: 1F */ maybe_trigger_vblank(7); /* ILLEGAL $1F — skip 3 */
label_F9D9:;
    /* $F9D9: 9E */ maybe_trigger_vblank(5); /* ILLEGAL $9E — skip 3 */
label_F9DC:;
    /* $F9DC: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x1D1D + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F9DF:;
    /* $F9DF: 94 */ maybe_trigger_vblank(4); nes_write((0x1D + g_cpu.X) & 0xFF, g_cpu.Y);
label_F9E1:;
    /* $F9E1: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x9C94 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F9E4:;
    /* $F9E4: 94 */ maybe_trigger_vblank(4); nes_write((0x1D + g_cpu.X) & 0xFF, g_cpu.Y);
label_F9E6:;
    /* $F9E6: 86 */ maybe_trigger_vblank(3); nes_write(0x18, g_cpu.X);
label_F9E8:;
    /* $F9E8: 85 */ maybe_trigger_vblank(3); nes_write(0x26, g_cpu.A);
label_F9EA:;
    /* $F9EA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xF970); return; }
label_F9EC:;
    /* $F9EC: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F9EE:;
    /* $F9EE: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_F976;
    }
label_F9F0:;
    /* $F9F0: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x85 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_F9F2:;
    /* $F9F2: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_F9F3:;
    /* $F9F3: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0484); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_F9F6:;
    /* $F9F6: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_F9F7:;
    /* $F9F7: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xD021); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_F9FA:;
    /* $F9FA: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xD0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_F9FC:;
    /* $F9FC: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0xD0) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_F9FE:;
    /* $F9FE: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xD0); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_FA00:;
    /* $FA00: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFA00); return;
label_FA01:; /* GroundM_P1Data */
    /* $FA01: 85 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.A);
label_FA03:;
    /* $FA03: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FA04:;
    /* $FA04: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2684 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FA07:;
    /* $FA07: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FA08:;
    /* $FA08: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FA0A:;
    /* $FA0A: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FA0C:;
    /* $FA0C: 87 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A & g_cpu.X); /* SAX */
label_FA0E:;
    /* $FA0E: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x3A + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FA10:;
    /* $FA10: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FA12:;
    /* $FA12: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x36); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FA14:;
    /* $FA14: 84 */ maybe_trigger_vblank(3); nes_write(0x3A, g_cpu.Y);
label_FA16:;
    /* $FA16: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x82 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FA18:;
    /* $FA18: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x8530); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FA1B:;
    /* $FA1B: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FA1C:; /* SilenceData */
    /* $FA1C: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFA1C); return;
label_FA1D:;
    /* $FA1D: 5D */ maybe_trigger_vblank(4); g_cpu.A ^= nes_read((0x4D55 + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FA20:;
    /* $FA20: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x19 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_FA22:;
    /* $FA22: 96 */ maybe_trigger_vblank(4); nes_write((0x15 + g_cpu.Y) & 0xFF, g_cpu.X);
label_FA24:;
    /* $FA24: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE3 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_FA26:;
    /* $FA26: EB */ maybe_trigger_vblank(2); { uint8_t m=0x2D; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_FA28:;
    /* $FA28: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x2B); FLAG_NZ(g_cpu.X);
label_FA2A:;
    /* $FA2A: 27 */ maybe_trigger_vblank(5); /* ILLEGAL $27 — skip 2 */
label_FA2C:;
    /* $FA2C: 9E */ maybe_trigger_vblank(5); /* ILLEGAL $9E — skip 3 */
label_FA2F:;
    /* $FA2F: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FA30:;
    /* $FA30: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x8414 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FA33:;
    /* $FA33: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x8222 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FA36:;
    /* $FA36: 20 */ maybe_trigger_vblank(6); call_by_address(0x041E);
label_FA39:;
    /* $FA39: 87 */ maybe_trigger_vblank(3); nes_write(0x1C, g_cpu.A & g_cpu.X); /* SAX */
label_FA3B:;
    /* $FA3B: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x8234); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FA3E:;
    /* $FA3E: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x04 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FA40:;
    /* $FA40: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xFA76); return; }
label_FA42:;
    /* $FA42: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FA44:;
    /* $FA44: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FA46:;
    /* $FA46: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FA47:;
    /* $FA47: 85 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A);
label_FA49:; /* GroundM_P2AData */
    /* $FA49: 84 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.Y);
label_FA4B:;
    /* $FA4B: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FA4D:;
    /* $FA4D: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_FA4E:;
    /* $FA4E: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x32 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FA50:;
    /* $FA50: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x34); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FA52:;
    /* $FA52: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x24); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FA54:;
    /* $FA54: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x2C; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FA56:;
    /* $FA56: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FA58:;
    /* $FA58: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0030); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FA5B:;
    /* $FA5B: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xB4); FLAG_NZ(g_cpu.A);
label_FA5D:;
    /* $FA5D: B2 */ maybe_trigger_vblank(2); /* ILLEGAL $B2 — skip 1 */
label_FA5E:;
    /* $FA5E: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xFA8B); return; }
label_FA60:;
    /* $FA60: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x9C84); FLAG_NZ(g_cpu.Y);
label_FA63:;
    /* $FA63: 9E */ maybe_trigger_vblank(5); /* ILLEGAL $9E — skip 3 */
label_FA66:;
    /* $FA66: 94 */ maybe_trigger_vblank(4); nes_write((0x9C + g_cpu.X) & 0xFF, g_cpu.Y);
label_FA68:;
    /* $FA68: 9E */ maybe_trigger_vblank(5); /* ILLEGAL $9E — skip 3 */
label_FA6B:;
    /* $FA6B: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FA6C:;
    /* $FA6C: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_FA6E:;
    /* $FA6E: 85 */ maybe_trigger_vblank(3); nes_write(0x1E, g_cpu.A);
label_FA70:;
    /* $FA70: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FA72:;
    /* $FA72: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_FA74:;
    /* $FA74: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x0484 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FA77:;
    /* $FA77: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FA79:;
    /* $FA79: 38 */ maybe_trigger_vblank(2); g_cpu.C = 1;
label_FA7A:;
    /* $FA7A: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x32 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FA7C:;
    /* $FA7C: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x34); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FA7E:;
    /* $FA7E: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x64); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FA80:;
    /* $FA80: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x64); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FA82:;
    /* $FA82: 86 */ maybe_trigger_vblank(3); nes_write(0x64, g_cpu.X);
label_FA84:;
    /* $FA84: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFA84); return;
label_FA85:;
    /* $FA85: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xB4); FLAG_NZ(g_cpu.A);
label_FA87:;
    /* $FA87: B2 */ maybe_trigger_vblank(2); /* ILLEGAL $B2 — skip 1 */
label_FA88:;
    /* $FA88: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) { call_by_address(0xFAB5); return; }
label_FA8A:;
    /* $FA8A: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x3784); FLAG_NZ(g_cpu.Y);
label_FA8D:;
    /* $FA8D: B6 */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xB6 + g_cpu.Y) & 0xFF); FLAG_NZ(g_cpu.X);
label_FA8F:;
    /* $FA8F: 45 */ maybe_trigger_vblank(3); g_cpu.A ^= nes_read(0x85); FLAG_NZ(g_cpu.A);
label_FA91:;
    /* $FA91: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x1C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FA93:;
    /* $FA93: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FA95:;
    /* $FA95: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_FA97:;
    /* $FA97: 4E */ maybe_trigger_vblank(6); { uint16_t a=0x4E82; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_FA9A:;
    /* $FA9A: 84 */ maybe_trigger_vblank(3); nes_write(0x4E, g_cpu.Y);
label_FA9C:;
    /* $FA9C: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FA9D:; /* GroundM_P2CData */
    /* $FA9D: 84 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.Y);
label_FA9F:;
    /* $FA9F: 85 */ maybe_trigger_vblank(3); nes_write(0x32, g_cpu.A);
label_FAA1:;
    /* $FAA1: 85 */ maybe_trigger_vblank(3); nes_write(0x30, g_cpu.A);
label_FAA3:;
    /* $FAA3: 86 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.X);
label_FAA5:;
    /* $FAA5: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FAA7:;
    /* $FAA7: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xA4); FLAG_NZ(g_cpu.A);
label_FAA9:;
    /* $FAA9: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x9E); FLAG_NZ(g_cpu.A);
label_FAAB:;
    /* $FAAB: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x9D); FLAG_NZ(g_cpu.A);
label_FAAD:;
    /* $FAAD: 85 */ maybe_trigger_vblank(3); nes_write(0x84, g_cpu.A);
label_FAAF:;
    /* $FAAF: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x85 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FAB1:;
    /* $FAB1: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x28); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FAB3:;
    /* $FAB3: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2282); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FAB6:;
    /* $FAB6: 84 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.Y);
label_FAB8:;
    /* $FAB8: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x21 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FABA:;
    /* $FABA: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_FA80;
    }
label_FABC:;
    /* $FABC: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_FAEF;
label_FABE:;
    /* $FABE: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_FA84;
    }
label_FAC0:;
    /* $FAC0: D0 */ maybe_trigger_vblank(2); if (!g_cpu.Z) goto label_FAC2;
label_FAC2:; /* GroundM_P3AData */
    /* $FAC2: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FAC4:;
    /* $FAC4: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_FAC6:;
    /* $FAC6: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2C82); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FAC9:;
    /* $FAC9: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_FACF;
label_FACB:;
    /* $FACB: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x2C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FACD:;
    /* $FACD: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FACF:;
    /* $FACF: 86 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.X);
label_FAD1:;
    /* $FAD1: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFAD1); return;
label_FAD2:;
    /* $FAD2: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x25); FLAG_NZ(g_cpu.Y);
label_FAD4:;
    /* $FAD4: 25 */ maybe_trigger_vblank(3); g_cpu.A &= nes_read(0xA4); FLAG_NZ(g_cpu.A);
label_FAD6:;
    /* $FAD6: 29 */ maybe_trigger_vblank(2); g_cpu.A &= 0xA2; FLAG_NZ(g_cpu.A);
label_FAD8:;
    /* $FAD8: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x959C + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FADB:; /* GroundM_P3BData */
    /* $FADB: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FADD:;
    /* $FADD: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2C04); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FAE0:;
    /* $FAE0: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FAE2:;
    /* $FAE2: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xFA69); return; }
label_FAE4:;
    /* $FAE4: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x04 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FAE6:;
    /* $FAE6: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FAE8:;
    /* $FAE8: A4 */ maybe_trigger_vblank(3); g_cpu.Y = nes_read(0x25); FLAG_NZ(g_cpu.Y);
label_FAEA:;
    /* $FAEA: 25 */ maybe_trigger_vblank(3); g_cpu.A &= nes_read(0xA4); FLAG_NZ(g_cpu.A);
label_FAEC:;
    /* $FAEC: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_FAED:;
    /* $FAED: 63 */ maybe_trigger_vblank(8); /* ILLEGAL $63 — skip 2 */
label_FAEF:;
    /* $FAEF: 85 */ maybe_trigger_vblank(3); nes_write(0x0E, g_cpu.A);
label_FAF1:;
    /* $FAF1: 1A */ maybe_trigger_vblank(2); /* NOP */
label_FAF2:;
    /* $FAF2: 84 */ maybe_trigger_vblank(3); nes_write(0x24, g_cpu.Y);
label_FAF4:;
    /* $FAF4: 85 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A);
label_FAF6:;
    /* $FAF6: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x84 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FAF8:;
    /* $FAF8: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x3482); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FAFB:;
    /* $FAFB: 84 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.Y);
label_FAFD:;
    /* $FAFD: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x82 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FAFF:;
    /* $FAFF: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x3484); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FB02:;
    /* $FB02: 86 */ maybe_trigger_vblank(3); nes_write(0x3A, g_cpu.X);
label_FB04:;
    /* $FB04: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FB06:;
    /* $FB06: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x21; FLAG_NZ(g_cpu.Y);
label_FB08:;
    /* $FB08: 21 */ maybe_trigger_vblank(6); g_cpu.A &= nes_read(nes_read16zp((0xA0 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FB0A:;
    /* $FB0A: 21 */ maybe_trigger_vblank(6); g_cpu.A &= nes_read(nes_read16zp((0x2B + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FB0C:;
    /* $FB0C: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0xA3); FLAG_NZ(g_cpu.A);
label_FB0E:;
    /* $FB0E: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FB10:;
    /* $FB10: 84 */ maybe_trigger_vblank(3); nes_write(0x18, g_cpu.Y);
label_FB12:;
    /* $FB12: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_FB13:;
    /* $FB13: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FB15:;
    /* $FB15: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_FB16:;
    /* $FB16: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x86); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FB18:;
    /* $FB18: 3A */ maybe_trigger_vblank(2); /* NOP */
label_FB19:;
    /* $FB19: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FB1A:;
    /* $FB1A: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x90) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FB1C:;
    /* $FB1C: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x90) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FB1E:;
    /* $FB1E: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x71) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FB20:;
    /* $FB20: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x90) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FB22:;
    /* $FB22: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { call_by_address(0xFAB4); return; }
label_FB24:;
    /* $FB24: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFB24); return;
label_FB25:; /* GroundM_P4AData */
    /* $FB25: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FB27:;
    /* $FB27: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_FB29:;
    /* $FB29: 85 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A);
label_FB2B:;
    /* $FB2B: 84 */ maybe_trigger_vblank(3); nes_write(0x24, g_cpu.Y);
label_FB2D:;
    /* $FB2D: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FB2F:;
    /* $FB2F: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x04 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FB31:;
    /* $FB31: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x86 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FB33:;
    /* $FB33: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x00; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FB35:;
    /* $FB35: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x5D27); FLAG_NZ(g_cpu.Y);
label_FB38:;
    /* $FB38: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x2D9E + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FB3B:;
    /* $FB3B: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x859F); FLAG_NZ(g_cpu.Y);
label_FB3E:;
    /* $FB3E: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x82 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FB40:;
    /* $FB40: 20 */ maybe_trigger_vblank(6); call_by_address(0x2284);
label_FB43:;
    /* $FB43: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x1E1E); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FB46:;
    /* $FB46: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FB48:;
    /* $FB48: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x041E); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FB4B:; /* GroundM_P4BData */
    /* $FB4B: 87 */ maybe_trigger_vblank(3); nes_write(0x2A, g_cpu.A & g_cpu.X); /* SAX */
label_FB4D:;
    /* $FB4D: 40 */ maybe_trigger_vblank(6); /* RTI */ g_cpu.S++; { uint8_t p=g_ram[0x100+g_cpu.S]; g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1; g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; } g_cpu.S++; g_cpu.S++; /* pop PCL, PCH */
    return;
label_FB4E:;
    /* $FB4E: 40 */ maybe_trigger_vblank(6); /* RTI */ g_cpu.S++; { uint8_t p=g_ram[0x100+g_cpu.S]; g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1; g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; } g_cpu.S++; g_cpu.S++; /* pop PCL, PCH */
    return;
label_FB4F:;
    /* $FB4F: 40 */ maybe_trigger_vblank(6); /* RTI */ g_cpu.S++; { uint8_t p=g_ram[0x100+g_cpu.S]; g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1; g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; } g_cpu.S++; g_cpu.S++; /* pop PCL, PCH */
    return;
label_FB50:;
    /* $FB50: 3A */ maybe_trigger_vblank(2); /* NOP */
label_FB51:;
    /* $FB51: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x82 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FB53:;
    /* $FB53: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x2C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FB55:;
    /* $FB55: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x26); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FB57:;
    /* $FB57: 86 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.X);
label_FB59:;
    /* $FB59: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFB59); return;
label_FB5A:;
    /* $FB5A: E3 */ maybe_trigger_vblank(8); /* ILLEGAL $E3 — skip 2 */
label_FB5C:;
    /* $FB5C: F7 */ maybe_trigger_vblank(6); /* ILLEGAL $F7 — skip 2 */
label_FB5E:;
    /* $FB5E: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xF1 + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_FB60:;
    /* $FB60: AC */ maybe_trigger_vblank(4); g_cpu.Y = nes_read(0x9E27); FLAG_NZ(g_cpu.Y);
label_FB63:;
    /* $FB63: 9D */ maybe_trigger_vblank(5); nes_write((0x1885 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_FB66:;
    /* $FB66: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FB68:;
    /* $FB68: 84 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.Y);
label_FB6A:;
    /* $FB6A: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FB6B:;
    /* $FB6B: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FB6C:;
    /* $FB6C: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FB6D:;
    /* $FB6D: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FB6F:;
    /* $FB6F: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0422); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FB72:; /* DeathMusData */
    /* $FB72: 86 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.X);
label_FB74:; /* GroundM_P4CData */
    /* $FB74: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FB76:;
    /* $FB76: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x04 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FB78:;
    /* $FB78: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x87 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FB7A:;
    /* $FB7A: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x34 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FB7C:;
    /* $FB7C: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_FB04;
    }
label_FB7E:;
    /* $FB7E: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0004); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FB81:;
    /* $FB81: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFB81); return;
label_FB82:;
    /* $FB82: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_FB83:;
    /* $FB83: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_FB84:;
    /* $FB84: 6C */ maybe_trigger_vblank(5); { uint16_t _jt = nes_read16_jmpbug(0xA245); maybe_trigger_vblank(2); call_by_address(_jt); return; }
label_FB87:;
    /* $FB87: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0xB0) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FB89:;
    /* $FB89: F1 */ maybe_trigger_vblank(5); { uint8_t m=nes_read((nes_read16zp(0xED) + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_FB8B:;
    /* $FB8B: EB */ maybe_trigger_vblank(2); { uint8_t m=0xA2; int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_FB8D:;
    /* $FB8D: 1D */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x959C + g_cpu.X) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FB90:;
    /* $FB90: 86 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.X);
label_FB92:;
    /* $FB92: 85 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A);
label_FB94:;
    /* $FB94: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FB96:;
    /* $FB96: 87 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.A & g_cpu.X); /* SAX */
label_FB98:;
    /* $FB98: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x2A; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FB9A:;
    /* $FB9A: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_FB9C:;
    /* $FB9C: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FB9D:;
    /* $FB9D: 86 */ maybe_trigger_vblank(3); nes_write(0x14, g_cpu.X);
label_FB9F:;
    /* $FB9F: 51 */ maybe_trigger_vblank(5); g_cpu.A ^= nes_read((nes_read16zp(0x90) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FBA1:;
    /* $FBA1: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x11) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FBA3:;
    /* $FBA3: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFBA3); return;
label_FBA4:; /* CastleMusData */
    /* $FBA4: 80 */ maybe_trigger_vblank(2); /* NOP */
label_FBA6:;
    /* $FBA6: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBA7:;
    /* $FBA7: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FBA8:;
    /* $FBA8: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x22; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBAA:;
    /* $FBAA: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x22); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FBAC:;
    /* $FBAC: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x22; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBAE:;
    /* $FBAE: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBAF:;
    /* $FBAF: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FBB0:;
    /* $FBB0: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FBB1:;
    /* $FBB1: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FBB2:;
    /* $FBB2: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBB3:;
    /* $FBB3: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FBB4:;
    /* $FBB4: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x22; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBB6:;
    /* $FBB6: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBB7:;
    /* $FBB7: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FBB8:;
    /* $FBB8: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x22; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBBA:;
    /* $FBBA: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x22); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FBBC:;
    /* $FBBC: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x22; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBBE:;
    /* $FBBE: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBBF:;
    /* $FBBF: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FBC0:;
    /* $FBC0: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FBC1:;
    /* $FBC1: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FBC2:;
    /* $FBC2: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBC3:;
    /* $FBC3: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FBC4:;
    /* $FBC4: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBC6:;
    /* $FBC6: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBC8:;
    /* $FBC8: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x20); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FBCA:;
    /* $FBCA: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBCC:;
    /* $FBCC: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBCD:;
    /* $FBCD: 20 */ maybe_trigger_vblank(6); call_by_address(0x2026);
label_FBD0:;
    /* $FBD0: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBD1:;
    /* $FBD1: 20 */ maybe_trigger_vblank(6); call_by_address(0x2026);
label_FBD4:;
    /* $FBD4: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x20); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FBD6:;
    /* $FBD6: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBD8:;
    /* $FBD8: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x20); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FBDA:;
    /* $FBDA: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x20; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBDC:;
    /* $FBDC: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBDD:;
    /* $FBDD: 20 */ maybe_trigger_vblank(6); call_by_address(0x2026);
label_FBE0:;
    /* $FBE0: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBE1:;
    /* $FBE1: 20 */ maybe_trigger_vblank(6); call_by_address(0x2026);
label_FBE4:;
    /* $FBE4: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x28); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FBE6:;
    /* $FBE6: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xFC10); return; }
label_FBE8:;
    /* $FBE8: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_FBE9:;
    /* $FBE9: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBEA:;
    /* $FBEA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_FC14;
label_FBEC:;
    /* $FBEC: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x3028; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBEF:;
    /* $FBEF: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBF0:;
    /* $FBF0: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x2C28; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBF3:;
    /* $FBF3: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBF4:;
    /* $FBF4: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x3028; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBF7:;
    /* $FBF7: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBF8:;
    /* $FBF8: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_FBF9:;
    /* $FBF9: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FBFA:;
    /* $FBFA: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_FC24;
label_FBFC:;
    /* $FBFC: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x3028; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FBFF:;
    /* $FBFF: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FC00:;
    /* $FC00: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x2C28; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC03:;
    /* $FC03: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FC04:;
    /* $FC04: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x0400; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC07:;
    /* $FC07: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) { call_by_address(0xFC77); return; }
label_FC09:;
    /* $FC09: 6C */ maybe_trigger_vblank(5); { uint16_t _jt = nes_read16_jmpbug(0x706E); maybe_trigger_vblank(2); call_by_address(_jt); return; }
label_FC0C:;
    /* $FC0C: 72 */ maybe_trigger_vblank(2); /* ILLEGAL $72 — skip 1 */
label_FC0D:;
    /* $FC0D: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) goto label_FC7D;
label_FC0F:;
    /* $FC0F: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) { call_by_address(0xFC7F); return; }
label_FC11:;
    /* $FC11: 6C */ maybe_trigger_vblank(5); { uint16_t _jt = nes_read16_jmpbug(0x706E); maybe_trigger_vblank(2); call_by_address(_jt); return; }
label_FC14:;
    /* $FC14: 72 */ maybe_trigger_vblank(2); /* ILLEGAL $72 — skip 1 */
label_FC15:;
    /* $FC15: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) { call_by_address(0xFC85); return; }
label_FC17:;
    /* $FC17: 6E */ maybe_trigger_vblank(6); { uint16_t a=0x6E6C; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC1A:;
    /* $FC1A: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) goto label_FC8A;
label_FC1C:;
    /* $FC1C: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) goto label_FC8C;
label_FC1E:;
    /* $FC1E: 6C */ maybe_trigger_vblank(5); { uint16_t _jt = nes_read16_jmpbug(0x6C6E); maybe_trigger_vblank(2); call_by_address(_jt); return; }
label_FC21:;
    /* $FC21: 6E */ maybe_trigger_vblank(6); { uint16_t a=0x6E70; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC24:;
    /* $FC24: 70 */ maybe_trigger_vblank(2); if (g_cpu.V) goto label_FC94;
label_FC26:;
    /* $FC26: 6C */ maybe_trigger_vblank(5); { uint16_t _jt = nes_read16_jmpbug(0x7876); maybe_trigger_vblank(2); call_by_address(_jt); return; }
label_FC29:;
    /* $FC29: 76 */ maybe_trigger_vblank(6); { uint16_t a=(0x74 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC2B:;
    /* $FC2B: 76 */ maybe_trigger_vblank(6); { uint16_t a=(0x74 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC2D:;
    /* $FC2D: 72 */ maybe_trigger_vblank(2); /* ILLEGAL $72 — skip 1 */
label_FC2E:;
    /* $FC2E: 74 */ maybe_trigger_vblank(4); (void)nes_read((0x76 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC30:;
    /* $FC30: 78 */ maybe_trigger_vblank(2); g_cpu.I = 1;
label_FC31:;
    /* $FC31: 76 */ maybe_trigger_vblank(6); { uint16_t a=(0x74 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC33:;
    /* $FC33: 76 */ maybe_trigger_vblank(6); { uint16_t a=(0x74 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC35:;
    /* $FC35: 72 */ maybe_trigger_vblank(2); /* ILLEGAL $72 — skip 1 */
label_FC36:;
    /* $FC36: 74 */ maybe_trigger_vblank(4); (void)nes_read((0x84 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC38:;
    /* $FC38: 1A */ maybe_trigger_vblank(2); /* NOP */
label_FC39:;
    /* $FC39: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x18 + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_FC3B:;
    /* $FC3B: 20 */ maybe_trigger_vblank(6); call_by_address(0x1E84);
label_FC3E:;
    /* $FC3E: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x1C + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_FC40:;
    /* $FC40: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FC41:;
    /* $FC41: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x1C; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC43:;
    /* $FC43: 1A */ maybe_trigger_vblank(2); /* NOP */
label_FC44:;
    /* $FC44: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2C82 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC47:;
    /* $FC47: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC49:;
    /* $FC49: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FC4A:;
    /* $FC4A: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC4C:;
    /* $FC4C: 84 */ maybe_trigger_vblank(3); nes_write(0x1C, g_cpu.Y);
label_FC4E:;
    /* $FC4E: 87 */ maybe_trigger_vblank(3); nes_write(0x26, g_cpu.A & g_cpu.X); /* SAX */
label_FC50:;
    /* $FC50: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FC51:;
    /* $FC51: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x84; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC53:;
    /* $FC53: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x28); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FC55:;
    /* $FC55: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x80); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FC57:;
    /* $FC57: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FC58:;
    /* $FC58: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFC58); return;
label_FC59:;
    /* $FC59: 9C */ maybe_trigger_vblank(5); /* ILLEGAL $9C — skip 3 */
label_FC5C:;
    /* $FC5C: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x0D); FLAG_NZ(g_cpu.A);
label_FC5E:;
    /* $FC5E: 9F */ maybe_trigger_vblank(5); /* ILLEGAL $9F — skip 3 */
label_FC61:;
    /* $FC61: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_FC62:;
    /* $FC62: 9D */ maybe_trigger_vblank(5); nes_write((0x2282 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_FC65:;
    /* $FC65: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC67:;
    /* $FC67: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x0404 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC6A:;
    /* $FC6A: 84 */ maybe_trigger_vblank(3); nes_write(0x14, g_cpu.Y);
label_FC6C:;
    /* $FC6C: 86 */ maybe_trigger_vblank(3); nes_write(0x1E, g_cpu.X);
label_FC6E:;
    /* $FC6E: 80 */ maybe_trigger_vblank(2); /* NOP */
label_FC70:;
    /* $FC70: 80 */ maybe_trigger_vblank(2); /* NOP */
label_FC72:; /* TimeRunOutMusData */
    /* $FC72: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x1C + g_cpu.X) & 0xFF), g_cpu.A);
label_FC74:;
    /* $FC74: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_FC7A;
label_FC76:;
    /* $FC76: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xFCA8); return; }
label_FC78:;
    /* $FC78: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x1E); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC7A:;
    /* $FC7A: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_FC7B:;
    /* $FC7B: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x32); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC7D:;
    /* $FC7D: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_FC7E:;
    /* $FC7E: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x20); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC80:;
    /* $FC80: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x04 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC82:;
    /* $FC82: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x34 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC84:;
    /* $FC84: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x36); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC86:;
    /* $FC86: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x84); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC88:;
    /* $FC88: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x00 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FC8A:;
    /* $FC8A: 46 */ maybe_trigger_vblank(5); { uint16_t a=0xA4; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_FC8C:;
    /* $FC8C: 64 */ maybe_trigger_vblank(3); (void)nes_read(0xA4); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC8E:;
    /* $FC8E: 48 */ maybe_trigger_vblank(3); g_ram[0x100 + g_cpu.S] = g_cpu.A; g_cpu.S--;
label_FC8F:;
    /* $FC8F: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x66); FLAG_NZ(g_cpu.X);
label_FC91:;
    /* $FC91: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x4A); FLAG_NZ(g_cpu.X);
label_FC93:;
    /* $FC93: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_FC94:;
    /* $FC94: 68 */ maybe_trigger_vblank(4); g_cpu.S++; g_cpu.A = g_ram[0x100 + g_cpu.S]; FLAG_NZ(g_cpu.A);
label_FC95:;
    /* $FC95: A8 */ maybe_trigger_vblank(2); g_cpu.Y = g_cpu.A; FLAG_NZ(g_cpu.Y);
label_FC96:;
    /* $FC96: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_FC97:;
    /* $FC97: 44 */ maybe_trigger_vblank(3); (void)nes_read(0x2B); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC99:;
    /* $FC99: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x2A + g_cpu.X) & 0xFF), g_cpu.A);
label_FC9B:;
    /* $FC9B: 42 */ maybe_trigger_vblank(2); /* ILLEGAL $42 — skip 1 */
label_FC9C:;
    /* $FC9C: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x42); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FC9E:;
    /* $FC9E: 42 */ maybe_trigger_vblank(2); /* ILLEGAL $42 — skip 1 */
label_FC9F:;
    /* $FC9F: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCA1:;
    /* $FCA1: 64 */ maybe_trigger_vblank(3); (void)nes_read(0x04); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCA3:;
    /* $FCA3: 64 */ maybe_trigger_vblank(3); (void)nes_read(0x64); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCA5:;
    /* $FCA5: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2E); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCA7:;
    /* $FCA7: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_FCA9:;
    /* $FCA9: 46 */ maybe_trigger_vblank(5); { uint16_t a=0x46; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_FCAB:;
    /* $FCAB: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCAD:;
    /* $FCAD: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x84); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCAF:;
    /* $FCAF: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FCB0:; /* WinLevelMusData */
    /* $FCB0: 87 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A & g_cpu.X); /* SAX */
label_FCB2:;
    /* $FCB2: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x0C; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FCB4:;
    /* $FCB4: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x1C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCB6:;
    /* $FCB6: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FCB7:;
    /* $FCB7: 86 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.X);
label_FCB9:;
    /* $FCB9: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FCBA:;
    /* $FCBA: 87 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A & g_cpu.X); /* SAX */
label_FCBC:;
    /* $FCBC: 60 */ maybe_trigger_vblank(6);
    return;
label_FCBD:;
    /* $FCBD: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x1A14; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FCC0:;
    /* $FCC0: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x86); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FCC2:;
    /* $FCC2: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x8724); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FCC5:;
    /* $FCC5: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x08); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCC7:;
    /* $FCC7: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { call_by_address(0xFCE1); return; }
label_FCC9:;
    /* $FCC9: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x8628 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FCCC:;
    /* $FCCC: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xFCFE); return; }
label_FCCE:;
    /* $FCCE: 80 */ maybe_trigger_vblank(2); /* NOP */
label_FCD0:;
    /* $FCD0: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFCD0); return;
label_FCD1:;
    /* $FCD1: CD */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0xDDD5); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_FCD4:;
    /* $FCD4: E3 */ maybe_trigger_vblank(8); /* ILLEGAL $E3 — skip 2 */
label_FCD6:;
    /* $FCD6: F5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xBB + g_cpu.X) & 0xFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_FCD8:;
    /* $FCD8: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xCF + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_FCDA:;
    /* $FCDA: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xDB + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_FCDC:;
    /* $FCDC: E5 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0xED); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_FCDE:;
    /* $FCDE: F3 */ maybe_trigger_vblank(8); /* ILLEGAL $F3 — skip 2 */
label_FCE0:;
    /* $FCE0: B3 */ maybe_trigger_vblank(5); g_cpu.A = g_cpu.X = nes_read((nes_read16zp(0xD1) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FCE2:;
    /* $FCE2: D9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xE9DF + g_cpu.Y) & 0xFFFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_FCE5:;
    /* $FCE5: F1 */ maybe_trigger_vblank(5); { uint8_t m=nes_read((nes_read16zp(0xF7) + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_FCE7:;
    /* $FCE7: BF */ maybe_trigger_vblank(4); g_cpu.A = g_cpu.X = nes_read((0xFFFF + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FCEA:;
    /* $FCEA: FF */ maybe_trigger_vblank(7); /* ILLEGAL $FF — skip 3 */
label_FCED:;
    /* $FCED: 86 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.X);
label_FCEF:;
    /* $FCEF: 87 */ maybe_trigger_vblank(3); nes_write(0x14, g_cpu.A & g_cpu.X); /* SAX */
label_FCF1:;
    /* $FCF1: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x8622 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCF4:;
    /* $FCF4: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x84 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCF6:;
    /* $FCF6: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x0404); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FCF9:;
    /* $FCF9: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x87); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCFB:;
    /* $FCFB: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x1A + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FCFD:;
    /* $FCFD: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x86); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FCFF:;
    /* $FCFF: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_FD00:;
    /* $FD00: 84 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.Y);
label_FD02:;
    /* $FD02: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x86); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FD04:;
    /* $FD04: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x87); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FD06:;
    /* $FD06: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_FD07:;
    /* $FD07: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x8628 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FD0A:;
    /* $FD0A: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x87 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FD0C:;
    /* $FD0C: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xFD3E); return; }
label_FD0E:;
    /* $FD0E: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xFC90); return; }
label_FD10:;
    /* $FD10: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x1482); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FD13:;
    /* $FD13: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2662); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FD16:;
    /* $FD16: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_FD40;
label_FD18:;
    /* $FD18: 80 */ maybe_trigger_vblank(2); /* NOP */
label_FD1A:;
    /* $FD1A: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FD1C:;
    /* $FD1C: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2662); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FD1F:;
    /* $FD1F: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) { call_by_address(0xFD49); return; }
label_FD21:;
    /* $FD21: 80 */ maybe_trigger_vblank(2); /* NOP */
label_FD23:;
    /* $FD23: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FD25:;
    /* $FD25: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x185E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FD28:;
    /* $FD28: 60 */ maybe_trigger_vblank(6);
    return;
label_FD29:;
    /* $FD29: 1A */ maybe_trigger_vblank(2); /* NOP */
label_FD2A:;
    /* $FD2A: 80 */ maybe_trigger_vblank(2); /* NOP */
label_FD2C:;
    /* $FD2C: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FD2E:;
    /* $FD2E: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x185E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FD31:;
    /* $FD31: 60 */ maybe_trigger_vblank(6);
    return;
label_FD32:;
    /* $FD32: 1A */ maybe_trigger_vblank(2); /* NOP */
label_FD33:;
    /* $FD33: 86 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.X);
label_FD35:;
    /* $FD35: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x1A + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_FD37:;
    /* $FD37: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_FD38:;
    /* $FD38: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x84 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FD3A:;
    /* $FD3A: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x1A + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FD3C:;
    /* $FD3C: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_FD3D:;
    /* $FD3D: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x160C; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FD40:;
    /* $FD40: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x14 + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_FD42:;
    /* $FD42: 20 */ maybe_trigger_vblank(6); call_by_address(0x1C1E);
label_FD45:;
    /* $FD45: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FD46:;
    /* $FD46: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x87; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FD48:;
    /* $FD48: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x1A); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FD4A:;
    /* $FD4A: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_FD4B:;
    /* $FD4B: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_FDAF;
label_FD4D:;
    /* $FD4D: 0E */ maybe_trigger_vblank(6); { uint16_t a=0x0480; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FD50:;
    /* $FD50: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FD52:; /* WaterMusData */
    /* $FD52: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FD54:;
    /* $FD54: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2220 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FD57:;
    /* $FD57: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x28; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FD59:;
    /* $FD59: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x2A + g_cpu.X) & 0xFF), g_cpu.A);
label_FD5B:;
    /* $FD5B: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FD5C:;
    /* $FD5C: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FD5D:;
    /* $FD5D: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x2A); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FD5F:;
    /* $FD5F: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x83); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FD61:;
    /* $FD61: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FD62:;
    /* $FD62: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FD64:;
    /* $FD64: 86 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.X);
label_FD66:;
    /* $FD66: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_FD67:;
    /* $FD67: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x81 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FD69:;
    /* $FD69: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FD6B:;
    /* $FD6B: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x2A; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FD6D:;
    /* $FD6D: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x8630); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FD70:;
    /* $FD70: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x83 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FD72:;
    /* $FD72: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_FD73:;
    /* $FD73: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FD75:;
    /* $FD75: 84 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.Y);
label_FD77:;
    /* $FD77: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_FD79:;
    /* $FD79: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x22 + g_cpu.X) & 0xFF), g_cpu.A);
label_FD7B:;
    /* $FD7B: 86 */ maybe_trigger_vblank(3); nes_write(0x30, g_cpu.X);
label_FD7D:;
    /* $FD7D: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x8130; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FD80:;
    /* $FD80: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x22); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FD82:;
    /* $FD82: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x2A; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FD84:;
    /* $FD84: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x862E); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FD87:;
    /* $FD87: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_FD0C;
    }
label_FD89:;
    /* $FD89: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FD8A:;
    /* $FD8A: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FD8C:;
    /* $FD8C: 84 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.Y);
label_FD8E:;
    /* $FD8E: 85 */ maybe_trigger_vblank(3); nes_write(0x04, g_cpu.A);
label_FD90:;
    /* $FD90: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x22 + g_cpu.X) & 0xFF), g_cpu.A);
label_FD92:;
    /* $FD92: 86 */ maybe_trigger_vblank(3); nes_write(0x3A, g_cpu.X);
label_FD94:;
    /* $FD94: 3A */ maybe_trigger_vblank(2); /* NOP */
label_FD95:;
    /* $FD95: 3A */ maybe_trigger_vblank(2); /* NOP */
label_FD96:;
    /* $FD96: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FD98:;
    /* $FD98: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x40 + g_cpu.X) & 0xFF), g_cpu.A);
label_FD9A:;
    /* $FD9A: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FD9C:;
    /* $FD9C: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x3A + g_cpu.X) & 0xFF), g_cpu.A);
label_FD9E:;
    /* $FD9E: 86 */ maybe_trigger_vblank(3); nes_write(0x36, g_cpu.X);
label_FDA0:;
    /* $FDA0: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x36 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FDA2:;
    /* $FDA2: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FDA4:;
    /* $FDA4: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x3A + g_cpu.X) & 0xFF), g_cpu.A);
label_FDA6:;
    /* $FDA6: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FDA8:;
    /* $FDA8: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x36 + g_cpu.X) & 0xFF), g_cpu.A);
label_FDAA:;
    /* $FDAA: 86 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.X);
label_FDAC:;
    /* $FDAC: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FDAE:;
    /* $FDAE: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FDAF:;
    /* $FDAF: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x81 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FDB1:;
    /* $FDB1: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x34 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FDB3:;
    /* $FDB3: 85 */ maybe_trigger_vblank(3); nes_write(0x34, g_cpu.A);
label_FDB5:;
    /* $FDB5: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x2A + g_cpu.X) & 0xFF), g_cpu.A);
label_FDB7:;
    /* $FDB7: 86 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.X);
label_FDB9:;
    /* $FDB9: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFDB9); return;
label_FDBA:;
    /* $FDBA: 84 */ maybe_trigger_vblank(3); nes_write(0x90, g_cpu.Y);
label_FDBC:;
    /* $FDBC: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_FD42;
    }
label_FDBE:;
    /* $FDBE: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) { call_by_address(0xFE10); return; }
label_FDC0:;
    /* $FDC0: B0 */ maybe_trigger_vblank(2); if (g_cpu.C) goto label_FDC2;
label_FDC2:;
    /* $FDC2: 98 */ maybe_trigger_vblank(2); g_cpu.A = g_cpu.Y; FLAG_NZ(g_cpu.A);
label_FDC3:;
    /* $FDC3: 96 */ maybe_trigger_vblank(4); nes_write((0x94 + g_cpu.Y) & 0xFF, g_cpu.X);
label_FDC5:;
    /* $FDC5: 92 */ maybe_trigger_vblank(2); /* ILLEGAL $92 — skip 1 */
label_FDC6:;
    /* $FDC6: 94 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.X) & 0xFF, g_cpu.Y);
label_FDC8:;
    /* $FDC8: 58 */ maybe_trigger_vblank(2); g_cpu.I = 0;
label_FDC9:;
    /* $FDC9: 58 */ maybe_trigger_vblank(2); g_cpu.I = 0;
label_FDCA:;
    /* $FDCA: 58 */ maybe_trigger_vblank(2); g_cpu.I = 0;
label_FDCB:;
    /* $FDCB: 44 */ maybe_trigger_vblank(3); (void)nes_read(0x5C); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FDCD:;
    /* $FDCD: 44 */ maybe_trigger_vblank(3); (void)nes_read(0x9F); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FDCF:;
    /* $FDCF: A3 */ maybe_trigger_vblank(6); g_cpu.A = g_cpu.X = nes_read(nes_read16zp((0xA1 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FDD1:;
    /* $FDD1: A3 */ maybe_trigger_vblank(6); g_cpu.A = g_cpu.X = nes_read(nes_read16zp((0x85 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FDD3:;
    /* $FDD3: A3 */ maybe_trigger_vblank(6); g_cpu.A = g_cpu.X = nes_read(nes_read16zp((0xE0 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FDD5:;
    /* $FDD5: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x23); FLAG_NZ(g_cpu.X);
label_FDD7:;
    /* $FDD7: C4 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x9F); int r=g_cpu.Y-m; g_cpu.C=(g_cpu.Y>=m)?1:0; FLAG_NZ(r&0xFF); }
label_FDD9:;
    /* $FDD9: 9D */ maybe_trigger_vblank(5); nes_write((0x859F + g_cpu.X) & 0xFFFF, g_cpu.A);
label_FDDC:;
    /* $FDDC: 9F */ maybe_trigger_vblank(5); /* ILLEGAL $9F — skip 3 */
label_FDDF:;
    /* $FDDF: 23 */ maybe_trigger_vblank(8); /* ILLEGAL $23 — skip 2 */
label_FDE1:;
    /* $FDE1: B5 */ maybe_trigger_vblank(4); g_cpu.A = nes_read((0xB1 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_FDE3:;
    /* $FDE3: AF */ maybe_trigger_vblank(4); g_cpu.A = g_cpu.X = nes_read(0xB185); FLAG_NZ(g_cpu.A);
label_FDE6:;
    /* $FDE6: AF */ maybe_trigger_vblank(4); g_cpu.A = g_cpu.X = nes_read(0x85AD); FLAG_NZ(g_cpu.A);
label_FDE9:;
    /* $FDE9: 95 */ maybe_trigger_vblank(4); nes_write((0x9E + g_cpu.X) & 0xFF, g_cpu.A);
label_FDEB:;
    /* $FDEB: A2 */ maybe_trigger_vblank(2); g_cpu.X = 0xAA; FLAG_NZ(g_cpu.X);
label_FDED:;
    /* $FDED: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_FDEE:;
    /* $FDEE: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_FDEF:;
    /* $FDEF: 6B */ maybe_trigger_vblank(2); /* ILLEGAL $6B — skip 2 */
label_FDF1:;
    /* $FDF1: 9D */ maybe_trigger_vblank(5); nes_write((0x0484 + g_cpu.X) & 0xFFFF, g_cpu.A);
label_FDF4:;
    /* $FDF4: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x82); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FDF6:;
    /* $FDF6: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FDF7:;
    /* $FDF7: 86 */ maybe_trigger_vblank(3); nes_write(0x22, g_cpu.X);
label_FDF9:;
    /* $FDF9: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FDFB:;
    /* $FDFB: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FDFC:;
    /* $FDFC: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2212); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FDFF:;
    /* $FDFF: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FE00:;
    /* $FE00: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x22 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE02:;
    /* $FE02: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x221C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FE05:;
    /* $FE05: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2214); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FE08:;
    /* $FE08: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2212); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FE0B:;
    /* $FE0B: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FE0C:;
    /* $FE0C: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x22 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE0E:;
    /* $FE0E: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x221C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FE11:;
    /* $FE11: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2218); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FE14:;
    /* $FE14: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FE15:;
    /* $FE15: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x20 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FE17:;
    /* $FE17: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FE18:;
    /* $FE18: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_FE19:;
    /* $FE19: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE1A:;
    /* $FE1A: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FE1B:;
    /* $FE1B: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_FE1C:;
    /* $FE1C: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE1D:;
    /* $FE1D: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FE1E:;
    /* $FE1E: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_FE1F:;
    /* $FE1F: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE20:;
    /* $FE20: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FE21:;
    /* $FE21: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_FE22:;
    /* $FE22: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE23:;
    /* $FE23: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FE24:;
    /* $FE24: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x22 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE26:;
    /* $FE26: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x220C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FE29:;
    /* $FE29: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x2214); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FE2C:;
    /* $FE2C: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x12 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE2E:;
    /* $FE2E: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE2F:;
    /* $FE2F: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_FE41;
label_FE31:;
    /* $FE31: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE32:;
    /* $FE32: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x2216; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FE35:;
    /* $FE35: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x18 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE37:;
    /* $FE37: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x36; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FE39:;
    /* $FE39: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x26 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FE3B:;
    /* $FE3B: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x14 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FE3D:;
    /* $FE3D: 26 */ maybe_trigger_vblank(5); { uint16_t a=0x36; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FE3F:;
    /* $FE3F: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_FE40:;
    /* $FE40: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE41:;
    /* $FE41: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x5C + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FE43:;
    /* $FE43: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE44:;
    /* $FE44: 34 */ maybe_trigger_vblank(4); (void)nes_read((0x0C + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE46:;
    /* $FE46: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE47:;
    /* $FE47: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE48:;
    /* $FE48: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x1E + g_cpu.X) & 0xFF), g_cpu.A);
label_FE4A:;
    /* $FE4A: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1E85 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FE4D:;
    /* $FE4D: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x12 + g_cpu.X) & 0xFF), g_cpu.A);
label_FE4F:;
    /* $FE4F: 86 */ maybe_trigger_vblank(3); nes_write(0x14, g_cpu.X);
label_FE51:; /* EndOfCastleMusData */
    /* $FE51: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x2C + g_cpu.X) & 0xFF), g_cpu.A);
label_FE53:;
    /* $FE53: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE54:;
    /* $FE54: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x222C + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE57:;
    /* $FE57: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2C85 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE5A:;
    /* $FE5A: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x81); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE5C:;
    /* $FE5C: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x1E24; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FE5F:;
    /* $FE5F: 2E */ maybe_trigger_vblank(6); { uint16_t a=0x1E24; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FE62:;
    /* $FE62: 85 */ maybe_trigger_vblank(3); nes_write(0x2E, g_cpu.A);
label_FE64:;
    /* $FE64: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x81); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE66:;
    /* $FE66: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_FE67:;
    /* $FE67: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FE68:;
    /* $FE68: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE69:;
    /* $FE69: 32 */ maybe_trigger_vblank(2); /* ILLEGAL $32 — skip 1 */
label_FE6A:;
    /* $FE6A: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FE6B:;
    /* $FE6B: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE6C:;
    /* $FE6C: 85 */ maybe_trigger_vblank(3); nes_write(0x32, g_cpu.A);
label_FE6E:;
    /* $FE6E: 87 */ maybe_trigger_vblank(3); nes_write(0x36, g_cpu.A & g_cpu.X); /* SAX */
label_FE70:;
    /* $FE70: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x36 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FE72:;
    /* $FE72: 84 */ maybe_trigger_vblank(3); nes_write(0x3A, g_cpu.Y);
label_FE74:;
    /* $FE74: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFE74); return;
label_FE75:;
    /* $FE75: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x4C54 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE78:;
    /* $FE78: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x4C54 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE7B:;
    /* $FE7B: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x1C1C + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE7E:;
    /* $FE7E: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x5C5C + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE81:;
    /* $FE81: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x565E + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FE84:;
    /* $FE84: 4E */ maybe_trigger_vblank(6); { uint16_t a=0x565E; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_FE87:;
    /* $FE87: 4E */ maybe_trigger_vblank(6); { uint16_t a=0x1E5E; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_FE8A:;
    /* $FE8A: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x5E5E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FE8D:;
    /* $FE8D: 5E */ maybe_trigger_vblank(7); { uint16_t a=(0x625E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=v&1; v>>=1; nes_write(a,v); FLAG_NZ(v); }
label_FE90:;
    /* $FE90: 5A */ maybe_trigger_vblank(2); /* NOP */
label_FE91:;
    /* $FE91: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) goto label_FEF5;
label_FE93:;
    /* $FE93: 5A */ maybe_trigger_vblank(2); /* NOP */
label_FE94:;
    /* $FE94: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) { call_by_address(0xFEF8); return; }
label_FE96:;
    /* $FE96: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE97:;
    /* $FE97: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FE98:;
    /* $FE98: 62 */ maybe_trigger_vblank(2); /* ILLEGAL $62 — skip 1 */
label_FE99:;
    /* $FE99: E7 */ maybe_trigger_vblank(5); /* ILLEGAL $E7 — skip 2 */
label_FE9B:;
    /* $FE9B: E7 */ maybe_trigger_vblank(5); /* ILLEGAL $E7 — skip 2 */
label_FE9D:;
    /* $FE9D: 86 */ maybe_trigger_vblank(3); nes_write(0x14, g_cpu.X);
label_FE9F:;
    /* $FE9F: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x14 + g_cpu.X) & 0xFF), g_cpu.A);
label_FEA1:;
    /* $FEA1: 80 */ maybe_trigger_vblank(2); /* NOP */
label_FEA3:;
    /* $FEA3: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x81 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FEA5:;
    /* $FEA5: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x14 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FEA7:;
    /* $FEA7: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x14 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FEA9:;
    /* $FEA9: 86 */ maybe_trigger_vblank(3); nes_write(0x16, g_cpu.X);
label_FEAB:;
    /* $FEAB: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x16 + g_cpu.X) & 0xFF), g_cpu.A);
label_FEAD:;
    /* $FEAD: 80 */ maybe_trigger_vblank(2); /* NOP */
label_FEAF:;
    /* $FEAF: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x81 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FEB1:;
    /* $FEB1: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x16 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FEB3:;
    /* $FEB3: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x16 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FEB5:;
    /* $FEB5: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x28 + g_cpu.X) & 0xFF), g_cpu.A);
label_FEB7:;
    /* $FEB7: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FEB8:;
    /* $FEB8: 1A */ maybe_trigger_vblank(2); /* NOP */
label_FEB9:;
    /* $FEB9: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FEBA:;
    /* $FEBA: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FEBB:;
    /* $FEBB: 1A */ maybe_trigger_vblank(2); /* NOP */
label_FEBC:;
    /* $FEBC: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FEBD:;
    /* $FEBD: 80 */ maybe_trigger_vblank(2); /* NOP */
label_FEBF:;
    /* $FEBF: 28 */ maybe_trigger_vblank(4); { g_cpu.S++; uint8_t p = g_ram[0x100 + g_cpu.S];
  g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1;
  g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; }
label_FEC0:;
    /* $FEC0: 81 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x28 + g_cpu.X) & 0xFF), g_cpu.A);
label_FEC2:;
    /* $FEC2: 87 */ maybe_trigger_vblank(3); nes_write(0x2C, g_cpu.A & g_cpu.X); /* SAX */
label_FEC4:;
    /* $FEC4: 2C */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x842C); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FEC7:;
    /* $FEC7: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) { call_by_address(0xFE4C); return; }
label_FEC9:;
    /* $FEC9: 04 */ maybe_trigger_vblank(3); (void)nes_read(0x84); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FECB:;
    /* $FECB: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x6283); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FECE:;
    /* $FECE: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_FE54;
    }
label_FED0:;
    /* $FED0: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_FED1:;
    /* $FED1: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x1C + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_FED3:;
    /* $FED3: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FED4:;
    /* $FED4: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x2622 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FED7:;
    /* $FED7: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_FED8:;
    /* $FED8: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1C04 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FEDB:;
    /* $FEDB: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFEDB); return;
label_FEDC:;
    /* $FEDC: E3 */ maybe_trigger_vblank(8); /* ILLEGAL $E3 — skip 2 */
label_FEDE:;
    /* $FEDE: E3 */ maybe_trigger_vblank(8); /* ILLEGAL $E3 — skip 2 */
label_FEE0:;
    /* $FEE0: DE */ maybe_trigger_vblank(7); { uint16_t a=(0x23E0 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)-1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FEE3:;
    /* $FEE3: EC */ maybe_trigger_vblank(4); { uint8_t m=nes_read(0x7475); int r=g_cpu.X-m; g_cpu.C=(g_cpu.X>=m)?1:0; FLAG_NZ(r&0xFF); }
label_FEE6:;
    /* $FEE6: F0 */ maybe_trigger_vblank(2); if (g_cpu.Z) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_FEDC;
    }
label_FEE8:;
    /* $FEE8: F6 */ maybe_trigger_vblank(6); { uint16_t a=(0xEA + g_cpu.X) & 0xFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FEEA:;
    /* $FEEA: 31 */ maybe_trigger_vblank(5); g_cpu.A &= nes_read((nes_read16zp(0x2D) + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FEEC:;
    /* $FEEC: 83 */ maybe_trigger_vblank(6); nes_write(nes_read16zp((0x12 + g_cpu.X) & 0xFF), g_cpu.A & g_cpu.X); /* SAX */
label_FEEE:;
    /* $FEEE: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x04 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FEF0:;
    /* $FEF0: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_FEF1:;
    /* $FEF1: 1A */ maybe_trigger_vblank(2); /* NOP */
label_FEF2:;
    /* $FEF2: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x2614 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FEF5:;
    /* $FEF5: 22 */ maybe_trigger_vblank(2); /* ILLEGAL $22 — skip 1 */
label_FEF6:;
    /* $FEF6: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x181C + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FEF9:;
    /* $FEF9: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x0C22 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FEFC:;
    /* $FEFC: 14 */ maybe_trigger_vblank(4); (void)nes_read((0xFF + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FEFE:;
    /* $FEFE: FF */ maybe_trigger_vblank(7); /* ILLEGAL $FF — skip 3 */
label_FF01:;
    /* $FF01: 88 */ maybe_trigger_vblank(2); g_cpu.Y = (g_cpu.Y-1)&0xFF; FLAG_NZ(g_cpu.Y);
label_FF02:;
    /* $FF02: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFF02); return;
label_FF03:;
    /* $FF03: 2F */ maybe_trigger_vblank(6); /* ILLEGAL $2F — skip 3 */
label_FF06:;
    /* $FF06: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_FF07:;
    /* $FF07: A6 */ maybe_trigger_vblank(3); g_cpu.X = nes_read(0x02); FLAG_NZ(g_cpu.X);
label_FF09:;
    /* $FF09: 80 */ maybe_trigger_vblank(2); /* NOP */
label_FF0B:;
    /* $FF0B: 5C */ maybe_trigger_vblank(4); (void)nes_read((0x3A02 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FF0E:;
    /* $FF0E: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_FF0F:;
    /* $FF0F: 1A */ maybe_trigger_vblank(2); /* NOP */
label_FF10:;
    /* $FF10: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0xDF + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FF12:;
    /* $FF12: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0xC4 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FF14:;
    /* $FF14: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0xAB + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FF16:;
    /* $FF16: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x93 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FF18:;
    /* $FF18: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x7C + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FF1A:;
    /* $FF1A: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x67 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FF1C:;
    /* $FF1C: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x53 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FF1E:;
    /* $FF1E: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x40 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FF20:;
    /* $FF20: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x2E + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FF22:;
    /* $FF22: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x1D + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FF24:;
    /* $FF24: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x0D + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FF26:;
    /* $FF26: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFF26); return;
label_FF27:;
    /* $FF27: FE */ maybe_trigger_vblank(7); { uint16_t a=(0xEF00 + g_cpu.X) & 0xFFFF; uint8_t v=(nes_read(a)+1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FF2A:;
    /* $FF2A: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFF2A); return;
label_FF2B:;
    /* $FF2B: E2 */ maybe_trigger_vblank(2); /* NOP */
label_FF2D:;
    /* $FF2D: D5 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x00 + g_cpu.X) & 0xFF); int r=g_cpu.A-m; g_cpu.C=(g_cpu.A>=m)?1:0; FLAG_NZ(r&0xFF); }
label_FF2F:;
    /* $FF2F: C9 */ maybe_trigger_vblank(2); { int r=g_cpu.A-0x00; g_cpu.C=(g_cpu.A>=0x00)?1:0; FLAG_NZ(r&0xFF); }
label_FF31:;
    /* $FF31: BE */ maybe_trigger_vblank(4); g_cpu.X = nes_read((0xB300 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.X);
label_FF34:;
    /* $FF34: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFF34); return;
label_FF35:;
    /* $FF35: A9 */ maybe_trigger_vblank(2); g_cpu.A = 0x00; FLAG_NZ(g_cpu.A);
label_FF37:;
    /* $FF37: A0 */ maybe_trigger_vblank(2); g_cpu.Y = 0x00; FLAG_NZ(g_cpu.Y);
label_FF39:;
    /* $FF39: 97 */ maybe_trigger_vblank(4); nes_write((0x00 + g_cpu.Y) & 0xFF, g_cpu.A & g_cpu.X); /* SAX */
label_FF3B:;
    /* $FF3B: 8E */ maybe_trigger_vblank(4); nes_write(0x8600, g_cpu.X);
label_FF3E:;
    /* $FF3E: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFF3E); return;
label_FF3F:;
    /* $FF3F: 77 */ maybe_trigger_vblank(6); /* ILLEGAL $77 — skip 2 */
label_FF41:;
    /* $FF41: 7E */ maybe_trigger_vblank(7); { uint16_t a=(0x7100 + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=v&1; v=((v>>1)|(c<<7))&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FF44:;
    /* $FF44: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFF44); return;
label_FF45:;
    /* $FF45: 54 */ maybe_trigger_vblank(4); (void)nes_read((0x00 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FF47:;
    /* $FF47: 64 */ maybe_trigger_vblank(3); (void)nes_read(0x00); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FF49:;
    /* $FF49: 5F */ maybe_trigger_vblank(7); /* ILLEGAL $5F — skip 3 */
label_FF4C:;
    /* $FF4C: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFF4C); return;
label_FF4D:;
    /* $FF4D: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) goto label_FF4F;
label_FF4F:;
    /* $FF4F: 47 */ maybe_trigger_vblank(5); /* ILLEGAL $47 — skip 2 */
label_FF51:;
    /* $FF51: 43 */ maybe_trigger_vblank(8); /* ILLEGAL $43 — skip 2 */
label_FF53:;
    /* $FF53: 3B */ maybe_trigger_vblank(7); /* ILLEGAL $3B — skip 3 */
label_FF56:;
    /* $FF56: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFF56); return;
label_FF57:;
    /* $FF57: 2A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=(g_cpu.A>>7)&1; g_cpu.A=((g_cpu.A<<1)|c)&0xFF; FLAG_NZ(g_cpu.A); }
label_FF58:;
    /* $FF58: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFF58); return;
label_FF59:;
    /* $FF59: 23 */ maybe_trigger_vblank(8); /* ILLEGAL $23 — skip 2 */
label_FF5B:;
    /* $FF5B: 75 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0x03 + g_cpu.X) & 0xFF); uint16_t r=g_cpu.A+m+g_cpu.C; FLAG_NZC_ADD(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_FF5D:;
    /* $FF5D: 57 */ maybe_trigger_vblank(6); /* ILLEGAL $57 — skip 2 */
label_FF5F:;
    /* $FF5F: F9 */ maybe_trigger_vblank(4); { uint8_t m=nes_read((0xCF02 + g_cpu.Y) & 0xFFFF); int16_t r=g_cpu.A-m-(1-g_cpu.C); FLAG_NZC_SUB(r,g_cpu.A,m); g_cpu.A=r&0xFF; }
label_FF62:;
    /* $FF62: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0xFC + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FF64:;
    /* $FF64: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFF64); return;
label_FF65:;
    /* $FF65: 6A */ maybe_trigger_vblank(2); { uint8_t c=g_cpu.C; g_cpu.C=g_cpu.A&1; g_cpu.A=((g_cpu.A>>1)|(c<<7))&0xFF; FLAG_NZ(g_cpu.A); }
label_FF66:; /* MusicLengthLookupTbl */
    /* $FF66: 05 */ maybe_trigger_vblank(3); g_cpu.A |= nes_read(0x0A); FLAG_NZ(g_cpu.A);
label_FF68:;
    /* $FF68: 14 */ maybe_trigger_vblank(4); (void)nes_read((0x28 + g_cpu.X) & 0xFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FF6A:;
    /* $FF6A: 50 */ maybe_trigger_vblank(2); if (!g_cpu.V) goto label_FF8A;
label_FF6C:;
    /* $FF6C: 3C */ maybe_trigger_vblank(4); (void)nes_read((0x0402 + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FF6F:;
    /* $FF6F: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_FF70:;
    /* $FF70: 10 */ maybe_trigger_vblank(2); if (!g_cpu.N) goto label_FF92;
label_FF72:;
    /* $FF72: 40 */ maybe_trigger_vblank(6); /* RTI */ g_cpu.S++; { uint8_t p=g_ram[0x100+g_cpu.S]; g_cpu.N=(p>>7)&1; g_cpu.V=(p>>6)&1; g_cpu.D=(p>>3)&1; g_cpu.I=(p>>2)&1; g_cpu.Z=(p>>1)&1; g_cpu.C=p&1; } g_cpu.S++; g_cpu.S++; /* pop PCL, PCH */
    return;
label_FF73:;
    /* $FF73: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_FF74:;
    /* $FF74: 30 */ maybe_trigger_vblank(2); if (g_cpu.N) goto label_FF82;
label_FF76:;
    /* $FF76: 03 */ maybe_trigger_vblank(8); /* ILLEGAL $03 — skip 2 */
label_FF78:;
    /* $FF78: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x3018); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FF7B:;
    /* $FF7B: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_FF7C:;
    /* $FF7C: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x08); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FF7E:;
    /* $FF7E: 36 */ maybe_trigger_vblank(6); { uint16_t a=(0x03 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); uint8_t c=g_cpu.C; g_cpu.C=(v>>7)&1; v=((v<<1)|c)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FF80:;
    /* $FF80: 09 */ maybe_trigger_vblank(2); g_cpu.A |= 0x06; FLAG_NZ(g_cpu.A);
label_FF82:;
    /* $FF82: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_FF83:;
    /* $FF83: 1B */ maybe_trigger_vblank(7); /* ILLEGAL $1B — skip 3 */
label_FF86:;
    /* $FF86: 24 */ maybe_trigger_vblank(3); { uint8_t m=nes_read(0x02); g_cpu.Z=(g_cpu.A&m)?0:1; g_cpu.N=(m>>7)&1; g_cpu.V=(m>>6)&1; }
label_FF88:;
    /* $FF88: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x04; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FF8A:;
    /* $FF8A: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x1812); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FF8D:;
    /* $FF8D: 08 */ maybe_trigger_vblank(3); { uint8_t p = (g_cpu.N<<7)|(g_cpu.V<<6)|0x30|(g_cpu.D<<3)|(g_cpu.I<<2)|(g_cpu.Z<<1)|g_cpu.C;
  g_ram[0x100 + g_cpu.S] = p; g_cpu.S--; }
label_FF8E:;
    /* $FF8E: 12 */ maybe_trigger_vblank(2); /* ILLEGAL $12 — skip 1 */
label_FF8F:;
    /* $FF8F: 01 */ maybe_trigger_vblank(6); g_cpu.A |= nes_read(nes_read16zp((0x03 + g_cpu.X) & 0xFF)); FLAG_NZ(g_cpu.A);
label_FF91:;
    /* $FF91: 02 */ maybe_trigger_vblank(2); /* ILLEGAL $02 — skip 1 */
label_FF92:;
    /* $FF92: 06 */ maybe_trigger_vblank(5); { uint16_t a=0x09; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FF94:;
    /* $FF94: 0C */ maybe_trigger_vblank(4); (void)nes_read(0x9804); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FF97:;
    /* $FF97: 99 */ maybe_trigger_vblank(5); nes_write((0x9B9A + g_cpu.Y) & 0xFFFF, g_cpu.A);
label_FF9A:; /* AreaMusicEnvData */
    /* $FF9A: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) { call_by_address(0xFF30); return; }
label_FF9C:;
    /* $FF9C: 94 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.X) & 0xFF, g_cpu.Y);
label_FF9E:;
    /* $FF9E: 95 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.X) & 0xFF, g_cpu.A);
label_FFA0:;
    /* $FFA0: 97 */ maybe_trigger_vblank(4); nes_write((0x98 + g_cpu.Y) & 0xFF, g_cpu.A & g_cpu.X); /* SAX */
label_FFA2:; /* WaterEventMusEnvData */
    /* $FFA2: 90 */ maybe_trigger_vblank(2); if (!g_cpu.C) {
    maybe_trigger_vblank(2);
#ifdef WATCHDOG_ENABLED
    watchdog_check();
#endif
    goto label_FF35;
    }
label_FFA4:;
    /* $FFA4: 92 */ maybe_trigger_vblank(2); /* ILLEGAL $92 — skip 1 */
label_FFA5:;
    /* $FFA5: 92 */ maybe_trigger_vblank(2); /* ILLEGAL $92 — skip 1 */
label_FFA6:;
    /* $FFA6: 93 */ maybe_trigger_vblank(6); /* ILLEGAL $93 — skip 2 */
label_FFA8:;
    /* $FFA8: 93 */ maybe_trigger_vblank(6); /* ILLEGAL $93 — skip 2 */
label_FFAA:;
    /* $FFAA: 94 */ maybe_trigger_vblank(4); nes_write((0x94 + g_cpu.X) & 0xFF, g_cpu.Y);
label_FFAC:;
    /* $FFAC: 94 */ maybe_trigger_vblank(4); nes_write((0x94 + g_cpu.X) & 0xFF, g_cpu.Y);
label_FFAE:;
    /* $FFAE: 94 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.X) & 0xFF, g_cpu.Y);
label_FFB0:;
    /* $FFB0: 95 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.X) & 0xFF, g_cpu.A);
label_FFB2:;
    /* $FFB2: 95 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.X) & 0xFF, g_cpu.A);
label_FFB4:;
    /* $FFB4: 95 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.X) & 0xFF, g_cpu.A);
label_FFB6:;
    /* $FFB6: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_FFB8:;
    /* $FFB8: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_FFBA:;
    /* $FFBA: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_FFBC:;
    /* $FFBC: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_FFBE:;
    /* $FFBE: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_FFC0:;
    /* $FFC0: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_FFC2:;
    /* $FFC2: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_FFC4:;
    /* $FFC4: 96 */ maybe_trigger_vblank(4); nes_write((0x96 + g_cpu.Y) & 0xFF, g_cpu.X);
label_FFC6:;
    /* $FFC6: 95 */ maybe_trigger_vblank(4); nes_write((0x95 + g_cpu.X) & 0xFF, g_cpu.A);
label_FFC8:;
    /* $FFC8: 94 */ maybe_trigger_vblank(4); nes_write((0x93 + g_cpu.X) & 0xFF, g_cpu.Y);
label_FFCA:; /* BowserFlameEnvData */
    /* $FFCA: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_FFCC:;
    /* $FFCC: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x17 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FFCE:;
    /* $FFCE: 17 */ maybe_trigger_vblank(6); /* ILLEGAL $17 — skip 2 */
label_FFD0:;
    /* $FFD0: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x1A19 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FFD3:;
    /* $FFD3: 1A */ maybe_trigger_vblank(2); /* NOP */
label_FFD4:;
    /* $FFD4: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x1D1D + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FFD7:;
    /* $FFD7: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1F1E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FFDA:;
    /* $FFDA: 1F */ maybe_trigger_vblank(7); /* ILLEGAL $1F — skip 3 */
label_FFDD:;
    /* $FFDD: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1C1D + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FFE0:;
    /* $FFE0: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1F1F + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FFE3:;
    /* $FFE3: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1C1D + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FFE6:;
    /* $FFE6: 1A */ maybe_trigger_vblank(2); /* NOP */
label_FFE7:;
    /* $FFE7: 18 */ maybe_trigger_vblank(2); g_cpu.C = 0;
label_FFE8:;
    /* $FFE8: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x14 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FFEA:; /* BrickShatterEnvData */
    /* $FFEA: 15 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x16 + g_cpu.X) & 0xFF); FLAG_NZ(g_cpu.A);
label_FFEC:;
    /* $FFEC: 16 */ maybe_trigger_vblank(6); { uint16_t a=(0x17 + g_cpu.X) & 0xFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FFEE:;
    /* $FFEE: 17 */ maybe_trigger_vblank(6); /* ILLEGAL $17 — skip 2 */
label_FFF0:;
    /* $FFF0: 19 */ maybe_trigger_vblank(4); g_cpu.A |= nes_read((0x1A19 + g_cpu.Y) & 0xFFFF); FLAG_NZ(g_cpu.A);
label_FFF3:;
    /* $FFF3: 1A */ maybe_trigger_vblank(2); /* NOP */
label_FFF4:;
    /* $FFF4: 1C */ maybe_trigger_vblank(4); (void)nes_read((0x1D1D + g_cpu.X) & 0xFFFF); /* NOP* (unofficial DOP/TOP read, result discarded) */
label_FFF7:;
    /* $FFF7: 1E */ maybe_trigger_vblank(7); { uint16_t a=(0x1F1E + g_cpu.X) & 0xFFFF; uint8_t v=nes_read(a); g_cpu.C=(v>>7)&1; v=(v<<1)&0xFF; nes_write(a,v); FLAG_NZ(v); }
label_FFFA:;
    /* $FFFA: 82 */ maybe_trigger_vblank(2); /* NOP */
label_FFFC:;
    /* $FFFC: 00 */ maybe_trigger_vblank(7); nes_brk_executed(0xFFFC); return;
}

}  // namespace smb::semcomp
