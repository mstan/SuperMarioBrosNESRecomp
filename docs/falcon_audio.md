# Captain Falcon audio

Captain Falcon's voice and move audio is loaded only from the owner's ignored
`assets_ssb64/audio/` quarantine. No decoded sample, WAV, AIFF, ROM slice, or
other SSB64-derived byte is linked into the executable or committed. A checkout
without those files prints one fallback message and continues with NES audio.

## Source mapping

The primary implementation reference is JRickey's
[BattleShip](https://github.com/JRickey/BattleShip) PC port/decomp (local
checkout `4fc1128`). Its US data exposes the original route as
`gmFGMVoiceID -> fgm.ucd -> fgm.tbl -> ALBank -> decoded AIFF`. The earlier
`SmashBrosDecomp` checkout remains the local decoded-preview source only.

| Runtime cue | Source id / route | Local input |
|---|---|---|
| jump effort | voice 353, articulation 201, trigger 83 | `B1_sounds2/wave_083.aiff` |
| "Falcon" | voice 348, articulation 208, trigger 90 | `B1_sounds2/wave_090.aiff` |
| "Punch" | voice 347, articulation 209, trigger 91 | `B1_sounds2/wave_091.aiff` |
| Falcon Kick call | voice 346, articulation 210, trigger 92 | `B1_sounds2/wave_092.aiff` |
| Punch impact | FGM 184 -> 187 + fork 0; articulations 146/7; triggers 11/4 | `B1_sounds2/wave_011.aiff` + `wave_004.aiff` |
| Kick opening swing | FGM 41, articulation 173, trigger 18 | `B1_sounds2/wave_018.aiff` |
| Kick energy start | FGM 183 -> 186, articulation 147, trigger 11 | `B1_sounds2/wave_011.aiff` |

The four voice articulations and the Falcon energy articulations specify
approximately -1200 cents. BattleShip's `audio.c` configures a 32000 Hz
synthesizer, and the FGM path in `n_env.c` sends
`alCents2Ratio(unk2C + unk30)` directly to
`n_alSynStartVoiceParams`; an `ALWaveTable` carries no independent source-rate
field. The original byte stream is therefore consumed at an effective 16000
samples/second. The decomp preview AIFF's 44100 Hz header is export metadata,
not the game's playback clock. Local conversion assigns 16000 Hz before
resampling to the runner's 44100 Hz. The LightSwingL path combines +550 and
-400 cents, so its representative waveform is rendered at +150 cents against
the 32000 Hz synthesizer.

The FGM trigger operand indexes the 322-entry `B1_sounds2` sound array loaded
as BattleShip's first audio bank. It is not a `B1_sounds1` instrument index.
The previous extractor confused those namespaces and played
`B1_sounds1/wave_019` for both Falcon energy cues; that looped tonal sample was
the reported guitar-like tail.

The local extractor now renders the authored subset of the FGM interpreter:
the 184 -> 187 Punch pitch sequence and its forked voice 0, the 183 -> 186 Kick
pitch/envelope sequence, and the FGM 41 LightSwingL pitch. It advances at
BattleShip's `184 / 32000`-second FGM tick and applies the source stop/release
ramp. The runtime still receives ordinary bounded PCM one-shots; no FGM engine
or ROM data is linked into the executable. Voice samples and their pitch remain
direct.

The ignored reproducibility helper is:

```text
py -3.12 assets_ssb64/tools_local/extract_falcon_audio.py
```

It calls FFmpeg, writes seven mono signed-16 44100 Hz WAVs plus a local
manifest, and never writes outside `assets_ssb64/audio/`.

## Runtime cues

The quarantined state machine emits allocation-free, one-tick cue ids through
`ForeignMoveResult.audio`. They match the source motion script:

- jump effort on the supported jump transition (the source uses this clip for
  JumpAerial; SMB1 has no double jump, so its one jump is the host adaptation);
- "Falcon" on Falcon Punch entry;
- "Punch" plus impact FGM on Punch frame 42;
- Kick voice plus LightSwingL on Falcon Kick entry;
- Kick energy-start FGM on Kick frame 12.

The SMB1 adapter resolves cue ids to optional clips. `mod_audio` copies each
registered clip, permits overlapping voice and FGM one-shots, saturating-adds
them into the APU's mono producer frame, and then lets the existing launcher
volume and clock-domain bridge process the combined stream. It does not open a
second SDL device.

`NESRECOMP_SSB64_ASSETS=<root>` overrides the asset root. Set
`NESRECOMP_SMASH64_AUDIO_TRACE=1` to log each successfully queued cue for
scripted evidence; ordinary play does not log per cue.

Disabling the mod unregisters its clips. A save-state load stops all host-side
overlay cursors before restoring mod state: an already-consumed call cannot
continue or replay stale audio, while a future cue genuinely reached again on
the restored timeline fires normally.

## Evidence

- `tests/falcon_harness/audio.script`: exact cue masks and one-frame timing;
  `mod_audio_test.c` covers registration, overlap saturation, stop, and
  unregister; the combined deterministic suite passes 12/12.
- `tests/falcon_m8_audio.script`: live jump, Punch, Kick, and Punch-windup
  save/load. With trace enabled, all seven mappings queue. The pre-save
  "Falcon" call occurs once; frame-42 "Punch" and impact each occur once on
  both continuations after the rewind.
- Final `RECOMP_AUDIO_DEBUG` capture
  `C:\temp\falcon_audio_battleship_16000_1556`: all seven cues queue at their
  expected frames. Reconstructing the first 500 bridge frames from `t1_apu`
  plus the registered clips, integer gains, overlap, and saturation matches
  `t2_bridge_in` exactly (367500/367500 samples). Corrected voice durations are
  0.218005 s (jump), 0.564014 s ("Falcon"), 0.938005 s ("Punch"), and
  0.829002 s (Kick).
- FGM route correction capture
  `C:\temp\falcon_audio_fgm_fix_20260809`: all seven corrected clips load and
  queue at the authored source frames. Reconstructing the complete 720-frame
  `t2_bridge_in` stream from `t1_apu`, cue chronology, regenerated clips,
  integer gains, save-load stop, overlap, and final saturation is sample-exact
  (529200/529200 samples). Correct FGM durations are 1.127778 s (Punch impact
  including fork 0), 0.810748 s (Kick energy start), and 0.187052 s
  (LightSwingL). `C:\temp\falcon_{punch,kick}_audio_spectrum_compare.png`
  contrasts the removed narrow tonal `B1_sounds1/wave_019` tail with the
  broadband authored `B1_sounds2` FGM routes.
- `tests/falcon_tier4_mod_off.script`: holding B with the package disabled
  produces no Smash64 controller, asset, audio-load, or cue log.
- Temporarily withholding the ignored audio directory produces exactly one
  `local Falcon clips unavailable; continuing silently` message and a clean
  smoke-test exit.
