# ---- initialize google test ----
enable_testing()
include(GoogleTest)
add_subdirectory(googletest)
set(GTEST_LIBS
        gtest
        gtest_main)

target_link_libraries(sootlib-test PRIVATE ${GTEST_LIBS} sootlib)

# ---- add tests ----


include_directories(standard)

if (BUILD_CANTERA_COMPAT)
    include_directories(cantera)
endif()
