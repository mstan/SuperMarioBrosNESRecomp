cmake_minimum_required(VERSION 3.20)
project(SuperMarioBrosRecomp C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(NESRECOMP_ROOT ${CMAKE_SOURCE_DIR}/nesrecomp)

# nesrecomp/ and recomp-ui/ are git submodules (see .gitmodules); the pinned
# commit is the gitlink recorded in this repo. After cloning run setup.sh/.bat
# (git submodule update --init) to fetch them at the recorded commits.

set(NESRECOMP_ENABLE_MODS ON CACHE BOOL
    "Enable package mods for Super Mario Bros." FORCE)
include(${NESRECOMP_ROOT}/runner/runner.cmake)

list(APPEND CMAKE_PREFIX_PATH "${NESRECOMP_ROOT}/runner/external/SDL2/cmake")
find_package(SDL2 REQUIRED)

# ---- Main executable ----
add_executable(SuperMarioBrosRecomp
    ${NESRECOMP_RUNNER_SOURCES}
    extras.c
    game_voxel.c
    game_smash64.c
    game_smash64_audio.c
    game_smash64_assets.c
    game_smash64_render.c
    game_samus.c
    game_samus_audio.c
    mods/widescreen_plugin.c
    mods/voxel_plugin.c
    mods/smash64_player_plugin.c
    mods/metroid_player_plugin.c
    mods/smash64_owner_assets.c
    mods/smash64/characters/captain_falcon.c
    mods/metroid/samus_controller.c
    mods/smash64/ssb_ported/falcon_locomotion.c
    nes_snapshot.c
    verify_mode.c
    watchdog.c
    generated/super-mario-bros_full.c
    generated/super-mario-bros_dispatch.c
)

target_compile_definitions(SuperMarioBrosRecomp PRIVATE
    RECOMP_STACK_TRACKING WATCHDOG_ENABLED
    NESRECOMP_GAME_PLAYERS=2
    NESRECOMP_GAME_ID="super-mario-bros-world"
    NESRECOMP_GAME_ROM_CRC32="d445f698"
    NESRECOMP_GAME_SDL_EVENT_HOOK=game_voxel_handle_event)

target_include_directories(SuperMarioBrosRecomp PRIVATE
    ${NESRECOMP_RUNNER_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(SuperMarioBrosRecomp PRIVATE ${SDL2_LIBRARIES})

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
if(WIN32)
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
                "${FALCON_OWNER_HELPER_DIST}/falcon_owner_assets.exe")
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
                    "$<TARGET_FILE_DIR:SuperMarioBrosRecomp>/falcon_owner_assets.exe")
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
# recomp-ui/ is a directory junction -> the shared recomp-ui checkout. Its
# module defines RECOMP_LAUNCHER on the target, un-gating the launcher block in
# launcher.c's main(), and stages the launcher assets next to the exe.
include(${CMAKE_SOURCE_DIR}/recomp-ui/recomp_ui.cmake)
recomp_target_launcher_ui(SuperMarioBrosRecomp
    CONSOLE nes
    BOXART ${CMAKE_SOURCE_DIR}/boxart.tga)

add_custom_command(TARGET SuperMarioBrosRecomp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/mods/preloaded"
        "$<TARGET_FILE_DIR:SuperMarioBrosRecomp>/mods"
    COMMENT "Staging SMB's preloaded NES mod packages")
