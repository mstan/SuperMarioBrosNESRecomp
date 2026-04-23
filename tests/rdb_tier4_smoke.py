"""Tier 4 oracle rewind smoke test."""
import socket, time, json

def cmd(sock, payload):
    sock.sendall((json.dumps(payload) + '\n').encode())
    buf = b''
    while True:
        chunk = sock.recv(65536)
        if not chunk: break
        buf += chunk
        if b'\n' in buf: break
    return json.loads(buf.decode(errors='replace').strip())

def main():
    s = socket.socket(); s.connect(('127.0.0.1', 4370))

    # Let the oracle run a bit before snapshotting.
    print('emu_step 30 frames ->', cmd(s, {'cmd':'emu_step','frames':30,'id':1}))
    print('emu_snapshot ->', cmd(s, {'cmd':'emu_snapshot','id':2}))
    tag1_resp = cmd(s, {'cmd':'emu_snapshot','id':3})
    tag1 = tag1_resp['tag']
    print('emu_snapshot ->', tag1_resp)

    # Step further, capture another.
    cmd(s, {'cmd':'emu_step','frames':60,'id':4})
    tag2_resp = cmd(s, {'cmd':'emu_snapshot','id':5})
    tag2 = tag2_resp['tag']
    print('after +60 frames emu_snapshot ->', tag2_resp)

    print('emu_rewind_list ->', cmd(s, {'cmd':'emu_rewind_list','id':6}))

    print(f'emu_rewind_to tag={tag1} ->', cmd(s, {'cmd':'emu_rewind_to','tag':tag1,'id':7}))
    # Now step one frame and see delta is small (we're back near the earlier state).
    cmd(s, {'cmd':'emu_step','frames':1,'id':8})
    d = cmd(s, {'cmd':'emu_wram_delta','id':9})
    print(f'emu_wram_delta after rewind+1step: changes={d["changes"]}')

    print(f'emu_rewind_to tag={tag2} ->', cmd(s, {'cmd':'emu_rewind_to','tag':tag2,'id':10}))

    s.close()

if __name__ == '__main__':
    main()
