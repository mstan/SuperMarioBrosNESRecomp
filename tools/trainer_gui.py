#!/usr/bin/env python3
"""Semcomp trainer — separate GUI window (tkinter).

Connects to a SuperMarioBrosRecomp.exe launched with --trainer on its
TCP debug port (default 4370). Provides a tabbed UI for inspecting
and overriding Mario / Level / PlayerSession state, with tooltips
documenting each byte's meaning and dropdowns for enum-valued fields.

Run alongside the game:
    Terminal A:  build_release\\SuperMarioBrosRecomp.exe --trainer
    Terminal B:  python tools\\trainer_gui.py

The Semcomp column should always equal the Raw RAM column. A mismatch
(rendered in red) indicates a wrong address in semcomp/SmbRamMap.h.
"""
import json
import socket
import sys
import threading
import tkinter as tk
from dataclasses import dataclass, field
from tkinter import ttk, messagebox
from typing import Callable, Dict, Optional

DEFAULT_HOST = "127.0.0.1"
DEFAULT_PORT = 4370
POLL_MS      = 200


# ---------------------------------------------------------------------------
# Tooltip helper
# ---------------------------------------------------------------------------

class Tooltip:
    """Hover-triggered text tooltip for a widget.

    Shows a small Toplevel near the cursor after a short delay; hides
    on leave or click. Multi-line text supported via '\\n'.
    """
    DELAY_MS = 450

    def __init__(self, widget, text):
        self.widget = widget
        self.text   = text
        self._after_id = None
        self._tip = None
        widget.bind("<Enter>",     self._schedule, add="+")
        widget.bind("<Leave>",     self._hide,     add="+")
        widget.bind("<ButtonPress>", self._hide,   add="+")

    def _schedule(self, _event):
        self._cancel()
        self._after_id = self.widget.after(self.DELAY_MS, self._show)

    def _cancel(self):
        if self._after_id is not None:
            self.widget.after_cancel(self._after_id)
            self._after_id = None

    def _show(self):
        if self._tip or not self.text:
            return
        x = self.widget.winfo_rootx() + 24
        y = self.widget.winfo_rooty() + self.widget.winfo_height() + 4
        self._tip = tk.Toplevel(self.widget)
        self._tip.wm_overrideredirect(True)
        self._tip.wm_geometry(f"+{x}+{y}")
        lbl = tk.Label(
            self._tip, text=self.text,
            justify="left",
            background="#fffbcc", foreground="#222",
            relief="solid", borderwidth=1,
            font=("Segoe UI", 9),
            padx=8, pady=6,
            wraplength=420,
        )
        lbl.pack()

    def _hide(self, _event=None):
        self._cancel()
        if self._tip is not None:
            try: self._tip.destroy()
            except tk.TclError: pass
            self._tip = None


# ---------------------------------------------------------------------------
# Slot definitions
# ---------------------------------------------------------------------------

@dataclass
class SlotDef:
    name:               str
    addr:               int
    sem_cmd:            str                          # e.g. "semcomp_mario"
    sem_field:          Optional[str]                # e.g. "x"; None = no semcomp validation
    tooltip:            str
    enum_values:        Optional[Dict[int, str]] = None
    enum_readonly:      bool = False
    formatter:          Optional[Callable[[int], str]] = None
    # When set, "Set" routes through this semantic-setter TCP command
    # (e.g. "semcomp_set_mario_power") so coupled-byte logic fires.
    # When None, falls back to raw trainer_set against this addr.
    semantic_set_cmd:    Optional[str] = None
    # When set, "Freeze" / "Thaw" route through C++ semantic freeze
    # methods (e.g. "semcomp_freeze_mario_power" → Mario::freeze_power).
    # The C++ class owns all the coupling knowledge; this GUI just names
    # the field.  When None, falls back to raw trainer_freeze/thaw
    # against this addr.
    semantic_freeze_cmd: Optional[str] = None
    semantic_thaw_cmd:   Optional[str] = None
    # The "name" string the trainer_list TCP command uses to report this
    # semantic freeze (e.g. "mario.power"). Used by polling to display
    # the frozen state.
    semantic_name:       Optional[str] = None
    # Optional warning to surface in the GUI row.
    warning:             Optional[str] = None


def _fmt_enum(v: int, mapping: Dict[int, str]) -> str:
    if v is None: return "?"
    name = mapping.get(v, "?")
    return f"{v} ({name})"


def _fmt_plain(v: Optional[int]) -> str:
    return "?" if v is None else str(v)


# ---- Mario tab slots ------------------------------------------------------
MARIO_SLOTS = [
    SlotDef(
        name="X Position", addr=0x0086, sem_cmd="semcomp_mario", sem_field="x",
        semantic_set_cmd="semcomp_set_mario_x",
        tooltip=(
            "Mario's horizontal pixel position WITHIN the current 256-pixel page.\n"
            "World X = (Page Loc * 256) + X Position.  Range 0–255.\n"
            "Wraps to 0 (and Page Loc increments) when Mario crosses a page "
            "boundary.\n\n"
            "RAM: $0086 — smbdis: Player_X_Position"
        ),
    ),
    SlotDef(
        name="Y Position", addr=0x00CE, sem_cmd="semcomp_mario", sem_field="y",
        semantic_set_cmd="semcomp_set_mario_y",
        tooltip=(
            "Mario's vertical pixel position. 0 = top of screen; ~176 = ground "
            "level in 1-1.  Decreases when Mario jumps (smaller values are "
            "higher).  Goes past 240 when Mario falls off a pit.\n\n"
            "RAM: $00CE — smbdis: Player_Y_Position"
        ),
    ),
    SlotDef(
        name="Page Loc", addr=0x006D, sem_cmd="semcomp_mario", sem_field="page",
        semantic_set_cmd="semcomp_set_mario_page",
        tooltip=(
            "Which 256-pixel-wide horizontal segment of the level Mario is "
            "currently in.\nWorld X = (Page Loc * 256) + X Position.\n"
            "Most overworld levels have 6–10 pages; large castles can have "
            "more.  Setting this jumps Mario forward/back by chunks of 256 "
            "pixels, but the level data won't reload — visual glitches likely.\n\n"
            "RAM: $006D — smbdis: Player_PageLoc"
        ),
    ),
    SlotDef(
        name="Power Status", addr=0x0756, sem_cmd="semcomp_mario", sem_field="power",
        semantic_set_cmd="semcomp_set_mario_power",
        semantic_freeze_cmd="semcomp_freeze_mario_power",
        semantic_thaw_cmd="semcomp_thaw_mario_power",
        semantic_name="mario.power",
        tooltip=(
            "Mario's power-up tier.\n"
            "  0 = Small  (default Mario; one hit = dead)\n"
            "  1 = Big    (after Super Mushroom; one hit shrinks to Small)\n"
            "  2 = Fire   (after Fire Flower; B button shoots fireballs)\n\n"
            "Set / Freeze route through Mario::set_power, which owns the\n"
            "full \"what does 'Power = Fire' mean\" coupling internally:\n"
            "  $0756 PlayerStatus         — the tier itself\n"
            "  $0754 PlayerSize           — 0=tall/1=short for the renderer\n"
            "  $070B PlayerChangeSizeFlag — cleared so damage doesn't trigger\n"
            "                               the visible shrink animation\n\n"
            "The GUI is intentionally dumb about which bytes those are —\n"
            "if SMB grows another power-related byte, the fix goes in the\n"
            "C++ class, not here.  Raw bypass falls back to a single-byte\n"
            "trainer_freeze of $0756 for verification (you'll see the old\n"
            "Fire-but-Small-on-damage artifact).\n\n"
            "RAM: $0756 — smbdis: PlayerStatus"
        ),
        enum_values={0: "Small", 1: "Big", 2: "Fire"},
        enum_readonly=True,
    ),
    SlotDef(
        name="Physics State", addr=0x001D, sem_cmd="semcomp_mario", sem_field="physics_state",
        semantic_set_cmd="semcomp_set_mario_physics_state",
        tooltip=(
            "Mario's movement-physics state.\n"
            "  0 = On Ground (standing/walking/running)\n"
            "  Non-zero = Airborne (jumping, falling, etc.)\n\n"
            "Observed during trace: value flips to 1 when Mario starts a jump "
            "and to 2 at some point during the airborne arc.  Exact "
            "1-vs-2 semantics are not yet fully characterized (likely rising "
            "vs falling, but unverified — see SmbRamMap.h TODO).\n\n"
            "RAM: $001D — smbdis: Player_State"
        ),
        enum_values={0: "On Ground", 1: "Airborne (1)", 2: "Airborne (2)"},
        enum_readonly=False,
    ),
    SlotDef(
        name="Facing Direction", addr=0x0033, sem_cmd="semcomp_mario", sem_field="facing",
        semantic_set_cmd="semcomp_set_mario_facing",
        tooltip=(
            "Direction Mario's sprite is currently facing.  Independent of "
            "Mario's actual movement direction — Mario can slide right while "
            "facing left (during the post-running deceleration skid).\n"
            "  0 = None / idle\n"
            "  1 = Right\n"
            "  2 = Left\n\n"
            "RAM: $0033 — smbdis: PlayerFacingDir"
        ),
        enum_values={0: "None", 1: "Right", 2: "Left"},
        enum_readonly=True,
    ),
]

