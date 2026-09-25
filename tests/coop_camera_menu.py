"""Native regressions for signed camera motion and the title-to-game menu."""
from pathlib import Path
import argparse
from coop_runtime import Harness, State, RAM

NT = RAM + 0x800 + 0x2000 + 0x2000 + 0x100 + 0x20


def tiles(text):
    return bytes(0x24 if c == ' ' else 0x28 if c == '-' else
                 int(c) if c.isdigit() else ord(c) - ord('A') + 10 for c in text)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--exe', required=True, type=Path)
    ap.add_argument('--rom', required=True, type=Path)
    ap.add_argument('--out', type=Path, default=Path('build-coop/camera-menu'))
    a = ap.parse_args()
    h = Harness(a.exe, a.rom, a.out)
    out = h.out
    title = h.run('title', '', boot_script='WAIT 60\n')
    assert title.data[NT+0x249] == 0xce, 'native mushroom cursor is missing'
    assert title.data[NT+0x24b:NT+0x258] == tiles('CO-OP PLAY   ')
    assert title.data[NT+0x28b:NT+0x298] == tiles('             ')
    selected = h.run('select', 'HOLD SELECT\nHOLD SELECT 2\nWAIT 3', fixture=title)
    assert selected.data[NT+0x249] == 0xce, 'Select moved the sole menu cursor'
    # WAIT 2 advances one frame in the script interpreter (WAIT 1 is immediate).
    # Record consecutive actual frames, including the frames after OperMode
    # changes but before the PPU has cleared the title nametable.
    body = 'HOLD START\n'
    for n in range(24):
        body += f'WAIT 2\nSAVE_STATE {(out/f"start-{n}.sav").as_posix()}\n'
        body += f'SCREENSHOT {(out/f"start-{n}.png").as_posix()}\n'
    h.run('start', body, fixture=title)
    for n in range(24):
        nt = State(out/f'start-{n}.sav').data[NT:NT+0x1000]
        assert tiles('1 PLAYER GAME') not in nt and tiles('2 PLAYER GAME') not in nt, n
    print('PASS: native mushroom, single menu, and no original labels throughout Start', flush=True)

    boot = h.run('boot', 'WAIT 1')
    for survivor in (None, 0, 3):
        f = State(out/'boot.sav')
        for p in range(4):
            actor = f.actor(p)
            actor[0x86] = 100 if survivor is not None else 80+p*8
            actor[0x57] = 0xe8  # already moving left at normal walking speed
            actor[0x755] = actor[0x86]
            if survivor is not None and p != survivor:
                actor[2048] = 2
        name = 'party' if survivor is None else f'survivor-{survivor+1}'
        body = f'SAVE_STATE {(out/f"{name}-initial.sav").as_posix()}\n'
        body += ''.join(f'HOLD LEFT {p+1}\n' for p in range(4))
        for n in range(16):
            body += f'WAIT 2\nSAVE_STATE {(out/f"{name}-{n}.sav").as_posix()}\n'
        h.run(name, body, fixture=f)
        previous = State(out/f'{name}-initial.sav')
        for n in range(16):
            current = State(out/f'{name}-{n}.sav')
            assert current.ram[0x71a]*256+current.ram[0x71c] == 0, (name,n,'leftward motion scrolled forward')
            for p in range(4):
                if current.actor(p)[2048] == 0:
                    assert -4 <= current.x(p)-previous.x(p) <= 0, (name,n,p,'player snapped')
            previous = current
    # A leader cannot move the boundary beyond a living teammate. Once the
    # teammate moves forward, normal scrolling resumes without teleporting it.
    waiting = h.run('rear-waits', 'HOLD RIGHT 4\nHOLD B 4\nWAIT 90', fixture=boot)
    assert waiting.ram[0x71a]*256+waiting.ram[0x71c] <= min(boot.x(p) for p in range(3))
    for p in range(3):
        assert waiting.x(p) == boot.x(p), 'camera pushed a waiting teammate'
    body = f'SAVE_STATE {(out/"catchup-initial.sav").as_posix()}\n'
    body += ''.join(f'HOLD RIGHT {p+1}\nHOLD B {p+1}\n' for p in range(4))
    for n in range(32):
        body += f'WAIT 2\nSAVE_STATE {(out/f"catchup-{n}.sav").as_posix()}\n'
    h.run('catchup', body, fixture=waiting)
    previous = State(out/'catchup-initial.sav')
    for n in range(32):
        current = State(out/f'catchup-{n}.sav')
        left = lambda state: state.ram[0x71a]*256+state.ram[0x71c]
        assert 0 <= left(current)-left(previous) <= 4, (n,'camera jumped during catchup')
        assert left(current) <= min(current.x(p) for p in range(4) if current.actor(p)[2048] == 0)
        for p in range(4):
            assert abs(current.x(p)-previous.x(p)) <= 4, (n,p,'player snapped during catchup')
        previous = current
    assert left(previous) > left(waiting), 'camera never resumed after the rear caught up'
    print('PASS: signed movement for party/P1/P4 survivors and rear-player camera limit', flush=True)


if __name__ == '__main__':
    main()
