/**
 * Josh Bedwell - June 2021
 */

#ifndef SOOTMODEL_MOMIC_H
#define SOOTMODEL_MOMIC_H

#include "sootlib/soot_model/PSDModel.h"
#include "sootlib/soot_model/SootChemistry.h"

namespace soot {
class PSDModel_MOMIC : public PSDModel {
/**
 * An implementation of the PSDModel interface following the MOMIC model
 *
 * Associated with the enum PSDMechanism:MOMIC
 */
public:
    /**
     * Sets the sootChemistry member
     * Marked explicit to avoid unintentional implicit conversions due to single argument
     *
     * @param sootChemistry
     */
    explicit PSDModel_MOMIC(const SootChemistry& sootChemistry);
    /**
     * Default deconstructor
     * requried by PSDModel
     */
    ~PSDModel_MOMIC() override = default;

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
    [[nodiscard]] static size_t downselectIfNeeded(std::vector<double>& M);
    [[nodiscard]] static double f_grid(int x, int y, const std::vector<double>& M);
    [[nodiscard]] static double MOMICCoagulationRate(const State& state, size_t r);
    [[nodiscard]] static double lagrangeInterp(double x_i, const std::vector<double>& x, const std::vector<double>& y);
    [[nodiscard]] static double MOMIC(double p, const std::vector<double>& M);
};
}

#endif //SOOTMODEL_MOMIC_H
