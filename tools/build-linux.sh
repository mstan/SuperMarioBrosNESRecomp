#!/usr/bin/env bash
# build-linux.sh — DEFINITIVE Linux build/package script for a recomp game.
#
# This is the Linux counterpart to tools/make_release.ps1 (Windows). It mirrors
# the same prod-vs-debug discipline:
#
#   prod  (default) — strips ALL developer tooling: no TCP debug server, no
#                     observability rings, no oracle backend. The shipped build.
#   debug           — compiles the TCP debug server + rings back in.
#
# It configures + builds with cmake/make, then wraps the ELF into a
# self-contained x86_64 AppImage whose AppRun:
#   * auto-finds a ROM beside the AppImage and seeds rom.cfg without bypassing
#     the launcher, so the Mods screen and owner-ROM picker remain reachable,
#   * exports the SDL hints that make controllers work out-of-the-box on a
#     Steam Deck (reads the pad natively instead of Steam's keyboard remap).
#
# Usage:
#   bash tools/build-linux.sh                 # prod AppImage (default)
#   bash tools/build-linux.sh --config debug  # debug build (TCP server + rings)
#   bash tools/build-linux.sh --regen         # regen src/gen first (tools/regen.sh)
#   bash tools/build-linux.sh --run           # launch the AppImage after building
#   bash tools/build-linux.sh --no-package    # configure + build only, skip AppImage
#   bash tools/build-linux.sh --out DIR       # where to drop the .AppImage
#   bash tools/build-linux.sh --jobs N        # parallel build jobs (default: nproc)
#
# Prereqs: cmake, a C/C++ toolchain, libsdl2-dev, libgl1-mesa-dev, curl,
# Python 3 with PyInstaller/Pillow, and FUSE support for AppImage tooling.
# Pinned linuxdeploy/appimagetool binaries are downloaded and SHA-256 checked.
# Regen needs a verified ROM at the repo root (see tools/regen.sh).
set -euo pipefail

# ============================ PER-GAME CONFIG ===============================
# The ONLY block that differs between games. Copy this file + edit just this header.
APP_NAME="SuperMarioBros"
RELEASE_SLUG="SuperMarioBrosRecomp"
CMAKE_TARGET="SuperMarioBrosRecomp"
ROM_EXTS="nes"                             # AppRun auto-finds *.nes next to the AppImage
EXTRA_ARGS=""
REGEN_CMD=""                               # generated C is committed; regen is the Windows recompiler
PREBUILD_CMD=""
POSTBUILD_CMD=""
# prod/debug -> framework cmake flags. NESRECOMP_ENABLE_TRACE OFF strips the TCP
# server from production builds.
PROD_CMAKE_FLAGS=( -DNESRECOMP_ENABLE_TRACE=OFF -DNESRECOMP_REQUIRE_FALCON_OWNER_HELPER=ON )
DEBUG_CMAKE_FLAGS=( -DNESRECOMP_ENABLE_TRACE=ON )
REQUIRED_MOD_MANIFESTS=(
  "packages/super-mario-bros.enhancement.voxel-first-person/1.0.0/manifest.toml"
  "packages/super-mario-bros.enhancement.widescreen/1.0.0/manifest.toml"
  "packages/super-mario-bros.gameplay.metroid-samus-player-replacement/1.0.0/manifest.toml"
  "packages/super-mario-bros.gameplay.s3k-sonic-player-replacement/1.0.0/manifest.toml"
  "packages/super-mario-bros.gameplay.smash64-player-replacement/1.0.0/manifest.toml"
  "packages/super-mario-bros.gameplay.zelda2-link-player-replacement/1.0.0/manifest.toml"
)
# ============================================================================

LINUXDEPLOY_URL=https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
LINUXDEPLOY_SHA=421ca71d5c69ea97c6309276232990d43df1dcece0edfaa26bbf926ff96ed12e
APPIMAGETOOL_URL=https://github.com/AppImage/appimagetool/releases/download/continuous/appimagetool-x86_64.AppImage
APPIMAGETOOL_SHA=a6d71e2b6cd66f8e8d16c37ad164658985e0cf5fcaa950c90a482890cb9d13e0

