#!/usr/bin/env python3
"""Render the eleven Captain Falcon PCM cues directly from an owner ROM.

This is intentionally a small, offline renderer rather than a general N64
audio engine.  It reads the US 1.0 B1_sounds2 ALBank and FGM blobs directly
from a normalized owner ROM, decodes only the eight wave tables used by the
existing Falcon move routes, and writes ordinary 44.1 kHz mono WAVs to an
*external* cache or staging directory.  It has no decomp checkout, FFmpeg, or
third-party Python dependency and never persists a ROM image.

The route constants mirror the game's known FGM programs.  The offline mixer
implements exactly the note/pitch/envelope subset used by Punch, Kick, and
Falcon Dive.  It is deliberately not a claim to emulate every FGM opcode or
the RSP synthesizer.
"""

from __future__ import annotations

import argparse
import array
import hashlib
import json
import math
import os
import shutil
import struct
import sys
import tempfile
import wave
from pathlib import Path


CANONICAL_SHA1 = "e2929e10fccc0aa84e5776227e798abc07cedabf"
CANONICAL_SIZE = 16 * 1024 * 1024
IS_FROZEN = bool(getattr(sys, "frozen", False) or getattr(sys, "_MEIPASS", None))
SOURCE_ROOT = None if IS_FROZEN else Path(__file__).resolve().parents[2]
OUTPUT_RATE = 44100
SYNTH_RATE = 32000
FGM_TICK_SECONDS = 184.0 / SYNTH_RATE

# Source ranges are the US 1.0 ROM's B1_sounds2/FGM DMA ranges.  They are
# read in-memory only; output contains only the 11 PCM cues consumed by SMB1.
B1_SOUNDS2_CTL = (0xC6B650, 0xC7B1F0)
B1_SOUNDS2_TBL = (0xC7B1F0, 0xF573D0)
FGM_TBL = (0xF57BF0, 0xF5A9C0)
FGM_UCD = (0xF5A9C0, 0xF5F4E0)

# B1_sounds2 soundArray indices (not B1_sounds1 instrument numbers).  Their
# sample data is VADPCM encoded in the paired table blob.
REQUIRED_WAVES = (4, 11, 18, 83, 90, 91, 92, 95)
VOICE_WAVES = {
    "falcon_jump_effort.wav": 83,
    "falcon_punch_falcon.wav": 90,
    "falcon_punch_punch.wav": 91,
    "falcon_kick.wav": 92,
}


def normalize_rom(source: bytes) -> bytes:
    """Return z64-order ROM data, retaining it only in process memory."""
    if len(source) != CANONICAL_SIZE:
        raise ValueError(f"expected {CANONICAL_SIZE}-byte ROM, got {len(source)}")
    magic = source[:4]
    if magic == b"\x80\x37\x12\x40":
        return source
    if magic == b"\x37\x80\x40\x12":
        swapped = bytearray(source)
        swapped[0::2], swapped[1::2] = source[1::2], source[0::2]
        return bytes(swapped)
    if magic == b"\x40\x12\x37\x80":
        swapped = bytearray(len(source))
        swapped[0::4], swapped[1::4] = source[3::4], source[2::4]
        swapped[2::4], swapped[3::4] = source[1::4], source[0::4]
        return bytes(swapped)
    raise ValueError(f"unrecognized N64 byte order ({magic.hex()})")


def _external_output(path: Path) -> None:
    resolved = path.resolve()
    if SOURCE_ROOT is not None and (resolved == SOURCE_ROOT or SOURCE_ROOT in resolved.parents):
        raise ValueError("audio output must be outside the source tree")


def _u32(data: bytes, offset: int) -> int:
    return struct.unpack_from(">I", data, offset)[0]


def _s32(data: bytes, offset: int) -> int:
    return struct.unpack_from(">i", data, offset)[0]


def _checked_offset(data: bytes, offset: int, size: int, what: str) -> None:
    if offset <= 0 or offset + size > len(data):
        raise ValueError(f"invalid {what} offset 0x{offset:X}")


