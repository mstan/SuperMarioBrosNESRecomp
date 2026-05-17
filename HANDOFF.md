# SESSION HANDOFF — SMB WIDESCREEN (SPRITE EXTENSION PHASE)

Branch: `feature/widescreen-2026-04-11`  
Commit: `16c8169` (wip: disable broken sprite wide_x computation)

---

## WHAT WORKS

- **BG rendering**: 480px (128L + 256C + 96R), nametable wrap correct, HUD/scrolling/sprite-0 split all good
- **Symbol names**: nesrecomp merged PR #2 — `.sym` file → inline comments + `#define` aliases in generated code. Pin updated to `9bf5197`.
- **Despawn hooks** (extras.c `game_ram_read_hook`): `ram_read_hook` entries in game.toml for $071A-$071D. At PCs $D680/$D693/$D69A/$D6A1, widens the OffscreenBoundsCheck boundaries by `g_widescreen_left`/`g_widescreen_right`. Enemies survive longer in the extension regions.
- **Offscreen bits hook** (extras.c `offscreen_bits_hook`): write_bp on $03D1 intercepts Enemy_OffscreenBits. Clears bits when any enemy is in the widescreen extension, so the game's sprite drawing code writes them to OAM instead of skipping them.
- **g_oam_wide_x[64]** renderer infrastructure: declared in `nes_runtime.h`, stored in `main_runner.c`, initialized to -1 each frame before `game_post_nmi`. Renderer in `ppu_renderer.c` checks: if `g_oam_wide_x[s] >= 0`, use it as sprite screen X instead of 8-bit OAM X. **Verified working** — forcing all 64 entries to 128 clusters every sprite at center screen.

---

## WHAT DOESN'T WORK

### The sprite positioning problem

Enemies past the 4:3 right edge (screen_x > 255) get their OAM X wrapped to 0-7 by the game's 8-bit math. They appear as ghosts near the LEFT of the viewport instead of in the right extension region.

The `g_oam_wide_x` infrastructure exists to fix this, but `compute_widescreen_sprite_x()` is **disabled** because every attempt to fill it caused flickering or ghost duplicates.

### Failed approaches to filling g_oam_wide_x

1. **OAM X unwrap** (try oam_x+256 / oam_x-256): Fundamentally ambiguous — can't tell if OAM X=44 means screen position 44 or 300. Creates ghost duplicates.

2. **World-position computation for extension-only sprites** (`screen_x >= 256`): Correctly identifies enemies in extension, but OAM slot mapping via `Enemy_SprDataOffset` ($06E5+i) is unreliable:
   - The offset might not align with actual OAM slots used
   - Tagging 2 consecutive OAM slots hits adjacent enemy/HUD sprites
   - Base OAM X delta computation (`dx = oam_x - base_oam_x`) produces wrong values when the base itself is wrapped

3. **World-position computation for ALL enemy sprites**: Same OAM mapping problems, now affecting every enemy every frame → constant flickering.

### Root cause analysis

The core difficulty: **mapping enemy game-logic slots to OAM sprite slots is not straightforward.** The game's sprite drawing code uses `Enemy_SprDataOffset` as a starting OAM byte offset, but:
- Different enemy types use different numbers of OAM entries (Goomba=2, Koopa=2-4, multi-segment enemies vary)
- The game may reorder OAM entries frame-to-frame for sprite priority rotation
- HUD, powerup, and effect sprites share the same OAM space
- Reading stale OAM data after offscreen-bits clearing leads to wrong slot identification

---

## WHAT TO TRY NEXT

### Option A: Hook the sprite X WRITE, not the READ

Instead of reverse-mapping OAM slots from enemy data, intercept the moment the game WRITES sprite X to OAM RAM ($0200-$02FF). At that point, the game knows exactly which sprite it's drawing. The write address tells us the OAM slot, and we can compute the correct wide X from the current enemy's world position.

Implementation:
- The game writes OAM data to `g_ram[$0200+offset]` via `nes_write`
- Add a write hook (or range hook) on `$0200-$02FF` that fires when byte offset % 4 == 3 (the X byte)
- At that moment, `g_cpu.X` or the current enemy slot index is likely in a register or temp variable — read it to identify which enemy this is
- Compute `wide_x = enemy_world_x - cam_x` and store in `g_oam_wide_x[oam_slot]`

Challenge: the write_bp system only supports ONE address. Would need to extend it to support a range, or add a second mechanism.

### Option B: Hook the offscreen bits computation differently

