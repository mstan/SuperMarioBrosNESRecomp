#!/bin/sh
set -eu

if [ "$#" -ne 1 ]; then
    echo "usage: $0 /path/to/AppDir" >&2
    exit 2
fi

appdir=$(CDPATH= cd -- "$1" && pwd)
exe="$appdir/usr/bin/SuperMarioBrosRecomp"
helper="$appdir/usr/bin/falcon_owner_assets"
[ -x "$exe" ] || { echo "missing Linux game executable" >&2; exit 1; }
[ -x "$helper" ] || { echo "missing Linux owner-ROM helper" >&2; exit 1; }
[ -x "$appdir/AppRun" ] || { echo "missing AppRun" >&2; exit 1; }

required_assets='fonts/LatoLatin-Bold.ttf
fonts/LatoLatin-Regular.ttf
fonts/NotoSansSymbols2-Regular.ttf
fonts/OpenMoji-black-glyf.ttf
img/boxart.tga
img/brand_mark.tga
img/brand_nes.tga
img/pad_nes.tga
img/verdict_bad.tga
img/verdict_none.tga
img/verdict_ok.tga
img/verdict_warn.tga'
actual_assets=$(cd "$appdir/usr/bin/assets" && find . -type f -printf '%P\n' | sort)
[ "$actual_assets" = "$required_assets" ] || {
    echo "launcher asset inventory differs from the approved list" >&2; exit 1; }

required_mods='packages/super-mario-bros.enhancement.voxel-first-person/1.0.0/manifest.toml
packages/super-mario-bros.enhancement.widescreen/1.0.0/manifest.toml
packages/super-mario-bros.gameplay.smash64-player-replacement/1.0.0/manifest.toml'
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
timeout 20 "$appdir/AppRun" >/dev/null 2>&1 || true

for manifest in $required_mods; do
    [ -f "$state/mods/$manifest" ] || {
        echo "AppRun did not seed $manifest beside the AppImage" >&2; exit 1; }
done
mkdir -p "$state/mods/packages/user.example/1.0.0"
printf 'user-owned\n' > "$state/mods/packages/user.example/1.0.0/marker.txt"
printf 'user-state\n' > "$state/mods/state.toml"
APPIMAGE="$state/SuperMarioBrosRecomp.AppImage" \
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy NESRECOMP_NO_LAUNCHER=1 \
timeout 20 "$appdir/AppRun" >/dev/null 2>&1 || true
[ "$(cat "$state/mods/packages/user.example/1.0.0/marker.txt")" = user-owned ] || {
    echo "AppRun overwrote a user-installed mod" >&2; exit 1; }
[ "$(cat "$state/mods/state.toml")" = user-state ] || {
    echo "AppRun overwrote user mod state" >&2; exit 1; }

(cd "$appdir" && find . -type f -print0 | sort -z | xargs -0 sha256sum) > "$after"
cmp -s "$before" "$after" || { echo "AppRun modified its read-only payload" >&2; exit 1; }
echo "AppImage layout test: PASS"