def _bank_wave_records(ctl: bytes) -> list[dict[str, int | tuple[int, ...]]]:
    """Walk ALBank -> Instrument -> Sound -> ALWaveTable, by file offsets."""
    if len(ctl) < 8:
        raise ValueError("B1_sounds2 ctl is truncated")
    bank_count = struct.unpack_from(">h", ctl, 2)[0]
    if bank_count <= 0 or 4 + bank_count * 4 > len(ctl):
        raise ValueError("B1_sounds2 has an invalid ALBankFile header")

    banks = [_u32(ctl, 4 + index * 4) for index in range(bank_count)]
    visited_instruments: set[int] = set()
    visited_sounds: set[int] = set()
    waves: dict[int, dict[str, int | tuple[int, ...]]] = {}

    def visit_wave(offset: int) -> None:
        if offset in waves:
            return
        _checked_offset(ctl, offset, 20, "ALWaveTable")
        base, length, wave_type, _flags = struct.unpack_from(">IiBB", ctl, offset)
        if wave_type != 0:
            raise ValueError(f"required B1_sounds2 wave at 0x{offset:X} is not VADPCM")
        loop, book = struct.unpack_from(">II", ctl, offset + 12)
        _checked_offset(ctl, book, 8, "ALADPCMBook")
        order, predictors = struct.unpack_from(">ii", ctl, book)
        if order <= 0 or predictors <= 0 or order > 8 or predictors > 64:
            raise ValueError("invalid B1_sounds2 ADPCM book geometry")
        coefficients = order * predictors * 8
        _checked_offset(ctl, book + 8, coefficients * 2, "ALADPCMBook coefficients")
        codebook = struct.unpack_from(f">{coefficients}h", ctl, book + 8)
        if base < 0 or length <= 0:
            raise ValueError("invalid B1_sounds2 wave table span")
        loop_start = loop_end = loop_count = 0
        if loop:
            _checked_offset(ctl, loop, 12, "ALADPCMloop")
            loop_start, loop_end, loop_count = struct.unpack_from(">III", ctl, loop)
        waves[offset] = {
            "base": base, "length": length, "order": order,
            "predictors": predictors, "codebook": codebook,
            "loop_start": loop_start, "loop_end": loop_end,
            "loop_count": loop_count,
        }

    def visit_sound(offset: int) -> None:
        if offset == 0 or offset in visited_sounds:
            return
        visited_sounds.add(offset)
        _checked_offset(ctl, offset, 16, "ALSound")
        visit_wave(_u32(ctl, offset + 8))

    def visit_instrument(offset: int) -> None:
        if offset == 0 or offset in visited_instruments:
            return
        visited_instruments.add(offset)
        _checked_offset(ctl, offset, 16, "ALInstrument")
        sound_count = struct.unpack_from(">h", ctl, offset + 14)[0]
        if sound_count < 0 or offset + 16 + sound_count * 4 > len(ctl):
            raise ValueError("invalid B1_sounds2 ALInstrument sound array")
        for index in range(sound_count):
            visit_sound(_u32(ctl, offset + 16 + index * 4))

    for bank in banks:
        _checked_offset(ctl, bank, 12, "ALBank")
        instrument_count = struct.unpack_from(">h", ctl, bank)[0]
        if instrument_count < 0 or bank + 12 + instrument_count * 4 > len(ctl):
            raise ValueError("invalid B1_sounds2 ALBank instruments")
        visit_instrument(_u32(ctl, bank + 8))  # percussion
        for index in range(instrument_count):
            visit_instrument(_u32(ctl, bank + 12 + index * 4))

    # The established extractor calls these wave_000..NNN in ascending tbl
    # base order, not their structs' in-file order.
    return sorted(waves.values(), key=lambda item: int(item["base"]))


def _clip_s16(value: int) -> int:
    return max(-32768, min(32767, value))


def vadpcm_decode(data: bytes, codebook: tuple[int, ...], order: int,
                  predictors: int) -> list[int]:
    """Decode Nintendo VADPCM frames (the exact standard ALWaveTable path)."""
    coefficients = []
    for predictor in range(predictors):
        base = predictor * order * 8
        coefficients.append([
            list(codebook[base + row * 8: base + row * 8 + 8])
            for row in range(order)
        ])
    state = [0] * order
    output: list[int] = []
    for frame_start in range(0, len(data) - 8, 9):
        frame = data[frame_start:frame_start + 9]
        scale_index, predictor = frame[0] >> 4, frame[0] & 0x0F
        if predictor >= predictors:
            raise ValueError("VADPCM frame selects invalid predictor")
        scale = 1 << scale_index if scale_index < 12 else 0
        residuals: list[int] = []
        for value in frame[1:]:
            for nibble in (value >> 4, value & 0x0F):
                residuals.append((nibble - 16 if nibble >= 8 else nibble) * scale)
        book = coefficients[predictor]
        for half in range(2):
            decoded: list[int] = []
            values = residuals[half * 8: half * 8 + 8]
            for column, residual in enumerate(values):
                accumulator = sum(state[row] * book[row][column] for row in range(order))
                accumulator += sum(values[prior] * book[order - 1][column - 1 - prior]
                                   for prior in range(column))
                decoded.append(_clip_s16((accumulator >> 11) + residual))
            output.extend(decoded)
            state = decoded[8 - order:]
    return output


