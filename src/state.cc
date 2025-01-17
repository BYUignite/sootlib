#include "state.h"

#include <numeric>

using namespace soot;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
/// 
/// Sets the thermodynamic state based on user input
/// 
/// Only point of contact between users and the state class. User provides
/// relevant data to be assigned to sootlib's internal state variables.
/// 
/// @param T_       \input temperature (K)
/// @param P_       \input pressure (Pa)
/// @param rhoGas_  \input density of gas mixture (kg/m3)
/// @param muGas_   \input dynamic viscosity (kg/m*s)            
/// @param MWGas_   \input gas mixture molecular weight (kg/kmol)
/// @param yGas_    \input gas species mass fractions [H, H2, O, O2, OH, H2O, CO, C2H2]
/// @param yPAH_    \input PAH species mass fractions [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
/// @param sootVar_ \input soot variable (moments or section values) values
/// @param nsoot_   \input number of soot variables
/// @param cMin_    \input minimum number of carbon atoms in a soot particle
/// 
/// IMPORTANT: gas and PAH species mass fractions MUST be provided in the order specified
/// above within the yGas and yPAH vectors. Values must be non-negative. If a species is
/// not represented or not present, DO NOT leave it out; instead, enter a mass fraction
/// value of zero. If the user mechanism contains more than one species with the same
/// molecular formula (C16H10 is a common culprit), enter the sum of the mass fractions
/// for the applicable species. Any additional species information is not used by sootlib
/// and will be ignored.
/// 
////////////////////////////////////////////////////////////////////////////////

void state::setState(double T_, double P_, double rhoGas_, double muGas_,
                     vector<double> yGas_, vector<double> yPah_, 
                     vector<double> sootVar_, int nsoot_ , 
                     vector<double> tarVar_, int Ntar_, double cMin_) {

    //------------ scalar variable values

    if (T_ <= 0) throw domain_error("Unphysical state value input: T");
    else T = T_;

    if (P_ <= 0) throw domain_error("Unphysical state value input: P");
    else P = P_;

    if (rhoGas_ <= 0) throw domain_error("Unphysical state value input: rhoGas");
    else rhoGas = rhoGas_;

    if (muGas_ <= 0) throw domain_error("Unphysical state value input: muGas");
    else muGas = muGas_;


    if (cMin_ <= 0) throw domain_error("Unphysical state value input: cMin");
    else cMin = cMin_;

    //------------ gas mean molecular weight

    MWGas = rhoGas*Rg*T/P;

    //------------ soot moments/bins

    for(int i=0; i<nsoot; i++)
        if(sootVar_[i] < 0)
            sootVar_[i] = 0.0;

    nsoot = nsoot_;
    for (double s : sootVar_)
        if (s < 0)
            throw domain_error("Unphysical state value input: negative soot moment(s)");

    sootVar = sootVar_;

    for(int i=0; i<Ntar; i++)
        if(tarVar_[i] < 0)
            tarVar_[i] = 0.0;
    
    Ntar = Ntar_;
    for (double s : tarVar_)
        if (s < 0)
            throw domain_error("Unphysical state value input: negative tar moment(s)");

    tarVar = tarVar_;
    //------------ gas species mass fractions

    for (double y : yGas_) {
        if (y < 0) {
            y = 0;
        }
        if (y > 1)
            throw domain_error("Unphysical state value input: gas species mass fraction > 1.0");
    }

    double yGas_sum = 0;
    for(double y : yGas_)
        yGas_sum += y;
    // if (yGas_sum > 1.0)
    //     throw domain_error("Unphysical state value input: sum of gas species mass fractions greater than one");

    yGas = yGas_;

    //------------ PAH mass fractions

    if (yPah_.size() != (yPah.size()))
        throw domain_error("Invalid input vector size: PAH species mass fractions");

    for (double y : yPah_)
        if (y < 0 || y > 1)
            throw domain_error("Unphysical state value input: PAH species mass fraction(s)");

    double yPAH_sum = 0;
    for(double y :yPah_)
        yPAH_sum += y;
    if (yPAH_sum > 1.0)
        throw domain_error("Unphysical state value input: sum of PAH species mass fractions greater than one");

    yPah = yPah_;

    //------------ Tar mass fractions

    /*if (yTar_.size() != (yTar.size()))
        throw domain_error("Invalid input vector size: Tar species mass fractions");

    for (double y : yTar_)
        if (y < 0 || y > 1)
            throw domain_error("Unphysical state value input: Tar species mass fraction(s)");

    double yTar_sum = 0;
    for(double y : yTar_)
        yTar_sum += y;
    if (yTar_sum > 1.0)
        throw domain_error("Unphysical state value input: sum of Tar species mass fractions greater than one");

    yTar = yTar_;*/



}

