#!/usr/bin/env python3
"""Render the minimal Pikachu runtime cue set from an owner Smash 64 ROM.

Direct character voices use the exact B1_sounds2 VADPCM wave, the selected
route's initial UCD/TBL pitch, and the shared deterministic windowed-sinc
resampler. FGM cues validate their canonical UCD
route, forks, articulation, and triggered source wave, then use a deliberately
focused offline pitch/gain approximation. This is not a general FGM engine.

ElectricLoop is emitted as one bounded ALADPCM loop period with explicit WAV
frame metadata; this tool never expands an infinite loop. All results live in
an external cache/staging directory and neither ROM bytes nor an input path are
written to the output.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import shutil
import tempfile
import wave
from array import array
from pathlib import Path

import owner_audio


FORMAT = "smb1-smash64-pikachu-runtime-audio-cache"
RECIPE_VERSION = 3

VOICE_CUES = {
    "special_n_voice": ("pikachu_special_n.wav", 540, 393, 268),
    "special_lw_voice": ("pikachu_special_lw.wav", 541, 395, 270),
    "special_hi_voice": ("pikachu_special_hi.wav", 547, 401, 276),
}
VOICE_ROUTE_PITCH_CENTS = {
    "special_n_voice": -440,
    "special_lw_voice": -560,
    "special_hi_voice": -1200,
}

# event: (filename, root route, articulation, source wave, pitch cents,
#         source-length stop tick, top volume, articulation volume)
# Curves are intentionally small focused approximations of the validated FGM
# programs. Stop ticks track one source-wave traversal at 32 kHz.
FGM_CUES = {
    "light_swing_l": ("pikachu_light_swing_l.wav", 41, 173, 18,
                      ((0, 80),), 35, 225, ((0, 118),)),
    "light_swing_m": ("pikachu_light_swing_m.wav", 42, 174, 71,
                      ((0, -120),), 28, 220, ((0, 118),)),
    "light_swing_s": ("pikachu_light_swing_s.wav", 43, 174, 71,
                      ((0, 180),), 28, 210, ((0, 112),)),
    "electric_1": ("pikachu_electric_1.wav", 225, 175, 25,
                   ((0, 0), (24, 140), (48, -80)), 70, 225,
                   ((0, 122), (48, 108))),
    "electric_2": ("pikachu_electric_2.wav", 226, 20, 12,
                   ((0, -260),), 42, 205, ((0, 118), (28, 92))),
    "electric_3": ("pikachu_electric_3.wav", 227, 20, 12,
                   ((0, 0),), 42, 215, ((0, 121), (28, 96))),
    "electric_5": ("pikachu_electric_5.wav", 229, 20, 12,
                   ((0, 260),), 42, 220, ((0, 124), (28, 100))),
    "quick_attack_start": ("pikachu_quick_attack_start.wav", 231, 154, 40,
                           ((0, -160), (18, 120), (42, 260)), 74, 225,
                           ((0, 120), (52, 100))),
    "thunder": ("pikachu_thunder.wav", 232, 55, 7,
                ((0, -80), (64, 0), (192, -120)), 344, 235,
                ((0, 124), (240, 108), (320, 72))),
    # Exact common FGM routes used by the newly reachable aerial landing
    # statuses. The host keeps the same deliberately labeled finite FGM
    # renderer as the existing cue set; it never aliases these to another
    # character sound.
    "landing": ("pikachu_landing.wav", 79, 3, 1,
                ((0, 700),), 10, 255, ((0, 127),)),
    "dead_slam": ("pikachu_dead_slam.wav", 294, 187, 28,
                  ((0, -1100),), 15, 255, ((0, 127),)),
}
# These two landing routes have a single source articulation. Pin its initial
# TBL pitch explicitly so a later curve edit cannot turn their source-derived
# baseline into an unlabeled proxy; finite decay remains the renderer's
# documented focused-FGM limitation.
FGM_INITIAL_ARTICULATION_CENTS = {"landing": 700, "dead_slam": -1100}

EXPECTED_FORKS = {
    226: (649,), 227: (649,), 229: (649,), 232: (674, 675), 294: (287,),
}
FORK_ARTICULATIONS = {287: 187, 649: 20, 674: 55, 675: 55}
LOOP_EVENT = "electric_loop"
LOOP_FILE = "pikachu_electric_loop.wav"
LOOP_ROUTE = 230
LOOP_ARTICULATION = 21
LOOP_WAVE = 12

# Exact numeric ABI from ssb_ported/pikachu_locomotion.h. A list allows a
# future controller event to intentionally fan out to multiple clips without
# overloading a Smash FGM route ID as a host event ID.
CONTROLLER_BINDINGS = {
    "special_n_voice": ((0, "PIKACHU_EVENT_VOICE_SPECIAL_N"),),
    "special_hi_voice": ((1, "PIKACHU_EVENT_VOICE_SPECIAL_HI"),),
    "special_lw_voice": ((2, "PIKACHU_EVENT_VOICE_SPECIAL_LW"),),
    "light_swing_s": ((3, "PIKACHU_EVENT_FGM_LIGHT_S"),),
    "light_swing_m": ((4, "PIKACHU_EVENT_FGM_LIGHT_M"),),
    "light_swing_l": ((5, "PIKACHU_EVENT_FGM_LIGHT_L"),),
    "electric_1": ((6, "PIKACHU_EVENT_FGM_ELECTRIC_1"),),
    "electric_2": ((7, "PIKACHU_EVENT_FGM_ELECTRIC_2"),),
    "electric_3": ((8, "PIKACHU_EVENT_FGM_ELECTRIC_3"),),
    "electric_5": ((9, "PIKACHU_EVENT_FGM_ELECTRIC_5"),),
    # Quick Attack emits this once when its 20-frame charge begins.
    "quick_attack_start": ((10, "PIKACHU_EVENT_FGM_QUICK_ATTACK_START"),),
    # PikachuMainMotion emits FGM232 on the owner Loop status's local f0;
    # the projectile is deliberately spawned earlier by Start f24.
    "thunder": ((24, "PIKACHU_EVENT_FGM_THUNDER"),),
    "landing": ((18, "PIKACHU_EVENT_FGM_LANDING"),),
    "dead_slam": ((19, "PIKACHU_EVENT_FGM_DEAD_SLAM"),),
    # BattleShip starts ElectricLoop when the Thunder Jolt weapon is created.
    "electric_loop": ((15, "PIKACHU_EVENT_PROJECTILE_JOLT_SPAWN"),),
}
UNRESOLVED_CONTROLLER_EVENTS = ({
    "id": 11, "name": "PIKACHU_EVENT_FGM_SWING_PULSE",
    "smash_route": 219, "smash_name": "nSYAudioFGMMarioUnkSwing2",
    "reason": "The requested ElectricLoop cue is route 230 and is not a source-faithful substitute.",
},)

APPROVED_CUES = {
    "special_hi_voice": (8732, "8f30c6caac48f441f70660aa4572d91153a05f0805df30d4ed56d9863cf5c411"),
    "special_lw_voice": (27760, "62ea8969d63c278c3d04edc1e57f53b346f87099020505a8c2b988bce0a75984"),
    "special_n_voice": (37416, "78ad0127c94b254807ad2c8b1cb73458618f3242e7bed25a598dd40777158278"),
    "electric_1": (17453, "7c64e2ae648edd2d13b75db99be6699f7369abf73984ee93ada6d73a982431cf"),
    "electric_2": (10904, "6894a05f3ddfd4d1ae68c2162e972f84a5a30acc948d4b9cf007db7b696b27f8"),
    "electric_3": (10583, "adc5ed81808b302fea581ca80c2086ccd40d01840a0380b53655b1cf984d6f7a"),
    "electric_5": (9107, "d399ed8df1e8f3560ddd0dc8c9428af4f7e155c3bfe95d3710749ae5fe21b456"),
    "light_swing_l": (8589, "c7ebe85fee1740ea134f7dbe026f6bd400f2dbc27535efbef67ff0edeb3ad6a7"),
    "light_swing_m": (7354, "fff5d375a9a7197ff0156aabf40a1d996c044d2e4912fa5347d9677b3583713a"),
    "light_swing_s": (6438, "8192ef6c410e72f48ddecbcc95e0bc75fad49664ae85c9f7df130042464aa59f"),
    "quick_attack_start": (17603, "639dab10e9a22e09a86051e22a295eb2cb4a05cb2b1fb6ee87e6929d460e8d5e"),
    "thunder": (87484, "015518530cebf78fbf508158fb8e581d15fc62c958ce1e61e153242791bd5718"),
    "landing": (2790, "b76078eaff982a8bea4c07d40dbf02ff53ea41b4bbd3904f8b8d0e7dcb9f5a84"),
    "dead_slam": (4058, "a5ff0a3ac4819afe2de2d0ae13e23ce764de06429a917ed949dc0f859258dc0a"),
    "electric_loop": (10425, "aedef3eda98f88e756a08848b37953d9b94e5fe94cfc78b31410dcf28df267a3"),
}


def _external_output(path: Path) -> None:
    owner_audio._external_output(path)


def _write_wav(path: Path, samples: list[int]) -> None:
    pcm = array("h", (max(-32768, min(32767, sample)) for sample in samples))
    with wave.open(str(path), "wb") as stream:
        stream.setnchannels(1)
        stream.setsampwidth(2)
        stream.setframerate(owner_audio.OUTPUT_RATE)
        stream.writeframes(pcm.tobytes())


def _binding(event: str) -> dict:
    bindings = CONTROLLER_BINDINGS[event]
    return {"controller_event_ids": [item[0] for item in bindings],
            "controller_event_names": [item[1] for item in bindings]}


def _route_tables(rom: bytes) -> tuple[dict[int, bytes], dict[int, bytes]]:
    roots = {route for _filename, route, _art, _wave in VOICE_CUES.values()}
    roots.update(spec[1] for spec in FGM_CUES.values())
    roots.add(LOOP_ROUTE)
    programs = roots | set(FORK_ARTICULATIONS)
    articulations = {art for _filename, _route, art, _wave in VOICE_CUES.values()}
    articulations.update(spec[2] for spec in FGM_CUES.values())
    articulations.add(LOOP_ARTICULATION)
    ucd = owner_audio._parse_fgm_blob(
        rom[slice(*owner_audio.FGM_UCD)], 695, "fgm.ucd", tuple(sorted(programs)))
    tbl = owner_audio._parse_fgm_blob(
        rom[slice(*owner_audio.FGM_TBL)], 464, "fgm.tbl",
        tuple(sorted(articulations)))
    return ucd, tbl


def _validate_routes(rom: bytes) -> dict:
    ucd, tbl = _route_tables(rom)
    route_specs = {
        route: (articulation, wave)
        for _filename, route, articulation, wave in VOICE_CUES.values()
    }
    route_specs.update({spec[1]: (spec[2], spec[3]) for spec in FGM_CUES.values()})
    route_specs[LOOP_ROUTE] = (LOOP_ARTICULATION, LOOP_WAVE)
    routes = {}
    voice_by_route = {spec[1]: event for event, spec in VOICE_CUES.items()}
    for route, (articulation, wave_id) in sorted(route_specs.items()):
        commands = owner_audio._ucd_commands(ucd[route])
        observed_forks = tuple(value for kind, value in commands if kind == "fork")
        if observed_forks != EXPECTED_FORKS.get(route, ()):
            raise ValueError(f"FGM route {route} changed fork closure")
        # FGM294's root program only forks to 287; preserve that source
        # topology rather than pretending the terminal articulation lives in
        # the root like the simpler landing route does.
        articulation_route = route
        if ("articulation", articulation) not in commands:
            candidates = [fork for fork in observed_forks
                          if ("articulation", articulation) in
                          owner_audio._ucd_commands(ucd[fork])]
            if len(candidates) != 1:
                raise ValueError(f"FGM route {route} changed articulation")
            articulation_route = candidates[0]
        if owner_audio._tbl_trigger(tbl[articulation]) != wave_id:
            raise ValueError(f"FGM articulation {articulation} changed wave")
        route_info = {"articulation": articulation, "wave_id": wave_id,
                      "commands": commands,
                      "ucd_sha256": hashlib.sha256(ucd[route]).hexdigest(),
                      "tbl_sha256": hashlib.sha256(tbl[articulation]).hexdigest()}
        if articulation_route != route:
            route_info["articulation_route"] = articulation_route
        if route in voice_by_route:
            event = voice_by_route[route]
            note_cents = owner_audio._ucd_initial_note_cents(ucd[route])
            articulation_cents = owner_audio._tbl_initial_pitch_cents(
                tbl[articulation])
            total_cents = note_cents + articulation_cents
            if total_cents != VOICE_ROUTE_PITCH_CENTS[event]:
                raise ValueError(f"Pikachu voice route {route} changed initial pitch")
            route_info.update({
                "initial_note_cents": note_cents,
                "initial_articulation_cents": articulation_cents,
                "initial_total_cents": total_cents,
                "effective_source_rate": owner_audio.pitched_source_rate(total_cents),
            })
        fgm_event = next((event for event, spec in FGM_CUES.items()
                          if spec[1] == route), None)
        if fgm_event in FGM_INITIAL_ARTICULATION_CENTS:
            observed_cents = owner_audio._tbl_initial_pitch_cents(tbl[articulation])
            if observed_cents != FGM_INITIAL_ARTICULATION_CENTS[fgm_event]:
                raise ValueError(f"Pikachu FGM route {route} changed initial pitch")
            route_info["initial_articulation_cents"] = observed_cents
        routes[str(route)] = route_info
    for fork, articulation in FORK_ARTICULATIONS.items():
        commands = owner_audio._ucd_commands(ucd[fork])
        if ("articulation", articulation) not in commands:
            raise ValueError(f"FGM fork {fork} changed articulation")
    return routes


def _loop_clip(rom: bytes, samples: list[int]) -> tuple[list[int], dict]:
    records = owner_audio._bank_wave_records(rom[slice(*owner_audio.B1_SOUNDS2_CTL)])
    if len(records) != 322:
        raise ValueError("unexpected B1_sounds2 wave count")
    record = records[LOOP_WAVE]
    start, end, count = (int(record["loop_start"]), int(record["loop_end"]),
                         int(record["loop_count"]))
    if count != 0xFFFFFFFF or not 0 <= start < end <= len(samples):
        raise ValueError("ElectricLoop ALADPCM loop metadata changed")
    body = samples[start:end]
    rendered = owner_audio.resample_windowed_sinc(
        body, owner_audio.SYNTH_RATE, owner_audio.OUTPUT_RATE)
    return rendered, {
        "mode": "forward", "start_frame": 0, "end_frame": len(rendered),
        "source_start_sample": start, "source_end_sample": end,
        "source_loop_count": count,
        "note": "One bounded source loop period; runtime repeats [start_frame,end_frame).",
    }


def expected_loop_metadata() -> dict:
    return {
        "mode": "forward", "start_frame": 0,
        "end_frame": APPROVED_CUES[LOOP_EVENT][0],
        "source_start_sample": 100, "source_end_sample": 7664,
        "source_loop_count": 0xFFFFFFFF,
        "note": "One bounded source loop period; runtime repeats [start_frame,end_frame).",
    }


def verify(output_dir: Path, expected_rom_sha1: str | None = None) -> dict:
    manifest = json.loads((output_dir / "manifest.json").read_text(encoding="utf-8"))
    if manifest.get("format") != FORMAT or manifest.get("recipe_version") != RECIPE_VERSION:
        raise ValueError("unsupported Pikachu runtime audio manifest")
    if manifest.get("normalized_rom_sha1") != owner_audio.CANONICAL_SHA1:
        raise ValueError("Pikachu audio cache is not from the supported ROM")
    if expected_rom_sha1 and manifest.get("normalized_rom_sha1") != expected_rom_sha1:
        raise ValueError("Pikachu audio cache belongs to a different ROM")
    clips = manifest.get("clips")
    expected_events = set(VOICE_CUES) | set(FGM_CUES) | {LOOP_EVENT}
    if (not isinstance(clips, list) or len(clips) != len(expected_events) or
            {clip.get("event") for clip in clips} != expected_events):
        raise ValueError("Pikachu runtime cue inventory is incomplete")
    expected_files = {"manifest.json"}
    for clip in clips:
        event = clip.get("event")
        if event in VOICE_CUES:
            filename, route, articulation, wave_id = VOICE_CUES[event]
            kind = "direct_voice"
        elif event in FGM_CUES:
            filename, route, articulation, wave_id = FGM_CUES[event][:4]
            kind = "focused_fgm_approximation"
        else:
            filename, route, articulation, wave_id = (
                LOOP_FILE, LOOP_ROUTE, LOOP_ARTICULATION, LOOP_WAVE)
            kind = "bounded_aladpcm_loop"
        expected_recipe = {
            "file": filename, "kind": kind, "route": route,
            "articulation": articulation, "wave_id": wave_id,
            "rate": owner_audio.OUTPUT_RATE,
        }
        if event in VOICE_CUES:
            cents = VOICE_ROUTE_PITCH_CENTS[event]
            expected_recipe.update({
                "nominal_source_rate": owner_audio.SYNTH_RATE,
                "initial_route_pitch_cents": cents,
                "effective_source_rate": owner_audio.pitched_source_rate(cents),
            })
        if any(clip.get(key) != value for key, value in expected_recipe.items()):
            raise ValueError(f"Pikachu cue recipe mismatch: {event}")
        filename = clip.get("file")
        if not isinstance(filename, str) or Path(filename).name != filename or not filename.endswith(".wav"):
            raise ValueError("invalid Pikachu runtime cue filename")
        path = output_dir / filename
        if not path.is_file() or path.stat().st_size == owner_audio.CANONICAL_SIZE:
            raise ValueError(f"missing or forbidden Pikachu cue {filename}")
        payload = path.read_bytes()
        if hashlib.sha256(payload).hexdigest() != clip.get("wav_sha256"):
            raise ValueError(f"Pikachu cue hash mismatch: {filename}")
        if hashlib.sha256(payload[44:]).hexdigest() != clip.get("pcm_sha256"):
            raise ValueError(f"Pikachu PCM hash mismatch: {filename}")
        if (clip.get("frames"), clip.get("pcm_sha256")) != APPROVED_CUES[event]:
            raise ValueError(f"Pikachu cue is not the approved render: {event}")
        with wave.open(str(path), "rb") as stream:
            if (stream.getnchannels(), stream.getsampwidth(), stream.getframerate(),
                    stream.getnframes()) != (1, 2, owner_audio.OUTPUT_RATE, clip.get("frames")):
                raise ValueError(f"Pikachu WAV geometry mismatch: {filename}")
        expected_binding = _binding(clip["event"])
        if any(clip.get(key) != value for key, value in expected_binding.items()):
            raise ValueError(f"Pikachu controller mapping mismatch: {clip['event']}")
        expected_files.add(filename)
    loop = next(clip for clip in clips if clip["event"] == LOOP_EVENT)
    if loop.get("loop") != expected_loop_metadata():
        raise ValueError("Pikachu ElectricLoop metadata mismatch")
    actual_files = {path.name for path in output_dir.iterdir() if path.is_file()}
    if actual_files != expected_files:
        raise ValueError("unexpected file in Pikachu runtime audio cache")
    if manifest.get("unresolved_controller_events") != list(UNRESOLVED_CONTROLLER_EVENTS):
        raise ValueError("Pikachu unresolved controller event inventory changed")
    return manifest


def render(rom_path: Path, output_dir: Path) -> Path:
    _external_output(output_dir)
    rom = owner_audio.normalize_rom(rom_path.read_bytes())
    rom_sha1 = hashlib.sha1(rom).hexdigest()
    if rom_sha1 != owner_audio.CANONICAL_SHA1:
        raise ValueError("ROM is not the supported Smash Bros. US v1.0 image")
    routes = _validate_routes(rom)
    wave_ids = {wave for _filename, _route, _art, wave in VOICE_CUES.values()}
    wave_ids.update(spec[3] for spec in FGM_CUES.values())
    wave_ids.add(LOOP_WAVE)
    waves = owner_audio.decode_waves(rom, tuple(sorted(wave_ids)))

    output_dir.parent.mkdir(parents=True, exist_ok=True)
    staging = Path(tempfile.mkdtemp(prefix=f".{output_dir.name}.",
                                    dir=output_dir.parent))
    try:
        clips = []
        for event, (filename, route, articulation, wave_id) in sorted(VOICE_CUES.items()):
            cents = VOICE_ROUTE_PITCH_CENTS[event]
            source_rate = owner_audio.pitched_source_rate(cents)
            rendered = owner_audio.resample_windowed_sinc(
                waves[wave_id], source_rate, owner_audio.OUTPUT_RATE)
            _write_wav(staging / filename, rendered)
            clips.append({"event": event, "file": filename, "kind": "direct_voice",
                          "route": route, "articulation": articulation,
                          "wave_id": wave_id, "frames": len(rendered),
                          "nominal_source_rate": owner_audio.SYNTH_RATE,
                          "initial_route_pitch_cents": cents,
                          "effective_source_rate": source_rate,
                          **_binding(event)})
        for event, spec in sorted(FGM_CUES.items()):
            filename, route, articulation, wave_id, pitch, stop, top, volume = spec
            rendered = owner_audio.synth_voice(waves[wave_id], list(pitch), stop,
                                               top, list(volume))
            _write_wav(staging / filename, rendered)
            clips.append({"event": event, "file": filename,
                          "kind": "focused_fgm_approximation", "route": route,
                          "articulation": articulation, "wave_id": wave_id,
                          "frames": len(rendered), **_binding(event)})
        loop, loop_metadata = _loop_clip(rom, waves[LOOP_WAVE])
        _write_wav(staging / LOOP_FILE, loop)
        clips.append({"event": LOOP_EVENT, "file": LOOP_FILE,
                      "kind": "bounded_aladpcm_loop", "route": LOOP_ROUTE,
                      "articulation": LOOP_ARTICULATION, "wave_id": LOOP_WAVE,
                      "frames": len(loop), "loop": loop_metadata,
                      **_binding(LOOP_EVENT)})

        for clip in clips:
            path = staging / clip["file"]
            clip["wav_sha256"] = hashlib.sha256(path.read_bytes()).hexdigest()
            clip["pcm_sha256"] = hashlib.sha256(path.read_bytes()[44:]).hexdigest()
            clip["rate"] = owner_audio.OUTPUT_RATE
        manifest = {
            "format": FORMAT, "recipe_version": RECIPE_VERSION,
            "normalized_rom_sha1": rom_sha1, "clips": clips, "routes": routes,
            "unresolved_controller_events": list(UNRESOLVED_CONTROLLER_EVENTS),
            "approximation": (
                "Direct voices use decoded source waves and their initial route pitch. "
                "Later UCD note changes are not synthesized. Finite FGM cues "
                "validate canonical routing but use focused offline pitch/gain curves; "
                "they are not full UCD/TBL/RSP emulation."),
        }
        (staging / "manifest.json").write_text(
            json.dumps(manifest, indent=1, sort_keys=True) + "\n", encoding="utf-8")
        verify(staging, rom_sha1)
        if output_dir.exists():
            raise FileExistsError(f"refusing to overwrite existing audio cache: {output_dir}")
        os.replace(staging, output_dir)
        return output_dir
    except Exception:
        shutil.rmtree(staging, ignore_errors=True)
        raise


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", required=True, type=Path)
    parser.add_argument("--out", required=True, type=Path)
    args = parser.parse_args(argv)
    print(render(args.rom, args.out))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
