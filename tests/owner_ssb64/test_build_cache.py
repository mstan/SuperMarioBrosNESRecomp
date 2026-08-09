"""Dependency-free checks for the owner-ROM cache bootstrap."""

from __future__ import annotations

import importlib.util
import hashlib
import os
import unittest
from pathlib import Path


MODULE = Path(__file__).resolve().parents[2] / "tools" / "owner_ssb64" / "build_cache.py"
SPEC = importlib.util.spec_from_file_location("owner_ssb64_build_cache", MODULE)
assert SPEC and SPEC.loader
cache = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(cache)


class NormalizationTests(unittest.TestCase):
    def test_normalizes_each_byte_order(self):
        z64 = bytearray(cache.CANONICAL_SIZE)
        z64[:4] = b"\x80\x37\x12\x40"
        v64 = bytearray(z64)
        v64[0::2], v64[1::2] = z64[1::2], z64[0::2]
        n64 = bytearray(cache.CANONICAL_SIZE)
        n64[0::4], n64[1::4], n64[2::4], n64[3::4] = z64[3::4], z64[2::4], z64[1::4], z64[0::4]
        self.assertEqual(cache.normalize_rom(bytes(v64)), bytes(z64))
        self.assertEqual(cache.normalize_rom(bytes(n64)), bytes(z64))

    def test_rejects_unknown_header(self):
        with self.assertRaises(ValueError):
            cache.normalize_rom(bytes(cache.CANONICAL_SIZE))

    def test_rejects_source_tree_as_cache_root(self):
        with self.assertRaises(ValueError):
            cache._require_external_cache_root(cache.SOURCE_ROOT / "assets_ssb64")


class RecipeTests(unittest.TestCase):
    def test_recipe_is_falcon_only_and_unique(self):
        ids = [item[0] for item in cache.RECIPE_FILES]
        self.assertEqual(len(ids), len(set(ids)))
        self.assertEqual(ids[:3], [332, 333, 350])
        self.assertGreaterEqual(len(ids), 40)


@unittest.skipUnless(os.environ.get("FALCON_OWNER_ROM_TEST"),
                     "set FALCON_OWNER_ROM_TEST to run against an owner ROM")
class OwnerRomIntegrationTests(unittest.TestCase):
    def test_vpk0_effect_extraction_matches_known_raw_effect(self):
        """Exercises the real VPK0 stream without embedding a ROM fixture."""
        rom = cache.normalize_rom(Path(os.environ["FALCON_OWNER_ROM_TEST"]).read_bytes())
        entry = cache._entry(rom, 333)
        self.assertTrue(entry["compressed"])
        self.assertEqual(entry["decompressed_bytes"], 2160)
        raw = cache.extract_reloc(rom, 333)
        self.assertEqual(hashlib.sha256(raw).hexdigest(),
                         "6523afbf08c88d34eeda8664b176a49375e63ead09129c1453c0881f04ef0ad8")


if __name__ == "__main__":
    unittest.main()
