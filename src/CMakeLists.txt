##################### SOOTMODEL LIBRARY #####################

# -------- library targets --------

add_library(sootModel sootDefs.h state.cc state.h sootModel.cc sootModel.h)
add_library(sootlib::sootModel ALIAS sootModel)    # alias for use as imported target

# -------- target properties --------

target_compile_features(sootModel PUBLIC cxx_std_11)

set_target_properties(sootModel PROPERTIES PUBLIC_HEADER "state.h;sootModel.h;sootDefs.h")

#------ src files ------------------

target_include_directories(sootModel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(sootModels/psdModels)
add_subdirectory(sootModels/sootChemistry/nucleationModels)
add_subdirectory(sootModels/sootChemistry/growthModels)
add_subdirectory(sootModels/sootChemistry/oxidationModels)
add_subdirectory(sootModels/sootChemistry/coagulationModels)

#------ external content ------------------

target_sources(sootModel PRIVATE ${PROJECT_SOURCE_DIR}/ext/eispack/eispack.h
                                 ${PROJECT_SOURCE_DIR}/ext/eispack/eispack.cc)

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
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib" )

install(FILES "sootModels/psdModels/psdModel.h"                               DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/sootModels/psdModels")
install(FILES "sootModels/sootChemistry/coagulationModels/coagulationModel.h" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/sootModels/sootChemistry/coagulationModels")
install(FILES "sootModels/sootChemistry/growthModels/growthModel.h"           DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/sootModels/sootChemistry/growthModels")
install(FILES "sootModels/sootChemistry/nucleationModels/nucleationModel.h"   DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/sootModels/sootChemistry/nucleationModels")
install(FILES "sootModels/sootChemistry/oxidationModels/oxidationModel.h"     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/sootModels/sootChemistry/oxidationModels")

install(EXPORT sootlib
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sootlib
        NAMESPACE sootlib::
        )
