/**
 * Josh Bedwell - June 2021
 */

#ifndef SOOTMODEL_LOGN_H
#define SOOTMODEL_LOGN_H

#include "sootlib/soot_model/PSDModel.h"
#include "sootlib/soot_model/SootChemistry.h"

namespace soot {
/**
 * An implementation of the PSDModel interface following the LOGN model
 * Inherits protected members from SootChemistry which gives it access to pointers to chemistry objects
 *
 * Associated with the enum PSDMechanism:LOGN
 */
class PSDModel_LOGN : public PSDModel {
public:
    /**
     * Gets a raw pointer to an instance of the class, calling its private constructor
     * Requires pointers to
     *
     * @param coagulationModel
     * @param growthModel
     * @param nucleationModel
     * @param oxidationModel
     * @return
     */
//    [[nodiscard]] static PSDModel_LOGN* getInstance(SootChemistry sootChemistry);

    explicit PSDModel_LOGN(const SootChemistry& sootChemistry);
    ~PSDModel_LOGN() override = default;

private:
    SootChemistry sootChemistry;

    [[nodiscard]] SourceTerms getSourceTermsImplementation(State& state, std::ostream* out) const override;

    void checkState(const State& state) const override;

    // helper functions specific to this PSD
    [[nodiscard]] static double Mk(double k, double M0, double M1, double M2);
    [[nodiscard]] static double getKfm(const State& state);
    [[nodiscard]] static double getKc(const State& state);
    [[nodiscard]] static double getKcp(const State& state);
};
}

#endif //SOOTMODEL_LOGN_H
