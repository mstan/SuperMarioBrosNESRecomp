# SMB1 player adapter

> **Status: SKELETON.** This is the M2 deliverable (`beads-2dw.2.1.3`).
> The adapter (`game_smash64.c`) is scaffolded but declines control and
> writes nothing, so SMB1 is currently untouched.

How a foreign movement controller takes ownership of Mario without breaking
the rest of Super Mario Bros.

Framework **RULE 0** applies to everything below: every address and every
6502 function is confirmed in Ghidra before it is read, written or hooked. No
guessing 6502 behaviour. The project file is `ghidra/SuperMarioBrosNES.gpr`.

## Hook point

SMB1's player update runs mid-frame inside recompiled 6502 code, so
frame-boundary hooks (`game_on_frame`, `game_post_nmi`) cannot intercept it.
Taking ownership requires the runtime-toggleable function hook tracked as
`beads-2dw.1.4`.

Candidate targets, from `symbols.sym`:

| Symbol | Address | Role |
|---|---|---|
| `PlayerCtrlRoutine` | `$B0E9` | primary takeover candidate |
| `PlayerMovementSubs` | `$B329` | movement dispatch |
| `MoveSubs` | `$B34E` | |
| `NoMoveSub` | `$B359` | |
| `PlayerPhysicsSub` | `$B450` | |
| `GetPlayerAnimSpeed` | `$B58F` | presentation only |
| `ImposeFriction` | `$B5CC` | horizontal traction |
| `ImposeGravity` | `$BFD7` | shared with sprite objects — check callers |

Confirm each in Ghidra before hooking. Note which are shared with non-player
objects; `ImposeGravity` in particular is used by more than the player.

## Authoritative player state

Confirm every address in Ghidra and cite the confirming function.

| Field | Address | Confirmed in | Notes |
|---|---|---|---|
| Player page | TODO | | |
| Player X (pixel) | TODO | | |
| Player Y | TODO | | |
| X velocity | TODO | | |
| Y velocity | TODO | | |
| X subpixel | TODO | | |
| Facing direction | TODO | | |
| Ground / air state | TODO | | |
| Player size / power state | TODO | | |
| Death state | TODO | | |
| Pipe state | TODO | | |
| Flagpole state | TODO | | |
| Autowalk / scripted state | TODO | | |
| Camera / scroll position | TODO | | |

## Ownership

```text
PLAYER_CONTROL_NATIVE     SMB1 moves the player (mod off)
PLAYER_CONTROL_FALCON     the fighter moves the player (ordinary play)
PLAYER_CONTROL_SCRIPTED   SMB1 sequence in progress — hands back
```

**Never blanket-suppress the player update.** SMB1 has scripted player states
that must stay native:

- entering and exiting pipes
- death
- flagpole
- level intro / autowalk
- power-up transitions, where they interfere
- castle and end-level sequences

| Sequence | Discriminator | Ownership |
|---|---|---|
| TODO | | |

## Coordinate projection

One documented transform, named explicitly, applied at this boundary only.
Do not tune it implicitly across the code.

```text
FALCON_TO_SMB1_X   SMB1_TO_FALCON_X
FALCON_TO_SMB1_Y   SMB1_TO_FALCON_Y
```

Current values are placeholder `1.0`; M0 derives the real scale from a stable
reference (fighter height against source platform geometry versus Mario's
height against SMB1's 16px metatile grid).

## Synchronization writes

Every write back into SMB1 RAM gets a row. Write the minimum SMB1 needs to
observe the player correctly — not every Mario physics variable.

| Address | Field | When written | Why SMB1 needs it |
|---|---|---|---|
| TODO | | | |

If SMB1 later reads a native velocity for unrelated gameplay logic, either
populate a compatible projected value or hook the consumer and give it host
state — and record which was chosen.

## Input mapping

The NES pad is digital; Smash distinguishes walk/dash/run by stick magnitude
and timing. `sample_input()` in `game_smash64.c` produces synthetic analog
values so partial-tilt behaviour stays reachable.

```text
LEFT / RIGHT   ->  stick_x -1.0 / +1.0   (opposing directions cancel)
UP / DOWN      ->  stick_y +1.0 / -1.0
A              ->  jump (held + rising edge)
B              ->  reserved
```

Transitions that pure digital input cannot reach are recorded in
`falcon_movement_dependency.md`.

## Collision

The controller proposes motion; SMB1's tiles remain the only truth about where
the player may go. Substep through `nes_foreign_sweep()` so a fighter moving
far more per frame than Mario cannot tunnel. Do not clamp the fighter to
Mario's speed to make collision work.

## Lifecycle

Host controller state lives outside NES RAM, so a save state that restores RAM
while leaving controller state from another frame puts the player in two
places at once.

| Event | Handling |
|---|---|
| Power-on | TODO |
| ROM reset | TODO |
| Level load | TODO |
| Death / respawn | TODO |
| Pipe transition | TODO |
| Warp | TODO |
| Save state | TODO |
| Load state | TODO |
| Mod enable / disable | TODO |

## Observability

Always-on movement ring — never armed at probe time:

- TCP `ftring` (`{"n":256}`)
- `NESRECOMP_FTRING_DUMP=<path>` for an exit CSV

Rows carry frame, ownership, state, buttons, stick, position, velocity,
requested delta, resolved delta, collision flags, and the native coordinates
written back. If an investigation needs a field that is not there, add the
field to the ring rather than writing a one-shot probe.
