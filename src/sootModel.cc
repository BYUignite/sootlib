#include "sootModel.h"

//#include "src/sootModels/psdModels/psdModel_SECT.h"
#include "src/sootModels/psdModels/psdModel_MONO.h"
#include "src/sootModels/psdModels/psdModel_LOGN.h"
#include "src/sootModels/psdModels/psdModel_QMOM.h"
#include "src/sootModels/psdModels/psdModel_MOMIC.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

sootModel::sootModel(psdMech modelType, int nVar, nucleationMech N, growthMech G, oxidationMech X, coagulationMech C) {

    //---------- init sourceTermStruct

    sourceTerms = new sourceTermStruct();

    //---------- store requested mechanisms

    psdMechanism = modelType;
    nucleationMechanism = N;
    growthMechanism = G;
    oxidationMechanism = X;
    coagulationMechanism = C;

    //---------- set PSD model type

    if      (psdMechanism == psdMech::MONO)  { psd = new psdModel_MONO (sourceTerms, nVar, N, G, X, C);}
    else if (psdMechanism == psdMech::LOGN)  { psd = new psdModel_LOGN (sourceTerms, nVar, N, G, X, C);}
    else if (psdMechanism == psdMech::QMOM)  { psd = new psdModel_QMOM (sourceTerms, nVar, N, G, X, C);}
    else if (psdMechanism == psdMech::MOMIC) { psd = new psdModel_MOMIC(sourceTerms, nVar, N, G, X, C);}
//    else if (psdMechanism == psdMech::SECT) {psd = new psdModel_SECT(sourceTerms, nVar, N, G, X, C);}
    else throw domain_error("Invalid PSD model type requested");

}

////////////////////////////////////////////////////////////////////////////////

void sootModel::calcSourceTerms(state& state) {

    // reset sourceTerms variable
    resetSourceTerms();

    // calculate new source terms
    psd->getSourceTermsImplementation(state, sourceTerms);

}

////////////////////////////////////////////////////////////////////////////////

void sootModel::resetSourceTerms() {

    // soot source terms
    for(int i=0; i < psd->nMom; i++)
        sourceTerms->sootSourceTerms.at(i) = 0;

    // gas source terms
    for (auto const& x : sourceTerms->gasSourceTerms) {
        gasSp sp = x.first;
        sourceTerms->gasSourceTerms.at(sp) = 0;
    }

    // pah source terms
    for (auto const& x : sourceTerms->pahSourceTerms) {
        pahSp sp = x.first;
        sourceTerms->pahSourceTerms.at(sp) = 0;
    }

}