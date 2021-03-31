add_subdirectory(standard)

if (BUILD_CANTERA_COMPAT)
    add_subdirectory(cantera)
endif ()
