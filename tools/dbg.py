#!/usr/bin/env python3
"""Compatibility entry point; implementation lives in the pinned NES engine."""
from pathlib import Path
import runpy
globals().update(runpy.run_path(str(Path(__file__).resolve().parents[1] / 'nesrecomp/tools/dbg.py'),
                               run_name='__main__' if __name__ == '__main__' else '_nes_shared_dbg'))

_shared_send_cmd = send_cmd
def send_cmd(cmd_name, **kwargs):
    return _shared_send_cmd(cmd_name, _host=HOST, _port=PORT, **kwargs)
