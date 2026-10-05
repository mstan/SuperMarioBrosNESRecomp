# Online play (rollback netplay)

Super Mario Bros. plays online over rollback netplay: two to four players of
[simultaneous co-op](SIMULTANEOUS_COOP.md), or the original 1P/2P game, with
recomp-net's episode driver hiding up to the prediction runway of network
latency. The engine side -- snapshots, digests, the replay model, the harness
and the measured capability matrix -- is documented in
[nesrecomp docs/NETPLAY.md](../nesrecomp/docs/NETPLAY.md); this page is what
is specific to this game.

Cycle migration status: built on Windows with the shared recomp-net lobby and
rollback driver. Focused local checks passed two-peer stock, four-peer co-op
with 23 forced rollback episodes, and two LAN lobby/rematch rounds. All peers
converged to identical complete cycle snapshots and pictures without desyncs.
Human online playtest is pending; separate-machine/WAN and macOS qualification
remain outstanding. Netplay defaults on for Windows and Linux builds.

## Seats

A room seats up to four players. Session slot == lobby seat == controller
port == character: seat 1 is Mario (port 1; Start and pause), seat 2 Luigi,
seat 3 Wario, seat 4 Waluigi. A player who moves seats changes characters.
Every seat's input comes only from the rows the peers publish; a peer's own
controllers drive its own seat through its player-1 device.

## What a match agrees on

A netplay launch commits **no mods** (the player's offline selection is not
touched) and runs the host's *session configuration* on every peer, applied
before boot and never saved:

| Key | Values | Host's offer |
| --- | --- | --- |
| `coop` | `0:player`, or `2..4:player` / `2..4:shared` | its offline selection of **Mods → Gameplay → Simultaneous Co-op** |
| `vw` (cycle) | fixed even width, 256..864 | the host's selected aspect; Fit settles at 16:9 online, and co-op uses 256 |
| `ws` (cycle) | enabled, HUD, enemy policy, camera | its offline widescreen options; forced off while co-op is on |
| `widescreen` (legacy) | `0` / `1` | the older host's display setting |

The lobby publishes the host's offer in the room's match caps; the rollback
driver's mod-set handshake then confirms every peer is running exactly the same
text and refuses the match (`mod_set_not_agreed`) otherwise. Everything else a
mod could change is not allowed to differ, because it is not there.

Cycle input scripts and `--load-state` are refused online. The menu keeps the
match running while sending neutral local input; it locks Mods and save/load
states. Resizing a window changes only its displayed size, since all peers run
the agreed width. Replay restores the full cycle hardware and enhancement
state and all four logical input seats; it displays and plays no replay frames.

The cycle snapshot domain is about 4 MB for this build (the shared ring retains
40 snapshots by default). A guest boots with the host's cartridge storage and
never reads or writes its personal save. Executable and ROM identities must
agree before the match; the legacy and cycle backends cannot share a match.

## Testing

Use a bounded cycle check with retained logs and exact complete-state
comparison. `--window-peer` runs the last peer through hidden SDL; the other
peers use the headless host. Rollback injection belongs to the host only.

```sh
python tests/cycle_netplay.py --exe build-cycle/Release/SuperMarioBrosRecomp.exe \
    --rom smb.nes --out cycle-net-qa --case widescreen --rollback --window-peer
```

The older legacy harnesses remain available:

```sh
# offline determinism probe over 4-player co-op gameplay (trace build)
python tests/netplay/gen_probe_script.py --players 4 coop4.script
NES_RB_PROBE=100:45:60:7 build/SuperMarioBrosRecomp smb.nes --coop 4 \
    --script coop4.script --smoke 1000000

# four processes, one match, exact ledger + confirmed-frame comparison
RB_LOOPBACK_SEATS=4 RB_LOOPBACK_SESSION='nes-session/1;coop=4:player;widescreen=0;' \
    nesrecomp/tools/rb_loopback.sh build/SuperMarioBrosRecomp smb.nes 60 45

# the whole matrix
RB_SWEEP_PROBE_SCRIPT=coop4.script RB_SWEEP_PROBE_ARGS="--coop 4" \
    nesrecomp/tools/rb_sweep.sh build/SuperMarioBrosRecomp smb.nes 45
```

`tests/coop_package.py --net-enabled` checks that an online launch seals the
co-op mode into the session and that scripts are refused online.
