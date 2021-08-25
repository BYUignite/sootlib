#include <catch2/catch.hpp>

#include "sootModel.h"
#include "constants.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("coagulation model initialization", "[coagulation][init]") {

    coagulationMech NONE = coagulationMech::NONE;
    coagulationMech LL   = coagulationMech::LL;
    coagulationMech FUCHS  = coagulationMech::FUCHS;
    coagulationMech FRENK  = coagulationMech::FRENK;

    nucleationMech  n = nucleationMech::NONE;
    growthMech      g = growthMech::NONE;
    oxidationMech   x = oxidationMech::NONE;

    SECTION("NONE coagulation") {
        sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, LL);
        REQUIRE(SM.coagulationMechanism == coagulationMech::LL);
    }

    SECTION("FUCHS coagulation") {
        sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, FUCHS);
        REQUIRE(SM.coagulationMechanism == coagulationMech::FUCHS);
    }

    SECTION("FRENK coagulation") {
        sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, FRENK);
        REQUIRE(SM.coagulationMechanism == coagulationMech::FRENK);
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("getCoagulationSootRate function call", "[coagulation][getSootRate]") {

    // NOTE: using 'bad' (unphysical) values should throw errors in the setState function;
    // those tests are covered in stateTests.cc

    coagulationMech NONE = coagulationMech::NONE;
    coagulationMech LL   = coagulationMech::LL;
    coagulationMech FUCHS  = coagulationMech::FUCHS;
    coagulationMech FRENK  = coagulationMech::FRENK;

    nucleationMech  n = nucleationMech::NONE;
    growthMech      g = growthMech::NONE;
    oxidationMech   x = oxidationMech::NONE;

    vector<double> yGas = {0, 0.1, 0.1, 0.01, 0.02, 0.03, 0.04, 2E-5};        // [H, H2, O, O2, OH, H2O, CO, C2H2]
    vector<double> yPAH = {0, 0.001, 0.001, 0.001, 0.0002, 0};                 // [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
    vector<double> ySootVar{1E14, 1E-12};

    double m1 = 1E-8;
    double m2 = 2E-6;

    state S = state();
    S.setState(2100, 101325, 0.1, 1E-5, 29, yGas, yPAH, ySootVar);

    SECTION("NONE coagulation model", "[NONE][coagulation][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, NONE);
        double coaSootRate = SM.psd->coa->getCoagulationSootRate(S, m1, m2);
        REQUIRE(coaSootRate == 0);
    }

    SECTION("LL coagulation model", "[LL][coagulation][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, LL);
        double coaSootRate = SM.psd->coa->getCoagulationSootRate(S, m1, m2);

        // requires that the result is on the order of 1E-12
        REQUIRE(coaSootRate/1E-12 < 10.0);
        REQUIRE(coaSootRate/1E-12 > 1.0);
    }

    SECTION("FUCHS coagulation model", "[FUCHS][coagulation][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, FUCHS);
        double coaSootRate = SM.psd->coa->getCoagulationSootRate(S, m1, m2);

        // requires that the result is on the order of 1E-14
        REQUIRE(coaSootRate/1E-14 < 10.0);
        REQUIRE(coaSootRate/1E-14 > 1.0);
    }

    SECTION("FRENK coagulation model", "[FRENK][coagulation][getSootRate]") {

        sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, FRENK);
        double coaSootRate = SM.psd->coa->getCoagulationSootRate(S, m1, m2);

        // requires that the result is on the order of 0.1
        REQUIRE(coaSootRate/1E-14 < 10.0);
        REQUIRE(coaSootRate/1E-14 > 1.0);
    }
}


