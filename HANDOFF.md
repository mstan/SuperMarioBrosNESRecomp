# Session Handoff - Smash 64 Captain Falcon in SMB1

Date: 2026-08-08

## Current QA status: corrected and freshly inspected

The defects shown in the owner's August 8 screenshots have been corrected in
the current worktree. Fresh Release captures were generated after the final
build and visually inspected, not accepted from script exit codes alone:

- `C:\temp\falcon_final_profile_title.png`: normal SMB1 title/menu with no
  Falcon overlay;
- `falcon_final_aa_on_idle.png`, `falcon_final_aa_on_run.png`, and
  `falcon_final_aa_on_walk.png`: 28–32px-tall purple/red/yellow Falcon in a
  true side profile; rightward Run faces right and leftward Walk faces left;
- `falcon_final_profile_{jump,punch,kick}.png`: coherent articulated action
  poses at the same Big-Mario-scale presentation.
- `C:\temp\falcon_idle_ground_contact.png`: five frames spanning the complete
  revised idle loop on World 1-1's light background; both boots remain planted
  and the large forward-foot lift is gone;
- `C:\temp\falcon_death_contact.png`: eight consecutive death frames showing
  Falcon rotating through distinct Star-KO-style angles while falling, with no
  native Mario death sprite visible.
- `C:\temp\falcon_transform_contact.png`: three separated frames each for
  mushroom/grow, damage/injury, and fire-flower scripts; all nine hold the same
  planted Falcon pose with no Mario transformation frame visible.

The fixes came from BattleShip's Smash 64 implementation rather than visual
guesswork. Costume frame zero now evaluates Captain's material-animation
scripts, Figatree tracks retain their source hold/linear/cubic/step segments,
the mesh mirror follows Smash's authored +LR convention, and replacement
ownership is gated on SMB1 `OperMode == 1` so stale gameplay state cannot draw
Falcon over the title screen. The prior screenshots and commits `93f8741` and
`7ce5406` remain useful failure evidence, not acceptance evidence.

Owner follow-up found the first corrected presentation still too large and too
three-quarter-facing. The final defaults are 32 native pixels high (Big Mario's
box), 88 degrees (an almost exact side profile with a 2-degree boot reveal), and a Falcon-only 2x
supersample/box-filter pass. Native NES pixels are never filtered. A/B captures
show changes confined to Falcon's footprint; a 512px widescreen run also passes
through the bounded 1024x480 mesh surface.

The later idle/death correction keeps Falcon's Wait animation inside source
frames 37..41, a slow ping-pong window whose two foot meshes remain within the
ground-contact tolerance. This deliberately omits the source Wait stream's
large weight-shift/fidget from SMB1's continuously looping idle. During SMB1
`PlayerDeath`, physics, life loss, timing, and respawn remain native/scripted;
only presentation changes. Mario's metasprite is suppressed and Falcon uses a
centered aerial pose, 18 degrees of screen-plane rotation per frame, and an
accelerating downward screen-space path. BattleShip's `DeadUpStar` status is
the reference: it uses the common `DamageFall` motion and a 180-frame depth
translation. Depth is unreadable in SMB1's 2D view, so downward travel is the
documented host adaptation.

SMB1's other player transformations are also presentation-only exceptions.
During `PlayerChangeSize` (`$09`), `PlayerInjuryBlink` (`$0A`), and
`PlayerFireFlower` (`$0C`), SMB1 retains exclusive ownership of timers, size,
status, collision, and progression. The renderer suppresses Mario and holds
Falcon at source Wait frame 39 (the midpoint of the planted 37..41 window), so
mushroom pickup, shrinking after damage, blinking, and fire-flower palette
cycling deliberately produce no Falcon visual change.

Captain Falcon's implementation milestone ladder is present—locomotion, host
collision/handoffs, corrected model/animation playback, representative combat,
native SMB1 enemy/block consequences, and corrected original voice/move
audio. The central Beads tracker remains the source of truth:

```powershell
bd -C F:\Software\beads\issues show beads-2dw.2.1 --json
bd -C F:\Software\beads\issues show beads-2dw.2.1.7 --json  # M6 rendering
bd -C F:\Software\beads\issues show beads-2dw.2.1.8 --json  # M7 combat
bd -C F:\Software\beads\issues show beads-do7 --json        # M8 audio
bd -C F:\Software\beads\issues show beads-2dw.2.1.10 --json # final QA
bd -C F:\Software\beads\issues show beads-2dw.1.10 --json   # mesh 2x SSAA
```

## Repositories

Both repositories use local branch `feat/smash64-player-replacement`.

| Repo | Path | Relevant HEAD |
|---|---|---|
| Engine | `F:\Projects\nesrecomp\_wt-falcon-smb\nesrecomp` | `c724785` (bounded 2x mesh targets; includes mod PCM overlay mixer) |
| Game | `F:\Projects\nesrecomp\_wt-falcon-smb` | current local HEAD; gitlink must point to `c724785` |

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
to zero-based model slots by the baker. Blob version 2 stores BattleShip's
source interpolation segments and tangent rates instead of flattening them
into linear keys. Costume-zero primary colors come from reloc 332's
`MatAnimJoint` programs, matching BattleShip's fighter-part material
initialization. The runtime normalizes each pose to a 32-pixel Big-Mario-scale
height and rotates the authored model 88 degrees into a near-exact side profile.
`game_smash64_render.c` renders only Falcon at 2x, then box-downsamples coverage
over the native frame; the NES background remains pixel-perfect. Missing model
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
  corrected Figatree joint-slot mapping, source interpolation, costume-zero
  material initialization, facing convention, 32px side profile, and 2x edge
  supersampling; screenshot-verified planted idle, falling death tumble,
  bidirectional locomotion, jump, Falcon Punch, Falcon Kick, clean title,
  widescreen, and absent-asset fallback.
