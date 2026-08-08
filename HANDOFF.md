# Session Handoff — Smash 64 Player Replacement (Captain Falcon in SMB1)

Date: 2026-08-07. Written for a Codex session taking over.

**FIRST ACTION, before reading further or touching any file:** the single
source of truth for this project is the **Beads tracker** —

```
bd -C F:\Software\beads\issues show beads-2dw.2.1 --json    # milestone ladder
bd -C F:\Software\beads\issues show beads-2dw.2.1.7 --json  # M6 (recommended next)
bd -C F:\Software\beads\issues show beads-2dw.2.1.6 --json  # M5 remaining
bd -C F:\Software\beads\issues show beads-2dw.2.1.5 --json  # M4 tail
```

Every milestone, measurement, evidence trail, and DISPROVED theory lives in
those beads, in more detail than this file. This file is only the map: rules,
build recipe, and pointers. When beads and this file disagree, the beads win.
Record your own work back into the beads the same way (`--append-notes`,
including anything you disprove).

North star: `F:\Projects\nesrecomp\.claude\GOAL.md` — finish the full Captain
Falcon port into SMB1 via the mod ecosystem, extensible to future fighters.
Design records: `docs/smb1_player_adapter.md`, `docs/smb1_scripted_handoffs.md`,
`docs/falcon_movement_dependency.md`, `assets_ssb64/SPEC.md`.

## Worktrees (both on branch `feat/smash64-player-replacement`, both clean)

| Repo   | Path                                        | HEAD    |
|--------|---------------------------------------------|---------|
| Engine | `F:\Projects\nesrecomp\_wt-falcon-nesrecomp` | c9aab82 |
| Game   | `F:\Projects\nesrecomp\_wt-falcon-smb`       | 49247aa (gitlink → c9aab82) |

## HARD RULES — read before anything else

1. **NEVER PUSH either repo.** Not with --force, not to a new remote, not
   "just the engine half". The branch carries a direct port of an unlicensed
   decomp (`mods/smash64/ssb_ported/`) AND now ROM-derived assets
   (`assets_ssb64/`, gitignored). pushRemote guards + a pre-push hook in the
   game repo are installed; do not remove them.
2. **Quarantine**: nothing under `mods/smash64/ssb_ported/` or `assets_ssb64/`
   may be published, quoted at length, moved out, or committed (assets are
   gitignored — keep them that way). Assets load at RUNTIME from the
   gitignored dir; the repo ships only the loader + a fallback.
3. **Never edit `generated/`** (`*_full*.c`, `*_dispatch.c`, `*_decls.h`).
   Fix the recompiler and regenerate. nesrecomp RULE 1.
4. **RULE 0**: confirm every 6502 address in Ghidra before reading/writing it.
   Headless only: MCP server `ghidra`, `registry_open key="nes/SuperMarioBrosNES"`.
   Never launch the GUI, never kill a Ghidra process, never commit .gpr/.rep.
   An empty xref list on this partially-disassembled program is NOT evidence
   of absence — byte-pattern search (`search_bytes`) is the reliable negative.
5. **NEVER `git add -A` in the game worktree** — Windows sees the `nesrecomp`
   junction as a symlink and stages it as a 120000 blob, destroying the
   160000 gitlink. Stage explicit paths. Repair:
   `git update-index --add --cacheinfo 160000,<engine-sha>,nesrecomp`.
   (`git submodule status` erroring here is normal, not damage.)
6. **One runtime instance at a time.** Kill `SuperMarioBrosRecomp.exe` before
   building (LNK1104 otherwise). All games share TCP port 4370.
7. **No printf debugging left behind.** Extend the always-on rings (ftring /
   fring) and query them; never arm-then-capture, never pause/step to observe.
8. **Always the complete option** — no "quick X now, proper Y later".
9. Track work in Beads (`bd -C F:\Software\beads\issues`). Record disproved
   theories explicitly. bd args containing double quotes break PowerShell —
   use single quotes / here-strings and `--append-notes`.
10. Scale policy: ONE uniform conversion, `FALCON_TO_SMB1_PX 0.08`. No
    per-parameter retuning (owner re-confirmed 2026-08-07: air momentum stays
    faithful). Do not contest `Player_State $001D`.
