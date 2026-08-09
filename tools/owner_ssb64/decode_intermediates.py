#!/usr/bin/env python3
"""Decode Falcon's raw owner-cache relocs into bake_falcon_runtime inputs.

This is intentionally a metadata-only recipe.  It contains reloc IDs,
structure offsets, and material/palette offsets, but no extracted game bytes.
All emitted JSON/bin files are owner-ROM-derived cache data and must live
outside the source tree.
"""

from __future__ import annotations

import argparse
import json
import shutil
import struct
from pathlib import Path

import build_cache


MODEL_ID = 332
MODEL_JOINT_TREE = 0x3BE0
MODEL_JOINT_COUNT = 26
MOBJ_SIZE = 0x78
TEXTURE_DIMENSIONS = {
    0xAF30: (16, 8), 0xAF78: (32, 32), 0xB518: (16, 8), 0xB5D8: (32, 56),
    0xB750: (32, 32), 0xB980: (32, 32), 0xBCE0: (16, 16), 0xBDB8: (16, 16),
    0xBE40: (16, 8), 0xBF70: (16, 16), 0xBFF8: (16, 4), 0xC048: (16, 8),
    0xC0E0: (16, 8), 0xC128: (32, 16), 0xC230: (16, 16), 0xC358: (16, 24),
    0xC420: (16, 8), 0xC508: (16, 8), 0xBBB0: (32, 16), 0xB270: (32, 32),
}

# (reloc id, canonical output name).  The binary headers contain only a
# pointer table, so the joint-table length is deliberately explicit metadata.
ANIM_SPECS = (
    (1512, "Wait", 25), (1513, "Walk1", 25), (1514, "Walk2", 25),
    (1515, "Walk3", 25), (1517, "Dash", 25),
    (1518, "Run", 25), (1519, "RunBrake", 25), (1520, "Turn", 25),
    (1521, "TurnRun", 26), (1522, "JumpF", 25), (1523, "JumpB", 26),
    (1524, "JumpAerialF", 25), (1525, "JumpAerialB", 26), (1526, "Fall", 25),
    (1527, "FallAerial", 25), (1554, "FallSpecial", 25), (1528, "Crouch_kneebend", 25),
    (1529, "CrouchIdle", 25), (1530, "CrouchEnd", 25),
    (1531, "LandingAirX", 25), (1516, "WalkEnd", 25), (1619, "Jab1", 25),
    (1628, "AttackS3", 25), (1638, "AttackAirN", 25), (1639, "AttackAirF", 25),
    (1640, "AttackAirB", 25), (1642, "AttackAirD", 25),
    (1652, "FalconPunchGround", 26), (1653, "FalconPunchAir", 25),
    (1654, "DownSpecial", 26), (1655, "VelocityXDownSpecialAir", 26),
    (1656, "LandingDownSpecial", 26), (1657, "DownSpecialAir", 26),
    (1658, "FalconDive", 26), (1659, "CatchingEnemyWhileDiving", 26),
    (1660, "FalconDiveEnd1", 26), (1661, "FalconDiveEnd2", 26),
)

# MObjSub locations/palette locations for costume 0, in the CaptainModel
# reloc. None means a direct RGBA material. This table was transcribed from
# the public BattleShip/SmashBrosDecomp type/reloc map; values are offsets,
# never palette or pixel bytes.
MATERIAL_RECIPE = (
    (), ((0xCB0, 0xB248), (0xD28, 0xB248)),
    ((0x2D8, 0xB248), (0x350, 0xB248), (0x3C8, 0xAF08), (0x440, 0xAF08), (0x4B8, 0xAF08)),
    (), ((0x710, None),), ((0x530, 0xAF08),),
    ((0x5A8, 0xBD90), (0x620, 0xB958), (0x698, 0xC0B8)), (),
    ((0x788, 0xB958), (0x800, None), (0x878, 0xB5B0), (0x8F0, 0xB4F0), (0x968, 0xB4F0)), (),
    ((0xBC0, None), (0xC38, 0xC4E0)), ((0x9E0, 0xAF08),),
    ((0xA58, 0xBD90), (0xAD0, 0xB958), (0xB48, 0xC0B8)), (), ((0xDA0, 0xB248),), (),
    ((0xF80, None),), ((0xE90, 0xC330), (0xF08, None),), (), ((0xE18, 0xB958),), (),
    ((0x1160, None),), ((0x1070, 0xC330), (0x10E8, None),), (), ((0x0FF8, 0xB958),), (),
)

