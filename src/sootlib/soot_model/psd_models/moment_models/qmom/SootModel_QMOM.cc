/**
 * @file SootModel_QMOM.cc
 * Source file for class SootModel_QMOM
 */

#include "SootModel_QMOM.h"
#include "lib/eispack/eispack.h"
#include "sootlib/soot_model/static.h"

using namespace std;
using namespace soot;

SootModel_QMOM::SootModel_QMOM(unique_ptr<CoagulationModel> coagulationModel,
                               unique_ptr<GrowthModel> growthModel,
                               unique_ptr<NucleationModel> nucleationModel,
                               unique_ptr<OxidationModel> oxidationModel)
    : SootChemistry(move(coagulationModel),
                    move(growthModel),
                    move(nucleationModel),
                    move(oxidationModel)) {}

SootModel_QMOM* SootModel_QMOM::getInstance(unique_ptr<CoagulationModel> coagulationModel,
                                            unique_ptr<GrowthModel> growthModel,
                                            unique_ptr<NucleationModel> nucleationModel,
                                            unique_ptr<OxidationModel> oxidationModel) {

    return new SootModel_QMOM(move(coagulationModel),
                              move(growthModel),
                              move(nucleationModel),
                              move(oxidationModel));
}

////////////////////////////////////////////////////////////////////////////////
/** getSourceTerms function
 *  
 *      Calculates soot source terms using quadrature method of momdents
 *      (QMOM). Returns soot, gas, and PAH source terms (where applicable). 
 *
 *      @param  state    \input gas/soot state (?)
 *
 */

