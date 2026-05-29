// semcomp/SpriteWorld.h — unified read-model over SMB's sprite-objects.
//
// This is the foundation of the object abstraction: a single place that
// enumerates every live sprite-object and exposes its identity, world/screen
// position, OAM region (SprDataOffset), and visibility — computed once, by
// reading the existing RAM through GameState. It centralizes the one piece
// the widescreen experiment kept reconstructing downstream and getting wrong:
// the world->screen projection. Nothing here mutates state; it is a pure read
// view, so adding/refreshing it cannot change game behavior (parity-neutral).
//
// Object classes correspond to SMB's per-class relative-position offset (the
// Y register passed to $F171 GetObjRelativePosition); see SmbRamMap.h.
#pragma once

#include <cstddef>
#include <cstdint>

namespace smb::semcomp {

class GameState;

enum class SprClass : std::uint8_t {
    None = 0,
    Player,    // rel_ofs 0
    Enemy,     // rel_ofs 1   (5 slots)
    Fireball,  // rel_ofs 2
    Bubble,    // rel_ofs 3
    Block,     // rel_ofs 4/5
    Misc,      // rel_ofs 6   (powerup / coin / flag)
};

// A snapshot of one live sprite-object for the current frame. Cheap value type.
struct SpriteObject {
    SprClass      cls = SprClass::None;
    std::uint8_t  slot = 0;             // class-local index (enemy 0..4)
    std::uint8_t  rel_ofs = 0;          // $F171 Y: $03AD+rel_ofs class slot
    std::uint8_t  obj_index = 0;        // $F171 X: unified SprObject index ($86+X)
    std::uint8_t  type_id = 0;          // Enemy_ID for enemies; 0 otherwise
    std::uint8_t  spr_data_offset = 0;  // OAM byte offset where its metasprite starts
    std::uint16_t world_x = 0;          // (PageLoc<<8)|X_Position
    std::uint16_t world_y = 0;
    std::int16_t  screen_x = 0;         // signed 16-bit: world_x - camera_left
    std::int16_t  screen_y = 0;

    // Vanilla 8-bit screen X SMB stores at $03AD+rel_ofs (== screen_x low byte).
    std::uint8_t rel_x8() const { return static_cast<std::uint8_t>(screen_x & 0xFF); }
    // First OAM slot index (0..63) the metasprite occupies.
    std::uint8_t oam_slot() const { return static_cast<std::uint8_t>(spr_data_offset >> 2); }
};

class SpriteWorld {
public:
    explicit SpriteWorld(GameState& state) : state_(state) {}

    // Snapshot every live sprite-object this frame. Pure reads via GameState.
    void refresh();

    std::size_t count() const { return count_; }
    const SpriteObject& at(std::size_t i) const { return objs_[i]; }

    // Lookups used by the OAM emit path (Phase 2+). by_obj_index resolves the
    // object $F171 was just called for (its X register); by_oam_slot resolves
    // the object that owns a given OAM slot (for deferred-draw attribution),
    // i.e. the object whose metasprite region contains that slot.
    const SpriteObject* by_obj_index(std::uint8_t obj_index) const;
    const SpriteObject* by_oam_slot(std::uint8_t oam_slot) const;

    // THE world->screen projection (mirrors $F171's 16-bit subtract). Signed,
    // so margin/left-edge positions are represented faithfully.
    std::int16_t project_screen_x(std::uint16_t world_x) const;

    int camera_world_x() const { return camera_world_x_; }

private:
    GameState& state_;
    static constexpr std::size_t kMaxObjs = 16;
    SpriteObject objs_[kMaxObjs];
    std::size_t  count_ = 0;
    int          camera_world_x_ = 0;  // full unsigned 16-bit camera-left world X

    void add_player();
    void add_enemies();
};

}  // namespace smb::semcomp