TRACK_NAMES = ("RotX", "RotY", "RotZ", "TraI", "TraX", "TraY", "TraZ", "ScaX", "ScaY", "ScaZ")
OP_NAMES = {
    0: "End", 1: "Block", 2: "SetValBlock", 3: "SetVal", 4: "SetValRateBlock",
    5: "SetValRate", 6: "SetTargetRate", 7: "SetVal0RateBlock", 8: "SetVal0Rate",
    9: "SetValAfterBlock", 10: "SetValAfter", 13: "Loop", 14: "SetFlags",
}
OP_PAYLOAD_WORDS = {2: 1, 3: 1, 4: 2, 5: 2, 6: 1, 7: 1, 8: 1, 9: 1, 10: 1}
OPNAMES = {
    0x01: "G_VTX", 0x05: "G_TRI1", 0x06: "G_TRI2", 0xD7: "G_TEXTURE",
    0xD9: "G_GEOMETRYMODE", 0xDB: "G_MOVEWORD", 0xDE: "G_DL", 0xDF: "G_ENDDL",
    0xE2: "G_SETOTHERMODE_L", 0xE3: "G_SETOTHERMODE_H", 0xE6: "G_RDPLOADSYNC",
    0xE7: "G_RDPPIPESYNC", 0xE8: "G_RDPTILESYNC", 0xF0: "G_LOADTLUT",
    0xF2: "G_SETTILESIZE", 0xF3: "G_LOADBLOCK", 0xF5: "G_SETTILE",
    0xF9: "G_SETBLENDCOLOR", 0xFC: "G_SETCOMBINE", 0xFD: "G_SETTIMG",
}
IM_FMT = {0: "RGBA", 2: "CI", 3: "IA", 4: "I"}
IM_SIZ = {0: 4, 1: 8, 2: 16, 3: 32}


def _token_offset(word: int) -> int | None:
    """Resolve a same-reloc pointer token, never a segmented N64 address."""
    # Internal reloc-chain links occupy the high 16 bits and can themselves
    # begin with 0x0E. Only 0x0E00xxxx is the fixed material-DL segment.
    if word == 0 or word >> 16 == 0x0E00:
        return None
    offset = (word & 0xFFFF) * 4
    return offset if offset else None


def _s16(data: bytes, offset: int) -> int:
    return struct.unpack_from(">h", data, offset)[0]


def _u16(data: bytes, offset: int) -> int:
    return struct.unpack_from(">H", data, offset)[0]


def _rgba16_to_argb(value: int) -> int:
    r = ((value >> 11) & 31) * 255 // 31
    g = ((value >> 6) & 31) * 255 // 31
    b = ((value >> 1) & 31) * 255 // 31
    return ((255 if value & 1 else 0) << 24) | (r << 16) | (g << 8) | b


def _mobj_primary(raw: bytes, offset: int) -> int:
    # SYColorPack is byte order RGBA in the serialized N64 data.  The source
    # material animation may subsequently tint this value; retaining the raw
    # default is preferable to baking a ROM-derived literal into this recipe.
    red, green, blue, alpha = raw[offset + 0x50:offset + 0x54]
    return (alpha << 24) | (red << 16) | (green << 8) | blue


def _rgba_word_to_argb(value: int) -> int:
    return ((value & 0xFF) << 24) | (value >> 8)


def _first_costume_primcolor(raw: bytes, offset: int) -> int | None:
    """Resolve costume-0's first material-animation primary-color target."""
    cursor = offset
    for _ in range(256):
        if cursor + 4 > len(raw):
            return None
        command = struct.unpack_from(">I", raw, cursor)[0]
        cursor += 4
        opcode = command >> 25
        flags = (command >> 15) & 0x3FF
        if opcode == 0:
            return None
        if opcode in (1, 13):
            cursor += 4
        elif opcode in (3, 4, 8, 9, 10, 11):
            cursor += 4 * flags.bit_count()
        elif opcode in (5, 6):
            cursor += 8 * flags.bit_count()
        elif opcode == 7:
            cursor += 4 * flags.bit_count()
        elif opcode in (18, 19, 20, 21):
            for track in range(5):
                if flags & (1 << track):
                    if cursor + 4 > len(raw):
                        return None
                    value = struct.unpack_from(">I", raw, cursor)[0]
                    cursor += 4
                    if track == 0:
                        return _rgba_word_to_argb(value)
        elif opcode == 22:
            cursor += 4 * (flags & 0x1F).bit_count()
        if cursor > len(raw):
            return None
    return None


