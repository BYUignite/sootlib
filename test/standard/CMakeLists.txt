# ---- list executable .cpp files without their extension ----

set(STANDARD_TESTS
        CoagulationModel_NONE
        GrowthModel_NONE
        NucleationModel_NONE
        OxidationModel_NONE
        OxidationModel_LL
        OxidationModel_HACA
        OxidationModel_LEE_NAOH
        OxidationModel_NSC_NEOH
        GasState
        BinSootState
        MomentSootState
        NucleationModel_PAH
        NucleationModel_LL
        NucleationModel_LIN
        GrowthModel_LL
        GrowthModel_LIN
        GrowthModel_HACA
        CoagulationModel_FRENK
        CoagulationModel_FUCHS
        CoagulationModel_LL)

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
