"""Apply the wiring from _wiring_<Module>.txt to the appropriate files."""
import sys
import os
import re

if len(sys.argv) != 3:
    print("usage: _apply_wiring.py <Module> <batch_label>")
    sys.exit(1)

module = sys.argv[1]
batch_label = sys.argv[2]

wiring_path = f"_wiring_{module}.txt"
with open(wiring_path, "r", encoding="utf-8") as f:
    text = f.read()

def section(header_marker):
    pat = re.compile(rf"// ---- {re.escape(header_marker)}.*?\n(.*?)(?=// ---- |$)", re.DOTALL)
    m = pat.search(text)
    return m.group(1).rstrip() + "\n" if m else ""

rt_h = section("Runtime.h decls")
rt_cpp = section("Runtime.cpp definitions")
extras = section("extras.c shims")
toml = section("game.toml [[replace_func]] entries")

# 1. Append decls to Runtime.h before the final #ifdef __cplusplus close.
with open("semcomp/Runtime.h", "r", encoding="utf-8") as f:
    s = f.read()
close = "\n#ifdef __cplusplus\n}\n#endif"
idx = s.rfind(close)
s = s[:idx] + "\n// " + batch_label + "\n" + rt_h + s[idx:]
with open("semcomp/Runtime.h", "w", encoding="utf-8") as f:
    f.write(s)

# 2. Insert defs into Runtime.cpp before the final `}  // extern "C"`.
with open("semcomp/Runtime.cpp", "r", encoding="utf-8") as f:
    s = f.read()
needle = '}  // extern "C"'
idx = s.rfind(needle)
s = s[:idx] + "// " + batch_label + "\n" + rt_cpp + "\n" + s[idx:]
with open("semcomp/Runtime.cpp", "w", encoding="utf-8") as f:
    f.write(s)

# 3. Append shims to extras.c.
with open("extras.c", "a", encoding="utf-8") as f:
    f.write("\n/* " + batch_label + " */\n")
    f.write(extras)

# 4. Append toml entries to game.toml.
with open("game.toml", "a", encoding="utf-8") as f:
    f.write("\n# " + batch_label + "\n")
    f.write(toml)

print(f"Applied wiring for {module} ({batch_label})")
