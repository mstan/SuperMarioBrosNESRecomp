// semcomp/PlayerSession.cpp — per-playthrough state reads.
#include "semcomp/PlayerSession.h"
#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"

namespace smb::semcomp {

std::uint8_t PlayerSession::lives() const {
    return state_.read8(ram::NumberofLives);
}

std::uint8_t PlayerSession::coins() const {
    return state_.read8(ram::CoinTally);
}

}  // namespace smb::semcomp
