#!/usr/bin/env bash
# Title policy only; platform orchestration belongs to the pinned engine.
set -euo pipefail
REPO="$(cd "$(dirname "$0")/.." && pwd)"
NES_ENGINE="${NESRECOMP_ROOT:-$REPO/nesrecomp}"
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
  "packages/super-mario-bros.gameplay.free-backtracking/1.0.0/manifest.toml"
  "packages/super-mario-bros.gameplay.metroid-samus-player-replacement/1.0.0/manifest.toml"
  "packages/super-mario-bros.gameplay.s3k-sonic-player-replacement/1.0.0/manifest.toml"
  "packages/super-mario-bros.gameplay.simultaneous-coop/1.0.0/manifest.toml"
  "packages/super-mario-bros.gameplay.smash64-player-replacement/1.0.0/manifest.toml"
  "packages/super-mario-bros.gameplay.zelda2-link-player-replacement/1.0.0/manifest.toml"
)
nes_platform_stage() {
    local destination="$1" BUILT_DIR="$2"
[ -x "$BUILT_DIR/falcon_owner_assets" ] || { echo "ERROR: Linux Falcon owner-ROM helper missing" >&2; exit 1; }
[ -x "$BUILT_DIR/smb_hdpack_importer" ] || { echo "ERROR: HD Mod importer missing" >&2; exit 1; }
mkdir -p "$destination/assets"
(
  shopt -s dotglob nullglob
  for asset in "$BUILT_DIR/assets/"*; do
    if [[ ${asset##*/} == shaders ]]; then continue; fi
    cp -r -- "$asset" "$destination/assets/"
  done
)
if [ -n "$SHADER_PRESET_DIR" ]; then
  cp -r -- "$SHADER_PRESET_DIR" "$destination/assets/shaders"
fi
cp "$BUILT_DIR/falcon_owner_assets" "$destination/falcon_owner_assets"
chmod 0755 "$destination/falcon_owner_assets"
cp "$BUILT_DIR/smb_hdpack_importer" "$destination/smb_hdpack_importer"
chmod 0755 "$destination/smb_hdpack_importer"
mkdir -p "$destination/THIRD-PARTY-LICENSES" "$destination/third_party/ymfm"
cp "$REPO/THIRD-PARTY-LICENSES/README.md" "$destination/THIRD-PARTY-LICENSES/README.md"
cp "$REPO/third_party/ymfm/LICENSE" "$destination/third_party/ymfm/LICENSE"

# Keep the component and font notices with the exact packaged assets.
ENGINE_SOURCE="${NESRECOMP_ROOT:-$REPO/nesrecomp}"
UI_SOURCE="${NESRECOMP_RECOMP_UI:-$REPO/recomp-ui}"
mkdir -p "$destination/licenses"
cp "$REPO/LICENSE" "$destination/licenses/Game-LICENSE.txt"
cp "$REPO/PERMISSIONS.md" "$destination/licenses/Game-PERMISSIONS.md"
cp "$ENGINE_SOURCE/LICENSE" "$destination/licenses/NESRecomp-LICENSE.txt"
cp "$ENGINE_SOURCE/runner/external/SDL2/COPYING.txt" "$destination/licenses/SDL2-COPYING.txt"
cp "$UI_SOURCE/LICENSE" "$destination/licenses/RecompUI-LICENSE.txt"
cp "$UI_SOURCE/src/third_party/imgui/LICENSE.txt" "$destination/licenses/ImGui-LICENSE.txt"
cp "$ENGINE_SOURCE/lib/recomp-net/LICENSE" "$destination/licenses/RecompNet-LICENSE.txt"
cp "$ENGINE_SOURCE/lib/retcomm-rbengine/LICENSE" "$destination/licenses/RBEngine-LICENSE.txt"
for notice in LatoLatin-OFL.txt NotoSansSymbols2-OFL.txt OpenMoji-LICENSE.txt; do
  cp "$REPO/tools/release-licenses/$notice" "$destination/licenses/$notice"
done

for manifest in "${REQUIRED_MOD_MANIFESTS[@]}"; do
  [ -f "$BUILT_DIR/mods/$manifest" ] || {
    echo "ERROR: built-in mod manifest missing: $manifest" >&2
    exit 1
  }
done


}
nes_platform_verify() { bash "$REPO/tools/test_appimage_layout.sh" "$1"; }
source "$NES_ENGINE/tools/build_cycle_linux.sh" "$@"
