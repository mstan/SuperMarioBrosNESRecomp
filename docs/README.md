# Developer guides

Start with the [project README](../README.md#building-from-source) to build the
game and the [test guide](../tests/README.md) to choose a validation suite.
Paths mentioned in these guides are relative to the repository root unless
stated otherwise.

## Game integration

| Guide | Contents |
| --- | --- |
| [Debugging protocol](TCP.md) | TCP setup, client tools, game commands, and RAM symbols |
| [Widescreen](WIDESCREEN.md) | Renderer behavior, camera options, limits, and validation |
| [SMB1 player adapter](smb1_player_adapter.md) | Connecting foreign controllers to native SMB movement and collision |
| [Scripted handoffs](smb1_scripted_handoffs.md) | Pipes, death, swimming, and other native scripted states |

The handwritten integration lives in [`src/`](../src/). `extras.c` supplies
runner hooks; `game_*.c` connects mods to the game; `smb_ws_*.c` implements
widescreen world and actor support. Snapshot, verification, and watchdog code
also live here. Shared runtime services, including call-stack tracking, live
in the `nesrecomp` submodule.

## Character mods

| Guide | Contents |
| --- | --- |
| [Samus](METROID_SAMUS_MOD.md) | Metroid controller, owner-ROM graphics/audio, and QA |
| [Link](ZELDA2_LINK_MOD.md) | Zelda II controller, owner-ROM assets, and QA |
| [Falcon movement dependencies](falcon_movement_dependency.md) | Source mapping and bounded movement dependencies |
| [Falcon combat](falcon_combat.md) | Attacks and native SMB collision consequences |
| [Falcon audio](falcon_audio.md) | Audio sources and integration |
| [Pikachu behavior](pikachu_behavior_spec.md) | Controller behavior specification |
| [Pikachu owner parity](pikachu_owner_parity.md) | Asset and behavior parity notes |
| [Owner-ROM cache tooling](../tools/owner_ssb64/README.md) | Deriving local Smash 64 caches |
| [Third-party notices](../THIRD-PARTY-LICENSES/README.md) | Source attribution and licensing notes |

Controllers and plugin entry points are under [`mods/`](../mods/); launcher
catalog entries are under `mods/preloaded/packages/`.

## Historical reference

[Archived investigations](archive/README.md) retain older root-cause analyses
and session notes. They may describe superseded implementations and local QA
setups. Use the current source and guides above for new work.
