/**
 * @file soot_QMOM.h
 * Header file for class soot_QMOM
 */

#pragma once

#include "soot.h"
#include <string>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

/** Class implementing child soot_QMOM of parent dv object.
 *
 *  @author Victoria B. Lansinger
 */

class soot_QMOM : virtual public soot {

    //////////////////// DATA MEMBERS //////////////////////

    private:

        vector<double>        wts;        ///< weights from inversion algorithm
        vector<double>        absc;       ///< abscissas from inversion algoritm

    //////////////////// MEMBER FUNCTIONS /////////////////

    public:

        virtual void setSrc();

    private:

        double  Mk(double exp);
        void    getWtsAbs(vector<double> M, vector<double> &wts, vector<double> &abs);

    //////////////////// CONSTRUCTOR FUNCTIONS /////////////////

    public:

        soot_QMOM(const int      p_nsvar, 
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

            wts.resize(nsvar/2);
            absc.resize(nsvar/2);
        }

        virtual ~soot_QMOM(){}

};


////////////////////////////////////////////////////////////////////////////////



