"""One real halfway crossing/revisit/pit-death contract; no result flags."""
from pathlib import Path
import argparse,hashlib,json,os,shutil,struct,subprocess,sys
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--exe',type=Path,required=True)
parser.add_argument('--rom',type=Path,required=True)
parser.add_argument('--state',type=Path,required=True,help='Current-build USA World1-1 gameplay snapshot; no ROM or state is bundled')
parser.add_argument('--out',type=Path,required=True,help='New disposable output directory')
parser.add_argument('--mods',type=Path,default=Path(__file__).resolve().parents[1]/'mods/preloaded')
args=parser.parse_args();S=Path(__file__).resolve().parents[1];sys.path.insert(0,str(S/'tests'));from coop_cycle_runtime import State
R=args.out.resolve();R.mkdir(parents=True,exist_ok=False);exe=args.exe.resolve();rom=args.rom.resolve();args.state=args.state.resolve()
assert hashlib.sha256(rom.read_bytes()).hexdigest()=='f61548fdf1670cffefcc4f0b7bdcdd9eaba0c226e3b74f8666071496988248de','Only the supported USA profile is qualified'
assert rom.read_bytes()[16+0x1206:16+0x1209]==bytes.fromhex('cd1a07'),'Native midpoint operand changed'
env={k:v for k,v in os.environ.items()if not k.startswith(('NESRECOMP_','LNG_','SDL_'))};env.update(NESRECOMP_NO_LAUNCHER='1',SDL_AUDIODRIVER='dummy',SDL_VIDEODRIVER='dummy',SDL_RENDER_DRIVER='software')
for k in ['APPDATA','LOCALAPPDATA','TEMP','TMP']:
 p=R/k.lower();p.mkdir();env[k]=str(p)
report=dict(binary=dict(path=str(exe),sha256=hashlib.sha256(exe.read_bytes()).hexdigest()),scope='Native InitializeArea entrance page4 is a traversal bypass. After loader clears HalfwayPage, player position1200 and contact protection are setup only. Ordinary controller input crosses real native page5 threshold, returns left, falls in an actual pit, loses a life and retries; no checkpoint/result/death/terrain flags assigned.',cases={})
def save():(R/'result.json').write_text(json.dumps(report,indent=2)+'\n')
def obs(s):
 r=s.ram;at=s.chunks.get(b'super-mario-bros.backtracking');return dict(frame=s.frame,x=r[0x6d]*256+r[0x86],camera=r[0x71a]*256+r[0x71c],y=r[0xce]+(r[0xb5]-1)*256,engine=r[0xe],task=r[0x772],halfway=r[0x75b],lives=r[0x75a],coin=r[0x75e],scroll_lock=r[0x723],high_water=struct.unpack_from('<i',s.data,at[0]+4)[0]if at else None)
