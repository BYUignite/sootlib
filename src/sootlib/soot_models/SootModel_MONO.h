#ifndef SOOTMODEL_MONO_H
#define SOOTMODEL_MONO_H

#include <memory>
#include <vector>

#include <sootlib/state/MomentSootState.h>
#include <sootlib/state/GasState.h>
#include <sootlib/soot_models/MomentSootModel_Base.h>

namespace soot
{
class SootModel_MONO : public MomentSootModel_Base
{
public:
	[[nodiscard]] static SootModel_MONO* getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
	                                                std::unique_ptr<GrowthModel> growthModel,
	                                                std::unique_ptr<NucleationModel> nucleationModel,
	                                                std::unique_ptr<OxidationModel> oxidationModel,
	                                                size_t numSootVars);

	[[nodiscard]] std::vector<double> getSourceTerms(const GasState& gasState, const MomentSootState& sootState) override;

	~SootModel_MONO() override = default;

private:
	SootModel_MONO(std::unique_ptr<CoagulationModel> coagulationModel,
				std::unique_ptr<GrowthModel> growthModel,
				std::unique_ptr<NucleationModel> nucleationModel,
				std::unique_ptr<OxidationModel> oxidationModel,
				size_t numSootVars);
};
}

#endif //SOOTMODEL_MONO_H
