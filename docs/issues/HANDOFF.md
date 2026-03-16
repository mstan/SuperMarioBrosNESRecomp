# Handoff Prompt — Widescreen Sprite Despawn Issue

Copy-paste this to start a new session:

---

I'm working on widescreen support for a Super Mario Bros NES static recompilation
(6502→C). The project is at `F:\Projects\nesrecomp projects\SuperMarioBrosRecomp`
on branch `feature/widescreen`.

## Context

We have a working 16:9 widescreen mode that:
- Extends the viewport left (look-back via g_shadow_nt from passed nametable data)
- Extends the viewport right (runahead: runs the area parser ahead for right-margin tiles)
- Shows enemy sprites in the right margin (sprite runahead: saves all state, shifts
  camera +256px via ScreenLeft_PageLoc++, runs full game engine `func_8212_b0`,
  captures OAM as `g_ppu_oam_ext`, restores all state)
- Ghost Mario removal is working (committed, uses runahead-state X matching with
  uint8_t circular distance)

Key files:
- `extras.c` — game-specific hooks including `runahead_sprites()` and `runahead_widescreen()`
- `nesrecomp/runner/src/runtime.c` — widescreen state, PPU abstraction
- `nesrecomp/runner/src/ppu_renderer.c` — renders extended OAM sprites in margins
- `nesrecomp/runner/include/nes_runtime.h` — shared state declarations
- `game_ram_read_hook()` in extras.c — currently disabled, was an attempt to extend
  enemy spawn range

## Current Issue: Piranha plant despawns in widescreen margin

Read `docs/issues/WIDESCREEN_ISSUES.md` for full details with screenshots.

**Summary:** Enemies (piranha plants confirmed, likely all enemies) visible in the
16:9 right margin via sprite runahead will HALF-RENDER then fully DISAPPEAR as
Mario approaches them. Once despawned, they never re-render even if Mario steps back.
The game's own off-screen enemy culling (designed for 4:3) deactivates enemies at
the 4:3 viewport boundary, which is INSIDE the 16:9 widescreen margin.

The sprite runahead captures extended OAM from a +256px camera shift. But it starts
from the REAL frame's RAM — if the real frame already deactivated an enemy, the
runahead won't render it either.

**Key code to investigate:**
- `CheckRightBounds` around NES $C164 — enemy spawn/despawn threshold
- $D69A/$D6A1 — 72px enemy activation check (DO NOT extend this carelessly —
  it was tried before and caused 8-bit X wrapping and reversed enemy movement)
- Enemy state arrays: $001E-$0023 (Enemy_Flag), $0016-$001B (Enemy_ID)
- `game_ram_read_hook()` in extras.c — PC-gated RAM value adjustment, currently
  disabled with a comment explaining why

**The core constraint:** NES sprites use 8-bit X (0-255). Enemies at X>255 from
ScreenLeft can't be positioned in OAM. The sprite runahead avoids this by shifting
the camera, but the real frame's game logic still culls at 4:3 boundaries.

**Possible fix directions:**
1. Hook the enemy off-screen check to widen the "keep active" zone
2. Prevent real-frame deactivation of enemies visible in widescreen margin
3. Save/restore enemy activation state around the runahead boundary

Use Ghidra (MCP server connected as `ghidra_smb`, binary `smb_prg.bin`) to
investigate the enemy lifecycle and off-screen checks.
