#------ src/sootModel/sootChemistry/oxidationModels files ------------------

target_sources(sootModel PRIVATE
                oxidationModel.cc           oxidationModel.h
                oxidationModel_HACA.cc      oxidationModel_HACA.h
                oxidationModel_LL.cc        oxidationModel_LL.h
                oxidationModel_LEE_NEOH.cc  oxidationModel_LEE_NEOH.h
                oxidationModel_NSC_NEOH.cc  oxidationModel_NSC_NEOH.h
                                            oxidationModel_NONE.h)