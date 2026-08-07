# Captain Falcon locomotion — dependency map

> **Status: SKELETON.** This is the M0 deliverable
> (`beads-2dw.2.1.1`) and is not yet filled in. Integration does not begin
> until this document is complete enough to implement from.

Source: `VetriTheRetri/ssb-decomp-re` at
**`054ffc23f396868cd1db2b87ee3a2c1d3bebb75a`** (branch `main`, 2026-08-04).
Local checkout: `F:\Projects\SmashBrosDecomp`.

## Rules for filling this in

- **No guessing.** Where a path is undecompiled or ambiguous, say so and cite
  the matching assembly or symbol. Do not invent behaviour to close a gap.
- Cite `file:line` at the pinned revision for every claim.
- Record every intentional adaptation the SMB1 environment forces, and why.
- Attribute nothing to "feel". If a value is not traceable to the source or a
  verified runtime trace, it is not done.

## Areas confirmed present at the pinned revision

```text
src/ft/ftphysics.c, ftphysics.h
src/ft/ftparam.c
src/ft/ftdata.c
src/ft/ftcommon.h, ftcommondata.c
src/ft/fttypes.h, ftdef.h, fighter.h
src/ft/ftchar/ftcaptain/
src/ft/ftcommon/ftcommondash.c
src/ft/ftcommon/ftcommonjump.c
src/ft/ftcommon/ftcommonjumpaerial.c
src/ft/ftcommon/ftcommonkneebend.c
src/ft/ftcommon/ftcommonlanding.c
src/ft/ftcommon/ftcommonlandingair.c
src/ft/ftcommon/ftcommonfall.c
```

Walk / wait / turn / run / stop live under `src/ft/ftcommon/` as well;
confirm the exact filenames against the checkout rather than assuming them.

## Transitions to trace

| # | Transition | Status |
|---|---|---|
| 1 | idle → walk | TODO |
| 2 | idle → dash | TODO |
| 3 | dash → run | TODO |
| 4 | run → stop | TODO |
| 5 | run → turn | TODO |
| 6 | ground → jump squat | TODO |
| 7 | jump squat → airborne | TODO |
| 8 | airborne horizontal movement | TODO |
| 9 | gravity | TODO |
| 10 | fast fall | TODO |
| 11 | landing | TODO |
| 12 | landing → idle/run | TODO |

### Record per transition

```text
State
Entry function
Per-frame update function
Physics function
Interrupt / transition function
Required fighter fields
Required character attributes
Required globals
Required helper functions
Collision dependency
Animation dependency
Audio / effect dependency
```

## Classification

Every dependency lands in exactly one bucket. The closure must exclude the
Smash renderer, object manager, stage system and combat.

| Bucket | Members |
|---|---|
| REQUIRED MOVEMENT LOGIC | TODO |
| OPTIONAL PRESENTATION | TODO |
| SMASH-STAGE-SPECIFIC COLLISION | TODO |
| COMBAT-ONLY | TODO |
| AUDIO / EFFECTS | TODO |
| UNRELATED ENGINE | TODO |

## Captain Falcon attributes

Extracted from `ftparam.c` / `ftdata.c`, in the source's own units. The single
world-scale conversion happens in the SMB1 adapter, not here.

| Attribute | Value | Source | Notes |
|---|---|---|---|
| Ground acceleration | TODO | | |
| Max walk speed | TODO | | |
| Dash speed | TODO | | |
| Max run speed | TODO | | |
| Traction / deceleration | TODO | | |
| Turn duration | TODO | | |
| Jump squat frames | TODO | | |
| Initial jump velocity | TODO | | |
| Short hop velocity | TODO | | distinguished from full hop? |
| Gravity | TODO | | |
| Terminal velocity | TODO | | |
| Air acceleration | TODO | | |
| Air drift limit | TODO | | |
| Fast-fall velocity | TODO | | |
| Landing lag | TODO | | |

## Unreachable with digital input

Smash differentiates behaviour by stick magnitude and timing; the NES pad is
digital. Record here which transitions become unreachable, and which the
adapter can synthesize (a walk modifier, a tap-dash detector, or a real analog
stick through the pad layer).

| Transition | Reachable? | Mitigation |
|---|---|---|
| TODO | | |

## Exit criterion

A bounded set of source functions and data that completely explains basic
Falcon locomotion, with the classification above applied and the attribute
table populated.
