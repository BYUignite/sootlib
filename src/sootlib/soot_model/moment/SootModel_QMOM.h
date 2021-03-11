#ifndef SOOTMODEL_QMOM_H
#define SOOTMODEL_QMOM_H

#include "sootlib/soot_model/moment/MomentSootModel.h"
#include "sootlib/MassRateRatio.h"

namespace soot
{
class SootModel_QMOM : public MomentSootModel
{
public:
	[[nodiscard]] static SootModel_QMOM* getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
	                                                 std::unique_ptr<GrowthModel> growthModel,
	                                                 std::unique_ptr<NucleationModel> nucleationModel,
	                                                 std::unique_ptr<OxidationModel> oxidationModel,
	                                                 CoagulationMechanism coagulationMechanism,
	                                                 GrowthMechanism growthMechanism,
	                                                 NucleationMechanism nucleationMechanism,
	                                                 OxidationMechanism oxidationMechanism);

	[[nodiscard]] SourceTerms getSourceTerms(MomentState& state) const override;

	~SootModel_QMOM() override = default;

private:
	SootModel_QMOM(std::unique_ptr<CoagulationModel> coagulationModel,
	               std::unique_ptr<GrowthModel> growthModel,
	               std::unique_ptr<NucleationModel> nucleationModel,
	               std::unique_ptr<OxidationModel> oxidationModel,
	               CoagulationMechanism coagulationMechanism,
	               GrowthMechanism growthMechanism,
	               NucleationMechanism nucleationMechanism,
	               OxidationMechanism oxidationMechanism);
};
}

#endif //SOOTMODEL_QMOM_H