CONFIG="prod"
DO_REGEN=0
DO_RUN=0
DO_PACKAGE=1
NOPIN=0
JOBS="$(nproc 2>/dev/null || echo 4)"
VERSION=""
REPO="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$REPO/release-linux"

while [ $# -gt 0 ]; do
  case "$1" in
    --config) CONFIG="$2"; shift 2;;
    --prod) CONFIG="prod"; shift;;
    --debug) CONFIG="debug"; shift;;
    --regen) DO_REGEN=1; shift;;
    --run) DO_RUN=1; shift;;
    --no-package) DO_PACKAGE=0; shift;;
    --nopin) NOPIN=1; shift;;
    --out) OUT="$2"; shift 2;;
    --jobs) JOBS="$2"; shift 2;;
    --version) VERSION="$2"; shift 2;;
    -h|--help) sed -n '2,40p' "$0"; exit 0;;
    *) echo "unknown arg: $1" >&2; exit 2;;
  esac
done
case "$CONFIG" in prod) FLAGS=( "${PROD_CMAKE_FLAGS[@]}" );; debug) FLAGS=( "${DEBUG_CMAKE_FLAGS[@]}" );;
  *) echo "--config must be prod or debug (got '$CONFIG')" >&2; exit 2;; esac

if [ -z "$VERSION" ]; then
  VERSION="$(git -C "$REPO" describe --tags --exact-match 2>/dev/null | sed 's/^v//' || true)"
  [ -n "$VERSION" ] || VERSION="dev"
fi

# Point cmake at the HOST's Linux SDL2. Several game CMakeLists pin a bundled
# (Windows) SDL2 dev pack on CMAKE_PREFIX_PATH for the MSVC build; -DSDL2_DIR is
# the explicit CONFIG-mode hint and is consulted before CMAKE_PREFIX_PATH, so the
# real Linux .so links instead of a Windows import lib. Harmless when the game
# already finds system SDL2.
SDL2_CFG_DIR="$( { find /usr/lib /usr/lib64 /usr/local/lib -type d -path '*cmake/SDL2' 2>/dev/null || true; } | head -1 )"
[ -n "$SDL2_CFG_DIR" ] && FLAGS+=( -DSDL2_DIR="$SDL2_CFG_DIR" )

# Single cleanup hook: remove the AppDir scratch dir AND restore any .pin files
# the --nopin bypass moved aside (so a failed build never leaves the repo dirty).
WORK=""; PIN_BAK=""; RAN_PREBUILD=0
cleanup() {
  [ -n "$WORK" ] && rm -rf "$WORK"
  for p in $PIN_BAK; do [ -f "$p.nopin.bak" ] && mv -f "$p.nopin.bak" "$p"; done
  # Restore the repo's gen state (re-run POSTBUILD) even if the build failed.
  [ "$RAN_PREBUILD" = "1" ] && [ -n "$POSTBUILD_CMD" ] && { echo "[postbuild] $POSTBUILD_CMD"; eval "$POSTBUILD_CMD" || true; }
  return 0   # never let the trap's last test override the script's real exit code
}
trap cleanup EXIT

BUILD="$REPO/build-linux-$CONFIG"
echo "==================== $APP_NAME ($CONFIG) ===================="
cd "$REPO"

