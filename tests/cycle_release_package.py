"""Focused cycle release check: both archives boot from a clean extraction."""
import argparse, hashlib, json, os, pathlib, subprocess, zipfile

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    for key in ('release','rom','out'):parser.add_argument('--'+key,required=True,type=pathlib.Path)
    args=parser.parse_args();out=args.out.resolve();out.mkdir(parents=True,exist_ok=False)
    startup=None
    if os.name=='nt':
        startup=subprocess.STARTUPINFO();startup.dwFlags|=subprocess.STARTF_USESHOWWINDOW;startup.wShowWindow=0
    records=[]
    for variant in ('stock','widescreen'):
        folder=out/variant;folder.mkdir()
        suffix='-widescreen' if variant=='widescreen' else ''
        with zipfile.ZipFile(args.release/f'SuperMarioBrosRecomp{suffix}-windows-x64.zip') as archive:
            assert {'SuperMarioBrosRecomp.exe','SDL2.dll','falcon_owner_assets.exe','smb_hdpack_importer.exe'}<=set(archive.namelist())
            assert not any(name.endswith(('.nes','.sav','.srm','.cycstate')) or name.endswith('debug.ini') for name in archive.namelist())
            archive.extractall(folder)
        schedule=folder/'route.txt';schedule.write_text('0 -\n90 START\n96 -\n240 RIGHT+B\n')
        command=[str(folder/'SuperMarioBrosRecomp.exe'),str(args.rom.resolve()),'--headless','--frames','360','--input',str(schedule),
                 '--mods-root',str(folder/'mods'),'--no-save','--screenshot',str(folder/'native.png'),'--present-out',str(folder/'picture.png')]
        env=dict(os.environ,NESRECOMP_NO_LAUNCHER='1',NES_NETPLAY='0')
        with (folder/'run.log').open('w') as log:
            subprocess.run(command,cwd=folder,env=env,stdout=log,stderr=subprocess.STDOUT,check=True,timeout=25,
                           startupinfo=startup,creationflags=getattr(subprocess,'CREATE_NO_WINDOW',0))
        from PIL import Image
        image=Image.open(folder/'picture.png');assert image.size==(256 if variant=='stock' else 426,240),image.size
        text=(folder/'run.log').read_text(errors='replace');assert '0 content mismatches' in text and '0 failed' in text,text[-1000:]
        records.append(dict(variant=variant,picture=list(image.size),exe_sha256=hashlib.sha256((folder/'SuperMarioBrosRecomp.exe').read_bytes()).hexdigest()))
    assert records[0]['exe_sha256']==records[1]['exe_sha256']
    (out/'result.json').write_text(json.dumps(records,indent=2));print(json.dumps(records,indent=2))

if __name__=='__main__':main()
