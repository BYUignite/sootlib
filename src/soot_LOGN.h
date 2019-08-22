/**
 * @file soot_LOGN.h
 * Header file for class soot_LOGN
 */

#pragma once

#include "soot.h"
#include <string>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

/** Class implementing child soot_LOGN of parent dv object.
 *
 *  @author Victoria B. Lansinger
 */

class soot_LOGN : virtual public soot {

    //////////////////// DATA MEMBERS //////////////////////

    private:
        double M0;
        double M1;
        double M2;

    //////////////////// MEMBER FUNCTIONS /////////////////

    public:

        virtual void setSrc();

    private:

        double Mk(const double &k);

    //////////////////// CONSTRUCTOR FUNCTIONS /////////////////

    public:

        soot_LOGN(const int      p_nsvar, 
                  vector<string> &spNames, 
                  vector<string> &PAH_spNames, 
                  vector<int>    &p_nC_PAH, 
                  vector<double> &p_MW_sp,
                  int            p_Cmin,
                  double         p_rhoSoot,
                  string         p_nucleation_mech,
                  string         p_growth_mech,
                  string         p_oxidation_mech,
                  string         p_coagulation_mech) :
            soot(p_nsvar, spNames, PAH_spNames, p_nC_PAH, p_MW_sp, p_Cmin, p_rhoSoot,
                 p_nucleation_mech, p_growth_mech, p_oxidation_mech, p_coagulation_mech){}

        virtual ~soot_LOGN(){}

};


////////////////////////////////////////////////////////////////////////////////



