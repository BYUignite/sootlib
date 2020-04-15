/**
 * @file soot_MOMIC.h
 * Header file for class soot_MOMIC
 */

#pragma once

#include "soot.h"
#include <string>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

/** Class implementing child soot_MOMIC of parent dv object.
 *
 *  @author Victoria B. Lansinger
 */

class soot_MOMIC : virtual public soot {

    //////////////////// DATA MEMBERS //////////////////////

    private:

    //////////////////// MEMBER FUNCTIONS /////////////////

    public:

        virtual void setSrc();

    private:

        double  lagrangeInterp(double x_i, vector<double> x, vector<double> y);
        double  MOMIC(double p, vector<double> M);
        double  f_grid(int x, int y, vector<double> M);
        double  beta(int p, int q, int ipt);
        double  getCoag(int r);
        void    downselectIfNeeded(int &N);

    //////////////////// CONSTRUCTOR FUNCTIONS /////////////////

    public:

        soot_MOMIC(const int      p_nsvar, 
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


        virtual ~soot_MOMIC(){}

};


////////////////////////////////////////////////////////////////////////////////



