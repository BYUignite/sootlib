#include "sootModel.h"

//#include "src/sootModels/psdModels/psdModel_SECT.h"
#include "sootModels/psdModels/psdModel_MONO.h"
#include "sootModels/psdModels/psdModel_LOGN.h"
#include "sootModels/psdModels/psdModel_QMOM.h"
#include "sootModels/psdModels/psdModel_MOMIC.h"

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

    switch (psdMechanism) {
        case psdMech::MONO  : psd = new psdModel_MONO (sourceTerms, nVar, N, G, X, C); break;
        case psdMech::LOGN  : psd = new psdModel_LOGN (sourceTerms, nVar, N, G, X, C); break;
        case psdMech::QMOM  : psd = new psdModel_QMOM (sourceTerms, nVar, N, G, X, C); break;
        case psdMech::MOMIC : psd = new psdModel_MOMIC(sourceTerms, nVar, N, G, X, C); break;
        //case psdMech::SECT  : psd = new psdModel_SECT (sourceTerms, nVar, N, G, X, C); break;
        default: throw domain_error("Invalid PSD model type requested");
    }
}

////////////////////////////////////////////////////////////////////////////////

void sootModel::calcSourceTerms(state& state) {

    // reset sourceTerms variable
    setSourceTerms();

    // calculate new source terms
    psd->getSourceTermsImplementation(state, sourceTerms);

}

////////////////////////////////////////////////////////////////////////////////

void sootModel::setSourceTerms() {

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
