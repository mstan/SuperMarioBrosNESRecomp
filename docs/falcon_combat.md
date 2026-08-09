# Captain Falcon combat in SMB1

M7 adds a deliberately small combat layer without replacing SMB1's enemy or
block systems. Captain Falcon publishes one source-space attack rectangle; the
SMB1 adapter converts it with the same uniform `0.08 px/unit` scale used by
movement and maps overlaps to native SMB1 consequences.

## NES controls

| Input | Ground | Air |
|---|---|---|
| A | Jab | Neutral air |
| Left/Right+A | Forward tilt | Forward/back air relative to facing |
| Up/Down+A | Reserved; source normals not ported yet | Up+A reserved; Down+A is DownAir |
| B or Left/Right+B | Falcon Punch | Falcon Punch |
| Down+B | Falcon Kick | Falcon Kick |
| Up+B | Falcon Dive | Falcon Dive |
| Up | Four-frame stick jump | Four-frame stick jump from ground only |

A and B preserve Smash 64's primary/special split. The NES has no C buttons,
so a fresh Up-stick is the jump adaptation; this reaches Falcon's authored
four-frame `KneeBend`, but the old A-tap short-hop binding is no longer exposed.
While Falcon owns the player, physical A and B are masked at
`PlayerPhysicsSub` so SMB1 cannot also jump, run, or throw a fireball. The
adapter synthesizes A only on Falcon's actual jump-launch frame. With the mod
off, SMB1 sees both buttons normally. Jumpsprings are the intentional exception:
while `JumpspringAnimCtrl` is active, native physical A remains visible so the
original spring-boost timing still works.

A neutral and horizontal reach `Jab`, `FTilt`, `NAir`, `Fair`, and `Bair`.
Down+A in the air reaches the authentic `AttackAirD`; Up+A and grounded Up/Down
A remain consumed and reserved until their real source motions are ported.
They never alias to a special. Smash 64 has no Side-B, so horizontal B remains
Falcon Punch and an opposite direction turns Falcon before it begins. Specials
have source interrupt priority if A and B rise on the same frame.

## Source fidelity and adaptations

The hit windows and damage come from the commands in the pinned decomp's
`235_CaptainMainMotion.c`. The rendered poses come directly from Figatree
scripts 1619, 1628, 1638–1640, 1652–1654, and 1657; state lengths use each
script's final decoded keyframe. Motions tagged with BattleShip's auxiliary
fighter-root flags skip their first root-motion stream before binding the
remaining Figatree streams to Falcon's model joints. This matches
`lbCommonAddFighterPartsFigatree`; treating that stream as model joint zero was
the cause of the formerly back-facing Falcon Punch and malformed Kick pose.

Falcon Punch's visible fire is also source-derived. The local baker decodes
BattleShip reloc 333 (`CaptainSpecial3`) as three 32x32 CI4 frames using its
embedded RGBA16 palette, while the runtime follows `ftcaptainspecialn.c` by
attaching the effect to fighter joint 16 (baked model slot 12) for source
frames 42 through 54. The quad is mirrored with facing and enlarged around its
hand-side corner for readability after Falcon is normalized to a 32-pixel NES
fighter. The ROM-derived reloc and baked pixels remain ignored local assets.

The generic rectangular hitbox is a portable union around the source collision
spheres because SMB1 has no joint-aware combat system. Falcon Kick and Falcon
Dive retain their BattleShip TransN tracks in the quarantined runtime blob.
The character bridge samples the exact current/next-frame root delta, removes
it from the mesh pose, and projects it through the same host scale as every
other source-space motion. This keeps model travel and collision travel on one
authored trajectory.

DownAir uses Figatree 1642 and the source motion's 40-frame duration. Its two
joint spheres are represented by one conservative host union, active at source
frames 7 through 24 for 14 damage and angle -80. `LightSwingL` plays once at
frame 7; the source authors no particle effect for this normal. Breaking an
ordinary brick beneath Falcon is an intentional SMB terrain adaptation and
does not reuse Down+B's fire card or root motion.

Falcon Dive is split exactly by source action: grounded launch uses
`FalconDive`/1658, aerial launch uses `FalconDiveEnd2`/1661, Catch uses
`CatchingEnemyWhileDiving`/1659, and Throw uses `FalconDiveEnd1`/1660. Both
launches force air, consume Falcon's jump, open the catch union at source frame
13, permit the source's one frame-13 stick-directed turn, and miss into a
special fall at frame 65. That helpless state keeps ordinary air acceleration
but clamps horizontal drift to 72% of Falcon's normal maximum, then forces the
common `LandingAirX` recovery at the source's 0.65 animation rate. A valid
connection stops the launch, plays 16 frames of Catch and 60 frames of Throw,
then returns to normal fall.
Because FalconDive's pre-launch TransN rise is smaller than one NES pixel,
the SMB adapter preserves the controller's single departure edge until its
first successful upward whole-pixel sweep. This host-side quantization bridge
is saved in adapter record v7 (with exact v6 and v5 migration), releases as soon as Falcon visibly separates
from the floor, and is cleared on any scripted/native ownership handoff.

