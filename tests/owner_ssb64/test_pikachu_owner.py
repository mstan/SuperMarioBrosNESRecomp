"""Dependency-free tests for the direct-owner-ROM Pikachu prototype cache."""

from __future__ import annotations

import hashlib
import json
import os
import sys
import tempfile
import struct
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "owner_ssb64"))
sys.path.insert(0, str(ROOT / "tools"))

import build_cache as falcon_cache  # noqa: E402
import pikachu_owner as pikachu  # noqa: E402
import bake_pikachu_runtime  # noqa: E402


class PikachuRecipeTests(unittest.TestCase):
    def test_recipe_is_unique_and_does_not_mutate_falcon_recipe(self):
        ids = [file_id for file_id, _name, _size in pikachu.RELOC_FILES]
        self.assertEqual(len(ids), len(set(ids)))
        self.assertEqual(ids[:4], [243, 341, 342, 347])
        self.assertEqual(len(pikachu.ANIM_SPECS), 37)
        self.assertEqual(pikachu.MODEL_JOINT_COUNT, 27)
        self.assertEqual(
            hashlib.sha256(repr(falcon_cache.RECIPE_FILES).encode()).hexdigest(),
            "f425406d553d0c3a8938bf811f89405a88df77cc31850e6533ba69d244aa3495",
        )

    def test_recipe_has_four_costumes_and_complete_audio_routes(self):
        self.assertEqual(set(pikachu.VOICE_WAVES.values()),
                         set(range(265, 281)))
        self.assertEqual(len(pikachu.FGM_ROUTES), 15)
        self.assertEqual([name for name, (_route, looping)
                          in pikachu.FGM_ROUTES.items() if looping],
                         ["electric_loop"])
        self.assertEqual(set(pikachu.FGM_SOURCE_WAVES),
                         {1, 7, 12, 25, 28, 35, 40})

    def test_rejects_repository_cache_output(self):
        with self.assertRaises(ValueError):
            pikachu._external(ROOT / "assets_ssb64" / "pikachu")

    def test_normalization_is_shared_for_all_three_byte_orders(self):
        z64 = bytearray(falcon_cache.CANONICAL_SIZE)
        z64[:4] = b"\x80\x37\x12\x40"
        v64 = bytearray(z64)
        v64[0::2], v64[1::2] = z64[1::2], z64[0::2]
        n64 = bytearray(len(z64))
        n64[0::4], n64[1::4] = z64[3::4], z64[2::4]
        n64[2::4], n64[3::4] = z64[1::4], z64[0::4]
        self.assertEqual(falcon_cache.normalize_rom(bytes(v64)), bytes(z64))
        self.assertEqual(falcon_cache.normalize_rom(bytes(n64)), bytes(z64))


@unittest.skipUnless(os.environ.get("PIKACHU_OWNER_ROM_TEST"),
                     "set PIKACHU_OWNER_ROM_TEST to run owner-ROM integration tests")
class PikachuOwnerRomIntegrationTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.workspace = tempfile.TemporaryDirectory(prefix="pikachu-owner-tests-")
        cls.root = Path(cls.workspace.name)
        cls.rom_path = Path(os.environ["PIKACHU_OWNER_ROM_TEST"])
        cls.cache = pikachu.build(cls.rom_path, cls.root / "z64-cache")

    @classmethod
    def tearDownClass(cls):
        cls.workspace.cleanup()

    def test_canonical_manifest_and_reloc_hashes(self):
        manifest_path = self.cache / "manifest.json"
        self.assertEqual(hashlib.sha256(manifest_path.read_bytes()).hexdigest(),
                         "481769832b15e463e3597041335519c5a0e0db628aea5bb4c11e0e6e1df7e5d3")
        expected = {
            243: "c217452a4a3919d1054e0b42311da68cea09b545aca74b3eb3fa33f5e464f69f",
            341: "0b99946b1e91697503c7f531711edeab18b275bd6ffb519e2599a7e0d18fedb4",
            342: "e09ecb102e8e963c375d32584e461868db536371be7a85ed1e14ab0ee8b99faa",
            347: "da99373c0fa5dcaa52cfd4c08d1e3c6ccd8efc822ba181da8899e8a807c9a938",
        }
        for file_id, digest in expected.items():
            payload = next((self.cache / "reloc").glob(f"{file_id:04d}_*.bin"))
            self.assertEqual(hashlib.sha256(payload.read_bytes()).hexdigest(), digest)

    def test_model_costumes_accessory_face_animations_and_effects(self):
        intermediate = self.cache / "intermediate"
        model = json.loads((intermediate / "model" / "pikachu_model.json").read_text())
        self.assertEqual(model["joint_count"], 27)
        self.assertEqual(len(model["joints"]), 27)
        self.assertEqual(model["accessory"]["joint"], 11)
        self.assertEqual(model["accessory"]["display_list_offset"], 0x63F0)
        self.assertEqual([entry["joint"] for entry in model["facial_texture_parts"]],
                         [11, 11])
        costumes = [json.loads((intermediate / "costumes" /
                                 f"costume_{index}.json").read_text())
                    for index in range(4)]
        self.assertEqual([item["material_animation_frame"] for item in costumes],
                         [0, 1, 2, 3])
        self.assertEqual([item["accessory"]["enabled"] for item in costumes],
                         [False, True, True, True])
        animations = json.loads((intermediate / "animations" / "manifest.json").read_text())
        self.assertEqual(len(animations), 37)
        self.assertEqual(sum(item["joint_count"] == 27 for item in animations), 5)
        effects = json.loads((intermediate / "effects" / "manifest.json").read_text())
        self.assertEqual([item["reloc_id"] for item in effects], [342, 347, 341])

    def test_runtime_baker_supports_hidden_costume_proof(self):
        expected = {
            0: (519672, "f4e71bcb3abf23000dbae91948162a6dd1c8d6e8064219874bda7b46171bf1ec"),
            1: (522364, "4f8256e4d667bb7c6ccd8fbc90398aa4374461f633c501a9dc73968162dabe17"),
            2: (522364, "2f51d7e4a123e89f4591784644c50a453aa7588a0fcfa23c47940c0e9504e33c"),
            3: (522376, "00d299887cf2241c6a77a5b01801c223c955802766619aac07a497b9b4a7d0e4"),
        }
        with tempfile.TemporaryDirectory(prefix="pikachu-runtime-") as temporary:
            outputs = []
            for costume in range(4):
                output = Path(temporary) / f"pikachu_costume_{costume}.bin"
                bake_pikachu_runtime.write_blob(self.cache / "intermediate",
                                                output, costume)
                payload = output.read_bytes()
                magic, version, joints, triangles, textures, animations = \
                    struct.unpack_from("<8s5I", payload, 0)
                self.assertEqual((magic, version, joints, animations),
                                 (b"FLCN64B\0", 6, 27, 37))
                self.assertEqual((len(payload), hashlib.sha256(payload).hexdigest()),
                                 expected[costume])
                outputs.append((triangles, textures))
            self.assertEqual(outputs[0][0], 317)
            self.assertEqual([item[0] for item in outputs[1:]], [326, 326, 326])
            self.assertEqual([item[1] for item in outputs], [11, 14, 14, 15])

    def test_audio_inventory_and_no_rom_leak(self):
        audio = json.loads((self.cache / "intermediate" / "audio" /
                            "manifest.json").read_text())
        self.assertEqual(len(audio["voices"]), 16)
        self.assertEqual({entry["trigger_wave"]
                          for entry in audio["fgm_articulations"].values()},
                         set(pikachu.FGM_SOURCE_WAVES))
        loops = [route["name"] for route in audio["fgm_routes"]
                 if route["looping"]]
        self.assertEqual(loops, ["electric_loop"])
        manifest = pikachu.verify_cache(self.cache, falcon_cache.CANONICAL_SHA1)
        self.assertNotIn(str(self.rom_path), json.dumps(manifest))
        self.assertTrue(all(Path(item["path"]).suffix.lower()
                            not in (".z64", ".v64", ".n64", ".rom")
                            for item in manifest["files"]))
        self.assertTrue(all(item["size"] != falcon_cache.CANONICAL_SIZE
                            for item in manifest["files"]))

    def test_z64_v64_n64_produce_byte_identical_cache(self):
        z64 = falcon_cache.normalize_rom(self.rom_path.read_bytes())
        v64 = bytearray(z64)
        v64[0::2], v64[1::2] = z64[1::2], z64[0::2]
        n64 = bytearray(len(z64))
        n64[0::4], n64[1::4] = z64[3::4], z64[2::4]
        n64[2::4], n64[3::4] = z64[1::4], z64[0::4]
        manifests = [(self.cache / "manifest.json").read_bytes()]
        for name, data in (("owner.v64", v64), ("owner.n64", n64)):
            rom = self.root / name
            rom.write_bytes(data)
            built = pikachu.build(rom, self.root / f"{name}-cache")
            manifests.append((built / "manifest.json").read_bytes())
        self.assertEqual(manifests[0], manifests[1])
        self.assertEqual(manifests[0], manifests[2])


if __name__ == "__main__":
    unittest.main()
