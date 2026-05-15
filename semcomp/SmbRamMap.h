// semcomp/SmbRamMap.h — Verified SMB RAM address constants.
//
// Source labels: doppelganger's SMBDIS.ASM, as ported by
// threecreepio/smb-disassembly (also the source of symbols.sym).
//
// Phase 0 rule: only constants documented in HANDOFF.md or directly verified
// against the disassembly are listed here. Inventing addresses is forbidden
// (handoff hard rule: no large unverified mappings). Unmapped concepts get
// TODO(phase1) comments instead of guessed values.
#pragma once

#include <cstdint>

namespace smb::semcomp::ram {

// ---- Player (Mario / Luigi) ------------------------------------------------
// Position is split: PageLoc holds the 256-pixel page, X/Y holds the offset
// within that page. World X = (PageLoc << 8) | X.
constexpr std::uint16_t Player_PageLoc      = 0x006D;
constexpr std::uint16_t Player_X_Position   = 0x0086;
// TODO(phase1): Player_Y_Position (smbdis label exists but not yet verified
// in this repo). Likely $00CE per common reference but unconfirmed here.

// OAM sprite-data offset for the player's sprite block.
constexpr std::uint16_t Player_SprDataOffset = 0x06EC;

// ---- Enemies (5-slot array; index 0..4) -----------------------------------
// All enemy arrays are indexed: read with base + slot.
constexpr std::uint16_t Enemy_Flag_Base       = 0x000F;  // 0 = inactive slot
constexpr std::uint16_t Enemy_ID_Base         = 0x0016;  // enemy type
constexpr std::uint16_t Enemy_PageLoc_Base    = 0x006E;
constexpr std::uint16_t Enemy_X_Position_Base = 0x0087;
constexpr std::uint16_t Enemy_SprDataOffset_Base = 0x06E5;  // per-slot OAM offset

// OffscreenBits is a single bitfield byte, not indexed.
constexpr std::uint16_t Enemy_OffscreenBits   = 0x03D1;

constexpr int kEnemySlotCount = 5;

// ---- Camera / screen bounds -----------------------------------------------
// Left and right edges in world coordinates (PageLoc << 8 | X_Pos).
constexpr std::uint16_t ScreenLeft_PageLoc  = 0x071A;
constexpr std::uint16_t ScreenLeft_X_Pos    = 0x071C;
constexpr std::uint16_t ScreenRight_PageLoc = 0x071B;
constexpr std::uint16_t ScreenRight_X_Pos   = 0x071D;

// ---- Level / world (unmapped — see Phase 1) -------------------------------
// TODO(phase1): WorldNumber, LevelNumber, AreaNumber. smbdis names these but
// the addresses ($075F/$0760/$0750 by common reference) are not yet verified
// against this repo's traces. Add only after verification.

}  // namespace smb::semcomp::ram
