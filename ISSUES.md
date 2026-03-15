# Super Mario Bros. — Known Issues

---

## ISSUE #1 — Black screen / CHR ROM zeroed at startup

**Status:** FIXED

**Root cause:** Two bugs combined:
1. `runtime_init()` called `memset(g_chr_ram, 0)` *after* `load_rom()` had already loaded
   the 8KB CHR ROM, destroying it.
2. SMB's RESET routine writes zeros to PPU address `$0000` (CHR space) as standard NES
   init. On hardware with CHR ROM this is a no-op, but our runtime wrote through to
   `g_chr_ram`, destroying it a second time.

**Fix:** Added `g_chr_is_rom` flag (set when `chr_banks > 0` in iNES header).
- `runtime_init()` skips `memset(g_chr_ram)` when `g_chr_is_rom` is set
- `ppu_write_reg($2007)` ignores writes to `$0000-$1FFF` when `g_chr_is_rom` is set

---

## ISSUE #2 — Background color black instead of blue

**Status:** FIXED

**Root cause:** NES PPU palette addresses `$3F10/$3F14/$3F18/$3F1C` physically mirror
`$3F00/$3F04/$3F08/$3F0C` (transparent/backdrop slots). SMB writes `$22` (blue) to
`$3F10`, which on real hardware also sets `$3F00`. Our runtime stored them separately,
so the universal background color stayed `$0F` (black).

**Fix:** In `ppu_write_reg` and `ppu_read_reg`, remap indices `$10/$14/$18/$1C` to
`$00/$04/$08/$0C` before accessing `g_ppu_pal[]`.

---

## ISSUE #3 — HUD flickers

