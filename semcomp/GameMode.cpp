// semcomp/GameMode.cpp — game-state facade.
#include "semcomp/GameMode.h"

#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

// ---- Reads ----------------------------------------------------------------

std::uint8_t GameMode::oper_mode_raw() const {
    return state_.read8(ram::OperMode);
}
OperModeValue GameMode::oper_mode() const {
    return static_cast<OperModeValue>(oper_mode_raw());
}
std::uint8_t GameMode::oper_mode_task() const {
    return state_.read8(ram::OperMode_Task);
}
std::uint8_t GameMode::player_ctrl_routine_raw() const {
    return state_.read8(ram::PlayerCtrlRoutine_Sel);
}
PlayerCtrlMode GameMode::player_ctrl_routine() const {
    return static_cast<PlayerCtrlMode>(player_ctrl_routine_raw());
}
bool GameMode::is_paused() const {
    return (state_.read8(ram::GamePauseStatus) & 0x01) != 0;
}
std::uint8_t GameMode::pause_status_raw() const {
    return state_.read8(ram::GamePauseStatus);
}
std::uint8_t GameMode::pause_timer() const {
    return state_.read8(ram::PauseTimer);
}

// ---- Verbs ----------------------------------------------------------------

void GameMode::set_paused(bool paused) {
    // Write the pause bit explicitly (don't toggle — caller-driven).
    // Set the debounce bit so the next natural Start-press doesn't
    // immediately flip us back. Reload the pause timer to its natural
    // pause-press value so the existing on_pause_tick countdown
    // doesn't fire on the very next frame.
    std::uint8_t v = state_.read8(ram::GamePauseStatus);
    v = (v & ~std::uint8_t{0x01}) | (paused ? 0x01 : 0x00);
    v |= 0x80;  // debounce
    state_.write8(ram::GamePauseStatus, v);
    state_.write8(ram::PauseTimer, 0x2B);
}

void GameMode::end_level() {
    // Trigger the level-complete state via PlayerCtrlRoutine.
    // PlayerEndLevel ($0B) runs the walk-into-castle + score-tally
    // sequence. Also queue the level-complete fanfare ($00FC = $20).
    state_.write8(ram::PlayerCtrlRoutine_Sel,
                  static_cast<std::uint8_t>(PlayerCtrlMode::PlayerEndLevel));
    state_.write8(ram::AreaMusicQueue, 0x20);
}

void GameMode::warp_to(std::uint8_t world, std::uint8_t level) {
    // Clamp inputs (worlds 0..7 = "1" through "8", levels 0..3 = "1"
    // through "4"). The world/level bytes here are 0-indexed; HUD
    // adds 1 at render time.
    if (world > 7) world = 7;
    if (level > 3) level = 3;
    state_.write8(ram::WorldNumber, world);
    state_.write8(ram::LevelNumber, level);
    // GoContinue at $830E also writes these dup copies. The dup is
    // what the level-loader reads on the next transition.
    state_.write8(0x0766, world);
    state_.write8(0x0767, level);
}

// ---- replace_func body ----------------------------------------------------

void GameMode::on_pause_tick() {
    // Mirror of $8182 PauseRoutine logic. Read-from-RAM matches the
    // natural code so the trainer doesn't desync from in-game state.

    // $8182-$8192: gate on OperMode. Allow if OperMode == 2 (gameplay)
    // or (OperMode == 1 AND OperMode_Task == 3). Else exit.
    const std::uint8_t mode = state_.read8(ram::OperMode);
    if (mode != 2) {
        if (mode != 1) return;
        if (state_.read8(ram::OperMode_Task) != 3) return;
    }

    // $8194-$819C: decrement PauseTimer if non-zero; on hit-zero this
    // frame, continue to ChkStart (don't decrement past 0).
    {
        const std::uint8_t t = state_.read8(ram::PauseTimer);
        if (t != 0) {
            state_.write8(ram::PauseTimer, static_cast<std::uint8_t>(t - 1));
            return;
        }
    }

    // $819D-$81A2 ChkStart: check Start bit in $06FC. If not pressed
    // newly, goto ClrPauseTimer (clear debounce bit).
    const std::uint8_t pressed = state_.read8(ram::Controller1_NewlyPressed);
    std::uint8_t pause_status = state_.read8(ram::GamePauseStatus);

    if ((pressed & ram::ControllerBtn_Start) == 0) {
        // ClrPauseTimer ($81BD): clear the debounce bit so a future
        // Start press will toggle pause.
        pause_status &= 0x7F;
        state_.write8(ram::GamePauseStatus, pause_status);
        return;
    }

    // $81A4-$81A9: if debounce bit set, exit silently.
    if ((pause_status & 0x80) != 0) return;

    // $81AB-$81BB: pause-press accepted. Reload timer to $2B (~43
    // frames), toggle bit 0, set debounce bit.
    state_.write8(ram::PauseTimer, 0x2B);
    pause_status ^= 0x01;
    pause_status |= 0x80;
    state_.write8(ram::GamePauseStatus, pause_status);
}

// ---- Phase 23 — Game-mode dispatchers --------------------------------------
//
// Each routine is a 5-line body: LDA $0772 OperMode_Task, then dispatch via
// the $8E04 inline-dispatch table into a small set of sub-handlers. All
// sub-handlers remain natural-generated (their bodies live in the recompiler
// output) and are reached via call_by_address.
//
// $8231 TitleScreenMode  — 4-way dispatch on OperMode_Task
// $AEDC GameMode         — 4-way dispatch (case 3 = GameCoreRoutine $AEEA)
// $9218 GameOverMode     — 3-way dispatch
//
// Each case in the original 6502 returns immediately (the inline_dispatch
// pops the return address itself), so the natural code never falls through
// past the switch. Our port returns from each case too.

void GameMode::title_screen_mode() {
    const std::uint8_t task = state_.read8(ram::OperMode_Task);
    g_cpu.A = task;
    switch (task) {
        case 0: call_by_address(0x8FCF); return;  // InitializeArea
        case 1: call_by_address(0x8567); return;  // ScreenRoutines
        case 2: call_by_address(0x9061); return;  // PrimaryGameSetup (title variant)
        case 3: call_by_address(0x8245); return;  // GameMenuRoutine
        default: return;
    }
}

void GameMode::game_mode_tick() {
    const std::uint8_t task = state_.read8(ram::OperMode_Task);
    g_cpu.A = task;
    switch (task) {
        case 0: call_by_address(0x8FE4); return;  // InitializeArea (gameplay variant)
        case 1: call_by_address(0x8567); return;  // ScreenRoutines
        case 2: call_by_address(0x9071); return;  // PrimaryGameSetup (gameplay)
        case 3: call_by_address(0xAEEA); return;  // GameCoreRoutine
        default: return;
    }
}

void GameMode::game_over_mode() {
    const std::uint8_t task = state_.read8(ram::OperMode_Task);
    g_cpu.A = task;
    switch (task) {
        case 0: call_by_address(0x9224); return;  // SetupGameOver
        case 1: call_by_address(0x8567); return;  // ScreenRoutines
        case 2: call_by_address(0x9237); return;  // RunGameOver
        default: return;
    }
}

}  // namespace smb::semcomp
