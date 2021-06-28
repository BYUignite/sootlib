#include "SootModelGenerator.h"

/* Moment psd_models */
#include "sootlib/soot_model/psd_models/moment_models/logn/PSDModel_LOGN.h"
#include "sootlib/soot_model/psd_models/moment_models/momic/PSDModel_MOMIC.h"
#include "sootlib/soot_model/psd_models/moment_models/mono/PSDModel_MONO.h"
#include "sootlib/soot_model/psd_models/moment_models/qmom/PSDModel_QMOM.h"

/* Bin psd_models */
#include "sootlib/soot_model/psd_models/sectional_models/sect/PSDModel_SECT.h"

/* coagulation psd_models */
#include "sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_FRENK.h"
#include "sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_FUCHS.h"
#include "sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_LL.h"
#include "sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel_NONE.h"

/* growth psd_models */
#include "sootlib/soot_model/soot_chemistry/growth_model/GrowthModel_HACA.h"
#include "sootlib/soot_model/soot_chemistry/growth_model/GrowthModel_LIN.h"
#include "sootlib/soot_model/soot_chemistry/growth_model/GrowthModel_LL.h"
#include "sootlib/soot_model/soot_chemistry/growth_model/GrowthModel_NONE.h"

/* nucleation psd_models */
#include "sootlib/soot_model/soot_chemistry/nucleation_model/NucleationModel_LIN.h"
#include "sootlib/soot_model/soot_chemistry/nucleation_model/NucleationModel_LL.h"
#include "sootlib/soot_model/soot_chemistry/nucleation_model/NucleationModel_NONE.h"
#include "sootlib/soot_model/soot_chemistry/nucleation_model/NucleationModel_PAH.h"

/* oxidation psd_models */
#include "sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel_HACA.h"
#include "sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel_LEE_NEOH.h"
#include "sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel_LL.h"
#include "sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel_NONE.h"
#include "sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel_NSC_NEOH.h"

using namespace std;
using namespace soot;

// Here are the default parameters for the soot model
SootModelGenerator::SootModelGenerator() {
    psdMechanism = PSDMechanism::MONO;
    nucleationMechanism = NucleationMechanism::NONE;
    growthMechanism = GrowthMechanism::NONE;
    oxidationMechanism = OxidationMechanism::NONE;
    coagulationMechanism = CoagulationMechanism::NONE;
}
void SootModelGenerator::setNucleationMechanism(NucleationMechanism mechanism) {
    nucleationMechanism = mechanism;
}
void SootModelGenerator::setGrowthMechanism(GrowthMechanism mechanism) {
    growthMechanism = mechanism;
}
void SootModelGenerator::setOxidationMechanism(OxidationMechanism mechanism) {
    oxidationMechanism = mechanism;
}
void SootModelGenerator::setCoagulationMechanism(CoagulationMechanism mechanism) {
    coagulationMechanism = mechanism;
}
CoagulationModel* SootModelGenerator::makeCoagulationModel() const {
    switch (coagulationMechanism) {
        case CoagulationMechanism::NONE: return new CoagulationModel_NONE();
        case CoagulationMechanism::LL: return new CoagulationModel_LL();
        case CoagulationMechanism::FUCHS: return new CoagulationModel_FUCHS();
        case CoagulationMechanism::FRENK: return new CoagulationModel_FRENK();
        default: throw domain_error("Bad soot coagulation mechanism");
    }
}
GrowthModel* SootModelGenerator::makeGrowthModel() const {
    switch (growthMechanism) {
        case GrowthMechanism::NONE: return new GrowthModel_NONE();
        case GrowthMechanism::LL: return new GrowthModel_LL();
        case GrowthMechanism::LIN: return new GrowthModel_LIN();
        case GrowthMechanism::HACA: return new GrowthModel_HACA();
        default: throw domain_error("Bad soot growth mechanism");
    }
}
NucleationModel* SootModelGenerator::makeNucleationModel() const {
    switch (nucleationMechanism) {
        case NucleationMechanism::NONE: return new NucleationModel_NONE();
        case NucleationMechanism::LL: return new NucleationModel_LL();
        case NucleationMechanism::LIN: return new NucleationModel_LIN();
        case NucleationMechanism::PAH: return new NucleationModel_PAH();
        default: throw domain_error("Bad soot nucleation mechanism");
    }
}
OxidationModel* SootModelGenerator::makeOxidationModel() const {
    switch (oxidationMechanism) {
        case OxidationMechanism::NONE: return new OxidationModel_NONE();
        case OxidationMechanism::LL: return new OxidationModel_LL();
        case OxidationMechanism::LEE_NEOH: return new OxidationModel_LEE_NEOH();
        case OxidationMechanism::NSC_NEOH: return new OxidationModel_NSC_NEOH();
        case OxidationMechanism::HACA: return new OxidationModel_HACA();
        default: throw domain_error("Bad soot oxidation model");
    }
}
void SootModelGenerator::setPSDModel(PSDMechanism modelType) {
    this->psdMechanism = modelType;
}
PSDModel* SootModelGenerator::getModel() const {
    /* create helper psd_models */
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
std::unique_ptr<PSDModel> SootModelGenerator::getModelUnique() const {
    return unique_ptr<PSDModel>(getModel());
}
std::shared_ptr<PSDModel> SootModelGenerator::getModelShared() const {
    return shared_ptr<PSDModel>(getModel());
}
