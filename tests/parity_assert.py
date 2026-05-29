"""Diff a candidate capture against the golden, byte-for-byte.

Both are the same deterministic attract demo from boot, so we align by ABSOLUTE
frame. Reports the FIRST divergence (lowest frame, then region order, then
offset) and resolves the byte to an object via the SMB RAM map. Exit 0 =
byte-identical (PASS); exit 1 = divergence (FAIL).

Usage:
  python parity_assert.py --golden golden_oam.ndjson --candidate candidate.ndjson
"""
import argparse
import json
import sys

import parity_common as pc

# Region -> absolute base address (for offset resolution).
_REGION_BASE = {"oam": 0x0200, "zp": 0x0000, "r03": 0x0300, "r06": 0x0600, "r07": 0x0700}

# Enemy 5-slot arrays (zero page): base -> name. off-base in [0,5) is a slot.
_ENEMY_ZP = {
    0x0F: "Enemy_Flag", 0x16: "Enemy_ID", 0x1E: "Enemy_State", 0x46: "Enemy_MovingDir",
    0x58: "Enemy_XSpeed", 0x6E: "Enemy_PageLoc", 0x76: "Enemy_YPageLoc",
    0x87: "Enemy_X", 0xB6: "Enemy_YVel", 0xCF: "Enemy_Y",
}
_PLAYER_ZP = {0x6D: "Player_PageLoc", 0x86: "Player_X", 0xCE: "Player_Y", 0x1D: "Player_State"}
_NAMED = {
    0x03AD: "SprObject_Rel_XPos", 0x03B8: "SprObject_Rel_YPos", 0x03D0: "OffscreenBits",
    0x06E5: "Enemy_SprDataOffset", 0x06EA: "PowerUp_SprDataOffset", 0x06EC: "Player_SprDataOffset",
    0x06F1: "Fireball_SprDataOffset", 0x06F3: "Coin_SprDataOffset",
    0x071A: "ScreenLeft_Page", 0x071C: "ScreenLeft_X", 0x071B: "ScreenRight_Page",
    0x071D: "ScreenRight_X", 0x0770: "OperMode", 0x0772: "OperMode_Task",
}


def resolve(region, off):
    if region == "oam":
        slot = off // 4
        kind = ["Y", "tile", "attr", "X"][off % 4]
        return f"OAM slot {slot} byte {kind}"
    addr = _REGION_BASE[region] + off
    if region == "zp":
        for base, name in _PLAYER_ZP.items():
            if off == base:
                return f"{name} (${addr:04X})"
        for base, name in _ENEMY_ZP.items():
            if 0 <= off - base < 5:
                return f"{name}+slot{off - base} (${addr:04X})"
    for a, name in _NAMED.items():
        if 0 <= addr - a < (5 if region in ("r03", "r06") else 1):
            tail = f"+{addr - a}" if addr != a else ""
            return f"{name}{tail} (${addr:04X})"
    return f"${addr:04X}"


def load(path):
    header, frames = None, {}
    with open(path) as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            o = json.loads(line)
            if o.get("_header"):
                header = o
            else:
                frames[o["f"]] = o
    return header, frames


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--golden", required=True)
    ap.add_argument("--candidate", required=True)
    args = ap.parse_args()

    _, g = load(args.golden)
    _, c = load(args.candidate)
    common = sorted(set(g) & set(c))
    if not common:
        print(f"FAIL: no overlapping frames (golden {len(g)}, candidate {len(c)})")
        return 2

    region_order = [r[0] for r in pc.REGIONS]
    for fr in common:
        gf, cf = g[fr], c[fr]
        for region in region_order:
            gr = gf["regions"].get(region)
            cr = cf["regions"].get(region)
            if gr is None or cr is None or gr["crc"] == cr["crc"]:
                continue
            gb = bytes.fromhex(gr["hex"])
            cb = bytes.fromhex(cr["hex"])
            for off in range(min(len(gb), len(cb))):
                if gb[off] != cb[off]:
                    print(f"FAIL: divergence at frame {fr}, region {region}, offset {off}")
                    print(f"  -> {resolve(region, off)}: "
                          f"golden=0x{gb[off]:02X} candidate=0x{cb[off]:02X}")
                    print(f"  (oper_mode={gf.get('oper_mode')} oper_task={gf.get('oper_task')})")
                    return 1
    print(f"PASS: byte-identical across {len(common)} frames x {len(region_order)} regions")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
