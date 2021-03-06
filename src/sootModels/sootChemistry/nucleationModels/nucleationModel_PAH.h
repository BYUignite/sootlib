#ifndef NUCLEATIONMODEL_PAH_H
#define NUCLEATIONMODEL_PAH_H

#include "nucleationModel.h"

namespace soot {

    ////////////////////////////////////////////////////////////////////////////////
    /*! PAH nucleation by Blanquart et al. (2009)
     *
     *      Rate from Blanquart & Pitsch (2009) article "A joint
     *      volume-surface-hydrogen multi-variate model for soot formation," ch. 27
     *      in Combustion Generated Fine Carbonaceous Particles ed. Bockhorn et al.
     *      Returns chemical nucleation rate in #/m3*s.
     *
     *      @param particleSizes        /input vector of soot particle sizes
     *      @param particleWeights      /input vector of soot particle weights
     */
    class nucleationModel_PAH : public nucleationModel {

    //////////////// DATA MEMBERS /////////////////////

    public:

        dimerStruct DIMER;      // contains mDimer, nDimer, and wDotD

    private:

        std::map<gasSp, double>  *nucleationRxnRatios;
        std::map<pahSp, double>  *nucleationPahRxnRatios;

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

        double getNucleationSootRate(state& state, const std::vector<double> &mi, const std::vector<double> &wi) override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

         nucleationModel_PAH();
        ~nucleationModel_PAH() override = default;
    };
}

#endif //NUCLEATIONMODEL_PAH_H
