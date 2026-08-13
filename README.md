# SuperMarioBrosRecomp

> _This recompilation is a **byproduct of developing
> [nesrecomp](https://github.com/mstan/nesrecomp)** — the games are the proving ground, the framework is the goal.
> **These are in-development previews, not finished ports — expect rough
> edges**, and depth will keep landing over months, not days. My time for any
> one title is limited, so I ask for your patience. Contributions are welcome —
> testing, issues, and PRs to the game or framework all help and will
> accelerate this game's polish. More on the why at:
> [Recomp + AI: 5 Months Later »](https://1379.tech/recomp-ai-5-months-later/)_

Static recompilation of Super Mario Bros. (NES) for native PC.
Built with the [NESRecomp](https://github.com/mstan/nesrecomp) framework.

> **Status:** The game is fully playable. All worlds and levels are believed to be completable, though not every path has been exhaustively tested. If you find a game-breaking bug, please [open an issue](../../issues).

## Known Issues

- **Demo sequence non-determinism** — the title screen auto-play demo may behave
  differently between launches — an item the demo collects on one run can be
  missed on another. This is a minor frame-timing inconsistency in real-time mode
  (turbo/fast-forward mode is fully deterministic).
  Gameplay is unaffected.

## Quick Start

1. Download `SuperMarioBrosRecomp-windows-x64.zip` from [Releases](../../releases)
2. Extract and run `SuperMarioBrosRecomp.exe`
3. Select your Super Mario Bros. (World) ROM when prompted — the path is saved for future launches

## Captain Falcon (bundled mod)

Open **Mods**, select **Smash 64 Player Replacement**, and choose your legally
owned **Super Smash Bros. (USA), NTSC-U v1.0** ROM. The launcher accepts z64,
v64, or n64 byte order and verifies normalized SHA-1
`e2929e10fccc0aa84e5776227e798abc07cedabf`. The mod cannot be enabled without
that exact revision.

On first play, the bundled helper derives Captain Falcon's model, animations,
effects, and audio into an integrity-checked user cache. Neither the Smash 64
ROM nor generated Falcon assets are included in the download or copied into
the game directory. A is Falcon's normal attack, B is his special, and Up is
his four-frame jump; Up+B is Falcon Dive and Down+B is Falcon Kick.

## Samus (bundled mod)

Open **Mods**, enable **Metroid Samus Player Replacement**, and select a legally
owned canonical **Metroid USA PRG0 or Europe/PAL** ROM. Headered and headerless
images are accepted; the launcher strips a valid iNES header and verifies
normalized SHA-1 `fdbfc7871962f72a1ef57e5a7e456164fb93430b` (USA) or
`68a55eafcefa3014a4771cb7983d7db42f80456a` (Europe). Samus's sprite tiles are extracted
into memory from that verified ROM. No Metroid ROM data or derived graphics are
shipped or written beside the game.

Samus begins with 99 energy and every original upgrade equipped. A jumps, B
fires, Down morphs, and Select switches between the combined Long/Wave/Ice beam
and infinite missiles. B lays bombs in Morph Ball. Screw Attack, missiles, and
bombs break only SMB's ordinary breakable bricks; contact hurts Samus instead
of stomping enemies. Mushroom restores 30 energy, Fire Flower restores all
energy. Bomb blasts boost a nearby Morph Ball upward, and Starman contact
defeats enemies while its native temporary invincibility is active. Metroid's
ability sound effects are rebuilt in memory from the verified owner ROM.

The Samus and Smash 64 packages share the `player-controller` exclusive group,
so the launcher permits only one at a time. See
[docs/METROID_SAMUS_MOD.md](docs/METROID_SAMUS_MOD.md) for implementation and
validation details.

## Zelda II Link (bundled mod)

Open **Mods**, enable **Zelda II Link Player Replacement**, and select a legally
owned canonical **Zelda II: The Adventure of Link (USA)** ROM. Headered and
headerless images are accepted; the launcher strips a valid iNES header and
verifies normalized SHA-1 `11333adb723a5975e0ecca3aee8f4747aa8d2d26`. Link's
side-view sprite tiles are extracted into memory from that verified ROM. No
Zelda II ROM data or derived graphics are shipped or written beside the game.

Link uses Zelda II-style controls: A jumps, B slashes, Down crouches, and
Up/Down with B in the air performs vertical stabs. Sword strikes hurt enemies
and, as an SMB-specific liberty, can break ordinary breakable bricks. The Link,
Samus and Smash 64 packages share the `player-controller` exclusive group, so
the launcher permits only one at a time. See
[docs/ZELDA2_LINK_MOD.md](docs/ZELDA2_LINK_MOD.md) for implementation and
validation details.

## Widescreen mod (experimental)

An optional 16:9 mode renders the world beyond the NES's 256-px viewport
— real background and sprites in the margins, no stretching. It is
**experimental and buggy** (see [WIDESCREEN.md](WIDESCREEN.md)).

Open **Mods** in the launcher and enable **Widescreen (16:9)**. It is a
default-off package alongside **Voxel 3D**. The two display modes are mutually
exclusive: enabling either one automatically disables the other. Neither
package patches the stock ROM. With both disabled the game is the authentic
4:3 recomp, verified byte-identical to the emulator reference.

## Voxel 3D (experimental)

[![Super Mario Bros. Voxel 3D video](https://img.youtube.com/vi/qEx9pl6CK1k/maxresdefault.jpg)](https://www.youtube.com/watch?v=qEx9pl6CK1k)

Open **Mods** in the launcher and enable **Voxel 3D**. This first-person
experiment rotates the sampled side-scroller plane upright and moves the camera
with Mario while looking along his live facing direction. Right faces forward
along the course; turning Left smoothly reverses the camera 180 degrees, as it
does for Samus in Metroid's first-person mode. Mario's own sprite is hidden
from the first-person view; enemies and items remain camera-facing cards among
the reconstructed blocks, pipes, flagpoles, and terrain.

First-person movement uses compact tank controls: Up advances in the direction
the camera faces and Left/Right select the corresponding facing. Down makes
small Mario backpedal without reversing the view; grounded tall Mario retains
his native crouch. The right stick looks vertically; pushing it fully upward
looks almost straight up and centers Mario's overhead column for lining up
jumps into blocks. Releasing the stick returns the camera to level. Crouching
lowers the camera to tall Mario's crouched eye level and standing raises it
again. Small Mario and pipe-entry input retain their ordinary eye height. A, B,
Start, and Select retain their original NES behavior.

The package saves camera pitch, yaw, roll, zoom, and sprite scale. During play,
Numpad 8/2 adjusts pitch, 4/6 rotates yaw, 7/9 rolls the view, +/- changes zoom,
and 1/3 changes sprite scale. Numpad 0 toggles Voxel 3D and Numpad 5 restores
the package defaults. These live controls are intended for experimentation;
the values selected in Mods remain the persistent defaults.

Voxel 3D is disabled by default, is mutually exclusive with Widescreen (16:9),
and does not patch the stock ROM or alter save data.

## Controls

| NES Button | Keyboard |
|------------|----------|
| D-Pad      | Arrow keys |
| A          | Z |
| B          | X |
| Start      | Enter |
| Select     | Right Shift |

## Hotkeys

| Key | Action |
|-----|--------|
| F5  | Toggle turbo (fast-forward) |
| F6  | Save state |
| F7  | Load state |

## ROM

| Field | Value |
|-------|-------|
| Title | Super Mario Bros. (World) |
| CRC32 | `3337EC46` |
| MD5   | `811b027eaf99c2def7b933c5208636de` |
| SHA-1 | `ea343f4e445a9050d4b4fbac2c77d0693b1d0922` |

## Building from Source

Prerequisites: Windows 10+, Visual Studio 2022, CMake 3.20+ (SDL2 is bundled).
Release builds also require Python 3 with `PyInstaller` and `Pillow` to package
the source-only owner-ROM cache helper.

```bash
git clone https://github.com/mstan/SuperMarioBrosNESRecomp
cd SuperMarioBrosNESRecomp

# Windows
setup.bat

# Linux / macOS
chmod +x setup.sh && ./setup.sh
```

This initializes the pinned [nesrecomp](https://github.com/mstan/nesrecomp)
submodule and links the Nestopia oracle core.

Then build:

```bash
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

## Architecture

This is a **static recompiler**, not an emulator. The 6502 machine code in the ROM
has been translated to C by [NESRecomp](nesrecomp/) and compiled to native x64.

| File | Purpose |
|------|---------|
| `extras.c` | SMB-specific runner hooks |
| `game.cfg` | Recompiler config (inline dispatch, NROM-256 layout) |
| `generated/super-mario-bros_full.c` | Recompiled 6502 code (committed) |
| `generated/super-mario-bros_dispatch.c` | Dispatch table (committed) |
| `ISSUES.md` | Detailed issue tracker with root-cause analysis |

---

<p align="center">
  <sub><b>R.A.I.D. — Retro AI Development</b> · a Discord for AI-assisted retro reverse-engineering, decomp &amp; recomp</sub>
</p>

<p align="center">
  <a href="https://discord.gg/Ad9BwSzctP"><img src=".github/raid-discord.png" alt="Join the Retro AI Development (R.A.I.D.) Discord" width="200"></a>
</p>
