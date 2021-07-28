#ifndef PSDMODEL_MONO_H
#define PSDMODEL_MONO_H

#include "src/sootModels/psdModels/psdModel.h"
//#include "psdModel.h"

namespace soot {

    ////////////////////////////////////////////////////////////////////////////////
    /** An implementation of the psdModel interface following the MONO model
     *
     *      Associated with enum psdMech:MONO
     */
    class psdModel_MONO : public psdModel {

    //////////////// DATA MEMBERS /////////////////////

    private:

        size_t nMom = 2;

        nucleationMech nucleationMechanism;

    //////////////// MEMBER FUNCTIONS /////////////////

    private:

        ////////////////////////////////////////////////////////////////////////////////
        /** getSourceTermsImplementation function
         *
         *      Calculates soot source terms using monodispersed PSD model (MONO).
         *      Updates soot, gas, and PAH source terms (where applicable).
         *
         *      NOTE: PAH source terms are updated from within the getNucleationSootRate
         *      function associated with PAH nucleation.
         *
         *      @param  state    \input     thermodynamic state object
         *
         */
        void getSourceTermsImplementation(state& state, sourceTermStruct& sourceTerms) const override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

         explicit psdModel_MONO(sourceTermStruct& sourceTerms, int nVar = 2,
                                nucleationMech N = nucleationMech::NONE,
                                growthMech G = growthMech::NONE,
                                oxidationMech X = oxidationMech::NONE,
                                coagulationMech C = coagulationMech::NONE);

        ~psdModel_MONO() override = default;

    };
}

#endif //PSDMODEL_MONO_H
