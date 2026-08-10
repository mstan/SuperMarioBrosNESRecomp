# Pikachu behavior contract for SMB1

This document is the implementation contract for the first Pikachu release.
It intentionally describes only the agreed subset: locomotion; Jab, forward
tilt, neutral/forward/back/down aerials; Thunder Jolt; Quick Attack; and
Thunder.  It is not a promise to port every SSB64 action state.

The authoritative behavioral reference is the local BattleShip checkout, not
the shipped game or this document:

- `F:\Projects\BattleShip\decomp\src\ft\ftdata.c:10881-11375` maps Pikachu
  motions to source scripts and marks Fair/DAir as `TRANSN_JOINT`.
- `F:\Projects\BattleShip\decomp\src\relocData\242_PikachuMainMotion.c`
  contains the US motion commands and their waits, attack records, effect
  calls, and sound calls.
- `F:\Projects\BattleShip\decomp\src\ft\ftchar\ftpikachu\ftpikachu.h`
  and `ftpikachuspecialhi.c` define Quick Attack's 20-frame start, two 5-frame
  zips, direction threshold, and recovery.
- `ftpikachuspecialn.c`, `ftpikachuspeciallw.c`,
  `src\wp\wppikachu\wppikachuthunderjolt.c`, and
  `src\wp\wppikachu\wppikachuthunder.c` define projectile and Thunder
  ownership/lifetime behavior.

No source asset is copied by this specification.  Models, animations, sound,
and effects must be generated only from the launcher-verified owner ROM into
the external cache, following the Captain Falcon asset gate.

## Coordinate, render, and host rules

- Use the existing `0.08 SMB pixels/source unit` conversion.  The source
  attributes in `243_PikachuMain.c` specify size `0.95`, walk multiplier
  `0.42`, dash `60`, run `55`, gravity `3`, terminal velocity `52`, and two
  source jumps.  Pikachu retains both source jumps: fresh `Up` launches the
  ground jump or, while airborne with one jump remaining, the aerial jump.
  Both use Pikachu's source idle/walk/dash/run/jump/fall motions.
- The default presentation is a side-on approximately 16-pixel-tall Pikachu,
  with a stable
  small-player collision profile.  It must fit every normal two-block SMB
  passage, including the HUD-route opening.  A mushroom, fire flower, and
  damage state may change native game state but must not grow, recolor, or
  substitute Mario's sprite/model.
- Ordinary locomotion is subject to the existing 4 px/frame streamer limit.
  A special may move farther, but each pixel of that motion must be swept
  against SMB1's own collision buffer and every crossed camera/metatile
  boundary must be presented to the streamer.  Never teleport a fighter,
  bypass a ceiling/wall, or leave a deferred position after blocked movement.
- Model root motion is visual only unless a move explicitly declares host
  travel below.  For motions marked `TRANSN_JOINT` (Fair and DAir), remove
  the root track from the model pose before binding joints, exactly as the
  Falcon bridge does.  This avoids a rear-facing/skewed presentation and
  double movement.
- Facing is logical left/right.  The model and every attached effect/projectile
  must mirror with `facing`; a right-moving action may not render left-facing.

## NES input arbitration

| Input edge | Ground result | Air result |
|---|---|---|
| `A` | Jab | Neutral air |
| facing direction + `A` | Forward tilt | Fair if facing direction; Bair if opposite |
| `Down+A` | consumed/reserved | Down air |
| `B`, `Left+B`, or `Right+B` | Thunder Jolt | Thunder Jolt |
| `Up+B` | Quick Attack | Quick Attack |
| `Down+B` | Thunder | Thunder |
| fresh `Up` | source ground jump | source aerial jump when one remains |

Specials outrank A when both edges occur on one emulated frame.  Physical A
and B are masked from SMB's normal jump/run/fireball paths while Pikachu owns
the player.  There is **no Skull Bash and no Side-B** in SSB64; horizontal B
never selects a separate move.

## Move/event table

`[a,b)` means active on source frames `a` through `b - 1`, with frame zero the
frame that consumes the input edge.  Damage is source US damage and is
converted to one conservative SMB enemy contact union per active interval.
Pikachu's physical A attacks may break eligible SMB bricks through the same
host terrain-contact path as Captain Falcon. Thunder Jolt and Thunder are
projectiles and never alter SMB blocks.

