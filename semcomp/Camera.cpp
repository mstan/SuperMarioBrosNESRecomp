// semcomp/Camera.cpp — Camera facade. Reads only.
#include "semcomp/Camera.h"
#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"

namespace smb::semcomp {

std::uint16_t Camera::left_world_x() const {
    return state_.read_page_offset(ram::ScreenLeft_PageLoc,
                                    ram::ScreenLeft_X_Pos);
}

std::uint16_t Camera::right_world_x() const {
    return state_.read_page_offset(ram::ScreenRight_PageLoc,
                                    ram::ScreenRight_X_Pos);
}

std::uint16_t Camera::width() const {
    const std::uint16_t l = left_world_x();
    const std::uint16_t r = right_world_x();
    return static_cast<std::uint16_t>(r - l);
}

}  // namespace smb::semcomp
