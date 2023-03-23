#------ src/sootModel/sootChemistry/nucleationModels files ------------------

target_sources(sootModel PRIVATE
                nucleationModel.h        nucleationModel.cc
                nucleationModel_PAH.h    nucleationModel_PAH.cc
                nucleationModel_LIN.h    nucleationModel_LIN.cc
                nucleationModel_LINA1.h  nucleationModel_LINA1.cc
                nucleationModel_LL.h     nucleationModel_LL.cc
                nucleationModel_NONE.h)
