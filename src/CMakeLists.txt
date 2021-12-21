##################### SOOTLIB #####################

add_library(sootlib)

target_compile_features(sootlib PUBLIC cxx_std_11)

#------ src files ------------------
target_sources(sootlib PRIVATE constants.h state.cc state.h sootModel.cc sootModel.h)

#------ src subdirectories ---------
add_subdirectory(sootModels/psdModels)
add_subdirectory(sootModels/sootChemistry/nucleationModels)
add_subdirectory(sootModels/sootChemistry/growthModels)
add_subdirectory(sootModels/sootChemistry/oxidationModels)
add_subdirectory(sootModels/sootChemistry/coagulationModels)

#------ external content ------------------
target_sources(sootlib PRIVATE
                ${PROJECT_SOURCE_DIR}/ext/eispack/eispack.h
                ${PROJECT_SOURCE_DIR}/ext/eispack/eispack.cc
                ${PROJECT_SOURCE_DIR}/ext/binomial/binomial.h
              )

#------ installation ----------------------

set_target_properties(sootlib PROPERTIES PUBLIC_HEADER "state.h;sootModel.h;constants.h")

# ---- allow sootlib to be used in other targets ----
target_include_directories(sootlib PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>"
        "$<INSTALL_INTERFACE:include>"
        )

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