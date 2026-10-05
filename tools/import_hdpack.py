#!/usr/bin/env python3
"""Create a local SMB1 LyonHrt HD .nesmod from the owner's stock ROM and pack."""
import argparse
from pathlib import Path
import sys

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--pack', type=Path, required=True)
    parser.add_argument('--rom', type=Path, required=True)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--framework', type=Path, default=Path(__file__).resolve().parents[1]/'nesrecomp')
    args = parser.parse_args()
    here = Path(__file__).resolve().parent
    sys.path[:0] = [str(here), str(args.framework/'tools')]
    from package_hdpack import main as package_main
    saved_argv = sys.argv
    sys.argv = ['package_hdpack', '--pack', str(args.pack),
        '--rom', str(args.rom), '--game-id', 'super-mario-bros-world',
        '--id', 'super-mario-bros.lyonhrt-hd', '--name', 'Super Mario Bros. LyonHrt HD',
        '--author', 'LyonHrt', '--license', 'User-supplied pack; original creator terms apply',
        '--out', str(args.out)]
    try:
        package_main()
    finally:
        sys.argv = saved_argv
    return 0

if __name__ == '__main__':
    raise SystemExit(main())
