# Semcomp — Semantic Recompilation Layer

> **Status (Phase 0 — scaffold):** Compile-only façade. No behavior changes.
> Existing recomp build is unchanged. Toggle via `-DENABLE_SEMCOMP=ON|OFF`
> (default ON). Source lives in `semcomp/`.

## What is Semcomp?

**Semcomp** — short for *semantic recompilation* — is a behavior-preserving
reconstruction layer built on top of a verified static recompilation. A normal
recomp mechanically translates original machine code into native code. A
semcomp keeps that verified recomp as the **correctness oracle**, then
incrementally wraps or replaces the machine-shaped generated code with
human-readable, mod-friendly source concepts: `Game`, `Mario`, `Level`,
`Camera`, `EnemySystem`, `ModApi`.

The goal is **observable behavioral equivalence** with a modern semantic
architecture. Same inputs, same RAM/state deltas, same visible side effects.
The internal organization is allowed to diverge freely.

## How it differs from decomp and recomp

| Layer    | What it produces | Faithfulness target |
|----------|------------------|---------------------|
| **Decomp**  | Source code that re-assembles to the original ROM, byte-identical | Source match: every instruction, every layout decision preserved |
| **Recomp**  | Native code mechanically translated from original machine code  | Behavior match: same observable execution given same inputs |
| **Semcomp** | Human-readable C++ classes wrapping/replacing the recomp        | Behavior match: same observable execution; internal architecture free to evolve |

Semcomp is **not** a source-matching decompilation — it does not try to
recreate the authoring/source architecture. It is **not** a loose remake — it
must reproduce observable behavior. It is a clean architectural layer that
preserves correctness by deferring to the recomp until a piece has been
independently validated.

## Architecture (Phase 0)

```
semcomp/
  semcomp.h        — umbrella include and version macros
  SmbRamMap.h      — verified RAM address constants (smbdis labels)
  GameState.h/.cpp — typed wrapper over g_ram[] and CPU state
  SemcompGame.h    — top-level facade: owns Mario/Level/Camera/ModApi
  Mario.h/.cpp     — Mario player accessors
  Level.h/.cpp     — world/level/area accessors
  Camera.h/.cpp    — screen edge accessors
  ModApi.h/.cpp    — hook registration surface (no-op stub)
  Selftest.cpp     — compile-checked exercise of every accessor
```

Everything lives in `namespace smb::semcomp`. Accessors are `const` and
read-only against the recomp's `g_ram` and CPU state.

## Migration plan

### Phase 0 — Semantic wrappers around recomp state *(this branch)*
- C++ façade classes exist and compile.
- Accessors read RAM via verified smbdis labels.
- No writes, no calls into the frame path, no behavior changes.
- `ENABLE_SEMCOMP=OFF` produces a byte-identical binary to pre-semcomp master.

### Phase 1 — Name RAM/state and function boundaries
- Extend `SmbRamMap.h` to cover every RAM byte used by SMB (currently HANDOFF
  documents ~13 RAM labels; smbdis has ~200+).
- Map every `func_XXXX` in `generated/super-mario-bros_full.c` to a named
  symbol via the existing `symbols.sym` → `symbol_file` codegen path.
- Identify semantic function boundaries: `Mario::update`, `EnemySystem::tick`,
  `Renderer::draw`, etc. — just *names* paired with generated PCs; no code
  movement yet.

### Phase 2 — Clean wrappers for Mario / Level / Enemy / Camera / Renderer
- The façade classes gain write accessors and lifecycle methods.
- `SemcompGame::update_frame()` is invoked from the runner's frame path; it
  delegates to the generated frame routine.
- Mod hooks fire before/after the delegated call.
- Still no replacement of generated logic.

### Phase 3 — Replace small verified routines one at a time
- Pick a leaf routine with low coupling (e.g., a math helper, a single sound
  effect dispatch).
- Write a C++ implementation in the appropriate semcomp class.
- Route the call through the façade with a runtime switch
  (`use_semantic` flag) so the generated and semantic implementations can be
  swapped at runtime for A/B parity testing.
- Promote the semantic implementation once parity holds across a recorded
  trace.

### Phase 4 — Replace larger systems with trace/parity validation
- Same shape as Phase 3, but for full subsystems: collision, physics, AI.
- Always validated against the recomp behind a runtime switch.

## Acceptance criteria for replacing generated behavior

A semantic implementation may replace a generated routine only when **all** of
the following hold:

1. **Same inputs** — function signature in semantic form accepts the same
   CPU/RAM state the generated routine reads.
2. **Same relevant RAM/state deltas** — every byte the generated routine
   writes is written by the semantic routine with the same value, modulo
   intermediate scratch addresses documented as "free to differ".
3. **Same visual/audio-relevant side effects** — OAM writes, palette writes,
   APU register writes, NMI signaling: byte-identical to the generated path
   across the validation trace.
4. **Fallback remains possible** — the generated implementation stays in the
   binary behind a runtime flag for at least one milestone after promotion,
   so regressions can be A/B-bisected against the recomp.

Parity validation uses the existing `--verify` mode (Nestopia oracle) plus
the reverse-debugger ring buffer documented in `nesrecomp/`'s
`REVERSE_DEBUGGER.md`.

## What semcomp does NOT do

- It does not rewrite gameplay in this branch.
- It does not edit `generated/*.c` (hard rule — those files are owned by the
  recompiler and regenerated by `build_all.bat`).
- It does not introduce fake gameplay stubs that bypass existing behavior.
- It does not require any new external dependency. RAM labels are sourced
  from the smbdis disassembly already pinned via `symbols.sym`
  (`threecreepio/smb-disassembly`).

## Build

`ENABLE_SEMCOMP` defaults to ON. To opt out and produce a binary identical to
pre-semcomp master:

```
cmake -S . -B build_release -G Ninja -DCMAKE_BUILD_TYPE=Release ^
      -DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl ^
      -DENABLE_NESTOPIA_ORACLE=OFF -DNESRECOMP_REVERSE_DEBUG=OFF ^
      -DENABLE_SEMCOMP=OFF
cmake --build build_release
```
