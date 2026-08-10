# Captain Falcon locomotion — dependency map

**Status: COMPLETE.** This is the M0 deliverable (`beads-2dw.2.1.1`), and the
gate it guards is now open: the closure is bounded, evidence-backed, and needs
neither the SSB64 ROM nor a mips64 toolchain.

Source: `smb-disassembly`'s sibling reference, `VetriTheRetri/ssb-decomp-re`, at
**`054ffc23f396868cd1db2b87ee3a2c1d3bebb75a`** (branch `main`, 2026-08-04).
Local checkout: `F:\Projects\SmashBrosDecomp`.

Every citation below is `path:function` at that revision. Nothing here is
inferred from a wiki, from memory, or from feel.

---

## 1. Match status — the correctness gate

`us_report.json` in the decomp gives per-unit match data, readable without a
ROM or toolchain. **Every unit this port depends on is 100% matched:**

| Unit | Functions | Match |
|---|---|---|
| `ft/ftphysics` | 31/31 | 100.00% |
| `ft/ftparam` | 98/98 | 100.00% |
| `ft/ftmain` | 54/54 | 100.00% |
| `ft/ftcommon/ftcommonwait` | 4/4 | 100.00% |
| `ft/ftcommon/ftcommonwalk` | 8/8 | 100.00% |
| `ft/ftcommon/ftcommondash` | 7/7 | 100.00% |
| `ft/ftcommon/ftcommonrun` | 3/3 | 100.00% |
| `ft/ftcommon/ftcommonrunbrake` | 5/5 | 100.00% |
| `ft/ftcommon/ftcommonturn` | 7/7 | 100.00% |
| `ft/ftcommon/ftcommonturnrun` | 4/4 | 100.00% |
| `ft/ftcommon/ftcommonkneebend` | 11/11 | 100.00% |
| `ft/ftcommon/ftcommonjump` | 3/3 | 100.00% |
| `ft/ftcommon/ftcommonjumpaerial` | 11/11 | 100.00% |
| `ft/ftcommon/ftcommonfall` | 2/2 | 100.00% |
| `ft/ftcommon/ftcommonlanding` | 5/5 | 100.00% |
| `ft/ftcommon/ftcommonlandingair` | 1/1 | 100.00% |

Repo-wide: 97.98% code, **100% data**, 7165 functions.

**Consequence:** the C being ported is byte-exact to the original game, so a
direct port cannot drift from it. This is why M1's runtime oracle is a
nice-to-have rather than a gate. **Re-check this table before porting any
function not listed** — a non-matching function's C does not reproduce the
original assembly, and porting one yields wrong physics silently.

---

## 2. The physics primitives

All of `src/ft/ftphysics.c`, 455 lines, and it is the entire model. Two
velocity vectors matter: `fp->physics.vel_ground.x` on the ground and
`fp->physics.vel_air.{x,y}` in the air.

| Function | Does |
|---|---|
| `ftPhysicsSetGroundVelFriction(fp, f)` | move `vel_ground.x` toward 0 by `f`, clamping at 0 |
| `ftPhysicsSetGroundVelAbsStickRange(fp, vel, friction)` | walk: target `\|stick.x\| * vel`; snap up instantly, decay down by `friction` |
| `ftPhysicsApplyGravityClampTVel(fp, g, tvel)` | `vel_air.y -= g`, floor at `-tvel` |
| `ftPhysicsApplyFastFall(fp, attr)` | `vel_air.y = -attr->tvel_fast` (a **set**, not an add) |
| `ftPhysicsCheckSetFastFall(fp)` | arms fast-fall; see §6 |
| `ftPhysicsClampAirVelXStickRange(fp, min, vel, clamp)` | air drift: `vel_air.x += stick.x * vel`, clamp to `±clamp` |
| `ftPhysicsApplyAirVelXFriction(fp, attr)` | decay `vel_air.x` toward 0 by `attr->air_friction` |
| `ftPhysicsCheckClampAirVelXDec(fp, clamp)` | if over `clamp`, bleed off **1.0/frame** and return TRUE |
| `ftPhysicsApplyAirVelDriftFastFall(gobj)` | the per-frame air tick — see below |

The air tick, `ftPhysicsApplyAirVelDriftFastFall`, is the important composite:

