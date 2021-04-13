#ifndef SOOTMODEL_BASE_H
#define SOOTMODEL_BASE_H

#include <memory>

#include "sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel.h"
#include "sootlib/soot_model/soot_chemistry/growth_model/GrowthModel.h"
#include "sootlib/soot_model/soot_chemistry/nucleation_model/NucleationModel.h"
#include "sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel.h"

/*
 * Contains supporting psd_models that all soot psd_models will need for calculations
 */

namespace soot {
class SootChemistry {
protected:
    SootChemistry(std::unique_ptr<CoagulationModel> coagulationModel,
                  std::unique_ptr<GrowthModel> growthModel,
                  std::unique_ptr<NucleationModel> nucleationModel,
                  std::unique_ptr<OxidationModel> oxidationModel)
        : coagulationModel(std::move(coagulationModel)),
          growthModel(std::move(growthModel)),
          nucleationModel(std::move(nucleationModel)),
          oxidationModel(std::move(oxidationModel)) {}

    /* Calculation Models */
    const std::unique_ptr<CoagulationModel> coagulationModel;
    const std::unique_ptr<GrowthModel> growthModel;
    const std::unique_ptr<NucleationModel> nucleationModel;
    const std::unique_ptr<OxidationModel> oxidationModel;

    [[nodiscard]] static std::map<GasSpecies, double> getGasSourceTerms(const State& state, MassRateRatios& ratio, double N, double G, double X, double C);
    [[nodiscard]] static std::map<size_t, double> getPAHSourceTerms(const State& state, MassRateRatios& ratio, double N, double G, double X, double C);
};
}

#endif //SOOTMODEL_BASE_H
