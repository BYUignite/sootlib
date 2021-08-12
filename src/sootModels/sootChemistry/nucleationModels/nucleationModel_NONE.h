#ifndef NUCLEATIONMODEL_NONE_H
#define NUCLEATIONMODEL_NONE_H

#include "nucleationModel.h"

namespace soot {

    class nucleationModel_NONE : public nucleationModel {

    //////////////// DATA MEMBERS /////////////////////

    private:

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

         double getNucleationSootRate(state &state) override { return 0; };

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

         nucleationModel_NONE() : nucleationModel() {};
        ~nucleationModel_NONE() override = default;

    };

}

#endif //NUCLEATIONMODEL_NONE_H
