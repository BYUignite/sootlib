#pragma once

#include "psdModel.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
/** An implementation of the psdModel interface following the MONO model
 *
 *      Associated with enum psdMech:MONO
 */
class psdModel_MONO : public psdModel {

//////////////// DATA MEMBERS /////////////////////

private:

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
    void getSourceTermsImplementation(state& state, sourceTermStruct *sourceTerms) const override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

     psdModel_MONO(sourceTermStruct* sourceTerms, int nVar,
                   nucleationMech N,
                   growthMech G,
                   oxidationMech X,
                   coagulationMech C);

    ~psdModel_MONO() override = default;

};
} // namespace soot
