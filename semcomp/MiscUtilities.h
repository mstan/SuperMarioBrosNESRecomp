// semcomp/MiscUtilities.h — bulk-ported routines (auto-generated).
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class MiscUtilities {
public:
    explicit MiscUtilities(GameState& state) : state_(state) {}

    void inc_subtask();  // $8745 IncSubtask
    void move_all_sprites_offscreen();  // $8220 MoveAllSpritesOffscreen
    void move_sprites_offscreen();  // $8223 MoveSpritesOffscreen
    void get_alternate_palette1();  // $8643 GetAlternatePalette1
    void get_m_tile_attrib();  // $DFB0 GetMTileAttrib
    void move_six_sprites_offscreen();  // $E5B3 MoveSixSpritesOffscreen
    void increment_column_pos();  // $92DB IncrementColumnPos
    void inc_area_obj_offset();  // $9589 IncAreaObjOffset
    void inc_mode_task__b();  // $874E IncModeTask_B

private:
    GameState& state_;
};

}  // namespace smb::semcomp
