"""Serial native co-op fixtures: actual guest execution, saved actor/world state.

Run with --exe and --rom. Artifacts go to --out (default build-coop/acceptance).
Tests deliberately use the public script and savestate paths, without pausing
or injecting host-only substitutes for SMB physics/collision.
"""
from pathlib import Path
import argparse
import struct
import subprocess

STRIDE = 2218
RAM = 20  # V7 file header (9) + CPU register bytes (11)


class State:
    def __init__(self, path):
        self.data = bytearray(Path(path).read_bytes())
        assert self.data[:5] == b"NSSR\x07"
        self.mod = self.data.index(b"smb.coop\0") + 68
        assert self.data[self.mod:self.mod+5] == b"SMBC\2"

    def actor(self, player):
        start = self.mod + 28 + player * STRIDE
        return memoryview(self.data)[start:start+STRIDE]

    @property
    def ram(self):
        return memoryview(self.data)[RAM:RAM+2048]

    def write(self, path):
        Path(path).write_bytes(self.data)

    def x(self, player):
        a = self.actor(player)
        return a[0x6d]*256+a[0x86]


class Harness:
    def __init__(self, exe, rom, out):
        self.exe=Path(exe);self.rom=Path(rom);self.out=Path(out).resolve()
        self.out.mkdir(parents=True,exist_ok=True)

    def run(self, name, body, players=4, fixture=None, shared=False, boot_script=None):
        out=self.out;args=self
        save=out/f'{name}.sav';shot=out/f'{name}.png';script=out/f'{name}.script'
        boot='WAIT 60\nHOLD START\nWAIT 6\nRELEASE START\nWAIT_RAM8 000E 08\nWAIT 30\n'
        if fixture:
            path=out/f'{name}-fixture.sav';fixture.write(path)
            boot=f'WAIT 2\nLOAD_STATE {path.as_posix()}\nWAIT 2\n'
        if boot_script is not None: boot=boot_script
        script.write_text(boot+body+f'\nSAVE_STATE {save.as_posix()}\nSCREENSHOT {shot.as_posix()}\nWAIT 2\nEXIT 0\n')
        command=[str(args.exe.resolve()),str(args.rom.resolve()),'--coop',str(players),'--script',str(script),
                 '--smoke','1000000','--smoke-interval','1000000']
        if shared: command+=['--coop-pause','shared']
        try:
            result=subprocess.run(command,creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0), capture_output=True,text=True,timeout=60)
        except subprocess.TimeoutExpired as e:
            (out/f'{name}.log').write_bytes((e.stdout or b'')+(e.stderr or b''))
            raise
        (out/f'{name}.log').write_text(result.stdout+result.stderr)
        assert result.returncode==0,(name,result.returncode,result.stderr[-2000:])
        assert 'dispatch miss' not in (result.stdout+result.stderr).lower(), name
        assert 'ASSERT FAIL' not in result.stdout+result.stderr,name
        assert 'TIMEOUT' not in result.stdout+result.stderr,name
        return State(save)


