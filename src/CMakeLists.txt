##################### SOOTMODEL LIBRARY #####################

# -------- library targets --------

add_library(sootModel)
add_library(sootlib::sootModel ALIAS sootModel)    # alias for use as imported target

target_sources(sootModel PRIVATE
               sootDefs.h
               sootModel.h
               state.h           state.cc
               sootModel_MONO.h  sootModel_MONO.cc
               )
               # sootModel_LOGN.h  sootModel_LOGN.cc
               # sootModel_MOMIC.h sootModel_MOMIC.cc binomial.h
               # sootModel_QMOM.h  sootModel_QMOM.cc
               # sootModel_SECT.h  sootModel_SECT.cc
               #)
               

# -------- target properties --------

target_compile_features(sootModel PUBLIC cxx_std_11)

set_target_properties(sootModel PROPERTIES PUBLIC_HEADER "state.h;sootModel.h;sootDefs.h")

#------ src files ------------------

target_include_directories(sootModel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(nucleationModels)
add_subdirectory(growthModels)
add_subdirectory(oxidationModels)
add_subdirectory(coagulationModels)

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
        EXPORT  sootlib
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib" )

install(FILES "coagulationModels/coagulationModel.h" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/coagulationModels")
install(FILES "growthModels/growthModel.h"           DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/growthModels")
install(FILES "nucleationModels/nucleationModel.h"   DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/nucleationModels")
install(FILES "oxidationModels/oxidationModel.h"     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/oxidationModels")

install(EXPORT sootlib
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sootlib
        NAMESPACE sootlib::
        )

