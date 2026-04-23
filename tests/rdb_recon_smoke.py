"""Verify block_idx in store dumps and rdb_wram_at_block reconstruction."""
import socket, time, json

HOST, PORT = '127.0.0.1', 4370

def cmd(sock, payload):
    sock.sendall((json.dumps(payload) + '\n').encode())
    buf = b''
    while True:
        chunk = sock.recv(65536)
        if not chunk:
            break
        buf += chunk
        if b'\n' in buf:
            break
    return json.loads(buf.decode(errors='replace').strip())

def main():
    s = socket.socket(); s.connect((HOST, PORT))

    # Arm Tier 3 — auto-captures $0000-$07FF writes into store ring.
    r = cmd(s, {'cmd': 'rdb_anchor_on', 'interval': 2048, 'id': 1})
    print('anchor_on ->', r)

    time.sleep(2.5)

    st = cmd(s, {'cmd': 'rdb_status', 'id': 2})
    print('status:')
    print(f'  block_idx={st["block_idx"]}  anchors={st["anchor_count"]}  '
          f'store_count={st["store_count"]}')

    an = cmd(s, {'cmd': 'rdb_anchor_status', 'id': 3})
    print('anchor_status:', an)

    # Peek a store entry — confirm block field is present.
    d = cmd(s, {'cmd': 'rdb_dump', 'start': 0, 'max': 1, 'id': 4})
    if d.get('entries'):
        e = d['entries'][0]
        print('store[0] has block field =>', 'block' in e, '  entry:', e)

    # Ask for reconstruction at block_idx = anchor_block + 1000.
    target = an['count'] and (int(st['block_idx']) - 10000)
    r = cmd(s, {'cmd': 'rdb_wram_at_block', 'block': target, 'id': 5})
    print(f'reconstruction at block={target}:')
    print(f'  anchor_block={r.get("anchor_block")}  replayed={r.get("replayed")}  '
          f'store_ring_wrapped={r.get("store_ring_wrapped")}')
    hex_blob = r.get('hex', '')
    print(f'  wram hex length = {len(hex_blob)} (expect 4096)')
    # Sanity: $072E (world) should be 0x00 for title screen.
    if len(hex_blob) >= 4096:
        b072e = hex_blob[0x072E * 2 : 0x072E * 2 + 2]
        print(f'  $072E (world) = 0x{b072e}')

    cmd(s, {'cmd': 'rdb_anchor_off', 'id': 6})
    s.close()

if __name__ == '__main__':
    main()
