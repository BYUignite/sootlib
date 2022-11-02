#pragma once

#include "sootDefs.h"
#include "state.h"

#include "nucleationModels/nucleationModel.h"
#include "growthModels/growthModel.h"
#include "oxidationModels/oxidationModel.h"
#include "coagulationModels/coagulationModel.h"

#include <vector>

////////////////////////////////////////////////////////////////////////////////

namespace soot {

class sootModel {

    //////////////// DATA MEMBERS /////////////////////

public:

    size_t            nsoot;  // # of soot variables: moments or sections

    nucleationModel  *nucl;   // chemical mechanisms ...
    growthModel      *grow;
    oxidationModel   *oxid;
    coagulationModel *coag;

    bool    mechsNewedHere;  // flag to delete "new" objects

    psdMech psdMechType;     // one of MONO, LOGN, QMOM, MOMIC, SECT, etc.

    //----------- for the SECT model interface

    std::vector<double> mBins; 

    //////////////// MEMBER FUNCTIONS /////////////////

    virtual void getSourceTerms(state &state, 
                                std::vector<double> &sootSources,
                                std::vector<double> &gasSources,
                                std::vector<double> &pahSources) const = 0;

    void checkSpec();

    //////////////// CONSTRUCTOR //////////////////////

    sootModel(size_t            nsoot_,
              nucleationModel  *nucl_,
              growthModel      *grow_,
              oxidationModel   *oxid_,
              coagulationModel *coag_);

    sootModel(size_t          nsoot_,
              nucleationMech  Nmech,
              growthMech      Gmech,
              oxidationMech   Omech,
              coagulationMech Cmech);

    virtual ~sootModel() {
        if(mechsNewedHere){
            delete(nucl);
            delete(grow);
            delete(oxid);
            delete(coag);
        }
    }

};
} // namespace soot
