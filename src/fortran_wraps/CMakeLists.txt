if (CMAKE_Fortran_COMPILER AND BUILD_FORTRAN_INTERFACE)

    add_library(sootlib_fortran)
    add_library(sootlib_fortran::sootlib_fortran ALIAS sootlib_fortran)

    target_sources(sootlib_fortran PRIVATE soot_module.f90 c_interface.cc)

    target_link_libraries(sootlib_fortran sootlib)
    target_include_directories(sootlib_fortran PRIVATE "${CMAKE_SOURCE_DIR}")

    ####################################### Install library 

    include(GNUInstallDirs)

    install(FILES "${CMAKE_BINARY_DIR}/src/fortran_wraps/soot_module.mod"
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    install(TARGETS sootlib_fortran
            EXPORT  sootlib_fortran_exp)

    install(EXPORT       sootlib_fortran_exp
            FILE         sootlib_fortran_exp.cmake
            NAMESPACE    sootlib_fortran::
            DESTINATION  "${CMAKE_INSTALL_LIBDIR}/cmake/sootlib_fortran")

    install(FILES        "sootlib_fortranConfig.cmake"
            DESTINATION  "${CMAKE_INSTALL_LIBDIR}/cmake/sootlib_fortran")

else()
    message([FATAL_ERROR] "No Fortran Compiler found")
endif()
