cmake_minimum_required(VERSION 3.20)
project(SuperMarioBrosRecomp C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(NESRECOMP_ROOT ${CMAKE_SOURCE_DIR}/nesrecomp)

# Super Mario Bros. is the first two-player delay-sync netplay title. ICE is
# enabled for Internet lobbies; recomp-net also retains its direct LAN path.
set(NESRECOMP_NET_ICE ON CACHE BOOL "" FORCE)

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
    mods/voxel_plugin.c
    nes_snapshot.c
    verify_mode.c
    watchdog.c
    generated/super-mario-bros_full.c
    generated/super-mario-bros_dispatch.c
)

target_compile_definitions(SuperMarioBrosRecomp PRIVATE
    RECOMP_STACK_TRACKING WATCHDOG_ENABLED
    NESRECOMP_GAME_PLAYERS=2
    NESRECOMP_GAME_VERSION="smb-netplay-v1"
    NESRECOMP_GAME_ID="super-mario-bros-world"
    NESRECOMP_GAME_ROM_CRC32="d445f698"
    NESRECOMP_GAME_SDL_EVENT_HOOK=game_voxel_handle_event)

target_include_directories(SuperMarioBrosRecomp PRIVATE
    ${NESRECOMP_RUNNER_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(SuperMarioBrosRecomp PRIVATE ${SDL2_LIBRARIES})
nesrecomp_enable_recomp_net(SuperMarioBrosRecomp)

if(WIN32)
    target_link_libraries(SuperMarioBrosRecomp PRIVATE ws2_32)
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
target_compile_definitions(SuperMarioBrosRecomp PRIVATE NESRECOMP_GAME_WIDESCREEN=1)
