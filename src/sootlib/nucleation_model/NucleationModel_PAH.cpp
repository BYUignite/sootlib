#include "NucleationModel_PAH.h"
double soot::NucleationModel_PAH::getNucleationRate(MomentState& state,
                                                    const std::vector<double>& particleSizes,
                                                    const std::vector<double>& particleWeights) const
{
	std::unique_ptr<CoagulationModel> coagModel = std::make_unique<CoagulationModel_FRENK>();
	const double beta_DD = coagModel->getCoagulationRate(state, state.getMDimer(), state.getMDimer());

	return 0.5 * beta_DD * state.getDimer() * state.getDimer();
}
