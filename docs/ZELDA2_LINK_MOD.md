# Zelda II Link Player Replacement

This package replaces SMB1's player presentation and player-controlled
locomotion with side-view Link from Zelda II. SMB1 still owns the world,
collision, scrolling, enemies, music, scripts, lives and level progression.

## Source Gate

The upstream `FiendsOfTheElements/z2disassembly` checkout was not byte-exact
against the supplied ROM as cloned. It rebuilt with missing bank-end trampoline
bytes, a bank 7 branch-length mismatch, and only 14 CHR banks in the generated
iNES header/output.

Before using it as a source, the local reference copy was reconciled and then
rebuilt byte-for-byte against:

```text
E:\Downloads\Zelda II_ The Adventure of Link.zip
Zelda II - The Adventure of Link (USA).nes
SHA-256 AD8C0FBCF092BF84B48E69FD3964EEA4ED91BFE62ABC352943D537979782680C
```

That validated local source is the basis for the constants and display tables
used here.

## Player Behavior

`mods/zelda2/link_controller.c` implements a clean-room controller behind the
nesrecomp `ForeignController` ABI:

- A jumps, with Zelda II-style lower gravity while A is held.
- B slashes with Zelda II's standing/crouched startup and active timing.
- Down crouches on the ground.
- Up or Down with B in the air produces vertical stab hitboxes.
- Sword hitboxes defeat enemies and set `FOREIGN_ATTACK_BREAK_BLOCKS`, an
  intentional SMB-host liberty so Link can cut ordinary breakable bricks.

The jump impulse is slightly higher than Zelda II's native side-view value so
Link clears SMB1 terrain at roughly Mario-compatible heights.

## Owner-ROM Assets

`game_link.c` extracts Link's CHR from the verified Zelda II owner ROM at
runtime. No Zelda II ROM bytes or derived graphics are committed or shipped.

The package accepts headered iNES and headerless PRG+CHR images that normalize
to:

```text
size 262144
sha1 11333adb723a5975e0ecca3aee8f4747aa8d2d26
```

## Validation

Focused controller/profile validation:

```text
cmake -S tests/link_harness -B build_link_harness
cmake --build build_link_harness
build_link_harness\link_controller_harness.exe

cmake -S tests/smash64_profile -B build_smash64_profile
cmake --build build_smash64_profile
build_smash64_profile\smash64_fighter_profile_test.exe
```

The full executable build also proves the new preloaded package, static
activation plugin, owner-ROM gate metadata, shared SMB adapter hooks, Link CHR
loader, and Link renderer all compile and link together.
