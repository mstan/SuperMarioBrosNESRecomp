"""Regression checks for the minimal direct-owner-ROM Pikachu cue cache."""

from __future__ import annotations

import json
import os
import re
import shutil
import sys
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "owner_ssb64"))

import owner_audio  # noqa: E402
import pikachu_audio  # noqa: E402


EXPECTED = {
    "special_hi_voice": (8732, "8f30c6caac48f441f70660aa4572d91153a05f0805df30d4ed56d9863cf5c411"),
    "special_lw_voice": (40176, "6020b00ed1326e3e1a39dc59d31e54a117b75a997311c46e94fe778d7a82bb11"),
    "special_n_voice": (58036, "1dab4da48e43f8e4d508defbd41c7719c27b92c3e7c36998abe454a28a9141a2"),
    "electric_1": (17453, "7c64e2ae648edd2d13b75db99be6699f7369abf73984ee93ada6d73a982431cf"),
    "electric_2": (10904, "6894a05f3ddfd4d1ae68c2162e972f84a5a30acc948d4b9cf007db7b696b27f8"),
    "electric_3": (10583, "adc5ed81808b302fea581ca80c2086ccd40d01840a0380b53655b1cf984d6f7a"),
    "electric_5": (9107, "d399ed8df1e8f3560ddd0dc8c9428af4f7e155c3bfe95d3710749ae5fe21b456"),
    "light_swing_l": (8589, "c7ebe85fee1740ea134f7dbe026f6bd400f2dbc27535efbef67ff0edeb3ad6a7"),
    "light_swing_m": (7354, "fff5d375a9a7197ff0156aabf40a1d996c044d2e4912fa5347d9677b3583713a"),
    "light_swing_s": (6438, "8192ef6c410e72f48ddecbcc95e0bc75fad49664ae85c9f7df130042464aa59f"),
    "quick_attack_start": (17603, "639dab10e9a22e09a86051e22a295eb2cb4a05cb2b1fb6ee87e6929d460e8d5e"),
    "thunder": (87484, "015518530cebf78fbf508158fb8e581d15fc62c958ce1e61e153242791bd5718"),
    "electric_loop": (10425, "aedef3eda98f88e756a08848b37953d9b94e5fe94cfc78b31410dcf28df267a3"),
}


class PikachuAudioRecipeTests(unittest.TestCase):
    def test_manifest_bindings_match_live_locomotion_event_abi(self):
        header = (ROOT / "mods" / "smash64" / "ssb_ported" /
                  "pikachu_locomotion.h").read_text()
        match = re.search(r"typedef enum \{([^{}]*PIKACHU_EVENT[^{}]*)\}\s*PikachuEvent;", header,
                          re.DOTALL)
        self.assertIsNotNone(match)
        names = []
        for entry in match.group(1).split(","):
            name = entry.strip().split("=")[0].strip()
            if name:
                names.append(name)
        self.assertEqual(names, [
            "PIKACHU_EVENT_VOICE_SPECIAL_N",
            "PIKACHU_EVENT_VOICE_SPECIAL_HI",
            "PIKACHU_EVENT_VOICE_SPECIAL_LW",
            "PIKACHU_EVENT_FGM_LIGHT_S",
            "PIKACHU_EVENT_FGM_LIGHT_M",
            "PIKACHU_EVENT_FGM_LIGHT_L",
            "PIKACHU_EVENT_FGM_ELECTRIC_1",
            "PIKACHU_EVENT_FGM_ELECTRIC_2",
            "PIKACHU_EVENT_FGM_ELECTRIC_3",
            "PIKACHU_EVENT_FGM_ELECTRIC_5",
            "PIKACHU_EVENT_FGM_QUICK_ATTACK_START",
            "PIKACHU_EVENT_FGM_SWING_PULSE",
            "PIKACHU_EVENT_EFFECT_SPARKLE",
            "PIKACHU_EVENT_EFFECT_RIPPLE",
            "PIKACHU_EVENT_EFFECT_THUNDER_AMP",
            "PIKACHU_EVENT_PROJECTILE_JOLT_SPAWN",
            "PIKACHU_EVENT_PROJECTILE_THUNDER_SPAWN",
            "PIKACHU_EVENT_PROJECTILE_THUNDER_SELF_HIT",
            "PIKACHU_EVENT_COUNT",
        ])
        for bindings in pikachu_audio.CONTROLLER_BINDINGS.values():
            for event_id, event_name in bindings:
                self.assertEqual(names[event_id], event_name)
        for unresolved in pikachu_audio.UNRESOLVED_CONTROLLER_EVENTS:
            self.assertEqual(names[unresolved["id"]], unresolved["name"])

    def test_runtime_event_inventory_is_minimal_and_unique(self):
        events = set(pikachu_audio.VOICE_CUES) | set(pikachu_audio.FGM_CUES)
        events.add(pikachu_audio.LOOP_EVENT)
        self.assertEqual(events, set(EXPECTED))
        files = [spec[0] for spec in pikachu_audio.VOICE_CUES.values()]
        files += [spec[0] for spec in pikachu_audio.FGM_CUES.values()]
        files.append(pikachu_audio.LOOP_FILE)
        self.assertEqual(len(files), len(set(files)))
        self.assertEqual(len(files), 13)
        bound = {event: tuple(item[0] for item in bindings)
                 for event, bindings in pikachu_audio.CONTROLLER_BINDINGS.items()}
        self.assertEqual(bound, {
            "special_n_voice": (0,), "special_hi_voice": (1,),
            "special_lw_voice": (2,), "light_swing_s": (3,),
            "light_swing_m": (4,), "light_swing_l": (5,),
            "electric_1": (6,), "electric_2": (7,), "electric_3": (8,),
            "electric_5": (9,), "quick_attack_start": (10,),
            "thunder": (16,), "electric_loop": (15,),
        })
        self.assertEqual(pikachu_audio.UNRESOLVED_CONTROLLER_EVENTS[0]["id"], 11)
        self.assertEqual(pikachu_audio.UNRESOLVED_CONTROLLER_EVENTS[0]["smash_route"], 219)

    def test_rejects_repository_output(self):
        with self.assertRaises(ValueError):
            pikachu_audio._external_output(ROOT / "tracked-audio")

    def test_loop_crop_and_resample_are_bounded(self):
        # A tiny fake record set exercises metadata rejection without a ROM.
        with self.assertRaises(ValueError):
            pikachu_audio._loop_clip(bytes(owner_audio.CANONICAL_SIZE), [0] * 32)


