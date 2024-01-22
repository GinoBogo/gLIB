cmake_minimum_required(VERSION 3.17)

set(COMPILER "clang")

if (COMPILER STREQUAL "clang")
    if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
        set(CMAKE_C_COMPILER "clang.exe")
        set(CMAKE_CXX_COMPILER "clang++.exe")
    else()
        set(CMAKE_C_COMPILER "clang")
        set(CMAKE_CXX_COMPILER "clang++")
    endif()

    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        add_compile_options(-fstandalone-debug)
    endif()
else()
    if (${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
        set(CMAKE_C_COMPILER "gcc.exe")
        set(CMAKE_CXX_COMPILER "g++.exe")
    else()
        set(CMAKE_C_COMPILER "gcc")
        set(CMAKE_CXX_COMPILER "g++")
    endif()
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("================================================================================")
message("   OS: " ${CMAKE_HOST_SYSTEM_NAME})
message("  DIR: " ${CMAKE_SOURCE_DIR})
message(" TYPE: " ${CMAKE_BUILD_TYPE})
message("================================================================================")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(benchmark)

add_compile_options(
    -fno-omit-frame-pointer
    -pedantic
    -Wall
    -Wcast-align
    -Wextra
    -Wfloat-equal
   #-Wno-unused-parameter
    -Wshadow
    -Wsign-conversion
    -Wswitch-default
)

if (COMPILE_LANGUAGE:CXX)
    add_compile_options(-Wold-style-cast)
endif()

include_directories("/usr/local/include")
link_directories("/usr/local/lib")

add_executable(BM_aligned_memory
BM_aligned_memory.cpp
)
target_link_libraries(BM_aligned_memory benchmark)

add_executable(BM_if_else_vs_array
BM_if_else_vs_array.cpp
)
target_link_libraries(BM_if_else_vs_array benchmark)

add_executable(BM_snprintf_vs_strcpy
BM_snprintf_vs_strcpy.cpp
)
target_link_libraries(BM_snprintf_vs_strcpy benchmark)

add_executable(BM_ofstream_vs_fwrite
BM_ofstream_vs_fwrite.cpp
)
target_link_libraries(BM_ofstream_vs_fwrite benchmark)
