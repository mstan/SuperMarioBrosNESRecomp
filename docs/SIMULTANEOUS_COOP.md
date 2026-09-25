# Simultaneous Co-op

Enable **Mods → Gameplay → Simultaneous Co-op**, choose **2**, **3**, or **4**
players, and assign devices in **Controls**. The title screen offers **CO-OP
PLAY**. Player 1 controls Start and pause, including while Mario is out.

| Port | Character | Controls and physics |
| --- | --- | --- |
| 1 | Mario | Native SMB movement; red palette |
| 2 | Luigi | Same movement; green palette |
| 3 | Wario | Same movement; yellow/purple palette |
| 4 | Waluigi | Same movement; purple palette |

Gamepad seats use the selected controller or an unused connected pad. Unplugging
a pad leaves that seat neutral and preserves the other assignments. Four pads
of the same model can be selected individually. P1 defaults to the keyboard;
P3/P4 keyboard bindings start empty and can be assigned in Controls.

## Rules

- One forward 4:3 camera keeps every living player on screen. The leader waits
  when a teammate reaches the rear edge. Players pass through each other.
  The rear edge advances only as the trailing survivor advances; dead players
  do not hold it back. Walking left never advances the camera.
- Score, coins, timer, and three starting attempts belong to the team. A 1-up
  adds one team attempt. Items and enemies retain their original spawn counts.
- The player hitting a question block determines mushroom versus flower. A
  small flower collector grows big. Stars and damage invulnerability are private.
- Each fire player has two native fireballs. Fireballs cannot hurt allies;
  kicked shells can. Simultaneous contests resolve P1, P2, P3, then P4.
- A dead player stays out for that level. A full wipe spends one team attempt
  and retries everyone small at the furthest native checkpoint reached by a
  survivor. Time running out wipes the team.
- Completing a level/world revives dead teammates small and preserves survivors'
  power states. Pipes, vines, cloud falls, and bonus-room returns preserve who is
  out. Any living player may initiate an exit; lethal contact resolves first.
- Exit animations stage the surviving party and award/progress once. Any living
  player may satisfy a castle maze route; a wrong route loops the whole party.
- Enemies that look at the player use the nearest survivor, with port order for
  ties. Piranha plants check horizontal distance to all survivors.
- Transformations pause only the affected player by default. The **Whole game**
  option freezes the shared world and other players during that transformation.

This is local play. The package excludes widescreen, voxel/first-person display,
and player replacement mods. Savestates require matching co-op mode, player
count, and pause policy; invalid/incompatible records are rejected before changing
the running game. Turning the mod off restores the original 1P/alternating 2P game.

## Implementation

`src/game_coop.c` binds explicit per-player RAM fields around the original SMB
routines. `GameCoreRoutine` advances the shared world once; movement, contact
checks, native graphics, and fireballs run for the appropriate players. Native
metasprites are captured and recolored in the renderer, retaining background
priority and the original one-frame OAM delay. No extra character ROMs are needed.

Addresses come from `symbols.sym` and the pinned `smb-disassembly/src/smb.asm`
at `da964553b3695fde607d796acde21b3f4b282dfe`. Run
`python tools/generate_coop_symbols.py` after adding a referenced symbol.
Change `game.toml` and regenerate with NESRecomp to change native entries;
never hand-edit generated C. Entry seeds below `$C000` belong to NROM bank 0.
Exit routines reached through native branches use `include_internal = true`.

The design follows the shared-world/player-pass structure of the sibling SMW
co-op adapter and the extra logical seat/input validation of the Sonic 2 party
implementation. The gameplay adapter here runs SMB's own disassembled routines.
Ghidra is optional; the headless MCP can be used autonomously when useful.

The `smb.coop` save extension is a fixed-width little-endian version 2 record:
28 bytes of session state followed by four 2,218-byte actor records. It includes
private RAM, timers, contact flags, pending/visible sprites, transition ownership,
loaded area, checkpoint, and extra-seat input. No pointers or C padding are saved.

## Validation

Build a trace-enabled executable for scripted tests (`NESRECOMP_ENABLE_TRACE=ON`).
From the repository root, pass your own stock ROM and executable paths:

```sh
python tests/coop_runtime.py --exe <exe> --rom <rom>
python tests/coop_rules.py --exe <exe> --rom <rom>
python tests/coop_campaign.py --exe <exe> --rom <rom>
python tests/coop_package.py --exe <exe> --rom <rom>
python tests/coop_launcher.py --exe <exe> --rom <rom>
python tests/coop_camera_menu.py --exe <exe> --rom <rom>
python tests/coop_stock_regression.py --stock <pristine-exe> --candidate <exe> --rom <rom>
```

The campaign fixtures load the real area parser and exercise all 32 levels'
flagpole/pipe/axe exits, including outdoor returns and the final castle. They
are boundary tests, not complete manual terrain playthroughs. Other fixtures
cover contested items, deaths, powers, camera limits, platforms, springs, vines,
whirlpools, firebars, maze routes, pause, and deterministic save replay.

The stock comparison checks exact serialized core state and screenshots against
game `27ae15e9` plus engine `cfc483fe` through the title, original 2P selection,
movement, and turn change. Engine tests in `tests/coop_input`, `tests/mod_runtime`,
and `tests/mod-hooks.test.ts` cover devices, launcher binding persistence, mod
constraints, and code generation. Generated artifacts stay under `build-coop/`.
The launcher test captures P3/P4 keys through SDL events, restarts to verify
their displayed bindings, and clicks Reset to Defaults for each extra seat.
The camera/menu test records consecutive native frames through Start and checks
the mushroom cursor, absent legacy menu labels, signed leftward movement with
one or several survivors, and smooth camera movement as the rear catches up.
Windows test processes suppress console windows; scripted launcher checks use
`LNG_TEST_HIDDEN=1` to avoid showing a window or taking desktop focus.

For launch-delay diagnosis, `LNG_BOOT_TIMING=1` logs launcher phases and
`NESRECOMP_BOOT_TIMING=1` logs runner initialization through the first presented
frame. Use an actual windowed launch: `--script` and `--smoke` skip SDL startup.

`tests/startup_launch.py` exercises Play, real video/audio initialization, and
90 game frames through TCP in an isolated copy. It captures the title and exits.
`NESRECOMP_TEST_HIDDEN=1` keeps the game window hidden, in addition to the
launcher's `LNG_TEST_HIDDEN=1`; all child consoles are suppressed. For example:

```sh
python tests/startup_launch.py --exe <exe> --rom <rom> --out build-coop/startup-direct
python tests/startup_launch.py --exe <exe> --rom <rom> --out build-coop/startup-powershell --powershell --max-startup-ms 3000
```

Use `--settings-from <existing-build-directory>` to test a copy of its mod and
controller settings. The optional time limit covers runner entry through the
first presented frame; it excludes time spent browsing the launcher.

The PowerShell case reproduces a Windows logging regression: forcing redirected
stdout to be unbuffered made startup messages take seconds to write. The runner
now buffers redirected stdout and explicitly flushes startup and critical
messages. The reproduced 22.6-second runtime startup fell below 0.6 seconds;
normal direct output measured about 0.16 seconds on the test machine.

Trace builds also accept `--coop 2|3|4`, `--coop-pause player|shared`, and the TCP
`coop_state` command. Release users select the package in the launcher.
With `NESRECOMP_ENABLE_NET=ON`, add `--net-enabled` to the package test to
verify that co-op rejects an online session before connecting.
