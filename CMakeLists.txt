cmake_minimum_required(VERSION 3.12)

project(sootlib)

# ---- set c++ version to 17 ----
set(CMAKE_CXX_STANDARD 17)

# ---- option to build tests ----
option(BUILD_TESTS "Build sootlib tests" ON)

# ---- option to build example ----
option(BUILD_EXAMPLE "Build sootlib example" ON)

# note: you might have to reset your CMakeCache.txt when changing any options

############################### SOOTLIB ###############################

# ---- list of sootlib source files ----
set(SRC_FILES
        src/sootlib/SootModel.h
        src/sootlib/SootModel_Base.h
        src/sootlib/SootModel_Base.cpp
        src/sootlib/SootModel_LOGN.h
        src/sootlib/SootModel_LOGN.cpp
        src/sootlib/SootModel_MOMIC.h
        src/sootlib/SootModel_MOMIC.cpp
        src/sootlib/SootModel_MONO.h
        src/sootlib/SootModel_MONO.cpp
        src/sootlib/SootModel_QMOM.h
        src/sootlib/SootModel_QMOM.cpp
        src/sootlib/SootModel_SECT.h
        src/sootlib/SootModel_SECT.cpp
        src/sootlib/SootModelFactory.h
        src/sootlib/SootModelFactory.cpp
        src/sootlib/state/GasState.h
        src/sootlib/state/GasState.cpp
        src/sootlib/state/SootState.h
        src/sootlib/state/SootState.cpp
        src/sootlib/coagulation_model/CoagulationModel.h
        src/sootlib/coagulation_model/CoagulationModel_NONE.h
        src/sootlib/coagulation_model/CoagulationModel_NONE.cpp
        src/sootlib/coagulation_model/CoagulationModel_FUCHS.h
        src/sootlib/coagulation_model/CoagulationModel_FUCHS.cpp
        src/sootlib/coagulation_model/CoagulationModel_FRENK.h
        src/sootlib/coagulation_model/CoagulationModel_FRENK.cpp
        src/sootlib/coagulation_model/CoagulationModel_LL.h
        src/sootlib/coagulation_model/CoagulationModel_LL.cpp
        src/sootlib/growth_model/GrowthModel.h
        src/sootlib/growth_model/GrowthModel_NONE.h
        src/sootlib/growth_model/GrowthModel_NONE.cpp
        src/sootlib/growth_model/GrowthModel_LIN.h
        src/sootlib/growth_model/GrowthModel_LIN.cpp
        src/sootlib/growth_model/GrowthModel_LL.h
        src/sootlib/growth_model/GrowthModel_LL.cpp
        src/sootlib/growth_model/GrowthModel_HACA.h
        src/sootlib/growth_model/GrowthModel_HACA.cpp
        src/sootlib/nucleation_model/NucleationModel.h
        src/sootlib/nucleation_model/NucleationModel_NONE.h
        src/sootlib/nucleation_model/NucleationModel_NONE.cpp
        src/sootlib/nucleation_model/NucleationModel_LIN.h
        src/sootlib/nucleation_model/NucleationModel_LIN.cpp
        src/sootlib/nucleation_model/NucleationModel_LL.h
        src/sootlib/nucleation_model/NucleationModel_LL.cpp
        src/sootlib/nucleation_model/NucleationModel_PAH.h
        src/sootlib/nucleation_model/NucleationModel_PAH.cpp
        src/sootlib/oxidation_model/OxidationModel.h
        src/sootlib/oxidation_model/OxidationModel_NONE.h
        src/sootlib/oxidation_model/OxidationModel_NONE.cpp
        src/sootlib/oxidation_model/OxidationModel_LL.h
        src/sootlib/oxidation_model/OxidationModel_LL.cpp
        src/sootlib/oxidation_model/OxidationModel_LEE_NEOH.h
        src/sootlib/oxidation_model/OxidationModel_LEE_NEOH.cpp
        src/sootlib/oxidation_model/OxidationModel_NSC_NEOH.h
        src/sootlib/oxidation_model/OxidationModel_NSC_NEOH.cpp
        src/sootlib/oxidation_model/OxidationModel_HACA.h
        src/sootlib/oxidation_model/OxidationModel_HACA.cpp)

# ---- add sootlib library target ----
add_library(sootlib STATIC ${SRC_FILES})

# ---- allow sootlib to be used in other targets ----
target_include_directories(sootlib PUBLIC src)

############################### TESTS ###############################

if (BUILD_TESTS)
    # ---- list of test source files ----
    set(TEST_SRC_FILES
            test/main.cpp)

    # ---- add test executable target ----
    add_executable(sootlib-test ${TEST_SRC_FILES})

    # ---- option to use shared of local google test library ----
    option(USE_SHARED_GTEST "Use a shared google test library rather than a local one" ON)

    # TODO I am not totally confident these options are equivalent
    if (USE_SHARED_GTEST)
        # ---- enable google test with shared library ----
        # linux instructions found at: https://stackoverflow.com/questions/13513905/how-to-set-up-googletest-as-a-shared-library-on-linux
        find_package(GTest REQUIRED)
        set(GTEST_LIBS
                GTest::GTest
                GTest::Main)
    else()
        # ---- enable google test with local files ----
        # found at: https://github.com/google/googletest
        enable_testing()
        include(GoogleTest)
        set(BUILD_GMOCK ON)
        # change this to change search location
        add_subdirectory(lib/googletest)

        set(GTEST_LIBS
                gtest
                gmock
                gtest_main)
    endif()

    # ---- add google test and sootlib to tests ----
    target_link_libraries(sootlib-test PRIVATE ${GTEST_LIBS} sootlib)

    # ---- tests ----
    # TODO these are placeholder tests

    # ---- no args tests ----
    gtest_add_tests(
            TARGET sootlib-test
            TEST_SUFFIX .noArgs
            TEST_LIST noArgsTests
    )
    set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 10)

    # ---- with args tests ----
    gtest_add_tests(
            TARGET sootlib-test
            EXTRA_ARGS --someArg someValue
            TEST_SUFFIX .withArgs
            TEST_LIST withArgsTests
    )
    set_tests_properties(${withArgsTests} PROPERTIES TIMEOUT 20)
endif()

############################### EXAMPLE ###############################
# this could be expanded to take any number of examples dynamically

if (BUILD_EXAMPLE)
    # ---- list of example source files ----
    set(EXAMPLE_SRC_FILES
            example/main.cpp)

    # ---- add example executable target ----
    add_executable(sootlib-example ${EXAMPLE_SRC_FILES})

    # TODO add a local option?
    # ---- find cantera ----
    # found at: https://cantera.org/install/index.html
    find_library(CANTERA cantera REQUIRED)

    # ---- add cantera and sootlib to example ----
    target_link_libraries(sootlib-example PRIVATE ${CANTERA} sootlib)
endif()
