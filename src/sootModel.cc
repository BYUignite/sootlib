#include "sootModel.h"

#include "nucleationModels/nucleationModel_NONE.h"
#include "nucleationModels/nucleationModel_LL.h"
#include "nucleationModels/nucleationModel_LIN.h"
#include "nucleationModels/nucleationModel_PAH.h"

#include "growthModels/growthModel_NONE.h"
#include "growthModels/growthModel_LL.h"
#include "growthModels/growthModel_LIN.h"
#include "growthModels/growthModel_HACA.h"

#include "oxidationModels/oxidationModel_NONE.h"
#include "oxidationModels/oxidationModel_LL.h"
#include "oxidationModels/oxidationModel_HACA.h"
#include "oxidationModels/oxidationModel_LEE_NEOH.h"
#include "oxidationModels/oxidationModel_NSC_NEOH.h"

#include "coagulationModels/coagulationModel_NONE.h"
#include "coagulationModels/coagulationModel_FM.h"
#include "coagulationModels/coagulationModel_CONTINUUM.h"
#include "coagulationModels/coagulationModel_HM.h"
#include "coagulationModels/coagulationModel_FUCHS.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////
///
/// Constructor taking pointers to chemistry models as input.
/// User creates these pointers nominally by "new-ing" them.
///
/// @param \input nsoot_ number of soot variables (moments or sections)
/// @param \input nucl_  pointer to nucleation model.
/// @param \input grow_  pointer to growth model.
/// @param \input oxid_  pointer to oxidation model.
/// @param \input coag_  pointer to coagulation model.
///
////////////////////////////////////////////////////////////////////////////////

sootModel::sootModel(size_t            nsoot_,
                     nucleationModel  *nucl_,
                     growthModel      *grow_,
                     oxidationModel   *oxid_,
                     coagulationModel *coag_) :
        nsoot(nsoot_), nucl(nucl_), grow(grow_), oxid(oxid_), coag(coag_), 
        mechsNewedHere(false) {
        checkSpec();
        nucl->SM = this;
        grow->SM = this;
        oxid->SM = this;
        coag->SM = this;
}


////////////////////////////////////////////////////////////////////////////////
///
/// Constructor taking enumerations names as input.
/// Chemistry pointers are created (new-ed) here based on those enumerations.
///
/// @param \input nsoot_ number of soot variables (moments or sections)
/// @param \input Nmech  one of enum class nucleationMech in sootDefs.h
/// @param \input Gmech  one of enum class growthMech in sootDefs.h
/// @param \input Omech  one of enum class oxidationMech in sootDefs.h
/// @param \input Cmech  one of enum class coagulationMech in sootDefs.h
///
////////////////////////////////////////////////////////////////////////////////

sootModel::sootModel(size_t          nsoot_,
                     nucleationMech  Nmech,
                     growthMech      Gmech,
                     oxidationMech   Omech,
                     coagulationMech Cmech) : nsoot(nsoot_), mechsNewedHere(true) {

    //---------- set nucleation model

    switch (Nmech) {
        case nucleationMech::NONE : nucl = new nucleationModel_NONE(); break;
        case nucleationMech::LL   : nucl = new nucleationModel_LL();   break;
        case nucleationMech::LIN  : nucl = new nucleationModel_LIN();  break;
        case nucleationMech::PAH  : nucl = new nucleationModel_PAH();  break;
        default: throw domain_error("Invalid nucleation model requested");
    }

    //---------- set growth model

    switch (Gmech) {
        case growthMech::NONE : grow = new growthModel_NONE(); break;
        case growthMech::LL   : grow = new growthModel_LL();   break;
        case growthMech::LIN  : grow = new growthModel_LIN();  break;
        case growthMech::HACA : grow = new growthModel_HACA(); break;
        default: throw domain_error("Invalid growth model requested");
    }

    //---------- set oxidation model

    switch (Omech) {
        case oxidationMech::NONE     : oxid = new oxidationModel_NONE();     break;
        case oxidationMech::LL       : oxid = new oxidationModel_LL();       break;
        case oxidationMech::LEE_NEOH : oxid = new oxidationModel_LEE_NEOH(); break;
        case oxidationMech::NSC_NEOH : oxid = new oxidationModel_NSC_NEOH(); break;
        case oxidationMech::HACA     : oxid = new oxidationModel_HACA();     break;
        default: throw domain_error("Invalid oxidation model requested");
    }

    //---------- set coagulation model

    switch (Cmech) {
        case coagulationMech::NONE      : coag = new coagulationModel_NONE();      break;
        case coagulationMech::FM        : coag = new coagulationModel_FM();        break;
        case coagulationMech::CONTINUUM : coag = new coagulationModel_CONTINUUM(); break;
        case coagulationMech::HM        : coag = new coagulationModel_HM();        break;
        case coagulationMech::FUCHS     : coag = new coagulationModel_FUCHS();     break;
        default: throw domain_error("Invalid coagulation model requested");
    }

    //----------- 

    nucl->SM = this;
    grow->SM = this;
    oxid->SM = this;
    coag->SM = this;

    //----------- 

    checkSpec();
}

////////////////////////////////////////////////////////////////////////////////
///
/// Verify the specification, HACA validity.
///
////////////////////////////////////////////////////////////////////////////////

void sootModel::checkSpec() {

    if((grow->mechType==growthMech::HACA    && oxid->mechType!=oxidationMech::HACA) ||
       (oxid->mechType==oxidationMech::HACA && grow->mechType!=growthMech::HACA))
        throw domain_error("Invalid model combination: HACA surface growth must pair with HACA oxid and vice-versa");
}
