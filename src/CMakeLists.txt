##################### SOOTMODEL LIBRARY #####################

add_library(sootlib SHARED)
add_library(sootlib::sootlib ALIAS sootlib)


target_sources(sootlib 
    PRIVATE
        sootModel.cc
        state.cc
        sootModel_MONO.cc
        sootModel_LOGN.cc
        sootModel_QMOM.cc
        sootModel_MOMIC.cc
        sootModel_SECT.cc
    PUBLIC    
    FILE_SET sootlib_headers
            TYPE HEADERS
            BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}" 
            FILES sootHeaders.h             
                  state.h
                  sootDefs.h
                  sootModel.h
                  sootModel_MONO.h
                  sootModel_MOMIC.h
                  sootModel_LOGN.h             
                  sootModel_QMOM.h
                  sootModel_SECT.h
                  nucleationModels/nucleationModel.h
                  nucleationModels/nucleationModel_LL.h
                  nucleationModels/nucleationModel_LIN.h        
                  nucleationModels/nucleationModel_LINA1.h
                  nucleationModels/nucleationModel_PAH.h
                  nucleationModels/nucleationModel_NONE.h
                  growthModels/growthModel.h
                  growthModels/growthModel_LL.h
                  growthModels/growthModel_LIN.h            
                  growthModels/growthModel_HACA.h
                  growthModels/growthModel_NONE.h
                  oxidationModels/oxidationModel.h
                  oxidationModels/oxidationModel_LL.h
                  oxidationModels/oxidationModel_LEE_NEOH.h
                  oxidationModels/oxidationModel_NSC_NEOH.h
                  oxidationModels/oxidationModel_HACA.h
                  oxidationModels/oxidationModel_OPTJ.h    
                  oxidationModels/oxidationModel_OPTG.h
                  oxidationModels/oxidationModel_NONE.h
                  coagulationModels/coagulationModel.h
                  coagulationModels/coagulationModel_FM.h
                  coagulationModels/coagulationModel_CONTINUUM.h 
                  coagulationModels/coagulationModel_HM.h
                  coagulationModels/coagulationModel_FUCHS.h
                  coagulationModels/coagulationModel_NONE.h
)

add_subdirectory(nucleationModels)
add_subdirectory(growthModels)
add_subdirectory(oxidationModels)
add_subdirectory(coagulationModels)

############################ Build library

if(APPLE)
    find_library(ACCELERATE Accelerate)
    target_link_libraries(sootlib ${ACCELERATE})
else()
    find_package(LAPACK REQUIRED)
    target_link_libraries(sootlib LAPACK::LAPACK)
endif()

############################ Install library

include(GNUInstallDirs)

install(
    TARGETS sootlib                                     # install library
    EXPORT  sootlib_exp                                 # define export var for next comand
    FILE_SET sootlib_headers   DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(
    EXPORT      sootlib_exp                             # hello export file
    FILE        sootlib_exp.cmake  
    NAMESPACE   sootlib::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/sootlib"
)

install(
    FILES       "sootlibConfig.cmake"                   # install config files
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/sootlib" # edit file sootlibConfig.cmake
)