OWNER_ROM = os.environ.get("PIKACHU_OWNER_ROM_TEST") or os.environ.get(
    "SSB64_OWNER_ROM_TEST_PATH")


@unittest.skipUnless(OWNER_ROM, "set PIKACHU_OWNER_ROM_TEST to run owner-ROM integration")
class PikachuAudioIntegrationTests(unittest.TestCase):
    def test_canonical_runtime_cues_routes_hashes_and_loop(self):
        root = Path(tempfile.mkdtemp(prefix="pikachu-runtime-audio-test-"))
        output = root / "audio"
        try:
            pikachu_audio.render(Path(OWNER_ROM), output)
            manifest = json.loads((output / "manifest.json").read_text())
            clips = {clip["event"]: clip for clip in manifest["clips"]}
            self.assertEqual(set(clips), set(EXPECTED))
            self.assertEqual({event: (clip["frames"], clip["pcm_sha256"])
                              for event, clip in clips.items()}, EXPECTED)
            self.assertEqual(len(manifest["routes"]), 13)
            self.assertIn("not full UCD/TBL/RSP emulation",
                          manifest["approximation"])
            loop = clips["electric_loop"]
            self.assertEqual(loop["kind"], "bounded_aladpcm_loop")
            self.assertEqual(loop["loop"]["start_frame"], 0)
            self.assertEqual(loop["loop"]["end_frame"], loop["frames"])
            self.assertEqual(loop["loop"]["source_start_sample"], 100)
            self.assertEqual(loop["loop"]["source_end_sample"], 7664)
            self.assertEqual(loop["controller_event_ids"], [15])
            self.assertEqual(clips["quick_attack_start"]["controller_event_ids"], [10])
            self.assertEqual(clips["thunder"]["controller_event_ids"], [16])
            self.assertEqual(manifest["unresolved_controller_events"][0]["id"], 11)
            pikachu_audio.verify(output, owner_audio.CANONICAL_SHA1)
            self.assertEqual({path.name for path in output.glob("*.wav")},
                             {clip["file"] for clip in clips.values()})
            manifest_text = (output / "manifest.json").read_text()
            self.assertNotIn(str(OWNER_ROM), manifest_text)
            self.assertFalse(any(path.stat().st_size == owner_audio.CANONICAL_SIZE
                                 for path in output.iterdir() if path.is_file()))
            damaged = output / clips["electric_1"]["file"]
            payload = bytearray(damaged.read_bytes())
            payload[-1] ^= 0x01
            damaged.write_bytes(payload)
            with self.assertRaisesRegex(ValueError, "hash mismatch"):
                pikachu_audio.verify(output, owner_audio.CANONICAL_SHA1)
            payload[-1] ^= 0x01
            damaged.write_bytes(payload)
            clips["electric_1"]["route"] = 999
            (output / "manifest.json").write_text(
                json.dumps(manifest, indent=1, sort_keys=True) + "\n")
            with self.assertRaisesRegex(ValueError, "recipe mismatch"):
                pikachu_audio.verify(output, owner_audio.CANONICAL_SHA1)
        finally:
            shutil.rmtree(root, ignore_errors=True)


if __name__ == "__main__":
    unittest.main()
