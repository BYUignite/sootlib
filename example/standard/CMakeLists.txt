# ---- list example executables here ----

# ---- put the names of the .cpp test files ----
set(STANDARD_EXAMPLES
        standard_example_1
        standard_example_2)

foreach(EXAMPLE IN STANDARD_EXAMPLES)
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
endforeach()
