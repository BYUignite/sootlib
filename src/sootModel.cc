#include "sootModel.h"

using namespace std;
using namespace soot;

sootModel::sootModel() {

    // default models
    psdMechanism            = psdMech::MONO;
    nucleationMechanism     = nucleationMech::NONE;
    growthMechanism         = growthMech::NONE;
    oxidationMechanism      = oxidationMech::NONE;
    coagulationMechanism    = coagulationMech::NONE;

}

void sootModel::setPSDModel(psdMech modelType, int nMom, int nBin) {

    this->psdMechanism = modelType;

    switch (modelType) {
        case psdMech::MONO:  psd = new psdModel_MONO();
        case psdMech::LOGN:  psd = new psdModel_LOGN();
        case psdMech::QMOM:  psd = new psdModel_QMOM(nMom);
        case psdMech::MOMIC: psd = new psdModel_MOMIC(nMom);
        case psdMech::SECT:  psd = new psdModel_SECT(nBin);
    }
}

void sootModel::setSootChemistry(nucleationMech N, growthMech G, oxidationMech X, coagulationMech C) {

    // store requested mechanisms
    this->nucleationMechanism = N;
    this->growthMechanism = G;
    this->oxidationMechanism = X;
    this->coagulationMechanism = C;

    // create nucleation model with desired mechanism
    switch (N) {
        case nucleationMech::NONE: N = new nucleationModel_NONE();
        case nucleationMech::LL:   N = new nucleationModel_LL();
        case nucleationMech::LIN:  N = new nucleationModel_LIN();
        case nucleationMech::PAH:  N = new nucleationModel_PAH();
        default: throw domain_error("Bad soot nucleation mechanism");
    }

    // create growth model with desired mechanism
    switch (G) {
        case growthMech::NONE: return new growthModel_NONE();
        case growthMech::LL:   return new growthModel_LL();
        case growthMech::LIN:  return new growthModel_LIN();
        case growthMech::HACA: return new growthModel_HACA();
        default: throw domain_error("Bad soot growth mechanism");
    }

    // create oxidation model with desired mechanism
    switch (X) {
        case oxidationMech::NONE:     return new oxidationModel_NONE();
        case oxidationMech::LL:       return new oxidationModel_LL();
        case oxidationMech::LEE_NEOH: return new oxidationModel_LEE_NEOH();
        case oxidationMech::NSC_NEOH: return new oxidationModel_NSC_NEOH();
        case oxidationMech::HACA:     return new oxidationModel_HACA();
        default: throw domain_error("Bad soot oxidation model");
    }

    // create coagulation model with desired mechanism
    switch (C) {
        case coagulationMech::NONE:  return new coagulationModel_NONE();
        case coagulationMech::LL:    return new coagulationModel_LL();
        case coagulationMech::FUCHS: return new coagulationModel_FUCHS();
        case coagulationMech::FRENK: return new coagulationModel_FRENK();
        default: throw domain_error("Bad soot coagulation mechanism");
    }

}

// TODO update this
void sootModel::calcSourceTerms(state& state) {
    checkState(state);
    return getSourceTermsImpl(state, nullptr);
}
