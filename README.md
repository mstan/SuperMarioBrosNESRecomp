# SuperMarioBrosRecomp

Static recompilation of Super Mario Bros. (NES) for native PC.
Built with [NESRecomp](https://github.com/yourusername/nesrecomp) framework.

## Prerequisites
- Windows 10+, Visual Studio 2022
- CMake 3.20+
- SDL2 (bundled in nesrecomp/runner/external/SDL2/)

## Build

```
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

## Run

Place your Super Mario Bros. ROM as `Super Mario Bros. (World).nes` in the build/Release/ directory, or:

```
build/Release/SuperMarioBrosRecomp.exe
```

The launcher will prompt for a ROM file if none is found.
