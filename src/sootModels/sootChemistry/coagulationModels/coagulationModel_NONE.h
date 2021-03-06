#ifndef COAGULATIONMODEL_NONE_H
#define COAGULATIONMODEL_NONE_H

#include "coagulationModel.h"

namespace soot {

    /**
    * The default implementation of coagulationModel interface
    */
    class coagulationModel_NONE : public coagulationModel {

    //////////////// DATA MEMBERS /////////////////////

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

        /**
         * Always returns 0 for coagulation rate - required by coagulationModel
         *
         * @param state
         * @param m1
         * @param m2
         */
         double getCoagulationSootRate(const state& state, double m1, double m2) const override { return 0; }

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

        coagulationModel_NONE() = default;
        ~coagulationModel_NONE() override = default;
    };
}

#endif //COAGULATIONMODEL_NONE_H
