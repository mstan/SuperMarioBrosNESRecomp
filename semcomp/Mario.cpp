// semcomp/Mario.cpp — Mario player facade. Reads only (Phase 1).
#include "semcomp/Mario.h"
#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"

namespace smb::semcomp {

namespace {
// Sign-extend an 8-bit RAM byte read as the integer part of a signed
// 8.8 fixed-point velocity.
inline std::int8_t to_int8(std::uint8_t v) {
    return static_cast<std::int8_t>(v);
}
}  // namespace

std::uint8_t Mario::x()    const { return state_.read8(ram::Player_X_Position); }
std::uint8_t Mario::y()    const { return state_.read8(ram::Player_Y_Position); }
std::uint8_t Mario::page() const { return state_.read8(ram::Player_PageLoc);    }

std::uint16_t Mario::world_x() const {
    return state_.read_page_offset(ram::Player_PageLoc, ram::Player_X_Position);
}

std::int8_t Mario::x_velocity() const {
    return to_int8(state_.read8(ram::Player_X_Speed));
}
std::int8_t Mario::y_velocity() const {
    return to_int8(state_.read8(ram::Player_Y_Speed));
}
std::uint8_t Mario::x_speed_absolute() const {
    return state_.read8(ram::Player_XSpeedAbsolute);
}

PowerStatus Mario::power() const {
    return static_cast<PowerStatus>(state_.read8(ram::PlayerStatus));
}

std::uint8_t Mario::size_byte() const {
    return state_.read8(ram::PlayerSize);
}

std::uint8_t Mario::physics_state_raw() const {
    return state_.read8(ram::Player_State);
}

Direction Mario::facing() const {
    return static_cast<Direction>(state_.read8(ram::PlayerFacingDir));
}

Direction Mario::moving() const {
    return static_cast<Direction>(state_.read8(ram::Player_MovingDir));
}

std::uint8_t Mario::spr_data_offset() const {
    return state_.read8(ram::Player_SprDataOffset);
}

// ---- Writes (Phase 2) -------------------------------------------------------

void Mario::set_x(std::uint8_t v) {
    state_.write8(ram::Player_X_Position, v);
}
void Mario::set_y(std::uint8_t v) {
    state_.write8(ram::Player_Y_Position, v);
}
void Mario::set_page(std::uint8_t v) {
    state_.write8(ram::Player_PageLoc, v);
}
void Mario::set_power(PowerStatus v) {
    // Power-up is two coupled bytes in SMB: PlayerStatus (which power
    // tier) and PlayerSize (the sprite/collision size used by the
    // render and physics routines). Setting Status alone produces
    // inconsistent state — e.g. "Fire" power but visually Small
    // because the sprite routine reads Size, not Status. The fireball
    // throw animation briefly reads Status, hence the one-frame
    // big-Mario flicker before reverting on the next sprite update.
    //
    // Size encoding: 0 = tall (Big or Fire Mario), 1 = short (Small).
    state_.write8(ram::PlayerStatus, static_cast<std::uint8_t>(v));
    state_.write8(ram::PlayerSize,
                  (v == PowerStatus::Small) ? std::uint8_t{1} : std::uint8_t{0});
}
void Mario::set_physics_state_raw(std::uint8_t v) {
    state_.write8(ram::Player_State, v);
}
void Mario::set_facing(Direction v) {
    state_.write8(ram::PlayerFacingDir, static_cast<std::uint8_t>(v));
}

}  // namespace smb::semcomp
