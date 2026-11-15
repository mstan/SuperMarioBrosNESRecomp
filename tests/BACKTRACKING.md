The backtracking checks require a current cycle build and a locally supplied
USA ROM. They never bundle ROMs or snapshots. Run them in new disposable output
directories; automated audio uses a dummy device.

`backtracking_checkpoint.py` accepts `--exe`, `--rom`, `--state` and `--out`.
The snapshot must be current-build World 1-1 gameplay. The test invokes the
original area loader at entrance page 4, verifies that native setup cleared the
midpoint field, and positions Mario before the actual page-5 threshold. These
are traversal prerequisites. Normal controller input crosses the threshold,
jumps the pit, returns left, then falls into a real pit and retries. The native
midpoint table, life loss and retry must choose page 5. A mod-Off forward control
must retain the same stock decision. The checkpoint/result field is never set
by the test after the native loader.

`backtracking_progress.py` accepts the same arguments plus `--enemy-policy`
(`native`, `classic`, or `viewport`). Its current-build World 1-1 snapshot needs
the first Goomba alive, the coin-question block at x=256 unused, and camera
x=32..240. Player positioning above the observed live Goomba and below the coin
block bypasses approach setup. Normal gravity/stomp and jump collision must
produce the score, enemy retirement, coin and used block. Ordinary right-left
travel then revisits them without restoring execution history. The test checks
a mod-Off stock clamp from the same rightward field. Native diagnostics use
Classic activation with the resident ledger when Backtracking is enabled.

Both scripts copy mod manifests into isolated test profiles and preserve the
source profile. No terrain, enemy, coin, score, checkpoint or completion output
is seeded. Each input index and resulting completed-frame index is recorded in
`result.json`. These are bounded World 1-1 regressions; they do not certify every
world, enemy type, linked platform, boss, custom ROM or alternate player mod.