```c
ftPhysicsCheckSetFastFall(fp);
(fp->is_fastfall) ? ftPhysicsApplyFastFall(fp, attr)
                  : ftPhysicsApplyGravityDefault(fp, attr);
if (ftPhysicsCheckClampAirVelXDecMax(fp, attr) == FALSE) {
    ftPhysicsClampAirVelXStickDefault(fp, attr);
    ftPhysicsApplyAirVelXFriction(fp, attr);
}
```

Note the ordering: while horizontal speed **exceeds** `air_speed_max_x` it
bleeds off at exactly 1.0 unit/frame and **stick drift and air friction are
skipped entirely** that frame. That is how a fast-moving Falcon keeps his
momentum out of a run-off. Getting this branch wrong is the most likely way to
produce something that looks close and feels wrong.

---

## 3. The twelve transitions

| # | Transition | Entry check | Effect |
|---|---|---|---|
| 1 | idle → walk | `ftCommonWalkCheckInputSuccess`: `stick.x * lr >= 8` | `ftCommonWalkSetStatusParam` picks Slow/Middle/Fast by `\|stick.x\|` |
| 2 | idle → dash | `ftCommonDashCheckInterruptCommon`: `\|stick.x\| >= 56` **and** `tap_stick_x < 3` | `vel_ground.x = attr->dash_speed`; if stick opposes `lr` → Turn instead |
| 3 | dash → run | `ftCommonRunCheckInterruptDash`: `anim_frame >= attr->dash_to_run` **and** `< dash_to_run + anim_speed` **and** `stick.x * lr >= 50` | `vel_ground.x = attr->run_speed` |
| 4 | run → stop | `ftCommonRunBrakeCheckInterruptRun`: `stick.x * lr < 50` | RunBrake; friction `attr->traction * 1.25` |
| 5 | run → turn | `ftCommonTurnRunCheckInterruptRun`: `stick.x * lr <= -30` | TurnRun; on flag frame `lr = -lr` and `vel_ground.x = -vel_ground.x` |
| 6 | ground → jumpsquat | `ftCommonKneeBendGetInputTypeCommon`: stick `y >= 53` with `tap_stick_y <= 3`, **or** a jump-button tap | KneeBend, records `jump_force = stick.y` |
| 7 | jumpsquat → air | `ftCommonKneeBendProcUpdate`: `attr->kneebend_anim_length <= anim_frame` | `ftCommonJumpSetStatus` — see §4 |
| 8 | air horizontal | `ftPhysicsClampAirVelXStickDefault` | `vel_air.x += stick.x * attr->air_accel`, clamp `±attr->air_speed_max_x` |
| 9 | gravity | `ftPhysicsApplyGravityDefault` | `vel_air.y -= attr->gravity`, floor `-attr->tvel_base` |
| 10 | fast fall | `ftPhysicsCheckSetFastFall` | `vel_air.y = -attr->tvel_fast`; see §6 |
| 11 | landing | `ftCommonLandingSetStatus` | Heavy if `is_fastfall && vel_air.y <= -tvel_fast`, else Light |
| 12 | landing → idle/run | `ftCommonLandingProcInterrupt` | only from `anim_frame >= 4.0`; then Turn or Walk check |

Dash also self-terminates: `ftCommonDashProcUpdate` — at `anim_frame <= 0`,
`vel_ground.x *= 0.75F` then Wait. And `ftCommonDashProcPhysics` applies
`attr->dash_decel` friction only once `anim_frame >= 7.0`.

### Which physics routine each state actually runs

From the status descriptor table, `src/ft/ftcommon/ftcommonstatus.h`. This is
the authoritative binding — a state file defining a `ProcPhysics` does not prove
the table uses it, and three states here run something other than what reading
their own file would suggest.

| State | Proc Physics | Effect on `vel_ground.x` / `vel_air` |
|---|---|---|
| Wait | `ftPhysicsApplyGroundVelFriction` | decays by `traction` |
| WalkSlow/Middle/Fast | `ftCommonWalkProcPhysics` | target `\|stick.x\| * walk_speed_mul` |
| Dash | `ftCommonDashProcPhysics` | `dash_decel` **only from frame 7** |
| **Run** | `ftPhysicsApplyGroundVelTransferAir` | **nothing — no friction at all** |
| RunBrake | `ftCommonRunBrakeProcPhysics` | decays by `traction * 1.25` |
| Turn | `ftPhysicsApplyGroundVelFriction` | decays by `traction` |
| **TurnRun** | **`ftPhysicsApplyGroundVelTransN`** | **animation-driven — see §6** |
| KneeBend | `ftPhysicsApplyGroundVelFriction` | decays by `traction` |
| JumpF, JumpB, JumpAerialF/B, Fall, FallAerial | `ftPhysicsApplyAirVelDriftFastFall` | the single air tick from §2 |
| LandingLight/Heavy/AirNull, Squat, SquatWait | `ftPhysicsApplyGroundVelFriction` | decays by `traction` |

