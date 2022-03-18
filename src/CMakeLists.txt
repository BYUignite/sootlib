##################### SOOTMODEL LIBRARY #####################

# -------- library targets --------
add_library(sootModel constants.h state.cc state.h sootModel.cc sootModel.h)
add_library(sootlib::sootModel ALIAS sootModel)    # alias for use as imported target

# -------- target properties --------
target_compile_features(sootModel PUBLIC cxx_std_11)
set_target_properties(sootModel PROPERTIES PUBLIC_HEADER "state.h;sootModel.h;constants.h")

#------ src files ------------------
add_subdirectory(sootModels/psdModels)
add_subdirectory(sootModels/sootChemistry/nucleationModels)
add_subdirectory(sootModels/sootChemistry/growthModels)
add_subdirectory(sootModels/sootChemistry/oxidationModels)
add_subdirectory(sootModels/sootChemistry/coagulationModels)

#------ external content ------------------
target_sources(sootModel PRIVATE ${PROJECT_SOURCE_DIR}/ext/eispack/eispack.h
                                 ${PROJECT_SOURCE_DIR}/ext/eispack/eispack.cc
                                 ${PROJECT_SOURCE_DIR}/ext/binomial/binomial.h
              )

############# LIBRARY INSTALLATION ################

include(GNUInstallDirs)

# ---- allow sootlib to be used in other targets ----
target_include_directories(sootModel
        INTERFACE
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/sootlib>"
        )

install(TARGETS sootModel
        EXPORT sootlib
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib"
        )

install(EXPORT sootlib
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sootlib
        NAMESPACE sootlib::
        )