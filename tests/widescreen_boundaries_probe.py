"""Focused visual regressions: streamed colors, complete enemies, owner F2 flag.

The enemy edge check deliberately positions one live enemy under frozen movement;
it tests rendering, not gameplay correctness. The optional F2 fixture can drop
the old experimental world and actor payloads while retaining its original machine state.
Owner save files are never edited.
"""
import argparse,json,struct
from pathlib import Path
from PIL import Image
from custom_widescreen_probe import Probe

def records(data):
    assert data[:5]==b'NSSR\x07'
    end=9+struct.unpack_from('<I',data,5)[0]
    count=struct.unpack_from('<H',data,end)[0];pos=end+2;items=[]
    for _ in range(count):
        tag=data[pos:pos+64];size=struct.unpack_from('<I',data,pos+64)[0]
        payload=data[pos+68:pos+68+size];items.append((tag,payload));pos+=68+size
    assert pos==len(data)
    return data[:end],items

def palette_errors(path):
    _,items=records(path.read_bytes())
    world=next(v for k,v in items if k.rstrip(b'\0')==b'super-mario-bros.widescreen.world')
    assert struct.unpack_from('<I',world)[0] in (2,3,4)
    pal=world[9+1024*26:9+2*1024*26]
    meta=world[9+2*1024*26:9+2*1024*26+512*13]
    return sum(pal[c*26+r]!=(meta[(c//2)*13+r//2]>>6) for c in range(1024) for r in range(26))

def poke(p,addr,val):p.cmd('write_ram',addr=f'{addr:04x}',val=f'{val&255:02x}')
def ram(p):return b''.join(bytes.fromhex(p.cmd('read_ram',addr=f'{a:04x}',len=256)['hex']) for a in range(0,0x800,256))
def fixture_for(args,source,name):
    fixture=Path(source).resolve()
    if args.reset_actors:
        base,items=records(fixture.read_bytes())
        items=[(k,v) for k,v in items if k.rstrip(b'\0') not in
               (b'super-mario-bros.widescreen.actors',b'super-mario-bros.widescreen.world')]
        fixture=(Path(args.out)/(name+'_machine.sav')).resolve()
        fixture.write_bytes(base+struct.pack('<H',len(items))+b''.join(k+struct.pack('<I',len(v))+v for k,v in items))
    return fixture

def colors(args):
    fixture=fixture_for(args,args.colors_state,'colors')
    p=Probe(args.exe,args.rom,Path(args.out)/'colors','32:9',extra_args=['--widescreen-enemies','native'])
    counts=[]
    try:
        p.cmd('load_state',path=fixture.as_posix())
        for i in range(120):
            p.advance(2,0x81 if (i//20)%2==0 else 1)
            state=p.out/'sample.sav';p.cmd('save_state',path=state.as_posix())
            counts.append(palette_errors(state))
            if counts[-1] and not any(counts[:-1]):p.capture('first_bad')
        (p.out/'errors.json').write_text(json.dumps(counts))
        print('colors',json.dumps(dict(samples=len(counts),bad_samples=sum(v>0 for v in counts),max_errors=max(counts))),flush=True)
        if not args.before:assert not any(counts),counts
        p.cmd('quit');assert p.proc.wait(timeout=10)==0
    finally:p.close()

def edges(args):
    p=Probe(args.exe,args.rom,Path(args.out)/'edges','32:9',extra_args=['--widescreen-enemies','viewport'])
    try:
        p.advance(180);p.advance(2,0x10);p.advance(160);p.advance(120,1);p.advance(40)
        state=p.out/'colors.sav';p.cmd('save_state',path=state.as_posix())
        bad_colors=palette_errors(state)
        data=p.cmd('smb_ws_enemies');a=next(e for e in data['enemies'] if e['slot']>=0 and e['kind']==6)
        slot=a['slot'];r=ram(p);cam=r[0x71a]*256+r[0x71c]
        assert cam>=8,(cam,data)
        images={}
        # Same graphics pose on both sides of the native left join.
        poses=[('center',192),('edge',-4),('outside',-20),('right_edge',252),('right_outside',268)]
        for name,offset in poses:
            for _ in range(4):
                poke(p,0x747,0xff);poke(p,9,0)
                poke(p,0x6e+slot,(cam+offset)>>8);poke(p,0x87+slot,cam+offset)
                p.advance(1)
            p.capture(name);images[name]=Image.open(p.out/(name+'.png')).convert('RGB')
        # Brown body pixels exclude sky, hills and black terrain outlines.
        ref=images['center'];x0=(ref.width-256)//2
        # SMB's Goomba palette in this ROM: determine body colors from the
        # center sprite itself, selecting brown pixels rather than background.
        pixels=[]
        for y in range(160,208):
            for x in range(16):
                color=ref.getpixel((x0+192+x,y));red,green,blue=color
                if red>green*1.15 and green>blue and red>80:pixels.append((x,y,color))
        assert len(pixels)>20,len(pixels)
        missing={name:sum(images[name].getpixel((x0+off+x,y))!=color for x,y,color in pixels)
                 for name,off in poses[1:]}
        result=dict(palette_errors=bad_colors,body_pixels=len(pixels),missing=missing)
        print('edges',json.dumps(result),flush=True)
        (p.out/'result.json').write_text(json.dumps(result,indent=2))
        if not args.before:assert bad_colors==0 and not any(missing.values()),result
        p.cmd('quit');assert p.proc.wait(timeout=10)==0
    finally:p.close()

def flag(args):
    fixture=fixture_for(args,args.state,'f2')
    p=Probe(args.exe,args.rom,Path(args.out)/'flag','32:9',extra_args=['--widescreen-enemies','viewport'])
    rows=[]
    try:
        p.cmd('load_state',path=fixture.as_posix());p.advance(4)
        p.capture('initial')
        if not args.before:
            row=p.cmd('smb_ws_flag');rows.append(row)
            assert row['sprites']>=3 and row['y']==49,row
            p.cmd('save_state',path=(p.out/'owner_f2_updated.sav').as_posix())
        for i in range(52):
            jump=(i<18 and i%6<3) or 32<=i<36
            p.advance(10,0x81 if jump else 1)
            if not args.before:rows.append(p.cmd('smb_ws_flag'))
            if i in (5,11,19,31,39,51):p.capture(f'step{i}')
        (p.out/'flag.json').write_text(json.dumps(rows,indent=2))
        if not args.before:
            assert any(r['native'] for r in rows),rows
            assert any(r['y']>60 for r in rows),rows
        print('flag',json.dumps(dict(frames=len(rows),native=any(r['native'] for r in rows),max_y=max((r['y'] for r in rows),default=-1))),flush=True)
        p.cmd('quit');assert p.proc.wait(timeout=10)==0
    finally:p.close()

if __name__=='__main__':
    ap=argparse.ArgumentParser(description=__doc__)
    for name in ('exe','rom','out'):ap.add_argument('--'+name,required=True)
    ap.add_argument('--before',action='store_true');ap.add_argument('--state')
    ap.add_argument('--colors-state')
    ap.add_argument('--reset-actors',action='store_true')
    args=ap.parse_args();Path(args.out).mkdir(parents=True,exist_ok=False)
    edges(args)
    if args.colors_state:colors(args)
    if args.state:flag(args)
