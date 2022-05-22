################### PREAMBLE ###############################

cmake_minimum_required(VERSION 3.15)

project(sootlib VERSION 0.1.0
        LANGUAGES CXX)

################### PROJECT SETUP ##########################

include(FetchContent)
include(ExternalProject)
include(GNUInstallDirs)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)       # Release or Debug
endif()

# ---- set C++ language standard ----
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# ---- module path ----
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)      # tells find_package() where to look for Find[pkg].cmake files

# ---- installation location ----
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib" $ENV{LD_RUN_PATH})
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# ---- build options ----
option(SOOTLIB_BUILD_EXAMPLES_BASIC     "Build sootlib basic examples"                  ON)
option(SOOTLIB_BUILD_EXAMPLES_ADVANCED  "Build sootlib advanced examples (w/ Cantera)"  ON)
option(SOOTLIB_SYSTEM_CANTERA           "Use system-wide Cantera installation"          OFF)
option(SOOTLIB_BUILD_TESTING            "Build sootlib tests"                           OFF)
option(SOOTLIB_BUILD_DOCS               "Build sootlib documentation"                   OFF)

################### MAIN PROJECT TARGETS #####################

add_subdirectory(src)

################### OPTIONAL PROJECT TARGETS #################

# -------- TESTING --------
if (SOOTLIB_BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

# -------- EXAMPLES --------
if (SOOTLIB_BUILD_EXAMPLES_BASIC OR SOOTLIB_BUILD_EXAMPLES_ADVANCED)
    add_subdirectory(examples)
endif()

# -------- DOCUMENTATION --------

if (SOOTLIB_BUILD_DOCS)
    add_subdirectory(docs)
endif()