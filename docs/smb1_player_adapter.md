# SMB1 player adapter

**Status: M2 + M3 + M3.5 COMPLETE** (`beads-2dw.2.1.3`, `beads-2dw.2.1.4`,
`beads-2dw.2.1.9`). Falcon owns horizontal movement, vertical motion — jump
velocity, gravity, terminal velocity, fast fall and air drift — and, since M3.5,
jump **timing**: his 4-frame jumpsquat runs and decides short hop versus full
hop. SMB1 still decides when a landing happens, and owns all collision and every
scripted sequence.

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

### The second hook: `MovePlayerVertically $BF4D`

M3's hook, and the reason it has to be a hook at all rather than a set of
numbers fed to SMB1:

```asm
MovePlayerVertically:
    ldx #$00
    lda VerticalPipeEntry-ish guards ($0747, $070E)   ; jumpspring / pipe
    lda VerticalForce      ; $0709 — the gravity amount
    sta $00
    lda #$04               ; <-- MAXIMUM Y SPEED
    jmp ImposeGravitySprObj ; $BFAD -> ImposeGravity $BFD7
```

`ImposeGravity`, decoded from the ROM, does three things:

```
YMF_Dummy   += Y_MoveForce                    ; sub-fraction accumulate
Y_Position  += Y_Speed, sign-extended into Y_HighPos
Y_MoveForce += gravity, carry into Y_Speed, then CLAMP Y_Speed to the max
```

That `#$04` caps the player's fall at **4 px/frame**. Falcon's terminal velocity
is 5.28 px/frame and his fast fall is 8.00. The clamp is applied *inside* the
routine, after the gravity add, so it cannot be pre-empted from outside: feeding
SMB1 Falcon's gravity would silently delete fast fall. So we skip the routine
and integrate ourselves, with no clamp.

Vertical **collision** is untouched — `PlayerBGCollision` runs separately, after
`PlayerMovementSubs`, and still corrects the position we wrote. This stays
"controller proposes, SMB1 resolves".

Reached only from `ExitMov1` at the tail of `LRAir`, i.e. only while airborne,
so the hook never fires on a ground frame.

#### The handoff frame belongs to SMB1

SMB1 decides to jump **during** the frame (`InitJS`, inside `PlayerPhysicsSub`),
but the controller ticks at VBlank, **before** the frame. On the very frame the
host launches, Falcon is still in jumpsquat with `vel_air_y = 0`.

Integrating that moves the player zero pixels — and SMB1's foot check then lands
him on the spot. Measured, before the guard: the ring showed a single `JUMP_F`
frame followed immediately by `LANDING_LIGHT`, and the jump visibly did not
happen at all.

So when the hook finds the controller still reporting `grounded`, it returns 0
and lets the original run for that one frame. The cost is the difference between
SMB1's -5 px and Falcon's -6.7 px, once. By the next VBlank `Player_State` is 1,
the controller reconciles into a real jump, and every frame after that is ours.
The same guard covers walking off a ledge.

### The third hook: `PlayerPhysicsSub $B450` — M3.5, jump *timing*

M3 gave Falcon the jump *physics* and left SMB1 owning the jump *trigger*.
`CheckForJumping $B479` fires `InitJS` on the A button's **rising edge**, so
Falcon's 4-frame `KneeBend` had nowhere to live and the short-hop branch of
`jump_force_button` was unreachable — every jump was a full hop. M3 had also
bypassed SMB1's *own* variable jump height as a side effect (`JumpSwimSub` swaps
`VerticalForce` for `VerticalForceDown` when A is released, and the `$BF4D` hook
never reads `VerticalForce`), so there was no height variety left at all.

The fix does **not** contest `Player_State`. It makes SMB1 see the press *late*:
withhold the A bit in `A_B_Buttons $000A` for the squat, then present it on the
frame Falcon actually leaves the ground. The controller announces the window
through `ForeignState.jump_phase`; the adapter decides which byte carries it.

