#!/usr/bin/env python3
"""Bulk-port a set of generated routines into a semcomp module.

Given a list of (hex_addr, name) tuples plus a module name, this:
1. Reads each function's body from generated/super-mario-bros_full.c
2. Emits semcomp/<Module>.cpp with verbatim port methods
3. Emits the header
4. Emits Runtime.cpp bridges + Runtime.h decls
5. Emits extras.c shims
6. Emits game.toml [[replace_func]] entries
7. Updates SemcompGame.h + CMakeLists.txt

Supports two emission patterns:

(A) Single-entry: function body emitted inline. Direct verbatim port.

(B) Shim+body (multi-entry): recompiler emits
        static void func_XXXX_body(int _entry) { switch(_entry){...} ... }
        void func_XXXX(void) { func_XXXX_body(0); }
        void func_YYYY(void) { func_XXXX_body(1); }
    For these, we port the shared body once and emit one public method per
    entry-point address. The tool auto-discovers ALL sibling entries that
    share a body so the whole body gets owned (no half-owned tangles).
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).parent.parent
FULL_C = ROOT / "generated" / "super-mario-bros_full.c"
GAME_TOML = ROOT / "game.toml"


def load_owned_addresses():
    """Read game.toml and return the set of addresses already replace_func'd.

    Used to auto-skip already-owned shims when auto-discovering body siblings
    so we don't emit duplicate [[replace_func]] entries.
    """
    owned = set()
    if not GAME_TOML.exists():
        return owned
    for line in GAME_TOML.read_text(encoding="utf-8").splitlines():
        m = re.match(r"\s*addr\s*=\s*0x([0-9A-Fa-f]+)", line)
        if m:
            owned.add(m.group(1).upper())
    return owned


# ---------------------------------------------------------------------------
# Function locators
# ---------------------------------------------------------------------------

def find_function(addr_hex, generated):
    """Find the function body for hex addr like 'C30E' or 'C30E_b0'.
    Returns (start_line, end_line, suffix). suffix is e.g. '_b0' or ''.
    """
    addr = addr_hex.upper()
    patterns = [
        (rf"^(?:static )?void func_{addr}_b0\(void\) \{{", "_b0"),
        (rf"^(?:static )?void func_{addr}\(void\) \{{", ""),
    ]
    for pat, suffix in patterns:
        for i, line in enumerate(generated):
            if re.match(pat, line):
                depth = 1
                for j in range(i + 1, len(generated)):
                    cur = generated[j]
                    opens = cur.count("{")
                    closes = cur.count("}")
                    if cur.rstrip() == "}" and depth == 1:
                        return (i, j, suffix)
                    depth += opens - closes
                    if depth == 0:
                        return (i, j, suffix)
                return (i, len(generated) - 1, suffix)
    return None


def detect_shim_target(start, end, lines):
    """If the function at lines[start:end+1] is a thin shim that only calls
    `func_XXXX_body(N);`, return (body_addr_hex, entry_index). Else None.
    """
    body_match = None
    for k in range(start + 1, end):
        line = lines[k].strip()
        if not line:
            continue
        if line.startswith("#ifdef") or line.startswith("#endif"):
            continue
        if "recomp_stack_" in line:
            continue
        m = re.match(r"^func_([0-9A-Fa-f]{4})_body\((\d+)\);?$", line)
        if m:
            if body_match is not None:
                # Multiple body calls — not a simple shim
                return None
            body_match = (m.group(1).upper(), int(m.group(2)))
            continue
        # Anything else means this isn't a simple shim
        return None
    return body_match


def find_body_def(body_addr_hex, generated):
    """Find `static void func_XXXX_body(int _entry) { ... }`.
    Returns (start_line, end_line, comment) or None.
    """
    pat = (
        rf"^static void func_{body_addr_hex}_body\(int _entry\) \{{"
        r"(?:\s*/\*\s*(.*?)\s*\*/)?"
    )
    for i, line in enumerate(generated):
        m = re.match(pat, line)
        if m:
            comment = m.group(1) or ""
            depth = 1
            for j in range(i + 1, len(generated)):
                cur = generated[j]
                opens = cur.count("{")
                closes = cur.count("}")
                if cur.rstrip() == "}" and depth == 1:
                    return (i, j, comment)
                depth += opens - closes
                if depth == 0:
                    return (i, j, comment)
    return None


def find_body_callers(body_addr_hex, generated):
    """Find all shim wrappers that call func_<body_addr>_body(N).
    Returns list of (addr_hex, suffix, entry_idx, comment) sorted by entry_idx.
    """
    func_def = re.compile(
        r"^void func_([0-9A-Fa-f]{4})(_b\d)?\(void\)\s*\{"
        r"(?:\s*/\*\s*(.*?)\s*\*/)?"
    )
    body_call = re.compile(
        rf"^func_{body_addr_hex}_body\((\d+)\);?$"
    )
    out = []
    seen = set()
    for i, line in enumerate(generated):
        m = func_def.match(line)
        if not m:
            continue
        addr = m.group(1).upper()
        suffix = m.group(2) or ""
        comment = m.group(3) or ""
        # Skim ahead ~20 lines for the body call
        for j in range(i + 1, min(i + 20, len(generated))):
            inner = generated[j].strip()
            mm = body_call.match(inner)
            if mm:
                idx = int(mm.group(1))
                key = (addr, suffix)
                if key in seen:
                    break
                seen.add(key)
                out.append((addr, suffix, idx, comment))
                break
    out.sort(key=lambda t: t[2])
    return out


# ---------------------------------------------------------------------------
# Body extraction + rewriting
# ---------------------------------------------------------------------------

def extract_body_lines(start, end, lines):
    """Extract just the body (between { and final }) excluding the function header.

    Strip the `#ifdef RECOMP_STACK_TRACKING ... #endif` blocks (entire block).
    """
    raw = []
    for k in range(start + 1, end):
        raw.append(lines[k].rstrip())
    out = []
    i = 0
    while i < len(raw):
        line = raw[i]
        if line.strip() == "#ifdef RECOMP_STACK_TRACKING":
            j = i + 1
            while j < len(raw) and raw[j].strip() != "#endif":
                j += 1
            i = j + 1
            continue
        out.append(line)
        i += 1
    return out


def rewrite_body(body_lines):
    """Rewrite inter-function calls to call_by_address.

    `func_XXXX_b0()` and `func_XXXX()` -> `call_by_address(0xXXXX)`.
    `func_XXXX_body(N)` calls (rare — body calling another body directly)
    are left as-is for now (won't link until those bodies are also ported).
    """
    out = []
    for line in body_lines:
        line = re.sub(
            r"\bfunc_([0-9A-Fa-f]{4})_b\d\(\)",
            r"call_by_address(0x\1)",
            line,
        )
        # Match func_XXXX() but NOT func_XXXX_body()
        line = re.sub(
            r"\bfunc_([0-9A-Fa-f]{4})\(\)(?!_body)",
            r"call_by_address(0x\1)",
            line,
        )
        out.append(line)
    return out


def slug_for_name(name):
    """Convert SymbolName to snake_case.

    Handles camelCase, acronyms, existing underscores, and digits.
    Examples:
      SoundEngine        -> sound_engine
      NoIncDAC           -> no_inc_dac
      Dump_Squ1_Regs     -> dump_squ1_regs
      Entry_F2D3         -> entry_f2d3
      Squ2NoteHandler    -> squ2_note_handler
    """
    # Split lowercase/digit -> uppercase boundary
    s = re.sub(r"([a-z0-9])([A-Z])", r"\1_\2", name)
    # Split end of acronym (UPPER+ -> Upper+lower)
    s = re.sub(r"([A-Z]+)([A-Z][a-z])", r"\1_\2", s)
    s = s.lower()
    # Replace any non-identifier chars
    s = re.sub(r"[^a-z0-9_]+", "_", s)
    # Collapse runs of underscores
    s = re.sub(r"_+", "_", s)
    return s.strip("_")


def entry_friendly_name(name_override, comment, addr_hex):
    """Pick a friendly C++ identifier for an entry point.

    Priority: user-supplied name > recompiler /* Comment */ > addr-based fallback.
    Address-based fallback uses lowercase `at_<addr>` so slug_for_name leaves it
    alone (no hex-digit-vs-letter splits).
    """
    if name_override:
        return name_override
    if comment:
        return comment
    return f"at_{addr_hex.lower()}"


# ---------------------------------------------------------------------------
# Module generation
# ---------------------------------------------------------------------------

def build_runtime_wiring(addr_hex, suffix, slug, class_name, name):
    """Generate (decl, def, extras_shim, toml_entry) for a single owned addr."""
    decl = f"void semcomp_runtime_{slug}(void);  // ${addr_hex} {name}"
    def_text = (
        f"void semcomp_runtime_{slug}(void) {{\n"
        f'    runtime().routines().register_routine(0x{addr_hex}, "{name}");\n'
        f"    runtime().routines().note_invocation(0x{addr_hex});\n"
        f"    runtime().{slug_for_name(class_name)}().{slug}();\n"
        f"}}"
    )
    func_decl = f"func_{addr_hex}{suffix}"
    extras_shim = f"void {func_decl}(void) {{ semcomp_runtime_{slug}(); }}"
    if suffix == "_b0":
        toml = f"[[replace_func]]\nbank = 0\naddr = 0x{addr_hex}\n"
    else:
        toml = f"[[replace_func]]\naddr = 0x{addr_hex}\n"
    return decl, def_text, extras_shim, toml


def generate_module(module_name, class_name, routines, generated):
    """Generate header + cpp + wiring fragments for a set of routines.

    Handles both single-entry and multi-entry (shim+body) patterns. For
    multi-entry, auto-discovers sibling entries to ensure full body ownership.
    """
    cpp_lines = [
        f"// semcomp/{module_name}.cpp — bulk-ported routines (auto-generated).",
        f'#include "semcomp/{module_name}.h"',
        "",
        '#include "semcomp/GameState.h"',
        '#include "semcomp/cpu_flags.h"',
        "",
        'extern "C" {',
        '#include "nes_runtime.h"',
        "}",
        "",
        "namespace smb::semcomp {",
        "",
    ]
    header_lines = [
        f"// semcomp/{module_name}.h — bulk-ported routines (auto-generated).",
        "#pragma once",
        "",
        "#include <cstdint>",
        "",
        "namespace smb::semcomp {",
        "",
        "class GameState;",
        "",
        f"class {class_name} {{",
        "public:",
        f"    explicit {class_name}(GameState& state) : state_(state) {{}}",
        "",
    ]
    runtime_decls = []
    runtime_defs = []
    extras_shims = []
    toml_entries = []
    skipped = []
    body_methods = []  # cpp blocks for private body() methods, appended later

    # ---- Phase 1: classify routines -----------------------------------------
    # singles: list of (addr, name, start, end, suffix)
    # body_groups: dict body_addr_hex -> {
    #     "comment": str,
    #     "user_overrides": dict entry_idx -> (name, suffix),
    # }
    singles = []
    body_groups = {}
    owned_already = load_owned_addresses()
    for addr_hex, name in routines:
        res = find_function(addr_hex, generated)
        if not res:
            skipped.append((addr_hex, name, "not found"))
            continue
        start, end, suffix = res
        shim = detect_shim_target(start, end, generated)
        if shim is None:
            # Single-entry — body is inline
            singles.append((addr_hex.upper(), name, start, end, suffix))
        else:
            body_addr, entry_idx = shim
            grp = body_groups.setdefault(body_addr, {"user_overrides": {}})
            grp["user_overrides"][entry_idx] = (name, suffix)

    # ---- Phase 2: emit single-entry methods ---------------------------------
    for addr_hex, name, start, end, suffix in singles:
        body = extract_body_lines(start, end, generated)
        body = rewrite_body(body)
        slug = slug_for_name(name)
        cpp_lines.append(f"void {class_name}::{slug}() {{")
        cpp_lines.append("    (void)state_;")
        for line in body:
            cpp_lines.append(line)
        cpp_lines.append("}")
        cpp_lines.append("")
        header_lines.append(f"    void {slug}();  // ${addr_hex} {name}")
        if addr_hex in owned_already:
            skipped.append((addr_hex, name, "already owned in game.toml — wiring skipped"))
            continue
        d, df, ex, tm = build_runtime_wiring(addr_hex, suffix, slug, class_name, name)
        runtime_decls.append(d)
        runtime_defs.append(df)
        extras_shims.append(ex)
        toml_entries.append(tm)

    # ---- Phase 3: emit multi-entry body groups ------------------------------
    private_body_decls = []  # for header private: section
    for body_addr in sorted(body_groups.keys()):
        grp = body_groups[body_addr]
        user_overrides = grp["user_overrides"]
        body_def = find_body_def(body_addr, generated)
        if not body_def:
            for idx, (nm, _) in user_overrides.items():
                skipped.append((body_addr, nm, f"body func_{body_addr}_body not found"))
            continue
        body_start, body_end, body_comment = body_def

        # Discover ALL siblings calling this body (auto-expand for 100% ownership).
        all_entries = find_body_callers(body_addr, generated)
        if not all_entries:
            # Shouldn't happen — we found a shim that pointed here. Fall through.
            skipped.append((body_addr, "?", "no callers found for body"))
            continue

        # Resolve friendly names for every entry.
        # Use user override if provided, otherwise recompiler comment, otherwise addr.
        entry_specs = []  # list of (addr, suffix, idx, friendly_name, slug)
        for addr, suf, idx, com in all_entries:
            override = user_overrides.get(idx)
            if override:
                friendly = override[0]
                use_suffix = override[1] if override[1] == suf else suf
            else:
                friendly = entry_friendly_name(None, com, addr)
                use_suffix = suf
            slug = slug_for_name(friendly)
            entry_specs.append((addr, use_suffix, idx, friendly, slug))
        entry_specs.sort(key=lambda t: t[2])

        # Pick a name for the body method based on entry 0's friendly name.
        root_friendly = entry_specs[0][3] if entry_specs else body_comment or f"body_{body_addr}"
        body_method_slug = slug_for_name(root_friendly) + "_body"

        # Extract body content (between { and final }).
        body_raw = extract_body_lines(body_start, body_end, generated)
        body_rewritten = rewrite_body(body_raw)

        # Emit private body method into cpp.
        body_methods.append(f"void {class_name}::{body_method_slug}(int _entry) {{")
        body_methods.append("    (void)state_;")
        for line in body_rewritten:
            body_methods.append(line)
        body_methods.append("}")
        body_methods.append("")

        # Declare body method in header (private section).
        private_body_decls.append(
            f"    void {body_method_slug}(int _entry);  // shared body for ${body_addr}"
            + (f" /* {body_comment} */" if body_comment else "")
        )

        # Emit one public method per entry.
        for addr, suf, idx, friendly, slug in entry_specs:
            cpp_lines.append(f"void {class_name}::{slug}() {{")
            cpp_lines.append(f"    {body_method_slug}({idx});")
            cpp_lines.append("}")
            cpp_lines.append("")
            header_lines.append(
                f"    void {slug}();  // ${addr} {friendly} (entry {idx})"
            )
            if addr in owned_already:
                # Already replace_func'd by an earlier phase. Skip wiring so we
                # don't emit duplicate toml/extras entries — the public method
                # still exists in our class for use by other semcomp code if
                # needed, but no new dispatch hookup.
                skipped.append(
                    (addr, friendly, "already owned in game.toml — wiring skipped")
                )
                continue
            d, df, ex, tm = build_runtime_wiring(addr, suf, slug, class_name, friendly)
            runtime_decls.append(d)
            runtime_defs.append(df)
            extras_shims.append(ex)
            toml_entries.append(tm)

    # Append the private body methods after public methods in the cpp.
    cpp_lines.extend(body_methods)

    # ---- Phase 4: finalize header -------------------------------------------
    header_lines.extend([
        "",
        "private:",
    ])
    for d in private_body_decls:
        header_lines.append(d)
    header_lines.extend([
        "    GameState& state_;",
        "};",
        "",
        "}  // namespace smb::semcomp",
    ])
    cpp_lines.append("}  // namespace smb::semcomp")

    return {
        "header": "\n".join(header_lines) + "\n",
        "cpp": "\n".join(cpp_lines) + "\n",
        "runtime_decls": "\n".join(runtime_decls) + "\n",
        "runtime_defs": "\n\n".join(runtime_defs) + "\n",
        "extras_shims": "\n".join(extras_shims) + "\n",
        "toml_entries": "\n".join(toml_entries),
        "skipped": skipped,
    }


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------

def main():
    """Driven by CLI args:  python semcomp_bulk_port.py <module> <class> <addr1=name1> ..."""
    if len(sys.argv) < 4:
        print("usage: semcomp_bulk_port.py <module> <class> <addr1=Name1> [addr2=Name2 ...]")
        sys.exit(1)
    module_name = sys.argv[1]
    class_name = sys.argv[2]
    routines = []
    for arg in sys.argv[3:]:
        addr, name = arg.split("=", 1)
        routines.append((addr, name))

    generated = FULL_C.read_text(encoding="utf-8").splitlines()
    result = generate_module(module_name, class_name, routines, generated)

    (ROOT / "semcomp" / f"{module_name}.h").write_text(result["header"], encoding="utf-8")
    (ROOT / "semcomp" / f"{module_name}.cpp").write_text(result["cpp"], encoding="utf-8")

    wiring = (
        "// ---- Runtime.h decls (add at end of bridges block) ----\n"
        + result["runtime_decls"]
        + "\n// ---- Runtime.cpp definitions ----\n"
        + result["runtime_defs"]
        + "\n// ---- extras.c shims ----\n"
        + result["extras_shims"]
        + "\n// ---- game.toml [[replace_func]] entries ----\n"
        + result["toml_entries"]
    )
    (ROOT / f"_wiring_{module_name}.txt").write_text(wiring, encoding="utf-8")

    print(f"Wrote semcomp/{module_name}.h, semcomp/{module_name}.cpp")
    n_emitted = result["toml_entries"].count("[[replace_func]]")
    print(f"Wrote _wiring_{module_name}.txt with {n_emitted} replace_func entries.")
    if result["skipped"]:
        print("SKIPPED:")
        for addr, name, reason in result["skipped"]:
            print(f"  ${addr} {name}: {reason}")


if __name__ == "__main__":
    main()
