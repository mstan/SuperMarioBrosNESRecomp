# Session Handoff - Smash 64 Captain Falcon in SMB1

Date: 2026-08-09

## Current QA status: final owner play/listen acceptance remains

The current worktree adds BattleShip-derived Falcon Dive/Up-B on top of the
previously accepted movement, presentation, Falcon Punch, and Falcon Kick
work. Ground and air use their distinct 1658/1661 launch motions and authored
TransN paths; a supported enemy contact enters the 1659 Catch and 1660 Throw
motions, applies one native SMB enemy defeat, and cannot consume a second
overlapping target. Misses use the dedicated 1554 `FallSpecial` motion, its
72%-maximum horizontal drift, and the forced 0.65x `LandingAirX` recovery.

Fresh scripted captures under `C:\temp\falcon_upb_*` cover clean ground and
air launches in both directions, isolated event frames, the frame-13 reversal,
midair contact, Catch, Throw, particle proxies, and save/load. The Catch save
and reload PNGs have the same SHA-256
`D5F0CD04ECFC69E7867518B21F52CCFD28074EC8F4C7132A1187CC6A3E4778C0`.
The trace shows one `attack_connected` edge, one native target consequence,
and no stale second hit. Eleven owner-side audio clips load; Falcon Dive launch,
Catch, explosion, and voice queue at the source-derived frames. The current
isolated Release rerun reproduces those results and additionally passes the
pit/death/reseed and render-fenced scripted-state smokes. Automated QA cannot
judge the final mix by ear, so an owner play/listen pass remains required before
closing the Up-B Bead or running the final integrated QA Bead.

Exact turn/event captures are isolated behind save-state reloads and render
settling; frames 12, 13, and 14 now have distinct hashes. Additional captures
show FallSpecial plus special-landing entry, midpoint, and completion.

The latest Falcon Kick direction concern had two host presentation causes.
The unsupported Kick-only body-yaw override is removed, leaving Captain's
BattleShip `lr * +90`-degree side view. The CaptainSpecial2 card geometry,
facing, and air roll remain source-authored, while its texture U axis now
matches the raw vertices: the boot/root edge (`z=-2`) uses `S≈48`, and the far
taper (`z=-1246`) uses `S=0`. Fresh Release captures
`C:\temp\falcon_kick_air_{right,left}_{12,16,20}.png` and
`falcon_kick_ground_right_{12,18,26}.png` show the bright core at the leading
boot and the taper trailing in both directions. Owner playtest remains the
subjective acceptance gate before closing the reopened Down-B Bead.

Ground Falcon Dive emits `force_airborne` once. Adapter save record v7 bridges
the source animation's subpixel startup across SMB1's integer floor state only
until the first successful upward whole-pixel sweep; the latest save/replay QA
proves the planted startup resumes into the same frame-13 lift (`Y $B0->$A6`).
Exact v6 and v5 readers preserve the owner's existing local slots.

The public controls now preserve Smash 64's split: A is normal, B is special,
and a fresh Up-stick is Falcon's four-frame jump. Neutral A is Jab; horizontal
A is FTilt/Fair/Bair; neutral or horizontal B is Falcon Punch because Smash 64
has no Side-B; Down+B is Falcon Kick; Up+B is Falcon Dive. Directional specials
use the source thresholds (`>= +40`, `<= -40`) with a one-VBlank NES-pad grace
when B arrives first. Specials win a same-frame A+B chord. The fresh trace from
`tests/falcon_input_map_qa.script` records Jab, FTilt, horizontal-B Punch,
stick-jump, and NAir without an accidental SMB jump. Adapter record v7 saves
the grace edge; v6/v5 migration restores it safely.

