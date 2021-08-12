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

