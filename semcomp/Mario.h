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
    // Phase 2: ctor takes a mutable GameState reference so set_* can call
    // write8. Read-only callers are unaffected.
    explicit Mario(GameState& state) : state_(state) {}

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

    // ---- Writes (Phase 2) ------------------------------------------------
    // Direct writes through the canonical RAM byte. Writes are stomped on
    // the next game-logic frame unless apply_freezes() is re-asserting
    // them post-NMI.  These setters carry the "what bytes does the
    // semantic concept actually own" knowledge — for example
    // set_power couples PlayerStatus + PlayerSize + PlayerChangeSizeFlag
    // because all three contribute to "Mario is Fire".
    void set_x(std::uint8_t v);
    void set_y(std::uint8_t v);
    void set_page(std::uint8_t v);
    void set_power(PowerStatus v);
    void set_physics_state_raw(std::uint8_t v);
    void set_facing(Direction v);

    // ---- Phase 3 verbs ---------------------------------------------------
    // give_power_up: Small → Big → Fire. Caps at Fire. No-op already-Fire.
    //                Mirrors the natural mushroom/fire-flower pickup path:
    //                writes the new $0756 tier, refreshes player palette
    //                when promoting to Fire (GetPlayerColors @ $85F1), and
    //                drives the player-routine selector ($0747/$0775/$0E/
    //                $1D) so the game's per-frame PlayerCtrlRoutine plays
    //                the multi-frame grow / fire-flower-flash animation.
    //                Returns true iff a tier transition actually happened.
    // take_damage:   Like getting hit by a Goomba: triggers the game's
    //                InjurePlayer routine ($D92C). For Fire/Big Mario this
    //                shrinks to Small with the invuln blink animation; for
    //                Small Mario it kicks off the death animation flow.
    //                Returns true iff the routine was actually invoked
    //                (currently always true — InjurePlayer self-gates on
    //                $079E invuln, which we pre-clear).
    bool give_power_up();
    bool take_damage();

    // ---- Semantic freezes (Phase 2.5) ------------------------------------
    // freeze_* records the desired value AND immediately asserts it.
    // apply_freezes() — called once per frame post-NMI — re-asserts every
    // active freeze via the corresponding set_* method, so coupled-byte
    // logic re-runs every frame.  The trainer GUI is "dumb": it just
    // calls freeze_power(Fire); Mario decides what bytes that means.
    void freeze_power(PowerStatus v);
    void thaw_power();
    bool is_power_frozen() const { return frozen_power_active_; }
    PowerStatus frozen_power_value() const { return frozen_power_; }

    // apply_freezes is called every frame by SemcompGame::apply_post_nmi.
    void apply_freezes();

private:
    GameState& state_;
    // Per-field optional-style frozen values. Using bool + value rather
    // than std::optional to keep the ABI flat and the header dependency
    // light.
    bool        frozen_power_active_ = false;
    PowerStatus frozen_power_        = PowerStatus::Small;
};

}  // namespace smb::semcomp