Falcon now presents a stable Big-Mario collision profile independent of the
hidden native powerup size. Both the high-precision sweep and the four native
`PlayerBGCollision` geometry reads see the same Big profile. PC-scoped RAM-read
hooks leave the actual size/crouch bytes untouched, so later native gameplay
still uses the real power-up state (including bump-vs-shatter brick behavior).
Two additional PC-scoped anchor reads (`$BD57/$BD5C`) align
`Block_Y_Position` with the Big head probe without changing those gameplay
consequences. `tests/falcon_mushroom_emergence_qa.script` and
`C:\temp\falcon_mushroom_{00..80}.png` show the mushroom beginning in the
contacted question-block layer, emerging one tile above it, and sliding there
instead of spawning one block low and falling.
The slot-0 regression walks both native size values through a true
32-pixel/two-block-high corridor and rejects a 16-pixel control. Its QA command
also paints the matching test tiles into the nametable, so
`C:\temp\falcon_clearance_32_big_mid.png` visibly confirms Falcon inside the
two-block opening rather than relying only on an X-coordinate assertion.

The owner's F4 slot exposed a one-tile step down into another proven 32px
cavity. The adapter now admits only that controlled descent when the lowered
Big profile has clear head/side probes and a solid foot; it still rejects a
16px tunnel and refuses the adaptation at SMB1's `$CF` no-collision band. The
native 16px Y change is reconciled once into Falcon's controller position and
serialized in adapter v7. The same repro also exposed wall-bound Kick root
motion wrapping above SMB1's playfield: upward foreign sweeps now clamp at
high-byte 1/Y `$20`, and wall-bound Kick stays airborne there only until its
authored track turns downward. `tests/falcon_slot4_clearance_kick_qa.script`
captures walk, Kick, peak, recovery, and asserts the player high byte never
leaves the map.

Pipe dispatches `$02` (side ingress), `$03` (vertical ingress), and `$07` with
`AltEntranceControl == $02` (vertical egress) now suppress Mario and render a
Falcon pipe pose. Occlusion uses the exact background-opaque coverage captured
by the PPU renderer for the most recently rendered frame, so Falcon passes
behind the pipe instead of being drawn over it. The real slot-0 run asserts
the `$02` and `$07/$0752 == $02` phases and captures partial side entry, full
occlusion, helmet emergence, and the ready Falcon on top of the pipe under
`C:\temp\falcon_slot0_pipe_*.png`.

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
  native Mario death sprite visible. `falcon_death_late_fixed.png` samples the
  rest of the native death delay: after the first fall leaves the screen,
  Falcon stays hidden through every late frame and reappears only in the final
  respawn panel.
- `C:\temp\falcon_second_death_validation_contact.png`: a deterministic
  two-life sequence. The first respawn returns normal Falcon control; the
  second independent pit death starts a fresh tumble, remains empty at late
  frames 64 and 144 after Falcon leaves the view, and ends on a second normal
  Falcon respawn. This closes the reported repeat-from-the-sky regression.
- `C:\temp\falcon_transform_contact.png`: three separated frames each for
  mushroom/grow, damage/injury, and fire-flower scripts; all nine hold the same
  planted Falcon pose with no Mario transformation frame visible.
- `C:\temp\falcon_punch_{right,left}_contact.png`: complete source-frame
  Falcon Punch impact sequences in both directions. Falcon stays side-on and
  the authentic three-frame fire plume stays attached to the forward hand and
  mirrors with facing.
- `C:\temp\falcon_scripted_contact.png`: flagpole-slide, end-level walk, and
  entrance dispatch states all suppress Mario and present Falcon. The separate
  `falcon_entrance_real_contact.png` follows the genuine World 1-2 native
  entrance through its settled playable state.
- `C:\temp\falcon_real_flagpole_early_contact.png` and
  `falcon_real_flagpole_late_contact.png`: 41 owner-provided-save captures of
  the genuine World 1-1 pole contact, full descent, dismount, castle autowalk,
  doorway entry, and native score countdown. Falcon remains visible throughout
  with no Mario fallback; the owner separately playtested and accepted the
  flagpole animation on August 8.
- `C:\temp\falcon_high_jump_contact.png` and
  `falcon_hud_edge_contact.png`: a full high-jump arc and explicit top-edge
  wrap cases show no Mario tile near or behind the HUD.
- `C:\temp\falcon_high_jump_sequence_fixed_scale.png` and
  `falcon_short_jump_sequence_fixed_scale.png`: 17 full-hop frames and 13
  short-hop frames from the former physical-A jump binding. They remain valid
  scale-stability evidence, but the current public map uses Up-stick jump and
  reserves A for normals. The fighter uses one bind-reference scale throughout,
  so crouched and extended source poses do not make the whole model pump or
  stretch.
