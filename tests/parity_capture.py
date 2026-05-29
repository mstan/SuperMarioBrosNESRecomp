"""Capture a window of the history ring to NDJSON (per-region CRC + hex).

The attract demo is deterministic from boot, so a given build reproduces the
same RAM/OAM at the same ABSOLUTE frame. We capture an absolute-frame window;
oper_mode/oper_task are recorded per frame so an oracle (Nestopia, different
boot timing) can be cycle-aligned later (see parity_oracle_check.py).

Usage:
  python parity_capture.py --out golden_oam.ndjson --label golden \
      [--start 120] [--frames 600] [--warmup 0]
"""
import argparse
import json
import sys
import time

import parity_common as pc


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", required=True)
    ap.add_argument("--label", default="capture")
    ap.add_argument("--start", type=int, default=120, help="skip boot/init frames")
    ap.add_argument("--frames", type=int, default=600)
    ap.add_argument("--warmup", type=float, default=0.0)
    args = ap.parse_args()

    if args.warmup:
        time.sleep(args.warmup)

    conn = pc.Conn()
    oldest, newest = pc.history(conn)
    start = max(args.start, oldest)
    end = start + args.frames - 1

    # Wait for the ring to reach the window end (game still running forward).
    deadline = time.time() + 90
    while newest < end and time.time() < deadline:
        time.sleep(0.5)
        oldest, newest = pc.history(conn)
    if newest < end:
        print(f"ring only reached frame {newest}, wanted {end}", file=sys.stderr)
        return 3
    if oldest > start:
        print(f"window start {start} already evicted (oldest={oldest})", file=sys.stderr)
        return 3

    ts = pc.pull_timeseries(conn, start, end)

    nframes = 0
    with open(args.out, "w") as f:
        f.write(json.dumps({
            "_header": True, "label": args.label,
            "start": start, "end": end,
            "regions": [r[0] for r in pc.REGIONS],
        }) + "\n")
        for frame in range(start, end + 1):
            gd = ts.get(frame)
            om, ot = pc.gd_oper(gd) if gd else (None, None)
            regs = {}
            for name, addr, length in pc.REGIONS:
                data = pc.read_region(conn, frame, addr, length)
                regs[name] = {"crc": pc.crc(data), "hex": data.hex()}
            f.write(json.dumps({
                "f": frame, "oper_mode": om, "oper_task": ot, "regions": regs,
            }) + "\n")
            nframes += 1
    conn.close()
    print(f"wrote {args.out}: {nframes} frames ({start}..{end}), regions={[r[0] for r in pc.REGIONS]}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
