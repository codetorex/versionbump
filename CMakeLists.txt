cmake_minimum_required(VERSION 3.3)
project(versionbump)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -fno-exceptions -s -fno-rtti -fvtable-gc  -fno-stack-protector -fno-ident -ffast-math")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")

set(SOURCE_FILES src/main.c)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(versionbump ${SOURCE_FILES})