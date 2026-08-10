cmake_minimum_required(VERSION 3.20)
project(PikachuHarness C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_executable(pikachu_harness
    pikachu_harness.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../mods/smash64/ssb_ported/pikachu_locomotion.c)
if(MSVC)
    target_compile_definitions(pikachu_harness PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_options(pikachu_harness PRIVATE /W4 /WX)
else()
    target_compile_options(pikachu_harness PRIVATE -Wall -Wextra -Werror)
    target_link_libraries(pikachu_harness PRIVATE m)
endif()
enable_testing()
add_test(NAME pikachu_behavior_vectors COMMAND pikachu_harness)
