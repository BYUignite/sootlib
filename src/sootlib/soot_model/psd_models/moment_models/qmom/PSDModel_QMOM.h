/**
 * Josh Bedwell - June 2021
 */

#ifndef SOOTMODEL_QMOM_H
#define SOOTMODEL_QMOM_H

#include "sootlib/soot_model/PSDModel.h"
#include "sootlib/soot_model/SootChemistry.h"

namespace soot {
class PSDModel_QMOM : public PSDModel {
/**
 * An implementation of the PSDModel interface following the QMOM model
 *
 * Associated with the enum PSDMechanism:QMOM
 */
public:
    /**
     * Sets the sootChemistry member
     * Marked explicit to avoid unintentional implicit conversions due to single argument
     *
     * @param sootChemistry
     */
    explicit PSDModel_QMOM(const SootChemistry& sootChemistry);
    /**
     * Default deconstructor
     * requried by PSDModel
     */
    ~PSDModel_QMOM() override = default;

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
    static void wheeler(const std::vector<double>& m, size_t N, std::vector<double>& w, std::vector<double>& x);
    static void getWtsAbs(const std::vector<double>& M, std::vector<double>& weights, std::vector<double>& abscissas);
    [[nodiscard]] static double Mk(double exp, const std::vector<double>& wts, const std::vector<double>& absc);
};
}

#endif //SOOTMODEL_QMOM_H
