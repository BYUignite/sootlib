#include "modelGenerator.h"

/* Moment psdModels */
#include "src/soot_model/psd_models/PSDModel_LOGN.h"
#include "src/soot_model/psd_models/PSDModel_MOMIC.h"
#include "src/soot_model/psd_models/PSDModel_MONO.h"
#include "src/soot_model/psd_models/PSDModel_QMOM.h"

/* Bin psdModels */
#include "src/soot_model/psd_models/PSDModel_SECT.h"

/* coagulation psdModels */
#include "src/soot_model/soot_chemistry/coagulation_model/CoagulationModel_FRENK.h"
#include "src/soot_model/soot_chemistry/coagulation_model/CoagulationModel_FUCHS.h"
#include "src/soot_model/soot_chemistry/coagulation_model/CoagulationModel_LL.h"
#include "src/soot_model/soot_chemistry/coagulation_model/CoagulationModel_NONE.h"

/* growth psdModels */
#include "src/soot_model/soot_chemistry/growth_model/GrowthModel_HACA.h"
#include "src/soot_model/soot_chemistry/growth_model/GrowthModel_LIN.h"
#include "src/soot_model/soot_chemistry/growth_model/GrowthModel_LL.h"
#include "src/soot_model/soot_chemistry/growth_model/GrowthModel_NONE.h"

/* nucleation psdModels */
#include "src/soot_model/soot_chemistry/nucleation_model/NucleationModel_LIN.h"
#include "src/soot_model/soot_chemistry/nucleation_model/NucleationModel_LL.h"
#include "src/soot_model/soot_chemistry/nucleation_model/NucleationModel_NONE.h"
#include "src/soot_model/soot_chemistry/nucleation_model/NucleationModel_PAH.h"

/* oxidation psdModels */
#include "src/soot_model/soot_chemistry/oxidation_model/OxidationModel_HACA.h"
#include "src/soot_model/soot_chemistry/oxidation_model/OxidationModel_LEE_NEOH.h"
#include "src/soot_model/soot_chemistry/oxidation_model/OxidationModel_LL.h"
#include "src/soot_model/soot_chemistry/oxidation_model/OxidationModel_NONE.h"
#include "src/soot_model/soot_chemistry/oxidation_model/OxidationModel_NSC_NEOH.h"

using namespace std;
using namespace soot;

// Here are the default parameters for the soot model
modelGenerator::modelGenerator() {
    psdMechanism = PSDMechanism::MONO;
    nucleationMechanism = NucleationMechanism::NONE;
    growthMechanism = GrowthMechanism::NONE;
    oxidationMechanism = OxidationMechanism::NONE;
    coagulationMechanism = CoagulationMechanism::NONE;
}
void modelGenerator::setNucleationMechanism(NucleationMechanism mechanism) {
    nucleationMechanism = mechanism;
}
void modelGenerator::setGrowthMechanism(GrowthMechanism mechanism) {
    growthMechanism = mechanism;
}
void modelGenerator::setOxidationMechanism(OxidationMechanism mechanism) {
    oxidationMechanism = mechanism;
}
void modelGenerator::setCoagulationMechanism(CoagulationMechanism mechanism) {
    coagulationMechanism = mechanism;
}
CoagulationModel* modelGenerator::makeCoagulationModel() const {
    switch (coagulationMechanism) {
        case CoagulationMechanism::NONE: return new CoagulationModel_NONE();
        case CoagulationMechanism::LL: return new CoagulationModel_LL();
        case CoagulationMechanism::FUCHS: return new CoagulationModel_FUCHS();
        case CoagulationMechanism::FRENK: return new CoagulationModel_FRENK();
        default: throw domain_error("Bad soot coagulation mechanism");
    }
}
GrowthModel* modelGenerator::makeGrowthModel() const {
    switch (growthMechanism) {
        case GrowthMechanism::NONE: return new GrowthModel_NONE();
        case GrowthMechanism::LL: return new GrowthModel_LL();
        case GrowthMechanism::LIN: return new GrowthModel_LIN();
        case GrowthMechanism::HACA: return new GrowthModel_HACA();
        default: throw domain_error("Bad soot growth mechanism");
    }
}
NucleationModel* modelGenerator::makeNucleationModel() const {
    switch (nucleationMechanism) {
        case NucleationMechanism::NONE: return new NucleationModel_NONE();
        case NucleationMechanism::LL: return new NucleationModel_LL();
        case NucleationMechanism::LIN: return new NucleationModel_LIN();
        case NucleationMechanism::PAH: return new NucleationModel_PAH();
        default: throw domain_error("Bad soot nucleation mechanism");
    }
}
OxidationModel* modelGenerator::makeOxidationModel() const {
    switch (oxidationMechanism) {
        case OxidationMechanism::NONE: return new OxidationModel_NONE();
        case OxidationMechanism::LL: return new OxidationModel_LL();
        case OxidationMechanism::LEE_NEOH: return new OxidationModel_LEE_NEOH();
        case OxidationMechanism::NSC_NEOH: return new OxidationModel_NSC_NEOH();
        case OxidationMechanism::HACA: return new OxidationModel_HACA();
        default: throw domain_error("Bad soot oxidation model");
    }
}
void modelGenerator::setPSDModel(PSDMechanism modelType) {
    this->psdMechanism = modelType;
}
PSDModel* modelGenerator::getModel() const {
    /* create helper psdModels */
    auto cm = makeCoagulationModel();
    auto gm = makeGrowthModel();
    auto nm = makeNucleationModel();
    auto om = makeOxidationModel();
    auto sootChemistry = SootChemistry(cm, gm, nm, om);

    /* create and return model ptr */
    switch (psdMechanism) {
        case PSDMechanism::MONO: return new PSDModel_MONO(sootChemistry);
        case PSDMechanism::LOGN: return new PSDModel_LOGN(sootChemistry);
        case PSDMechanism::MOMIC: return new PSDModel_MOMIC(sootChemistry);
        case PSDMechanism::QMOM: return new PSDModel_QMOM(sootChemistry);
        case PSDMechanism::SECT: return new PSDModel_SECT(sootChemistry);
        default: throw domain_error("Bad soot model type");
    }
}
std::unique_ptr<PSDModel> modelGenerator::getModelUnique() const {
    return unique_ptr<PSDModel>(getModel());
}
std::shared_ptr<PSDModel> modelGenerator::getModelShared() const {
    return shared_ptr<PSDModel>(getModel());
}
