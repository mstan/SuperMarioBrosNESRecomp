// semcomp/Mario.h — semantic facade over the player avatar.
//
// Phase 1: reads only. Every accessor delegates to verified RAM addresses
// in SmbRamMap.h. Writes and physics-driving logic are Phase 2+ work.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

// Powerup status. Verified values: Small, Big. Fire is smbdis-canonical
// but unobserved in the verifying trace (demo never picks up a fire
// flower).
enum class PowerStatus : std::uint8_t {
    Small = 0,
    Big   = 1,
    Fire  = 2,
};

// Facing / movement direction encoding.
enum class Direction : std::uint8_t {
    None  = 0,
    Right = 1,
    Left  = 2,
};

class Mario {
public:
    explicit Mario(const GameState& state) : state_(state) {}

    // ---- Position --------------------------------------------------------
    std::uint8_t  x() const;
    std::uint8_t  y() const;
    std::uint8_t  page() const;
    std::uint16_t world_x() const;  // (page << 8) | x

    // ---- Velocity (signed 8-bit integer part of 8.8 fixed-point) ---------
    std::int8_t  x_velocity() const;
    std::int8_t  y_velocity() const;
    // Unsigned magnitude. Walking caps around 24, running caps at 40.
    std::uint8_t x_speed_absolute() const;

    // ---- Power / size ----------------------------------------------------
    PowerStatus  power() const;
    // 0 = tall (Big/Fire Mario), 1 = short (Small Mario). Tracked
    // independently of power() because SMB updates the two bytes on
    // different frames during powerup/damage transitions.
    std::uint8_t size_byte() const;

    // ---- Physics state ---------------------------------------------------
    // Raw $001D byte. Known: 0 = on ground; nonzero = airborne (the
    // 1-vs-2 distinction is observed but not yet semantically named —
    // see SmbRamMap.h TODO(phase1.5)).
    std::uint8_t physics_state_raw() const;
    bool         on_ground() const { return physics_state_raw() == 0; }

    // ---- Facing / movement ----------------------------------------------
    Direction facing() const;
    Direction moving() const;

    // ---- OAM ------------------------------------------------------------
    std::uint8_t spr_data_offset() const;

private:
    const GameState& state_;
};

}  // namespace smb::semcomp
