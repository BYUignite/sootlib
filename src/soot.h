/**
 * @file soot.h
 * Header file for class soot
 */

#pragma once

#include <string>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

/** Class implementing child soot of parent dv object.
 *  This is a virtual base class.
 *  @author Victoria B. Lansinger
 */

class soot {

    //////////////////// DATA MEMBERS //////////////////////

    public:
        int                     nsvar;                  ///< number of soot variables
        vector<double>          sootvar;                ///< main soot quantity (soot moments or sections)
        vector<double>          gasSootSources;         ///< gas species sources due to soot reactions (all species)
        vector<double>          src;                    ///< source terms for soot variables (size nsvar)

    protected:

        static constexpr double Na    = 6.02214086E26;  ///< Avogadro's constant: #/kmol
        static constexpr double kb    = 1.38064852E-23; ///< Boltzmann constant = Rg/Na: J/#*K
        static constexpr double Rg    = 8314.46;        ///< Universal gas constant
        static constexpr double eps_c = 2.2;            ///< coagulation constant
        static constexpr double Df    = 1.8;            ///< soot fractal dimension
        static constexpr double MW_c  = 12.011;         ///< mw of carbon
        static constexpr double MW_h  = 1.00794;        ///< mw of hydrogen 

        //-----------

        static double           rhoSoot;                ///< soot density kg/m3
        static string           nucleation_mech;        ///< soot nucleation chemistry flag
        static string           growth_mech;            ///< soot growth chemistry flag
        static string           oxidation_mech;         ///< soot oxidation chemistry flag
        static string           coagulation_mech;       ///< soot coagulation mechanism flag

        double                  Cmin;                   ///< number of carbons in soot nucleation size
        double                  DIMER;                  ///< dimer concentration
        double                  m_dimer;                ///< dimer mass

        //-----------

        double                  rC2H2_rSoot_n;          ///<
        double                  rH2_rSoot_ncnd;         ///< mass rate ratio: for gasSootSources from nucleation
        vector<double>          rPAH_rSoot_ncnd;        ///< mass rate ratio: for gasSootSources from nucleation/condensation
        double                  rO2_rSoot_go;           ///< mass rate ratio: for gasSootSources from growth/oxidation
        double                  rOH_rSoot_go;           ///<
        double                  rH_rSoot_go;            ///<
        double                  rCO_rSoot_go;           ///<
        double                  rH2_rSoot_go;           ///<
        double                  rC2H2_rSoot_go;         ///<

        //----------- gas state variables

        double                  T;                      ///< K
        double                  P;                      ///< Pa
        double                  rho;                    ///< kg/m3
        double                  MW;                     ///< kg/kmol mean molecular weight
        double                  mu;                     ///< kg/m*s
        vector<double>         *yi;                     ///< pointer to species mass fractions

        //-----------

        static int              i_c2h2;                 ///< soot gas species indices
        static int              i_o2;
        static int              i_h;
        static int              i_h2;
        static int              i_oh;
        static int              i_h2o;
        static int              i_co;
        static int              i_elem_c;               ///< index if element C
        static int              i_elem_h;               ///< index if element H
        static vector<int>      i_pah;                  ///< vector of PAH species indicies
        static vector<double>   MW_sp;                  ///< vector of molecular weights
        static vector<string>   spNames;                ///< gas species names
        static vector<int>      nC_PAH;                 ///< number of carbon atoms in each PAH molecule considered


    //////////////////// MEMBER FUNCTIONS /////////////////

    public:

        virtual void setSrc() = 0;            ///< this class is an abstract base class
        void   set_gas_state_vars(const double &T_p, const double &P_p, const double &rho_p, const double &MW_p, const double &mu_p, vector<double> &y_p);

    protected:


        double getNucleationRate  (const vector<double> &mi=vector<double>(0), const vector<double> &wi=vector<double>(0));
        double getGrowthRate      (const double &M0=-1, const double &M1=-1);
        double getOxidationRate   (const double &M0=-1, const double &M1=-1);
        double getCoagulationRate (const double &m1,    const double &m2);

        double get_gas_mean_free_path();
        double get_Kc();
        double get_Kcp();
        double get_Kfm();

        double set_m_dimer();
        void   set_Ndimer(const vector<double> &mi, const vector<double> &wi);

        void   set_gasSootSources(const double &N1, const double &Cnd1, const double &G1, const double &X1);

    private:

        double nucleation_LL      ();
        double nucleation_Linstedt();
        double nucleation_PAH     (const vector<double> &mi, const vector<double> &wi);

        double growth_Lindstedt   ();
        double growth_LL          (const double &M0, const double &M1);
        double growth_HACA        (const double &M0, const double &M1);

        double oxidation_LL       ();
        double oxidation_Lee_Neoh ();
        double oxidation_NSC_Neoh ();
        double oxidation_HACA     (const double &M0, const double &M1);

        double coagulation_LL     (const double &m1, const double &m2);
        double coagulation_Fuchs  (const double &m1, const double &m2);
        double coagulation_Frenk  (const double &m1, const double &m2);

    //////////////////// CONSTRUCTOR FUNCTIONS /////////////////

    public:

        soot(const int  p_nsvar, 
           vector<string> &spNames, 
           vector<string> &PAH_spNames, 
           vector<int>    &p_nC_PAH, 
           vector<double> &p_MW_sp,
           int            p_Cmin,
           double         p_rhoSoot,
           string         p_nucleation_mech,
           string         p_growth_mech,
           string         p_oxidation_mech,
           string         p_coagulation_mech);

        virtual ~soot(){}

};

