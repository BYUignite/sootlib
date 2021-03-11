#ifndef SOOTMODEL_SECT_H
#define SOOTMODEL_SECT_H

#include "sootlib/soot_model/bin/BinSootModel.h"

namespace soot
{
class SootModel_SECT : public BinSootModel
{
public:
	[[nodiscard]] static SootModel_SECT* getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
	                                                 std::unique_ptr<GrowthModel> growthModel,
	                                                 std::unique_ptr<NucleationModel> nucleationModel,
	                                                 std::unique_ptr<OxidationModel> oxidationModel,
	                                                 CoagulationMechanism coagulationMechanism,
	                                                 GrowthMechanism growthMechanism,
	                                                 NucleationMechanism nucleationMechanism,
	                                                 OxidationMechanism oxidationMechanism);

	[[nodiscard]] SourceTerms getSourceTerms(const BinState& state) const override;

	~SootModel_SECT() override = default;

private:
	SootModel_SECT(std::unique_ptr<CoagulationModel> coagulationModel,
	               std::unique_ptr<GrowthModel> growthModel,
	               std::unique_ptr<NucleationModel> nucleationModel,
	               std::unique_ptr<OxidationModel> oxidationModel,
	               CoagulationMechanism coagulationMechanism,
	               GrowthMechanism growthMechanism,
	               NucleationMechanism nucleationMechanism,
	               OxidationMechanism oxidationMechanism);
};
}

#endif //SOOTMODEL_SECT_H
