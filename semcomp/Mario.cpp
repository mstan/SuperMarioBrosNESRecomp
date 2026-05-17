// semcomp/Mario.cpp — Mario player facade. Reads only (Phase 1).
#include "semcomp/Mario.h"
#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"
#include "semcomp/SmbRoutines.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

// ---- Player-routine selector + animation bytes -----------------------------
// $0747 is the per-frame "PlayerCtrlRoutine" tick counter. The natural
// HandlePowerUpCollision / InjurePlayer paths terminate with the
// SetPRout fragment at $D948..$D952 which writes:
//   $000E = anim_length   (e.g. $09 for grow, $0C for fire flash, $0A for
//                          injury blink)
//   $001D = 0             (Player_State = on ground)
//   $0747 = $FF           (animation tick starts at $FF, ticks toward $C4)
//   $0775 = 0
// PlayerCtrlRoutine reads $0747 each frame and dispatches to
// PlayerChangeSize / PlayerInjuryBlink / PlayerFireFlower according to
// the value windows ($F8 → InitChangeSize, $C4 → DonePlayerTask, etc.).
// We don't decode that here — we just write the exact bytes the natural
// path writes and let the game run.
namespace {
constexpr std::uint16_t kRam_PlayerAnimTimer   = 0x000E;
constexpr std::uint16_t kRam_PlayerState       = 0x001D;
constexpr std::uint16_t kRam_GameEngineSubrPC  = 0x0747;
constexpr std::uint16_t kRam_PlayerStatusBar0775 = 0x0775;
constexpr std::uint16_t kRam_InjuryTimer       = 0x079E;
constexpr std::uint8_t  kAnim_GrowToBig        = 0x09;  // PlayerChangeSize
constexpr std::uint8_t  kAnim_FireFlowerFlash  = 0x0C;  // PlayerFireFlower
constexpr std::uint16_t kPC_GetPlayerColors    = 0x85F1;
constexpr std::uint16_t kPC_InjurePlayer       = 0xD92C;

void start_player_animation(GameState& s, std::uint8_t anim_length) {
    s.write8(kRam_PlayerAnimTimer,    anim_length);
    s.write8(kRam_PlayerState,        0x00);  // ground
    s.write8(kRam_GameEngineSubrPC,   0xFF);  // tick start
    s.write8(kRam_PlayerStatusBar0775, 0x00);
}
}  // namespace

namespace {
// Sign-extend an 8-bit RAM byte read as the integer part of a signed
// 8.8 fixed-point velocity.
inline std::int8_t to_int8(std::uint8_t v) {
    return static_cast<std::int8_t>(v);
}
}  // namespace

std::uint8_t Mario::x()    const { return state_.read8(ram::Player_X_Position); }
std::uint8_t Mario::y()    const { return state_.read8(ram::Player_Y_Position); }
std::uint8_t Mario::page() const { return state_.read8(ram::Player_PageLoc);    }

std::uint16_t Mario::world_x() const {
    return state_.read_page_offset(ram::Player_PageLoc, ram::Player_X_Position);
}

std::int8_t Mario::x_velocity() const {
    return to_int8(state_.read8(ram::Player_X_Speed));
}
std::int8_t Mario::y_velocity() const {
    return to_int8(state_.read8(ram::Player_Y_Speed));
}
std::uint8_t Mario::x_speed_absolute() const {
    return state_.read8(ram::Player_XSpeedAbsolute);
}

PowerStatus Mario::power() const {
    return static_cast<PowerStatus>(state_.read8(ram::PlayerStatus));
}

std::uint8_t Mario::size_byte() const {
    return state_.read8(ram::PlayerSize);
}

std::uint8_t Mario::physics_state_raw() const {
    return state_.read8(ram::Player_State);
}

Direction Mario::facing() const {
    return static_cast<Direction>(state_.read8(ram::PlayerFacingDir));
}

Direction Mario::moving() const {
    return static_cast<Direction>(state_.read8(ram::Player_MovingDir));
}

std::uint8_t Mario::spr_data_offset() const {
    return state_.read8(ram::Player_SprDataOffset);
}

// ---- Writes (Phase 2) -------------------------------------------------------

void Mario::set_x(std::uint8_t v) {
    state_.write8(ram::Player_X_Position, v);
}
void Mario::set_y(std::uint8_t v) {
    state_.write8(ram::Player_Y_Position, v);
}
void Mario::set_page(std::uint8_t v) {
    state_.write8(ram::Player_PageLoc, v);
}
void Mario::set_power(PowerStatus v) {
    // "Mario's power" is a semantic concept that maps to multiple
    // RAM bytes in SMB.  All bytes that contribute to the concept
    // belong here; the trainer / mod API / GUI shouldn't have to know
    // about any of them.
    //
    //  $0756 PlayerStatus         — the tier itself (Small/Big/Fire)
    //  $0754 PlayerSize           — sprite/collision size; 0=tall, 1=short.
    //                               Without this Mario reads as Fire (so
    //                               throws fireballs) but renders Small.
    //  $070B PlayerChangeSizeFlag — set by damage routine to trigger the
    //                               shrink animation. Cleared here so any
    //                               in-progress damage transition is
    //                               cancelled (the freeze path re-clears
    //                               it every frame, which is why frozen
    //                               Fire-Mario stops visually shrinking
    //                               on damage).
    state_.write8(ram::PlayerStatus, static_cast<std::uint8_t>(v));
    state_.write8(ram::PlayerSize,
                  (v == PowerStatus::Small) ? std::uint8_t{1} : std::uint8_t{0});
    state_.write8(ram::PlayerChangeSizeFlag, 0);
}
void Mario::set_physics_state_raw(std::uint8_t v) {
    state_.write8(ram::Player_State, v);
}
void Mario::set_facing(Direction v) {
    state_.write8(ram::PlayerFacingDir, static_cast<std::uint8_t>(v));
}

