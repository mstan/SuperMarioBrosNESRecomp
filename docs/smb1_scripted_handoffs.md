# SMB1 scripted-sequence handoffs

**Status: M5.1-M5.4 SHIPPED, M5.6 (this document)**
(`beads-2dw.2.1.6`, dependency `beads-2dw.2.1.5`). Companion to
`docs/smb1_player_adapter.md`, which covers the ownership dispatch table,
the physics hooks and the swept collision. This document is the audit
record the M5 bead's acceptance criteria require: every scripted sequence
and every player-adjacent interaction the M5 description names
(Goombas/Koopas, stomp detection, enemy side collision, pits, springboards,
swimming, vines, flagpoles, pipes), its classification, and — for the ones
that are genuinely ownership questions — the boundary behaviour: what the
adapter does when the game hands control away, and what it does when the
game hands it back.

Every address below was confirmed either in Ghidra (as recorded in the bead
notes) or by reading `smb-disassembly/src/smb.asm` directly; the citation is
the line number in that file as checked for this document. A claim I could
not independently verify against the disassembly is marked **[unverified]**
rather than asserted.

---

## 1. The two mechanisms this table is built on

Everything below reduces to two already-shipped pieces of machinery in
`game_smash64.c`:

**`decide_ownership()`** (line 491) returns one of `NATIVE` / `FOREIGN` /
`SCRIPTED`. `FOREIGN` is the only value under which the physics hooks
(`ImposeFriction`, `MovePlayerVertically`, `MovePlayerHorizontally`,
`PlayerPhysicsSub`) do anything; each hook re-checks it and returns 0 (let
SMB1's own code run) whenever it is not `FOREIGN`. So a scripted sequence
cannot leak Falcon motion into it by construction — this was confirmed, not
assumed, because the scripted routines (vine, pipes, flagpole, death) call
`PlayerCtrlRoutine` internally via `AutoControlPlayer` (`smb.asm:5493`) with
forced pad bits, meaning the hooked routines *do* run during a scripted
sequence, and every one of them declines.

**The reseed** (lines 599–633). On the `SCRIPTED -> FOREIGN` edge the
adapter calls `nes_foreign_select(s_controller_id)` again — the same call
used at mod-enable, whose contract is a full controller reset — and clears
its own subpixel accumulators (`s_y_sub`, `s_x_sub`) and its `s_wrote_*`
valid flags. Nothing ticks the fighter while ownership is `SCRIPTED` (the
per-frame `nes_foreign_tick` call only drives motion under `FOREIGN`), so
`vel_ground_x`, the move state and every mid-gesture buffer (kneebend, turn,
stick-tap) would otherwise freeze at whatever they held when ownership left
and reappear unchanged on the far side of the sequence — a dash frozen into
a pipe exits as a full-speed phantom dash SMB1 never asked for.

**Measured correction to the design.** The design predicted this phantom
would reproduce at the death edge. It does not: `game_smash64_update_input`
calls `nes_foreign_resolve` unconditionally every frame, including while
`GameEngineSubroutine` is running `PlayerDeath`, so the fighter keeps being
fed the scripted RAM through `resolve` — it is not frozen, it is driven by
the death animation's own numbers. `PlayerDeath` (`smb.asm:5704`) routes
through `KillPlayer` (`smb.asm:11365`), which stores a fixed `Player_Y_Speed
= $FC` (bounce/death velocity, `smb.asm:11370`) before the fall; the imposed-
velocity readback (already shipped at M4, described in
`smb1_player_adapter.md` §4) reads that write back as an impulse and lands
the fighter in `LANDING_LIGHT` with `vx = 0` before the level reloads
(measured on the ring, frame 649 of a death-edge trace, pre-fix build). So
**death self-heals by accident** — it happens to route through a state that
zeroes velocity — while a pipe transition has no equivalent landing event
and the phantom-dash risk stands there undiminished. The reseed closes the
whole class rather than relying on which sequence happens to end in a way
that clears state.

**Facing needs no special case.** Every scripted re-entry into ordinary
play funnels through `PlayerRdy` (`smb.asm:5480-5483`), which unconditionally
stores `PlayerFacingDir = 1` (line 5483) before falling into
`GameEngineSubroutine = 8`. That is the same default the reseed's
`nes_foreign_select` reset gives the fighter, so the two agree without the
adapter doing anything extra.

**`jump_phase`** needs no special case either: it is already cleared
generically by `nes_foreign_tick`'s non-driving branch whenever the
controller is not ticking (i.e. every frame ownership is `SCRIPTED`).

---

## 2. The audit table

`GameEngineSubroutine $000E` is the dispatch index read at `GameRoutines`
(`smb.asm:5412-5428`); ownership is what `decide_ownership()` returns while
each value is active.

| Value | Handler | smb.asm | RAM signal | Adapter boundary behaviour | Classification |
|---|---|---|---|---|---|
| 0 | `Entrance_GameTimerSetup` | 2781 | `GameEngineSubroutine==0`; sets `Player_State=0` (2790), the `SwimmingFlag` gate (2794-2797), starting position | Declared `SCRIPTED` by the catch-all (§3.1). No hooks reachable — physics hasn't started. Ends by storing `GameEngineSubroutine=7` (2837-2838) | **WORKS NATIVELY** — pure setup, no player-adjacent motion to own |
| 1 | `Vine_AutoClimb` | 5604 | forces `Player_State=3` (5613, climbing) and pad-override `UP` (5610-5611), via `AutoControlPlayer` (5614) | `Player_State>2` is also an independent `SCRIPTED` gate in `decide_ownership()` (line 525) so this is double-covered even if `GameEngineSubroutine` misclassified it | **DEFERRED** — vine climb is native code the mod does not model at all (`smb1_player_adapter.md` §3); no Falcon-shaped work item exists for it |
| 2 | `SideExitPipeEntry` | 5643 | drives `EnterSidePipe` (5655), which sets a fixed `Player_X_Speed` and forces controller bits via `AutoControlPlayer` (5665) | `SCRIPTED`; reseed fires on the `FOREIGN` re-entry that follows (§1) | **NEEDS ADAPTER (shipped)** — the reseed is the whole fix; no pipe-specific code, the general edge handles it |
| 3 | `VerticalPipeEntry` | 5621 | `MovePlayerYAxis` (5635) adds a fixed delta to `Player_Y_Position` directly, bypassing the physics hooks entirely | `SCRIPTED`; same reseed on exit | **NEEDS ADAPTER (shipped)** — same as side pipes |
| 4 | `FlagpoleSlide` | 5748 | forces climb-down via `AutoControlPlayer` (5760); exits by advancing to `PlayerEndLevel` | `SCRIPTED` for the whole slide | **NEEDS ADAPTER (shipped)** — reseed on the eventual return to ordinary play (after level end / respawn), not on this transition directly |
| 5 | `PlayerEndLevel` | 5769 | forces walk-right via `AutoControlPlayer` (5771); watches `Player_Y_Position` and `Player_CollisionBits` for the walk-off-screen finish | `SCRIPTED` — the end-of-level autowalk | **NEEDS ADAPTER (shipped)** — same reseed contract; this is the "end-of-level walk" item from the M5 enumeration |
| 6 | `PlayerLoseLife` | 2854 | decrements `NumberofLives` (2860), sets `OperMode`/`GameOverModeValue` if out of lives | `SCRIPTED` | **NEEDS ADAPTER (shipped)** — reseed on the respawn-edge re-entry |
| 7 | `PlayerEntrance` | 5432 | autowalk-in via `AutoControlPlayer` (5439, 5448); finishes through `PlayerRdy` (5480-5483) | `SCRIPTED` for the whole autowalk | **NEEDS ADAPTER (shipped)** — reseed on the transition to `GameEngineSubroutine=8`; this is the "entrance/`PlayerEntrance`" item |
| **8** | **`PlayerCtrlRoutine`** | 5496 | the ordinary-play value; `SaveJoyp` writes `A_B_Buttons` here every frame | `FOREIGN` (subject to the `SwimmingFlag` and `Player_State>2` sub-gates below) | **WORKS NATIVELY as the FOREIGN condition** — this is the value everything else in `smb1_player_adapter.md` is written against |
| 9 | `PlayerChangeSize` | 5670 | gated on `TimerControl` reaching `$f8`/`$c4` (5672, 5675); flips `PlayerSize` via `InitChangeSize` (5691-5698) | `SCRIPTED` for the whole grow/shrink animation | **NEEDS ADAPTER (shipped)** — reseed on return; this is the "grow/shrink" item |
| 10 | `PlayerInjuryBlink` | 5682 | gated on `TimerControl` (5684, 5686); falls through to `PlayerCtrlRoutine` (5688) between blink phases | `SCRIPTED` while blinking; note it *calls into* `PlayerCtrlRoutine` itself mid-sequence, which is the routine `decide_ownership()` also gates — so even that inner call declines correctly | **NEEDS ADAPTER (shipped)** — this is the "injury blink" item |
| 11 | `PlayerDeath` | 5704 | gated on `TimerControl` reaching `$f0` (5706); calls `KillPlayer` (11365) which sets `Player_State=1` via `SetKRout` (11372, 11353-11354) and `Player_Y_Speed=$fc` (11370) | `SCRIPTED` | **NEEDS ADAPTER (shipped)** — see §1's measured death-edge finding; self-heals by accident, reseed makes it a contract instead |
| 12 | `PlayerFireFlower` | 5717 | gated on `TimerControl==$c0` (5719); cycles `Player_SprAttrib` palette bits (5725-5731) | `SCRIPTED` for the whole freeze-and-flash | **NEEDS ADAPTER (shipped)** — this is the "fireflower freeze" item |

### 2.1 `Player_State $001D` — the second, finer-grained gate

Active only while `GameEngineSubroutine==8` (i.e. inside the `FOREIGN`
candidate above). `decide_ownership()` line 525 additionally declines to
`SCRIPTED` when `Player_State > 2`:

| Value | Meaning | Store site | smb.asm | Ownership |
|---|---|---|---|---|
| 0 | on ground | `Entrance_GameTimerSetup` default | 2789-2790 | FOREIGN |
| 1 | jumping / swimming (overloaded) | `InitJS`, `SetKRout` (injury+death), `JumpspringHandler` boost path, `Vine_AutoClimb`→`SetEntr` | 11353-11355 (SetKRout) | FOREIGN, gated further by `SwimmingFlag` below |
| 2 | falling | `PlayerBGCollision`'s `SetFallS` path | 11855-11856 | FOREIGN |
| 3 | climbing a vine | `Vine_AutoClimb`/`AutoClimb` path, `VineEntr` | 5612-5613, 5470-5471 | SCRIPTED (deferred, §2 row 1) |

**Player_State==4 "killed" does not exist in this ROM.** An earlier design
revision asserted 4 = killed. Checked directly: `SetKRout` (11353) always
stores `#$01` via `ldy #$01`, and it is the only site that runs for
`ForceInjury` (11343-11353) *and* `KillPlayer` (11365-11372) — both funnel
through the same store. There is no `sta Player_State` anywhere in
`smb.asm` that writes `#$04`; that includes `SetPRout`/`SetKRout`,
`Entrance_GameTimerSetup`, `PlayerBGCollision`, and `Vine_AutoClimb`. This
does not create an ownership hole: `GameEngineSubroutine` already leaves 8
for the entire death sequence (row 11 of the table above) and gates first,
so `Player_State` never has to distinguish "dying" from "falling" for
ownership purposes.

### 2.2 Swimming — `SwimmingFlag $0704`, a level-scoped third gate

```c
if (g_ram[SwimmingFlag])
    return FOREIGN_OWNERSHIP_SCRIPTED;
```
(`game_smash64.c:510-511`, inside `decide_ownership()`, checked before the
`Player_State` gate.)

The gate exists because SSB64 has no swim model of its own, and
`Player_State==1` is the same value used for an ordinary jump — without
this check a water level would be driven as an endless Falcon jump inside
the water tile column.

**Why one boolean check is exact rather than an approximation.** The bead's
Ghidra pass byte-searched the whole ROM for every absolute store opcode
against `$0704` (`8D`/`8C`/`8E 04 07`) and found exactly one: `Entrance_
GameTimerSetup`, disassembled here at `smb.asm:2794-2797`:

```
2794  lda AreaType      ; check area type
2795  bne ChkStPos       ; if water type, set swimming flag, otherwise do not set
2796  iny
2797  ChkStPos: sty SwimmingFlag
```

`AreaType==0` is the water-level encoding; the flag is written once at
level entrance and never touched again anywhere in the ROM for the rest of
that level's lifetime. So gating the whole level on this one flag is exact,
not a heuristic — there is no mid-level toggle to miss.

**Defence in depth, not duplication.** The jumpsquat hook
(`jumpsquat_hook`, `game_smash64.c:1245`) independently declines while
`SwimmingFlag` is set, for an unrelated reason documented in
`smb1_player_adapter.md` §1 (masking the A bit would reach the swim
hold-check at `$B37A` and the stroke-animation branch at `$F05D`). That
hook-local check was already correct on its own; `decide_ownership()`'s
gate additionally stops the friction and vertical hooks, which the
jumpsquat hook's local check never touched. Both exist; neither is
redundant.

**Coverage note.** Not yet exercised against a real water level — none is
quickly reachable from World 1-1. Tracked as M5.7 (tier-4 coverage,
water level test), still open.

**Classification: NEEDS ADAPTER (shipped)** — the gate is landed
(`game 82cd20d`); the water-level exercise is the open coverage item.

### 2.3 Jumpsprings

Handled entirely by machinery that shipped at M4, not by anything M5 added.
`JumpspringHandler` (`smb.asm:6566`) animates the spring and, on its
fifth frame (`cpy #$03` at line 6595), stores a fixed force into
`Player_Y_Speed` (line 6598: `sta Player_Y_Speed`). The vertical event
readback in `game_smash64_update_input` (`game_smash64.c:769-798`) already
watches for exactly this: any frame where `Player_Y_Speed` differs from
what the hook itself last wrote is read as SMB1 imposing a velocity, and
that value is converted into `hit.imposed_vy` and handed to
`nes_foreign_resolve` regardless of who owns the player. Both the
jumpsquat hook (`jumpsquat_hook`, `game_smash64.c:1253`) and the
horizontal sweep hook (`move_player_horizontally_hook`,
`game_smash64.c:1149`) also decline outright while `JumpspringAnimCtrl
$070E` is nonzero — the latter mirroring `MovePlayerHorizontally`'s own
first act (`$BF09: LDA $070E / BNE ExXMove`), the former mirroring
`CheckForJumping`'s jumpspring gate (`$B479`, cited in
`smb1_player_adapter.md` §1).

