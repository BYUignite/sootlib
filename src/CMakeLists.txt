##################### SOOTLIB #####################

add_library(sootlib)

target_compile_features(sootlib PUBLIC cxx_std_11)

#------ src files ------------------

target_sources(sootlib PRIVATE  constants.h
                state.cc        state.h
                sootModel.cc    sootModel.h)

#------ src subdirectories ---------

add_subdirectory(sootModels/psdModels                       ${CMAKE_CURRENT_BINARY_DIR}/sootModels/psdModels)
add_subdirectory(sootModels/sootChemistry/nucleationModels  ${CMAKE_CURRENT_BINARY_DIR}/sootModels/sootChemistry/nucleationModels)
add_subdirectory(sootModels/sootChemistry/growthModels      ${CMAKE_CURRENT_BINARY_DIR}/sootModels/sootChemistry/growthModels)
add_subdirectory(sootModels/sootChemistry/oxidationModels   ${CMAKE_CURRENT_BINARY_DIR}/sootModels/sootChemistry/oxidationModels)
add_subdirectory(sootModels/sootChemistry/coagulationModels ${CMAKE_CURRENT_BINARY_DIR}/sootModels/sootChemistry/coagulationModels)

#------ extern lib files ------------------

target_sources(sootlib PRIVATE
                ${CMAKE_SOURCE_DIR}/extern/eispack/eispack.h
                ${CMAKE_SOURCE_DIR}/extern/eispack/eispack.cc
                ${CMAKE_SOURCE_DIR}/extern/binomial/binomial.h)

#------ installation ----------------------

set_target_properties(sootlib PROPERTIES PUBLIC_HEADER "state.h;sootModel.h;constants.h")

install(TARGETS sootlib
        EXPORT sootlibTargets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        )

install(EXPORT sootlibTargets
        FILE sootlib.cmake
        NAMESPACE sootlib::
        DESTINATION cmake/sootlib
        )
