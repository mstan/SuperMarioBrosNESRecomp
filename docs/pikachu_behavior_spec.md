# Pikachu behavior contract for SMB1

This document is the implementation contract for the first Pikachu release.
It covers the implemented standard-state tranche: locomotion, Run Brake/Turn
Run, crouch, ordinary and attack-air landing, Jab, dash/forward/up/down tilts,
neutral/forward/back/up/down aerials, Thunder Jolt, Quick Attack, and Thunder.
It is not full roster parity; the inventory below names every major missing
source family and the ABI that prevents a faithful controller state today.

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

## Source status and motion inventory

The common status/motion order is authoritative in
`src/ft/ftdef.h:296-500,505-764`; Pikachu's actual non-null motion entries are
in `src/ft/ftdata.c:10881-11375`. A common status existing in the enum does not
mean Pikachu owns a distinct motion for it. In particular, Pikachu's NAir and
BAir landing-motion entries are null and route to `LandingAirNull`, while Fair
and DAir own relocations 2031 and 2032. The executable coverage companion is
`tests/pikachu_harness/behavior_vectors.json#source_status_inventory`.

| Source family | Controller coverage | Missing source statuses / motions | Faithful-port blocker |
|---|---|---|---|
| Standard locomotion | Wait; WalkSlow/Middle/Fast; Dash; Run; RunBrake; TurnRun; KneeBend and both Jump directions; both JumpAerial directions; Fall/FallAerial; Squat/Wait/Rv; LandingLight/Heavy; FallSpecial/LandingFallSpecial | WalkEnd, common Turn, GuardKneeBend, Pass/GuardPass, OttottoWait/Ottotto | The NES input has no analog tier history, platform-drop surface, edge-balance geometry, or shield-jump chord. Walk direction tiers are deterministic projections, not a claim that a D-pad recreates analog input. |
| Ground attacks and smashes | Attack11, AttackDash, neutral AttackS3, AttackHi3, AttackLw3 | AttackS3Hi (reloc 2018), AttackS3Lw (2020), AttackS4 (2023), AttackHi4 (2024), AttackLw4 (2025) | `PikachuInputRaw` has no stick-tap age, held-A duration, or C-button edge, so tilt-versus-smash selection cannot match `hold_stick_{x,y}`. `PikachuAttack` also lacks angle, base/set/growth knockback, hitlag, element, and per-joint hitboxes. Damage values alone must not be presented as combat parity. |
| Aerial attacks and landings | AttackAirN/F/B/Hi/Lw; LandingAirNull, LandingAirF, LandingAirLw | Successful smooth landing / Z-cancel | The input ABI has no Z-trigger edge or `tics_since_last_z`. This controller therefore implements the source's missed-Z branch only; it does not substitute jump, attack, or special as an invented Z input. |
| Grab and throws | None | Catch, CatchPull, CatchWait, ThrowF, ThrowB and all capture/thrown counterparts | No grab input, opponent object, capture ownership, throw victim transform, percent, or launch contract exists. |
| Shield, dodge, and shield break | None | GuardOn/Guard/GuardOff/GuardSetOff, EscapeF/EscapeB, ShieldBreakFly/Fall/Down/Stand, FuraFura/FuraSleep | No shield pressure/button, shield health, intangibility/hurtbox, or roll collision contract exists. |
| Taunt | None | Appeal (reloc 1997, motion 0x0E1C) | No taunt input edge is exposed. |
| Damage, knockdown, and tech | Native SMB handoff only | DamageHi/N/Lw/Air/E, DamageFlyHi/N/Lw/Top/Roll, WallDamage, DamageFall, DownBounce/Wait/Stand/Forward/Back/Attack, Passive/PassiveStandF/PassiveStandB, Rebound | No percent, attacker, launch vector, hitstun, tumble, wall/ground tech input, or surface-normal contract exists. |
| Ledge | None | CliffCatch/Wait/Quick/Slow and all CliffClimb/Attack/Escape variants | SMB collision exposes neither ledge identity nor ledge occupancy, hang offset, ledge invulnerability, or get-up choice. |
| Death, entry, and respawn | Native SMB death/respawn ownership with Pikachu presentation fallback | DeadDown/LeftRight/UpStar/UpFall, Entry, RebirthDown/Stand/Wait; Pikachu Appear1/Appear2 motions 2081/2082 | The controller has no stocks, blast zones, camera-death route, respawn platform, or lifecycle authority. Replacing native SMB timing locally would create two competing death systems. |

Item pickup/throw, Hammer, pipe, tornado, capture, and other stage/item common
statuses are likewise outside the fighter-only ABI. They are intentionally not
silently mapped to Wait.

No source asset is copied by this specification.  Models, animations, sound,
and effects must be generated only from the launcher-verified owner ROM into
the external cache, following the Captain Falcon asset gate.

