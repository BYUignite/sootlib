#pragma once

#include "sootDefs.h"
#include "state.h"

#include "sootModels/sootChemistry/nucleationModels/nucleationModel.h"
#include "sootModels/sootChemistry/growthModels/growthModel.h"
#include "sootModels/sootChemistry/oxidationModels/oxidationModel.h"
#include "sootModels/sootChemistry/coagulationModels/coagulationModel.h"

#include <vector>

////////////////////////////////////////////////////////////////////////////////

namespace soot {

class sootModel {

    //////////////// DATA MEMBERS /////////////////////

    size_t            nsoot;  // # of soot variables: moments or sections

    nucleationModel  *nucl;   // chemical mechanisms ...
    growthModel      *grow;
    oxidationModel   *oxid;
    coagulationModel *coag;


    //////////////// MEMBER FUNCTIONS /////////////////

public:

    virtual void getSourceTerms(const state &stt, 
                                std::vector<double> &sootSources,
                                std::vector<double> &gasSources,
                                std::vector<double> &pahSources) const = 0;

    //////////////// CONSTRUCTOR //////////////////////

    sootModel(){};

    sootModel(size_t nsoot_,
              nucleationModel  *nucl_,
              oxidationModel   *oxid_,
              growthModel      *grow_,
              coagulationModel *coag_) :
        nsoot(nsoot_), nucl(nucl_), oxid(oxid_), grow(grow_), coag(coag_) {}

    virtual ~sootModel() {};

};
} // namespace soot
