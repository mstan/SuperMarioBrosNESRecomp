// semcomp/BgRenderer.h — bulk-ported routines (auto-generated).
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class BgRenderer {
public:
    explicit BgRenderer(GameState& state) : state_(state) {}

    void set_v_r_a_m_addr__a();  // $85C5 SetVRAMAddr_A
    void set_v_r_a_m_offset();  // $863F SetVRAMOffset
    void set_v_r_a_m_addr__b();  // $864C SetVRAMAddr_B
    void write_top_status_line();  // $8652 WriteTopStatusLine
    void write_bottom_status_line();  // $865A WriteBottomStatusLine
    void write_top_score();  // $8749 WriteTopScore
    void set_v_r_a_m_ctrl();  // $89BD SetVRAMCtrl
    void write_n_t_addr();  // $8E2D WriteNTAddr
    void write_buffer_to_screen();  // $8E92 WriteBufferToScreen
    void write_p_p_u_reg1();  // $8EED WritePPUReg1

private:
    GameState& state_;
};

}  // namespace smb::semcomp
