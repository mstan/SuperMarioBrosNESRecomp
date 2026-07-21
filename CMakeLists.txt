cmake_minimum_required(VERSION 3.20)
project(SuperMarioBrosRecomp C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(NESRECOMP_ROOT ${CMAKE_SOURCE_DIR}/nesrecomp)

# nesrecomp/ and recomp-ui/ are git submodules (see .gitmodules); the pinned
# commit is the gitlink recorded in this repo. After cloning run setup.sh/.bat
# (git submodule update --init) to fetch them at the recorded commits.

# ---- Nestopia Oracle (optional) ----
option(ENABLE_NESTOPIA_ORACLE "Build with Nestopia emulator oracle for verify mode" ON)
if(ENABLE_NESTOPIA_ORACLE)
    set(NESTOPIA_DIR ${CMAKE_SOURCE_DIR}/nestopia-core)
endif()

# ---- Reverse debugger (Tier 1+, optional) ----
# When ON, runner.cmake adds reverse_debug.c and this file sets
# NESRECOMP_REVERSE_DEBUG=1 on the target. You MUST regenerate the
# recompiled C with `NESRecomp.exe <rom> --game game.toml --reverse-debug`
# before building, or the generated stores will still call nes_write
# directly and the ring will remain empty. See REVERSE_DEBUGGER.md.
option(NESRECOMP_REVERSE_DEBUG "Build Tier-1+ reverse debugger hooks (requires regen with --reverse-debug)" OFF)

include(${NESRECOMP_ROOT}/runner/runner.cmake)

list(APPEND CMAKE_PREFIX_PATH "${NESRECOMP_ROOT}/runner/external/SDL2/cmake")
find_package(SDL2 REQUIRED)

# ---- Main executable ----
add_executable(SuperMarioBrosRecomp
    ${NESRECOMP_RUNNER_SOURCES}
    extras.c
    nes_snapshot.c
    verify_mode.c
    watchdog.c
    generated/super-mario-bros_full.c
    generated/super-mario-bros_dispatch.c
)

target_compile_definitions(SuperMarioBrosRecomp PRIVATE RECOMP_STACK_TRACKING WATCHDOG_ENABLED)

if(NESRECOMP_REVERSE_DEBUG)
    target_compile_definitions(SuperMarioBrosRecomp PRIVATE NESRECOMP_REVERSE_DEBUG=1)
    message(STATUS "Reverse debugger: ON (must have regenerated with --reverse-debug)")
endif()

target_include_directories(SuperMarioBrosRecomp PRIVATE
    ${NESRECOMP_RUNNER_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(SuperMarioBrosRecomp PRIVATE ${SDL2_LIBRARIES})

if(WIN32)
    target_link_libraries(SuperMarioBrosRecomp PRIVATE ws2_32)
endif()

# ---- Nestopia Oracle integration ----
if(ENABLE_NESTOPIA_ORACLE)
    target_link_libraries(SuperMarioBrosRecomp PRIVATE nestopia_core)
    target_compile_definitions(SuperMarioBrosRecomp PRIVATE ENABLE_NESTOPIA_ORACLE)
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
recomp_target_launcher_ui(SuperMarioBrosRecomp BOXART ${CMAKE_SOURCE_DIR}/boxart.tga)
target_compile_definitions(SuperMarioBrosRecomp PRIVATE NESRECOMP_GAME_WIDESCREEN=1)
