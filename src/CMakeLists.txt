##################### SOOTMODEL LIBRARY #####################

# -------- library targets --------
add_library(sootModel constants.h state.cc state.h sootModel.cc sootModel.h)
add_library(sootlib::sootModel ALIAS sootModel)    # alias for use as imported target

# -------- target properties --------
target_compile_features(sootModel PUBLIC cxx_std_11)
set_target_properties(sootModel PROPERTIES PUBLIC_HEADER "state.h;sootModel.h;constants.h")
set_target_properties(sootModel PROPERTIES PRIVATE_HEADER "sootModels/psdModels/psdModel_QMOM.h;sootModels/psdModels/psdModel_MONO.h;sootModels/psdModels/psdModel_MOMIC.h;sootModels/psdModels/psdModel_LOGN.h;sootModels/psdModels/psdModel.h;sootModels/sootChemistry/coagulationModels/coagulationModel.h;sootModels/sootChemistry/coagulationModels/coagulationModel_NONE.h;sootModels/sootChemistry/coagulationModels/coagulationModel_LL.h;sootModels/sootChemistry/coagulationModels/coagulationModel_FUCHS.h;sootModels/sootChemistry/coagulationModels/coagulationModel_FRENK.h;sootModels/sootChemistry/growthModels/growthModel.h;sootModels/sootChemistry/growthModels/growthModel_NONE.h;sootModels/sootChemistry/growthModels/growthModel_LL.h;sootModels/sootChemistry/growthModels/growthModel_LIN.h;sootModels/sootChemistry/growthModels/growthModel_HACA.h;sootModels/sootChemistry/nucleationModels/nucleationModel.h;sootModels/sootChemistry/nucleationModels/nucleationModel_PAH.h;sootModels/sootChemistry/nucleationModels/nucleationModel_LIN.h;sootModels/sootChemistry/nucleationModels/nucleationModel_LL.h;sootModels/sootChemistry/nucleationModels/nucleationModel_NONE.h;sootModels/sootChemistry/oxidationModels/oxidationModel.h;sootModels/sootChemistry/oxidationModels/oxidationModel_HACA.h;sootModels/sootChemistry/oxidationModels/oxidationModel_LL.h;sootModels/sootChemistry/oxidationModels/oxidationModel_LEE_NEOH.h;sootModels/sootChemistry/oxidationModels/oxidationModel_NSC_NEOH.h;sootModels/sootChemistry/oxidationModels/oxidationModel_NONE.h")

#------ src files ------------------
add_subdirectory(sootModels/psdModels)
add_subdirectory(sootModels/sootChemistry/nucleationModels)
add_subdirectory(sootModels/sootChemistry/growthModels)
add_subdirectory(sootModels/sootChemistry/oxidationModels)
add_subdirectory(sootModels/sootChemistry/coagulationModels)

#------ external content ------------------
target_sources(sootModel PRIVATE ${PROJECT_SOURCE_DIR}/ext/eispack/eispack.h
                                 ${PROJECT_SOURCE_DIR}/ext/eispack/eispack.cc
                                 ${PROJECT_SOURCE_DIR}/ext/binomial/binomial.h)

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
        PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/sootModels"
        )

install(EXPORT sootlib
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sootlib
        NAMESPACE sootlib::
        )