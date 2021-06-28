/**
 * Josh Bedwell - June 2021
 */

#ifndef SOOTMODEL_SECT_H
#define SOOTMODEL_SECT_H

#include "sootlib/soot_model/PSDModel.h"
#include "sootlib/soot_model/SootChemistry.h"

namespace soot {
class PSDModel_SECT : public PSDModel {
/**
 * An implementation of the PSDModel interaface following the SECT sectional/bin-based model
 *
 * Associated with the enum PSDMechanism:SECT
 */
public:
    /**
     * Sets the sootChemistry member
     * Marked explicit to avoid unintentional implicit conversions due to single argument
     *
     * @param sootChemistry
     */
    explicit PSDModel_SECT(const SootChemistry& sootChemistry);
    /**
     * Default deconstructor
     * requried by PSDModel
     */
    ~PSDModel_SECT() override = default;

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
    // TODO I don't know good descriptions for these functions
    [[nodiscard]] static std::vector<double> getDivision(double mass, double num, const std::vector<double>& absc);
};
}

#endif //SOOTMODEL_SECT_H
