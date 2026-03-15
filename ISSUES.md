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

**Status:** OPEN

### Symptom
When Mario dies and play switches to Luigi, Luigi cannot move.

### Likely causes (two candidates — check the simple one first)

**Candidate A — No player 2 controller bound (likely):**
The runner currently only implements controller 1 (`$4016`). Controller 2 (`$4017`)
always returns `$40` (no buttons pressed). In 2-player alternating mode SMB reads
controller 2 for Luigi's input. If that's the case this is a one-liner fix: map
keyboard or a second button layout to `g_controller2_buttons` and wire it into the
`$4017` read in `runtime.c`.

**Candidate B — Player 2 init bug:**
If the game's player-2 initialization routine has a dispatch miss or uninitialized
state, Luigi may be stuck regardless of controller input.

### Next steps
1. Check `runtime.c` `$4017` handler — confirm it always returns `$40` (no buttons)
2. Add a temporary second controller binding (e.g. WASD + numpad) and test
3. Only if Luigi still can't move after binding → Ghidra the player-switch routine

---

## ISSUE #7 — World 1-2 causes random game over / warp pipe crash

**Status:** OPEN

### Symptom
Entering world 1-2 sometimes causes an immediate game over or a crash. Suspected to
be related to the underground secret warp pipes (world 1-2 contains pipes that warp
to worlds 2, 3, 4).

### Likely cause
The warp pipe mechanic likely triggers a different code path for pipe-entry vs. normal
pipe traversal. If the warp zone entity or the screen-transition routine has a dispatch
miss, the game may jump to an invalid address or corrupt Mario's world/level state,
causing an immediate game over.

### Next steps
- Check for `[Dispatch] MISS` or `[Dispatch] INLINE MISS` when entering the warp pipes
- Ghidra the pipe-entry and world-transition routines
- Verify `g_miss_count_any` is zero through a clean 1-2 run

---

## ISSUE #8 — Residual HUD flicker / occasional missing HUD frame

**Status:** OPEN

### Symptom
Despite the three-part fix in Issue #3, the HUD still occasionally flickers or
disappears for a frame during gameplay. Much less frequent than before (was every
few frames, now rare) but still noticeable.

### Likely cause
The sprite-0 counter-based simulation still has timing edge cases:
- The counter threshold (3 reads) may not align with the game's actual spin-wait
  pattern on every frame — interruptions from subroutine calls between Phase 1 and
  Phase 2 of the sprite-0 wait (`JSR $8223`, `JSR $81C6`) may read `$2002` and
  disrupt the counter cycle
- The renderer fallback uses OAM[0] Y to decide the split; if OAM[0] is briefly
  hidden (`Y=$EF`) during a transition frame, the fallback doesn't activate
- The pre-captured `g_ppuctrl_hud` value is set at VBlank start (before NMI writes
  `$2000` for the HUD nametable), so it may have stale nametable bits from the
  previous frame's gameplay PPUCTRL

### Next steps
- Add per-frame debug logging of `g_spr0_split_active`, `g_ppuctrl_hud`, OAM[0] Y,
  and `g_ppuscroll_x_hud` to identify which value is wrong on flicker frames
- Consider replacing the counter-based sim entirely with a scanline-timing model:
  set sprite-0 hit flag after a fixed number of memory accesses post-VBlank
  (approximating the real scanline at which sprite 0 overlaps BG)
- Compare PPU trace CSV against Mesen's PPU register writes frame-by-frame

---

## ISSUE #9 — Title screen artifacts and split-line glitch

**Status:** OPEN

### Symptom
1. A horizontal line artifact (single scanline, wrong color/tile data) appears at the
   sprite-0 split boundary — visible as a thin line just below the HUD during gameplay
   and just below the HUD on the title screen
2. On the title screen, the top portion of the "SUPER MARIO BROS." brown curtain area
   shows a brief artifact/corruption that persists for several frames before clearing
3. A stray `?` block sprite appears on the right side of the title screen (it shouldn't
   be visible during the title screen)

### Likely cause
**Split-line artifact:** The split boundary at `split_y = OAM[0].Y + 9` may be off by
one scanline. The renderer switches from HUD scroll to gameplay scroll at exactly that
row — if the boundary is wrong, one row gets rendered with the wrong scroll source,
producing a visible seam.

**Title screen corruption:** During the title-to-gameplay or gameplay-to-title
transition, nametable data is being updated over multiple frames. The renderer may
capture a partially-updated nametable, showing stale tiles from the previous screen
state mixed with new ones.

**Stray ? block sprite:** Sprite OAM may not be fully cleared during transitions. If
the game expects OAM to be DMA'd fresh each frame but a transition frame skips the
DMA, stale sprite data from the previous state (gameplay ? blocks) remains visible.

### Next steps
- Check the exact `split_y` value: compare OAM[0] Y against Mesen to see if +9 is
  the right offset for SMB (Faxanadu uses +9, SMB may differ)
- Check if the artifact line is always at the same Y position or varies
- For the stray ? block: dump OAM slot data on the title screen and compare against
  Mesen — check if OAM should be blanked during the transition
- For the title corruption: check if the nametable content at the artifact location
  matches expected tiles or contains stale data from the gameplay screen

---

## ROM / config facts
- SMB ROM: `F:/Projects/nesrecomp/Super Mario Bros. (World).nes`
- Mapper 0 (NROM-256), 2 PRG banks × 16KB, 1 CHR bank × 8KB (CHR ROM, read-only)
- Ghidra server: `mcp__ghidra_smb__*` (`smb_prg.bin` loaded, base `$8000`, full 32KB)
- Runner build: `build/runner_smb/Release/NESRecompGame.exe`
- Test script: `C:/temp/smb_test.txt`
