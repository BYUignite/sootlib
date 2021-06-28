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
public:
    SootChemistry() :
    coagulationModel(nullptr),
    growthModel(nullptr),
    nucleationModel(nullptr),
    oxidationModel(nullptr) {}
    SootChemistry(CoagulationModel* coagulationModel,
                  GrowthModel* growthModel,
                  NucleationModel* nucleationModel,
                  OxidationModel* oxidationModel)
        : coagulationModel(coagulationModel),
          growthModel(growthModel),
          nucleationModel(nucleationModel),
          oxidationModel(oxidationModel) {}
    ~SootChemistry() {
        delete coagulationModel;
        delete growthModel;
        delete nucleationModel;
        delete oxidationModel;
    }

    /* Calculation Models */
    const CoagulationModel* coagulationModel;
    const GrowthModel* growthModel;
    const NucleationModel* nucleationModel;
    const OxidationModel* oxidationModel;

    [[nodiscard]] static std::map<GasSpecies, double> getGasSourceTerms(const State& state, MassRateRatios& ratio, double N, double G, double X, double C);
    [[nodiscard]] static std::map<size_t, double> getPAHSourceTerms(const State& state, MassRateRatios& ratio, double N, double G, double X, double C);
};
}

#endif //SOOTMODEL_BASE_H