**Status:** PARTIALLY FIXED — major flicker eliminated, residual issues remain (see #8, #9)

### Symptom
The score/lives/coins HUD at the top of the screen flickered heavily during gameplay.

### Root cause
Three problems in the sprite-0 hit simulation combined to cause the flicker:

1. **Stale scroll at VBlank start.** The NMI handler writes `$2000` (PPUCTRL) early for
   the HUD nametable but does NOT write `$2005` (PPUSCROLL) until after the sprite-0
   wait. `g_ppuscroll_x/y` retained the previous frame's gameplay scroll, so when
   sprite-0 captured HUD values, it got gameplay scroll instead of (0,0).

2. **Counter contaminated by PPU upload reads.** The NMI handler reads `$2002` to reset
   the address latch before `$2006`/`$2007` writes (standard PPU upload pattern). Each
   read incremented `g_spr0_reads_ctr`, causing premature sprite-0 triggers during PPU
   uploads — before the game had written the correct PPUCTRL for the HUD.

3. **No fallback when counter missed.** If the counter-based sprite-0 sim failed to
   trigger, `g_spr0_split_active` stayed 0 and the entire screen rendered with gameplay
   scroll, making the HUD invisible.

### Fix (three changes in `runtime.c` + `ppu_renderer.c`)
- **VBlank reset:** Reset `g_ppuscroll_x/y` to 0 and pre-capture HUD scroll values as
  (0,0) in `maybe_trigger_vblank()` before calling NMI.
- **Counter reset on PPU write:** Reset `g_spr0_reads_ctr = 0` in `ppu_write_reg()` so
  that only consecutive `$2002` reads (genuine spin-wait polls) accumulate the counter.
- **Renderer fallback:** When `g_spr0_split_active == 0` but OAM sprite 0 is on-screen
  and rendering is enabled, apply the split using the pre-captured HUD values.

---

## ISSUE #4 — Enemy hit detection unreliable

**Status:** FIXED

### Symptom
- Jumping on Goombas did not kill them (stomp phased through)
- Walking into enemies did not reliably deal damage to Mario
- The auto-play demo diverged: Mario missed the mushroom power-up because the first
  Goomba wasn't killed, causing Mario to go too far right

### Root cause
The enemy state determination function at `$D969` was missing from the dispatch table.
This function is reached exclusively via cross-function branches (`BNE`/`BEQ` from
`$D8FD`, `$D90C`, `$D911`, etc. — approximately 50 call sites). No `JSR` or `JMP`
targets `$D969` directly, so the recompiler's function finder never discovered it.

When the generated code hit `call_by_address(0xD969)`, the dispatch table had no entry,
causing `nes_log_dispatch_miss()` and a silent no-op return. The function loads entity
state from `($16,X)` and compares against values `$12, $14, $08, $33, $0C, $05, $11,
$07` — this is the core enemy behavior state machine. Without it, enemies were
effectively frozen in their initial state and collision responses were never processed.

### Fix
Added `extra_func -1 D969` to `game.cfg`. This tells the recompiler to treat `$D969`
as a function entry point in the fixed bank. After regeneration, the dispatch table
includes the function and all ~50 cross-function branch call sites resolve correctly.

Verified: zero dispatch misses in 30-second gameplay runs. Auto-play demo now shows
Mario stomping the Goomba, collecting the mushroom power-up (Big Mario), and
progressing further through World 1-1.

---

## ISSUE #5 — Items don't spawn from ? blocks

**Status:** FIXED

### Symptom
Hitting a `?` block did not spawn a mushroom, coin, or other item.

### Root cause
`function_finder.c` inline_dispatch target bank tagging was wrong for NROM-256.
When scanning the fixed bank (bank 1), `switchable_bank == fixed_bank == 1`. The
old code:
```c
int dest_bank = (dest >= 0xC000) ? fixed_bank : switchable_bank;
```
Tagged all `$8000-$BFFF` inline_dispatch targets as bank 1, generating garbage
`func_XXXX_b1` functions decoded from the wrong ROM region. The entity state machine
runs in `$C000+` with `g_current_bank=1`, so `call_by_address(0xBC60)` dispatched to
the garbage `func_BC60_b1` instead of the correct `func_BC60_b0`.

### Fix
`function_finder.c`: changed inline_dispatch bank tagging to match regular JSR logic:
```c
if (dest >= 0xC000) {
    add_function(list, dest, fixed_bank);
} else if (switchable_bank != fixed_bank) {
    add_function(list, dest, switchable_bank);
} else {
    /* Fixed bank scanning switchable region: add for all switchable banks */
    for (int _b = 0; _b < fixed_bank; _b++)
        add_function(list, dest, _b);
}
```
Mushroom now spawns and rises from `?` block correctly (verified by screenshot).

---

## ISSUE #6 — Luigi unable to move (2-player mode) *(lowest priority)*

**Status:** OPEN (by design — controller 2 not wired)

### Symptom
When Mario dies and play switches to Luigi, Luigi cannot move.

### Cause
Controller 2 (`$4017`) always returns `$40` (no buttons pressed) in `runtime.c`.
SMB reads controller 2 for Luigi's input in 2-player alternating mode. This is not
a bug — controller 2 simply hasn't been implemented yet.

### Fix (when needed)
Add `g_controller2_buttons` with a second keyboard mapping (e.g. WASD + numpad)
and wire it into the `$4017` read path in `runtime.c`, mirroring the controller 1
strobe/shift logic.

---

## ISSUE #7 — World 1-2 causes random game over / warp pipe crash

**Status:** FIXED (resolved by earlier dispatch/function-finder fixes)

---

## ISSUE #8 — Residual HUD flicker / occasional missing HUD frame

**Status:** FIXED (four-part fix across three sessions)

### Symptom
Despite the three-part fix in Issue #3, the HUD still flickered during gameplay.
The flicker began once the screen started scrolling (e.g., when Mario hits the
first ? block in the demo and the camera follows) and persisted throughout.

### Root cause (final, after Ghidra investigation)
Four separate problems combined:

**1. Blank frames during screen transitions.**
SMB temporarily disables rendering (ppumask=$06) for 6-16 frames during nametable
loads. Our renderer painted the background color on those frames, visible as
flashes on LCD. CRT persistence makes them invisible on real hardware.

**2. Split-line seam artifact.** (See Issue #9.)

**3. Sprite-0 capture picked up gameplay nametable bits (PRIMARY CAUSE).**
The NMI's upload routine at `$8EA9` calls `FUN_8eed` (`STA $2000, STA $0778`)
which writes PPUCTRL with the **gameplay** nametable select bits (bit 0-1 from
`$0778`). This happens BEFORE the sprite-0 wait. When the counter-based sim
triggered, it captured `g_ppuctrl & 0x3B` — preserving nametable bits 0-1 from
the upload context. Once scrolling began, bit 0 alternated between 0 and 1 at
256-pixel boundaries, causing the HUD to render from the wrong nametable on
alternating scroll regions.

**4. Fallback split activated when game didn't want one.**
The renderer fallback condition `(spr0_y > 0 && spr0_y < 200)` triggered even
when `$0722` (ScrollFlag) was 0, meaning the game had skipped its sprite-0 wait
entirely. During mode transitions (title→gameplay, death, etc.), OAM[0].Y was
still on-screen from the previous frame, creating unwanted splits.

### Fix (four changes across `runtime.c` + `ppu_renderer.c`)
1. **Frame retention**: Skip rendering when ppumask bits 3-4 both clear; keep
   previous framebuffer content (CRT persistence emulation).
2. **Tile-aligned split_y**: `(spr0_y + 15) & ~7` for 8px tile boundary.
3. **Capture mask fix** (`runtime.c`): Changed sprite-0 counter capture from
   `g_ppuctrl & 0x3B` to `g_ppuctrl & 0x38` — clears nametable bits 0-1,
   forcing HUD to always use nametable 0. Matches VBlank pre-capture mask.
4. **ScrollFlag guard** (`ppu_renderer.c`): Fallback split only activates when
   `g_ram[0x0722]` (ScrollFlag) is non-zero, matching the NMI's own gate at
   `$8138: LDA $0722; BEQ skip_sprite0_wait`.

---

## ISSUE #9 — Title screen artifacts and split-line glitch

**Status:** FIXED

### Symptom
1. A horizontal line artifact (single scanline, wrong color/tile data) appears at the
   sprite-0 split boundary — visible as a thin line just below the HUD during gameplay
   and just below the HUD on the title screen
2. On the title screen, the top portion of the "SUPER MARIO BROS." brown curtain area
   shows a brief artifact/corruption that persists for several frames before clearing
3. A stray `?` block sprite appears on the right side of the title screen (it shouldn't
   be visible during the title screen)

### Root cause
**Split-line artifact:** The split boundary at `split_y = OAM[0].Y + 9` was not
tile-aligned. The renderer switched from HUD scroll to gameplay scroll at a non-tile
boundary, rendering a partial tile row with the wrong scroll source. The seam was
visible as a single scanline of wrong-colored pixels.

**Title screen artifacts (2 & 3):** These were caused by the same rendering-off
blank frame issue described in Issue #8 — during title-to-gameplay and gameplay-to-title
transitions, the game disables rendering for several frames while loading nametable data.
Our renderer was painting the background color during these frames, which was briefly
visible as a flash of stale/wrong content before the correct screen appeared. The frame
retention fix (Issue #8) resolved this.

### Fix (two changes in `ppu_renderer.c`)
1. **Tile-aligned split boundary:** Changed `split_y` from `spr0_y + 9` to
   `(spr0_y + 15) & ~7`. This rounds up to the next 8-pixel tile boundary, ensuring
   the HUD/gameplay boundary always lands on a tile row edge. For SMB (OAM[0].Y=24)
   this gives split_y=32 (4 tile rows), matching the actual 4-row HUD area.

2. **Frame retention when rendering disabled:** See Issue #8 fix — prevents
   blank frames during nametable loading transitions.

3. **PPUCTRL HUD mask cleanup:** Pre-capture mask changed from `g_ppuctrl & ~0x03`
   to `g_ppuctrl & 0x38` (only rendering-relevant bits 3-5). Counter-triggered
   capture mask changed from `g_ppuctrl` to `g_ppuctrl & 0x3B` (rendering bits
   0-1,3-5). This prevents stale VRAM increment (bit 2) and NMI enable (bit 7)
   values from affecting HUD rendering.

---

## ISSUE #10 — Demo non-determinism in real-time mode

**Status:** OPEN (inconsistency on odd-numbered launches)

### Symptom
The auto-play demo on the title screen has mistimings on odd-numbered launches in
real-time (non-turbo) mode. Even-numbered launches play correctly. The divergence
manifests at the mushroom pickup: Mario either picks it up correctly (even runs) or
misses it (odd runs), causing the rest of the demo to play out wrong.

**Turbo mode is fully deterministic** — verified across multiple runs with identical
output.

### Attempt 1: High-resolution timer + frame-start anchoring

**Changes made** (`runtime.c`):
- Replaced `clock()` (15ms Windows granularity) with `QueryPerformanceCounter()`
  (microsecond precision) via `get_time_us()` helper
- Changed VBlank period from `CLOCKS_PER_SEC/60` to exact `16667us` (1/60s)
- Removed "SET #2" — the `s_last = clock()` after the NMI callback that anchored
  to frame END instead of frame START. Now anchors only to frame start.
- Turbo mode bypasses timing entirely (previously was still gated by `clock()`)

**Result:** Changed the pattern from random jitter to a **deterministic alternation**:
odd-numbered launches wrong, even-numbered launches correct. Reproducible.

### Attempt 2: First-call timer initialization

**Changes made** (`runtime.c`):
- Added `if (s_last_us == 0) s_last_us = now_us` to anchor the first VBlank to
  process start time instead of time-since-boot

**Result:** Did not fix the alternating pattern.

### Attempt 3: Operation-counting VBlank model

**Changes made** (`runtime.c`):
- Replaced wall-clock timing entirely with a deterministic operation counter
- VBlank fires every 7000 `nes_read`/`nes_write` calls (`OPS_PER_VBLANK`)
- Display pacing handled by existing SDL_Delay + VSync in the callback
- Turbo mode unchanged (fires on every call)

**Result:** Did not fix the alternating pattern. The non-determinism source is
not in `maybe_trigger_vblank()` timing — it persists even with fully deterministic
VBlank triggering.

### Current understanding
- The alternating odd/even pattern survives all three timing approaches, including
  fully deterministic operation counting. This rules out VBlank timing as the cause.
- The source of non-determinism must be elsewhere: possibly SDL initialization order,
  VSync phase alignment, `SDL_GetTicks()` residual in the callback's pacing loop,
  or some other external state that alternates between process launches.
- The mushroom pickup requires frame-precise positioning — one frame off means
  Mario's jump arc misses the mushroom.

### SMB demo mechanism
SMB stores pre-recorded controller inputs in ROM at `$D6FE+`. The demo replays these
inputs frame-by-frame during OperMode=0 (title/demo). The demo is perfectly
deterministic on real hardware and in emulators.

### Next steps (if revisited)
- Investigate SDL_Delay / VSync interaction in `nes_vblank_callback()` — the callback
  has its own wall-clock pacing (`SDL_GetTicks` + `SDL_Delay(16)`) that could cause
  frame-count drift even with deterministic VBlank triggering
- Try removing the callback's SDL_Delay entirely (rely only on VSync for pacing)
- Log `g_frame_count` at demo divergence point to confirm off-by-one theory
- Check if `SDL_RENDERER_PRESENTVSYNC` phase alignment varies between launches

---

---

# Feature Enhancements

---

## FEATURE #1 — Widescreen support (Phase 1: viewport extension)

**Status:** DONE

### What it does
Configurable widescreen rendering that extends the visible area horizontally beyond the
NES-native 256px. Supports 16:9 (427px) and 21:9 (560px) aspect ratios. The extra
pixels are filled by reading existing nametable data that wraps in the 512px nametable
space. Asymmetric split: ~1/3 extra on left, ~2/3 on right (look-ahead direction).

### Implementation
- **`nes_runtime.h`**: `AspectRatio` enum, `g_render_width`, `g_widescreen_left/right` globals
- **`runtime.c`**: `widescreen_set()` configures width/margins per aspect ratio
- **`ppu_renderer.c`**: BG loop widened (`wx = 0..g_render_width`), sprites offset by
  `g_widescreen_left`, HUD margins blanked, edge vignette (outermost 24px)
- **`main_runner.c`**: `--widescreen 16:9|21:9` CLI arg, F8 hotkey to cycle aspect
  ratios at runtime, SDL window/texture resized dynamically, screenshot code updated

### Usage
```
SuperMarioBrosRecomp.exe <rom> --widescreen 16:9
SuperMarioBrosRecomp.exe <rom> --widescreen 21:9
# Or press F8 at runtime to cycle: 4:3 → 16:9 → 21:9 → 4:3
```

### Known limitations (Phase 1)
1. **Stale tiles at far margins.** SMB writes nametable columns ~1 column ahead of the
   camera. The far right margin reads old data that hasn't been overwritten yet, so
   tiles from earlier in the level (or the title screen) may appear at the rightmost
   edge. Phase 2 will fix this.
2. **Enemies don't spawn in the extended area.** SMB's object activation window is tied
   to a narrow horizontal range around the camera position. Enemies only appear within
   the original 256px viewport. Phase 3 will fix this.
3. **Sprites limited to 256px range.** NES OAM X coordinates are 8-bit (0-255), so game
   entities can only be drawn in the center 256px. Phase 4 will add extended sprites.

---

## FEATURE #2 — Widescreen Phase 2: Tile lookahead

**Status:** OPEN

### Goal
Hook SMB's column-writing routine from `extras.c` `game_post_nmi()` to write additional
nametable columns ahead of the camera, reducing/eliminating stale tiles in the right
margin.

### Approach
Identify SMB's column render routine (writes one 30-tile column to the nametable) and
call it repeatedly to fill columns ahead of the current scroll position. This requires
understanding SMB's `ColumnPos` / `CurrentNTAddr` variables and safely calling the
column renderer outside its normal NMI context.

---

## FEATURE #3 — Widescreen Phase 3: Extended object activation

**Status:** OPEN

### Goal
Widen SMB's enemy/object spawn threshold so entities activate when they enter the wider
viewport rather than only the 256px window.

### Approach
SMB checks if an enemy's X position is within a range of the camera's X coordinate
before activating it. Hook this check in `extras.c` to extend the activation range by
`g_widescreen_right` pixels.

---

## FEATURE #4 — Widescreen Phase 4: Extended sprites

**Status:** OPEN

### Goal
Render game entities (enemies, items, projectiles) in the widescreen margins beyond the
NES OAM 8-bit X coordinate limit (0-255).

### Approach
Create an auxiliary sprite rendering system that reads entity positions from SMB's RAM
tables (which store 16-bit positions) and renders them directly into the widescreen
framebuffer, bypassing the 256px OAM limitation.

---

## ROM / config facts
- SMB ROM: `F:/Projects/nesrecomp/Super Mario Bros. (World).nes`
- Mapper 0 (NROM-256), 2 PRG banks × 16KB, 1 CHR bank × 8KB (CHR ROM, read-only)
- Ghidra server: `mcp__ghidra_smb__*` (`smb_prg.bin` loaded, base `$8000`, full 32KB)
- Runner build: `build/runner_smb/Release/NESRecompGame.exe`
- Test script: `C:/temp/smb_test.txt`
