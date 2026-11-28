#!/usr/bin/env python3
"""Compatibility entry point; implementation lives in the pinned NES engine."""
from pathlib import Path
import runpy
globals().update(runpy.run_path(str(Path(__file__).resolve().parents[1] / 'nesrecomp/tools/verify_usa_rom.py'),
                               run_name='__main__' if __name__ == '__main__' else '_nes_shared_verify_usa_rom'))
