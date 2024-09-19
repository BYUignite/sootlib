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
    
    double Tg = state.T;                // K
    double Pl = log10 (state.P/101325); // atm
    double mtar = state.mtar;

    double N0 = state.tarVar[0]; // \#/m3

    ////// Declare the mass fractions of tar and average molecular size based on constituents /////////

    double ytar_cell;
    double mtar_cell;
    double ytar_hw_hc;
    double mtar_hw_hc;
    double ytar_sw_hc;
    double mtar_sw_hc;
    double ytar_hw_lig;
    double mtar_hw_lig;
    double ytar_sw_lig;
    double mtar_sw_lig;

    /////////////////////// Tar constituent mass fraction equations ///////////////////////////////////

    ytar_cell = (-1.57E5 + Tg*(290.6 - 0.022*Tg + 8.0*Pl + Tg*(3.6E-5*Tg - 0.036*Pl)))/ \
                (-2.03E5 + Tg*(382.9 + 11.2*Pl + Tg*(4.53E-5*Tg - 0.042*Pl)));

    mtar_cell = (-3.06E4 + 242.2*Tg + Pl*(1.05E4 - 83.1*Tg + Pl*(-1.84E3 + 461.8*Pl)))/ \
                (0.635*Tg - Pl*(0.145*Tg - Pl*(0.021*Tg - 2.78*Pl)));

    ytar_hw_hc = (-5.21E5 + Tg*(3.12E3 - 1.08E3*Pl + Tg*(-0.382 + 0.207*Pl)))/ \
                 (Tg*(5.75E3 - 2.65E3*Pl - Tg*(1.45E-4*Tg + 0.518*Pl)));

    mtar_hw_hc = (236.7*Tg - 5.92E4*Pl) / (0.608*Tg - 109.4*Pl);

    ytar_sw_hc = (7.05E4 - 1.29E-5*Pl + Tg*(144.4 + Tg*(0.233 - 7.41E-5*Tg)))/ \
                 (3.69E5 - 3.22E5*Pl + Tg*(91.0 + Tg*(0.725 - 2.08E-4*Tg)));

    mtar_sw_hc = Pl*(Tg*(50.0 + 26.0*Pl) + Pl*(-6.41E4 + 1.56E4*Pl))/ \
                 (Pl*(Tg*(0.126 + 0.072*Pl) + Pl*(-1.65E3 + 41.3*Pl)));

    ytar_hw_lig = (9.04E4 - 3.43E4*Pl + Tg*(-76.2 + 36.6*Pl + Tg*(6.03E-3 - 0.011*Pl + 7.69E-6*Tg)))/ \
                  (1.37E5 - 3.66E4*Pl + Tg*(-117.5 + 39.3*Pl + Tg*(0.012 + 1.00E-5*Tg - 0.012*Pl)));

    mtar_hw_lig = (4.78E6 + Tg*(-8.4E3 + Tg*(7.36 - 1.23E-3*Tg)) + Pl*(-573.1*Tg + Pl*(3.39E6 + 340.1*Tg - 4.85E5*Pl)))/ \
                  (8.13*Tg + Pl*Pl*(1.47E4 - 2.64*Tg + 997.9*Pl));

    ytar_sw_lig = (470.5 - 165.4*Pl + Tg*(-0.303 + 0.124*Pl + Tg*(3.22E-5 + 6.46E-9*Tg - 2.37E-5*Pl)))/ \
                  (735.3 - 176.0*Pl + Tg*(-0.55 + 0.133*Pl + Tg*(1.05E-4 - 2.56E-5*Pl)));

    mtar_sw_lig = (115.8 +Tg*(0.117 - 3.86E-5*Tg + 3.46E-3*Pl) + Pl*(-29.7 - 2.16*Pl))/ \
                  (0.887 -2.19E-4*Tg + Pl*(0.106 - 4.0E-5*Tg));

    /////////////////// Tar mass fraction and average molecular size ////////////////////// 
    
    double ytar = ytar_cell*state.yBio[0] + ytar_hw_hc*state.yBio[1] + ytar_sw_hc*state.yBio[2] + ytar_hw_lig*state.yBio[3] + ytar_sw_lig*state.yBio[4];
    
    mtar = mtar_cell*state.yBio[0] + mtar_hw_hc*state.yBio[1] + mtar_sw_hc*state.yBio[2] + mtar_hw_lig*state.yBio[3] + mtar_sw_lig*state.yBio[4];
    
    ////////////////// Primary pyrolysis rate rv ///////////////////////////////////////// 

    state.mtar = mtar;

    double rv;

    rv = 2.0; // jansenpb TODO: implement a primary pyrolysis model 

    return ytar * rv / mtar;  // #/m3-s
}

double tarModel_AJ_RED::getCrackingTarRate(state &state) {
    
    double N0 = state.tarVar[0];
    double k1, k2, k3, k4, k5; // reaction rate constants
    double xphe, xnapth, xtol, xben; // mole fractions of surrogate tars
    double Cl = 0.0;
    if (N0 > 0) double Cl   = log10 (N0);

    //////////////////// Rate constant calculations ///////////////////////////////////// 

    k1 = 1.0E7*exp(-1.0E5/(Rg*state.T));
    k2 = 1.0E8*exp(-1.0E5/(Rg*state.T));
    k3 = 1.58E12*exp(-3.24E5/(Rg*state.T));
    k4 = 1.04E12*exp(-2.47E5/(Rg*state.T));
    k5 = 4.40E8*exp(-2.2E5/(Rg*state.T));

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
    double eps = 2.2; // same steric factor from soot nucleation for this model
    double Bts; // frequency of collision between soot and tar molecules
    double muTS = state.mtar*state.sootVar[1]/(state.mtar + state.sootVar[1]);
    
    double dsoot = pow(6*state.sootVar[1]/(M_PI*rhoSoot), onethird);
    double dtar  = 6.06E-9 * sqrt(2*state.mtar/(3*12.011));

    Bts = pow((dsoot + dtar), 2) * sqrt(M_PI*kb*state.T/(2*muTS));

    return eps*Bts*N0*state.sootVar[0];

}

double tarModel_AJ_RED::getSurfaceTarRate(state &state) {

    ////////////////////// This is only the gasification part. See oxidationModel_AJ_RED and growthModel_HACA //////////// jansenpb
    
    double term1 = 1.92E-3 * sqrt(state.getGasSpP(gasSp::CO2))*state.T*state.T*exp(-5.55E3/(Rg*state.T));
    double term2 = 1.92E-3 * pow(state.getGasSpP(gasSp::H2O), 1.21) / sqrt(state.T) * exp(-4.17E5/(Rg*state.T));

    return term1 + term2;
}



