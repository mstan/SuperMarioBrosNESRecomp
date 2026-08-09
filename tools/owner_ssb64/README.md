# Smash 64 owner-ROM cache bootstrap

`build_cache.py` is the deliberately small, dependency-free first half of the
Captain Falcon owner-ROM pipeline.  It accepts only the verified US 1.0 ROM,
normalizes z64/v64/n64 byte order in memory, and writes the *Falcon-only*
reloc files required by the current mod to a recipe- and ROM-hash-keyed user
cache.

It never copies the ROM, retains its path, or writes any data under the source
tree.  The cache is committed as a directory rename only after every
allowlisted file has been extracted, decompressed, size-checked, and hashed.
The manifest contains the normalized input SHA-1 and artifact SHA-256 values,
not a ROM path. It also preserves each allowlisted reloc's compression flag,
payload/table offset, decompressed size, and internal/external relocation-chain
heads. The next decode stage currently uses fixed validated offsets for its
selected resources, but retaining the table metadata prevents the cache from
pretending those relocation details do not exist.

Example:

```powershell
py -3 tools/owner_ssb64/build_cache.py `
  --rom 'D:\Roms\Super Smash Bros. (U) (V1.0).z64'
```

The tool implements the public VPK0/reloc format directly so neither a
BattleShip nor a SmashBrosDecomp checkout is an end-user dependency. The
recipe is intentionally limited to the currently used model (332), two effect
files (333/350), and named motion files.

`decode_intermediates.py` consumes that verified raw cache and emits the
external intermediate schema already accepted by `bake_falcon_runtime.py`:

```powershell
py -3 tools/owner_ssb64/decode_intermediates.py `
  --reloc-cache "$env:LOCALAPPDATA\SuperMarioBrosRecomp\smash64\falcon-reloc-r2-e2929e10fccc0aa84e5776227e798abc07cedabf" `
  --out "$env:LOCALAPPDATA\SuperMarioBrosRecomp\smash64\intermediate"
py -3 tools/bake_falcon_runtime.py `
  "$env:LOCALAPPDATA\SuperMarioBrosRecomp\smash64\intermediate" `
  "$env:LOCALAPPDATA\SuperMarioBrosRecomp\smash64\falcon_runtime.bin"
```

`owner_audio.py` is a separate, direct-ROM audio stage. It reads the US
`B1_sounds2.ctl/.tbl` ALBank plus the `fgm.tbl/.ucd` route directories in
memory, then writes only the eleven current Falcon PCM cues to an external
staging directory. It needs neither FFmpeg nor either upstream checkout:

```powershell
py -3 tools/owner_ssb64/owner_audio.py `
  --rom 'D:\Roms\Super Smash Bros. (U) (V1.0).z64' `
  --out "$env:LOCALAPPDATA\SuperMarioBrosRecomp\smash64\staging-audio"
```

The output directory must not be in this repository and must not already
exist. Its `manifest.json` contains the normalized owner-ROM hash and
per-cue PCM hashes, never the ROM path or a ROM slice. The four voice cues use
a deterministic, dependency-free 32-tap Kaiser-windowed sinc resampler; the
seven focused FGM cues remain sample-identical to the approved local outputs.
Integration still needs to make the launcher run these stages and validate
the final cache.

`build_final_cache.py` is the release-facing entry point. It stages the raw
reloc cache, decoder intermediates, approved `falcon_runtime.bin`, and all
eleven WAV cues on the same external volume, then publishes an immutable
content-addressed final cache only after every approved hash verifies:

```powershell
py -3 tools/owner_ssb64/build_final_cache.py `
  --rom 'D:\Roms\Super Smash Bros. (U) (V1.0).z64' `
  --cache-root "$env:LOCALAPPDATA\SuperMarioBrosRecomp\smash64"
```

The final directory contains exactly `falcon_runtime.bin`, `audio/*.wav`, and
`manifest.json`; it never contains the ROM, a ROM path, raw relocs, or decoder
intermediates. A valid cache is immutable rather than replaced in place, so a
crash or concurrent first run cannot make an already working cache disappear.
The launcher should call this only after its own owner-ROM validation, pass a
user cache root (not the installation directory), and enable the mod only
when the final baked cache manifest verifies.
