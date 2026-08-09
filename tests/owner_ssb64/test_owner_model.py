"""Owner-ROM integration check for Falcon's approved model and animations."""

from __future__ import annotations

import hashlib
import os
import sys
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "owner_ssb64"))
sys.path.insert(0, str(ROOT / "tools"))

import build_cache  # noqa: E402
import decode_intermediates  # noqa: E402
import bake_falcon_runtime  # noqa: E402


APPROVED_RUNTIME_SHA256 = (
    "8a8e0ac01341584488dad5681ae7563f3142ee15915ff154f5e3122c57146a3e"
)


@unittest.skipUnless(os.environ.get("FALCON_OWNER_ROM_TEST"),
                     "set FALCON_OWNER_ROM_TEST to run against an owner ROM")
class OwnerModelIntegrationTests(unittest.TestCase):
    def test_direct_owner_rom_bake_matches_approved_runtime(self):
        with tempfile.TemporaryDirectory(prefix="falcon-owner-model-") as tmp:
            tmp_path = Path(tmp)
            cache_path = build_cache.build_cache(
                Path(os.environ["FALCON_OWNER_ROM_TEST"]), tmp_path / "cache")
            intermediate = tmp_path / "intermediate"
            blob = tmp_path / "falcon_runtime.bin"
            decode_intermediates.materialize(cache_path, intermediate)
            bake_falcon_runtime.write_blob(intermediate, blob)
            self.assertEqual(hashlib.sha256(blob.read_bytes()).hexdigest(),
                             APPROVED_RUNTIME_SHA256)


if __name__ == "__main__":
    unittest.main()