SMB1 has no persistent fighter-capture object. Its safe adaptation applies the
source throw's eventual 20-damage consequence immediately through one native
`ShellOrBlockDefeat`, then reserves the remaining Catch/Throw time for Falcon's
visual and audio presentation. `FOREIGN_ATTACK_CONTACT_ONLY` lets the host
confirm one supported target back to the portable controller. The adapter
retires that volume immediately and again after resolve, preventing a stale
pre-Catch frame from defeating a second overlapping enemy. Blocks, hazards,
special objects, and bosses never enter the contact path.

## Native SMB1 consequences

Headless Ghidra validation against `nes/SuperMarioBrosNES` confirmed:

- `PlayerHeadCollision` at `$BCED` and `BrickShatter` at `$BE02`;
- `ShellOrBlockDefeat` at `$D795`;
- the block-buffer bases from the table at `$9BDD` (`$0500`/`$05D0`).

Enemy hits call `RelativeEnemyPosition` followed by `ShellOrBlockDefeat`, so
SMB1 owns defeated state, score, floatey number, and sound. The adapter rejects
already-defeated enemies, frenzy Bullet Bills, Podoboos, special objects, and
Bowser-class IDs.

Only ordinary brick metatiles `$51` and `$52` are eligible for Punch/Kick
terrain damage. The adapter presents the target to `PlayerHeadCollision` as a
Big-Mario head contact, producing SMB1's own block-buffer/VRAM update, debris,
50 points, and brick-shatter sound. Question blocks, pipes, scenery, castle
tiles, and other nonbreakable metatiles are never passed to that routine. After
native shatter changes the collision cell to temporary `$23`, the adapter
commits its eventual zero immediately so a broad multi-frame Falcon attack
cannot leave a visually blank but collision-solid orphan when SMB1's two block
object slots are busy.

## Evidence

- `tests/falcon_harness/combat.script` checks all move selections, exact active
  windows/damage, Punch/Kick/DownAir break flags, and active-window save
  roundtrips.
- `tests/falcon_dair_block_qa.script` captures DownAir startup, active, and
  recovery frames, injects a fresh `$51` only after ascent, proves native blue
  debris and an immediate `$00` collision result, and preserves adjacent `$54`.
- `tests/falcon_air_downb_block_qa.script` independently performs aerial
  Down+B, injects its fresh `$51` immediately before the source 12..<32 active
  window, and proves Falcon Kick's unchanged authored descent breaks it,
  preserves both `$54` neighbors, and lands on-map.
- `tests/falcon_upb_block_barrier_qa.script` proves Dive cannot phase through a
  five-brick ceiling or start a native block transaction, while the identical
  ordinary stick jump still performs SMB1's `$52` bump.
- `tests/falcon_harness/upb.script` checks the two launch states, frame-13
  20-damage contact-only window, confirmed Catch, Catch/Throw audio masks,
  Catch and Throw save roundtrips, special-fall drift/landing recovery, and
  source-frame reversal. It additionally proves a host ceiling clamps both
  displacement and upward velocity without cancelling Falcon Dive, and
  enumerates every accepted ordinary ID plus the Bullet-Bill-frenzy, Podoboo,
  special/Bowser, and already-defeated rejection branches through the same
  pure target-policy helper used by the runtime.
- `tests/falcon_m7_combat.script` seeds a Goomba, one brick, and adjacent
  nonbreakable scenery, then validates native Punch and Kick consequences.
- `tests/falcon_m7_savestate.script` saves during Punch windup and demonstrates
  the same enemy+brick consequence before and after load.
- `tests/falcon_visual_punch_effect_qa.script` captures the complete active
  fire sequence facing both right and left; acceptance requires a side-on pose
  and a hand-attached plume on the attack side in both directions.
- `tests/falcon_visual_upb_qa.script` captures clean grounded and aerial launch
  arcs in both directions, isolated frames 12/13/14, Catch/Throw, compact
  source-timed particle proxies, a two-target one-shot contact, and an
  image-identical Catch save/load replay. The exact turn captures are isolated
  behind reload/render fences; their three hashes differ, avoiding the former
  asynchronous duplicate-frame false evidence. It also captures FallSpecial
  and the 0.65x forced landing at entry/midpoint/completion.
- `tests/falcon_visual_scripted_presentation_qa.script` waits two rendered
  frames after direct state injection, so its first flagpole, end-walk, and
  entrance images prove Falcon presentation instead of recording the preceding
  asynchronous framebuffer.
- Trace flags: `0x100` attack active, `0x200` enemy defeated, `0x400` brick
  broken, `0x800` Falcon Dive contact confirmed, and `0x1000` the one-tick
  controller-to-host airborne edge. CSV and live `ftring` output also expose
  the contact verdict as the named `attack_connected`/`contact` field.
