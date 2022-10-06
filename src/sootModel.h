#pragma once

#include "constants.h"
#include "state.h"

#include "sootModels/psdModels/psdModel.h"

/** sootModel class
 *
 *      Main point of contact between sootlib library and the user (external CFD code).
 *
 *      To create/initialize a soot model with desired mechanisms:
 *          1. Create a new sootModel object (initializes with default models)
 *          2. Specify the desired PSD model with setPsdModel function
 *          3. Specify desired soot chemistry with setSootChemistry function
 *
 *      To get source terms //TODO finish this documentation
 *
 */
namespace soot {

class sootModel {

//////////////// DATA MEMBERS /////////////////////

public:

    // stored values for mechanism selections
    psdMech             psdMechanism;
    nucleationMech      nucleationMechanism;
    growthMech          growthMechanism;
    oxidationMech       oxidationMechanism;
    coagulationMech     coagulationMechanism;

    // pointers to selected mechanisms
    psdModel*           psd;

    // source terms storage
    sourceTermStruct* sourceTerms;

//////////////// MEMBER FUNCTIONS /////////////////

public:

    // TODO documentation
    void setSourceTerms(state& state);

//////////////// CONSTRUCTOR /////////////////////////////

public:

    sootModel(psdMech modelType, int nVar,
              nucleationMech N,
              growthMech G,
              oxidationMech X,
              coagulationMech C);

    virtual ~sootModel() = default;

};
} // namespace soot
