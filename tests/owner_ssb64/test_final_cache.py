"""Tests for the release-facing atomic Falcon owner-cache orchestrator."""

from __future__ import annotations

import array
import hashlib
import importlib.util
import json
import os
import shutil
import tempfile
import unittest
import wave
from pathlib import Path
from unittest import mock


ROOT = Path(__file__).resolve().parents[2]
MODULE = ROOT / "tools" / "owner_ssb64" / "build_final_cache.py"
SPEC = importlib.util.spec_from_file_location("owner_ssb64_final_cache", MODULE)
assert SPEC and SPEC.loader
final_cache = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(final_cache)


class FinalCacheTests(unittest.TestCase):
    def _fixture_cache(self, root: Path) -> None:
        """Write a valid synthetic cache under temporarily narrowed hashes."""
        (root / "audio").mkdir(parents=True)
        runtime = root / final_cache.RUNTIME_FILENAME
        runtime.write_bytes(b"approved synthetic Falcon runtime")
        expected_audio = {}
        for index, name in enumerate(sorted(final_cache.EXPECTED_AUDIO)):
            samples = array.array("h", [index + 1, -(index + 1)])
            path = root / "audio" / name
            with wave.open(str(path), "wb") as stream:
                stream.setnchannels(1)
                stream.setsampwidth(2)
                stream.setframerate(44100)
                stream.writeframes(samples.tobytes())
            expected_audio[name] = (2, hashlib.sha256(samples.tobytes()).hexdigest())
        runtime_hash = hashlib.sha256(runtime.read_bytes()).hexdigest()
        with mock.patch.object(final_cache, "APPROVED_RUNTIME_SHA256", runtime_hash), \
             mock.patch.object(final_cache, "EXPECTED_AUDIO", expected_audio):
            final_cache._write_manifest(root, "a" * 40)
            final_cache.verify_final_cache(root, "a" * 40)

    def test_refuses_source_tree_cache(self) -> None:
        with self.assertRaises(ValueError):
            final_cache._require_external(ROOT / "owner-cache")

    def test_manifest_verification_fails_closed_on_extra_or_tampered_files(self) -> None:
        with tempfile.TemporaryDirectory(prefix="falcon-final-cache-test-") as tmp:
            root = Path(tmp) / "cache"
            self._fixture_cache(root)
            runtime_hash = hashlib.sha256((root / final_cache.RUNTIME_FILENAME).read_bytes()).hexdigest()
            expected_audio = {
                name: final_cache._read_wav(root / "audio" / name)
                for name in final_cache.EXPECTED_AUDIO
            }
            with mock.patch.object(final_cache, "APPROVED_RUNTIME_SHA256", runtime_hash), \
                 mock.patch.object(final_cache, "EXPECTED_AUDIO", expected_audio):
                (root / "unexpected.bin").write_bytes(b"not part of the release cache")
                with self.assertRaisesRegex(ValueError, "unexpected"):
                    final_cache.verify_final_cache(root, "a" * 40)
                (root / "unexpected.bin").unlink()
                (root / "leftover-intermediate").mkdir()
                with self.assertRaisesRegex(ValueError, "directories"):
                    final_cache.verify_final_cache(root, "a" * 40)
                (root / "leftover-intermediate").rmdir()
                cue = root / "audio" / next(iter(expected_audio))
                cue.write_bytes(cue.read_bytes() + b"tamper")
                with self.assertRaises(ValueError):
                    final_cache.verify_final_cache(root, "a" * 40)

    def test_immutable_publish_never_replaces_existing_verified_cache(self) -> None:
        with tempfile.TemporaryDirectory(prefix="falcon-final-cache-atomic-") as tmp:
            parent = Path(tmp)
            existing_stage = parent / "existing-stage"
            self._fixture_cache(existing_stage)
            runtime_hash = hashlib.sha256((existing_stage / final_cache.RUNTIME_FILENAME).read_bytes()).hexdigest()
            expected_audio = {
                name: final_cache._read_wav(existing_stage / "audio" / name)
                for name in final_cache.EXPECTED_AUDIO
            }
            with mock.patch.object(final_cache, "APPROVED_RUNTIME_SHA256", runtime_hash), \
                 mock.patch.object(final_cache, "EXPECTED_AUDIO", expected_audio):
                manifest_hash = final_cache._sha256(existing_stage / "manifest.json")
                target = parent / f"falcon-final-r1-{'a' * 40}-{manifest_hash[:16]}"
                os.rename(existing_stage, target)
                stage = parent / "new-stage"
                self._fixture_cache(stage)
                returned = final_cache._publish_immutable(stage, parent, "a" * 40)
                self.assertEqual(returned, target)
                self.assertFalse(stage.exists(), "losing staged build must be discarded")
                self.assertEqual(final_cache.verify_final_cache(target, "a" * 40)["format"],
                                 final_cache.FINAL_FORMAT)

    def test_result_file_contains_only_safe_cache_basename(self) -> None:
        with tempfile.TemporaryDirectory(prefix="falcon-final-result-") as tmp:
            parent = Path(tmp)
            cache = parent / f"falcon-final-r1-{'a' * 40}-0123456789abcdef"
            cache.mkdir()
            result = parent / "active-cache.txt"
            final_cache.write_result_file(result, cache)
            self.assertEqual(result.read_text(encoding="utf-8"), cache.name + "\n")

    def test_publish_quarantines_corrupt_matching_target(self) -> None:
        with tempfile.TemporaryDirectory(prefix="falcon-final-recover-") as tmp:
            parent = Path(tmp)
            stage = parent / "stage"
            self._fixture_cache(stage)
            runtime_hash = hashlib.sha256((stage / final_cache.RUNTIME_FILENAME).read_bytes()).hexdigest()
            expected_audio = {
                name: final_cache._read_wav(stage / "audio" / name)
                for name in final_cache.EXPECTED_AUDIO
            }
            with mock.patch.object(final_cache, "APPROVED_RUNTIME_SHA256", runtime_hash), \
                 mock.patch.object(final_cache, "EXPECTED_AUDIO", expected_audio):
                manifest_hash = final_cache._sha256(stage / "manifest.json")
                target = parent / f"falcon-final-r1-{'a' * 40}-{manifest_hash[:16]}"
                target.mkdir()
                (target / "manifest.json").write_text("corrupt", encoding="utf-8")
                returned = final_cache._publish_immutable(stage, parent, "a" * 40)
                self.assertEqual(returned, target)
                final_cache.verify_final_cache(returned, "a" * 40)
                self.assertTrue(any(item.name.startswith(f".{target.name}.corrupt-")
                                    for item in parent.iterdir()))


