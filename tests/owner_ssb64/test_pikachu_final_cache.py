"""Fail-closed tests for the Pikachu immutable final cache."""

from __future__ import annotations

import array
import hashlib
import json
import os
import shutil
import sys
import tempfile
import unittest
import wave
from pathlib import Path
from unittest import mock


ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "owner_ssb64"))

import build_cache  # noqa: E402
import pikachu_audio  # noqa: E402
import pikachu_final_cache as final_cache  # noqa: E402


class PikachuFinalCacheTests(unittest.TestCase):
    def _fixture(self, root: Path, costume: int = 0) -> tuple[str, dict]:
        (root / "audio").mkdir(parents=True)
        runtime = root / final_cache.RUNTIME_FILENAME
        runtime.write_bytes(b"synthetic Pikachu runtime")
        runtime_hash = hashlib.sha256(runtime.read_bytes()).hexdigest()
        approved = {}
        clips = []
        events = sorted(pikachu_audio.APPROVED_CUES)
        filenames = {
            event: (next((spec[0] for key, spec in pikachu_audio.VOICE_CUES.items()
                          if key == event), None) or
                    next((spec[0] for key, spec in pikachu_audio.FGM_CUES.items()
                          if key == event), None) or pikachu_audio.LOOP_FILE)
            for event in events
        }
        for index, event in enumerate(events):
            samples = array.array("h", [index + 1, -(index + 1)])
            path = root / "audio" / filenames[event]
            with wave.open(str(path), "wb") as stream:
                stream.setnchannels(1)
                stream.setsampwidth(2)
                stream.setframerate(44100)
                stream.writeframes(samples.tobytes())
            frames = 2
            pcm_hash = hashlib.sha256(samples.tobytes()).hexdigest()
            approved[event] = (frames, pcm_hash)
            entry = {"event": event, "file": f"audio/{path.name}",
                     "frames": frames, "pcm_sha256": pcm_hash,
                     "wav_sha256": hashlib.sha256(path.read_bytes()).hexdigest()}
            if event == pikachu_audio.LOOP_EVENT:
                entry["loop"] = pikachu_audio.expected_loop_metadata()
                entry["loop"]["end_frame"] = frames
            clips.append(entry)
        manifest = {
            "format": final_cache.FORMAT,
            "recipe_version": final_cache.RECIPE_VERSION,
            "normalized_rom_sha1": build_cache.CANONICAL_SHA1,
            "character": "pikachu", "costume": costume,
            "runtime_sha256": runtime_hash,
            "audio": clips,
        }
        (root / "manifest.json").write_text(
            json.dumps(manifest, indent=2, sort_keys=True) + "\n",
            encoding="utf-8")
        return runtime_hash, approved

    def test_strict_inventory_tamper_and_costume_identity(self):
        with tempfile.TemporaryDirectory(prefix="pikachu-final-unit-") as temp:
            root = Path(temp) / "cache"
            runtime_hash, approved = self._fixture(root, 1)
            with mock.patch.dict(final_cache.RUNTIME_HASHES, {1: runtime_hash}), \
                 mock.patch.object(pikachu_audio, "APPROVED_CUES", approved):
                final_cache.verify(root, 1)
                with self.assertRaises(ValueError):
                    final_cache.verify(root, 0)
                manifest_path = root / "manifest.json"
                manifest = json.loads(manifest_path.read_text(encoding="utf-8"))
                loop = next(clip for clip in manifest["audio"]
                            if clip["event"] == pikachu_audio.LOOP_EVENT)
                loop["loop"]["end_frame"] -= 1
                manifest_path.write_text(json.dumps(manifest), encoding="utf-8")
                with self.assertRaisesRegex(ValueError, "loop metadata"):
                    final_cache.verify(root, 1)
                loop["loop"] = pikachu_audio.expected_loop_metadata()
                voice = next(clip for clip in manifest["audio"]
                             if clip["event"] == "special_n_voice")
                voice["file"] = "audio/pikachu_electric_1.wav"
                manifest_path.write_text(json.dumps(manifest), encoding="utf-8")
                with self.assertRaisesRegex(ValueError, "manifest entry"):
                    final_cache.verify(root, 1)
                voice["file"] = "audio/pikachu_special_n.wav"
                manifest_path.write_text(json.dumps(manifest), encoding="utf-8")
                (root / "unexpected.bin").write_bytes(b"not allowed")
                with self.assertRaisesRegex(ValueError, "inventory"):
                    final_cache.verify(root, 1)

    def test_result_name_is_character_and_costume_namespaced(self):
        self.assertTrue(final_cache.cache_name(0).startswith(
            "pikachu-final-r8-c0-e2929e10"))
        self.assertNotEqual(final_cache.cache_name(0), final_cache.cache_name(1))
        with self.assertRaises(ValueError):
            final_cache.cache_name(4)

    def test_cache_hit_never_bypasses_current_rom_validation(self):
        with tempfile.TemporaryDirectory(prefix="pikachu-rom-gate-") as temp:
            root = Path(temp) / "external"
            (root / final_cache.cache_name(0)).mkdir(parents=True)
            bad_rom = Path(temp) / "wrong.z64"
            bad_rom.write_bytes(b"not a canonical owner ROM")
            with self.assertRaises(ValueError):
                final_cache.build(bad_rom, root, 0)

    def test_publish_never_replaces_existing_valid_cache(self):
        with tempfile.TemporaryDirectory(prefix="pikachu-cache-publish-") as temp:
            base = Path(temp)
            target = base / final_cache.cache_name(0)
            staging = base / ".staging"
            target_hash, approved = self._fixture(target, 0)
            staging_hash, _ = self._fixture(staging, 0)
            self.assertEqual(target_hash, staging_hash)
            runtime = target / final_cache.RUNTIME_FILENAME
            old_time = 1_700_000_000_000_000_000
            os.utime(runtime, ns=(old_time, old_time))
            with mock.patch.dict(final_cache.RUNTIME_HASHES, {0: target_hash}), \
                 mock.patch.object(pikachu_audio, "APPROVED_CUES", approved):
                self.assertEqual(
                    final_cache._publish_immutable(staging, target, 0), target)
                self.assertFalse(staging.exists())
                self.assertEqual(runtime.stat().st_mtime_ns, old_time)


OWNER_ROM = os.environ.get("PIKACHU_OWNER_ROM_TEST")


@unittest.skipUnless(OWNER_ROM, "set PIKACHU_OWNER_ROM_TEST for full final-cache tests")
class PikachuFinalCacheIntegrationTests(unittest.TestCase):
    def test_costumes_zero_and_one_build_and_recover_atomically(self):
        with tempfile.TemporaryDirectory(prefix="pikachu-final-integration-") as temp:
            cache_root = Path(temp) / "external"
            rom = Path(OWNER_ROM)
            plain = final_cache.build(rom, cache_root, 0)
            accessory = final_cache.build(rom, cache_root, 1)
            self.assertEqual(final_cache.verify(plain, 0)["costume"], 0)
            self.assertEqual(final_cache.verify(accessory, 1)["costume"], 1)
            self.assertEqual({path.relative_to(plain).as_posix()
                              for path in plain.rglob("*") if path.is_file()},
                             final_cache._expected_files())
            (plain / final_cache.RUNTIME_FILENAME).write_bytes(b"corrupt")
            rebuilt = final_cache.build(rom, cache_root, 0)
            final_cache.verify(rebuilt, 0)
            self.assertTrue(any(".corrupt-" in item.name
                                for item in cache_root.iterdir()))


if __name__ == "__main__":
    unittest.main()
