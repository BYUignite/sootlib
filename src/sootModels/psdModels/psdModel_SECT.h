#pragma once

#include "src/sootModel.h"
//#include "sootModels/psdModels/psdModel.h"
#include "state.h"

namespace soot {

/**
 * An implementation of the psdModel interface following the SECT sectional/bin-based model
 *
 * Associated with the enum psdMech::SECT
 */
class psdModel_SECT : public sootModel {
//    class psdModel_SECT : public psdModel {

//////////////// DATA MEMBERS /////////////////////

private:

    size_t nBins;

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
    static std::vector<double> getDivision(double mass, double num, const std::vector<double>& absc);


//////////////// CONSTRUCTOR FUNCTIONS ////////////

public:

    psdModel_SECT(size_t n);
    ~psdModel_SECT() override = default;

};
} // namespace soot
