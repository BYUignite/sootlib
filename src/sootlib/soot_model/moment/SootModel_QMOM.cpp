/**
 * @file SootModel_QMOM.cpp
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
    : SootModel_Base(move(coagulationModel),
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

SourceTerms SootModel_QMOM::getSourceTerms(InputState& state) const {

    MassRateRatios massRateRatios;

    int nMom = state.getNumMoments();
    vector<double> M(nMom, 0);
    vector<double> weights = {0};
    vector<double> abscissas = {0};

    //---------- get moments

    if (nMom % 2 == 1)
        throw runtime_error("QMOM soot model requires even number of moments");
    if (nMom < 2)
        throw runtime_error("QMOM soot model requries at least 2 moments");

    for (int k = 0; k < nMom; k++)
        M.at(k) = state.getMoment(k);

    //---------- set weights and abscissas

    getWtsAbs(M, weights, abscissas);           // wheeler algorithms applied here

    for (int i = 0; i < weights.size(); i++) {
        if (weights.at(i) < 0.0)
            weights.at(i) = 0.0;
        if (abscissas.at(i) < 0.0)
            abscissas.at(i) = 0.0;
    }

    //---------- get chemical rates

    const double jNuc = nucleationModel->getNucleationRate(state, abscissas, weights, massRateRatios);
    const double kGrw = growthModel->getGrowthRate(state, massRateRatios);
    const double kOxi = oxidationModel->getOxidationRate(state, massRateRatios);
//    const double coag = coagulationModel->getCoagulationRate(state, abscissas.at(0), abscissas.at(0));

    //---------- nucleation terms

    vector<double> nucleationSourceM(nMom, 0.0);                        // nucleation source terms for moments
    double mNuc = state.getCMin() * MW_C / Na;                              // mass of a nucleated particle
    for (int k = 0; k < nMom; k++)
        nucleationSourceM.at(k) = pow(mNuc, k) * jNuc;                          // Nuc_rate = m_nuc^r * jNuc

    //---------- PAH condensation terms

    vector<double> condensationSourceM(nMom, 0.0);                            // PAH condensation source terms
    if (nucleationModel->getMechanism()
        == NucleationMechanism::PAH) {      // do PAH condensation if PAH nucleation is selected
        for (int k = 1; k < nMom;
             k++) {                                         // M0 = 0.0 for condensation by definition
            for (int ii = 0; ii < abscissas.size(); ii++)
                condensationSourceM.at(k) += coagulationModel->getCoagulationRate(state, state.getMDimer(), abscissas.at(ii)) * pow(abscissas.at(ii), k - 1) * weights.at(ii);
            condensationSourceM.at(k) *= state.getDimer() * state.getMDimer() * k;
        }
    }

    //---------- growth terms

    vector<double> growthSourceM(nMom, 0.0);                                      // growth source terms for moments
    double Acoef = M_PI * pow(abs(6.0 / M_PI / state.getRhoSoot()), 2.0 / 3.0);   // Acoef (=) kmol^2/3 / kg^2/3
    for (int k = 1; k < nMom; k++)                                                   // M0 = 0.0 for growth by definition
        growthSourceM.at(k) = kGrw * Acoef * k * Mk(k - 1.0 / 3.0, weights, abscissas);                  // kg^k/m3*s

    //---------- oxidation terms

    vector<double> oxidationSourceM(nMom, 0.0);                                   // oxidation source terms
    for (int k = 1; k < nMom; k++)                                                   // M0 = 0.0 for oxidation by definition
        oxidationSourceM.at(k) = -kOxi * Acoef * k * Mk(k - 1.0 / 3.0, weights, abscissas);              // kg^k/m3*s

    //---------- coagulation terms

    vector<double>
        coagulationSourceM(nMom, 0.0);                                 // coagulation source terms: initialize to zero!
    for (int k = 0; k < nMom; k++) {
        if (k == 1)
            continue;                                                       // M1 = 0.0 for coagulation by definition
        for (int ii = 1; ii < abscissas.size(); ii++)                                 // off-diagonal terms (looping half of them) with *2 incorporated
            for (int j = 0; j < ii; j++)
                coagulationSourceM.at(k) += coagulationModel->getCoagulationRate(state, abscissas.at(ii), abscissas.at(j)) * weights.at(ii) * weights.at(j) * (k == 0 ? -1.0 : (pow(abscissas.at(ii) + abscissas.at(j), k)) - pow(abscissas.at(ii), k) - pow(abscissas.at(j), k));
        for (int ii = 0; ii < abscissas.size(); ii++)                                      // diagonal terms
            coagulationSourceM.at(k) += coagulationModel->getCoagulationRate(state, abscissas.at(ii), abscissas.at(ii)) * weights.at(ii) * weights.at(ii) * (k == 0 ? -0.5 : pow(abscissas.at(ii), k) * (pow(2, k - 1) - 1));
    }

    //---------- combinine to make source terms

    vector<double> sootSourceTerms(nMom, 0.0);

    for (int k = 0; k < nMom; k++)
        sootSourceTerms.at(k) = (nucleationSourceM.at(k) + condensationSourceM.at(k) + growthSourceM.at(k) + oxidationSourceM.at(k) + coagulationSourceM.at(k)) / state.getRhoGas();

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
