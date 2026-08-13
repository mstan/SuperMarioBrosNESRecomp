cmake_minimum_required(VERSION 3.20)
project(LinkControllerHarness C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(link_controller_harness
    link_controller_harness.c
    ../../mods/zelda2/link_controller.c
    ../../nesrecomp/runner/src/foreign_controller.c
    ../../nesrecomp/runner/src/mod_savestate.c
)
target_include_directories(link_controller_harness PRIVATE
    ../..
    ../../nesrecomp/runner/include
)
if(NOT MSVC)
    target_link_libraries(link_controller_harness m)
endif()

enable_testing()
add_test(NAME link_controller COMMAND $<TARGET_FILE:link_controller_harness>)