SourceTerms SootModel_QMOM::getSourceTerms(State& state) const {

    MassRateRatios massRateRatios;

    vector<double> M(state.getNumMoments(), 0);
    vector<double> weights = {0};
    vector<double> abscissas = {0};

    //---------- get moments

    if (state.getNumMoments() % 2 == 1)
        throw runtime_error("QMOM soot model requires even number of moments");
    if (state.getNumMoments() < 2)
        throw runtime_error("QMOM soot model requries at least 2 moments");

    for (size_t i = 0; i < state.getNumMoments(); i++)
        M.at(i) = state.getMoment(i);

    //---------- set weights and abscissas

    getWtsAbs(M, weights, abscissas);           // wheeler algorithms applied here

    for (size_t i = 0; i < weights.size(); i++) {
        if (weights.at(i) < 0)
            weights.at(i) = 0;
        if (abscissas.at(i) < 0)
            abscissas.at(i) = 0;
    }

    //---------- get chemical rates

    const double jNuc = nucleationModel->getNucleationRate(state, abscissas, weights, massRateRatios);
    const double kGrw = growthModel->getGrowthRate(state, massRateRatios);
    const double kOxi = oxidationModel->getOxidationRate(state, massRateRatios);
//    const double coag = coagulationModel->getCoagulationRate(state, abscissas.at(0), abscissas.at(0));

    //---------- nucleation terms

    vector<double> nucleationSourceM(state.getNumMoments(), 0.);                        // nucleation source terms for moments
    const double mNuc = state.getCMin() * MW_C / Na;                              // mass of a nucleated particle
    for (size_t i = 0; i < state.getNumMoments(); i++)
        nucleationSourceM.at(i) = pow(mNuc, i) * jNuc;                          // Nuc_rate = m_nuc^r * jNuc

    //---------- PAH condensation terms

    vector<double> condensationSourceM(state.getNumMoments(), 0);                            // PAH condensation source terms
    if (nucleationModel->getMechanism() == NucleationMechanism::PAH) {      // do PAH condensation if PAH nucleation is selected
        for (size_t i = 1; i < state.getNumMoments(); i++) {                                         // M0 = 0.0 for condensation by definition
            for (size_t j = 0; j < abscissas.size(); j++)
                condensationSourceM.at(i) += coagulationModel->getCoagulationRate(state, state.getMDimer(), abscissas.at(j)) * pow(abscissas.at(j), i - 1) * weights.at(j);
            condensationSourceM.at(i) *= state.getDimer() * state.getMDimer() * (double) i;
        }
    }

    //---------- growth terms

    vector<double> growthSourceM(state.getNumMoments(), 0);                                      // growth source terms for moments
    const double Acoef = M_PI * pow(abs(6 / M_PI / state.getRhoSoot()), 2.0 / 3);   // Acoef (=) kmol^2/3 / kg^2/3
    for (size_t i = 1; i < state.getNumMoments(); i++)                                                   // M0 = 0.0 for growth by definition
        growthSourceM.at(i) = kGrw * Acoef * (double) i * Mk((double) i - 1.0 / 3, weights, abscissas);                  // kg^k/m3*s

    //---------- oxidation terms

    vector<double> oxidationSourceM(state.getNumMoments(), 0);                                   // oxidation source terms
    for (size_t i = 1; i < state.getNumMoments(); i++)                                                   // M0 = 0.0 for oxidation by definition
        oxidationSourceM.at(i) = -kOxi * Acoef * (double) i * Mk((double) i - 1.0 / 3, weights, abscissas);              // kg^k/m3*s

    //---------- coagulation terms

    vector<double> coagulationSourceM(state.getNumMoments(), 0);                                 // coagulation source terms: initialize to zero!

    // there is a different case for the first moment
    // the second moment does not need calculation
    // the other moments are handled by the second loop
    for (size_t i = 0; i < abscissas.size(); i++) {
    	if (i != 0) {
    		for (size_t j = 0; j < i; j++)
			    coagulationSourceM.at(0) += coagulationModel->getCoagulationRate(state, abscissas.at(i), abscissas.at(j)) * weights.at(i) * weights.at(j) * -1;
    	}
	    coagulationSourceM.at(0) += coagulationModel->getCoagulationRate(state, abscissas.at(i), abscissas.at(i)) * weights.at(i) * weights.at(i) * -0.5;
    }
    for (size_t i = 2; i < state.getNumMoments(); i++) {
    	for (size_t j = 0; j < abscissas.size(); j++) {
    		if (j != 0) {
    			for (size_t k = 0; k < j; k++)
				    coagulationSourceM.at(i) += coagulationModel->getCoagulationRate(state, abscissas.at(j), abscissas.at(k)) * weights.at(j) * weights.at(k) * (i == 0 ? -1 : (pow(abscissas.at(j) + abscissas.at(k), i)) - pow(abscissas.at(j), i) - pow(abscissas.at(k), i));
    		}
		    coagulationSourceM.at(i) += coagulationModel->getCoagulationRate(state, abscissas.at(j), abscissas.at(j)) * weights.at(j) * weights.at(j) * (i == 0 ? -0.5 : pow(abscissas.at(j), i) * (pow(2, i - 1) - 1));
    	}
    }

    //---------- combinine to make source terms

    vector<double> sootSourceTerms(state.getNumMoments(), 0);

    for (size_t i = 0; i < state.getNumMoments(); i++)
        sootSourceTerms.at(i) = (nucleationSourceM.at(i) + condensationSourceM.at(i) + growthSourceM.at(i) + oxidationSourceM.at(i) + coagulationSourceM.at(i)) / state.getRhoGas();

    //---------- get gas source terms

    map<GasSpecies, double> gasSourceTerms;
    map<size_t, double> PAHSourceTerms;

    // Nucleation
    for (auto it = massRateRatios.nucCond().gasSpeciesBegin(); it != massRateRatios.nucCond().gasSpeciesEnd(); it++)
        gasSourceTerms.at(it->first) += nucleationSourceM.at(1) * it->second / state.getRhoGas();
    for (auto it = massRateRatios.nucCond().PAHBegin(); it != massRateRatios.nucCond().PAHEnd(); it++)
        PAHSourceTerms.at(it->first) += nucleationSourceM.at(1) * it->second / state.getRhoGas();

    // Growth
    for (auto it = massRateRatios.groOxi().gasSpeciesBegin(); it != massRateRatios.groOxi().gasSpeciesEnd(); it++)
        gasSourceTerms.at(it->first) += growthSourceM.at(1) * it->second / state.getRhoGas();

    // Oxidation
    for (auto it = massRateRatios.groOxi().gasSpeciesBegin(); it != massRateRatios.groOxi().gasSpeciesEnd(); it++)
        gasSourceTerms.at(it->first) += oxidationSourceM.at(1) * it->second / state.getRhoGas();
    for (auto it = massRateRatios.groOxi().PAHBegin(); it != massRateRatios.groOxi().PAHEnd(); it++)
        PAHSourceTerms.at(it->first) += oxidationSourceM.at(1) * it->second / state.getRhoGas();

    // Coagulation - n/a

    return SourceTerms(sootSourceTerms, gasSourceTerms, PAHSourceTerms);
}