Three things here are easy to get wrong and worth stating plainly:

- **Run applies no friction.** `ftPhysicsApplyGroundVelTransferAir` only
  projects onto the floor angle; it never touches `vel_ground.x`. Run therefore
  holds `run_speed` *exactly* until a state change. Assuming friction during
  run would make Falcon decelerate while sprinting, which he does not.
- **Jumpsquat does apply friction.** KneeBend runs
  `ftPhysicsApplyGroundVelFriction`, so there are 4 frames of `traction` decay
  between the input and takeoff. That is part of why a standing jump out of a
  run loses speed.
- **Every air state shares one function.** Jump, double jump, fall and
  fall-aerial all run `ftPhysicsApplyAirVelDriftFastFall`. Air behaviour is one
  routine, not six.

### Jump velocity (§4)

`ftCommonJumpSetStatus`, `src/ft/ftcommon/ftcommonjump.c`:

```c
vel_air.y = (vel_y * attr->jump_height_mul) + attr->jump_height_base;
vel_air.x = vel_x * attr->jump_vel_x;
```

`vel_y` comes from one of two paths:

- **stick jump** — `vel_y = kneebend.jump_force` (the *maximum* stick Y seen
  during jumpsquat, per `ftCommonKneeBendProcInterrupt`), floored at 53.
- **button jump** — `ftCommonJumpGetJumpForceButton`, a trig form:
  `vel_y = FORCE * sqrt(1 - (|stick.x|/80)^2) + MIN`, with
  `(FORCE, MIN) = (17, 63)` full hop and `(9, 36)` short hop, the whole thing
  clamped to `<= 77`, and additionally clamped onto the unit circle
  `vel_x² + vel_y² <= 80²`.

Short hop is decided in `ftCommonKneeBendProcUpdate`: the jump button released
within `FTCOMMON_KNEEBEND_SHORTHOP_FRAMES` (3.0) of jumpsquat start. The source
comment notes this is a real window, "unlike Melee where the user must simply
not be holding their jump input on the last frame of jumpsquat".

---

## 4. Captain Falcon's attributes

`src/relocData/236_CaptainMain.c`, `dCaptainMain_attr`. These are in **source**,
not extracted ROM data — no ROM needed. Units are the game's own; §8 converts.

| Attribute | US | JP | Used by |
|---|---|---|---|
| `walk_speed_mul` | 0.32 | — | walk target = `\|stick.x\| * this` |
| `traction` | 1.8 | — | ground friction; RunBrake uses `× 1.25` |
| `dash_speed` | 80.0 | — | dash entry velocity |
| `dash_decel` | 6.0 | — | dash friction after frame 7 |
| `run_speed` | **75.0** | **70.0** | run entry velocity |
| `dash_to_run` | 16.0 | — | frames before dash may become run |
| `kneebend_anim_length` | **4.0** | — | jumpsquat duration, frames |
| `jump_vel_x` | **0.31** | **0.35** | horizontal jump velocity per stick unit |
| `jump_height_mul` | 1.0 | — | jump Y scale |
| `jump_height_base` | **24.0** | **25.0** | jump Y offset |
| `jumpaerial_vel_x` | 0.35 | — | double jump |
| `jumpaerial_height` | **0.9** | **0.95** | double jump |
| `air_accel` | 0.04 | — | air drift per stick unit |
| `air_speed_max_x` | 31.0 | — | air drift clamp |
| `air_friction` | 0.2 | — | air horizontal decay |
| `gravity` | 3.4 | — | per frame |
| `tvel_base` | **66.0** | **60.0** | terminal velocity |
| `tvel_fast` | 100.0 | — | fast-fall velocity |
| `jumps_max` | 2 | — | Fall vs FallAerial |
| `weight` | 0.96 | — | knockback only — **not needed** |
| `map_coll` | `{top 400, center 250, bottom 0, width 150}` | — | collision diamond; the scale reference |

