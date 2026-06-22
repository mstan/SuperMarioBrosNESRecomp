#!/usr/bin/env python3
"""One-shot smb_ws_state dump."""
import socket, json
s = socket.socket(); s.settimeout(5); s.connect(("127.0.0.1", 4370))
s.sendall((json.dumps({"cmd": "smb_ws_state", "id": 1}) + "\n").encode())
b = b""
while b"\n" not in b:
    b += s.recv(65536)
ws = json.loads(b.split(b"\n", 1)[0])
print("oper_mode", ws["oper_mode"], "camera", ws["camera_x"])
print("guard_frames", ws.get("guard_frames"),
      "corr_applied", ws.get("corr_applied"),
      "embed_detect", ws.get("embed_detect"))
print("enemies", [(e["slot"], e["flag"], e["id"], e["screen_x"]) for e in ws["enemies"]])
