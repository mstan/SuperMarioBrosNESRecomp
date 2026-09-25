"""Check AppImage launcher bindings survive restart and reach the game.

Run under xvfb-run on Linux to keep the actual SDL launcher off the desktop.
The packaged production build is sufficient; no TCP/debug server is used.
"""
import argparse
import configparser
import os
from pathlib import Path
import shutil
import subprocess


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--appimage', required=True, type=Path)
    ap.add_argument('--rom', required=True, type=Path)
    ap.add_argument('--out', required=True, type=Path)
    a = ap.parse_args()
    out = a.out.resolve()
    out.mkdir(parents=True, exist_ok=False)
    image = out / a.appimage.name
    shutil.copy2(a.appimage, image)
    image.chmod(0o755)
    (out / 'rom.cfg').write_text(str(a.rom.resolve()) + '\n')
    (out / 'config.ini').write_text('[Input]\nPlayer1Source=1\nPlayer2Source=1\nPlayer3Source=1\nPlayer4Source=1\n')
    (out / 'keybinds.ini').write_text('[player1]\na=Z\n[player2]\na=K\n[player3]\na=None\n[player4]\nb=None\n[gamepad4]\na=rightshoulder\n')
    env = dict(os.environ, APPIMAGE_EXTRACT_AND_RUN='1', LNG_TEST_HIDDEN='1', SDL_AUDIODRIVER='dummy')
    env.pop('NESRECOMP_NO_LAUNCHER', None)
    env.pop('NES_NETPLAY', None)

    def launch(name, commands):
        scripted = dict(env, LNG_SCRIPT=';'.join(['size:1100x880', 'wait:20'] + commands + ['quit']))
        result = subprocess.run([str(image), '--launcher'], cwd=out, env=scripted,
                                capture_output=True, text=True, timeout=45)
        (out / f'{name}.log').write_text(result.stdout + result.stderr)
        assert result.returncode == 0, result.stderr

    launch('capture', ['view:controller', 'player:2', 'capbtn:4', 'key:U', 'wait:3',
                      'player:3', 'capbtn:5', 'key:I', 'wait:3'])
    ini = configparser.ConfigParser()
    ini.read(out / 'keybinds.ini')
    assert ini['player3']['a'] == 'U' and ini['player4']['b'] == 'I'
    assert ini['player1']['a'] == 'Z' and ini['player2']['a'] == 'K'
    assert ini['gamepad4']['a'] == 'rightshoulder'
    saved = (out / 'keybinds.ini').read_bytes()
    launch('reload', ['view:controller', 'player:2', 'wait:3',
                     f'shot:{out}/p3.png', 'player:3', 'wait:3', f'shot:{out}/p4.png'])
    assert (out / 'keybinds.ini').read_bytes() == saved
    for player in ('p3', 'p4'):
        assert (out / f'{player}.png').stat().st_size > 1000
    result = subprocess.run([str(image), str(a.rom.resolve()), '--smoke', '1'],
                            cwd=out, env=env, capture_output=True, text=True, timeout=30)
    (out / 'runner.log').write_text(result.stdout + result.stderr)
    assert result.returncode == 0, result.stderr
    assert f'[Keybinds] Loaded {out}/keybinds.ini' in result.stdout, result.stdout
    assert (out / 'keybinds.ini').read_bytes() == saved
    assert 'TCP server listening' not in result.stderr
    print('PASS: packaged AppImage P3/P4 capture, reload, persistent runtime path, and untouched P1/P2/gamepad binds')


if __name__ == '__main__':
    main()