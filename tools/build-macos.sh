#!/usr/bin/env bash
# Title policy only; platform orchestration belongs to the pinned engine.
set -euo pipefail
REPO="$(cd "$(dirname "$0")/.." && pwd)"
NES_ENGINE="${NESRECOMP_ROOT:-$REPO/nesrecomp}"
APP_NAME="SuperMarioBros"
CMAKE_TARGET="SuperMarioBrosRecomp"
ROM_EXTS="nes"
EXTRA_ARGS=""
REGEN_CMD=""
PREBUILD_CMD=""
POSTBUILD_CMD=""
PROD_CMAKE_FLAGS=( -DNESRECOMP_ENABLE_TRACE=OFF -DNESRECOMP_REQUIRE_FALCON_OWNER_HELPER=ON )
DEBUG_CMAKE_FLAGS=( -DNESRECOMP_ENABLE_TRACE=ON )
BUNDLE_ID="com.mstan.supermariobrosrecomp"
nes_platform_stage() {
    local destination="$1" BUILT_DIR="$2"
    for helper in falcon_owner_assets smb_hdpack_importer; do
        [ -x "$BUILT_DIR/$helper" ] || { echo "Missing $helper" >&2; exit 1; }
        cp "$BUILT_DIR/$helper" "$destination/$helper"
    done
}
source "$NES_ENGINE/tools/build_cycle_macos.sh" "$@"
