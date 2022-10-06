#pragma once

#include "constants.h"
#include "state.h"

#include "sootModels/sootChemistry/nucleationModels/nucleationModel.h"
#include "sootModels/sootChemistry/growthModels/growthModel.h"
#include "sootModels/sootChemistry/oxidationModels/oxidationModel.h"
#include "sootModels/sootChemistry/coagulationModels/coagulationModel.h"

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

    virtual void setSourceTerms(state& state, sourceTermStruct* sourceTerms) const = 0;

//////////////// CONSTRUCTOR /////////////////////////////

    psdModel(sourceTermStruct* sourceTerms, int nVar, 
             nucleationMech N, growthMech G, 
             oxidationMech X, coagulationMech C);

    virtual ~psdModel() = default;

};
} // namespace soot
