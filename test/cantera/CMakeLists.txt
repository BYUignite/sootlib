file(GLOB CANTERA_TEST_SRCS *.cpp)

add_executable(sootlib_cantera_test ${CANTERA_TEST_SRCS})

gtest_add_tests(
        TARGET sootlib-cantera-test
        TEST_SUFFIX .noArgs
        TEST_LIST noArgsTests
)
set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 10)

gtest_add_tests(
        TARGET sootlib-cantera-test
        TEST_SUFFIX .withArgs
        TEST_LIST withArgsTests
)
set_tests_properties(${withArgsTests} PROPERTIES TIMEOUT 10)

target_link_libraries(sootlib_cantera_test
        sootlib
        GTEST_LIBS)
