"""Compare cached terrain with native background at both scrolling joins."""
import argparse
import json
from pathlib import Path
from custom_widescreen_probe import Probe

parser=argparse.ArgumentParser(description=__doc__)
for key in ('exe','rom','out'):parser.add_argument('--'+key,required=True)
parser.add_argument('--mode',default='native')
parser.add_argument('--require-aligned',action='store_true')
args=parser.parse_args()
p=Probe(args.exe,args.rom,args.out,'32:9',extra_args=['--widescreen-enemies',args.mode])
rows=[]
try:
    p.advance(180);p.advance(2,0x10);p.advance(300)
    for buttons in (1,0x81,1):
        for _ in range(80):
            p.advance(1,buttons)
            row=p.cmd('smb_ws_seam');row.pop('id',None);rows.append(row)
    p.capture('end')
    p.cmd('quit');assert p.proc.wait(timeout=10)==0
finally:p.close()
(Path(args.out)/'seams.json').write_text(json.dumps(rows,indent=2))
moving=[r for r in rows if r['render_camera']>0 and r['samples']]
wrong=[r for r in moving if r['offset_errors'][4]>min(r['offset_errors'])]
print(json.dumps(dict(frames=len(rows),scrolling=len(moving),misaligned=len(wrong),examples=wrong[:4])),flush=True)
if args.require_aligned:assert not wrong,'A shifted cache fits the native background better than the rendered alignment'
