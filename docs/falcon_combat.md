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
script's final decoded keyframe. The generic rectangular hitbox is a portable
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
- Trace flags: `0x100` attack active, `0x200` enemy defeated, `0x400` brick
  broken.
