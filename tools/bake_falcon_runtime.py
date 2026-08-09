#!/usr/bin/env python3
"""Bake ignored SSB64 Falcon intermediates into one ignored runtime blob.

This script contains no extracted data.  It consumes assets_ssb64/ (which is
locally extracted from the owner's ROM and gitignored) and writes a compact
little-endian file that the game-side C loader can parse without embedding a
JSON or PNG implementation in the executable.
"""

from __future__ import annotations

import argparse
import json
import math
import struct
from pathlib import Path

from PIL import Image


MAGIC = b"FLCN64B\0"
VERSION = 4
TRACK_IDS = {
    "RotX": 0,
    "RotY": 1,
    "RotZ": 2,
    "TraX": 3,
    "TraY": 4,
    "TraZ": 5,
    "ScaX": 6,
    "ScaY": 7,
    "ScaZ": 8,
}
LOOPING_ANIMS = {"Wait", "Walk1", "Walk2", "Walk3", "Run", "CrouchIdle"}

# BattleShip ftdata.c marks these motions with one of the auxiliary fighter
# root flags (the historically swapped TRANSN/XROTN macro names both create a
# root before CommonStart). lbCommonAddFighterPartsFigatree walks that root
# first, so stream 0 is not model joint 0 and every common-part stream follows
# it by one slot. The host owns root motion; omit the auxiliary stream and bind
# streams 1..25 to baked model joints 0..24 exactly as Smash does.
AUXILIARY_ROOT_ANIMS = {
    "TurnRun", "JumpB", "JumpAerialB", "FalconPunchGround",
    "DownSpecial", "VelocityXDownSpecialAir", "LandingDownSpecial",
    "DownSpecialAir", "FalconDive", "FalconDiveEnd1", "FalconDiveEnd2",
}

INTERP_HOLD = 0
INTERP_LINEAR = 1
INTERP_CUBIC = 2
INTERP_STEP = 3

FALCON_PUNCH_RELOC_SIZE = 0x870
FALCON_PUNCH_PALETTE_OFFSET = 0x58
FALCON_PUNCH_TEXTURE_OFFSETS = (0x80, 0x288, 0x490)
FALCON_PUNCH_TEXTURE_WIDTH = 32
FALCON_PUNCH_TEXTURE_HEIGHT = 32

FALCON_KICK_RELOC_SIZE = 0x65E0
FALCON_KICK_PALETTE_OFFSET = 0x30
FALCON_KICK_TEXTURE_OFFSETS = (0x4E0, 0x58)
FALCON_KICK_TEXTURE_WIDTH = 48
FALCON_KICK_TEXTURE_HEIGHT = 48


def load_json(path: Path):
    with path.open("r", encoding="utf-8") as stream:
        return json.load(stream)


