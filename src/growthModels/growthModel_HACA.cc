#include "growthModels/growthModel_HACA.h"
#include "sootDefs.h"
#include "sootModel.h"          // for the SM back pointer

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

growthModel_HACA::growthModel_HACA() {

    growthRxnRatios[(int)gasSp::O2]   =  0;
    growthRxnRatios[(int)gasSp::OH]   = -1;
    growthRxnRatios[(int)gasSp::H]    = -1;
    growthRxnRatios[(int)gasSp::H2]   =  1;
    growthRxnRatios[(int)gasSp::H2O]  =  1;
    growthRxnRatios[(int)gasSp::C2H2] = -1;
    growthRxnRatios[(int)gasSp::CO]   =  0;
    growthRxnRatios[(int)gasSp::C]    =  2;

    mechType = growthMech::HACA;
}

////////////////////////////////////////////////////////////////////////////////
///
/// HACA via ABF mechanism: Appel, Bockhorn, Frenklach, Combustion and Flame 121:122-136 (2000).
/// See also see Franklach and Wang (1990), 23rd Symposium, pp. 1559-1566.
/// Parameters for steric factor alpha updated to those given in Balthasar
/// and Franklach (2005) Comb. & Flame 140:130-145.
/// 
/// Reactions:
/// 1. Cs-H + H    <==> Cs* + H2
/// 2. Cs-H + OH   <==> Cs* + H2O
/// 3. Cs*  + H     ==> Cs-H
/// 4. Cs*  + C2H2  ==> (CsCs)Cs-H + H
/// 5. Cs*  + O2    ==> 2CO + (products)
/// ( 6. Cs-H + OH  ==> CO + (products) )
///
/// The key reaction is Rxn 4. The rest are used to get Cs* from a QSSA.
/// Rxn 6 is oxidation via OH, treated in the oxidation mechanism elsewhere.
/// Rxn 5 is used here to compute Cs*, but oxidation balance is done elsewhere.
/// 
/// Note, in terms of species balance, soot is treated as carbon, and we could 
/// use a simple balance n*soot + C2H2 ==> (n+2)*soot + H2.
/// However, the reations and growthRxnRatios here are self-consistent, so we'll use those.
///
/// Rates: See Frenklach and Wang, Proceedings of the Combustion Institute 23:1559-1566 (1990).
/// kf4 = 8E7*T**1.56*exp(-3.8/RT) has units of cm3/(mol*site*s).
/// Hence, kf4*[C2H2]*alpha*(Chi_Cs*) = cm3/(mol*site*s)*(mol/cm3)*alpha*(sites/cm2) = rxns/(cm2*s)
/// If reactions happen at soot sites, then * mc to get kg_c/(cm2*s), where mc is the mass of a carbon atom.
/// This is not so obvious from Frenklach and Wang, but see Balthasar and Frenklach, Combustion and Flame 140:130-145(2005).
///
/// The reverse reaction rates are from Ken Revzan and Frenklach 02/15/02 code soot.f: http://combustion.berkeley.edu/soot/codes/routines.html
/// Those rates are also in cantera: test/data/haca2.yaml
///
/// The a_param and b_param values are from Blathasar and Frenklach (2005).
///
/// @param state       \input  gas and soot state, set by user.
/// @return soot growth rate (kg/m2*s)
///
////////////////////////////////////////////////////////////////////////////////

double growthModel_HACA::getGrowthSootRate(const state& state) const {

    double M0 = state.sootVar[0];                           // #/m3
    double M1 = state.sootVar[1];                           // kg/m3

    if (SM->psdMechType == psdMech::SECT) {
        M0 = 0.0;
        M1 = 0.0;
        for (size_t k=0; k<state.nsoot; k++) {
            M0 += state.sootVar[k];
            M1 += state.sootVar[k]*SM->mBins[k];
        }
    }

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
        alpha = tanh(a_param/log10(M1/M0) + b_param);                     // alpha = fraction of available surface sites
    if (alpha < 0) alpha=1.0;

    double rxns_s = fR4*alpha*chi_S * 1E4;        // reactions at sites per m2 per s.
    return 2.0*rxns_s*gasSpMW[(int)gasSp::C]/Na;  // kg/m2/s: each site: 2.0: each site gets 2 Carbons
}