- `C:\temp\falcon_watchdog_fix_contact.png` and
  `falcon_savestate_endless_loop_survived.png`: the owner's exact slot and a
  durable World 1-2 state both resume at SMB1's `$8057` frame-driver loop and
  continue far beyond the former two-million-instruction watchdog boundary.
  The apparent Falcon-Punch crash was a save-resume interpreter bug, not enemy
  combat; engine commit `52af090` hands a generated direct self-loop back to
  native execution without weakening the watchdog.

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
documented host adaptation. The presentation clock remains latched through
transient native restart states; once Falcon has left the bottom of the view,
the renderer keeps him hidden until ordinary `$08` player control proves a
real respawn.

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
| Engine | `F:\Projects\nesrecomp\_wt-falcon-smb\nesrecomp` | `5ef6145` (contact-only connection ABI/trace; includes forced-air, 2x mesh, and PCM work) |
| Game | `F:\Projects\nesrecomp\_wt-falcon-smb` | current local HEAD; gitlink must point to `5ef6145` |

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
# Expected: 14/14.

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

The SMB1 adapter in `game_smash64.c` owns the host details: scoped 6502
function-entry and PC-qualified RAM-read hooks, horizontal/vertical sweeps
against SMB1's own block buffer, scripted ownership, native enemy defeat, and
native brick shatter.
Confirmed combat entries are `PlayerHeadCollision $BCED`, `BrickShatter $BE02`,
and `ShellOrBlockDefeat $D795`.

Captain Falcon's state machine remains in the quarantined
`mods/smash64/ssb_ported/falcon_locomotion.*`; the publishable character bridge
only translates to/from the generic ABI.

Presentation uses `game_smash64_assets.c`: 26 joints, 319 triangles,
28 textures, and 36 animations. Figatree's one-based joint names are converted
to zero-based model slots by the baker. Motions carrying BattleShip's auxiliary
fighter-root flags omit their first host-owned root stream before joint
binding; this corrects Falcon Punch, TurnRun, JumpB/JumpAerialB, Falcon Kick,
and Falcon Dive's ground/air/throw poses. Blob version 4 stores BattleShip's
source interpolation segments and tangent rates instead of flattening them
into linear keys, plus reloc 333's three CaptainSpecial3 CI4 fire frames and
their embedded RGBA16 palette. Costume-zero primary colors come from reloc 332's
`MatAnimJoint` programs, matching BattleShip's fighter-part material
initialization. The runtime derives one invariant 32-pixel Big-Mario-scale
factor from the model's bind bounds, then uses animated bounds only to center
and foot-anchor each pose. It rotates the authored model 88 degrees into a
near-exact side profile.
`game_smash64_render.c` renders only Falcon at 2x, then box-downsamples coverage
over the native frame; the NES background remains pixel-perfect. Missing model
data uses the cube fallback.

Audio uses `game_smash64_audio.c`: eleven local cues for jump effort, "Falcon",
"Punch", Falcon Kick, Punch impact, Kick swing, Kick energy start, Falcon Dive
launch, Catch, throw explosion, and throw voice. Missing
clips are a silent fallback. The focused offline FGM renderer resolves trigger
indices through BattleShip's `B1_sounds2` sound array and implements the
decoded pitch/envelope/fork/stop commands used by these move programs; this
removes the old `B1_sounds1/wave_019` guitar-like tail without claiming a full
N64 audio-engine emulation. Exact table provenance, renderer timing, spectral
A/B evidence, and sample-exact host-mixer reconstruction are in
`docs/falcon_audio.md`.

## Completed milestones and evidence

- M4 collision: vertical/horizontal tunnelling prevention, wall/ceiling/floor
  reconciliation, native camera delta, and collision matrix.
- M5 gameplay: ordinary/scripted ownership, pipes/water/castle/death handoffs,
  save states, reseed behavior, and mod-off regression.
- M6 rendering: real Falcon model, textures, and authentic animation selection;
  corrected Figatree joint-slot mapping, source interpolation, costume-zero
  material initialization, facing convention, 32px side profile, and 2x edge
  supersampling; exact OAM-slot suppression at the HUD edge; source-derived
  Falcon Punch fire; Falcon presentation during flagpole and native autowalk;
  screenshot-verified planted idle, falling death tumble, bidirectional
  locomotion, jump, Falcon Punch, Falcon Kick, clean title, widescreen, and
  absent-asset fallback.
