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

Four coordinated layers, all gated at runtime on the config AND the
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
3. **Window widening** — the game's own draw-cull and despawn decisions
   are widened by shifting the screen-edge values they read at exactly the
   PCs that implement each decision (`game.toml` `[[ram_read_hook]]` + the
   policy table in `extras.c`). Player edge clamping, loop-command rewind,
   and the area parser remain vanilla — they are dual-purpose state, not
   draw logic.

   **Spawns stay vanilla 4:3.** The spawn-window PCs (`$C164/$C16E`,
   `$C1B6/$C1BB`, `$C5DA/$C5E2`, `$C73C/$C741`) are deliberately *not*
   widened: enemies spawn at the authentic 4:3 edge, with vanilla position
   and timing. The widened draw-cull/despawn then keep those objects
   visible across the full 16:9 width. This is **4:3 spawns + 16:9
   culling** — see "Spawn behavior" below.
4. **Collision offscreen gate** — keeping margin enemies "on-screen" for
   rendering (layer 3) also makes the game build a *collision* bounding box
   for them, and that box is 8-bit screen-relative, so it wraps to the
   opposite side of the screen — a phantom hitbox the player can stomp/hit
   even though the enemy renders correctly in the margin. At
   `GetMaskedOffScrBits` (`$E268`) the runner reports any enemy whose true
   screen X is in a margin as offscreen, so the vanilla `MoveBoundBoxOffscreen`
   parks its box at `$FF,$FF`. The player is always clamped on-screen and can
   never reach a margin, so a margin enemy never truly touches it — this is
   the collision analogue of the sprite-X sidecar. On-screen enemies are
   untouched, so collision stays byte-for-byte vanilla.

The simulation itself stays vanilla-exact; only *when* the draw-cull and
despawn windows trigger changes (by the margin width), which is what keeps
the margins free of despawn pop-out, plus the collision gate that keeps
margin enemies from forming phantom hitboxes.

## Caps (load-bearing — do not raise)

- **Right ≤ 96**: SMB's column writer leads ScreenRight by ~98 px at
  minimum; beyond that the margin would show not-yet-written tiles.
- **Left ≤ 128**: the left margin shows just-scrolled-out columns, valid
  until the column writer wraps the nametable (512 px total).

## Spawn behavior (4:3 spawns + 16:9 culling)

Enemies spawn on the **vanilla 4:3 timeline and position**, not at the
widened 16:9 edge. The earlier "widen the spawn window too" approach
caused serious spawn-area bugs — frenzy/group spawners derive an enemy's
X straight from the screen edge, so a widened edge dropped enemies *inside*
pipes and blocks with no collision to escape, and authored enemies
activated early enough to drift off their walk/fall pattern. Holding the
spawn PCs at 4:3 removes those bugs entirely.

The trade-off is a **spawn pop-in at the 4:3 edge line**: an enemy
materializes inside the right margin (where the 4:3 edge falls on the wider
screen) rather than at the very screen edge. Once spawned it is fully
covered by the widened draw-cull and despawn, so it never pops *out*. This
is the intended, accepted behavior.

## Known issues (why this is experimental)

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
