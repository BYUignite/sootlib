cmake_minimum_required(VERSION 3.15)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)       # Release or Debug
endif()

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")

project(sootlib
        VERSION 1.0
        LANGUAGES CXX)

############################### PROJECT OPTIONS ###############################

option(BUILD_TESTS "Build sootlib tests" ON)        # option to build tests
option(BUILD_EXAMPLES "Build sootlib example" ON)   # option to build examples

############################### SOOTLIB ###############################

add_subdirectory(src ${CMAKE_CURRENT_BINARY_DIR}/src)

# ---- allow sootlib to be used in other targets ----
target_include_directories(sootlib PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include>"
        )

################## TESTS ###############################

if (BUILD_TESTS)
    add_subdirectory(test ${CMAKE_CURRENT_BINARY_DIR}/test)
endif()

################## EXAMPLES ###############################

if (BUILD_EXAMPLES)
    add_subdirectory(examples ${CMAKE_CURRENT_BINARY_DIR}/examples)
endif()
