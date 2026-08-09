# Third-party licenses and attribution

This project (`SuperMarioBrosRecomp`) ships the NESRecomp runner plus
game-specific code. This file records third-party work the project depends on
or derives from, and the terms under which each is used.

Nothing in this repository redistributes Nintendo assets. The runner requires a
stock Super Mario Bros. ROM the user supplies; it is verified by CRC32 and
never modified.

## Mod authors and derived work

### Super Smash Bros. 64 decompilation — *community/decomp-derived controller*

The Smash 64 player replacement mod's locomotion derives from
**`VetriTheRetri/ssb-decomp-re`**, a decompilation of the original *Super Smash
Bros.* for Nintendo 64, at pinned revision
`054ffc23f396868cd1db2b87ee3a2c1d3bebb75a` (branch `main`, 2026-08-04).

The behavioural research — the fighter state machine, the physics model, and
the per-character attribute data that make Captain Falcon move like Captain
Falcon — is the work of **VetriTheRetri and the `ssb-decomp-re` contributors**.

**That repository publishes no license.** Verified 2026-08-07 via the GitHub
API (`license: null`); the repository root carries no license file. For the
initial Captain Falcon release, the project owner has directed this project to
treat the community/decomp-derived controller as permissively reusable. That
is a project publication assumption, not a verified upstream license grant or
a legal conclusion about the upstream repository.

Consequently:

- The published controller preserves the upstream attribution and pinned
  revision above. Its treatment as publishable is the project assumption just
  stated, not an assertion that the upstream repository has a permissive
  license.
- The decomp is **not** a submodule, so cloning this repository never pulls it.
- No Super Smash Bros. 64 ROM, ROM slice, decoded asset, generated runtime
  blob, or locally rendered audio is distributed. The mod requires a
  user-selected, locally verified owner ROM and keeps generated data outside
  the release payload.

The mod's own integration contributions — the mod package manifest, plugin
registration, the SMB1 host adapter, and the engine-side `ForeignController`
interface — are original to this project and carry its license.

### Super Mario Bros. disassembly — *submodule, technical reference*

`smb-disassembly/` is a submodule pointing at
**`threecreepio/smb-disassembly`** (a ca65 port of doppelganger's Super Mario
Bros. disassembly) pinned at `da964553b3695fde607d796acde21b3f4b282dfe`. It is
the authoritative source for this project's SMB1 symbol names.

That repository publishes no license. A submodule records a URL and a commit —
it redistributes nothing, and the pin is there so a symbol name can always be
traced back to the exact revision it came from.

`nesrecomp/tools/ingest_smbdis.py` derives `symbols.sym` from it and copies
**only names and addresses** — no ROM bytes, no instruction text, and none of
the disassembly's own commentary. That is the same treatment
`snesrecomp/tools/ingest_dkc2_disasm.py` applies to the DKC2 disassembly.

## Framework and libraries

| Component | Role | Terms |
|---|---|---|
| [`nesrecomp`](https://github.com/mstan/nesrecomp) | 6502 static recompiler and runner | see that repository |
| [`recomp-ui`](https://github.com/mstan/recomp-ui) | pre-boot launcher (Dear ImGui) | see that repository |
| SDL2 | window, input, audio | zlib |
| Dear ImGui | launcher widgets | MIT |
