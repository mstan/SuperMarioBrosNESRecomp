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

// Size-change animation flag. Set non-zero by the damage routine (and
// by powerup pickup) to trigger the shrink/grow animation; sprite
// renderer respects it for the animation frames even when PlayerSize is
// at the target value. Mario::set_power clears this so the freeze
// path suppresses the damage-shrink visual.
// Smbdis: PlayerChangeSizeFlag. Reference only — not trace-verified
// against this repo's traces yet.
constexpr std::uint16_t PlayerChangeSizeFlag = 0x070B;

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
// Per-slot bytes indexed off these base addresses. Y-register pattern in
// the ROM: most enemy routines do `LDY slot` (where the loop counter
// has been set up in $C5...) then `LDA Enemy_X,Y` etc. The C++ Enemy
// facade replicates that by holding a slot index and reading
// `base + slot` via GameState::read8.
constexpr int           kEnemySlotCount      = 5;
constexpr std::uint16_t Enemy_Flag_Base      = 0x000F;  // 0=empty, !=0=active
constexpr std::uint16_t Enemy_ID_Base        = 0x0016;  // type byte; see Enemy.h enum
constexpr std::uint16_t Enemy_State_Base     = 0x001E;  // movement phase (walking/stomped/shell)
constexpr std::uint16_t Enemy_MovingDir_Base = 0x0046;
constexpr std::uint16_t Enemy_XSpeed_Base    = 0x0058;  // signed 8-bit
constexpr std::uint16_t Enemy_PageLoc_Base   = 0x006E;  // X page
constexpr std::uint16_t Enemy_YPageLoc_Base  = 0x0076;
constexpr std::uint16_t Enemy_X_Position_Base = 0x0087;
constexpr std::uint16_t Enemy_YVelocity_Base = 0x00B6;  // signed 8-bit
constexpr std::uint16_t Enemy_Y_Position_Base = 0x00CF;
constexpr std::uint16_t Enemy_SprDataOffset_Base = 0x06E5;
constexpr std::uint16_t Enemy_OffscreenBits   = 0x03D1;

// Kill / stomp / spawn entry points (call_by_address with X=slot, A=ID).
//   $E18E KillEnemyAboveBlock — instant remove, no points / no anim
//   $D969 EnemyStomped        — score grant + floatey number + state=$20
//   $C26C CheckpointEnemyID   — populate slot with type A (subject to verification)
constexpr std::uint16_t kPC_KillEnemy        = 0xE18E;
constexpr std::uint16_t kPC_EnemyStomped     = 0xD969;
constexpr std::uint16_t kPC_SpawnEnemyByID   = 0xC26C;

// Block + power-up + floatey routine entry points.
//   $BD9B BumpBlock             — invoke a brick/coin/powerup bump.
//                                 A = block code (0..8), $05 = metatile col.
//   $BC49 SetupPowerUp          — spawn a power-up entity. X = slot,
//                                 $0039 PowerUpType = mushroom/flower/star/1up.
//   $DA11 SetupFloateyNumber    — pop a "+N pts" sprite. X = obj slot,
//                                 A = points-table index (0..9 -> 100..8000).
constexpr std::uint16_t kPC_BumpBlock           = 0xBD9B;
constexpr std::uint16_t kPC_SetupPowerUp        = 0xBC49;
constexpr std::uint16_t kPC_SetupFloateyNumber  = 0xDA11;

// PowerUpType byte read by SetupPowerUp / HandlePowerUpCollision.
//   0 = mushroom
//   1 = fire flower (also star vs flower decision)
//   2 = star
//   3 = 1-up
// Game writes this when a bumped brick is configured for power-ups.
constexpr std::uint16_t PowerUpType          = 0x0039;

// BumpBlock scratch — metatile column / row staging.
constexpr std::uint16_t Block_BumpedMetaCol  = 0x0005;

// ---- Camera / screen bounds -----------------------------------------------
constexpr std::uint16_t ScreenLeft_PageLoc  = 0x071A;
constexpr std::uint16_t ScreenLeft_X_Pos    = 0x071C;
constexpr std::uint16_t ScreenRight_PageLoc = 0x071B;
constexpr std::uint16_t ScreenRight_X_Pos   = 0x071D;

// Scroll-lock flag. ScrollHandler at $AF9D reads this; if non-zero,
// the auto-scroll code is skipped. SMB uses it in boss rooms to pin
// the camera. Trainer "Lock Camera" sets and reasserts this.
constexpr std::uint16_t ScrollLock          = 0x0723;

// Per-frame scroll amount staged at the bottom of UpdScrollVar at
// $AFC4 (TYA / STA $0775). ScrollScreen reads it back to advance
// $071C/$071A. Zeroing this each frame is an alternative to setting
// $0723 — same end effect, slightly different code paths.
constexpr std::uint16_t ScrollAmount        = 0x0775;

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

// Two-player slot index, $00 = player 1, $01 = player 2. Used by routines
// that share work between the two players (CoinTallyOffsets, ScoreOffsets,
// StatusBarNybbles all index off of CurrentPlayer).
constexpr std::uint16_t CurrentPlayer       = 0x0753;

// Per-player 1-Up coin counter. Independent of CoinTally — increments
// every coin grab and is consumed by an outer routine for the 100-coin
// extra-life award. Documented for completeness; not used directly by
// the GiveOneCoin replacement.
constexpr std::uint16_t CoinTallyFor1Ups    = 0x0748;

