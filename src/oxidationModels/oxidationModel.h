#pragma once

#include "state.h"
#include "sootDefs.h"

#include <vector>

namespace soot {

class sootModel;

class oxidationModel {

//////////////// DATA MEMBERS /////////////////////

public:

    std::vector<double> oxidationRxnRatios;

    oxidationMech mechType;

    sootModel *SM;

//////////////// MEMBER FUNCTIONS /////////////////

    virtual double getOxidationSootRate(const state &state) const = 0;

    void getOxidationGasRates(const state &stt, 
                               const double &msootDotOxid, 
                               std::vector<double> &gasSourcesOxid) const;

//        virtual void getOxidationPahRates(state& state) const = 0;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

    oxidationModel() : oxidationRxnRatios(std::vector<double>((int)gasSp::size, 0.0)) {
        oxidationRxnRatios[(int)gasSp::C] = 1.0;
    }
    virtual ~oxidationModel() = default;
};
} // namespace soot
