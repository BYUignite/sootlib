set(COAGULATION_SRC_FILES
        coagulation_model/CoagulationModel.h
        coagulation_model/CoagulationModel_FRENK.h
        coagulation_model/CoagulationModel_FRENK.cpp
        coagulation_model/CoagulationModel_FUCHS.h
        coagulation_model/CoagulationModel_FUCHS.cpp
        coagulation_model/CoagulationModel_LL.h
        coagulation_model/CoagulationModel_LL.cpp)

set(GROWTH_SRC_FILES
        growth_model/GrowthModel.h
        growth_model/GrowthModel_HACA.h
        growth_model/GrowthModel_HACA.cpp
        growth_model/GrowthModel_LIN.h
        growth_model/GrowthModel_LIN.cpp
        growth_model/GrowthModel_LL.h
        growth_model/GrowthModel_LL.cpp
        growth_model/GrowthModel_NONE.h)

set(NUCLEATION_SRC_FILES
        nucleation_model/NucleationModel.h
        nucleation_model/NucleationModel_LIN.h
        nucleation_model/NucleationModel_LIN.cpp
        nucleation_model/NucleationModel_LL.h
        nucleation_model/NucleationModel_LL.cpp
        nucleation_model/NucleationModel_NONE.h
        nucleation_model/NucleationModel_PAH.h
        nucleation_model/NucleationModel_PAH.cpp)

set(OXIDATION_SRC_FILES
        oxidation_model/OxidationModel.h
        oxidation_model/OxidationModel_HACA.h
        oxidation_model/OxidationModel_HACA.cpp
        oxidation_model/OxidationModel_LEE_NEOH.h
        oxidation_model/OxidationModel_LEE_NEOH.cpp
        oxidation_model/OxidationModel_LL.h
        oxidation_model/OxidationModel_LL.cpp
        oxidation_model/OxidationModel_NONE.h
        oxidation_model/OxidationModel_NSC_NEOH.h
        oxidation_model/OxidationModel_NSC_NEOH.cpp)

set(SOOTMODELS_SRC_FILES
        soot_models/SootModel_Base.h
        soot_models/SootModel_Base.cpp
        soot_models/SootModel_LOGN.h
        soot_models/SootModel_LOGN.cpp
        soot_models/SootModel_MOMIC.h
        soot_models/SootModel_MOMIC.cpp
        soot_models/SootModel_MONO.h
        soot_models/SootModel_MONO.cpp
        soot_models/SootModel_QMOM.h
        soot_models/SootModel_QMOM.cpp
        soot_models/SootModel_SECT.h
        soot_models/SootModel_SECT.cpp)

set(STATE_SRC_FILES
        state/GasState.h
        state/GasState.cpp
        state/SootState.h
        state/SootState.h)

set(SRC_FILES
        SootModel.h
        SootModelFactory.h
        SootModelFactory.cpp
        static.h)

set(CANTERACOMPAT_SRC_FILES
        )

if (BUILD_CANTERA_COMPAT)
    set(CANTERACOMPAT_SRC_FILES
            ${CANTERACOMPAT_SRC_FILES}
            cantera_compat/cantera_compat.h
            cantera_compat/cantera_compat.cpp)
endif()

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
