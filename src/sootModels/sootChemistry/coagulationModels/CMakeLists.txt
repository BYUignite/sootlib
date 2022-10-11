#------ src/sootModel/sootChemistry/coagulationModels files ------------------

target_sources(sootModel PRIVATE              coagulationModel.h
                coagulationModel_FM.cc        coagulationModel_FM.h
                coagulationModel_CONTINUUM.cc coagulationModel_CONTINUUM.h
                coagulationModel_HM.cc        coagulationModel_HM.h
                coagulationModel_FUCHS.cc     coagulationModel_FUCHS.h
                                              coagulationModel_NONE.h)
