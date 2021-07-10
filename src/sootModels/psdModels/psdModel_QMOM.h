#ifndef PSDMODEL_QMOM_H
#define PSDMODEL_QMOM_H

#include "psdModel.h"

namespace soot {

    /**
     * An implementation of the psdModel interface following the QMOM model
     *
     * Associated with the enum psdMech:QMOM
     */
    class psdModel_QMOM : public psdModel {

    //////////////// DATA MEMBERS /////////////////////

        size_t nMom = 4;    // default value // TODO incorporate user specified value

    //////////////// MEMBER FUNCTIONS /////////////////

    private:
        /**
         * source terms calculation function required by psdModel
         *
         * @param state contains soot and gas state data
         * @param out pointer to an outstream for debugging purposes, can be null
         * @return source terms object with computer values
         */
        sourceTermStruct getSourceTermsImplementation(state& state, std::ostream* out) const override;
        /**
         * throws exceptions if the state object is in an illegal state to calculate source terms required by psdModel
         *
         * @param state
         */
        void checkState(const state& state) const override;

        // helper functions specific to this PSD
        static void wheeler(const std::vector<double>& m, size_t N, std::vector<double>& w, std::vector<double>& x);
        static void getWtsAbs(const std::vector<double>& M, std::vector<double>& weights, std::vector<double>& abscissas);
        static double Mk(double exp, const std::vector<double>& wts, const std::vector<double>& absc);


    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

        psdModel_QMOM(size_t n);
        ~psdModel_QMOM() override = default;

    };
}

#endif //PSDMODEL_QMOM_H
