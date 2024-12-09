#include "tarModels/tarModel_AJ_RED.h"
#include "sootDefs.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///
/// Tar inception, thermal cracking, deposition, and surface reactions (2019)
///
/// Rates from Alexander Josephson "Reduction of a detailed soot model for simulations of pyrolysing solid fuels"
/// Returns chemical nucleation rate in #/m3*s.
///
///
/// @param state \input  gas, soot, and tar state, set by user.
/// @return tar reaction rates (\#/m3*s, kg/m3*s)
///
////////////////////////////////////////////////////////////////////////////////

double tarModel_AJ_RED::getInceptionTarRate(state &state) {
    

    double rv;

    rv = 2.0; // jansenpb TODO: implement a primary pyrolysis model 

    return state.ytar * rv / state.mtar;  // #/m3-s
}

double tarModel_AJ_RED::getCrackingTarRate(state &state) {
    
    double N0 = state.tarVar[0];
    double k1, k2, k3, k4, k5; // reaction rate constants
    double xphe, xnapth, xtol, xben; // mole fractions of surrogate tars
    double Cl = 0.0;
    if (N0 > 0) double Cl   = log10 (N0);

    //////////////////// Rate constant calculations ///////////////////////////////////// 

    k1 = 1.0E7*exp(-1.0E8/(Rg*state.T));
    k2 = 1.0E8*exp(-1.0E8/(Rg*state.T));
    k3 = 1.58E12*exp(-3.24E8/(Rg*state.T));
    k4 = 1.04E12*exp(-2.47E8/(Rg*state.T));
    k5 = 4.40E8*exp(-2.2E8/(Rg*state.T));

    /////////////////// Empirical model for surrogate tar mole fractions //////////////// 
    
    xphe = 1/6*tanh(5.73 - 0.00384*state.T - 0.159*Cl) - 0.218 + 0.0277*Cl;
    xnapth = 0.5*tanh(-1.98 + 6.18E-4*state.T + 0.124*Cl - 0.00285*Cl*Cl + 4.14E-7*state.T*state.T - 4.97E-5*state.T*Cl) \
             -0.576 + 0.000233*state.T - 1.69E-7*state.T*state.T;
    xtol   = 1/3*tanh(17.3 - 0.00869*state.T + Cl*(-1.08 + 0.000365*state.T + 0.0199*Cl)) + 2.65E-4*state.T + Cl*(-1.11E-4*Cl - 9.32E-6*state.T);
    xben   = 1 - xphe - xnapth - xtol;

    double r1 = 31.1/94*k1*xphe;
    double r2 = k2*xphe;
    double r3 = 50/128*k3*xnapth*pow(state.getGasSpC(gasSp::H2), 0.4);
    double r4 = 14/92*k4*xtol*pow(state.getGasSpC(gasSp::H2), 0.5);
    double r5 = k5*xben;

    return N0*(r1 + r2 + r3 + r4 + r5);

}

double tarModel_AJ_RED::getDepositionTarRate(state &state) {

    double N0 = state.tarVar[0];
    double eps = 2.2;                  // same steric factor from soot nucleation for this model
    double Bts;                        // frequency of collision between soot and tar molecules
    
    double muTS = state.mtar*state.sootVar[1]/(state.mtar + state.sootVar[1]);

    double d_a  = sqrt(1.395E-10 * 3);                                // diameter of a single aromatic ring
    double dsoot = pow(6*state.sootVar[1]/(M_PI*rhoSoot), onethird);  // diameter of average soot particle
    double dtar  = d_a * sqrt(2*state.mtar/(3*12.011));               // diameter of average tar particle

    Bts = pow((dsoot + dtar), 2) * sqrt(M_PI*kb*state.T/(2*muTS));

    return eps*Bts*N0*state.sootVar[0];

}

double tarModel_AJ_RED::getSurfaceTarRate(state &state) {

    ////////////////////// This is only the gasification part. See oxidationModel_AJ_RED and growthModel_HACA //////////// jansenpb
    
    double term1 = 1.92E-3 * sqrt(state.getGasSpP(gasSp::CO2))*state.T*state.T*exp(-5.55E6/(Rg*state.T));
    double term2 = 1.92E-3 * pow(state.getGasSpP(gasSp::H2O), 1.21) / sqrt(state.T) * exp(-4.17E8/(Rg*state.T));

    return term1 + term2;
}



