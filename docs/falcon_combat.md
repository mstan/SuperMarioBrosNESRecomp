# Captain Falcon combat in SMB1

M7 adds a deliberately small combat layer without replacing SMB1's enemy or
block systems. Captain Falcon publishes one source-space attack rectangle; the
SMB1 adapter converts it with the same uniform `0.08 px/unit` scale used by
movement and maps overlaps to native SMB1 consequences.

## NES controls

| Input | Ground | Air |
|---|---|---|
| B | Falcon Punch | Falcon Punch |
| Down+B | Falcon Kick | Falcon Kick |
| Left/Right+B | Forward tilt | Forward/back air relative to facing |
| Up+B | Jab 1 | Neutral air |

A remains jump. While Falcon owns the player, B is masked at
`PlayerPhysicsSub` so SMB1 cannot also run or throw a fireball. With the mod
off, SMB1 sees B normally.

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

The generic rectangular hitbox is a portable
union around the source collision spheres because SMB1 has no joint-aware
combat system. Falcon Kick's translation is an explicit adaptation: Smash 64
derives it from the animated TransN joint, while the quarantined state machine
does not run the model evaluator.

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
tiles, and other nonbreakable metatiles are never passed to that routine.

## Evidence

- `tests/falcon_harness/combat.script` checks all move selections, exact active
  windows/damage, Punch/Kick break flags, and an active-window save roundtrip.
- `tests/falcon_m7_combat.script` seeds a Goomba, one brick, and adjacent
  nonbreakable scenery, then validates native Punch and Kick consequences.
- `tests/falcon_m7_savestate.script` saves during Punch windup and demonstrates
  the same enemy+brick consequence before and after load.
- `tests/falcon_visual_punch_effect_qa.script` captures the complete active
  fire sequence facing both right and left; acceptance requires a side-on pose
  and a hand-attached plume on the attack side in both directions.
- Trace flags: `0x100` attack active, `0x200` enemy defeated, `0x400` brick
  broken.
