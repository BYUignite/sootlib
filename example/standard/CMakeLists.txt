# ---- list executable .cpp files without their extension ----

set(STANDARD_EXAMPLES
        simple_moment_example
        simple_bin_example
        generator_example
        advanced_moment_example)

foreach(EXAMPLE ${STANDARD_EXAMPLES})
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
    target_link_libraries(${EXAMPLE} PRIVATE sootlib)
endforeach()
