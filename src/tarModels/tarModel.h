#pragma once

#include "state.h"
#include "sootDefs.h"

#include <vector>

namespace soot {

class sootModel;
    
///////////////////////////////////////////////////////////////////////////////
///
/// Abstract soot class to calculate tar inception rates
///
///////////////////////////////////////////////////////////////////////////////

class tarModel {
    
    ////////////////// DATA MEMBERS: //////////////////////////////////////////
    
public:

    sootModel *SM;
    tarMech mechType;

    std::vector<double> crackingRxnRatios;
    std::vector<double> crackingPahRxnRates;
    std::vector<double> depositionRxnRatios;
    std::vector<double> depositionPahRxnRates;
    std::vector<double> surfaceRxnRatios;
    std::vector<double> surfacePahRxnRates;

    ///////////////// MEMBER FUNCTIONS ////////////////////////////////////////

    virtual double getCrackingTarRate(state &state)   = 0;
    virtual double getDepositionTarRate(state &state) = 0;
    virtual double getSurfaceTarRate(state &state)    = 0;

    ///////////////// CONSTRUCTOR ///////////////////////////////////////////// 

    tarModel() : crackingPahRxnRates(std::vector<double>((int)pahSp::size, 0.0)),
                 crackingRxnRatios(std::vector<double>((int)gasSp::size, 0.0)),
                 depositionPahRxnRates(std::vector<double>((int)pahSp::size, 0.0)),
                 depositionRxnRatios(std::vector<double>((int)gasSp::size, 0.0)),
                 surfacePahRxnRates(std::vector<double>((int)pahSp::size, 0.0)),
                 surfaceRxnRatios(std::vector<double>((int)gasSp::size, 0.0)) { }

    virtual ~tarModel() = default;
    
};
} // namespace soot


