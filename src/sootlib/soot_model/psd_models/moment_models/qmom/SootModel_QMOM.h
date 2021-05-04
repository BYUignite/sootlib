/**
 * @file SootModel_QMOM.h
 * Header file for class SootModel_QMOM
 */

#ifndef SOOTMODEL_QMOM_H
#define SOOTMODEL_QMOM_H

#include "sootlib/soot_model/SootModel.h"
#include "sootlib/soot_model/SootChemistry.h"

namespace soot {
class SootModel_QMOM : public SootModel, public SootChemistry {
public:
    [[nodiscard]] static SootModel_QMOM* getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                     std::unique_ptr<GrowthModel> growthModel,
                                                     std::unique_ptr<NucleationModel> nucleationModel,
                                                     std::unique_ptr<OxidationModel> oxidationModel);

    ~SootModel_QMOM() override = default;

private:
    [[nodiscard]] SourceTerms getSourceTermsImpl(State& state, std::ostream* out) const override;

    SootModel_QMOM(std::unique_ptr<CoagulationModel> coagulationModel,
                   std::unique_ptr<GrowthModel> growthModel,
                   std::unique_ptr<NucleationModel> nucleationModel,
                   std::unique_ptr<OxidationModel> oxidationModel);

    // helper functions specific to this PSD
    static void wheeler(const std::vector<double>& m, size_t N, std::vector<double>& w, std::vector<double>& x);
    static void getWtsAbs(const std::vector<double>& M, std::vector<double>& weights, std::vector<double>& abscissas);
    [[nodiscard]] static double Mk(double exp, const std::vector<double>& wts, const std::vector<double>& absc);
};
}

#endif //SOOTMODEL_QMOM_H
