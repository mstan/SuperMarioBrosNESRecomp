#!/usr/bin/env python3
"""
ws_check.py — widescreen verification probe for SuperMarioBrosRecomp.

Drives Mario through 1-1 over the TCP debug server while sampling enemy
state, camera, and the OAM sidecar every few frames.  Asserts the three
historical widescreen failure modes never occur:

  1. WRAP GHOST — a sprite belonging to an enemy whose true screen X is in
     a margin renders inside the vanilla viewport at (true & 0xFF), i.e.
     teleports to the opposite edge.
  2. SPAWN ANOMALY — under the 4:3-spawns/16:9-cull design enemies spawn on
     the vanilla 4:3 timeline, so a right-side spawn legitimately appears at
     the 4:3 edge (screen X ~256), inside the visible right margin — that is
     the accepted pop-in, NOT a bug.  What IS a bug is an enemy materializing
     well inside the 4:3 viewport (screen X comfortably left of the 4:3 edge),
     which means it spawned in the playfield instead of at the edge.
  3. DESPAWN POP — an enemy vanishes while visible in a MARGIN without being
     in a defeat state.  Scoped to the margins on purpose: the widened
     despawn bound keeps enemies alive far past the visible margins, so a
     margin despawn is a real culling failure; despawns inside the vanilla
     0..256 viewport (stomps, pit falls, transition slot clears) are vanilla
     gameplay the widescreen layer does not govern and are not counted.

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
    despawn_pops = []         # isolated margin despawns (real culling bugs)
    margin_despawn_cand = []  # (frame, slot, psx, pstate) margin despawns, pre-filter
    all_despawn_frames = []   # every flag 1->0, any position (for cluster detect)
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
                    # 4:3 spawns: a right-side spawn should appear at/near the
                    # vanilla 4:3 edge (screen X ~256), not deep inside the
                    # 4:3 viewport.  Flag only spawns that materialize well
                    # left of the 4:3 edge while still on-screen (a genuine
                    # in-playfield placement bug).  Appearing in the right
                    # margin at the 4:3 edge is the accepted, intended pop-in.
                    if -left + 8 < sx < 256 - 24:
                        spawn_pops.append((d.frame(), slot, e["id"], sx))
                if pflag and not flag:
                    fr = d.frame()
                    all_despawn_frames.append(fr)
                    # Despawn pop = a culling failure the WIDESCREEN feature
                    # is responsible for: an enemy vanishing while visible in
                    # a MARGIN.  The widened OffscreenBoundsCheck keeps enemies
                    # alive out to camera-158 / ScreenRight+158 (screen X ~-158
                    # / ~414), both well past the visible margins, so nothing
                    # should ever despawn inside a margin.
                    #
                    # Despawns inside the vanilla 0..256 viewport (stomps, pit
                    # falls) are governed by the game's untouched vanilla logic
                    # — the widescreen layer neither causes nor can fix them,
                    # they fire identically with widescreen off — so they are
                    # not counted.  Area-transition and death slot-clears wipe
                    # several slots at once (including any that happen to sit in
                    # a margin); those are filtered post-run as clusters below.
                    in_left_margin  = -left < psx < 0
                    in_right_margin = 256 < psx < 256 + right
                    if (in_left_margin or in_right_margin) and not (pstate & 0xE0):
                        margin_despawn_cand.append((fr, slot, psx, pstate))
            prev[slot] = (flag, sx, states[slot] if slot < 5 else 0)

        time.sleep(0.08)

    d.call("clear_input")

    # Filter margin despawns: a transition/death slot-clear wipes several
    # slots within a few frames, so a margin candidate that coincides with
    # another despawn in a +/-6 frame window is a batch clear, not a culling
    # pop-out.  Only ISOLATED margin despawns count as real bugs.
    CLUSTER_W = 6
    for cand in margin_despawn_cand:
        fr = cand[0]
        coincident = sum(1 for f in all_despawn_frames if abs(f - fr) <= CLUSTER_W)
        if coincident <= 1:           # only this despawn in the window
            despawn_pops.append(cand)
    batch_clears = len(margin_despawn_cand) - len(despawn_pops)

    print(f"\nsampled ~{int(45/0.08)} ticks")
    print(f"margin enemy-frames: {margin_alive_frames}, drawn correctly: {margin_draws}")
    print(f"wrap ghosts:  {len(wrap_ghosts)}  {wrap_ghosts[:5]}")
    print(f"spawn pops:   {len(spawn_pops)}  {spawn_pops[:5]}")
    print(f"despawn pops (isolated, real): {len(despawn_pops)}  {despawn_pops[:5]}")
    print(f"  (filtered {batch_clears} margin despawn(s) as transition/death batch clears)")

    ok = not wrap_ghosts and not spawn_pops and not despawn_pops
    if margin_alive_frames == 0:
        print("WARNING: no enemy ever entered a margin — run inconclusive")
        ok = False
    print("PASS" if ok else "FAIL")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
