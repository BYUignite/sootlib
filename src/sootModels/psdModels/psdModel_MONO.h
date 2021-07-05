/**
 * Josh Bedwell - June 2021
 */

#ifndef SOOTMODEL_MONO_H
#define SOOTMODEL_MONO_H

#include "sootlib/soot_model/PSDModel.h"
#include "sootlib/soot_model/SootChemistry.h"

namespace soot {
/**
 * An implementation of the PSDModel interface following the MONO model
 *
 * Associated with the enum PSDMechanism:MONO
 */
class PSDModel_MONO : public PSDModel {
public:
    /**
     * Sets the sootChemistry member
     * Marked explicit to avoid unintentional implicit conversions due to single argument
     *
     * @param sootChemistry
     */
    explicit PSDModel_MONO(const SootChemistry& sootChemistry);
    /**
     * Default deconstructor
     * requried by PSDModel
     */
    ~PSDModel_MONO() override = default;

private:
    /**
     * source terms calculation function required by PSDModel
     *
     * @param state contains soot and gas state data
     * @param out pointer to an outstream for debugging purposes, can be null
     * @return source terms object with computer values
     */
    [[nodiscard]] SourceTerms getSourceTermsImplementation(State& state, std::ostream* out) const override;
    /**
     * throws exceptions if the state object is in an illegal state to calculate source terms required by PSDModel
     *
     * @param state
     */
    void checkState(const State& state) const override;

    /**
     * SootChemistry member used in calculations during getSourceTermsImplementation
     */
    SootChemistry sootChemistry;

    // helper functions specific to this PSD
};
}

#endif //SOOTMODEL_MONO_H
