cmake_minimum_required(VERSION 3.16)
project(Smash64ActionsTest C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_executable(smash64_actions_test
    smash64_actions_test.c
    ../../game_smash64_actions.c)
target_include_directories(smash64_actions_test PRIVATE
    ../..
    ../../nesrecomp/runner/include)
if(NOT MSVC)
    target_link_libraries(smash64_actions_test m)
endif()
enable_testing()
add_test(NAME smash64_actions COMMAND smash64_actions_test)
