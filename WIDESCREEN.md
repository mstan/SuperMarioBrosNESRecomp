# Widescreen mode (EXPERIMENTAL)

Optional 16:9 (or custom-margin) rendering for Super Mario Bros.
**Status: experimental and buggy.** The default build is always the
authentic 4:3 game; everything described here is runtime-gated and
off unless explicitly enabled.

## Enabling

Either ship a `widescreen.ini` next to the exe:

```ini
enabled = 1
aspect = 16:9        # or: margins = 85x85  (left x right, in pixels)
```

or pass a command-line flag (overrides the ini):

```
SuperMarioBrosRecomp.exe --widescreen 16:9
SuperMarioBrosRecomp.exe --widescreen 85x85
SuperMarioBrosRecomp.exe --widescreen off
```

`16:9` resolves to 428 px wide (86 left + 256 + 86 right) at 240 lines.
Margins are capped at **left ≤ 128, right ≤ 96** — see Caps below.

With no ini and no flag, or `enabled = 0`, or `margins = 0x0`, the game
is exactly vanilla: the 8000-frame `--verify` oracle run is byte-identical
to the Nestopia reference in work RAM with widescreen off.

## How it works

Three coordinated layers, all gated at runtime on the config AND the
gameplay mode (OperMode 1 = game, 2 = victory; the title screen, attract
demo, and game-over screens stay fully vanilla and pillarboxed):

1. **Presentation** — the renderer draws extra background columns into
   the margins. SMB's two vertically-mirrored nametables hold 512 px of
   world; the margins show columns the game has already written.
2. **Sprite-X sidecar** — SMB computes sprite X with 8-bit math, so
   anything past the vanilla edges would wrap to the opposite side. A
   16-bit sidecar, keyed per rel-position slot at `GetObjRelativePosition`
   and re-armed on every rel-var read, unwraps OAM X writes so sprites
   render correctly inside the margins.
3. **Window widening** — the game's own draw-cull, despawn, and spawn
   decisions are widened by shifting the screen-edge values they read at
   exactly the PCs that implement each decision (`game.toml`
   `[[ram_read_hook]]` + the policy table in `extras.c`). Player edge
   clamping, loop-command rewind, and the area parser remain vanilla —
   they are dual-purpose state, not draw logic.

The simulation itself stays vanilla-exact; only *when* spawn/despawn
windows trigger changes (by the margin width), which is what makes the
margins free of pop-in.

## Caps (load-bearing — do not raise)

- **Right ≤ 96**: SMB's column writer leads ScreenRight by ~98 px at
  minimum; beyond that the margin would show not-yet-written tiles.
- **Left ≤ 128**: the left margin shows just-scrolled-out columns, valid
  until the column writer wraps the nametable (512 px total).

## Known issues (why this is experimental)

- **Enemy spawn-timeline drift** (ISSUES.md #12, deferred): enemies spawn
  up to `right-margin` px of camera travel earlier, so their walk/fall
  phase differs from the vanilla timeline on approach — different
  patterns, enemies meeting each other, and occasionally an enemy visibly
  overlapping geometry in the margin (vanilla produces the same spawn
  states, but guarantees they happen offscreen).
- Occasional sprite placement glitches in and near the margins are still
  being found; HUD-row margin rendering on non-sky palettes is untested,
  as are parts of later worlds (lifts, frenzy spawners, flagpole edge
  content).
- Sprite-0 timing, scores, physics, and RNG are unaffected — the
  `--verify` oracle gate is run on every change.

## Verification tooling

- `tools/ws_check.py` — drives 1-1 over the TCP debug server and asserts
  the three historical failure modes never occur (wrap ghosts, spawn
  pops, despawn pops). Requires a debug build (`build_rdb.bat`) and
  `debug.ini` next to the exe.
- `--verify` — dual-execution lockstep against the Nestopia oracle
  (debug build), comparing all 2 KB of work RAM every frame.
