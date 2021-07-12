#ifndef PSDMODEL_LOGN_H
#define PSDMODEL_LOGN_H

#include "src/sootModel.h"
//#include "psdModel.h"

namespace soot {

    /**
     * An implementation of the psdModel interface following the LOGN moment-based model
     *
     * Associated with the enum psdMech:LOGN
     */
    class psdModel_LOGN : public sootModel {
//    class psdModel_LOGN : public psdModel {

    //////////////// DATA MEMBERS /////////////////////

    public:

        size_t nMom;

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
        static double Mk(double k, double M0, double M1, double M2);
        static double getKfm(const state& state);
        static double getKc( const state& state);
        static double getKcp(const state& state);

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

        psdModel_LOGN(size_t n);
        ~psdModel_LOGN() override = default;


    };
}

#endif //PSDMODEL_LOGN_H
