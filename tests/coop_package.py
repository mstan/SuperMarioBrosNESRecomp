"""Exercise the shipped manifest and persisted launcher options without CLI overrides."""
import argparse
import os
import shutil
import subprocess
from pathlib import Path
from coop_runtime import State


def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--exe',type=Path,required=True)
    ap.add_argument('--rom',type=Path,required=True)
    ap.add_argument('--out',type=Path,default=Path('build-coop/package-test'))
    ap.add_argument('--net-enabled',action='store_true',help='Also test the online session seal (netplay builds)')
    a=ap.parse_args();out=a.out.resolve();out.mkdir(parents=True,exist_ok=True)
    exe=out/a.exe.name;shutil.copy2(a.exe,exe)
    for dll in a.exe.parent.glob('*.dll'): shutil.copy2(dll,out/dll.name)
    root=Path(__file__).resolve().parents[1]
    shutil.copytree(root/'mods/preloaded/packages',out/'mods/packages',dirs_exist_ok=True)
    package='super-mario-bros.gameplay.simultaneous-coop'
    for count,pause in [(2,'player'),(3,'shared'),(4,'player')]:
        state=f'''format_version=1
[[package]]
id="{package}"
version="1.0.0"
[[feature]]
package_id="{package}"
id="coop"
enabled=true
[feature.values]
players="{count}"
pause="{pause}"
'''
        (out/'mods/state.toml').write_text(state)
        save=out/f'package-{count}.sav';script=out/'package.script'
        script.write_text(f'WAIT 60\nHOLD START\nWAIT 6\nRELEASE START\nWAIT_RAM8 000E 08\nWAIT 4\nSAVE_STATE {save.as_posix()}\nWAIT 2\nEXIT 0\n')
        command=[str(exe),str(a.rom.resolve()),'--script',str(script),'--smoke','1000000','--smoke-interval','1000000']
        r=subprocess.run(command,creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0), capture_output=True,text=True,timeout=40)
        (out/f'package-{count}.log').write_text(r.stdout+r.stderr)
        assert r.returncode==0,(count,r.stderr)
        s=State(save)
        assert s.data[s.mod+5:s.mod+8]==bytes([count,pause=='shared',1])
        # A second launch consumes the runtime's rewritten state file.
        r=subprocess.run(command,creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0), capture_output=True,text=True,timeout=40)
        assert r.returncode==0
        assert State(save).data[s.mod+5:s.mod+8]==bytes([count,pause=='shared',1])
    if a.net_enabled:
        # Co-op is online-capable (docs/NETPLAY.md): an online launch commits
        # no mods, takes the co-op mode from the host's offline SELECTION as
        # the sealed session configuration, and starts the session. With no
        # peer it must then give up at the pre-boot barrier -- the same place
        # any unanswered match stops -- not reject co-op up front.
        env=dict(os.environ,NES_NETPLAY='1',NES_NET_CONNECT_TIMEOUT_MS='1500',
                 NES_NET_EXIT_ON_RETURN='1',SDL_VIDEODRIVER='dummy',SDL_AUDIODRIVER='dummy',
                 NES_NET_BIND='127.0.0.1:0',NES_NET_PEER='127.0.0.1:9')
        online=subprocess.run([str(exe),str(a.rom.resolve())],creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0), capture_output=True,text=True,timeout=30,env=env)
        (out/'online-session.log').write_text(online.stdout+online.stderr)
        assert 'requires local play' not in online.stderr, 'co-op was refused online'
        want=f'session_config="nes-session/1;coop={count}:{pause};widescreen=0;"'
        assert want in online.stderr, ('session configuration not sealed', want)
        assert 'connect_timeout' in online.stderr and online.returncode==3, online.returncode
        # Scripts stay local-only: an input source outside the published rows.
        scripted=subprocess.run(command,creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0), capture_output=True,text=True,timeout=15,env=env)
        assert scripted.returncode!=0 and 'input scripts requires local play' in scripted.stderr
        print('PASS: co-op sealed into the online session; scripts refused online')
    print('PASS: shipped package activation and persisted 2/3/4-player/pause options')


if __name__=='__main__': main()
