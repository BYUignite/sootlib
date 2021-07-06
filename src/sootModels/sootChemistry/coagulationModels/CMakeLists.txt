#------ src/sootModel/sootChemistry/coagulationModels files ------------------

target_sources(sootlib PRIVATE              coagulationModel.h
                coagulationModel_FRENK.cc   coagulationModel_FRENK.h
                coagulationModel_FUCHS.cc   coagulationModel_FUCHS.h
                coagulationModel_LL.cc      coagulationModel_LL.h
                                            coagulationModel_NONE.h)
