#!/usr/bin/env python3
"""One-shot deep diagnostic: for each embedded enemy, show whether the
vanilla-equivalent X (wide_x - right_margin) is clear, scanning left."""
import socket, json
s = socket.socket(); s.settimeout(5); s.connect(("127.0.0.1", 4370))


def call(cmd, **kw):
    s.sendall((json.dumps({"cmd": cmd, "id": 1, **kw}) + "\n").encode())
    buf = b""
    while b"\n" not in buf:
        buf += s.recv(65536)
    return json.loads(buf.split(b"\n", 1)[0])


def read(addr, n):
    return bytes.fromhex(call("read_ram", addr=f"0x{addr:04X}", len=n)["hex"])


PASSABLE = {0x00, 0x26, 0xC2, 0xC3, 0x5F, 0x60}
bb = read(0x0500, 0x200)


def mt(page, xlo, y):
    base = 0xD0 if (page & 1) else 0
    idx = (base + (((xlo >> 4) + (((y & 0xF0) - 0x20) & 0xFF)) & 0xFF))
    return bb[idx] if 0 <= idx < len(bb) else -1


def solid(wx, y):
    return mt((wx >> 8) & 0xFF, wx & 0xFF, y) not in PASSABLE


def torso(wx, y):
    return any(solid((wx + dx) & 0xFFFF, (y + dy) & 0xFF)
               for dx, dy in ((2, 4), (13, 4), (2, 8), (13, 8), (2, 12), (13, 12), (8, 8)))


ws = call("smb_ws_state")
right = ws["right"]; cam = ws["camera_x"]
print("right", right, "cam", cam, "oper_mode", ws["oper_mode"],
      "corr_applied", ws.get("corr_applied"), "embed_detect", ws.get("embed_detect"))
pages = read(0x6E, 5); xlos = read(0x87, 5); ys = read(0xCF, 5)
ids = read(0x16, 5); flags = read(0x0F, 5); states = read(0x1E, 5)
for i in range(5):
    if not flags[i]:
        continue
    wx = (pages[i] << 8) | xlos[i]; y = ys[i]
    e = torso(wx, y)
    print(f"slot{i} id={ids[i]} state=0x{states[i]:02x} world=({wx:#06x},{y}) torso_emb={e}")
    if e:
        van = (wx - right) & 0xFFFF
        print(f"   wide_x={wx:#06x} emb={torso(wx, y)} | vanilla_x={van:#06x} emb={torso(van, y)}")
        for dx in range(0, right + 33, 16):
            cx = (wx - dx) & 0xFFFF
            row = " ".join(f"{mt((cx + ox) >> 8 & 0xFF, (cx + ox) & 0xFF, y + oy):02x}"
                           for ox, oy in ((2, 4), (13, 4), (8, 8), (2, 12), (13, 12)))
            print(f"     x-{dx:3d}={cx:#06x} emb={int(torso(cx, y))}  mt[{row}]")