def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--exe',required=True,type=Path)
    ap.add_argument('--rom',required=True,type=Path)
    ap.add_argument('--out',type=Path,default=Path('build-coop/acceptance'))
    args=ap.parse_args();out=args.out.resolve();out.mkdir(parents=True,exist_ok=True)
    run=Harness(args.exe,args.rom,out).run

    boot=run('boot','WAIT 1')
    assert boot.data[boot.mod+7]==1,'session did not initialize'
    assert [boot.x(p) for p in range(4)]==[40,32,24,16]
    roster=State(out/'boot.sav')
    for p in range(4):roster.actor(p)[0x86]=40+p*40
    run('roster','WAIT 1',fixture=roster)
    p4=run('p4','HOLD RIGHT 4\nHOLD A 4\nWAIT 30\nRELEASE RIGHT 4\nRELEASE A 4',fixture=boot)
    assert [p4.x(p) for p in range(3)]==[boot.x(p) for p in range(3)],'P4 moved another seat'
    assert p4.x(3)>boot.x(3) and p4.actor(3)[0xce]<boot.actor(3)[0xce]
    for n in (2,3):
        a=run(f'count-{n}','WAIT 1',players=n)
        assert a.data[a.mod+5]==n
    # All four overlapping a collectible: only P1 wins; flower makes small big.
    fixture=State(out/'boot.sav')
    for p in range(4): fixture.actor(p)[0x86]=40
    for addr,value in {0x14:1,0x1b:0x2e,0x23:0x80,0x73:0,0x8c:40,0xbB:1,0xd4:176,0x39:1}.items(): fixture.ram[addr]=value
    pickup=run('flower-contest','WAIT 8',fixture=fixture)
    assert [pickup.actor(p)[0x756] for p in range(4)]==[1,0,0,0],'pickup duplicated or small player gained fire'
    # One player drops below screen; others remain alive with no life spent.
    fixture=State(out/'boot.sav');fixture.actor(0)[0xb5]=2;fixture.actor(0)[0xce]=16
    death=run('p1-dead','WAIT 35',fixture=fixture)
    assert death.actor(0)[2048]==2
    assert all(death.actor(p)[2048]==0 for p in (1,2,3))
    assert death.ram[0x75a]==boot.ram[0x75a]
    # Full wipe costs one attempt and returns every actor small.
    fixture=State(out/'boot.sav')
    for p in range(4): fixture.actor(p)[0xb5]=2;fixture.actor(p)[0xce]=16
    retry=run('wipe-retry','WAIT 340',fixture=fixture)
    assert retry.ram[0x75a]==boot.ram[0x75a]-1,'wipe did not spend exactly one attempt'
    assert all(retry.actor(p)[2048]==0 and retry.actor(p)[0x756]==0 for p in range(4))
    print('PASS: native 2/3/4-player spawn, P4 isolation, contested flower, P1 death, team retry',flush=True)

    def press(button): return ''.join(f'HOLD {button} {p+1}\n' for p in range(4))
    def release(button): return ''.join(f'RELEASE {button} {p+1}\n' for p in range(4))
    fixture=State(out/'boot.sav')
    for p in range(4):
        fixture.actor(p)[0x756]=2;fixture.actor(p)[0x754]=0;fixture.actor(p)[0x86]=40
    fire=run('eight-fireballs',press('B')+'WAIT 3\n'+release('B')+'WAIT 3\n'+press('B')+'WAIT 3\n'+release('B')+'WAIT 2',fixture=fixture)
    assert all(fire.actor(p)[0x24] and fire.actor(p)[0x25] for p in range(4)), 'two fireballs per actor were not retained'
    assert all(fire.actor(p)[0x756]==2 and fire.actor(p)[2048]==0 for p in range(4)), 'allied fireball damaged actor'
    print('PASS: eight native fireballs, harmless allied projectiles',flush=True)

    fixture=State(out/'boot.sav');fixture.actor(0)[0x756]=1;fixture.actor(0)[0x0e]=9;fixture.actor(0)[2049]=255
    transform=run('private-transform','HOLD RIGHT 4\nWAIT 16',fixture=fixture)
    assert transform.x(0)==fixture.x(0) and transform.x(3)>fixture.x(3), 'transform froze the party'
    assert transform.actor(0)[0x754]==0,'native growth did not change size'
    fixture.data[fixture.mod+6]=1
    paused=run('shared-transform','HOLD RIGHT 4\nWAIT 16',fixture=fixture,shared=True)
    assert paused.x(3)==fixture.x(3), 'shared transform did not freeze teammate'
    assert paused.actor(0)[0x754]==0, 'shared pause stopped the transforming actor timer'
    print('PASS: individual/shared transformation pause',flush=True)

    fixture=State(out/'boot.sav')
    for p in range(4): fixture.actor(p)[0x79f]=255
    camera=run('camera-limit','HOLD RIGHT 4\nHOLD B 4\nWAIT 180',fixture=fixture)
    left=camera.ram[0x71a]*256+camera.ram[0x71c]
    assert left<=min(fixture.x(p) for p in range(3)), 'camera abandoned a living player'
    assert all(left<=camera.x(p)<=left+240 for p in range(4)), 'party escaped screen bounds'
    print('PASS: shared camera retains living party',flush=True)

    # Four overlapping riders: native right platform moves exactly once, and
    # each actor inherits its displacement and standing Y.
    fixture=State(out/'boot.sav')
    for p in range(4):
        fixture.actor(p)[0x86]=88;fixture.actor(p)[0xce]=128
    for addr,value in {0x0f:1,0x16:0x2a,0x1e:0,0x6e:0,0x87:80,0xb6:1,0xcf:160,0x58:16,0x49a:6}.items(): fixture.ram[addr]=value
    riders=run('four-platform-riders','WAIT 20',fixture=fixture)
    distance=riders.ram[0x6e]*256+riders.ram[0x87]-80
    assert 18<=distance<=24,('platform moved more than once per frame',distance)
    assert all(riders.x(p)==88+distance and riders.actor(p)[0xce]==128 for p in range(4)), 'platform failed to carry every rider'
    print('PASS: four platform riders, one platform update',flush=True)

    fixture=State(out/'boot.sav');fixture.ram[0x787]=0
    fixture.ram[0x7f8:0x7fb]=bytes(3)
    timeout=run('team-timeout','WAIT 5',fixture=fixture)
    assert all(timeout.actor(p)[2048]==2 for p in range(4)), 'timeout spared a teammate'
    assert timeout.ram[0x75a]==boot.ram[0x75a], 'timeout charged before wipe retry'
    print('PASS: shared timer expires the whole team',flush=True)

    for power in (0,1):
        fixture=State(out/'boot.sav');fixture.actor(3)[0x86]=80
        fixture.actor(3)[0x756]=power;fixture.actor(3)[0x754]=1-power
        fixture.actor(0)[0x756]=1-power;fixture.actor(0)[0x754]=power
        fixture.ram[0x575]=0xc1  # Native mushroom/flower question block at (80,144).
        block=run(f'hitter-power-{power}','HOLD A 4\nWAIT 18',fixture=fixture)
        assert block.ram[0x1b]==0x2e and block.ram[0x39]==power, 'item selected party power instead of hitter power'
    fixture=State(out/'boot.sav');fixture.actor(0)[0x86]=44;fixture.actor(1)[0x86]=80
    for addr,value in {0x0f:1,0x16:0,0x1e:4,0x6e:0,0x87:52,0xb6:1,0xcf:176,0x58:0,0x46:1,0x49a:3,0x796:20}.items(): fixture.ram[addr]=value
    shell=run('ally-shell','WAIT 25',fixture=fixture)
    assert shell.actor(0)[2048]==0 and shell.actor(1)[2048]!=0, 'kicked shell did not hurt teammate'
    print('PASS: hitter-selected scarce powerups and allied shell damage',flush=True)

    # P4 accepts a native down-pipe transition while P1 is out. The same pipe
    # touched with a lethal enemy must wait for death resolution and be denied.
    fixture=State(out/'boot.sav');fixture.actor(0)[2048]=2;fixture.actor(3)[0x86]=88
    fixture.ram[0x5b5]=0x10;fixture.ram[0x5b6]=0x11
    fixture.ram[0x750]=0xc2  # Native underground bonus-room destination.
    pipe=run('p4-pipe','HOLD DOWN 4\nWAIT 5',fixture=fixture)
    assert pipe.data[pipe.mod+10]==1 and pipe.data[pipe.mod+9]==3, 'P4 could not take pipe'
    room=run('pipe-no-revival','HOLD DOWN 4\nWAIT 230',fixture=fixture)
    assert room.data[room.mod+7]==1 and room.actor(0)[2048]==2, 'bonus room revived dead teammate'
    for addr,value in {0x0f:1,0x16:0x0d,0x1e:0,0x6e:0,0x87:88,0xb6:1,0xcf:176,0x58:0,0x49a:3}.items(): fixture.ram[addr]=value
    # Keep the stationary piranha at the pipe mouth on both collision parities.
    fixture.ram[0x78a]=255
    denied=run('lethal-before-pipe','HOLD DOWN 4\nWAIT 5',fixture=fixture)
    assert denied.data[denied.mod+10]==0 and denied.actor(3)[2048]!=0, 'lethal collision lost to pipe acceptance'
    print('PASS: P4 pipe entry, no bonus-room revival, lethal contact before exit',flush=True)

    # Restored private buttons/projectiles/timers must replay deterministically.
    body=press('RIGHT')+press('B')+'WAIT 12\n'+release('B')+'WAIT 6\n'+press('B')+'WAIT 8\n'
    replay1=run('replay-a',body,fixture=fire)
    replay2=run('replay-b',body,fixture=fire)
    assert replay1.data[replay1.mod:]==replay2.data[replay2.mod:], 'actor replay diverged'
    base=9+struct.unpack_from('<I',replay1.data,5)[0]
    assert replay1.data[:base]==replay2.data[:base], 'shared guest replay diverged'
    # Poison guest lives in each incompatible file. Preflight rejection must
    # leave the running game's lives intact, before any guest state is applied.
    rejects=[]
    for label,offset,value in [('count',5,3),('mode',5,0),('version',4,255),('active',9,4)]:
        bad=State(out/'boot.sav');bad.data[bad.mod+offset]=value;bad.ram[0x75a]=99
        path=out/f'reject-{label}.sav';bad.write(path);rejects.append(path)
    bad=State(out/'boot.sav');bad.actor(0)[2056]=255;bad.ram[0x75a]=99
    path=out/'reject-sprite-count.sav';bad.write(path);rejects.append(path)
    body=''.join(f'LOAD_STATE {path.as_posix()}\nWAIT 2\nASSERT_RAM8 075A 02 rejected-state-mutated-lives\n' for path in rejects)
    run('reject-incompatible',body,fixture=boot)
    log=(out/'reject-incompatible.log').read_text()
    assert log.count("load rejected before changing the game")==len(rejects), 'missing preflight rejection'
    off=run('reject-coop-while-off',f'LOAD_STATE {(out/"boot.sav").as_posix()}\nWAIT 3\nASSERT_RAM8 075A 02 mode-mismatch',players=0)
    assert off.data[off.mod+5]==0 and 'load rejected before changing the game' in (out/'reject-coop-while-off.log').read_text()
    run('title','WAIT 1',boot_script='WAIT 60\n')
    print('PASS: deterministic save replay, mode/count/corruption rejection before mutation',flush=True)


if __name__=='__main__': main()
