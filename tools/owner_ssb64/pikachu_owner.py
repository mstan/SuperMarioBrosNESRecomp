#!/usr/bin/env python3
"""Build deterministic Pikachu intermediates directly from an owner SSB64 ROM.

This prototype intentionally stops before the SMB runtime format.  It emits a
small allowlisted reloc set, decoded model/animation metadata, all four costume
selections (including Pikachu's optional joint-11 accessory and facial texture
parts), character effect inputs, direct voice WAVs, and the FGM route/source
wave inputs needed by a later offline sound renderer.  ROM bytes are normalized
only in memory and every output must be outside the source tree.

The constants are offsets/IDs from the public BattleShip/SmashBrosDecomp map;
no texture, sample, model, or ROM payload is embedded in this source file.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import shutil
import struct
import tempfile
import wave
from array import array
from pathlib import Path

import build_cache as falcon_cache
import decode_intermediates as falcon_decode
import owner_audio


RECIPE_VERSION = 1
CACHE_FORMAT = "smb1-smash64-pikachu-prototype-cache"
MODEL_ID = 341
MAIN_ID = 243
MODEL_JOINT_TREE = 0x2650
MODEL_JOINT_COUNT = 27
MODEL_MOBJ_DISPATCH = 0x0000
MODEL_COSTUME_MATANIM_DISPATCH = MODEL_JOINT_TREE + 0x4D0
ACCESS_JOINT = 11
ACCESS_DL = 0x63F0
ACCESS_MOBJ_LIST = 0x6350
ACCESS_MATANIM_LIST = 0x654C
TEXTURE_PARTS_OFFSET = 0x140

# A Falcon-parity animation set: locomotion, crouch/fall/landing, representative
# normals/aerials, and every Pikachu special animation present in the fighter
# bank. Pointer-table sizes are explicit because the binary has no count field.
ANIM_SPECS = (
    (1957, "Idle", 26), (1958, "Walk1", 26), (1959, "Walk2", 26),
    (1960, "Walk3", 26), (1961, "WalkEnd", 26), (1962, "Dash", 26),
    (1963, "Run", 26), (1964, "RunBrake", 26), (1965, "Turn", 26),
    (1966, "TurnRun", 27), (1967, "JumpF", 26), (1968, "JumpB", 26),
    (1969, "JumpAerialF", 26), (1970, "JumpAerialB", 26),
    (1971, "Fall", 26), (1972, "FallAerial", 26), (1973, "Crouch", 26),
    (1974, "CrouchIdle", 26), (1975, "CrouchEnd", 26),
    (1976, "LandingAirX", 26), (1990, "FallSpecial", 26),
    (2016, "Jab1", 26), (2019, "AttackS3", 26),
    (2026, "AttackAirN", 26), (2027, "AttackAirF", 27),
    (2028, "AttackAirB", 26), (2030, "AttackAirD", 27),
    (2086, "NeutralSpecialGround", 26), (2087, "NeutralSpecialAir", 26),
    (2088, "UpSpecialEnd", 27), (2089, "UpSpecialAirEnd", 27),
    (2090, "DownSpecialStart", 26), (2091, "GettingThundered", 26),
    (2092, "DownSpecialEnd", 26), (2093, "DownSpecialStartAir", 26),
    (2094, "DownSpecialThunderedAir", 26),
    (2095, "DownSpecialEndAir", 26),
)

RELOC_FILES = (
    (MAIN_ID, "pikachu_main", 1904),
    (MODEL_ID, "pikachu_model", 39984),
    (342, "thunder_jolt_effect", 9104),
    (347, "thunder_effect", 7008),
) + tuple((file_id, name.lower(), {
    1957: 6448, 1958: 1712, 1959: 1776, 1960: 1904, 1961: 944,
    1962: 2896, 1963: 1952, 1964: 2896, 1965: 1536, 1966: 3264,
    1967: 2288, 1968: 2016, 1969: 2000, 1970: 1792, 1971: 1040,
    1972: 1056, 1973: 1152, 1974: 4592, 1975: 1456, 1976: 1904,
    1990: 1008, 2016: 3296, 2019: 4448, 2026: 2928, 2027: 4112,
    2028: 4320, 2030: 4208, 2086: 5472, 2087: 5936, 2088: 6064,
    2089: 3248, 2090: 2464, 2091: 1728, 2092: 2992, 2093: 2544,
    2094: 1408, 2095: 3136,
}[file_id]) for file_id, name, _count in ANIM_SPECS)

# Exact storage spans. Dimensions reported by the generated decomp comments on
# model atlases are known to be advisory/inconsistent, so storage byte counts
# remain authoritative and the runtime task must resolve individual tile views.
MODEL_TEXTURE_REGIONS = (
    (0x7350, 528, "body_face_ci4_atlas"),
    (0x7560, 2968, "body_material_ci4_atlas"),
    (0x80F8, 4904, "body_accessory_thunder_atlas"),
)
EFFECT_TEXTURE_REGIONS = {
    342: ((0x0030, 512, "jolt_ci4"), (0x0408, 1032, "jolt_ia8_0"),
          (0x0810, 1032, "jolt_ia8_1"), (0x0C18, 1024, "jolt_ia8_2"),
          (0x1C98, 512, "jolt_ci4_0"), (0x1EA0, 512, "jolt_ci4_1")),
    347: ((0x0030, 512, "thunder_ci4_0"), (0x0238, 512, "thunder_ci4_1"),
          (0x0440, 512, "thunder_ci4_2"), (0x11A0, 512, "shock_ci4")),
}

VOICE_WAVES = {
    "pikachu_appeal.wav": 265, "pikachu_smash1.wav": 266,
    "pikachu_smash2.wav": 267, "pikachu_smash3.wav": 269,
    "pikachu_special_n.wav": 268, "pikachu_special_lw.wav": 270,
    "pikachu_dead_up.wav": 271, "pikachu_fura_fura.wav": 272,
    "pikachu_damage.wav": 273, "pikachu_final_pika.wav": 274,
    "pikachu_final_chu.wav": 275, "pikachu_special_hi.wav": 276,
    "pikachu_heavy_get.wav": 277, "pikachu_ottotto.wav": 278,
    "pikachu_dead.wav": 279, "pikachu_fura_sleep.wav": 280,
}
FGM_ROUTES = {
    "landing": (79, False), "jump_inflate_2": (90, False),
    "jump_inflate_7": (101, False), "foot": (112, False),
    "dash": (125, False), "electric_1": (225, False),
    "electric_2": (226, False), "electric_3": (227, False),
    "electric_4": (228, False), "electric_5": (229, False),
    "electric_loop": (230, True), "special_hi_start": (231, False),
    "special_lw_thunder": (232, False), "dead_slam": (294, False),
    "down_bounce": (305, False),
}
FGM_FORKS = (86, 94, 105, 116, 287, 298, 649, 674, 675)
FGM_ARTICULATIONS = (3, 20, 21, 55, 74, 75, 154, 175, 187)
FGM_SOURCE_WAVES = (1, 7, 12, 25, 28, 35, 40)

AOBJ32_NAMES = {
    0: "End", 1: "Jump", 2: "Wait", 3: "SetValBlock", 4: "SetVal",
    5: "SetValRateBlock", 6: "SetValRate", 7: "SetTargetRate",
    8: "SetVal0RateBlock", 9: "SetVal0Rate", 10: "SetValAfterBlock",
    11: "SetValAfter", 13: "SetInterp", 14: "SetAnim", 15: "SetFlags",
    18: "SetExtValAfterBlock", 19: "SetExtValAfter", 20: "SetExtValBlock",
    21: "SetExtVal",
}


def cache_path(cache_root: Path, rom_sha1: str) -> Path:
    return cache_root / f"pikachu-prototype-r{RECIPE_VERSION}-{rom_sha1}"


def _external(path: Path) -> None:
    falcon_cache._require_external_cache_root(path)


def _token(raw: bytes, offset: int) -> int | None:
    if offset < 0 or offset + 4 > len(raw):
        raise ValueError(f"pointer word at 0x{offset:X} exceeds reloc")
    return falcon_decode._token_offset(struct.unpack_from(">I", raw, offset)[0])


def _pointer_list(raw: bytes, offset: int, limit: int = 16) -> list[int]:
    values = []
    for index in range(limit):
        target = _token(raw, offset + index * 4)
        if target is None:
            return values
        values.append(target)
    raise ValueError(f"pointer list at 0x{offset:X} lacks a terminator")


def _decode_aobj32(raw: bytes, start: int) -> list[dict]:
    """Decode the finite AObjEvent32 subset used by Pikachu costume scripts."""
    cursor, commands = start, []
    for _ in range(1024):
        if cursor + 4 > len(raw):
            raise ValueError(f"AObjEvent32 script at 0x{start:X} exceeds reloc")
        word = struct.unpack_from(">I", raw, cursor)[0]
        cursor += 4
        opcode, flags, payload = word >> 25, (word >> 15) & 0x3FF, word & 0x7FFF
        command = {"op": AOBJ32_NAMES.get(opcode, f"Cmd{opcode}"),
                   "opcode": opcode, "flags": flags, "payload": payload,
                   "word": f"{word:08x}"}
        if opcode == 0:
            commands.append(command)
            return commands
        if opcode == 1:
            command["target"] = _token(raw, cursor)
            cursor += 4
            commands.append(command)
            return commands
        value_count = 0
        if opcode in (3, 4, 8, 9, 10, 11, 18, 19, 20, 21):
            value_count = flags.bit_count()
        elif opcode in (5, 6):
            value_count = flags.bit_count() * 2
        elif opcode == 7:
            value_count = flags.bit_count()
        elif opcode in (2, 13, 14, 15):
            value_count = 0
        elif opcode in (12, 16, 23):
            value_count = 0
        elif opcode == 17:
            value_count = flags.bit_count()
        elif opcode == 22:
            value_count = (flags & 0x1F).bit_count()
        else:
            # Several model matanim blocks are intentionally left opaque by
            # the upstream reloc splitter and contain relocation-chain words
            # interleaved with commands. Preserve the authoritative offset and
            # stop at the first non-command rather than inventing semantics.
            command["opaque_tail"] = True
            commands.append(command)
            return commands
        if cursor + value_count * 4 > len(raw):
            raise ValueError("truncated AObjEvent32 payload")
        if value_count:
            command["values_u32"] = [
                f"{struct.unpack_from('>I', raw, cursor + index * 4)[0]:08x}"
                for index in range(value_count)
            ]
            cursor += value_count * 4
        commands.append(command)
    raise ValueError(f"AObjEvent32 script at 0x{start:X} has no terminator")


def _mobj(raw: bytes, offset: int) -> dict:
    if offset + 0x78 > len(raw):
        raise ValueError(f"MObjSub at 0x{offset:X} exceeds model")
    sprite_table = _token(raw, offset + 4)
    palette_table = _token(raw, offset + 0x2C)
    return {
        "offset": offset, "format": raw[offset + 2], "size": raw[offset + 3],
        "sprite_table": sprite_table, "palette_table": palette_table,
        "primary_argb": falcon_decode._mobj_primary(raw, offset),
        "env_rgba": raw[offset + 0x58:offset + 0x5C].hex(),
        "sha256": hashlib.sha256(raw[offset:offset + 0x78]).hexdigest(),
    }


def _decode_figatree(raw: bytes, start: int) -> list[dict]:
    """Falcon's Figatree decoder plus Pikachu's opcodes 11 and 12."""
    cursor, operations = start, []
    for _ in range(4096):
        if cursor + 2 > len(raw):
            raise ValueError(f"Figatree at 0x{start:X} exceeds reloc")
        command = struct.unpack_from(">H", raw, cursor)[0]
        cursor += 2
        opcode, flags, toggle = command >> 11, (command >> 1) & 0x3FF, command & 1
        if opcode == 0:
            operations.append({"op": "End"})
            return operations
        if opcode == 13:
            relative = struct.unpack_from(">h", raw, cursor)[0]
            cursor += 2
            operations.append({"op": "Loop", "cmd_word": command,
                               "offset": relative})
            if cursor + 2 <= len(raw) and struct.unpack_from(">H", raw, cursor)[0] == 0:
                operations.append({"op": "End"})
            return operations
        if opcode == 12:
            if cursor + 2 > len(raw):
                raise ValueError("truncated Figatree translate interpolation")
            relative = struct.unpack_from(">h", raw, cursor)[0]
            cursor += 2
            operations.append({"op": "SetTranslateInterp", "toggle": toggle,
                               "flags_raw": flags, "offset": relative})
            continue
        duration = struct.unpack_from(">H", raw, cursor)[0] if toggle else None
        if toggle:
            cursor += 2
        if opcode == 11:
            operations.append({"op": "AddLength", "toggle": toggle,
                               "dur": duration, "flags_raw": flags})
            continue
        name = falcon_decode.OP_NAMES.get(opcode)
        if name is None:
            raise ValueError(f"unsupported Figatree opcode {opcode} at 0x{cursor - 2:X}")
        if opcode == 1:
            operations.append({"op": name, "toggle": toggle, "dur": duration,
                               "flags_raw": flags})
            continue
        if opcode == 14:
            operations.append({"op": name, "toggle": toggle, "dur": duration,
                               "anim_flags": flags})
            continue
        tracks = [track for bit, track in enumerate(falcon_decode.TRACK_NAMES)
                  if flags & (1 << bit)]
        words = falcon_decode.OP_PAYLOAD_WORDS[opcode]
        payload = {}
        for track in tracks:
            values = []
            for _ in range(words):
                if cursor + 2 > len(raw):
                    raise ValueError("truncated Figatree track payload")
                values.append(struct.unpack_from(">h", raw, cursor)[0])
                cursor += 2
            payload[track] = values if words == 2 else values[0]
        operations.append({"op": name, "toggle": toggle, "dur": duration,
                           "tracks": tracks, "payload": payload})
    raise ValueError(f"Figatree at 0x{start:X} has no terminator")


def _decode_joint_tree(raw: bytes) -> tuple[list[dict], dict[int, list[dict]]]:
    joints, stack, display_lists = [], {}, {}
    for index in range(MODEL_JOINT_COUNT):
        offset = MODEL_JOINT_TREE + index * 44
        depth, dl_word, *values = struct.unpack_from(">II9f", raw, offset)
        dl_offset = falcon_decode._token_offset(dl_word)
        parent = stack.get(depth - 1) if depth else None
        joints.append({"index": index, "depth": depth, "parent": parent,
                       "dl_offset": dl_offset, "translate": values[:3],
                       "rotate_rad": values[3:6], "scale": values[6:9]})
        stack[depth] = index
        if dl_offset is not None and dl_offset not in display_lists:
            display_lists[dl_offset] = falcon_decode._decode_dl(raw, dl_offset)
    return joints, display_lists


def _material_recipe(raw: bytes) -> list[dict]:
    result = []
    for joint in range(MODEL_JOINT_COUNT):
        mobj_list = _token(raw, MODEL_MOBJ_DISPATCH + joint * 4)
        matanim_list = _token(raw, MODEL_COSTUME_MATANIM_DISPATCH + joint * 4)
        mobjs = _pointer_list(raw, mobj_list) if mobj_list is not None else []
        scripts = []
        for material_index in range(len(mobjs)):
            script = _token(raw, matanim_list + material_index * 4) if matanim_list is not None else None
            scripts.append({"offset": script,
                            "commands": _decode_aobj32(raw, script) if script is not None else None})
        result.append({"joint": joint, "mobj_list": mobj_list,
                       "matanim_list": matanim_list,
                       "materials": [_mobj(raw, offset) for offset in mobjs],
                       "costume_material_scripts": scripts})
    return result


def _write_model(main_raw: bytes, model_raw: bytes, output: Path) -> None:
    model_dir = output / "model"
    dl_dir = model_dir / "dl"
    vertex_dir = model_dir / "vtx"
    texture_dir = model_dir / "texture_storage"
    costume_dir = output / "costumes"
    dl_dir.mkdir(parents=True)
    vertex_dir.mkdir()
    texture_dir.mkdir()
    costume_dir.mkdir()
    joints, display_lists = _decode_joint_tree(model_raw)
    for offset, commands in display_lists.items():
        (dl_dir / f"dl_{offset:04x}.json").write_text(
            json.dumps(commands, indent=1) + "\n", encoding="utf-8")
    materials = _material_recipe(model_raw)
    for offset, size, name in MODEL_TEXTURE_REGIONS:
        if offset + size > len(model_raw):
            raise ValueError(f"model texture storage {name} exceeds reloc")
        (texture_dir / f"{offset:04x}_{name}.bin").write_bytes(model_raw[offset:offset + size])

    access_dl = _token(main_raw, 0x134)
    access_mobjs = _token(main_raw, 0x138)
    access_matanims = _token(main_raw, 0x13C)
    if (struct.unpack_from(">I", main_raw, 0x130)[0], access_dl, access_mobjs, access_matanims) != (
            ACCESS_JOINT, ACCESS_DL, ACCESS_MOBJ_LIST, ACCESS_MATANIM_LIST):
        raise ValueError("Pikachu accessory descriptor changed")
    accessory_material_offsets = _pointer_list(model_raw, access_mobjs)
    accessory_scripts = []
    for index in range(len(accessory_material_offsets)):
        script = _token(model_raw, access_matanims + index * 4)
        accessory_scripts.append({"offset": script,
                                  "commands": _decode_aobj32(model_raw, script) if script else None})
    accessory = {
        "joint": ACCESS_JOINT, "display_list_offset": ACCESS_DL,
        "display_list": falcon_decode._decode_dl(model_raw, ACCESS_DL),
        "materials": [_mobj(model_raw, offset) for offset in accessory_material_offsets],
        "costume_material_scripts": accessory_scripts,
    }
    vertex_counts: dict[int, int] = {}
    for commands in list(display_lists.values()) + [accessory["display_list"]]:
        for command in commands:
            if command["op"] == "G_VTX" and command.get("vbuf"):
                offset = int(command["vbuf"].rsplit("_", 1)[1], 16)
                vertex_counts[offset] = max(vertex_counts.get(offset, 0),
                                            int(command["numv"]))
    for offset, count in sorted(vertex_counts.items()):
        if offset + count * 16 > len(model_raw):
            raise ValueError(f"vertex run at 0x{offset:X} exceeds PikachuModel")
        vertices = [falcon_decode._decode_vertex(model_raw, offset + index * 16)
                    for index in range(count)]
        (vertex_dir / f"vtx_{offset:04x}.json").write_text(
            json.dumps(vertices, indent=1) + "\n", encoding="utf-8")
    texture_parts = []
    for index in range(2):
        joint, high_detail, low_detail = struct.unpack_from(">BBB", main_raw,
                                                            TEXTURE_PARTS_OFFSET + index * 3)
        texture_parts.append({"index": index, "joint": joint,
                              "detail_texture_ids": [high_detail, low_detail]})
    model = {"format": "ssb64-pikachu-model-intermediate", "version": 1,
             "reloc_id": MODEL_ID, "joint_tree_offset": MODEL_JOINT_TREE,
             "joint_count": MODEL_JOINT_COUNT, "joints": joints,
             "materials": materials, "facial_texture_parts": texture_parts,
             "accessory": accessory,
             "texture_storage": [{"offset": offset, "size": size, "name": name}
                                 for offset, size, name in MODEL_TEXTURE_REGIONS]}
    (model_dir / "pikachu_model.json").write_text(
        json.dumps(model, indent=1, sort_keys=True) + "\n", encoding="utf-8")
    for costume in range(4):
        selection = {
            "format": "ssb64-pikachu-costume-selection", "version": 1,
            "costume_id": costume, "material_animation_frame": costume,
            "common_material_recipe": "../model/pikachu_model.json#materials",
            "facial_texture_parts": "../model/pikachu_model.json#facial_texture_parts",
            "accessory": ({"enabled": False} if costume == 0 else {
                "enabled": True, "joint": ACCESS_JOINT,
                "recipe": "../model/pikachu_model.json#accessory",
                "material_animation_frame": costume,
            }),
        }
        (costume_dir / f"costume_{costume}.json").write_text(
            json.dumps(selection, indent=1, sort_keys=True) + "\n", encoding="utf-8")


def _write_animations(reloc_dir: Path, output: Path) -> None:
    animation_dir = output / "animations"
    animation_dir.mkdir()
    manifest = []
    for file_id, name, count in ANIM_SPECS:
        raw = next(reloc_dir.glob(f"{file_id:04d}_*.bin")).read_bytes()
        joints = []
        for slot in range(count):
            target = _token(raw, slot * 4)
            joints.append({"joint_slot": slot, "joint_id": slot + 1,
                           "script_offset": target,
                           "ops": _decode_figatree(raw, target)
                           if target is not None else None})
        filename = f"{name}.json"
        (animation_dir / filename).write_text(json.dumps({
            "file_id": file_id, "canonical_name": name, "joint_count": count,
            "has_auxiliary_root": count == MODEL_JOINT_COUNT, "joints": joints,
        }, indent=1, sort_keys=True) + "\n", encoding="utf-8")
        manifest.append({"file_id": file_id, "canonical_name": name,
                         "joint_count": count, "output": filename})
    (animation_dir / "manifest.json").write_text(
        json.dumps(manifest, indent=1, sort_keys=True) + "\n", encoding="utf-8")


def _write_effects(reloc_dir: Path, output: Path) -> None:
    effect_dir = output / "effects"
    texture_dir = effect_dir / "texture_storage"
    effect_dir.mkdir()
    texture_dir.mkdir()
    inventory = []
    for file_id, output_name in ((342, "PikachuSpecial3.bin"),
                                 (347, "PikachuSpecial2.bin")):
        raw = next(reloc_dir.glob(f"{file_id:04d}_*.bin")).read_bytes()
        (effect_dir / output_name).write_bytes(raw)
        regions = []
        for offset, size, name in EFFECT_TEXTURE_REGIONS[file_id]:
            if offset + size > len(raw):
                raise ValueError(f"effect texture {file_id}:{name} exceeds reloc")
            filename = f"{file_id}_{offset:04x}_{name}.bin"
            (texture_dir / filename).write_bytes(raw[offset:offset + size])
            regions.append({"offset": offset, "size": size, "name": name,
                            "output": f"texture_storage/{filename}"})
        inventory.append({"reloc_id": file_id, "raw": output_name,
                          "texture_storage": regions})
    # Thunder Trail is embedded in PikachuModel, with four consecutive IA8
    # frames. The final frame is 1024 bytes; preceding storage strides include
    # eight bytes of alignment/tail data.
    model_raw = next(reloc_dir.glob("0341_*.bin")).read_bytes()
    trail_regions = []
    for index, (offset, size) in enumerate(((0x8408, 1032), (0x8810, 1032),
                                            (0x8C18, 1032), (0x9020, 1024))):
        filename = f"341_{offset:04x}_thunder_trail_{index}.bin"
        (texture_dir / filename).write_bytes(model_raw[offset:offset + size])
        trail_regions.append({"offset": offset, "size": size,
                              "output": f"texture_storage/{filename}"})
    inventory.append({"reloc_id": 341, "effect": "thunder_trail",
                      "mobj_offset": 0x9420, "dobjdesc_offset": 0x95B0,
                      "texture_storage": trail_regions})
    (effect_dir / "manifest.json").write_text(
        json.dumps(inventory, indent=1, sort_keys=True) + "\n", encoding="utf-8")


def _write_pcm(path: Path, samples: list[int], rate: int) -> None:
    pcm = array("h", (max(-32768, min(32767, sample)) for sample in samples))
    with wave.open(str(path), "wb") as stream:
        stream.setnchannels(1)
        stream.setsampwidth(2)
        stream.setframerate(rate)
        stream.writeframes(pcm.tobytes())


def _write_audio(rom: bytes, output: Path) -> None:
    audio_dir = output / "audio"
    sources_dir = audio_dir / "fgm_source_waves"
    audio_dir.mkdir()
    sources_dir.mkdir()
    required = tuple(sorted(set(VOICE_WAVES.values()) | set(FGM_SOURCE_WAVES)))
    waves = owner_audio.decode_waves(rom, required)
    voices = []
    for filename, wave_id in sorted(VOICE_WAVES.items()):
        samples = owner_audio.resample_windowed_sinc(
            waves[wave_id], 16000, owner_audio.OUTPUT_RATE)
        _write_pcm(audio_dir / filename, samples, owner_audio.OUTPUT_RATE)
        voices.append({"file": filename, "wave_id": wave_id,
                       "frames": len(samples), "rate": owner_audio.OUTPUT_RATE})
    for wave_id in FGM_SOURCE_WAVES:
        _write_pcm(sources_dir / f"wave_{wave_id:03d}.wav", waves[wave_id],
                   owner_audio.SYNTH_RATE)

    route_ids = tuple(route for route, _loop in FGM_ROUTES.values())
    all_ucd_ids = tuple(sorted(set(route_ids) | set(FGM_FORKS)))
    ucd = owner_audio._parse_fgm_blob(rom[slice(*owner_audio.FGM_UCD)], 695,
                                      "fgm.ucd", all_ucd_ids)
    tbl = owner_audio._parse_fgm_blob(rom[slice(*owner_audio.FGM_TBL)], 464,
                                      "fgm.tbl", FGM_ARTICULATIONS)
    programs = {str(index): {"bytecode": program.hex(),
                             "commands": owner_audio._ucd_commands(program)}
                for index, program in sorted(ucd.items())}
    articulations = {str(index): {"bytecode": program.hex(),
                                  "trigger_wave": owner_audio._tbl_trigger(program)}
                     for index, program in sorted(tbl.items())}
    observed_waves = {entry["trigger_wave"] for entry in articulations.values()}
    if observed_waves != set(FGM_SOURCE_WAVES):
        raise ValueError(f"Pikachu FGM trigger set changed: {sorted(observed_waves)}")
    routes = [{"name": name, "route": route, "looping": looping}
              for name, (route, looping) in FGM_ROUTES.items()]
    (audio_dir / "manifest.json").write_text(json.dumps({
        "format": "ssb64-pikachu-audio-intermediate", "version": 1,
        "voices": voices, "fgm_routes": routes, "fgm_programs": programs,
        "fgm_articulations": articulations,
        "fgm_source_rate": owner_audio.SYNTH_RATE,
        "note": "FGM WAVs are decoded source waves; route bytecode still requires offline synthesis.",
    }, indent=1, sort_keys=True) + "\n", encoding="utf-8")


def _files(root: Path) -> list[dict]:
    result = []
    for path in sorted(item for item in root.rglob("*") if item.is_file()
                       and item != root / "manifest.json"):
        relative = path.relative_to(root).as_posix()
        if Path(relative).suffix.lower() in (".z64", ".v64", ".n64", ".rom"):
            raise ValueError("ROM-like file leaked into owner cache")
        result.append({"path": relative, "size": path.stat().st_size,
                       "sha256": hashlib.sha256(path.read_bytes()).hexdigest()})
    return result


def verify_cache(path: Path, expected_rom_sha1: str | None = None) -> dict:
    manifest = json.loads((path / "manifest.json").read_text(encoding="utf-8"))
    if manifest.get("format") != CACHE_FORMAT or manifest.get("recipe_version") != RECIPE_VERSION:
        raise ValueError("unsupported Pikachu owner-cache manifest")
    if expected_rom_sha1 and manifest.get("normalized_rom_sha1") != expected_rom_sha1:
        raise ValueError("Pikachu cache belongs to a different ROM")
    expected = manifest.get("files")
    if not isinstance(expected, list) or expected != _files(path):
        raise ValueError("Pikachu cache file inventory or hash mismatch")
    if any(item["size"] == falcon_cache.CANONICAL_SIZE for item in expected):
        raise ValueError("owner ROM-sized payload is forbidden in cache")
    return manifest


def build(rom_path: Path, cache_root: Path) -> Path:
    _external(cache_root)
    rom = falcon_cache.normalize_rom(rom_path.read_bytes())
    rom_sha1 = hashlib.sha1(rom).hexdigest()
    if rom_sha1 != falcon_cache.CANONICAL_SHA1:
        raise ValueError("ROM is not the supported Smash Bros. US v1.0 image")
    target = cache_path(cache_root, rom_sha1)
    if target.exists():
        verify_cache(target, rom_sha1)
        return target
    cache_root.mkdir(parents=True, exist_ok=True)
    staging = Path(tempfile.mkdtemp(prefix=f".{target.name}.", dir=cache_root))
    try:
        reloc_dir = staging / "reloc"
        intermediate = staging / "intermediate"
        reloc_dir.mkdir()
        intermediate.mkdir()
        for file_id, name, expected_size in RELOC_FILES:
            payload = falcon_cache.extract_reloc(rom, file_id)
            if len(payload) != expected_size:
                raise ValueError(f"reloc {file_id} size changed")
            (reloc_dir / f"{file_id:04d}_{name}.bin").write_bytes(payload)
        main_raw = next(reloc_dir.glob("0243_*.bin")).read_bytes()
        model_raw = next(reloc_dir.glob("0341_*.bin")).read_bytes()
        _write_model(main_raw, model_raw, intermediate)
        _write_animations(reloc_dir, intermediate)
        _write_effects(reloc_dir, intermediate)
        _write_audio(rom, intermediate)
        manifest = {"format": CACHE_FORMAT, "recipe_version": RECIPE_VERSION,
                    "normalized_rom_sha1": rom_sha1, "character": "pikachu",
                    "files": _files(staging)}
        (staging / "manifest.json").write_text(
            json.dumps(manifest, indent=1, sort_keys=True) + "\n", encoding="utf-8")
        verify_cache(staging, rom_sha1)
        os.replace(staging, target)
        return target
    except Exception:
        shutil.rmtree(staging, ignore_errors=True)
        raise


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--rom", type=Path)
    parser.add_argument("--cache-root", type=Path,
                        default=falcon_cache.default_cache_root())
    parser.add_argument("--verify", type=Path)
    args = parser.parse_args(argv)
    if args.verify:
        verify_cache(args.verify)
        print(f"verified {args.verify}")
    else:
        if args.rom is None:
            parser.error("--rom is required unless --verify is used")
        print(build(args.rom, args.cache_root))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
