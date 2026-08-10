cmake_minimum_required(VERSION 3.20)
project(SamusControllerHarness C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(samus_controller_harness
    samus_controller_harness.c
    ../../mods/metroid/samus_controller.c
    ../../nesrecomp/runner/src/foreign_controller.c
    ../../nesrecomp/runner/src/mod_savestate.c
)
target_include_directories(samus_controller_harness PRIVATE
    ../..
    ../../nesrecomp/runner/include
)
if(NOT MSVC)
    target_link_libraries(samus_controller_harness m)
endif()

enable_testing()
add_test(NAME samus_controller COMMAND samus_controller_harness)
