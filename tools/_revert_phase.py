import sys
target = sys.argv[1]
with open('game.toml', 'r', encoding='utf-8') as f: s = f.read()
idx = s.find(target)
if idx >= 0:
    s = s[:idx].rstrip() + '\n'
    with open('game.toml', 'w', encoding='utf-8') as f: f.write(s)
    print(f'Reverted {target!r} from game.toml')
else:
    print(f'{target!r} not found')
