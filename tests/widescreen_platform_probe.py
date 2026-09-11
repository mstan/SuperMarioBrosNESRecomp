"""Replay the owner's 1-2 lift setup; preserve original save files."""
import argparse,ctypes,json,struct
from pathlib import Path
from PIL import Image
from custom_widescreen_probe import Probe
from widescreen_boundaries_probe import records,ram,poke

def fixture(args,p):
    source=Path(args.state).resolve()
    if not args.upgrade_fixture:return source
    # Test-only v3 -> v4 fixture conversion. The fixed arrays/layout are
    # unchanged; append the newly managed authored records while preserving
    # every old resident and slot owner. Runtime has no legacy save loader.
    class Actor(ctypes.LittleEndianStructure):
        _fields_=[('x',ctypes.c_uint16)]+[(n,ctypes.c_uint8) for n in
                  ('offset','member','y','kind','loaded','active','dead')]+[
                  ('slot',ctypes.c_int16),('state',ctypes.c_uint8*26)]
    class Header(ctypes.LittleEndianStructure):
        _fields_=[('version',ctypes.c_uint32),('area',ctypes.c_uint16),
                  ('enemy',ctypes.c_uint16),('count',ctypes.c_uint16),
                  ('world',ctypes.c_uint8),('owner',ctypes.c_int16*5),('actors',Actor*384)]
    base,items=records(source.read_bytes());result=[];rom=Path(args.rom).read_bytes()
    for tag,payload in items:
        if tag.rstrip(b'\0')==b'super-mario-bros.widescreen.actors':
            payload=bytearray(payload);header=Header.from_buffer(payload)
            assert header.version==3 and ctypes.sizeof(Actor)==38 and Header.actors.offset==22
            page=selected=offset=0
            while offset<255:
                b0,b1=rom[header.enemy-0x8000+16+offset:header.enemy-0x8000+18+offset]
                if b0==255:break
                row=b0&15
                if b1&128 and not selected:page+=1;selected=1
                if row==15 and not selected:page=b1&63;selected=1;offset+=2;continue
                kind=b1&63
                if row<14 and 0x25<=kind<=0x2c:
                    a=header.actors[header.count];header.count+=1
                    a.x=page*256+(b0&240);a.y=row*16;a.offset=offset;a.kind=kind;a.slot=-1
                offset+=3 if row==14 else 2;selected=0
            header.version=4;payload=bytes(payload)
        result.append((tag,payload))
    target=p.out/'fixture_v4.sav'
    target.write_bytes(base+struct.pack('<H',len(result))+b''.join(t+struct.pack('<I',len(v))+v for t,v in result))
    return target

def snapshot(p):
    r=ram(p)
    return dict(camera=r[0x71a]*256+r[0x71c],player_x=r[0x6d]*256+r[0x86],
                player_y=r[0xce],timer=r[0x747],
                native=[dict(slot=s,kind=r[0x16+s],flag=r[0xf+s],
                             x=r[0x6e+s]*256+r[0x87+s],y=r[0xcf+s],
                             speed=r[0xa0+s],force=r[0x434+s],fraction=r[0x417+s],
                             collision=r[0x3a2+s]) for s in range(5)],
                host=p.cmd('smb_ws_enemies'))

