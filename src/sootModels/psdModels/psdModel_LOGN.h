#ifndef PSDMODEL_LOGN_H
#define PSDMODEL_LOGN_H

#include "psdModel.h"

namespace soot {

    ////////////////////////////////////////////////////////////////////////////////
    /** An implementation of the psdModel interface following the LOGN model
     *
     *      Associated with enum psdMech:LOGN
     */
    class psdModel_LOGN : public psdModel {

    //////////////// DATA MEMBERS /////////////////////

    private:

        nucleationMech nucleationMechanism;

    //////////////// MEMBER FUNCTIONS /////////////////

    private:

        ////////////////////////////////////////////////////////////////////////////////
        /** getSourceTermsImplementation function
         *
         *      Calculates soot source terms using lognormal PSD model (LOGN).
         *      Updates soot, gas, and PAH source terms (where applicable).
         *
         *      NOTE: PAH source terms are updated from within the getNucleationSootRate
         *      function associated with PAH nucleation.
         *
         *      @param  state    \input     thermodynamic state object
         *
         */
        void getSourceTermsImplementation(state& state, sourceTermStruct *sourceTerms) const override;

        ////////////////////////////////////////////////////////////////////////////////
        /** Mk function (LOGN)
         *
         *      Calculates fractional moment values assuming lognormal PSD
         *
         *      @param  k    \input     fractional moment to compute
         *      @param  M0   \input     moment value M0
         *      @param  M1   \input     moment value M1
         *      @param  M2   \input     moment value M2
         *
         */
        static double Mk(double k, double M0, double M1, double M2);

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

        psdModel_LOGN(sourceTermStruct* sourceTerms, int nVar,
                      nucleationMech N,
                      growthMech G,
                      oxidationMech X,
                      coagulationMech C);

        ~psdModel_LOGN() override = default;


    };
}

#endif //PSDMODEL_LOGN_H