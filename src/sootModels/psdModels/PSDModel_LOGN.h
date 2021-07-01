/**
 * Josh Bedwell - June 2021
 */

#ifndef SOOTMODEL_LOGN_H
#define SOOTMODEL_LOGN_H

#include "sootlib/soot_model/PSDModel.h"
#include "sootlib/soot_model/SootChemistry.h"

namespace soot {
/**
 * An implementation of the PSDModel interface following the LOGN moment-based model
 *
 * Associated with the enum PSDMechanism:LOGN
 */
class PSDModel_LOGN : public PSDModel {
public:
    /**
     * Sets the sootChemistry member
     * Marked explicit to avoid unintentional implicit conversions due to single argument
     *
     * @param sootChemistry
     */
    explicit PSDModel_LOGN(const SootChemistry& sootChemistry);
    /**
     * Default deconstructor
     * requried by PSDModel
     */
    ~PSDModel_LOGN() override = default;

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
    [[nodiscard]] static double Mk(double k, double M0, double M1, double M2);
    [[nodiscard]] static double getKfm(const State& state);
    [[nodiscard]] static double getKc(const State& state);
    [[nodiscard]] static double getKcp(const State& state);
};
}

#endif //SOOTMODEL_LOGN_H
