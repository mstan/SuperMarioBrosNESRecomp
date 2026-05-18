// semcomp/SoundEngine.h — bulk-ported routines (auto-generated).
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class SoundEngine {
public:
    explicit SoundEngine(GameState& state) : state_(state) {}

    void run_offscr_bits_subs();  // $F1D7 RunOffscrBitsSubs
    void play_flagpole_slide();  // $F3BF PlayFlagpoleSlide
    void play_small_jump();  // $F3CD PlaySmallJump
    void play_big_jump();  // $F3D1 PlayBigJump
    void play_fireball_throw();  // $F3F9 PlayFireballThrow
    void play_bump();  // $F3FF PlayBump
    void play_timer_tick();  // $F51E PlayTimerTick
    void play_blast();  // $F53A PlayBlast
    void play_power_up_grab();  // $F552 PlayPowerUpGrab
    void play_noise_sfx();  // $F64D PlayNoiseSfx

private:
    GameState& state_;
};

}  // namespace smb::semcomp
