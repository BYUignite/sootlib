#include "sootModel.h"

//#include "src/sootModels/psdModels/psdModel_SECT.h"
#include "src/sootModels/psdModels/psdModel_MONO.h"
#include "src/sootModels/psdModels/psdModel_LOGN.h"
#include "src/sootModels/psdModels/psdModel_QMOM.h"
#include "src/sootModels/psdModels/psdModel_MOMIC.h"

using namespace std;
using namespace soot;

sootModel::sootModel(psdMech modelType, int nVar, nucleationMech N, growthMech G, oxidationMech X, coagulationMech C) {

    //---------- store requested mechanisms

    psdMechanism = modelType;
    nucleationMechanism = N;
    growthMechanism = G;
    oxidationMechanism = X;
    coagulationMechanism = C;

    //---------- set PSD model type

    if (psdMechanism == psdMech::MONO) {psd = new psdModel_MONO(sourceTerms, nVar, N, G, X, C);}
    else if (psdMechanism == psdMech::LOGN) {psd = new psdModel_LOGN(sourceTerms, nVar, N, G, X, C);}
    else if (psdMechanism == psdMech::QMOM) {psd = new psdModel_QMOM(sourceTerms, nVar, N, G, X, C);}
    else if (psdMechanism == psdMech::MOMIC) {psd = new psdModel_MOMIC(sourceTerms, nVar, N, G, X, C);}
//    else if (psdMechanism == psdMech::SECT) {psd = new psdModel_SECT(sourceTerms, nVar, N, G, X, C);}
    else throw domain_error("Invalid PSD model type requested");

}

////////////////////////////////////////////////////////////////////////////////

// TODO update this
void sootModel::calcSourceTerms(state& state) {

    psd->getSourceTermsImplementation(state, *sourceTerms);

}