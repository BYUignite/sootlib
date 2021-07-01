#ifndef BASESTATE_H
#define BASESTATE_H

#include "src/constants.h"

#include <vector>

namespace soot {
    class state {

        //////////////// DATA MEMBERS /////////////////////
        private:

            std::map<gasSpecies, double> gasFractions;
            std::map<size_t, double>     pahFractions;
            std::vector<double>          sootBins;

            double T = 0;
            double P = 0;
            double rhoGas = 0;
            double MWGas = 0;
            double muGas = 0;

        //////////////// MEMBER FUNCTIONS /////////////////

        public:
//            double get_PAHFrac(size_t n, double def = 0) const;
//            void   set_PAHFrac(size_t n, double frac);
            double get_PAHC(size_t n, double def = 0) const;
            double get_PAHP(size_t n, double def = 0) const;

            static double PAH_MW(size_t n);
            static double getPAHGamma(size_t n);
            double getPAHN(size_t n) const;

//            double          getsootBin(size_t i) const          { checkSize(i);return sootBins.at(i); }
//            void            setsootBin(size_t i, double value)  { checkSize(i);sootBins.at(i) = value; }
//            void            resetsootBins(size_t numsootBins)    { sootBins = vector<double>(numsootBins, 0); }
//            size_t          getNumsootBins() const              { return sootBins.size(); }
//            vector<double>  getsootBins() const                 { return sootBins; }

//            double  get_T() const                { return T; }
//            void    set_T(double t)              { T = t; }
//            double  get_P() const                { return P; }
//            void    set_P(double p)              { P = p; }
//            double  get_rhoGas() const           { return rhoGas; }
//            void    set_rhoGas(double rhoGas_)   { rhoGas = rhoGas_; }
//            double  get_cMin() const             { return cMin; }
//            void    set_cMin(double cMin_)       { cMin = cMin_; }
//
//            std::map<gasSpecies, double>::const_iterator gasFractionsBegin() const { return gasFractions.begin(); }
//            std::map<gasSpecies, double>::const_iterator gasFractionsEnd() const   { return gasFractions.end(); }
//
//            double  getMWGas() const            { return MWGas; }
//            void    setMWGas(double MWGas_)     { MWGas = MWGas_; }
//            double  getMuGas() const            { return muGas; }
//            void    setMuGas(double muGas_)     { muGas = muGas_; }
//
//            double  getGasSpeciesFrac(gasSpecies species, double def = 0) const;
//            void    setGasSpeciesFrac(gasSpecies species, double frac);
            double  getGasSpeciesC(gasSpecies species, double def = 0) const;
            double  getGasSpeciesP(gasSpecies species, double def = 0) const;
            double  getGasMeanFreePath() const;

            void setState();

//            void setPAHFrac(size_t n, double frac);

//            virtual void printInfo(std::ostream& out) const;

        //////////////// CONSTRUCTOR FUNCTIONS ////////////

    };
}



//void pahState::printInfo(ostream& out) const {
//    out << " === [pahState] ===" << endl;
//
//    out << "PAH fractions (" << PAHFractions.size() << ")" << endl;
//    for (const auto& [p, f] : PAHFractions)
//        out << "PAH species " << p << ": " << f << endl;
//    out << endl;
//}




#endif //BASESTATE_H