**Port the US column.** Six attributes differ by region, and `ftcommonrunbrake.c`
carries a US-only "momentum slide fix" (`#if defined(REGION_US)`) that clamps
`vel_ground.x` down to `run_speed` when braking out of TurnRun. Mixing regions
would produce a Falcon that exists in no released build.

---

## 5. Thresholds and shared constants

`src/ft/ftcommon.h`, `src/ft/ftphysics.h`, `include/macros.h`. Stick range is an
integer clamped to **±80** (`I_CONTROLLER_RANGE_MAX`).

| Constant | Value |
|---|---|
| `I_CONTROLLER_RANGE_MAX` | 80 |
| `FTCOMMON_WALKMIDDLE_STICK_RANGE_MIN` | 26 |
| `FTCOMMON_WALKFAST_STICK_RANGE_MIN` | 62 |
| `FTCOMMON_DASH_STICK_RANGE_MIN` | 56 |
| `FTCOMMON_DASH_BUFFER_TICS_MAX` | 3 |
| `FTCOMMON_DASH_DECELERATE_BEGIN` | 7.0 |
| `FTCOMMON_RUN_STICK_RANGE_MIN` | 50 |
| `FTCOMMON_TURN_STICK_RANGE_MIN` | −20 |
| `FTCOMMON_TURNRUN_STICK_RANGE_MIN` | −30 |
| `FTCOMMON_KNEEBEND_STICK_RANGE_MIN` | 53 |
| `FTCOMMON_KNEEBEND_RUN_STICK_RANGE_MIN` | 44 |
| `FTCOMMON_KNEEBEND_BUFFER_TICS_MAX` | 3 |
| `FTCOMMON_KNEEBEND_SHORTHOP_FRAMES` | 3.0 |
| `FTCOMMON_KNEEBEND_JUMP_F_OR_B_RANGE` | −10 |
| `FTCOMMON_KNEEBEND_BUTTON_{SHORT,LONG}_FORCE` | 9.0, 17.0 |
| `FTCOMMON_KNEEBEND_BUTTON_{SHORT,LONG}_MIN` | 36.0, 63.0 |
| `FTCOMMON_KNEEBEND_BUTTON_HEIGHT_CLAMP` | 77.0 |
| `FTCOMMON_FASTFALL_STICK_RANGE_MIN` | −53 |
| `FTCOMMON_FASTFALL_BUFFER_TICS_MAX` | 4 |
| `FTPHYSICS_AIRDRIFT_CLAMP_RANGE_MIN` | 8 |
| `FTINPUT_STICKBUFFER_TICS_MAX` | 254 (`U8_MAX - 1`) |
| `FTCOMMON_LANDING_INTERRUPT_BEGIN` | 4.0 |

### The stick-tap buffer (§6)

`ftmain.c:1320-1345` — this is the mechanism the whole dash/jump input model
rests on, and it is not obvious:

```
if |stick.x| crossed the ±20 deadzone:
    tap_stick_x = (was it already outside?) ? tap_stick_x + 1 : 1
else
    tap_stick_x = 254        // inside the deadzone
```

So `tap_stick_x` is **1 on the frame the stick crosses ±20**, then counts up
while held, and is pinned to 254 while neutral. `tap_stick_x < 3` therefore
means "crossed within the last 2 frames" — a *fresh tap*. Holding the stick
cannot re-trigger dash, because the counter runs past 3 and stays there.

Fast-fall (`ftPhysicsCheckSetFastFall`) uses the same idea on Y, with the extra
guards `!is_fastfall`, `vel_air.y < 0` (descending only), `stick.y <= -53`, and
`tap_stick_y < 4`.

---

## 6. Dependency classification

The closure excludes the Smash renderer, object manager, stage system and
combat, as required.

### REQUIRED MOVEMENT LOGIC — port this

- All of `ftphysics.c` except the TransN and jostle/damage paths (below).
- `ftcommon/{wait,walk,dash,run,runbrake,turn,turnrun,kneebend,jump,fall,landing}.c`
  — the state-entry, per-frame and transition functions named in §3.
- The stick-tap buffer from `ftmain.c`.
- `dCaptainMain_attr` (US column) and the §5 constants.

