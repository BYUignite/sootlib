#pragma once

#include "sootModel.h"
#include "sootDefs.h"
#include "state.h"

namespace soot {

class sootModel_MONO : public sootModel {

    //////////////// DATA MEMBERS /////////////////////

    //////////////// MEMBER FUNCTIONS /////////////////

public:

    virtual void getSourceTerms(const state &stt, 
                                std::vector<double> &sootSources,
                                std::vector<double> &gasSources) const;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    sootModel_MONO(size_t nsoot_,
                   nucleationModel  *nucl_,
                   oxidationModel   *oxid_,
                   growthModel      *grow_,
                   coagulationModel *coag_);

    virtual ~sootModel_MONO() {};

};
} // namespace soot
