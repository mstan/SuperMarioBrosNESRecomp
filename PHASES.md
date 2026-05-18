# Semcomp Phase Plan — SuperMarioBrosNES Recomp

Living document tracking the architectural-ownership effort: lift SMB
routines into the C++ `semcomp/` layer one at a time via game.toml's
`[[replace_func]]` mechanism, verified by **natural in-game behavior**
(not trainer buttons).

## Operational principles

1. **Replace_func over buttons.** A trainer button is optional polish.
   Architectural ownership = the recompiler dispatches into our C++
   class when the natural caller fires. See
   `memory/feedback_replace_func_over_buttons.md`.
2. **No recompiler edits.** When stuck on an inner-label tangle,
   re-implement sub-pieces in C++ first; don't touch `nesrecomp/`.
3. **No printf/log files.** Use TCP debug commands + ring buffer.
4. **Taskkill before build.** `cmake --build` can't overwrite a
   running exe; kill `SuperMarioBrosRecomp.exe` and `python.exe`
   (trainer GUI) first.
5. **One natural in-game test per phase.** Never ship a phase whose
   verification is "trainer button clicks the right thing".
6. **1-3 small routines per phase** (< ~40 lines each). Larger
   routines get dedicated phases. Bigger batches are bisect-hostile.
7. **Atomic commits per phase.** `git log` reads like the phase
   list; bisect is clean.

## Inner-label issue (recurring blocker)

The recompiler emits some "inner labels" (jump targets inside a
function) as separately-emitted standalone functions that
`call_by_address` back into the parent's interior. When the parent is
`[[replace_func]]`'d, the body containing those labels disappears, and
the standalone's `call_by_address` invocation now hits our replacement
(potentially infinite-recursing or missing the label).