def decode_waves(rom: bytes, wave_ids: tuple[int, ...]) -> dict[int, list[int]]:
    """Decode an explicit, allowlisted set of B1_sounds2 wave indices."""
    ctl = rom[slice(*B1_SOUNDS2_CTL)]
    tbl = rom[slice(*B1_SOUNDS2_TBL)]
    records = _bank_wave_records(ctl)
    if len(records) != 322:
        raise ValueError(f"expected 322 B1_sounds2 waves, found {len(records)}")
    result: dict[int, list[int]] = {}
    for wave_id in wave_ids:
        if not 0 <= wave_id < len(records):
            raise ValueError(f"invalid B1_sounds2 wave index {wave_id}")
        record = records[wave_id]
        base, length = int(record["base"]), int(record["length"])
        if base + length > len(tbl):
            raise ValueError(f"B1_sounds2 wave {wave_id} exceeds table data")
        result[wave_id] = vadpcm_decode(
            tbl[base:base + length], record["codebook"], int(record["order"]),
            int(record["predictors"]),
        )
    return result


def decode_required_waves(rom: bytes) -> dict[int, list[int]]:
    """Preserve the original Falcon-only decoder entry point exactly."""
    return decode_waves(rom, REQUIRED_WAVES)


def _parse_fgm_blob(data: bytes, expected_count: int, label: str,
                    needed_entries: tuple[int, ...]) -> dict[int, bytes]:
    """Parse an FGM `{count, offsets[], bytecode}` blob and select routes."""
    if len(data) < 4:
        raise ValueError(f"{label} is truncated")
    count = _u32(data, 0)
    if count != expected_count or 4 + count * 4 > len(data):
        raise ValueError(f"unexpected {label} directory")
    offsets = struct.unpack_from(f">{count}I", data, 4)
    if any(offset < 4 + count * 4 or offset >= len(data) for offset in offsets):
        raise ValueError(f"invalid {label} entry offset")
    if tuple(sorted(offsets)) != offsets:
        raise ValueError(f"{label} entry offsets are not ordered")
    selected = {}
    for entry in needed_entries:
        if not 0 <= entry < count:
            raise ValueError(f"invalid requested {label} route {entry}")
        end = offsets[entry + 1] if entry + 1 < count else len(data)
        selected[entry] = data[offsets[entry]:end]
    return selected


def _read_varint(data: bytes, offset: int) -> tuple[int, int]:
    if offset >= len(data):
        raise ValueError("truncated FGM varint")
    value = data[offset]
    if value & 0x80:
        if offset + 1 >= len(data):
            raise ValueError("truncated extended FGM varint")
        return ((value & 0x7F) << 8) | data[offset + 1], offset + 2
    return value, offset + 1


def _ucd_commands(entry: bytes) -> list[tuple[str, int | None]]:
    """Minimal decoder for the UCD voice-script operations used by Falcon."""
    commands: list[tuple[str, int | None]] = []
    offset = 0
    byte_args = {0xD2, 0xD3, 0xD5, 0xD6, 0xD7, 0xD8, 0xDC, 0xDD, 0xDE}
    varint_args = {0xD1, 0xD9}
    while offset < len(entry):
        opcode = entry[offset]
        offset += 1
        if (opcode & 0xF8) < 0xD0:  # note, with optional explicit duration
            if (opcode & 7) == 7:
                _duration, offset = _read_varint(entry, offset)
            continue
        if opcode == 0xD0:
            commands.append(("stop", None))
            break
        if opcode in varint_args:
            value, offset = _read_varint(entry, offset)
            commands.append(("articulation" if opcode == 0xD1 else "fork", value))
        elif opcode == 0xD4:
            for _ in range(6):
                _unused, offset = _read_varint(entry, offset)
        elif opcode in byte_args:
            if offset >= len(entry):
                raise ValueError("truncated FGM UCD byte argument")
            offset += 1
        elif opcode not in (0xDA, 0xDB, 0xDF, 0xE0):
            raise ValueError(f"unsupported FGM UCD opcode 0x{opcode:02X}")
    return commands


