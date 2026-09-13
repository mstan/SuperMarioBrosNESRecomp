# Custom widescreen (experimental)

Enable **Widescreen (Experimental)** in the launcher's **Mods** screen. The package is off by
default and shares the display-mode group with Voxel 3D. Stock play uses the
original renderer. The ROM is unchanged.

The renderer extends terrain, ordinary authored enemies and independent moving
platforms across the viewport.
Enemy movement can begin on load or retain original 4:3 activation timing.
Special spawners, linked balance platforms and some other objects retain native limits;
this experimental branch has not been validated through every world.

## Presentation

Choose **Fit window**, **16:9**, **21:9**, or **32:9**. Fit follows the window's
drawable aspect during play, clamped between the native aspect and 32:9. The
status bar can stay centered or sit at the screen edges.

**Camera: Anchor at area edges** is the default within the enabled mod. The
wide view stops at the start and end of the authored area, letting Mario stand
near either edge of the screen. Small fixed rooms, including pipe intros and
each underground bonus room, stay centered. **Keep native view centered**
restores the previous presentation. Both policies keep the original game
camera, player boundaries and classic enemy activation logic; extended
loading follows the displayed viewport.

The engine uses square pixels throughout:

| Mode | Logical frame |
| --- | --- |
| Stock | 256 x 240 |
| 16:9 | 426 x 240 |
| 21:9 | 560 x 240 |
| 32:9 | 854 x 240 |
| Fit | 256–854 x 240, following the window |

Developer overrides:

```powershell
.\SuperMarioBrosRecomp.exe baserom.nes --widescreen fit
.\SuperMarioBrosRecomp.exe baserom.nes --widescreen 16:9
.\SuperMarioBrosRecomp.exe baserom.nes --widescreen 21:9
.\SuperMarioBrosRecomp.exe baserom.nes --widescreen 32:9
.\SuperMarioBrosRecomp.exe baserom.nes --widescreen off
.\SuperMarioBrosRecomp.exe baserom.nes --widescreen 32:9 --widescreen-enemies classic
.\SuperMarioBrosRecomp.exe baserom.nes --widescreen 32:9 --widescreen-enemies viewport
.\SuperMarioBrosRecomp.exe baserom.nes --widescreen 32:9 --widescreen-camera edges
.\SuperMarioBrosRecomp.exe baserom.nes --widescreen 32:9 --widescreen-camera centered
```

The old arbitrary-margin syntax, screen-edge read patches and OAM sidecar policy
are removed from SMB's widescreen implementation. The old `widescreen.ini`
configuration file is obsolete; configure the package through Mods. The
widescreen release ZIP includes a portable Mods selection for 16:9 and viewport
activation. The standard ZIP and Linux AppImage leave the package disabled.

## World cache and compositor

`src/smb_ws_world.c` runs SMB's original `AreaParserCore` over the area's 512 possible
metatile columns in an isolated guest context, outside rendering. It restores
RAM, CPU registers, continuation state and the runtime state blob afterward;
the extra decoding advances no guest CPU/APU time. The live `AreaData` pointer
identifies the room, since `AreaPointer` may already name a pipe destination.

The host cache owns the resulting terrain tiles and palette indices. The
custom renderer samples it by world position instead of treating both physical
nametables as valid across an arbitrarily wide viewport. This removes the old
left/right limits imposed by nametable reuse and partial streaming.

An observation hook at `RenderAreaGraphics` compares generated metatile columns
against the cache and records their intended world coordinates. A physical
nametable column receives that binding only after its actual tile bytes match
the pending upload. Live bound columns update the cache, retaining visible
brick and coin edits as the nametables are reused. `InitializeArea` clears the
cache, including when restarting the same area after death.

Each column keeps the palette selected by its decoded metatiles. SMB uploads
attribute bytes later than tile bytes, so copying a reused physical attribute
could briefly turn part of a white cloud green. Live tile edits still update
the cache; delayed attributes cannot recolor unrelated world columns.

The native 256-pixel pass remains authoritative for its original background,
unmanaged sprites and transient background updates. The compositor
positions that pass at the same world offset as the extended terrain and
resident sprites, then places the HUD independently. Title and
other non-gameplay screens retain the centered native image. Dot-PPU rejects
the custom hook; HD-pack compositing is bypassed while the hook is active.

