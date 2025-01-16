#pragma once

#include "sootDefs.h"

#include <vector>

namespace soot {

///////////////////////////////////////////////////////////////////////////////
///
/// Soot and gas state variables. Gas state includes T, P, yi (species mass fractions)
/// density, molecular weight, viscosity. Soot state includes the soot variables (e.g.,
/// moments or number of particles in a section). Also includes scaling factors for soot.
///
///////////////////////////////////////////////////////////////////////////////

class state {

    //////////////// DATA MEMBERS /////////////////////

    public:

        double              T = 0;         ///< gas temperature (K)
        double              P = 0;         ///< gas pressure (Pa)
        double              rhoGas = 0;    ///< gas density (kg/m3)
        double              MWGas = 0;     ///< gas mean molecular weight (kg/kmol)
        double              muGas = 0;     ///< gas viscosity (kg/m*s)
        std::vector<double> yGas;          ///< gas species mass fractions
        std::vector<double> yPah;          ///< gas PAH species mass fractions

        int                 nsoot;         ///< \# of soot variables
        std::vector<double> sootVar;       ///< soot variables (moments or \# in sections>
        std::vector<double> absc;          ///< moment abscissas
        std::vector<double> wts;           ///< moment weights
        std::vector<double> sootScales;    ///< soot scales for external numerical solvers
        double              cMin = 100;    ///< soot min num carbon atoms (dynamic for PAH nucleation)
        
        int                 Ntar;          ///< \# of tar variables   jansenpb: do I need this?
        std::vector<double> tarVar;        ///> tar variables 
        std::vector<double> yBio;          ///< biomass components from CPDbio
        double              mtar = 0.0;    ///< average tar molecular size jansenpb TODO: does this go here?
        double              ytar = 0.0;    ///< average tar mass fraction
        double              OC   = 0.0;    ///< oxygen-carbon ratio in coal      
        double              HC   = 0.0;    ///< hydrogen-carbon ratio in coal 
        double              V    = 0.0;    ///< mass % of volatile matter in coal 


    //////////////// MEMBER FUNCTIONS /////////////////

        void setState(double T_, double P_, double rhoGas_, double muGas_, 
                      std::vector<double> yGas_, std::vector<double> yPAH_, 
                      std::vector<double> sootVar_, int nsoot_ = 2, 
                      std::vector<double> tarVar_ = std::vector<double>(),
                      int Ntar_ = 0, double cMin_ = 100 ); 
        
        // TODO: make it so tar variables have defaults so non-tar sims don't need more inputs than necessary

        /** gas species concentration (kmol/m3) */
        double getGasSpC(gasSp sp)  const { return rhoGas * yGas[(int)sp] / gasSpMW[(int)sp]; }

        /** gas species partial pressure (Pa) */
        double getGasSpP(gasSp sp)  const { return yGas[(int)sp] * MWGas / gasSpMW[(int)sp] * P; }

        /** gas mean free path */
        double getGasMeanFreePath() const { return muGas/rhoGas*sqrt(M_PI*MWGas/(2.0*Rg*T)); }

        /** PAH species concentration (kmol/m3) */
        double get_pahSpC(pahSp sp) const { return rhoGas * yPah[(int)sp] / pahSpMW[(int)sp]; }

        /** PAH species partial pressure (Pa) */
        double get_pahSpP(pahSp sp) const { return yPah[(int)sp] * MWGas  / pahSpMW[(int)sp] * P; }

        /** sets variable sootScales */
        void setSootScales(std::vector<double> &sootScales_) { sootScales = sootScales_; }

        /** tar species concentration (kmol/m3) */
        //double getTarSpC(tarSp sp)  const {return rhoGas * yTar[(int)sp] / tarSpMW[(int)sp]; }

        /** set bio species mass fractions */ 
        void getyBio(std::vector<double> &yBio_) { yBio = yBio_; }

        /** get mtar and ytar from biomass*/ 
        void get_mtar_ytar();

        /** set coal O/C, H/C, and V */
        void get_coal(double OC_, double HC_, double V_);

        /** get mtar and ytar from coal */ 
        void get_mtar_ytar_coal();


    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    state(size_t nsoot_=0, size_t Ntar_ =0) :
        nsoot(nsoot_),
        Ntar(Ntar_),
        sootVar(std::vector<double>(   nsoot_,           0.0)),
        tarVar(std::vector<double> (   Ntar_,            0.0)),
        sootScales(std::vector<double>(nsoot_,           1.0)),
        absc(std::vector<double>(      nsoot_/2,         0.0)),
        wts(std::vector<double>(       nsoot_/2,         0.0)),
        yGas(std::vector<double>(      (int)gasSp::size, 0.0)),
        yPah(std::vector<double>(      (int)pahSp::size, 0.0)) { }
    ~state() = default;

};
}     // namespace soot
