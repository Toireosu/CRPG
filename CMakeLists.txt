cmake_minimum_required(VERSION 3.20)
project(Falloff C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)

FetchContent_Declare(
    klib
    GIT_REPOSITORY https://github.com/attractivechaos/klib
    GIT_TAG master
)
    
FetchContent_MakeAvailable(raylib)
    
FetchContent_MakeAvailable(klib)

add_library(klib INTERFACE)

target_include_directories(klib INTERFACE ${klib_SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    src/*.c
)

add_executable(Falloff ${SOURCES})
target_include_directories(Falloff PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(Falloff raylib klib)

