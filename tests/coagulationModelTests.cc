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

