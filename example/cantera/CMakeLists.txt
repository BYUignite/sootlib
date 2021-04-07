# ---- list executable .cc files without their extension ----

set(CANTERA_EXAMPLES
        cantera_example_1
        cantera_example_2)

foreach (EXAMPLE ${CANTERA_EXAMPLES})
    add_executable(${EXAMPLE} ${EXAMPLE}.cc)
    target_link_libraries(${EXAMPLE} PRIVATE ${CANTERA} sootlib)
endforeach ()
