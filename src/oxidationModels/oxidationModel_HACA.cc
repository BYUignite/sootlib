#include "oxidationModels/oxidationModel_HACA.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

oxidationModel_HACA::oxidationModel_HACA() {

    oxidationRxnRatios[(int)gasSp::O2]   = -1;
    oxidationRxnRatios[(int)gasSp::OH]   = -1;
    oxidationRxnRatios[(int)gasSp::H ]   =  1;
    oxidationRxnRatios[(int)gasSp::CO]   =  3;
    oxidationRxnRatios[(int)gasSp::C]    = -3;

    mechType = oxidationMech::HACA;
}

//////////////////////////////////////////////////////////////////////////////////
///
/// Oxidation by HACA.
/// See HACA description in growthModel_HACA.cc
/// 5. Cs*  + O2    ==> 2CO + (products)
/// 6. Cs-H + OH  ==> CO + (products)
///    implement the balance for reaction 6 as C + OH ==> CO + H
///
/// @param state \input  gas and soot state, set by user.
/// @return soot oxidation rate (kg/m2*s)
///
//////////////////////////////////////////////////////////////////////////////////

double oxidationModel_HACA::getOxidationSootRate(const state &state) const {

    double M0 = state.sootVar[0];                       // #/m3
    double M1 = state.sootVar[1];                       // kg/m3
    ///< \todo: generalize this to sectional.

    //---------- calculate alpha, other constants

    double RT = 1.9872036E-3 * state.T;                 // R (=) kcal/mol
    double chi_CH  = 2.3E15;                            // C-H sites/cm^2
    double a_param = 33.167 - 0.0154 * state.T;         // a parameter for calculating alpha
    double b_param = -2.5786 + 0.00112 * state.T;       // b parameter for calculating alpha

    //---------- calculate raw HACA reaction rates

    double fR1 = 4.2E13 * exp(-13.0 / RT) * state.getGasSpC(gasSp::H) / 1000;
    double rR1 = 3.9E12 * exp(-11.0 / RT) * state.getGasSpC(gasSp::H2) / 1000;
    double fR2 = 1.0E10 * pow(state.T, 0.734) * exp(-1.43 / RT) * state.getGasSpC(gasSp::OH) / 1000;
    double rR2 = 3.68E8 * pow(state.T, 1.139) * exp(-17.1 / RT) * state.getGasSpC(gasSp::H2O) / 1000;
    double fR3 = 2.0E13 * state.getGasSpC(gasSp::H) / 1000;
    double fR4 = 8.00E7 * pow(state.T, 1.56) * exp(-3.8 / RT) * state.getGasSpC(gasSp::C2H2) / 1000;
    double fR5 = 2.2E12 * exp(-7.5 / RT) * state.getGasSpC(gasSp::O2) / 1000;

    //---------- Steady state calculation of chi for soot radical; see Frenklach 1990 pg. 1561

    double denom = rR1 + rR2 + fR3 + fR4 + fR5;
    double chi_S = denom == 0 ? 0 : 2 * chi_CH * (fR1 + fR2) / denom;  // C-* sites/cm^2

    double alpha = 1.0;
    if (M0 > 0)
        alpha = tanh(a_param/log10(M1/M0) + b_param);      // alpha = fraction of available surface sites
    if (alpha < 0) alpha=1.0;

    double rxns_s = fR5*alpha*chi_S * 1E4;                 // reactions at sites per m2 per s.
    double RO2    = 2.0*rxns_s*gasSpMW[(int)gasSp::C]/Na;  // kg/m2/s: each site: 2.0: each site gets 2 Carbons
    double ROH    = 0.13*state.getGasSpC(gasSp::OH)*       // kg/m2/s     = 1290*0.13*POH/sqrt(T) with POH in atm
                    sqrt(Rg*state.T/(2.0*M_PI*gasSpMW[(int)gasSp::OH]))*
                    gasSpMW[(int)gasSp::C];
    return RO2 + ROH;
}
