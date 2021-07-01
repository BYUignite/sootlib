/**
 * Josh Bedwell - June 2021
 */

#ifndef BASESOOTMODELFACTORY_H
#define BASESOOTMODELFACTORY_H

#include <memory>

/* Soot model */
#include "src/soot_model/psd_models/PSDModel.h"

/* coagulation model */
#include "src/soot_model/soot_chemistry/coagulation_model/CoagulationModel.h"

/* growth model */
#include "src/soot_model/soot_chemistry/growth_model/GrowthModel.h"

/* nucleation model */
#include "src/soot_model/soot_chemistry/nucleation_model/NucleationModel.h"

/* oxidation model */
#include "src/soot_model/soot_chemistry/oxidation_model/OxidationModel.h"

namespace soot {
/**
 * Used to create PSDModels
 *
 * Simplifies the process by eliminating user interaction with a complicated specific PSDModel constructor and having default values
 * Properties of the next PSDModel to be generated are set and then a PSDModel is generated
 */
class modelGenerator {
public:
    /**
     * Sets default properties of the next PSDModel to be generated
     */
    modelGenerator();

    /**
     * Sets the PSDMechanism the next generated PSDModel will use
     *
     * @param modelType
     */
    void setPSDModel(PSDMechanism modelType);
    /**
     * Sets the NucleationMechanism of the chemistry the next generated PSDModel will use
     *
     * @param mechanism
     */
    void setNucleationMechanism(NucleationMechanism mechanism);
    /**
     * Sets the GrowthMechanism of the chemistry the next generated PSDModel will use
     *
     * @param mechanism
     */
    void setGrowthMechanism(GrowthMechanism mechanism);
    /**
     * Sets the OxidationMechanism of the chemistry the next generated PSDModel will use
     *
     * @param mechanism
     */
    void setOxidationMechanism(OxidationMechanism mechanism);
    /**
     * Sets the CoagulationMechanism of the chemistry the next generated PSDModel will use
     *
     * @param mechanism
     */
    void setCoagulationMechanism(CoagulationMechanism mechanism);

    /**
     * Creates a new PSDModel based on the current parameters and returns a raw pointer to it
     *
     * @return raw pointer to a new PSDModel
     */
    [[nodiscard]] PSDModel* getModel() const;
    /**
     * Wrapper for getModel() which creates an std unique smart pointer
     *
     * @return unique pointer to a new PSDModel
     */
    [[nodiscard]] std::unique_ptr<PSDModel> getModelUnique() const;
    /**
     * Wrapper for getModel() which creates an std shared smart pointer
     *
     * @return shared pointer to a new PSDModel
     */
    [[nodiscard]] std::shared_ptr<PSDModel> getModelShared() const;

private:
    /**
     * The stored PSDMechanism for the next generated PSDModel
     */
    PSDMechanism psdMechanism;
    /**
     * The stored NucleationMechanism for the chemistry of the next generated PSDModel
     */
    NucleationMechanism nucleationMechanism;
    /**
     * The stored GrowthMechanism for the chemistry of the next generated PSDModel
     */
    GrowthMechanism growthMechanism;
    /**
     * The stored OxidationMechanism for the chemistry of the next generated PSDModel
     */
    OxidationMechanism oxidationMechanism;
    /**
     * The stored CoagulationMechanism for the chemistry of the next generated PSDModel
     */
    CoagulationMechanism coagulationMechanism;

    /**
     * Function that handles creating a pointer to a CoagulationModel based on the stored CoagulationMechanism
     * Called by getModel() when a new PSDModel is being generated
     *
     * @return a raw pointer to a CoagulationModel
     */
    [[nodiscard]] CoagulationModel* makeCoagulationModel() const;
    /**
     * Function that handles creating a pointer to a GrowthModel based on the stored GrowthMechanism
     * Called by getModel() when a new PSDModel is being generated
     *
     * @return a raw pointer to a GrowthModel
     */
    [[nodiscard]] GrowthModel* makeGrowthModel() const;
    /**
     * Function that handles creating a pointer to a NucleationModel based on the stored NucleationMechanism
     * Called by getModel() when a new PSDModel is being generated
     *
     * @return a raw pointer to a NucleationModel
     */
    [[nodiscard]] NucleationModel* makeNucleationModel() const;
    /**
     * Function that handles creating a pointer to an OxidationModel based on the stored OxidationMechanism
     * Called by getModel() when a new PSDModel is being generated
     *
     * @return a raw pointer to an OxidationModel
     */
    [[nodiscard]] OxidationModel* makeOxidationModel() const;
};
}

#endif //BASESOOTMODELFACTORY_H
