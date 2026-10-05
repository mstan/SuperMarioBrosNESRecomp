#!/usr/bin/env python3
"""Verify a relocated cycle Mod's activation and paused save presentation.

Requires local owner ROMs/resources and a matching save/picture captured from
an active headless run. No copyrighted test inputs are distributed. Example:
  python tests/cycle_mod_runtime.py --exe build/Release/SuperMarioBrosRecomp.exe
    --rom game.nes --mods <local-mod-root> --state <active-save.cycstate>
    --picture <headless-present.png> --activation 'Player replacement armed: Captain Falcon'
    --out build/mod-smoke-falcon
"""
import argparse
import json
import os
from pathlib import Path
import shutil
import socket
import subprocess
import time


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    for name in ('exe', 'rom', 'mods', 'state', 'picture', 'out'):
        ap.add_argument('--'+name, type=Path, required=True)
    ap.add_argument('--activation', required=True, help='Expected successful activation log message')
    args = ap.parse_args()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    source = args.exe.resolve().parent
    assert out != source, 'Run from an isolated staging folder'
    for name in (args.exe.name, 'SDL2.dll', 'falcon_owner_assets.exe', 'falcon_owner_assets'):
        file = source / name
        if file.is_file():
            shutil.copy2(file, out / name)
    if (source / 'assets').is_dir():
        shutil.copytree(source / 'assets', out / 'assets', dirs_exist_ok=True)
    shutil.copytree(args.mods.resolve(), out / 'mods', dirs_exist_ok=True)
    config = out / 'config.ini'
    config.write_text('[Launcher]\nSkipLauncher=1\n[Display]\nWindowScale=1\n')
    with socket.socket() as reservation:
        reservation.bind(('127.0.0.1', 0))
        port = reservation.getsockname()[1]
    si = None
    if hasattr(subprocess, 'STARTUPINFO'):
        si = subprocess.STARTUPINFO()
        si.dwFlags |= subprocess.STARTF_USESHOWWINDOW
        si.wShowWindow = 0
    env = dict(os.environ, NESRECOMP_NO_LAUNCHER='1', SDL_VIDEODRIVER='dummy', SDL_AUDIODRIVER='dummy')
    with (out / 'window.log').open('w') as log:
        proc = subprocess.Popen([
            str(out / args.exe.name), str(args.rom.resolve()), '--tcp', str(port),
            '--config', str(config), '--hidden', '--no-save'],
            cwd=out, stdout=log, stderr=subprocess.STDOUT, env=env,
            startupinfo=si, creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0))
        try:
            deadline = time.monotonic()+60
            while True:
                try:
                    sock = socket.create_connection(('127.0.0.1', port), timeout=15)
                    break
                except OSError:
                    assert proc.poll() is None and time.monotonic() < deadline, (out/'window.log').read_text(errors='replace')
                    time.sleep(.05)
            with sock, sock.makefile('rwb', buffering=0) as stream:
                responses = []

                def ask(cmd, **fields):
                    stream.write((json.dumps(dict(cmd=cmd, id=len(responses)+1, **fields))+'\n').encode())
                    response = json.loads(stream.readline())
                    responses.append(response)
                    assert response.get('ok'), response
                    return response

                text = (out / 'window.log').read_text(errors='replace')
                assert args.activation in text and 'could not be prepared' not in text, 'Mod activation failed: '+text
                ask('menu', open=True)
                ask('load_state', path=str(args.state.resolve()))
                frame = ask('state')['frame']
                for n in range(3):
                    picture = out / f'restored-{n}.png'
                    ask('screenshot', path=str(picture))
                    assert picture.read_bytes() == args.picture.read_bytes(), 'Restored picture differs from the active headless capture'
                    assert ask('state')['frame'] == frame, 'Paused frame advanced'
                ask('save_state', path=str(out/'restored.cycstate'))
                ask('quit')
                assert proc.wait(timeout=10) == 0
                (out/'qa.json').write_text(json.dumps(responses, indent=2))
        finally:
            if proc.poll() is None:
                proc.terminate()
                proc.wait(timeout=10)
    print('Relocated Mod activation and restored paused picture pass', flush=True)


if __name__ == '__main__':
    main()
