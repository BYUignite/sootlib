#ifndef PSDMODEL_MOMIC_H
#define PSDMODEL_MOMIC_H

#include "src/sootModel.h"
//#include "psdModel.h"
#include "include/extern/binomial/binomial.h"

namespace soot {

    /** An implementation of the psdModel interface following the MOMIC model
     *
     *  Associated with the enum psdMech:MOMIC
     */
    class psdModel_MOMIC : public sootModel {
//    class psdModel_MOMIC : public psdModel {

    //////////////// DATA MEMBERS /////////////////////

        size_t nMom = 4;        // default value

    //////////////// MEMBER FUNCTIONS /////////////////

    private:

        /**
         * source terms calculation function required by psdModel
         *
         * @param state contains soot and gas state data
         * @param out pointer to an outstream for debugging purposes, can be null
         * @return source terms object with computer values
         */
        void getSourceTermsImplementation(state& state, std::ostream* out) const override;

        /**
         * throws exceptions if the state object is in an illegal state to calculate source terms required by psdModel
         *
         * @param state
         */
        void checkState(const state& state) const override;

        // helper functions specific to this PSD
        static size_t downselectIfNeeded(std::vector<double>& M);
        static double f_grid(int x, int y, const std::vector<double>& M);
        static double MOMICCoagulationRate(const state& state, size_t r);
        static double lagrangeInterp(double x_i, const std::vector<double>& x, const std::vector<double>& y);
        static double MOMIC(double p, const std::vector<double>& M);

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

        psdModel_MOMIC(size_t n);
        ~psdModel_MOMIC() override = default;


    };
}

#endif //SOOTMODEL_MOMIC_H
