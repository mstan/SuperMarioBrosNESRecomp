"""Run existing co-op gameplay and campaign fixtures on the cycle backend.

The harness uses public headless input/save/load paths. WAIT_RAM8 observes
each saved frame in bounded batches, then continues at the first match.
Rejection tests also verify the running SDL machine over TCP separately.
"""
import argparse
import importlib
import json
import os
from pathlib import Path
import struct
import subprocess
import sys

import coop_runtime

BITS = dict(A=0x80, B=0x40, SELECT=0x20, START=0x10, UP=8, DOWN=4, LEFT=2, RIGHT=1)
NO_WINDOW = getattr(subprocess, 'CREATE_NO_WINDOW', 0)


class State:
    def __init__(self, path):
        self.data = bytearray(Path(path).read_bytes())
        assert self.data[:8] == b'CYCSTATE'
        self.chunks = {}
        pos = 32
        while pos < len(self.data):
            tag = bytes(self.data[pos:pos+4])
            length = struct.unpack_from('<I', self.data, pos+4)[0]
            start = pos+8
            assert start+length <= len(self.data)
            if tag == b'MOD ':
                key = bytes(self.data[start:start+64]).split(b'\0')[0]
                self.chunks[key] = (start+64, length-64)
            else:
                self.chunks[tag] = (start, length)
            pos = start+length
        self.mod = self.chunks[b'smb.coop'][0]
        assert self.data[self.mod:self.mod+5] == b'SMBC\2'
        # HwMachine ABI: u8 tick/align, aligned u64 cycles, bus fields, RAM.
        self.ram_start = self.chunks[b'HW  '][0] + 23
        assert self.chunks[b'HW  '][1] == 2072
        self.frame = struct.unpack_from('<I', self.data, 28)[0]

    def actor(self, player):
        start = self.mod+28+player*coop_runtime.STRIDE
        return memoryview(self.data)[start:start+coop_runtime.STRIDE]

    @property
    def ram(self):
        return memoryview(self.data)[self.ram_start:self.ram_start+2048]

    def write(self, path):
        Path(path).write_bytes(self.data)

    def x(self, player):
        actor = self.actor(player)
        return actor[0x6d]*256+actor[0x86]


class Harness:
    def __init__(self, exe, rom, out):
        self.exe = Path(exe).resolve()
        self.rom = Path(rom).resolve()
        self.out = Path(out).resolve()
        self.out.mkdir(parents=True, exist_ok=True)

    def run(self, name, body, players=4, fixture=None, shared=False, boot_script=None):
        held = [0]*4
        previous = None
        serial = 0
        log_parts = []
        options = ['--coop', str(players)] + (['--coop-pause', 'shared'] if shared else [])
        if os.environ.get('SMB_CYCLE_INTERP') == '1':
            options.append('--interp-only')

        def advance(count, observe=False):
            nonlocal previous, serial
            assert count > 0
            serial += 1
            stem = self.out/f'{name}-step{serial}'
            start = previous.frame if previous else 0
            route = stem.with_suffix('.input')
            route.write_text(''.join(f'{start} {p+1}:'+(' '.join(k for k,v in BITS.items() if value&v) or '-')+'\n' for p,value in enumerate(held)))
            command = [str(self.exe), str(self.rom), '--no-save', '--frames', str(start+count), '--input', str(route), *options]
            if previous:
                state_path = stem.with_suffix('.load.cycstate')
                previous.write(state_path)
                command += ['--load-state', str(state_path)]
            paths = []
            for frame in (range(start, start+count) if observe else [start+count-1]):
                path = Path(str(stem)+f'-{frame}.cycstate')
                command += ['--save-state', f'{frame}:{path}']
                paths.append(path)
            command += ['--present-out', str(self.out/f'{name}.png')]
            result = subprocess.run(command, cwd=self.out, env=dict(os.environ, NESRECOMP_NO_LAUNCHER='1'),
                                    capture_output=True, text=True, timeout=120, creationflags=NO_WINDOW)
            log_parts.append(result.stdout+result.stderr)
            (self.out/f'{name}.log').write_text(''.join(log_parts))
            assert result.returncode == 0, (name, result.returncode, result.stderr[-2000:])
            states = [State(path) for path in paths]
            previous = states[-1]
            return states

        if fixture:
            previous = fixture
            boot = 'WAIT 2\n'
        else:
            boot = 'WAIT 60\nHOLD START\nWAIT 6\nRELEASE START\nWAIT_RAM8 000E 08\nWAIT 30\n'
        if boot_script is not None:
            boot = boot_script
        # Keep the input timeline intact through consecutive WAIT statements.
        pending = 0
        for line in (boot+body).splitlines():
            fields = line.split()
            if not fields:
                continue
            command = fields[0]
            if command == 'WAIT':
                pending += int(fields[1])
                continue
            if pending:
                advance(pending)
                pending = 0
            if command in ('HOLD', 'RELEASE'):
                player = int(fields[2])-1 if len(fields)>2 else 0
                if command == 'HOLD': held[player] |= BITS[fields[1]]
                else: held[player] &= ~BITS[fields[1]]
            elif command == 'WAIT_RAM8':
                addr, value = int(fields[1],16), int(fields[2],16)
                for _ in range(120):
                    if previous and previous.ram[addr] == value:
                        break
                    candidates = advance(16, observe=True)
                    match = next((s for s in candidates if s.ram[addr] == value), None)
                    if match:
                        previous = match
                        break
                else:
                    raise AssertionError((name, line, 'timeout'))
            else:
                raise ValueError(f'{name}: unsupported cycle fixture command {line}')
        if pending:
            advance(pending)
        assert previous is not None
        previous.write(self.out/f'{name}.sav')
        return previous


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--exe', required=True)
    parser.add_argument('--rom', required=True)
    parser.add_argument('--out', default='build-cycle/coop-fixtures')
    parser.add_argument('--suite', choices=['rules', 'campaign'], default='rules')
    parser.add_argument('--level', default='all')
    args = parser.parse_args()
    coop_runtime.State = State
    coop_runtime.Harness = Harness
    module = importlib.import_module('coop_'+args.suite)
    sys.argv = [sys.argv[0], '--exe', args.exe, '--rom', args.rom, '--out', args.out]
    if args.suite == 'campaign':
        sys.argv += ['--level', args.level]
    module.main()


if __name__ == '__main__':
    main()