11. The stock ROM is `baserom.nes` (headerless CRC32 d445f698). Never restore
    `_HACKED-smb-not-stock-do-not-use.nes.bak`.

## Build & run (PowerShell; msys2 MUST be stripped from PATH)

```powershell
$VS = "C:\Program Files\Microsoft Visual Studio\2022\Community"
$CM = "$VS\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
$CT = "$VS\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\ctest.exe"
$NJ = "$VS\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja"
$ENG  = "F:\Projects\nesrecomp\_wt-falcon-nesrecomp"
$GAME = "F:\Projects\nesrecomp\_wt-falcon-smb"
$env:PATH = "$NJ;" + (($env:PATH -split ';' | Where-Object { $_ -notmatch 'msys64|mingw' }) -join ';')
& "C:\Windows\System32\cmd.exe" /c "`"$VS\VC\Auxiliary\Build\vcvarsall.bat`" x64 > nul 2>&1 && set" |
  ForEach-Object { if ($_ -match '^([^=]+)=(.*)$') { Set-Item "env:$($matches[1])" $matches[2] } }
Get-Process SuperMarioBrosRecomp -ErrorAction SilentlyContinue | Stop-Process -Force

& $CM --build "$ENG\build_recomp_falcon" --config Release --target NESRecomp   # only if recompiler changed
Set-Location $GAME
& "$ENG\build_recomp_falcon\Release\NESRecomp.exe" baserom.nes --game game.toml  # regen (only if recompiler/game.toml changed)
& $CM --build "$GAME\build_falcon"  --config Release
& $CM --build "$GAME\build_harness" --config Release
& $CT --test-dir "$GAME\build_harness" -C Release        # expect 9/9

