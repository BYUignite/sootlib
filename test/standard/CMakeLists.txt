# ---- list executable .cpp files without their extension ----

set(STANDARD_TESTS
        standard_test_1
        standard_test_2
        CoagulationModel_NONE)

foreach(TEST ${STANDARD_TESTS})
    add_executable(${TEST} ${TEST}.cpp)
    target_link_libraries(${TEST} PRIVATE ${GTEST_LIBS} sootlib)

    gtest_add_tests(
            TARGET ${TEST}
            TEST_SUFFIX .standard
            TEST_LIST standardTests
    )
endforeach()
