#ifndef BASESOOTMODELFACTORY_H
#define BASESOOTMODELFACTORY_H

#include <memory>

/* Soot model */
#include "sootlib/soot_model/PSDModel.h"

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

    void setPSDModel(PSDMechanism modelType);
    void setNucleationMechanism(NucleationMechanism mechanism);
    void setGrowthMechanism(GrowthMechanism mechanism);
    void setOxidationMechanism(OxidationMechanism mechanism);
    void setCoagulationMechanism(CoagulationMechanism mechanism);

    [[nodiscard]] PSDModel* getModel() const;
    [[nodiscard]] std::unique_ptr<PSDModel> getModelUnique() const;
    [[nodiscard]] std::shared_ptr<PSDModel> getModelShared() const;

private:
    PSDMechanism psdMechanism;
    NucleationMechanism nucleationMechanism;
    GrowthMechanism growthMechanism;
    OxidationMechanism oxidationMechanism;
    CoagulationMechanism coagulationMechanism;

    [[nodiscard]] std::unique_ptr<CoagulationModel> makeCoagulationModel() const;
    [[nodiscard]] std::unique_ptr<GrowthModel> makeGrowthModel() const;
    [[nodiscard]] std::unique_ptr<NucleationModel> makeNucleationModel() const;
    [[nodiscard]] std::unique_ptr<OxidationModel> makeOxidationModel() const;
};
}

#endif //BASESOOTMODELFACTORY_H
