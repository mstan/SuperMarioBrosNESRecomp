"""Area-edge camera regressions using real gameplay and the original room loader.

Compare centered mode with the prior binary, native pixels/guest state across
camera policies, fixed bonus entrances, goal flags, saved replay and live Fit.
The bonus fixtures deliberately invoke the normal room initializer through RAM;
they validate room selection/rendering, not a player route into those pipes.
"""
import argparse
import json
from pathlib import Path
import struct
from PIL import Image
from custom_widescreen_probe import Probe
from widescreen_boundaries_probe import records, poke


def machine_fixture(source, destination):
    base, items = records(Path(source).read_bytes())
    items = [(k, v) for k, v in items if k.rstrip(b'\0') not in
             (b'super-mario-bros.widescreen.world', b'super-mario-bros.widescreen.actors')]
    destination.write_bytes(base + struct.pack('<H', len(items)) + b''.join(
        k + struct.pack('<I', len(v)) + v for k, v in items))
    return destination


def capture(p, name, anchored=False):
    guest = p.capture(name)
    st = p.cmd('smb_ws_state')
    im = Image.open(p.out / (name + '.png')).convert('RGB')
    x0 = st.get('native_x0', (im.width - 256) // 2)
    assert 0 <= x0 <= im.width - 256, st
    assert st['mismatched_columns'] == 0, st
    # Stock pixels remain authoritative at their new location, including Mario.
    result = (guest, im.crop((x0, 32, x0 + 256, 240)).tobytes())
    if anchored:
        seam = p.cmd('smb_ws_seam')
        assert seam['samples'] > 0 and seam['offset_errors'][4] == 0, seam
    return result, st


def run(args, name, aspect='32:9', camera='edges', baseline=False, mods=False):
    extra = ['--widescreen-enemies', 'classic']
    if not baseline: extra += ['--widescreen-camera', camera]
    options = {}
    if mods:
        extra = []
        options = dict(mods=args.mods, state=f'''format_version = 1
[[package]]
id = "super-mario-bros.enhancement.widescreen"
version = "1.0.0"
[[feature]]
package_id = "super-mario-bros.enhancement.widescreen"
id = "widescreen"
enabled = true
[feature.values]
aspect = "32-9"
enemy_activation = "classic"
camera = "{camera}"
''')
    args.port += 1
    p = Probe(args.baseline if baseline else args.exe, args.rom, args.out / name,
              None if mods else aspect, extra_args=extra, port=args.port, **options)
    result = []
    try:
        assert p.cmd('frame')['frame'] == 0, 'Probe connected after startup pause was lost'
        p.advance(180, resize=(1920, 540) if aspect == 'fit' else None)
        p.advance(2, 0x10); p.advance(160)
        snap, st = capture(p, 'start', not baseline)
        result.append(snap)
        if not baseline and camera == 'edges': assert st['view_left'] == 0, st
        for i, (frames, buttons) in enumerate(((80, 1), (80, 0x81), (80, 1))):
            p.advance(frames, buttons)
            snap, st = capture(p, f'move{i}', not baseline)
            result.append(snap)
        if aspect == 'fit':
            for w, h, expected in ((1600, 900, 426), (2100, 900, 560),
                                   (640, 600, 256), (1920, 540, 854)):
                p.advance(60, resize=(w, h))
                assert p.cmd('smb_ws_state')['render_width'] == expected
            # Fit uses a separate route after resizing; the other cases are A/B.
            result = None
        p.cmd('load_state', path=args.fixture.as_posix()); p.advance(4)
        snap, st = capture(p, 'goal', not baseline)
        if result is not None: result.append(snap)
        flag = p.cmd('smb_ws_flag')
        assert flag['sprites'] >= 3, flag
        if not baseline and camera == 'edges' and st['render_width'] == 854:
            assert st['area_end'] == 3328 and st['view_left'] == 2474, st
        saved = p.out / 'replay.sav'
        p.cmd('save_state', path=saved.as_posix())
        p.advance(20, 1); fresh = capture(p, 'fresh')[0]
        p.cmd('load_state', path=saved.as_posix()); p.advance(20, 1)
        assert capture(p, 'restored')[0] == fresh
        assert (p.out / 'fresh.png').read_bytes() == (p.out / 'restored.png').read_bytes()
        # Bonus rooms share one AreaData stream but have independent entrances.
        for page in (0, 2):
            for addr, value in ((0x750, 0xc2), (0x751, page), (0x752, 2),
                                (0x75b, 0), (0x772, 0)):
                poke(p, addr, value)
            p.advance(160)
            snap, st = capture(p, 'bonus' + str(page), not baseline)
            if result is not None: result.append(snap)
            if not baseline and camera == 'edges':
                assert st['fixed_rooms'] and st['native_x0'] == (st['render_width'] - 256) // 2, st
                assert st['camera_x'] == page * 256, st
                im = Image.open(p.out / ('bonus' + str(page) + '.png')).convert('RGB')
                # No terrain or objects from neighboring bonus rooms in padding.
                x0 = st['native_x0']
                for region in ((0, 32, x0, 240), (x0 + 256, 32, im.width, 240)):
                    assert im.crop(region).getbbox() is None
        p.cmd('quit'); assert p.proc.wait(timeout=10) == 0
        log = (p.out / 'runner.log').read_text(errors='replace')
        assert 'DISPATCH MISS' not in log and '=== WATCHDOG:' not in log
        print('PASS', name, 'camera placement, native pixels, flag, replay and fixed rooms', flush=True)
        return result
    finally:
        p.close()


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    for key in ('exe', 'baseline', 'rom', 'out', 'f2'): ap.add_argument('--' + key, required=True)
    ap.add_argument('--mods')
    args = ap.parse_args()
    args.port = 15490
    args.out = Path(args.out).resolve(); args.out.mkdir(parents=True, exist_ok=False)
    args.fixture = machine_fixture(args.f2, args.out / 'f2_machine.sav')
    reference = run(args, 'before', baseline=True)
    centered = run(args, 'centered', camera='centered')
    assert reference == centered, 'Centered mode changed guest state or native pixels'
    for image in (args.out / 'before').glob('*.png'):
        assert image.read_bytes() == (args.out / 'centered' / image.name).read_bytes(), image.name
    hashes = lambda folder: [json.loads(line) for line in (args.out / folder / 'machine.jsonl').read_text().splitlines()]
    assert hashes('before') == hashes('centered'), 'Centered mode changed full machine hashes'
    for aspect in ('16:9', '21:9', '32:9'):
        assert run(args, aspect.replace(':', '_'), aspect=aspect) == reference, aspect
    run(args, 'fit', aspect='fit')
    if args.mods:
        for camera in ('edges', 'centered'):
            assert run(args, 'mods_' + camera, camera=camera, mods=True) == reference
    print('PASS centered A/B hashes and images; all camera policies retain native pixels and guest state', flush=True)


if __name__ == '__main__': main()
