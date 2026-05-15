// semcomp/Trainer.cpp — freeze table impl.
#include "semcomp/Trainer.h"
#include "semcomp/GameState.h"

namespace smb::semcomp {

std::size_t Trainer::find_index(std::uint16_t addr) const {
    for (std::size_t i = 0; i < count_; ++i) {
        if (slots_[i].addr == addr) return i;
    }
    return kMaxFreezeEntries;
}

bool Trainer::set(std::uint16_t addr, std::uint8_t val) {
    state_.write8(addr, val);
    return true;
}

bool Trainer::freeze(std::uint16_t addr, std::uint8_t val) {
    const std::size_t idx = find_index(addr);
    if (idx < count_) {
        slots_[idx].value = val;
        // Apply immediately so the user sees the value take effect even
        // before the next post-NMI tick.
        state_.write8(addr, val);
        return true;
    }
    if (count_ >= kMaxFreezeEntries) return false;
    slots_[count_] = {addr, val};
    ++count_;
    state_.write8(addr, val);
    return true;
}

bool Trainer::thaw(std::uint16_t addr) {
    const std::size_t idx = find_index(addr);
    if (idx >= count_) return false;
    // Compact: move last entry into the gap.
    slots_[idx] = slots_[count_ - 1];
    slots_[count_ - 1] = {};
    --count_;
    return true;
}

bool Trainer::is_frozen(std::uint16_t addr) const {
    return find_index(addr) < count_;
}

std::uint8_t Trainer::frozen_value(std::uint16_t addr) const {
    const std::size_t idx = find_index(addr);
    return (idx < count_) ? slots_[idx].value : 0;
}

std::uint16_t Trainer::entry_addr(std::size_t i) const {
    return (i < count_) ? slots_[i].addr : 0;
}

std::uint8_t Trainer::entry_value(std::size_t i) const {
    return (i < count_) ? slots_[i].value : 0;
}

void Trainer::apply() {
    if (!enabled_) return;
    for (std::size_t i = 0; i < count_; ++i) {
        state_.write8(slots_[i].addr, slots_[i].value);
    }
}

}  // namespace smb::semcomp
