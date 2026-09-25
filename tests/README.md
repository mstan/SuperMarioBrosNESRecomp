# Tests

Run commands from the repository root. Initialize the pinned dependencies with
`setup.bat` or `./setup.sh` first. Keep build output under `build/`, `build-*`,
or `build_*`; these directories are ignored.

## Controller and adapter harnesses

For simultaneous co-op, see [the co-op guide](../docs/SIMULTANEOUS_COOP.md#validation).
`coop_runtime.py`, `coop_rules.py`, `coop_campaign.py`, and `coop_package.py`
exercise the actual game with a supplied ROM. `coop_stock_regression.py` compares
mod-off saves and screenshots against a pristine executable.

Each directory below is a standalone CMake project. For example:

```sh
cmake -S tests/falcon_harness -B build/falcon_harness
cmake --build build/falcon_harness --config Release
ctest --test-dir build/falcon_harness -C Release --output-on-failure
```

| Directory | Coverage |
| --- | --- |
| `falcon_harness` | Falcon movement/combat traces and mod audio |
| `pikachu_harness` | Pikachu behavior vectors, host burst planning, and presentation |
| `pikachu_bridge` | Pikachu host-controller bridge |
| `smash64_actions` | Shared attack actions and world interaction |
| `smash64_profile` | Fighter profile traits |
| `samus_harness` | Samus controller and save state |
| `link_harness` | Link controller and save state |
| `sonic_harness` | S3K Sonic player port and controller; run the built `sonic_controller_harness` executable directly |

These harnesses do not need a ROM or running game. On Visual Studio builds,
executables are in the build directory's `Release/` subdirectory.

`s3k_sound_harness` is the exception: it renders Sonic 3 & Knuckles sounds
through the Sonic mod's emulated Genesis sound board, so it needs the owner ROM.
Run `s3k_sound_harness <s3k.bin> <out.wav> [log.csv] id[@frame] ...`; hex ids
below `33` are music, the rest sound effects.

## Owner-ROM tooling

```sh
python -m unittest discover -s tests/owner_ssb64 -p "test_*.py"
```

The suite includes recipe and synthetic-data checks. Tests requiring private
ROMs or caches skip when their inputs are absent. See the
[owner cache guide](../tools/owner_ssb64/README.md) and each test's environment
variables for optional asset validation. Some checks require Pillow.

## Startup latency

`startup_launch.py` requires a trace-enabled build and an owner ROM. It tests
actual launcher-to-game initialization with hidden windows and records timings
and a title screenshot. Add `--powershell` on Windows to cover redirected log
output, which previously stalled unbuffered stdout. See the
[co-op validation guide](../docs/SIMULTANEOUS_COOP.md#validation) for commands.

## Game and release probes

The `*.script` files are reusable input/QA scenarios for the runner's
`--script` option. Some load a maintainer save slot or expect a particular mod
and world; read the scenario before running it. They are test inputs, not
generated output.

The `rdb_*.py` scripts exercise the TCP debugger. `widescreen_*_probe.py` and
`custom_widescreen_probe.py` check renderer behavior; `release_package_probe.py`
checks Windows ZIP contents and runtime behavior. Read each script's arguments
and prerequisites, and see the [debugging guide](../docs/TCP.md) or
[widescreen guide](../docs/WIDESCREEN.md) for the associated workflow.

`regression.test.ts` is the Windows end-to-end regeneration/build/smoke suite.
It expects a matching ROM at the repository root, a built recompiler at
`nesrecomp/build/recompiler/Release/NESRecomp.exe`, and a Visual Studio solution
under `build/`. From `tests/`, run `npm install` followed by `npm test`.
`baseline.json` contains the checked-in reference hashes; review baseline
changes separately from implementation changes.

For Linux AppImage controller persistence, run under a virtual display:

```sh
xvfb-run -a python3 tests/appimage_bindings.py --appimage <AppImage> --rom <rom> --out build/appimage-binds
```

This captures P3/P4 bindings in the packaged launcher, restarts it, and checks
that the game reads the same persistent file beside the AppImage.
