cmake_minimum_required(VERSION 3.20)
project(SonicControllerHarness C)

set(CMAKE_C_STANDARD 11)

add_executable(sonic_controller_harness
    sonic_controller_harness.c
    ../../mods/s3k/sonic_controller.c
    ../../nesrecomp/runner/src/foreign_controller.c
    ../../nesrecomp/runner/src/mod_savestate.c)

target_include_directories(sonic_controller_harness PRIVATE
    ../..
    ../../nesrecomp/runner/include)
