#pragma once

#include "../../constants.h"
#include "../../state.h"

#include "../sootChemistry/nucleationModels/nucleationModel.h"
#include "../sootChemistry/growthModels/growthModel.h"
#include "../sootChemistry/oxidationModels/oxidationModel.h"
#include "../sootChemistry/coagulationModels/coagulationModel.h"

namespace soot {

class psdModel {

//////////////// DATA MEMBERS /////////////////////

public:

    int nMom;                   // for moment models
    int nBin;                   // for sectional models

    nucleationModel*    nuc;    // pointers to mechanisms
    growthModel*        grw;
    oxidationModel*     oxi;
    coagulationModel*   coa;

//////////////// MEMBER FUNCTIONS /////////////////

public:

    virtual void getSourceTermsImplementation(state& state, sourceTermStruct* sourceTerms) const = 0;

//////////////// CONSTRUCTOR /////////////////////////////

public:

    psdModel(sourceTermStruct* sourceTerms, int nVar, 
             nucleationMech N, growthMech G, 
             oxidationMech X, coagulationMech C);

    virtual ~psdModel() = default;

};
} // namespace soot
