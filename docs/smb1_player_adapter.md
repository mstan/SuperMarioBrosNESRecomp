# SMB1 player adapter

**Status: M2 COMPLETE** (`beads-2dw.2.1.3`). Falcon owns horizontal ground
movement in World 1-1. SMB1 keeps jump, gravity, vertical collision,
horizontal collision and position integration.

Every address below was confirmed in Ghidra (`nes/SuperMarioBrosNES`) before
being read or written — framework RULE 0 — and the confirming instruction is
cited. Names come from `symbols.sym`, emitted into the generated decls header,
so `game_smash64.c` contains no bare literals.

---

## 1. The hook: `ImposeFriction $B5CC`

SMB1 splits player physics cleanly, which made the choice easy once the split
was visible:

| Function | Does |
|---|---|
| `PlayerPhysicsSub $B450` | **vertical** — jump initiation, `JumpSwimTimer`, `VerticalForce`, `Player_Y_Speed`, then tail-calls X_Physics |
| `X_Physics $B51C` | **selects** the frame's speed caps and friction adders; moves nothing |
| `ImposeFriction $B5CC` | **the horizontal integrator** — advances `Player_X_Speed`:`Player_X_MoveForce` from input, clamps to the caps |
| `MoveObjectHorizontally $BF0F` | applies the velocity to position, with SMB1's collision |

So the hook goes on **`ImposeFriction`**. Skipping it and writing our own
velocity leaves everything else intact: SMB1 still integrates, still collides,
still owns the whole vertical axis.

`ImposeFriction` is player-only by construction — it reads
`Player_CollisionBits`, `Player_X_Speed`, `Player_X_MoveForce`,
`Player_XSpeedAbsolute` and the caps all non-indexed — and is called from just
two sites, `GndMove $B363` and `LRAir $B3B0`.

Declared in `game.toml`:

```toml
[[mod_function_hook]]
addr = 0xB5CC           # ImposeFriction
```

That one line is the entire generated-code diff for M2, which is why the
regen (`beads-2dw.2.2`) was landed separately.

### Rejected: hooking `PlayerCtrlRoutine $B0E9`

The obvious target, and wrong for M2. Skipping it would take the vertical axis
too — jump, gravity, the lot — which is M3's job, not M2's.

---

## 2. Velocity representation

`MoveObjectHorizontally $BF0F` is explicit about the units:

```asm
LDA $57,X       ; SprObject_X_Speed
ASL A x4        ; low nibble  -> subpixel accumulator
LDA $57,X
LSR A x4        ; high nibble -> sign-extended pixel delta
```

So **`Player_X_Speed` is a signed 8-bit value in units of 1/16 pixel per
frame**, with the remainder accumulated in `SprObject_X_MoveForce $0400`.

Note `Player_X_MoveForce $0705` is a *different* thing — it is the friction
accumulator `ImposeFriction` uses, not the position subpixel. Easy to conflate;
they are separate bytes with separate roles.

SMB1's own caps, read straight from the ROM:

| Table | Bytes | px/frame |
|---|---|---|
| `MaxRightXSpdData $B443` | `28 18 10 0C` | 2.50, 1.50, 1.00, 0.75 |
| `MaxLeftXSpdData $B440` | `D8 E8 F0` | −2.50, −1.50, −1.00 |
| `FrictionData $B447` | `E4 98 D0` | 228, 152, 208 subpixel/frame |

**Mario's top speed is 2.50 px/frame.** Falcon's run is 6.00 and his dash 6.38
— 2.4× and 2.55× — and both fit inside the signed 8-bit field, which is why
writing `Player_X_Speed` directly works at all.

### The one conversion

```
FALCON_TO_SMB1_XSPEED = 0.08 px/unit * 16 xspeed/px = 1.28
```

Applied in `clamp_xspeed()` and nowhere else. Falcon's `run_speed` 75 → 96,
`dash_speed` 80 → 102.

---

## 3. Ownership

The `GameRoutines $B04A` dispatch table at `$B04F`, decoded from the ROM, is
the whole ownership map — no guesswork:

| `GameEngineSubroutine $000E` | Handler | Ownership |
|---|---|---|
| 0 | `Entrance_GameTimerSetup` | SCRIPTED |
| 1 | `Vine_AutoClimb` | SCRIPTED |
| 2 | `SideExitPipeEntry` | SCRIPTED |
| 3 | `VerticalPipeEntry` | SCRIPTED |
| 4 | `FlagpoleSlide` | SCRIPTED |
| 5 | `PlayerEndLevel` | SCRIPTED |
| 6 | `PlayerLoseLife` | SCRIPTED |
| 7 | `PlayerEntrance` | SCRIPTED (autowalk) |
| **8** | **`PlayerCtrlRoutine`** | **FOREIGN — ordinary play** |
| 9 | `PlayerChangeSize` | SCRIPTED (powerup) |
| 10 | `PlayerInjuryBlink` | SCRIPTED |
| 11 | `PlayerDeath` | SCRIPTED |
| 12 | `PlayerFireFlower` | SCRIPTED |

