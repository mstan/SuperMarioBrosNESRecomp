// semcomp/SemcompGame.h — top-level semantic facade.
//
// Owns a GameState and constructs Mario/Level/Camera/PlayerSession/ModApi
// views over it. Phase 1: read-only views are available; nothing here is
// invoked from the runner's frame path yet.
#pragma once

#include "semcomp/Blocks.h"
#include "semcomp/Camera.h"
#include "semcomp/Enemies.h"
#include "semcomp/FloateyNumbers.h"
#include "semcomp/GameMode.h"
#include "semcomp/GameState.h"
#include "semcomp/Hud.h"
#include "semcomp/Level.h"
#include "semcomp/Mario.h"
#include "semcomp/ModApi.h"
#include "semcomp/PlayerAnim.h"
#include "semcomp/PlayerCollision.h"
#include "semcomp/PlayerGraphics.h"
#include "semcomp/ObjectHandlers.h"
#include "semcomp/DamageChain.h"
#include "semcomp/EnemyHandlers.h"
#include "semcomp/EnemyHandlers2.h"
#include "semcomp/LevelParser.h"
#include "semcomp/BgRenderer.h"
#include "semcomp/SoundEngine.h"
#include "semcomp/AudioEngine.h"
#include "semcomp/EnemyEngine.h"
#include "semcomp/LevelEngine.h"
#include "semcomp/RenderEngine.h"
#include "semcomp/FinalBodies.h"
#include "semcomp/MiscUtilities.h"
#include "semcomp/PlayerPhysics.h"
#include "semcomp/PlayerSession.h"
#include "semcomp/Powerups.h"
#include "semcomp/RoutineRegistry.h"
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
          enemies_(state_),
          blocks_(state_),
          powerups_(state_),
          mode_(state_),
          hud_(state_),
          floateys_(state_),
          player_physics_(state_),
          player_anim_(state_),
          player_collision_(state_),
          player_graphics_(state_),
          object_handlers_(state_),
          damage_chain_(state_),
          enemy_handlers_(state_),
          enemy_handlers2_(state_),
          level_parser_(state_),
          bg_renderer_(state_),
          sound_engine_(state_),
          audio_engine_(state_),
          enemy_engine_(state_),
          level_engine_(state_),
          render_engine_(state_),
          final_bodies_(state_),
          misc_utilities_(state_),
          trainer_(state_),
          trainer_ui_(*this),
          mod_api_(),
          routines_() {}

    void init()     {}
    void shutdown() {}
    void update_frame() {}

    // Called every frame post-NMI by extras.c (via Runtime bridge).
    // Runs:
    //   1. Trainer raw-byte freezes (addr-keyed; unchanged from Phase 2)
    //   2. Mario semantic freezes (re-assert frozen Power, etc., which
    //      re-runs Mario::set_power and thereby re-couples Size +
    //      ChangeSizeFlag every frame)
    //   3. PlayerSession semantic freezes (clamped lives/coins)
    // The order matters: semantic runs AFTER raw so that a slot frozen
    // both ways uses the semantic value.
    void apply_post_nmi() {
        trainer_.apply();
        mario_.apply_freezes();
        session_.apply_freezes();
        camera_.apply_freezes();
    }

    // ---- Const accessors (read paths) ------------------------------------
    const GameState&     state()   const { return state_;   }
    const Level&         level()   const { return level_;   }
    Camera&              camera()        { return camera_;  }
    const Camera&        camera()  const { return camera_;  }

    // ---- Mutable Mario / PlayerSession / Trainer accessors --------------
    // Phase 2: PlayerSession gained write methods; needs mutable form.
    Mario&               mario()         { return mario_;   }
    const Mario&         mario()   const { return mario_;   }
    PlayerSession&       session()       { return session_; }
    const PlayerSession& session() const { return session_; }
    Enemies&             enemies()       { return enemies_; }
    const Enemies&       enemies() const { return enemies_; }
    Blocks&              blocks()        { return blocks_;   }
    Powerups&            powerups()      { return powerups_; }
    GameMode&            mode()          { return mode_;     }
    const GameMode&      mode()    const { return mode_;     }
    Hud&                 hud()           { return hud_;      }
    FloateyNumbers&      floateys()      { return floateys_; }
    PlayerPhysics&       player_physics(){ return player_physics_; }
    PlayerAnim&          player_anim()   { return player_anim_;    }
    PlayerCollision&     player_collision() { return player_collision_; }
    PlayerGraphics&      player_graphics() { return player_graphics_; }
    ObjectHandlers&      object_handlers() { return object_handlers_; }
    DamageChain&         damage_chain()    { return damage_chain_; }
    EnemyHandlers&       enemy_handlers()  { return enemy_handlers_; }
    EnemyHandlers2&      enemy_handlers2() { return enemy_handlers2_; }
    LevelParser&         level_parser()    { return level_parser_; }
    BgRenderer&          bg_renderer()     { return bg_renderer_; }
    SoundEngine&         sound_engine()    { return sound_engine_; }
    AudioEngine&         audio_engine()    { return audio_engine_; }
    EnemyEngine&         enemy_engine()    { return enemy_engine_; }
    LevelEngine&         level_engine()    { return level_engine_; }
    RenderEngine&        render_engine()   { return render_engine_; }
    FinalBodies&         final_bodies()    { return final_bodies_; }
    MiscUtilities&       misc_utilities()  { return misc_utilities_; }
    Trainer&             trainer()       { return trainer_; }
    const Trainer&       trainer() const { return trainer_; }

    TrainerUI&       trainer_ui()       { return trainer_ui_; }
    const TrainerUI& trainer_ui() const { return trainer_ui_; }

    ModApi&        mod_api()       { return mod_api_; }

    RoutineRegistry&       routines()       { return routines_; }
    const RoutineRegistry& routines() const { return routines_; }

private:
    GameState        state_;
    Mario            mario_;
    Level            level_;
    Camera           camera_;
    PlayerSession    session_;
    Enemies          enemies_;
    Blocks           blocks_;
    Powerups         powerups_;
    GameMode         mode_;
    Hud              hud_;
    FloateyNumbers   floateys_;
    PlayerPhysics    player_physics_;
    PlayerAnim       player_anim_;
    PlayerCollision  player_collision_;
    PlayerGraphics   player_graphics_;
    ObjectHandlers   object_handlers_;
    DamageChain      damage_chain_;
    EnemyHandlers    enemy_handlers_;
    EnemyHandlers2   enemy_handlers2_;
    LevelParser      level_parser_;
    BgRenderer       bg_renderer_;
    SoundEngine      sound_engine_;
    AudioEngine      audio_engine_;
    EnemyEngine      enemy_engine_;
    LevelEngine      level_engine_;
    RenderEngine     render_engine_;
    FinalBodies      final_bodies_;
    MiscUtilities    misc_utilities_;
    Trainer          trainer_;
    TrainerUI        trainer_ui_;
    ModApi           mod_api_;
    RoutineRegistry  routines_;
};

}  // namespace smb::semcomp