def decode_tri_word(word: int) -> tuple[int, int, int]:
    """Decode one F3DEX2 triangle word (three doubled vertex slots)."""
    return ((word >> 16 & 0xFF) // 2,
            (word >> 8 & 0xFF) // 2,
            (word & 0xFF) // 2)


def texture_image(textures_dir: Path, symbol: str) -> Image.Image | None:
    candidates = (
        textures_dir / f"{symbol}.png",
        textures_dir / f"{symbol}.index_preview.png",
    )
    for candidate in candidates:
        if candidate.is_file():
            return Image.open(candidate).convert("RGBA")
    return None


def fallback_pixel(symbol: str) -> bytes:
    # Stable, visibly Falcon-ish fallback when a CI palette is unresolved.
    value = sum((i + 1) * ord(ch) for i, ch in enumerate(symbol))
    r = 40 + value % 72
    g = 50 + (value // 7) % 72
    b = 118 + (value // 17) % 100
    return struct.pack("<I", 0xFF000000 | (r << 16) | (g << 8) | b)


def rgba_to_argb_bytes(image: Image.Image) -> bytes:
    out = bytearray()
    rgba = image.tobytes()
    for offset in range(0, len(rgba), 4):
        r, g, b, a = rgba[offset:offset + 4]
        out += struct.pack("<I", (a << 24) | (r << 16) | (g << 8) | b)
    return bytes(out)


def rgba16_to_argb(value: int) -> int:
    """Decode one big-endian N64 RGBA16 palette entry."""
    r5 = (value >> 11) & 0x1F
    g5 = (value >> 6) & 0x1F
    b5 = (value >> 1) & 0x1F
    alpha = 0xFF if value & 1 else 0
    red = (r5 * 255 + 15) // 31
    green = (g5 * 255 + 15) // 31
    blue = (b5 * 255 + 15) // 31
    return (alpha << 24) | (red << 16) | (green << 8) | blue


def collect_falcon_punch_textures(root: Path):
    """Decode CaptainSpecial3's authored three-frame CI4 fire billboard.

    BattleShip identifies reloc file 333 as CaptainSpecial3. Its decompiled
    layout places the shared RGBA16 palette at 0x58 and the three 32x32 CI4
    frames at 0x80, 0x288, and 0x490. The decompressed reloc remains an
    owner-derived, ignored input; only this extraction recipe is publishable.
    """
    source = root / "effects" / "CaptainSpecial3.bin"
    if not source.is_file():
        raise FileNotFoundError(
            f"missing {source}; extract BattleShip reloc file 333 from the "
            "owner's Smash 64 ROM before baking")
    data = source.read_bytes()
    if len(data) != FALCON_PUNCH_RELOC_SIZE:
        raise ValueError(
            f"{source} is {len(data)} bytes; expected "
            f"{FALCON_PUNCH_RELOC_SIZE} bytes")

    palette = []
    for index in range(16):
        offset = FALCON_PUNCH_PALETTE_OFFSET + index * 2
        palette.append(rgba16_to_argb(
            int.from_bytes(data[offset:offset + 2], "big")))

    records = []
    pixel_count = FALCON_PUNCH_TEXTURE_WIDTH * FALCON_PUNCH_TEXTURE_HEIGHT
    byte_count = pixel_count // 2
    for frame, offset in enumerate(FALCON_PUNCH_TEXTURE_OFFSETS):
        packed = data[offset:offset + byte_count]
        if len(packed) != byte_count:
            raise ValueError(f"truncated Falcon Punch texture frame {frame}")
        pixels = bytearray()
        for pixel in range(pixel_count):
            value = packed[pixel // 2]
            palette_index = value >> 4 if pixel % 2 == 0 else value & 0x0F
            pixels += struct.pack("<I", palette[palette_index])
        records.append((f"FalconPunch{frame}",
                        FALCON_PUNCH_TEXTURE_WIDTH,
                        FALCON_PUNCH_TEXTURE_HEIGHT, bytes(pixels)))
    return records


def collect_falcon_kick_textures(root: Path):
    """Decode CaptainSpecial2's two authored CI4 Falcon Kick cards.

    BattleShip reloc file 350 supplies a shared RGBA16 palette at 0x30 and
    two 48x48 CI4 frames at 0x4E0 and 0x58. The odd source order is the
    MObjSub sprite order used by the effect's material animation.
    """
    source = root / "effects" / "CaptainSpecial2.bin"
    if not source.is_file():
        raise FileNotFoundError(
            f"missing {source}; extract BattleShip reloc file 350 from the "
            "owner's Smash 64 ROM before baking")
    data = source.read_bytes()
    if len(data) != FALCON_KICK_RELOC_SIZE:
        raise ValueError(
            f"{source} is {len(data)} bytes; expected "
            f"{FALCON_KICK_RELOC_SIZE} bytes")

    palette = []
    for index in range(16):
        offset = FALCON_KICK_PALETTE_OFFSET + index * 2
        palette.append(rgba16_to_argb(
            int.from_bytes(data[offset:offset + 2], "big")))

    records = []
    pixel_count = FALCON_KICK_TEXTURE_WIDTH * FALCON_KICK_TEXTURE_HEIGHT
    byte_count = pixel_count // 2
    for frame, offset in enumerate(FALCON_KICK_TEXTURE_OFFSETS):
        packed = data[offset:offset + byte_count]
        if len(packed) != byte_count:
            raise ValueError(f"truncated Falcon Kick texture frame {frame}")
        pixels = bytearray()
        for pixel in range(pixel_count):
            value = packed[pixel // 2]
            palette_index = value >> 4 if pixel % 2 == 0 else value & 0x0F
            pixels += struct.pack("<I", palette[palette_index])
        records.append((f"FalconKick{frame}",
                        FALCON_KICK_TEXTURE_WIDTH,
                        FALCON_KICK_TEXTURE_HEIGHT, bytes(pixels)))
    return records


class TextureCatalog:
    def __init__(self, root: Path, palettes: dict[str, list[int]],
                 dimensions: dict[str, list[int]]):
        self.textures_dir = root / "textures"
        self.palettes = palettes
        self.dimensions = dimensions
        self.records = []
        self.ids = {}

    def _add(self, key, symbol: str, width: int, height: int, pixels: bytes):
        if key not in self.ids:
            self.ids[key] = len(self.records)
            self.records.append((symbol, width, height, pixels))
        return self.ids[key]

    def solid(self, argb: int) -> int:
        return self._add(("solid", argb), f"solid_{argb:08x}", 1, 1,
                         struct.pack("<I", argb))

    def fallback(self, symbol: str) -> int:
        image = texture_image(self.textures_dir, symbol)
        if image is None:
            return self._add(("fallback", symbol), symbol, 1, 1,
                             fallback_pixel(symbol))
        width, height = image.size
        return self._add(("png", symbol), symbol, width, height,
                         rgba_to_argb_bytes(image))

    def ci(self, symbol: str, palette_symbol: str | None,
           width: int, height: int, bpp: int) -> int:
        if symbol in self.dimensions:
            width, height = map(int, self.dimensions[symbol])
        key = ("ci", symbol, palette_symbol, width, height, bpp)
        if key in self.ids:
            return self.ids[key]
        raw_path = self.textures_dir / f"{symbol}.bin"
        palette = self.palettes.get(palette_symbol or "")
        expected = (width * height * bpp + 7) // 8
        if (raw_path.is_file() and expected > raw_path.stat().st_size and
                bpp == 4 and width % 2 == 0):
            # CI4 display lists use a 16-bit load-block convention.  When no
            # @tex annotation exists, the tile window can therefore report
            # twice the stored pixel width.
            width //= 2
            key = ("ci", symbol, palette_symbol, width, height, bpp)
            expected = (width * height * bpp + 7) // 8
            if key in self.ids:
                return self.ids[key]
        if bpp not in (4, 8) or not raw_path.is_file() or not palette:
            return self.fallback(symbol)
        raw = raw_path.read_bytes()
        if expected > len(raw):
            return self.fallback(symbol)
        raw = raw[:expected]
        pixels = bytearray()
        for pixel in range(width * height):
            if bpp == 4:
                value = raw[pixel // 2]
                index = value >> 4 if pixel % 2 == 0 else value & 0x0F
            else:
                index = raw[pixel]
            argb = palette[index] if index < len(palette) else 0xFFFF00FF
            pixels += struct.pack("<I", argb)
        label = f"{symbol}@{palette_symbol}"
        return self._add(key, label, width, height, bytes(pixels))


def decoded_tile_size(op: dict) -> tuple[int, int] | None:
    """Decode a G_SETTILESIZE window, accounting for non-zero UL coords."""
    w0, w1 = op.get("w0"), op.get("w1")
    if not isinstance(w0, int) or not isinstance(w1, int):
        return None
    uls, ult = (w0 >> 12) & 0xFFF, w0 & 0xFFF
    lrs, lrt = (w1 >> 12) & 0xFFF, w1 & 0xFFF
    if lrs < uls or lrt < ult:
        return None
    return (lrs - uls) // 4 + 1, (lrt - ult) // 4 + 1


def collect_model(root: Path):
    model_dir = root / "model"
    model = load_json(model_dir / "captain_model.json")
    tree = model["trees"]["dCaptainModel_JointTree"]

    # The extractor preserves the source END marker as a 27th depth-18 entry.
    # It is not a drawable joint; the documented Falcon skeleton is 0..25.
    joints = [j for j in tree["joints"] if int(j["index"]) < 26]
    if len(joints) != 26:
        raise ValueError(f"expected 26 Falcon joints, found {len(joints)}")

    vertex_cache = {}
    triangles = []
    joint_ranges = []
    bindings_path = root / "textures" / "material_bindings.json"
    bindings = load_json(bindings_path) if bindings_path.is_file() else {}
    joint_materials = bindings.get("joint_materials", [[] for _ in range(26)])
    palettes = bindings.get("palettes_argb", {})
    texture_dimensions = bindings.get("texture_dimensions", {})
    catalog = TextureCatalog(root, palettes, texture_dimensions)

    for joint in joints:
        first = len(triangles)
        dl_name = joint.get("dl")
        if dl_name:
            dl_path = model_dir / "dl" / f"{dl_name}.json"
            ops = load_json(dl_path) if dl_path.is_file() else []
            slots = [None] * 32
            current_texture = 0xFFFF
            current_image = None
            current_palette = None
            current_dims = None
            current_bpp = 4
            pending_dims = None
            last_settimg = None
            for op in ops:
                opname = op.get("op")
                if opname == "G_SETTILE" and op.get("tile") == 0:
                    current_bpp = int(op.get("siz_bpp", current_bpp))
                elif opname == "G_SETTILESIZE":
                    pending_dims = decoded_tile_size(op)
                elif opname == "G_SETTIMG":
                    last_settimg = op.get("image")
                elif opname == "G_LOADTLUT":
                    if last_settimg in palettes:
                        current_palette = last_settimg
                        if current_image and current_dims:
                            current_texture = catalog.ci(
                                current_image, current_palette,
                                current_dims[0], current_dims[1], current_bpp)
                    last_settimg = None
                elif opname == "G_DL":
                    word = op.get("w1")
                    materials = (joint_materials[int(joint["index"])]
                                 if int(joint["index"]) < len(joint_materials)
                                 else [])
                    if isinstance(word, int) and word >> 24 == 0x0E:
                        material_index = (word & 0x00FFFFFF) // 8
                        if material_index < len(materials):
                            material = materials[material_index]
                            if material.get("format") == "CI":
                                current_palette = material.get("palette_symbol")
                                if current_image and current_dims:
                                    current_texture = catalog.ci(
                                        current_image, current_palette,
                                        current_dims[0], current_dims[1],
                                        current_bpp)
                            else:
                                current_texture = catalog.solid(
                                    int(material.get("default_primary_argb",
                                                     material["primary_argb"])))
                        # The called material DL supplies the palette image;
                        # prevent the preceding pixel SETTIMG from masquerading
                        # as a static TLUT source when G_LOADTLUT follows.
                        last_settimg = None
                elif opname == "G_LOADBLOCK":
                    if last_settimg and pending_dims:
                        current_image = last_settimg
                        current_dims = pending_dims
                        current_texture = catalog.ci(
                            current_image, current_palette,
                            current_dims[0], current_dims[1], current_bpp)
                    last_settimg = None
                elif opname == "G_VTX":
                    symbol = op.get("vbuf")
                    if not symbol:
                        continue
                    if symbol not in vertex_cache:
                        vertex_cache[symbol] = load_json(
                            model_dir / "vtx" / f"{symbol}.json")
                    vertices = vertex_cache[symbol]
                    v0 = int(op.get("v0", 0))
                    count = int(op.get("numv", len(vertices)))
                    for offset, vertex in enumerate(vertices[:count]):
                        if v0 + offset < len(slots):
                            slots[v0 + offset] = vertex
                elif opname in ("G_TRI1", "G_TRI2"):
                    index_sets = []
                    if opname == "G_TRI1":
                        index_sets.append(tuple(int(x) for x in op["indices"]))
                    else:
                        index_sets.append(decode_tri_word(int(op["w0"])))
                        index_sets.append(decode_tri_word(int(op["w1"])))
                    for indices in index_sets:
                        verts = [slots[index] if index < len(slots) else None
                                 for index in indices]
                        if any(vertex is None for vertex in verts):
                            raise ValueError(
                                f"{dl_name}: triangle {indices} references an unloaded slot")
                        triangles.append({
                            "joint": int(joint["index"]),
                            "texture": current_texture,
                            "vertices": verts,
                        })
        joint_ranges.append((first, len(triangles) - first))

    return joints, joint_ranges, triangles, catalog.records


def _track_segments(joint: dict):
    """Compile one Figatree joint stream with objanim.c's AObj semantics.

    A Figatree command changes an AObj's target immediately, then a blocking
    command advances the shared stream clock while the AObj interpolates from
    its previous target.  Flattening commands into target keyframes loses that
    previous target, the authored tangent rates, step-vs-linear behavior, and
    the duration after the final target.  Keep explicit segments instead.
    """
    states = {}
    segments = {}
    frame = 0.0

    def state_for(track):
        return states.setdefault(track, {"target": 0.0, "rate": 0.0})

    for op in joint.get("ops", []):
        opname = op.get("op")
        duration = float(op.get("dur") or 0.0)
        if opname == "Block":
            frame += duration
            continue
        if opname == "SetTargetRate":
            for track in op.get("tracks", []):
                raw = op["payload"][track]
                state_for(track)["rate"] = raw_to_rate_units(track, raw)
            continue
        if opname not in {
            "SetValBlock", "SetVal", "SetValRateBlock", "SetValRate",
            "SetVal0RateBlock", "SetVal0Rate", "SetValAfterBlock",
            "SetValAfter",
        }:
            continue

        is_block = opname.endswith("Block") and duration > 0.0
        for track in op.get("tracks", []):
            payload = op["payload"][track]
            raw_value = payload[0] if isinstance(payload, list) else payload
            target = raw_to_units(track, raw_value)
            state = state_for(track)
            base = state["target"]
            rate_base = state["rate"]

            if opname.startswith("SetValRate"):
                raw_rate = payload[1]
                rate_target = raw_to_rate_units(track, raw_rate)
                kind = INTERP_CUBIC
            elif opname.startswith("SetVal0Rate"):
                rate_target = 0.0
                kind = INTERP_CUBIC
            elif opname.startswith("SetValAfter"):
                rate_target = 0.0
                kind = INTERP_STEP
            else:
                rate_target = 0.0
                kind = INTERP_LINEAR

            # Timed non-blocking commands start an interpolation just like
            # their Block counterparts; they merely let this joint stream
            # continue parsing until another command supplies the wait. This
            # matters especially for Falcon Kick's TransN stream, where TraZ
            # travels during blocks owned by TraY.
            if duration > 0.0:
                segments.setdefault(track, []).append((
                    frame, duration, base, target, rate_base, rate_target, kind
                ))
            # This assignment is immediate in gcParseDObjAnimJoint, even for
            # a blocking command; the elapsed segment still starts at `base`.
            state["target"] = target
            state["rate"] = rate_target

        if is_block:
            frame += duration

    # Preserve tracks that only contain a zero-duration initializer.  A hold
    # record gives the runtime the initialized target instead of inventing 0.
    for track, state in states.items():
        if not segments.get(track):
            segments.setdefault(track, []).append((
                0.0, 0.0, state["target"], state["target"],
                state["rate"], state["rate"], INTERP_HOLD
            ))
    return segments, frame


def raw_to_units(track: str, raw: int) -> float:
    if track.startswith("Rot"):
        return raw / 512.0
    if track == "TraI":
        return raw / 16384.0
    if track.startswith("Tra"):
        return raw / 4.0
    if track.startswith("Sca"):
        return raw / 4096.0
    raise ValueError(f"unknown Figatree track {track}")


def raw_to_rate_units(track: str, raw: int) -> float:
    """Decode ftAnimGetTargetValue(..., value_or_step=1).

    BattleShip's rate table deliberately differs from its target-value table:
    rotation remains /512, translation is /32 (not /4), and scale is /8192
    (not /4096). Treating a translation tangent like a position made cubic
    Falcon motions overshoot by eight times and visibly warp/snap.
    """
    if track.startswith("Rot"):
        return raw / 512.0
    if track == "TraI":
        return raw / 16384.0
    if track.startswith("Tra"):
        return raw / 32.0
    if track.startswith("Sca"):
        return raw / 8192.0
    raise ValueError(f"unknown Figatree track {track}")


def collect_animations(root: Path):
    manifest = load_json(root / "anim" / "anim_manifest.json")
    animations = []
    tracks = []
    segments = []

    for entry in manifest:
        if entry.get("status") != "ok":
            continue
        data = load_json(root / "anim" / entry["output"])
        name = str(data["canonical_name"])
        first_track = len(tracks)
        duration = 0.0
        for joint in data.get("joints", []):
            # Figatree names are one-based (joint1..joint26), while the
            # extracted DObj descriptor array and runtime model are zero-based.
            # The first Figatree stream is attached to TopN->child, i.e. model
            # joint 0, not model joint 1.
            joint_index = int(joint.get(
                "joint_slot", int(joint.get("joint_id", 1)) - 1))
            if name in AUXILIARY_ROOT_ANIMS:
                if joint_index == 0:
                    # Keep the hidden TransN stream in the ignored runtime
                    # blob for source-root-motion sampling, but never apply it
                    # to the visible skeleton. 0xFFFF is outside the 26 model
                    # joints and is recognized by the runtime loader as the
                    # animation-motion track sentinel.
                    joint_index = 0xFFFF
                else:
                    joint_index -= 1
            if joint_index != 0xFFFF and not 0 <= joint_index < 26:
                continue
            joint_segments, joint_duration = _track_segments(joint)
            duration = max(duration, joint_duration)
            for track_name, track_segments in joint_segments.items():
                if track_name not in TRACK_IDS or not track_segments:
                    continue
                first_segment = len(segments)
                segments.extend(track_segments)
                tracks.append((joint_index, TRACK_IDS[track_name],
                               first_segment, len(track_segments)))
        animations.append((name, duration if duration > 0.0 else 1.0,
                           1 if name in LOOPING_ANIMS else 0,
                           first_track, len(tracks) - first_track))

    return animations, tracks, segments


def write_blob(root: Path, output: Path):
    joints, joint_ranges, triangles, textures = collect_model(root)
    animations, tracks, segments = collect_animations(root)
    effect_texture_first = len(textures)
    effect_textures = collect_falcon_punch_textures(root)
    textures.extend(effect_textures)
    kick_effect_textures = collect_falcon_kick_textures(root)
    textures.extend(kick_effect_textures)

    output.parent.mkdir(parents=True, exist_ok=True)
    with output.open("wb") as stream:
        stream.write(MAGIC)
        stream.write(struct.pack(
            "<9I", VERSION, len(joints), len(triangles), len(textures),
            len(animations), len(tracks), len(segments),
            effect_texture_first, len(effect_textures)))

        for joint, (first_tri, tri_count) in zip(joints, joint_ranges):
            parent = joint.get("parent")
            parent = -1 if parent is None else int(parent)
            values = [float(x) for key in ("translate", "rotate_rad", "scale")
                      for x in joint[key]]
            stream.write(struct.pack("<i9f2I", parent, *values,
                                     first_tri, tri_count))

        for triangle in triangles:
            stream.write(struct.pack("<HH", triangle["joint"],
                                     triangle["texture"]))
            for vertex in triangle["vertices"]:
                pos = [float(x) for x in vertex["pos"]]
                uv = [float(x) for x in vertex["uv_texels"]]
                stream.write(struct.pack("<5f", *(pos + uv)))

        for _symbol, width, height, pixels in textures:
            stream.write(struct.pack("<HHI", width, height, len(pixels)))
            stream.write(pixels)

        for name, duration, loop, first_track, track_count in animations:
            encoded = name.encode("ascii")[:31]
            stream.write(encoded + b"\0" * (32 - len(encoded)))
            stream.write(struct.pack("<f3I", duration, loop, first_track,
                                     track_count))

        for joint, kind, first_segment, segment_count in tracks:
            stream.write(struct.pack("<HH2I", joint, kind, first_segment,
                                     segment_count))

        for frame, duration, base, target, rate_base, rate_target, kind in segments:
            stream.write(struct.pack("<6fI", frame, duration, base, target,
                                     rate_base, rate_target, kind))

    print(f"wrote {output} ({output.stat().st_size} bytes): "
          f"{len(joints)} joints, {len(triangles)} triangles, "
          f"{len(textures)} textures, {len(animations)} animations, "
          f"{len(tracks)} tracks, {len(segments)} interpolation segments, "
          f"{len(effect_textures)} Falcon Punch effect frames, "
          f"{len(kick_effect_textures)} Falcon Kick effect frames")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("assets_root", type=Path)
    parser.add_argument("output", type=Path)
    args = parser.parse_args()
    write_blob(args.assets_root.resolve(), args.output.resolve())


if __name__ == "__main__":
    main()
