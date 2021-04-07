#include "SootModelGenerator.h"

/* Moment psd_models */
#include "sootlib/soot_model/psd_models/moment_models/logn/SootModel_LOGN.h"
#include "sootlib/soot_model/psd_models/moment_models/momic/SootModel_MOMIC.h"
#include "sootlib/soot_model/psd_models/moment_models/mono/SootModel_MONO.h"
#include "sootlib/soot_model/psd_models/moment_models/qmom/SootModel_QMOM.h"

/* Bin psd_models */
#include "sootlib/soot_model/psd_models/sectional_models/sect/SootModel_SECT.h"

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

SootModelGenerator::SootModelGenerator() {
    modelType = SootModelType::MONO;
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
unique_ptr<CoagulationModel> SootModelGenerator::getCoagulationModel() const {
    switch (coagulationMechanism) {
        case CoagulationMechanism::NONE: return make_unique<CoagulationModel_NONE>();
        case CoagulationMechanism::LL: return make_unique<CoagulationModel_LL>();
        case CoagulationMechanism::FUCHS: make_unique<CoagulationModel_FUCHS>();
        case CoagulationMechanism::FRENK: make_unique<CoagulationModel_FRENK>();
        default: throw domain_error("Bad soot coagulation mechanism");
    }
}
unique_ptr<GrowthModel> SootModelGenerator::getGrowthModel() const {
    switch (growthMechanism) {
        case GrowthMechanism::NONE: return make_unique<GrowthModel_NONE>();
        case GrowthMechanism::LL: return make_unique<GrowthModel_LL>();
        case GrowthMechanism::LIN: return make_unique<GrowthModel_LIN>();
        case GrowthMechanism::HACA: return make_unique<GrowthModel_HACA>();
        default: throw domain_error("Bad soot growth mechanism");
    }
}
unique_ptr<NucleationModel> SootModelGenerator::getNucleationModel() const {
    switch (nucleationMechanism) {
        case NucleationMechanism::NONE: return make_unique<NucleationModel_NONE>();
        case NucleationMechanism::LL: return make_unique<NucleationModel_LL>();
        case NucleationMechanism::LIN: return make_unique<NucleationModel_LIN>();
        case NucleationMechanism::PAH: return make_unique<NucleationModel_PAH>();
        default: throw domain_error("Bad soot nucleation mechanism");
    }
}
unique_ptr<OxidationModel> SootModelGenerator::getOxidationModel() const {
    switch (oxidationMechanism) {
        case OxidationMechanism::NONE: return make_unique<OxidationModel_NONE>();
        case OxidationMechanism::LL: return make_unique<OxidationModel_LL>();
        case OxidationMechanism::LEE_NEOH: return make_unique<OxidationModel_LEE_NEOH>();
        case OxidationMechanism::NSC_NEOH: return make_unique<OxidationModel_NSC_NEOH>();
        case OxidationMechanism::HACA: return make_unique<OxidationModel_HACA>();
        default: throw domain_error("Bad soot oxidation model");
    }
}
void SootModelGenerator::setModel(SootModelType modelType) {
    this->modelType = modelType;
}
SootModel* SootModelGenerator::getModel() const {
    /* create helper psd_models */
    unique_ptr<CoagulationModel> cm = getCoagulationModel();
    unique_ptr<GrowthModel> gm = getGrowthModel();
    unique_ptr<NucleationModel> nm = getNucleationModel();
    unique_ptr<OxidationModel> om = getOxidationModel();

    /* create and return model ptr */
    switch (modelType) {
        case SootModelType::MONO:
            return SootModel_MONO::getInstance(move(cm),
                                               move(gm),
                                               move(nm),
                                               move(om));
        case SootModelType::LOGN:
            return SootModel_LOGN::getInstance(move(cm),
                                               move(gm),
                                               move(nm),
                                               move(om));
        case SootModelType::MOMIC:
            return SootModel_MOMIC::getInstance(move(cm),
                                                move(gm),
                                                move(nm),
                                                move(om));
        case SootModelType::QMOM:
            return SootModel_QMOM::getInstance(move(cm),
                                               move(gm),
                                               move(nm),
                                               move(om));
        case SootModelType::SECT:
            return SootModel_SECT::getInstance(move(cm),
                                               move(gm),
                                               move(nm),
                                               move(om));
        default: throw domain_error("Bad soot model type");
    }
}
std::unique_ptr<SootModel> SootModelGenerator::getModelUnique() const {
    return unique_ptr<SootModel>(getModel());
}
std::shared_ptr<SootModel> SootModelGenerator::getModelShared() const {
    return shared_ptr<SootModel>(getModel());
}
