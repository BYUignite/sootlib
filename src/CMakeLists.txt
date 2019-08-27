cmake_minimum_required(VERSION 3.12)
project(sootlib LANGUAGES CXX C)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)      # Release or Debug
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_library(sootlib "")
target_include_directories(sootlib PRIVATE .)

find_package(Boost REQUIRED COMPONENTS system)
target_include_directories(sootlib PRIVATE ${Boost_INCLUDE_DIRS})

#################### Compile options

target_compile_features(sootlib PUBLIC cxx_std_11)

set(CMAKE_CXX_FLAGS_DEBUG   "-ggdb3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
#set(CMAKE_CXX_FLAGS        "-Wall -Wextra")

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_link_libraries(sootlib "-framework Accelerate")
endif()

#################### Local source files

target_sources(sootlib
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/pdgen.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/wheeler.cc
        ${CMAKE_CURRENT_SOURCE_DIR}/soot.cc          ${CMAKE_CURRENT_SOURCE_DIR}/soot.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soot_MONO.cc     ${CMAKE_CURRENT_SOURCE_DIR}/soot_MONO.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soot_QMOM.cc     ${CMAKE_CURRENT_SOURCE_DIR}/soot_QMOM.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soot_MOMIC.cc    ${CMAKE_CURRENT_SOURCE_DIR}/soot_MOMIC.h
        ${CMAKE_CURRENT_SOURCE_DIR}/soot_LOGN.cc     ${CMAKE_CURRENT_SOURCE_DIR}/soot_LOGN.h
        ${CMAKE_CURRENT_SOURCE_DIR}/eispack.cc       ${CMAKE_CURRENT_SOURCE_DIR}/eispack.h
)

#CQMOM.cc
#dv_soot_CQMOM.cc
#wheeler_ARCHES.cc
#vandermonde.cc
#dv_soot_CQMOM.h
