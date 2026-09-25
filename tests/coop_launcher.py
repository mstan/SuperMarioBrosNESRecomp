"""Exercise P3/P4 keyboard capture in the actual launcher and restart it.

Uses the launcher's SDL event script, not direct calls to its binding store.
Copies the build into an isolated folder so user settings are preserved.
"""
from pathlib import Path
import argparse
import configparser
import os
import shutil
import subprocess


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--exe', required=True, type=Path)
    ap.add_argument('--rom', required=True, type=Path)
    ap.add_argument('--out', type=Path, default=Path('build-coop/launcher-test'))
    a = ap.parse_args()
    out = a.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    exe = out / a.exe.name
    shutil.copy2(a.exe, exe)
    for dll in a.exe.parent.glob('*.dll'):
        shutil.copy2(dll, out / dll.name)
    for folder in ('assets', 'mods/packages'):
        shutil.copytree(a.exe.parent / folder, out / folder, dirs_exist_ok=True)
    (out / 'rom.cfg').write_text(str(a.rom.resolve()) + '\n')
    (out / 'config.ini').write_text(
        '[Input]\nPlayer1Source=1\nPlayer2Source=1\nPlayer3Source=1\nPlayer4Source=1\n')
    original = '[player1]\na=Z\n[player2]\na=K\n[player3]\na=None\n[player4]\nb=None\n'
    # Include a runtime-owned section to catch accidental whole-file rewrites.
    (out / 'keybinds.ini').write_text(original + '[gamepad4]\na=rightshoulder\n')

    def launch(name, commands):
        env = dict(os.environ, LNG_TEST_HIDDEN='1',
                   LNG_SCRIPT=';'.join(['size:1100x880'] + commands))
        env.pop('NESRECOMP_NO_LAUNCHER', None)
        env.pop('NES_NETPLAY', None)
        r = subprocess.run([str(exe), '--launcher'], cwd=out, env=env,
                           creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0), capture_output=True, text=True, timeout=60)
        (out / f'{name}.log').write_text(r.stdout + r.stderr)
        assert r.returncode == 0, (name, r.returncode, r.stderr)

    launch('capture', ['wait:20', 'view:controller', 'player:2', 'capbtn:4',
                      'key:U', 'wait:3', f'shot:{(out / "p3.png").as_posix()}',
                      'player:3', 'capbtn:5', 'key:I', 'wait:3',
                      f'shot:{(out / "p4.png").as_posix()}', 'quit'])
    ini = configparser.ConfigParser()
    ini.read(out / 'keybinds.ini')
    assert ini['player3']['a'] == 'U', 'P3 capture did not persist'
    assert ini['player4']['b'] == 'I', 'P4 capture did not persist'
    assert ini['player1']['a'] == 'Z' and ini['player2']['a'] == 'K'
    assert ini['gamepad4']['a'] == 'rightshoulder'
    saved = (out / 'keybinds.ini').read_bytes()
    launch('reload', ['wait:20', 'view:controller', 'player:2', 'wait:3',
                     f'shot:{(out / "p3-reloaded.png").as_posix()}',
                     'player:3', 'wait:3',
                     f'shot:{(out / "p4-reloaded.png").as_posix()}', 'quit'])
    assert (out / 'keybinds.ini').read_bytes() == saved
    # Click the real Reset to Defaults button in the fixed-size controller view.
    launch('reset', ['wait:20', 'view:controller', 'player:2', 'wait:3',
                     'click:120,440', 'wait:5', 'player:3', 'wait:3',
                     'click:120,440', 'wait:5', 'quit'])
    ini.read(out / 'keybinds.ini')
    for player in ('player3', 'player4'):
        assert len(ini[player]) == 8 and set(ini[player].values()) == {'None'}, player
    assert ini['player1']['a'] == 'Z' and ini['player2']['a'] == 'K'
    assert ini['gamepad4']['a'] == 'rightshoulder'
    print('PASS: launcher SDL capture, restart, and reset for P3/P4; P1/P2 and pad binds preserved')


if __name__ == '__main__':
    main()
