# Pikachu owner-presentation boundary

The Pikachu cache is built only from a checksum-validated user-supplied Smash
64 US v1.0 ROM. Its r11 cache key covers the 43 owner motion clips, all four
costume blobs, and the 15 finite/looping audio cues. No ROM or decoded asset is
committed to this repository.

The following presentation decisions are intentional and are not labeled as
exact source effects:

- `DustHeavyDouble` on aerial landing and `ImpactWave` on down-air landing are
  state-entry bounded host adaptations using the existing one-pixel dust/white
  helpers. The source has generic particles rather than Pikachu-owned cards;
  these quads therefore remain explicitly adaptations, not extracted effects.
- `QuakeMag1` on Thunder self-hit is emitted by the source path but has no
  host camera-quake API. It is deliberately unavailable; the extracted
  ThunderAmp card remains visible without claiming to shake the SMB camera.
- `ThunderHitColor` is a source-timed per-mesh overlay: self-hit repeats blue
  a90, white a100, clear, while End repeats white a80, black a80, clear,
  clear for its whole status. It composes over the extracted owner textures
  without mutating the cache and is suppressed while SMB owns death, water,
  or scripted presentation.

`SparkleWhite` and `Ripple` are generic SSB64 particles. Their present small
host quads/ring are bounded visual adaptations, not owner-extracted card
assets. The owner-extracted ThunderAmp effect is separate and source-timed.