### OPTIONAL PRESENTATION — exclude

- `ftMainSetStatus` / `ftMainPlayAnimEventsAll` / `ftAnimEndCheckSetStatus`:
  animation dispatch. Our controller needs the *state id* and *frame counter*
  they maintain, not the animation. Replace with a plain state + frame counter.
- `attr->walk{slow,middle,fast}_anim_length` and the frame-rescaling in
  `ftCommonWalkProcInterrupt` — cosmetic gait blending between walk tiers.
- `ftParamCheckSetFighterColAnimID` / `ftMainRunUpdateColAnim` in
  `ftPhysicsCheckSetFastFall` — the fast-fall colour flash.
- `ftParamSetPlayerTagWait`, `attr->shadow_size`, `cam_offset_y`, all
  `camera_*`, `shade_color`, `fog_color`, every `*_sfx` / `*_fgm_ids`.
- `DObjGetStruct(gobj)->anim_speed`: appears in three real conditions
  (dash→run window, landing interrupt window, kneebend frame advance). It is
  1.0 for all of these states, so substitute the literal and note it.

### SMASH-STAGE-SPECIFIC COLLISION — exclude, replace at the boundary

- `ftPhysicsSetGroundVelTransferAir` — projects ground velocity onto
  `coll_data.floor_angle` for slopes, and carries the Z axis. SMB1 has no
  slopes and no Z. **Excluded**; the adapter supplies flat-ground transfer.
- `dMPCollisionMaterialFrictions[fp->coll_data.floor_flags & MAP_VERTEX_MAT_MASK]`
  in `ftPhysicsApplyGroundVelFriction` — a per-surface-material multiplier on
  `traction`. SMB1 has no material classes; use 1.0 and record the adaptation.
- `mpCommonSetFighterGround` / `mpCommonSetFighterAir` / `fp->ga` — Smash's
  ground/air kinetic state. Maps onto `ForeignState.grounded`.
- `mpCommonProcFighterOnCliffEdge`, `mpCommonSetFighterFallOnGroundBreak` in
  `ftCommonDashProcMap` — ledge behaviour. SMB1 has no ledge-grab; edge
  departure is the adapter's business (M4).

### COMBAT-ONLY — exclude

- Every `ftCommonAttack*CheckInterrupt*`, `ftCommonSpecial*`,
  `ftCommonCatch*`, `ftCommonGuardOn*`, `ftCommonEscape*`, `ftCommonAppeal*`,
  `ftCommonSquat*`, `ftCommonPass*`, `ftCommonDokan*`. These are the bulk of
  the `ProcInterrupt` bodies by line count and **none affect locomotion** —
  each is a "did the player start something else" early-out.
- `ftHammerCheckHoldHammer` and the whole hammer branch.
- `physics.vel_damage_*`, `attr->weight`, `shield_*`, `attack1_followup_frames`.
- `physics.vel_jostle_x/z` — multi-fighter body pushing. Single player: 0.

### ANIMATION-DRIVEN MOVEMENT — one state is NOT excludable

This is the one place the closure does not come out clean, and it is worth
reading carefully.

`ftPhysicsApplyGroundVelTransN` derives ground velocity from the TransN
skeleton joint's animated translation:

```c
vel_ground.x = (joints[nFTPartsJointTransN]->translate.vec.f.z - anim_vel.z) * scale.z;
```

**TurnRun's `ProcPhysics` is `ftPhysicsApplyGroundVelTransN`, unconditionally.**
Not behind the `is_use_transn_joint` flag — the status table binds it directly.
So Falcon's run-turn velocity comes out of the animation, and **transition #5
cannot be ported from source alone**: it needs the skeleton and
`FTCaptainAnimTurnRun`'s joint data.

This also explains why `ftcommonturnrun.c` defines no `ProcPhysics` of its own.

**Adaptation required (record it in the port):** TurnRun must be replaced. The
observable behaviour is already visible in `ftCommonTurnRunProcUpdate` without
the animation — on the flag frame it flips `lr` and negates `vel_ground.x`, then
`ftAnimEndCheckSetStatus` hands off to Run. A defensible substitute is to keep
that flip and hold velocity constant for the animation's length (as Run does),
rather than invent a deceleration curve. Flag it as an adaptation, not as
Falcon's real TurnRun.

Genuinely excludable, by contrast:

