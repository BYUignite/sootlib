/**
 * @file soot_MONO.h
 * Header file for class soot_MONO
 */

#pragma once

#include "soot.h"
#include <string>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

/** Class implementing child soot_MONO of parent dv object.
 *
 *  @author Victoria B. Lansinger
 */

class soot_MONO : virtual public soot {

    //////////////////// DATA MEMBERS //////////////////////

    private:

        vector<double>        wts;        ///< weights of the particle size distribution
        vector<double>        absc;       ///< abscissas of the particle size distribution

    //////////////////// MEMBER FUNCTIONS /////////////////

    public:

        virtual void setSrc();


    //////////////////// CONSTRUCTOR FUNCTIONS /////////////////

    public:

        soot_MONO(const int      p_nsvar, 
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
                 p_nucleation_mech, p_growth_mech, p_oxidation_mech, p_coagulation_mech){

            wts.resize(1);
            absc.resize(1);
        }

        virtual ~soot_MONO(){}

};


////////////////////////////////////////////////////////////////////////////////



