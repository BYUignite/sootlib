# ---- list executable .cpp files without their extension ----

set(STANDARD_TESTS
        CoagulationModel_NONE
        GrowthModel_NONE
        NucleationModel_NONE
        OxidationModel_NONE)

set(TEST_LIBS
        ${GTEST_LIBS}
        sootlib
        testtools)

foreach(TEST ${STANDARD_TESTS})
    add_executable(${TEST} ${TEST}.cpp)
    target_link_libraries(${TEST} PRIVATE ${TEST_LIBS})

    gtest_add_tests(
            TARGET ${TEST}
            TEST_SUFFIX .standard
            TEST_LIST standardTests
    )
endforeach()
