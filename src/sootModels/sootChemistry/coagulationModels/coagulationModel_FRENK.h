#ifndef COAGULATIONMODEL_FRENK_H
#define COAGULATIONMODEL_FRENK_H

#include "coagulationModel.h"

namespace soot {

    ////////////////////////////////////////////////////////////////////////////////
    /*! Coagulation by Frenklach
     *
     *      Implementation of coagulationModel interface
     *
     *      Returns the value of the collision rate function beta in m3/#*s. See
     *      Frenklach & Wang (1994) "Detailed mechanism and modeling of soot particle
     *      formation" in Soot Formation in Combustion, pp. 165-192.
     *
     *      @param MomentState&     \input      local moment state; need M0 and M1
     *      @param m1               \input      first particle size (kg)
     *      @param m2               \input      second particle size (kg)
     *
     */
    class coagulationModel_FRENK : public coagulationModel {

    //////////////// DATA MEMBERS /////////////////////

    //////////////// MEMBER FUNCTIONS /////////////////

    public:
        /**
         * Calculates coagulation rate - required by coagulationModel
         *
         * @param state
         * @param m1
         * @param m2
         * @return
         */
         double getCoagulationSootRate(const state& state, double m1, double m2) const override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

         coagulationModel_FRENK() = default;
        ~coagulationModel_FRENK() override = default;
    };
}

#endif //COAGULATIONMODEL_FRENK_H