**Classification: WORKS NATIVELY (via the shipped M4 imposed-velocity
path)** — this is the bead's own conclusion ("Jumpsprings need NOTHING,
already correct via M4 imposed_vy readback") and it checks out against the
code: no jumpspring-specific branch exists anywhere in `decide_ownership()`
or the reseed; the general readback and the general decline-while-animating
checks are enough.

---

## 3. The non-ownership items

The M5 bead's audit request explicitly named Goombas, Koopas, stomp
detection, enemy side collision and pits. None of these are ownership
questions, and the reason is the same reason jumpsprings need nothing extra
(§2.3): **`decide_ownership()` only ever changes who *drives* the player.
It has no opinion on who *notices contact*, because SMB1 never stopped
noticing contact.**

- **Goombas / Koopas / enemy side collision.** Enemy-vs-player collision is
  detected by `PlayerCollisionCore`, called from the per-enemy update loop
  at `smb.asm:11246`, guarded on `GameEngineSubroutine==8`
  (`smb.asm:11239-11241` — `cmp #$08 / bne NoPECol`) exactly like the
  ownership dispatch's own `FOREIGN` value. This runs every frame
  regardless of whether Falcon or SMB1 is currently integrating position;
  it reads `Player_X_Position`/`Player_Y_Position`, which are the same
  bytes the adapter writes every `FOREIGN` frame (`smb1_player_adapter.md`
  §4). An injury sets `GameEngineSubroutine=10` or `11` via `ForceInjury`/
  `KillPlayer` (`smb.asm:11343-11372`), which is row 10/11 of the table
  above — already a scripted-sequence ownership transition with a reseed
  on exit. There is nothing for `decide_ownership()` to add: the collision
  check and its consequence are both already inside the machinery this
  document audits.

