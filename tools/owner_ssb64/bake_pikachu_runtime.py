#!/usr/bin/env python3
"""Bake owner-ROM Pikachu intermediates into the shared runtime mesh format.

Geometry, material-selected CI4 pixels, palettes, and Figatree streams come
from ``pikachu_owner.py``. No derived bytes are stored in source.
"""

from __future__ import annotations

import argparse
import copy
import json
import struct
import sys
from pathlib import Path

TOOLS_ROOT = Path(__file__).resolve().parent.parent
if str(TOOLS_ROOT) not in sys.path:
    sys.path.insert(0, str(TOOLS_ROOT))

import bake_falcon_runtime as common


MAGIC = common.MAGIC
VERSION = common.VERSION
PIKACHU_RUNTIME_VERSION = 8
LOOPS = {"Idle", "Walk1", "Walk2", "Walk3", "Run", "CrouchIdle"}
BODY_COLORS = (0xFFFFD933, 0xFFE8A828, 0xFFFFD933, 0xFFC8C828)
ACCESSORY_COLORS = (0x00000000, 0xFFFF5B79, 0xFFFFFFFF, 0xFFB1FF24)


def load(path: Path):
    return json.loads(path.read_text(encoding="utf-8"))


class Solids:
    def __init__(self):
        self.records: list[tuple[str, int, int, bytes]] = []
        self.ids: dict[int, int] = {}

    def get(self, argb: int) -> int:
        if argb not in self.ids:
            self.ids[argb] = len(self.records)
            self.records.append((f"solid_{argb:08x}", 1, 1,
                                 struct.pack("<I", argb)))
        return self.ids[argb]

    def ci4(self, key: tuple, name: str, raw: bytes, palette: list[int],
            width: int, height: int) -> int:
        record_key = ("ci4",) + key
        if record_key in self.ids:
            return self.ids[record_key]
        needed = (width * height + 1) // 2
        if width <= 0 or height <= 0 or len(raw) < needed or len(palette) < 16:
            raise ValueError(f"invalid CI4 material {name}")
        pixels = bytearray()
        for pixel in range(width * height):
            value = raw[pixel // 2]
            index = value >> 4 if pixel % 2 == 0 else value & 0x0F
            pixels += struct.pack("<I", int(palette[index]))
        self.ids[record_key] = len(self.records)
        self.records.append((name, width, height, bytes(pixels)))
        return self.ids[record_key]


def storage_bytes(model_dir: Path, model: dict, offset: int,
                  size: int) -> bytes:
    for region in model["texture_storage"]:
        start = int(region["offset"])
        end = start + int(region["size"])
        if start <= offset and offset + size <= end:
            path = model_dir / "texture_storage" / (
                f"{start:04x}_{region['name']}.bin")
            raw = path.read_bytes()
            relative = offset - start
            return raw[relative:relative + size]
    raise ValueError(f"texture range 0x{offset:X}+0x{size:X} is not exported")


def wrap_axis(values: list[float], extent: int) -> list[float]:
    """Put one triangle's repeated N64 tile coordinates in one local period."""
    if extent <= 0:
        return values
    base = values[0]
    adjusted = [base]
    for value in values[1:]:
        adjusted.append(value + round((base - value) / extent) * extent)
    center = sum(adjusted) / len(adjusted)
    shift = -int(center // extent) * extent
    return [value + shift for value in adjusted]


def textured_vertices(vertices: list[dict], width: int, height: int,
                      tile_origin: tuple[float, float] | None,
                      source_u_scale: float) -> list[dict]:
    result = [copy.deepcopy(vertex) for vertex in vertices]
    origin_u, origin_v = tile_origin or (0.0, 0.0)
    us = [(float(vertex["uv_texels"][0]) - origin_u) / source_u_scale
          for vertex in result]
    vs = [float(vertex["uv_texels"][1]) - origin_v for vertex in result]
    us = wrap_axis(us, width)
    vs = wrap_axis(vs, height)
    for vertex, u, v in zip(result, us, vs):
        vertex["uv_texels"] = [u, v]
    return result


def triangles_from_ops(model_dir: Path, model: dict, ops: list[dict],
                       joint: int, color: int, materials: list[dict],
                       catalog: Solids,
                       slots: list[tuple[int, dict] | None]) -> list[dict]:
    triangles: list[dict] = []
    texture = catalog.get(color)
    current_material = None
    current_image = None
    tile_origin = None
    texture_width = texture_height = 1
    source_u_scale = 1.0
    vertex_cache: dict[str, list[dict]] = {}

    def bind_ci4(image_offset: int) -> None:
        nonlocal texture, current_image, texture_width, texture_height
        nonlocal source_u_scale
        if current_material is None:
            raise ValueError(f"joint {joint}: image without material")
        palette = current_material.get("selected_palette_argb")
        palette_offset = current_material.get("selected_palette_offset")
        if palette is None or palette_offset is None:
            raise ValueError(f"joint {joint}: unresolved CI4 palette")
        # SSB64's fighter MObj records use a 16-bit load image for a CI4
        # sampled tile. The stored pixel width is therefore half the MObj
        # load width, while its height is unchanged.
        texture_width = max(1, int(current_material["source_width"]) // 2)
        texture_height = max(1, int(current_material["source_height"]))
        needed = (texture_width * texture_height + 1) // 2
        raw = storage_bytes(model_dir, model, image_offset, needed)
        texture = catalog.ci4(
            (image_offset, int(palette_offset), texture_width, texture_height),
            f"ci4_{image_offset:04x}_{int(palette_offset):04x}",
            raw, palette, texture_width, texture_height)
        current_image = image_offset
        source_u_scale = 2.0

    for op in ops:
        name = op.get("op")
        if (name == "G_DL" and isinstance(op.get("w1"), int) and
                int(op["w1"]) >> 24 == 0x0E):
            material_index = (int(op["w1"]) & 0x00FFFFFF) // 8
            if material_index >= len(materials):
                raise ValueError(f"joint {joint}: missing material {material_index}")
            current_material = materials[material_index]
            if int(current_material["format"]) == 2:
                image_offset = current_material.get("selected_sprite_offset")
                if image_offset is not None:
                    bind_ci4(int(image_offset))
            else:
                texture = catalog.get(int(current_material["primary_argb"]))
                current_image = None
                texture_width = texture_height = 1
                source_u_scale = 1.0
        elif name == "G_SETTILESIZE":
            tile_origin = (float(op.get("uls", 0.0)),
                           float(op.get("ult", 0.0)))
        elif (name == "G_SETTIMG" and current_material is not None and
              int(current_material["format"]) == 2):
            image_name = op.get("image")
            if image_name and image_name.startswith("image_"):
                bind_ci4(int(image_name[6:], 16))
        elif name == "G_VTX":
            symbol = op.get("vbuf")
            if not symbol:
                continue
            if symbol not in vertex_cache:
                vertex_cache[symbol] = load(model_dir / "vtx" /
                                            f"{symbol}.json")
            vertices = vertex_cache[symbol]
            v0 = int(op.get("v0", 0))
            count = min(int(op.get("numv", len(vertices))), len(vertices))
            for index in range(count):
                if v0 + index < len(slots):
                    slots[v0 + index] = (joint, copy.deepcopy(vertices[index]))
        elif name == "UNK_0x02":
            where = (int(op["w0"]) >> 16) & 0xFF
            slot = (int(op["w0"]) & 0xFFFF) >> 1
            if slot >= len(slots) or slots[slot] is None:
                raise ValueError(f"joint {joint}: modify unloaded vertex {slot}")
            _owner, vertex = slots[slot]
            value = int(op["w1"])
            if where == 0x10:
                vertex["rgba_or_normal"] = [
                    (value >> shift) & 0xFF for shift in (24, 16, 8, 0)]
            elif where == 0x14:
                raw = [struct.unpack(">h", struct.pack(">H", part))[0]
                       for part in ((value >> 16) & 0xFFFF, value & 0xFFFF)]
                vertex["uv_raw"] = raw
                vertex["uv_texels"] = [component / 32.0 for component in raw]
            elif where not in (0x18, 0x1C):
                raise ValueError(
                    f"joint {joint}: unsupported G_MODIFYVTX field {where:#x}")
        elif name in ("G_TRI1", "G_TRI2"):
            sets = ([common.decode_tri_word(int(op["w0"]))]
                    if name == "G_TRI1" else
                    [common.decode_tri_word(int(op["w0"])),
                     common.decode_tri_word(int(op["w1"]))])
            for indices in sets:
                cached = [slots[index] if index < len(slots) else None
                          for index in indices]
                if any(vertex is None for vertex in cached):
                    raise ValueError(f"joint {joint}: unloaded vertex {indices}")
                triangles.append({
                    "joints": [int(entry[0]) for entry in cached],
                    "texture": texture,
                    "vertices": (textured_vertices(
                        [entry[1] for entry in cached], texture_width,
                        texture_height, tile_origin, source_u_scale)
                        if current_material is not None and
                           int(current_material["format"]) == 2 and
                           current_image is not None else
                        [copy.deepcopy(entry[1]) for entry in cached]),
                })
    return triangles


def collect_model(root: Path, costume: int):
    if costume not in range(4):
        raise ValueError("costume must be 0..3")
    model_dir = root / "model"
    data = load(model_dir / "pikachu_model.json")
    joints = data["joints"]
    if len(joints) != 27:
        raise ValueError(f"expected 27 Pikachu joints, found {len(joints)}")
    catalog = Solids()
    triangles: list[dict] = []
    ranges: list[tuple[int, int]] = []
    slots: list[tuple[int, dict] | None] = [None] * 32
    material_lists = {int(entry["joint"]): entry["materials"]
                      for entry in data["materials"]}
    for joint in joints:
        first = len(triangles)
        offset = joint.get("dl_offset")
        if offset is not None:
            ops = load(model_dir / "dl" / f"dl_{int(offset):04x}.json")
            triangles.extend(triangles_from_ops(
                model_dir, data, ops, int(joint["index"]),
                BODY_COLORS[costume],
                material_lists.get(int(joint["index"]), []), catalog, slots))
        if costume and int(joint["index"]) == int(data["accessory"]["joint"]):
            accessory_slots: list[tuple[int, dict] | None] = [None] * 32
            triangles.extend(triangles_from_ops(
                model_dir, data, data["accessory"]["display_list"],
                int(joint["index"]), ACCESSORY_COLORS[costume],
                data["accessory"]["materials"], catalog, accessory_slots))
        ranges.append((first, len(triangles) - first))
    return joints, ranges, triangles, catalog.records


def collect_animations(root: Path):
    entries = load(root / "animations" / "manifest.json")
    animations, tracks, segments = [], [], []
    for entry in entries:
        data = load(root / "animations" / entry["output"])
        name = data["canonical_name"]
        first_track = len(tracks)
        duration = 0.0
        auxiliary = bool(data.get("has_auxiliary_root"))
        for joint in data.get("joints", []):
            if joint is None or not joint.get("ops"):
                continue
            slot = int(joint["joint_slot"])
            if auxiliary:
                joint_index = 0xFFFF if slot == 0 else slot - 1
            else:
                joint_index = slot
            if joint_index != 0xFFFF and not 0 <= joint_index < 27:
                continue
            compiled, joint_duration = common._track_segments(joint)
            duration = max(duration, joint_duration)
            for track_name, values in compiled.items():
                if track_name not in common.TRACK_IDS or not values:
                    continue
                first_segment = len(segments)
                segments.extend(values)
                tracks.append((joint_index, common.TRACK_IDS[track_name],
                               first_segment, len(values)))
        animations.append((name, max(duration, 1.0),
                           1 if name in LOOPS else 0,
                           first_track, len(tracks) - first_track))
    return animations, tracks, segments


def rgba5551(value: int) -> int:
    """Expand the owner N64 RGBA5551 entry to the runtime ARGB convention."""
    red = ((value >> 11) & 0x1F) * 255 // 31
    green = ((value >> 6) & 0x1F) * 255 // 31
    blue = ((value >> 1) & 0x1F) * 255 // 31
    alpha = 0xFF if value & 1 else 0
    return (alpha << 24) | (red << 16) | (green << 8) | blue


def effect_ci4(raw: bytes, palette_offset: int, image_offset: int,
               name: str) -> tuple[str, int, int, bytes]:
    """Bake one 32x32 owner CI4 special-effect card without source payloads."""
    if palette_offset + 32 > len(raw) or image_offset + 512 > len(raw):
        raise ValueError(f"truncated owner special-effect card {name}")
    palette = [rgba5551(struct.unpack_from(">H", raw, palette_offset + i * 2)[0])
               for i in range(16)]
    pixels = bytearray()
    for packed in raw[image_offset:image_offset + 512]:
        pixels += struct.pack("<I", palette[packed >> 4])
        pixels += struct.pack("<I", palette[packed & 0x0F])
    return name, 32, 32, bytes(pixels)


def effect_ia8(raw: bytes, image_offset: int, name: str) -> tuple[str, int, int, bytes]:
    """Bake one source-owned 32x32 IA8 Thunder Shock card.

    The high nibble is intensity and the low nibble alpha.  Keeping both is
    important: Thunder Shock is an additive-looking translucent aura in the
    original, not an opaque yellow replacement card.
    """
    needed = 32 * 32
    if image_offset < 0 or image_offset + needed > len(raw):
        raise ValueError(f"truncated owner IA8 special-effect card {name}")
    pixels = bytearray()
    for value in raw[image_offset:image_offset + needed]:
        intensity = (value >> 4) * 17
        alpha = (value & 0x0F) * 17
        pixels += struct.pack("<I", (alpha << 24) | (intensity << 16) |
                      (intensity << 8) | intensity)
    return name, 32, 32, bytes(pixels)


def effect_ia8_particle_env(raw: bytes, name: str) -> tuple[str, int, int, bytes]:
    """Bake script 0x74 texture 46 through its exact PRIM/ENV combiner.

    lbParticleDrawTextures uses ``(PRIM - ENV) * TEXEL0 + ENV`` for both
    cycles when ``lbpEnvColor`` is set.  ThunderAmp sets PRIM to white/a200
    and ENV to blue (0,100,255,a0), then alpha-compares against 8.  A naive
    IA8 grayscale bake makes its soft blue field black, which is visibly
    wrong even though the ROM frame bytes are correct.
    """
    needed = 64 * 64
    if len(raw) != needed:
        raise ValueError(f"invalid owner ThunderAmp texture length for {name}")
    pixels = bytearray()
    for value in raw:
        intensity = (value >> 4) * 17
        tex_alpha = (value & 0x0F) * 17
        red = intensity
        green = 100 + (155 * intensity + 127) // 255
        blue = 255
        # This is the alpha half of the same source combine LERP: with
        # PRIM.a=200 and ENV.a=0 it is (200 - 0) * TEXEL0.a + 0.  Do not gate
        # it by intensity: IA8's low-intensity/high-alpha texels are genuine
        # source data. Their presentation is handled by the XLU blend mode,
        # rather than deleting them while baking the immutable owner card.
        alpha = (200 * tex_alpha + 127) // 255
        # script_116 leaves ALPHABLEND disabled, so the N64 threshold compare
        # rejects combined alpha at or below the blend color (8).
        if alpha <= 8:
            alpha = 0
        pixels += struct.pack("<I", (alpha << 24) | (red << 16) |
                      (green << 8) | blue)
    return name, 64, 64, bytes(pixels)


def collect_effect_textures(root: Path) -> list[tuple[str, int, int, bytes]]:
    """Return source-owned Jolt, Thunder, Thunder Shock and ThunderAmp cards.

    Reloc 342's ThunderJolt MObj uses its 0x1C70 palette with the two 32x32
    cards at 0x1C98/0x1EA0.  Reloc 347's first MObj is the three-frame 32x32
    Thunder cycle using palette 0x0008 and images 0x0030/0x0238/0x0440.
    The renderer owns only the host-space card placement; every pixel here is
    selected directly from the verified owner-ROM intermediates.
    """
    effect_root = root / "effects"
    jolt = (effect_root / "PikachuSpecial3.bin").read_bytes()
    thunder = (effect_root / "PikachuSpecial2.bin").read_bytes()
    return [
        effect_ci4(jolt, 0x1C70, 0x1C98, "pikachu_jolt_0"),
        effect_ci4(jolt, 0x1C70, 0x1EA0, "pikachu_jolt_1"),
        effect_ci4(thunder, 0x0008, 0x0030, "pikachu_thunder_0"),
        effect_ci4(thunder, 0x0008, 0x0238, "pikachu_thunder_1"),
        effect_ci4(thunder, 0x0008, 0x0440, "pikachu_thunder_2"),
        # `ThunderShockMObjSub` in fid 347 uses these two IA8 cards in that
        # order (0x0D98 then 0x0990), switching them by its source material
        # timeline.  They are the owner-authored cards for the contact aura.
        effect_ia8(thunder, 0x0D98, "pikachu_thunder_shock_0"),
        effect_ia8(thunder, 0x0990, "pikachu_thunder_shock_1"),
        # nEFKindThunderAmp is generic particle script 0x74, texture 46.
        # These direct common-bank IA8 extracts are kept separate from the
        # Pikachu-owned ThunderShock MObj above: their size/timeline are
        # evaluated by the renderer from script_116 rather than treated as a
        # rotating contact-card surrogate.
        effect_ia8_particle_env((effect_root / "texture_storage" /
                                 "efcommon_46_thunder_amp_0.ia8").read_bytes(),
                                "pikachu_thunder_amp_0"),
        effect_ia8_particle_env((effect_root / "texture_storage" /
                                 "efcommon_46_thunder_amp_1.ia8").read_bytes(),
                                "pikachu_thunder_amp_1"),
        effect_ia8_particle_env((effect_root / "texture_storage" /
                                 "efcommon_46_thunder_amp_2.ia8").read_bytes(),
                                "pikachu_thunder_amp_2"),
    ]


def write_blob(root: Path, output: Path, costume: int) -> None:
    joints, ranges, triangles, textures = collect_model(root, costume)
    animations, tracks, segments = collect_animations(root)
    effect_first = len(textures)
    textures.extend(collect_effect_textures(root))
    output.parent.mkdir(parents=True, exist_ok=True)
    with output.open("wb") as stream:
        stream.write(MAGIC)
        stream.write(struct.pack("<9I", PIKACHU_RUNTIME_VERSION, len(joints), len(triangles),
                                 len(textures), len(animations), len(tracks),
                                 len(segments), effect_first,
                                 len(textures) - effect_first))
        for joint, (first, count) in zip(joints, ranges):
            parent = -1 if joint.get("parent") is None else int(joint["parent"])
            values = [float(value) for key in
                      ("translate", "rotate_rad", "scale")
                      for value in joint[key]]
            stream.write(struct.pack("<i9f2I", parent, *values, first, count))
        for triangle in triangles:
            stream.write(struct.pack("<4H", *triangle["joints"],
                                     triangle["texture"]))
            for vertex in triangle["vertices"]:
                stream.write(struct.pack("<5f", *[float(v) for v in
                    vertex["pos"] + vertex["uv_texels"]]))
        for _name, width, height, pixels in textures:
            stream.write(struct.pack("<HHI", width, height, len(pixels)))
            stream.write(pixels)
        for name, duration, loop, first, count in animations:
            encoded = name.encode("ascii")[:31]
            stream.write(encoded + b"\0" * (32 - len(encoded)))
            stream.write(struct.pack("<f3I", duration, loop, first, count))
        for joint, kind, first, count in tracks:
            stream.write(struct.pack("<HH2I", joint, kind, first, count))
        for frame, duration, base, target, rate0, rate1, kind in segments:
            stream.write(struct.pack("<6fI", frame, duration, base, target,
                                     rate0, rate1, kind))
    print(f"wrote {output}: costume {costume}, {len(joints)} joints, "
          f"{len(triangles)} triangles, {len(animations)} animations")


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("intermediate_root", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--costume", type=int, default=0)
    args = parser.parse_args()
    write_blob(args.intermediate_root.resolve(), args.output.resolve(),
               args.costume)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
