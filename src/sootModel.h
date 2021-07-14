#ifndef SOOTMODEL_H
#define SOOTMODEL_H

#include "src/constants.h"
#include "src/state.h"

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
        sootModel*          psd;
        nucleationModel*    nuc;
        growthModel*        grw;
        oxidationModel*     oxi;
        coagulationModel*   coa;

        sourceTermStruct* sourceTerms;

        size_t nMom = 0;    // for moment models
        size_t nBin = 0;    // for sectional models

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

        /** Sets PSD mechanism for the soot model based on user input
         *
         *      @param modelType     type of PSD mechanism
         *      @param nMom          number of moments (for moment based models)
         *      @param nBin          number of bins (for sectional models)
         */
        void setPsdModel(psdMech modelType, int nMom = 0, int nBins = 0);

        /** Selects soot chemistry mechanisms based on user input
         *
         *      @param N     user-requested nucleation mechanism
         *      @param G     user-requested growth mechanism
         *      @param X     user-requested oxidation mechanism
         *      @param C     user-requested coagulation mechanism
         */
        void setSootChemistry(nucleationMech N, growthMech G, oxidationMech X, coagulationMech C);

        virtual void getSourceTermsImplementation(state& state, std::ostream* out) const = 0;

            // TODO documentation
        void calcSourceTerms(state& state);

    //////////////// CONSTRUCTOR /////////////////////////////

    public:

        sootModel();       // Sets default properties of the created soot model
        virtual ~sootModel() = default;

    };
}

#endif //SOOTMODEL_H
