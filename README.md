# SuperMarioBrosRecomp

Static recompilation of Super Mario Bros. (NES) for native PC.
Built with the [NESRecomp](https://github.com/mstan/nesrecomp) framework.

> **Status:** The game is fully playable. All worlds and levels are believed to be completable, though not every path has been exhaustively tested. If you find a game-breaking bug, please [open an issue](../../issues).

## Known Issues

- **Demo sequence non-determinism** — the title screen auto-play demo may behave
  differently between launches. On some runs Mario misses the mushroom from the
  first `?` block; on others he collects it normally. This is a minor frame-timing
  inconsistency in real-time mode (turbo/fast-forward mode is fully deterministic).
  Gameplay is unaffected.
- **2-player mode non-functional** — controller 2 input is not bound; Luigi cannot
  move when play switches to him after Mario dies.

## Quick Start

1. Download `SuperMarioBrosRecomp-windows-x64.zip` from [Releases](../../releases)
2. Extract and run `SuperMarioBrosRecomp.exe`
3. Select your Super Mario Bros. (World) ROM when prompted — the path is saved for future launches

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

Prerequisites: Windows 10+, Visual Studio 2022, CMake 3.20+ (SDL2 is bundled)

```bash
git clone https://github.com/mstan/SuperMarioBrosNESRecomp
cd SuperMarioBrosNESRecomp

# Windows
setup.bat

# Linux / macOS
chmod +x setup.sh && ./setup.sh
```

This clones [nesrecomp](https://github.com/mstan/nesrecomp) at the exact
version pinned in `nesrecomp.pin` and links the Nestopia oracle core.

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
