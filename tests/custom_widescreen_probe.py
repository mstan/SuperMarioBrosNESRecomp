"""Isolated SMB custom-renderer checks. Requires a TRACE-enabled executable.

Compares live guest RAM/CPU and the native playfield against the untouched
binary, validates decoded columns against the actual game area parser, and
checks deterministic save/load rendering. All files stay under --out.
"""
import argparse
import ctypes
from ctypes import wintypes
import json
import os
from pathlib import Path
import shutil
import socket
import subprocess
import time
from PIL import Image

class Probe:
    def __init__(self, exe, rom, out, aspect, *, mods=None, state=None, extra_args=()):
        self.out = Path(out).resolve(); self.out.mkdir(parents=True, exist_ok=False)
        exe = Path(exe).resolve()
        for name in (exe.name,'SDL2.dll'):shutil.copy2(exe.parent/name,self.out/name)
        if mods:shutil.copytree(mods,self.out/'mods')
        if state:(self.out/'mods/state.toml').write_text(state)
        env=dict(os.environ,NESRECOMP_NO_LAUNCHER='1',NESRECOMP_START_PAUSED='1')
        env.pop('NESRECOMP_FALLBACK_LOG',None)
        env['NESRECOMP_COSIM_HASH']=str(self.out/'machine.jsonl')
        self.log=(self.out/'runner.log').open('w')
        args=[str(self.out/exe.name),str(Path(rom).resolve()),'--tcp-port','5397']
        if aspect!='fit':args+=['--smoke','1000000','--smoke-output',str(self.out/'smoke.json')]
        if aspect is not None:args+=['--widescreen',aspect]
        args+=list(extra_args)
        si=subprocess.STARTUPINFO();si.dwFlags|=subprocess.STARTF_USESHOWWINDOW;si.wShowWindow=0
        self.proc=subprocess.Popen(args,cwd=self.out,env=env,stdout=self.log,stderr=subprocess.STDOUT,startupinfo=si)
        self.seq=0
        try:
            deadline=time.monotonic()+20
            while True:
                if self.proc.poll() is not None:raise RuntimeError('Runner exited; see '+str(self.out/'runner.log'))
                try:self.sock=socket.create_connection(('127.0.0.1',5397),timeout=1);break
                except OSError:
                    if time.monotonic()>deadline:raise
                    time.sleep(.05)
            self.sock.settimeout(30);self.stream=self.sock.makefile('rwb',buffering=0)
            self.cmd('set_turbo',enabled=1)
        except BaseException:self.close();raise
    def cmd(self,cmd,**kw):
        self.seq+=1
        self.stream.write((json.dumps(dict(id=self.seq,cmd=cmd,**kw))+'\n').encode())
        while True:
            line=self.stream.readline()
            if not line:raise RuntimeError('Runner connection closed')
            r=json.loads(line)
            if r.get('id')==self.seq:
                if r.get('ok') is False:raise RuntimeError(r)
                return r
    def advance(self,frames,buttons=0,resize=None):
        target=self.cmd('frame')['frame']+frames
        self.cmd('set_input',buttons=f'{buttons:02x}')
        self.cmd('run_to_frame',frame=target)
        # The engine's debugger pause loop currently discards resize events.
        # Resize during normal execution to exercise the presentation path.
        if resize:self.resize(*resize)
        while True:
            line=self.stream.readline()
            if not line:raise RuntimeError('Runner exited while advancing')
            if json.loads(line).get('event')=='run_to_done':break
    def resize(self,width,height):
        user=ctypes.WinDLL('user32',use_last_error=True)
        callback=ctypes.WINFUNCTYPE(wintypes.BOOL,wintypes.HWND,wintypes.LPARAM)
        user.EnumWindows.argtypes=[callback,wintypes.LPARAM]
        user.GetWindowThreadProcessId.argtypes=[wintypes.HWND,ctypes.POINTER(wintypes.DWORD)]
        user.GetClassNameW.argtypes=[wintypes.HWND,wintypes.LPWSTR,ctypes.c_int]
        user.GetClientRect.argtypes=[wintypes.HWND,ctypes.POINTER(wintypes.RECT)]
        user.GetWindowRect.argtypes=[wintypes.HWND,ctypes.POINTER(wintypes.RECT)]
        user.SetWindowPos.argtypes=[wintypes.HWND,wintypes.HWND,ctypes.c_int,ctypes.c_int,ctypes.c_int,ctypes.c_int,wintypes.UINT]
        windows=[]
        @callback
        def visit(hwnd,_):
            pid=wintypes.DWORD()
            user.GetWindowThreadProcessId(hwnd,ctypes.byref(pid))
            name=ctypes.create_unicode_buffer(128)
            user.GetClassNameW(hwnd,name,len(name))
            if pid.value==self.proc.pid and name.value=='SDL_app':windows.append(hwnd)
            return True
        user.EnumWindows(visit,0)
        assert len(windows)==1,windows
        hwnd=windows[0]
        client=wintypes.RECT();outer=wintypes.RECT()
        user.GetClientRect(hwnd,ctypes.byref(client));user.GetWindowRect(hwnd,ctypes.byref(outer))
        w=width+(outer.right-outer.left)-(client.right-client.left)
        h=height+(outer.bottom-outer.top)-(client.bottom-client.top)
        assert user.SetWindowPos(hwnd,None,-20000,-20000,w,h,0x0004|0x0010)
    def capture(self,name,stats=True):
        ram=b''.join(bytes.fromhex(self.cmd('read_ram',addr=f'{a:04x}',len=256)['hex']) for a in range(0,0x800,256))
        cpu=self.cmd('get_registers');cpu.pop('id',None)
        self.cmd('screenshot',path=(self.out/f'{name}.png').as_posix())
        (self.out/f'{name}.ram').write_bytes(ram)
        rec=dict(cpu=cpu,frame=self.cmd('frame')['frame'])
        if stats:rec['stats']=self.cmd('smb_ws_state')
        (self.out/f'{name}.json').write_text(json.dumps(rec,indent=2))
        return ram,cpu
    def close(self):
        if hasattr(self,'proc') and self.proc.poll() is None:
            self.proc.terminate()
            try:self.proc.wait(timeout=5)
            except subprocess.TimeoutExpired:self.proc.kill();self.proc.wait()
        if hasattr(self,'stream'):self.stream.close()
        if hasattr(self,'sock'):self.sock.close()
        self.log.close()

