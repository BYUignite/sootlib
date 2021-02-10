#ifndef SOOTMODEL_MONO_H
#define SOOTMODEL_MONO_H

#include <memory>

#include "sootlib/SootSourceTerms.h"
#include "sootlib/MomentSootModel.h"
#include "sootlib/state/soot/MomentSootState.h"
#include "sootlib/state/gas/GasState.h"

namespace soot
{
class SootModel_MONO : public MomentSootModel
{
public:
	[[nodiscard]] static SootModel_MONO* getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
	                                                std::unique_ptr<GrowthModel> growthModel,
	                                                std::unique_ptr<NucleationModel> nucleationModel,
	                                                std::unique_ptr<OxidationModel> oxidationModel);

	[[nodiscard]] SootSourceTerms getSourceTerms(const GasState& gasState, const MomentSootState& sootState) const override;

	~SootModel_MONO() override = default;

private:
	SootModel_MONO(std::unique_ptr<CoagulationModel> coagulationModel,
				std::unique_ptr<GrowthModel> growthModel,
				std::unique_ptr<NucleationModel> nucleationModel,
				std::unique_ptr<OxidationModel> oxidationModel);
};
}

#endif //SOOTMODEL_MONO_H
