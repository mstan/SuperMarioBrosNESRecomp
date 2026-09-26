"""Write a deterministic multi-seat input script for the rollback probe.

    python tests/netplay/gen_probe_script.py --players 4 --frames 5400 --seed 7 out.script

The script starts a game (Start at the title; with --coop N the runner offers
CO-OP PLAY) and then drives every seat with its own run/jump/back-off pattern,
so NES_RB_PROBE windows land on title, gameplay, deaths and team wipes. Used by
nesrecomp tools/rb_sweep.sh as RB_SWEEP_PROBE_SCRIPT (with
RB_SWEEP_PROBE_ARGS="--coop 4"). Scripts are offline-only: an online session
refuses them (every seat's input must come from the published rows).
"""
import argparse
import random


def generate(players, frames, seed):
    r = random.Random(seed)
    lines = ['WAIT 60', 'HOLD START', 'WAIT 6', 'RELEASE START',
             'WAIT_RAM8 000E 08', 'WAIT 20']
    held = {p: set() for p in range(1, players + 1)}
    t = 0
    while t < frames:
        for p in range(1, players + 1):
            sfx = '' if players == 1 else f' {p}'
            want = set()
            x = r.random()
            if x < 0.8:
                want.add('RIGHT')
            elif x < 0.9:
                want.add('LEFT')
            if r.random() < 0.45:
                want.add('A')
            if r.random() < 0.5:
                want.add('B')
            if r.random() < 0.05:
                want.add('DOWN')
            for b in sorted(held[p] - want):
                lines.append(f'RELEASE {b}{sfx}')
            for b in sorted(want - held[p]):
                lines.append(f'HOLD {b}{sfx}')
            held[p] = want
        w = r.choice([4, 8, 12, 20, 30])
        lines.append(f'WAIT {w}')
        t += w
    lines.append('EXIT 0')
    return '\n'.join(lines) + '\n'


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--players', type=int, default=4)
    ap.add_argument('--frames', type=int, default=5400)
    ap.add_argument('--seed', type=int, default=7)
    ap.add_argument('out')
    a = ap.parse_args()
    with open(a.out, 'w') as f:
        f.write(generate(a.players, a.frames, a.seed))


if __name__ == '__main__':
    main()
