#------ src/sootModel/sootChemistry/nucleationModels files ------------------

target_sources(sootlib PRIVATE
                nucleationModel.h        nucleationModel.cc
                nucleationModel_PAH.h    nucleationModel_PAH.cc
                nucleationModel_LIN.h    nucleationModel_LIN.cc
                nucleationModel_LL.h     nucleationModel_LL.cc
                nucleationModel_NONE.h)
