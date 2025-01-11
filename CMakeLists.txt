cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(game VERSION 1.0)

option(ENABLE_CLANG_TIDY "Enable clang-tidy for static analysis" OFF)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Using ccache: ${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_PROGRAM clang-tidy)
    if(CLANG_TIDY_PROGRAM)
        message(STATUS "Using clang-tidy: ${CLANG_TIDY_PROGRAM}")
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_PROGRAM};-header-filter=.*")
        set(USE_PCH OFF)
    else()
        message(WARNING "clang-tidy not found, ignoring ENABLE_CLANG_TIDY option.")
    endif()
else()
    set(USE_PCH ON)
endif()

set(SOURCE_PATH "${CMAKE_SOURCE_DIR}/example")
set(LIBRARY_PATH "${CMAKE_SOURCE_DIR}/lucid")
set(LIB_PCH_PATH "${LIBRARY_PATH}/common")
set(LIB_PCH_HEADER "${LIB_PCH_PATH}/LIB_PCH.hpp")

include_directories("${LIB_PCH_PATH}")

file(GLOB_RECURSE SOURCE_FILES "${SOURCE_PATH}/*.cpp")

add_library(lucidscript STATIC "${LIBRARY_PATH}/source/Lucid.cpp")
target_include_directories(lucidscript PUBLIC "${LIBRARY_PATH}/include")
target_compile_options(lucidscript PRIVATE -Werror -Wextra)

add_executable(game "${SOURCE_FILES}")
target_link_libraries(game PRIVATE lucidscript)

set_target_properties(game PROPERTIES UNITY_BUILD ON)
set_target_properties(lucidscript PROPERTIES UNITY_BUILD ON)

message(STATUS "Detected operating system: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Current build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -march=native -flto -fomit-frame-pointer -funroll-loops")

target_include_directories(game PRIVATE "${LIBRARY_PATH}/include")

target_compile_options(game PRIVATE -Werror -Wextra)

if (USE_PCH)
    target_precompile_headers(lucidscript PRIVATE "${LIB_PCH_HEADER}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)