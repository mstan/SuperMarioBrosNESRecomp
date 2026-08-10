#!/usr/bin/env python3
"""Build and verify one immutable Pikachu runtime cache."""

from __future__ import annotations

import hashlib
import json
import os
import shutil
import tempfile
import time
import wave
from pathlib import Path

import bake_pikachu_runtime
import build_cache
import pikachu_audio
import pikachu_owner


FORMAT = "smb1-smash64-pikachu-owner-cache"
RECIPE_VERSION = 8
RUNTIME_FILENAME = "pikachu_runtime.bin"
# Source-derived runtime hashes are intentionally updated with the cache
# recipe whenever the binary layout changes. These were regenerated from the
# accepted US v1.0 owner ROM after the presentation-animation expansion.
RUNTIME_HASHES = {
    0: "248d1b4e53568f14c13eaa85c14eea19ae7cc0e6d6d5c84bcce39388812d69f5",
    1: "8a2cce060382215079bcaf6616c7ae090a31b8fa7e228383fcb92a35478a8b41",
    2: "4bf130211a67c31e945a81e3a1846d267ef3cdb10bb4a67c438e92d2fbeb2ac6",
    3: "0e987e182c784e37380e5a6e2cc0422d430e240cdd786594203b4f15cdf7bb24",
}


def _sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def _wav_pcm(path: Path) -> tuple[int, str]:
    with wave.open(str(path), "rb") as stream:
        if (stream.getnchannels(), stream.getsampwidth(), stream.getframerate(),
                stream.getcomptype()) != (1, 2, 44100, "NONE"):
            raise ValueError(f"invalid Pikachu runtime WAV format: {path.name}")
        frames = stream.getnframes()
        pcm = stream.readframes(frames)
    if len(pcm) != frames * 2:
        raise ValueError(f"truncated Pikachu runtime WAV: {path.name}")
    return frames, hashlib.sha256(pcm).hexdigest()


def cache_name(costume: int) -> str:
    if costume not in RUNTIME_HASHES:
        raise ValueError("Pikachu costume must be 0..3")
    return (f"pikachu-final-r{RECIPE_VERSION}-c{costume}-"
            f"{build_cache.CANONICAL_SHA1}-{RUNTIME_HASHES[costume][:16]}")


def _expected_files() -> set[str]:
    filenames = [spec[0] for spec in pikachu_audio.VOICE_CUES.values()]
    filenames += [spec[0] for spec in pikachu_audio.FGM_CUES.values()]
    filenames.append(pikachu_audio.LOOP_FILE)
    return {"manifest.json", RUNTIME_FILENAME} | {
        f"audio/{name}" for name in filenames}


def verify(root: Path, costume: int | None = None) -> dict:
    if not root.is_dir() or root.is_symlink():
        raise ValueError("Pikachu cache is not a real directory")
    entries = list(root.rglob("*"))
    if any(path.is_symlink() for path in entries):
        raise ValueError("Pikachu cache contains a symbolic link")
    files = {path.relative_to(root).as_posix()
             for path in entries if path.is_file()}
    directories = {path.relative_to(root).as_posix()
                   for path in entries if path.is_dir()}
    if files != _expected_files() or directories != {"audio"}:
        raise ValueError("Pikachu cache inventory changed")
    manifest = json.loads((root / "manifest.json").read_text(encoding="utf-8"))
    selected = int(manifest.get("costume", -1))
    if costume is not None and selected != costume:
        raise ValueError("Pikachu cache costume does not match selection")
    if selected not in RUNTIME_HASHES or manifest.get("format") != FORMAT or \
            manifest.get("recipe_version") != RECIPE_VERSION or \
            manifest.get("normalized_rom_sha1") != build_cache.CANONICAL_SHA1:
        raise ValueError("Pikachu cache identity changed")
    runtime = root / RUNTIME_FILENAME
    if _sha256(runtime) != RUNTIME_HASHES[selected] or \
            manifest.get("runtime_sha256") != RUNTIME_HASHES[selected]:
        raise ValueError("Pikachu runtime blob failed validation")
    clips = manifest.get("audio")
    if not isinstance(clips, list) or len(clips) != len(pikachu_audio.APPROVED_CUES):
        raise ValueError("Pikachu audio manifest is incomplete")
    seen = set()
    for clip in clips:
        event = clip.get("event")
        relative = clip.get("file")
        if event in pikachu_audio.VOICE_CUES:
            expected_filename = pikachu_audio.VOICE_CUES[event][0]
        elif event in pikachu_audio.FGM_CUES:
            expected_filename = pikachu_audio.FGM_CUES[event][0]
        elif event == pikachu_audio.LOOP_EVENT:
            expected_filename = pikachu_audio.LOOP_FILE
        else:
            expected_filename = None
        if event in seen or event not in pikachu_audio.APPROVED_CUES or \
                expected_filename is None or \
                relative != f"audio/{expected_filename}":
            raise ValueError("invalid Pikachu audio manifest entry")
        path = root / relative
        frames, pcm_hash = _wav_pcm(path)
        if (frames, pcm_hash) != pikachu_audio.APPROVED_CUES[event] or \
                clip.get("frames") != frames or \
                clip.get("pcm_sha256") != pcm_hash or \
                clip.get("wav_sha256") != _sha256(path):
            raise ValueError(f"Pikachu audio cue failed validation: {event}")
        seen.add(event)
        if event == pikachu_audio.LOOP_EVENT and \
                clip.get("loop") != pikachu_audio.expected_loop_metadata():
            raise ValueError("Pikachu audio loop metadata changed")
    if seen != set(pikachu_audio.APPROVED_CUES):
        raise ValueError("Pikachu audio cue inventory is incomplete")
    return manifest


