cmake_minimum_required(VERSION 3.16)
project(pikachu_bridge_test C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(pikachu_bridge_test
    pikachu_bridge_test.c
    ../../mods/smash64/characters/pikachu.c
    ../../mods/smash64/ssb_ported/pikachu_locomotion.c)
target_include_directories(pikachu_bridge_test PRIVATE
    ../..
    ../../nesrecomp/runner/include)
if(NOT MSVC)
    target_link_libraries(pikachu_bridge_test m)
endif()

enable_testing()
add_test(NAME pikachu_bridge COMMAND pikachu_bridge_test)
