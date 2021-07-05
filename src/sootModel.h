#ifndef BASESOOTMODELFACTORY_H
#define BASESOOTMODELFACTORY_H

#include <memory>
#include <vector>

#include "src/constants.h"
#include "src/state.h"

#include "src/sootModels/psdModels/psdModel.h"
#include "src/sootModels/psdModels/psdModel_SECT.h"
#include "src/sootModels/psdModels/psdModel_MONO.h"
#include "src/sootModels/psdModels/psdModel_LOGN.h"
#include "src/sootModels/psdModels/psdModel_QMOM.h"
#include "src/sootModels/psdModels/psdModel_MOMIC.h"

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
 *      To get source terms //TODO finish this
 *
 */
namespace soot {

    class sootModel {

    //////////////// CONSTRUCTOR /////////////////////////////

    public:

        sootModel();       // Sets default properties of the created soot model


    //////////////// DATA MEMBERS /////////////////////

    private:

        // stored values for mechanism selections; probably not needed
        psdMech             psdMechanism;
        nucleationMech      nucleationMechanism;
        growthMech          growthMechanism;
        oxidationMech       oxidationMechanism;
        coagulationMech     coagulationMechanism;

        // pointers to selected mechanisms
        psdModel*           psd;
        nucleationModel*    nuc;
        growthModel*        grw;
        oxidationModel*     oxi;
        coagulationModel*   coa;

    public:

        sourceTermStruct* sourceTerms;

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

        /** Sets PSD mechanism for the soot model based on user input
         *
         *      @param modelType     type of PSD mechanism
         *      @param nMom          number of moments (for moment based models)
         *      @param nBin          number of bins (for sectional models)
         */
        void setPSDModel(psdMech modelType, int nMom = 0, int nBin = 0);

        /** Selects soot chemistry mechanisms based on user input
         *
         *      @param N     user-requested nucleation mechanism
         *      @param G     user-requested growth mechanism
         *      @param X     user-requested oxidation mechanism
         *      @param C     user-requested coagulation mechanism
         */
        void setSootChemistry(nucleationMech N, growthMech G, oxidationMech X, coagulationMech C);

        // TODO documentation
        void calcSourceTerms(state& state);

    };
}

#endif //BASESOOTMODELFACTORY_H