def _decode_vertex(raw: bytes, offset: int) -> dict:
    x, y, z, flag, u, v, r, g, b, a = struct.unpack_from(">hhhHhh4B", raw, offset)
    return {"pos": [x, y, z], "flag": flag, "uv_raw": [u, v],
            "uv_texels": [u / 32.0, v / 32.0], "rgba_or_normal": [r, g, b, a]}


def _decode_dl(raw: bytes, offset: int) -> list[dict]:
    """Decode the F3DEX2 subset consumed by bake_falcon_runtime.py."""
    ops, cursor, current_vtx = [], offset, None
    for _ in range(4096):
        if cursor + 8 > len(raw):
            raise ValueError(f"display list at {offset:#x} ran past model EOF")
        w0, w1 = struct.unpack_from(">II", raw, cursor)
        cursor += 8
        opcode = w0 >> 24
        op = {"op": OPNAMES.get(opcode, f"UNK_0x{opcode:02X}"), "opcode": opcode, "w0": w0, "w1": w1, "w1_sym": None}
        ptr = _token_offset(w1)
        if opcode == 0x01:
            count = (w0 >> 12) & 0xFF
            current_vtx = f"vtx_{ptr:04X}" if ptr is not None else None
            op.update(numv=count, v0=((w0 >> 1) & 0x7F) - count, vbuf=current_vtx)
        elif opcode == 0x05:
            op.update(indices=[((w1 >> shift) & 0xFF) // 2 for shift in (16, 8, 0)], vbuf=current_vtx)
        elif opcode == 0x06:
            op.update(vbuf=current_vtx)
        elif opcode == 0xFD:
            size = (w0 >> 19) & 3
            fmt = (w0 >> 21) & 7
            op.update(fmt=IM_FMT.get(fmt, fmt), siz_bpp=IM_SIZ.get(size, size), width=(w0 & 0xFFF) + 1,
                      image=f"image_{ptr:04X}" if ptr is not None else None)
        elif opcode == 0xF5:
            size = (w0 >> 19) & 3
            fmt = (w0 >> 21) & 7
            op.update(fmt=IM_FMT.get(fmt, fmt), siz_bpp=IM_SIZ.get(size, size), line=(w0 >> 9) & 0x1FF,
                      tmem=w0 & 0x1FF, tile=(w1 >> 24) & 7, palette=(w1 >> 20) & 0xF)
        elif opcode == 0xF2:
            uls, ult, lrs, lrt = (w0 >> 12) & 0xFFF, w0 & 0xFFF, (w1 >> 12) & 0xFFF, w1 & 0xFFF
            op.update(uls=uls / 4.0, ult=ult / 4.0, lrs=lrs / 4.0, lrt=lrt / 4.0,
                      width_px=(lrs - uls) // 4 + 1, height_px=(lrt - ult) // 4 + 1)
        elif opcode == 0xF3:
            op.update(texels=((w1 >> 12) & 0xFFF) + 1)
        elif opcode == 0xF0:
            op.update(palette_entries=((w1 >> 14) & 0x3FF) + 1)
        elif opcode == 0xDE:
            op.update(target=f"dl_{ptr:04X}" if ptr is not None else None)
        ops.append(op)
        if opcode == 0xDF:
            return ops
    raise ValueError(f"display list at {offset:#x} lacks G_ENDDL")


def _write_model(raw: bytes, output: Path) -> None:
    model_dir, dl_dir, vtx_dir, tex_dir = output / "model", output / "model" / "dl", output / "model" / "vtx", output / "textures"
    dl_dir.mkdir(parents=True); vtx_dir.mkdir(parents=True); tex_dir.mkdir(parents=True)
    joints, stack, dls = [], {}, {}
    vtx_counts: dict[int, int] = {}
    for index in range(MODEL_JOINT_COUNT):
        off = MODEL_JOINT_TREE + index * 44
        depth, dl_token, *floats = struct.unpack_from(">II9f", raw, off)
        dl_offset = _token_offset(dl_token)
        parent = stack.get(depth - 1) if depth else None
        entry = {"index": index, "depth": depth, "parent": parent,
                 "dl": f"dl_{dl_offset:04X}" if dl_offset is not None else None,
                 "translate": floats[:3], "rotate_rad": floats[3:6], "scale": floats[6:9]}
        stack[depth] = index
        joints.append(entry)
        if dl_offset is not None and dl_offset not in dls:
            dls[dl_offset] = _decode_dl(raw, dl_offset)
    for off, ops in dls.items():
        for op in ops:
            if op["op"] == "G_VTX" and op.get("vbuf"):
                vtx_offset = int(op["vbuf"].rsplit("_", 1)[1], 16)
                vtx_counts[vtx_offset] = max(vtx_counts.get(vtx_offset, 0), int(op["numv"]))
        (dl_dir / f"dl_{off:04X}.json").write_text(json.dumps(ops, indent=1) + "\n", encoding="utf-8")
    for off, count in vtx_counts.items():
        if off + count * 16 > len(raw):
            raise ValueError(f"vertex run {off:#x} exceeds CaptainModel")
        vertices = [_decode_vertex(raw, off + index * 16) for index in range(count)]
        (vtx_dir / f"vtx_{off:04X}.json").write_text(json.dumps(vertices, indent=1) + "\n", encoding="utf-8")

    # Feed the baker the direct material metadata. Palette values are read now
    # from the owner cache, while the recipe carries only palette offsets.
    palettes, joint_materials = {}, []
    material_dispatch = MODEL_JOINT_TREE + 0x4B0
    for joint_index, material_list in enumerate(MATERIAL_RECIPE):
        entries = []
        dispatch_word = struct.unpack_from(">I", raw, material_dispatch + joint_index * 4)[0]
        material_anims = _token_offset(dispatch_word)
        for material_index, (mobj_offset, palette_offset) in enumerate(material_list):
            if mobj_offset + MOBJ_SIZE > len(raw):
                raise ValueError(f"MObjSub {mobj_offset:#x} exceeds CaptainModel")
            fmt = "CI" if raw[mobj_offset + 2] == 2 else "RGBA"
            palette_name = None
            if palette_offset is not None:
                palette_name = f"palette_{palette_offset:04X}"
                palette = [_rgba16_to_argb(_u16(raw, palette_offset + item * 2)) for item in range(16)]
                palettes.setdefault(palette_name, palette)
                # Some display lists load a palette through its image symbol.
                palettes.setdefault(f"image_{palette_offset:04X}", palette)
            entry = {"name": f"mobj_{mobj_offset:04X}", "format": fmt,
                     "palette_symbol": palette_name, "primary_argb": _mobj_primary(raw, mobj_offset)}
            if material_anims is not None:
                pointer_at = material_anims + material_index * 4
                if pointer_at + 4 <= len(raw):
                    script_offset = _token_offset(struct.unpack_from(">I", raw, pointer_at)[0])
                    if script_offset is not None:
                        default_primary = _first_costume_primcolor(raw, script_offset)
                        if default_primary is not None:
                            entry["default_primary_argb"] = default_primary
            entries.append(entry)
        joint_materials.append(entries)
    texture_dimensions: dict[str, list[int]] = {}
    # Fighter DL tile windows crop/expand the underlying image, so their
    # G_SETTILESIZE values are not the source texture dimensions. The known
    # CI4 declarations are recipe metadata; read exactly their owner-ROM bytes.
    for image_off, (width, height) in TEXTURE_DIMENSIONS.items():
        image = f"image_{image_off:04X}"
        size = width * height // 2
        if image_off + size > len(raw):
            raise ValueError(f"texture {image_off:#x} exceeds CaptainModel")
        (tex_dir / f"{image}.bin").write_bytes(raw[image_off:image_off + size])
        texture_dimensions[image] = [width, height]
    (model_dir / "captain_model.json").write_text(json.dumps({"trees": {"dCaptainModel_JointTree": {"joints": joints}}}, indent=1) + "\n", encoding="utf-8")
    (tex_dir / "material_bindings.json").write_text(json.dumps({"version": 1, "costume_index": 0, "joint_materials": joint_materials, "palettes_argb": palettes, "texture_dimensions": texture_dimensions}, indent=1) + "\n", encoding="utf-8")


def _decode_script(raw: bytes, start: int) -> list[dict]:
    cursor, ops = start, []
    for _ in range(4096):
        if cursor + 2 > len(raw):
            raise ValueError(f"animation script at {start:#x} ran past EOF")
        command = _u16(raw, cursor); cursor += 2
        opcode, flags, toggle = command >> 11, (command >> 1) & 0x3FF, command & 1
        if opcode == 0:
            ops.append({"op": "End"}); return ops
        if opcode == 13:
            if cursor + 2 > len(raw): raise ValueError("truncated Figatree loop")
            # The target is earlier in this same script. Bytes after the loop
            # are normally the following joint's script, but a few source
            # arrays retain an explicit End sentinel after their Loop.
            ops.append({"op": "Loop", "cmd_word": command, "offset": _s16(raw, cursor)})
            cursor += 2
            if cursor + 2 <= len(raw) and _u16(raw, cursor) == 0:
                ops.append({"op": "End"})
            return ops
        name = OP_NAMES.get(opcode)
        if name is None:
            raise ValueError(f"unsupported Figatree opcode {opcode} at {cursor - 2:#x}")
        duration = _u16(raw, cursor) if toggle else None
        if toggle: cursor += 2
        if opcode == 1:
            ops.append({"op": name, "toggle": toggle, "dur": duration, "flags_raw": flags}); continue
        if opcode == 14:
            ops.append({"op": name, "toggle": toggle, "dur": duration, "anim_flags": flags}); continue
        tracks = [track for bit, track in enumerate(TRACK_NAMES) if flags & (1 << bit)]
        payload = {}
        words = OP_PAYLOAD_WORDS[opcode]
        for track in tracks:
            values = []
            for _ in range(words):
                if cursor + 2 > len(raw): raise ValueError("truncated Figatree payload")
                values.append(_s16(raw, cursor)); cursor += 2
            payload[track] = values if words == 2 else values[0]
        ops.append({"op": name, "toggle": toggle, "dur": duration, "tracks": tracks, "payload": payload})
    raise ValueError(f"animation script at {start:#x} has no End")


def _write_anims(reloc_dir: Path, output: Path) -> None:
    anim_dir = output / "anim"; anim_dir.mkdir(parents=True)
    manifest = []
    for file_id, name, count in ANIM_SPECS:
        path = next(reloc_dir.glob(f"{file_id:04d}_*.bin"))
        raw = path.read_bytes()
        joints = []
        for slot in range(count):
            target = _token_offset(struct.unpack_from(">I", raw, slot * 4)[0])
            if target is None:
                joints.append({"joint_slot": slot, "joint_id": slot + 1, "script": None})
            else:
                joints.append({"joint_slot": slot, "joint_id": slot + 1, "array_symbol": f"script_{target:04X}", "ops": _decode_script(raw, target)})
        data = {"file_id": file_id, "source_name": f"reloc_{file_id}", "canonical_name": name,
                "note": None, "joints_table": "raw_header", "joint_count": count, "joints": joints}
        filename = f"{name}.json"
        (anim_dir / filename).write_text(json.dumps(data, indent=1) + "\n", encoding="utf-8")
        manifest.append({"file_id": file_id, "source_name": f"reloc_{file_id}", "canonical_name": name,
                         "note": None, "joint_count": count, "output": filename, "status": "ok"})
    (anim_dir / "anim_manifest.json").write_text(json.dumps(manifest, indent=1) + "\n", encoding="utf-8")


def materialize(reloc_cache: Path, output: Path) -> None:
    build_cache.verify_cache(reloc_cache)
    source_root = Path(__file__).resolve().parents[2]
    resolved = output.resolve()
    if resolved == source_root or source_root in resolved.parents:
        raise ValueError("decoded owner assets must live outside the source tree")
    if output.exists():
        raise ValueError(f"output already exists: {output}")
    reloc_dir = reloc_cache / "reloc"
    model_path = next(reloc_dir.glob("0332_*.bin"))
    output.mkdir(parents=True)
    try:
        _write_model(model_path.read_bytes(), output)
        _write_anims(reloc_dir, output)
        effects = output / "effects"; effects.mkdir()
        shutil.copyfile(next(reloc_dir.glob("0333_*.bin")), effects / "CaptainSpecial3.bin")
        shutil.copyfile(next(reloc_dir.glob("0350_*.bin")), effects / "CaptainSpecial2.bin")
    except Exception:
        shutil.rmtree(output, ignore_errors=True)
        raise


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--reloc-cache", required=True, type=Path)
    parser.add_argument("--out", required=True, type=Path)
    args = parser.parse_args()
    try:
        materialize(args.reloc_cache.resolve(), args.out)
    except (OSError, ValueError, json.JSONDecodeError) as exc:
        parser.exit(1, f"owner-ROM decode error: {exc}\n")
    print(args.out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
