"""Owner-ROM audio recipe regression checks.

Set SSB64_OWNER_ROM_TEST_PATH to a locally owned canonical US v1.0 image to
run the integration assertion.  The test writes its derived files into the OS
temporary directory only; no ROM or PCM asset is written into this repository.
"""

from __future__ import annotations

import hashlib
import json
import os
import shutil
import sys
import tempfile
import unittest
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "owner_ssb64"))
import owner_audio  # noqa: E402


# These frame counts are the accepted current local cue durations at 44.1 kHz.
# The seven FGM paths are bit-identical to their established ignored WAV PCM;
# the four direct voices use this dependency-free renderer's deterministic
# windowed-sinc resampling, so duration is the cross-tool invariant.
EXPECTED_FRAMES = {
    "falcon_dive_catch_fgm.wav": 6593,
    "falcon_dive_explosion_fgm.wav": 30396,
    "falcon_dive_launch_fgm.wav": 8945,
    "falcon_dive_voice.wav": 30683,
    "falcon_jump_effort.wav": 9614,
    "falcon_kick.wav": 36559,
    "falcon_kick_start_fgm.wav": 35754,
    "falcon_kick_swing_fgm.wav": 8249,
    "falcon_punch_falcon.wav": 24873,
    "falcon_punch_impact_fgm.wav": 49735,
    "falcon_punch_punch.wav": 41366,
}
EXPECTED_FGM_PCM_SHA256 = {
    "falcon_dive_catch_fgm.wav": "854e7149472e8a57fba488013ee43e7a7418aa676ff34f5c02d1b2be681963ad",
    "falcon_dive_explosion_fgm.wav": "13d4cf67808b38c38807d17766e625a41c0aa6ac7364e16b90270388daa34cc4",
    "falcon_dive_launch_fgm.wav": "f1c39a977653576dafa3b1dcf555045b72085db959bae339ebe57511c30b01d9",
    "falcon_dive_voice.wav": "25c37937c449dc7ee1e2121db0aeb443fa20cf5155916b3a1152641968a94e98",
    "falcon_kick_start_fgm.wav": "637ebd882d912d2a7e4b4d466c3c83e5b02b3e2e81f5f32b16307077340ddd94",
    "falcon_kick_swing_fgm.wav": "0bd5f000cb8a363be1de4ed114963c5377dc196d52584b79e048e8dcf7a4a128",
    "falcon_punch_impact_fgm.wav": "05daa8a3791a37b89d4327d7e4b99b8ecf3079c1023a1e8e8ceb0fd257caf436",
}


class OwnerAudioTests(unittest.TestCase):
    def test_windowed_sinc_is_deterministic_bounded_and_duration_exact(self) -> None:
        source = [32767, -32768, 1000, -1000, 0, 12345, -23456]
        first = owner_audio.resample_windowed_sinc(source, 16000, 44100)
        second = owner_audio.resample_windowed_sinc(source, 16000, 44100)
        self.assertEqual(first, second)
        self.assertEqual(len(first), 20)
        self.assertTrue(all(-32768 <= sample <= 32767 for sample in first))

    def test_windowed_sinc_preserves_dc_and_identity(self) -> None:
        constant = [1234] * 96
        rendered = owner_audio.resample_windowed_sinc(constant, 16000, 44100)
        self.assertTrue(all(sample == 1234 for sample in rendered))
        identity = [-30000, -123, 0, 456, 30000]
        self.assertEqual(owner_audio.resample_windowed_sinc(identity, 44100, 44100), identity)

    def test_windowed_sinc_rejects_invalid_rates(self) -> None:
        with self.assertRaises(ValueError):
            owner_audio.resample_windowed_sinc([1], 0, 44100)

    def test_rejects_output_under_source_tree(self) -> None:
        with self.assertRaises(ValueError):
            owner_audio._external_output(ROOT / "not-a-cache")

    @unittest.skipUnless(os.environ.get("SSB64_OWNER_ROM_TEST_PATH"), "owner ROM test path not configured")
    def test_canonical_rom_matches_accepted_cue_set(self) -> None:
        output = Path(tempfile.mkdtemp(prefix="falcon-owner-audio-test-")) / "audio"
        try:
            owner_audio.render_audio(Path(os.environ["SSB64_OWNER_ROM_TEST_PATH"]), output)
            manifest = json.loads((output / "manifest.json").read_text(encoding="utf-8"))
            clips = {entry["file"]: entry for entry in manifest["clips"]}
            self.assertEqual(set(clips), set(EXPECTED_FRAMES))
            self.assertEqual({name: entry["frames"] for name, entry in clips.items()}, EXPECTED_FRAMES)
            for name, expected in EXPECTED_FGM_PCM_SHA256.items():
                self.assertEqual(clips[name]["pcm_sha256"], expected)
        finally:
            shutil.rmtree(output.parent, ignore_errors=True)


if __name__ == "__main__":
    unittest.main()