- `ftPhysicsGetAirVelTransN`, `ftPhysicsSetAirVelTransN`,
  `ftPhysicsApplyAirVelTransNAll/YZ` — commented in-source as Ness / Yoshi
  double-jump physics. **No Falcon locomotion state binds them**: every air
  state uses `ftPhysicsApplyAirVelDriftFastFall`.
- `ftPhysicsApplyGroundFrictionOrTransN` and its
  `anim_desc.flags.is_use_transn_joint` branch — no Falcon locomotion state
  binds this function either.

**A caveat on that flag.** Falcon's animation table
(`src/ft/ftdata.c:4160-4176`) does set `FTANIM_FLAG_TRANSN_JOINT` on `JumpB` and
`JumpAerialB`, and `FTANIM_FLAG_XROTN_JOINT` on `TurnRun`. That looked alarming
until the status table showed JumpB using ordinary air drift, so the flag there
governs joint animation, not velocity. Note also that the decomp's two
annotations of these bits **disagree**:

| Source | `0x80000000` | `0x40000000` |
|---|---|---|
| `ftdef.h:28-29` macros | `FTANIM_FLAG_TRANSN_JOINT` | `FTANIM_FLAG_XROTN_JOINT` |
| `fttypes.h:54-55` bitfield | `is_use_xrotn_joint` | `is_use_transn_joint` |

They are swapped relative to each other. Bitfield declaration order says the
first-declared bit is the most significant, which favours `fttypes.h`; that
reading also makes TurnRun the TransN state, which matches the status table.
**It does not change the port** — the status table is what binds physics — but
do not rely on either label when reading this data.

### UNRELATED ENGINE — exclude

`GObj`/`DObj` scene graph, `lbRelocGetFileData` overlay loading, `ftmanager.c`,
`ftcomputer.c` (CPU players), audio, effects, item systems.

---

## 7. Reachability from a digital NES pad

This is the sharpest finding in M0, and it is good news with one exception.

A d-pad press moves the synthetic stick from 0 to ±80 in one frame. By the §6
buffer rule that sets `tap_stick_x = 1`, which is *exactly* a fresh tap.

| Behaviour | Reachable? | Why |
|---|---|---|
| **Dash** | **Yes, always** | needs `\|stick.x\| >= 56` and `tap_stick_x < 3`; a d-pad press is 80 with tap=1 |
| Dash → Run | Yes | needs held `stick.x * lr >= 50` in the frame-16 window; holding gives 80 |
| Run → brake | Yes | release → 0 < 50 |
| Run → turn | Yes | opposite press → −80 <= −30 |
| Turn (from idle) | Yes | opposite press <= −20 |
| Jumpsquat (button) | Yes | NES **A** maps to the Smash jump-button path |
| Short hop | Yes | release A within 3 frames of jumpsquat start |
| Full hop | Yes | hold A past frame 3 |
| Fast fall | Yes | **Down** while descending: −80 <= −53, tap=1 |
| Double jump | Yes (if enabled) | `jumps_max` 2; a scope decision, not an input limit |
| **Walk (any tier)** | **NO** | see below |

**Walk is unreachable from a bare d-pad.** Walk needs `stick.x * lr >= 8` while
*not* satisfying dash's `>= 56 && tap < 3`. A d-pad press always lands at 80
with `tap = 1`, so dash always wins. The three walk tiers (Slow < 26, Middle
26–61, Fast >= 62) are all inside the analog band a d-pad cannot express.

Mitigations, in order of preference — this is a decision for M2, not M0:

1. **A walk modifier.** Hold **B** to clamp the synthetic stick to ~40, giving
   WalkMiddle. Costs one button and reaches two of three tiers.
2. **A ramp.** Have the digital→analog adapter ramp 0 → 80 over ~4 frames.
   That crosses the deadzone with `tap = 1` but at magnitude < 56, so a *quick*
   tap-and-hold walks and a *double* tap dashes. Closer to Smash's feel; risks
   making dash feel unresponsive.
3. **Accept dash-only.** Falcon's identity is his run, and plan.md explicitly
   prioritises "authentic Falcon high-speed movement over exposing every analog
   nuance" for the first milestone.

Recommendation: ship (3) for M2, add (1) behind a mod option later. Record it
either way — the adapter already keeps synthetic magnitudes rather than
hardcoding 1.0, precisely so this stays reachable.

