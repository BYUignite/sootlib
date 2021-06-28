/**
 * Josh Bedwell - June 2021
 */

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
/**
 * An object which holds pointers to chemistry model objects used in PSD calculations
 *
 * All members of this class are public as it is a rather simple data storage object
 */
public:
    /**
     * Default constructor which sets all member pointers to null
     */
    SootChemistry() :
    coagulationModel(nullptr),
    growthModel(nullptr),
    nucleationModel(nullptr),
    oxidationModel(nullptr) {}
    /**
     * Constructor which sets each member pointer
     *
     * @param coagulationModel
     * @param growthModel
     * @param nucleationModel
     * @param oxidationModel
     */
    SootChemistry(CoagulationModel* coagulationModel,
                  GrowthModel* growthModel,
                  NucleationModel* nucleationModel,
                  OxidationModel* oxidationModel)
        : coagulationModel(coagulationModel),
          growthModel(growthModel),
          nucleationModel(nucleationModel),
          oxidationModel(oxidationModel) {}
    /**
     * Deconstructor which calls delete on all member pointers
     */
    ~SootChemistry() {
        delete coagulationModel;
        delete growthModel;
        delete nucleationModel;
        delete oxidationModel;
    }

    /**
     * Pointer to CoagulationModel
     */
    const CoagulationModel* coagulationModel;
    /**
     * Pointer to GrowthModel
     */
    const GrowthModel* growthModel;
    /**
     * Pointer to NucleationModel
     */
    const NucleationModel* nucleationModel;
    /**
     * Pointer to OxidationModel
     */
    const OxidationModel* oxidationModel;

    /**
     * Used for calculations which are repeated by most PSDModels at the end of their calculations
     *
     * @param state
     * @param ratio
     * @param N
     * @param G
     * @param X
     * @param C
     * @return
     */
    [[nodiscard]] static std::map<GasSpecies, double> getGasSourceTerms(const State& state, MassRateRatios& ratio, double N, double G, double X, double C);
    /**
     * Used for calculations which are repeated by most PSDModels at the end of their calculations
     *
     * @param state
     * @param ratio
     * @param N
     * @param G
     * @param X
     * @param C
     * @return
     */
    [[nodiscard]] static std::map<size_t, double> getPAHSourceTerms(const State& state, MassRateRatios& ratio, double N, double G, double X, double C);
};
}

#endif //SOOTMODEL_BASE_H
