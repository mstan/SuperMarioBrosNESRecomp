"""Native stomp/coin outcomes, ordinary revisit persistence and stock-Off clamp."""
from pathlib import Path
import argparse,hashlib,json,os,shutil,struct,subprocess,sys
parser=argparse.ArgumentParser(description='Actual native stomp, coin, ordinary right-left revisit and stock-Off clamp regression')
parser.add_argument('--exe',type=Path,required=True)
parser.add_argument('--rom',type=Path,required=True)
parser.add_argument('--state',type=Path,required=True,help='Current USA1-1 gameplay state: first Goomba alive and unused coin block x256, with camera32..240')
parser.add_argument('--out',type=Path,required=True)
parser.add_argument('--mods',type=Path,default=Path(__file__).resolve().parents[1]/'mods/preloaded')
parser.add_argument('--enemy-policy',choices=['native','classic','viewport'],default='native')
args=parser.parse_args();S=Path(__file__).resolve().parents[1];sys.path.insert(0,str(S/'tests'));from coop_cycle_runtime import State
R=args.out.resolve();R.mkdir(parents=True,exist_ok=False);app=R/'app';app.mkdir();exe=args.exe.resolve();rom=args.rom.resolve();args.state=args.state.resolve()
assert hashlib.sha256(rom.read_bytes()).hexdigest()=='f61548fdf1670cffefcc4f0b7bdcdd9eaba0c226e3b74f8666071496988248de'
shutil.copy2(exe,app/'SuperMarioBrosRecomp.exe')
if (exe.parent/'SDL2.dll').is_file():shutil.copy2(exe.parent/'SDL2.dll',app/'SDL2.dll')
if (exe.parent/'assets').is_dir():shutil.copytree(exe.parent/'assets',app/'assets')
shutil.copytree(args.mods,app/'mods');mods=R/'headless-mods';shutil.copytree(args.mods,mods)
env={k:v for k,v in os.environ.items()if not k.startswith(('NESRECOMP_','LNG_','SDL_'))};env.update(PATH=str(exe.parent)+os.pathsep+os.environ['PATH'],SDL_AUDIODRIVER='dummy',SDL_VIDEODRIVER='dummy',SDL_RENDER_DRIVER='software',NESRECOMP_NO_LAUNCHER='1',LNG_TEST_HIDDEN='1',SDL_GAMECONTROLLER_IGNORE_DEVICES_EXCEPT='0xfeed/0xbeef')
for k in ['APPDATA','LOCALAPPDATA','TEMP','TMP','TMPDIR','XDG_CONFIG_HOME','XDG_DATA_HOME','XDG_CACHE_HOME']:
 p=R/k.lower();p.mkdir();env[k]=str(p)
report=dict(binary=dict(path=str(exe),sha256=hashlib.sha256(exe.read_bytes()).hexdigest()),scope='Current-build fixture and player/contact-protection positions are prerequisites; normal native gravity/stomp and jump collision produce actual enemy retirement/score and used coin block. Ordinary right-left controls revisit both. No block, collision, coin, enemy or score outputs are assigned.')
def save():(R/'result.json').write_text(json.dumps(report,indent=2)+'\n')
def payload(s,key):a,n=s.chunks[key];return bytes(s.data[a:a+n])
def status(s):
 w=payload(s,b'super-mario-bros.widescreen.world');a=payload(s,b'super-mario-bros.widescreen.actors');meta=9+2*1024*26;col,row=16,7;actors=[];count=struct.unpack_from('<H',a,8)[0]
 for n in range(count):
  at=22+n*38
  if a[at+2]==3 and a[at+3]==0 and a[at+5]==6 and struct.unpack_from('<H',a,at)[0]==352:actors.append(dict(loaded=a[at+6],active=a[at+7],dead=a[at+8],state=list(a[at+12:at+38])))
 assert len(actors)==1
 return dict(frame=s.frame,coin=s.ram[0x75e],player_score=list(s.ram[0x7dd:0x7e3]),block_collision=w[meta+512*13+col*13+row],block_tiles=[w[9+(col*2+x)*26+row*2+y]for y in range(2)for x in range(2)],enemy=actors[0])
