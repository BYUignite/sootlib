# ---- list executable .cpp files without their extension ----

set(STANDARD_TESTS
        cantera_test_1
        cantera_test_2)

set(CANTERA_TEST_LIBS
        ${GTEST_LIBS}
        ${CANTERA}
        sootlib
        testtools)

foreach(TEST ${STANDARD_TESTS})
    add_executable(${TEST} ${TEST}.cpp)

    target_link_libraries(${TEST} PRIVATE ${CANTERA_TEST_LIBS})

    gtest_add_tests(
            TARGET ${TEST}
            TEST_SUFFIX .cantera
            TEST_LIST canteraTests
    )
endforeach()
