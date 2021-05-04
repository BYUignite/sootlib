# ---- create test helper library ----

set(TEST_HELP_LIB_FILES
        testtools/TestTools.h)

add_library(testtools STATIC ${TEST_HELP_LIB_FILES})
set_target_properties(testtools PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(testtools PUBLIC testtools)

# ---- add tests ----

add_subdirectory(tests)