- M7 combat: Jab, forward tilt, neutral/forward/back air, Falcon Punch, Falcon
  Kick; source hit windows/damage; native SMB1 enemy defeat and `$51/$52` brick
  shatter; nonbreakable/special/boss filtering; save/load and mod-off coverage.
- M8 audio: exact source-frame cue events, seven ignored local clips, shared
  NES mix, BattleShip-accurate pitch, stop-on-load, mod unload, silent fallback,
  and no per-frame spam.

Key committed evidence/docs:

- `docs/falcon_combat.md`
- `docs/falcon_audio.md`
- `tests/falcon_harness/combat.script`
- `tests/falcon_harness/audio.script`
- `tests/falcon_m7_combat.script`
- `tests/falcon_m7_savestate.script`
- `tests/falcon_m8_audio.script`
- `tests/falcon_visual_acceptance.script`
- `tests/falcon_visual_locomotion_qa.script`
- `tests/falcon_visual_idle_loop_qa.script`
- `tests/falcon_visual_idle_ground_qa.script`
- `tests/falcon_visual_transform_qa.script`
- `tests/falcon_visual_title_qa.script`
- `tests/falcon_visual_combat_qa.script`
- `tests/falcon_visual_aerial_sequence_qa.script`
- `tests/falcon_tier4_death_respawn_qa.script`
- `tests/falcon_tier4_mod_off.script`

The M8 live trace loads 7/7 clips and queues every mapping. During a Punch
windup save/load, the already-consumed "Falcon" entry call does not replay;
the future frame-42 "Punch" and impact cues each occur once on both genuine
continuations. The August 8 final 12-second capture queues all seven cues; its
first 500 frames match a sample-level reconstruction of native APU plus Falcon
overlays exactly (367,500/367,500 samples). BattleShip establishes a 32 kHz
synthesizer and direct -1200-cent FGM voice ratio, so the voice bytes have a
16 kHz effective playback clock before conversion to the runner's 44.1 kHz.
With the mod disabled, no Falcon asset or audio load occurs. With the ignored
asset directory withheld, startup emits one model and one audio fallback
message and a smoke run exits cleanly.

## Known adaptations and traps

- Hook player wrapper `$BF09`, never generic `$BF0F`; enemies use the latter.
- SMB1 has no double jump, so Falcon's JumpAerial effort voice maps to its one
  supported jump.
- Voice previews preserve the original -1200-cent articulation against Smash
  64's 32 kHz output clock (effective 16 kHz source consumption), not against
  the decomp preview AIFF's incidental 44.1 kHz header. The three FGM
  previews preserve mapped waveform/pitch but adapt the full N64 envelope and
  forked-voice program; do not describe them as a complete N64 synthesizer.
- Native enemy defeat is intentionally not Smash percentage/knockback. The host
  maps accepted fighter hits to its own consequences.
- The block path temporarily presents Big-Mario head contact to SMB1's native
  routine, then restores player/CPU scratch while retaining block/VRAM/debris/
  score/sound effects.
- Runtime assets are loaded lazily only when the mod is enabled. Mod-off must
  produce no asset-load log.
- Falcon's planted SMB1 idle is a presentation adaptation over source Wait
  frames 37..41. `NESRECOMP_FALCON_ANIM_FRAME` may force a source frame for
  local visual diagnosis; it must not be set for acceptance runs.
- The death tumble is presentation-only. Never move ownership of
  `GameEngineSubroutine == $0B` away from SMB1 to implement it.
- Grow/shrink, injury blink, and fire-flower are intentionally visually inert
  for Falcon. Their `$09/$0A/$0C` routines must remain `SCRIPTED`; only sprite
  suppression and the planted Falcon overlay persist through them.
- Never accept presentation from counters or load logs alone. Run
  `tests/falcon_visual_acceptance.script` and inspect all five native-resolution
  screenshots under `C:\temp\falcon_accept_*.png`; a coherent, recognizable
  Falcon silhouette is the M6 acceptance criterion.
- `WAIT_RAM8 000E 08` becomes true while World 1-2's native entrance drop is
  still in progress. Visual tests must wait 120 more frames before saving a
  settled ground baseline. A `SCREENSHOT` is also queued until the next render;
  wait at least two frames before loading another savestate or changing the
  pose, or the PNG will record the replacement state instead.
- World 1-2's black backdrop is useful for the purple/yellow ground poses, but
  can hide Falcon's darkest lower-leg polygons during aerial kicks. The aerial
  sequence QA repeats consecutive Fair/Bair frames against World 1-1's light
  sky to distinguish connected dark geometry from a genuinely detached joint.
- `falcon_tier4_mod_off.script` does not toggle package state itself. Set the
  staged `build_falcon/Release/mods/state.toml` Smash64 feature to `false`
  before running it, verify no Falcon trace/asset/audio initialization occurs,
  then restore the feature to `true`.
- `nes_foreign_sweep` is not used by SMB1 because the host needs its own
  inclusive per-pixel collision semantics.

## Verification bar

For any future fighter/change: build Release, run all 12 deterministic tests,
collect a scripted in-game trace, exercise save/load and missing-assets, run the
mod-off test, inspect `git diff --check`, commit engine/game separately, update
the gitlink explicitly, and record the durable result in Beads. Never push.
