#!/usr/bin/env python3
"""Semcomp trainer REPL.

Talks to a SuperMarioBrosRecomp.exe launched with --trainer on the
TCP debug port (default 4370). Lets you set or freeze Mario state
by semantic name, and shows the live values both via raw read_ram
and via the semcomp facade (semcomp_mario) so you can spot
discrepancies between the canonical RAM and the semantic accessors.

Usage:
    python tools/trainer.py [host[:port]]

Commands inside the REPL:
    show                    one-shot read of the Mario block
    watch [interval_ms]     refresh every N ms (default 250) until Enter
    set <name> <val>        one-shot write through the trainer
    freeze <name> <val>     freeze a slot (rewritten every post-NMI)
    thaw <name>             unfreeze a slot
    list                    list active freezes
    raw <addr> <val>        operate on a raw hex address (one-shot)
    rfreeze <addr> <val>    freeze a raw address
    rthaw <addr>            thaw a raw address
    help                    this message
    quit                    exit

Slot names are dotted: mario.x, mario.y, mario.page, mario.power,
mario.physics, mario.facing.

For mario.power and mario.facing, value can be either an integer or
a keyword (mario.power: small|big|fire; mario.facing: none|right|left).
"""
import json
import socket
import sys
import threading
import time

DEFAULT_HOST = "127.0.0.1"
DEFAULT_PORT = 4370

# Slot registry: name -> (addr, parser, formatter)
# parser(str) -> int; formatter(int) -> str
def _int(v):
    s = v.strip()
    if s.startswith("$"):     return int(s[1:], 16)
    if s.startswith(("0x","0X")): return int(s[2:], 16)
    return int(s)

POWER_MAP = {"small": 0, "big": 1, "fire": 2}
DIR_MAP   = {"none": 0, "right": 1, "left": 2}

def parse_power(v):
    s = v.strip().lower()
    if s in POWER_MAP: return POWER_MAP[s]
    return _int(v) & 0xFF

def fmt_power(v):
    for k, n in POWER_MAP.items():
        if n == v: return f"{v} ({k.capitalize()})"
    return f"{v} (?)"

def parse_dir(v):
    s = v.strip().lower()
    if s in DIR_MAP: return DIR_MAP[s]
    return _int(v) & 0xFF

def fmt_dir(v):
    for k, n in DIR_MAP.items():
        if n == v: return f"{v} ({k.capitalize()})"
    return f"{v} (?)"

def fmt_int(v): return str(v)

SLOTS = {
    "mario.x":       (0x0086, _int, fmt_int),
    "mario.y":       (0x00CE, _int, fmt_int),
    "mario.page":    (0x006D, _int, fmt_int),
    "mario.power":   (0x0756, parse_power, fmt_power),
    "mario.physics": (0x001D, _int, fmt_int),
    "mario.facing":  (0x0033, parse_dir, fmt_dir),
}


