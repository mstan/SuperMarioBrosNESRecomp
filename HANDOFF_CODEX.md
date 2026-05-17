# CODEX HANDOFF — SMB WIDESCREEN SPRITE EXTENSION

Branch: `feature/widescreen-2026-04-11`
Commit: `d31ff04`

## THE PROBLEM

Super Mario Bros. is running as a statically recompiled native executable (6502 → C → x64).
BG rendering works at 480px (128L + 256C + 96R widescreen). Enemy sprites are NOT visible
in the widescreen extension regions. They wrap to incorrect positions in the base 4:3 viewport.

## WHAT IS PROVEN (DO NOT RE-INVESTIGATE)

All of the following were verified by frame-by-frame TCP ring buffer inspection:

1. **Enemy_SprDataOffset ($06E5+i) IS reliable.** It rotates each frame for sprite priority
   (e.g., 0xD0→0x30→0x88→repeat) but ALWAYS points to the correct first OAM byte for that enemy.

2. **Goombas use exactly 3 OAM entries** from the SprDataOffset position.

3. **OAM X = screen_x & 0xFF** — pure 8-bit truncation. An enemy at screen_x=301 has OAM X=45.

4. **The game sets OAM Y=0xF8 (hidden) for off-screen sprites.** When an enemy is beyond the
   256px viewport, the game's sprite drawing code writes Y=0xF8 to ALL its OAM slots. This
   happens DURING game logic, BEFORE our post-NMI hook runs. The game also does NOT write valid
   tile or attribute data to the OAM slots when it considers the sprite off-screen.

5. **TCP read_ram parameter is `len`, NOT `count`.** `count` silently returns 1 byte.

## ROOT CAUSE

The game's sprite drawing pipeline has TWO off-screen checks:

- **Entity lifecycle** ($D67A OffscreenBoundsCheck): determines if the enemy ENTITY stays alive.
  This is successfully hooked to widen boundaries.

- **Sprite visibility** ($F1F6 CheckOffscreenBits → $03D1 Enemy_OffscreenBits): determines
  whether to DRAW the sprite to OAM. When the enemy is past the 256px edge, the game:
  1. Sets offscreen bits in $03D1
  2. The sprite drawing code reads these bits
  3. Writes Y=0xF8 to the OAM slots (hiding them)
  4. Does NOT write valid tile/attribute/X data

  We hook the $03D1 write (via write_bp) to clear the bits, but the sprite drawing code
  has ADDITIONAL checks that bypass our hook. The $F1F6 routine uses INDEXED addressing
  (`LDA $071C,Y`) which the ram_read_hook system does NOT intercept (it only hooks
  absolute addressing `LDA $071D`).

## WHAT HAS BEEN TRIED AND FAILED

1. **OAM X unwrap heuristics** — ambiguous, creates ghost duplicates.
2. **Post-NMI g_oam_wide_x computation** — correctly identifies enemies in extension
   (proven by debug output showing sX=301,313,etc.) but:
   - OAM Y is 0xF8 (hidden) → renderer skips before reading g_oam_wide_x
   - OAM tile/attr data is STALE or MISSING → even if Y is restored, tiles are wrong
3. **Renderer fix to skip Y>=0xEF check when g_oam_wide_x set** — attempted, doesn't
   render because tile data wasn't written by the game.
4. **Restoring Y from Enemy_Y_Position** — applied but tiles/attrs are still invalid.
5. **Spawn lookahead widening** — causes enemies to start AI too early, walk into pipes.

## INFRASTRUCTURE THAT EXISTS AND WORKS

- `g_oam_wide_x[64]` in `nes_runtime.h` / `main_runner.c` — per-slot int16_t override.
  Reset to -1 each frame. Renderer uses it when >= 0. **Verified working**: forcing all
  entries to 128 clusters every sprite at center screen.
- `game_ram_read_hook(pc, addr, val)` — PC-specific RAM read interception for absolute
  addressing. Active for $071A-$071D.
- `write_bp` on $03D1 — intercepts Enemy_OffscreenBits writes.
- `game_post_nmi` hook — runs after NMI, before rendering.
- `game_post_render` hook — runs after rendering.
- SMB symbol names in generated code (symbols.sym, 81 entries).

## THE ACTUAL REMAINING PROBLEM

When the game considers a sprite off-screen, it writes Y=0xF8 and does NOT populate
valid tile, attribute, or X data in OAM. Our post-NMI hook can compute the correct X
position, but the OAM entry has no valid tile/attribute data to render.

## CANDIDATE SOLUTIONS (RANKED)

