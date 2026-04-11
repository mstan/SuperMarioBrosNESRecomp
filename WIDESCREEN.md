# WIDESCREEN.md — SMB 512px Widescreen Enhancement

## Overview

Expand Super Mario Bros. from 256px to 512px horizontal output while
preserving correct gameplay and deterministic behavior. The center 256px
must remain identical to stock NES output at all times.

## Architecture

The nesrecomp runner already supports widescreen via three globals set in
`game_on_init()`:

```c
g_widescreen_left  = 128;   // extra pixels rendered left of column 0
g_widescreen_right = 128;   // extra pixels rendered right of column 255
g_render_width     = 512;   // total output width
```

The PPU renderer (`ppu_renderer.c`) iterates
`sx = -g_widescreen_left .. 255 + g_widescreen_right` per scanline,
using 9-bit horizontal wrap (`(origin_x + sx) & 0x1FF`) to address the
512px virtual nametable space. Sprites are offset by `g_widescreen_left`.

SMB uses **vertical mirroring** (mirror mode 2): two physical nametables
side by side = 512px of addressable BG tile data.

## The Stale Tile Problem

### Root Cause

SMB writes new nametable columns just ahead of the scroll position. On a
real NES at 256px, the write-ahead is always off-screen — invisible to the
player. The game writes ~2 metatile columns (32px) per frame, maintaining
a write-head approximately **98-117px ahead** of the 256px right edge.

At 512px, our right edge extends **128px** further right. This exposes a
**~11-30px (2-4 tile) stale band** at the far right where the nametable
contains leftover data from the previous scroll cycle.

### Empirical Measurement

Using the ring buffer to diff nametable snapshots during the attract demo:

```
Game write-ahead past 256px right edge: +98 to +117px
Our widescreen right edge:              +128px past 256px edge
Stale band:                             11-30px (2-4 tiles)
Stale band frequency:                   80% of column-write frames
```

The stale tiles look like real level content (pipes, bricks, ground) but
are from a previous scroll position. This is visually confusing.

### Identical Problem on the Left

The left side has the same issue in reverse: the game overwrites columns
that have scrolled off the left edge of the 256px viewport. At 512px, our
left extension shows ~128px of "behind" content. Some of this may also be
stale if the game has already started writing new data for the next scroll
cycle into those columns.

In practice, the left side is less noticeable because the player is moving
rightward and the "behind" content was recently valid. The right side is
worse because it shows **future** content that hasn't been written yet.

## Solutions

### Option 1: Renderer Mask (simplest, renderer-only)

Fade, darken, or blank the rightmost ~32px of the widescreen viewport.

**Pros:** Zero gameplay risk. Renderer-only change. Trivial to implement.
**Cons:** Wastes 4 tiles of viewport. Looks like a visual hack. Doesn't
solve the problem — just hides it.

**Implementation:** In `game_post_render()`, darken pixels in the rightmost
32px band of the framebuffer.

### Option 2: Reduce Extension (conservative)

Use `g_widescreen_right = 96` instead of 128, keeping the right edge within
the game's natural write-ahead distance.

**Pros:** Zero stale tiles. No gameplay changes. Simple.
**Cons:** Asymmetric viewport (128 left, 96 right = 480px total). Loses
32px of legitimate visible area. Doesn't fix the underlying issue.

### Option 3: Extend Column Writer (correct fix) ← CHOSEN

Hook SMB's column writing system to write additional columns further ahead,
filling the stale band with real level data.

**Pros:** Full 512px of correct data. No visual hacks. The "real" fix.
**Cons:** Requires understanding and hooking the column writer. Touches
gameplay-adjacent logic (level data decoding). Must not affect the center
256px or game state.

**Approach:**
1. Identify SMB's column writer functions (ColumnSet, DrawNewColumn, etc.)
2. After the game writes its normal columns, run the writer again for
   additional columns further ahead
3. The extra writes must use the same level data decoder so the content
   is correct
4. The extra writes must not advance any game state (enemy spawns, etc.)
5. Only the nametable write is needed — no attribute table or collision

**Key constraint:** The column writer must be called with a future column
position but must not trigger side effects (enemy spawns, powerup spawns,
area transitions). This may require shadowing the column position state
and restoring it after the extra writes.

### Option 4: BG Runahead (nuclear option)

Run the entire game N frames ahead in a shadow state to populate the
nametable with future content.

**Pros:** Perfectly correct for all subsystems (BG, sprites, entities).
**Cons:** Extremely complex. Doubles CPU cost. State management nightmare.
Prior attempts at this approach failed (see project history).

**Status:** Not recommended unless Option 3 proves insufficient.

## Decision: Option 2 (reduced right extension) for Phase 2

Option 3 (extend column writer) was attempted but proved too fragile:
- Bumping AreaParserTaskNum ($071E) disrupted the game's internal state
  machine, causing crashes and gameplay corruption
- Blanking stale columns with sky tiles looked jarring (ground abruptly
  becomes sky at the blank boundary, HUD corruption)
- A true level data decoder (re-implementing SMB's area parser to write
  future columns) is a large reverse engineering project

Option 2 (reduced right extension) eliminates the problem entirely:
- `g_widescreen_right = 96` stays within the game's proven 98-117px
  write-ahead distance
- Zero stale tiles, zero gameplay side effects, zero hacks
- Total viewport: 480px (128 left + 256 center + 96 right)
- The 32px asymmetry is barely noticeable in practice

Option 3 remains available as a future enhancement if 480px is insufficient.

## Current State

- **Phase 1 complete:** Widescreen renderer working. Center 256px preserved.
  Smooth scrolling. 9-bit wrap correct. Sprites positioned correctly.
- **Phase 2 complete:** Stale band identified (2-4 tiles on right side).
  Right extension reduced to 96px to stay within write-ahead distance.
  480px total viewport, zero stale tiles.
- **Phase 3 pending:** Entity/lifecycle assumption mapping.

## Files Modified

| File | Change |
|------|--------|
| `extras.c` | `game_on_init()`: set widescreen globals (128L + 96R = 480px) |

## Key SMB RAM Addresses (Column Writer)

| Address | Name | Purpose |
|---------|------|---------|
| 0x06A0 | ColumnPos | Current metatile column position |
| 0x0726 | CurrentPageLoc | Current page (which 256px nametable) |
| 0x071A | ScreenLeft_X_Pos | Left edge of screen (lo byte) |
| 0x071C | ScreenLeft_PageLoc | Left edge of screen (page) |
| 0x0300-0x03FF | VRAM_Buffer1 | Column data buffer for NMI transfer |

These addresses need Ghidra verification before hooking.