def _publish_immutable(staging: Path, target: Path, costume: int) -> Path:
    """Publish a verified content-addressed cache without replacing a peer."""
    for attempt in range(4):
        try:
            # Another process may finish the same build first. A valid cache
            # must never be evicted, even on platforms where replace() would
            # otherwise make that overwrite atomic.
            os.rename(staging, target)
            return target
        except (FileExistsError, OSError):
            if not target.exists():
                if attempt == 3:
                    raise
                continue
            try:
                verify(target, costume)
            except (OSError, ValueError, json.JSONDecodeError):
                quarantine = target.with_name(
                    f".{target.name}.corrupt-{os.getpid()}-{time.time_ns()}")
                try:
                    os.rename(target, quarantine)
                except FileNotFoundError:
                    continue
                continue
            shutil.rmtree(staging, ignore_errors=True)
            return target
    raise ValueError("could not publish the rebuilt Pikachu owner cache")


def build(rom_path: Path, cache_root: Path, costume: int = 0) -> Path:
    build_cache._require_external_cache_root(cache_root)
    if costume not in RUNTIME_HASHES:
        raise ValueError("Pikachu costume must be 0..3")
    # Revalidate the selected owner ROM even on an immutable cache hit. The
    # cache proves previously derived bytes, not that the file selected for
    # this PLAY still exists and is the supported canonical image.
    normalized = build_cache.normalize_rom(rom_path.read_bytes())
    if hashlib.sha1(normalized).hexdigest() != build_cache.CANONICAL_SHA1:
        raise ValueError("ROM is not the supported Smash Bros. US v1.0 image")
    target = cache_root / cache_name(costume)
    if target.exists():
        try:
            verify(target, costume)
            return target
        except (OSError, ValueError, json.JSONDecodeError):
            quarantine = target.with_name(
                f".{target.name}.corrupt-{os.getpid()}-{time.time_ns()}")
            os.rename(target, quarantine)
    cache_root.mkdir(parents=True, exist_ok=True)
    staging = Path(tempfile.mkdtemp(prefix=".pikachu-final-stage-",
                                    dir=cache_root))
    try:
        prototype = pikachu_owner.build(rom_path, staging / "prototype-cache")
        bake_pikachu_runtime.write_blob(prototype / "intermediate",
                                        staging / RUNTIME_FILENAME, costume)
        rendered_audio = pikachu_audio.render(rom_path, staging / "rendered-audio")
        audio_dir = staging / "audio"
        audio_dir.mkdir()
        audio_manifest = json.loads(
            (rendered_audio / "manifest.json").read_text(encoding="utf-8"))
        clips = []
        for clip in audio_manifest["clips"]:
            source = rendered_audio / clip["file"]
            destination = audio_dir / clip["file"]
            shutil.move(source, destination)
            frames, pcm_hash = _wav_pcm(destination)
            clips.append({"event": clip["event"],
                          "file": f"audio/{clip['file']}",
                          "frames": frames, "pcm_sha256": pcm_hash,
                          "wav_sha256": _sha256(destination),
                          **({"loop": clip["loop"]} if "loop" in clip else {})})
        shutil.rmtree(staging / "prototype-cache")
        shutil.rmtree(rendered_audio)
        manifest = {
            "format": FORMAT, "recipe_version": RECIPE_VERSION,
            "normalized_rom_sha1": build_cache.CANONICAL_SHA1,
            "character": "pikachu", "costume": costume,
            "runtime_sha256": RUNTIME_HASHES[costume],
            "audio": sorted(clips, key=lambda item: item["event"]),
            "audio_note": audio_manifest["approximation"],
        }
        (staging / "manifest.json").write_text(
            json.dumps(manifest, indent=2, sort_keys=True) + "\n",
            encoding="utf-8")
        verify(staging, costume)
        return _publish_immutable(staging, target, costume)
    except Exception:
        shutil.rmtree(staging, ignore_errors=True)
        raise
