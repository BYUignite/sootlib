#------ src/sootModel/sootChemistry/growthModels files ------------------

target_sources(sootModel PRIVATE
                growthModel.cc      growthModel.h
                growthModel_HACA.cc growthModel_HACA.h
                growthModel_LIN.cc  growthModel_LIN.h
                growthModel_LL.cc   growthModel_LL.h
                                    growthModel_NONE.h)