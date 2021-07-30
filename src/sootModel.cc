#include "sootModel.h"

//#include "src/sootModels/psdModels/psdModel_SECT.h"
#include "src/sootModels/psdModels/psdModel_MONO.h"
#include "src/sootModels/psdModels/psdModel_LOGN.h"
#include "src/sootModels/psdModels/psdModel_QMOM.h"
#include "src/sootModels/psdModels/psdModel_MOMIC.h"

using namespace std;
using namespace soot;

sootModel::sootModel(psdMech modelType, int nVar, nucleationMech N, growthMech G, oxidationMech X, coagulationMech C) {

    //---------- set defaults

//    psdMechanism            = psdMech::MONO;
//    nucleationMechanism     = nucleationMech::NONE;
//    growthMechanism         = growthMech::NONE;
//    oxidationMechanism      = oxidationMech::NONE;
//    coagulationMechanism    = coagulationMech::NONE;

    //---------- store requested mechanisms

    this->psdMechanism = modelType;
    this->nucleationMechanism = N;
    this->growthMechanism = G;
    this->oxidationMechanism = X;
    this->coagulationMechanism = C;

    //---------- set PSD model type

    if (psdMechanism == psdMech::MONO) {psd = new psdModel_MONO(sourceTerms, nVar, N, G, X, C);}
    else if (psdMechanism == psdMech::LOGN) {psd = new psdModel_LOGN(sourceTerms, nVar, N, G, X, C);}
    else if (psdMechanism == psdMech::QMOM) {psd = new psdModel_QMOM(sourceTerms, nVar, N, G, X, C);}
    else if (psdMechanism == psdMech::MOMIC) {psd = new psdModel_MOMIC(sourceTerms, nVar, N, G, X, C);}
//    else if (psdMechanism == psdMech::SECT) {psd = new psdModel_SECT(sourceTerms, nVar, N, G, X, C);}
    else throw domain_error("Invalid PSD model type requested");

}

//void sootModel::setPsdModel(psdMech modelType, int nMoms, int nBins) {
//
//    psdMechanism = modelType;
//
//    switch (psdMechanism) {
//        case psdMech::MONO:  psd = new psdModel_MONO(nMoms);
//        case psdMech::LOGN:  psd = new psdModel_LOGN(nMoms);
//        case psdMech::QMOM:  psd = new psdModel_QMOM(nMoms);
//        case psdMech::MOMIC: psd = new psdModel_MOMIC(nMoms);
//        //case psdMech::SECT:  psd = new psdModel_SECT(nBins);
//    }
//}
//
//void sootModel::setSootChemistry(nucleationMech N, growthMech G, oxidationMech X, coagulationMech C) {
//
//    // store requested mechanisms
//    this->nucleationMechanism = N;
//    this->growthMechanism = G;
//    this->oxidationMechanism = X;
//    this->coagulationMechanism = C;
//
//    // create nucleation model with desired mechanism
//    switch (nucleationMechanism) {
//        case nucleationMech::NONE: nuc = new nucleationModel_NONE();
//        case nucleationMech::LL:   nuc = new nucleationModel_LL();
//        case nucleationMech::LIN:  nuc = new nucleationModel_LIN();
//        case nucleationMech::PAH:  nuc = new nucleationModel_PAH();
////        default: throw domain_error("Bad soot nucleation mechanism");
//    }
//
//    // create growth model with desired mechanism
//    switch (growthMechanism) {
//        case growthMech::NONE: grw = new growthModel_NONE();
//        case growthMech::LL:   grw = new growthModel_LL();
//        case growthMech::LIN:  grw = new growthModel_LIN();
//        case growthMech::HACA: grw = new growthModel_HACA();
////        default: throw domain_error("Bad soot growth mechanism");
//    }
//
//    // create oxidation model with desired mechanism
//    switch (oxidationMechanism) {
//        case oxidationMech::NONE:     oxi = new oxidationModel_NONE();
//        case oxidationMech::LL:       oxi = new oxidationModel_LL();
//        case oxidationMech::LEE_NEOH: oxi = new oxidationModel_LEE_NEOH();
//        case oxidationMech::NSC_NEOH: oxi = new oxidationModel_NSC_NEOH();
//        case oxidationMech::HACA:     oxi = new oxidationModel_HACA();
////        default: throw domain_error("Bad soot oxidation model");
//    }
//
//    // create coagulation model with desired mechanism
//    switch (coagulationMechanism) {
//        case coagulationMech::NONE:  coa = new coagulationModel_NONE();
//        case coagulationMech::LL:    coa = new coagulationModel_LL();
//        case coagulationMech::FUCHS: coa = new coagulationModel_FUCHS();
//        case coagulationMech::FRENK: coa = new coagulationModel_FRENK();
////        default: throw domain_error("Bad soot coagulation mechanism");
//    }
//
//}

// TODO update this
void sootModel::calcSourceTerms(state& state) {

    psd->getSourceTermsImplementation(state, *sourceTerms);

}

//void sootModel::getSourceTermsImplementation(state& state, std::ostream* out) const {}

