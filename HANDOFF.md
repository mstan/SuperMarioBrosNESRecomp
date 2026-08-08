# Session Handoff - Smash 64 Captain Falcon in SMB1

Date: 2026-08-08

Captain Falcon's first complete milestone ladder is finished: authentic
locomotion, host collision/handoffs, real model and animation playback,
representative grounded/aerial combat, native SMB1 enemy/block consequences,
and original voice/move audio. The central Beads tracker remains the source of
truth:

```powershell
bd -C F:\Software\beads\issues show beads-2dw.2.1 --json
bd -C F:\Software\beads\issues show beads-2dw.2.1.8 --json  # M7 combat
bd -C F:\Software\beads\issues show beads-do7 --json        # M8 audio
```

## Repositories

Both repositories use local branch `feat/smash64-player-replacement`.

| Repo | Path | Relevant HEAD |
|---|---|---|
| Engine | `F:\Projects\nesrecomp\_wt-falcon-smb\nesrecomp` | `6cb121d` (mod PCM overlay mixer/audio-event ABI) |
| Game | `F:\Projects\nesrecomp\_wt-falcon-smb` | current local HEAD; gitlink must point to `6cb121d` |

Never push either repository. The branch contains a direct port of an
unlicensed decomp and depends on owner-only ROM-derived runtime assets.

## Hard rules

1. Never push or publish either repo, `mods/smash64/ssb_ported/`, or anything
   under `assets_ssb64/`.
2. `assets_ssb64/` is ignored. Never stage its model, animation, texture,
   audio, manifest, or baked runtime bytes.
3. Never edit `generated/`. Fix the recompiler and regenerate.
4. Confirm every 6502 address with the headless `ghidra` MCP server before
   reading or writing it. Use `registry_open key="nes/SuperMarioBrosNES"`;
   never launch the GUI or kill a Ghidra process.
5. Never run `git add -A` in the game worktree. Stage explicit paths and update
   the engine gitlink explicitly:

   ```powershell
   git update-index --add --cacheinfo 160000,<engine-sha>,nesrecomp
   ```

6. Do not run two `SuperMarioBrosRecomp.exe` instances. They contend for the
   executable during builds and share the trace server port.
7. Keep the one scale conversion: `FALCON_TO_SMB1_PX 0.08`. Do not retune
   individual source physics constants.
8. Track substantive work in the central Beads database only:
   `bd -C F:\Software\beads\issues ...`.
9. `baserom.nes` is the stock headerless ROM (CRC32 `d445f698`).

## Build and validation

Use Visual Studio's CMake binary. Bare `cmake` may inherit a broken generator
from another shell.

```powershell
$CM = 'C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe'
$CT = 'C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\ctest.exe'
$GAME = 'F:\Projects\nesrecomp\_wt-falcon-smb'

& $CM -S "$GAME\tests\falcon_harness" -B "$GAME\build_harness" -A x64
& $CM --build "$GAME\build_harness" --config Release
& $CT --test-dir "$GAME\build_harness" -C Release --output-on-failure
# Expected: 12/12.

& $CM -S $GAME -B "$GAME\build_falcon" -A x64
& $CM --build "$GAME\build_falcon" --config Release
```

Scripted runs require the ROM as the first positional argument or the launcher
will open instead:

```powershell
$env:SDL_AUDIODRIVER = 'dummy'
& "$GAME\build_falcon\Release\SuperMarioBrosRecomp.exe" `
  "$GAME\baserom.nes" --script "$GAME\tests\falcon_m8_audio.script"