// ---- Phase 3 verbs ----------------------------------------------------------

bool Mario::give_power_up() {
    // Mirrors HandlePowerUpCollision's Shroom_Flower_PUp branch:
    //   Small → Big: write $0756=1, A=$09 → grow animation
    //   Big   → Fire: write $0756=2, JSR GetPlayerColors ($85F1), A=$0C
    //                 → fire-flower flash animation
    // Fire is the cap; no-op.
    //
    // The tier byte is committed immediately (matches the natural pickup)
    // and the animation is purely cosmetic, driven by the game's
    // per-frame PlayerCtrlRoutine reading $0747.
    const PowerStatus cur = power();
    if (cur == PowerStatus::Fire) return false;

    if (cur == PowerStatus::Small) {
        state_.write8(ram::PlayerStatus, static_cast<std::uint8_t>(PowerStatus::Big));
        start_player_animation(state_, kAnim_GrowToBig);
    } else {  // Big → Fire
        state_.write8(ram::PlayerStatus, static_cast<std::uint8_t>(PowerStatus::Fire));
        call_by_address(kPC_GetPlayerColors);  // install fire-mario palette
        start_player_animation(state_, kAnim_FireFlowerFlash);
    }
    // Tandem SFX: queue $00FE |= $20 (power-up grab bit) + JSR
    // PlayPowerUpGrab. This is what HandlePowerUpCollision does in the
    // natural pickup path ($D808 LDA #$20 / STA $FE). May still be
    // silent in TCP context — accepted tradeoff (see SmbRoutines.cpp
    // tandem note).
    play_power_up_grab();
    // PlayerSize and PlayerChangeSizeFlag are managed by the animation
    // itself (InitChangeSize toggles $0754; the size update lands on its
    // own frame mid-animation). Don't touch them here — let the game do
    // it the way the natural mushroom pickup does.
    return true;
}

bool Mario::take_damage() {
    // Hit by an enemy: trigger the real damage flow. InjurePlayer ($D92C)
    // self-gates on $079E (invuln timer); we clear it first so the call
    // always lands. Once in:
    //   - Reads $0756 (current tier).
    //   - If Small (0): falls through to KillPlayer ($D958) — sets up the
    //     death animation, plays death music, decrements lives, etc.
    //   - Else: writes 0 to $0756 (shrinks to Small), sets $079E=$08
    //     (invuln), JSRs GetPlayerColors, kicks off the injury blink
    //     animation via SetPRout (A=$0A, Y=$01).
    //
    // We push A=0 into CPU state so InjurePlayer's prelude
    //   $D92C LDA $079E   (loads the cleared invuln timer = 0 into A)
    //   $D92F BNE skip    (not taken because A==0)
    //   $D931 ForceInjury / $D936 STA $0756 (writes A=0 = Small)
    // works as intended even if some prior generated code left A
    // non-zero — call_by_address starts execution at $D92C but the LDA
    // overwrites A before STA, so A=0 staging is actually redundant. We
    // leave it as a belt-and-suspenders no-op.
    // Snapshot BEFORE InjurePlayer runs — used to decide which tandem
    // SFX backup to layer (pipe-down warble vs. let the death-music
    // path inside KillPlayer own the audio).
    const bool was_small = (power() == PowerStatus::Small);
    state_.write8(kRam_InjuryTimer, 0x00);
    g_cpu.A = 0;
    call_by_address(kPC_InjurePlayer);
    // InjurePlayer queues $00FF |= $10 internally via STA $FF at $D93F,
    // but that's been silent from TCP context. Layer a direct
    // PlayPipeDownInj call on top — same tandem reasoning as
    // play_coin_pickup_sfx (see SmbRoutines.cpp). Skip on already-Small
    // since KillPlayer's death-music path handles that audio.
    if (!was_small) {
        play_pipe_down_injury();
    }
    return true;
}

// ---- Semantic freezes -------------------------------------------------------

void Mario::freeze_power(PowerStatus v) {
    frozen_power_active_ = true;
    frozen_power_        = v;
    set_power(v);  // immediate
}

void Mario::thaw_power() {
    frozen_power_active_ = false;
}

void Mario::apply_freezes() {
    if (frozen_power_active_) set_power(frozen_power_);
}

}  // namespace smb::semcomp
