# Online play (rollback netplay)

Super Mario Bros. plays online over rollback netplay: two to four players of
[simultaneous co-op](SIMULTANEOUS_COOP.md), or the original 1P/2P game, with
recomp-net's episode driver hiding up to the prediction runway of network
latency. The engine side -- snapshots, digests, the replay model, the harness
and the measured capability matrix -- is documented in
[nesrecomp docs/NETPLAY.md](../nesrecomp/docs/NETPLAY.md); this page is what
is specific to this game.

Status (2026-09-25): built and measured on Linux, headless, over loopback and a
local lobby server. **Not played by a human yet**, not run between two
machines, and not built or run on Windows/macOS (netplay is on by default only
for Linux builds, `SMB_ENABLE_NETPLAY`).

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
| `widescreen` | `0` / `1` | its display setting; forced `0` while co-op is on (the package excludes widescreen) |

The lobby publishes the host's offer in the room's match caps; the rollback
driver's mod-set handshake then confirms every peer is running exactly the same
text and refuses the match (`mod_set_not_agreed`) otherwise. Everything else a
mod could change is not allowed to differ, because it is not there.

Input scripts, input recording, `--loadstate`, quick states, turbo and the TCP
debug server's execution-control verbs are refused while a session is active.

## Testing

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
