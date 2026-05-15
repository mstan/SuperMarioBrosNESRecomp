// semcomp/SmbRamMap.h — Verified SMB RAM address constants.
//
// Source labels: doppelganger's SMBDIS.ASM (canonical), as ported by
// threecreepio/smb-disassembly. Each constant below was verified against
// a recorded attract-demo trace on 2026-05-14 (semcomp/phase1-mario
// branch). Verification methodology: TCP read_ram sampling across the
// demo, correlating value transitions with known game events (Mario
// jumping, mushroom pickup, demo cycling between levels).
//
// Historical note: prior to commit 4408aa8, extras.c labeled $001D and
// $0756 with swapped names (PlayerSize/Player_State) and read
// $075A/$075C/$075E with wrong-byte names for world/level/area_type.
// That commit removed those mislabeled fields outright. The
// verification pass that produced this file is what surfaced the bug.
#pragma once

#include <cstdint>

namespace smb::semcomp::ram {

// ---- Player (Mario / Luigi) ------------------------------------------------
// Position split: PageLoc holds the 256-pixel page; X/Y holds the offset
// within that page. World X = (PageLoc << 8) | X.
constexpr std::uint16_t Player_PageLoc      = 0x006D;
constexpr std::uint16_t Player_X_Position   = 0x0086;
constexpr std::uint16_t Player_Y_Position   = 0x00CE;

// Physics state byte. Observed values during demo:
//   0 = on ground
//   1, 2 = airborne (likely rising vs. falling, full semantic mapping
//          deferred to Phase 1.5 via targeted probe).
constexpr std::uint16_t Player_State        = 0x001D;

// Power-up status. Observed Small=0 and Big=1 during a mushroom-pickup
// demo run. Fire=2 is smbdis-canonical but not observed in this trace
// (demo never grabs a fire flower).
constexpr std::uint16_t PlayerStatus        = 0x0756;

// Size byte tracked separately from PlayerStatus in original SMB.
//   0 = tall (Big or Fire Mario)
//   1 = short (Small Mario)
// Redundant with PlayerStatus in steady state but updated on different
// frames during powerup/damage transitions.
constexpr std::uint16_t PlayerSize          = 0x0754;

// Facing and movement direction. Observed [0, 1, 2]:
//   0 = none / uninitialized / title idle
//   1 = right
//   2 = left
constexpr std::uint16_t PlayerFacingDir     = 0x0033;
constexpr std::uint16_t Player_MovingDir    = 0x0045;

// Velocity (signed 8-bit integer part of 8.8 fixed-point).
//   $0057 X velocity, observed signed range [-26..+40].
//   $009F Y velocity, observed signed range [-5..+4] (narrow because
//         10Hz sampling missed peak-velocity frames; full range in
//         original SMB is roughly [-40..+45]). Treat the observed
//         range as a lower bound on the true variation.
constexpr std::uint16_t Player_X_Speed      = 0x0057;
constexpr std::uint16_t Player_Y_Speed      = 0x009F;

// Unsigned speed magnitude, observed [0..40]. The 40 cap matches the
// running-speed limit; walking caps around 24.
constexpr std::uint16_t Player_XSpeedAbsolute = 0x0700;

// OAM sprite-data offset for the player's sprite block.
constexpr std::uint16_t Player_SprDataOffset = 0x06EC;

// ---- Enemies (5-slot array; index 0..4) -----------------------------------
constexpr std::uint16_t Enemy_Flag_Base       = 0x000F;
constexpr std::uint16_t Enemy_ID_Base         = 0x0016;
constexpr std::uint16_t Enemy_PageLoc_Base    = 0x006E;
constexpr std::uint16_t Enemy_X_Position_Base = 0x0087;
constexpr std::uint16_t Enemy_SprDataOffset_Base = 0x06E5;
constexpr std::uint16_t Enemy_OffscreenBits   = 0x03D1;
constexpr int kEnemySlotCount = 5;

// ---- Camera / screen bounds -----------------------------------------------
constexpr std::uint16_t ScreenLeft_PageLoc  = 0x071A;
constexpr std::uint16_t ScreenLeft_X_Pos    = 0x071C;
constexpr std::uint16_t ScreenRight_PageLoc = 0x071B;
constexpr std::uint16_t ScreenRight_X_Pos   = 0x071D;

// ---- Level identity -------------------------------------------------------
// 0-indexed: World 1-1 reads as world=0, level=0. The HUD displays "1-1"
// by adding 1 to each at render time.
constexpr std::uint16_t WorldNumber         = 0x075F;
constexpr std::uint16_t LevelNumber         = 0x0760;

// ---- Run/session state ----------------------------------------------------
// NumberofLives observed [0..2] across demo cycles (starts at 2, decrements
// on death). The HUD-displayed life count is this value plus a constant
// offset that smbdis handles in the render routine.
constexpr std::uint16_t NumberofLives       = 0x075A;
// CoinTally observed [0..2] during a single demo cycle as Mario picks up
// coins. 0..99 range expected in full gameplay.
constexpr std::uint16_t CoinTally           = 0x075E;

// TODO(phase1.5): score ($07FC..$07FE BCD triplet), GameTimer
// ($0747..$0749 or similar; address unverified), AreaNumber (the
// sub-area index inside a level used for pipe rooms). None of these
// are required for the Mario-as-object milestone.

}  // namespace smb::semcomp::ram
