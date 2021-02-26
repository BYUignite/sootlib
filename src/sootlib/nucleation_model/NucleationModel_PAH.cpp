#include "NucleationModel_PAH.h"
double soot::NucleationModel_PAH::getNucleationRate(const soot::State& gasState,
                                                    const soot::MomentSootState& sootState,
                                                    const std::vector<double>& particleSizes,
                                                    const std::vector<double>& particleWeights) const
{
	// TODO this seems unsupported
	// set_Ndimer


	std::unique_ptr<CoagulationModel> coagModel = std::make_unique<CoagulationModel_FRENK>();
	const double beta_DD = coagModel->getCoagulationRate(gasState, sootState, sootState.getMDimer(), sootState.getMDimer());

	return 0.5 * beta_DD * sootState.getDimer() * sootState.getDimer();
}