So `GameEngineSubroutine == 8` **is** plan.md's `PLAYER_CONTROL_FALCON`
condition, and every other value is a sequence that must stay native. This is
better than a hand-maintained list of scripted states: it is the game's own
dispatch table.

Second condition, an M2 simplification: `Player_State $001D == 0` (on the
ground). While airborne, SMB1's own air physics run untouched and the
controller is **not ticked** — its air simulation would disagree with SMB1's
jump and inject a wrong speed on touchdown. The controller holds its ground
state and resumes on landing. M3 takes the air properly.

The ownership check runs **twice**: once per frame in
`game_smash64_update_input` to publish it and record a trace row, and again
inside the hook, where it is authoritative for the frame the game logic
actually runs. The second is defence in depth on top of a structural
guarantee — `ImposeFriction` is only reached during ordinary play at all.

---

## 4. Synchronization writes

Two bytes. Both are the ones `ImposeFriction` itself writes, so no new state is
introduced into SMB1.

| Address | Name | Value | Why SMB1 needs it |
|---|---|---|---|
| `$0057` | `Player_X_Speed` | `round(requested_dx * 1.28)`, clamped ±127 | the velocity `MoveObjectHorizontally` integrates |
| `$0700` | `Player_XSpeedAbsolute` | `abs(Player_X_Speed)` | **not decoration** — `$B51C` reads it to pick the speed tier and `$B4BB` reads it to scale jump height, so a stale value makes Falcon jump like a walking Mario |

Everything else Falcon needs lives host-side in the ported module, per the
host-owned-state rule. No contention for a guest byte.

**Not written, deliberately:** `PlayerFacingDir $0033`. SMB1 sets it from raw
input, which agrees with Falcon's facing in every case M2 exercises. It becomes
a real question when Falcon's TURN state holds a facing the raw input
contradicts — revisit at M3.

---

## 5. Input mapping

`sample_input()` in `game_smash64.c`. A d-pad press moves the synthetic stick
0 → ±80 in one frame, which by the source's tap rule is exactly a fresh stick
tap — so dash, dash→run, brake, turn, short hop, full hop and fast fall are all
reachable. See `falcon_movement_dependency.md` §7.

```text
LEFT / RIGHT  ->  stick_x -80 / +80   (opposing directions cancel)
UP / DOWN     ->  stick_y +80 / -80
A             ->  jump (held + rising edge)
B             ->  reserved (candidate walk modifier)
```

**Correction to the M0 finding.** M0 said walk is unreachable from a d-pad.
That is true *from neutral* — a d-pad always lands at 80 with a fresh tap, so
dash always wins. But the M2 turn trace shows `TURN → WALK_FAST`: after a state
change with the stick already held, `tap_stick_x` has counted past 3, so no
fresh tap exists and the walk check wins. **Walk is reachable mid-sequence,
just not from a standing start.**

---

## 6. Verified behaviour

Scripted run, mod enabled, World 1-1, from the always-on ring:

```
f  28  WAIT        X_Speed    0 =  0.00 px/f
f 621  DASH        X_Speed  102 =  6.38 px/f
f 637  RUN         X_Speed   96 =  6.00 px/f     (+16 frames = dash_to_run)
f1048  RUN_BRAKE   X_Speed   93 =  5.81 px/f
f1054  WAIT        X_Speed   76 =  4.75 px/f
f1059  TURN        X_Speed   65 =  4.06 px/f
f1063  WALK_FAST   X_Speed  -33 = -2.06 px/f     (+4 frames = TURN flag frame)
```

- Dash → run fires exactly 16 frames after dash entry, matching `dash_to_run`.
- Turn flips direction exactly 4 frames in, matching the motion script's
  `SetFlag1` at t=4.
- Peak 6.38 px/frame = **2.55× Mario's own maximum**.
- A/B screenshots at frame 120 of identical held input: vanilla Mario is at the
  first question block, Falcon is past the block row at the pipe.

Ownership handoffs, same run — the ring records **1237 rows for 1236 frames**,
so handoffs appear as transitions rather than gaps:

```
f   0 SCRIPTED   (boot / title)
f  28 FOREIGN
f 302 SCRIPTED   (title -> level load)
f 461 FOREIGN    (gameplay)
f 672 SCRIPTED   (death: ran into a pit at 2.5x speed)
f1048 FOREIGN    (respawn)
```

Death, the death sequence and respawn all behaved natively and control came
back correctly — which is the ownership state machine working, not a bug.

---

## 7. Known-open for M3+

- **Air is SMB1's.** Falcon's jump, gravity, air drift, fast fall and landing
  are M3. Today a jump is Mario's.
- **No swept collision.** The controller is told its motion was granted in
  full; SMB1 refuses it at a wall by not advancing the position. At 6.4 px/frame
  that is a real tunnelling exposure — `beads-2dw.2.1.5` (M4), and
  `nes_foreign_sweep` is already in the engine waiting for it.
- **`TurnRun` is an adaptation**, not Falcon's real run-turn — the original is
  animation-driven. See `falcon_movement_dependency.md` §6.
- **Two provisional durations** (`FL_DASH`, landings) still need the Figatree
  animation length.
- **Save states** do not yet carry the controller's host-side state.
