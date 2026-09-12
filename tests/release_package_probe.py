"""Check clean Windows release ZIPs, real Mods activation and stock parity."""
import argparse,json,os,subprocess,tomllib,zipfile
from pathlib import Path
from PIL import Image

ap=argparse.ArgumentParser(description=__doc__)
for key in ('release','rom','out','baseline'):ap.add_argument('--'+key,required=True)
args=ap.parse_args();out=Path(args.out).resolve();out.mkdir(parents=True,exist_ok=False)
release=Path(args.release).resolve();rom=Path(args.rom).resolve()
script='WAIT 180\nHOLD START\nWAIT 2\nRELEASE START\nWAIT 300\nSCREENSHOT spawn.png\nHOLD RIGHT\nWAIT 120\nRELEASE RIGHT\nSCREENSHOT right.png\nWAIT 1200\n'
results={};images={};binaries=[]
for name,variant,extra in [('stock','',[]),('preset','-widescreen',[]),
                           ('explicit','',['--widescreen','16:9','--widescreen-enemies','viewport']),
                           ('override','-widescreen',['--widescreen','off'])]:
    directory=out/name;directory.mkdir()
    with zipfile.ZipFile(release/f'SuperMarioBrosRecomp{variant}-windows-x64.zip') as archive:
        names=archive.namelist()
        assert not any(n.endswith(('.nes','.sav','.srm')) or n=='debug.ini' or n=='widescreen.ini' for n in names)
        binaries.append(archive.read('SuperMarioBrosRecomp.exe'))
        archive.extractall(directory)
    catalog=directory/'mods/packages/super-mario-bros.enhancement.widescreen/1.0.0/manifest.toml'
    manifest=tomllib.loads(catalog.read_text())
    assert 'Experimental' in manifest['name'] and 'Experimental' in manifest['feature'][0]['name']
    assert manifest['feature'][0]['default_enabled'] is False
    camera=next(option for option in manifest['option'] if option['id']=='camera')
    assert camera['default']=='edges' and {c['value'] for c in camera['choice']}=={'edges','centered'}
    state=directory/'mods/state.toml'
    if variant:
        values=tomllib.loads(state.read_text())['feature'][0]
        assert values['enabled'] and values['values']==dict(aspect='16-9',hud='edges',enemy_activation='viewport',camera='edges')
    else:assert not state.exists()
    commands=script.replace('SCREENSHOT spawn.png',f'SCREENSHOT {(directory/"spawn.png").as_posix()}')
    commands=commands.replace('SCREENSHOT right.png',f'SCREENSHOT {(directory/"right.png").as_posix()}')
    (directory/'route.script').write_text(commands)
    env=dict(os.environ,NESRECOMP_NO_LAUNCHER='1')
    for key in ('NESRECOMP_START_PAUSED','NESRECOMP_COSIM_HASH','NESRECOMP_FALLBACK_LOG'):env.pop(key,None)
    with (directory/'runner.log').open('w') as log:
        subprocess.run([str(directory/'SuperMarioBrosRecomp.exe'),str(rom),'--smoke','1200',
                        '--smoke-interval','10','--smoke-output','smoke.json','--script','route.script',*extra],
                       cwd=directory,env=env,stdout=log,stderr=subprocess.STDOUT,check=True,timeout=60)
    results[name]=json.loads((directory/'smoke.json').read_text())
    assert results[name]['frames_run']==1200 and results[name]['dispatch_miss_count']==0
    images[name]=Image.open(directory/'right.png')
    assert images[name].width==256 if name in ('stock','override') else images[name].width>256
    assert 'TCP server listening' not in (directory/'runner.log').read_text(errors='replace')
    print('PASS packaged',name,'width',images[name].width,flush=True)
assert all(b==binaries[0] for b in binaries)
assert results['stock']['frame_hashes']==results['override']['frame_hashes']
assert results['stock']['frame_hashes']==json.loads(Path(args.baseline).read_text())['frame_hashes']
assert results['preset']['frame_hashes']==results['explicit']['frame_hashes']
assert images['preset'].tobytes()==images['explicit'].tobytes()
print('PASS release presets, experimental labels, no debug server, stock 120/120 frame hashes',flush=True)
