#!/usr/bin/env python3
"""Poll semcomp_enemies in a loop. Prints any change in active_count or
slot data. Run this in a terminal while playing — when a Goomba spawns,
the probe will print the slot state.

Stop with Ctrl-C."""
import json, socket, time, sys


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

    last_sig = None
    print("Polling... (Ctrl-C to stop)")
    while True:
        r = call(s, "semcomp_enemies")
        if not r.get("ok"):
            print(f"ERR: {r}")
            time.sleep(0.5)
            continue
        # Signature for change-detection.
        sig = (r.get("active_count"),
               tuple((e.get("slot"), e.get("active"), e.get("id"),
                      e.get("state"), e.get("world_x"))
                     for e in r.get("slots", [])))
        if sig != last_sig:
            ts = time.strftime("%H:%M:%S")
            ac = r.get("active_count")
            print(f"\n[{ts}] active_count={ac}")
            for entry in r.get("slots", []):
                if entry.get("active"):
                    print(f"  slot {entry['slot']}: "
                          f"id=0x{entry.get('id',0):02X} "
                          f"state=0x{entry.get('state',0):02X} "
                          f"wx={entry.get('world_x')} y={entry.get('y')} "
                          f"xv={entry.get('x_vel')} yv={entry.get('y_vel')}")
            last_sig = sig
        time.sleep(0.2)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\nstopped")
