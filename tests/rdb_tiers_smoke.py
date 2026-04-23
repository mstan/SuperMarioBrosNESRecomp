"""Smoke test for Tier 1/1.5/2/2.5/3 RDB commands."""
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
    return buf.decode(errors='replace').strip()

def j(sock, c, **kw):
    kw['cmd'] = c
    kw.setdefault('id', 1)
    out = cmd(sock, kw)
    if len(out) > 300:
        return out[:300] + f'... (+{len(out)-300} bytes)'
    return out

def main():
    s = socket.socket(); s.connect((HOST, PORT))

    print('== status ==');                print(j(s, 'rdb_status'))

    print('== trace_calls ==');           print(j(s, 'trace_calls'))
    print('== trace_blocks ==');          print(j(s, 'trace_blocks'))
    print('== trace_blocks_range 8082-80FF ==')
    print(j(s, 'trace_blocks_range', lo='0x8082', hi='0x80FF'))
    print('== rdb_range 0x0700 0x07FF ==')
    print(j(s, 'rdb_range', lo='0x0700', hi='0x07FF'))
    print('== rdb_watch_add $0770 any ==')
    print(j(s, 'rdb_watch_add', addr='0x0770'))
    print('== rdb_break $8082 (NMI entry) ==')
    print(j(s, 'rdb_break', pc='0x8082'))
    print('== rdb_anchor_on interval=256 ==')
    print(j(s, 'rdb_anchor_on', interval=256))

    print('-- sleep 2 s for traffic --')
    time.sleep(2.0)

    print('== rdb_parked ==');            print(j(s, 'rdb_parked'))
    print('== status ==');                print(j(s, 'rdb_status'))

    # If something parked (watch or break), continue it.
    print('== rdb_break_continue ==');    print(j(s, 'rdb_break_continue'))
    print('== rdb_watch_continue ==');    print(j(s, 'rdb_watch_continue'))

    print('== get_block_trace max=5 ==')
    print(j(s, 'get_block_trace', max=5))
    print('== get_call_trace max=5 ==')
    print(j(s, 'get_call_trace', max=5))
    print('== rdb_dump max=5 ==')
    print(j(s, 'rdb_dump', max=5))
    print('== rdb_anchor_status ==');     print(j(s, 'rdb_anchor_status'))
    print('== rdb_wram_at_block block=512 ==')
    out = j(s, 'rdb_wram_at_block', block=512)
    print(out)

    print('-- cleanup --')
    print(j(s, 'trace_blocks_reset'))
    print(j(s, 'trace_calls_reset'))
    print(j(s, 'rdb_break_clear'))
    print(j(s, 'rdb_watch_clear'))
    print(j(s, 'rdb_anchor_off'))

    s.close()

if __name__ == '__main__':
    main()
