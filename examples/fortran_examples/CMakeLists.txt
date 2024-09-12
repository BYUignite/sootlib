
#--------------- simple_example.f90

if (CMAKE_Fortran_COMPILER AND BUILD_FORTRAN_INTERFACE)
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")


    add_executable(            simple_example_fort.x simple_example_fort.f90)
    target_include_directories(simple_example_fort.x PRIVATE "${CMAKE_BINARY_DIR}/src/fortran_wraps")
    target_link_libraries(     simple_example_fort.x PRIVATE sootlib sootlib_fortran -fPIC)
    install(TARGETS            simple_example_fort.x DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

elseif(!CMAKE_Fortran_COMPILER AND BUILD_FORTRAN_INTERFACE)

    message([FATAL_ERROR] "No Fortran compiler found")

endif()
