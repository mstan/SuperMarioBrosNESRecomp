# Deterministic trace harness for the ported Captain Falcon locomotion.
#
# Standalone on purpose: no SDL, no nesrecomp runner, no generated 6502. It
# links only the ported state machine, so a failure here is unambiguously the
# controller and not the SMB1 adapter.
#
#   cmake -S tests/falcon_harness -B build_harness
#   cmake --build build_harness --config Release
#   ctest --test-dir build_harness -C Release
cmake_minimum_required(VERSION 3.20)
project(FalconHarness C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(falcon_harness
    falcon_harness.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../mods/smash64/ssb_ported/falcon_locomotion.c
)

add_executable(mod_audio_test
    mod_audio_test.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../../nesrecomp/runner/src/mod_audio.c
)
target_include_directories(mod_audio_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../nesrecomp/runner/include)

if(MSVC)
    target_compile_definitions(falcon_harness PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_options(falcon_harness PRIVATE /W4)
else()
    target_compile_options(falcon_harness PRIVATE -Wall -Wextra)
    target_link_libraries(falcon_harness m)
endif()

# Each script carries its own expect_state assertions and exits non-zero on
# failure, so running them IS the test.
enable_testing()
foreach(trace run_right dash_turn jump fast_fall short_hop
              host_launch host_ledge_fall jump_height_split
              host_impulse combat downb_transitions upb audio)
    add_test(NAME falcon_${trace}
             COMMAND falcon_harness
                     ${CMAKE_CURRENT_SOURCE_DIR}/${trace}.script
                     --csv ${CMAKE_CURRENT_BINARY_DIR}/trace_${trace}.csv)
endforeach()

add_test(NAME mod_audio COMMAND mod_audio_test)