# ---- Level tab slots ------------------------------------------------------
LEVEL_SLOTS = [
    SlotDef(
        name="World", addr=0x075F, sem_cmd="semcomp_level", sem_field="world",
        tooltip=(
            "Current world number, 0-indexed.\n"
            "  0 = World 1, 1 = World 2, …, 7 = World 8.\n"
            "The HUD shows World+1 (so 0 displays as 'WORLD 1-1').\n\n"
            "Setting this mid-level doesn't transport Mario immediately — the "
            "value takes effect when the next area/level loads (e.g., through "
            "a pipe or after death).\n\n"
            "RAM: $075F — smbdis: WorldNumber"
        ),
    ),
    SlotDef(
        name="Level", addr=0x0760, sem_cmd="semcomp_level", sem_field="level",
        tooltip=(
            "Current level number within the world, 0-indexed.\n"
            "  0 = Level 1 (overworld)\n"
            "  1 = Level 2 (typically underground/water)\n"
            "  2 = Level 3 (overworld variant)\n"
            "  3 = Level 4 (castle, ends with Bowser fight)\n\n"
            "Like World, this takes effect on the next level load, not "
            "immediately.\n\n"
            "RAM: $0760 — smbdis: LevelNumber"
        ),
    ),
]

# ---- Player / session tab slots -------------------------------------------
# Both Coins and Lives now live under "Actions" — the byte-level slot
# rows are gone in favor of semantic verbs (Add Coins / Add Lives). Phase
# 3 plan: future verbs (take_damage, give_power_up, ...) follow the same
# pattern.
PLAYER_SLOTS = []


# ---------------------------------------------------------------------------
# TCP client
# ---------------------------------------------------------------------------

class TrainerClient:
    """Persistent TCP client; one socket for the lifetime of the GUI."""

    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.sock = None
        self.lock = threading.Lock()
        self._id  = 0
        # Persistent recv buffer. The server emits {...}\n\n per response
        # (format string ends in \n; debug_server_send_line tacks on
        # another). Without a persistent buffer, a recv that happens to
        # split a response across boundaries can leak a leading \n into
        # the next call's parse — first split returns empty line, JSON
        # decode fails, response gets silently dropped. The persistent
        # buffer absorbs the trailing \n cleanly across calls.
        self._buf = b""

    def connect(self):
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.settimeout(2.0)
        s.connect((self.host, self.port))
        self.sock = s

    def close(self):
        with self.lock:
            if self.sock:
                try: self.sock.close()
                except OSError: pass
                self.sock = None

    def _call(self, cmd, **kw):
        if not self.sock: raise ConnectionError("not connected")
        with self.lock:
            self._id += 1
            kw["cmd"] = cmd
            kw["id"]  = self._id
            self.sock.sendall((json.dumps(kw) + "\n").encode())
            # Pull lines from the persistent buffer; refill from socket
            # when empty. Skip leading empty lines (the server double-\n
            # framing emits one as a separator after each response).
            while True:
                while b"\n" not in self._buf:
                    chunk = self.sock.recv(65536)
                    if not chunk: raise ConnectionError("server closed connection")
                    self._buf += chunk
                line, _, rest = self._buf.partition(b"\n")
                self._buf = rest
                s = line.decode(errors="replace").strip()
                if s:
                    break  # got a non-empty line
            try:
                return json.loads(s)
            except json.JSONDecodeError as e:
                return {"ok": False, "raw": s, "error": str(e)}

    def read_ram(self, addr):
        r = self._call("read_ram", addr=f"0x{addr:04X}", **{"len": 1})
        if r.get("ok") and "hex" in r:
            return int(r["hex"][:2], 16)
        return None

    def semcomp(self, cmd):
        return self._call(cmd)

    def trainer_set(self, addr, val):
        return self._call("trainer_set", addr=f"0x{addr:04X}", val=val)
    def trainer_freeze(self, addr, val):
        return self._call("trainer_freeze", addr=f"0x{addr:04X}", val=val)
    def trainer_thaw(self, addr):
        return self._call("trainer_thaw", addr=f"0x{addr:04X}")
    def trainer_list(self):
        return self._call("trainer_list")
    def call_named(self, cmd, **kw):
        """Send an arbitrary semantic-setter command, e.g.
        client.call_named("semcomp_set_mario_power", val=2)."""
        return self._call(cmd, **kw)


# ---------------------------------------------------------------------------
# Tab + row widgets
# ---------------------------------------------------------------------------

