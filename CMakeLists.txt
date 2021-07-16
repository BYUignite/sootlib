cmake_minimum_required(VERSION 3.15)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)       # Release or Debug
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")

include(FetchContent)

#################### PROJECT OPTIONS ###############################

# ---- set installation location ----
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/installed" CACHE STRING "installation location")

# ---- options to build examples ----
option(BUILD_EXAMPLES "Build sootlib examples" OFF)

# ---- options to build tests -------
option(BUILD_TESTING "Build sootlib tests" ON)

####################### SOOTLIB ###############################

project(sootlib
        VERSION 1.0
        LANGUAGES CXX)

add_subdirectory(src ${CMAKE_CURRENT_BINARY_DIR}/src)

# ---- allow sootlib to be used in other targets ----
target_include_directories(sootlib PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include>"
        )

######################### TESTS ###############################

if (BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests ${CMAKE_CURRENT_BINARY_DIR}/tests)
endif()

######################## EXAMPLES ###############################

if (BUILD_EXAMPLES)
    add_subdirectory(examples ${CMAKE_CURRENT_BINARY_DIR}/examples)
endif()
