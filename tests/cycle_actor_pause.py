#!/usr/bin/env python3
"""Exercise detached cycle actors through the original Start pause path.

Uses the supported headless input/save/load interface and the existing MOD
snapshot chunks. Supply a matching local USA ROM; all output is task-local.
"""
import argparse
import json
import os
from pathlib import Path
import shutil
import struct
import subprocess


class Snapshot:
    def __init__(self, path):
        self.data = Path(path).read_bytes()
        assert self.data[:8] == b'CYCSTATE'
        self.frame = struct.unpack_from('<I', self.data, 28)[0]
        self.chunks = {}
        pos = 32
        while pos < len(self.data):
            tag = self.data[pos:pos+4]
            size = struct.unpack_from('<I', self.data, pos+4)[0]
            start, end = pos+8, pos+8+size
            assert end <= len(self.data)
            if tag == b'MOD ':
                key = self.data[start:start+64].split(b'\0')[0]
                self.chunks[key] = self.data[start+64:end]
            else:
                self.chunks[tag] = self.data[start:end]
            pos = end
        hw = self.chunks[b'HW  ']
        assert len(hw) == 2072, 'Update this build-specific HW layout'
        self.ram = hw[23:23+2048]
        self.residents = self.chunks[b'super-mario-bros.widescreen.actors']
        assert struct.unpack_from('<I', self.residents)[0] == 4

    def first_goomba(self):
        # Actor v4 has no pointers: a 22-byte prefix, then 38-byte records.
        count = struct.unpack_from('<H', self.residents, 8)[0]
        assert count <= 384 and len(self.residents) >= 22+count*38
        for i in range(count):
            spawn, offset, member, sy, kind, loaded, active, dead, slot, state = struct.unpack_from('<H7Bxh26s', self.residents, 22+i*38)
            if spawn == 352 and kind == 6 and member == 0:
                # Movement, fractions and timers must freeze during guest pause.
                motion = [state[n] for n in (3,4,5,6,7,8,9,11,12,13,17,18)]
                # Actor v4 stores 384 records followed by 40-byte packets.
                packet = self.residents[22+384*38+i*40:22+384*38+(i+1)*40]
                return dict(spawn_x=spawn, x=state[5]*256+state[6], y=state[9]+(state[8]-1)*256,
                            loaded=loaded, active=active, dead=dead, slot=slot, motion=motion,
                            displayed_sprites=packet[0], packet=list(packet))
        raise AssertionError('Authored opening Goomba was not found')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('exe', 'rom', 'mods', 'out'):
        parser.add_argument('--'+name, type=Path, required=True)
    parser.add_argument('--interp-only', action='store_true')
    args = parser.parse_args()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    mods = out/'mods'
    shutil.copytree(args.mods.resolve(), mods, dirs_exist_ok=True)
    schedule = out/'pause.input'
    schedule.write_text('120 START\n122 -\n360 START\n362 -\n420 START\n422 -\n')
    env = {k:v for k,v in os.environ.items() if not k.startswith(('NESRECOMP_', 'LNG_', 'SDL_'))}
    env.update(SDL_VIDEODRIVER='dummy', SDL_AUDIODRIVER='dummy', NESRECOMP_NO_LAUNCHER='1',
               NESRECOMP_DIAGNOSTICS_DIR=str(out/'diagnostics'), NESRECOMP_REPLAY_DIR=str(out/'recordings'))
    base = [str(args.exe.resolve()), str(args.rom.resolve()), '--no-save', '--headless',
            '--mods-root', str(mods), '--widescreen', '16:9', '--widescreen-enemies', 'viewport',
            '--input', str(schedule), '--frames', '480']
    if args.interp_only:
        base.append('--interp-only')

    def run(name, extra):
        with (out/(name+'.log')).open('wb') as log:
            result = subprocess.run(base+extra, cwd=out, env=env, stdout=log, stderr=subprocess.STDOUT,
                                    creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0), timeout=120)
        assert result.returncode == 0, (out/(name+'.log')).read_text(errors='replace')[-2500:]

    run('continuous', ['--save-state', '389:'+str(out/'paused-a.state'), '--save-state', '409:'+str(out/'paused-b.state'),
                       '--save-state', '479:'+str(out/'end.state'), '--hash-out', str(out/'continuous.hash'),
                       '--screenshot', str(out/'continuous.png'), '--present-out', str(out/'continuous-present.png')])
    a, b, end = [Snapshot(out/name) for name in ('paused-a.state', 'paused-b.state', 'end.state')]
    poses = dict(paused_a=a.first_goomba(), paused_b=b.first_goomba(), resumed=end.first_goomba(),
                 pause_flags=[a.ram[0x776], b.ram[0x776], end.ram[0x776]], frames=[a.frame,b.frame,end.frame])
    (out/'observations.json').write_text(json.dumps(poses, indent=2))
    assert a.frame == 390 and b.frame == 410 and end.frame == 480
    assert a.ram[0x776]&1 and b.ram[0x776]&1 and not end.ram[0x776]&1, poses
    assert poses['paused_a']['loaded'] and poses['paused_a']['active'] and not poses['paused_a']['dead'] and poses['paused_a']['slot'] == -1, poses
    assert poses['paused_a']['motion'] == poses['paused_b']['motion'] and poses['paused_b']['slot'] == -1, 'Detached actor advanced while the game was paused: '+json.dumps(poses)
    assert poses['paused_a']['displayed_sprites'] > 0 and poses['paused_a']['packet'] == poses['paused_b']['packet'], 'Paused detached actor lost its displayed packet: '+json.dumps(poses)
    assert poses['resumed']['x'] < poses['paused_b']['x'], 'Detached actor did not resume: '+json.dumps(poses)
    run('restored', ['--load-state', str(out/'paused-a.state'), '--save-state', '479:'+str(out/'restored.state'),
                     '--hash-out', str(out/'restored.hash'), '--screenshot', str(out/'restored.png'),
                     '--present-out', str(out/'restored-present.png')])
    full = {line.split()[0]:line for line in (out/'continuous.hash').read_bytes().splitlines()}
    resumed = (out/'restored.hash').read_bytes().splitlines()
    assert len(resumed) == 90 and all(full[line.split()[0]] == line for line in resumed)
    assert Snapshot(out/'restored.state').residents == end.residents
    assert (out/'continuous.png').read_bytes() == (out/'restored.png').read_bytes()
    assert (out/'continuous-present.png').read_bytes() == (out/'restored-present.png').read_bytes()
    (out/'result.json').write_text(json.dumps(dict(passed=False, observations=poses, continuation_frames=90, native_margin_pending=True), indent=2))
    # At this later ordinary cadence the same Goomba owns a native slot but
    # remains in the extended right margin. Paused OAM cannot draw that margin.
    schedule.write_text('120 START\n122 -\n420 START\n422 -\n480 START\n482 -\n')
    run('native-margin', ['--frames', '540', '--save-state', '449:'+str(out/'native-paused-a.state'),
                          '--save-state', '469:'+str(out/'native-paused-b.state'),
                          '--save-state', '539:'+str(out/'native-end.state'),
                          '--hash-out', str(out/'native-margin.hash'),
                          '--screenshot', str(out/'native-margin-native.png'),
                          '--present-out', str(out/'native-margin.png')])
    na, nb, ne = [Snapshot(out/name) for name in ('native-paused-a.state', 'native-paused-b.state', 'native-end.state')]
    native = dict(paused_a=na.first_goomba(), paused_b=nb.first_goomba(), resumed=ne.first_goomba())
    assert na.ram[0x776]&1 and nb.ram[0x776]&1 and not ne.ram[0x776]&1
    assert native['paused_a']['slot'] >= 0 and 256 <= native['paused_a']['x'] <= 304, native
    assert native['paused_a']['displayed_sprites'] > 0, native
    assert native['paused_a']['packet'] == native['paused_b']['packet'], native
    assert native['paused_a']['motion'] == native['paused_b']['motion'], native
    assert native['resumed']['x'] < native['paused_b']['x'], native
    result = json.loads((out/'result.json').read_text())
    run('native-restored', ['--frames', '540', '--load-state', str(out/'native-paused-a.state'),
                            '--save-state', '539:'+str(out/'native-restored.state'),
                            '--hash-out', str(out/'native-restored.hash'),
                            '--screenshot', str(out/'native-restored-native.png'),
                            '--present-out', str(out/'native-restored.png')])
    reference = {line.split()[0]:line for line in (out/'native-margin.hash').read_bytes().splitlines()}
    resumed = (out/'native-restored.hash').read_bytes().splitlines()
    assert len(resumed) == 90 and all(reference[line.split()[0]] == line for line in resumed)
    assert Snapshot(out/'native-restored.state').residents == ne.residents
    assert (out/'native-restored-native.png').read_bytes() == (out/'native-margin-native.png').read_bytes()
    assert (out/'native-restored.png').read_bytes() == (out/'native-margin.png').read_bytes()
    result['passed'] = True
    result.pop('native_margin_pending', None)
    result['native_margin'] = native
    result['native_continuation_frames'] = 90
    (out/'result.json').write_text(json.dumps(result, indent=2))
    print('PASS: detached/native-margin packets pause and resume; current-build continuation')


if __name__ == '__main__':
    main()