```

Mod selection lives in `build_falcon\Release\mods\state.toml`. The committed
source default remains Captain Falcon enabled; mod-off tests temporarily change
the staged build copy and must restore it.

## Architecture

The engine owns the reusable boundaries:

- `ForeignController`: ownership, high-precision movement, jump handshake,
  host-imposed velocity, portable attack hitbox, and bounded one-tick audio
  events.
- `mod_savestate`: id-keyed external fighter/adapter state.
- `mod_audio`: copied mono S16/44100 clips, eight overlapping one-shots,
  saturating mix into the NES producer frame before shared volume/bridge.
- voxel renderer: model mesh and texture submission.

The SMB1 adapter in `game_smash64.c` owns the host details: four scoped 6502
function-entry hooks, horizontal/vertical sweeps against SMB1's own block
buffer, scripted ownership, native enemy defeat, and native brick shatter.
Confirmed combat entries are `PlayerHeadCollision $BCED`, `BrickShatter $BE02`,
and `ShellOrBlockDefeat $D795`.

Captain Falcon's state machine remains in the quarantined
`mods/smash64/ssb_ported/falcon_locomotion.*`; the publishable character bridge
only translates to/from the generic ABI.

Presentation uses `game_smash64_assets.c`: 26 joints, 319 triangles,
23 textures, and 30 animations. Figatree's one-based joint names are converted
to zero-based model slots by the baker. The runtime normalizes each pose to a
64-pixel readable height and uses a 60-degree three-quarter view. Missing model
data uses the cube fallback.

Audio uses `game_smash64_audio.c`: seven local cues for jump effort, "Falcon",
"Punch", Falcon Kick, Punch impact, Kick swing, and Kick energy start. Missing
clips are a silent fallback. Exact table provenance and documented N64-FGM
adaptations are in `docs/falcon_audio.md`.

## Completed milestones and evidence

- M4 collision: vertical/horizontal tunnelling prevention, wall/ceiling/floor
  reconciliation, native camera delta, and collision matrix.
- M5 gameplay: ordinary/scripted ownership, pipes/water/castle/death handoffs,
  save states, reseed behavior, and mod-off regression.
- M6 rendering: real Falcon model, textures, and authentic animation selection;
  corrected Figatree joint-slot mapping; screenshot-verified readable idle,
  run, jump, Falcon Punch, and Falcon Kick poses; absent-asset fallback.
- M7 combat: Jab, forward tilt, neutral/forward/back air, Falcon Punch, Falcon
  Kick; source hit windows/damage; native SMB1 enemy defeat and `$51/$52` brick
  shatter; nonbreakable/special/boss filtering; save/load and mod-off coverage.
- M8 audio: exact source-frame cue events, seven ignored local clips, shared
  NES mix, stop-on-load, mod unload, silent fallback, and no per-frame spam.

Key committed evidence/docs:

- `docs/falcon_combat.md`
- `docs/falcon_audio.md`
- `tests/falcon_harness/combat.script`
- `tests/falcon_harness/audio.script`
- `tests/falcon_m7_combat.script`
- `tests/falcon_m7_savestate.script`
- `tests/falcon_m8_audio.script`
- `tests/falcon_visual_acceptance.script`
- `tests/falcon_tier4_mod_off.script`

The M8 live trace loads 7/7 clips and queues every mapping. During a Punch
windup save/load, the already-consumed "Falcon" entry call does not replay;
the future frame-42 "Punch" and impact cues each occur once on both genuine
continuations. A 12-second audio-debug capture contains both native APU output
and a distinct combined bridge input. With the mod disabled, no Falcon asset or
audio load occurs. With the ignored audio directory withheld, startup emits one
fallback message and a smoke run exits cleanly.

## Known adaptations and traps

- Hook player wrapper `$BF09`, never generic `$BF0F`; enemies use the latter.
- SMB1 has no double jump, so Falcon's JumpAerial effort voice maps to its one
  supported jump.
- Voice previews preserve the original -1200-cent articulation. The three FGM
  previews preserve mapped waveform/pitch but adapt the full N64 envelope and
  forked-voice program; do not describe them as a complete N64 synthesizer.
- Native enemy defeat is intentionally not Smash percentage/knockback. The host
  maps accepted fighter hits to its own consequences.
- The block path temporarily presents Big-Mario head contact to SMB1's native
  routine, then restores player/CPU scratch while retaining block/VRAM/debris/
  score/sound effects.
- Runtime assets are loaded lazily only when the mod is enabled. Mod-off must
  produce no asset-load log.
- Never accept presentation from counters or load logs alone. Run
  `tests/falcon_visual_acceptance.script` and inspect all five native-resolution
  screenshots under `C:\temp\falcon_accept_*.png`; a coherent, recognizable
  Falcon silhouette is the M6 acceptance criterion.
- `nes_foreign_sweep` is not used by SMB1 because the host needs its own
  inclusive per-pixel collision semantics.

## Verification bar

For any future fighter/change: build Release, run all 12 deterministic tests,
collect a scripted in-game trace, exercise save/load and missing-assets, run the
mod-off test, inspect `git diff --check`, commit engine/game separately, update
the gitlink explicitly, and record the durable result in Beads. Never push.
