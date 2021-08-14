#include <catch2/catch.hpp>

#include "sootModel.h"
#include "constants.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("growth model initialization", "[growth][init]") {

    growthMech NONE = growthMech::NONE;
    growthMech LL   = growthMech::LL;
    growthMech LIN  = growthMech::LIN;
    growthMech HACA = growthMech::HACA;

    nucleationMech  n = nucleationMech::NONE;
    oxidationMech   x = oxidationMech::NONE;
    coagulationMech c = coagulationMech::NONE;

    SECTION("NONE growth") {
        sootModel SM = sootModel(psdMech::MONO, 2, n, NONE, x, c);
        REQUIRE(SM.growthMechanism == growthMech::NONE);
    }

    SECTION("LL growth") {
        sootModel SM = sootModel(psdMech::MONO, 2, n, LL, x, c);
        REQUIRE(SM.growthMechanism == growthMech::LL);
        REQUIRE(SM.psd->grw->growthRxnRatios.at(gasSp::C2H2) == -1);
        REQUIRE(SM.psd->grw->growthRxnRatios.at(gasSp::H2) == 1);
        REQUIRE(SM.psd->grw->growthRxnRatios.at(gasSp::C) == 2);
    }

    SECTION("LIN growth") {
        sootModel SM = sootModel(psdMech::MONO, 2, n, LIN, x, c);
        REQUIRE(SM.growthMechanism == growthMech::LIN);
        REQUIRE(SM.psd->grw->growthRxnRatios.at(gasSp::C2H2) == -1);
        REQUIRE(SM.psd->grw->growthRxnRatios.at(gasSp::H2) == 1);
        REQUIRE(SM.psd->grw->growthRxnRatios.at(gasSp::C) == 2);
    }

    SECTION("HACA growth") {
        sootModel SM = sootModel(psdMech::MONO, 2, n, HACA, x, c);
        REQUIRE(SM.growthMechanism == growthMech::HACA);
        REQUIRE(SM.psd->grw->growthRxnRatios.at(gasSp::O2) == -1);
        REQUIRE(SM.psd->grw->growthRxnRatios.at(gasSp::OH) == -1);
        REQUIRE(SM.psd->grw->growthRxnRatios.at(gasSp::CO) == 3);
        REQUIRE(SM.psd->grw->growthRxnRatios.at(gasSp::C)  == 2);
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("getGrowthSootRate function call", "[groth][getSootRate]") {

    // NOTE: using 'bad' (unphysical) values should throw errors in the setState function;
    // those tests are covered in stateTests.cc

    growthMech NONE = growthMech::NONE;
    growthMech LL   = growthMech::LL;
    growthMech LIN  = growthMech::LIN;
    growthMech HACA = growthMech::HACA;

    nucleationMech  n    = nucleationMech::NONE;
    oxidationMech   x    = oxidationMech::NONE;
    coagulationMech c    = coagulationMech::NONE;

    vector<double> yGas = {0, 0.1, 0.1, 0.01, 0.02, 0.03, 0.04, 2E-5};        // [H, H2, O, O2, OH, H2O, CO, C2H2]
    vector<double> yPAH = {0, 0.001, 0.001, 0.001, 0.0002, 0};                 // [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
    vector<double> ySootVar{1E14, 1E-12};

    state S = state();
    S.setState(2100, 101325, 0.1, 1E-5, 29, yGas, yPAH, ySootVar);

    SECTION("NONE growth model", "[NONE][growth][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, n, NONE, x, c);
        double grwSootRate = SM.psd->grw->getGrowthSootRate(S);
        REQUIRE(grwSootRate == 0);
    }

    SECTION("LL growth model", "[LL][growth][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, n, LL, x, c);
        double grwSootRate = SM.psd->grw->getGrowthSootRate(S);

        // requires that the result is on the order of 1E-3
        REQUIRE(grwSootRate/1E-3 < 10.0);
        REQUIRE(grwSootRate/1E-3 > 1.0);
    }

    SECTION("LIN growth model", "[LIN][growth][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, n, LIN, x, c);
        double grwSootRate = SM.psd->grw->getGrowthSootRate(S);

        // requires that the result is on the order of 1E-7
        REQUIRE(grwSootRate/1E-7 < 10.0);
        REQUIRE(grwSootRate/1E-7 > 1.0);
    }

    SECTION("HACA growth model", "[HACA][growth][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, n, HACA, x, c);
        double grwSootRate = SM.psd->grw->getGrowthSootRate(S);

        // requires that the result is on the order of 1E-2
        REQUIRE(grwSootRate/1E-2 < 10.0);
        REQUIRE(grwSootRate/1E-2 > 1.0);
    }

}

