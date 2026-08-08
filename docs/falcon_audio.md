# Captain Falcon audio

Captain Falcon's voice and move audio is loaded only from the owner's ignored
`assets_ssb64/audio/` quarantine. No decoded sample, WAV, AIFF, ROM slice, or
other SSB64-derived byte is linked into the executable or committed. A checkout
without those files prints one fallback message and continues with NES audio.

## Source mapping

The pinned `SmashBrosDecomp` US build exposes the original route as
`gmFGMVoiceID -> fgm.ucd -> fgm.tbl -> ALBank -> decoded AIFF`.

| Runtime cue | Source id / route | Local input |
|---|---|---|
| jump effort | voice 353, articulation 201, trigger 83 | `B1_sounds2/wave_083.aiff` |
| "Falcon" | voice 348, articulation 208, trigger 90 | `B1_sounds2/wave_090.aiff` |
| "Punch" | voice 347, articulation 209, trigger 91 | `B1_sounds2/wave_091.aiff` |
| Falcon Kick call | voice 346, articulation 210, trigger 92 | `B1_sounds2/wave_092.aiff` |
| Punch impact | FGM 184 -> 187, articulation 146, instrument 11 | `B1_sounds1/wave_019.aiff` |
| Kick opening swing | FGM 41, articulation 173, instrument 18 | `B1_sounds1/wave_053.aiff` |
| Kick energy start | FGM 183 -> 186, articulation 147, instrument 11 | `B1_sounds1/wave_019.aiff` |

The four voice articulations and instrument 11 specify approximately -1200
cents, so the local conversion preserves their half-speed playback before
resampling to 44100 Hz. The LightSwingL path combines +550 and -400 cents, so
its representative waveform is rendered at +150 cents.

The original FGM interpreter also applies evolving envelopes, repeated notes,
and (for the Punch impact) a forked explosion voice. Reimplementing that whole
N64 synthesizer is outside this host adapter. The local previews preserve the
identified source waveform and pitch; Punch/Kick FGM envelopes and the selected
middle-range swing waveform are documented audio adaptations. Voice samples
and their pitch are direct.

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
- `RECOMP_AUDIO_DEBUG` capture: `t1_apu.wav` and `t2_bridge_in.wav` are both
  mono 44100 Hz/12 seconds but have different SHA-256 hashes, demonstrating
  overlays are present at the shared bridge input while native APU audio is
  also active.
- `tests/falcon_tier4_mod_off.script`: holding B with the package disabled
  produces no Smash64 controller, asset, audio-load, or cue log.
- Temporarily withholding the ignored audio directory produces exactly one
  `local Falcon clips unavailable; continuing silently` message and a clean
  smoke-test exit.
