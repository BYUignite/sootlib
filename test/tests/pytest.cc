#include <chrono>

#include "TestTools.h"

#include "sootlib/soot_model/generator/SootModelGenerator.h"

using namespace std;
using namespace soot;

string argvString(int& counter, char** argv) {
    string ret = argv[counter];
    counter++;
    return ret;
}

int argvInt(int& counter, char** argv) {
    int ret = stoi(argv[counter]);
    counter++;
    return ret;
}

double argvDouble(int& counter, char** argv) {
    double ret = stod(argv[counter]);
    counter++;
    return ret;
}

double interp(double start, double stop, int n, int step) {
    return (stop - start) * step / n + start;
}

int main(int argc, char** argv) {
    int counter = 0;
    const string exe = argvString(counter, argv);

    // general parts of config
    const string output = argvString(counter, argv);
    const string PSDModel = argvString(counter, argv);
    const string coagulationMethod = argvString(counter, argv);
    const string growthMethod = argvString(counter, argv);
    const string nucleationMethod = argvString(counter, argv);
    const string oxidationMethod = argvString(counter, argv);
    const int steps = argvInt(counter, argv);

    // sectional state
    const int numSections = 10;
    int numSectionsFound = 0;
    double initialSections[numSections];
    double finalSections[numSections];
    for (int i = 0; i < numSections; i++) {
        initialSections[i] = argvDouble(counter, argv);
        finalSections[i] = argvDouble(counter, argv);
        if (initialSections[i] != 0 || finalSections[i] != 0) {
            numSectionsFound++;
        }
    }
    
    // moment state
    const int numMoments = 10;
    int numMomentsFound = 0;
    double initialMoments[numMoments];
    double finalMoments[numMoments];
    for (int i = 0; i < numMoments; i++) {
        initialMoments[i] = argvDouble(counter, argv);
        finalMoments[i] = argvDouble(counter, argv);
        if (initialMoments[i] != 0 || finalMoments[i] != 0) {
            numMomentsFound++;
        }
    }
    
    // gas state
    const double tempIni = argvDouble(counter, argv);
    const double tempFin = argvDouble(counter, argv);
    const double presIni = argvDouble(counter, argv);
    const double presFin = argvDouble(counter, argv);
    const double rhoGasIni = argvDouble(counter, argv);
    const double rhoGasFin = argvDouble(counter, argv);
    const double MWGasIni = argvDouble(counter, argv);
    const double MWGasFin = argvDouble(counter, argv);
    const double muGasIni = argvDouble(counter, argv);
    const double muGasFin = argvDouble(counter, argv);

    const double C_C2H2Ini = argvDouble(counter, argv);
    const double C_C2H2Fin = argvDouble(counter, argv);

    const double C_O2Ini = argvDouble(counter, argv);
    const double C_O2Fin = argvDouble(counter, argv);

    const double C_HIni = argvDouble(counter, argv);
    const double C_HFin = argvDouble(counter, argv);

    const double C_H2Ini = argvDouble(counter, argv);
    const double C_H2Fin = argvDouble(counter, argv);

    const double C_OHIni = argvDouble(counter, argv);
    const double C_OHFin = argvDouble(counter, argv);

    const double C_H2OIni = argvDouble(counter, argv);
    const double C_H2OFin = argvDouble(counter, argv);

    const double C_COIni = argvDouble(counter, argv);
    const double C_COFin = argvDouble(counter, argv);

    const double C_CIni = argvDouble(counter, argv);
    const double C_CFin = argvDouble(counter, argv);

    const int numPAHFractions = 34;
    double PAHFractionsIni[numPAHFractions];
    double PAHFractionsFin[numPAHFractions];
    for (int i = 0 ; i < numPAHFractions; i++) {
        PAHFractionsIni[i] = argvDouble(counter, argv);
        PAHFractionsFin[i] = argvDouble(counter, argv);
    }

    const double CMinIni = argvDouble(counter, argv);
    const double CMinFin = argvDouble(counter, argv);

    cout << "Got " << counter << " parameters" << endl;

    // make soot model
    auto sootModelGenerator = SootModelGenerator();
    if (PSDModel == "logn") {
        sootModelGenerator.setPSDModel(PSDMechanism::LOGN);
    }
    else if (PSDModel == "momic") {
        sootModelGenerator.setPSDModel(PSDMechanism::MOMIC);
    }
    else if (PSDModel == "mono") {
        sootModelGenerator.setPSDModel(PSDMechanism::MONO);
    }
    else if (PSDModel == "qmom") {
        sootModelGenerator.setPSDModel(PSDMechanism::QMOM);
    }
    else if (PSDModel == "sect") {
        sootModelGenerator.setPSDModel(PSDMechanism::SECT);
    }

    if (coagulationMethod == "frenk") {
        sootModelGenerator.setCoagulationMechanism(CoagulationMechanism::FRENK);
    }
    else if (coagulationMethod == "fuchs") {
        sootModelGenerator.setCoagulationMechanism(CoagulationMechanism::FUCHS);
    }
    else if (coagulationMethod == "ll") {
        sootModelGenerator.setCoagulationMechanism(CoagulationMechanism::LL);
    }
    else if (coagulationMethod == "none") {
        sootModelGenerator.setCoagulationMechanism(CoagulationMechanism::NONE);
    }

    if (growthMethod == "haca") {
        sootModelGenerator.setGrowthMechanism(GrowthMechanism::HACA);
    }
    else if (growthMethod == "lin") {
        sootModelGenerator.setGrowthMechanism(GrowthMechanism::LIN);
    }
    else if (growthMethod == "ll") {
        sootModelGenerator.setGrowthMechanism(GrowthMechanism::LL);
    }
    else if (growthMethod == "none") {
        sootModelGenerator.setGrowthMechanism(GrowthMechanism::NONE);
    }

    if (nucleationMethod == "lin") {
        sootModelGenerator.setNucleationMechanism(NucleationMechanism::LIN);
    }
    else if (nucleationMethod == "ll") {
        sootModelGenerator.setNucleationMechanism(NucleationMechanism::LL);
    }
    else if (nucleationMethod == "pah") {
        sootModelGenerator.setNucleationMechanism(NucleationMechanism::PAH);
    }
    else if (nucleationMethod == "none") {
        sootModelGenerator.setNucleationMechanism(NucleationMechanism::NONE);
    }

    if (oxidationMethod == "haca") {
        sootModelGenerator.setOxidationMechanism(OxidationMechanism::HACA);
    }
    else if (oxidationMethod == "lee_neoh") {
        sootModelGenerator.setOxidationMechanism(OxidationMechanism::LEE_NEOH);
    }
    else if (oxidationMethod == "ll") {
        sootModelGenerator.setOxidationMechanism(OxidationMechanism::LL);
    }
    else if (oxidationMethod == "nsc_neoh") {
        sootModelGenerator.setOxidationMechanism(OxidationMechanism::NSC_NEOH);
    }
    else if (oxidationMethod == "none") {
        sootModelGenerator.setOxidationMechanism(OxidationMechanism::NONE);
    }

    // make vars
    auto sootModel = sootModelGenerator.getModelUnique();
    State state;
    SourceTerms sourceTerms;
    const int numSootSourceTerms = 10;

    // open out file
    ofstream out;
    out.open(output + "/data.csv");

    // state headers
    for (int i = 0; i < numSections; i++) {
        out << "section_" << i << ", ";
    }
    for (int i = 0; i < numMoments; i++) {
        out << "moment_" << i << ", ";
    }
    out << "T, P, RhoGas, MWGas, MuGas, C_C2H2, C_O2, C_H, C_H2, C_OH, C_H2O, C_CO, C_C, ";
    for (int i = 0; i < numPAHFractions; i++) {
        out << "PAH_frac_" << (i + 1) * 6 << ", ";
    }
    out << "CMin, ";

    // source term headers
    for (int i = 0; i < numSootSourceTerms; i++) {
        out << "soot_source_" << i << ", ";
    }
    for (int i = 0; i < numPAHFractions; i++) {
        out << "PAH_source_" << (i + 1) * 6 << ", ";
    }
    out << "C2H2_source, O2_source, H_source, H2_source, OH_source, H2O_source, CO_source, C_source, time" << endl;

    // do calculations
    auto jobStart = chrono::steady_clock::now();
    chrono::time_point<chrono::steady_clock> startTime;
    chrono::time_point<chrono::steady_clock> endTime;
    for (int i = 0; i < steps; i++) {
        cout << "\rRunning step " << i + 1 << "/" << steps << "         ";
        // reset state
        state.resetSections(numSectionsFound);
        for (int j = 0; j < numSectionsFound; j++) {
            state.setSection(j, interp(initialSections[j], finalSections[j], steps, i));
        }

        state.resetMoments(numMomentsFound);
        for (int j = 0; j < numMomentsFound; j++) {
            state.setMoment(j, interp(initialMoments[j], initialMoments[j], steps, i));
        }

        state.setT(interp(tempIni, tempFin, steps, i));
        state.setP(interp(presIni, presFin, steps, i));
        state.setRhoGas(interp(rhoGasIni, rhoGasFin, steps, i));
        state.setMWGas(interp(MWGasIni, MWGasFin, steps, i));
        state.setMuGas(interp(muGasIni, muGasFin, steps, i));

        state.setGasSpeciesFrac(GasSpecies::C2H2, interp(C_C2H2Ini, C_C2H2Fin, steps, i));
        state.setGasSpeciesFrac(GasSpecies::O2, interp(C_O2Ini, C_O2Fin, steps, i));
        state.setGasSpeciesFrac(GasSpecies::H, interp(C_HIni, C_HFin, steps, i));
        state.setGasSpeciesFrac(GasSpecies::H2, interp(C_H2Ini, C_H2Fin, steps, i));
        state.setGasSpeciesFrac(GasSpecies::OH, interp(C_OHIni, C_OHFin, steps, i));
        state.setGasSpeciesFrac(GasSpecies::H2O, interp(C_H2OIni, C_H2OFin, steps, i));
        state.setGasSpeciesFrac(GasSpecies::CO, interp(C_COIni, C_COFin, steps, i));
        state.setGasSpeciesFrac(GasSpecies::C, interp(C_CIni, C_CFin, steps, i));

        for (int j = 0; j < numPAHFractions; j++) {
            state.setPAHFrac((j + 1) * 6, interp(PAHFractionsIni[j], PAHFractionsFin[j], steps, i));
        }

        state.setCMin(interp(CMinIni, CMinFin, steps, i));

        // print state to file
        for (int j = 0; j < numSectionsFound; j++) {
            out << state.getSection(j) << ", ";
        }
        for (int j = 0; j < numSections - numSectionsFound; j++) {
            out << 0 << ", ";
        }
        for (int j = 0; j < numMomentsFound; j++) {
            out << state.getMoment(j) << ", ";
        }
        for (int j = 0; j < numMoments - numMomentsFound; j++) {
            out << 0 << ", ";
        }
        out << state.getT() << ", " << state.getP() << ", " << state.getRhoGas() << ", " << state.getMWGas() << ", " << state.getMuGas() << ", ";
        out << state.getGasSpeciesC(GasSpecies::C2H2) << ", ";
        out << state.getGasSpeciesC(GasSpecies::O2) << ", ";
        out << state.getGasSpeciesC(GasSpecies::H) << ", ";
        out << state.getGasSpeciesC(GasSpecies::H2) << ", ";
        out << state.getGasSpeciesC(GasSpecies::OH) << ", ";
        out << state.getGasSpeciesC(GasSpecies::H2O) << ", ";
        out << state.getGasSpeciesC(GasSpecies::CO) << ", ";
        out << state.getGasSpeciesC(GasSpecies::C) << ", ";
        for (int j = 0; j < numPAHFractions; j++) {
            out << state.getPAHFrac((j + 1) * 6) << ", ";
        }
        out << state.getCMin() << ", ";

        // get new source terms
        startTime = chrono::steady_clock::now();
        sourceTerms = sootModel->getSourceTerms(state);
        endTime = chrono::steady_clock::now();

        // print new source terms to file
        for (int j = 0; j < sourceTerms.getNumSootSourceTerms() && j < numSootSourceTerms; j++) {
            out << sourceTerms.getSootSourceTerm(j) << ", ";
        }
        for (int j = 0; j < numSootSourceTerms - sourceTerms.getNumSootSourceTerms(); j++) {
            out << 0 << ", ";
        }
        for (int j = 0; j < numPAHFractions; j++) {
            out << sourceTerms.getPAHSourceTerm((j + 1) * 6) << ", ";
        }
        out << sourceTerms.getGasSourceTerm(GasSpecies::C2H2) << ", ";
        out << sourceTerms.getGasSourceTerm(GasSpecies::O2) << ", ";
        out << sourceTerms.getGasSourceTerm(GasSpecies::H) << ", ";
        out << sourceTerms.getGasSourceTerm(GasSpecies::H2) << ", ";
        out << sourceTerms.getGasSourceTerm(GasSpecies::OH) << ", ";
        out << sourceTerms.getGasSourceTerm(GasSpecies::H2O) << ", ";
        out << sourceTerms.getGasSourceTerm(GasSpecies::CO) << ", ";
        out << sourceTerms.getGasSourceTerm(GasSpecies::C) << ", ";
        out << (float) chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count() / 1e9 << endl;
    }

    // print time elapsed
    const size_t elapsed = chrono::duration_cast<chrono::seconds>(jobStart - chrono::steady_clock::now()).count();
    cout << endl << "Finished in " << elapsed << "s" << endl;

    // close out file
    out.close();

    return 0;
}
