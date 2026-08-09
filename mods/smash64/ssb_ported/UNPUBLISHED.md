# Captain Falcon controller provenance and initial-release publication policy

This directory holds source **ported directly** from the Super Smash Bros. 64
decompilation:

- Upstream: <https://github.com/VetriTheRetri/ssb-decomp-re>
- Pinned revision: `054ffc23f396868cd1db2b87ee3a2c1d3bebb75a` (branch `main`, 2026-08-04)
- Local reference checkout: `F:\Projects\SmashBrosDecomp` (untracked, not a submodule)

## Upstream license status and project decision

That repository **publishes no license** — verified 2026-08-07 via the GitHub
API, which reports `license: null`, and the repository root carries no license
file.

For this initial release, the project owner has directed this project to treat
the community/decomp-derived controller as permissively reusable. This is a
project publication assumption, **not** a verified upstream license grant or a
legal conclusion about the upstream repository. Preserve the upstream credit
and pinned revision above in every release that includes this code.

The historical filename is retained so existing source comments continue to
lead to this provenance record. It is not a publication prohibition.

## Release boundary that remains in force

The release may include this controller source under the project assumption
above. It must never include any Super Smash Bros. 64 ROM, ROM slice, decoded
asset, generated fighter runtime blob, locally rendered audio, user cache, or
saved configuration containing an owner-ROM path.

The release builder enforces this by staging only the executable, approved
launcher assets, and source-controlled package manifests. It stages neither
`assets_ssb64/` nor `mods/state.toml`.

## What may be published

The controller, the mod package manifest and registration, the SMB1 host
adapter, and the engine-side `ForeignController` integration may be published
for the initial release. Revisit this decision if verified upstream licensing
information becomes available or the project release policy changes.

## Attribution

See `THIRD-PARTY-LICENSES/README.md` in the repository root.