**Why `$B450` and not `PlayerCtrlRoutine $B0E9`.** `$B0E9` is the obvious
candidate for this too, and it does not work: `SaveJoyp` lives *inside*
`PlayerCtrlRoutine`, a few instructions past entry, and rewrites `$000A` from
`SavedJoypadBits` every frame —

```
SaveJoyp:  lda SavedJoypadBits / and #%11000000 / sta A_B_Buttons
```

— so a mask applied at `$B0E9` entry is overwritten by the game itself before
`CheckForJumping` ever reads it. `$B450` is downstream of `SaveJoyp`, upstream of
`$B479` in the same routine, and entered from exactly one site (`ProcMove`).
Ghidra, confirming both:

```
b450: LDA $001D / CMP #3 / BNE $b479      ; PlayerPhysicsSub entry
b479: LDA $070e / BNE $b488               ; CheckForJumping, jumpspring gate
b47e: LDA $000a / AND #$80 / BEQ $b488
b484: AND $000d / BEQ $b48b -> InitJS $b4a0
```

The hook **always returns 0** — it moves one input byte and lets SMB1's physics
run unmodified.

#### Every reader of `$000A`, and which ones are in scope

Enumerated from the byte-exact disassembly and cross-checked against a ROM-wide
search for `LDA $0A`: 8 byte hits, 7 real readers plus one false positive at
`$A134` inside `E_UndergroundArea3` level data. Sole writer is `SaveJoyp`.
Frame order is `GameRoutines` (→ `$B450`) → `GameEngine` → `SaveAB`, so all of
these are downstream of the write within the same frame.

| Reader | Reads | In scope? |
|---|---|---|
| `$B47E` `CheckForJumping` | `and #$80` | **the target** |
| `$AF67` `SaveAB` | `sta PreviousA_B_Buttons` | **affected and required** — this is what manufactures the clean rising edge on the launch frame, and what stops `InitJS` re-firing the frame after while A is still held |
| `$B37A` `JumpSwimSub` | `and #$80 / and $0D` | not reached — guarded by `ldy Player_Y_Speed / bpl DumpFall`, and Falcon is grounded with `vy 0` for the whole squat |
| `$B8E5` `JumpspringHandler` | `and #$80` | **gated off** — masking would suppress the "press A on frame 3 of the bounce" boost, and `CheckForJumping` already declines while `JumpspringAnimCtrl` is set, so it would buy nothing |
| `$F05D` `ActionSwimming` | `asl / bcs` | **gated off** — swim stroke animation extent |
| `$B53A`, `$B62B` | `and #B_Button` (`$40`) | untouched; the mask is A-only |

So the hook declines entirely when `SwimmingFlag $0704` or
`JumpspringAnimCtrl $070E` is set.

#### LAUNCH must *set* the bit, not just stop masking

A short hop means the player already released A, so `SavedJoypadBits` no longer
carries it and `SaveJoyp` has already written `$000A` without it. If the hook
only stopped suppressing, a short hop would produce **no jump at all** —
silently, and it would read as the physics being wrong. So `FOREIGN_JUMP_LAUNCH`
forces the bit on.

#### The launch frame is the mirror of the handoff frame

The subsection above gives SMB1 the handoff frame because the host leads and the
controller lags. On the launch frame the polarity reverses: Falcon left the
ground at VBlank, and SMB1 will not set `Player_State = 1` until it runs
`InitJS` later in that same frame. So `Player_State` still reads 0 when the
adapter builds its `ForeignCollisionResult`, and reporting that as `grounded`
makes `falcon_resolve` conclude he *landed*.

Measured, before the guard: a 2-frame tap took off at `vy 65.60` — the correct
short-hop force — and was overwritten to `97.60`, the full-hop force, on the
very next frame. `enter_landing` ran, then the M3 reconciliation branch saw a
ground state with the host reporting airborne and re-launched him at full
height. **Every short hop silently became a full hop while the takeoff row in
the trace still looked correct.** The adapter now believes the controller for
that one frame; SMB1 confirms on the next.

