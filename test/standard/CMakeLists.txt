file(GLOB STANDARD_TEST_SRCS *.cpp)

add_executable(sootlib_standard_test ${STANDARD_TEST_SRCS})

gtest_add_tests(
        TARGET sootlib-standard-test
        TEST_SUFFIX .noArgs
        TEST_LIST noArgsTests
)
set_tests_properties(${noArgsTests} PROPERTIES TIMEOUT 10)

gtest_add_tests(
        TARGET sootlib-standard-test
        TEST_SUFFIX .withArgs
        TEST_LIST withArgsTests
)
set_tests_properties(${withArgsTests} PROPERTIES TIMEOUT 10)

target_link_libraries(sootlib_standard_test
        sootlib
        GTEST_LIBS)
