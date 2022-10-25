#include "sootModel.h"

//#include "src/sootModels/psdModels/psdModel_SECT.h"
#include "sootModels/psdModels/psdModel_MONO.h"
#include "sootModels/psdModels/psdModel_LOGN.h"
#include "sootModels/psdModels/psdModel_QMOM.h"
#include "sootModels/psdModels/psdModel_MOMIC.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

sootModel::sootModel(psdMech modelType, int nsoot_, nucleationMech N, growthMech G, oxidationMech X, coagulationMech C) {

    //---------- store requested mechanisms

    psdMechanism = modelType;
    nucleationMechanism = N;
    growthMechanism = G;
    oxidationMechanism = X;
    coagulationMechanism = C;

    //---------- set PSD model type

    switch (psdMechanism) {
        case psdMech::MONO  : psd = new psdModel_MONO (nsoot_, N, G, X, C); break;
        case psdMech::LOGN  : psd = new psdModel_LOGN (nsoot_, N, G, X, C); break;
        case psdMech::QMOM  : psd = new psdModel_QMOM (nsoot_, N, G, X, C); break;
        case psdMech::MOMIC : psd = new psdModel_MOMIC(nsoot_, N, G, X, C); break;
        //case psdMech::SECT  : psd = new psdModel_SECT (nsoot_, N, G, X, C); break;
        default: throw domain_error("Invalid PSD model type requested");
    }

    //---------- init sourceTermStruct

    sourceTerms = new sourceTermStruct();
    sourceTerms->sootSourceTerms = vector<double>(nsoot_, 0.0);

}

////////////////////////////////////////////////////////////////////////////////

void sootModel::setSourceTerms(state& state) {

    //-----------  reset source term variable values to zero

    for(int i=0; i < psd->nsoot; i++)
        sourceTerms->sootSourceTerms[i] = 0;

    for (int sp=0; sp<(int)gasSp::size; sp++)
        sourceTerms->gasSourceTerms[sp] = 0;

    sourceTerms->pahSourceTerms = vector<double>{(int)pahSp::size, 0.0};

    //-----------  calculate new source terms

    psd->setSourceTerms(state, sourceTerms);

}