| Move | Source animation + motion script | Active frame(s), source damage | Required event(s) and host result |
|---|---|---|---|
| Jab | reloc `2016_FTPikachuAnimJab1`; `0x0E34` | `[2,6)`, 4 | `FGMLightSwingS` at 2; one forward union; no root travel. |
| Forward tilt | reloc `2019_FTPikachuAnimFTilt`; `0x0F50` | `[5,15)`, 10 | `FGMLightSwingM` at 5; one forward union; no root travel. |
| Neutral air | reloc `2026_FTPikachuAnimAttackAirN`; `0x12E8` | `[3,11)`, 14 then `[11,29)`, 11 | `FGMLightSwingM` at 3; body union follows the pose; physical contact may break eligible bricks. |
| Forward air | reloc `2027_FTPikachuAnimAttackAirF`; `0x1380`, `TRANSN_JOINT` | `[7,9)`, `[10,12)`, `[13,15)`, `[16,18)`, `[19,21)`, `[22,24)`, `[25,27)`, each 3 | `FGMPikachuElectric2` at 7, then `FGMMarioUnkSwing2` for each pulse; show electric color/effect on the attack side. |
| Back air | reloc `2028_FTPikachuAnimAttackAirB`; `0x1420` | `[10,14)`, 16 then `[14,22)`, 14 | `FGMLightSwingL` at 10; union is behind logical facing. |
| Down air | reloc `2030_FTPikachuAnimAttackAirD`; `0x14DC`, `TRANSN_JOINT` | `[8,26)`, 13 | `FGMPikachuElectric3` and electric effect at 8; downward union only; physical contact may break eligible bricks. |
| Thunder Jolt | ground `0x15AC`; air `0x15F0` | projectile begins at 21 | `VoicePikachuSpecialN` at entry; air also plays `FGMPikachuElectric5` at entry. Spawn from source joint 11, facing-relative, at -45 degrees with source speed 40. It may defeat eligible enemies once, follows floor/wall surfaces after contact, and expires on unsupported/invalid surfaces. It never changes SMB blocks. |
| Quick Attack | start has no source motion; zip/end `0x1710`, `0x1730` | no hitbox | 20-frame intangible aim startup; first 5-frame zip; after the end-script's 9-frame direction window, one second 5-frame zip only if stick magnitude is at least 60 and differs by more than 42 degrees. `VoicePikachuSpecialHi`, `FGMPikachuElectric1`, and sparkle fire on each zip entry; ripple and rumble fire at each zip end. Render the authored 0.8/0.8/1.2 scale/pitch transform on joint 4. |
| Thunder | start `0x162C`; loop `0x1644`; self-hit `0x1668` | self-hit `[0,10)`, 16 | `VoicePikachuSpecialLw` at entry; spawn a vertical bolt at frame 24 from the gameplay top above Pikachu. While it falls it owns all trail/effect events. On self-contact, consume the bolt, emit ThunderAmp + dust + quake + color event, and give airborne Pikachu source +20 vertical velocity. Pikachu does not take host damage from own Thunder. Thunder may defeat an eligible enemy once but never breaks blocks. |

The `0x0E34`, `0x0F50`, `0x12E8`, `0x1380`, `0x1420`, and `0x14DC`
associations are explicitly established by the US `dFTPikachuMotionDescs`
table at `ftdata.c:11234-11290`; they are not inferred from filename order.
The Thunder Jolt air/ground values and wall/floor conversion are defined in
`wppikachuthunderjolt.c:66-759`; use the existing host persistent-action pool
rather than Mario's fireball slot.

## Recovery and scripted SMB states

- A Quick Attack collision resolves at the first swept solid pixel.  It stops
  at that pixel and enters recovery; it cannot phase through a ceiling, wall,
  floor, HUD-route tile, pipe, or block.  The source's platform pass buffer is
  not an authorization to pass SMB solid tiles.
- After no second zip, recovery has 0.4 normal air drift and source landing
  multiplier `0.4`, per `ftpikachuspecialhi.c:404-553`.  The host must preserve
  this state and its zip/direction counters in savestates.
- Water, pipe entry/exit, flagpole, level transition, injury, growth, and
  death remain native SMB motion/collision timing.  During each scripted
  window, render Pikachu's corresponding presentation or a stable Pikachu
  fallback; never show Mario.  Reseed the controller from native position on
  exit and cancel all active projectiles/effects once.
- Death latches after a single fall below the kill plane.  No controller or
  model may re-enter from the top of the screen before the native respawn.

## Determinism and observable event ABI

The controller must expose a monotonic per-action `action_frame`, a
`persistent_action_id`, and a bitset/queue of logical events:
`VOICE_SPECIAL_N`, `VOICE_SPECIAL_HI`, `VOICE_SPECIAL_LW`, `FGM_LIGHT_S`,
`FGM_LIGHT_M`, `FGM_LIGHT_L`, `FGM_ELECTRIC_1`, `FGM_ELECTRIC_2`,
`FGM_ELECTRIC_3`, `FGM_ELECTRIC_5`, `EFFECT_SPARKLE`, `EFFECT_RIPPLE`,
`EFFECT_THUNDER_AMP`, `PROJECTILE_JOLT_SPAWN`, `PROJECTILE_THUNDER_SPAWN`,
and `PROJECTILE_THUNDER_SELF_HIT`.  Events are emitted once on their listed
frame and survive save/load exactly once: restoring before an event may emit
it on the replay; restoring after it may not duplicate it.

`tests/pikachu_harness/behavior_vectors.json` is the normative machine-readable
companion.  A future harness must reject a controller that selects a different
action, shifts an interval, emits a duplicate event, allows a block mutation,
or permits Quick Attack to cross a solid cell.