class TrainerClient:
    """Persistent TCP client. The debug server clears input overrides
    on disconnect, so we keep one socket open for the whole session."""

    def __init__(self, host, port):
        self.host = host; self.port = port
        self.sock = None
        self.lock = threading.Lock()
        self._next_id = 1

    def connect(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(5)
        s.connect((self.host, self.port))
        self.sock = s

    def close(self):
        if self.sock:
            try: self.sock.close()
            except OSError: pass
            self.sock = None

    def call(self, cmd, **kw):
        with self.lock:
            kw["cmd"] = cmd
            kw["id"] = self._next_id; self._next_id += 1
            self.sock.sendall((json.dumps(kw) + "\n").encode())
            buf = b""
            while True:
                chunk = self.sock.recv(65536)
                if not chunk: break
                buf += chunk
                if b"\n" in buf: break
            line = buf.split(b"\n", 1)[0].decode(errors="replace").strip()
            try:
                return json.loads(line)
            except json.JSONDecodeError:
                return {"ok": False, "raw": line}

    def read_ram(self, addr, length=1):
        r = self.call("read_ram", addr=f"0x{addr:04X}", len=length)
        if r.get("ok") and "hex" in r:
            return int(r["hex"][:2], 16) if length == 1 else r["hex"]
        return None

    def semcomp_mario(self):
        return self.call("semcomp_mario")

    def trainer_set(self, addr, val):
        return self.call("trainer_set", addr=f"0x{addr:04X}", val=val)
    def trainer_freeze(self, addr, val):
        return self.call("trainer_freeze", addr=f"0x{addr:04X}", val=val)
    def trainer_thaw(self, addr):
        return self.call("trainer_thaw", addr=f"0x{addr:04X}")
    def trainer_list(self):
        return self.call("trainer_list")


def render_state(client):
    """Build the human-readable status block.

    Two columns: raw read_ram value vs. semcomp facade value. They MUST
    agree byte-for-byte if the semcomp Mario accessors are correct.
    """
    sm = client.semcomp_mario()
    lst = client.trainer_list()
    frozen = {int(e["addr"], 16): e["val"] for e in lst.get("entries", [])}

    lines = []
    lines.append(f"  enabled={lst.get('enabled', False)}  frozen={lst.get('count', 0)}")
    lines.append(f"  {'slot':<14} {'addr':<7} {'raw':<6} {'semcomp':<22} {'frozen':<6}")
    for name, (addr, _, fmt) in SLOTS.items():
        raw = client.read_ram(addr)
        if name == "mario.x":         sem = sm.get("x")
        elif name == "mario.y":       sem = sm.get("y")
        elif name == "mario.page":    sem = sm.get("page")
        elif name == "mario.power":   sem = sm.get("power")
        elif name == "mario.physics": sem = sm.get("physics_state")
        elif name == "mario.facing":  sem = sm.get("facing")
        else: sem = None
        agree = "✓" if (raw is not None and sem is not None and raw == sem) else "!"
        sem_disp = fmt(sem) if sem is not None else "?"
        fz = f"= {frozen[addr]}" if addr in frozen else ""
        lines.append(f"  {name:<14} ${addr:04X}  {raw if raw is not None else '?':<5} {sem_disp:<22} {fz:<6} {agree}")
    if sm.get("on_ground") is not None:
        lines.append(f"  (mario.on_ground={'yes' if sm['on_ground'] else 'no'}, "
                     f"world_x={sm.get('world_x')}, "
                     f"x_vel={sm.get('x_velocity')}, y_vel={sm.get('y_velocity')})")
    return "\n".join(lines)


def cmd_show(client, _args):
    print(render_state(client))

def cmd_watch(client, args):
    interval_ms = int(args[0]) if args else 250
    print(f"watching every {interval_ms}ms — press Enter to stop")
    stop = threading.Event()
    def waiter():
        input()
        stop.set()
    threading.Thread(target=waiter, daemon=True).start()
    while not stop.is_set():
        sys.stdout.write("\x1b[2J\x1b[H")  # clear+home (ANSI)
        sys.stdout.write(render_state(client) + "\n")
        sys.stdout.flush()
        stop.wait(interval_ms / 1000.0)

def _resolve_slot(name):
    if name not in SLOTS:
        raise KeyError(f"unknown slot '{name}'. known: {', '.join(SLOTS)}")
    return SLOTS[name]

def cmd_set(client, args):
    if len(args) < 2:
        print("usage: set <name> <val>"); return
    addr, parse, _ = _resolve_slot(args[0])
    val = parse(args[1]) & 0xFF
    print(client.trainer_set(addr, val))

def cmd_freeze(client, args):
    if len(args) < 2:
        print("usage: freeze <name> <val>"); return
    addr, parse, _ = _resolve_slot(args[0])
    val = parse(args[1]) & 0xFF
    print(client.trainer_freeze(addr, val))

def cmd_thaw(client, args):
    if len(args) < 1:
        print("usage: thaw <name>"); return
    addr, _, _ = _resolve_slot(args[0])
    print(client.trainer_thaw(addr))

def cmd_list(client, _args):
    r = client.trainer_list()
    print(json.dumps(r, indent=2))

def cmd_raw(client, args):
    if len(args) < 2:
        print("usage: raw <addr> <val>"); return
    print(client.trainer_set(_int(args[0]) & 0xFFFF, _int(args[1]) & 0xFF))

def cmd_rfreeze(client, args):
    if len(args) < 2:
        print("usage: rfreeze <addr> <val>"); return
    print(client.trainer_freeze(_int(args[0]) & 0xFFFF, _int(args[1]) & 0xFF))

def cmd_rthaw(client, args):
    if len(args) < 1:
        print("usage: rthaw <addr>"); return
    print(client.trainer_thaw(_int(args[0]) & 0xFFFF))

def cmd_help(_client, _args):
    print(__doc__)


COMMANDS = {
    "show": cmd_show, "watch": cmd_watch,
    "set": cmd_set, "freeze": cmd_freeze, "thaw": cmd_thaw, "list": cmd_list,
    "raw": cmd_raw, "rfreeze": cmd_rfreeze, "rthaw": cmd_rthaw,
    "help": cmd_help, "?": cmd_help,
}


def main():
    host, port = DEFAULT_HOST, DEFAULT_PORT
    if len(sys.argv) > 1:
        if ":" in sys.argv[1]:
            host, p = sys.argv[1].rsplit(":", 1); port = int(p)
        else:
            host = sys.argv[1]

    client = TrainerClient(host, port)
    try:
        client.connect()
    except OSError as e:
        print(f"connect {host}:{port} failed: {e}")
        print("is the game running with --trainer ?")
        sys.exit(1)

    print(f"connected to {host}:{port}.  type 'help' for commands.")
    print(render_state(client))
    while True:
        try:
            line = input("> ").strip()
        except (EOFError, KeyboardInterrupt):
            print()
            break
        if not line: continue
        parts = line.split()
        cmd, args = parts[0], parts[1:]
        if cmd in ("quit", "exit", "q"):
            break
        fn = COMMANDS.get(cmd)
        if not fn:
            print(f"unknown command '{cmd}'. try 'help'.")
            continue
        try:
            fn(client, args)
        except (KeyError, ValueError) as e:
            print(f"error: {e}")
    client.close()


if __name__ == "__main__":
    main()
