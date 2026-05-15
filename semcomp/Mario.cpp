// semcomp/Mario.cpp — Mario player facade. Reads only.
#include "semcomp/Mario.h"
#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"

namespace smb::semcomp {

std::uint8_t Mario::x() const {
    return state_.read8(ram::Player_X_Position);
}

std::uint8_t Mario::page() const {
    return state_.read8(ram::Player_PageLoc);
}

std::uint16_t Mario::world_x() const {
    return state_.read_page_offset(ram::Player_PageLoc,
                                    ram::Player_X_Position);
}

std::uint8_t Mario::spr_data_offset() const {
    return state_.read8(ram::Player_SprDataOffset);
}

}  // namespace smb::semcomp
