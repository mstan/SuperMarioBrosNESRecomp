cmake_minimum_required(VERSION 3.20)
project(SuperMarioBrosRecomp C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(NESRECOMP_ROOT "${CMAKE_SOURCE_DIR}/nesrecomp" CACHE PATH "NESRecomp engine checkout")

# nesrecomp/ and recomp-ui/ are git submodules (see .gitmodules); the pinned
# commit is the gitlink recorded in this repo. After cloning run setup.sh/.bat
# (git submodule update --init) to fetch them at the recorded commits.

set(NESRECOMP_ENABLE_MODS ON CACHE BOOL
    "Enable package mods for Super Mario Bros." FORCE)
set(NESRECOMP_BACKEND "cycle" CACHE STRING "CPU backend: cycle or legacy")
set_property(CACHE NESRECOMP_BACKEND PROPERTY STRINGS cycle legacy)
if(NESRECOMP_BACKEND STREQUAL "cycle")
    set(NESRECOMP_ROM "" CACHE FILEPATH "Original SMB1 World / USA ROM, not distributed")
    set(NESRECOMP_HOST_COMPILER "" CACHE FILEPATH "Optional prebuilt compiler")
    include("${NESRECOMP_ROOT}/runner/cyc/project.cmake")
    nesrecomp_add_cycle_game(SuperMarioBrosRecomp
        ROM "${NESRECOMP_ROM}" GAME_CONFIG "${CMAKE_CURRENT_SOURCE_DIR}/game-cycle.toml"
        RECOMPILER "${NESRECOMP_HOST_COMPILER}" SEED_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cyc_seeds.txt"
        MODS HD_PACKS GAME_ID "super-mario-bros-world" PLAYERS 4 REGION NTSC
        BOXART "${CMAKE_CURRENT_SOURCE_DIR}/boxart.tga"
        HOST_EXTRAS src/cycle_extras.c src/cycle_bridge.c src/cycle_calls.c
            src/game_coop.c
            mods/coop_plugin.c
            src/game_widescreen.c
            src/smb_ws_world.c
            src/smb_ws_actors.c
            src/game_voxel.c
            src/game_smash64.c
            src/game_smash64_actions.c
            src/game_smash64_fighter_profile.c
            src/game_smash64_audio.c
            src/game_smash64_assets.c
            src/game_smash64_render.c
            src/game_link.c
            src/game_link_audio.c
            src/game_samus.c
            src/game_samus_audio.c
            src/game_sonic.c
            src/game_sonic_adapter.c
            src/game_sonic_audio.c
            src/game_sonic_items.c
            mods/widescreen_plugin.c
            mods/voxel_plugin.c
            mods/smash64_player_plugin.c
            mods/zelda2_player_plugin.c
            mods/metroid_player_plugin.c
            mods/s3k_player_plugin.c
            mods/smash64_owner_assets.c
            mods/smash64/characters/captain_falcon.c
            mods/zelda2/link_controller.c
            mods/metroid/samus_controller.c
            mods/s3k/s3k_player.c
            mods/s3k/s3k_rings.c
            mods/s3k/sonic_controller.c
            mods/s3k/audio/z80.c
            mods/s3k/audio/sn76489.c
            mods/s3k/audio/s3k_sound_board.c
            mods/s3k/audio/ym2612_ymfm.cpp
            third_party/ymfm/ymfm_opn.cpp
            third_party/ymfm/ymfm_ssg.cpp
            third_party/ymfm/ymfm_adpcm.cpp
            mods/smash64/ssb_ported/falcon_locomotion.c
            mods/smash64/characters/pikachu.c
            mods/smash64/ssb_ported/pikachu_locomotion.c
            "${NESRECOMP_ROOT}/runner/cyc/cyc_presentation.c"
            "${NESRECOMP_ROOT}/runner/cyc/../src/voxel_renderer.c"
            "${NESRECOMP_ROOT}/runner/cyc/../src/voxel_screen_profile.c"
            "${NESRECOMP_ROOT}/runner/cyc/../src/keybinds.c"
            "${NESRECOMP_ROOT}/runner/cyc/../src/foreign_controller.c"
            "${NESRECOMP_ROOT}/runner/cyc/../src/mod_audio.c"
            "${NESRECOMP_ROOT}/runner/cyc/../src/rollback/nes_session_config.c"
)
    target_include_directories(SuperMarioBrosRecomp PRIVATE "${CMAKE_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/src" "${NESRECOMP_ROOT}/runner/include")
    target_compile_definitions(SuperMarioBrosRecomp PRIVATE SMB1_CYCLE NESRECOMP_CYCLE_PRESENTATION NESRECOMP_INPUT_SEATS=4 NESRECOMP_TRACE=1)
elseif(NESRECOMP_BACKEND STREQUAL "legacy")
include(${NESRECOMP_ROOT}/runner/runner.cmake)

list(APPEND CMAKE_PREFIX_PATH "${NESRECOMP_ROOT}/runner/external/SDL2/cmake")
find_package(SDL2 REQUIRED)

# ---- Main executable ----
add_executable(SuperMarioBrosRecomp
    ${NESRECOMP_RUNNER_SOURCES}
    src/extras.c
    src/game_coop.c
    mods/coop_plugin.c
    src/game_widescreen.c
    src/smb_ws_world.c
    src/smb_ws_actors.c
    src/game_voxel.c
    src/game_smash64.c
    src/game_smash64_actions.c
    src/game_smash64_fighter_profile.c
    src/game_smash64_audio.c
    src/game_smash64_assets.c
    src/game_smash64_render.c
    src/game_link.c
    src/game_link_audio.c
    src/game_samus.c
    src/game_samus_audio.c
    src/game_sonic.c
    src/game_sonic_adapter.c
    src/game_sonic_audio.c
    src/game_sonic_items.c
    mods/widescreen_plugin.c
    mods/voxel_plugin.c
    mods/smash64_player_plugin.c
    mods/zelda2_player_plugin.c
    mods/metroid_player_plugin.c
    mods/s3k_player_plugin.c
    mods/smash64_owner_assets.c
    mods/smash64/characters/captain_falcon.c
    mods/zelda2/link_controller.c
    mods/metroid/samus_controller.c
    mods/s3k/s3k_player.c
    mods/s3k/s3k_rings.c
    mods/s3k/sonic_controller.c
    mods/s3k/audio/z80.c
    mods/s3k/audio/sn76489.c
    mods/s3k/audio/s3k_sound_board.c
    mods/s3k/audio/ym2612_ymfm.cpp
    third_party/ymfm/ymfm_opn.cpp
    third_party/ymfm/ymfm_ssg.cpp
    third_party/ymfm/ymfm_adpcm.cpp
    mods/smash64/ssb_ported/falcon_locomotion.c
    mods/smash64/characters/pikachu.c
    mods/smash64/ssb_ported/pikachu_locomotion.c
    src/nes_snapshot.c
    src/verify_mode.c
    src/watchdog.c
    generated/super-mario-bros_full.c
    generated/super-mario-bros_dispatch.c
)

target_compile_definitions(SuperMarioBrosRecomp PRIVATE
    RECOMP_STACK_TRACKING WATCHDOG_ENABLED
    NESRECOMP_GAME_PLAYERS=4
    NESRECOMP_INPUT_SEATS=4
    NESRECOMP_GAME_ID="super-mario-bros-world"
    NESRECOMP_GAME_ROM_CRC32="d445f698"
    NESRECOMP_GAME_SDL_EVENT_HOOK=game_voxel_handle_event)

target_include_directories(SuperMarioBrosRecomp PRIVATE
    ${NESRECOMP_RUNNER_INCLUDE_DIRS}
    ${NESRECOMP_ROOT}/runner/src
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(SuperMarioBrosRecomp PRIVATE ${SDL2_LIBRARIES} ${NESRECOMP_RUNNER_LIBRARIES})

else()
    message(FATAL_ERROR "NESRECOMP_BACKEND must be cycle or legacy")
endif()

# The baker is publishable code; its inputs and output remain under the
# ignored assets_ssb64 quarantine. A checkout without those local assets
# simply omits this target and the runtime uses its cube fallback.
set(FALCON_ASSET_ROOT "${CMAKE_SOURCE_DIR}/assets_ssb64")
set(FALCON_RUNTIME_BLOB "${FALCON_ASSET_ROOT}/falcon_runtime.bin")
if(EXISTS "${FALCON_ASSET_ROOT}/model/captain_model.json")
    find_package(Python3 COMPONENTS Interpreter QUIET)
    if(Python3_Interpreter_FOUND)
        file(GLOB_RECURSE FALCON_ASSET_INPUTS CONFIGURE_DEPENDS
            "${FALCON_ASSET_ROOT}/model/*.json"
            "${FALCON_ASSET_ROOT}/textures/*.json"
            "${FALCON_ASSET_ROOT}/textures/*.bin"
            "${FALCON_ASSET_ROOT}/textures/*.png"
            "${FALCON_ASSET_ROOT}/anim/*.json"
            "${FALCON_ASSET_ROOT}/effects/*.bin")
        add_custom_command(
            OUTPUT "${FALCON_RUNTIME_BLOB}"
            COMMAND "${Python3_EXECUTABLE}"
                "${CMAKE_SOURCE_DIR}/tools/bake_falcon_runtime.py"
                "${FALCON_ASSET_ROOT}" "${FALCON_RUNTIME_BLOB}"
            DEPENDS
                "${CMAKE_SOURCE_DIR}/tools/bake_falcon_runtime.py"
                ${FALCON_ASSET_INPUTS}
            COMMENT "Baking local-only Captain Falcon runtime assets"
            VERBATIM)
        add_custom_target(falcon_runtime_assets DEPENDS "${FALCON_RUNTIME_BLOB}")
        add_dependencies(SuperMarioBrosRecomp falcon_runtime_assets)
    endif()
endif()

# Release-facing owner-ROM extractor. The executable contains only recipe
# code; it derives Falcon's cache from the launcher-verified owner ROM and no
# ROM or generated asset is staged beside the game.
option(NESRECOMP_REQUIRE_FALCON_OWNER_HELPER
    "Fail configuration unless the release Falcon owner-ROM helper can be built" OFF)
find_package(Python3 COMPONENTS Interpreter QUIET)
if(Python3_Interpreter_FOUND)
    execute_process(
        COMMAND "${Python3_EXECUTABLE}" -c "import PyInstaller; import PIL"
        RESULT_VARIABLE FALCON_PYINSTALLER_AVAILABLE
        OUTPUT_QUIET ERROR_QUIET)
    if(FALCON_PYINSTALLER_AVAILABLE EQUAL 0)
        file(GLOB FALCON_OWNER_HELPER_SOURCES CONFIGURE_DEPENDS
            "${CMAKE_SOURCE_DIR}/tools/owner_ssb64/*.py")
        set(FALCON_OWNER_HELPER_BUILD
            "${CMAKE_BINARY_DIR}/falcon_owner_helper_build")
        set(FALCON_OWNER_HELPER_DIST
            "${CMAKE_BINARY_DIR}/falcon_owner_helper_dist")
        set(FALCON_OWNER_HELPER_EXE
            "${FALCON_OWNER_HELPER_DIST}/falcon_owner_assets${CMAKE_EXECUTABLE_SUFFIX}")
        add_custom_command(
            OUTPUT "${FALCON_OWNER_HELPER_EXE}"
            COMMAND "${CMAKE_COMMAND}" -E make_directory
                "${FALCON_OWNER_HELPER_BUILD}" "${FALCON_OWNER_HELPER_DIST}"
            COMMAND "${Python3_EXECUTABLE}" -m PyInstaller
                --noconfirm --clean --onefile --exclude-module numpy
                --name falcon_owner_assets
                --distpath "${FALCON_OWNER_HELPER_DIST}"
                --workpath "${FALCON_OWNER_HELPER_BUILD}/work"
                --specpath "${FALCON_OWNER_HELPER_BUILD}"
                --paths "${CMAKE_SOURCE_DIR}/tools"
                --paths "${CMAKE_SOURCE_DIR}/tools/owner_ssb64"
                "${CMAKE_SOURCE_DIR}/tools/owner_ssb64/build_final_cache.py"
            DEPENDS
                "${CMAKE_SOURCE_DIR}/tools/bake_falcon_runtime.py"
                ${FALCON_OWNER_HELPER_SOURCES}
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            COMMENT "Packaging the Falcon owner-ROM cache helper"
            VERBATIM)
        add_custom_target(falcon_owner_assets_helper
            DEPENDS "${FALCON_OWNER_HELPER_EXE}")
        add_dependencies(SuperMarioBrosRecomp falcon_owner_assets_helper)
        add_custom_command(TARGET SuperMarioBrosRecomp POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                "${FALCON_OWNER_HELPER_EXE}"
                "$<TARGET_FILE_DIR:SuperMarioBrosRecomp>/falcon_owner_assets${CMAKE_EXECUTABLE_SUFFIX}")
    else()
        if(NESRECOMP_REQUIRE_FALCON_OWNER_HELPER)
            message(FATAL_ERROR
                "Release requires Python packages PyInstaller and Pillow for the Falcon owner-ROM helper")
        else()
            message(WARNING
                "PyInstaller/Pillow unavailable; Falcon owner-ROM helper will not be built")
        endif()
    endif()
elseif(NESRECOMP_REQUIRE_FALCON_OWNER_HELPER)
    message(FATAL_ERROR
        "Release requires Python 3 for the Falcon owner-ROM helper")
endif()

if(WIN32)
    target_link_libraries(SuperMarioBrosRecomp PRIVATE ws2_32 dbghelp)
endif()

# ---- Post-build ----
if(WIN32)
    add_custom_command(TARGET SuperMarioBrosRecomp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${NESRECOMP_ROOT}/runner/external/SDL2/lib/x64/SDL2.dll"
            "$<TARGET_FILE_DIR:SuperMarioBrosRecomp>"
    )
endif()

if(MSVC)
    target_compile_options(SuperMarioBrosRecomp PRIVATE /W3 /WX-)
    target_compile_options(SuperMarioBrosRecomp PRIVATE /wd4102)
endif()

# ---- Pre-boot GUI launcher (recomp-ui / Dear ImGui) ----
# recomp-ui/ is a pinned submodule. Its
# module defines RECOMP_LAUNCHER on the target, un-gating the launcher block in
# launcher.c's main(), and stages the launcher assets next to the exe.
if(NESRECOMP_BACKEND STREQUAL "legacy")
if(NESRECOMP_RECOMP_UI)
    set(RECOMP_UI_ROOT "${NESRECOMP_RECOMP_UI}" CACHE PATH "recomp-ui checkout" FORCE)
    include("${NESRECOMP_RECOMP_UI}/recomp_ui.cmake")
else()
    include(${CMAKE_SOURCE_DIR}/recomp-ui/recomp_ui.cmake)
endif()
recomp_target_launcher_ui(SuperMarioBrosRecomp
    CONSOLE nes
    BOXART ${CMAKE_SOURCE_DIR}/boxart.tga)

endif()

# ---- Online play: rollback netplay over recomp-net ----
# 2-4 player simultaneous co-op online (docs/NETPLAY.md). On by default for
# Linux builds; the Windows/macOS toolchains have not been verified with the
# rollback stack yet, so there it stays opt-in.
if(UNIX AND NOT APPLE)
    set(_smb_net_default ON)
else()
    set(_smb_net_default OFF)
endif()
option(SMB_ENABLE_NETPLAY "Build rollback netplay (recomp-net + recomp-ui lobby)"
    ${_smb_net_default})
if((SMB_ENABLE_NETPLAY OR NESRECOMP_ENABLE_NET) AND NESRECOMP_BACKEND STREQUAL "legacy")
    nesrecomp_enable_recomp_net(SuperMarioBrosRecomp)
elseif(SMB_ENABLE_NETPLAY OR NESRECOMP_ENABLE_NET)
    message(FATAL_ERROR "Cycle rollback netplay is being ported (beads-2dw.1.93). Use SMB_ENABLE_NETPLAY=OFF for the local cycle preview; requested online support is never silently omitted.")
endif()

add_custom_command(TARGET SuperMarioBrosRecomp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/mods/preloaded"
        "$<TARGET_FILE_DIR:SuperMarioBrosRecomp>/mods"
    COMMENT "Staging SMB's preloaded NES mod packages")
