cmake_minimum_required(VERSION 3.20)
project(s3k_sound_harness C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
get_filename_component(GAME_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)

add_executable(s3k_sound_harness
    s3k_sound_harness.c
    ${GAME_ROOT}/mods/s3k/audio/z80.c
    ${GAME_ROOT}/mods/s3k/audio/sn76489.c
    ${GAME_ROOT}/mods/s3k/audio/s3k_sound_board.c
    ${GAME_ROOT}/mods/s3k/audio/ym2612_ymfm.cpp
    ${GAME_ROOT}/third_party/ymfm/ymfm_opn.cpp
    ${GAME_ROOT}/third_party/ymfm/ymfm_ssg.cpp
    ${GAME_ROOT}/third_party/ymfm/ymfm_adpcm.cpp)
target_include_directories(s3k_sound_harness PRIVATE ${GAME_ROOT})
if(MSVC)
    target_compile_definitions(s3k_sound_harness PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