class SlotRow:
    """One row in a tab: name | addr | raw | semcomp | input | buttons | frozen."""

    def __init__(self, parent, row_index, slot: SlotDef, client: TrainerClient,
                 status_setter: Callable[[str], None]):
        self.slot   = slot
        self.client = client
        self.status_setter = status_setter

        # Name with tooltip.
        name_lbl = ttk.Label(parent, text=slot.name, width=18, anchor="w")
        name_lbl.grid(row=row_index, column=0, padx=4, pady=3, sticky="w")
        Tooltip(name_lbl, slot.tooltip)

        # Addr.
        ttk.Label(parent, text=f"${slot.addr:04X}", width=7, anchor="w").grid(
            row=row_index, column=1, padx=2, pady=3, sticky="w")

        # Raw (live read_ram).
        self.raw_var = tk.StringVar(value="?")
        ttk.Label(parent, textvariable=self.raw_var, width=14, anchor="w").grid(
            row=row_index, column=2, padx=2, pady=3, sticky="w")

        # Semcomp (live via semcomp_* command). Goes red on mismatch.
        self.sem_var = tk.StringVar(value=("?" if slot.sem_field else "—"))
        self.sem_lbl = ttk.Label(parent, textvariable=self.sem_var,
                                  width=14, anchor="w")
        self.sem_lbl.grid(row=row_index, column=3, padx=2, pady=3, sticky="w")
        if slot.sem_field is None:
            self.sem_lbl.configure(foreground="#888")

        # Input: Combobox for enums, Entry for plain.
        self.input_var = tk.StringVar(value="0")
        if slot.enum_values:
            state = "readonly" if slot.enum_readonly else "normal"
            values = [f"{v} - {name}" for v, name in slot.enum_values.items()]
            self.input = ttk.Combobox(parent, textvariable=self.input_var,
                                       values=values, width=14,
                                       state=state)
            self.input.grid(row=row_index, column=4, padx=(4, 4), pady=3, sticky="w")
        else:
            self.input = ttk.Entry(parent, textvariable=self.input_var, width=8)
            self.input.grid(row=row_index, column=4, padx=(4, 4), pady=3, sticky="w")

        # Buttons.
        ttk.Button(parent, text="Set",    width=5, command=self.on_set).grid(
            row=row_index, column=5, padx=2, pady=3)
        ttk.Button(parent, text="Freeze", width=7, command=self.on_freeze).grid(
            row=row_index, column=6, padx=2, pady=3)
        ttk.Button(parent, text="Thaw",   width=5, command=self.on_thaw).grid(
            row=row_index, column=7, padx=2, pady=3)

        # Raw bypass checkbox. When checked, Set / Freeze / Thaw bypass
        # the semantic methods and write only the primary address via
        # trainer_set / trainer_freeze.  Useful for verification work —
        # toggle on, set the same value, see whether the outcome
        # differs from semantic.  Should differ for any slot with
        # semantic_set_cmd or semantic_freeze_cmd defined.
        # CRITICAL: this variable used to be named `self.raw_var`, which
        # shadowed the StringVar created above for the raw RAM display
        # label. After shadowing, `self.raw_var.set("223")` from update()
        # hit the BooleanVar, which Tcl rejects ("expected boolean value
        # but got '223'") — killing the poll loop and freezing every
        # tab. Renamed to make the distinction explicit.
        self.raw_bypass_var = tk.BooleanVar(value=False)
        if slot.semantic_set_cmd or slot.semantic_freeze_cmd:
            raw_cb = ttk.Checkbutton(parent, text="Raw", variable=self.raw_bypass_var)
            raw_cb.grid(row=row_index, column=8, padx=(8, 2), pady=3, sticky="w")
            Tooltip(raw_cb,
                    "Bypass the semcomp semantic methods for this row.\n"
                    "Set / Freeze / Thaw operate on the primary address\n"
                    "only via trainer_set / trainer_freeze / trainer_thaw\n"
                    "— no coupled bytes, no C++ class involvement.\n"
                    "Useful for demonstrating what the semantic methods\n"
                    "actually do differently (e.g. raw Power=Fire shows\n"
                    "Fire-but-Small-on-damage; semantic doesn't).")
            warning_column = 9
        else:
            warning_column = 8

        # Frozen indicator + per-slot warning.
        self.frozen_var = tk.StringVar(value="")
        ttk.Label(parent, textvariable=self.frozen_var, width=40,
                  foreground="#c84", anchor="w").grid(
            row=row_index, column=warning_column,
            padx=2, pady=3, sticky="w")

    def _parse_input(self) -> Optional[int]:
        s = self.input_var.get().strip()
        if not s: return None
        # Combobox may render as "N - Name"; take the leading int.
        head = s.split("-", 1)[0].strip() if " - " in s else s
        try:
            if head.startswith("$"):           return int(head[1:], 16)
            if head.startswith(("0x", "0X")):  return int(head[2:], 16)
            return int(head)
        except ValueError:
            return None

    def on_set(self):
        val = self._parse_input()
        if val is None:
            self.status_setter(f"set ${self.slot.addr:04X}: invalid value")
            return
        # Raw bypass: write the byte directly with no semantic / coupling.
        if self.raw_bypass_var.get() or not self.slot.semantic_set_cmd:
            self.client.trainer_set(self.slot.addr, val & 0xFF)
            return
        # Semantic path: routes through C++ Mario::set_*, PlayerSession::set_*
        # which handles coupling and clamping.
        self.client.call_named(self.slot.semantic_set_cmd, val=val & 0xFF)

    def on_freeze(self):
        val = self._parse_input()
        if val is None:
            self.status_setter(f"freeze ${self.slot.addr:04X}: invalid value")
            return
        # Semantic path: C++ class owns the coupling, GUI just names the
        # field. Raw path: single-byte trainer_freeze.
        if self.raw_bypass_var.get() or not self.slot.semantic_freeze_cmd:
            self.client.trainer_freeze(self.slot.addr, val & 0xFF)
        else:
            self.client.call_named(self.slot.semantic_freeze_cmd, val=val & 0xFF)

    def on_thaw(self):
        if self.raw_bypass_var.get() or not self.slot.semantic_thaw_cmd:
            self.client.trainer_thaw(self.slot.addr)
        else:
            self.client.call_named(self.slot.semantic_thaw_cmd)

    def update(self, raw_val: Optional[int], sem_val: Optional[int],
               frozen_value: Optional[int]):
        # Display formatting.
        if self.slot.enum_values:
            self.raw_var.set(_fmt_enum(raw_val, self.slot.enum_values))
            self.sem_var.set(_fmt_enum(sem_val, self.slot.enum_values)
                             if self.slot.sem_field else "—")
        else:
            self.raw_var.set(_fmt_plain(raw_val))
            self.sem_var.set(_fmt_plain(sem_val) if self.slot.sem_field else "—")

        # Mismatch warning.
        if (self.slot.sem_field and raw_val is not None
                and sem_val is not None and raw_val != sem_val):
            self.sem_lbl.configure(foreground="#c33")
        else:
            self.sem_lbl.configure(
                foreground=("#888" if self.slot.sem_field is None else "#000"))

        # Frozen indicator.  Append a per-slot warning if defined.
        warn = f"  ⚠ {self.slot.warning}" if self.slot.warning else ""
        if frozen_value is not None:
            self.frozen_var.set(f"frozen={frozen_value}{warn}")
        else:
            self.frozen_var.set(warn.lstrip("  ") if warn else "")