# Scripted run with the always-on ring dumped at exit:
$env:NESRECOMP_FTRING_DUMP = "C:/temp/ftring.csv"
& "$GAME\build_falcon\Release\SuperMarioBrosRecomp.exe" baserom.nes --script C:/temp/foo.script
```

Regen invariants: 3445 functions (3258+187), **4 declared / 4 matched** mod
function hooks, 2 `[codegen] WARNING` lines about PowerUpObjHandler/SetAnimSpd
(intentional — bank-qualified aliases, beads-2dw.1.5 CLOSED). Scripts must
anchor on RAM, not frame counts: `WAIT_RAM8 000E 08` = ordinary play,
`WAIT_RAM8 000E 0B` = death. Mod selection persists in
`build_falcon\Release\mods\state.toml` (smash64-player enabled, captain-falcon).

## Architecture in one paragraph

Three layers. Engine `ForeignController` (game-agnostic; `foreign_controller.h`
— ownership NATIVE/FOREIGN/SCRIPTED, ForeignState, jump_phase, imposed_vy,
`reseeded` ring column, per-mod savestate registry `mod_savestate.h`). SMB1
adapter (`game_smash64.c` — decide_ownership; four function-entry hooks:
ImposeFriction $B5CC, MovePlayerVertically $BF4D, PlayerPhysicsSub $B450
jumpsquat, MovePlayerHorizontally $BF09 horizontal sweep; per-pixel swept
motion both axes probing SMB1's own block-buffer routines; reseed on
SCRIPTED→FOREIGN). Character layer (`mods/smash64/characters/captain_falcon.c`
+ quarantined `ssb_ported/falcon_locomotion.c`). Presentation:
`game_smash64_render.c` (OAM suppression + tracking 3D cube via the engine's
`nes_voxel_mesh_*` API). Ring columns incl. collision_flags bits: 0x1
HEAD_IN_SOLID 0x2 FEET_IN_SOLID 0x4/0x8 SWEPT_CEILING/FLOOR 0x10 SWEPT_RAN
0x20 SWEPT_WALL 0x40 SIDE_SWEPT_RAN 0x80 WALL_READBACK.

## What is DONE (verified, committed)

- M0–M3.5, M4 both axes, M5.1–M5.6, M6.1/M6.2. See beads beads-2dw.2.1.5/.6/.7
  for the full evidence; highlights:
  - Vertical tunnelling was PROVEN real (NESRECOMP_SMASH64_SWEEP_NOBLOCK=1
    diagnostic, governs both axes) and the sweep fixes it.
  - Horizontal sweep pins flush at pipes, zero penetration; the hook
    synthesizes return A = pixels moved (drives Player_X_Scroll → scroll).
  - Save states round-trip fighter + ForeignState + adapter latches
    (measured: identical post-load ring row).
  - Falcon's REAL assets extracted (skeleton 26 joints, 705 verts, 54 DLs,
    21 textures, 20 Figatree anims) into `assets_ssb64/` with `SPEC.md`.
  - Owner playtested and approved jumping (M3.5).

## NEXT WORK, in recommended order

1. **M6.3 — runtime asset loader** (beads-2dw.2.1.7; owner-recommended start).
   C loader in the mod that parses `assets_ssb64/` intermediates at startup
   (JSON/bin per SPEC.md; consider baking to a compact binary on first load),
   builds per-joint meshes, transforms via a pose sampler
   (`nes_voxel_pose_sample` design in the bead), feeds `nes_voxel_mesh_*`.
   Cube remains the fallback when assets are absent. Camera/registration
   lessons are in the bead and `game_smash64_render.c` comments (world space
   IS screen space, +Y up, eye at +Z — looking along +Z MIRRORS the scene).
   Known asset gaps (in the bead): some CI palette bindings runtime-selected
   (trace MObjSub in the decomp's 332_CaptainModel.c), Wait anim identity
   (decomp file 1512 mislabeled "EggLay"), no plain Landing (directional only).
2. **M5.7 — tier-4 coverage** (beads-2dw.2.1.6): water level (swim gate is
   implemented + Ghidra-verified but NEVER exercised in water), both pipe
   types (the reseed's motivating case — a pipe-frozen dash — was never
   reproduced; death edge self-heals by accident, see the bead), castle,
   A/B mod-off. Also the deferred mid-KNEEBEND and mid-air savestate checks.
3. **M4 tail** (beads-2dw.2.1.5): delete the legacy WALL_READBACK inference
   after the fastfall + a one-tile-gap script corroborate agreement pass 1
   (pass 1 result: readback caught NOTHING the sweep missed); scripted
   head-bump repro.
4. **M7** (beads-2dw.2.1.8, not started). Meta: beads-2dw.1.6 (Ghidra symbol
   import), .1.9 (stale HDPACK.md), and an unfiled oddity — why function
   discovery standalone-emits bank-1 copies of sub-$C000 functions on NROM
   (noted in beads-2dw.1.5).

## Gotchas that cost real time (do not rediscover)

- Hook $BF09 MovePlayerHorizontally, NEVER $BF0F MoveObjectHorizontally
  (generic — enemies share it). Return A drives the scroll engine.
- The horizontal side predicate is CheckSideMTiles' own chain, NOT either
  vertical predicate (see game_smash64.c side_tile_is_wall comments).
- CheckForCoinMTiles has side effects (queues coin sound) — compare $C2/$C3
  bytes directly instead of calling it.
- `nes_foreign_resolve` runs every frame INCLUDING scripted — the fighter is
  fed scripted RAM, not frozen. Death self-heals by accident; pipes wouldn't.
- Renderer handedness: eye at −Z looking +Z mirrors the scene horizontally.
- In-game scripts die to the first Goomba (~x330) unless they jump ~40 frames
  after motion starts. SMB1 is fully deterministic under scripted input.
- The SCREENSHOT script command worked correctly all session (the old "stale
  buffer" note is intermittent, not absolute).
- `Enter-VsDevShell`/msys cmake are broken here; use the exact build recipe
  above. Bare `cmd` resolves to an msys doc file — use C:\Windows\System32\cmd.exe.
- `nes_foreign_sweep` in the engine is deliberately UNUSED (wrong semantics
  for a host that resolves its own collisions); add an inclusive-stop mode if
  a second game ever needs it — don't copy the adapter loop.

## Verification bar for every change

Edit → regen (only if recompiler/game.toml changed; check the invariants) →
build both → harness 9/9 → scripted in-game measurement via the ftring dump →
mod-off regression (zero `[Smash64]` lines, no ring dump, Mario draws) →
commit engine and game separately with concrete numbers → bump the gitlink
when the engine moved → update the bead (including anything DISPROVED).
