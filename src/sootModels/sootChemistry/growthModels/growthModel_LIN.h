#ifndef GROWTHMODEL_LIN_H
#define GROWTHMODEL_LIN_H

#include "growthModel.h"

namespace soot {

    ////////////////////////////////////////////////////////////////////////////////
    /*! Growth by Lindstedt (1994)
     *
     *      Rate from Bockhorn (1994) pg. 417, "Simplified Soot Nucleation and Surface Growth Steps..."
     *      Equation (27.35). Returns chemical surface growth rate in kg/m2*s.
     *
     *      @param MomentState&     /input      local moment state; need M0 and M1
     *      @param rSoot            /output     soot growth rate (kg/m2*s)
     */
    class growthModel_LIN : public growthModel {

    //////////////// DATA MEMBERS /////////////////////

    public:

        std::map<gasSp, double>   *growthRxnRatios;

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

         double getGrowthSootRate(const state &state) const override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

        growthModel_LIN();
        ~growthModel_LIN() override = default;

    };
}

#endif //GROWTHMODEL_LIN_H
