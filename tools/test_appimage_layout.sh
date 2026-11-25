#!/bin/sh
set -eu

if [ "$#" -lt 1 ] || [ "$#" -gt 2 ]; then
    echo "usage: $0 /path/to/AppDir [shader-preset-directory]" >&2
    exit 2
fi

appdir=$(CDPATH= cd -- "$1" && pwd)
shader_source=${2:-}
asset_root="$appdir/usr/bin/assets"
exe="$appdir/usr/bin/SuperMarioBrosRecomp"
helper="$appdir/usr/bin/falcon_owner_assets"
[ -x "$exe" ] || { echo "missing Linux game executable" >&2; exit 1; }
[ -x "$helper" ] || { echo "missing Linux owner-ROM helper" >&2; exit 1; }
[ -x "$appdir/AppRun" ] || { echo "missing AppRun" >&2; exit 1; }

for notice in THIRD-PARTY-LICENSES/README.md third_party/ymfm/LICENSE \
    licenses/Game-LICENSE.txt licenses/Game-PERMISSIONS.md \
    licenses/NESRecomp-LICENSE.txt licenses/SDL2-COPYING.txt \
    licenses/RecompUI-LICENSE.txt licenses/ImGui-LICENSE.txt \
    licenses/RecompNet-LICENSE.txt licenses/RBEngine-LICENSE.txt \
    licenses/LatoLatin-OFL.txt licenses/NotoSansSymbols2-OFL.txt \
    licenses/OpenMoji-LICENSE.txt; do
    [ -s "$appdir/usr/bin/$notice" ] || { echo "missing attribution: $notice" >&2; exit 1; }
done
required_assets='fonts/LatoLatin-Bold.ttf
fonts/LatoLatin-Regular.ttf
fonts/NotoSansSymbols2-Regular.ttf
fonts/OpenMoji-black-glyf.ttf
img/boxart.tga
img/brand_mark.tga
img/brand_nes.tga
img/flags.png
img/pad_nes.tga
img/verdict_bad.tga
img/verdict_none.tga
img/verdict_ok.tga
img/verdict_warn.tga'
if [ -n "$shader_source" ]; then
    shader_assets='shaders/README.md
shaders/_passes/crt-soft-pass.glsl
shaders/_passes/lcd-grid-pass.glsl
shaders/_passes/sharp-pass.glsl
shaders/_passes/warm-composite-pass.glsl
shaders/crt-soft.glslp
shaders/lcd-grid.glslp
shaders/sharp.glslp
shaders/warm-composite.glslp'
    required_assets=$(printf '%s\n' "$required_assets" "$shader_assets" | LC_ALL=C sort)
fi
actual_assets=$(cd "$asset_root" && find . -type f -printf '%P\n' | LC_ALL=C sort)
[ "$actual_assets" = "$required_assets" ] || {
    echo "launcher asset inventory differs from the approved list" >&2; exit 1; }
if [ -n "$shader_source" ]; then
    for asset in $shader_assets; do
        cmp -s "$shader_source/${asset#shaders/}" "$asset_root/$asset" || {
            echo "bundled shader differs from its source: $asset" >&2; exit 1; }
    done
fi

required_mods='packages/nesrecomp.developer.replay/1.0.0/manifest.toml
packages/nesrecomp.twitch-chat/1.0.0/manifest.toml
packages/super-mario-bros.enhancement.voxel-first-person/1.0.0/manifest.toml
packages/super-mario-bros.enhancement.widescreen/1.0.0/manifest.toml
packages/super-mario-bros.gameplay.free-backtracking/1.0.0/manifest.toml
packages/super-mario-bros.gameplay.metroid-samus-player-replacement/1.0.0/manifest.toml
packages/super-mario-bros.gameplay.s3k-sonic-player-replacement/1.0.0/manifest.toml
packages/super-mario-bros.gameplay.simultaneous-coop/1.0.0/manifest.toml
packages/super-mario-bros.gameplay.smash64-player-replacement/1.0.0/manifest.toml
packages/super-mario-bros.gameplay.zelda2-link-player-replacement/1.0.0/manifest.toml'
actual_mods=$(cd "$appdir/usr/bin/mods" && find . -type f -printf '%P\n' | sort)
[ "$actual_mods" = "$required_mods" ] || {
    echo "preloaded mod inventory differs from the pristine manifests" >&2; exit 1; }