**Untangle workaround:** re-implement the sub-pieces (the "inner
label" callees) as standalone C++ first, THEN replace the parent.
Strategy used for future phases 15-21.

Known tangles (deferred for now):
- `$BD9B BumpBlock` — sub-handlers MushFlowerBlock/$BDD2, VineBlock/
  $BDDF, $BB38, $BDD5, $BDD8 are inner labels.
- `$8F5F DigitsMathRoutine` — `$8F75 StoreNewD` is emitted separately
  and calls back into `$8F68 AddModLoop` inside $8F5F.
- `$84C3 FloateyNumbersRoutine` — `$8534` calls back inside.
- `$D92C InjurePlayer / $D931 ForceInjury / $D958 KillPlayer` — fused
  body with `call_by_address(0xD92C)` re-entry from inside.
- `$F41B Square1SfxHandler`, `$F57C Square2SfxHandler`, `$F2D0
  SoundEngine` — multi-entry dispatch via call_by_address.

## Owned routines (as of Phase 11)

| Address | Routine             | Class                     | Phase  |
| ------- | ------------------- | ------------------------- | ------ |
| $BBFE   | GiveOneCoin         | SmbRoutines::give_coin    | 3      |
| $BC49   | SetupPowerUp        | Powerups::setup           | 4b     |
| $8182   | PauseRoutine        | GameMode::on_pause_tick   | 5      |
| $8F06   | PrintStatusBarNumbers | Hud::print_status_bar_numbers | 6  |
| $BC27   | AddToScore          | Hud::add_to_score         | 6      |
| $DA11   | SetupFloateyNumber  | FloateyNumbers::setup     | 7      |
| $C30E   | InitNormalEnemy     | Enemies::init_normal_enemy| 8      |
| $CA77   | MoveNormalEnemy     | Enemies::move_normal_enemy| 8      |
| $B0E6   | AutoControlPlayer   | PlayerPhysics::auto_control | 9    |
| $B329   | PlayerMovementSubs  | PlayerPhysics::movement_subs | 9   |
| $B233   | PlayerChangeSize    | PlayerAnim::change_size   | 10     |
| $B245   | PlayerInjuryBlink   | PlayerAnim::injury_blink  | 10     |
| $B269   | PlayerDeath         | PlayerAnim::player_death  | 10     |
| $B27D   | PlayerFireFlower    | PlayerAnim::fire_flower   | 10     |
| $B35A   | OnGroundStateSub    | PlayerPhysics::on_ground_state_sub | 11 |
| $B36D   | FallingSub          | PlayerPhysics::falling_sub | 11    |

**16 routines owned. ~0.8% of 2026 total functions, but most of the
core gameplay loop.**

## C++ facade classes

```
semcomp/
  Mario.h/.cpp           — player attribute reads + verbs
  Level.h/.cpp           — level reads
  Camera.h/.cpp          — camera reads + lock/teleport
  PlayerSession.h/.cpp   — coins/lives/score/timer
  Enemy.h/.cpp           — single-slot enemy facade
  Enemies.h/.cpp         — 5-slot container + init/move
  Powerups.h/.cpp        — power-up entity setup
  Blocks.h/.cpp          — DEFERRED (BumpBlock tangle)
  Hud.h/.cpp             — status bar refresh + add_to_score
  FloateyNumbers.h/.cpp  — floatey-points spawn
  GameMode.h/.cpp        — OperMode + pause + end_level + warp
  PlayerPhysics.h/.cpp   — auto_control, movement_subs, ground/fall
  PlayerAnim.h/.cpp      — 4 anim state routines
  SemcompGame.h          — top-level singleton (owns all)
  Runtime.h/.cpp         — C-ABI bridge (called from extras.c)
  SmbRamMap.h            — verified RAM address constants
  SmbRoutines.h/.cpp     — primitives (BCD setup, SFX, etc.)
  RoutineRegistry.h/.cpp — invocation counter for owned routines
  Trainer.h/.cpp         — addr-keyed freeze table
  TrainerUI.h/.cpp       — F8 overlay
  GameState.h/.cpp       — raw RAM accessor
  ModApi.h/.cpp          — mod hooks
  Selftest.cpp           — sanity tests
```

## Remaining phases (revised cadence — 1-3 routines per phase)

### Phase 12 — JumpSwimSub (dedicated, ~75 lines)
- `$B376 JumpSwimSub` — careful port. Heavy branching: gravity check,
  swim-tier physics, BPL sign-check (the polarity gotcha that bit Phase
  11 mid-batch).

### Phase 13 — ClimbingSub (dedicated, ~140 lines)
- `$B3CF ClimbingSub` — vine/flagpole climb. Position update plus
  $B420-$B447 animation-frame tail.

### Phase 14 — PhysicsSub (DEFERRED — dedicated future session, ~300 lines)
- `$B450 PlayerPhysicsSub` — per-frame physics dispatcher. 3 nested
  branches (ProcClimb / CheckForJumping / X_Physics) + multiple ROM
  table lookups at $B44D/$B44A/$B424/$B42B/$B439/$B432/$B440/$B443/$B447.
- Calls into 3 standalone helpers ($B488 NoJump, $B51C X_Physics, $B55E
  GetXPhy) which all exist as separately-emitted func_XXXX_b0.
- Carry-flag propagation hazards: 16-bit physics-tier accumulator math
  + branch-polarity hazards (BPL/BCS/BCC checks against $0700 sub-state).
- **Why deferred:** highest-stakes routine in the player-control chain;
  a subtle polarity inversion makes Mario unplayable. Worth a full
  session of careful porting + frame-perfect comparison vs Nestopia
  oracle, not a rushed spike.

### Phase 15 — MovePlayer family (DEFERRED — split across other phases)
Candidate addresses surveyed via symbols.sym:
- `$B200 MovePlayerYAxis` — trivial 3-instruction Y-position increment.
  Too small for a standalone phase; will roll into Phase 14 (PhysicsSub)
  when that lands, since $B450 is its main caller.
- `$BF09 MovePlayerHorizontally` — emitted with multi-entry-point body
  via `func_BF09_b0_body(int _entry)`. Shares body with `$BF4C ExXMove`.
  Inner-tangle: needs untangle before replace_func can land.
- `$BF4D MovePlayerVertically` — `call_by_address(0xBF4C)` re-entry from
  inside. Same tangle class. Untangle first.

**Why deferred:** the trivial $B200 isn't worth a phase on its own, and
the $BF09/$BF4D pair needs the same untangle treatment as Phase 19/20/21.
Bundled into a future untangle-batch phase.

### Phase 16 — Player BG collision (DEFERRED — large + likely tangled)
- `$DC64 PlayerBGCollision` — 420 lines of generated C. Almost certainly
  contains inner labels (post-DA00 routines pattern). Needs an untangle
  audit before replace_func is safe.
- Related: `$E325 PlayerCollisionCore`, `$BCED PlayerHeadCollision`.
- **Why deferred:** size + tangle risk. High-stakes (Mario's
  collision response — falling off cliffs, hitting blocks). Worth a
  dedicated session with frame-perfect oracle comparison.

### Phase 17 — Player graphics (DEFERRED — multi-entry-point tangles)
Original Phase 17 addresses were wrong. Verified via symbols.sym:
- `$EFA4 DrawPlayer_Intermediate`, `$EFDC DrawPlayerLoop`
- `$F12A RelativePlayerPosition` — multi-entry body shared with $F12C
  (multi-entry _body(int _entry) pattern)
- `$85F1 GetPlayerColors`
- `$EEE9 PlayerGfxHandler` — 12-entry-point body (heaviest tangle in the
  codebase so far)

**Why deferred:** Pervasive multi-entry-point tangles. Each entry has
distinct semantics handled by the case dispatch at function head.
Replacing one entry without the others is unsafe. Untangle pass needed.

### Phase 18 — Non-enemy object handlers (DEFERRED — inner-label split + helper chain)
- `$BC85 PowerUpObjHandler` — ~100 lines. Has inner-label split:
  $BCD8 RunPUSubs is emitted as standalone func_BCD8_b0 and is
  tail-called from within $BC85 at $BCA7/$BCB0. The RunPUSubs block at
  $BCD8 also exists inline in $BC85's body (fall-through path).
- Fireball/coin per-frame handlers: `$D410 FireballObjCore`,
  `$F38C FireballObjHandler`, related coin entry.
- **Why deferred:** PowerUpObjHandler is mostly mechanical (state dispatch +
  6 sub-routine calls), but coordinating with Powerups facade ownership
  + tail-call to RunPUSubs needs careful planning. Bundles cleanly with
  Phase 19 (Block ownership) which also touches the power-up path.

### Phase 19 — Block ownership (DEFERRED — known untangle, dedicated session)
- Re-implement `$BDD2 MushFlowerBlock`, `$BDDF VineBlock`, `$BB38`,
  `$BDD5`, `$BDD8` as standalone C++.
- Then [[replace_func]] `$BD9B BumpBlock`. Activates dormant
  `Blocks` class.
- **Why deferred:** untangle work is high-risk — re-implementing the
  sub-handlers requires bit-for-bit fidelity with the generated code.
  Worth a dedicated session per untangle target.

### Phase 20 — HUD math reconciliation (DEFERRED — known untangle)
- Re-implement `$8F75 StoreNewD` in C++.
- Then [[replace_func]] `$8F5F DigitsMathRoutine` + `$8F11
  OutputNumbers`.
- **Why deferred:** same untangle-fidelity risk as Phase 19.

### Phase 21 — Floatey per-frame (DEFERRED — known untangle)
- Re-implement `$8534` helper.
- Then [[replace_func]] `$84C3 FloateyNumbersRoutine`.
- **Why deferred:** same untangle-fidelity risk as Phase 19.

### Phase 22 — Damage chain (DEFERRED — known untangle)
- Untangle `$D92C InjurePlayer / $D931 ForceInjury / $D958
  KillPlayer`. Full re-implementation of the fused body.
- **Why deferred:** highest-stakes untangle — wrong port lets Mario
  die unexpectedly or become invincible. Dedicated session.

### Phase 23 — Game-mode dispatchers
- `$8231 TitleScreenMode`, `$AEDC GameMode`, `$9218 GameOverMode`,
  `$8212 OperModeExecutionTree`. Extends `GameMode`.

### Phase 24 — Enemies mega-phase (DEFERRED — pervasive multi-entry-body tangles)
Spike audit of the C2F0-C3xx area surfaces severe tangling:
- `$C31E InitRedKoopa` is multi-entry-body with $C321
- `$C342 InitBloober` is multi-entry-body (entries at $C342, $C365, $C367)
- `$C34A InitRedPTroopa` is an INNER LABEL inside $C342_body
- `$C346 SmallBBox` is inside $C342_body — $C2F1 InitGoomba tail-calls it
  via func_C346(), so the recompiler must emit it standalone too

Many enemy inits share bodies via fall-through (smaller per-type bounding
box init, then a shared "rest of init" block). Original 6502 used fall-
through liberally to save bytes. Untangling each is a per-routine task.

Original plan unchanged below — ~60-80 routines under Enemies class
covering inits, per-type movement, collision, graphics. Test 1-1 through 1-4.

**Why deferred:** mega-phase. Per the existing plan this gets its own
check-in. Untangle audit + per-init replace_func is a multi-session
project, not a spike target.

### Phase 25 — Level parser (DEFERRED — mega-phase, own check-in)
- AreaParser, LoadAreaPointer, ProcessAreaData, segment parsers,
  AreaParserTaskHandler dispatch, Castle/Underwater/Bonus-room
  handlers.
- New `LevelLoader` class. ~30-40 routines.
- **Why deferred:** mega-phase per existing plan. Needs dedicated
  multi-session ownership pass. AreaParser has dense bit-packed
  level-format decoders that need careful porting + cross-level
  verification.

### Phase 26 — Background renderer + NMI/VRAM helpers (DEFERRED — timing-critical)
- Column writers, MetatileBuffer, BG_collision helpers.
- Reset vector, NMI handler chain, WritePPUReg, WritePPUData.
- **Why deferred:** NMI handler runs once per frame and is the most
  timing-sensitive code in the codebase. The existing tile-pipeline has
  documented stale-band behavior (see memory/project_stale_band.md) —
  changing this path risks frame-perfect rendering quirks. Needs a
  dedicated session with frame-by-frame diff vs Nestopia oracle.

### Phase 27-30 — Sound + music (deprioritized, own check-in)
- Untangle Square1Sfx / Square2Sfx / Noise inner-label tangles.
- [[replace_func]] `$F41B`, `$F57C`, NoiseSfxHandler.
- [[replace_func]] `$F2D0 SoundEngine`.
- Music routines (MainMusicLoop, AreaMusic, MainHandler,
  NoteLengthHandler).
- DMC handlers.
- ~80-100 routines under new `Sound` class.
- Bonus: may unblock silent-coin-pickup mystery.
- **Check-in BEFORE starting Phase 27.**

### Phase 31 — Utility routines (last, own check-in)
- Math helpers, OAM dumpers, sprite-data writers, palette writers,
  misc small utilities.
- Final coverage audit; document anything intentionally left natural.
- **Check-in BEFORE starting Phase 31.**

## Skill / tooling notes

- **Verbatim porting workflow:** for each routine, read its body in
  `generated/super-mario-bros_full.c`, port to C++ using `nes_read` /
  `nes_write` / `g_cpu` / `call_by_address(0xXXXX)` for sub-callees.
  Use `goto` labels matching the 6502 label names for fidelity. Watch
  signed-comparison polarity (BPL/BMI/BCC/BCS); inverted gotos break
  gameplay silently.
- **Sub-callee discovery:** before porting, `grep "^void func_XXXX_b0"`
  on referenced sub-routines to confirm they're emitted standalone.
  If they're inner labels of another function, plan an untangle first.
- **Trainer GUI:** restart it whenever the game exe restarts (TCP
  disconnect on game restart). See `memory/feedback_restart_trainer_with_game.md`.
- **Python launch caveat:** use full pyenv path
  `C:\Users\Matthew\.pyenv\pyenv-win\versions\3.10.9\python.exe` —
  MS Store python.exe shim silently fails for the GUI.

## Build commands

```powershell
# Full rebuild (recompiler regen + game):
try { Stop-Process -Name SuperMarioBrosRecomp -Force -ErrorAction Stop } catch {}
Set-Location F:\Projects\nesrecomp-release\SuperMarioBrosRecomp
& .\nesrecomp\build_recomp\NESRecomp.exe baserom.nes --game game.toml
& cmd.exe /c 'call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64 >nul 2>&1 && set "PATH=C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin;C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja;%PATH%" && cmake --build build_release 2>&1'

# Launch:
Start-Process -FilePath "$PWD\build_release\SuperMarioBrosRecomp.exe" -ArgumentList "--trainer" -WorkingDirectory "$PWD\build_release"
Start-Process -FilePath "C:\Users\Matthew\.pyenv\pyenv-win\versions\3.10.9\python.exe" -ArgumentList "tools\trainer_gui.py" -WorkingDirectory $PWD
```

## Memory references

User-facing context lives in `~/.claude/projects/F--Projects-nesrecomp-release-SuperMarioBrosRecomp/memory/`:

- `user_profile.md` — experienced recomp dev
- `project_semcomp.md` — Phase 3 framework notes
- `feedback_replace_func_over_buttons.md` — architectural ownership over GUI buttons
- `feedback_restart_trainer_with_game.md` — bundle GUI relaunch with game relaunch
- `feedback_use_tcp_screenshots.md` — verify via TCP, not by asking user
- `feedback_tcp_persistent.md` — set_input clears on disconnect
- `feedback_taskkill_before_build.md` — always taskkill game before build
- `feedback_background_tasks.md` — task completion != game exit
- `feedback_ring_buffer_autonomous.md` — ring buffer records every frame
- `reference_tcp_server.md` — TCP server reference (port 4370)
- `reference_ghidra_mcp.md` — Ghidra MCP for SMB
- `project_extras_c_wrong_labels.md` — extras.c had bad RAM labels
- `project_smb_hud_in_ppu.md` — HUD lives in PPU VRAM
- `project_smb_givecoin_falls_through.md` — $BBFE/$BC22/$BC27 fall-through
- `project_widescreen.md` — shelved widescreen project
- `feedback_widescreen.md` — lessons from widescreen
- `project_stale_band.md` — NT column write behavior
