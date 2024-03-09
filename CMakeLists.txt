################### PREAMBLE ###############################

cmake_minimum_required(VERSION 3.28)

project(sootlib VERSION 0.1.0 LANGUAGES CXX)

################### PROJECT SETUP ##########################

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)       # Release or Debug
endif()

#---- set C++ language standard ----

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

#---- installation location: SET ON COMMAND LINE with cmake --install-prefix /opt/sootlib ..
#---- or uncomment here, but don't do both
#---- default is usr/local

#---- installation location
# set here, OR comment these and set on command line with cmake --install-prefix /path/sootlib ..

set(CMAKE_INSTALL_PREFIX "/opt/sootlib")              # --> /opt/sootlib/include and /opt/sootlib/lib
#set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")    # --> ./include and ./lib

# ---- build options ----

option(SOOTLIB_BUILD_EXAMPLES   "Build sootlib examples"        ON)
option(SOOTLIB_BUILD_TESTING    "Build sootlib tests"           OFF)
option(SOOTLIB_BUILD_DOCS       "Build sootlib documentation"   OFF)

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