def _tbl_trigger(entry: bytes) -> int:
    """Find a selected articulation's first trigger operand."""
    offset = 0
    while offset < len(entry):
        instruction = entry[offset]
        offset += 1
        opcode, timer = instruction & 0xF0, instruction & 0x0F
        if timer & 8:
            if offset >= len(entry):
                raise ValueError("truncated FGM tbl timer")
            extension = entry[offset]
            offset += 1
            if extension & 0x80:
                if offset >= len(entry):
                    raise ValueError("truncated long FGM tbl timer")
                offset += 1
        if opcode == 0x60:
            trigger, _ = _read_varint(entry, offset)
            return trigger
        if opcode == 0x20:
            offset += 2
        elif opcode == 0x40:
            offset += 1
            _unused, offset = _read_varint(entry, offset)
        elif opcode in (0x00, 0x10, 0x30, 0x50):
            offset += 1
        elif opcode in (0x70, 0x80, 0x90):
            if opcode == 0x70:
                break
        else:
            raise ValueError(f"unsupported FGM tbl opcode 0x{opcode:02X}")
        if offset > len(entry):
            raise ValueError("truncated FGM tbl argument")
    raise ValueError("FGM articulation has no trigger")


def _ucd_initial_note_cents(entry: bytes) -> int:
    """Return the first UCD note's pitch relative to the 32 kHz base."""
    offset = 0
    octave_offset = 0
    byte_args = {0xD2, 0xD3, 0xD5, 0xD6, 0xD7, 0xD8, 0xDC, 0xDD, 0xDE}
    while offset < len(entry):
        opcode = entry[offset]
        offset += 1
        if (opcode & 0xF8) < 0xD0:
            if (opcode & 7) == 7:
                _duration, offset = _read_varint(entry, offset)
            return ((opcode >> 3) * 100) - 1300 + octave_offset
        if opcode in (0xD1, 0xD9):
            _unused, offset = _read_varint(entry, offset)
        elif opcode == 0xD4:
            for _ in range(6):
                _unused, offset = _read_varint(entry, offset)
        elif opcode in byte_args:
            offset += 1
        elif opcode == 0xDF:
            octave_offset = -2400
        elif opcode == 0xE0:
            octave_offset = -4800
        elif opcode in (0xDA, 0xDB):
            pass
        elif opcode == 0xD0:
            break
        else:
            raise ValueError(f"unsupported FGM UCD opcode 0x{opcode:02X}")
        if offset > len(entry):
            raise ValueError("truncated FGM UCD argument")
    raise ValueError("FGM UCD route has no note")


def _tbl_initial_pitch_cents(entry: bytes) -> int:
    """Return the articulation pitch in effect at its first trigger."""
    offset = 0
    pitch = 0
    triggered = False
    while offset < len(entry):
        instruction = entry[offset]
        offset += 1
        opcode, timer = instruction & 0xF0, instruction & 0x0F
        if timer & 8:
            if offset >= len(entry):
                raise ValueError("truncated FGM tbl timer")
            extension = entry[offset]
            offset += 1
            timer = ((timer & 7) << 7) | (extension & 0x7F)
            if extension & 0x80:
                if offset >= len(entry):
                    raise ValueError("truncated long FGM tbl timer")
                timer = (timer << 8) | entry[offset]
                offset += 1
        if opcode == 0x60:
            _trigger, offset = _read_varint(entry, offset)
            triggered = True
        elif opcode == 0x20:
            if offset + 2 > len(entry):
                raise ValueError("truncated FGM tbl pitch")
            pitch = struct.unpack_from(">h", entry, offset)[0]
            offset += 2
        elif opcode == 0x40:
            offset += 1
            _unused, offset = _read_varint(entry, offset)
        elif opcode in (0x00, 0x10, 0x30, 0x50):
            offset += 1
        elif opcode in (0x70, 0x80, 0x90):
            if opcode == 0x70:
                return pitch if triggered else 0
        else:
            raise ValueError(f"unsupported FGM tbl opcode 0x{opcode:02X}")
        if offset > len(entry):
            raise ValueError("truncated FGM tbl argument")
        if triggered and timer:
            return pitch
    raise ValueError("FGM articulation has no trigger")


