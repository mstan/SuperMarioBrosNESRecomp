// semcomp/TrainerUI.cpp — in-game text overlay for the trainer.
//
// Renders into the 256x240 ARGB framebuffer (top byte = ignored or alpha;
// runner uses 0xAARRGGBB layout). Uses a 5x7 bitmap font advancing 6
// pixels horizontally and 8 vertically. Font covers space, digits,
// uppercase A-Z, and a handful of symbols used by the trainer UI; any
// other char renders blank.
#include "semcomp/TrainerUI.h"
#include "semcomp/SemcompGame.h"
#include "semcomp/SmbRamMap.h"

#include <SDL.h>

#include <cstdio>
#include <cstring>

namespace smb::semcomp {

namespace {

// 5x7 glyphs in 8-byte cells. Each byte = one row; MSB-first; pixels
// occupy bits 7..3 (cols 0..4). Index = ASCII - 0x20. Undefined glyphs
// are zero-initialized to render as blank.
constexpr int kCellW = 6;   // 5 pixels + 1 spacing
constexpr int kCellH = 8;

constexpr std::uint8_t FONT[96][8] = {
    /* 0x20 ' ' */ {0,0,0,0,0,0,0,0},
    /* 0x21 '!' */ {0x20,0x20,0x20,0x20,0x20,0x00,0x20,0x00},
    /* 0x22 '"' */ {0x50,0x50,0,0,0,0,0,0},
    /* 0x23 '#' */ {0x50,0x50,0xF8,0x50,0xF8,0x50,0x50,0x00},
    /* 0x24 '$' */ {0x20,0x78,0xA0,0x70,0x28,0xF0,0x20,0x00},
    /* 0x25 '%' */ {0xC8,0xC8,0x10,0x20,0x40,0x98,0x98,0x00},
    /* 0x26 '&' */ {0x60,0x90,0xA0,0x40,0xA8,0x90,0x68,0x00},
    /* 0x27 ''' */ {0x20,0x20,0,0,0,0,0,0},
    /* 0x28 '(' */ {0x10,0x20,0x40,0x40,0x40,0x20,0x10,0x00},
    /* 0x29 ')' */ {0x40,0x20,0x10,0x10,0x10,0x20,0x40,0x00},
    /* 0x2A '*' */ {0,0xA8,0x70,0xF8,0x70,0xA8,0,0},
    /* 0x2B '+' */ {0,0x20,0x20,0xF8,0x20,0x20,0,0},
    /* 0x2C ',' */ {0,0,0,0,0,0x30,0x30,0x20},
    /* 0x2D '-' */ {0,0,0,0xF8,0,0,0,0},
    /* 0x2E '.' */ {0,0,0,0,0,0x60,0x60,0},
    /* 0x2F '/' */ {0x08,0x10,0x10,0x20,0x40,0x40,0x80,0x00},

    /* 0x30 '0' */ {0x70,0x88,0x98,0xA8,0xC8,0x88,0x70,0x00},
    /* 0x31 '1' */ {0x20,0x60,0x20,0x20,0x20,0x20,0x70,0x00},
    /* 0x32 '2' */ {0x70,0x88,0x08,0x70,0x80,0x80,0xF8,0x00},
    /* 0x33 '3' */ {0xF8,0x10,0x20,0x10,0x08,0x88,0x70,0x00},
    /* 0x34 '4' */ {0x10,0x30,0x50,0x90,0xF8,0x10,0x10,0x00},
    /* 0x35 '5' */ {0xF8,0x80,0xF0,0x08,0x08,0x88,0x70,0x00},
    /* 0x36 '6' */ {0x70,0x80,0xF0,0x88,0x88,0x88,0x70,0x00},
    /* 0x37 '7' */ {0xF8,0x08,0x10,0x10,0x20,0x20,0x20,0x00},
    /* 0x38 '8' */ {0x70,0x88,0x88,0x70,0x88,0x88,0x70,0x00},
    /* 0x39 '9' */ {0x70,0x88,0x88,0x88,0x78,0x08,0x70,0x00},

    /* 0x3A ':' */ {0,0x60,0x60,0,0x60,0x60,0,0},
    /* 0x3B ';' */ {0,0x60,0x60,0,0x60,0x60,0x40,0},
    /* 0x3C '<' */ {0x10,0x20,0x40,0x80,0x40,0x20,0x10,0x00},
    /* 0x3D '=' */ {0,0,0xF8,0,0xF8,0,0,0},
    /* 0x3E '>' */ {0x80,0x40,0x20,0x10,0x20,0x40,0x80,0x00},
    /* 0x3F '?' */ {0x70,0x88,0x08,0x10,0x20,0x00,0x20,0x00},

    /* 0x40 '@' */ {0x70,0x88,0xB8,0xA8,0xB8,0x80,0x70,0x00},

    /* 0x41 'A' */ {0x70,0x88,0x88,0xF8,0x88,0x88,0x88,0x00},
    /* 0x42 'B' */ {0xF0,0x88,0x88,0xF0,0x88,0x88,0xF0,0x00},
    /* 0x43 'C' */ {0x70,0x88,0x80,0x80,0x80,0x88,0x70,0x00},
    /* 0x44 'D' */ {0xF0,0x88,0x88,0x88,0x88,0x88,0xF0,0x00},
    /* 0x45 'E' */ {0xF8,0x80,0x80,0xF0,0x80,0x80,0xF8,0x00},
    /* 0x46 'F' */ {0xF8,0x80,0x80,0xF0,0x80,0x80,0x80,0x00},
    /* 0x47 'G' */ {0x70,0x88,0x80,0xB8,0x88,0x88,0x78,0x00},
    /* 0x48 'H' */ {0x88,0x88,0x88,0xF8,0x88,0x88,0x88,0x00},
    /* 0x49 'I' */ {0x70,0x20,0x20,0x20,0x20,0x20,0x70,0x00},
    /* 0x4A 'J' */ {0x38,0x10,0x10,0x10,0x10,0x90,0x60,0x00},
    /* 0x4B 'K' */ {0x88,0x90,0xA0,0xC0,0xA0,0x90,0x88,0x00},
    /* 0x4C 'L' */ {0x80,0x80,0x80,0x80,0x80,0x80,0xF8,0x00},
    /* 0x4D 'M' */ {0x88,0xD8,0xA8,0xA8,0x88,0x88,0x88,0x00},
    /* 0x4E 'N' */ {0x88,0x88,0xC8,0xA8,0x98,0x88,0x88,0x00},
    /* 0x4F 'O' */ {0x70,0x88,0x88,0x88,0x88,0x88,0x70,0x00},
    /* 0x50 'P' */ {0xF0,0x88,0x88,0xF0,0x80,0x80,0x80,0x00},
    /* 0x51 'Q' */ {0x70,0x88,0x88,0x88,0xA8,0x90,0x68,0x00},
    /* 0x52 'R' */ {0xF0,0x88,0x88,0xF0,0xA0,0x90,0x88,0x00},
    /* 0x53 'S' */ {0x70,0x88,0x80,0x70,0x08,0x88,0x70,0x00},
    /* 0x54 'T' */ {0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0x00},
    /* 0x55 'U' */ {0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00},
    /* 0x56 'V' */ {0x88,0x88,0x88,0x88,0x88,0x50,0x20,0x00},
    /* 0x57 'W' */ {0x88,0x88,0x88,0xA8,0xA8,0xD8,0x88,0x00},
    /* 0x58 'X' */ {0x88,0x88,0x50,0x20,0x50,0x88,0x88,0x00},
    /* 0x59 'Y' */ {0x88,0x88,0x88,0x50,0x20,0x20,0x20,0x00},
    /* 0x5A 'Z' */ {0xF8,0x08,0x10,0x20,0x40,0x80,0xF8,0x00},

    /* 0x5B '[' */ {0x70,0x40,0x40,0x40,0x40,0x40,0x70,0x00},
    /* 0x5C '\' */ {0x80,0x40,0x40,0x20,0x10,0x10,0x08,0x00},
    /* 0x5D ']' */ {0x70,0x10,0x10,0x10,0x10,0x10,0x70,0x00},
    /* 0x5E '^' */ {0x20,0x50,0x88,0,0,0,0,0},
    /* 0x5F '_' */ {0,0,0,0,0,0,0xF8,0},

    /* 0x60..0x7F : unused (lowercase / browse-grade) - zero-filled */
    /* 0x60 */ {0,0,0,0,0,0,0,0},
    /* 0x61 */ {0,0,0,0,0,0,0,0}, /* 0x62 */ {0,0,0,0,0,0,0,0},
    /* 0x63 */ {0,0,0,0,0,0,0,0}, /* 0x64 */ {0,0,0,0,0,0,0,0},
    /* 0x65 */ {0,0,0,0,0,0,0,0}, /* 0x66 */ {0,0,0,0,0,0,0,0},
    /* 0x67 */ {0,0,0,0,0,0,0,0}, /* 0x68 */ {0,0,0,0,0,0,0,0},
    /* 0x69 */ {0,0,0,0,0,0,0,0}, /* 0x6A */ {0,0,0,0,0,0,0,0},
    /* 0x6B */ {0,0,0,0,0,0,0,0}, /* 0x6C */ {0,0,0,0,0,0,0,0},
    /* 0x6D */ {0,0,0,0,0,0,0,0}, /* 0x6E */ {0,0,0,0,0,0,0,0},
    /* 0x6F */ {0,0,0,0,0,0,0,0}, /* 0x70 */ {0,0,0,0,0,0,0,0},
    /* 0x71 */ {0,0,0,0,0,0,0,0}, /* 0x72 */ {0,0,0,0,0,0,0,0},
    /* 0x73 */ {0,0,0,0,0,0,0,0}, /* 0x74 */ {0,0,0,0,0,0,0,0},
    /* 0x75 */ {0,0,0,0,0,0,0,0}, /* 0x76 */ {0,0,0,0,0,0,0,0},
    /* 0x77 */ {0,0,0,0,0,0,0,0}, /* 0x78 */ {0,0,0,0,0,0,0,0},
    /* 0x79 */ {0,0,0,0,0,0,0,0}, /* 0x7A */ {0,0,0,0,0,0,0,0},
    /* 0x7B */ {0,0,0,0,0,0,0,0}, /* 0x7C */ {0,0,0,0,0,0,0,0},
    /* 0x7D */ {0,0,0,0,0,0,0,0}, /* 0x7E */ {0,0,0,0,0,0,0,0},
    /* 0x7F */ {0,0,0,0,0,0,0,0},
};

// ARGB color constants (top byte is alpha-ignored by the present path).
constexpr std::uint32_t kColorPanel  = 0xFF101820u;  // dark navy
constexpr std::uint32_t kColorBorder = 0xFFFFFFFFu;  // white
constexpr std::uint32_t kColorText   = 0xFFFFFFFFu;  // white
constexpr std::uint32_t kColorDim    = 0xFF808080u;  // gray
constexpr std::uint32_t kColorAccent = 0xFF40D040u;  // green (selected)
constexpr std::uint32_t kColorFrozen = 0xFFFFA040u;  // orange (frozen)

inline void put_pixel(std::uint32_t* fb, int w, int h, int x, int y,
                      std::uint32_t color) {
    if (x < 0 || x >= w || y < 0 || y >= h) return;
    fb[y * w + x] = color;
}

void fill_rect(std::uint32_t* fb, int w, int h, int x, int y,
               int rw, int rh, std::uint32_t color) {
    for (int j = 0; j < rh; ++j) {
        for (int i = 0; i < rw; ++i) {
            put_pixel(fb, w, h, x + i, y + j, color);
        }
    }
}

void stroke_rect(std::uint32_t* fb, int w, int h, int x, int y,
                 int rw, int rh, std::uint32_t color) {
    for (int i = 0; i < rw; ++i) {
        put_pixel(fb, w, h, x + i, y, color);
        put_pixel(fb, w, h, x + i, y + rh - 1, color);
    }
    for (int j = 0; j < rh; ++j) {
        put_pixel(fb, w, h, x, y + j, color);
        put_pixel(fb, w, h, x + rw - 1, y + j, color);
    }
}

void draw_char(std::uint32_t* fb, int w, int h, int x, int y,
               char c, std::uint32_t color) {
    int idx = static_cast<unsigned char>(c) - 0x20;
    if (idx < 0 || idx >= 96) return;
    const std::uint8_t* g = FONT[idx];
    for (int row = 0; row < 7; ++row) {
        std::uint8_t b = g[row];
        for (int col = 0; col < 5; ++col) {
            if (b & (0x80 >> col)) {
                put_pixel(fb, w, h, x + col, y + row, color);
            }
        }
    }
}

void draw_string(std::uint32_t* fb, int w, int h, int x, int y,
                 const char* s, std::uint32_t color) {
    for (int i = 0; s[i]; ++i) {
        // Uppercase pass: simple A-Z mapping for any lowercase that
        // slips in. Avoids needing lowercase glyphs in the font table.
        char c = s[i];
        if (c >= 'a' && c <= 'z') c = static_cast<char>(c - 'a' + 'A');
        draw_char(fb, w, h, x + i * kCellW, y, c, color);
    }
}

}  // anonymous namespace

// ---- TrainerUI helpers ----------------------------------------------------

std::uint16_t TrainerUI::slot_addr(int slot) const {
    switch (slot) {
        case kSlotX:       return ram::Player_X_Position;
        case kSlotY:       return ram::Player_Y_Position;
        case kSlotPage:    return ram::Player_PageLoc;
        case kSlotPower:   return ram::PlayerStatus;
        case kSlotPhysics: return ram::Player_State;
        case kSlotFacing:  return ram::PlayerFacingDir;
    }
    return 0;
}

std::uint8_t TrainerUI::slot_current_raw(int slot) const {
    return game_.state().read8(slot_addr(slot));
}

bool TrainerUI::slot_is_frozen(int slot) const {
    return game_.trainer().is_frozen(slot_addr(slot));
}

const char* TrainerUI::slot_label(int slot) const {
    switch (slot) {
        case kSlotX:       return "MARIO.X";
        case kSlotY:       return "MARIO.Y";
        case kSlotPage:    return "MARIO.PAGE";
        case kSlotPower:   return "MARIO.POWER";
        case kSlotPhysics: return "MARIO.PHYS";
        case kSlotFacing:  return "MARIO.FACE";
    }
    return "?";
}

void TrainerUI::format_slot_value(int slot, std::uint8_t val,
                                   char* out, std::size_t out_sz) const {
    if (slot == kSlotPower) {
        const char* n = (val == 0) ? "SMALL" : (val == 1) ? "BIG"
                       : (val == 2) ? "FIRE" : "??";
        std::snprintf(out, out_sz, "%3u %s", val, n);
    } else if (slot == kSlotFacing) {
        const char* n = (val == 0) ? "NONE" : (val == 1) ? "RIGHT"
                       : (val == 2) ? "LEFT" : "??";
        std::snprintf(out, out_sz, "%3u %s", val, n);
    } else {
        std::snprintf(out, out_sz, "%3u", val);
    }
}

void TrainerUI::on_open() {
    // Initialize edit buffers from current RAM values so left/right
    // start adjusting from the live state.
    for (int i = 0; i < kSlotCount; ++i) {
        edit_value_[i] = slot_current_raw(i);
    }
}

// ---- Input tick ------------------------------------------------------------

namespace {
// Key index slots in TrainerUI::key_prev_.
constexpr int kKeyF8        = 0;
constexpr int kKeyEsc       = 1;
constexpr int kKeyUp        = 2;
constexpr int kKeyDown      = 3;
constexpr int kKeyLeft      = 4;
constexpr int kKeyRight     = 5;
constexpr int kKeyEnter     = 6;
constexpr int kKeyBackspace = 7;

inline bool edge(const std::uint8_t* keys, SDL_Scancode sc, bool& prev) {
    bool now = keys[sc] != 0;
    bool e = now && !prev;
    prev = now;
    return e;
}
}  // anonymous namespace

void TrainerUI::tick() {
    const std::uint8_t* keys = SDL_GetKeyboardState(nullptr);
    if (!keys) return;

    if (edge(keys, SDL_SCANCODE_F8, key_prev_[kKeyF8])) {
        visible_ = !visible_;
        if (visible_) on_open();
    }
    if (!visible_) {
        // While invisible, still flush other key edge state so a held
        // arrow key from the game doesn't trigger on the first frame
        // the overlay opens.
        (void)edge(keys, SDL_SCANCODE_ESCAPE, key_prev_[kKeyEsc]);
        (void)edge(keys, SDL_SCANCODE_UP,     key_prev_[kKeyUp]);
        (void)edge(keys, SDL_SCANCODE_DOWN,   key_prev_[kKeyDown]);
        (void)edge(keys, SDL_SCANCODE_LEFT,   key_prev_[kKeyLeft]);
        (void)edge(keys, SDL_SCANCODE_RIGHT,  key_prev_[kKeyRight]);
        (void)edge(keys, SDL_SCANCODE_RETURN, key_prev_[kKeyEnter]);
        (void)edge(keys, SDL_SCANCODE_BACKSPACE, key_prev_[kKeyBackspace]);
        return;
    }

    if (edge(keys, SDL_SCANCODE_ESCAPE, key_prev_[kKeyEsc])) {
        visible_ = false;
        return;
    }
    if (edge(keys, SDL_SCANCODE_UP, key_prev_[kKeyUp])) {
        selected_ = (selected_ - 1 + kSlotCount) % kSlotCount;
    }
    if (edge(keys, SDL_SCANCODE_DOWN, key_prev_[kKeyDown])) {
        selected_ = (selected_ + 1) % kSlotCount;
    }
    if (edge(keys, SDL_SCANCODE_LEFT, key_prev_[kKeyLeft])) {
        edit_value_[selected_] = static_cast<std::uint8_t>(edit_value_[selected_] - 1);
    }
    if (edge(keys, SDL_SCANCODE_RIGHT, key_prev_[kKeyRight])) {
        edit_value_[selected_] = static_cast<std::uint8_t>(edit_value_[selected_] + 1);
    }
    if (edge(keys, SDL_SCANCODE_RETURN, key_prev_[kKeyEnter])) {
        // Freeze selected slot at the current edit_value_.
        game_.trainer().freeze(slot_addr(selected_), edit_value_[selected_]);
    }
    if (edge(keys, SDL_SCANCODE_BACKSPACE, key_prev_[kKeyBackspace])) {
        game_.trainer().thaw(slot_addr(selected_));
    }
}

// ---- Render ---------------------------------------------------------------

void TrainerUI::render(std::uint32_t* fb, int width, int height) const {
    if (!visible_ || !fb) return;

    // Panel: centered-ish, leaves room for HUD.
    constexpr int panel_x = 16;
    constexpr int panel_y = 24;
    constexpr int panel_w = 224;
    constexpr int panel_h = 168;

    fill_rect(fb, width, height, panel_x, panel_y, panel_w, panel_h, kColorPanel);
    stroke_rect(fb, width, height, panel_x, panel_y, panel_w, panel_h, kColorBorder);

    // Title bar.
    fill_rect(fb, width, height, panel_x + 1, panel_y + 1, panel_w - 2, 11,
              0xFF202830u);
    draw_string(fb, width, height, panel_x + 6, panel_y + 3,
                "SEMCOMP TRAINER", kColorText);
    draw_string(fb, width, height, panel_x + panel_w - 60, panel_y + 3,
                "F8 CLOSE", kColorDim);

    // Slot rows.
    constexpr int row_h    = 12;
    constexpr int rows_y0  = 38;
    for (int i = 0; i < kSlotCount; ++i) {
        int y = rows_y0 + i * row_h;
        std::uint32_t fg = (i == selected_) ? kColorAccent : kColorText;

        // Selection marker.
        if (i == selected_) {
            draw_string(fb, width, height, panel_x + 4, y, ">", kColorAccent);
        }

        draw_string(fb, width, height, panel_x + 12, y, slot_label(i), fg);

        // Live raw value.
        char buf[32];
        std::uint8_t raw  = slot_current_raw(i);
        std::uint8_t edit = edit_value_[i];
        format_slot_value(i, raw, buf, sizeof(buf));
        draw_string(fb, width, height, panel_x + 80, y, "=", fg);
        draw_string(fb, width, height, panel_x + 88, y, buf, fg);

        // Edit-buffer value (if it differs from live raw, show in brackets).
        if (edit != raw) {
            char ebuf[16];
            std::snprintf(ebuf, sizeof(ebuf), "[%u]", edit);
            draw_string(fb, width, height, panel_x + 150, y, ebuf, kColorDim);
        }

        // Frozen marker.
        if (slot_is_frozen(i)) {
            draw_string(fb, width, height, panel_x + panel_w - 30, y,
                        "FROZE", kColorFrozen);
        }
    }

    // Controls hint.
    int hint_y = panel_y + panel_h - 28;
    draw_string(fb, width, height, panel_x + 4, hint_y,
                "UP DN  SELECT", kColorDim);
    draw_string(fb, width, height, panel_x + 4, hint_y + 9,
                "LF RT  -1 +1", kColorDim);
    int hint2_x = panel_x + 120;
    draw_string(fb, width, height, hint2_x, hint_y,
                "ENT  FREEZE", kColorDim);
    draw_string(fb, width, height, hint2_x, hint_y + 9,
                "BSP  THAW", kColorDim);
}

}  // namespace smb::semcomp