def run(label,state,count,route):
 start=State(state).frame;stop=start+count;out=R/(label+'.state');picture=R/(label+'.png');native=R/(label+'-native.png');hashes=R/(label+'.hash');argv=[str(app/'SuperMarioBrosRecomp.exe'),str(rom),'--headless','--no-save','--mods-root',str(mods),'--widescreen','16:9','--widescreen-enemies',args.enemy_policy,'--load-state',str(state),'--input',str(route),'--frames',str(stop),'--save-state',str(stop-1)+':'+str(out),'--present-out',str(picture),'--screenshot',str(native),'--hash-out',str(hashes)]
 with(R/(label+'.log')).open('wb')as log:r=subprocess.run(argv,cwd=R,env=env,stdin=subprocess.DEVNULL,stdout=log,stderr=subprocess.STDOUT,timeout=90,creationflags=getattr(subprocess,'CREATE_NO_WINDOW',0)|getattr(subprocess,'BELOW_NORMAL_PRIORITY_CLASS',0))
 assert r.returncode==0;st=State(out);assert st.frame==stop and st.ram[0xe]==8;return out,dict(state=str(out),picture=str(picture),native=str(native),hashes=str(hashes),input_first=start,input_last=stop-1,completed_frame=stop,status=status(st))
def pos(s):return s.ram[0x6d]*256+s.ram[0x86]
def cam(s):return s.ram[0x71a]*256+s.ram[0x71c]
own_before=args.state;s=State(args.state);before=status(s);assert before['coin']==0 and before['block_collision']==0xc0 and 32<=cam(s)<=240;enemy=before['enemy']['state'];enemy_x=enemy[5]*256+enemy[6];assert enemy[0]and not before['enemy']['dead']
# Position above the actual current native actor; allow normal gravity/stomp
# collision to perform retirement/score. No actor/result output is changed.
changes={0x6d:enemy_x>>8,0x86:enemy_x&255,0xce:120,0xb5:1,0x57:0,0x400:0,0x9f:0,0x433:0,0x1d:2,0x79e:255}
for a,v in changes.items():s.ram[a]=v
path=R/'above-live-native-goomba-prerequisite.state';s.write(path);route=R/'fall.input';route.write_text(str(s.frame)+' B\n');path,row=run('actual-native-stomp',path,60,route);assert row['status']['enemy']['dead']and row['status']['player_score']!=before['player_score'];report['actual_stomp_after_position_prerequisite']=dict(changes={hex(a):v for a,v in changes.items()},before=before,after=row);save()
s=State(path);assert cam(s)+16<=256<=cam(s)+224
changes={0x6d:1,0x86:0,0xce:176,0xb5:1,0x57:0,0x400:0,0x9f:0,0x433:0,0x1d:0,0x79e:255}
for a,v in changes.items():s.ram[a]=v
prepared=R/'below-coin-prerequisite.state';s.write(prepared);route=R/'coin.input';route.write_text(f'{s.frame} A\n{s.frame+20} B\n');path,row=run('actual-coin',prepared,60,route);changed=row['status'];assert changed['enemy']['dead']and changed['coin']==1 and changed['block_collision']==0xc4;report['actual_coin']=row;save()
serial=0
def move(label,path,direction):
 global serial
 serial+=1;s=State(path);s.ram[0x79e]=255;prepared=R/(label+'-protection.state');s.write(prepared);start=s.frame;route=R/(label+'.input');route.write_text(''.join(f'{start+n} {direction} B A\n{start+n+25} {direction} B\n'for n in [0,40]if n<60));return run(label,prepared,60,route)[0]
for n in range(10):
 if pos(State(path))>=900:break
 path=move('right'+str(n),path,'RIGHT')
s=State(path);assert 900<=pos(s)<1100 and cam(s)>600,(pos(s),cam(s));far=path;report['ordinary_right']=dict(state=str(path),x=pos(s),camera=cam(s),status=status(s));save()
for n in range(12):
 if cam(State(path))<=224:break
 path=move('left'+str(n),path,'LEFT')
s=State(path);assert cam(s)<=224 and pos(s)<400,(pos(s),cam(s));end=status(s);assert end['enemy']['dead']and end['coin']==1 and end['block_collision']==0xc4 and end['block_tiles']==changed['block_tiles'];report['native_selection_ordinary_revisit']=dict(state=str(path),x=pos(s),camera=cam(s),status=end);save()
# Same native diagnostic selection with Backtracking OFF keeps stock camera.
(mods/'state.toml').write_text('format_version=1\n[[package]]\nid="super-mario-bros.gameplay.free-backtracking"\nversion="1.0.0"\n[[feature]]\npackage_id="super-mario-bros.gameplay.free-backtracking"\nid="backtracking"\nenabled=false\n')
s=State(far);start=s.frame;route=R/'off-left.input';route.write_text(''.join(f'{start+n} LEFT B A\n{start+n+25} LEFT B\n'for n in range(0,240,40)));path,row=run('off-left',far,241,route);after=State(path);assert cam(after)>=cam(s)and pos(after)>=cam(s),(pos(after),cam(after),cam(s));report['native_selection_off_stock_clamp']=dict(initial_camera=cam(s),x=pos(after),camera=cam(after),state=str(path));report['passed']=True;save();print('PASS Native effective Classic actual defeat/coin/right-left revisit; Off stock clamp',flush=True)
