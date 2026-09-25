"""Compare mod-off gameplay to pristine game + engine commits, not a mock."""
import argparse
from pathlib import Path
import struct
import subprocess


def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--stock',required=True,type=Path)
    ap.add_argument('--candidate',required=True,type=Path)
    ap.add_argument('--rom',required=True,type=Path)
    ap.add_argument('--out',type=Path,default=Path('build-coop/stock-comparison'))
    a=ap.parse_args();out=a.out.resolve();out.mkdir(parents=True,exist_ok=True)
    for name,exe in [('stock',a.stock),('candidate',a.candidate)]:
        target=out/name;target.mkdir(exist_ok=True)
        def snap(label):
            return f'SAVE_STATE {(target/(label+".sav")).as_posix()}\nSCREENSHOT {(target/(label+".png")).as_posix()}\nWAIT 2\n'
        body='WAIT 60\n'+snap('title')+'HOLD SELECT\nWAIT 5\nRELEASE SELECT\nWAIT 10\n'+snap('two-player-menu')
        body+='HOLD START\nWAIT 6\nRELEASE START\nWAIT_RAM8 000E 08\nWAIT 30\n'+snap('spawn')
        body+='HOLD RIGHT\nWAIT 26\nHOLD A\nWAIT 26\nRELEASE A\nWAIT 50\nRELEASE RIGHT\nWAIT 20\n'+snap('motion')
        body+='WRITE_RAM8 00B5 06\nWAIT 430\n'+snap('turn-change')+'EXIT 0\n'
        script=target/'stock.script';script.write_text(body)
        r=subprocess.run([str(exe.resolve()),str(a.rom.resolve()),'--script',str(script),'--smoke','1000000','--smoke-interval','1000000'],creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0), capture_output=True,text=True,timeout=70)
        (target/'run.log').write_text(r.stdout+r.stderr)
        assert r.returncode==0,(name,r.returncode)
        assert 'dispatch miss' not in (r.stdout+r.stderr).lower(),name
    for label in ['title','two-player-menu','spawn','motion','turn-change']:
        stock=(out/'stock'/f'{label}.sav').read_bytes()
        candidate=(out/'candidate'/f'{label}.sav').read_bytes()
        size=9+struct.unpack_from('<I',stock,5)[0]
        assert stock[:size]==candidate[:size],(label,'CPU/RAM/PPU/mapper/APU/runtime mismatch',
            [(n,x,y) for n,(x,y) in enumerate(zip(stock[:size],candidate[:size])) if x!=y][:15])
        assert (out/'stock'/f'{label}.png').read_bytes()==(out/'candidate'/f'{label}.png').read_bytes(),(label,'render mismatch')
    print('PASS: mod-off CPU/RAM/PPU/APU/runtime and images match pristine commits across title, 2P menu, spawn, movement and turn change')


if __name__=='__main__': main()
