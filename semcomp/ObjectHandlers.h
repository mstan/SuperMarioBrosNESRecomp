// semcomp/ObjectHandlers.h — Phase 18 ownership of object handlers.
//
//   $BC85 PowerUpObjHandler  — per-frame power-up entity dispatcher
//   $B689 FireballObjCore    — per-frame fireball update + collision
//   $BB38 CoinBlock          — coin metatile bookkeeping after a bump
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class ObjectHandlers {
public:
    explicit ObjectHandlers(GameState& state) : state_(state) {}

    void powerup_obj_handler();  // $BC85
    void fireball_obj_core();    // $B689
    void coin_block();           // $BB38

private:
    GameState& state_;
};

}  // namespace smb::semcomp
