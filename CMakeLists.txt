################### PREAMBLE ###############################

cmake_minimum_required(VERSION 3.23)

project(sootlib VERSION 0.1.0 LANGUAGES CXX)

################### PROJECT SETUP ##########################

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)       # Release or Debug
endif()

#---- set C++ language standard ----

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")

#---- installation location: SET ON COMMAND LINE with cmake --install-prefix /opt/sootlib ..
#---- or uncomment here, but don't do both
#---- default is usr/local

#---- installation location
# set here, OR comment these and set on command line with cmake --install-prefix /path/sootlib ..

#set(CMAKE_INSTALL_PREFIX "/opt/sootlib" CACHE STRING "install location")
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}" CACHE STRING "install location")

# ---- build options ----

option(SOOTLIB_BUILD_EXAMPLES   "Build sootlib examples"        ON)
option(SOOTLIB_BUILD_TESTING    "Build sootlib tests"           OFF)
option(SOOTLIB_BUILD_DOCS       "Build sootlib documentation"   OFF)

# ---- Fortran Wrappers ----
option(BUILD_FORTRAN_INTERFACE  "Build fortran interface"        ON)

################### MAIN PROJECT TARGETS #####################

add_subdirectory(src)

################### OPTIONAL PROJECT TARGETS #################

#-------- EXAMPLES --------

if(SOOTLIB_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

#-------- TESTING --------

if(SOOTLIB_BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

#-------- DOCUMENTATION --------

if(SOOTLIB_BUILD_DOCS)
    add_subdirectory(docs)
endif()

#-------- FORTRAN INTERFACE ----

if(BUILD_FORTRAN_INTERFACE)
    enable_language(Fortran)
    add_subdirectory(src/fortran_wraps)
    add_subdirectory(examples/fortran_examples)
endif()
