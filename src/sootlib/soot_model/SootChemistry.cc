#include "SootChemistry.h"

using namespace soot;
using namespace std;

map<GasSpecies, double> SootChemistry::getGasSourceTerms(const State& state, MassRateRatios& ratio, double N, double G, double X, double C) {
    map<GasSpecies, double> gasSourceTerms;

    // Nucleation
    if (N != 0) {
        for (auto it = ratio.nucCond().gasSpeciesBegin(); it != ratio.nucCond().gasSpeciesEnd(); it++) {
            if (gasSourceTerms.count(it->first) == 0)
                gasSourceTerms[it->first] = 0;
            gasSourceTerms[it->first] += N * it->second / state.getRhoGas();
        }
    }

    // Growth
    if (G != 0) {
        for (auto it = ratio.groOxi().gasSpeciesBegin(); it != ratio.groOxi().gasSpeciesEnd(); it++) {
            if (gasSourceTerms.count(it->first) == 0)
                gasSourceTerms[it->first] = 0;
            gasSourceTerms[it->first] += G * it->second / state.getRhoGas();
        }
    }

    // Oxidation
    if (X != 0) {
        for (auto it = ratio.groOxi().gasSpeciesBegin(); it != ratio.groOxi().gasSpeciesEnd(); it++) {
            if (gasSourceTerms.count(it->first) == 0)
                gasSourceTerms[it->first] = 0;
            gasSourceTerms[it->first] += X * it->second / state.getRhoGas();
        }
    }

    // PAH condensation
    if (C != 0) {
        for (auto it = ratio.groOxi().gasSpeciesBegin(); it != ratio.groOxi().gasSpeciesEnd(); it++) {
            if (gasSourceTerms.count(it->first) == 0)
                gasSourceTerms[it->first] = 0;
            gasSourceTerms[it->first] += C * it->second / state.getRhoGas();
        }
    }

    return gasSourceTerms;
}
map<size_t, double> SootChemistry::getPAHSourceTerms(const State& state, MassRateRatios& ratio, double N, double G, double X, double C) {
    map<size_t, double> PAHSourceTerms;

    // Nucleation
    if (N != 0) {
        for (auto it = ratio.nucCond().PAHBegin(); it != ratio.nucCond().PAHEnd(); it++) {
            if (PAHSourceTerms.count(it->first) == 0)
                PAHSourceTerms[it->first] = 0;
            PAHSourceTerms[it->first] += N * it->second / state.getRhoGas();
        }
    }

    // Growth
    if (G != 0) {
        for (auto it = ratio.groOxi().PAHBegin(); it != ratio.groOxi().PAHEnd(); it++) {
            if (PAHSourceTerms.count(it->first) == 0)
                PAHSourceTerms[it->first] = 0;
            PAHSourceTerms[it->first] += G * it->second / state.getRhoGas();
        }
    }

    // Oxidation
    if (X != 0) {
        for (auto it = ratio.groOxi().PAHBegin(); it != ratio.groOxi().PAHEnd(); it++) {
            if (PAHSourceTerms.count(it->first) == 0)
                PAHSourceTerms[it->first] = 0;
            PAHSourceTerms[it->first] += X * it->second / state.getRhoGas();
        }
    }

    // PAH condensation
    if (C != 0) {
        for (auto it = ratio.groOxi().PAHBegin(); it != ratio.groOxi().PAHEnd(); it++) {
            if (PAHSourceTerms.count(it->first) == 0)
                PAHSourceTerms[it->first] = 0;
            PAHSourceTerms[it->first] += C * it->second / state.getRhoGas();
        }
    }

    return PAHSourceTerms;
}