if find "$appdir" -type f \( -iname '*.nes' -o -iname '*.z64' -o -iname '*.v64' \
    -o -iname '*.n64' -o -iname '*.wav' -o -name 'falcon_runtime.bin' \
    -o -name 'state.toml' -o -iname '*.sav' \) | grep -q .; then
    echo "forbidden ROM, cache, audio, or state payload in AppDir" >&2
    exit 1
fi

tmp=$(mktemp -d)
trap 'chmod -R u+w "$appdir" "$tmp" 2>/dev/null || true; rm -rf "$tmp"' EXIT HUP INT TERM
before="$tmp/before.sha"
after="$tmp/after.sha"
(cd "$appdir" && find . -type f -print0 | sort -z | xargs -0 sha256sum) > "$before"
chmod -R a-w "$appdir"

state="$tmp/state"
mkdir -p "$state"
APPIMAGE="$state/SuperMarioBrosRecomp.AppImage" \
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy NESRECOMP_NO_LAUNCHER=1 \
"$appdir/AppRun" >/dev/null 2>&1 || true

for manifest in $required_mods; do
    [ -f "$state/mods/$manifest" ] || {
        echo "AppRun did not seed $manifest beside the AppImage" >&2; exit 1; }
done
mkdir -p "$state/mods/packages/user.example/1.0.0"
printf 'user-owned\n' > "$state/mods/packages/user.example/1.0.0/marker.txt"
cat > "$state/mods/state.toml" <<'STATE'
format_version = 1
[[package]]
id = "super-mario-bros.enhancement.widescreen"
version = "1.0.0"
[[feature]]
package_id = "super-mario-bros.enhancement.widescreen"
id = "widescreen"
enabled = false
[feature.values]
aspect = "21-9"
hud = "center"
[[package]]
id = "super-mario-bros.gameplay.free-backtracking"
version = "1.0.0"
[[feature]]
package_id = "super-mario-bros.gameplay.free-backtracking"
id = "backtracking"
enabled = false
STATE
APPIMAGE="$state/SuperMarioBrosRecomp.AppImage" \
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy NESRECOMP_NO_LAUNCHER=1 \
"$appdir/AppRun" >/dev/null 2>&1 || true
[ "$(cat "$state/mods/packages/user.example/1.0.0/marker.txt")" = user-owned ] || {
    echo "AppRun overwrote a user-installed mod" >&2; exit 1; }
# The runtime normalizes valid selections on startup. Check the actual saved
# choice rather than an invalid-TOML sentinel or incidental file formatting.
python3 - "$state/mods/state.toml" <<'PY'
import re, sys
with open(sys.argv[1], encoding='utf-8') as stream:
    state = stream.read()
def field(block, key, value):
    return re.search(r'(?m)^\s*' + re.escape(key) + r'\s*=\s*' + re.escape(value) + r'\s*$', block)
# Check the engine's canonical selection output using the standard library;
# packaging must not acquire an additional Python 3.11 requirement.
assert any(field(block, 'package_id', '"super-mario-bros.enhancement.widescreen"')
           and field(block, 'id', '"widescreen"')
           and field(block, 'enabled', 'false')
           and field(block, 'aspect', '"21-9"')
           and field(block, 'hud', '"center"')
           for block in re.split(r'(?m)^\[\[feature\]\]\s*$', state)[1:]), 'AppRun lost the saved widescreen choice'
assert any(field(block, 'package_id', '"super-mario-bros.gameplay.free-backtracking"')
           and field(block, 'id', '"backtracking"')
           and field(block, 'enabled', 'false')
           for block in re.split(r'(?m)^\[\[feature\]\]\s*$', state)[1:]), 'AppRun lost the saved backtracking choice'
PY

(cd "$appdir" && find . -type f -print0 | sort -z | xargs -0 sha256sum) > "$after"
cmp -s "$before" "$after" || { echo "AppRun modified its read-only payload" >&2; exit 1; }
echo "AppImage layout test: PASS"