The offscreen bits computation at `func_F1F6` ($F1F6) reads `$071C+Y` and `$071A+Y` with INDEXED addressing (LDA $071C,Y). The `ram_read_hook` system only hooks ABSOLUTE addressing, not indexed. If we extended the recompiler to also hook indexed absolute reads for hooked addresses, we could widen the offscreen comparison directly. The game would then naturally write correct OAM data for extension-region sprites.

### Option C: Replace the enemy sprite drawing routine entirely

Use `game_dispatch_override` or a `replace_func` in game.toml to replace the SMB sprite drawing function with a C reimplementation that natively supports widescreen coordinates. This is the most robust but most work-intensive approach.

### Option D: Per-frame RAM patching of OAM X

In `game_post_nmi`, after OAM DMA, directly rewrite `g_ppu_oam[slot*4+3]` for sprites whose X is clearly wrong (wrapped). Use a heuristic: if an active enemy's computed screen_x is in [256, 352] and its OAM X is in [0, 96], it's wrapped — write the correct wide X. This avoids the slot-mapping problem by operating on the OAM data directly.

But still needs the `g_oam_wide_x` path for the renderer to draw beyond 255.

---

## KEY FILES

| File | Purpose |
|------|---------|
| `extras.c` | Game hooks: ram_read_hook, offscreen_bits_hook, compute_widescreen_sprite_x (disabled) |
| `game.toml` | ram_read_hook entries for $071A-$071D, symbol_file |
| `symbols.sym` | 81 SMB address labels for codegen readability |
| `nesrecomp/runner/include/nes_runtime.h` | `g_oam_wide_x[64]` extern declaration |
| `nesrecomp/runner/src/main_runner.c` | `g_oam_wide_x` storage + per-frame -1 init |
| `nesrecomp/runner/src/ppu_renderer.c` | Sprite rendering with wide_x override (lines 531-533, 572-575) |
| `generated/super-mario-bros_full.c` | Regenerated with ram_read_hooks + symbol comments |

## KEY RAM ADDRESSES (SMB)

| Address | Symbol | Purpose |
|---------|--------|---------|
| $000F+i | Enemy_Flag | 5 enemy slots, 0=inactive |
| $0016+i | Enemy_ID | Enemy type |
| $006D | Player_PageLoc | Player 256px page |
| $006E+i | Enemy_PageLoc | Enemy 256px page |
| $0086 | Player_X_Position | Player X within page |
| $0087+i | Enemy_X_Position | Enemy X within page |
| $071A | ScreenLeft_PageLoc | Camera left edge page |
| $071C | ScreenLeft_X_Pos | Camera left edge X |
| $071B | ScreenRight_PageLoc | Camera right edge page |
| $071D | ScreenRight_X_Pos | Camera right edge X |
| $03D1 | Enemy_OffscreenBits | Bitfield controlling sprite visibility |
| $06E5+i | Enemy_SprDataOffset | OAM byte offset for enemy sprites |
| $06EC | Player_SprDataOffset | OAM byte offset for player sprites |

## KEY PCS (from lifecycle analysis)

| PC | Function | Classification |
|----|----------|---------------|
| $C164 | CalcSpawnLookahead | DO NOT HOOK — causes enemies to start AI too early |
| $D67A | OffscreenBoundsCheck | Entity lifecycle despawn check |
| $D680 | OffscreenCalcLeftBound | SAFE threshold (hooked) |
| $D69A | OffscreenCalcRightBound | SAFE threshold (hooked) |
| $C998 | EraseEnemyObject | Zeros Enemy_Flag + related fields |
| $F1D1 | WriteOffscreenBits | Writes $03D1 (hooked via write_bp) |
| $F1F6 | CheckOffscreenBits | Uses INDEXED read of $071C+Y — not hookable by current ram_read_hook |

## BUILD

```batch
# Full rebuild (recompiler + regen + game):
build_all.bat

# Game only (after extras.c changes):
rebuild.bat

# If submodule files changed (nes_runtime.h, ppu_renderer.c, main_runner.c):
# Must delete build/ and use build.bat, OR manually delete stale .obj files.
# Ninja doesn't detect submodule working-tree changes reliably.
```

## CONSTRAINTS

- DO NOT modify `generated/*.c` directly
- DO NOT hook spawn lookahead ($C164) — spawning enemies early breaks positioning
- nesrecomp renderer changes must be backward-compatible (g_oam_wide_x defaults to -1 = authentic)
- Game-specific logic stays in extras.c, generic infrastructure in nesrecomp
