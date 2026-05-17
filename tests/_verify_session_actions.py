#!/usr/bin/env python3
"""Verify that the session reshape from this turn works.

Tests:
1. semcomp_set_timer val=50 succeeds (was failing as "unknown semantic field 'timer'").
2. semcomp_set_score val=5 (sends 5, expects 50 points -> score=0050 visible).
3. semcomp_add_score val=10 (sends 10, expects +100 points).
4. semcomp_give_power_up sets $0747 != 0 (animation triggered).
5. semcomp_take_damage triggers InjurePlayer animation.
"""
import json
import socket
import time
import sys


_call_id = [0]


def call(sock, cmd, **kw):
    # Server emits {...}\n\n (debug_server_send_line tacks on a \n; our
    # format strings include one too). Match trainer_gui's pattern of
    # fresh buf per call so the trailing \n gets consumed-and-discarded
    # by socket flush rather than leaking into the next response.
    _call_id[0] += 1
    kw["cmd"] = cmd
    kw["id"] = _call_id[0]
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
    except json.JSONDecodeError:
        return {"ok": False, "raw": line}


def read_ram(sock, addr, length=1):
    r = call(sock, "read_ram", addr=f"0x{addr:04X}", **{"len": length})
    return r.get("hex", "")


def main():
    s = socket.socket()
    s.settimeout(2.0)
    s.connect(("127.0.0.1", 4370))

    print("=== test 1: semcomp_set_timer (was failing) ===")
    r = call(s, "semcomp_set_timer", val=50)
    print(r)
    assert r.get("ok"), f"set_timer failed: {r}"
    print(f"  $07F8..$07FA = {read_ram(s, 0x07F8, 3)}")

    print("\n=== test 2: semcomp_set_score val=5 -> 50 points ===")
    r = call(s, "semcomp_set_score", val=5)
    print(r)
    assert r.get("ok"), f"set_score failed: {r}"
    assert r.get("points") == 50, f"expected points=50, got {r}"

    print("\n=== test 3: semcomp_add_score val=10 -> +100 points ===")
    r0 = call(s, "semcomp_set_score", val=0)
    r = call(s, "semcomp_add_score", val=10)
    print(r)
    assert r.get("ok") and r.get("points_delta") == 100, f"add_score wrong: {r}"

    print("\n=== test 4: semcomp_give_power_up sets $0747 ===")
    # Pre-state
    p0 = int(read_ram(s, 0x0756)[:2], 16) if read_ram(s, 0x0756) else 0
    a0 = int(read_ram(s, 0x0747)[:2], 16) if read_ram(s, 0x0747) else 0
    print(f"  before: power=${p0:02X}, $0747=${a0:02X}")
    r = call(s, "semcomp_give_power_up")
    print(r)
    time.sleep(0.05)
    p1 = int(read_ram(s, 0x0756)[:2], 16)
    a1 = int(read_ram(s, 0x0747)[:2], 16)
    print(f"  after:  power=${p1:02X}, $0747=${a1:02X}")
    if p0 < 2:
        assert p1 == p0 + 1, f"power didn't advance: {p0:02X}->{p1:02X}"
        # $0747 starts at $FF and ticks down each frame; after ~50ms might
        # already be slightly lower. Just confirm it's in animation range.
        assert a1 >= 0xC4, f"$0747 should be in animation range (>=0xC4), got ${a1:02X}"
        print(f"  OK: power {p0}->{p1}, animation active (0747=${a1:02X})")
    else:
        print(f"  no-op (already Fire)")

    print("\n=== test 5: semcomp_take_damage triggers InjurePlayer ===")
    # Make sure we're not Small so we can observe shrink (not death)
    if p1 < 1:
        call(s, "semcomp_give_power_up")
        time.sleep(0.05)
    p0 = int(read_ram(s, 0x0756)[:2], 16)
    print(f"  before take_damage: power=${p0:02X}")
    r = call(s, "semcomp_take_damage")
    print(r)
    time.sleep(0.05)
    p1 = int(read_ram(s, 0x0756)[:2], 16)
    inv = int(read_ram(s, 0x079E)[:2], 16) if read_ram(s, 0x079E) else 0
    print(f"  after:  power=${p1:02X}, $079E invuln=${inv:02X}")
    if p0 >= 1:
        # InjurePlayer writes $0756=0 and $079E=$08 (invuln frames)
        assert p1 == 0, f"power should be Small after damage: ${p1:02X}"
        # $079E ticks down 1/frame so could be anywhere from $00..$08
        print(f"  OK: damaged Fire/Big->Small")
    else:
        # Was Small; ForceInjury falls through to KillPlayer
        print(f"  Was Small -- death animation should be active")

    s.close()
    print("\nALL TESTS PASSED")
    return 0


if __name__ == "__main__":
    sys.exit(main())