void state::get_mtar_ytar() {

    double Tg = T;  
    double Pl = log10(P/101325);
    
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

    mtar_sw_hc = (Tg*(50.0 + 26.0*Pl) + Pl*(-6.41E4 + 1.56E4*Pl))/ \
                 ((Tg*(0.126 + 0.072*Pl) + Pl*(-1.65E3 + 41.3*Pl)));

    ytar_hw_lig = (9.04E4 - 3.43E4*Pl + Tg*(-76.2 + 36.6*Pl + Tg*(6.03E-3 - 0.011*Pl + 7.69E-6*Tg)))/ \
                  (1.37E5 - 3.66E4*Pl + Tg*(-117.5 + 39.3*Pl + Tg*(0.012 + 1.00E-5*Tg - 0.012*Pl)));

    mtar_hw_lig = (4.78E6 + Tg*(-8.4E3 + Tg*(7.36 - 1.23E-3*Tg)) + Pl*(-573.1*Tg + Pl*(3.39E6 + 340.1*Tg - 4.85E5*Pl)))/ \
                  (8.13*Tg + Pl*Pl*(1.47E4 - 2.64*Tg + 997.9*Pl));

    ytar_sw_lig = (470.5 - 165.4*Pl + Tg*(-0.303 + 0.124*Pl + Tg*(3.22E-5 + 6.46E-9*Tg - 2.37E-5*Pl)))/ \
                  (735.3 - 176.0*Pl + Tg*(-0.55 + 0.133*Pl + Tg*(1.05E-4 - 2.56E-5*Pl)));

    mtar_sw_lig = (115.8 +Tg*(0.117 - 3.86E-5*Tg + 3.46E-3*Pl) + Pl*(-29.7 - 2.16*Pl))/ \
                  (0.887 -2.19E-4*Tg + Pl*(0.106 - 4.0E-5*Tg));

    /////////////////// Tar mass fraction and average molecular size ////////////////////// 
    
    ytar = ytar_cell*yBio[0] + ytar_hw_hc*yBio[1] + ytar_sw_hc*yBio[2] + ytar_hw_lig*yBio[3] + ytar_sw_lig*yBio[4];
    
    mtar = mtar_cell*yBio[0] + mtar_hw_hc*yBio[1] + mtar_sw_hc*yBio[2] + mtar_hw_lig*yBio[3] + mtar_sw_lig*yBio[4];
}

void state::get_coal(double OC_, double HC_, double V_) {
    OC = OC_;
    HC = HC_;
    V  = V_;
}

void state::get_mtar_ytar_coal() {
    
    double Tg = T;
    double Pl = log10(P/101325);

    double num, denom;

    num   = -124.2 + 35.7*Pl + 93.5*OC - 223.9*OC*OC + 284.8*HC -107.3*HC*HC +5.48*V +0.014*V*V - 58.2*Pl*HC - 0.521*Pl*V - 5.32*HC*V;
    denom = -303.8 + 52.4*Pl +1.55E3*OC - 2.46E3*OC*OC + 656.9*HC - 266.3*HC*HC + 15.9*V + 0.025*V*V - 90.0*Pl*HC - 462.5*OC*HC +4.8*OC*V - 17.8*HC*V;
    ytar = num/denom;
    
    num = 0.0;
    denom = 0.0;

    num   = 3.12E5 + 16.4*Tg + 4.34E5*OC - 8.48E5*HC + 6.38E5*HC*HC - 361.3*V - 0.221*Tg*V - 6.39E5*OC*HC + 1.91E3*HC*V;
    denom = 753.6 + 0.042*Tg + 83.9*OC - 1.77E3*HC + 1.2E3*HC*HC + 5.09E-3*Tg*Pl - 0.024*Tg*HC - 5.27E-4*Tg*V + 0.513*Pl*V - 361.0*OC*HC + 3.83*HC*V;

    mtar = num/denom;
}

////////////////////////////////////////////////////////////////////////////////

