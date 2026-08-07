# Third-party licenses and attribution

This project (`SuperMarioBrosRecomp`) ships the NESRecomp runner plus
game-specific code. This file records third-party work the project depends on
or derives from, and the terms under which each is used.

Nothing in this repository redistributes Nintendo assets. The runner requires a
stock Super Mario Bros. ROM the user supplies; it is verified by CRC32 and
never modified.

## Mod authors and derived work

### Super Smash Bros. 64 decompilation — *technical source, not redistributed*

The Smash 64 player replacement mod's locomotion derives from
**`VetriTheRetri/ssb-decomp-re`**, a decompilation of the original *Super Smash
Bros.* for Nintendo 64, at pinned revision
`054ffc23f396868cd1db2b87ee3a2c1d3bebb75a` (branch `main`, 2026-08-04).

The behavioural research — the fighter state machine, the physics model, and
the per-character attribute data that make Captain Falcon move like Captain
Falcon — is the work of **VetriTheRetri and the `ssb-decomp-re` contributors**.

**That repository publishes no license.** Verified 2026-08-07 via the GitHub
API (`license: null`); the repository root carries no license file. Reading it
as a technical reference is fine; redistributing its source from a public
repository is not.

Consequently:

- No decompiled Smash 64 source is present in any published branch of this
  repository.
- Work that ports it lives on a local-only branch and is quarantined under
  `mods/smash64/ssb_ported/`, with push guards described in
  `mods/smash64/ssb_ported/UNPUBLISHED.md`.
- The decomp is **not** a submodule, so cloning this repository never pulls it.
- No Smash 64 assets — models, textures, animations, audio — are used or
  distributed.

This mirrors how `MegaManX6Recomp` treats acediez's *Mega Man X6 Tweaks*
research: full credit to the original author, re-implementation of only the
integration layer, and none of the upstream payload redistributed.

The mod's own contributions — the mod package manifest, plugin registration,
the SMB1 host adapter, and the engine-side `ForeignController` interface — are
original to this project and carry its license.

## Framework and libraries

| Component | Role | Terms |
|---|---|---|
| [`nesrecomp`](https://github.com/mstan/nesrecomp) | 6502 static recompiler and runner | see that repository |
| [`recomp-ui`](https://github.com/mstan/recomp-ui) | pre-boot launcher (Dear ImGui) | see that repository |
| SDL2 | window, input, audio | zlib |
| Dear ImGui | launcher widgets | MIT |