## Coordinate, render, and host rules

- Use the existing `0.08 SMB pixels/source unit` conversion.  The source
  attributes in `243_PikachuMain.c` specify size `0.95`, walk multiplier
  `0.42`, dash `60`, run `55`, gravity `3`, terminal velocity `52`, and two
  source jumps. Pikachu retains both source jumps: fresh `Up` launches the
  ground jump or, while airborne with one jump remaining, the aerial jump.
  Both use the source `((80 * 0.67) + 37) * jump_height = 90.6` vertical
  launch and `0.35 * stick_x` horizontal launch, before normal gravity.
  Both use Pikachu's source idle/walk/dash/run/jump/fall motions.
- A full directional press enters Dash for source frames 0 through 12 and
  transitions to Run at frame 13. Run persists while the same full direction
  remains held; it must not collapse into Walk after one frame. The dash
  begins decelerating by the source `4.5` friction attribute at frame 7; Run
  then installs the source run speed `55` at the transition. Walk1/2/3 remain
  the low/middle/high analog walk tiers;
  an ordinary digital NES direction naturally takes the Dash-to-Run path.
- Releasing Run enters Run Brake (source traction `2 * 1.25 = 2.5` per
  frame). Reversing a held full run enters Turn Run, keeps the old facing and
  speed through frame 12, flips facing and run velocity at frame 13, and
  returns to Run at frame 18. This follows the frame-13 flags in `0x00E4`;
  it is distinct from the separate common Turn used to reverse during Dash.
