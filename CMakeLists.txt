cmake_minimum_required(VERSION 3.3)
project(versionbump)

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -s -Doff64_t=_off64_t")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -s")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s")

set(SOURCE_FILES src/main.c src/array.c src/array.h)

# include_directories("${CMAKE_SOURCE_DIR}/libs/jansson/src")
include_directories("${CMAKE_SOURCE_DIR}/src")
include_directories("${CMAKE_BINARY_DIR}/libs/jansson/include")
add_subdirectory("${CMAKE_SOURCE_DIR}/libs/jansson/")

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(versionbump ${SOURCE_FILES})
target_link_libraries (versionbump jansson)
add_dependencies(versionbump jansson)