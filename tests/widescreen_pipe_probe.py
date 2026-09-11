"""Replay the owner's underground pipe setup without modifying their saves."""
import argparse,ctypes,json
from pathlib import Path
from custom_widescreen_probe import Probe
from widescreen_boundaries_probe import records,ram,poke,fixture_for

class World(ctypes.LittleEndianStructure):
    _fields_=[('version',ctypes.c_uint32),('area',ctypes.c_uint16),('kind',ctypes.c_uint8),
              ('world',ctypes.c_uint8),('valid',ctypes.c_uint8),
              ('tiles',ctypes.c_uint8*(1024*26)),('palettes',ctypes.c_uint8*(1024*26)),
              ('meta',ctypes.c_uint8*(512*13)),('collision',ctypes.c_uint8*(512*13)),
              ('block_world',ctypes.c_int16*32)]

ap=argparse.ArgumentParser(description=__doc__)
for key in ('exe','rom','out','state'):ap.add_argument('--'+key,required=True)
ap.add_argument('--restart-area',action='store_true')
ap.add_argument('--reset-actors',action='store_true')
ap.add_argument('--mode',default='viewport')
ap.add_argument('--require-fixed',action='store_true')
args=ap.parse_args();p=Probe(args.exe,args.rom,args.out,'32:9',extra_args=['--widescreen-enemies',args.mode])
rows=[];inside=[];plant_seen=False
try:
    p.cmd('load_state',path=fixture_for(args,args.state,'f5').as_posix())
    if args.restart_area:
        # A fresh 1-2 checkpoint before the pipes, using native InitializeArea.
        # F5's old group has already spawned inside a pipe; replay fresh loading
        # rather than claiming a spawn fix can undo that saved game state.
        for addr,val in [(0x750,0xc0),(0x75b,5),(0x752,0),(0x772,0)]:poke(p,addr,val)
        p.advance(180)
    else:p.advance(4)
    for i in range(61):
        if i:
            # Keep this collision/visibility replay alive without freezing
            # enemies. The checkpoint saved at step0 has no such override.
            if args.require_fixed:poke(p,0x79e,0xff)
            p.advance(10,1 if i<31 else 0)
        data=p.cmd('smb_ws_enemies');data.pop('id',None)
        r=ram(p);data['frame']=p.cmd('frame')['frame'];data['player_x']=r[0x6d]*256+r[0x86]
        data['flag']=p.cmd('smb_ws_flag')
        data['native_slots']=[dict(slot=s,flag=r[0xf+s],kind=r[0x16+s],x=r[0x6e+s]*256+r[0x87+s],y=r[0xcf+s],
                                   direction=r[0x46+s],speed=r[0x58+s],state=r[0x1e+s]) for s in range(6)]
        rows.append(data)
        for enemy in data['enemies']:
            if enemy['dead']:continue
            if enemy['kind']==6 and any(lo<=enemy['x']+8<hi for lo,hi in ((1648,1680),(1744,1776),(1840,1872))):
                inside.append(dict(frame=data['frame'],enemy=enemy))
            if enemy['kind']==13 and enemy['spawn_x']==1752 and enemy['x']>data['camera']+256 and enemy['y']<=120 and enemy['sprites']:
                if not plant_seen:p.capture('plant_wide')
                plant_seen=True
        if i in (0,10,30,60):
            p.capture(f'step{i}')
            state=p.out/f'step{i}.sav';p.cmd('save_state',path=state.as_posix())
            _,items=records(state.read_bytes());payload=next(v for k,v in items if k.rstrip(b'\0')==b'super-mario-bros.widescreen.world')
            world=World.from_buffer_copy(payload)
            cols=range(max(0,(data['camera']-300)//16),min(512,(data['camera']+560)//16))
            collision={c:dict(meta=list(world.meta[c*13:(c+1)*13]),collision=list(world.collision[c*13:(c+1)*13])) for c in cols}
            (p.out/f'step{i}.collision.json').write_text(json.dumps(collision,indent=2))
    (p.out/'route.json').write_text(json.dumps(rows,indent=2))
    print(json.dumps(dict(plant_visible_outside_native=plant_seen,goomba_inside_pipe_samples=len(inside))),flush=True)
    if args.require_fixed:
        assert plant_seen,'Middle plant was never visible beyond the native boundary'
        assert not inside,inside[:3]
        assert not any(row['flag']['sprites'] for row in rows),'Flag remained in underground area'
        assert all(r['native_slots'][2]['x']!=1656 for r in rows if r['native_slots'][2]['kind']==6), 'Old embedded group member returned'
        state=p.out/'replay.sav';p.cmd('save_state',path=state.as_posix())
        p.advance(30);expected=p.capture('fresh');enemies=p.cmd('smb_ws_enemies');enemies.pop('id',None)
        p.cmd('load_state',path=state.as_posix());p.advance(30)
        actual=p.capture('restored');restored=p.cmd('smb_ws_enemies');restored.pop('id',None)
        assert actual==expected and enemies==restored
        assert (p.out/'fresh.png').read_bytes()==(p.out/'restored.png').read_bytes()
    print(json.dumps(dict(initial={k:rows[0][k] for k in ('camera','authored','loaded','flag','native_slots')},
                          end={k:rows[-1][k] for k in ('camera','authored','loaded','flag','native_slots')})),flush=True)
    p.cmd('quit');assert p.proc.wait(timeout=10)==0
finally:p.close()