class TrainerTab(ttk.Frame):
    """A tab containing a set of SlotRows backed by a single semcomp_* cmd.

    Optional `actions` is a list of ActionDef tuples rendered as buttons
    in a footer "Actions" group. Each click dispatches the named TCP
    command — with or without a `val` argument depending on whether the
    action declares an input field. This is the trainer's "semantic
    verb" UI surface (e.g. "Add Coins" → semcomp_add_coins → N coin
    grants), preferred over the byte-level Set/Freeze in the slot rows
    above.
    """

    def __init__(self, parent, title: str, slots, client: TrainerClient,
                 status_setter: Callable[[str], None],
                 actions=None, actions_on_top=False):
        super().__init__(parent, padding=(8, 8, 8, 8))
        self.title  = title
        self.slots  = slots
        self.client = client
        self.status_setter = status_setter

        row = 0

        if actions and actions_on_top:
            row = self._build_actions(actions, row)
            ttk.Separator(self, orient="horizontal").grid(
                row=row, column=0, sticky="ew", pady=(8, 4))
            row += 1

        # Header row.
        hdr = ttk.Frame(self)
        hdr.grid(row=row, column=0, sticky="ew")
        row += 1
        hdr_cfg = [
            ("Field", 18, 0), ("Addr", 7, 1),
            ("Raw RAM", 14, 2), ("Semcomp", 14, 3),
            ("Value to set/freeze", 16, 4),
        ]
        for text, width, col in hdr_cfg:
            ttk.Label(hdr, text=text, width=width, anchor="w",
                      font=("Segoe UI", 9, "bold")).grid(row=0, column=col, padx=4, pady=2)

        # Slot rows.
        rows_frame = ttk.Frame(self)
        rows_frame.grid(row=row, column=0, sticky="nsew", pady=(4, 0))
        row += 1
        self.rows = [SlotRow(rows_frame, i, s, client, status_setter)
                     for i, s in enumerate(slots)]

        if actions and not actions_on_top:
            ttk.Separator(self, orient="horizontal").grid(
                row=row, column=0, sticky="ew", pady=(8, 4))
            row += 1
            row = self._build_actions(actions, row)

        # Per-tab note.
        ttk.Separator(self, orient="horizontal").grid(
            row=row, column=0, sticky="ew", pady=(8, 4))
        row += 1
        note_text = ("Hover any Field name for a description of the byte. "
                     "Semcomp column should always equal Raw RAM; "
                     "mismatch (red) means the semcomp accessor reads the wrong address.")
        ttk.Label(self, text=note_text, foreground="#666",
                  wraplength=720, justify="left").grid(row=row, column=0, sticky="w")

    def _build_actions(self, actions, row: int) -> int:
        # One action per row: [entry] [button]. Keeps the row readable
        # at a glance — the single horizontal row of 6 actions overflowed
        # the window. Header label gets its own row above the grid.
        actions_frame = ttk.Frame(self)
        actions_frame.grid(row=row, column=0, sticky="w")
        ttk.Label(actions_frame, text="Actions:",
                  font=("Segoe UI", 9, "bold")).grid(
            row=0, column=0, columnspan=2, sticky="w", padx=(0, 8), pady=(0, 4))
        for i, action in enumerate(actions):
            self._build_action(actions_frame, i + 1, action)
        return row + 1

    def _build_action(self, parent, row: int, action) -> None:
        """Render one action on its own row.

        ActionDef shape (dict, recommended):
          {"label": str, "cmd": str, "tip": str,
           "default": int|None,    # if given, action takes a `val` field
           "neg_cmd": str|None,    # for signed inputs, command used when N<0
           "scale": int = 1,       # display = val_sent * scale (val_sent = display / scale)
           "max_abs": int = 255}   # GUI clamp on absolute value of (display / scale)

        Or legacy tuple:
          (label, cmd, tip)                            — no arg
          (label, cmd, tip, default)                   — unsigned val
          (label, cmd, tip, default, neg_cmd)          — signed val
        """
        a = self._normalize_action(action)
        if a.get("default") is None:
            btn = ttk.Button(
                parent, text=a["label"], width=14,
                command=lambda c=a["cmd"], l=a["label"]: self._on_action(c, l))
            btn.grid(row=row, column=0, columnspan=2, padx=4, pady=2, sticky="w")
            if a["tip"]: Tooltip(btn, a["tip"])
            return

        input_var = tk.StringVar(value=str(a["default"]))
        ent = ttk.Entry(parent, textvariable=input_var, width=8)
        ent.grid(row=row, column=0, padx=(4, 2), pady=2, sticky="w")
        btn = ttk.Button(
            parent, text=a["label"], width=14,
            command=lambda cfg=a, v=input_var: self._on_action_val(cfg, v))
        btn.grid(row=row, column=1, padx=2, pady=2, sticky="w")
        if a["tip"]: Tooltip(btn, a["tip"])

    @staticmethod
    def _normalize_action(action) -> dict:
        if isinstance(action, dict):
            a = dict(action)
        else:
            a = {"label": action[0], "cmd": action[1], "tip": action[2]}
            if len(action) >= 4: a["default"] = action[3]
            if len(action) >= 5: a["neg_cmd"] = action[4]
        a.setdefault("default", None)
        a.setdefault("neg_cmd", None)
        a.setdefault("scale",   1)   # display_val / scale = val sent to TCP
        a.setdefault("step",    None) # quantum on the display value; defaults to scale
        a.setdefault("max_abs", 255)
        if a["step"] is None:
            a["step"] = a["scale"]
        return a

    def _on_action(self, tcp_cmd: str, label: str):
        try:
            r = self.client.call_named(tcp_cmd)
            self._report(label, r)
        except (ConnectionError, OSError) as e:
            self.status_setter(f"{label}: TCP error {e}")

    def _on_action_val(self, cfg: dict, var: tk.StringVar):
        label = cfg["label"]
        scale = max(1, int(cfg.get("scale") or 1))
        step  = max(1, int(cfg.get("step")  or scale))
        raw   = var.get().strip()
        try:
            display = int(raw, 0) if raw else 0
        except ValueError:
            self.status_setter(f"{label}: invalid value '{raw}'"); return
        # Quantum check on the display value. `step` is independent of
        # `scale` so e.g. score can have scale=10 (C++ multiplies val by
        # 10) yet require display to be a multiple of 100 (the smallest
        # in-game-visible score change — the BCD ones place is hidden on
        # the HUD).
        if step > 1 and (display % step) != 0:
            self.status_setter(
                f"{label}: value must be a multiple of {step} (got {display})"); return
        # After step validation, the display value is necessarily a
        # multiple of scale (since step is a multiple of scale by
        # construction). val_sent = display / scale is exact.
        val_sent = display // scale
        max_abs  = int(cfg.get("max_abs") or 255)
        if not (-max_abs <= val_sent <= max_abs):
            self.status_setter(
                f"{label}: value out of range "
                f"(|sent|={abs(val_sent)} > {max_abs}; "
                f"display={display}, scale={scale})"); return
        neg_cmd = cfg.get("neg_cmd")
        if val_sent < 0:
            if neg_cmd is None:
                self.status_setter(
                    f"{label}: negative not supported"); return
            cmd = neg_cmd; payload = -val_sent
        else:
            cmd = cfg["cmd"]; payload = val_sent
        try:
            r = self.client.call_named(cmd, val=payload)
            tag = f"{label} ({display:+d})" if display != 0 else f"{label} (0)"
            self._report(tag, r)
        except (ConnectionError, OSError) as e:
            self.status_setter(f"{label}: TCP error {e}")

    def _report(self, label: str, resp: dict):
        if resp.get("ok"):
            extras = []
            for k in ("coin_tally", "lives", "n"):
                if k in resp: extras.append(f"{k}={resp[k]}")
            self.status_setter(f"{label}: ok" + (
                f"  ({', '.join(extras)})" if extras else ""))
        else:
            self.status_setter(f"{label}: {resp}")

    def refresh(self, frozen_addrs: Dict[int, int],
                semantic_freezes: Dict[str, int],
                sem_responses: Dict[str, dict]):
        for row in self.rows:
            raw = self.client.read_ram(row.slot.addr)
            sem = None
            if row.slot.sem_field:
                sem_resp = sem_responses.get(row.slot.sem_cmd)
                if sem_resp:
                    sem = sem_resp.get(row.slot.sem_field)
            # Semantic freeze takes precedence in the display since the
            # GUI ought to think in semantic terms.
            if row.slot.semantic_name and row.slot.semantic_name in semantic_freezes:
                fv = semantic_freezes[row.slot.semantic_name]
            else:
                fv = frozen_addrs.get(row.slot.addr)
            row.update(raw, sem, fv)


