// semcomp/OamWriter.h — identity-tagged OAM emission.
//
// The emit half of the object abstraction. SMB writes OAM bytes from ~128
// scattered sites inside transcribed draw routines; on its own, an OAM X byte
// has lost the 256px "page" and the identity of the object that wrote it (the
// exact failure that made widescreen a treadmill). OamWriter carries that
// identity forward instead of reconstructing it:
//
//   * The owned $F171 GetObjRelativePosition publishes the object it just
//     positioned via set_current_owner(). Player and enemies draw their whole
//     metasprite immediately after their own $F171, so the current owner IS
//     the true owner of the upcoming OAM writes — no value-matching, no page
//     ambiguity.
//   * record() is appended immediately AFTER each vanilla OAM-byte nes_write
//     (added per class in Phase 3). It is a pure side effect: it never alters
//     the vanilla store, so it cannot change behavior (byte parity holds). It
//     tags the byte with its owner and reconstructs the true 16-bit screen X
//     (screen_x16 + signed8(byte - rel_x8)); the low byte equals the byte by
//     construction, so the page is recovered, not guessed.
//
// On a 4:3 build the recorded batch is unused (rendering uses the vanilla OAM
// byte); it is the structured, identity-correct sprite stream a feature like
// widescreen would consume — computed at the layer where identity exists.
#pragma once

#include <cstddef>
#include <cstdint>

namespace smb::semcomp {

enum class OamByteKind : std::uint8_t { Y = 0, Tile = 1, Attr = 2, X = 3 };

class OamWriter {
public:
    // Published by the owned $F171 just before an object's sprites are drawn.
    //   obj_index  : unified SprObject index (the $F171 X register)
    //   rel_ofs    : per-class relative-table offset (the $F171 Y register)
    //   screen_x16 : object's signed 16-bit screen X (world_x - camera_left)
    //   rel_x8     : object's vanilla 8-bit screen X (== screen_x16 low byte)
    static void set_current_owner(std::uint8_t obj_index, std::uint8_t rel_ofs,
                                  std::int16_t screen_x16, std::uint8_t rel_x8);
    static void clear_current_owner();
    static bool has_current_owner();

    // Reset per-frame state. Called once per game frame.
    static void begin_frame();

    // Tap after a vanilla OAM-byte store at oam_addr ($0200-$02FF) of `value`.
    // Pure side effect (records identity + reconstructed wide X for X bytes).
    static void record(std::uint16_t oam_addr, std::uint8_t value);

    // Per-OAM-slot reconstructed signed 16-bit screen X (valid only for slots
    // whose X byte was recorded this frame). For downstream consumers.
    static std::int16_t slot_screen_x(std::uint8_t slot);
    static bool slot_valid(std::uint8_t slot);
    static std::uint8_t slot_owner_rel_ofs(std::uint8_t slot);

private:
    static bool         s_owner_valid;
    static std::uint8_t s_owner_obj_index;
    static std::uint8_t s_owner_rel_ofs;
    static std::int16_t s_owner_screen_x16;
    static std::uint8_t s_owner_rel_x8;

    // Per-frame per-slot reconstructed wide X + provenance.
    static std::int16_t s_slot_x16[64];
    static std::uint8_t s_slot_valid[64];
    static std::uint8_t s_slot_rel_ofs[64];
};

}  // namespace smb::semcomp
