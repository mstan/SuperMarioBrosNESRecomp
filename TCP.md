# TCP.md — Super Mario Bros. Debug Server Protocol

The TCP debug server is the **only** sanctioned debugging interface for this
project. See `nesrecomp/TCP.md` for the full framework-level protocol
reference. This file covers SMB-specific configuration and commands.

---

## IMPORTANT — Finding the TCP Server

The TCP server lives in `nesrecomp/runner/src/debug_server.c`. It is built
into the runner, not a separate tool or external dependency. If you cannot
find it, you are searching in the wrong directory.

**Common failure mode in prior sessions:** Claude searched only the game
repo root or `extras.c`, failed to find TCP tooling, and incorrectly
concluded it didn't exist. The fix: always search inside
`nesrecomp/runner/src/` for `debug_server.c`. It is ~1750 lines and
contains the full implementation.

Game-specific command extensions are in `extras.c::game_handle_debug_cmd()`.
Python client scripts are the `tcp_*.py` files in the project root.

---

## Ports

| Server | Mode | Port |
|--------|------|------|
| Native recomp (SMB) | default / debug.ini | **127.0.0.1:4370** |
| Nestopia oracle (SMB) | `--emulated`, `--verify` | **127.0.0.1:4371** |

Port selection is in `extras.c::s_tcp_port` (line 41).

---

## Activation

Requires one of:
1. `debug.ini` file in the same directory as `SuperMarioBrosRecomp.exe`
2. `--verify` or `--emulated` CLI flags

---

## Game-Specific Commands

### `smb_state`
Returns current gameplay state.

```json
{
  "id": 1,
  "cmd": "smb_state",
  "oper_mode": 0,        // 0=title/demo, 1=gameplay, 2=victory, 3=game over
  "oper_task": 0,
  "world": 0,            // 0-indexed world number (RAM 0x075A)
  "level": 0,            // 0-indexed level number (RAM 0x075C)
  "player_x": 40,        // Mario X position (RAM 0x0086)
  "player_y": 176,       // Mario Y position (RAM 0x00CE)
  "player_size": 0,      // 0=big, 1=small (RAM 0x001D)
  "player_state": 0,     // (RAM 0x0756)
  "area_type": 0,        // (RAM 0x075E)
  "score_hi": 0,         // (RAM 0x07FC)
  "score_mid": 0,        // (RAM 0x07FD)
  "score_lo": 0,         // (RAM 0x07FE)
  "lives": 2,            // (RAM 0x075A — note: same as world, bug in extras.c)
  "frame_counter": 42    // (RAM 0x0009)
}
```

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

| Address | Name | Notes |
|---------|------|-------|
| 0x0009 | FrameCounter | Increments every frame |
| 0x001D | PlayerSize | 0=big, 1=small |
| 0x0086 | Player_X_Position | Pixel X within screen |
| 0x00CE | Player_Y_Position | Pixel Y |
| 0x006D | ScrollAmount (lo) | Horizontal scroll amount |
| 0x0756 | Player_State | Player state flags |
| 0x075A | WorldNumber | 0-indexed |
| 0x075C | LevelNumber | 0-indexed |
| 0x075E | AreaType | Area type code |
| 0x0770 | OperMode | 0=title, 1=game, 2=victory, 3=game over |
| 0x0772 | OperMode_Task | Sub-task within mode |
| 0x0776 | DemoActionTimer | Demo playback timer |

---

## Python Client Scripts

| Script | Purpose |
|--------|---------|
| `tcp_quick.py` | Minimal test: send `smb_state` |
| `tcp_test.py` | Basic ping and state check |
| `tcp_check.py` | Startup sequence (press Start twice, check state) |
| `tcp_run.py` | Hold Right+B, monitor position/camera |
| `tcp_screenshot.py` | Capture screenshot |
| `tcp_walk.py` | Walk right, read enemy/camera RAM |
| `tcp_input_test.py` | Test controller input mapping |
| `tcp_start_game.py` | Enter gameplay by pressing Start twice |
| `tcp_verify_input.py` | Verify input override mechanics |
| `tcp_validate_margins.py` | Walk right looking for margin-spawned enemies |

---

## Common Workflow

```python
import socket, json

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

See `nesrecomp/TCP.md` for the full list. Key ones for SMB work:

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