// ---- Sound queue slots (CORRECTED) ----------------------------------------
// The actual SFX queues are in ZERO PAGE, read by SoundEngine's handlers
// (Square1SfxHandler reads $00FF; Square2SfxHandler reads $00FE). Each is
// a bitmask — bit-per-SFX, so multiple effects can be queued in one byte.
// Game code triggers an effect by ORing or storing the bit:
//   $00FE bit 0 ($01) = coin pickup ("ding")   — JCoinC writes this at $BB79
//   $00FE bit 6 ($40) = extra-life jingle       — GiveOneCoin 1-Up branch
//   $00FF = Square1 SFX queue (various effects, exact map TBD)
//
// IMPORTANT: $0138 and $0139 are NOT sound queues — they are entries 4 and
// 5 of the DigitModifier array (see below). The earlier naming was wrong;
// it conflated the GiveOneCoin instructions LDA #$01; STA $0139 (which
// sets DigitModifier[5]=1 for the BCD coin-digit add) with a sound queue.
// The actual coin SFX queue write happens in the CALLER (JCoinC at $BB79:
// STA $FE), not inside GiveOneCoin itself.
constexpr std::uint16_t Square2_SoundQueue  = 0x00FE;
constexpr std::uint16_t Square1_SoundQueue  = 0x00FF;

// SFX magic values for Square2 queue. Each bit drives one effect.
constexpr std::uint8_t  SFX_CoinPickup       = 0x01;  // bit 0
constexpr std::uint8_t  SFX_ExtraLifeJingle  = 0x40;  // bit 6

// ---- DigitModifier array --------------------------------------------------
// $0134..$0139 is a 6-byte BCD-add work buffer that DigitsMathRoutine
// ($8F5F) reads. Each entry says "add N to the corresponding digit
// position of the target digit run." Callers set up DigitModifier[k] = N
// before JSR'ing DigitsMathRoutine; the routine clears each entry as it
// consumes it.
//
// GiveOneCoin uses two slots:
//   $0139 DigitModifier[5] = 1 → advance the coin display by 1
//   $0138 DigitModifier[4] = 2 → add 2 to the hundreds digit of score
//                                (BCD math turns this into +200 points)
constexpr std::uint16_t DigitModifier_Base  = 0x0134;     // base of 6-byte array
constexpr std::uint16_t DigitModifier_4     = 0x0138;     // hundreds slot (score +200)
constexpr std::uint16_t DigitModifier_5     = 0x0139;     // units slot (coin +1)

// ---- VRAM update buffer ---------------------------------------------------
// The CPU stages PPU writes into VRAM_Buffer1; the NMI handler flushes the
// buffer at vblank. The HUD digit refresh path (PrintStatusBarNumbers ->
// the tail of GiveOneCoin) drops a sentinel tile $24 into the buffer slot
// at $02FB + VRAM_Buffer1_Offset when that slot reads zero.
constexpr std::uint16_t VRAM_Buffer1        = 0x0301;
constexpr std::uint16_t VRAM_Buffer1_Offset = 0x0300;
constexpr std::uint16_t VRAM_Buffer1_BackQueue = 0x02FB;

// Zero-page scratch slot $08 — generated code uses this as a scratch X
// save across the GiveOneCoin fall-through to AddToScore. Named here so
// the semantic replacement can do the same save/restore.
constexpr std::uint16_t ZP_Scratch_08       = 0x0008;

// ---- Score / Timer --------------------------------------------------------
// Score is stored as 6 BCD digits per player. Two parallel copies exist:
//   $07D7..$07DC PlayerOneScore_Display — what PrintStatusBarNumbers reads
//                                          to push the HUD tiles. Each byte
//                                          holds one decimal digit (0-9),
//                                          leftmost = hundred-thousands.
//   $07DD..$07E2 PlayerOneScore_Internal — gameplay-mutable; UpdateTopScore
//                                          copies internal→display when the
//                                          current run sets a new top.
// Trainer-side set/add writes BOTH so the HUD reflects the new value
// without waiting on UpdateTopScore.
constexpr std::uint16_t PlayerOneScore_Display  = 0x07D7;
constexpr std::uint16_t PlayerOneScore_Internal = 0x07DD;
constexpr int           kScoreDigits            = 6;

// Game timer — 3 BCD digits, hundreds/tens/units. Counts down during
// gameplay. PrintStatusBarNumbers refreshes the displayed digits via the
// same status-bar nybbles mechanism used for score and coins.
constexpr std::uint16_t GameTimer_Hundreds = 0x07F8;
constexpr std::uint16_t GameTimer_Tens     = 0x07F9;
constexpr std::uint16_t GameTimer_Units    = 0x07FA;

// ---- ROM tables (indexed by CurrentPlayer) --------------------------------
// These live in PRG ROM, not work RAM, so they must be read via the
// runtime's nes_read (which falls through the mapper) rather than via
// GameState::read8 (which only models the 2KB work-RAM window). They are
// adjacent to the GiveOneCoin routine itself in the original ROM.
constexpr std::uint16_t ROM_CoinTallyOffsets = 0xBBF8;
constexpr std::uint16_t ROM_ScoreOffsets     = 0xBBFA;
constexpr std::uint16_t ROM_StatusBarNybbles = 0xBBFC;

// TODO(phase1.5): score ($07FC..$07FE BCD triplet), GameTimer
// ($0747..$0749 or similar; address unverified), AreaNumber (the
// sub-area index inside a level used for pipe rooms). None of these
// are required for the Mario-as-object milestone.

}  // namespace smb::semcomp::ram
