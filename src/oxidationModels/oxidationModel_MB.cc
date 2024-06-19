#include "oxidationModels/oxidationModel_MB.h"
#include "sootDefs.h"
#include "sootModel.h"

using namespace std;
using namespace soot;

//////////////////////////////////////////////////////////////////////////

oxidationModel_MB::oxidationModel_MB() {

    oxidationRxnRatios[(int)gasSp::CO] =  1;       // C(soot) + OH --> CO + H
    oxidationRxnRatios[(int)gasSp::H]  =  1;
    oxidationRxnRatios[(int)gasSp::C]  = -1;
    oxidationRxnRatios[(int)gasSp::OH] = -1;

    mechType = oxidationMech::MB;
}

//////////////////////////////////////////////////////////////////////////
///
/// Oxidation by Moss-Brookes (1999)
///
/// Rate from Moss-Brookes (1999) Predictions of Soot and Thermal Radiation Properties in...
///
/// C + OH --> CO + H
///
/// @param state \input gas and soot state, set by user
/// @return soot oxidation rate (kg/m2*s)
///
//////////////////////////////////////////////////////////////////////////

double oxidationModel_MB::getOxidationSootRate(const state &state) const {
    
    double M0, M1;           // #/m3, kg/m3

    if (SM->psdMechType == psdMech::SECT) {
        M0 = SM->get_M0_sectional(state);
        M1 = SM->get_M1_sectional(state);
    }
    else {
        M0 = state.sootVar[0];
        M1 = state.sootVar[1];
    }

    double omega = 4.2325 * state.getGasSpC(gasSp::OH) * sqrt(state.T); // check against NEO, collision eff=0.04 here

    return -omega * pow(M_PI * M0, 1.0/3.0) * pow(6 * M1 / rhoSoot, 2.0/3.0); // kg_soot/m2*s
}