# ---------------------------------------------------------------------------
# World tab — camera, block bumps, power-up spawn, floatey points
# ---------------------------------------------------------------------------

class WorldTab(ttk.Frame):
    """Phase 4 verbs: camera lock / teleport, block bump under Mario,
    power-up entity spawn, standalone floatey-points popup. Each is a
    one-shot button (or input + button) with the relevant TCP command
    wired up — same dispatch pattern as the Player tab Actions."""

    def __init__(self, parent, client: TrainerClient,
                 status_setter: Callable[[str], None]):
        super().__init__(parent, padding=(8, 8, 8, 8))
        self.client = client
        self.status_setter = status_setter

        # ---- Camera section ----
        ttk.Label(self, text="Camera", font=("Segoe UI", 10, "bold")).grid(
            row=0, column=0, sticky="w", pady=(0, 4))
        cam = ttk.Frame(self)
        cam.grid(row=1, column=0, sticky="w", pady=(0, 8))

        self.cam_status = tk.StringVar(value="left=?   right=?   locked=?")
        ttk.Label(cam, textvariable=self.cam_status,
                  foreground="#444", width=44).grid(
            row=0, column=0, columnspan=4, sticky="w", padx=(0, 8), pady=(0, 4))

        ttk.Button(cam, text="Lock",   width=8,
                   command=lambda: self._fire("semcomp_camera_lock",   "Lock Camera")
                   ).grid(row=1, column=0, padx=2)
        ttk.Button(cam, text="Unlock", width=8,
                   command=lambda: self._fire("semcomp_camera_unlock", "Unlock Camera")
                   ).grid(row=1, column=1, padx=2)

        self.cam_x_var = tk.StringVar(value="0")
        ttk.Entry(cam, textvariable=self.cam_x_var, width=8).grid(
            row=1, column=2, padx=(12, 2))
        ttk.Button(cam, text="Teleport (world X)", width=18,
                   command=self._on_teleport).grid(row=1, column=3, padx=2)

        ttk.Separator(self, orient="horizontal").grid(
            row=2, column=0, sticky="ew", pady=(8, 4))
        ttk.Label(self, foreground="#666", justify="left", wraplength=720,
                  text=(
                    "Camera teleport sets the screen-left/right page+x bytes; "
                    "the level loader won't re-stream — small offsets in the "
                    "currently-loaded window are visually clean.\n\n"
                    "Note: Player tab → Add Score automatically pops a "
                    "floatey-points sprite (+N pts) above Mario, picking the "
                    "closest preset to the score delta (100 / 200 / 400 / "
                    "500 / 800 / 1000 / 2000 / 4000 / 5000 / 8000).\n\n"
                    "Block-bump and power-up entity spawn TCP commands "
                    "(semcomp_bump_block, semcomp_spawn_powerup, "
                    "semcomp_spawn_floatey) exist but are deferred from "
                    "the GUI — the natural-caller state setup is more "
                    "intricate than a single button can stage. Revisit "
                    "after researching BumpBlock metatile staging and "
                    "SetupPowerUp slot conventions.")).grid(
            row=3, column=0, sticky="w")

    def _fire(self, cmd, label):
        try:
            r = self.client.call_named(cmd)
            self.status_setter(f"{label}: {'ok' if r.get('ok') else r}")
        except (ConnectionError, OSError) as e:
            self.status_setter(f"{label}: TCP error {e}")

    def _fire_val(self, cmd, val, label):
        try:
            r = self.client.call_named(cmd, val=val)
            self.status_setter(f"{label}: {'ok' if r.get('ok') else r}")
        except (ConnectionError, OSError) as e:
            self.status_setter(f"{label}: TCP error {e}")

    def _parse_combo_int(self, s):
        # "N - Name" -> N; "N" -> N.
        head = s.split("-", 1)[0].strip() if "-" in s else s.strip()
        try: return int(head, 0)
        except ValueError: return 0

    def _on_teleport(self):
        try: wx = int(self.cam_x_var.get(), 0)
        except ValueError:
            self.status_setter("Teleport: invalid world X"); return
        self._fire_val("semcomp_camera_set_world_x", wx, "Teleport")

    def refresh(self, _frozen_addrs, _sem_responses):
        # Live camera status.
        try:
            r = self.client.call_named("semcomp_camera")
        except (ConnectionError, OSError):
            return
        if not r.get("ok"): return
        self.cam_status.set(
            f"left={r.get('left_world_x','?')}   "
            f"right={r.get('right_world_x','?')}   "
            f"locked={r.get('locked','?')}")


# ---------------------------------------------------------------------------
# Enemies tab — facade over the 5-slot enemy array
# ---------------------------------------------------------------------------

