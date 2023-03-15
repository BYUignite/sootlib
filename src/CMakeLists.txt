##################### SOOTMODEL LIBRARY #####################

# -------- library targets --------

add_library(sootModel)
add_library(sootlib::sootModel ALIAS sootModel)    # alias for use as imported target

target_sources(sootModel PRIVATE
               sootDefs.h
               sootHeaders.h
               sootModel.h       sootModel.cc
               state.h           state.cc
               sootModel_MONO.h  sootModel_MONO.cc
               sootModel_LOGN.h  sootModel_LOGN.cc
               sootModel_QMOM.h  sootModel_QMOM.cc
               sootModel_MOMIC.h sootModel_MOMIC.cc binomial.h
               sootModel_SECT.h  sootModel_SECT.cc
               )
               

# -------- target properties --------

target_compile_features(sootModel PUBLIC cxx_std_11)

set_target_properties(sootModel PROPERTIES PUBLIC_HEADER "state.h;sootModel.h;sootDefs.h;sootHeaders.h")

if(APPLE)
    find_library(ACCELERATE Accelerate)
    target_link_libraries(sootModel ${ACCELERATE})
else()
    find_package(LAPACK REQUIRED)
    target_link_libraries(sootModel LAPACK::LAPACK)
endif()

#------ src files ------------------

target_include_directories(sootModel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(nucleationModels)
add_subdirectory(growthModels)
add_subdirectory(oxidationModels)
add_subdirectory(coagulationModels)

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

install(FILES "sootHeaders.h"                                  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib")
install(FILES "state.h"                                        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib")
install(FILES "sootDefs.h"                                     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib")

install(FILES "sootModel.h"                                    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib")
install(FILES "sootModel_MONO.h"                               DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib")
install(FILES "sootModel_MOMIC.h"                              DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib")
install(FILES "sootModel_LOGN.h"                               DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib")
install(FILES "sootModel_QMOM.h"                               DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib")
install(FILES "sootModel_SECT.h"                               DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib")

install(FILES "nucleationModels/nucleationModel.h"             DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/nucleationModels")
install(FILES "nucleationModels/nucleationModel_LL.h"          DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/nucleationModels")
install(FILES "nucleationModels/nucleationModel_LIN.h"         DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/nucleationModels")
install(FILES "nucleationModels/nucleationModel_PAH.h"         DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/nucleationModels")
install(FILES "nucleationModels/nucleationModel_NONE.h"        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/nucleationModels")

install(FILES "growthModels/growthModel.h"                     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/growthModels")
install(FILES "growthModels/growthModel_LL.h"                  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/growthModels")
install(FILES "growthModels/growthModel_LIN.h"                 DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/growthModels")
install(FILES "growthModels/growthModel_HACA.h"                DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/growthModels")
install(FILES "growthModels/growthModel_NONE.h"                DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/growthModels")

install(FILES "oxidationModels/oxidationModel.h"               DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/oxidationModels")
install(FILES "oxidationModels/oxidationModel_LL.h"            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/oxidationModels")
install(FILES "oxidationModels/oxidationModel_LEE_NEOH.h"      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/oxidationModels")
install(FILES "oxidationModels/oxidationModel_NSC_NEOH.h"      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/oxidationModels")
install(FILES "oxidationModels/oxidationModel_HACA.h"          DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/oxidationModels")
install(FILES "oxidationModels/oxidationModel_OPTJ.h"          DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/oxidationModels")
install(FILES "oxidationModels/oxidationModel_OPTG.h"          DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/oxidationModels")
install(FILES "oxidationModels/oxidationModel_NONE.h"          DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/oxidationModels")

install(FILES "coagulationModels/coagulationModel.h"           DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/coagulationModels")
install(FILES "coagulationModels/coagulationModel_FM.h"        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/coagulationModels")
install(FILES "coagulationModels/coagulationModel_CONTINUUM.h" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/coagulationModels")
install(FILES "coagulationModels/coagulationModel_HM.h"        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/coagulationModels")
install(FILES "coagulationModels/coagulationModel_FUCHS.h"     DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/coagulationModels")
install(FILES "coagulationModels/coagulationModel_NONE.h"      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/sootlib/coagulationModels")


install(EXPORT sootlib
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/sootlib
        NAMESPACE sootlib::
        )

