"""Measure real Play-to-game startup, including Windows PowerShell redirection.

Requires a trace-enabled build. Uses real video/audio and a hidden SDL window.
Settings and logs live in an isolated copy; the owner's running game is untouched.
"""
import argparse
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import socket
import threading
import time


def ps_quote(value):
    return "'" + str(value).replace("'", "''") + "'"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--exe', required=True, type=Path)
    ap.add_argument('--rom', required=True, type=Path)
    ap.add_argument('--out', required=True, type=Path)
    ap.add_argument('--powershell', action='store_true')
    ap.add_argument('--settings-from', type=Path)
    ap.add_argument('--max-startup-ms', type=float)
    a = ap.parse_args()
    out = a.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    (out / 'title.png').unlink(missing_ok=True)
    source = a.exe.resolve().parent
    exe = out / a.exe.name
    shutil.copy2(a.exe, exe)
    for dll in source.glob('*.dll'):
        shutil.copy2(dll, out / dll.name)
    for folder in ('assets', 'mods/packages'):
        shutil.copytree(source / folder, out / folder, dirs_exist_ok=True)
    settings = a.settings_from.resolve() if a.settings_from else source
    for config in ('config.ini', 'keybinds.ini', 'mods/state.toml'):
        if (settings / config).exists():
            shutil.copy2(settings / config, out / config)
    (out / 'rom.cfg').write_text(str(a.rom.resolve()) + '\n')
    # A runner --script forces headless mode, so drive the real game via TCP.
    with socket.socket() as reservation:
        reservation.bind(('127.0.0.1', 0))
        port = reservation.getsockname()[1]
    stdout = out / 'stdout.log'
    stderr = out / 'stderr.log'
    command = [str(exe), '--launcher']
    env = dict(os.environ, NESRECOMP_BOOT_TIMING='1', LNG_BOOT_TIMING='1',
               NESRECOMP_DEBUG='1', NESRECOMP_DEBUG_PORT=str(port),
               NESRECOMP_TEST_HIDDEN='1', LNG_TEST_HIDDEN='1',
               LNG_SCRIPT='size:1100x880;wait:20;click:970,819;wait:500;quit')
    env.pop('NESRECOMP_NO_LAUNCHER', None)
    env.pop('NES_NETPLAY', None)
    flags = getattr(subprocess, 'CREATE_NO_WINDOW', 0)
    monitor_errors = []
    stop = threading.Event()

    def observe_game():
        try:
            deadline = time.monotonic() + 75
            while time.monotonic() < deadline:
                try:
                    connection = socket.create_connection(('127.0.0.1', port), timeout=0.2)
                    break
                except OSError:
                    if stop.wait(0.1):
                        return
            else:
                raise AssertionError('Game debug server did not start')
            with connection:
                connection.settimeout(30)
                reader = connection.makefile('rb')
                sequence = 0

                def request(cmd, **fields):
                    nonlocal sequence
                    sequence += 1
                    connection.sendall((json.dumps(dict(id=sequence, cmd=cmd, **fields)) + '\n').encode())
                    while True:
                        row = reader.readline()
                        assert row, 'Game disconnected'
                        response = json.loads(row)
                        if response.get('id') == sequence:
                            assert response.get('ok'), response
                            return response

                # Prove real frames are running after video/audio initialization.
                while time.monotonic() < deadline:
                    if request('frame')['frame'] >= 90:
                        break
                    if stop.wait(0.1):
                        return
                else:
                    raise AssertionError('Game never reached the title')
                request('pause')
                request('screenshot', path=(out / 'title.png').as_posix())
                request('quit')
        except Exception as exc:
            monitor_errors.append(repr(exc))

    monitor = threading.Thread(target=observe_game, daemon=True)
    monitor.start()
    started = time.perf_counter()
    if a.powershell:
        assert os.name == 'nt', 'PowerShell redirection check requires Windows'
        ps = Path(os.environ['SystemRoot']) / 'System32/WindowsPowerShell/v1.0/powershell.exe'
        # Start-Process uses a different pipe reader from Python's Popen. This
        # is the launch method that exposed character-at-a-time stdout stalls.
        launcher = out / 'launch.ps1'
        launcher.write_text(
            '$ErrorActionPreference = "Stop"\n'
            f'$p = Start-Process -FilePath {ps_quote(exe)} '
            f'-ArgumentList {ps_quote(subprocess.list2cmdline(command[1:]))} '
            f'-WorkingDirectory {ps_quote(out)} -WindowStyle Hidden '
            f'-RedirectStandardOutput {ps_quote(stdout)} '
            f'-RedirectStandardError {ps_quote(stderr)} -PassThru\n'
            'if (!$p.WaitForExit(75000)) { $p.Kill(); $p.WaitForExit(); exit 124 }\n'
            '$p.WaitForExit()\n'
            'exit $p.ExitCode\n')
        result = subprocess.run([str(ps), '-NoProfile', '-NonInteractive', '-File', str(launcher)],
                                env=env, capture_output=True, text=True,
                                creationflags=flags, timeout=90)
    else:
        with stdout.open('wb') as sout, stderr.open('wb') as serr:
            result = subprocess.run(command, cwd=out, env=env, stdout=sout, stderr=serr,
                                    creationflags=flags, timeout=90)
    elapsed = time.perf_counter() - started
    stop.set()
    monitor.join(timeout=2)
    assert not monitor_errors, monitor_errors
    log = stderr.read_text(errors='replace')
    assert result.returncode == 0, (result.returncode, log)
    phases = {phase: float(ms) for ms, phase in re.findall(r'\[startup\]\s+([0-9.]+) ms\s+(\w+)', log)}
    assert all(phase in phases for phase in ('audio_opened', 'renderer_created', 'first_frame_presented')), log
    assert '[Runner] Starting main game loop' in stdout.read_text(errors='replace')
    assert (out / 'title.png').stat().st_size > 1000, 'Title capture missing'
    summary = dict(method='powershell' if a.powershell else 'direct', elapsed_s=round(elapsed, 3), phases_ms=phases)
    (out / 'timings.json').write_text(json.dumps(summary, indent=2) + '\n')
    print(json.dumps(summary, indent=2), flush=True)
    if a.max_startup_ms is not None:
        assert phases['first_frame_presented'] < a.max_startup_ms, 'Slow startup regression'
    print('PASS: real hidden launcher, Play, first game frame, title capture, and clean exit')


if __name__ == '__main__':
    main()