# ---- list example executables here ----

# ---- put the names of the .cpp test files ----
set(CANTERA_EXAMPLES
        cantera_example_1
        cantera_example_2)

foreach(EXAMPLE IN CANTERA_EXAMPLES)
    add_executable(${EXAMPLE} ${EXAMPLE}.cpp)
    target_link_libraries(${EXAMPLE} PRIVATE ${CANTERA} sootlib)
endforeach()
