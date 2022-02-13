################### PREAMBLE ###############################

cmake_minimum_required(VERSION 3.15)

project(sootlib VERSION 0.1.0
        LANGUAGES CXX)

################### PROJECT SETUP ##########################

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)       # Release or Debug
endif()

# ---- set C++ language standard ----
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# ---- installation location ----
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")

# ---- build options ----
option(SOOTLIB_BUILD_EXAMPLES   "Build sootlib examples"        OFF)
option(SOOTLIB_BUILD_TESTING    "Build sootlib tests"           OFF)
option(SOOTLIB_BUILD_DOCS       "Build sootlib documentation"   OFF)

################### MAIN PROJECT TARGETS #####################

add_subdirectory(src)

################### OPTIONAL PROJECT TARGETS #################

# -------- TESTING --------
if (SOOTLIB_BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

# -------- EXAMPLES --------
if (SOOTLIB_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# -------- DOCUMENTATION --------

if (SOOTLIB_BUILD_DOCS)
    add_subdirectory(docs)
endif()