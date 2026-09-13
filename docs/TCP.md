# Super Mario Bros. debug server protocol

The TCP debug server is the debugging interface for this project. See the
[framework protocol reference](../nesrecomp/TCP.md) for shared commands.
This guide covers SMB-specific configuration and commands. Paths below are
relative to the repository root.

---

## Implementation and client

The server lives in `nesrecomp/runner/src/debug_server.c` and is built into
the runner when tracing is enabled. Game-specific command extensions are in
`src/extras.c::game_handle_debug_cmd()`. Use [`tools/dbg.py`](../tools/dbg.py)
to send commands from Python.

---

## Ports

| Server | Mode | Port |
|--------|------|------|
| Native recomp (SMB) | default / debug.ini | **127.0.0.1:4370** |
| Nestopia oracle (SMB) | `--emulated`, `--verify` | **127.0.0.1:4371** |

Port selection is in `src/extras.c::s_tcp_port`.

---

## Activation

Configure a diagnostic build with `-DNESRECOMP_ENABLE_TRACE=ON`; production
builds compile out the server. Then enable it with one of:
1. `debug.ini` file in the same directory as `SuperMarioBrosRecomp.exe`
2. `--verify` or `--emulated` CLI flags

---

## Game-Specific Commands

### `smb_state`
Returns current gameplay state. Only trace-verified fields are exposed.

```json
{
  "id": 1,
  "cmd": "smb_state",
  "oper_mode": 0,        // 0=title/demo, 1=gameplay, 2=victory, 3=game over (RAM 0x0770)
  "oper_task": 0,        // Sub-task within mode (RAM 0x0772)
  "player_x": 40,        // Mario X position (RAM 0x0086)
  "player_y": 176,       // Mario Y position (RAM 0x00CE)
  "score_hi": 0,         // (RAM 0x07FC)
  "score_mid": 0,        // (RAM 0x07FD)
  "score_lo": 0,         // (RAM 0x07FE)
  "lives": 2,            // NumberofLives (RAM 0x075A)
  "frame_counter": 42    // (RAM 0x0009)
}
```

Fields previously exposed but removed (they were mislabeled or read the
wrong RAM byte): `world`, `level`, `player_size`, `player_state`,
`area_type`. Use `read_ram` against the canonical addresses below if
you need them; [`symbols.sym`](../symbols.sym) records the symbolic addresses.

### `smb_demo_state`
Returns demo/attract mode timing.

```json
{
  "id": 1,
  "cmd": "smb_demo_state",
  "demo_timer": 0,       // (RAM 0x0776)
  "frame_counter": 42,   // (RAM 0x0009)
  "oper_mode": 0,
  "oper_task": 0
}
```

---

## Key SMB RAM Addresses

Canonical smbdis labels, trace-verified 2026-05-14. See
[`symbols.sym`](../symbols.sym) for the full symbol list.

| Address | Name | Notes |
|---------|------|-------|
| 0x0009 | FrameCounter | Increments every frame |
| 0x001D | Player_State | Physics state (0=on ground, nonzero=airborne) |
| 0x0033 | PlayerFacingDir | 0=none, 1=right, 2=left |
| 0x0045 | Player_MovingDir | 0=none, 1=right, 2=left |
| 0x0057 | Player_X_Speed | Signed velocity (integer part of 8.8 fixed-point) |
| 0x006D | Player_PageLoc | Player 256px page |
| 0x0086 | Player_X_Position | Pixel X within page |
| 0x009F | Player_Y_Speed | Signed Y velocity |
| 0x00CE | Player_Y_Position | Pixel Y |
| 0x0700 | Player_XSpeedAbsolute | Unsigned speed magnitude (cap 40 = running) |
| 0x0754 | PlayerSize | 0=tall, 1=short |
| 0x0756 | PlayerStatus | Powerup: 0=Small, 1=Big, 2=Fire |
| 0x075A | NumberofLives | Plus 1 for HUD display |
| 0x075E | CoinTally | 0..99 |
| 0x075F | WorldNumber | 0-indexed |
| 0x0760 | LevelNumber | 0-indexed |
| 0x0770 | OperMode | 0=title, 1=game, 2=victory, 3=game over |
| 0x0772 | OperMode_Task | Sub-task within mode |
| 0x0776 | DemoActionTimer | Demo playback timer |

**Historical note:** earlier versions of this file documented `$001D`
and `$0756` with swapped labels, and `$075A`/`$075C`/`$075E` as
world/level/area_type. Those were wrong; the table above reflects
verification against a recorded attract-demo trace.

---

## Python client

Run from the repository root against a diagnostic build:

```sh
python tools/dbg.py ping
python tools/dbg.py smb_state
python tools/dbg.py read_ram 0x075F 2
```

For reusable automated scenarios, see the [test guide](../tests/README.md).

---

## Common Workflow

```python
import socket, json, time

def send_cmd(cmd, port=4370):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(5)
    s.connect(('127.0.0.1', port))
    s.sendall((json.dumps(cmd) + '\n').encode())
    data = b''
    while b'\n' not in data:
        chunk = s.recv(4096)
        if not chunk: break
        data += chunk
    s.close()
    return json.loads(data.decode().strip())

# Get into gameplay
send_cmd({'cmd':'press','buttons':0x10,'frames':5,'id':1})   # Start
time.sleep(2)
send_cmd({'cmd':'press','buttons':0x10,'frames':5,'id':2})   # Start again

# Walk right
send_cmd({'cmd':'set_input','buttons':'01','id':3})           # Hold Right

# Check state
state = send_cmd({'cmd':'smb_state','id':4})

# Screenshot
send_cmd({'cmd':'screenshot','path':'check.png','id':5})

# Clean up
send_cmd({'cmd':'clear_input','id':6})
```

---

## Built-in Commands

See the [framework reference](../nesrecomp/TCP.md) for the full list. Key ones
for SMB work:

- `ping`, `frame` — heartbeat
- `smb_state`, `smb_demo_state` — game-specific state
- `read_ram`, `write_ram` — raw memory access
- `read_ppu`, `ppu_state` — PPU/nametable/palette inspection (raw)
- `read_nametable` — formatted 32×30 nametable grid + attribute table
- `dump_nametables` — full 4KB nametable dump in one call
- `read_palette` — formatted palette dump with BG/sprite groups
- `read_oam` — formatted sprite list (64 entries parsed)
- `read_chr` — CHR tile dump with optional 2-bitplane decode
- `scroll_info` — high-level effective scroll state (origin, split, mirror)
- `screenshot` — capture current frame as PNG
- `set_input`, `press`, `clear_input` — controller override
- `pause`, `continue`, `step`, `run_to_frame` — execution control
- `history`, `get_frame`, `frame_range` — ring buffer time-travel
- `frame_diff` — verify diffs for a frame, or compare two frames' full state
- `memory_diff` — compare current state vs historical frame (ram/nt/pal/oam/all)
- `watch`, `follow`, `follow_history` — write tracking
- `scroll_trace` — PPU scroll register history
