#include <catch2/catch.hpp>

#include "sootModel.h"
#include "constants.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

nucleationMech NONE = nucleationMech::NONE;
nucleationMech LL  = nucleationMech::LL;
nucleationMech LIN = nucleationMech::LIN;
nucleationMech PAH = nucleationMech::PAH;

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("nucleation model initialization", "[nucleation][init]") {

    growthMech      g = growthMech::NONE;
    oxidationMech   x = oxidationMech::NONE;
    coagulationMech c = coagulationMech::NONE;

    SECTION("NONE nucleation") {
        sootModel SM = sootModel(psdMech::MONO, 2, NONE, g, x, c);
        REQUIRE(SM.nucleationMechanism == nucleationMech::NONE);
        REQUIRE(SM.psd->nuc->nucleationRxnRatios.at(gasSp::C2H2) == 0);
    }

    SECTION("LL nucleation") {
        sootModel SM = sootModel(psdMech::MONO, 2, LL, g, x, c);
        REQUIRE(SM.nucleationMechanism == nucleationMech::LL);
        REQUIRE(SM.psd->nuc->nucleationRxnRatios.at(gasSp::C2H2) == -1);
        REQUIRE(SM.psd->nuc->nucleationRxnRatios.at(gasSp::H2) == 1);
        REQUIRE(SM.psd->nuc->nucleationRxnRatios.at(gasSp::C) == 2);
    }

    SECTION("LIN nucleation") {
        sootModel SM = sootModel(psdMech::MONO, 2, LIN, g, x, c);
        REQUIRE(SM.nucleationMechanism == nucleationMech::LIN);
        REQUIRE(SM.psd->nuc->nucleationRxnRatios.at(gasSp::C2H2) == -1);
        REQUIRE(SM.psd->nuc->nucleationRxnRatios.at(gasSp::H2) == 1);
        REQUIRE(SM.psd->nuc->nucleationRxnRatios.at(gasSp::C) == 2);
    }

    SECTION("PAH nucleation") {
        sootModel SM = sootModel(psdMech::MONO, 2, PAH, g, x, c);
        REQUIRE(SM.nucleationMechanism == nucleationMech::PAH);
        REQUIRE(SM.psd->nuc->nucleationRxnRatios.at(gasSp::C2H2) == 0);
        REQUIRE(SM.psd->nuc->DIMER.mDimer == 0);
        REQUIRE(SM.psd->nuc->DIMER.nDimer == 0);
        REQUIRE(SM.psd->nuc->DIMER.wDotD  == 0);
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("getNucleationSootRate function call", "[nucleation][getSootRate]") {

    // NOTE: using 'bad' (unphysical) values should throw errors in the setState function;
    // those tests are covered in stateTests.cc

    growthMech      g    = growthMech::NONE;
    oxidationMech   x    = oxidationMech::NONE;
    coagulationMech c    = coagulationMech::NONE;

    vector<double> yGas = {0, 0.1, 0.1, 0.01, 0.02, 0.03, 0.04, 2E-15};   // [H, H2, O, O2, OH, H2O, CO, C2H2]
    vector<double> yPAH = {0, 0.001, 0.001, 0.001, 0.0002, 0};                 // [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
    vector<double> ySootVar{0.003, 1.5E-5};

    state S = state();
    S.setState(2100, 101325, 0.1, 1E-5, 29, yGas, yPAH, ySootVar);

    SECTION("NONE nucleation model", "[NONE][nucleation][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, NONE, g, x, c);
        double nucSootRate = SM.psd->nuc->getNucleationSootRate(S);
        REQUIRE(nucSootRate == 0);
    }

    SECTION("LL nucleation model", "[LL][nucleation][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, LL, g, x, c);
        double nucSootRate = SM.psd->nuc->getNucleationSootRate(S);

        // requires that the result is on the order of 1E7
        REQUIRE(nucSootRate/1E7 < 10.0);
        REQUIRE(nucSootRate/1E7 > 1.0);
    }

    SECTION("LIN nucleation model", "[LIN][nucleation][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, LIN, g, x, c);
        double nucSootRate = SM.psd->nuc->getNucleationSootRate(S);

        // requires that the result is on the order of 1E7
        REQUIRE(nucSootRate/1E7 < 10.0);
        REQUIRE(nucSootRate/1E7 > 1.0);
    }

    SECTION("PAH nucleation model", "[PAH][nucleation][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, PAH, g, x, c);
        double nucSootRate = SM.psd->nuc->getNucleationSootRate(S);

        // requires that the result is on the order of 1E7
        REQUIRE(nucSootRate/1E7 < 10.0);
        REQUIRE(nucSootRate/1E7 > 1.0);
    }

}


////////////////////////////////////////////////////////////////////////////////





