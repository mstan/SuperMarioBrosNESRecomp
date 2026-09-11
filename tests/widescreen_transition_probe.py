"""Replay 1-1 completion through the 1-2 entrance; reject flags in other areas."""
import argparse,json
from pathlib import Path
from custom_widescreen_probe import Probe
from widescreen_boundaries_probe import fixture_for,ram

ap=argparse.ArgumentParser(description=__doc__)
for key in ('exe','rom','out','state'):ap.add_argument('--'+key,required=True)
ap.add_argument('--reset-actors',action='store_true');ap.add_argument('--before',action='store_true')
args=ap.parse_args();p=Probe(args.exe,args.rom,args.out,'32:9',extra_args=['--widescreen-enemies','viewport'])
rows=[];areas=set();underground=0
try:
    p.cmd('load_state',path=fixture_for(args,args.state,'f2').as_posix());p.advance(4)
    for i in range(232):
        buttons=(0x81 if ((i<18 and i%6<3) or 32<=i<36) else 1) if i<52 else 0
        p.advance(10,buttons)
        r=ram(p);flag=p.cmd('smb_ws_flag');area=r[0xe7]+r[0xe8]*256
        row=dict(frame=p.cmd('frame')['frame'],area=area,level=r[0x75c],type=r[0x74e],flag=flag)
        rows.append(row)
        if area not in areas:
            areas.add(area);p.capture(f'area_{area:04x}')
        if flag['world_x']<0 and flag['sprites']:
            if not (p.out/'ghost.png').exists():p.capture('ghost')
        if r[0x75c]==1 and r[0x74e]==2:
            underground+=1
            if underground>=20:break
    ghosts=[r for r in rows if r['flag']['world_x']<0 and r['flag']['sprites']]
    (p.out/'transitions.json').write_text(json.dumps(rows,indent=2))
    print(json.dumps(dict(areas=[hex(a) for a in areas],underground_samples=underground,ghost_samples=len(ghosts),first_ghost=ghosts[:1])),flush=True)
    assert underground>=20,'Route did not reach 1-2'
    if not args.before:assert not ghosts,'Flag survived into a different area'
    p.cmd('quit');assert p.proc.wait(timeout=10)==0
finally:p.close()
