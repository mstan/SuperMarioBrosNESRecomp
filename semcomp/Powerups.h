// semcomp/Powerups.h — facade over the power-up entity setup ($BC49).
//
// Routine ownership via [[replace_func]]. The natural in-game caller
// is MushFlowerBlock at $BDD2 (when Mario bumps a power-up brick): it
// writes $0039 = 0 (mushroom slot) and JMPs into SetupPowerUp. Our
// replacement handles the slot-position copy + Mario-status-driven
// type translation (mushroom upgrades to fire flower if Mario is
// already Big/Fire — the natural SMB rule).
//
// Test surface: bump a power-up brick in 1-1. The mushroom should
// emerge and bounce naturally. Power-up grab SFX ($00FE bit 1) plays.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class Powerups {
public:
    explicit Powerups(GameState& state) : state_(state) {}

    // setup: replacement body for $BC49 SetupPowerUp. Caller has set:
    //   X = slot index (the brick-bump path uses slot 5 conventionally)
    //   $0039 = base power-up type (0=mushroom, 1=fire, 2=star, 3=1up)
    //   $76+X / $8F+X / $D7+X = spawn position bytes
    //
    // We reproduce the 6502 flow:
    //   1. $1B = $2E (some constant)
    //   2. Copy slot's $76+X to $73, $8F+X to $8C, set $BB = 1,
    //      $D4 = $D7+X - 8 (spawn position scratch).
    //   3. PwrUpJmp body: $23 = 1, $14 = 1, $049F = 3 (mark active).
    //   4. Type-translate: if base type < 2, replace with min(2,
    //      Mario's PlayerStatus / 2) — i.e. Small Mario gets a
    //      mushroom, Big or Fire Mario gets a fire flower.
    //   5. $03CA = $20 (sprite attribute), $00FE = $02 (queue
    //      power-up-grab SFX bit).
    void setup();

private:
    GameState& state_;
};

}  // namespace smb::semcomp
