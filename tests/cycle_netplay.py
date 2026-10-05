"""Bounded loopback check for complete cycle rollback state convergence."""
import argparse, hashlib, json, os, pathlib, re, subprocess, time

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('exe', 'rom', 'out'):
        parser.add_argument('--'+name, type=pathlib.Path, required=True)
    parser.add_argument('--case', choices=('stock', 'coop4', 'widescreen'), default='stock')
    parser.add_argument('--rollback', action='store_true')
    parser.add_argument('--window-peer', action='store_true', help='last peer uses hidden SDL instead of headless host')
    parser.add_argument('--port', type=int, default=47850)
    args = parser.parse_args()
    out = args.out.resolve(); out.mkdir(parents=True, exist_ok=False)
    seats = 4 if args.case == 'coop4' else 2
    session = f'nes-session/1;coop={4 if seats==4 else 0}:player;vw={426 if args.case=="widescreen" else 256};ws={1 if args.case=="widescreen" else 0}:1:0:1;'
    startup = None
    if os.name == 'nt':
        startup = subprocess.STARTUPINFO(); startup.dwFlags |= subprocess.STARTF_USESHOWWINDOW; startup.wShowWindow = 0
    processes, logs = [], []
    try:
        for slot in range(seats):
            env = dict(os.environ, NESRECOMP_NO_LAUNCHER='1', NES_NETPLAY='1', NES_NET_SLOT=str(slot),
                NES_NET_SLOTS=str(seats), NES_NET_BIND=f'127.0.0.1:{args.port+slot}',
                NES_NET_PEER=f'127.0.0.1:{args.port+(1 if slot==0 and seats==2 else 0)}',
                NES_NET_SESSION_CONFIG=session, NES_NET_SESSION_ID=str(args.port), NES_NET_TEST_PAD=str(slot),
                NES_NET_MATCH_TICKS='360', NES_NET_SRAM_SYNC='1', NES_NET_CONNECT_TIMEOUT_MS='10000',
                NES_NET_FINAL_STATE=str(out/f'{slot}.rbstate'), NES_RB_FORCE_MISPREDICT='45' if args.rollback and slot==0 else '0',
                SDL_AUDIODRIVER='dummy', SDL_VIDEODRIVER='dummy')
            host = ['--hidden', '--exit-after', '500'] if args.window_peer and slot==seats-1 else ['--headless', '--frames', '500', '--realtime']
            log = (out/f'{slot}.log').open('w'); logs.append(log)
            processes.append(subprocess.Popen([str(args.exe.resolve()), str(args.rom.resolve()), *host, '--no-save'],
                cwd=out, env=env, stdout=log, stderr=subprocess.STDOUT, startupinfo=startup,
                creationflags=getattr(subprocess, 'CREATE_NO_WINDOW', 0)))
        deadline = time.monotonic()+65
        while any(p.poll() is None for p in processes) and time.monotonic()<deadline:
            time.sleep(.2)
    finally:
        for p in processes:
            if p.poll() is None: p.terminate(); p.wait(timeout=10)
        for log in logs: log.close()
    assert len(processes)==seats and all(p.returncode==0 for p in processes), 'Peer failed; see retained logs'
    states = [(out/f'{slot}.rbstate').read_bytes() for slot in range(seats)]
    assert all(state==states[0] for state in states), 'Complete final states differ'
    summaries = [re.search(r'NETPLAY_DRIVER .*', (out/f'{slot}.log').read_text(errors='replace')) for slot in range(seats)]
    assert all(row and 'desyncs=0' in row[0] for row in summaries), 'Missing clean driver summary'
    if args.rollback:
        assert any(int(re.search(r'resim_ticks=(\d+)', row[0])[1])>0 for row in summaries), 'No replay occurred'
    result = dict(case=args.case, window_peer=args.window_peer, state_sha256=hashlib.sha256(states[0]).hexdigest(),
        summaries=[row[0] for row in summaries])
    (out/'result.json').write_text(json.dumps(result, indent=2)); print(json.dumps(result, indent=2))

if __name__=='__main__': main()