def pitched_source_rate(cents: int, nominal_rate: int = SYNTH_RATE) -> int:
    """Quantize the N64 pitch ratio to an integer rate for offline sinc output."""
    if nominal_rate <= 0:
        raise ValueError("nominal sample rate must be positive")
    return round(nominal_rate * math.pow(2.0, cents / 1200.0))


def parse_fgm_routes(rom: bytes) -> dict[str, dict[int, bytes]]:
    """Read the documented FGM directories used by the Falcon cue recipe."""
    # The selected ucd entries include Falcon Punch/Kick/Dive programs and
    # their forked voices.  The selected tbl entries are their articulations.
    # We retain the bytecode only long enough to validate this ROM's route
    # directories; the focused offline renderer below applies their known
    # pitch/envelope results without bundling an in-game FGM interpreter.
    routes = {
        "tbl": _parse_fgm_blob(rom[slice(*FGM_TBL)], 464, "fgm.tbl",
                                (6, 7, 41, 146, 147, 173, 186, 187, 213, 463)),
        "ucd": _parse_fgm_blob(rom[slice(*FGM_UCD)], 695, "fgm.ucd",
                                (0, 1, 19, 41, 182, 183, 184, 186, 187, 338, 641)),
    }
    ucd = {index: _ucd_commands(program) for index, program in routes["ucd"].items()}
    expected_articulations = {0: 7, 1: 6, 19: 463, 41: 173, 182: 41,
                              186: 147, 187: 146, 338: 213, 641: 6}
    for voice, articulation in expected_articulations.items():
        if ("articulation", articulation) not in ucd[voice]:
            raise ValueError(f"FGM UCD route {voice} does not select articulation {articulation}")
    expected_forks = {1: 641, 183: 186, 184: 187, 187: 0}
    for voice, fork in expected_forks.items():
        if ("fork", fork) not in ucd[voice]:
            raise ValueError(f"FGM UCD route {voice} does not fork {fork}")
    expected_triggers = {6: 4, 7: 4, 41: 18, 146: 11, 147: 11,
                         173: 18, 213: 95, 463: 11}
    for articulation, trigger in expected_triggers.items():
        if _tbl_trigger(routes["tbl"][articulation]) != trigger:
            raise ValueError(f"FGM articulation {articulation} does not trigger sound {trigger}")
    return routes


SINC_RADIUS = 16
SINC_CUTOFF = 0.97
SINC_KAISER_BETA = 9.0
SINC_COEFFICIENT_SCALE = 1 << 30


def _bessel_i0(value: float) -> float:
    """Dependency-free modified Bessel I0 for the finite Kaiser window."""
    result = 1.0
    term = 1.0
    square = value * value / 4.0
    for index in range(1, 32):
        term *= square / (index * index)
        result += term
        if term <= result * 1.0e-16:
            break
    return result


