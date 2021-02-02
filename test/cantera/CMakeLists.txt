# ---- list executable .cpp files without their extension ----

set(STANDARD_TESTS
        cantera_test_1
        cantera_test_2)

foreach(TEST ${STANDARD_TESTS})
    add_executable(${TEST} ${TEST}.cpp)

    target_link_libraries(${TEST} PRIVATE ${GTEST_LIBS} ${CANTERA} sootlib)

    gtest_add_tests(
            TARGET ${TEST}
            TEST_SUFFIX .cantera
            TEST_LIST canteraTests
    )
endforeach()
