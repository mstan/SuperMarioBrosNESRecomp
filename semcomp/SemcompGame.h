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
#include "semcomp/Trainer.h"
#include "semcomp/TrainerUI.h"

namespace smb::semcomp {

class SemcompGame {
public:
    SemcompGame()
        : state_(),
          mario_(state_),
          level_(state_),
          camera_(state_),
          session_(state_),
          trainer_(state_),
          trainer_ui_(*this),
          mod_api_() {}

    void init()     {}
    void shutdown() {}
    void update_frame() {}

    // ---- Const accessors (read paths) ------------------------------------
    const GameState&     state()   const { return state_;   }
    const Level&         level()   const { return level_;   }
    const Camera&        camera()  const { return camera_;  }
    const PlayerSession& session() const { return session_; }

    // ---- Mutable Mario / Trainer accessors (Phase 2 write paths) --------
    // Both read- and write-side validation needs a mutable Mario; const
    // overload provided for read-only callers.
    Mario&         mario()       { return mario_; }
    const Mario&   mario() const { return mario_; }
    Trainer&       trainer()       { return trainer_; }
    const Trainer& trainer() const { return trainer_; }

    TrainerUI&       trainer_ui()       { return trainer_ui_; }
    const TrainerUI& trainer_ui() const { return trainer_ui_; }

    ModApi&        mod_api()       { return mod_api_; }

private:
    GameState     state_;
    Mario         mario_;
    Level         level_;
    Camera        camera_;
    PlayerSession session_;
    Trainer       trainer_;
    TrainerUI     trainer_ui_;
    ModApi        mod_api_;
};

}  // namespace smb::semcomp
