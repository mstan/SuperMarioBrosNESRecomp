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
    semantic_set_cmd:   Optional[str] = None
    # Additional byte(s) to also freeze/thaw alongside this one (for
    # coupled-byte slots like Power, where PlayerStatus needs to be
    # frozen together with PlayerSize). Each entry is
    # (addr, value_fn) where value_fn(primary_value) -> coupled_value.
    freeze_couples:     Optional[list] = None
    # Optional warning to surface in the GUI row.
    warning:            Optional[str] = None


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
        # When freezing power, also freeze PlayerSize ($0754) — otherwise
        # the game shrinks Mario on hit and we get "Fire but visually Small".
        # Size encoding: 1 = short (Small Mario), 0 = tall (Big/Fire).
        freeze_couples=[(0x0754, lambda v: 1 if v == 0 else 0)],
        tooltip=(
            "Mario's power-up tier.\n"
            "  0 = Small  (default Mario; one hit = dead)\n"
            "  1 = Big    (after Super Mushroom; one hit shrinks to Small)\n"
            "  2 = Fire   (after Fire Flower; B button shoots fireballs)\n\n"
            "Set via semantic setter Mario::set_power, which couples\n"
            "PlayerStatus ($0756) and PlayerSize ($0754) — necessary\n"
            "because the sprite/collision routines read Size, not Status.\n"
            "Freeze locks both bytes; Raw bypass would leave Size unfrozen.\n\n"
            "RAM: $0756 — smbdis: PlayerStatus  (coupled: $0754 PlayerSize)"
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
PLAYER_SLOTS = [
    SlotDef(
        name="Lives", addr=0x075A, sem_cmd="semcomp_session", sem_field="lives",
        semantic_set_cmd="semcomp_set_session_lives",
        warning="HUD doesn't auto-refresh — see tooltip",
        tooltip=(
            "Lives remaining BEYOND the current Mario (so '0' here = the Mario "
            "you're playing is the last one; one more death = Game Over).\n"
            "The HUD displays Lives+1 (a value of 2 shows as 'x3').\n\n"
            "Decrements on Mario's death; +1 when a 1-Up Mushroom is collected "
            "or every 100 Coins.\n\n"
            "⚠ HUD limitation: SMB's lives/coins display digits live in PPU\n"
            "VRAM and are only refreshed when the game's own life-grant /\n"
            "level-intro code runs.  Setting this byte updates the internal\n"
            "counter; the visible HUD won't reflect the new value until the\n"
            "next time the game itself rewrites it (death/respawn, 1-Up\n"
            "pickup, level transition).\n\n"
            "Semantic setter clamps value to 0–99 to avoid garbled tile\n"
            "glyphs (the byte gets used as a CHR tile index in some render\n"
            "paths — e.g. 25 was rendering as 'F').\n\n"
            "RAM: $075A — smbdis: NumberofLives"
        ),
    ),
    SlotDef(
        name="Coins", addr=0x075E, sem_cmd="semcomp_session", sem_field="coins",
        semantic_set_cmd="semcomp_set_session_coins",
        warning="HUD doesn't auto-refresh — see tooltip",
        tooltip=(
            "Coins collected in the current run, 0–99.\nRolls over to 0 at "
            "100 and grants a 1-Up (Lives += 1).\n\n"
            "⚠ HUD limitation: same as Lives — the displayed coin digits\n"
            "live in PPU VRAM, populated by SMB's coin-grant routine which\n"
            "writes BOTH the counter AND the VRAM update queue.  Setting\n"
            "the counter alone leaves the HUD showing the old value until\n"
            "the next natural coin pickup, which then increments from the\n"
            "stale HUD value (so freezing at 66 with HUD=17 plus one\n"
            "pickup gives HUD=18, not 67).\n\n"
            "Phase 3 plan: dispatch into the coin-grant routine via\n"
            "game_dispatch_override so the HUD refreshes correctly.  Until\n"
            "then this setter only updates the counter.\n\n"
            "Semantic setter clamps value to 0–99.\n\n"
            "RAM: $075E — smbdis: CoinTally"
        ),
    ),
]


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
            buf = b""
            while b"\n" not in buf:
                chunk = self.sock.recv(65536)
                if not chunk: raise ConnectionError("server closed connection")
                buf += chunk
            line = buf.split(b"\n", 1)[0].decode(errors="replace").strip()
            try:
                return json.loads(line)
            except json.JSONDecodeError as e:
                return {"ok": False, "raw": line, "error": str(e)}

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
        # the semantic setter (semcomp_set_*) and any coupled-byte
        # logic, writing only the primary address via trainer_set /
        # trainer_freeze.  Useful for verification work — set the same
        # value semantic vs raw and observe whether the outcomes differ
        # (they should, for any slot with coupling or clamping).
        self.raw_var = tk.BooleanVar(value=False)
        # Only show the checkbox when there's actually a difference
        # between semantic and raw (a semantic_set_cmd or freeze_couples
        # is defined). Otherwise raw and semantic are identical and the
        # toggle is noise.
        if slot.semantic_set_cmd or slot.freeze_couples:
            raw_cb = ttk.Checkbutton(parent, text="Raw", variable=self.raw_var)
            raw_cb.grid(row=row_index, column=8, padx=(8, 2), pady=3, sticky="w")
            Tooltip(raw_cb,
                    "Bypass the semcomp semantic setter and any coupled-byte\n"
                    "freezes for this row.  Writes only the primary address\n"
                    "via trainer_set / trainer_freeze.  Useful for verifying\n"
                    "what the semantic setter actually changes (e.g. checking\n"
                    "that semantic Power=Fire produces a different outcome\n"
                    "than raw $0756=2 alone).")
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
        if self.raw_var.get() or not self.slot.semantic_set_cmd:
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
        # Primary byte is always frozen.
        self.client.trainer_freeze(self.slot.addr, val & 0xFF)
        # Coupled bytes (e.g. PlayerSize when freezing Power) — skipped
        # when Raw bypass is on.
        if self.raw_var.get():
            return
        for coupled_addr, value_fn in (self.slot.freeze_couples or []):
            try:
                cval = value_fn(val) & 0xFF
            except Exception as e:  # noqa: BLE001
                self.status_setter(f"freeze couple failed: {e}")
                continue
            self.client.trainer_freeze(coupled_addr, cval)

    def on_thaw(self):
        self.client.trainer_thaw(self.slot.addr)
        # Skip coupled thaws when Raw is on (caller wanted a raw-only op).
        if self.raw_var.get():
            return
        for coupled_addr, _ in (self.slot.freeze_couples or []):
            self.client.trainer_thaw(coupled_addr)

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
    """A tab containing a set of SlotRows backed by a single semcomp_* cmd."""

    def __init__(self, parent, title: str, slots, client: TrainerClient,
                 status_setter: Callable[[str], None]):
        super().__init__(parent, padding=(8, 8, 8, 8))
        self.title  = title
        self.slots  = slots
        self.client = client

        # Header row.
        hdr = ttk.Frame(self)
        hdr.grid(row=0, column=0, sticky="ew")
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
        rows_frame.grid(row=1, column=0, sticky="nsew", pady=(4, 0))
        self.rows = [SlotRow(rows_frame, i, s, client, status_setter)
                     for i, s in enumerate(slots)]

        # Per-tab note.
        ttk.Separator(self, orient="horizontal").grid(
            row=2, column=0, sticky="ew", pady=(8, 4))
        note_text = ("Hover any Field name for a description of the byte. "
                     "Semcomp column should always equal Raw RAM; "
                     "mismatch (red) means the semcomp accessor reads the wrong address.")
        ttk.Label(self, text=note_text, foreground="#666",
                  wraplength=720, justify="left").grid(row=3, column=0, sticky="w")

    def refresh(self, frozen_addrs: Dict[int, int], sem_responses: Dict[str, dict]):
        for row in self.rows:
            raw = self.client.read_ram(row.slot.addr)
            sem = None
            if row.slot.sem_field:
                sem_resp = sem_responses.get(row.slot.sem_cmd)
                if sem_resp:
                    sem = sem_resp.get(row.slot.sem_field)
            row.update(raw, sem, frozen_addrs.get(row.slot.addr))


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

        self.mario_tab  = TrainerTab(nb, "Mario",  MARIO_SLOTS,  self.client, self._status)
        self.level_tab  = TrainerTab(nb, "Level",  LEVEL_SLOTS,  self.client, self._status)
        self.player_tab = TrainerTab(nb, "Player", PLAYER_SLOTS, self.client, self._status)
        self.raw_tab    = RawTab(nb, self.client, self._status)

        nb.add(self.mario_tab,  text="Mario")
        nb.add(self.level_tab,  text="Level")
        nb.add(self.player_tab, text="Player")
        nb.add(self.raw_tab,    text="Raw")

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
            sem = {
                "semcomp_mario":   self.client.semcomp("semcomp_mario"),
                "semcomp_level":   self.client.semcomp("semcomp_level"),
                "semcomp_session": self.client.semcomp("semcomp_session"),
            }
            self.mario_tab.refresh(frozen, sem)
            self.level_tab.refresh(frozen, sem)
            self.player_tab.refresh(frozen, sem)
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
