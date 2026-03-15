cmake_minimum_required(VERSION 3.20)
project(SuperMarioBrosRecomp C)

set(CMAKE_C_STANDARD 11)

set(NESRECOMP_ROOT ${CMAKE_SOURCE_DIR}/nesrecomp)
include(${NESRECOMP_ROOT}/runner/runner.cmake)

list(APPEND CMAKE_PREFIX_PATH "${NESRECOMP_ROOT}/runner/external/SDL2/cmake")
find_package(SDL2 REQUIRED)

add_executable(SuperMarioBrosRecomp
    ${NESRECOMP_RUNNER_SOURCES}
    extras.c
    generated/super-mario-bros_full.c
    generated/super-mario-bros_dispatch.c
)

target_include_directories(SuperMarioBrosRecomp PRIVATE
    ${NESRECOMP_RUNNER_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(SuperMarioBrosRecomp PRIVATE ${SDL2_LIBRARIES})

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
