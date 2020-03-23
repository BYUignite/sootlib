/**
 * @file soot_SECT.cc
 * Header file for class soot_SECT
 * @author Victoria B. Lansinger
 * @author Keturah A. Oldham
 */

#include "soot_SECT.h"
#include <cstdlib>
#include <cmath>

////////////////////////////////////////////////////////////////////////////////
/*! Sets src: soot moment source terms. Also sets gasSootSources.
 *  Units: #/(m^3*s), kg-soot/(m^3*s)
 */


vector<double> dv_soot_SECT::getDivision(double mass, double num, vector<double> absc) {
    int nsvar = absc.size();
    int loc = 0;
    bool found = false;
    vector<double> to_return(nsvar, 0.0);
    while (!found) {
        loc++;
        if (loc >= nsvar) {
            loc = nsvar - 1;
            found = true;
        }
        if (absc[loc] > mass) {
            found = true;
        }
    }
    // using lever rule to divide particles, conserving particle number and mass
    double right = (mass - absc[loc - 1])/(absc[loc] - absc[loc - 1]) * num;
    double left = (absc[loc] - mass)/(absc[loc] - absc[loc - 1]) * num;
    to_return[loc - 1] += left;
    to_return[loc] += right;
//    cout << "to_return right" << to_return[loc] << endl;
    return to_return;
}

void soot_SECT::setSrc() {

    
    
    vector<double> &wts = sootvar;    // wts: # in section
    vector<double> absc(nsvar);       // absc: density
    
    for (int k=0; k<nsvar; k++) 
                absc[k] = Cmin*pow(2.0,k)*MW_c/Na;       // TODO: 2.0 is hardcoded here, but should be an inputtable variable
    //---------- set weights


    for(int i = 0; i < nsvar; i++) {
        if(wts[i] <= 0.0) {
            wts[i] = 0.0;
        }
        else {
            wts[i] = wts[i];
        }
    }




    //--------- chemical soot rates
    
    double Jnuc  = getNucleationRate(absc, wts);         // #/m3*s
    vector<double> Kgrw(nsvar);
    for(int i = 0; i < nsvar; i++) {
        Kgrw[i] = getGrowthRate(wts[k], absc[k]*wts[k]);                // kg/m2*s 	
    }
    vector<double> Koxi(nsvar);
	for(int i = 0; i < nsvar; i++) {
        Koxi[i] = getOxidationRate(wts[i], absc[i]);                // kg/m2*s 	
    }
    
    //--------- coagulation terms
    vector<double> Coag(nsvar);
    for (int i = 0; i < nsvar; i++) {
        for (int j = 0; j < nsvar; j++) {
            double leaving = 0.5 * getCoagulationRate(absc[i],absc[j]) * wts[i]*wts[j];
            Coag[i] = Coag[i] - leaving;
            Coag[j] = Coag[j] - leaving;
            vector<double> divided = getDivision((sections[i] + sections[j]), leaving);
            for (int k = 0; k < nsvar; k++) {
                Coag[k] += divided[k];
            }
        }
    }

    //--------- nucleation terms

    vector<double> N0(nsvar, 0.0);
    N0[0] = Jnuc;                                              // all nucleation goes into the smallest section
    double N_tot = Jnuc*Cmin*MW_c/Na;

    //---------- PAH condensation terms

    vector<double> Cnd0(nsvar,0.0);
    double Cnd_tot = 0.0;
    if(nucleation_mech=="PAH")  {
        // condense PAH if nucleate PAH
        for (int i = 0; i < nsvar; i++) {
            Cnd0[i] = DIMER*m_dimer*getCoagulationRate(m_dimer, absc[i])*wts[i];
            Cnd_tot += Cnd0[i]*absc[i];
        }
    }                 

    //--------- growth terms

    vector<double> Am2m3(nsvar);                                  // m^2_soot / m^3_total
    for(int i = 0; i < nsvar; i++) {
        if(wts[i] > 0.0) {
            Am2m3[i] = M_PI * pow(abs(6/(M_PI*rhoSoot)*sections[i]),2.0/3.0) * abs(wts[i]);    // m^2_soot / m^3_total = pi*di^2*wts
    	}   
        else {
            Am2m3[i] = 0;
        }
    }
    vector<double> G0(nsvar);
    double G_tot = 0.0;
    for (int i=0; i < nsvar; i++) {
        double Ngrw = 0;
        if (i==0) {
            Ngrw = - Kgrw[i]*Am2m3[i]*wts[i]/(absc[i+1]-absc[i]);
        }
        else if (k==(nsvar-1)) {
            Ngrw = Kgrw[i-1]*Am2m3[i-1]*wts[i-1]/(absc[i]-absc[i-1]);
        }
        else {
            Ngrw = Kgrw[i-1]*Am2m3[i-1]*wts[i-1]/(absc[i]-absc[i-1]) - Kgrw[i]*Am2m3[i]*wts[i]/(absc[i+1]-absc[i]);
        }
        G0[i] = Ngrw;
        G_tot += Ngrw*absc[i];
        
    }                            

    //--------- oxidation terms

    vector<double> X0(nsvar);
    double X_tot = 0.0;
    for (int i=0; i < nsvar; i++) {
        double Noxi = 0;
        if (i==0) {
            Noxi = Koxi[i]*Am2m3[i]*wts[i]/(absc[i+1]-absc[i]);
        }
        else if (i==(nsvar-1)) {
            Noxi = - Koxi[i-1]*Am2m3[i-1]*wts[i-1]/(absc[i]-absc[i-1]);
        }
        else {
            Noxi = - Koxi[i-1]*Am2m3[i-1]*wts[i-1]/(absc[i]-absc[i-1]) + Koxi[i]*Am2m3[i]*wts[i]/(absc[i+1]-absc[i]);
        }
        X0[i] = Noxi;
        X_tot += Noxi*absc[i];
    }                                      

    ////--------- coagulation terms

    vector<double> C0 = Coag;                                 

    //--------- combine to make source terms

    for (int i = 0; i < nsvar; i++) {
        src[i] = (N0[i] + Cnd0[i] + G0[i] + X0[i] + C0[i])/ rho;
    }
    
    //---------- compute gas source terms
  //  vector<double> N1(nsvar);
  //  vector<double> Cnd1(nsvar);
  //  vector<double> G1(nsvar);
  //  vector<double> X1(nsvar);
  //  for (int i = 0; i < nsvar; i++) {
  //      N1[i] = N0[i] * sections[i];
  //      Cnd1[i] = Cnd0[i] * sections[i];
  //      G1[i] = G0[i] * sections[i];
  //      X1[i] = X0[i] * sections[i];
        
  //  }
    set_gasSootSources(N_tot, Cnd_tot, G_tot, X_tot);

}
