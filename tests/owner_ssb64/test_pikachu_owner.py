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
        self.assertEqual(len(pikachu.ANIM_SPECS), 43)
        self.assertEqual(pikachu.MODEL_JOINT_COUNT, 27)
        self.assertEqual((pikachu.EF_COMMON_THUNDER_AMP_SCRIPT_ID,
                          pikachu.EF_COMMON_THUNDER_AMP_TEXTURE_ID,
                          pikachu.EF_COMMON_THUNDER_AMP_FRAME_COUNT),
                         (0x74, 46, 3))
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

    def test_down_special_air_motion_family_is_allowlisted(self):
        """Keep the presentation seam tied to the owner motion table.

        Pikachu's Down-B does not reuse the grounded pose in air: owner file
        IDs 2093--2095 are the three explicit air submotions.  This test is
        intentionally independent of an owner ROM so a later cache rewrite
        cannot quietly drop the assets required by the state-to-motion map.
        """
        animations = {name: file_id for file_id, name, _count
                      in pikachu.ANIM_SPECS}
        self.assertEqual({name: animations[name] for name in (
            "DownSpecialStart", "GettingThundered", "DownSpecialEnd",
            "DownSpecialStartAir", "DownSpecialThunderedAir",
            "DownSpecialEndAir",
        )}, {
            "DownSpecialStart": 2090, "GettingThundered": 2091,
            "DownSpecialEnd": 2092, "DownSpecialStartAir": 2093,
            "DownSpecialThunderedAir": 2094, "DownSpecialEndAir": 2095,
        })
        source = (ROOT / "game_smash64_assets.c").read_text(encoding="utf-8")
        self.assertIn('state->grounded ? "DownSpecialStart" :', source)
        self.assertIn('"DownSpecialStartAir"', source)
        self.assertIn('state->grounded ? "GettingThundered" :', source)
        self.assertIn('"DownSpecialThunderedAir"', source)
        for state, motion in (
            ("PK_THUNDER_END", "DownSpecialEnd"),
            ("PK_THUNDER_AIR_START", "DownSpecialStartAir"),
            ("PK_THUNDER_AIR_END", "DownSpecialEndAir"),
        ):
            self.assertIn(f'case {state}: return "{motion}";', source)
        self.assertIn("case PK_THUNDER_AIR_LOOP:", source)
        self.assertIn("case PK_THUNDER_AIR_SELF_HIT: return \"DownSpecialThunderedAir\";", source)

    def test_reachable_landing_and_fallspecial_states_use_owner_motions(self):
        """Never let an appended controller state silently render as Idle."""
        animations = {name: file_id for file_id, name, _count
                      in pikachu.ANIM_SPECS}
        self.assertEqual({name: animations[name] for name in (
            "LandingAirX", "FallSpecial", "LandingAirF", "LandingAirD",
        )}, {
            "LandingAirX": 1976, "FallSpecial": 1990,
            "LandingAirF": 2031, "LandingAirD": 2032,
        })
        source = (ROOT / "game_smash64_assets.c").read_text(encoding="utf-8")
        for state, motion in (
            ("PK_FALL_SPECIAL", "FallSpecial"),
            ("PK_FALL_SPECIAL_LANDING", "LandingAirX"),
            ("PK_LANDING_AIR_NULL", "LandingAirX"),
            ("PK_LANDING_AIR_F", "LandingAirF"),
            ("PK_LANDING_AIR_D", "LandingAirD"),
        ):
            self.assertIn(f'case {state}: return "{motion}";', source)

    def test_appended_common_jump_states_use_cached_source_motions(self):
        animations = {name: file_id for file_id, name, _count
                      in pikachu.ANIM_SPECS}
        self.assertEqual({name: animations[name] for name in (
            "LandingAirX", "JumpB", "JumpAerialB", "FallAerial",
        )}, {
            "LandingAirX": 1976, "JumpB": 1968,
            "JumpAerialB": 1970, "FallAerial": 1972,
        })
        source = (ROOT / "game_smash64_assets.c").read_text(encoding="utf-8")
        for state, motion in (
            ("PK_KNEEBEND", "LandingAirX"),
            ("PK_LANDING_HEAVY", "LandingAirX"),
            ("PK_JUMP_GROUND_B", "JumpB"),
            ("PK_JUMP_AERIAL_B", "JumpAerialB"),
            ("PK_AIR_FALL_AERIAL", "FallAerial"),
        ):
            self.assertIn(f'case {state}: return "{motion}";', source)
        sampler = source[source.index("static float pikachu_source_animation_frame"):
                         source.index("static float presentation_animation_frame")]
        self.assertIn("case PK_LANDING_HEAVY: return (float)state->state_frame * 0.5f", sampler)

    def test_landing_events_have_explicit_bounded_host_visuals(self):
        source = (ROOT / "game_smash64_assets.c").read_text(encoding="utf-8")
        landing = source[source.index("static void draw_pikachu_landing_effect"):
                         source.index("static int evaluate_pikachu_joint_render")]
        self.assertIn("PK_LANDING_AIR_NULL", landing)
        self.assertIn("PK_LANDING_AIR_F", landing)
        self.assertIn("PK_LANDING_AIR_D", landing)
        self.assertIn("for (i = 0; i < 2u; ++i)", landing)
        self.assertIn("QuakeMag1 remains unavailable", source)
        self.assertIn("draw_pikachu_landing_effect(state", source)

    def test_thunder_hit_color_uses_source_tint_sequence(self):
        source = (ROOT / "game_smash64_assets.c").read_text(encoding="utf-8")
        tint = source[source.index("static uint32_t pikachu_thunder_color_overlay"):
                      source.index("static int evaluate_pikachu_joint_render")]
        helper = (ROOT / "game_smash64_pikachu_presentation.h").read_text(
            encoding="utf-8")
        self.assertIn("0x5A0000FFu", helper)
        self.assertIn("0x64FFFFFFu", helper)
        self.assertIn("0x50FFFFFFu", helper)
        self.assertIn("0x50000000u", helper)
        self.assertIn("frame % 4u", helper)
        self.assertIn("normal_gameplay", tint)
        self.assertIn("nes_voxel_mesh_set_color_overlay", source)

    def test_quick_attack_uses_static_start_zip_and_end_local_clock(self):
        source = (ROOT / "game_smash64_assets.c").read_text(encoding="utf-8")
        animations = {name: file_id for file_id, name, _count
                      in pikachu.ANIM_SPECS}
        self.assertEqual(animations["UpSpecialAirEnd"], 2089)
        mapping = source[source.index("static const char *animation_for_state"):
                         source.index("static float pikachu_source_animation_frame")]
        self.assertIn('case PK_QUICK_ATTACK_ZIP2: return "UpSpecialAirEnd";',
                      mapping)
        self.assertIn('case PK_QUICK_ATTACK_RECOVERY: return "UpSpecialAirEnd";',
                      mapping)
        self.assertEqual(animations["UpSpecialEnd"], 2088)
        self.assertIn('case PK_QUICK_ATTACK_GROUND_ZIP2: return "UpSpecialEnd";',
                      mapping)
        self.assertIn('case PK_QUICK_ATTACK_GROUND_RECOVERY: return "UpSpecialEnd";',
                      mapping)
        sampler = source[source.index("static float pikachu_source_animation_frame"):
                         source.index("static float presentation_animation_frame")]
        for state in ("PK_QUICK_ATTACK_START", "PK_QUICK_ATTACK_ZIP1",
                      "PK_QUICK_ATTACK_ZIP2",
                      "PK_QUICK_ATTACK_GROUND_START",
                      "PK_QUICK_ATTACK_GROUND_ZIP1",
                      "PK_QUICK_ATTACK_GROUND_ZIP2"):
            self.assertIn(f"case {state}:", sampler)
        for state in ("PK_QUICK_ATTACK_WINDOW", "PK_QUICK_ATTACK_RECOVERY",
                      "PK_QUICK_ATTACK_GROUND_WINDOW",
                      "PK_QUICK_ATTACK_GROUND_RECOVERY"):
            self.assertIn(f"case {state}:", sampler)
        self.assertIn("game_smash64_pikachu_quick_animation_frame(1", sampler)
        self.assertIn("game_smash64_pikachu_quick_animation_frame(0", sampler)
        # Ripple's former whole-action 25/39 gates must not survive the
        # bridge's source End-local public clock.
        quick_fx = source[source.index("static void draw_pikachu_quick_attack_effect"):
                          source.index("static void draw_pikachu_landing_effect")]
        self.assertIn("frame < 8u", quick_fx)
        self.assertNotIn("frame >= 25u", quick_fx)
        self.assertNotIn("frame >= 39u", quick_fx)
        pose = source[source.index("static void apply_pikachu_quick_attack_pose"):
                      source.index("static void draw_pikachu_quick_attack_effect")]
        self.assertIn("state->state != PK_QUICK_ATTACK_ZIP1", pose)
        self.assertIn("state->state != PK_QUICK_ATTACK_ZIP2", pose)

    def test_quick_start_freezes_serialized_wait_run_fall_entry_pose(self):
        """Source SpecialHi Start uses motion -1, not End frame zero."""
        source = (ROOT / "game_smash64_assets.c").read_text(encoding="utf-8")
        entry = source[source.index("static int pikachu_quick_start_entry_sample"):
                       source.index("static int evaluate_pikachu_joint_render")]
        self.assertIn("smash64_pikachu_quick_entry_pose", entry)
        self.assertIn("entry.state = entry_state", entry)
        self.assertIn("entry.state_frame = entry_frame", entry)
        self.assertIn("animation_for_state(&entry)", entry)
        self.assertIn("pikachu_source_animation_frame(&entry)", entry)
        # Table of source-safe entry motions which must remain reachable at
        # their captured local frame for the whole Start status.
        source_motions = {
            "PK_GROUND_WAIT": "Idle", "PK_RUN": "Run",
            "PK_AIR_FALL": "Fall",
        }
        mapping = source[source.index("static const char *animation_for_state"):
                         source.index("static float pikachu_source_animation_frame")]
        for state, motion in source_motions.items():
            self.assertIn(f'case {state}: return "{motion}";', mapping)

    def test_joint_attachment_api_is_current_pose_not_last_draw(self):
        header = (ROOT / "game_smash64_assets.h").read_text(encoding="utf-8")
        source = (ROOT / "game_smash64_assets.c").read_text(encoding="utf-8")
        self.assertIn("game_smash64_assets_pikachu_joint_native", header)
        self.assertIn("evaluate_pikachu_joint_render", source)
        self.assertIn("animation_for_state(state)", source)
        self.assertIn("apply_pikachu_quick_attack_pose(state, r, s)", source)
        self.assertIn("240.0f - foot_y", source)
        native_start = source.index("int game_smash64_assets_pikachu_joint_native(")
        native_body = source[native_start:source.index(
            "\n}\n\nstatic int draw_model", native_start) + 2]
        self.assertIn("pikachu_source_animation_frame(", native_body)
        self.assertIn("PIKACHU_RENDER_HEIGHT", native_body)
        self.assertIn("PIKACHU_YAW_DEG, 0", native_body)
        self.assertNotIn("env_", native_body)

    def test_attachment_pose_is_env_invariant_and_landing_rate_is_source_backed(self):
        source = (ROOT / "game_smash64_assets.c").read_text(encoding="utf-8")
        evaluator = source[source.index("static int evaluate_pikachu_joint_render"):
                           source.index("int game_smash64_assets_pikachu_joint_native")]
        self.assertNotIn("env_", evaluator)
        native = source[source.index("int game_smash64_assets_pikachu_joint_native("):
                        source.index("static int draw_model", source.index(
                            "int game_smash64_assets_pikachu_joint_native("))]
        self.assertIn("pikachu_source_animation_frame(", native)
        sampler = source[source.index("static float pikachu_source_animation_frame"):
                         source.index("static float presentation_animation_frame")]
        self.assertIn("PK_LANDING_AIR_NULL: return (float)state->state_frame * 0.5f", sampler)
        self.assertIn("PK_FALL_SPECIAL_LANDING: return (float)state->state_frame * 0.4f", sampler)
        self.assertIn("case PK_WALK:", sampler)
        self.assertIn("(45.0f / 60.0f)", sampler)
        self.assertIn("(24.0f / 30.0f)", sampler)

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
                         "2c794f84c5556e1d8a545a33f86510c0075e31c0b068b3137c29b01667ccbf62")
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
        self.assertEqual(len(animations), 43)
        self.assertEqual(sum(item["joint_count"] == 27 for item in animations), 5)
        effects = json.loads((intermediate / "effects" / "manifest.json").read_text())
        self.assertEqual([item.get("reloc_id") for item in effects[:3]],
                         [342, 347, 341])
        common = effects[3]
        self.assertEqual((common["bank"], common["script_id"],
                          common["texture_id"]), ("efcommon", 0x74, 46))
        self.assertEqual(len(common["texture_storage"]), 3)

    def test_runtime_baker_supports_hidden_costume_proof(self):
        expected = {
            0: (687896, "08968239e0f76da15c47fbe6b457c17dd5df9b59c992f215f23f99c1dbb94d21"),
            1: (690588, "63b4075c1a6b41a8d4b28b130ead766bb0cde9a3e3bd4cc9746242328ad16c83"),
            2: (690588, "7d1c454b2b610bb40753e5a7eea02d6c5624ef14e60012856366a56c471d4cae"),
            3: (690600, "f4070de73114c4f5f06db04fabff06defc21a7e613c7b62850b5af3f5a62a05d"),
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
                                 (b"FLCN64B\0", 10, 27, 43))
                self.assertEqual((len(payload), hashlib.sha256(payload).hexdigest()),
                                 expected[costume])
                outputs.append((triangles, textures))
            self.assertEqual(outputs[0][0], 317)
            self.assertEqual([item[0] for item in outputs[1:]], [326, 326, 326])
            self.assertEqual([item[1] for item in outputs], [20, 23, 23, 24])

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
