#include <catch2/catch.hpp>

#include "sootModel.h"
#include "constants.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("psdModel object initialization", "[psdModel]") {

    SECTION("PSD models with NONE soot chemistry") {

        nucleationMech  n = nucleationMech::NONE;
        growthMech      g = growthMech::NONE;
        oxidationMech   x = oxidationMech::NONE;
        coagulationMech c = coagulationMech::NONE;

        SECTION("MONO") {

            sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::MONO);
            REQUIRE(SM.psd->nMom == 2);
            REQUIRE(SM.nucleationMechanism == nucleationMech::NONE);
            REQUIRE(SM.growthMechanism == growthMech::NONE);
            REQUIRE(SM.oxidationMechanism == oxidationMech::NONE);
            REQUIRE(SM.coagulationMechanism == coagulationMech::NONE);
        }

        SECTION("LOGN") {

            sootModel SM = sootModel(psdMech::LOGN, 3, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::LOGN);
            REQUIRE(SM.psd->nMom == 3);
            REQUIRE(SM.nucleationMechanism == nucleationMech::NONE);
            REQUIRE(SM.growthMechanism == growthMech::NONE);
            REQUIRE(SM.oxidationMechanism == oxidationMech::NONE);
            REQUIRE(SM.coagulationMechanism == coagulationMech::NONE);
        }

        SECTION("QMOM (4 moments)") {

            sootModel SM = sootModel(psdMech::QMOM, 4, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::QMOM);
            REQUIRE(SM.psd->nMom == 4);
            REQUIRE(SM.nucleationMechanism == nucleationMech::NONE);
            REQUIRE(SM.growthMechanism == growthMech::NONE);
            REQUIRE(SM.oxidationMechanism == oxidationMech::NONE);
            REQUIRE(SM.coagulationMechanism == coagulationMech::NONE);
        }

        SECTION("MOMIC (5 moments)") {

            sootModel SM = sootModel(psdMech::MOMIC, 5, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::MOMIC);
            REQUIRE(SM.psd->nMom == 5);
            REQUIRE(SM.nucleationMechanism == nucleationMech::NONE);
            REQUIRE(SM.growthMechanism == growthMech::NONE);
            REQUIRE(SM.oxidationMechanism == oxidationMech::NONE);
            REQUIRE(SM.coagulationMechanism == coagulationMech::NONE);
        }

    }

}

////////////////////////////////////////////////////////////////////////////////
