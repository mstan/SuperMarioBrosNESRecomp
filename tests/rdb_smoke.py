"""Tier-1 RDB smoke test — arm $0700-$07FF, let game run, dump hits."""
import socket, time, json, sys

HOST, PORT = '127.0.0.1', 4370

def cmd(sock, payload):
    sock.sendall((json.dumps(payload) + '\n').encode())
    buf = b''
    while True:
        chunk = sock.recv(32768)
        if not chunk:
            break
        buf += chunk
        if buf.endswith(b'\n') or b'\n' in buf:
            break
    return buf.decode(errors='replace').strip()

def main():
    s = socket.socket()
    s.connect((HOST, PORT))

    print('=== rdb_status (before) ===')
    print(cmd(s, {'cmd': 'rdb_status', 'id': 1}))

    print('=== rdb_range 0x0700 0x07FF ===')
    print(cmd(s, {'cmd': 'rdb_range', 'lo': '0x0700', 'hi': '0x07FF', 'id': 2}))

    print('=== waiting 3 s for stores to accumulate ===')
    time.sleep(3.0)

    print('=== rdb_count ===')
    print(cmd(s, {'cmd': 'rdb_count', 'id': 3}))

    print('=== rdb_dump first 10 ===')
    print(cmd(s, {'cmd': 'rdb_dump', 'start': 0, 'max': 10, 'id': 4}))

    print('=== rdb_status (after) ===')
    print(cmd(s, {'cmd': 'rdb_status', 'id': 5}))

    s.close()

if __name__ == '__main__':
    main()
