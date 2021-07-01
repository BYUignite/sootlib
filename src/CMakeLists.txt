# ---- set each batch of files ----

set(COAGULATION_SRC_FILES
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel.h
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_FRENK.h
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_FRENK.cc
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_FUCHS.h
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_FUCHS.cc
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_LL.h
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_LL.cc)

set(GROWTH_SRC_FILES
        sootlib/soot_model/soot_chemistry/growth_model/GrowthModel.h
        sootlib/soot_model/soot_chemistry/growth_model/GrowthModel_HACA.h
        sootlib/soot_model/soot_chemistry/growth_model/GrowthModel_HACA.cc
        sootlib/soot_model/soot_chemistry/growth_model/GrowthModel_LIN.h
        sootlib/soot_model/soot_chemistry/growth_model/GrowthModel_LIN.cc
        sootlib/soot_model/soot_chemistry/growth_model/GrowthModel_LL.h
        sootlib/soot_model/soot_chemistry/growth_model/GrowthModel_LL.cc
        sootlib/soot_model/soot_chemistry/growth_model/GrowthModel_NONE.h)

set(NUCLEATION_SRC_FILES
        sootlib/soot_model/soot_chemistry/nucleation_model/NucleationModel.h
        sootlib/soot_model/soot_chemistry/nucleation_model/NucleationModel_LIN.h
        sootlib/soot_model/soot_chemistry/nucleation_model/NucleationModel_LIN.cc
        sootlib/soot_model/soot_chemistry/nucleation_model/NucleationModel_LL.h
        sootlib/soot_model/soot_chemistry/nucleation_model/NucleationModel_LL.cc
        sootlib/soot_model/soot_chemistry/nucleation_model/NucleationModel_NONE.h
        sootlib/soot_model/soot_chemistry/nucleation_model/NucleationModel_PAH.h
        sootlib/soot_model/soot_chemistry/nucleation_model/NucleationModel_PAH.cc)

set(OXIDATION_SRC_FILES
        sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel.h
        sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel_HACA.h
        sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel_HACA.cc
        sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel_LEE_NEOH.h
        sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel_LEE_NEOH.cc
        sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel_LL.h
        sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel_LL.cc
        sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel_NONE.h
        sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel_NSC_NEOH.h
        sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel_NSC_NEOH.cc)

set(SOOTMODELS_SRC_FILES
        soot_model/SootChemistry.h
        soot_model/SootChemistry.cc
        sootlib/soot_model/psd_models/moment_models/logn/PSDModel_LOGN.h
        sootlib/soot_model/psd_models/moment_models/logn/PSDModel_LOGN.cc
        sootlib/soot_model/psd_models/moment_models/momic/PSDModel_MOMIC.h
        sootlib/soot_model/psd_models/moment_models/momic/PSDModel_MOMIC.cc
        sootlib/soot_model/psd_models/moment_models/mono/PSDModel_MONO.h
        sootlib/soot_model/psd_models/moment_models/mono/PSDModel_MONO.cc
        sootlib/soot_model/psd_models/moment_models/qmom/PSDModel_QMOM.h
        sootlib/soot_model/psd_models/moment_models/qmom/PSDModel_QMOM.cc
        sootlib/soot_model/psd_models/sectional_models/sect/PSDModel_SECT.h
        sootlib/soot_model/psd_models/sectional_models/sect/PSDModel_SECT.cc)

set(STATE_SRC_FILES
        state/State.h
        state/State.cc
        state/GasState.h
        state/GasState.cc
        state/MomentState.h
        state/MomentState.cc
        state/SectionalState.h
        state/SectionalState.cc
        state/SootState.h
        state/SootState.cc)

set(SRC_FILES
        soot_model/psdModels/PSDModel.h
        sootModels/modelGenerator.h
        sootModels/modelGenerator.cc
        constants.h
        sootlib/ratio/MassRateRatio.h
        sootlib/ratio/MassRateRatios.h)

set(LIB_FILES
        ../include/extern/eispack/eispack.h
        ../include/extern/eispack/eispack.cc
        ../include/extern/binomial/binomial.h
        ../include/extern/jutil/jutil.h)

# ---- compile all files ----

set(ALL_SRC_FILES
        ${COAGULATION_SRC_FILES}
        ${GROWTH_SRC_FILES}
        ${NUCLEATION_SRC_FILES}
        ${OXIDATION_SRC_FILES}
        ${SOOTMODELS_SRC_FILES}
        ${STATE_SRC_FILES}
        ${SRC_FILES}
        ${LIB_FILES})

add_library(sootlib STATIC ${ALL_SRC_FILES})