- M7 combat: Jab, forward tilt, neutral/forward/back air, Falcon Punch, Falcon
  Kick; source hit windows/damage; native SMB1 enemy defeat and `$51/$52` brick
  shatter; nonbreakable/special/boss filtering; save/load and mod-off coverage.
- M8 audio: exact source-frame cue events, eleven ignored local clips, shared
  NES mix, BattleShip-accurate pitch, stop-on-load, mod unload, silent fallback,
  and no per-frame spam.

Key committed evidence/docs:

- `docs/falcon_combat.md`
- `docs/falcon_audio.md`
- `tests/falcon_harness/combat.script`
- `tests/falcon_harness/audio.script`
- `tests/falcon_harness/upb.script`
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
- `tests/falcon_visual_upb_qa.script`
- `tests/falcon_tier4_death_respawn_qa.script`
- `tests/falcon_tier4_mod_off.script`
- `tests/falcon_savestate_endless_loop_qa.script`

The original M8 live trace loads 7/7 Punch/Kick clips and queues every mapping.
The Falcon Dive QA trace now loads 11/11 and additionally queues launch, Catch,
throw explosion, and throw voice. During a Punch
windup save/load, the already-consumed "Falcon" entry call does not replay;
the future frame-42 "Punch" and impact cues each occur once on both genuine
continuations. The August 8 final 12-second capture queues all seven cues; its
first 500 frames match a sample-level reconstruction of native APU plus Falcon
overlays exactly (367,500/367,500 samples). BattleShip establishes a 32 kHz
synthesizer and direct -1200-cent FGM voice ratio, so the voice bytes have a
16 kHz effective playback clock before conversion to the runner's 44.1 kHz.
Current-build mod-off screenshots show ordinary Mario with no Falcon asset or
audio initialization. With the ignored asset quarantine temporarily withheld,
Falcon retains control using the blue cube across idle/run/jump/Punch/Kick,
startup emits one model and one silent-audio fallback, and the script exits
cleanly. The quarantine and Falcon-enabled staged configuration were verified
restored afterward.

The standalone Up-B harness also models a physical ceiling (zero displacement
and upward velocity without changing Falcon Dive state) and enumerates the
adapter's full ordinary-enemy ID boundary. It rejects the frenzy Bullet-Bill
marker, Podoboo, IDs at/above BowserFlame, and the native defeated-state bit.
Runtime static assertions bind those testable policy constants to the generated
SMB symbol values.

`tests/falcon_visual_scripted_presentation_qa.script` now waits two render
frames after directly injecting flagpole, end-walk, or entrance state. This
prevents its first PNG from reusing the prior framebuffer; fresh first-valid
captures show Falcon in all three states rather than a false one-frame Mario.

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
- Scripted presentation is keyed narrowly to SMB1
  `GameEngineSubroutine` values `$02` (side pipe), `$03` (vertical pipe), `$04`
  (flagpole), `$05` (end-level walk), and `$07` (entrance walk or vertical pipe
  exit when `AltEntranceControl == $02`). SMB1 retains all motion and
  progression. Flagpole uses a fixed calm source Fall pose because the
  extracted Smash set has no ladder or pole motion; horizontal walks advance
  source `Walk2`, while vertical pipe travel uses the planted `CrouchIdle`.
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
- Save states commonly capture SMB1 at permanent loop `$8057`. Do not keep a
  generated direct self-loop in the explicit-resume interpreter: unlike a
  returning tail, it has no interpreted ancestor to preserve. Engine commit
  `52af090` probes that exact resume case and re-enters the generated loop;
  `tests/falcon_savestate_endless_loop_qa.script` guards the integration.

## Verification bar

For any future fighter/change: build Release, run all 12 deterministic tests,
collect a scripted in-game trace, exercise save/load and missing-assets, run the
mod-off test, inspect `git diff --check`, commit engine/game separately, update
the gitlink explicitly, and record the durable result in Beads. Never push.
