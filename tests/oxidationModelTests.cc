#include <catch2/catch.hpp>

#include "sootModel.h"
#include "constants.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("oxidation model initialization", "[oxidation][init]") {

    oxidationMech NONE = oxidationMech::NONE;
    oxidationMech LL   = oxidationMech::LL;
    oxidationMech HACA = oxidationMech::HACA;
    oxidationMech LEE  = oxidationMech::LEE_NEOH;
    oxidationMech NSC  = oxidationMech::NSC_NEOH;

    nucleationMech  n = nucleationMech::NONE;
    growthMech      g = growthMech::NONE;
    coagulationMech c = coagulationMech::NONE;

    SECTION("NONE oxidation") {
        sootModel SM = sootModel(psdMech::MONO, 2, n, g, NONE, c);
        REQUIRE(SM.oxidationMechanism == oxidationMech::NONE);
    }

    SECTION("LL oxidation") {
        sootModel SM = sootModel(psdMech::MONO, 2, n, g, LL, c);
        REQUIRE(SM.oxidationMechanism == oxidationMech::LL);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::CO) == 1);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::O2) == -0.5);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::C) == -1);
    }

    SECTION("HACA oxidation") {
        sootModel SM = sootModel(psdMech::MONO, 2, n, g, HACA, c);
        REQUIRE(SM.oxidationMechanism == oxidationMech::HACA);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::C2H2) == -1);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::OH) == -1);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::CO) == 1);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::C) == 1);
    }

    SECTION("LEE_NEOH oxidation") {
        sootModel SM = sootModel(psdMech::MONO, 2, n, g, LEE, c);
        REQUIRE(SM.oxidationMechanism == oxidationMech::LEE_NEOH);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::CO) == 2);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::H)  == 1);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::OH) == -1);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::O2) == -0.5);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::C) == -2);
    }

    SECTION("NSC_NEOH oxidation") {
        sootModel SM = sootModel(psdMech::MONO, 2, n, g, NSC, c);
        REQUIRE(SM.oxidationMechanism == oxidationMech::NSC_NEOH);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::CO) == 2);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::H)  == 1);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::OH) == -1);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::O2) == -0.5);
        REQUIRE(SM.psd->oxi->oxidationRxnRatios.at(gasSp::C) == -2);
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("getOxidationSootRate function call", "[groth][getSootRate]") {

    // NOTE: using 'bad' (unphysical) values should throw errors in the setState function;
    // those tests are covered in stateTests.cc

    oxidationMech NONE = oxidationMech::NONE;
    oxidationMech LL   = oxidationMech::LL;
    oxidationMech HACA = oxidationMech::HACA;
    oxidationMech LEE  = oxidationMech::LEE_NEOH;
    oxidationMech NSC  = oxidationMech::NSC_NEOH;

    nucleationMech  n = nucleationMech::NONE;
    growthMech      g = growthMech::NONE;
    coagulationMech c = coagulationMech::NONE;

    vector<double> yGas = {0, 0.1, 0.1, 0.01, 0.02, 0.03, 0.04, 2E-5};        // [H, H2, O, O2, OH, H2O, CO, C2H2]
    vector<double> yPAH = {0, 0.001, 0.001, 0.001, 0.0002, 0};                 // [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
    vector<double> ySootVar{1E14, 1E-12};

    state S = state();
    S.setState(2100, 101325, 0.1, 1E-5, 29, yGas, yPAH, ySootVar);

    SECTION("NONE oxidation model", "[NONE][oxidation][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, n, g, NONE, c);
        double oxiSootRate = SM.psd->oxi->getOxidationSootRate(S);
        REQUIRE(oxiSootRate == 0);
    }

    SECTION("LL oxidation model", "[LL][oxidation][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, n, g, LL, c);
        double oxiSootRate = SM.psd->oxi->getOxidationSootRate(S);

        // requires that the result is on the order of 1E-5
        REQUIRE(oxiSootRate/1E-5 < 10.0);
        REQUIRE(oxiSootRate/1E-5 > 1.0);
    }

    SECTION("HACA oxidation model", "[HACA][oxidation][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, n, g, HACA, c);
        double oxiSootRate = SM.psd->oxi->getOxidationSootRate(S);

        // requires that the result is on the order of 0.1
        REQUIRE(oxiSootRate/1E-1 < 10.0);
        REQUIRE(oxiSootRate/1E-1 > 1.0);
    }

    SECTION("LEE_NEOH oxidation model", "[LEE_NEOH][oxidation][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, n, g, LEE, c);
        double oxiSootRate = SM.psd->oxi->getOxidationSootRate(S);

        // requires that the result is on the order of 0.1
        REQUIRE(oxiSootRate/1E-1 < 10.0);
        REQUIRE(oxiSootRate/1E-1 > 1.0);
    }

    SECTION("NSC_NEOH oxidation model", "[NSC_NEOH][oxidation][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, n, g, NSC, c);
        double oxiSootRate = SM.psd->oxi->getOxidationSootRate(S);

        // requires that the result is on the order of 0.1
        REQUIRE(oxiSootRate/1E-1 < 10.0);
        REQUIRE(oxiSootRate/1E-1 > 1.0);
    }

}

