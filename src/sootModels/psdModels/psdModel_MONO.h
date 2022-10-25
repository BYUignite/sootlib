#pragma once

#include "sootModels/psdModels/psdModel.h"
#include "sootDefs.h"
#include "state.h"

namespace soot {

////////////////////////////////////////////////////////////////////////////////
/** An implementation of the psdModel interface following the MONO model
 *
 *      Associated with enum psdMech:MONO
 */
class psdModel_MONO : public psdModel {

//////////////// DATA MEMBERS /////////////////////

private:

//////////////// MEMBER FUNCTIONS /////////////////

    ////////////////////////////////////////////////////////////////////////////////
    /** setSourceTerms function
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
    void setSourceTerms(state& state, sourceTermStruct *sourceTerms) const override;

//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

     psdModel_MONO(int nVar,
                   nucleationMech N,
                   growthMech G,
                   oxidationMech X,
                   coagulationMech C);

    ~psdModel_MONO() override = default;

};
} // namespace soot
