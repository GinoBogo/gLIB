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

    if (${CMAKE_BUILD_TYPE} STREQUAL "debug")
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

message("================================================================================")
message("   OS: " ${CMAKE_HOST_SYSTEM_NAME})
message("  DIR: " ${CMAKE_SOURCE_DIR})
message(" TYPE: " ${CMAKE_BUILD_TYPE})
message("================================================================================")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(test)

add_compile_options(
    -fno-omit-frame-pointer
    -pedantic
    -Wall
    -Wcast-align
    -Wextra
    -Wfloat-equal
   #-Wno-unused-parameter
   #-Wno-unused-variable
    -Wshadow
    -Wsign-conversion
    -Wswitch-default
)

if (COMPILE_LANGUAGE:CXX)
    add_compile_options(-Wold-style-cast)
endif()

find_library(LIB_FMT fmt)

add_library(gLIB OBJECT
../src/GBuffer.cpp
../src/GFifo.cpp
../src/GFilePipe.cpp
../src/GLogger.cpp
../src/GPingPong.cpp
../src/GThreadPriority.cpp
)

include_directories(../src /usr/local/include)

add_executable(test_GPingPong test_GPingPong.cpp)
target_link_libraries(test_GPingPong pthread ${LIB_FMT} gLIB)

add_executable(test_GMeasure test_GMeasure.cpp)
target_link_libraries(test_GMeasure pthread ${LIB_FMT} gLIB)

add_executable(test_GFilePipe test_GFilePipe.cpp)
target_link_libraries(test_GFilePipe pthread ${LIB_FMT} gLIB)
