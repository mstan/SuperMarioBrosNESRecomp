#!/usr/bin/env python3
"""Build a Falcon-only, ROM-hash-keyed cache from an owner SSB64 US ROM.

No external decompilation checkout or Python package is required.  This file
contains only format code and an allowlisted extraction recipe; it neither
embeds nor writes a ROM image.  The resulting *raw reloc* cache is an
intermediate for the later model/animation/audio baker, not an install asset.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import shutil
import struct
import sys
import tempfile
import time
from pathlib import Path


CANONICAL_SHA1 = "e2929e10fccc0aa84e5776227e798abc07cedabf"
CANONICAL_SIZE = 16 * 1024 * 1024
RECIPE_VERSION = 2
RELOC_TABLE_ROM_ADDR = 0x001AC870
RELOC_FILE_COUNT = 2132
RELOC_TABLE_ENTRY_SIZE = 12
RELOC_DATA_START = RELOC_TABLE_ROM_ADDR + (RELOC_FILE_COUNT + 1) * RELOC_TABLE_ENTRY_SIZE
IS_FROZEN = bool(getattr(sys, "frozen", False) or getattr(sys, "_MEIPASS", None))
SOURCE_ROOT = None if IS_FROZEN else Path(__file__).resolve().parents[2]

# Names are diagnostic only.  IDs and expected decompressed sizes are the
# stable BattleShip/SmashBrosDecomp-derived recipe for this initial release.
RECIPE_FILES = (
    (332, "captain_model", 51344),
    (333, "falcon_punch_effect", 2160),
    (350, "falcon_kick_effect", 26080),
    (1512, "wait", 10784), (1513, "walk_1", 1648), (1514, "walk_2", 1920),
    (1515, "walk_3", 2272), (1516, "walk_end", 784), (1517, "dash", 4144),
    (1518, "run", 2240), (1519, "run_brake", 2864), (1520, "turn", 1792),
    (1521, "turn_run", 2736), (1522, "jump_forward", 2256),
    (1523, "jump_back", 3520), (1524, "jump_aerial_forward", 3344),
    (1525, "jump_aerial_back", 2928), (1526, "fall", 752),
    (1527, "fall_aerial", 784), (1528, "crouch", 1168),
    (1529, "crouch_idle", 1952), (1530, "crouch_end", 1232),
    (1531, "landing_air", 1184), (1554, "fall_special", 880),
    (1619, "jab_1", 2656), (1628, "forward_tilt", 3856),
    (1638, "attack_air_neutral", 2544), (1639, "attack_air_forward", 4576),
    (1640, "attack_air_back", 3168), (1642, "attack_air_down", 3760),
    (1652, "falcon_punch_ground", 8896), (1653, "falcon_punch_air", 5696),
    (1654, "down_special", 6464), (1655, "down_special_air_velocity", 1712),
    (1656, "down_special_landing", 3216), (1657, "down_special_air", 4224),
    (1658, "falcon_dive", 6144), (1659, "falcon_dive_catch", 736),
    (1660, "falcon_dive_end_1", 3696), (1661, "falcon_dive_end_2", 6352),
)


class BitStream:
    def __init__(self, data: bytes):
        self.data, self.pos, self.bits, self.available = data, 0, 0, 0

    def read(self, count: int) -> int:
        while self.available < count:
            if self.pos >= len(self.data):
                raise ValueError("VPK0 bitstream ended unexpectedly")
            self.bits = (self.bits << 8) | self.data[self.pos]
            self.pos += 1
            self.available += 8
        self.available -= count
        return (self.bits >> self.available) & ((1 << count) - 1)


class HuffNode:
    def __init__(self, value: int | None = None, left=None, right=None):
        self.value, self.left, self.right = value, left, right


def _tree(stream: BitStream) -> HuffNode:
    stack: list[HuffNode] = []
    while True:
        branch = stream.read(1)
        if branch and len(stack) < 2:
            return stack[0]
        if branch:
            stack[-2:] = [HuffNode(left=stack[-2], right=stack[-1])]
        else:
            stack.append(HuffNode(value=stream.read(8)))


def _decode_tree(stream: BitStream, node: HuffNode) -> int:
    while node.left is not None:
        node = node.right if stream.read(1) else node.left
    assert node.value is not None
    return node.value


def vpk0_decode(source: bytes) -> bytes:
    """Decode the VPK0 stream used by SSB64 reloc files."""
    if len(source) < 9 or source[:4] != b"vpk0":
        raise ValueError("expected a VPK0 stream")
    output_size = struct.unpack_from(">I", source, 4)[0]
    stream = BitStream(source[4:])
    stream.read(32)
    sample_method = stream.read(8)
    offsets, lengths = _tree(stream), _tree(stream)
    output = bytearray()
    while len(output) < output_size:
        if stream.read(1) == 0:
            output.append(stream.read(8))
            continue
        offset_bits = _decode_tree(stream, offsets)
        value = stream.read(offset_bits) if offset_bits else 0
        if sample_method:
            sub_offset = 0
            if value <= 2:
                sub_offset = value + 1
                extra_bits = _decode_tree(stream, offsets)
                value = stream.read(extra_bits) if extra_bits else 0
            source_index = len(output) - value * 4 - sub_offset + 8
        else:
            source_index = len(output) - value
        length_bits = _decode_tree(stream, lengths)
        length = stream.read(length_bits) if length_bits else 0
        for _ in range(length):
            if source_index < 0 or source_index >= len(output):
                raise ValueError("VPK0 invalid back-reference")
            output.append(output[source_index])
            source_index += 1
            if len(output) == output_size:
                break
    return bytes(output)


def normalize_rom(source: bytes) -> bytes:
    """Return a z64-order ROM without persisting any normalized ROM bytes."""
    if len(source) != CANONICAL_SIZE:
        raise ValueError(f"expected a {CANONICAL_SIZE}-byte Smash 64 ROM, got {len(source)}")
    magic = source[:4]
    if magic == b"\x80\x37\x12\x40":
        return source
    if magic == b"\x37\x80\x40\x12":  # v64: bytes in each 16-bit word swapped
        result = bytearray(source)
        result[0::2], result[1::2] = source[1::2], source[0::2]
        return bytes(result)
    if magic == b"\x40\x12\x37\x80":  # n64: bytes in each 32-bit word reversed
        result = bytearray(len(source))
        result[0::4], result[1::4] = source[3::4], source[2::4]
        result[2::4], result[3::4] = source[1::4], source[0::4]
        return bytes(result)
    raise ValueError(f"unrecognized N64 byte order ({magic.hex()})")


def _entry(rom: bytes, file_id: int) -> dict[str, int | bool]:
    if not 0 <= file_id < RELOC_FILE_COUNT:
        raise ValueError(f"invalid reloc file id {file_id}")
    offset = RELOC_TABLE_ROM_ADDR + file_id * RELOC_TABLE_ENTRY_SIZE
    first_word, reloc_intern, compressed_words, reloc_extern, decompressed_words = struct.unpack_from(">IHHHH", rom, offset)
    return {
        "compressed": bool(first_word >> 31),
        "data_offset": first_word & 0x7FFFFFFF,
        "reloc_intern_word": reloc_intern,
        "compressed_bytes": compressed_words * 4,
        "reloc_extern_word": reloc_extern,
        "decompressed_bytes": decompressed_words * 4,
    }


def extract_reloc(rom: bytes, file_id: int) -> bytes:
    entry = _entry(rom, file_id)
    begin = RELOC_DATA_START + int(entry["data_offset"])
    end = begin + int(entry["compressed_bytes"])
    if begin < RELOC_DATA_START or end > len(rom):
        raise ValueError(f"reloc {file_id} points outside the ROM")
    payload = rom[begin:end]
    output = vpk0_decode(payload) if entry["compressed"] else payload[:int(entry["decompressed_bytes"])]
    if len(output) != entry["decompressed_bytes"]:
        raise ValueError(f"reloc {file_id} decoded to {len(output)}, expected {entry['decompressed_bytes']}")
    return output


def default_cache_root() -> Path:
    local = os.environ.get("LOCALAPPDATA")
    if local:
        return Path(local) / "SuperMarioBrosRecomp" / "smash64"
    return Path.home() / ".cache" / "SuperMarioBrosRecomp" / "smash64"


def cache_path(cache_root: Path, rom_sha1: str) -> Path:
    return cache_root / f"falcon-reloc-r{RECIPE_VERSION}-{rom_sha1}"


def _require_external_cache_root(cache_root: Path) -> None:
    """Never let a convenient command line put owner-derived data in git."""
    try:
        resolved = cache_root.resolve()
    except OSError as exc:
        raise ValueError(f"cannot resolve cache root {cache_root}: {exc}") from exc
    if SOURCE_ROOT is not None and (resolved == SOURCE_ROOT or SOURCE_ROOT in resolved.parents):
        raise ValueError("cache root must be outside the source tree")


def _read_manifest(path: Path) -> dict:
    return json.loads((path / "manifest.json").read_text(encoding="utf-8"))


def verify_cache(path: Path, expected_rom_sha1: str | None = None) -> dict:
    manifest = _read_manifest(path)
    if manifest.get("recipe_version") != RECIPE_VERSION:
        raise ValueError("unsupported cache recipe version")
    if expected_rom_sha1 and manifest.get("normalized_rom_sha1") != expected_rom_sha1:
        raise ValueError("cache belongs to a different owner ROM")
    artifacts = manifest.get("artifacts")
    if not isinstance(artifacts, list) or len(artifacts) != len(RECIPE_FILES):
        raise ValueError("cache artifact list is incomplete")
    expected = {file_id: (name, size) for file_id, name, size in RECIPE_FILES}
    seen: set[int] = set()
    for artifact in artifacts:
        file_id = artifact.get("file_id")
        if file_id in seen or file_id not in expected:
            raise ValueError("cache has an invalid reloc artifact")
        seen.add(file_id)
        name, size = expected[file_id]
        if artifact.get("name") != name or artifact.get("size") != size:
            raise ValueError(f"cache artifact {file_id} does not match its recipe")
        reloc = artifact.get("reloc")
        if not isinstance(reloc, dict) or any(key not in reloc for key in (
                "compressed", "data_offset", "compressed_bytes", "decompressed_bytes",
                "reloc_intern_word", "reloc_extern_word")):
            raise ValueError(f"cache artifact {file_id} lacks relocation metadata")
        if reloc["decompressed_bytes"] != size:
            raise ValueError(f"cache artifact {file_id} relocation size mismatch")
        payload = path / "reloc" / f"{file_id:04d}_{name}.bin"
        if not payload.is_file() or payload.stat().st_size != size:
            raise ValueError(f"cache artifact {file_id} is missing or truncated")
        if hashlib.sha256(payload.read_bytes()).hexdigest() != artifact.get("sha256"):
            raise ValueError(f"cache artifact {file_id} hash mismatch")
    return manifest


def build_cache(rom_path: Path, cache_root: Path, rebuild: bool = False) -> Path:
    _require_external_cache_root(cache_root)
    rom = normalize_rom(rom_path.read_bytes())
    rom_sha1 = hashlib.sha1(rom).hexdigest()
    if rom_sha1 != CANONICAL_SHA1:
        raise ValueError("ROM is not the supported Smash Bros. US v1.0 image")
    target = cache_path(cache_root, rom_sha1)
    if target.exists() and not rebuild:
        verify_cache(target, rom_sha1)
        return target
    cache_root.mkdir(parents=True, exist_ok=True)
    staging = Path(tempfile.mkdtemp(prefix=f".{target.name}.", dir=cache_root))
    try:
        reloc_dir = staging / "reloc"
        reloc_dir.mkdir()
        artifacts = []
        for file_id, name, expected_size in RECIPE_FILES:
            reloc = _entry(rom, file_id)
            payload = extract_reloc(rom, file_id)
            if len(payload) != expected_size:
                raise ValueError(f"reloc {file_id} size changed: {len(payload)} != {expected_size}")
            output = reloc_dir / f"{file_id:04d}_{name}.bin"
            output.write_bytes(payload)
            artifacts.append({"file_id": file_id, "name": name, "size": len(payload),
                              "sha256": hashlib.sha256(payload).hexdigest(), "reloc": reloc})
        manifest = {"format": "smb1-smash64-falcon-reloc-cache", "recipe_version": RECIPE_VERSION,
                    "normalized_rom_sha1": rom_sha1, "artifacts": artifacts}
        (staging / "manifest.json").write_text(json.dumps(manifest, indent=2, sort_keys=True) + "\n", encoding="utf-8")
        verify_cache(staging, rom_sha1)
        if target.exists():
            if not rebuild:
                verify_cache(target, rom_sha1)
                return target
            quarantine = cache_root / f"{target.name}.corrupt-{int(time.time())}"
            target.rename(quarantine)
        os.replace(staging, target)
        return target
    except Exception:
        shutil.rmtree(staging, ignore_errors=True)
        raise


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path, help="owner Smash 64 US v1.0 ROM (.z64/.v64/.n64)")
    parser.add_argument("--cache-root", type=Path, default=default_cache_root())
    parser.add_argument("--verify", type=Path, help="verify an existing raw-reloc cache only")
    parser.add_argument("--rebuild", action="store_true", help="replace a bad/obsolete cache atomically")
    args = parser.parse_args(argv)
    try:
        if args.verify:
            manifest = verify_cache(args.verify)
            print(f"verified {args.verify} (recipe {manifest['recipe_version']})")
            return 0
        if not args.rom:
            parser.error("--rom is required unless --verify is used")
        output = build_cache(args.rom, args.cache_root, args.rebuild)
        print(output)
        return 0
    except (OSError, ValueError, json.JSONDecodeError) as exc:
        print(f"owner-ROM cache error: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    raise SystemExit(main())
