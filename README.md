# SuperMarioBrosRecomp

Static recompilation of Super Mario Bros. (NES) for native PC.
Built with the [NESRecomp](https://github.com/mstan/nesrecomp) framework.

> **Status: Work in progress.** World 1-1 is fully playable and the title screen renders correctly. Known issues exist (see below) — this is an early release intended for testing and development.

## Known Issues

- **HUD flicker** — sprite-0 split timing is approximate; score/lives area may flicker occasionally
- **Enemy hit detection unreliable** — walking into Goombas may not deal damage consistently; jumping on them can phase through
- **World 1-2 warp pipe crash** — entering the warp zone causes a game over; world transitions not fully implemented
- **Luigi frozen after Mario dies** — controller 2 input not yet bound; 2-player mode non-functional

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

## Save States

| Key | Action |
|-----|--------|
| F5  | Toggle turbo (fast-forward) |
| F6  | Save state → `C:\temp\quicksave.sav` |
| F7  | Load state ← `C:\temp\quicksave.sav` |

## Building from Source

Prerequisites: Windows 10+, Visual Studio 2022, CMake 3.20+ (SDL2 is bundled)

```
git clone --recurse-submodules https://github.com/mstan/SuperMarioBrosNESRecomp
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
| `ISSUES.md` | Detailed open issue tracker |