def resample_windowed_sinc(samples: list[int], source_rate: int,
                           output_rate: int) -> list[int]:
    """Deterministic bounded Kaiser-windowed sinc resampling.

    The 32-tap, 0.97-cutoff filter mirrors the quality class and defaults of
    the historical FFmpeg/libswresample previews. Rational phases are
    precomputed once and quantized to signed Q30; sample accumulation and
    rounding are integer-only, making output independent of host SIMD paths
    and floating-point accumulation order. Boundary phases are DC-normalized
    and all output is explicitly saturated to signed 16-bit PCM.
    """
    if not samples:
        return []
    if source_rate <= 0 or output_rate <= 0:
        raise ValueError("sample rates must be positive")
    if source_rate == output_rate:
        return [_clip_s16(sample) for sample in samples]
    # FFmpeg's resampler includes the final fractional sample for the old
    # developer previews; preserve that established cue duration.
    count = math.ceil(len(samples) * output_rate / source_rate)
    divisor = math.gcd(source_rate, output_rate)
    position_step = source_rate // divisor
    phase_count = output_rate // divisor
    cutoff = SINC_CUTOFF * min(1.0, output_rate / source_rate)
    offsets = tuple(range(-SINC_RADIUS + 1, SINC_RADIUS + 1))
    window_scale = _bessel_i0(SINC_KAISER_BETA)
    phases: list[tuple[int, ...]] = []
    for phase in range(phase_count):
        fraction = phase / phase_count
        weights = []
        for tap in offsets:
            distance = fraction - tap
            angle = math.pi * cutoff * distance
            sinc = 1.0 if angle == 0.0 else math.sin(angle) / angle
            relative = distance / SINC_RADIUS
            if abs(relative) >= 1.0:
                window = 0.0
            else:
                window = (_bessel_i0(SINC_KAISER_BETA *
                                      math.sqrt(1.0 - relative * relative)) /
                          window_scale)
            weights.append(cutoff * sinc * window)
        normalization = sum(weights)
        quantized = [round(weight / normalization * SINC_COEFFICIENT_SCALE)
                     for weight in weights]
        # Preserve unity DC gain exactly in the full filter. Put the tiny
        # quantization remainder in the dominant tap to minimize error.
        dominant = max(range(len(quantized)), key=lambda index: abs(quantized[index]))
        quantized[dominant] += SINC_COEFFICIENT_SCALE - sum(quantized)
        phases.append(tuple(quantized))

    rendered: list[int] = []
    for index in range(count):
        numerator = index * position_step
        center, phase = divmod(numerator, phase_count)
        total = 0
        normalization = 0
        for tap, weight in zip(offsets, phases[phase]):
            source_index = center + tap
            if 0 <= source_index < len(samples):
                total += samples[source_index] * weight
                normalization += weight
        if normalization <= 0:
            raise ValueError("windowed-sinc boundary has invalid normalization")
        if total >= 0:
            value = (total + normalization // 2) // normalization
        else:
            value = -((-total + normalization // 2) // normalization)
        rendered.append(_clip_s16(value))
    return rendered


def _value_at(points: list[tuple[float, float]], tick: float) -> float:
    value = points[0][1]
    for start, candidate in points:
        if tick < start:
            break
        value = candidate
    return value


def synth_voice(samples: list[int], pitch_cents: list[tuple[float, float]],
                stop_tick: float, top_volume: int | list[tuple[float, float]],
                articulation_volume: list[tuple[float, float]]) -> list[int]:
    """Render the FGM articulation subset exercised by Falcon's seven cues."""
    position = 0.0
    output: list[int] = []
    stop_sample = int(round(stop_tick * FGM_TICK_SECONDS * OUTPUT_RATE))
    release_samples = max(1, int(round(FGM_TICK_SECONDS * OUTPUT_RATE)))
    for output_index in range(stop_sample + release_samples):
        if position >= len(samples) - 1:
            break
        tick = output_index / (FGM_TICK_SECONDS * OUTPUT_RATE)
        fraction, low = math.modf(position)
        low = int(low)
        sample = samples[low] + (samples[low + 1] - samples[low]) * fraction
        top = _value_at(top_volume, tick) if isinstance(top_volume, list) else top_volume
        gain = (top / 255.0) * (_value_at(articulation_volume, tick) / 127.0) * (126.0 / 127.0)
        if output_index >= stop_sample:
            gain *= 1.0 - ((output_index - stop_sample) / release_samples)
        output.append(round(sample * gain))
        position += SYNTH_RATE * math.pow(2.0, _value_at(pitch_cents, tick) / 1200.0) / OUTPUT_RATE
    return output


def mix_voices(*voices: list[int]) -> list[int]:
    mixed = [0] * max(map(len, voices))
    for voice in voices:
        for index, sample in enumerate(voice):
            mixed[index] = _clip_s16(mixed[index] + sample)
    return mixed


def render_fgm(waves: dict[int, list[int]]) -> dict[str, list[int]]:
    """Known FGM routes, checked against fgm.tbl/fgm.ucd at extraction time."""
    # Read the selected programs so a wrong/revision-mismatched input cannot
    # silently be treated as this recipe.  The canonical hash is the primary
    # identity check; the route assertions are a focused structural guard.
    result = {
        "falcon_punch_impact_fgm.wav": mix_voices(
            synth_voice(waves[11], [(0, -1499), (20, -999), (30, -1299), (40, -1199), (100, -1499)], 300, 255, [(0, 127)]),
            synth_voice(waves[4], [(0, -700)], 135, 220,
                        [(0, 127), (8, 122), (16, 115), (24, 110), (32, 105), (40, 100), (48, 95), (56, 90), (64, 85), (72, 80), (80, 75), (88, 70), (96, 65), (104, 60), (112, 55), (120, 50), (128, 45)]),
        ),
        "falcon_kick_start_fgm.wav": synth_voice(waves[11], [(0, -2299), (20, -2199), (40, -1999)], 140, 190, [(0, 127), (50, 90), (100, 60)]),
        "falcon_kick_swing_fgm.wav": synth_voice(waves[18], [(0, 150)], 35, 230, [(0, 120)]),
        "falcon_dive_launch_fgm.wav": synth_voice(waves[18], [(0, 200), (1, -600), (6, -300), (11, 0), (21, 200), (31, 400), (51, 100), (61, 0), (71, -100), (81, -200), (91, -300)], 99, [(0, 200), (25, 220), (51, 160), (69, 130)], [(0, 110), (41, 120)]),
        "falcon_dive_catch_fgm.wav": synth_voice(waves[11], [(0, -200), (7, 2300), (10, 2300), (12, 2300), (14, 2300), (16, 2300)], 25, 255, [(0, 5), (1, 16), (2, 50), (3, 100), (4, 125), (7, 90), (10, 60), (12, 30), (14, 20), (16, 5)]),
        "falcon_dive_explosion_fgm.wav": mix_voices(
            synth_voice(waves[4], [(0, 550)], 190, 255, [(0, 120)]),
            synth_voice(waves[4], [(0, 550)], 520, 180, [(0, 120)]),
        ),
        "falcon_dive_voice.wav": synth_voice(waves[95], [(0, -1200)], 120, 215, [(0, 127)]),
    }
    return result


def _write_wav(path: Path, samples: list[int]) -> None:
    pcm = array.array("h", (_clip_s16(sample) for sample in samples))
    with wave.open(str(path), "wb") as output:
        output.setnchannels(1)
        output.setsampwidth(2)
        output.setframerate(OUTPUT_RATE)
        output.writeframes(pcm.tobytes())


def render_audio(rom_path: Path, output_dir: Path) -> Path:
    """Verify, decode, render, and atomically commit an external audio cache."""
    _external_output(output_dir)
    rom = normalize_rom(rom_path.read_bytes())
    rom_sha1 = hashlib.sha1(rom).hexdigest()
    if rom_sha1 != CANONICAL_SHA1:
        raise ValueError("ROM is not the supported Smash Bros. US v1.0 image")
    parse_fgm_routes(rom)

    parent = output_dir.parent
    parent.mkdir(parents=True, exist_ok=True)
    staging = Path(tempfile.mkdtemp(prefix=f".{output_dir.name}.", dir=parent))
    try:
        waves = decode_required_waves(rom)
        rendered = {
            name: resample_windowed_sinc(waves[wave_id], 16000, OUTPUT_RATE)
            for name, wave_id in VOICE_WAVES.items()
        }
        rendered.update(render_fgm(waves))
        if set(rendered) != {
            "falcon_jump_effort.wav", "falcon_punch_falcon.wav", "falcon_punch_punch.wav", "falcon_kick.wav",
            "falcon_punch_impact_fgm.wav", "falcon_kick_start_fgm.wav", "falcon_kick_swing_fgm.wav",
            "falcon_dive_launch_fgm.wav", "falcon_dive_catch_fgm.wav", "falcon_dive_explosion_fgm.wav", "falcon_dive_voice.wav",
        }:
            raise AssertionError("Falcon audio recipe must render exactly eleven clips")
        clips = []
        for name, samples in sorted(rendered.items()):
            path = staging / name
            _write_wav(path, samples)
            clips.append({"file": name, "frames": len(samples),
                          "pcm_sha256": hashlib.sha256(path.read_bytes()[44:]).hexdigest()})
        (staging / "manifest.json").write_text(json.dumps({
            "format": "smb1-smash64-falcon-audio-cache", "recipe_version": 1,
            "normalized_rom_sha1": rom_sha1, "clips": clips,
        }, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        if output_dir.exists():
            raise FileExistsError(f"refusing to overwrite existing audio cache: {output_dir}")
        os.replace(staging, output_dir)
        return output_dir
    except Exception:
        shutil.rmtree(staging, ignore_errors=True)
        raise


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, required=True, help="owner US v1.0 ROM (.z64/.v64/.n64)")
    parser.add_argument("--out", type=Path, required=True, help="external cache/staging output directory")
    args = parser.parse_args(argv)
    print(render_audio(args.rom, args.out))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
