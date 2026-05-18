// semcomp/AudioEngine.h — bulk-ported routines (auto-generated).
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class AudioEngine {
public:
    explicit AudioEngine(GameState& state) : state_(state) {}

    void square1_sfx_handler();  // $F41B Square1SfxHandler
    void square2_sfx_handler();  // $F57C Square2SfxHandler
    void sound_engine();  // $F2D0 SoundEngine (entry 0)
    void at_f2d3();  // $F2D3 at_f2d3 (entry 1)
    void at_f2ea();  // $F2EA at_f2ea (entry 2)
    void at_f2f3();  // $F2F3 at_f2f3 (entry 3)
    void at_f329();  // $F329 at_f329 (entry 4)
    void at_f380();  // $F380 at_f380 (entry 5)
    void at_f367();  // $F367 at_f367 (entry 6)
    void no_inc_dac();  // $F377 NoIncDAC (entry 7)
    void dump_squ1_regs();  // $F381 Dump_Squ1_Regs (entry 0)
    void at_f384();  // $F384 at_f384 (entry 1)
    void play_squ1_sfx();  // $F388 PlaySqu1Sfx (entry 0)
    void at_f38e();  // $F38E at_f38e (entry 1)
    void dump_sq2_regs();  // $F39F Dump_Sq2_Regs (entry 0)
    void at_f3a5();  // $F3A5 at_f3a5 (entry 1)
    void play_squ2_sfx();  // $F3A6 PlaySqu2Sfx (entry 0)
    void no_p_dwn_l();  // $F4D1 NoPDwnL (entry 1)
    void at_f410();  // $F410 at_f410 (entry 2)
    void at_f4b0();  // $F4B0 at_f4b0 (entry 3)
    void fps2nd();  // $F3F2 FPS2nd (entry 4)
    void dmp_jp_fps();  // $F3F4 DmpJpFPS (entry 5)
    void at_f4be();  // $F4BE at_f4be (entry 6)
    void at_f4bf();  // $F4BF at_f4bf (entry 7)
    void at_f4a5();  // $F4A5 at_f4a5 (entry 8)
    void at_f405();  // $F405 at_f405 (entry 9)
    void at_f486();  // $F486 at_f486 (entry 10)
    void at_f421();  // $F421 at_f421 (entry 11)
    void at_f3ee();  // $F3EE at_f3ee (entry 12)
    void at_f490();  // $F490 at_f490 (entry 13)
    void at_f462();  // $F462 at_f462 (entry 14)
    void at_f4a9();  // $F4A9 at_f4a9 (entry 15)
    void at_f44c();  // $F44C at_f44c (entry 16)
    void play_coin_grab();  // $F518 PlayCoinGrab (entry 0)
    void blst_s_jp();  // $F5D1 BlstSJp (entry 1)
    void grow_item_regs();  // $F602 GrowItemRegs (entry 2)
    void n2_tone();  // $F538 N2Tone (entry 3)
    void at_f607();  // $F607 at_f607 (entry 4)
    void at_f621();  // $F621 at_f621 (entry 5)
    void at_f5f6();  // $F5F6 at_f5f6 (entry 6)
    void play_grow_power_up();  // $F5FC PlayGrowPowerUp (entry 7)
    void at_f624();  // $F624 at_f624 (entry 8)
    void at_f586();  // $F586 at_f586 (entry 9)
    void at_f5b2();  // $F5B2 at_f5b2 (entry 10)
    void at_f5f8();  // $F5F8 at_f5f8 (entry 11)
    void at_f5ed();  // $F5ED at_f5ed (entry 12)
    void jump_to_dec_length2();  // $F5C5 JumpToDecLength2 (entry 13)
    void el_l_regs();  // $F5E0 EL_LRegs (entry 14)
    void at_f5cf();  // $F5CF at_f5cf (entry 15)
    void div_l_loop();  // $F5EC DivLLoop (entry 16)
    void at_f5b9();  // $F5B9 at_f5b9 (entry 17)
    void at_f605();  // $F605 at_f605 (entry 18)
    void c_grab_t_tick_reg_l();  // $F522 CGrab_TTickRegL (entry 19)
    void at_f617();  // $F617 at_f617 (entry 20)
    void play_brick_shatter();  // $F63B PlayBrickShatter (entry 0)
    void decrement_sfx3_length();  // $F658 DecrementSfx3Length (entry 1)
    void at_f644();  // $F644 at_f644 (entry 2)
    void noise_sfx_handler();  // $F667 NoiseSfxHandler (entry 0)
    void continue_bowser_flame();  // $F685 ContinueBowserFlame (entry 1)
    void at_f679();  // $F679 at_f679 (entry 2)
    void at_f68f();  // $F68F at_f68f (entry 3)
    void music_handler();  // $F694 MusicHandler (entry 0)
    void silent_beat();  // $F8B9 SilentBeat (entry 1)
    void at_f7c3();  // $F7C3 at_f7c3 (entry 2)
    void at_f860();  // $F860 at_f860 (entry 3)
    void strong_beat();  // $F8A9 StrongBeat (entry 4)
    void find_event_music_header();  // $F6F1 FindEventMusicHeader (entry 5)
    void at_f80d();  // $F80D at_f80d (entry 6)
    void at_f720();  // $F720 at_f720 (entry 7)
    void at_f710();  // $F710 at_f710 (entry 8)
    void at_f6a1();  // $F6A1 at_f6a1 (entry 9)
    void at_f8ad();  // $F8AD at_f8ad (entry 10)
    void at_f829();  // $F829 at_f829 (entry 11)
    void at_f750();  // $F750 at_f750 (entry 12)
    void at_f6fc();  // $F6FC at_f6fc (entry 13)
    void at_f7a9();  // $F7A9 at_f7a9 (entry 14)
    void death_m_alt_reg();  // $F810 DeathMAltReg (entry 15)
    void at_f784();  // $F784 at_f784 (entry 16)
    void at_f885();  // $F885 at_f885 (entry 17)
    void squ2_note_handler();  // $F786 Squ2NoteHandler (entry 18)
    void at_f7a5();  // $F7A5 at_f7a5 (entry 19)
    void at_f7e6();  // $F7E6 at_f7e6 (entry 20)
    void at_f7e7();  // $F7E7 at_f7e7 (entry 21)
    void at_f8a5();  // $F8A5 at_f8a5 (entry 22)
    void at_f7e4();  // $F7E4 at_f7e4 (entry 23)
    void misc_squ1_music_tasks();  // $F7F7 MiscSqu1MusicTasks (entry 24)
    void skip_ctrl_l();  // $F7F1 SkipCtrlL (entry 25)
    void load_header();  // $F6F5 LoadHeader (entry 26)
    void fetch_noise_beat_data();  // $F878 FetchNoiseBeatData (entry 27)
    void at_f6b8();  // $F6B8 at_f6b8 (entry 28)
    void at_f7fb();  // $F7FB at_f7fb (entry 29)
    void at_f850();  // $F850 at_f850 (entry 30)
    void at_f88d();  // $F88D at_f88d (entry 31)
    void at_f6b6();  // $F6B6 at_f6b6 (entry 32)
    void medi_n();  // $F864 MediN (entry 33)
    void at_f862();  // $F862 at_f862 (entry 34)
    void at_f741();  // $F741 at_f741 (entry 35)
    void at_f844();  // $F844 at_f844 (entry 36)
    void at_f807();  // $F807 at_f807 (entry 37)
    void at_f706();  // $F706 at_f706 (entry 38)
    void at_f729();  // $F729 at_f729 (entry 39)
    void alternate_length_handler();  // $F8C5 AlternateLengthHandler (entry 0)
    void at_f8d0();  // $F8D0 at_f8d0 (entry 1)
    void at_f8c9();  // $F8C9 at_f8c9 (entry 2)
    void at_f8ca();  // $F8CA at_f8ca (entry 3)
    void at_f8c6();  // $F8C6 at_f8c6 (entry 4)
    void at_f8ce();  // $F8CE at_f8ce (entry 5)
    void at_f8c8();  // $F8C8 at_f8c8 (entry 6)
    void load_control_regs();  // $F8D8 LoadControlRegs (entry 0)
    void at_f8f1();  // $F8F1 at_f8f1 (entry 1)
    void at_f8e7();  // $F8E7 at_f8e7 (entry 2)
    void load_envelope_data();  // $F8F4 LoadEnvelopeData (entry 0)
    void at_f8fb();  // $F8FB at_f8fb (entry 1)
    void at_f90c();  // $F90C at_f90c (entry 2)
    void at_f903();  // $F903 at_f903 (entry 3)
    void at_f905();  // $F905 at_f905 (entry 4)

private:
    void sound_engine_body(int _entry);  // shared body for $F2D0 /* SoundEngine */
    void dump_squ1_regs_body(int _entry);  // shared body for $F381 /* Dump_Squ1_Regs */
    void play_squ1_sfx_body(int _entry);  // shared body for $F388 /* PlaySqu1Sfx */
    void dump_sq2_regs_body(int _entry);  // shared body for $F39F /* Dump_Sq2_Regs */
    void play_squ2_sfx_body(int _entry);  // shared body for $F3A6 /* PlaySqu2Sfx */
    void play_coin_grab_body(int _entry);  // shared body for $F518 /* PlayCoinGrab */
    void play_brick_shatter_body(int _entry);  // shared body for $F63B /* PlayBrickShatter */
    void noise_sfx_handler_body(int _entry);  // shared body for $F667 /* NoiseSfxHandler */
    void music_handler_body(int _entry);  // shared body for $F694 /* MusicHandler */
    void alternate_length_handler_body(int _entry);  // shared body for $F8C5 /* AlternateLengthHandler */
    void load_control_regs_body(int _entry);  // shared body for $F8D8 /* LoadControlRegs */
    void load_envelope_data_body(int _entry);  // shared body for $F8F4 /* LoadEnvelopeData */
    GameState& state_;
};

}  // namespace smb::semcomp
