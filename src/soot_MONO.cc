/**
 * @file soot_MONO.cc
 * Header file for class soot_MONO
 * @author Victoria B. Lansinger
 */

#include "soot_MONO.h"
#include <cstdlib>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////
/*! Sets src: soot moment source terms. Also sets gasSootSources.
 *  Units: #/(m^3*s), kg-soot/(m^3*s)
 */

void soot_MONO::setSrc() {

    double &M0    = sootvar[0];    //todo issue some checks here like enforcesootmom
    double &M1    = sootvar[1];

    //---------- set weights and abscissas

    if(M0 <= 0.0) {
        wts[0] = 0.0;
        absc[0] = 0.0;
    }
    else {
        wts[0] = M0;                 // defined weights and abscissas for the monodisperse case
        absc[0] = M1/M0;
    }

    //--------- chemical soot rates

    double Jnuc  = getNucleationRate(absc, wts);         // #/m3*s
    double Kgrw  = getGrowthRate(M0, M1);                // kg/m2*s
    double Koxi  = getOxidationRate(M0, M1);             // kg/m2*s
    double Coag  = getCoagulationRate(absc[0], absc[0]);

    //--------- nucleation terms

    double N0 = Jnuc;                                    // #/m3*s
    double N1 = Jnuc*Cmin*MW_c/Na;                       // kg/m3*s

    //---------- PAH condensation terms

    double Cnd0 = 0.0;
    double Cnd1 = 0.0;

    if(nucleation_mech=="PAH")                           // condense PAH if nucleate PAH
        Cnd1 = DIMER*m_dimer*getCoagulationRate(m_dimer, absc[0])*wts[0];

    //--------- growth terms

    double Am2m3 = 0.0;                                  // m^2_soot / m^3_total
    if(M0 > 0.0)
        Am2m3 = M_PI * pow(abs(6/(M_PI*rhoSoot)*M1/M0),2.0/3.0) * abs(M0);    // m^2_soot / m^3_total = pi*di^2*M0

    double G0 = 0.0;                                     // zero by definition, #/m3*s
    double G1 = Kgrw*Am2m3;                              // kg/m3*s

    //--------- oxidation terms

    double X0 = 0.0;                                     // zero by definition, #/m3*s
    double X1 = -Koxi*Am2m3;                             // kg/m3*s

    ////--------- coagulation terms

    double C0 = -0.5*Coag*wts[0]*wts[0];                 // #/m3*s
    double C1 = 0.0;                                     // zero by definition, kg/m3*s

    //--------- combine to make source terms

    src[0] = (N0 + Cnd0 + G0 + X0 + C0);                 // #/m3*s
    src[1] = (N1 + Cnd1 + G1 + X1 + C1);                 // kg-soot/m3*s

    //---------- compute gas source terms

    set_gasSootSources(N1, Cnd1, G1, X1);

}