# Pin bypass (non-destructive): the per-game CMakeLists FATAL_ERRORs when the
# <framework>.pin SHA != framework HEAD. Release policy is to build against HEAD,
# so hide the pin for the duration; cleanup() restores it on exit either way.
if [ "$NOPIN" = "1" ]; then
  for p in "$REPO"/*.pin; do [ -f "$p" ] || continue; mv "$p" "$p.nopin.bak"; PIN_BAK="$PIN_BAK $p"; done
  [ -n "$PIN_BAK" ] && echo "      pin bypass: hid$PIN_BAK"
fi

if [ "$DO_REGEN" = "1" ] && [ -n "$REGEN_CMD" ]; then
  echo "[regen] $REGEN_CMD"
  eval "$REGEN_CMD"
fi

if [ -n "$PREBUILD_CMD" ]; then
  echo "[prebuild] $PREBUILD_CMD"
  RAN_PREBUILD=1
  eval "$PREBUILD_CMD"
fi

echo "[1/3] configure ($CONFIG: ${FLAGS[*]})"
cmake -S "$REPO" -B "$BUILD" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release "${FLAGS[@]}"
echo "[2/3] build ($CMAKE_TARGET, -j$JOBS)"
cmake --build "$BUILD" --target "$CMAKE_TARGET" -j"$JOBS"

# Locate the produced ELF by magic (the NTFS mount marks every file executable,
# so the exec bit is meaningless here).
BIN=""
while IFS= read -r f; do
  if [ "$(basename "$f")" = "$CMAKE_TARGET" ] && file -b "$f" 2>/dev/null | grep -q "ELF.*executable"; then BIN="$f"; break; fi
done < <(find "$BUILD" -maxdepth 3 -type f)
[ -n "$BIN" ] || { echo "ERROR: no ELF named '$CMAKE_TARGET' under $BUILD" >&2; exit 1; }
echo "      ELF: $BIN ($(du -h "$BIN" | cut -f1))"

if [ "$DO_PACKAGE" = "0" ]; then echo "      (--no-package) done."; exit 0; fi

echo "[3/4] package AppImage"
TOOLS_DIR="$BUILD/appimage-tools"
mkdir -p "$TOOLS_DIR"
fetch_tool() {
  local url="$1" sha="$2" dest="$3"
  if [ ! -f "$dest" ] || [ "$(sha256sum "$dest" | awk '{print $1}')" != "$sha" ]; then
    echo "      fetching $(basename "$dest")"
    curl -fL --retry 3 "$url" -o "$dest.tmp"
    printf '%s  %s\n' "$sha" "$dest.tmp" | sha256sum -c - >/dev/null
    mv "$dest.tmp" "$dest"
  fi
  chmod 0755 "$dest"
}
LINUXDEPLOY_BIN="$TOOLS_DIR/linuxdeploy-x86_64.AppImage"
APPIMAGETOOL_BIN="$TOOLS_DIR/appimagetool-x86_64.AppImage"
fetch_tool "$LINUXDEPLOY_URL" "$LINUXDEPLOY_SHA" "$LINUXDEPLOY_BIN"
fetch_tool "$APPIMAGETOOL_URL" "$APPIMAGETOOL_SHA" "$APPIMAGETOOL_BIN"
LINUXDEPLOY="$LINUXDEPLOY_BIN --appimage-extract-and-run"
APPIMAGETOOL="$APPIMAGETOOL_BIN --appimage-extract-and-run"
mkdir -p "$OUT"
EXE="$(basename "$BIN")"
SLUG="$(echo "$APP_NAME" | tr '[:upper:] ' '[:lower:]-' | tr -cd 'a-z0-9-')"
WORK="$(mktemp -d)"   # cleaned by the EXIT trap registered above
APPDIR="$WORK/AppDir"; mkdir -p "$APPDIR"

# Minimal 256x256 PNG icon (flat color from the slug; no image deps).
python3 - "$WORK/$SLUG.png" "$SLUG" <<'PY'
import sys, zlib, struct, hashlib
out, slug = sys.argv[1], sys.argv[2]
h = hashlib.md5(slug.encode()).digest()
r, g, b = h[0] | 0x30, h[1] | 0x30, h[2] | 0x30
N = 256; row = bytes([0]) + bytes([r, g, b]) * N; raw = row * N
def chunk(t, d):
    c = t + d
    return struct.pack(">I", len(d)) + c + struct.pack(">I", zlib.crc32(c) & 0xffffffff)
png = b"\x89PNG\r\n\x1a\n"
png += chunk(b"IHDR", struct.pack(">IIBBBBB", N, N, 8, 2, 0, 0, 0))
png += chunk(b"IDAT", zlib.compress(raw, 9)) + chunk(b"IEND", b"")
open(out, "wb").write(png)
PY

cat > "$WORK/$SLUG.desktop" <<EOF
[Desktop Entry]
Type=Application
Name=$APP_NAME
Exec=$EXE
Icon=$SLUG
Categories=Game;
Terminal=false
EOF

$LINUXDEPLOY --appdir "$APPDIR" --executable "$BIN" \
    --desktop-file "$WORK/$SLUG.desktop" --icon-file "$WORK/$SLUG.png"

BUILT_DIR="$(dirname "$BIN")"
[ -d "$BUILT_DIR/assets" ] || { echo "ERROR: launcher assets missing beside $BIN" >&2; exit 1; }
[ -x "$BUILT_DIR/falcon_owner_assets" ] || { echo "ERROR: Linux Falcon owner-ROM helper missing" >&2; exit 1; }
cp -r "$BUILT_DIR/assets" "$APPDIR/usr/bin/assets"
cp "$BUILT_DIR/falcon_owner_assets" "$APPDIR/usr/bin/falcon_owner_assets"
chmod 0755 "$APPDIR/usr/bin/falcon_owner_assets"

for manifest in "${REQUIRED_MOD_MANIFESTS[@]}"; do
  [ -f "$BUILT_DIR/mods/$manifest" ] || {
    echo "ERROR: built-in mod manifest missing: $manifest" >&2
    exit 1
  }
done
cp -r "$BUILT_DIR/mods" "$APPDIR/usr/bin/mods"

# Custom AppRun: bundle libs, read the controller natively on a Steam Deck, find
# the ROM next to the .AppImage, run from the ROM's folder so saves land there.
rm -f "$APPDIR/AppRun"   # linuxdeploy leaves it a symlink to the real exe
cat > "$APPDIR/AppRun" <<EOF
#!/bin/sh
HERE="\$(dirname "\$(readlink -f "\$0")")"
export LD_LIBRARY_PATH="\$HERE/usr/lib:\${LD_LIBRARY_PATH}"
# Steam Deck: read the built-in pad as a real gamepad instead of letting Steam's
# desktop layout retype it as keyboard (which otherwise sends Esc on B, etc.).
export SDL_JOYSTICK_HIDAPI_STEAM=1
export SDL_GAMECONTROLLER_ALLOW_STEAM_VIRTUAL_GAMEPAD=1
SELF="\${APPIMAGE:-\$0}"
ROMDIR="\$(dirname "\$(readlink -f "\$SELF")")"
ROM=""
for ext in $ROM_EXTS; do
    [ "\$ext" = "none" ] && break
    for f in "\$ROMDIR"/*."\$ext"; do [ -e "\$f" ] && ROM="\$f" && break 2; done
done
cd "\$ROMDIR" 2>/dev/null || true
# The engine anchors mod state beside the AppImage. Refresh only the pristine
# release-owned manifests; user packages and state.toml are never in the
# read-only payload and are not removed or replaced wholesale.
if [ -d "\$HERE/usr/bin/mods" ] && [ -w "\$ROMDIR" ]; then
    mkdir -p "\$ROMDIR/mods" 2>/dev/null || true
    cp -a "\$HERE/usr/bin/mods/." "\$ROMDIR/mods/" 2>/dev/null || true
    chmod -R u+rwX "\$ROMDIR/mods" 2>/dev/null || true
fi
# Seed the SMB ROM cache without passing a positional ROM. A positional ROM
# skips the launcher, which would make the Mods screen and SSB64 picker
# unreachable on first launch.
if [ -n "\$ROM" ]; then
    cached=""
    [ -f "\$ROMDIR/rom.cfg" ] && cached="\$(head -n1 "\$ROMDIR/rom.cfg" 2>/dev/null | tr -d '\r\n')"
    if [ -z "\$cached" ] || [ ! -f "\$cached" ]; then
        [ -w "\$ROMDIR" ] && printf '%s\n' "\$ROM" > "\$ROMDIR/rom.cfg" 2>/dev/null || true
    fi
fi
if [ "\$#" -eq 0 ]; then
    exec "\$HERE/usr/bin/$EXE" $EXTRA_ARGS
fi
exec "\$HERE/usr/bin/$EXE" "\$@"
EOF
chmod +x "$APPDIR/AppRun"

APP="$OUT/$RELEASE_SLUG-linux-$VERSION-x86_64.AppImage"
rm -f "$APP"
ARCH=x86_64 $APPIMAGETOOL "$APPDIR" "$APP"
chmod +x "$APP"
echo "      BUILT: $APP ($(du -h "$APP" | cut -f1))"

echo "[4/4] layout and payload test"
bash "$REPO/tools/test_appimage_layout.sh" "$APPDIR"

if [ "$DO_RUN" = "1" ]; then echo "[run] $APP"; "$APP" || true; fi