- **Stomp detection.** `EnemyStomped` (`smb.asm:11377`) and its
  `HandleStompedShellE`/`SBnce` tail (`smb.asm:11437-11451`) write a fixed
  `Player_Y_Speed` directly — `$fd` for a fresh stomp (line 11416), `$fc`
  for a chained bounce (line 11450) — the exact same byte the vertical
  event readback (`game_smash64.c:769-798`) watches for a jumpspring or a
  block bump. A stomp bounce is read back as an imposed velocity and
  applied to the fighter whether or not `FOREIGN` is currently true for
  the frame the stomp landed on. No stomp-specific code exists or is
  needed; it rides the same general mechanism as jumpsprings.

- **Pits.** A pit is not a distinct game state at all — SMB1 detects it as
  `Player_Y_Position` exceeding a bottom-of-screen threshold inside the
  ordinary collision path (`PlayerBGCollision`'s `ChkOnScr`/`ExPBGCol`
  region, `smb.asm:11857-11865`, and the `cmp #$cf` checks reused by
  `DoFootCheck` at `smb.asm:11916`), which leads to `PlayerLoseLife`
  (`GameEngineSubroutine=6`, row 6 above) exactly like any other death.
  There is no separate "in a pit" ownership state; falling in a pit is
  just falling until SMB1's own vertical-extent check ends the life. The
  M4 swept-collision work (`beads-2dw.2.1.5`) is the relevant audit for
  *whether Falcon's speed can miss the pit-vs-floor distinction entirely*
  (verified real for uncapped fast fall, fixed by the vertical sweep) — but
  that is a collision-fidelity question, not an ownership one, which is
  why it lives on the sibling bead rather than this table.