Because Falcon integrates the launch frame himself, the M3 handoff frame is no
longer consumed on a button jump — which is why the running full hop measures
85 px now against M3's 90 px. The 5 px is exactly SMB1's one free `-5`.

### Rejected: hooking `PlayerCtrlRoutine $B0E9`

The obvious target, and wrong for M2. Skipping it would take the vertical axis
too — jump, gravity, the lot — which is M3's job, not M2's. It is also the wrong
place to move the A bit, for a different reason — see `$B450` above.

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

Second condition, `Player_State $001D`. The encoding is from the
disassembly — `PlayerPhysicsSub $B450` compares `#$03` for climbing, `InitJS
$B4A0` stores `#$01`, and `PlayerBGCollision`'s `SetFallS` path stores `#$02`:

| `Player_State` | Meaning | Ownership |
|---|---|---|
| 0 | on ground | FOREIGN |
| 1 | jumping / swimming | FOREIGN |
| 2 | falling | FOREIGN |
| 3 | climbing a vine | SCRIPTED |
| 4 | killed | SCRIPTED |

M2 restricted this to 0; M3 opened 1 and 2. State 1 doubles as swimming, which
`SwimmingFlag` distinguishes — water levels are out of M3's scope, so a swim is
currently driven as a jump. That is tracked with the scripted-state handoffs in
M5.

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

Three more from the vertical hook, all of them bytes `ImposeGravity` itself
writes:

| Address | Name | Value | Why SMB1 needs it |
|---|---|---|---|
| `$00CE` | `Player_Y_Position` | integrated from Falcon's `vel_air_y × 0.08` | the position everything else reads |
| `$00B5` | `Player_Y_HighPos` | carry/borrow out of the above | the high half of the 16-bit coordinate |
| `$009F` | `Player_Y_Speed` | `round(dy_px)` | collision bias, the landing / heavy-landing check and the player graphics handler all read it, and a stale value makes them disagree with the motion |

`Player_Y_MoveForce $0433` and `Player_YMF_Dummy $0416` are **not** written:
they are SMB1's subpixel accumulator, and ours lives host-side at full
precision. Everything else Falcon needs lives host-side in the ported module,
per the host-owned-state rule. No contention for a guest byte.

### Reading SMB1's answer back

The horizontal path detects a refused move by reading `Player_X_Speed` back and
watching `SideCollisionTimer`. The vertical path is the exact twin: the hook
remembers the 16-bit Y it wrote, and the next VBlank compares it against what is
actually there. A difference means `PlayerBGCollision` overruled us — upward
becomes `hit_ceiling`, downward `hit_floor` — and the delta is converted back
into the controller's units and sign for `nes_foreign_resolve`.

Without it, running into the underside of the 1-1 brick row left Falcon pressing
upward at +32 units/frame for three frames while SMB1 silently pinned him: the
pixels were right, but the controller believed it was still rising. That is the
same class of mistake as the wall the player could tunnel through before the
horizontal check existed.

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

### M3, same run

Full hop from a run, World 1-1, from the ring (`native_y` is
`Player_Y_Position`, which grows downward):

```
f251  KNEEBEND       vy    0.00   y 176      A pressed; SMB1 has not launched yet
f252  JUMP_F         vy  +83.60   y 171      host launched, controller reconciled
f258  JUMP_F         vy  +63.20   y 135
f267  JUMP_F         vy  +32.60   y 100
f276  JUMP_F         vy   +2.00   y  86      apex, hit_ceiling = 0 (genuine apex)
f281  FALL           vy  -15.00   y  87
f291  FALL           vy  -49.00   y 111
f292  LANDING_LIGHT  vy    0.00   y 112      hit_floor = 1
```

- Rise of **90 px** — five and a half NES tiles, against Mario's own ~4.
- Gravity is a constant 3.4 units/frame the whole way: `83.6, 80.2, 76.8, …`,
  Falcon's `A_GRAVITY`, not SMB1's `JumpMForceData`.
