cmake_minimum_required(VERSION 3.3)
project(versionbump)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wall -Wextra -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")

set(SOURCE_FILES src/main.cpp src/pathiterator.h)

include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("${CMAKE_SOURCE_DIR}/libs/rapidjson-1.0.2/include")
add_subdirectory("${CMAKE_SOURCE_DIR}/libs/rapidjson-1.0.2/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(versionbump ${SOURCE_FILES})