// semcomp/SpriteWorld.cpp — see SpriteWorld.h.
//
// Phase 1 enumerates the player + 5 enemy slots (the classes whose state
// arrays are mapped in SmbRamMap.h). Fireball/bubble/block/misc are added as
// their draw paths are migrated through the emit layer (Phase 3), so the
// model grows alongside the classes that actually consume it.
#include "semcomp/SpriteWorld.h"

#include "semcomp/GameState.h"
#include "semcomp/SmbRamMap.h"

namespace smb::semcomp {

namespace {
std::int16_t clamp_s16(int v) {
    if (v > 32767) v -= 65536;
    if (v < -32768) v += 65536;
    return static_cast<std::int16_t>(v);
}
}  // namespace

void SpriteWorld::refresh() {
    count_ = 0;
    camera_world_x_ = (state_.read8(ram::ScreenLeft_PageLoc) << 8) |
                      state_.read8(ram::ScreenLeft_X_Pos);
    add_player();
    add_enemies();
}

std::int16_t SpriteWorld::project_screen_x(std::uint16_t world_x) const {
    return clamp_s16(static_cast<int>(world_x) - camera_world_x_);
}

void SpriteWorld::add_player() {
    if (count_ >= kMaxObjs) return;
    SpriteObject& o = objs_[count_++];
    o = SpriteObject{};
    o.cls = SprClass::Player;
    o.slot = 0;
    o.rel_ofs = 0;
    o.obj_index = 0;  // unified index 0 -> $86+0 / $6D+0
    o.world_x = static_cast<std::uint16_t>(
        (state_.read8(ram::Player_PageLoc) << 8) | state_.read8(ram::Player_X_Position));
    o.world_y = state_.read8(ram::Player_Y_Position);
    o.screen_x = project_screen_x(o.world_x);
    o.screen_y = static_cast<std::int16_t>(o.world_y);
    o.spr_data_offset = state_.read8(ram::Player_SprDataOffset);
}

void SpriteWorld::add_enemies() {
    for (int s = 0; s < ram::kEnemySlotCount; ++s) {
        if (state_.read8(ram::Enemy_Flag_Base + s) == 0) continue;
        if (count_ >= kMaxObjs) return;
        SpriteObject& o = objs_[count_++];
        o = SpriteObject{};
        o.cls = SprClass::Enemy;
        o.slot = static_cast<std::uint8_t>(s);
        o.rel_ofs = 1;
        o.obj_index = static_cast<std::uint8_t>(s + 1);  // enemy slot -> unified index s+1
        o.type_id = state_.read8(ram::Enemy_ID_Base + s);
        o.world_x = static_cast<std::uint16_t>(
            (state_.read8(ram::Enemy_PageLoc_Base + s) << 8) |
            state_.read8(ram::Enemy_X_Position_Base + s));
        o.world_y = state_.read8(ram::Enemy_Y_Position_Base + s);
        o.screen_x = project_screen_x(o.world_x);
        o.screen_y = static_cast<std::int16_t>(o.world_y);
        o.spr_data_offset = state_.read8(ram::Enemy_SprDataOffset_Base + s);
    }
}

const SpriteObject* SpriteWorld::by_obj_index(std::uint8_t obj_index) const {
    for (std::size_t i = 0; i < count_; ++i) {
        if (objs_[i].obj_index == obj_index) return &objs_[i];
    }
    return nullptr;
}

const SpriteObject* SpriteWorld::by_oam_slot(std::uint8_t oam_slot) const {
    // The object whose metasprite region contains this OAM slot: the largest
    // base <= oam_slot within a metasprite's reach. SMB lays each object's
    // sprites contiguously from its SprDataOffset, and SprDataOffsets are
    // assigned disjointly, so "nearest base at or below" is unambiguous.
    const SpriteObject* best = nullptr;
    int best_base = -1;
    for (std::size_t i = 0; i < count_; ++i) {
        const int base = objs_[i].oam_slot();
        if (base <= oam_slot && base > best_base && (oam_slot - base) < 8) {
            best_base = base;
            best = &objs_[i];
        }
    }
    return best;
}

}  // namespace smb::semcomp
