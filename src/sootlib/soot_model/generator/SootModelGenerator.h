#ifndef BASESOOTMODELFACTORY_H
#define BASESOOTMODELFACTORY_H

#include <memory>

/* Soot model */
#include "sootlib/soot_model/SootModel.h"

/* coagulation model */
#include "sootlib/soot_model/soot_chemistry/coagulation_model/CoagulationModel.h"

/* growth model */
#include "sootlib/soot_model/soot_chemistry/growth_model/GrowthModel.h"

/* nucleation model */
#include "sootlib/soot_model/soot_chemistry/nucleation_model/NucleationModel.h"

/* oxidation model */
#include "sootlib/soot_model/soot_chemistry/oxidation_model/OxidationModel.h"

namespace soot {
class SootModelGenerator {
public:
    SootModelGenerator();

    void setModel(SootModelType modelType);
    void setNucleationMechanism(NucleationMechanism mechanism);
    void setGrowthMechanism(GrowthMechanism mechanism);
    void setOxidationMechanism(OxidationMechanism mechanism);
    void setCoagulationMechanism(CoagulationMechanism mechanism);

    [[nodiscard]] SootModel* getModel() const;
    [[nodiscard]] std::unique_ptr<SootModel> getModelUnique() const;
    [[nodiscard]] std::shared_ptr<SootModel> getModelShared() const;

private:
    SootModelType modelType;
    NucleationMechanism nucleationMechanism;
    GrowthMechanism growthMechanism;
    OxidationMechanism oxidationMechanism;
    CoagulationMechanism coagulationMechanism;

    [[nodiscard]] std::unique_ptr<CoagulationModel> getCoagulationModel() const;
    [[nodiscard]] std::unique_ptr<GrowthModel> getGrowthModel() const;
    [[nodiscard]] std::unique_ptr<NucleationModel> getNucleationModel() const;
    [[nodiscard]] std::unique_ptr<OxidationModel> getOxidationModel() const;
};
}

#endif //BASESOOTMODELFACTORY_H
