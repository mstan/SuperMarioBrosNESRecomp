with open('semcomp/Runtime.cpp', 'r', encoding='utf-8') as f: s = f.read()
with open('/tmp/eh2_rt_cpp.txt', 'r', encoding='utf-8') as f: eh2 = f.read()
needle = '}  // extern "C"'
idx = s.rfind(needle)
new_s = s[:idx] + '// Phase 24 batch 2 — Enemies mega (continued).\n' + eh2 + '\n' + s[idx:]
with open('semcomp/Runtime.cpp', 'w', encoding='utf-8') as f: f.write(new_s)
print('ok')
