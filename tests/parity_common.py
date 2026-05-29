"""Shared helpers for the byte-level object/OAM parity harness.

Captures slices of the runner's ALWAYS-ON post-NMI history ring over TCP
(127.0.0.1:4370) and diffs them between builds. The ring records every frame
from boot, so we QUERY a window — we never arm-then-record. The attract demo is
deterministic from boot, so a behavior-preserving build reproduces byte-identical
RAM/OAM at the same absolute frame.

Regions captured per frame (each <=256B = one read_frame_ram call; all are
slices of one coherent post-NMI record):
  oam  $0200-$02FF : sprite display list (DMA'd to PPU) — THE render output
  zp   $0000-$00FF : SprObject state (Enemy_Flag/ID/State/Pos/Vel, Player_*)
  r03  $0300-$03FF : relative-pos tables ($03AD/$03B8) + offscreen bits ($03D0)
  r06  $0600-$06FF : SprDataOffset region ($06E5 enemy / $06EC player / $06EA pu)
  r07  $0700-$07FF : camera ($071A-$071D) + OperMode ($0770/$0772)
($FE00 PPU OAM is just the deterministic DMA copy of $0200, and is stale under
--emulated, so we omit it — $0200 is the authoritative parity target.)
"""
import socket
import json
import zlib

HOST, PORT = "127.0.0.1", 4370

REGIONS = [
    ("oam", 0x0200, 256),
    ("zp", 0x0000, 256),
    ("r03", 0x0300, 256),
    ("r06", 0x0600, 256),
    ("r07", 0x0700, 256),
]


class Conn:
    def __init__(self, host=HOST, port=PORT, timeout=10):
        self.s = socket.socket()
        self.s.settimeout(timeout)
        self.s.connect((host, port))
        self.rx = b""

    def call(self, cmd, **kw):
        p = {"cmd": cmd, "id": 1}
        p.update(kw)
        self.s.sendall((json.dumps(p) + "\n").encode())
        while b"\n" not in self.rx:
            chunk = self.s.recv(65536)
            if not chunk:
                raise RuntimeError("debug socket closed")
            self.rx += chunk
        line, self.rx = self.rx.split(b"\n", 1)
        return json.loads(line.decode(errors="replace").strip())

    def close(self):
        try:
            self.s.close()
        except OSError:
            pass


def read_region(conn, frame, addr, length):
    out = bytearray()
    cur, rem = addr, length
    while rem > 0:
        n = min(rem, 256)
        r = conn.call("read_frame_ram", frame=frame, addr=f"0x{cur:04X}", len=n)
        if not r.get("ok"):
            raise RuntimeError(f"read_frame_ram fail f={frame} a=0x{cur:04X}: {r}")
        out += bytes.fromhex(r["hex"])
        cur += n
        rem -= n
    return bytes(out)


def crc(b):
    return f"0x{zlib.crc32(b) & 0xFFFFFFFF:08x}"


def history(conn):
    h = conn.call("history")
    if not h.get("ok"):
        raise RuntimeError(f"history failed: {h}")
    return int(h["oldest"]), int(h["newest"])


def gd_oper(gd_hex):
    """(oper_mode, oper_task) from the 16-byte game_data hex (extras.c layout)."""
    b = bytes.fromhex(gd_hex)
    return b[0], b[1]


def pull_timeseries(conn, start, end):
    """frame_timeseries in <=200-frame chunks -> {frame: gd_hex}."""
    out = {}
    s = start
    while s <= end:
        e = min(s + 199, end)
        r = conn.call("frame_timeseries", start=s, end=e)
        for entry in r.get("ts", []):
            if entry:
                out[entry["f"]] = entry["gd"]
        s = e + 1
    return out
