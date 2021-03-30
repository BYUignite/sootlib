# ---- set each batch of files ----

set(COAGULATION_SRC_FILES
        sootlib/coagulation_model/CoagulationModel.h
        sootlib/coagulation_model/CoagulationModel_FRENK.h
        sootlib/coagulation_model/CoagulationModel_FRENK.cpp
        sootlib/coagulation_model/CoagulationModel_FUCHS.h
        sootlib/coagulation_model/CoagulationModel_FUCHS.cpp
        sootlib/coagulation_model/CoagulationModel_LL.h
        sootlib/coagulation_model/CoagulationModel_LL.cpp)

set(GROWTH_SRC_FILES
        sootlib/growth_model/GrowthModel.h
        sootlib/growth_model/GrowthModel_HACA.h
        sootlib/growth_model/GrowthModel_HACA.cpp
        sootlib/growth_model/GrowthModel_LIN.h
        sootlib/growth_model/GrowthModel_LIN.cpp
        sootlib/growth_model/GrowthModel_LL.h
        sootlib/growth_model/GrowthModel_LL.cpp
        sootlib/growth_model/GrowthModel_NONE.h)

set(NUCLEATION_SRC_FILES
        sootlib/nucleation_model/NucleationModel.h
        sootlib/nucleation_model/NucleationModel_LIN.h
        sootlib/nucleation_model/NucleationModel_LIN.cpp
        sootlib/nucleation_model/NucleationModel_LL.h
        sootlib/nucleation_model/NucleationModel_LL.cpp
        sootlib/nucleation_model/NucleationModel_NONE.h
        sootlib/nucleation_model/NucleationModel_PAH.h
        sootlib/nucleation_model/NucleationModel_PAH.cpp)

set(OXIDATION_SRC_FILES
        sootlib/oxidation_model/OxidationModel.h
        sootlib/oxidation_model/OxidationModel_HACA.h
        sootlib/oxidation_model/OxidationModel_HACA.cpp
        sootlib/oxidation_model/OxidationModel_LEE_NEOH.h
        sootlib/oxidation_model/OxidationModel_LEE_NEOH.cpp
        sootlib/oxidation_model/OxidationModel_LL.h
        sootlib/oxidation_model/OxidationModel_LL.cpp
        sootlib/oxidation_model/OxidationModel_NONE.h
        sootlib/oxidation_model/OxidationModel_NSC_NEOH.h
        sootlib/oxidation_model/OxidationModel_NSC_NEOH.cpp)

set(SOOTMODELS_SRC_FILES
        sootlib/soot_model/SootModel_Base.h
        sootlib/soot_model/moment/SootModel_LOGN.h
        sootlib/soot_model/moment/SootModel_LOGN.cpp
        sootlib/soot_model/moment/SootModel_MOMIC.h
        sootlib/soot_model/moment/SootModel_MOMIC.cpp
        sootlib/soot_model/moment/SootModel_MONO.h
        sootlib/soot_model/moment/SootModel_MONO.cpp
        sootlib/soot_model/moment/SootModel_QMOM.h
        sootlib/soot_model/moment/SootModel_QMOM.cpp
        sootlib/soot_model/bin/SootModel_SECT.h
        sootlib/soot_model/bin/SootModel_SECT.cpp)

set(STATE_SRC_FILES
        sootlib/state/BaseState.h
        sootlib/state/BaseState.cpp
        sootlib/state/BinState.h
        sootlib/state/BinState.cpp
        sootlib/state/MomentState.h
        sootlib/state/MomentState.cpp)

set(SRC_FILES
        sootlib/soot_model/moment/MomentSootModel.h
        sootlib/soot_model/bin/BinSootModel.h
        sootlib/soot_model/generator/SootModelGenerator.h
        sootlib/soot_model/generator/SootModelGenerator.cpp
        sootlib/soot_model/generator/MomentSootModelGenerator.h
        sootlib/soot_model/generator/MomentSootModelGenerator.cpp
        sootlib/soot_model/generator/BinSootModelGenerator.h
        sootlib/soot_model/generator/BinSootModelGenerator.cpp
        sootlib/static.h
        sootlib/SourceTerms.h
        sootlib/MassRateRatio.h)

# ---- optionally include cantera comaptability files ----

set(CANTERACOMPAT_SRC_FILES
        )

if (BUILD_CANTERA_COMPAT)
    set(CANTERACOMPAT_SRC_FILES
            ${CANTERACOMPAT_SRC_FILES}
            sootlib/cantera_compat/cantera_compat.h
            sootlib/cantera_compat/cantera_compat.cpp)
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
        ${CANTERACOMPAT_SRC_FILES})

add_library(sootlib STATIC ${ALL_SRC_FILES})