Terrain and extended sprites use the same captured PPU scroll as the native
pass. Reading the already-advanced game camera produced a one-frame offset
at the two joins while scrolling; the captured scroll removes that seam.

Area bounds use the original parser's `$FD` terminator after its buffered
objects finish, rounded to the last authored 256-pixel page. Repeated scenery
beyond that point is cache capacity, not another part of the stage. A scroll
lock during the initial 24-column preload identifies the supported ROM's fixed
rooms; each selected bonus-room page is isolated from the other entries in
that area's shared stream. Scripted native movement can extend the right
bound if necessary to keep its full playfield visible during the castle walk.
The `native` enemy diagnostic policy retains centered presentation for stock
pixel comparisons.

The world cache and enemy residents participate in mod savestates. Mod settings belong to
the mod configuration and are not overwritten by loading a state. Internal
mod state layouts may change across experimental versions.

## Enemy movement and remaining limits

The mod's **Enemy movement** option offers two policies:

- **Move when loaded in the wide view** (default): ordinary authored enemies
  initialize and move when their spawn enters the viewport plus a 48-pixel pad.
- **Preserve original 4:3 activation**: show a frozen preview at the authored
  location, then let the native parser initialize and activate it normally.

`src/smb_ws_actors.c` keeps enemy records in world coordinates. It invokes the
original initialization, graphics, terrain collision and movement routines in
an isolated guest context for residents outside native interaction slots.
Collision columns carry world ownership, so actors see their local terrain
instead of whichever columns currently occupy the two native block buffers.
Sprites use host packets beyond the original screen; near Mario, complete
per-enemy state transfers into native slots for normal player interactions.
The parser consumes already-loaded records without creating duplicate enemies.
Group records are activation triggers: their first enemy belongs 48 pixels
before the trigger, followed by 24-pixel spacing. Treating the trigger as the
first body's position placed a 1-2 Goomba inside a pipe. Classic activation
still takes the native parser's actual positions and timing.

Piranha Plants come from the area parser rather than ordinary enemy records.
The isolated area decode captures their pipe coordinates and original vertical
limits, and the resident manager observes `InitPiranhaPlant` for native handoff.
It also adopts plants created during initial screen construction. This makes
plants visible and active beyond the old screen without duplicating them when
their pipe streams in.

Independent platforms (`$25` through `$2C`) use their original initializer,
movement and graphics routines. The resident owns each complete six-sprite
packet, including both decks of a small looping lift. Large platforms move
before drawing; small lifts draw before moving, matching the original order.
The same activation option applies to platforms. Native interaction slots
retain Mario's landing and riding collision; detached platforms have no rider.
Multiple lifts sharing one X coordinate retain separate records and phases.
Linked balance platforms (`$24`) still need ownership of their paired slots.

Managed enemies are drawn as complete sprites across both old screen edges;
their corresponding native OAM slots are suppressed for presentation. This
avoids joining half a host sprite to SMB's column-clipped native sprite. The
compositor preserves foreground priority for higher-priority native sprites.

The goal flag appears alongside a decoded flagpole before native loading.
After the real flag loads, the compositor follows its original graphics,
lowering animation and score sprites. Flag collision and level completion
remain controlled by the native game.
Areas without a flag explicitly reject the missing-position sentinel; it can
never become a preview at world X=-1 during an area transition.

Remaining work, tracked in **beads-2dw.2.5**:

- Special bosses, linked balance platforms, frenzy controllers, and objects such as power-ups
  and projectiles still use native spawning/culling. Offscreen Hammer Bros'
  generated projectiles are not retained by the resident simulation yet.
- Mario's interactions still use the five original enemy slots, assigned to
  nearby actors. Dense crowds, offscreen shell scoring, score popups and special
  enemy behavior need more work and validation. This is not unlimited simulation.
- The whole-stage experiment (both viewing and simulating the entire stage) is
  still pending. Decoding 512 terrain columns alone does not implement it.

The previous spawn bugs were not solely a rendering problem: group and frenzy
spawners derive coordinates from screen edges. Rewriting those shared values
moved some spawns into terrain. The replacement must keep authored positions,
viewport extent and activation policy separate.

