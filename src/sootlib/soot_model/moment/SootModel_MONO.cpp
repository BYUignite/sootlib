#include "SootModel_MONO.h"
soot::SootModel_MONO::SootModel_MONO(std::unique_ptr<CoagulationModel> coagulationModel,
                                     std::unique_ptr<GrowthModel> growthModel,
                                     std::unique_ptr<NucleationModel> nucleationModel,
                                     std::unique_ptr<OxidationModel> oxidationModel)
	: MomentSootModel(std::move(coagulationModel),
	                 std::move(growthModel),
	                 std::move(nucleationModel),
	                 std::move(oxidationModel))
{
}
soot::SootModel_MONO* soot::SootModel_MONO::getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                        std::unique_ptr<GrowthModel> growthModel,
                                                        std::unique_ptr<NucleationModel> nucleationModel,
                                                        std::unique_ptr<OxidationModel> oxidationModel)
{
	return new SootModel_MONO(std::move(coagulationModel),
	                          std::move(growthModel),
	                          std::move(nucleationModel),
	                          std::move(oxidationModel));
}
soot::SourceTerms soot::SootModel_MONO::getSourceTerms(MomentState& state) const
{
	MassRateRatio nucleationRateRatios;
	MassRateRatio oxidationRateRatios;

	std::vector<double> weights = {0};
	std::vector<double> abscissas = {0};

	if (state.getNumMoments() < 2)
		throw std::runtime_error("MONO soot model requries at least 2 soot moments");

	const double M0 = state.getMoment(0);
	const double M1 = state.getMoment(1);

	if (M0 > 0)
	{
		weights.at(0) = M0;
		abscissas.at(0) = M1 / M0;
	}

	const double jNuc = nucleationModel->getNucleationRate(state, abscissas, weights, nucleationRateRatios);
	const double kGrw = growthModel->getGrowthRate(state);
	const double kOxi = oxidationModel->getOxidationRate(state, oxidationRateRatios);
	const double coag = coagulationModel->getCoagulationRate(state, abscissas.at(0), abscissas.at(0));

	const double N0 = jNuc;
	const double N1 = jNuc * state.getCMin() * MW_C / Na;

	const double Cnd0 = 0;
	const double Cnd1 = nucleationModel->getMechanism() == NucleationMechanism::PAH ? state.getDimer() * state.getMDimer() * coagulationModel->getCoagulationRate(state, state.getMDimer(), abscissas.at(0)) * weights.at(0) : 0;

	const double Am2m3 = M0 > 0 ? M_PI * pow(std::abs(6.0 / (M_PI * state.getRhoSoot()) * M1 / M0), 2.0 / 3.0) * std::abs(M0) : 0;

	const double G0 = 0;
	const double G1 = kGrw * Am2m3;

	const double X0 = 0;
	const double X1 = -kOxi * Am2m3;

	const double C0 = -0.5 * coag * weights.at(0) * weights.at(0);
	const double C1 = 0;

	std::vector<double> sootSourceTerms = {N0 + Cnd0 + G0 + X0 + C0, N1 + Cnd1 + G1 + X1 + C1};
	std::map<GasSpecies, double> gasSourceTerms;
	std::map<size_t, double> PAHSourceTerms;

	// initialize all gas sources to 0
	initializeGasSpecies(gasSourceTerms, PAHSourceTerms, nucleationRateRatios);
	initializeGasSpecies(gasSourceTerms, PAHSourceTerms, oxidationRateRatios);

	// Nucleation
	for (auto it = nucleationRateRatios.gasSpeciesBegin(); it != nucleationRateRatios.gasSpeciesEnd(); it++)
		gasSourceTerms[it->first] += N1 * it->second / state.getRhoGas();
	for (auto it = nucleationRateRatios.PAHBegin(); it != nucleationRateRatios.PAHEnd(); it++)
		PAHSourceTerms[it->first] += N1 * it->second / state.getRhoGas();

	// Oxidation
	for (auto it = oxidationRateRatios.gasSpeciesBegin(); it != oxidationRateRatios.gasSpeciesEnd(); it++)
		gasSourceTerms[it->first] += X1 * it->second / state.getRhoGas();
	for (auto it = oxidationRateRatios.PAHBegin(); it != oxidationRateRatios.PAHEnd(); it++)
		PAHSourceTerms[it->first] += X1 * it->second / state.getRhoGas();

	// Coagulation - n/a

	return SourceTerms(sootSourceTerms, gasSourceTerms, PAHSourceTerms);
}
