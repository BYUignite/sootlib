#ifndef PSDMODEL_MONO_H
#define PSDMODEL_MONO_H

#include "src/sootModel.h"
//#include "psdModel.h"

namespace soot {

    ////////////////////////////////////////////////////////////////////////////////
    /** An implementation of the psdModel interface following the MONO model
     *
     *      Associated with enum psdMech:MONO
     */
    class psdModel_MONO : public sootModel {

    //////////////// DATA MEMBERS /////////////////////

    private:

        size_t nMom = 2;

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
        void getSourceTermsImplementation(state& state, std::ostream* out) const override;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

         explicit psdModel_MONO(size_t n);
        ~psdModel_MONO() override = default;

    };
}

#endif //PSDMODEL_MONO_H
