# ---- list executable .cc files without their extension ----

set(TEST_FILES
        test1
        pytest
        momic_debug)

foreach (TEST_FILE ${TEST_FILES})
    add_executable(${TEST_FILE} ${TEST_FILE}.cc)
    target_link_libraries(${TEST_FILE} PRIVATE sootlib)
    target_link_libraries(${TEST_FILE} PUBLIC testtools)
endforeach()
