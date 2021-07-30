#ifndef SOOTMODEL_H
#define SOOTMODEL_H

#include "src/constants.h"
#include "src/state.h"

#include "src/sootModels/psdModels/psdModel.h"

#include "src/sootModels/sootChemistry/nucleationModels/nucleationModel.h"
#include "src/sootModels/sootChemistry/nucleationModels/nucleationModel_NONE.h"
#include "src/sootModels/sootChemistry/nucleationModels/nucleationModel_LL.h"
#include "src/sootModels/sootChemistry/nucleationModels/nucleationModel_LIN.h"
#include "src/sootModels/sootChemistry/nucleationModels/nucleationModel_PAH.h"

#include "src/sootModels/sootChemistry/growthModels/growthModel.h"
#include "src/sootModels/sootChemistry/growthModels/growthModel_NONE.h"
#include "src/sootModels/sootChemistry/growthModels/growthModel_LL.h"
#include "src/sootModels/sootChemistry/growthModels/growthModel_LIN.h"
#include "src/sootModels/sootChemistry/growthModels/growthModel_HACA.h"

#include "src/sootModels/sootChemistry/oxidationModels/oxidationModel.h"
#include "src/sootModels/sootChemistry/oxidationModels/oxidationModel_NONE.h"
#include "src/sootModels/sootChemistry/oxidationModels/oxidationModel_LL.h"
#include "src/sootModels/sootChemistry/oxidationModels/oxidationModel_HACA.h"
#include "src/sootModels/sootChemistry/oxidationModels/oxidationModel_LEE_NEOH.h"
#include "src/sootModels/sootChemistry/oxidationModels/oxidationModel_NSC_NEOH.h"

#include "src/sootModels/sootChemistry/coagulationModels/coagulationModel.h"
#include "src/sootModels/sootChemistry/coagulationModels/coagulationModel_NONE.h"
#include "src/sootModels/sootChemistry/coagulationModels/coagulationModel_LL.h"
#include "src/sootModels/sootChemistry/coagulationModels/coagulationModel_FUCHS.h"
#include "src/sootModels/sootChemistry/coagulationModels/coagulationModel_FRENK.h"

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
        sourceTermStruct* sourceTerms = new sourceTermStruct();

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

        // TODO documentation
        void calcSourceTerms(state& state);

    //////////////// CONSTRUCTOR /////////////////////////////

    public:

        sootModel(psdMech modelType, int nVar,
                  nucleationMech N,
                  growthMech G,
                  oxidationMech X,
                  coagulationMech C);

        virtual ~sootModel() = default;

    };
}

#endif //SOOTMODEL_H
