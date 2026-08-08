#!/usr/bin/env python3
"""Resolve Smash 64 Falcon's runtime material and palette indirection.

The publishable script contains no game data.  It reads the owner's local
SSB64 decomp/extraction, follows the per-joint MObjSub tables, decodes the
default-costume RGBA16 palettes, and writes an ignored JSON input for the
runtime baker.  It also recovers pixel blobs declared as u16 (several of the
model's CI4 images have misleading ``palette`` names in the decomp).
"""

from __future__ import annotations

import argparse
import json
import re
import struct
from pathlib import Path


SYMBOL_RE = r"dCaptainModel_\w+"


def declaration_bodies(source: str, c_type: str, stars: str = ""):
    pattern = re.compile(
        rf"(?m)^{re.escape(c_type)}\s+{re.escape(stars)}(\w+)\[\d+\]"
        rf"\s*=\s*\{{(.*?)^\}};",
        re.S | re.M,
    )
    return {match.group(1): match.group(2) for match in pattern.finditer(source)}


def pointer_entries(body: str) -> list[str | None]:
    return [
        match.group(1) if match.group(1) else None
        for match in re.finditer(rf"({SYMBOL_RE})|\bNULL\b", body)
    ]


def rgba16_to_argb(value: int) -> int:
    red = ((value >> 11) & 0x1F) * 255 // 31
    green = ((value >> 6) & 0x1F) * 255 // 31
    blue = ((value >> 1) & 0x1F) * 255 // 31
    alpha = 255 if value & 1 else 0
    return alpha << 24 | red << 16 | green << 8 | blue


def include_values(path: Path) -> list[int]:
    text = path.read_text(encoding="utf-8", errors="replace")
    return [int(value, 16) for value in re.findall(r"0x([0-9A-Fa-f]{1,4})", text)]


def parse_asset_declarations(source: str, build_dir: Path):
    declarations = {}
    pattern = re.compile(
        rf"(?m)^(u8|u16)\s+({SYMBOL_RE})\[(\d+)\]\s*=\s*\{{\s*"
        r"#include <CaptainModel/([\w.]+)>"
    )
    for match in pattern.finditer(source):
        kind, symbol, _count, filename = match.groups()
        path = build_dir / filename
        if not path.is_file():
            raise FileNotFoundError(f"missing extracted include for {symbol}: {path}")
        values = include_values(path)
        # Several reloc declarations retain stale splitter-era element counts
        # (Stock_tex is the clearest example).  The generated include is the
        # authoritative extracted byte/halfword stream.
        declarations[symbol] = (kind, values)
    return declarations


def parse_texture_dimensions(source: str) -> dict[str, tuple[int, int]]:
    pattern = re.compile(
        rf"/\*\s*@tex\s+fmt=\w+\s+dim=(\d+)x(\d+)[^*]*\*/\s*"
        rf"(?:u8|u16)\s+({SYMBOL_RE})\[",
        re.S,
    )
    return {
        match.group(3): (int(match.group(1)), int(match.group(2)))
        for match in pattern.finditer(source)
    }


def symbol_file_offset(symbol: str) -> int | None:
    relative = re.search(
        r"_0x([0-9A-Fa-f]+)(?:_post)?_sub_0x([0-9A-Fa-f]+)(?=_|$)",
        symbol,
    )
    if relative:
        return int(relative.group(1), 16) + int(relative.group(2), 16)
    matches = re.findall(r"_0x([0-9A-Fa-f]+)(?=_|$)", symbol)
    return int(matches[-1], 16) if matches else None


def declaration_bytes(kind: str, values: list[int]) -> bytes:
    if kind == "u8":
        return bytes(values)
    return b"".join(struct.pack(">H", value) for value in values)


def parse_materials(source: str):
    materials = {}
    pattern = re.compile(
        rf"(?m)^MObjSub\s+({SYMBOL_RE})\[1\]\s*=\s*\{{(.*?)^\}};",
        re.S | re.M,
    )
    for match in pattern.finditer(source):
        symbol, body = match.groups()
        pointers = re.findall(
            rf"\(void\*\*\)(0x00000000|{SYMBOL_RE})", body
        )
        formats = re.findall(r"G_IM_FMT_(\w+)", body)
        color = re.search(
            r"0x00022205,\s*\{\s*\{\s*"
            r"(0x[0-9A-Fa-f]+),\s*(0x[0-9A-Fa-f]+),\s*"
            r"(0x[0-9A-Fa-f]+),\s*(0x[0-9A-Fa-f]+)",
            body,
        )
        if len(pointers) < 2 or not formats or not color:
            raise ValueError(f"could not parse MObjSub {symbol}")
        palette_set = pointers[1]
        materials[symbol] = {
            "name": symbol,
            "format": formats[0],
            "palette_set": None if palette_set == "0x00000000" else palette_set,
            "primary_argb": (
                int(color.group(4), 16) << 24
                | int(color.group(1), 16) << 16
                | int(color.group(2), 16) << 8
                | int(color.group(3), 16)
            ),
        }
    return materials


def parse_dispatch(source: str) -> list[str | None]:
    head = re.search(
        r"MObjSub\s+\*\*dCaptainModel_gap_0x0000\[24\]\s*=\s*\{(.*?)\};",
        source,
        re.S,
    )
    tail = re.search(
        r"void\s+\*dCaptainModel_Joint_0x0060_post\[2\]\s*=\s*\{(.*?)\};",
        source,
        re.S,
    )
    if not head or not tail:
        raise ValueError("CaptainModel per-joint material dispatch tables not found")
    result = pointer_entries(head.group(1)) + pointer_entries(tail.group(1))
    if len(result) != 26:
        raise ValueError(f"expected 26 material dispatch entries, found {len(result)}")
    return result


