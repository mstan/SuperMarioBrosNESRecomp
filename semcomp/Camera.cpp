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

bool Camera::is_locked() const {
    return state_.read8(ram::ScrollLock) != 0;
}

void Camera::set_world_x(std::uint16_t world_x) {
    // Width is assumed 256 — vanilla SMB invariant. Right edge tracks
    // left + 256, with the high byte rolling on overflow.
    const std::uint8_t left_page = static_cast<std::uint8_t>(world_x >> 8);
    const std::uint8_t left_x    = static_cast<std::uint8_t>(world_x & 0xFF);
    const std::uint16_t right_world = static_cast<std::uint16_t>(world_x + 0x100);
    const std::uint8_t right_page = static_cast<std::uint8_t>(right_world >> 8);
    const std::uint8_t right_x    = static_cast<std::uint8_t>(right_world & 0xFF);
    state_.write8(ram::ScreenLeft_PageLoc,  left_page);
    state_.write8(ram::ScreenLeft_X_Pos,    left_x);
    state_.write8(ram::ScreenRight_PageLoc, right_page);
    state_.write8(ram::ScreenRight_X_Pos,   right_x);
}

void Camera::lock() {
    locked_ = true;
    state_.write8(ram::ScrollLock, 0x01);
}

void Camera::unlock() {
    locked_ = false;
    state_.write8(ram::ScrollLock, 0x00);
}

void Camera::apply_freezes() {
    if (locked_) state_.write8(ram::ScrollLock, 0x01);
}

}  // namespace smb::semcomp
