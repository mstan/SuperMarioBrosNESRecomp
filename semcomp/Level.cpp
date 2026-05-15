// semcomp/Level.cpp — stage identity reads.
#include "semcomp/Level.h"
#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"

namespace smb::semcomp {

std::uint8_t Level::world() const { return state_.read8(ram::WorldNumber); }
std::uint8_t Level::level() const { return state_.read8(ram::LevelNumber); }

}  // namespace smb::semcomp
