// semcomp/SemcompGame.h — top-level semantic facade.
//
// Owns a GameState and constructs Mario/Level/Camera/ModApi views over it.
// Phase 0: no init/shutdown/frame work is wired into the runner. The class
// is a compile-checked declaration of where the semantic layer will live.
#pragma once

#include "semcomp/Camera.h"
#include "semcomp/GameState.h"
#include "semcomp/Level.h"
#include "semcomp/Mario.h"
#include "semcomp/ModApi.h"

namespace smb::semcomp {

class SemcompGame {
public:
    SemcompGame()
        : state_(),
          mario_(state_),
          level_(state_),
          camera_(state_),
          mod_api_() {}

    // Phase 0 lifecycle stubs. Not yet invoked by the runner.
    void init()     {}
    void shutdown() {}

    // Phase 0: would delegate to the generated frame path. Currently a
    // no-op so that mistakenly wiring this in does not alter behavior.
    void update_frame() {}

    const GameState& state()  const { return state_;  }
    const Mario&     mario()  const { return mario_;  }
    const Level&     level()  const { return level_;  }
    const Camera&    camera() const { return camera_; }
    ModApi&          mod_api()      { return mod_api_; }

private:
    GameState state_;
    Mario     mario_;
    Level     level_;
    Camera    camera_;
    ModApi    mod_api_;
};

}  // namespace smb::semcomp
