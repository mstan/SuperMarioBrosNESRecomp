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

Used for Phase 24+ where individual hand-porting is impractical due
to the routine count (60-80 enemies + 30-40 level + 80-100 sound).
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).parent.parent
FULL_C = ROOT / "generated" / "super-mario-bros_full.c"


def find_function(addr_hex, generated):
    """Find the function body for hex addr like 'C30E' or 'C30E_b0'.
    Returns (start_line, end_line, suffix). suffix is e.g. '_b0' or ''.
    """
    addr = addr_hex.upper()
    # Try with _b0 suffix first (bank-suffixed names)
    # Only match the DEFINITION (line ends with `{`), not the forward
    # declaration (line ends with `;`).
    patterns = [
        (rf"^(?:static )?void func_{addr}_b0\(void\) \{{", "_b0"),
        (rf"^(?:static )?void func_{addr}\(void\) \{{", ""),
    ]
    for pat, suffix in patterns:
        for i, line in enumerate(generated):
            if re.match(pat, line):
                # Track brace depth to find the matching close brace.
                # Start at depth 1 because the header line ends with `{`.
                depth = 1
                for j in range(i + 1, len(generated)):
                    cur = generated[j]
                    # Count occurrences (very rough, but ok for generated code
                    # which doesn't use { or } inside strings/comments often).
                    opens = cur.count("{")
                    closes = cur.count("}")
                    # If the line is the standalone closing `}` at depth 1,
                    # treat it as function close. Otherwise update depth.
                    if cur.rstrip() == "}" and depth == 1:
                        return (i, j, suffix)
                    depth += opens - closes
                    if depth == 0:
                        return (i, j, suffix)
                return (i, len(generated) - 1, suffix)
    return None


def extract_body_lines(start, end, lines):
    """Extract just the body (between { and final }) excluding the function header.

    Strip the `#ifdef RECOMP_STACK_TRACKING ... #endif` blocks (entire block, 3 lines).
    Other `#ifdef ... #endif` blocks (e.g. WATCHDOG_ENABLED) are preserved.
    """
    raw = []
    for k in range(start + 1, end):
        raw.append(lines[k].rstrip())
    out = []
    i = 0
    while i < len(raw):
        line = raw[i]
        # Detect the 3-line stack-tracking block:
        #   #ifdef RECOMP_STACK_TRACKING
        #       recomp_stack_push(...) or recomp_stack_pop()
        #   #endif
        if line.strip() == "#ifdef RECOMP_STACK_TRACKING":
            # Skip until matching #endif (inside the body, RECOMP_STACK_TRACKING
            # blocks are short and never nested).
            j = i + 1
            while j < len(raw) and raw[j].strip() != "#endif":
                j += 1
            i = j + 1  # skip past #endif
            continue
        out.append(line)
        i += 1
    return out


def rewrite_body(body_lines):
    """Rewrite the body to use call_by_address for cross-function calls.

    The recompiler emits both `func_XXXX_b0()` and `call_by_address(0xXXXX)`.
    For our verbatim port to compile, we need to ensure all func_*_b0() calls
    refer to functions that still exist OR be converted to call_by_address.
    Since replace_func may strip some functions, the safest is to convert
    all `func_XXXX[_b0]()` calls to `call_by_address(0xXXXX)`.
    """
    out = []
    for line in body_lines:
        # func_XXXX_b0()  -> call_by_address(0xXXXX)
        line = re.sub(
            r"\bfunc_([0-9A-Fa-f]{4})_b\d\(\)",
            r"call_by_address(0x\1)",
            line,
        )
        # func_XXXX()     -> call_by_address(0xXXXX)
        # Avoid matching func_XXXX_body() helpers (private)
        line = re.sub(
            r"\bfunc_([0-9A-Fa-f]{4})\(\)(?!_body)",
            r"call_by_address(0x\1)",
            line,
        )
        out.append(line)
    return out


def slug_for_name(name):
    """Convert SymbolName to snake_case."""
    s = re.sub(r"(?<!^)(?=[A-Z])", "_", name).lower()
    return s


def generate_module(module_name, class_name, routines, generated):
    """Generate header + cpp + wiring fragments for a set of routines."""
    cpp_lines = [
        f"// semcomp/{module_name}.cpp — bulk-ported routines (auto-generated).",
        '#include "semcomp/' + module_name + '.h"',
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

    for addr_hex, name in routines:
        result = find_function(addr_hex, generated)
        if not result:
            skipped.append((addr_hex, name, "not found"))
            continue
        start, end, suffix = result
        body = extract_body_lines(start, end, generated)
        # Detect multi-entry-body wrapper (body is just `func_XXX_body(N);`)
        body_stripped = [l for l in body if l.strip()]
        if any("_body(" in l for l in body_stripped):
            skipped.append((addr_hex, name, "multi-entry-body wrapper"))
            continue
        body = rewrite_body(body)
        slug = slug_for_name(name)
        # Method
        cpp_lines.append(f"void {class_name}::{slug}() {{")
        cpp_lines.append("    (void)state_;")
        for line in body:
            cpp_lines.append(line)
        cpp_lines.append("}")
        cpp_lines.append("")
        # Header
        header_lines.append(f"    void {slug}();  // ${addr_hex} {name}")
        # Runtime bridge
        runtime_decls.append(
            f"void semcomp_runtime_{slug}(void);  // ${addr_hex} {name}"
        )
        member_lc = class_name[0].lower() + class_name[1:]
        # Use snake_case for runtime accessor: PhaseNNFoo -> phase_n_n_foo... no, just hardcode.
        runtime_defs.append(
            f"""void semcomp_runtime_{slug}(void) {{
    runtime().routines().register_routine(0x{addr_hex}, "{name}");
    runtime().routines().note_invocation(0x{addr_hex});
    runtime().{slug_for_name(class_name)}().{slug}();
}}"""
        )
        # extras.c shim
        func_decl = f"func_{addr_hex}{suffix}"
        extras_shims.append(f"void {func_decl}(void) {{ semcomp_runtime_{slug}(); }}")
        # toml entry — fixed-bank functions get no `bank = 0`
        if suffix == "_b0":
            toml_entries.append(f"[[replace_func]]\nbank = 0\naddr = 0x{addr_hex}\n")
        else:
            toml_entries.append(f"[[replace_func]]\naddr = 0x{addr_hex}\n")

    header_lines.extend([
        "",
        "private:",
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

    # Write header + cpp
    (ROOT / "semcomp" / f"{module_name}.h").write_text(result["header"], encoding="utf-8")
    (ROOT / "semcomp" / f"{module_name}.cpp").write_text(result["cpp"], encoding="utf-8")

    # Emit wiring fragments to a single file so the caller can review/paste
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
    print(f"Wrote _wiring_{module_name}.txt with {len(routines) - len(result['skipped'])} routines.")
    if result["skipped"]:
        print("SKIPPED (not found):")
        for addr, name, reason in result["skipped"]:
            print(f"  ${addr} {name}: {reason}")


if __name__ == "__main__":
    main()
