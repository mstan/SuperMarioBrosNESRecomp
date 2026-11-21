"""Native castle rewinds, presentation and current-build continuation.

Requires an original USA/World ROM and a cycle build. Position, speed and
collision protection bypass traversal; original scrolling/parser/maze handlers
still decide the rewind. This does not certify ordinary platforming/combat.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess

from PIL import Image, ImageChops
from coop_cycle_runtime import State


def observe(s):
    r=s.ram
    return dict(frame=s.frame,x=r[0x6d]*256+r[0x86],y=r[0xce]+(r[0xb5]-1)*256,
                camera=r[0x71a]*256+r[0x71c],engine=r[0xe],mode=r[0x770],task=r[0x772],
                page=r[0x725],column=r[0x726],offset=r[0x72c],loop=r[0x745])


class Probe:
    def __init__(self,args,world,wide,back):
        self.args=args;self.world=world;self.wide=wide
        self.out=args.out/f'{world}-4-wide{int(wide)}-back{int(back)}'
        self.out.mkdir()
        self.mods=self.out/'mods';shutil.copytree(args.mods,self.mods)
        (self.mods/'state.toml').write_text(
            'format_version=1\n[[package]]\nid="super-mario-bros.gameplay.free-backtracking"\n'
            'version="1.0.0"\n[[feature]]\npackage_id="super-mario-bros.gameplay.free-backtracking"\n'
            'id="backtracking"\nenabled='+str(back).lower()+'\n')
        self.env={k:v for k,v in os.environ.items() if not k.startswith(('NESRECOMP_','LNG_','SDL_'))}
        self.env.update(NESRECOMP_NO_LAUNCHER='1',NES_NETPLAY='0',LNG_TEST_HIDDEN='1',
                        SDL_VIDEODRIVER='dummy',SDL_AUDIODRIVER='dummy',SDL_RENDER_DRIVER='software')
        self.env['PATH']=str(args.exe.parent)+os.pathsep+self.env['PATH']
        for key in ['APPDATA','LOCALAPPDATA','TEMP','TMP','XDG_CONFIG_HOME','XDG_DATA_HOME','XDG_CACHE_HOME']:
            folder=self.out/key.lower();folder.mkdir();self.env[key]=str(folder)

    def run(self,label,state,count,events,step=None):
        start=State(state).frame if state else 0
        route=self.out/(label+'.input')
        route.write_text(''.join(f'{start+n} {keys}\n' for n,keys in events))
        points=list(range(start,start+count,step)) if step else [start+count-1]
        if points[-1]!=start+count-1:points.append(start+count-1)
        files=[self.out/(label+f'-{n}.state') for n in points]
        argv=[str(self.args.exe),str(self.args.rom),'--headless','--no-save',
              '--mods-root',str(self.mods),'--widescreen','16:9' if self.wide else 'off',
              '--input',str(route),'--frames',str(start+count),
              '--present-out',str(self.out/(label+'.png')),
              '--screenshot',str(self.out/(label+'-native.png'))]
        if state:argv+=['--load-state',str(state)]
        for n,path in zip(points,files):argv+=['--save-state',f'{n}:{path}']
        with (self.out/(label+'.log')).open('wb') as log:
            p=subprocess.run(argv,cwd=self.out,env=self.env,stdin=subprocess.DEVNULL,
                             stdout=log,stderr=subprocess.STDOUT,
                             creationflags=getattr(subprocess,'CREATE_NO_WINDOW',0))
        text=(self.out/(label+'.log')).read_text(errors='replace')
        assert p.returncode==0,(label,p.returncode,text[-2000:])
        for owned in ['super-mario-bros.backtracking','super-mario-bros.widescreen.world']:
            assert f"mod '{owned}' did not take its state" not in text,(label,owned)
        return files[-1],files,[observe(State(path)) for path in files]

    def case(self):
        boot,_,_=self.run('boot',None,360,[(0,'-'),(90,'START'),(96,'-')])
        s=State(boot);assert s.ram[0xe]==8
        pointer,area={4:(0x61,4),7:(0x64,4),8:(0x65,3)}[self.world]
        for address,value in {0x750:pointer,0x75f:self.world-1,0x75c:3,0x760:area,
                              0x75b:0,0x752:0,0x772:0}.items():s.ram[address]=value
        seed=self.out/'native-loader-prerequisite.state';s.write(seed)
        _,files,values=self.run('native-loader',seed,256,[(0,'-')],8)
        current=next(p for p,v in zip(files,values) if v['task']==3 and v['engine']==8)
        rows=[];rewound=False
        for n in range(150):
            s=State(current);before=observe(s);x=(before['camera']+128)&65535
            # No camera, parser, maze counters or outcome fields are assigned.
            changes={0x6d:x>>8,0x86:x&255,0xce:176 if self.world==4 else 192,0xb5:1,
                     0x57:40,0x400:0,0x9f:0,0x433:0,0x1d:0,0x79e:0,0x79f:255,
                     0x716:1,0x490:255,0x785:0}
            for address,value in changes.items():s.ram[address]=value
            seed=self.out/'traversal-prerequisite.state';s.write(seed)
            label=f'wrong-path-{n}'
            current,_,values=self.run(label,seed,4,[(0,'RIGHT B')]);rows+=values
            if ((values[-1]['camera']-before['camera'])&65535)>32767:
                rewound=True;break
        assert rewound,('No native maze rewind in finite route',self.world,rows[-1])
        picture=Image.open(self.out/(label+'.png')).convert('RGB')
        native=Image.open(self.out/(label+'-native.png')).convert('RGB')
        origin=0 if self.world==4 or not self.wide else (picture.width-256)//2
        assert picture.size==(426 if self.wide else 256,240)
        assert ImageChops.difference(native.crop((0,32,256,240)),
                                    picture.crop((origin,32,origin+256,240))).getbbox() is None, 'Native maze picture changed or was clipped'
        assert observe(State(current))['offset']=={4:0x12,7:0x0e,8:0x0a}[self.world]
        s=State(current)
        for address,value in {0x716:0,0x79f:0,0x57:0}.items():s.ram[address]=value
        seed=self.out/'native-collision-restored.state';s.write(seed)
        endpoints=[]
        for repeat in range(2):
            path,_,_=self.run(f'current40-{repeat}',seed,40,[(0,'-')]);endpoints.append(path)
        assert endpoints[0].read_bytes()==endpoints[1].read_bytes()
        assert (self.out/'current40-0.png').read_bytes()==(self.out/'current40-1.png').read_bytes()
        return dict(world=self.world,wide=self.wide,loop=rows[-1],nativePictureExact=True,
                    wholeCurrent40Exact=True,observations=rows)


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    for key in ['exe','rom','out']:ap.add_argument('--'+key,required=True,type=Path)
    ap.add_argument('--mods',type=Path,default=Path(__file__).resolve().parents[1]/'mods/preloaded')
    ap.add_argument('--worlds',nargs='+',type=int,choices=[4,7,8],default=[4,7,8])
    args=ap.parse_args()
    for key in ['exe','rom','out','mods']:setattr(args,key,getattr(args,key).resolve())
    assert hashlib.sha256(args.rom.read_bytes()).hexdigest()=='f61548fdf1670cffefcc4f0b7bdcdd9eaba0c226e3b74f8666071496988248de'
    args.out.mkdir(parents=True,exist_ok=False)
    result={'binarySha256':hashlib.sha256(args.exe.read_bytes()).hexdigest(),'cases':[]}
    for world in args.worlds:
        for wide,back in [(False,False),(False,True),(True,True)]:
            row=Probe(args,world,wide,back).case();result['cases'].append(row)
            (args.out/'result.json').write_text(json.dumps(result,indent=2)+'\n')
            print('PASS',world,'wide',wide,'backtracking',back,flush=True)


if __name__=='__main__':main()
