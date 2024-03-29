#include "oxidationModels/oxidationModel_NSC_NEOH.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

oxidationModel_NSC_NEOH::oxidationModel_NSC_NEOH() {

    // C + OH      --> CO + H   
    //                          --> 2C_soot + OH + (1/2)O2 --> 2CO + H
    // C + (1/2)O2 --> CO 

    oxidationRxnRatios[(int)gasSp::CO] =  2;
    oxidationRxnRatios[(int)gasSp::H] =   1;
    oxidationRxnRatios[(int)gasSp::OH] = -1;
    oxidationRxnRatios[(int)gasSp::O2] = -0.5;
    oxidationRxnRatios[(int)gasSp::C]  = -2;

    mechType = oxidationMech::NSC_NEOH;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Oxidation by NSC + Neoh
///
/// Rates from Nagle and Strickland-Constable (1961) and Neoh (1981) "Soot
/// oxidation in flames" in Particulate Carbon Formation During Combustion
/// book
/// C + 0.5 O2 --> CO
/// C + OH     --> CO + H
///
/// @param state \input  gas and soot state, set by user.
/// @return soot oxidation rate (kg/m2*s)
///
////////////////////////////////////////////////////////////////////////////////

double oxidationModel_NSC_NEOH::getOxidationSootRate(const state &state) const {

    double pO2_atm = state.getGasSpP(gasSp::O2) / 101325.0; // partial pressure of O2 (atm)
    double pOH_atm = state.getGasSpP(gasSp::OH) / 101325.0; // partial pressure of OH (atm)

    double kA = 20 * exp(-15098 / state.T);                 // rate constants
    double kB = 4.46E-3 * exp(-7650 / state.T);
    double kT = 1.51E5 * exp(-48817 / state.T);
    double kz = 21.3 * exp(2063 / state.T);

    double x = 1 / (1 + kT / (kB * pO2_atm));                    // x = unitless fraction
    double NSC_rate = kA * pO2_atm * x / (1 + kz * pO2_atm) + kB * pO2_atm * (1.0 - x);   // kmol/m^2*s
    double rSootO2 = NSC_rate * rhoSoot;                        // kg/m2*s
    double rSootOH = 1290. * 0.13 * pOH_atm / sqrt(state.T);    // kg/m2*s

    return rSootO2 + rSootOH;                                   // kg/m2*s
}
