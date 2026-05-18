// semcomp/DamageChain.h — Phase 22 ownership of damage/death routines.
//
//   $D92C InjurePlayer  — start of damage chain (gate on $079E).
//   $D931 ForceInjury   — body that demotes Mario by one power tier or
//                          falls into KillPlayer if PlayerStatus=0.
//   $D958 KillPlayer    — death-state setup + enemy-stomp pts dispatch.
//
// $D92C and $D931 are separately-emitted with overlapping bodies; the
// recompiler emits each as a full function whose body starts at the
// respective entry point and runs to the same exit. We model this with
// a shared private helper, the same way the recompiler's multi-entry-
// body pattern works.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

class DamageChain {
public:
    explicit DamageChain(GameState& state) : state_(state) {}

    void injure_player();   // $D92C
    void force_injury();    // $D931

private:
    GameState& state_;
};

}  // namespace smb::semcomp
