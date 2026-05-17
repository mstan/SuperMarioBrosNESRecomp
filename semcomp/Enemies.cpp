// semcomp/Enemies.cpp — container over the 5 enemy slots.
#include "semcomp/Enemies.h"

#include "semcomp/GameState.h"

namespace smb::semcomp {

int Enemies::active_count() const {
    int n = 0;
    for (int i = 0; i < kSlotCount; ++i) {
        if (Enemy(const_cast<GameState&>(state_), (std::uint8_t)i).active())
            ++n;
    }
    return n;
}

void Enemies::kill_all() {
    for (int i = 0; i < kSlotCount; ++i) {
        Enemy e(state_, (std::uint8_t)i);
        if (e.active()) e.kill();
    }
}

void Enemies::stomp_all() {
    for (int i = 0; i < kSlotCount; ++i) {
        Enemy e(state_, (std::uint8_t)i);
        if (e.active()) e.stomp();
    }
}

void Enemies::freeze_all() {
    for (int i = 0; i < kSlotCount; ++i) {
        Enemy e(state_, (std::uint8_t)i);
        if (e.active()) e.freeze();
    }
}

}  // namespace smb::semcomp
