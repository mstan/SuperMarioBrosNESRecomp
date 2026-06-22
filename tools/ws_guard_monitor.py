#!/usr/bin/env python3
"""
ws_guard_monitor.py — READ-ONLY widescreen guard monitor.

Watches the live TCP debug server while a human plays.  Does NOT touch
input.  Logs:
  * every change in corr_applied (mode-B birth-quarantine corrector
    nudging a group spawn out of geometry — expected, benign),
  * every change in embed_detect (a torso-embed that slipped PAST the
    quarantine — the residual-bug signal, should stay ~0),
  * any ACTIVE enemy torso-embedded in solid geometry for >~0.3s, with
    world pos / on-screen X / frame,
  * any ACTIVE, alive enemy that sits world-stationary >~1.4s while
    on screen (behavioural "stuck" signal).
Heartbeat every 5s with totals.  Run while the game is up:
  python tools/ws_guard_monitor.py [seconds]   (default 900)
"""
import json, socket, sys, time

HOST, PORT = "127.0.0.1", 4370
PASSABLE = {0x00, 0x26, 0xC2, 0xC3, 0x5F, 0x60}


class Dbg:
    def __init__(self, wait_s=0):
        # Patiently wait (in-process; the shell `sleep` is blocked here) for
        # the game's TCP server to come up — it only starts once the game is
        # booted from the launcher, so the human can take their time.
        deadline = time.time() + wait_s
        while True:
            try:
                self.s = socket.socket(); self.s.settimeout(10.0)
                self.s.connect((HOST, PORT)); self.buf = b""
                return
            except OSError:
                if time.time() >= deadline:
                    raise
                time.sleep(1.0)

    def call(self, cmd, **kw):
        self.s.sendall((json.dumps({"cmd": cmd, "id": 1, **kw}) + "\n").encode())
        while True:
            while b"\n" not in self.buf:
                ch = self.s.recv(65536)
                if not ch:
                    raise RuntimeError("connection closed")
                self.buf += ch
            line, self.buf = self.buf.split(b"\n", 1)
            if line.strip():
                return json.loads(line)

    def read(self, addr, n):
        return bytes.fromhex(self.call("read_ram", addr=f"0x{addr:04X}", len=n)["hex"])

    def frame(self):
        return self.call("frame")["frame"]


def metatile(bb, page, x_lo, y):
    base = 0x05D0 if (page & 1) else 0x0500
    idx = (base + (((x_lo >> 4) + (((y & 0xF0) - 0x20) & 0xFF)) & 0xFF)) - 0x0500
    return bb[idx] if 0 <= idx < len(bb) else 0


def solid(bb, wx, y):
    return metatile(bb, (wx >> 8) & 0xFF, wx & 0xFF, y) not in PASSABLE


def embedded(bb, wx, y):
    """Torso/side overlap (NOT feet) — matches the C ws_torso_embedded test."""
    pts = ((2, 4), (13, 4), (2, 8), (13, 8), (2, 12), (13, 12), (8, 8))
    return any(solid(bb, (wx + dx) & 0xFFFF, (y + dy) & 0xFF) for dx, dy in pts)


def log(msg):
    print(f"[{time.strftime('%H:%M:%S')}] {msg}", flush=True)


def main():
    dur = float(sys.argv[1]) if len(sys.argv) > 1 else 900.0
    log("waiting for game/TCP server on 4370 — start the widescreen game in the launcher...")
    try:
        d = Dbg(wait_s=3300)
    except OSError:
        log("gave up waiting — game never booted within the window. Re-run me once you're in a level.")
        return
    ws = d.call("smb_ws_state")
    log(f"monitor up — margins {ws['left']}L/{ws['right']}R, "
        f"detect field={'embed_detect' in ws}. Watching {dur:.0f}s. Play now.")
    det = ws.get("embed_detect", 0); corr = ws.get("corr_applied", 0)
    emb = {}; still = {}; lastwx = {}; reported_emb = set(); reported_stuck = set()
    last_hb = 0
    start = time.time()
    try:
        while time.time() - start < dur:
            ws = d.call("smb_ws_state")
            if ws.get("corr_applied", 0) != corr:
                corr = ws.get("corr_applied", 0)
                log(f".. CORRECTOR nudged spawn -> corr_applied={corr} "
                    f"(oper_mode={ws['oper_mode']}, frame={d.frame()})")
            if ws.get("embed_detect", 0) != det:
                det = ws.get("embed_detect", 0)
                log(f"!! RESIDUAL EMBED (past quarantine) embed_detect={det} "
                    f"(oper_mode={ws['oper_mode']}, frame={d.frame()})")
            if ws["oper_mode"] == 1:
                pages = d.read(0x6E, 5); xlos = d.read(0x87, 5); ys = d.read(0xCF, 5)
                states = d.read(0x1E, 5); flags = d.read(0x0F, 5); bb = d.read(0x0500, 0x200)
                cam = ws["camera_x"]
                for i in range(5):
                    if not flags[i]:
                        emb[i] = still[i] = 0; lastwx.pop(i, None); continue
                    wx = (pages[i] << 8) | xlos[i]; y = ys[i]; dead = bool(states[i] & 0xE0)
                    emb[i] = emb.get(i, 0) + 1 if embedded(bb, wx, y) else 0
                    if emb[i] == 4 and not dead and (i, wx) not in reported_emb:
                        reported_emb.add((i, wx))
                        log(f"!! EMBEDDED slot{i} id={ws['enemies'][i].get('id')} "
                            f"world=({wx:#06x},{y}) screenX={wx-cam} frame={d.frame()}")
                        # Clearance analysis: is the vanilla-equivalent X (wx-right)
                        # clear at this Y, and how far left must we go to clear?
                        rt = ws['right']
                        van = (wx - rt) & 0xFFFF
                        clr = next((dx for dx in range(0, rt + 33, 16)
                                    if not embedded(bb, (wx - dx) & 0xFFFF, y)), None)
                        log(f"   CLEAR-SCAN y={y} right={rt} vanilla_x={van:#06x} "
                            f"emb@vanilla={int(embedded(bb, van, y))} "
                            f"first_clear_dx={clr} "
                            f"(0=already clear, None=no clear within margin)")
                    if i in lastwx and abs(wx - lastwx[i]) <= 1 and not dead:
                        still[i] = still.get(i, 0) + 1
                        if still[i] == 18 and -ws['left'] < (wx-cam) < 256+ws['right'] \
                           and (i, wx) not in reported_stuck:
                            reported_stuck.add((i, wx))
                            log(f"!! STUCK   slot{i} id={ws['enemies'][i].get('id')} "
                                f"world=({wx:#06x},{y}) screenX={wx-cam} frame={d.frame()}")
                    else:
                        still[i] = 0
                    lastwx[i] = wx
            if time.time() - last_hb > 5:
                last_hb = time.time()
                log(f"... mode={ws['oper_mode']} cam={ws['camera_x']} "
                    f"corr_applied={corr} embed_detect={det} "
                    f"embedded_seen={len(reported_emb)} stuck_seen={len(reported_stuck)}")
            time.sleep(0.1)
    except (RuntimeError, OSError) as e:
        log(f"connection ended ({e}) — game closed?")
    log(f"DONE — corr_applied={corr} embed_detect={det} "
        f"embedded_seen={len(reported_emb)} stuck_seen={len(reported_stuck)}")


if __name__ == "__main__":
    main()