# Verified enemy ID names. Unlisted IDs render as "0xNN ?".
ENEMY_ID_NAMES = {
    # Verified in-game 2026-05-17: 1-1 first three enemies all read as
    # ID $06 — those are the iconic walking Goombas. The earlier
    # "Goomba=$14" guess from the research agent looks wrong.
    0x00: "Green Koopa",
    0x01: "Red Koopa",
    0x02: "Buzzy Beetle",
    0x03: "Red Koopa (no fall)",
    0x04: "Hammer Bro",
    0x05: "Green Koopa (patient)",
    0x06: "Goomba",
    0x07: "Bloober",
    0x08: "Bullet Bill",
    0x09: "Yellow CheepCheep",
    0x0A: "Gray CheepCheep",
    0x0B: "Podoboo",
    0x0C: "Piranha Plant",
    0x0D: "Green Paratroopa",
    0x0E: "Green CheepCheep",
    0x0F: "Red CheepCheep",
    0x10: "Lakitu",
    0x11: "Spiny Egg",
    0x12: "Spiny",
    0x2D: "Bowser",
}


class EnemiesTab(ttk.Frame):
    """Live view of the 5-slot enemy array with bulk + per-slot verbs.

    Polls semcomp_enemies each tick; renders one row per slot with
    active flag, ID + name, state byte, world position, velocities, and
    [Kill]/[Stomp] buttons gated on the slot being active.
    """

    SLOT_COUNT = 5

    def __init__(self, parent, client: TrainerClient,
                 status_setter: Callable[[str], None]):
        super().__init__(parent, padding=(8, 8, 8, 8))
        self.client = client
        self.status_setter = status_setter

        # ---- Bulk action row ----
        actions = ttk.Frame(self)
        actions.grid(row=0, column=0, sticky="w", pady=(0, 8))
        ttk.Label(actions, text="Bulk:",
                  font=("Segoe UI", 9, "bold")).grid(row=0, column=0, padx=(0, 8))
        btn_specs = [
            ("Kill All",    "semcomp_kill_all_enemies",
             "Instant-remove every active enemy. No score, no anim.\n"
             "Routes through KillEnemyAboveBlock ($E18E) per slot."),
            ("Stomp All",   "semcomp_stomp_all_enemies",
             "Stomp every active enemy with score grant + bounce anim.\n"
             "Routes through EnemyStomped ($D969) per slot."),
            ("Freeze All",  "semcomp_freeze_enemies",
             "Zero $0058 (x-velocity) and $00B6 (y-velocity) for every\n"
             "active enemy. Some types (Piranha Plant scheduled motion,\n"
             "Lakitu) recompute velocity each frame and will resist."),
        ]
        for col, (label, cmd, tip) in enumerate(btn_specs, start=1):
            b = ttk.Button(actions, text=label, width=12,
                           command=lambda c=cmd, l=label: self._on_bulk(c, l))
            b.grid(row=0, column=col, padx=2)
            Tooltip(b, tip)

        # ---- Per-slot grid header ----
        ttk.Separator(self, orient="horizontal").grid(
            row=1, column=0, sticky="ew", pady=(0, 4))
        hdr = ttk.Frame(self)
        hdr.grid(row=2, column=0, sticky="w")
        for col, (text, width) in enumerate([
            ("Slot",   4), ("Active", 6), ("ID",  6), ("Type", 18),
            ("State",  6), ("WrldX", 7), ("Y",   5), ("XV",   5), ("YV", 5),
        ]):
            ttk.Label(hdr, text=text, width=width, anchor="w",
                      font=("Segoe UI", 9, "bold")).grid(
                row=0, column=col, padx=2)

        # ---- Per-slot rows ----
        rows_frame = ttk.Frame(self)
        rows_frame.grid(row=3, column=0, sticky="nsew", pady=(4, 0))
        self.rows = []
        for i in range(self.SLOT_COUNT):
            r = self._build_row(rows_frame, i)
            self.rows.append(r)

        ttk.Separator(self, orient="horizontal").grid(
            row=4, column=0, sticky="ew", pady=(8, 4))
        ttk.Label(self,
                  text=("Polls semcomp_enemies each tick. Per-slot Kill/Stomp "
                        "are gated on Active; inactive slots show dashes."),
                  foreground="#666", wraplength=720, justify="left").grid(
            row=5, column=0, sticky="w")

    def _build_row(self, parent, slot_idx: int) -> dict:
        v = {k: tk.StringVar(value="—") for k in
             ("active", "id", "type", "state", "wx", "y", "xv", "yv")}
        cols = [
            (str(slot_idx), 4),
            (v["active"],   6), (v["id"], 6), (v["type"], 18),
            (v["state"],    6), (v["wx"], 7), (v["y"],    5),
            (v["xv"],       5), (v["yv"], 5),
        ]
        for col, (val, width) in enumerate(cols):
            if isinstance(val, tk.StringVar):
                ttk.Label(parent, textvariable=val, width=width,
                          anchor="w").grid(row=slot_idx, column=col, padx=2, pady=1)
            else:
                ttk.Label(parent, text=val, width=width, anchor="w").grid(
                    row=slot_idx, column=col, padx=2, pady=1)
        kill_btn = ttk.Button(parent, text="Kill", width=5, state="disabled",
                              command=lambda s=slot_idx:
                              self._on_per_slot("semcomp_kill_enemy", s, "Kill"))
        kill_btn.grid(row=slot_idx, column=len(cols), padx=2)
        stomp_btn = ttk.Button(parent, text="Stomp", width=6, state="disabled",
                               command=lambda s=slot_idx:
                               self._on_per_slot("semcomp_stomp_enemy", s, "Stomp"))
        stomp_btn.grid(row=slot_idx, column=len(cols) + 1, padx=2)
        return {**v, "kill": kill_btn, "stomp": stomp_btn}

    def _on_bulk(self, cmd: str, label: str):
        try:
            r = self.client.call_named(cmd)
            if r.get("ok"):
                n = r.get("killed", r.get("stomped", r.get("frozen", 0)))
                self.status_setter(f"{label}: {n} slot(s) affected")
            else:
                self.status_setter(f"{label}: {r}")
        except (ConnectionError, OSError) as e:
            self.status_setter(f"{label}: TCP error {e}")

    def _on_per_slot(self, cmd: str, slot: int, label: str):
        try:
            r = self.client.call_named(cmd, slot=slot)
            ok = r.get("ok") and (r.get("killed") or r.get("stomped"))
            self.status_setter(f"{label} slot {slot}: {'ok' if ok else r}")
        except (ConnectionError, OSError) as e:
            self.status_setter(f"{label} slot {slot}: TCP error {e}")

    def refresh(self, _frozen_addrs, _sem_responses):
        try:
            r = self.client.call_named("semcomp_enemies")
        except (ConnectionError, OSError) as e:
            self.status_setter(f"enemies refresh: TCP error {e}")
            return
        if not r.get("ok"):
            # Diagnostic: surface failed responses to the status bar so
            # we can tell whether the parser is eating valid data or the
            # server returned an error.
            self.status_setter(f"enemies refresh: not-ok response {r}")
            return
        # Diagnostic: brief status update on every successful refresh so
        # the user can confirm live data is flowing.
        ac = r.get("active_count", 0)
        if ac > 0:
            self.status_setter(f"enemies: active_count={ac}")
        for entry in r.get("slots", []):
            i = entry.get("slot")
            if i is None or i >= len(self.rows): continue
            row = self.rows[i]
            active = entry.get("active", False)
            if active:
                row["active"].set("YES")
                eid = entry.get("id", 0)
                row["id"].set(f"0x{eid:02X}")
                row["type"].set(ENEMY_ID_NAMES.get(eid, "?"))
                row["state"].set(f"0x{entry.get('state', 0):02X}")
                row["wx"].set(str(entry.get("world_x", 0)))
                row["y"].set(str(entry.get("y", 0)))
                row["xv"].set(str(entry.get("x_vel", 0)))
                row["yv"].set(str(entry.get("y_vel", 0)))
                row["kill"].configure(state="normal")
                row["stomp"].configure(state="normal")
            else:
                for k in ("active", "id", "type", "state", "wx", "y", "xv", "yv"):
                    row[k].set("—")
                row["kill"].configure(state="disabled")
                row["stomp"].configure(state="disabled")


