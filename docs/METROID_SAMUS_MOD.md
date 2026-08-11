# Metroid Samus player replacement

This is an independent, default-off gameplay package. It does not depend on or
select Captain Falcon, and it has no character picker. Both packages use the
same `player-controller` exclusive group so enabling one disables the other.

## Owner-ROM boundary

The package accepts only the 131,072-byte cartridge payload from canonical
Metroid USA PRG0 (SHA-1 `fdbfc7871962f72a1ef57e5a7e456164fb93430b`)
or Europe/PAL (SHA-1 `68a55eafcefa3014a4771cb7983d7db42f80456a`).
The engine's `nes` external-ROM
normalizer accepts a headerless payload or a strict trainer-free iNES 1.0/2.0
container, strips the 16-byte header, and rejects wrong declared sizes,
truncation, trailing data, and NES 2.0 exponent encoding.

The consumed 1,968-byte Samus graphics block is identical in both revisions.
At activation, `game_samus.c` reads that CHR-RAM source block from
PRG bank 6 (`normalized PRG offset 0x18000`) into process memory. The executable,
mod manifest, and release archive contain no Metroid tiles or ROM bytes.

The behavioral reference is the m1disasm source at commit
`2ead7e54d20473e43900f1cfa00fe4cf67e69624`, cross-checked against the local
MetroidNESRecomp checkout. The mod is a clean-room host adaptation; it does not
copy Metroid executable code.

## Gameplay contract

- Metroid acceleration, traction, air control, variable-height High Jump,
  Morph Ball, bombs, Varia damage reduction, Screw Attack, and a combined
  Long/Wave/Ice beam.
- A Morph Ball inside its bomb's compact blast radius receives Metroid's
  `$FD` vertical knockback (3 px/frame upward) through the host adapter's
  force-airborne handshake, so successive bombs can chain boosts.
- Select toggles beam/missile mode. Missiles are unlimited but preserve the
  original one-missile-in-flight rule through the three-slot weapon pool.
- 99 maximum energy. Mushroom restores 30; Fire Flower restores all; 1-Up keeps
  native SMB behavior. Starman retains SMB's timer but defeats enemies on tight
  Samus-body contact.
- Enemy contact cannot stomp. It drains energy and grants a 60-frame damage
  grace period. Ordinary enemies die to weapons; Bowser is frozen as the
  multi-hit target and takes five missile/Screw hits before entering SMB's
  defeated-fall state.
- Beam ice freezes the multi-hit target for 300 ticks. Frozen position and
  velocity are held while SMB continues to own enemy allocation and rendering.
- Bombs, missiles, and airborne Screw Attack route through SMB's native brick
  shatter transaction and only accept metatiles `$51/$52`.
- SMB keeps its level geometry, enemies, pipes, flagpole, death/respawn,
  scrolling, progression, music, and Starman behavior. Metroid physics stays
  active in water instead of handing movement to SMB's swim routine.

## Architecture and tests

`game_samus_audio.c` reads Metroid's original APU register seeds from normalized
PRG offset `$3230`, replays the sound-driver changes into temporary PCM, and
registers it only for the active process. No extracted audio is written or
packaged.

`mods/metroid/samus_controller.c` is game-independent locomotion behind the
nesrecomp `ForeignController` ABI. `game_smash64.c` remains the shared SMB host
adapter because it already owns the proven per-pixel collision sweeps and guest
function hooks; identity gates prevent Falcon audio/rendering from running for
Samus. `game_samus.c` owns only character-specific combat, energy, projectiles,
freeze state, owner assets, HUD, and 2D presentation.

Focused validation:

```text
cmake -S tests/samus_harness -B build_samus_harness
cmake --build build_samus_harness
ctest --test-dir build_samus_harness --output-on-failure
```

The full executable build also proves the two preloaded packages, shared hook
router, generated guest hook guards, and renderer link together. The nesrecomp
`external_rom_gate_selftest` covers both headered and headerless NES
normalization in addition to the existing N64/raw cases.
