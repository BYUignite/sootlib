##################### SOOTLIB #####################

add_library(sootlib)

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
                ${CMAKE_SOURCE_DIR}/include/extern/eispack/eispack.h
                ${CMAKE_SOURCE_DIR}/include/extern/eispack/eispack.cc
                ${CMAKE_SOURCE_DIR}/include/extern/binomial/binomial.h
                ${CMAKE_SOURCE_DIR}/include/extern/jutil/jutil.h)
