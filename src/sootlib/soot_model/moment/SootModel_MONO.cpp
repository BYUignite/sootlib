/**
 * @file SootModel_MONO.cc
 * Source file for class SootModel_MONO
 */

#include "SootModel_MONO.h"

using namespace soot;

SootModel_MONO::SootModel_MONO(std::unique_ptr<CoagulationModel> coagulationModel,
                                     std::unique_ptr<GrowthModel> growthModel,
                                     std::unique_ptr<NucleationModel> nucleationModel,
                                     std::unique_ptr<OxidationModel> oxidationModel)
	                : SootModel_Base(std::move(coagulationModel),
	                                 std::move(growthModel),
	                                 std::move(nucleationModel),
	                                 std::move(oxidationModel)) {}

SootModel_MONO* SootModel_MONO::getInstance(std::unique_ptr<CoagulationModel> coagulationModel,
                                                        std::unique_ptr<GrowthModel> growthModel,
                                                        std::unique_ptr<NucleationModel> nucleationModel,
                                                        std::unique_ptr<OxidationModel> oxidationModel)
{
	return new SootModel_MONO(std::move(coagulationModel),
	                          std::move(growthModel),
	                          std::move(nucleationModel),
	                          std::move(oxidationModel));
}

////////////////////////////////////////////////////////////////////////////////
/** getSourceTerms function
 *  
 *      Calculates soot source terms using monodispersed PSD model (MONO).
 *      Returns soot, gas, and PAH source terms (where applicable). 
 *
 *      @param  state    \input gas/soot state (?)
 *
 */

SourceTerms SootModel_MONO::getSourceTerms(MomentState& state) const {

	MassRateRatio nucleationRateRatios;
	MassRateRatio oxidationRateRatios;
	MassRateRatio growthRateRatios;

	std::vector<double> weights = {0};
	std::vector<double> abscissas = {0};

    //---------- get moments 
	
    if (state.getNumMoments() < 2)
		throw std::runtime_error("MONO soot model requires 2 soot moments");

	const double M0 = state.getMoment(0);
	const double M1 = state.getMoment(1);
    
    //---------- set weights and abscissas

	if (M0 > 0) {
		weights.at(0) = M0;
		abscissas.at(0) = M1 / M0;
	}

    //---------- get chemical rates
	
    const double jNuc = nucleationModel->getNucleationRate(state, abscissas, weights, nucleationRateRatios);
//	const double kGrw = growthModel->getGrowthRate(state, growthRateRatios); // TODO need to make something to deal with growth rate ratios
	const double kGrw = growthModel->getGrowthRate(state);
	const double kOxi = oxidationModel->getOxidationRate(state, oxidationRateRatios);
	const double coag = coagulationModel->getCoagulationRate(state, abscissas.at(0), abscissas.at(0));

    //---------- nucleation terms
	
    const double N0 = jNuc;
	const double N1 = jNuc * state.getCMin() * MW_C / Na;

    //---------- PAH condensation terms

	const double Cnd0 = 0;
	const double Cnd1 = nucleationModel->getMechanism() == NucleationMechanism::PAH ? state.getDimer() * state.getMDimer() * coagulationModel->getCoagulationRate(state, state.getMDimer(), abscissas.at(0)) * weights.at(0) : 0;

    //---------- growth terms

	const double Am2m3 = M0 > 0 ? M_PI * pow(std::abs(6.0 / (M_PI * state.getRhoSoot()) * M1 / M0), 2.0 / 3.0) * std::abs(M0) : 0;

	const double G0 = 0;
	const double G1 = kGrw * Am2m3;

    //---------- oxidation terms

	const double X0 = 0;
	const double X1 = -kOxi * Am2m3;

    //---------- coagulation terms

	const double C0 = -0.5 * coag * weights.at(0) * weights.at(0);
	const double C1 = 0;

    //---------- combinine to make soot source terms
	
    std::vector<double> sootSourceTerms = {(N0 + Cnd0 + G0 + X0 + C0)/state.getRhoGas(), (N1 + Cnd1 + G1 + X1 + C1)/state.getRhoGas()};

    //---------- get gas source terms
	
    std::map<GasSpecies, double> gasSourceTerms;
	std::map<size_t, double> PAHSourceTerms;

	// Nucleation
	for (auto it = nucleationRateRatios.gasSpeciesBegin(); it != nucleationRateRatios.gasSpeciesEnd(); it++)
		gasSourceTerms[it->first] += N1 * it->second / state.getRhoGas();
	for (auto it = nucleationRateRatios.PAHBegin(); it != nucleationRateRatios.PAHEnd(); it++)
		PAHSourceTerms[it->first] += N1 * it->second / state.getRhoGas();
	
    // Growth
	for (auto it = growthRateRatios.gasSpeciesBegin(); it != growthRateRatios.gasSpeciesEnd(); it++)
		gasSourceTerms[it->first] += G1 * it->second / state.getRhoGas();

	// Oxidation
	for (auto it = oxidationRateRatios.gasSpeciesBegin(); it != oxidationRateRatios.gasSpeciesEnd(); it++)
		gasSourceTerms[it->first] += X1 * it->second / state.getRhoGas();
	for (auto it = oxidationRateRatios.PAHBegin(); it != oxidationRateRatios.PAHEnd(); it++)
		PAHSourceTerms[it->first] += X1 * it->second / state.getRhoGas();

	// Coagulation - n/a

	return SourceTerms(sootSourceTerms, gasSourceTerms, PAHSourceTerms);
}
