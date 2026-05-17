// semcomp/Enemy.cpp — single-slot accessor over the 5-slot enemy array.
#include "semcomp/Enemy.h"

#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"

extern "C" {
#include "nes_runtime.h"
}

namespace smb::semcomp {

namespace {
inline std::uint16_t at(std::uint16_t base, std::uint8_t slot) {
    return static_cast<std::uint16_t>(base + slot);
}
}  // namespace

bool Enemy::active() const {
    return state_.read8(at(ram::Enemy_Flag_Base, slot_)) != 0;
}

std::uint8_t Enemy::id_raw() const {
    return state_.read8(at(ram::Enemy_ID_Base, slot_));
}

std::uint8_t Enemy::state_raw() const {
    return state_.read8(at(ram::Enemy_State_Base, slot_));
}

std::uint8_t Enemy::x() const {
    return state_.read8(at(ram::Enemy_X_Position_Base, slot_));
}
std::uint8_t Enemy::y() const {
    return state_.read8(at(ram::Enemy_Y_Position_Base, slot_));
}
std::uint8_t Enemy::x_page() const {
    return state_.read8(at(ram::Enemy_PageLoc_Base, slot_));
}
std::uint8_t Enemy::y_page() const {
    return state_.read8(at(ram::Enemy_YPageLoc_Base, slot_));
}

std::int8_t Enemy::x_velocity() const {
    return static_cast<std::int8_t>(state_.read8(at(ram::Enemy_XSpeed_Base, slot_)));
}
std::int8_t Enemy::y_velocity() const {
    return static_cast<std::int8_t>(state_.read8(at(ram::Enemy_YVelocity_Base, slot_)));
}

void Enemy::kill() {
    // Set X to slot index, jump into KillEnemyAboveBlock. The natural
    // call sites (fireball / falling block) do exactly this.
    g_cpu.X = slot_;
    call_by_address(ram::kPC_KillEnemy);
}

void Enemy::stomp() {
    // Set X to slot index, jump into EnemyStomped. The Y register is
    // expected to hold a "stomp chain" index that scales the score; we
    // pass 0 (= base 100-point grant) per call. If the trainer chains
    // multiple stomps in one tick, they'll all score the base amount —
    // the natural game increments Y across stomps within one frame.
    g_cpu.X = slot_;
    g_cpu.Y = 0;
    call_by_address(ram::kPC_EnemyStomped);
}

void Enemy::freeze() {
    state_.write8(at(ram::Enemy_XSpeed_Base,    slot_), 0);
    state_.write8(at(ram::Enemy_YVelocity_Base, slot_), 0);
}

}  // namespace smb::semcomp
