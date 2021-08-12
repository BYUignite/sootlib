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