# ---------------------------------------------------------------------------
# Raw tab (no semcomp validation — direct address poking)
# ---------------------------------------------------------------------------

class RawTab(ttk.Frame):
    def __init__(self, parent, client: TrainerClient,
                 status_setter: Callable[[str], None]):
        super().__init__(parent, padding=(8, 8, 8, 8))
        self.client = client
        self.status_setter = status_setter

        intro = ttk.Label(self, justify="left", foreground="#444", wraplength=720,
            text=("Raw address poker — for any byte not (yet) named in the "
                  "tabs above.\nUse for Phase 1.5 verification of new RAM "
                  "addresses you suspect mean something specific, or for "
                  "quick experiments before adding a slot to the semcomp "
                  "facade."))
        intro.grid(row=0, column=0, columnspan=5, sticky="w", pady=(0, 8))

        ttk.Label(self, text="Address (hex, e.g. $0086 or 0x86):").grid(
            row=1, column=0, sticky="w", padx=2)
        self.addr_var = tk.StringVar(value="0x")
        ttk.Entry(self, textvariable=self.addr_var, width=10).grid(
            row=1, column=1, padx=2, sticky="w")

        ttk.Label(self, text="Value (0-255):").grid(row=1, column=2, sticky="w", padx=8)
        self.val_var = tk.StringVar(value="0")
        ttk.Entry(self, textvariable=self.val_var, width=6).grid(
            row=1, column=3, padx=2, sticky="w")

        ttk.Button(self, text="Set",    command=self.on_set,
                   width=6).grid(row=1, column=4, padx=4)
        ttk.Button(self, text="Freeze", command=self.on_freeze,
                   width=8).grid(row=1, column=5, padx=4)
        ttk.Button(self, text="Thaw",   command=self.on_thaw,
                   width=6).grid(row=1, column=6, padx=4)

        # Read-only view of the current raw byte and full freeze list.
        ttk.Label(self, text="Current byte at address:").grid(
            row=2, column=0, sticky="w", padx=2, pady=(12, 2))
        self.current_var = tk.StringVar(value="?")
        ttk.Label(self, textvariable=self.current_var,
                  font=("Consolas", 10, "bold")).grid(
            row=2, column=1, columnspan=2, sticky="w", padx=2, pady=(12, 2))

        ttk.Label(self, text="Active freezes:",
                  font=("Segoe UI", 9, "bold")).grid(
            row=3, column=0, sticky="w", padx=2, pady=(12, 2))
        self.freeze_list_var = tk.StringVar(value="(none)")
        ttk.Label(self, textvariable=self.freeze_list_var, foreground="#555",
                  wraplength=720, justify="left").grid(
            row=4, column=0, columnspan=7, sticky="w", padx=2)

    def _parse_int(self, s):
        s = s.strip()
        if not s: return None
        try:
            if s.startswith("$"):           return int(s[1:], 16)
            if s.startswith(("0x", "0X")):  return int(s[2:], 16)
            return int(s)
        except ValueError:
            return None

    def on_set(self):
        a = self._parse_int(self.addr_var.get())
        v = self._parse_int(self.val_var.get())
        if a is None or v is None:
            self.status_setter("raw set: addr and val required"); return
        self.client.trainer_set(a & 0xFFFF, v & 0xFF)
    def on_freeze(self):
        a = self._parse_int(self.addr_var.get())
        v = self._parse_int(self.val_var.get())
        if a is None or v is None:
            self.status_setter("raw freeze: addr and val required"); return
        self.client.trainer_freeze(a & 0xFFFF, v & 0xFF)
    def on_thaw(self):
        a = self._parse_int(self.addr_var.get())
        if a is None:
            self.status_setter("raw thaw: addr required"); return
        self.client.trainer_thaw(a & 0xFFFF)

    def refresh(self, frozen_addrs: Dict[int, int], _sem_responses):
        # Update current-byte display if the addr field is parseable.
        a = self._parse_int(self.addr_var.get())
        if a is not None:
            v = self.client.read_ram(a)
            self.current_var.set(f"{v}  (${v:02X})" if v is not None else "?")
        # Render full freeze list.
        if not frozen_addrs:
            self.freeze_list_var.set("(none)")
        else:
            parts = [f"${a:04X}={v}" for a, v in sorted(frozen_addrs.items())]
            self.freeze_list_var.set(", ".join(parts))


# ---------------------------------------------------------------------------
# Main GUI
# ---------------------------------------------------------------------------

