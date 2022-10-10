#include "sootModels/psdModels/psdModel.h"

#include "sootModels/sootChemistry/nucleationModels/nucleationModel_NONE.h"
#include "sootModels/sootChemistry/nucleationModels/nucleationModel_LL.h"
#include "sootModels/sootChemistry/nucleationModels/nucleationModel_LIN.h"
#include "sootModels/sootChemistry/nucleationModels/nucleationModel_PAH.h"

#include "sootModels/sootChemistry/growthModels/growthModel_NONE.h"
#include "sootModels/sootChemistry/growthModels/growthModel_LL.h"
#include "sootModels/sootChemistry/growthModels/growthModel_LIN.h"
#include "sootModels/sootChemistry/growthModels/growthModel_HACA.h"

#include "sootModels/sootChemistry/oxidationModels/oxidationModel_NONE.h"
#include "sootModels/sootChemistry/oxidationModels/oxidationModel_LL.h"
#include "sootModels/sootChemistry/oxidationModels/oxidationModel_HACA.h"
#include "sootModels/sootChemistry/oxidationModels/oxidationModel_LEE_NEOH.h"
#include "sootModels/sootChemistry/oxidationModels/oxidationModel_NSC_NEOH.h"

#include "sootModels/sootChemistry/coagulationModels/coagulationModel_NONE.h"
#include "sootModels/sootChemistry/coagulationModels/coagulationModel_LL.h"
#include "sootModels/sootChemistry/coagulationModels/coagulationModel_FUCHS.h"
#include "sootModels/sootChemistry/coagulationModels/coagulationModel_FRENK.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

psdModel::psdModel(sourceTermStruct* sourceTerms, int nsoot_, 
                   nucleationMech N, growthMech G, 
                   oxidationMech X, coagulationMech C) {

    nsoot = nsoot_;

    //---------- set nucleation model

    switch (N) {
        case nucleationMech::NONE : nuc = new nucleationModel_NONE(); break;
        case nucleationMech::LL   : nuc = new nucleationModel_LL();   break;
        case nucleationMech::LIN  : nuc = new nucleationModel_LIN();  break;
        case nucleationMech::PAH  : nuc = new nucleationModel_PAH();  break;
        default: throw domain_error("Invalid nucleation model requested");
    }

    //---------- set growth model

    switch (G) {
        case growthMech::NONE : grw = new growthModel_NONE(); break;
        case growthMech::LL   : grw = new growthModel_LL();   break;
        case growthMech::LIN  : grw = new growthModel_LIN();  break;
        case growthMech::HACA : grw = new growthModel_HACA(); break;
        default: throw domain_error("Invalid growth model requested");
    }

    //---------- set oxidation model

    switch (X) {
        case oxidationMech::NONE     : oxi = new oxidationModel_NONE();     break;
        case oxidationMech::LL       : oxi = new oxidationModel_LL();       break;
        case oxidationMech::LEE_NEOH : oxi = new oxidationModel_LEE_NEOH(); break;
        case oxidationMech::NSC_NEOH : oxi = new oxidationModel_NSC_NEOH(); break;
        case oxidationMech::HACA     : oxi = new oxidationModel_HACA();     break;
        default: throw domain_error("Invalid oxidation model requested");
    }

    //---------- set coagulation model

    switch (C) {
        case coagulationMech::NONE  : coa = new coagulationModel_NONE();  break;
        case coagulationMech::LL    : coa = new coagulationModel_LL();    break;
        case coagulationMech::FUCHS : coa = new coagulationModel_FUCHS(); break;
        case coagulationMech::FRENK : coa = new coagulationModel_FRENK(); break;
        default: throw domain_error("Invalid coagulation model requested");
    }
}
