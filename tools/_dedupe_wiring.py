"""Remove duplicate function definitions in Runtime.cpp/h, extras.c, game.toml.

For each file, find duplicate `void XXX(void)` definitions and keep only the
first occurrence. Works by line-based deduplication of function bodies.
"""
import re

def dedupe_runtime_cpp():
    with open('semcomp/Runtime.cpp', 'r', encoding='utf-8') as f:
        s = f.read()
    # Match `void semcomp_runtime_NAME(void) {` ... `}` blocks. Keep first.
    pattern = re.compile(
        r'(void (semcomp_runtime_\w+)\(void\) \{[^}]*?\})',
        re.DOTALL
    )
    seen = set()
    def replace(m):
        name = m.group(2)
        if name in seen:
            return ''
        seen.add(name)
        return m.group(1)
    s = pattern.sub(replace, s)
    # Collapse triple-blank lines.
    s = re.sub(r'\n\n\n+', '\n\n', s)
    with open('semcomp/Runtime.cpp', 'w', encoding='utf-8') as f:
        f.write(s)

def dedupe_runtime_h():
    with open('semcomp/Runtime.h', 'r', encoding='utf-8') as f:
        lines = f.readlines()
    seen = set()
    out = []
    for line in lines:
        m = re.match(r'^void (semcomp_runtime_\w+)\(void\);', line)
        if m:
            if m.group(1) in seen:
                continue
            seen.add(m.group(1))
        out.append(line)
    with open('semcomp/Runtime.h', 'w', encoding='utf-8') as f:
        f.writelines(out)

def dedupe_extras():
    with open('extras.c', 'r', encoding='utf-8') as f:
        lines = f.readlines()
    seen = set()
    out = []
    for line in lines:
        m = re.match(r'^void (func_\w+)\(void\) \{', line)
        if m:
            if m.group(1) in seen:
                continue
            seen.add(m.group(1))
        out.append(line)
    with open('extras.c', 'w', encoding='utf-8') as f:
        f.writelines(out)

def dedupe_toml():
    with open('game.toml', 'r', encoding='utf-8') as f:
        s = f.read()
    # For each `addr = 0xXXXX`, keep only the first [[replace_func]] block.
    pattern = re.compile(r'(\[\[replace_func\]\]\r?\n(?:bank = \d+\r?\n)?addr = (0x[0-9A-Fa-f]+)[^\n]*\r?\n)', re.MULTILINE)
    seen = set()
    def replace(m):
        addr = m.group(2).upper()
        if addr in seen:
            return ''
        seen.add(addr)
        return m.group(1)
    s = pattern.sub(replace, s)
    s = re.sub(r'\r?\n\r?\n\r?\n+', '\r\n\r\n', s)
    with open('game.toml', 'w', encoding='utf-8', newline='') as f:
        f.write(s)

dedupe_runtime_cpp()
dedupe_runtime_h()
dedupe_extras()
dedupe_toml()
print('dedupe complete')
