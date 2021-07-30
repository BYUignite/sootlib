#ifndef PSDMODEL_H
#define PSDMODEL_H

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

namespace soot {

    class psdModel {

    //////////////// DATA MEMBERS /////////////////////

    public:

        int nMom;    // for moment models
        int nBin;    // for sectional models

        // pointers to selected mechanisms
        nucleationModel*    nuc;
        growthModel*        grw;
        oxidationModel*     oxi;
        coagulationModel*   coa;

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

        virtual void getSourceTermsImplementation(state& state, sourceTermStruct& sourceTerms) const = 0;


        //////////////// CONSTRUCTOR /////////////////////////////

    public:

        psdModel(sourceTermStruct* sourceTerms, int nVar, nucleationMech N, growthMech G, oxidationMech X, coagulationMech C);

        virtual ~psdModel() = default;

    };

}


#endif //PSDMODEL_H
