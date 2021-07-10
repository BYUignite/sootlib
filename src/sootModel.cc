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

void sootModel::setPsdModel(psdMech modelType, int nMom, int nBins) {

    this->psdMechanism = modelType;

    switch (modelType) {
        case psdMech::MONO:  psd = new psdModel_MONO(nMom);
        case psdMech::LOGN:  psd = new psdModel_LOGN(nMom);
        case psdMech::QMOM:  psd = new psdModel_QMOM(nMom);
        case psdMech::MOMIC: psd = new psdModel_MOMIC(nMom);
        case psdMech::SECT:  psd = new psdModel_SECT(nBins);
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
        case nucleationMech::NONE: nuc = new nucleationModel_NONE();
        case nucleationMech::LL:   nuc = new nucleationModel_LL();
        case nucleationMech::LIN:  nuc = new nucleationModel_LIN();
        case nucleationMech::PAH:  nuc = new nucleationModel_PAH();
//        default: throw domain_error("Bad soot nucleation mechanism");
    }

    // create growth model with desired mechanism
    switch (G) {
        case growthMech::NONE: grw = new growthModel_NONE();
        case growthMech::LL:   grw = new growthModel_LL();
        case growthMech::LIN:  grw = new growthModel_LIN();
        case growthMech::HACA: grw = new growthModel_HACA();
//        default: throw domain_error("Bad soot growth mechanism");
    }

    // create oxidation model with desired mechanism
    switch (X) {
        case oxidationMech::NONE:     oxi = new oxidationModel_NONE();
        case oxidationMech::LL:       oxi = new oxidationModel_LL();
        case oxidationMech::LEE_NEOH: oxi = new oxidationModel_LEE_NEOH();
        case oxidationMech::NSC_NEOH: oxi = new oxidationModel_NSC_NEOH();
        case oxidationMech::HACA:     oxi = new oxidationModel_HACA();
//        default: throw domain_error("Bad soot oxidation model");
    }

    // create coagulation model with desired mechanism
    switch (C) {
        case coagulationMech::NONE:  coa = new coagulationModel_NONE();
        case coagulationMech::LL:    coa = new coagulationModel_LL();
        case coagulationMech::FUCHS: coa = new coagulationModel_FUCHS();
        case coagulationMech::FRENK: coa = new coagulationModel_FRENK();
        default: throw domain_error("Bad soot coagulation mechanism");
    }

}

// TODO update this
void sootModel::calcSourceTerms(state& state) {

//    checkState(state);
//    return getSourceTermsImpl(state, nullptr);

}
