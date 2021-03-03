#ifndef SOOTMODEL_MONO_H
#define SOOTMODEL_MONO_H

#include "sootlib/soot_model/moment/MomentSootModel.h"

namespace soot
{
class SootModel_MONO : public MomentSootModel
{
public:
	[[nodiscard]] static SootModel_MONO* getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
	                                                std::unique_ptr<GrowthModel> growthModel,
	                                                std::unique_ptr<NucleationModel> nucleationModel,
	                                                std::unique_ptr<OxidationModel> oxidationModel);

	[[nodiscard]] SourceTerms getSourceTerms(const MomentState& state) const override;

	~SootModel_MONO() override = default;

private:
	SootModel_MONO(std::unique_ptr<CoagulationModel> coagulationModel,
				std::unique_ptr<GrowthModel> growthModel,
				std::unique_ptr<NucleationModel> nucleationModel,
				std::unique_ptr<OxidationModel> oxidationModel);
};
}

#endif //SOOTMODEL_MONO_H