- `hit_floor` fires exactly on touchdown; `hit_ceiling` never fires on this
  jump, which is how we know the flat apex is an apex and not a brick row.
- Before the M3 hook was enabled the same script produced 5,5,5,5,4,4,4… — the
  signature of SMB1's own `PlayerYSpdData` + `JumpMForceData`. That difference
  is what proves the takeover, and it is worth keeping as the check.

Harness coverage: `tests/falcon_harness/host_launch.script` and
`host_ledge_fall.script` exercise the reconciliation branch directly, which the
fighter's own kneebend path never reaches.

---

### M3.5, short hop versus full hop

Two scripted runs, identical except for how long A is held. World 1-1, standing
start (neutral stick, so `jump_force_button` gets `sq = 1` and the full force
term). Ground is `native_y 176`.

```
        f290  KNEEBEND  jp=CHARGING  gnd=1  vy   0.00   y 176
        f291  KNEEBEND  jp=CHARGING  gnd=1  vy   0.00   y 176
        f292  KNEEBEND  jp=CHARGING  gnd=1  vy   0.00   y 176
        f293  KNEEBEND  jp=CHARGING  gnd=1  vy   0.00   y 176
2-frame tap:
        f294  JUMP_F    jp=LAUNCH    gnd=0  vy +65.60   y 171   peak y 123 = 53 px
30-frame hold:
        f294  JUMP_F    jp=LAUNCH    gnd=0  vy +97.60   y 169   peak y  61 = 115 px
```

- **The squat is real**: `KNEEBEND` for exactly 4 frames with `grounded = 1` and
  `native_y` unchanged, then one `JUMP_F` frame. Under M3 this was a single
  `KNEEBEND` frame that got overwritten.
- **The height split is real**: 53 px versus 115 px from the same script.
- Both takeoff velocities are **derived, not fitted**. With a neutral stick
  `jump_force_button` gives `force + min`, then `+A_JUMP_HEIGHT_BASE 24.0`, then
  `-A_GRAVITY 3.4` on the same tick:
  `short 9+36+24-3.4 = 65.6`, `full 17+63→77 (clamped) +24-3.4 = 97.6`.
  Both matched the runtime to the digit.
- Gravity stays a constant 3.4/frame in both.
- The running full hop (`falcon_m3.script`, stick held at 80) still takes off at
  `vy 83.60`, identical to M3.

Harness coverage: `jump_height_split.script` does both jumps in one run and
asserts the takeoff velocities and both peak heights numerically. That matters
because a short hop and a full hop are *both* `KNEEBEND → JUMP_F`, so
`expect_state` alone cannot tell them apart — which is exactly how M3 shipped a
build where every jump was a full hop and every state assertion still passed.
Its predicted peaks (666 and 1450 units, ×0.08 = 53 and 116 px) match the
in-game measurement above. `ctest --test-dir build_harness` runs **8/8**.

**Mod-off regression:** with `smash64-player` disabled the run produces zero
`[Smash64]` output, no ring rows at all, and exits 0. The generated diff is one
line — the `$B450` hook.

---

## 7. Known-open for M4+

- **Jump now costs 4 frames of input latency.** That is the jumpsquat, it is
  authentic to the source game, and it is alien to SMB1's. It belongs to the
  character, never to the runner — it only happens while the mod is on.
  Owner-playtested and accepted (2026-08-07, "jumping is good yes").
- **The stick-based jump-height path is still unreachable.** M3.5 opened the
  window for `KB_INPUT_BUTTON`; `kneebend_input_type` can also return
  `KB_INPUT_STICK` on a fresh upward tap, and a d-pad UP press does produce one.
  Not exercised or measured — it just is not reached in any trace so far.
- **Swimming keeps SMB1's rising-edge jump.** The jumpsquat hook declines
  entirely while `SwimmingFlag` is set, because masking A would reach the swim
  hold-check at `$B37A` and the stroke animation at `$F05D`. `Player_State == 1`
  doubles as swimming and water levels are M5, so this is deferred, not solved.
