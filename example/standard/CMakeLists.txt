# ---- list executable .cpp files without their extension ----

set(STANDARD_EXAMPLES
        simple_example
        generator_example
        advanced_example)

foreach (EXAMPLE ${STANDARD_EXAMPLES})
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
    target_link_libraries(${EXAMPLE} PRIVATE sootlib)
endforeach ()
