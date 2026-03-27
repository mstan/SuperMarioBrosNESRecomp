#!/usr/bin/env python3
"""
dbg.py — TCP debug client for NES recomp projects.

Usage:
    python dbg.py <command> [args...]
    python dbg.py ping
    python dbg.py frame
    python dbg.py get_registers
    python dbg.py read_ram 0x0012 16
    python dbg.py dump_ram 0x0000 2048
    python dbg.py write_ram 0x0012 0xFF
    python dbg.py read_ppu 0x2000 64
    python dbg.py mapper_state
    python dbg.py watch 0x0012
    python dbg.py unwatch 0x0012
    python dbg.py set_input 0x80       # hold A button
    python dbg.py clear_input
    python dbg.py pause
    python dbg.py continue
    python dbg.py step 5
    python dbg.py run_to_frame 1000
    python dbg.py history
    python dbg.py get_frame 500
    python dbg.py frame_range 100 200
    python dbg.py first_failure
    python dbg.py faxanadu_state
    python dbg.py entity_table
    python dbg.py ppu_state
    python dbg.py call_stack
    python dbg.py quit
"""
import socket
import sys
import json

HOST = "127.0.0.1"
PORT = 4370

def send_cmd(cmd_name, **kwargs):
    """Send a JSON command and return the parsed response."""
    msg = {"id": 1, "cmd": cmd_name}
    msg.update(kwargs)

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.settimeout(5.0)
    try:
        sock.connect((HOST, PORT))
        sock.sendall((json.dumps(msg) + "\n").encode())

        # Read response (newline-terminated)
        buf = b""
        while b"\n" not in buf:
            chunk = sock.recv(4096)
            if not chunk:
                break
            buf += chunk

        lines = buf.decode().strip().split("\n")
        for line in lines:
            try:
                resp = json.loads(line)
                print(json.dumps(resp, indent=2))
            except json.JSONDecodeError:
                print(line)
    except ConnectionRefusedError:
        print(f"ERROR: Cannot connect to {HOST}:{PORT}. Is the game running?")
        sys.exit(1)
    except socket.timeout:
        print("ERROR: Timeout waiting for response")
        sys.exit(1)
    finally:
        sock.close()


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)

    cmd = sys.argv[1]
    args = sys.argv[2:]

    # Build kwargs based on command
    kwargs = {}
    if cmd == "read_ram" and len(args) >= 1:
        kwargs["addr"] = args[0]
        if len(args) >= 2:
            kwargs["len"] = int(args[1])
    elif cmd == "dump_ram" and len(args) >= 1:
        kwargs["addr"] = args[0]
        if len(args) >= 2:
            kwargs["len"] = int(args[1])
    elif cmd == "write_ram" and len(args) >= 2:
        kwargs["addr"] = args[0]
        kwargs["val"] = args[1]
    elif cmd == "read_ppu" and len(args) >= 1:
        kwargs["addr"] = args[0]
        if len(args) >= 2:
            kwargs["len"] = int(args[1])
    elif cmd == "watch" and len(args) >= 1:
        kwargs["addr"] = args[0]
    elif cmd == "unwatch" and len(args) >= 1:
        kwargs["addr"] = args[0]
    elif cmd == "set_input" and len(args) >= 1:
        kwargs["buttons"] = args[0]
    elif cmd == "step" and len(args) >= 1:
        kwargs["count"] = int(args[0])
    elif cmd == "run_to_frame" and len(args) >= 1:
        kwargs["frame"] = int(args[0])
    elif cmd == "get_frame" and len(args) >= 1:
        kwargs["frame"] = int(args[0])
    elif cmd == "frame_range" and len(args) >= 2:
        kwargs["start"] = int(args[0])
        kwargs["end"] = int(args[1])

    send_cmd(cmd, **kwargs)


if __name__ == "__main__":
    main()