- Down without an A edge enters 4-frame Crouch, then Crouch Wait; release
  plays the 8-frame Crouch End. Attack-air collision follows
  `ftCommonAttackAirProcMap`: when the move's flag1 window is active, NAir and
  BAir use the 8-frame LandingAirX motion at flag1's 50% speed (16 ticks), Fair
  uses its 16-frame authored landing, and DAir uses its 40-frame authored
  landing. UAir never sets flag1. Outside a flag window, vertical velocity
  above `-20` skips the ordinary landing motion; `-20` itself does not. These
  state values are append-only in savestates; all pre-existing state ordinals
  remain unchanged.
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
- Quick Attack is the narrow finite-burst exception.  Its source values remain
  330 and 297 units/tick in the fighter state, but the host snapshots one
  direction-preserving collision plan at each zip: at parser debt below `$20`,
  ZIP1 may use 16 px/component/tick (80 px cardinal total); at debt below
  `$6C`, ZIP2 may use 14.4 px/component/tick (72 px cardinal total).  At or
  above either boundary it uses 4 px/component/tick.  This is not a claim that
  SMB1 can safely stream the 132/118.8 px source distances: ZIP1 incurs 60 px
  of finite debt, the nine-frame aim repays 36 px, and ZIP2 incurs 52 px from
  its admitted starting range, remaining below the signed `$A0` hazard.
  The profile owns the thresholds; the generic adapter neither identifies
  Pikachu states nor mutates its source velocity.  The complete selected plan
  is serialized in adapter save v9.  Older adapter records fall back to 4 px
  until the coupled action ends, never re-deciding an active zip from live RAM.
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
| `Up+A` | Up tilt | Up air |
| `Down+A` | Down tilt | Down air |
| full held run + facing direction + `A` | Dash attack | n/a |
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
| Dash attack | reloc `2017_FTPikachuAnimDashAttack`; `0x0E80` | `[4,23)`, 12 | `FGMLightSwingL` at 4; one forward union; no root travel. Regression rule: source macros are `(aid,gid,jid,damage,...,kbb)`; the record's 40 is KBB, not damage. |
| Up tilt | reloc `2021_FTPikachuAnimUTilt`; `0x0FF0` | `[5,15)`, 11 | `FGMLightSwingM` at 5; upward union; no root travel. The same fourth-argument rule prevents regressing this to 10. |
| Down tilt | reloc `2022_FTPikachuAnimDTilt`; `0x103C` | `[6,14)`, 12 | `FGMLightSwingM` at 6; low forward union; no root travel. |
| Neutral air | reloc `2026_FTPikachuAnimAttackAirN`; `0x12E8` | `[3,11)`, 14 then `[11,29)`, 11 | `FGMLightSwingM` at 3; body union follows the pose; physical contact may break eligible bricks. |
| Forward air | reloc `2027_FTPikachuAnimAttackAirF`; `0x1380`, `TRANSN_JOINT` | `[7,9)`, `[10,12)`, `[13,15)`, `[16,18)`, `[19,21)`, `[22,24)`, `[25,27)`, each 3 | `FGMPikachuElectric2` at 7, then `FGMMarioUnkSwing2` for each pulse; show electric color/effect on the attack side. |
| Back air | reloc `2028_FTPikachuAnimAttackAirB`; `0x1420` | `[10,14)`, 16 then `[14,22)`, 14 | `FGMLightSwingL` at 10; union is behind logical facing. |
| Down air | reloc `2030_FTPikachuAnimAttackAirD`; `0x14DC`, `TRANSN_JOINT` | `[8,26)`, 13 | `FGMPikachuElectric3` and electric effect at 8; downward union only; physical contact may break eligible bricks. |
| Up air | reloc `2029_FTPikachuAnimAttackAirU`; `0x1490`, `TRANSN_JOINT` | `[3,11)`, 10 | `FGMLightSwingM` at 3; upward union follows the pose; physical contact may break eligible bricks. |
| NAir / BAir missed-Z landing | reloc `1976_FTPikachuAnimLandingAirX`; `0x1574` | NAir flag `[3,29)`, BAir flag `[10,22)`; no hitbox | The motion is 8 source animation frames at flag1 `50` percent speed, hence 16 controller ticks. Play Pikachu landing and heavy-double dust at entry. |
| Fair missed-Z landing | reloc `2031_FTPikachuAnimLandingAirF`; `0x13EC` | selected from Fair flag `[7,27)`; landing hitbox `[0,2)`, 6 | Dedicated 16-frame landing; Pikachu landing sound and heavy-double dust at entry. The hitbox is created by the landing script, not carried over from Fair. |
| DAir missed-Z landing | reloc `2032_FTPikachuAnimLandingAirD`; `0x1534` | selected from DAir flag `[0,26)`; no landing hitbox | Dedicated 40-frame landing; dead-slam sound, heavy-double dust, impact wave, and magnitude-1 quake at entry. The aerial hitbox is cleared by the status transition/script. |
| Thunder Jolt | ground `0x15AC`; air `0x15F0` | projectile begins at 21 | `VoicePikachuSpecialN` at entry; air also plays `FGMPikachuElectric5` at entry. Spawn from source joint 11, facing-relative, at -45 degrees with source speed 40. It may defeat eligible enemies once, follows floor/wall surfaces after contact, and expires on unsupported/invalid surfaces. It never changes SMB blocks. |
| Quick Attack | start has no source motion; zip/end `0x1710`, `0x1730` | no hitbox | `FGMPikachuSpecialHiStart` begins the 20-frame intangible aim startup. A first aim at stick length `<=60` is source-defaulted to `(0,80)` (UP), never facing-horizontal; this makes neutral Up+B then Right a valid 90-degree route. Each source zip is normalized `stick * (3 * min(|stick|,80)+90)`, so full cardinal is 330 source units; the second is 0.9x (297). The first is exactly 5 frames; after the end-script's 9-frame direction window, one second 5-frame zip only occurs if stick magnitude is at least 60 and differs by more than 42 degrees. Zip end backs velocity up by 0.2, repeats the 46-frame UpSpecialAirEnd animation, then enters FallSpecial with source 0.4 drift/landing-speed parameters. `VoicePikachuSpecialHi`, `FGMPikachuElectric1`, and sparkle fire on each zip entry; ripple and rumble fire at each zip end. Render the authored 0.8/0.8/1.2 scale/pitch transform on joint 4. |
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
- After no second zip, the 46-frame recovery backs the zip vector up by 0.2.
  On exactly that end-frame it enters the append-only aerial `FALL_SPECIAL`
  state, which has ordinary source 0.4 drift and no Quick Attack root-burst,
  coupled-DDA, or ceiling-barrier host traits. A floor contact enters the explicit
  append-only `FALL_SPECIAL_LANDING` state (20 host ticks for the 8-frame
  source motion at 0.4), not ordinary `GROUND_WAIT`.  The host must preserve
  this state and its zip/direction counters in savestates; a v1 controller
  save in any active Quick Attack phase is rejected rather than guessing its
  missing end/recovery clock.
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
`FGM_ELECTRIC_3`, `FGM_ELECTRIC_5`, `FGM_QUICK_ATTACK_START`,
`EFFECT_SPARKLE`, `EFFECT_RIPPLE`,
`EFFECT_THUNDER_AMP`, `PROJECTILE_JOLT_SPAWN`, `PROJECTILE_THUNDER_SPAWN`,
and `PROJECTILE_THUNDER_SELF_HIT`.  Events are emitted once on their listed
frame and survive save/load exactly once: restoring before an event may emit
it on the replay; restoring after it may not duplicate it.

Attack-air landings additionally expose `FGM_LANDING`, `FGM_DEAD_SLAM`,
`EFFECT_DUST_HEAVY_DOUBLE`, `EFFECT_IMPACT_WAVE`, and `EFFECT_QUAKE_MAG1`.

`tests/pikachu_harness/behavior_vectors.json` is the normative machine-readable
companion.  A future harness must reject a controller that selects a different
action, shifts an interval, emits a duplicate event, allows a block mutation,
or permits Quick Attack to cross a solid cell.
