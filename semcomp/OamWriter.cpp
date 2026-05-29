// semcomp/OamWriter.cpp — see OamWriter.h.
#include "semcomp/OamWriter.h"

namespace smb::semcomp {

bool         OamWriter::s_owner_valid = false;
std::uint8_t OamWriter::s_owner_obj_index = 0;
std::uint8_t OamWriter::s_owner_rel_ofs = 0;
std::int16_t OamWriter::s_owner_screen_x16 = 0;
std::uint8_t OamWriter::s_owner_rel_x8 = 0;
std::int16_t OamWriter::s_slot_x16[64] = {};
std::uint8_t OamWriter::s_slot_valid[64] = {};
std::uint8_t OamWriter::s_slot_rel_ofs[64] = {};

void OamWriter::set_current_owner(std::uint8_t obj_index, std::uint8_t rel_ofs,
                                  std::int16_t screen_x16, std::uint8_t rel_x8) {
    s_owner_valid = true;
    s_owner_obj_index = obj_index;
    s_owner_rel_ofs = rel_ofs;
    s_owner_screen_x16 = screen_x16;
    s_owner_rel_x8 = rel_x8;
}

void OamWriter::clear_current_owner() { s_owner_valid = false; }
bool OamWriter::has_current_owner() { return s_owner_valid; }

void OamWriter::begin_frame() {
    s_owner_valid = false;
    for (int i = 0; i < 64; ++i) s_slot_valid[i] = 0;
}

void OamWriter::record(std::uint16_t oam_addr, std::uint8_t value) {
    if (oam_addr < 0x0200 || oam_addr > 0x02FF) return;
    const int slot = (oam_addr - 0x0200) >> 2;
    const OamByteKind kind = static_cast<OamByteKind>((oam_addr - 0x0200) & 3);
    if (kind != OamByteKind::X) return;   // only the X byte carries wide position
    if (!s_owner_valid) return;           // deferred-draw attribution: Phase 3

    // Sub-sprite column from the object's rel origin, signed (sprites can sit a
    // few px left of origin). screen_x16 + col has low byte == value, so the
    // 256px page is recovered, not guessed.
    const int col = static_cast<std::int8_t>(
        static_cast<std::uint8_t>(value - s_owner_rel_x8));
    int x16 = s_owner_screen_x16 + col;
    if (x16 > 32767) x16 -= 65536;
    if (x16 < -32768) x16 += 65536;
    s_slot_x16[slot] = static_cast<std::int16_t>(x16);
    s_slot_valid[slot] = 1;
    s_slot_rel_ofs[slot] = s_owner_rel_ofs;
}

std::int16_t OamWriter::slot_screen_x(std::uint8_t slot) {
    return slot < 64 ? s_slot_x16[slot] : 0;
}
bool OamWriter::slot_valid(std::uint8_t slot) {
    return slot < 64 && s_slot_valid[slot] != 0;
}
std::uint8_t OamWriter::slot_owner_rel_ofs(std::uint8_t slot) {
    return slot < 64 ? s_slot_rel_ofs[slot] : 0;
}

}  // namespace smb::semcomp
