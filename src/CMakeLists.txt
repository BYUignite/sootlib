# ---- set each batch of files ----

set(COAGULATION_SRC_FILES
        sootlib/coagulation_model/CoagulationModel.h
        sootlib/coagulation_model/CoagulationModel_FRENK.h
        sootlib/coagulation_model/CoagulationModel_FRENK.cc
        sootlib/coagulation_model/CoagulationModel_FUCHS.h
        sootlib/coagulation_model/CoagulationModel_FUCHS.cc
        sootlib/coagulation_model/CoagulationModel_LL.h
        sootlib/coagulation_model/CoagulationModel_LL.cc
        sootlib/coagulation_model/CoagulationModel_MOMIC.h
        sootlib/coagulation_model/CoagulationModel_MOMIC.cc)

set(GROWTH_SRC_FILES
        sootlib/growth_model/GrowthModel.h
        sootlib/growth_model/GrowthModel_HACA.h
        sootlib/growth_model/GrowthModel_HACA.cc
        sootlib/growth_model/GrowthModel_LIN.h
        sootlib/growth_model/GrowthModel_LIN.cc
        sootlib/growth_model/GrowthModel_LL.h
        sootlib/growth_model/GrowthModel_LL.cc
        sootlib/growth_model/GrowthModel_NONE.h)

set(NUCLEATION_SRC_FILES
        sootlib/nucleation_model/NucleationModel.h
        sootlib/nucleation_model/NucleationModel_LIN.h
        sootlib/nucleation_model/NucleationModel_LIN.cc
        sootlib/nucleation_model/NucleationModel_LL.h
        sootlib/nucleation_model/NucleationModel_LL.cc
        sootlib/nucleation_model/NucleationModel_NONE.h
        sootlib/nucleation_model/NucleationModel_PAH.h
        sootlib/nucleation_model/NucleationModel_PAH.cc)

set(OXIDATION_SRC_FILES
        sootlib/oxidation_model/OxidationModel.h
        sootlib/oxidation_model/OxidationModel_HACA.h
        sootlib/oxidation_model/OxidationModel_HACA.cc
        sootlib/oxidation_model/OxidationModel_LEE_NEOH.h
        sootlib/oxidation_model/OxidationModel_LEE_NEOH.cc
        sootlib/oxidation_model/OxidationModel_LL.h
        sootlib/oxidation_model/OxidationModel_LL.cc
        sootlib/oxidation_model/OxidationModel_NONE.h
        sootlib/oxidation_model/OxidationModel_NSC_NEOH.h
        sootlib/oxidation_model/OxidationModel_NSC_NEOH.cc)

set(SOOTMODELS_SRC_FILES
        sootlib/soot_model/SootModel_Base.h
        sootlib/soot_model/models/SootModel_LOGN.h
        sootlib/soot_model/models/SootModel_LOGN.cc
        sootlib/soot_model/models/SootModel_MOMIC.h
        sootlib/soot_model/models/SootModel_MOMIC.cc
        sootlib/soot_model/models/SootModel_MONO.h
        sootlib/soot_model/models/SootModel_MONO.cc
        sootlib/soot_model/models/SootModel_QMOM.h
        sootlib/soot_model/models/SootModel_QMOM.cc
        sootlib/soot_model/models/SootModel_SECT.h
        sootlib/soot_model/models/SootModel_SECT.cc
        sootlib/soot_model/static.h)

set(STATE_SRC_FILES
        sootlib/state/InputState.h
        sootlib/state/InputState.cc
        )

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

# ---- optionally include cantera comaptability files ----

set(CANTERACOMPAT_SRC_FILES
        )

if (BUILD_CANTERA_COMPAT)
    set(CANTERACOMPAT_SRC_FILES
            ${CANTERACOMPAT_SRC_FILES}
            sootlib/cantera_compat/cantera_compat.h
            sootlib/cantera_compat/cantera_compat.cc)
endif()

# ---- compile all files ----

set(ALL_SRC_FILES
        ${COAGULATION_SRC_FILES}
        ${GROWTH_SRC_FILES}
        ${NUCLEATION_SRC_FILES}
        ${OXIDATION_SRC_FILES}
        ${SOOTMODELS_SRC_FILES}
        ${STATE_SRC_FILES}
        ${SRC_FILES}
        ${CANTERACOMPAT_SRC_FILES}
        ${LIB_FILES})

add_library(sootlib STATIC ${ALL_SRC_FILES})
