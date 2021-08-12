#include <catch2/catch.hpp>

#include "sootModel.h"
#include "constants.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("nucleation model initialization", "[nucleation][init]") {

    nucleationMech NONE = nucleationMech::NONE;
    nucleationMech LL = nucleationMech::LL;
    nucleationMech LIN = nucleationMech::LIN;
    nucleationMech PAH = nucleationMech::PAH;

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