### A. Hook the INDEXED read at $F1F6 (RECOMMENDED)

The offscreen bits computation at $F1F6 uses `LDA $071C,Y` (indexed absolute). Y=0 checks
left edge, Y=1 checks right edge. If we extend the recompiler's ram_read_hook to also wrap
INDEXED absolute reads (ABSX, ABSY modes) for hooked addresses, we can widen the offscreen
comparison at $F1F6. The game would then think the enemy is still on-screen and write VALID
tile/attribute/X data to OAM. Our g_oam_wide_x override would then fix the X position.

This is the most surgical fix:
- One recompiler change (code_generator.c: emit game_ram_read_hook for ABSX/ABSY modes too)
- One hook addition in extras.c (handle PC $F1FA reading $071D via indexed)
- Game writes correct OAM data naturally
- g_oam_wide_x handles positioning

### B. Replace the sprite drawing routine

Use `replace_func` in game.toml to replace the SMB sprite drawing function with a C
reimplementation that natively supports widescreen coordinates. Most robust but most work.

### C. Intercept OAM writes

Hook nes_write for the $0200-$02FF range. When the game writes Y=0xF8, check if the enemy
is in the widescreen extension. If so, block the write and substitute correct data. Requires
extending write_bp to support address ranges.

### D. Reconstruct OAM data in post-NMI

For enemies in the extension region, look up the correct tile/attribute data based on
Enemy_ID and animation state, then manually populate the OAM entry. Requires a tile lookup
table per enemy type — complex and fragile.

## KEY FILES

| File | What to change |
|------|---------------|
| `extras.c` | Game hooks, compute_widescreen_sprite_x |
| `game.toml` | ram_read_hook entries, symbol_file |
| `nesrecomp/recompiler/src/code_generator.c` | If extending ram_read_hook to indexed modes |
| `nesrecomp/runner/src/ppu_renderer.c` | g_oam_wide_x renderer support (already done) |
| `nesrecomp/runner/src/main_runner.c` | g_oam_wide_x storage + init (already done) |
| `nesrecomp/runner/include/nes_runtime.h` | g_oam_wide_x extern (already done) |

## KEY ADDRESSES

| Address | Name | Notes |
|---------|------|-------|
| $000F+i | Enemy_Flag | 5 slots |
| $0016+i | Enemy_ID | Enemy type |
| $006E+i | Enemy_PageLoc | World page |
| $0087+i | Enemy_X_Position | World X within page |
| $00CF+i | Enemy_Y_Position | Screen Y |
| $03D1 | Enemy_OffscreenBits | Bitfield, hooked via write_bp |
| $06E5+i | Enemy_SprDataOffset | OAM byte offset (reliable, proven) |
| $071A | ScreenLeft_PageLoc | |
| $071B | ScreenRight_PageLoc | |
| $071C | ScreenLeft_X_Pos | |
| $071D | ScreenRight_X_Pos | |
| $F1F6 | CheckOffscreenBits | Uses LDA $071C,Y — NOT hooked by current ram_read_hook |
| $F1FA | The actual indexed read | `LDA ($071C),Y` where Y=1 reads $071D |
| $D67A | OffscreenBoundsCheck | Entity lifecycle (hooked) |

## BUILD

```batch
# Full clean rebuild (required when nesrecomp runner files change):
del /s /q build
build.bat
echo port=4370 > build\debug.ini

# Game-only rebuild (extras.c changes only):
rebuild.bat

# IMPORTANT: Ninja does NOT detect nesrecomp submodule file changes.
# Always delete build/ and use build.bat when touching runner source.
```

## TCP COMMANDS

```json
{"cmd":"read_ram","addr":"0x000F","len":5}     // Enemy_Flag (NOTE: 'len' NOT 'count')
{"cmd":"read_ram","addr":"0x06E5","len":5}     // Enemy_SprDataOffset
{"cmd":"read_oam"}                              // Full OAM dump
{"cmd":"frame"}                                 // Current frame number
{"cmd":"pause"}                                 // Pause for stepping
{"cmd":"step"}                                  // Advance one frame
{"cmd":"read_frame_ram","frame":N,"addr":"0x000F","len":5}  // Ring buffer read
```

## CONSTRAINTS

- DO NOT modify generated/*.c
- DO NOT hook spawn lookahead at $C164 (breaks enemy positioning)
- TCP read_ram uses `len`, NOT `count`
- Always delete build/ when changing nesrecomp runner/renderer files
- Always create build/debug.ini after clean rebuild
- g_oam_wide_x default -1 must remain authentic NES behavior
