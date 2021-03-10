#include "SootModel_MONO.h"
soot::SootModel_MONO::SootModel_MONO(std::unique_ptr<CoagulationModel> coagulationModel,
                                     std::unique_ptr<GrowthModel> growthModel,
                                     std::unique_ptr<NucleationModel> nucleationModel,
                                     std::unique_ptr<OxidationModel> oxidationModel,
                                     CoagulationMechanism coagulationMechanism,
                                     GrowthMechanism growthMechanism,
                                     NucleationMechanism nucleationMechanism,
                                     OxidationMechanism oxidationMechanism)
	: MomentSootModel(std::move(coagulationModel),
	                 std::move(growthModel),
	                 std::move(nucleationModel),
	                 std::move(oxidationModel),
	                 coagulationMechanism,
	                 growthMechanism,
	                 nucleationMechanism,
	                 oxidationMechanism)
{
}
soot::SootModel_MONO* soot::SootModel_MONO::getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                        std::unique_ptr<GrowthModel> growthModel,
                                                        std::unique_ptr<NucleationModel> nucleationModel,
                                                        std::unique_ptr<OxidationModel> oxidationModel,
                                                        CoagulationMechanism coagulationMechanism,
                                                        GrowthMechanism growthMechanism,
                                                        NucleationMechanism nucleationMechanism,
                                                        OxidationMechanism oxidationMechanism)
{
	return new SootModel_MONO(std::move(coagulationModel),
	                          std::move(growthModel),
	                          std::move(nucleationModel),
	                          std::move(oxidationModel),
	                          coagulationMechanism,
	                          growthMechanism,
	                          nucleationMechanism,
	                          oxidationMechanism);
}
soot::SourceTerms soot::SootModel_MONO::getSourceTerms(MomentState& state) const
{
	std::vector<double> weights = {0};
	std::vector<double> abscissas = {0};

	const double M0 = state.getMoment(0);
	const double M1 = state.getMoment(1);

	if (M0 > 0)
	{
		weights.at(0) = M0;
		abscissas.at(0) = M1 / M0;
	}

	const double jNuc = nucleationModel->getNucleationRate(state, abscissas, weights);
	const double kGrw = growthModel->getGrowthRate(state);
	const double kOxi = oxidationModel->getOxidationRate(state);
	const double coag = coagulationModel->getCoagulationRate(state, abscissas.at(0), abscissas.at(0));

	const double N0 = jNuc;
	const double N1 = jNuc * state.getCMin() * MW_C / Na;

	const double Cnd0 = 0;
	const double Cnd1 = nucleationMechanism == NucleationMechanism::PAH ? state.getDimer() * state.getMDimer() * coagulationModel->getCoagulationRate(state, state.getMDimer(), abscissas.at(0)) * weights.at(0) : 0;

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

	// FIXME there are rate ratios that are not being kept track of
	// they probably need to go in the state somewhere but the state is getting a little bloated

	// Nucleation
	gasSourceTerms[GasSpecies::C2H2] = N1 * 0000000000 / state.getRhoGas();
	gasSourceTerms[GasSpecies::H2] = N1 * 00000000000 / state.getRhoGas();
	for (auto it = state.PAHFractionsBegin(); it != state.PAHFractionsEnd(); it++)
		PAHSourceTerms[it->first] = N1 * 00000000000 / state.getRhoGas();

	// Growth
	gasSourceTerms[GasSpecies::C2H2] += G1 * 000000000 / state.getRhoGas();
	gasSourceTerms[GasSpecies::H2] += G1 * 00000000000 / state.getRhoGas();

	// Oxidation
	gasSourceTerms[GasSpecies::O2] = X1 * 0000000000 / state.getRhoGas();
	gasSourceTerms[GasSpecies::OH] = X1 * 0000000000 / state.getRhoGas();
	gasSourceTerms[GasSpecies::H] = X1 * 0000000000 / state.getRhoGas();
	gasSourceTerms[GasSpecies::CO] = X1 * 0000000000 / state.getRhoGas();

	// PAH Condensation
	gasSourceTerms[GasSpecies::H2] += Cnd1 * 00000000000 / state.getRhoGas();
	for (auto it = state.PAHFractionsBegin(); it != state.PAHFractionsEnd(); it++)
		PAHSourceTerms[it->first] += Cnd1 * 0000000000 / state.getRhoGas();

	// Coagulation - n/a

	return SourceTerms(sootSourceTerms, gasSourceTerms, PAHSourceTerms);
}
