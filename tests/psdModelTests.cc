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

    SECTION("PSD models with LL soot chemistry") {

        nucleationMech  n = nucleationMech::LL;
        growthMech      g = growthMech::LL;
        oxidationMech   x = oxidationMech::LL;
        coagulationMech c = coagulationMech::LL;

        SECTION("MONO") {

            sootModel SM = sootModel(psdMech::MONO, 2, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::MONO);
            REQUIRE(SM.psd->nMom == 2);
            REQUIRE(SM.nucleationMechanism == nucleationMech::LL);
            REQUIRE(SM.growthMechanism == growthMech::LL);
            REQUIRE(SM.oxidationMechanism == oxidationMech::LL);
            REQUIRE(SM.coagulationMechanism == coagulationMech::LL);
        }

        SECTION("LOGN") {

            sootModel SM = sootModel(psdMech::LOGN, 3, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::LOGN);
            REQUIRE(SM.psd->nMom == 3);
            REQUIRE(SM.nucleationMechanism == nucleationMech::LL);
            REQUIRE(SM.growthMechanism == growthMech::LL);
            REQUIRE(SM.oxidationMechanism == oxidationMech::LL);
            REQUIRE(SM.coagulationMechanism == coagulationMech::LL);
        }

        SECTION("QMOM (4 moments)") {

            sootModel SM = sootModel(psdMech::QMOM, 4, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::QMOM);
            REQUIRE(SM.psd->nMom == 4);
            REQUIRE(SM.nucleationMechanism == nucleationMech::LL);
            REQUIRE(SM.growthMechanism == growthMech::LL);
            REQUIRE(SM.oxidationMechanism == oxidationMech::LL);
            REQUIRE(SM.coagulationMechanism == coagulationMech::LL);
        }

        SECTION("MOMIC (5 moments)") {

            sootModel SM = sootModel(psdMech::MOMIC, 5, n, g, x, c);

            REQUIRE(SM.psdMechanism == psdMech::MOMIC);
            REQUIRE(SM.psd->nMom == 5);
            REQUIRE(SM.nucleationMechanism == nucleationMech::LL);
            REQUIRE(SM.growthMechanism == growthMech::LL);
            REQUIRE(SM.oxidationMechanism == oxidationMech::LL);
            REQUIRE(SM.coagulationMechanism == coagulationMech::LL);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("getSourceTermsImplementation function call", "[getSourceTerms][psdModel]") {



    vector<double> yGas = {0, 0.1, 0.1, 0.01, 0.02, 0.03, 0.04, 2E-15};        // [H, H2, O, O2, OH, H2O, CO, C2H2]
    vector<double> yPAH = {0, 0, 0, 0, 0, 0};                 // [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
//    vector<double> ySootVar{0.003, 1.5E-5};

    SECTION("MONO psdModel getSourceTermsImplementation", "[MONO][psdModel][getSourceTerms]") {

        SECTION("M0 = M1 = 0.0") {

            state S = state();
            S.setState(2100, 101325, 0.1, 1E-5, 29, yGas, yPAH, {0,0});

            sootModel SM = sootModel(psdMech::MONO, 2, nucleationMech::LL, growthMech::LL, oxidationMech::LL, coagulationMech::LL);

            sourceTermStruct sourceTerms;
            SM.psd->getSourceTermsImplementation(S, &sourceTerms);

//            REQUIRE(sourceTerms.sootSourceTerms.at(0) == 0);
//            REQUIRE(sourceTerms.sootSourceTerms.at(1) == 0);

        }

    }
}