@unittest.skipUnless(os.environ.get("FALCON_OWNER_ROM_TEST"),
                     "set FALCON_OWNER_ROM_TEST to run against an owner ROM")
class OwnerRomFinalCacheIntegrationTests(unittest.TestCase):
    def test_full_pipeline_writes_only_verified_release_artifacts(self) -> None:
        with tempfile.TemporaryDirectory(prefix="falcon-owner-final-") as tmp:
            root = Path(tmp) / "external-cache"
            output = final_cache.build_final_cache(Path(os.environ["FALCON_OWNER_ROM_TEST"]), root)
            manifest = final_cache.verify_final_cache(output, final_cache.build_cache.CANONICAL_SHA1)
            self.assertEqual(manifest["runtime"]["sha256"], final_cache.APPROVED_RUNTIME_SHA256)
            self.assertEqual(len(manifest["audio"]), 11)
            self.assertEqual(final_cache._relative_file_inventory(output), final_cache._expected_relative_files())
            self.assertFalse((output / "intermediate").exists())

    def test_all_n64_byte_orders_produce_identical_final_manifest(self) -> None:
        """Byte-order normalization must cover audio as well as raw relocs."""
        with tempfile.TemporaryDirectory(prefix="falcon-owner-byteorder-") as tmp:
            tmp_path = Path(tmp)
            z64 = Path(os.environ["FALCON_OWNER_ROM_TEST"]).read_bytes()
            v64 = bytearray(z64)
            v64[0::2], v64[1::2] = z64[1::2], z64[0::2]
            n64 = bytearray(len(z64))
            n64[0::4], n64[1::4], n64[2::4], n64[3::4] = (
                z64[3::4], z64[2::4], z64[1::4], z64[0::4])
            paths = []
            for name, payload in (("z64", z64), ("v64", v64), ("n64", n64)):
                rom = tmp_path / f"owner.{name}"
                rom.write_bytes(payload)
                paths.append(final_cache.build_final_cache(rom, tmp_path / f"cache-{name}"))
            manifests = [(path / "manifest.json").read_bytes() for path in paths]
            self.assertEqual(manifests[0], manifests[1])
            self.assertEqual(manifests[0], manifests[2])

    def test_corrupt_raw_and_final_caches_rebuild_without_manual_cleanup(self) -> None:
        with tempfile.TemporaryDirectory(prefix="falcon-owner-recovery-") as tmp:
            root = Path(tmp) / "external-cache"
            rom = Path(os.environ["FALCON_OWNER_ROM_TEST"])
            output = final_cache.build_final_cache(rom, root)
            raw_cache = final_cache.build_cache.cache_path(
                root / "reloc", final_cache.build_cache.CANONICAL_SHA1)
            (raw_cache / "manifest.json").write_text("corrupt", encoding="utf-8")
            (output / final_cache.RUNTIME_FILENAME).write_bytes(b"corrupt")
            rebuilt = final_cache.build_final_cache(rom, root)
            final_cache.verify_final_cache(rebuilt, final_cache.build_cache.CANONICAL_SHA1)
            final_cache.build_cache.verify_cache(
                final_cache.build_cache.cache_path(
                    root / "reloc", final_cache.build_cache.CANONICAL_SHA1),
                final_cache.build_cache.CANONICAL_SHA1)
            self.assertTrue(any(".corrupt-" in item.name for item in root.iterdir()))


if __name__ == "__main__":
    unittest.main()
