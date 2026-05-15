// semcomp/SemcompGame.h — top-level semantic facade.
//
// Owns a GameState and constructs Mario/Level/Camera/PlayerSession/ModApi
// views over it. Phase 1: read-only views are available; nothing here is
// invoked from the runner's frame path yet.
#pragma once

#include "semcomp/Camera.h"
#include "semcomp/GameState.h"
#include "semcomp/Level.h"
#include "semcomp/Mario.h"
#include "semcomp/ModApi.h"
#include "semcomp/PlayerSession.h"

namespace smb::semcomp {

class SemcompGame {
public:
    SemcompGame()
        : state_(),
          mario_(state_),
          level_(state_),
          camera_(state_),
          session_(state_),
          mod_api_() {}

    void init()     {}
    void shutdown() {}
    void update_frame() {}

    const GameState&     state()   const { return state_;   }
    const Mario&         mario()   const { return mario_;   }
    const Level&         level()   const { return level_;   }
    const Camera&        camera()  const { return camera_;  }
    const PlayerSession& session() const { return session_; }
    ModApi&              mod_api()       { return mod_api_; }

private:
    GameState     state_;
    Mario         mario_;
    Level         level_;
    Camera        camera_;
    PlayerSession session_;
    ModApi        mod_api_;
};

}  // namespace smb::semcomp