class TrainerGUI:
    def __init__(self, root, client):
        self.root   = root
        self.client = client
        self.error_count = 0
        self.build_ui()
        self.schedule_poll()

    def build_ui(self):
        self.root.title("Semcomp Trainer")
        self.root.geometry("1000x460")
        self.root.minsize(900, 400)

        nb = ttk.Notebook(self.root)
        nb.pack(fill="both", expand=True, padx=8, pady=(8, 0))

        # Mario tab — Actions section (top) for semantic verbs; the
        # byte-level slots stay below for inspection / freeze use.
        self.mario_tab = TrainerTab(
            nb, "Mario", MARIO_SLOTS, self.client, self._status,
            actions_on_top=True,
            actions=[
                ("Give Power-Up", "semcomp_give_power_up",
                 "Step Mario up one power tier: Small → Big → Fire.\n"
                 "No-op at Fire. Routes through Mario::set_power so\n"
                 "PlayerStatus, PlayerSize, and PlayerChangeSizeFlag\n"
                 "stay coupled."),
                ("Take Damage", "semcomp_take_damage",
                 "Step Mario down one power tier: Fire → Big → Small.\n"
                 "Stays at Small (does NOT auto-kill — the death\n"
                 "animation flow is a separate Phase 3 verb to be\n"
                 "lifted later)."),
            ])
        self.level_tab  = TrainerTab(nb, "Level",  LEVEL_SLOTS,  self.client, self._status)
        # Player tab — Actions are the primary verbs (slot rows are gone).
        # Coins / Lives accept signed N (positive → add with SFX,
        # negative → remove silent). Score uses scale=10 because SMB's
        # smallest score increment is 10 points (BCD low digit is always
        # 0 on the HUD); the user types the real point value, the GUI
        # divides by 10 before sending, and the C++ side multiplies back.
        self.player_tab = TrainerTab(
            nb, "Player", PLAYER_SLOTS, self.client, self._status,
            actions_on_top=True,
            actions=[
                {"label": "Add Coins", "cmd": "semcomp_add_coins",
                 "default": 1, "neg_cmd": "semcomp_remove_coins",
                 "tip":
                 "Coin delta.\n"
                 "  • Positive N → bump $075E by N (wraps every 100 with\n"
                 "    one extra-life grant per rollover), HUD refresh,\n"
                 "    one coin-pickup SFX (or extra-life jingle if a\n"
                 "    rollover fired).\n"
                 "  • Negative N → decrement $075E (clamped at 0), HUD\n"
                 "    refresh, silent (no 'un-grab a coin' verb exists)."},
                {"label": "Add Lives", "cmd": "semcomp_add_lives",
                 "default": 1, "neg_cmd": "semcomp_remove_lives",
                 "tip":
                 "Life delta.\n"
                 "  • Positive N → bump $075A by N (clamped at 99 — values\n"
                 "    higher render as garbled HUD tiles), HUD refresh,\n"
                 "    extra-life jingle.\n"
                 "  • Negative N → decrement $075A (clamped at 0), HUD\n"
                 "    refresh, silent."},
                {"label": "Add Score", "cmd": "semcomp_add_score",
                 "default": 100, "scale": 10, "step": 100, "max_abs": 99999,
                 "tip":
                 "Score delta in real points. Must be a multiple of 100\n"
                 "(SMB's HUD only shows score changes in 100-point chunks —\n"
                 "the rightmost two BCD digits aren't independently rendered\n"
                 "during normal play). Positive adds, negative subtracts\n"
                 "(clamped at 0 in C++). Max ±999900.\n\n"
                 "Wire: GUI sends val = display/10; C++ handler multiplies\n"
                 "back by 10. Writes BCD to both $07D7..$07DC (display)\n"
                 "and $07DD..$07E2 (gameplay), refreshes HUD. No SFX."},
                {"label": "Set Score", "cmd": "semcomp_set_score",
                 "default": 50000, "scale": 10, "step": 100, "max_abs": 99999,
                 "tip":
                 "Set the score to an exact value (multiple of 100).\n"
                 "Max 999900. Writes both BCD copies, refreshes HUD."},
                {"label": "Add Time", "cmd": "semcomp_add_timer",
                 "default": 100, "max_abs": 999,
                 "tip":
                 "Game-timer delta (signed). Positive extends, negative\n"
                 "subtracts (clamped at 0; max 999). Refreshes HUD."},
                {"label": "Set Time", "cmd": "semcomp_set_timer",
                 "default": 400, "max_abs": 999,
                 "tip":
                 "Set the game timer to an exact value (0..999).\n"
                 "Refreshes the HUD."},
            ])
        self.enemies_tab = EnemiesTab(nb, self.client, self._status)
        self.world_tab   = WorldTab(nb, self.client, self._status)
        self.raw_tab     = RawTab(nb, self.client, self._status)

        nb.add(self.mario_tab,   text="Mario")
        nb.add(self.level_tab,   text="Level")
        nb.add(self.player_tab,  text="Player")
        nb.add(self.enemies_tab, text="Enemies")
        nb.add(self.world_tab,   text="World")
        nb.add(self.raw_tab,     text="Raw")

        # Status bar.
        self.status_var = tk.StringVar(
            value=f"Connected to {self.client.host}:{self.client.port}")
        ttk.Label(self.root, textvariable=self.status_var,
                  relief="sunken", anchor="w",
                  padding=4).pack(fill="x", side="bottom")

    def _status(self, msg: str):
        self.status_var.set(msg)

    def schedule_poll(self):
        self.root.after(POLL_MS, self.poll)

    def poll(self):
        try:
            tl = self.client.trainer_list()
            frozen = {int(e["addr"], 16): e["val"] for e in tl.get("entries", [])}
            sem_freezes = {e["name"]: e["val"] for e in tl.get("semantic", [])}
            sem = {
                "semcomp_mario":   self.client.semcomp("semcomp_mario"),
                "semcomp_level":   self.client.semcomp("semcomp_level"),
                "semcomp_session": self.client.semcomp("semcomp_session"),
            }
            self.mario_tab.refresh(frozen, sem_freezes, sem)
            self.level_tab.refresh(frozen, sem_freezes, sem)
            self.player_tab.refresh(frozen, sem_freezes, sem)
            self.enemies_tab.refresh(frozen, sem)
            self.world_tab.refresh(frozen, sem)
            self.raw_tab.refresh(frozen, sem)
            self.error_count = 0
            world  = sem["semcomp_level"].get("world", "?")
            level  = sem["semcomp_level"].get("level", "?")
            lives  = sem["semcomp_session"].get("lives", "?")
            self._status(
                f"Connected   "
                f"world={world+1 if isinstance(world, int) else world}-"
                f"{level+1 if isinstance(level, int) else level}   "
                f"lives={lives}   "
                f"frozen={tl.get('count', 0)}"
            )
        except (ConnectionError, OSError, json.JSONDecodeError) as e:
            self.error_count += 1
            self._status(f"TCP error ({self.error_count}): {e}")
            if self.error_count > 5:
                messagebox.showerror("Trainer GUI",
                    f"Lost connection to game ({e}).\n"
                    f"Is the game still running with --trainer?")
                self.root.destroy()
                return
        self.schedule_poll()


def main():
    host, port = DEFAULT_HOST, DEFAULT_PORT
    if len(sys.argv) > 1:
        a = sys.argv[1]
        if ":" in a:
            host, p = a.rsplit(":", 1); port = int(p)
        else:
            host = a

    client = TrainerClient(host, port)
    try:
        client.connect()
    except OSError as e:
        root = tk.Tk(); root.withdraw()
        messagebox.showerror("Trainer GUI",
            f"Could not connect to {host}:{port}: {e}\n\n"
            f"Is the game running with --trainer?")
        return

    root = tk.Tk()
    try:
        ttk.Style().theme_use("vista")
    except tk.TclError:
        pass
    TrainerGUI(root, client)
    root.mainloop()
    client.close()


if __name__ == "__main__":
    main()
