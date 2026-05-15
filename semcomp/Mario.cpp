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
    // "Mario's power" is a semantic concept that maps to multiple
    // RAM bytes in SMB.  All bytes that contribute to the concept
    // belong here; the trainer / mod API / GUI shouldn't have to know
    // about any of them.
    //
    //  $0756 PlayerStatus         — the tier itself (Small/Big/Fire)
    //  $0754 PlayerSize           — sprite/collision size; 0=tall, 1=short.
    //                               Without this Mario reads as Fire (so
    //                               throws fireballs) but renders Small.
    //  $070B PlayerChangeSizeFlag — set by damage routine to trigger the
    //                               shrink animation. Cleared here so any
    //                               in-progress damage transition is
    //                               cancelled (the freeze path re-clears
    //                               it every frame, which is why frozen
    //                               Fire-Mario stops visually shrinking
    //                               on damage).
    state_.write8(ram::PlayerStatus, static_cast<std::uint8_t>(v));
    state_.write8(ram::PlayerSize,
                  (v == PowerStatus::Small) ? std::uint8_t{1} : std::uint8_t{0});
    state_.write8(ram::PlayerChangeSizeFlag, 0);
}
void Mario::set_physics_state_raw(std::uint8_t v) {
    state_.write8(ram::Player_State, v);
}
void Mario::set_facing(Direction v) {
    state_.write8(ram::PlayerFacingDir, static_cast<std::uint8_t>(v));
}

// ---- Semantic freezes -------------------------------------------------------

void Mario::freeze_power(PowerStatus v) {
    frozen_power_active_ = true;
    frozen_power_        = v;
    set_power(v);  // immediate
}

void Mario::thaw_power() {
    frozen_power_active_ = false;
}

void Mario::apply_freezes() {
    if (frozen_power_active_) set_power(frozen_power_);
}

}  // namespace smb::semcomp