**Classification for all of the above: WORKS NATIVELY** — not because
nothing needed building, but because the M4 imposed-velocity readback and
the M5 scripted-sequence gating already cover every consequence these
interactions produce; there is no fourth mechanism to add.

---

## 4. Summary by classification

| Classification | Items |
|---|---|
| **WORKS NATIVELY** | `Entrance_GameTimerSetup` setup phase; `PlayerCtrlRoutine` (the FOREIGN condition itself); jumpsprings (M4 readback); Goombas/Koopas/enemy side collision; stomp detection; pits |
| **NEEDS ADAPTER (shipped)** | side pipe entry, vertical pipe entry, flagpole slide, end-of-level walk, lose-life, entrance autowalk, grow/shrink, injury blink, death, fireflower freeze — all via the single `SCRIPTED -> FOREIGN` reseed (§1); swimming, via the level-scoped `SwimmingFlag` gate (§2.2) |
| **DEFERRED** | vine autoclimb (`Player_State==3`) — native climbing code the mod does not model; tracked as a known-open item in `smb1_player_adapter.md` §7, not a separate bead at time of writing |

---

## 5. Open coverage (M5.7, not yet run)

- Water level run to exercise the `SwimmingFlag` gate against real
  gameplay (§2.2) — not yet reachable quickly from World 1-1.
- Both pipe types (side and vertical) run against a pre-reseed build to
  demonstrate the predicted phantom-dash, then against the fixed build to
  confirm it is closed — not yet built; the reseed shipped as the
  class-closing fix without a pipe-specific repro (the death-edge repro
  was built instead, and it was the one that produced the measured
  correction in §1).
- Castle level run (mixed hazards, per the M5 description).
- A/B run with the mod disabled, as a regression baseline.

No claim in this document depends on that coverage landing; it documents
what the code does now for every item the audit named, and separately
what has and has not yet been *exercised* end to end.
