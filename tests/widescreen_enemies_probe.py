"""Enemy residency regression route; all artifacts and saves stay in --out."""
import argparse,json
from pathlib import Path
from custom_widescreen_probe import Probe

def stats(p,name):
    data=p.cmd('smb_ws_enemies');data.pop('id',None)
    (p.out/(name+'.enemies.json')).write_text(json.dumps(data,indent=2))
    print(name,json.dumps(data),flush=True)
    return data

def run(args,mode):
    if args.mods:
        assert mode!='native','The native diagnostic policy is intentionally not a mod option'
        state=f'''format_version = 1
[[package]]
id = "super-mario-bros.enhancement.widescreen"
version = "1.0.0"
[[feature]]
package_id = "super-mario-bros.enhancement.widescreen"
id = "widescreen"
enabled = true
[feature.values]
aspect = "32-9"
enemy_activation = "{mode}"
'''
        p=Probe(args.exe,args.rom,Path(args.out)/mode,None,mods=args.mods,state=state)
    else:
        p=Probe(args.exe,args.rom,Path(args.out)/mode,'32:9',extra_args=['--widescreen-enemies',mode])
    try:
        p.advance(180);p.advance(2,0x10);p.advance(160)
        initial=stats(p,'initial');ram0=p.capture('initial')
        if mode!='native':
            assert initial['loaded']>0 and initial['sprites']>0,initial
            first=next(e for e in initial['enemies'] if e['spawn_x']==352)
            assert first['slot']==-1 and first['y']==184,first
            assert first['active']==(mode=='viewport'),first
        p.advance(100)
        idle=stats(p,'idle');p.capture('idle')
        if mode!='native':
            first=next(e for e in idle['enemies'] if e['spawn_x']==352)
            assert first['x']==352 if mode=='classic' else first['x']<340,first
            assert first['y']==184 and not first['dead'],first
        state=(p.out/'check.sav').as_posix();p.cmd('save_state',path=state)
        for phase in ('fresh','restored'):
            if phase=='restored':p.cmd('load_state',path=state)
            for frames,buttons in [(80,1),(80,0x81),(80,1),(80,0)]:p.advance(frames,buttons)
            data=stats(p,phase);capture=p.capture(phase)
            if phase=='fresh':expected=(data,capture,(p.out/'fresh.png').read_bytes())
            else:assert expected==(data,capture,(p.out/'restored.png').read_bytes())
        p.cmd('quit');assert p.proc.wait(timeout=10)==0
        log=(p.out/'runner.log').read_text(errors='replace')
        assert 'DISPATCH MISS' not in log and '=== WATCHDOG:' not in log
        return ram0,capture
    finally:p.close()

if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__)
    for name in ('exe','rom','out'):parser.add_argument('--'+name,required=True)
    parser.add_argument('--modes',nargs='+',default=['native','classic','viewport'])
    parser.add_argument('--mods',help='Use saved mod choices instead of CLI overrides; select classic/viewport modes')
    args=parser.parse_args();results={mode:run(args,mode) for mode in args.modes}
    if 'native' in results and 'classic' in results:assert results['native']==results['classic'],'Classic activation changed guest state on the opening route'
    print('PASS enemy visibility, activation policies, floor collision and save/load')
