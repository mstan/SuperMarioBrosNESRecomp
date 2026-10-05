SMB1's migration branch defaults to the cycle backend. Select
`-DNESRECOMP_BACKEND=legacy` to build the retained legacy runner.

The local cycle preview preserves stock Mario, simultaneous co-op for two to
four players, adaptive widescreen, the voxel first-person camera, and the
Falcon, Pikachu, Link, Samus and Sonic replacement Mods. Their existing
verified owner-ROM extraction and caches remain in use. Enhancements are
selected in the launcher's Mods screen and start disabled.

The LyonHrt HD pack uses the framework's modern HD Mod provider. Windows
releases bundle `smb_hdpack_importer.exe`; run it with
`--pack <folder> --rom <stock-rom> --out <archive.nesmod>`, then install and
select the package in Mods. Source checkouts can use `tools/import_hdpack.py`.
The ROM and third-party pack assets are local inputs. Preserve any notices
supplied with your pack.

Cycle adapters invoke original guest routines through verified hook sites
and isolated calls; there is no second CPU. Character collision policies
override selected final RAM operand values while preserving the real bus
read. Four host input seats still feed a two-port physical NES. Sprite
replacement uses the captured physical background; native sprite evaluation
and sprite-zero timing continue in hardware. Replacement PCM and Sonic's
Genesis sound-board stream use the host audio mixer.

Validation on this branch:

- Stock CPU/trace/memory matched the independent TriCNES reference over
  3,000 frames at all four clock alignments.
- Stock, four-player co-op, 16:9 and 32:9 matched native/interpreter frame
  hashes, physical and composed pictures, and final saves over 1,000 frames.
- All five character Mods, voxel and modern HD matched native/interpreter
  pictures and complete middle/final saves over 1,000 frames.
- Co-op passed the existing shared gameplay rule fixtures and all 32 native
  campaign exit fixtures. These are boundary tests, not full playthroughs.
- Window checks covered independent fourth-seat movement/jumping, cached
  presentations, Fit at 1280×720, and rejected co-op saves without mutation.
- Stock and all five replacements produced exact native/interpreter mono
  PCM at 44,100 Hz. The explicit legacy build and its rule fixtures pass.
- Relocated SDL character builds include the verified owner-asset helper.
  All five replacements load matching full saves and show the exact active
  headless picture while paused. The common adapter restores its ownership
  latch before the next input tick.
- Actual displayed window pixels pass for HD at 512x480 and for the character
  previews. The host fits pictures below their presentation resolution and
  restores integer scaling after enlargement.

The owner accepted the local previews, including corrected Falcon, Pikachu
and modern HD builds. Windows cycle rollback now uses the shared lobby and
driver. Two-peer stock and four-peer co-op converged to identical complete
snapshots and pictures, including 23 forced rollback episodes; two lobby
launch/return/rematch rounds passed without desyncs. Both production ZIPs
booted from clean extracted directories and the bundled HD importer converted
the owner's local pack. These bounded checks do not qualify WAN play.

Integration still awaits the owner's online playtest and final dependency
pins. No migration merge has occurred. Windows and Linux enable online by
default; `SMB_ENABLE_NETPLAY=OFF` retains local-only builds.

Regenerate checked-in call aliases with `tools/generate_cycle_symbols.py`;
`--check` verifies them. The symbol map derives from the pinned SMB
disassembly. Cycle co-op fixtures run through
`tests/coop_cycle_runtime.py --suite rules|campaign --exe <exe> --rom <rom>`.
The existing legacy fixture programs remain available.
`tests/cycle_mod_runtime.py` checks a supplied local Mod root, active save and
headless picture in a relocated SDL build; it refuses silent Mario fallback.
