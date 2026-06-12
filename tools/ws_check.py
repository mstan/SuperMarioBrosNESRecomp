#!/usr/bin/env python3
"""
ws_check.py — widescreen verification probe for SuperMarioBrosRecomp.

Drives Mario through 1-1 over the TCP debug server while sampling enemy
state, camera, and the OAM sidecar every few frames.  Asserts the three
historical widescreen failure modes never occur:

  1. WRAP GHOST — a sprite belonging to an enemy whose true screen X is in
     a margin renders inside the vanilla viewport at (true & 0xFF), i.e.
     teleports to the opposite edge.
  2. SPAWN POP — an enemy materializes at a screen X already visible inside
     the widened viewport (must spawn at/right of the widened right edge).
  3. DESPAWN POP — an enemy vanishes while visible in the widened viewport
     without being in a defeat state.

Run the game first:
  build_debug\\SuperMarioBrosRecomp.exe baserom.nes --widescreen 16:9
  (with debug.ini present next to the exe)
Then:  python tools/ws_check.py

Exit code 0 = all checks passed.
"""
import json
import socket
import sys
import time

HOST, PORT = "127.0.0.1", 4370

BTN_A, BTN_RIGHT, BTN_START = 0x80, 0x01, 0x10


class Dbg:
    def __init__(self):
        self.s = socket.socket()
        self.s.settimeout(10.0)
        self.s.connect((HOST, PORT))
        self.buf = b""

    def call(self, cmd, **kw):
        msg = {"cmd": cmd, "id": 1, **kw}
        self.s.sendall((json.dumps(msg) + "\n").encode())
        while True:
            while b"\n" not in self.buf:
                chunk = self.s.recv(65536)
                if not chunk:
                    raise RuntimeError("connection closed")
                self.buf += chunk
            line, self.buf = self.buf.split(b"\n", 1)
            if line.strip():
                return json.loads(line)

    def read(self, addr, n):
        r = self.call("read_ram", addr=f"0x{addr:04X}", len=n)
        return bytes.fromhex(r["hex"])

    def frame(self):
        return self.call("frame")["frame"]


def main():
    d = Dbg()
    ws = d.call("smb_ws_state")
    if not ws.get("enabled"):
        print("FAIL: widescreen not enabled in the running game")
        return 2
    left, right = ws["left"], ws["right"]
    print(f"widescreen margins: {left}L/{right}R  mode={ws['oper_mode']}")

    # --- reach gameplay: press START on the title screen ---
    deadline = time.time() + 30
    while ws["oper_mode"] != 1:
        d.call("press", buttons=BTN_START, frames=4)
        time.sleep(0.3)
        ws = d.call("smb_ws_state")
        if time.time() > deadline:
            print("FAIL: never reached gameplay mode")
            return 2
    print(f"in gameplay at frame {d.frame()}")
    time.sleep(2.5)  # level intro

    wrap_ghosts = []
    spawn_pops = []
    despawn_pops = []
    margin_draws = 0          # sprites correctly drawn in margins
    margin_alive_frames = 0   # enemy-frames alive in margins
    prev = {}                 # slot -> (flag, screen_x, state)

    start = time.time()
    jump_until = 0
    while time.time() - start < 45.0:
        # --- drive: hold RIGHT; jump when an enemy is close ahead ---
        ws = d.call("smb_ws_state")
        if ws["oper_mode"] != 1:
            # died or transitioned; keep holding START/RIGHT to continue
            d.call("press", buttons=BTN_START, frames=4)
            time.sleep(0.3)
            d.call("set_input", buttons="0x01")
            prev.clear()
            continue

        player_x = d.read(0x86, 1)[0]
        cam = ws["camera_x"]
        player_screen = player_x  # $86 is world-low; close enough with page
        # true player screen x:
        ppage = d.read(0x6D, 1)[0]
        player_screen = ((ppage << 8) | player_x) - cam

        danger = False
        for e in ws["enemies"]:
            if e["flag"] and 0 < e["screen_x"] - player_screen < 64:
                danger = True
        now = time.time()
        # bunny-hop: jump when an enemy is near OR periodically (pits, pipes)
        if (danger or now > jump_until + 0.9) and now > jump_until:
            jump_until = now + 0.5
        d.call("set_input", buttons=("0x%02X" % ((BTN_RIGHT | BTN_A) if now < jump_until else BTN_RIGHT)))

        # --- sample & assert ---
        oam = d.call("read_oam")["sprites"]
        states = d.read(0x1E, 5)
        for e in ws["enemies"]:
            slot, flag, sx = e["slot"], e["flag"], e["screen_x"]
            in_left_margin = flag and -left + 8 <= sx < -8
            in_right_margin = flag and 264 < sx < 256 + right - 16
            if in_left_margin or in_right_margin:
                margin_alive_frames += 1
                # find this enemy's sprites by sidecar x16 proximity
                # (skip OAM slot 0 — SMB's static HUD sprite-0 coin)
                near = [s for s in oam if s["i"] != 0 and s["visible"]
                        and abs(s["x16"] - sx) <= 32]
                ghosts = [s for s in oam if s["i"] != 0 and s["visible"]
                          and abs((s["x16"] & 0xFF) - (sx & 0xFF)) <= 8
                          and 8 <= s["x16"] < 248
                          and abs(s["x16"] - sx) > 200]
                if near:
                    margin_draws += 1
                elif ghosts:
                    wrap_ghosts.append((d.frame(), slot, sx, [(g['i'], g['x16']) for g in ghosts[:3]]))

            p = prev.get(slot)
            if p is not None:
                pflag, psx, pstate = p
                if flag and not pflag:
                    # spawn: must not appear already visible inside the widened view
                    if sx < 256 + right - 8 and sx > -left:
                        spawn_pops.append((d.frame(), slot, e["id"], sx))
                if pflag and not flag:
                    # despawn while visible & not defeated (state bit 5 = $20 dead/stomped... report raw)
                    if -left + 8 < psx < 256 + right - 8 and not (pstate & 0xE0):
                        despawn_pops.append((d.frame(), slot, psx, pstate))
            prev[slot] = (flag, sx, states[slot] if slot < 5 else 0)

        time.sleep(0.08)

    d.call("clear_input")

    print(f"\nsampled ~{int(45/0.08)} ticks")
    print(f"margin enemy-frames: {margin_alive_frames}, drawn correctly: {margin_draws}")
    print(f"wrap ghosts:  {len(wrap_ghosts)}  {wrap_ghosts[:5]}")
    print(f"spawn pops:   {len(spawn_pops)}  {spawn_pops[:5]}")
    print(f"despawn pops: {len(despawn_pops)}  {despawn_pops[:5]}")

    ok = not wrap_ghosts and not spawn_pops and not despawn_pops
    if margin_alive_frames == 0:
        print("WARNING: no enemy ever entered a margin — run inconclusive")
        ok = False
    print("PASS" if ok else "FAIL")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