def run(args,name,exe,aspect,**options):
    if name!='baseline':options.setdefault('extra_args',['--widescreen-enemies','native'])
    p=Probe(exe,args.rom,Path(args.out)/name,aspect,**options)
    snapshots=[]
    try:
        p.advance(180,resize=(1600,900) if aspect=='fit' else None)
        p.advance(2,0x10);p.advance(300)
        for index,frames,buttons in [(0,0,0),(1,80,1),(2,80,0x81),(3,80,1),(4,80,0)]:
            if frames:p.advance(frames,buttons)
            snapshots.append(p.capture(f'frame{index}',name!='baseline'))
        if name!='baseline':
            stats=p.cmd('smb_ws_state')
            print(name, json.dumps(stats),flush=True)
            if stats['enabled']:
                assert stats['wide_frames']>0
                assert stats['decoded_columns']==512
                assert stats['verified_columns']>0 and stats['mismatched_columns']==0,stats
                state=(p.out/'state.sav').as_posix();p.cmd('save_state',path=state)
                p.advance(20,1);fresh=p.capture('fresh')
                p.cmd('load_state',path=state);p.advance(20,1);restored=p.capture('restored')
                assert fresh==restored
                assert (p.out/'fresh.png').read_bytes()==(p.out/'restored.png').read_bytes()
                if aspect=='fit':
                    for width,height,expected in [(2100,900,560),(1920,540,854),(640,600,256),(1600,900,426)]:
                        p.advance(60,resize=(width,height))
                        assert p.cmd('smb_ws_state')['render_width']==expected,(width,height)
        p.cmd('quit');assert p.proc.wait(timeout=10)==0
        log=(p.out/'runner.log').read_text(errors='replace')
        assert 'DISPATCH MISS' not in log and '=== WATCHDOG:' not in log
    finally:p.close()
    return snapshots

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    for key in ('exe','baseline','rom','out'):ap.add_argument('--'+key,required=True)
    ap.add_argument('--aspects',nargs='+',default=['off','16:9','21:9','32:9','fit'])
    ap.add_argument('--mods',help='Optional pristine preloaded mod catalog for saved-option checks')
    args=ap.parse_args()
    baseline=run(args,'baseline',args.baseline,'off')
    cases=[(aspect.replace(':','_'),aspect,{}) for aspect in args.aspects]
    if args.mods:
        state='''format_version = 1
[[package]]
id = "super-mario-bros.enhancement.widescreen"
version = "1.0.0"
[[feature]]
package_id = "super-mario-bros.enhancement.widescreen"
id = "widescreen"
enabled = true
[feature.values]
aspect = "21-9"
hud = "center"
'''
        cases+=[('mod_default',None,dict(mods=args.mods)),
                ('mod_selected',None,dict(mods=args.mods,state=state)),
                ('mod_override','off',dict(mods=args.mods,state=state))]
    machine=[json.loads(line) for line in (Path(args.out)/'baseline/machine.jsonl').read_text().splitlines() if line]
    assert len(machine)>700 and len({r['sub']['ram'] for r in machine})>1
    for name,aspect,options in cases:
        result=run(args,name,args.exe,aspect,**options)
        assert result==baseline,(name,'guest RAM/CPU changed')
        hashes=[json.loads(line) for line in (Path(args.out)/name/'machine.jsonl').read_text().splitlines() if line]
        assert hashes[:len(machine)]==machine,(name,'full machine hashes changed')
        for i in range(5):
            a=Image.open(Path(args.out)/'baseline'/f'frame{i}.png').convert('RGBA')
            b=Image.open(Path(args.out)/name/f'frame{i}.png').convert('RGBA')
            margin=(b.width-256)//2
            assert a.crop((0,32,256,240)).tobytes()==b.crop((margin,32,margin+256,240)).tobytes(),(name,i,'native pixels changed')
            if name=='mod_selected':
                assert b.width==560
                assert a.crop((0,0,256,32)).tobytes()==b.crop((margin,0,margin+256,32)).tobytes()
            elif name in ('mod_default','mod_override'):assert b.width==256
        print('PASS',name,'full machine hashes, guest state and native pixels',flush=True)
if __name__=='__main__':main()
