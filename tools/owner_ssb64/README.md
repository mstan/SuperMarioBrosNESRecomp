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

## Pikachu prototype intermediates

`pikachu_owner.py` is an isolated, dependency-free prototype for the next
character. It deliberately does **not** alter or replace any Falcon cache or
runtime output. Given the same verified owner ROM, it creates an external
`pikachu-prototype-r2-<sha1>` cache containing:

- reloc 341's 27-joint high-detail model and structured material pointers;
- costume selections 0-3, including the costume-frame material animation
  inputs, joint-11 accessory used by costumes 1-3, and both facial texture-part
  selections;
- 37 locomotion, normal, aerial, and special animations, with their explicit
  26/27-entry pointer-table geometry;
- Thunder Jolt (342), Thunder/Thunder Shock (347), and model-resident Thunder
  Trail effect inputs and exact texture-storage spans;
- all 16 direct Pikachu voice waves as deterministic 44.1 kHz WAVs, using
  each route's initial UCD note plus TBL articulation pitch from the nominal
  32 kHz N64 mixer rate; and
- the 15 required Pikachu FGM programs, their fork/articulation bytecode,
  decoded source waves, and explicit looping metadata for ElectricLoop.

```powershell
py -3 tools/owner_ssb64/pikachu_owner.py `
  --rom 'D:\Roms\Super Smash Bros. (U) (V1.0).z64' `
  --cache-root "$env:LOCALAPPDATA\SuperMarioBrosRecomp\smash64"
```

The character model's generated upstream comments do not reliably describe
the dimensions of its packed CI4 atlases. This stage therefore preserves the
exact owner-ROM storage spans and structured MObj/material-animation offsets;
the later runtime baker remains responsible for mapping individual tile views.
Likewise, FGM outputs here are route programs plus decoded source samples, not
claims of fully synthesized final effects. The manifest recursively hashes
every nested manifest and payload, rejects ROM-like filenames and ROM-sized
files, contains no input path, and is byte-identical for canonical z64, v64,
and n64 inputs.

### Minimal Pikachu runtime audio

`pikachu_audio.py` turns the audio intermediates into a minimal 13-cue runtime
set: three special-move voices, light swing S/M/L, Electric 1/2/3/5, Quick
Attack start, Thunder, and ElectricLoop. Its manifest also records the exact
numeric `PikachuEvent` ABI from `pikachu_locomotion.h` rather than assuming an
FGM route number is a host event number.

```powershell
py -3 tools/owner_ssb64/pikachu_audio.py `
  --rom 'D:\Roms\Super Smash Bros. (U) (V1.0).z64' `
  --out "$env:LOCALAPPDATA\SuperMarioBrosRecomp\smash64\pikachu-audio-staging"
```

Direct voices are exact VADPCM decodes followed by the same deterministic
windowed-sinc resampling used by Falcon. Their effective rates come from the
nominal 32 kHz N64 mixer plus each route's initial UCD note and TBL
articulation pitch: Special-N is -440 cents (24,818 Hz), Special-Lw is -560
cents (23,156 Hz), and Special-Hi is -1200 cents (16,000 Hz). This focused
offline renderer bakes the on-trigger pitch and does not claim to emulate later
UCD note changes. Each finite FGM cue validates its US
1.0 UCD route, fork closure, articulation, and triggered wave, then applies a
small recipe-specific pitch/gain approximation. It is explicitly not a full
FGM or RSP synthesizer. `pikachu_electric_loop.wav` contains one bounded period
of wave 12's canonical ALADPCM loop (source samples 100 through 7664); its
manifest provides `[start_frame, end_frame)` forward-loop metadata instead of
expanding the source's infinite loop count. The renderer writes atomically to
an external new directory, embeds neither ROM bytes nor its path, and does not
create tracked WAV assets.

The current controller directly maps events 0-9 to the three voices, three
swings, and Electric 1/2/3/5. Quick Attack route 231 maps to event 10 and is
emitted alongside voice-Hi on each zip. ElectricLoop route 230 maps to Thunder
Jolt projectile-spawn event 15, matching BattleShip's weapon creation path;
Thunder route 232 maps to projectile-spawn event 16. Conversely, event 11
(`PIKACHU_EVENT_FGM_SWING_PULSE`) represents Smash route 219
(`nSYAudioFGMMarioUnkSwing2`), not ElectricLoop, and is listed as unresolved in
the manifest until that distinct cue is added. Runtime integration must not
substitute the ElectricLoop WAV for event 11.