for mode in ['on','off']:
 out=R/mode;out.mkdir();mods=out/'mods';shutil.copytree(args.mods,mods);(mods/'state.toml').write_text('format_version=1\n[[package]]\nid="super-mario-bros.gameplay.free-backtracking"\nversion="1.0.0"\n[[feature]]\npackage_id="super-mario-bros.gameplay.free-backtracking"\nid="backtracking"\nenabled='+('true'if mode=='on'else'false')+'\n')
 row=dict(legs=[]);report['cases'][mode]=row;serial=0
 def run(label,path,count,events,step=None):
  global serial
  serial+=1;s=State(path);start=s.frame;stop=start+count;root=out/(str(serial)+'-'+label);root.mkdir();route=root/'input.txt';route.write_text(''.join(f'{start+n} {v}\n'for n,v in events));points=list(range(start,stop,step))if step else[]
  if stop-1 not in points:points.append(stop-1)
  files=[root/(str(n)+'.state')for n in points];a=[str(exe),str(rom),'--headless','--no-save','--mods-root',str(mods),'--widescreen','16:9','--load-state',str(path),'--input',str(route),'--frames',str(stop),'--present-out',str(root/'last.png')]
  for n,p in zip(points,files):a+=['--save-state',str(n)+':'+str(p.relative_to(out))]
  with(root/'run.log').open('wb')as log:r=subprocess.run(a,cwd=out,env=env,stdin=subprocess.DEVNULL,stdout=log,stderr=subprocess.STDOUT,timeout=120,creationflags=getattr(subprocess,'CREATE_NO_WINDOW',0)|getattr(subprocess,'BELOW_NORMAL_PRIORITY_CLASS',0))
  assert r.returncode==0,(root/'run.log').read_text(errors='replace')[-3000:];samples=[obs(State(p))for p in files];row['legs'].append(dict(label=label,input_first=start,input_last=stop-1,completed_frame=stop,files=list(map(str,files)),samples=samples));save();print(mode,label,samples[-1],flush=True);return files[-1],files,samples
 source=State(args.state)
 for a,v in [(0x750,0x25),(0x75b,4),(0x752,0),(0x772,0)]:source.ram[a]=v
 path=out/'loader-prerequisite.state';source.write(path);path,files,samples=run('native-loader',path,192,[(0,'B')],4);ready=next((p for p in files if State(p).ram[0x772]==3 and State(p).ram[0xe]==8),None);assert ready,'No native first control';s=State(ready);assert s.ram[0x75b]==0 and obs(s)['camera']==1024,obs(s)
 row['native_first_control']=obs(s)
 for a,v in {0x6d:4,0x86:176,0xce:176,0xb5:1,0x57:0,0x400:0,0x9f:0,0x433:0,0x1d:0,0x79e:255}.items():s.ram[a]=v
 path=out/'before-threshold-position-prerequisite.state';s.write(path);row['before_threshold']=obs(s);assert obs(s)['x']==1200 and obs(s)['camera']<1280
 for n in range(12):
  if obs(State(path))['x']>=1320:break
  path,_,_=run('approach-pit'+str(n),path,8,[(0,'RIGHT B')])
 assert 1320<=obs(State(path))['x']<1376,obs(State(path))
 path,_,_=run('cross-pit-right',path,65,[(0,'RIGHT B A'),(25,'RIGHT B')]);s=State(path);assert s.ram[0xe]==8 and s.ram[0xb5]==1 and obs(s)['camera']>=1280,obs(s);row['ordinary_threshold_crossed']=obs(s)
 # Turn on actual terrain to the right of the native gap at columns86..88.
 for n in range(14):
  if obs(State(path))['x']<=1450:break
  path,_,_=run('return-to-pit'+str(n),path,8,[(0,'LEFT B')])
 if mode=='on':
  assert 1424<obs(State(path))['x']<=1450,obs(State(path))
  path,_,_=run('cross-pit-left',path,65,[(0,'LEFT B A'),(25,'LEFT B')]);s=State(path);assert s.ram[0xb5]==1 and not s.ram[0x723]and obs(s)['camera']<1280,obs(s);row['ordinary_left_revisit']=obs(s);direction='LEFT B'
 else:
  s=State(path);assert obs(s)['camera']>=1280,obs(s);row['stock_left_clamp']=obs(s);direction='RIGHT B'
 before=State(path);path,files,samples=run('actual-pit-death-and-retry',path,820,[(0,direction),(480,'B')],4);native=[(p,r)for p,r in zip(files,samples)if r['lives']==before.ram[0x75a]-1 and r['engine']==8 and r['task']==3]
 assert native,'No genuine life-loss/retry';ready,after=native[0];row['first_retry']=after;assert after['camera']==1280 and after['halfway']==0 and after['x']>=1280 and after['x']<1400,after;assert any(x['halfway']==5 for x in samples),'No native midpoint choice';assert after['coin']==before.ram[0x75e];row['passed']=True;save()
report['passed']=True;save();print('PASS actual ordinary threshold/revisit/pit death/native retry plus stock Off control',flush=True)
