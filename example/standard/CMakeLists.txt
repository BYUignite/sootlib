# ---- list executable .cpp files without their extension ----

set(STANDARD_EXAMPLES
        standard_example_1
        standard_example_2)

foreach(EXAMPLE ${STANDARD_EXAMPLES})
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
    target_link_libraries(${EXAMPLE} PRIVATE sootlib)
endforeach()
