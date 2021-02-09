# ---- initialize google test ----
enable_testing()
include(GoogleTest)
# include_directories(googletest)
add_subdirectory(googletest)
set(GTEST_LIBS
        gtest
        gtest_main)

# ---- add tests ----

add_subdirectory(standard)

if (BUILD_CANTERA_COMPAT)
    add_subdirectory(cantera)
endif()
