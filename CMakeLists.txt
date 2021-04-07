cmake_minimum_required(VERSION 3.12)

project(sootlib)

############################### PROJECT OPTIONS ###############################

# ---- set C++ version to 17 ----
# (this project uses C++17 features)
set(CMAKE_CXX_STANDARD 17)

# ---- option to build tests ----
option(BUILD_TESTS "Build sootlib tests" ON)

# ---- option to build examples ----
option(BUILD_EXAMPLES "Build sootlib example" ON)

############################### SOOTLIB ###############################

add_subdirectory(src)

# ---- allow sootlib to be used in other targets ----
target_include_directories(sootlib PUBLIC src)

############################### TESTS ###############################

if (BUILD_TESTS)
    add_subdirectory(test)
endif()

############################### EXAMPLES ###############################

if (BUILD_EXAMPLES)
    add_subdirectory(example)
endif()