## Validation

`tests/custom_widescreen_probe.py` drives isolated TRACE-enabled executables,
using `--widescreen-enemies native` to isolate renderer regressions.
It compares RAM, CPU state and the native playfield against an untouched stock
binary; checks cached columns against live parser output; and verifies
deterministic rendering across save/load. On Windows it also resizes the live
Fit window through all supported widths.

```powershell
python tests/custom_widescreen_probe.py --exe <candidate.exe> `
  --baseline <untouched-stock.exe> --rom baserom.nes --out <new-artifact-directory>
```

The initial 1-1 route passed all presets and Fit: 34 streamed columns matched,
RAM/CPU and native playfield pixels matched stock, and save/load reproduced the
same state and image. A separate 1,200-frame stock smoke run matched all 120
baseline frame hashes with zero dispatch misses. The 32:9 route also matched
all 806 full-machine hash records from the untouched binary, including timing,
APU, PPU memory, open bus and mapper state. Saved mod selections enabled 21:9
with a centered HUD; package defaults and the `off` override retained stock
output. These checks do not establish all-world or extended-enemy correctness.

`tests/widescreen_enemies_probe.py` checks the first Goomba is visible outside
the native screen, stays frozen in classic mode, moves on load in viewport
mode, stays on the floor, and reproduces its state and image after save/load.
`tests/widescreen_seam_probe.py --require-aligned` compares cached and native
background opacity near both joins during a 240-frame scrolling route. The old
camera produced 143 misaligned frames; the captured-scroll version produced
none. Both probes require the same `--exe`, `--rom` and `--out` arguments.

`tests/widescreen_boundaries_probe.py` exercises complete enemy sprites on
both edges, palette ownership while streaming, and the owner's F2 flag setup.
The reproduced left-edge case lost 46 brown body pixels before the fix and
none afterward. The color route had 18 bad samples out of 120 before the fix
and none afterward. The F2 route verifies a preview flag, transfer to native
flag graphics, and lowering from Y=49 to Y=172. Its optional fixture conversion
drops obsolete world and actor payloads from a copy; owner saves are never modified.

`tests/widescreen_pipe_probe.py` checks the owner's 1-2 pipe scene. A fresh
native area restart is needed to test corrected spawning: the old F5 already
contains the misplaced Goomba. The replay verifies the middle plant beyond
the native viewport, no Goomba centered inside the three pipes, and deterministic
save/load. Its optional injury-timer override keeps the test alive without
freezing enemy movement; the initial preview checkpoint has no override.
`tests/widescreen_transition_probe.py` follows 1-1 completion through the 1-2
entry scene and underground arrival: 50 sampled ghost-flag frames before the
sentinel fix, zero afterward. The world state layout is version 4; the actor
layout is version 4 after adding independent platform residents.

`tests/widescreen_camera_probe.py` compares centered presentation with the
previous executable, checks native pixels and guest state at all three fixed
aspects, and exercises the goal, two fixed bonus entrances, save/load, live Fit
resizing and both saved Camera choices in Mods. Bonus-room cases drive the
original room initializer directly; they are rendering fixtures, not player
routes through the bonus pipes. Use `--exe`, `--baseline`, `--rom`, `--out`,
`--f2 <goal-approach-state>` and optionally `--mods mods/preloaded`.

`tests/widescreen_platform_probe.py` checks the owner's F5 lift setup. The old
renderer lost 150 of 300 platform pixels at the left edge and 186 at the right;
the new renderer loses none at either edge or fully outside native bounds.
The four 1-2 lifts match their original native positions across 360 frames,
including a transfer to private simulation. Mario rides an ascending lift for
30 frames with the same positions and collision flags as before. A controlled
loading setup places all four lifts beyond native activation, verifying visible
preloading and frozen classic versus moving viewport behavior. Save/load gives
identical RAM, CPU state, resident state and images. The test can convert a copy
of the previous F5 fixture without adding compatibility code to the runtime.

The engine's TCP pause loop currently drops window-resize events
(**beads-2dw.1.28**). Resizing during ordinary execution works; the probe tests
that path. Old `ws_check.py` and `ws_diag.py` probes depended on the retired
margin policy and have been replaced by this renderer comparison.