- **Jumpsprings keep SMB1's behaviour too**, for the same reason — the boost
  check at `$B8E5` reads the A bit later in the frame.
- **Swept collision: vertical DONE, horizontal open.** The vertical axis now
  walks the motion one pixel at a time against SMB1's own block buffer (§ the
  vertical hook). The tunnelling exposure it guards against is **measured, not
  hypothetical**: with the sweep's blocking branch disabled
  (`NESRECOMP_SMASH64_SWEEP_NOBLOCK=1`, a permanent diagnostic announced on
  stderr at mod enable), a fast-fall at `vy = -100` moves 8 px/frame, the feet
  cross the floor at Y residues 14/6/14/6 (mod 16) — never inside
  `DoFootCheck`'s `cpy #$05` landing window — and the player falls through the
  entire two-tile floor (native_y 190→198→206→214, `FEET_IN_SOLID` +
  `SWEPT_FLOOR` flagged on every frame) off the bottom of the screen and dies.
  With the sweep active, the same 22-cycle input never puts a frame below
  y=176 and every floor block parks at exactly y%16==0, the coordinate
  `LandPlyr` fires on. (Rings: `ftring_ff_control.csv` /
  `ftring_ff_noblock.csv`, 2026-08-07.) The **horizontal** axis is swept the
  same way via a fourth hook at `MovePlayerHorizontally` `$BF09` (NOT the
  generic `MoveObjectHorizontally` `$BF0F`, which enemies share), probing
  `BlockBufferColli_Side` `$E3EC` with `CheckSideMTiles`' own predicate and
  synthesizing the routine's return A (pixels moved → `Player_X_Scroll`, the
  scroll driver). Measured: dash pins flush at native_x 434 against 1-1's
  first pipe (probe adder 13 → pixel 447, last column before the tile at
  448), zero penetration over ~400 contact frames, one frame of wall latency
  removed. The legacy `ImpedePlayerMove` readback stays as a ring-visible
  cross-check (`WALL_READBACK` 0x80) until the harness scripts show sustained
  agreement, then gets deleted. `nes_foreign_sweep` in the engine remains
  unused: its last-unblocked semantics don't fit a host that resolves its own
  collisions and needs the overlap; if a second game needs it, add an
  inclusive-stop mode to the helper rather than copying this adapter's loop.
- **`TurnRun` is an adaptation**, not Falcon's real run-turn — the original is
  animation-driven. See `falcon_movement_dependency.md` §6.
- **Two provisional durations** (`FL_DASH`, landings) still need the Figatree
  animation length.
- **Save states now carry the controller's host-side state (M5.5).** The
  engine's generic per-mod savestate registry (`mod_savestate.h`, SS_VERSION
  6) is used by two hooks, matching the fighter/adapter boundary: a fighter
  hook registered from `captain_falcon.c` under `SMASH64_CAPTAIN_FALCON_ID`
  (the `FalconFighter` struct via `falcon_serialize`/`falcon_deserialize` in
  `ssb_ported/falcon_locomotion.c`, plus the engine's `ForeignState`, since
  this file owns the reset path for both), and an adapter hook registered
  from `game_smash64_register_hooks()` under
  `"super-mario-bros.smash64.adapter"` covering the in-flight subpixel
  accumulators and previous-frame readback latches (`s_y_sub`, `s_x_sub`,
  `s_wrote_*`, `s_prev_ownership`, the undrained per-frame sweep/collision
  flags, `s_prev_buttons`). Both blobs are version-prefixed so a future
  layout change degrades to "hook present, record skipped" rather than a
  misread. `s_enabled`/`s_selected`/`s_controller_id` are deliberately never
  restored -- mod activation stays the live session's choice -- and the
  adapter hook writes a 0-byte record whenever the mod is off, so a vanilla
  or mod-off save carries no dead payload. Diagnostic counters
  (`s_owned_frames` and siblings) and the env-derived
  `NESRECOMP_SMASH64_SWEEP_NOBLOCK` flag are excluded on the same
  live-session grounds.
