// semcomp/GameMode.h — facade over SMB's game-state dispatcher.
//
// Owns the canonical OperMode / PauseStatus / PlayerCtrlRoutine
// concepts as typed reads + verbs. The pause routine ($8182) is
// architecturally replaced via [[replace_func]] — when the user
// presses Start in-game, the natural caller flow lands in
// GameMode::on_pause_tick().
//
// "End level" and "warp to world,level" are trainer-only verbs: no
// natural in-game caller would invoke them from arbitrary state, so
// they get exposed as buttons rather than replacements.
#pragma once

#include <cstdint>

namespace smb::semcomp {

class GameState;

// Canonical OperMode values. Sub-state lives in $0772 (OperMode_Task)
// and is mode-dependent.
enum class OperModeValue : std::uint8_t {
    TitleOrDemo = 0,
    OnePlayerInit = 1,
    Gameplay = 2,
    GameOver = 3,
};

// PlayerCtrlRoutine selector ($000E). The natural game cycles
// through these per frame in Player_Hndl. Trainer end-level writes
// PlayerEndLevel here to force the end-of-level sequence.
enum class PlayerCtrlMode : std::uint8_t {
    PlayerEntrance   = 0,
    NormalCtrl       = 1,
    // 2..A: various intermediate states (slide, blink, fire-flower
    // anim, death, etc.) — see smbdis canonical reference.
    PlayerEndLevel   = 11,  // $0B — FlagpoleSlide / castle-walk path
};

class GameMode {
public:
    explicit GameMode(GameState& state) : state_(state) {}

    // ---- Reads ---------------------------------------------------------
    OperModeValue   oper_mode() const;
    std::uint8_t    oper_mode_raw() const;
    std::uint8_t    oper_mode_task() const;
    std::uint8_t    player_ctrl_routine_raw() const;
    PlayerCtrlMode  player_ctrl_routine() const;
    bool            is_paused() const;       // $0776 bit 0
    std::uint8_t    pause_status_raw() const;
    std::uint8_t    pause_timer() const;     // $0777 countdown

    // ---- Verbs ---------------------------------------------------------
    // Force the pause state on/off. Bypasses the debounce window —
    // matches what the natural code would do mid-press but skips the
    // controller-button check. The pause-forbidden bit is set so the
    // next natural Start-press doesn't immediately toggle again.
    void set_paused(bool paused);

    // End the level immediately. Sets $0E = $0B (PlayerEndLevel)
    // which causes the natural per-frame Player_Hndl dispatcher to
    // run the end-of-level walk-into-castle sequence. The music
    // queue gets the level-complete jingle written too.
    void end_level();

    // Jump to world,level. Writes $075F (world) + $0760 (level) +
    // their dup copies at $0766/$0767. The transition fires on the
    // next level-load (e.g. after a pipe entry or death). For an
    // instant transition we also write to AreaPointer state — best
    // effort.
    void warp_to(std::uint8_t world, std::uint8_t level);

    // ---- replace_func body for $8182 PauseRoutine -----------------------
    // Called every frame by the natural caller chain. Mirrors the
    // 6502 logic: gate on OperMode/Task, decrement pause timer if
    // active, otherwise read newly-pressed Start, toggle pause + set
    // debounce + reload timer.
    void on_pause_tick();

    // ---- Phase 23 — Game-mode dispatchers -------------------------------
    // These three are small inline-dispatch routines: LDA $0772 OperMode_Task,
    // then 4-way (3-way for GameOver) dispatch into the natural sub-handlers.
    // All sub-handlers (InitializeArea, ScreenRoutines, PrimaryGameSetup,
    // GameCoreRoutine, SetupGameOver, etc.) remain natural-generated and
    // are reached via call_by_address.
    //
    // $8231 TitleScreenMode  — OperMode 0 (title + demo)
    // $AEDC GameMode         — OperMode 2 (gameplay)
    // $9218 GameOverMode     — OperMode 3
    //
    // $8212 OperModeExecutionTree NOT owned (multi-entry-body tangle with $8222).
    void title_screen_mode();
    void game_mode_tick();
    void game_over_mode();

private:
    GameState& state_;
};

}  // namespace smb::semcomp
