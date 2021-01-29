cmake_minimum_required(VERSION 3.12)

project(sootlib)

############################### PROJECT OPTIONS ###############################

# ---- set c++ version to 17 ----
set(CMAKE_CXX_STANDARD 17)

# ---- option to build tests ----
option(BUILD_TESTS "Build sootlib tests" ON)

# ---- option to build examples ----
option(BUILD_EXAMPLES "Build sootlib example" ON)

# ---- option to build Cantera compatability ----
option(BUILD_CANTERA_COMPAT "Build Cantera compatability" ON)

# note: you might have to reset your CMakeCache.txt when changing any options

############################### CANTERA ###############################

# ---- make cantera library available to project if it is being built
if (BUILD_CANTERA_COMPAT)
    find_library(CANTERA cantera REQUIRED)
endif()

############################### SOOTLIB ###############################

include_directories(src/sootlib)

# ---- allow sootlib to be used in other targets ----
target_include_directories(sootlib PUBLIC src)

############################### TESTS ###############################

if (BUILD_TESTS)
    include_directories(test)
endif()

############################### EXAMPLES ###############################

if (BUILD_EXAMPLES)
    include_directories(example)
endif()
