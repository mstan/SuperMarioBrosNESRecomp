#!/usr/bin/env python3
"""Probe semcomp_enemies + raw RAM at the enemy slot bases. Compare what
the C++ facade reports against the raw bytes the TCP read_ram returns.

Run with the game already in a level with a visible Goomba/Koopa."""
import json, socket, sys


def call(sock, cmd, **kw):
    kw["cmd"] = cmd
    kw.setdefault("id", 1)
    sock.sendall((json.dumps(kw) + "\n").encode())
    buf = b""
    while b"\n" not in buf:
        chunk = sock.recv(65536)
        if not chunk: break
        buf += chunk
    line = buf.split(b"\n", 1)[0].decode(errors="replace").strip()
    if not line:
        return {"ok": False, "raw": "(empty)"}
    try:
        return json.loads(line)
    except json.JSONDecodeError as e:
        return {"ok": False, "raw": line, "err": str(e)}


def main():
    s = socket.socket(); s.settimeout(2.0)
    s.connect(("127.0.0.1", 4370))

    print("=== semcomp_enemies ===")
    r = call(s, "semcomp_enemies")
    print(json.dumps(r, indent=2))

    print("\n=== Raw RAM at enemy slot bases ($000F+, $0016+, $001E+, $006E+, $0087+, $00CF+) ===")
    for base, name in [(0x000F, "Flag"), (0x0016, "ID"), (0x001E, "State"),
                       (0x0058, "XSpd"), (0x006E, "PageLoc"),
                       (0x0087, "X"), (0x00B6, "YVel"), (0x00CF, "Y")]:
        r = call(s, "read_ram", addr=f"0x{base:04X}", **{"len": 5})
        print(f"  ${base:04X} {name:8s}: {r.get('hex', '?')}")


if __name__ == "__main__":
    main()
