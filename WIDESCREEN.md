# Widescreen Strategy — Super Mario Bros. Recomp

## Approach: Extend the PPU, not the game

Modeled after [snesrev/zelda3](https://github.com/snesrev/zelda3)'s widescreen implementation.
The game's 6502 code runs unmodified. We extend the hardware abstraction layer so it
naturally handles a wider viewport. Game-specific fixups live in `extras.c` behind an
opt-in flag.

**Core principle**: The NES PPU is emulated in C (`ppu_renderer.c`, `runtime.c`).
We control it completely. We can give the game a wider nametable, wider sprite
coordinates, and wider clipping bounds — the game's own logic then fills them.

---

## Architecture

### Layer 1: PPU Extension (nesrecomp runner, opt-in constant)

**Compile-time constant** in `nes_runtime.h`:
```c
#define NES_PPU_EXTRA_LEFT_RIGHT  96   /* 0 = authentic, 96 = 16:9 */
```

When non-zero:

| Component | Authentic (0) | Extended (96) |
|-----------|--------------|---------------|
| Nametable width | 512px (2 NTs) | 512px + extra rendering from existing NT wrapping |
| BG render loop | sx = 0..255 | sx = -extra..255+extra |
| Sprite X range | 0..255 (8-bit OAM) | Unwrap 9-bit X into extended range |
| Framebuffer | 256×240 | (256 + extra*2) × 240 |
| Priority buffers | 256 wide | Extended width |

**Key change**: The BG tile renderer already loops wider (we have this). The new
work is:
1. **Sprite X unwrapping** — NES OAM X is 8-bit (0-255). Sprites near X=0 may
   actually be at the left edge of the extended viewport. Unwrap by checking if
   the sprite's world position maps to the extended range.
2. **Wider nametable access** — The 512px nametable wraps. For margin pixels, we
   read whatever's in the NT at that wrapped position. The game already writes
   columns as it scrolls; with adjusted scroll bounds (Layer 2), it writes more.

### Layer 2: Scroll & Spawn Bound Adjustments (extras.c, per-game)

The game's own code determines:
- When to write new nametable columns (based on scroll position)
- When to spawn enemies (based on ScreenRight + lookahead)
- When to despawn enemies (off-screen checks)

We adjust these thresholds via `ram_read_hook` so the game naturally:
- **Writes more columns ahead** — by making it think the viewport is wider
- **Spawns enemies earlier** — extending CheckRightBounds
- **Despawns later** — extending off-screen right checks

The `ram_read_hook` feature in the recompiler already supports this. The hook is
specified in `game.cfg` and implemented in `extras.c`, only active when widescreen
is enabled. Vanilla builds don't use it.

**Critical**: only hook the RIGHT set of PCs. Previous attempt failed because we
hooked positioning routines ($C1B6) in addition to threshold checks ($C164). The
hooks must be carefully validated per-PC.

### Layer 3: Dynamic Per-Frame Control (extras.c)

Like zelda3's `ConfigurePpuSideSpace()`, the game can control how much extra space
to show each frame:
- Full widescreen during normal scrolling gameplay
- Reduced/zero during title screen, transitions, pipe animations
- Based on `OperMode` ($0770) and game state

```c
void game_post_nmi(uint64_t frame_count) {
    if (nes_read(0x0770) == 1) {  /* gameplay */
        ppu_set_extra_side_space(NES_PPU_EXTRA_LEFT_RIGHT, NES_PPU_EXTRA_LEFT_RIGHT);
    } else {
        ppu_set_extra_side_space(0, 0);  /* title/transitions: authentic */
    }
}
```

### Layer 4: World Scroll Clamping (already implemented)

Left margin blanked where `world_x < 0` (before level start). Already working
via `g_ws_world_scroll` tracking from SMB RAM ($071A/$071C).

---

## Implementation Plan

### Phase A: PPU Extension Infrastructure (nesrecomp runner)

Files: `nes_runtime.h`, `runtime.c`, `ppu_renderer.c`, `main_runner.c`

1. Add `NES_PPU_EXTRA_LEFT_RIGHT` constant (0 by default)
2. Add `ppu_set_extra_side_space(int left, int right)` API
3. Add `g_ppu_extra_left_cur` / `g_ppu_extra_right_cur` runtime state
4. BG renderer: use `g_ppu_extra_left_cur` / `right_cur` for loop bounds
   (replaces current `g_widescreen_left` / `right` — unify these)
5. Sprite renderer: unwrap OAM X into extended range
   - Read OAM X (8-bit), compute world X from game state
   - Map to extended framebuffer position
6. Framebuffer sized to max width: `256 + NES_PPU_EXTRA_LEFT_RIGHT * 2`
7. SDL window/texture sized to actual current width

### Phase B: Scroll Extension (SMB extras.c + ram_read_hook)

Make the game write more nametable columns ahead.

1. Identify the PC where SMB checks "should I write a new column?" — this is
   the scroll handler that compares the scroll position against the last-written
   column
2. Hook that check via `ram_read_hook` to make the game think it needs to write
   columns further ahead (by `g_ppu_extra_right_cur` pixels)
3. The game's own column-writing code runs and fills the nametable ahead
4. The renderer reads these naturally — no pre-decoded map needed

### Phase C: Enemy Spawn/Despawn Extension (SMB extras.c + ram_read_hook)

1. Re-enable CheckRightBounds hook ($C164/$C16E) — extends spawn threshold
2. Add off-screen despawn hooks (carefully, only the right PCs)
3. Validate each hooked PC against Ghidra disassembly

### Phase D: Sprite X Extension (nesrecomp runner)

Make sprites visible in the widescreen margins.

1. The NES has 8-bit OAM X (0-255). Sprites at X=0 in OAM could be at the
   left edge of the extended viewport.
2. For each sprite, compute its actual world X position:
   - World X = ScreenLeft + OAM_X (for most sprites)
   - Map to framebuffer position: fb_x = world_x - (world_scroll - extra_left)
3. Sprites that would be at fb_x < 0 or >= render_width are clipped

### Phase E: Per-Frame Dynamic Control (SMB extras.c)

1. Check OperMode ($0770) each frame
2. During title/demo/transitions: set extra side space to 0
3. During gameplay: set to full NES_PPU_EXTRA_LEFT_RIGHT
4. During pipe transitions or area changes: reduce smoothly

---

## File Ownership

| File | Changes | Repo |
|------|---------|------|
| `runner/include/nes_runtime.h` | Extra constant, side space API | nesrecomp |
| `runner/src/runtime.c` | Extra state, side space impl | nesrecomp |
| `runner/src/ppu_renderer.c` | Extended BG/sprite rendering | nesrecomp |
| `runner/src/main_runner.c` | Framebuffer sizing, F8 toggle | nesrecomp |
| `recompiler/src/code_generator.c` | ram_read_hook (already done) | nesrecomp |
| `recompiler/src/game_config.c` | ram_read_hook parsing (already done) | nesrecomp |
| `extras.c` | SMB-specific hooks, dynamic control | game repo |
| `game.cfg` | ram_read_hook directives | game repo |

**All runner changes are behind `NES_PPU_EXTRA_LEFT_RIGHT == 0` guard.**
When 0, behavior is identical to authentic. No code paths change for vanilla builds.

---

## Current Status (16:9 only — 21:9 removed)

### Done
- [x] Phase A: BG renderer widens, framebuffer resizes, F8 toggle (4:3 / 16:9)
- [x] Phase A: world scroll clamping (left margin blanked before level start)
- [x] ram_read_hook infrastructure in recompiler
- [x] 16:9 look-back working (left margin shows passed tiles correctly)
- [x] World-column tracking: PPU $2007 writes stamped with world column,
      renderer validates margin tiles, scroll discontinuity detection on area transitions
- [x] Sprite runahead: full game engine runs with camera shifted +256px, captures
      extended OAM for right-margin sprites. Ghost player removal via Y-position blanking.
- [x] Enemy despawn fix: ram_read_hook at PC=$D693/$D6A1 restores boundary pages
      during runahead — piranha plants and enemies survive in the right margin
- [x] Default to 16:9 on startup (game_on_init sets ASPECT_16_9)

### Remaining
- [ ] Phase A: sprite X unwrapping (for left-margin sprites)
- [ ] Phase A: unify widescreen state under extra_left/right API
- [ ] Phase B: right-margin tile lookahead (game needs to write more columns ahead)
- [ ] Phase C: re-enable spawn hooks with correct PC set
- [ ] Phase D: sprite world-X computation
- [ ] Phase E: dynamic per-frame control (reduce margins during transitions)

### Known Limitations
- Occasional sprite flickering at the 4:3/widescreen boundary (cosmetic only)
- Right margin tiles limited to ~16px look-ahead until Phase B is implemented
- Flagpole flag not visible in the widescreen margin (entity management issue)

---

## Failed Approaches Log

### Attempt 1: ram_read_hook for spawn thresholds (Phase C first)

**What**: Hooked `nes_read($071B)` / `nes_read($071D)` at multiple PCs to shift
ScreenRight reads, making the game spawn enemies earlier and write columns further.

**PCs hooked**: $C164, $C16E, $C1B6, $C1BB, $C5DA, $C5E2, $C73C, $C741, $D69A, $DEB3

**Result**: Enemy spawning completely broken — wrong Y positions, missing enemies,
enemies spawning at wrong locations.

**Why it failed**:
- $C1B6/$C1BB (`PositionEnemyObj`) — CMP/SBC on ScreenRight, used for screen-relative
  positioning, NOT threshold checks. Shifting these corrupts enemy X placement.
- $C5DA/$C5E2 — SETS enemy position TO ScreenRight+32. Shifting makes enemies spawn
  at wrong absolute positions.
- $C73C/$C741 — reads $071B BEFORE $071D (reversed order vs $C164/$C16E). The carry
  mechanism between page/X reads breaks when the pair order is different.
- $D69A/$DEB3 — standalone reads; carry state from other hooks leaked into them.
- Even with ONLY $C164/$C16E hooked, spawning was still broken (cause unclear —
  possibly the CheckRightBounds shift interacts badly with the game's 8-bit arithmetic
  when large offsets wrap).

**Lesson**: `ram_read_hook` is fragile for arithmetic hooks. Every call site that reads
the hooked address gets the shifted value, and many of those call sites use the value
for positioning (not thresholds). Need to validate EVERY call site that reads $071B/$071D
in the entire ROM, not just the ones we intend to hook.

### Attempt 2: Shadow area parser (Phase B, direct approach)

**What**: After the game's NMI, save all RAM + CPU state, run the area parser
(`func_92B0_b0()`) forward for N extra columns to pre-fill nametable data, parse
the resulting VRAM upload buffer at $0341, write tile data directly to `g_ppu_nt[]`,
then restore state.

**Result**: Massive nametable corruption — blue waterfall-like streaks in ground tiles,
"MARIO" corrupted to "ARI" in HUD, garbage throughout the main viewport (not just margins).

**Why it failed**:
1. **Wrong buffer**: The upload buffer at $0341 (buffer index 6) contains **attribute
   table data** (palette assignments), NOT tile data. `func_896A` computes PPU addresses
   in the $23C0-$27FF range (attribute tables) and writes palette group bytes. My parser
   interpreted these as tile IDs and wrote them to arbitrary nametable positions.
2. **Multi-frame pipeline**: SMB's column writing is split across multiple screen routine
   states over 2-3 frames:
   - State 6 (`func_86A8`): calls `func_8808` → builds **tile data** upload at $0301
   - State 7 (`func_889D`): wait for VRAM upload countdown ($07A0)
   - State 8 (`func_86E6`): runs area parser → `func_896A` builds **attribute** upload at $0341
   The shadow parser only runs state 8's portion, missing the tile data entirely.
3. **Nametable wrapping danger**: The nametable is 64 columns (512px). For 16:9 (427px
   visible = ~54 columns), only 10 columns are "safe" to write ahead without overwriting
   currently-visible data. The shadow parser didn't account for this boundary.
4. **Also removed `sx > 271` clamp** at the same time, compounding the damage — stale data
   was now visible even without the shadow parser doing anything useful.

**Lesson**: Can't capture the game's VRAM upload pipeline by parsing RAM buffers. The
pipeline is multi-frame, multi-buffer, and the buffer formats are specific to each upload
type. Need a different approach that doesn't depend on understanding the upload format.

### Attempt 3 (implemented): World-column tracking via PPU write interception

**What**: Instead of a separate tile map, replaced the broken `g_nt_generation` /
`g_nt_col_gen[64]` system with `g_nt_col_world[64]` — each nametable column stores
the **world column** it was last written for (computed from `g_ws_world_scroll` at
PPU write time). The renderer checks whether the stored world column matches the
expected world column for each margin pixel; mismatches are blanked.

**Implementation** (runtime.c `$2007` handler):
```c
int cam_wc = g_ws_world_scroll >> 3;   // camera world column
int cam_nc = cam_wc & 63;              // camera nametable column
int off = (nt_col - cam_nc + 64) & 63; // offset from camera (0-63)
g_nt_col_world[nt_col] = cam_wc + (off > 34 ? off - 64 : off);
```
Threshold 34 = viewport (32 cols) + write cursor (2 cols). Offsets 0-34 are "ahead",
35-63 are "behind" (wrapped from previous scroll cycle).

**Scroll discontinuity detection** (extras.c `game_post_nmi`): If scroll changes by
>128px in one frame, all 64 entries are invalidated to -1. Handles pipes, death, area
transitions.

**Right vignette**: Extended to cover the full right margin (85px for 16:9) with
quadratic falloff, since most of the right margin is blank.

**Result**: Left margin correctly shows passed tiles. Right margin properly blanked
with gradual vignette. No artifacts. Clean transitions. Foundation ready for Phase B.

**Remaining limitation**: Only shows tiles the game has ALREADY written. Right margin
gets ~16px of look-ahead (game's write cursor). Full right-margin look-ahead still
needs Phase B (making the game write more columns ahead).

### Attempt 4 (implemented): Runahead enemy bounds-check fix via ram_read_hook

**What**: The sprite runahead runs the full game engine with the camera shifted +256px
(one page). This shifts the enemy bounds check's left boundary by +256px, causing
enemies in the real frame's 4:3 viewport to be deactivated via JSR $C998 during the
runahead frame. Those deactivated enemies then have no OAM sprites, so the extended
OAM capture misses them. Fix: hook the specific LDA $071A at PC=$D693 (where the
bounds check computes its left boundary page) and subtract 1 during runahead to
restore the real frame's left boundary.

**Root cause analysis** (Ghidra):
- Bounds check at $D67A-$D6D5 creates keep-alive zone: ScreenLeft-72 to ScreenRight+72
- Left boundary computation: $D680 LDA $071C, $D68F SBC #$48, $D693 LDA $071A, $D696 SBC #$00
- Right boundary: $D69A LDA $071D, $D6A0 ADC #$48, $D6A3 LDA $071B, $D6A6 ADC #$00
- Deactivation at $D6D2: JSR $C998 zeros 8 enemy fields ($0F+X, $16+X, $1E+X, etc.)
- During runahead: ScreenLeft_PageLoc($071A) is incremented by 1 → left boundary shifts
  right by 256px → enemies at page 0 (real frame's viewport) fail the check → deactivated

**Implementation**:
- `game.cfg`: `ram_read_hook 071A` (plus $071B/$071C/$071D for future use)
- `extras.c` `game_ram_read_hook()`: when `g_runahead_mode && pc == 0xD693 && addr == 0x071A`,
  return `(val > 0) ? val - 1 : val`
- Only fires during runahead mode; vanilla gameplay unaffected
- The RIGHT boundary is naturally widened (ScreenRight+256+72) which is desirable —
  keeps margin enemies alive during runahead

**Result**: Piranha plants (and other enemies) remain visible in the widescreen right
margin as Mario approaches. Verified in World 1-2 with save state: piranha plant
stays rendered in the right margin without half-rendering or disappearing.

**Key insight**: Only ONE PC ($D693) needs hooking — the specific instruction where the
bounds check reads ScreenLeft_PageLoc for its left boundary computation. The hook is
PC-gated, so no other code paths reading $071A are affected.
