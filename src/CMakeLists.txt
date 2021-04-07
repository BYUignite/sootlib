# ---- set each batch of files ----

set(COAGULATION_SRC_FILES
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel.h
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_FRENK.h
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_FRENK.cc
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_FUCHS.h
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_FUCHS.cc
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_LL.h
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_LL.cc
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_MOMIC.h
        sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_MOMIC.cc)

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
        sootlib/soot_model/SootChemistry.h
        sootlib/soot_model/psd_models/moment_models/logn/SootModel_LOGN.h
        sootlib/soot_model/psd_models/moment_models/logn/SootModel_LOGN.cc
        sootlib/soot_model/psd_models/moment_models/momic/SootModel_MOMIC.h
        sootlib/soot_model/psd_models/moment_models/momic/SootModel_MOMIC.cc
        sootlib/soot_model/psd_models/moment_models/mono/SootModel_MONO.h
        sootlib/soot_model/psd_models/moment_models/mono/SootModel_MONO.cc
        sootlib/soot_model/psd_models/moment_models/qmom/SootModel_QMOM.h
        sootlib/soot_model/psd_models/moment_models/qmom/SootModel_QMOM.cc
        sootlib/soot_model/psd_models/sectional_models/sect/SootModel_SECT.h
        sootlib/soot_model/psd_models/sectional_models/sect/SootModel_SECT.cc
        sootlib/soot_model/static.h)

set(STATE_SRC_FILES
        sootlib/state/State.h
        sootlib/state/State.cc
        sootlib/state/GasState.h
        sootlib/state/GasState.cc
        sootlib/state/MomentState.h
        sootlib/state/MomentState.cc
        sootlib/state/PAHState.h
        sootlib/state/PAHState.cc
        sootlib/state/SectionalState.h
        sootlib/state/SectionalState.cc
        sootlib/state/SootState.h
        sootlib/state/SootState.cc)

set(SRC_FILES
        sootlib/soot_model/SootModel.h
        sootlib/soot_model/generator/SootModelGenerator.h
        sootlib/soot_model/generator/SootModelGenerator.cc
        sootlib/static.h
        sootlib/SourceTerms.h
        sootlib/MassRateRatio.h
        sootlib/MassRateRatios.h)

set(LIB_FILES
        lib/eispack/eispack.h
        lib/eispack/eispack.cc)

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