ap=argparse.ArgumentParser(description=__doc__)
for key in ('exe','rom','out','state'):ap.add_argument('--'+key,required=True)
ap.add_argument('--upgrade-fixture',action='store_true')
ap.add_argument('--before',action='store_true')
ap.add_argument('--mode',default='viewport')
ap.add_argument('--baseline-route')
ap.add_argument('--preload-only',action='store_true')
ap.add_argument('--ride-only',action='store_true')
args=ap.parse_args()
p=Probe(args.exe,args.rom,args.out,'32:9',extra_args=['--widescreen-enemies',args.mode])
try:
    source=fixture(args,p);p.cmd('load_state',path=source.as_posix())
    if args.preload_only:
        # Controlled loading boundary: no native platforms yet, with their
        # authored records beyond native activation but within the wide view.
        # Preserve other residents and the original level data in the fixture.
        r=ram(p)
        for slot in range(5):
            if 0x25<=r[0x16+slot]<=0x2c:poke(p,0xf+slot,0)
        cam=1940
        for addr,value in [(0x71a,cam>>8),(0x71c,cam),(0x71b,(cam+255)>>8),
                           (0x71d,cam+255),(0x73f,cam),(0x778,(r[0x778]&~1)|((cam>>8)&1)),(0x723,1)]:poke(p,addr,value)
        p.advance(4);before=snapshot(p);p.capture('preload')
        lifts=lambda row:[a for a in row['host']['enemies'] if 0x25<=a['kind']<=0x2c and not a['dead']]
        a=lifts(before)
        assert before['camera']==cam and len(a)==4,before
        assert all(e['slot']==-1 and e['x']>cam+256 for e in a),a
        assert sum(e['sprites'] for e in a)>=12,a
        assert all(e['active']==(args.mode=='viewport') for e in a),a
        p.advance(64);after=snapshot(p);b=lifts(after);p.capture('preload_later')
        assert [e['y'] for e in a]!=[e['y'] for e in b] if args.mode=='viewport' else [e['y'] for e in a]==[e['y'] for e in b]
        (p.out/'preload.json').write_text(json.dumps(dict(before=before,after=after),indent=2))
        print('PASS',args.mode,'four lifts load beyond native activation; policy respected',flush=True)
        p.cmd('quit');assert p.proc.wait(timeout=10)==0
        raise SystemExit(0)
    p.advance(4)
    p.capture('initial');p.cmd('save_state',path=(p.out/'initial.sav').as_posix())
    initial=snapshot(p)
    if args.ride_only:
        lift=next(a for a in initial['native'] if a['flag'] and a['kind']==0x26 and 80<a['y']<180)
        x=lift['x']+8
        for addr,value in [(0x6d,x>>8),(0x86,x),(0xce,lift['y']-32),(0xb5,1),
                           (0x1d,0),(0x57,0),(0x9f,0),(0x433,0),(0x723,1)]:poke(p,addr,value)
        ride=[]
        for i in range(30):
            p.advance(1);row=snapshot(p);platform=row['native'][lift['slot']]
            ride.append(dict(player_x=row['player_x'],player_y=row['player_y'],platform=platform))
            assert row['player_y']==platform['y']-32 and platform['collision']<5,ride[-1]
        (p.out/'ride.json').write_text(json.dumps(ride,indent=2));p.capture('riding')
        if args.baseline_route:assert ride==json.loads(Path(args.baseline_route).read_text())
        print('PASS Mario rides ascending lift for 30 frames',flush=True)
        p.cmd('quit');assert p.proc.wait(timeout=10)==0
        raise SystemExit(0)
    rows=[]
    for i in range(60):
        p.advance(6);rows.append(snapshot(p))
        if i in (9,29,59):p.capture(f'idle{i}')
    (p.out/'route.json').write_text(json.dumps(rows,indent=2))
    if args.baseline_route:
        baseline=json.loads(Path(args.baseline_route).read_text())
        for old,new in zip(baseline,rows,strict=True):
            expected=sorted((a['kind'],a['x'],a['y']) for a in old['native'] if a['flag'] and 0x25<=a['kind']<=0x2c)
            actual=sorted((a['kind'],a['x'],a['y']) for a in new['host']['enemies'] if not a['dead'] and 0x25<=a['kind']<=0x2c)
            assert actual==expected,(expected,actual)
        print('PASS 360-frame lift positions match original native movement',flush=True)
    # Freeze one platform to isolate sprite clipping from its movement. Reload
    # the same checkpoint for each pose, including fully outside native edges.
    state=(p.out/'initial.sav').as_posix();images={}
    slot=next(a['slot'] for a in initial['native'] if a['flag'] and a['kind']==0x27)
    cam=initial['camera'];poses=[('center',96),('left_edge',-22),('left_outside',-56),('right_edge',238),('right_outside',280)]
    for name,off in poses:
        p.cmd('load_state',path=state)
        for addr,value in [(0x747,255),(0x6e+slot,(cam+off)>>8),(0x87+slot,cam+off),(0xcf+slot,80)]:poke(p,addr,value)
        p.advance(4);p.capture(name);images[name]=Image.open(p.out/(name+'.png')).convert('RGB')
    ref=images['center'];x0=(ref.width-256)//2
    pixels=[(x,y,ref.getpixel((x0+96+x,81+y))) for y in range(8) for x in range(48)
            if ref.getpixel((x0+96+x,81+y))!=(0,0,0)]
    assert len(pixels)>100,len(pixels)
    missing={name:sum(images[name].getpixel((x0+off+x,81+y))!=c for x,y,c in pixels) for name,off in poses[1:]}
    (p.out/'edges.json').write_text(json.dumps(dict(body_pixels=len(pixels),missing=missing),indent=2))
    print('platform pixels',json.dumps(missing),flush=True)
    if not args.before:assert not any(missing.values()),missing
    p.cmd('load_state',path=state);p.advance(40)
    saved=(p.out/'replay.sav').as_posix();p.cmd('save_state',path=saved)
    p.advance(60);expected=p.capture('fresh');actors=p.cmd('smb_ws_enemies');actors.pop('id',None)
    p.cmd('load_state',path=saved);p.advance(60)
    actual=p.capture('restored');other=p.cmd('smb_ws_enemies');other.pop('id',None)
    assert actual==expected and actors==other
    assert (p.out/'fresh.png').read_bytes()==(p.out/'restored.png').read_bytes()
    p.cmd('quit');assert p.proc.wait(timeout=10)==0
finally:p.close()
