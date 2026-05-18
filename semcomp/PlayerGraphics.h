// semcomp/PlayerGraphics.h — Phase 17 ownership of player-graphics routines.
//
// Multiple multi-entry-body groups owned here:
//   $EEE9 PlayerGfxHandler  + 12 inner entries (EEF7, EF85, EEFC, EEFE,
//                              EEEE, EEF0, EEF1, EF10, EF01, EF42, EF7A, EF97)
//   $EFA4 DrawPlayer_Intermediate + 2 inner entries (EFA6 PIntLoop, EFAC)
//   $F12A RelativePlayerPosition  + 1 inner entry (F12C RelWOfs path)
//   $EFDC DrawPlayerLoop          (single entry)
//   $85F1 GetPlayerColors         (single entry)
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class PlayerGraphics {
public:
    explicit PlayerGraphics(GameState& state) : state_(state) {}

    // $85F1 GetPlayerColors — palette + sprite-attribute init.
    void get_player_colors();

    // $EFDC DrawPlayerLoop — render Mario's 4-tile sprite block.
    void draw_player_loop();

    // $F12A RelativePlayerPosition (multi-entry-body, 2 entries).
    void relative_player_position();   // entry 0 ($F12A)
    void relative_player_position_f12c();  // entry 1 ($F12C RelWOfs path)

    // $EFA4 DrawPlayer_Intermediate (multi-entry-body, 3 entries).
    void draw_player_intermediate();   // entry 0 ($EFA4)
    void draw_player_intermediate_pintloop();  // entry 1 ($EFA6 PIntLoop)
    void draw_player_intermediate_efac();      // entry 2 ($EFAC)

    // $EEE9 PlayerGfxHandler (multi-entry-body, 13 entries).
    void player_gfx_handler();         // entry 0 ($EEE9)
    void player_gfx_handler_eef7();    // entry 1 ($EEF7)
    void player_gfx_handler_ef85();    // entry 2 ($EF85)
    void player_gfx_handler_eefc();    // entry 3 ($EEFC)
    void player_gfx_handler_eefe();    // entry 4 ($EEFE)
    void player_gfx_handler_eeee();    // entry 5 ($EEEE)
    void player_gfx_handler_eef0();    // entry 6 ($EEF0)
    void player_gfx_handler_eef1();    // entry 7 ($EEF1)
    void player_gfx_handler_ef10();    // entry 8 ($EF10)
    void player_gfx_handler_ef01();    // entry 9 ($EF01)
    void player_gfx_handler_ef42();    // entry 10 ($EF42)
    void player_gfx_handler_ef7a();    // entry 11 ($EF7A PlayerOffscreenChk)
    void player_gfx_handler_ef97();    // entry 12 ($EF97)

private:
    GameState& state_;
};

}  // namespace smb::semcomp
