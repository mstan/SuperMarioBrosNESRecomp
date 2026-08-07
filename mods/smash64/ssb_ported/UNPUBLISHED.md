# Quarantine — do not publish anything in this directory

This directory holds source **ported directly** from the Super Smash Bros. 64
decompilation:

- Upstream: <https://github.com/VetriTheRetri/ssb-decomp-re>
- Pinned revision: `054ffc23f396868cd1db2b87ee3a2c1d3bebb75a` (branch `main`, 2026-08-04)
- Local reference checkout: `F:\Projects\SmashBrosDecomp` (untracked, not a submodule)

## Why it is quarantined

That repository **publishes no license** — verified 2026-08-07 via the GitHub
API, which reports `license: null`, and the repository root carries no license
file. Using it as a technical reference is fine. Redistributing its source, or
code derived closely from it, is not something we can do from a repository
whose remote is public.

`SuperMarioBrosNESRecomp` and `nesrecomp` both have public GitHub remotes.
Therefore:

> **`feat/smash64-player-replacement` is a local branch. It is not pushed,
> not merged to `master`, and not released.**

## Guards in place

1. `branch.feat/smash64-player-replacement.pushRemote` points at
   `UNPUBLISHED-ssb-decomp-port`, a remote that does not exist, so a reflexive
   `git push` fails instead of succeeding.
2. `.git/hooks/pre-push` in this repository rejects any push whose commits
   touch `mods/smash64/ssb_ported/`.
3. This file.

Guards are a safety net, not the policy. The policy is that the branch stays
local.

## What may leave this directory

Nothing derived from the decompilation.

These are unaffected and remain publishable on their own, because they contain
no ported code:

- the engine work on the `nesrecomp` side (`foreign_controller`,
  `nes_mod_option_value`, conditional plugin activation);
- the mod package manifest and plugin registration;
- the SMB1 host adapter (`game_smash64.c`);
- the ForeignController interface that the character controllers implement.

If the upstream project later adopts a license that permits redistribution, or
the locomotion is reimplemented clean-room from documented behaviour and
constants, revisit this file — and only then.

## Attribution

See `THIRD-PARTY-LICENSES/README.md` in the repository root.