---

## 8. Scale

One uniform conversion, per the scale policy. The stable reference is body
height against tile geometry:

- Falcon's collision diamond is **400 units** tall (`map_coll` top 400,
  bottom 0).
- SMB1's metatile grid is **16 px**, and big Mario is **2 tiles = 32 px**.

So 1 tile = 200 units, and:

```
FALCON_TO_SMB1 = 16 / 200 = 0.08   px per unit
SMB1_TO_FALCON = 12.5              units per px
```

Applied to the US attributes (per frame, or per frame² for accelerations):

| Quantity | Smash units | SMB1 px |
|---|---|---|
| `dash_speed` | 80.0 | **6.40 authored; 4.00 host-stream cap** |
| `run_speed` | 75.0 | **6.00 authored; 4.00 host-stream cap** |
| walk, full analog | 80 × 0.32 = 25.6 | 2.05 |
| `air_speed_max_x` | 31.0 | 2.48 |
| `gravity` | 3.4 | 0.272 |
| `tvel_base` | 66.0 | 5.28 |
| `tvel_fast` | 100.0 | **8.00** |
| jump, stick full | 80 × 1.0 + 24 = 104 | 8.32 |
| jump, button full hop | 77 + 24 = 101 | 8.08 |
| jump, short hop | 45 + 24 = 69 | 5.52 |
| `traction` | 1.8 | 0.144 |
| `dash_decel` | 6.0 | 0.48 |
| `air_accel`, full stick | 80 × 0.04 = 3.2 | 0.256 |
| `air_friction` | 0.2 | 0.016 |

**M4 is confirmed necessary, quantitatively.** At 6.4 px/frame running and
8.0 px/frame fast-falling, Falcon crosses half a metatile per frame
horizontally and half a tile vertically. SMB1's own collision only ever had to
cope with Mario's much smaller per-frame step, so swept/substepped motion is
not a precaution here — it is a requirement.

The remaining comparison — Falcon's 6.0 px/frame against SMB1's own
`MaximumRightSpeed` (`$0456`) — needs a Ghidra-confirmed reading of that table
and belongs to M2. Do not assume a value for it.

---

## 9. Recorded adaptations

Three, all forced by the target and none discretionary. Every one of these is a
place where the port deliberately differs from the original, and the reason.

| # | Original | Adaptation | Why |
|---|---|---|---|
| 1 | `ftPhysicsApplyGroundVelFriction` scales `traction` by `dMPCollisionMaterialFrictions[floor_flags & MAP_VERTEX_MAT_MASK]` | multiplier = 1.0 | SMB1 has no per-surface material classes |
| 2 | `ftPhysicsSetGroundVelTransferAir` projects ground velocity onto `coll_data.floor_angle` and carries a Z axis | flat-ground transfer, no Z | SMB1 has no slopes and no third axis |
| 3 | TurnRun velocity comes from the TransN joint's animated translation | keep the `lr` flip and velocity negation from `ftCommonTurnRunProcUpdate`, hold velocity for the state's duration | the animation data is not portable without the skeleton (§6) |

Plus one input limitation, which is not an adaptation of the source but of the
control scheme: **walk is unreachable from a bare d-pad** (§7), with three
documented mitigations and a recommendation.

---

## 10. Exit criterion

**Met.** The bounded set is:

- `ftphysics.c` minus the TransN, jostle and damage paths — the ground/air
  velocity primitives and the single air tick;
- the entry / update / transition functions of eleven `ftcommon` locomotion
  files, with their `ProcPhysics` bindings taken from `ftcommonstatus.h` rather
  than from the files themselves;
- the stick-tap buffer from `ftmain.c:1320-1345`;
- twenty-two shared constants (§5);
- twenty-one Captain Falcon attributes, US column (§4).

All 100% matched. All readable in source. **No ROM and no toolchain required** —
which is the finding that unblocks M1.

Every excluded dependency is named in §6 with its reason: presentation,
stage collision, combat, animation-driven movement, or unrelated engine. The
only place the closure is not clean is TurnRun, stated plainly rather than
papered over.

Two of my own working assumptions turned out wrong and were corrected against
the source rather than kept: Run applies **no** friction, and TurnRun **is**
animation-driven. Both would have produced a Falcon that felt subtly wrong with
nothing in the code to point at.