def validate_dl_material_indices(assets: Path, joint_materials: list[list[dict]]):
    model = json.loads((assets / "model" / "captain_model.json").read_text())
    joints = {
        int(joint["index"]): joint
        for joint in model["trees"]["dCaptainModel_JointTree"]["joints"]
        if int(joint["index"]) < 26
    }
    for joint_id, materials in enumerate(joint_materials):
        dl_name = joints[joint_id].get("dl")
        if not dl_name:
            continue
        ops = json.loads((assets / "model" / "dl" / f"{dl_name}.json").read_text())
        indices = []
        for op in ops:
            word = op.get("w1")
            if op.get("op") == "G_DL" and isinstance(word, int) and word >> 24 == 0x0E:
                offset = word & 0x00FFFFFF
                if offset % 8:
                    raise ValueError(f"{dl_name}: unaligned material DL offset {offset:#x}")
                indices.append(offset // 8)
        if indices and max(indices) >= len(materials):
            raise ValueError(
                f"{dl_name}: material index {max(indices)} but only {len(materials)} entries"
            )
        if len(set(indices)) != len(materials):
            raise ValueError(
                f"{dl_name}: DL references {sorted(set(indices))}, expected "
                f"one reference for each of {len(materials)} materials"
            )


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--source", type=Path, required=True,
                        help="path to src/relocData/332_CaptainModel.c")
    parser.add_argument("--assets", type=Path, default=Path("assets_ssb64"))
    parser.add_argument("--build-dir", type=Path,
                        help="directory containing CaptainModel/*.inc.c")
    args = parser.parse_args()

    source_path = args.source.resolve()
    assets = args.assets.resolve()
    decomp_root = source_path.parents[2]
    build_dir = (args.build_dir or
                 decomp_root / "build" / "us" / "src" / "relocData" / "CaptainModel")
    source = source_path.read_text(encoding="utf-8", errors="replace")

    arrays = {}
    for c_type in ("void", "u16", "MObjSub"):
        arrays.update({
            symbol: pointer_entries(body)
            for symbol, body in declaration_bodies(source, c_type, "*").items()
        })

    declarations = parse_asset_declarations(source, build_dir)
    texture_dimensions = parse_texture_dimensions(source)
    materials = parse_materials(source)
    dispatch = parse_dispatch(source)
    joint_materials = []

    for list_symbol in dispatch:
        resolved = []
        for material_symbol in (arrays.get(list_symbol, []) if list_symbol else []):
            if material_symbol is None:
                continue
            material = dict(materials[material_symbol])
            palette_set = material.pop("palette_set")
            palette_entries = [item for item in arrays.get(palette_set, []) if item]
            material["palette_symbol"] = palette_entries[0] if palette_entries else None
            resolved.append(material)
        joint_materials.append(resolved)

    validate_dl_material_indices(assets, joint_materials)

    # Include every declared palette because a few unmaterialed display lists
    # load one statically with G_LOADTLUT (notably the torso emblem joint).
    palettes = {}
    for symbol, (kind, values) in declarations.items():
        if kind == "u16" and len(values) >= 16:
            palettes[symbol] = [rgba16_to_argb(value) for value in values]

    # Some CI4 pixel images are declared as u16 and named "palette".  Recover
    # them as big-endian byte streams so the baker can treat every G_LOADBLOCK
    # source uniformly.
    image_symbols = set()
    for dl_path in (assets / "model" / "dl").glob("*.json"):
        for op in json.loads(dl_path.read_text()):
            if op.get("op") == "G_SETTIMG" and op.get("image"):
                image_symbols.add(op["image"])
    recovered = []
    textures_dir = assets / "textures"
    textures_dir.mkdir(parents=True, exist_ok=True)

    # Rebuild the portion of the reloc file described by absolute-offset
    # symbols.  Some logical texture atlases overlap declarations that the
    # decomp splitter also names as costume palettes; placing every declaration
    # at its source offset recovers those atlases without a model-specific map.
    placements = []
    file_size = 0
    for symbol, (kind, values) in declarations.items():
        offset = symbol_file_offset(symbol)
        if offset is None:
            continue
        raw = declaration_bytes(kind, values)
        placements.append((offset, raw))
        file_size = max(file_size, offset + len(raw))
    file_image = bytearray(file_size)
    for offset, raw in placements:
        file_image[offset:offset + len(raw)] = raw

    for symbol in sorted(image_symbols):
        declaration = declarations.get(symbol)
        if not declaration:
            continue
        kind, values = declaration
        raw = declaration_bytes(kind, values)
        dimensions = texture_dimensions.get(symbol)
        offset = symbol_file_offset(symbol)
        if dimensions and offset is not None:
            expected = (dimensions[0] * dimensions[1] + 1) // 2
            if offset + expected <= len(file_image):
                raw = bytes(file_image[offset:offset + expected])
        output = textures_dir / f"{symbol}.bin"
        output.write_bytes(raw)
        recovered.append(output.name)

    result = {
        "version": 1,
        "costume_index": 0,
        "source": source_path.name,
        "joint_materials": joint_materials,
        "palettes_argb": palettes,
        "texture_dimensions": {
            symbol: list(dimensions)
            for symbol, dimensions in texture_dimensions.items()
        },
        "recovered_texture_bins": recovered,
    }
    output = textures_dir / "material_bindings.json"
    output.write_text(json.dumps(result, indent=1) + "\n", encoding="utf-8")
    print(
        f"wrote {output}: {sum(map(len, joint_materials))} materials, "
        f"{len(palettes)} palettes, {len(recovered)} texture blobs"
    )


if __name__ == "__main__":
    main()
