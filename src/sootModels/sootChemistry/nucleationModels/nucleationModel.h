#ifndef NUCLEATIONMODEL_H
#define NUCLEATIONMODEL_H

#include "src/state.h"
//#include "src/sootModel.h"
#include "src/constants.h"

namespace soot {

    class nucleationModel {

    //////////////// DATA MEMBERS /////////////////////

    public:

        dimerStruct DIMER;      // used for PAH nucleation only

    private:

        std::map<gasSp, double>   *nucleationRxnRatios;
        std::map<pahSp, double>   *nucleationPahRxnRatios;

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

        virtual double getNucleationSootRate(state& state, const std::vector<double> &mi, const std::vector<double> &wi) = 0;

        sourceTermStruct getNucleationGasRates(const state& state, const double &N1) const;  //TODO override for PAH nucleation

//        virtual void    getNucleationPahRates(state& state) const = 0;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

        nucleationModel();
        virtual ~nucleationModel() = default;

    };
}

#endif //NUCLEATIONMODEL_H
