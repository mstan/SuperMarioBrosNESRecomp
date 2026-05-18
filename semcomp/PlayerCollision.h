// semcomp/PlayerCollision.h — player-vs-background collision ownership.
//
// Phase 16 ports:
//   $DC64 PlayerBGCollision    — main entry point
//   (Future) $E325 PlayerCollisionCore, $BCED PlayerHeadCollision
//
// PlayerBGCollision is the per-frame check that drives jumping/landing
// transitions, coin pickup, pipe entry, side-collision stop, and head
// bumps. It tail-calls many natural-generated helpers — $E3E9 GetMTileAttrib,
// $DFA1 / $DF8F / $DF9A metatile pattern matchers, $DEBD / $DEDD pattern
// gates, $DEC4 / $DEE8 landing helpers, plus standalone inner-label
// targets ($DCF6 DoFootCheck, $DD1A AwardTouchedCoin, $DDFF StopPlayerMove,
// $DE05 HandleCoinMetatile, $DE0E HandleClimbMTile, $DE2E ChkPipeEnter,
// $DF4B InitChkPMove). All of those stay natural-generated.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class PlayerCollision {
public:
    explicit PlayerCollision(GameState& state) : state_(state) {}

    // $DC64 PlayerBGCollision. Reads $0716 PlayerCollisionRoutine selector,
    // gates on the $0E PlayerCtrlRoutine state, picks a metatile-check
    // bounding-box based on PlayerSize + CrouchingFlag + SwimmingFlag,
    // calls into $E3AD bbox tables, then runs head/foot/side checks
    // via natural-generated metatile readers.
    void player_bg_collision();

private:
    GameState& state_;
};

}  // namespace smb::semcomp
