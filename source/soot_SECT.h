/**
 * @file soot_SECT.h
 * Header file for class soot_SECT
 */

#pragma once

#include "soot.h"
#include <string>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

/** Class implementing child soot_SECT of parent dv object.
 *
 *  @author Victoria B. Lansinger
 *  @auther Keturah A. Oldham
 */

class soot_SECT : virtual public soot {

    //////////////////// DATA MEMBERS //////////////////////

    private:

        vector<double>        wts;        ///< weights of the particle size distribution; number in section # partics/m3
        vector<double>        absc;   ///< mass of the particles in each section; kg/particle this'll need to be input when the class is created! kg/particle
    //////////////////// MEMBER FUNCTIONS /////////////////

    public:

        virtual void setSrc();
    
    private:
        vector<double> getDivision(double mass, double num);


    //////////////////// CONSTRUCTOR FUNCTIONS /////////////////

    public:

        soot_SECT(const int      p_nsvar, //number of soot variables
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

            wts.resize(p_nsvar);
        }

        virtual ~soot_SECT(){}

};


////////////////////////////////////////////////////////////////////////////////



