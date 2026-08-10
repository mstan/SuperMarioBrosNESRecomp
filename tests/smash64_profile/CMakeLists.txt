cmake_minimum_required(VERSION 3.20)
project(smash64_fighter_profile_test C)

set(CMAKE_C_STANDARD 11)
enable_testing()

add_executable(smash64_fighter_profile_test
    smash64_fighter_profile_test.c
    ../../game_smash64_fighter_profile.c)
target_include_directories(smash64_fighter_profile_test PRIVATE ../..)

add_test(NAME smash64_fighter_profile COMMAND smash64_fighter_profile_test)

