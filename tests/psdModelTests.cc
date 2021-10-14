#include <catch2/catch.hpp>

#include "sootModel.h"
#include "constants.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE_SIG("psdModel object initialization", "[psdModel]", ((psdMech P, int N), P, N),
                       (psdMech::MONO,2), (psdMech::LOGN,3), (psdMech::QMOM,2), (psdMech::QMOM,4), (psdMech::QMOM,6),
                       (psdMech::MOMIC,2), (psdMech::MOMIC,3), (psdMech::MOMIC,4), (psdMech::MOMIC,5), (psdMech::MOMIC,6)) {

    SECTION("Soot chemistry combinations","[psdModel][sootChemistry]") {

        SECTION("With NONE soot chemistry") {

            nucleationMech  n = nucleationMech::NONE;
            growthMech      g = growthMech::NONE;
            oxidationMech   x = oxidationMech::NONE;
            coagulationMech c = coagulationMech::NONE;

            sootModel SM = sootModel(P, N, n, g, x, c);

            REQUIRE(SM.nucleationMechanism == n);
            REQUIRE(SM.growthMechanism == g);
            REQUIRE(SM.oxidationMechanism == x);
            REQUIRE(SM.coagulationMechanism == c);
        }

        SECTION("With LL soot chemistry") {

            nucleationMech  n = nucleationMech::LL;
            growthMech      g = growthMech::LL;
            oxidationMech   x = oxidationMech::LL;
            coagulationMech c = coagulationMech::LL;

            sootModel SM = sootModel(P, N, n, g, x, c);

            REQUIRE(SM.nucleationMechanism == n);
            REQUIRE(SM.growthMechanism == g);
            REQUIRE(SM.oxidationMechanism == x);
            REQUIRE(SM.coagulationMechanism == c);
        }

        SECTION("With LIN/LIN/LEE_NEOH/FUCHS soot chemistry") {

            nucleationMech  n = nucleationMech::LIN;
            growthMech      g = growthMech::LIN;
            oxidationMech   x = oxidationMech::LEE_NEOH;
            coagulationMech c = coagulationMech::FUCHS;

            sootModel SM = sootModel(P, N, n, g, x, c);

            REQUIRE(SM.nucleationMechanism == n);
            REQUIRE(SM.growthMechanism == g);
            REQUIRE(SM.oxidationMechanism == x);
            REQUIRE(SM.coagulationMechanism == c);
        }

        SECTION("With PAH/HACA/HACA/FRENK soot chemistry") {

            nucleationMech  n = nucleationMech::PAH;
            growthMech      g = growthMech::HACA;
            oxidationMech   x = oxidationMech::HACA;
            coagulationMech c = coagulationMech::FRENK;

            sootModel SM = sootModel(P, N, n, g, x, c);

            REQUIRE(SM.nucleationMechanism == n);
            REQUIRE(SM.growthMechanism == g);
            REQUIRE(SM.oxidationMechanism == x);
            REQUIRE(SM.coagulationMechanism == c);
        }

        SECTION("With LL/HACA/NSC_NEOH/FUCHS soot chemistry") {

            nucleationMech  n = nucleationMech::LL;
            growthMech      g = growthMech::HACA;
            oxidationMech   x = oxidationMech::NSC_NEOH;
            coagulationMech c = coagulationMech::FUCHS;

            sootModel SM = sootModel(P, N, n, g, x, c);

            REQUIRE(SM.nucleationMechanism == n);
            REQUIRE(SM.growthMechanism == g);
            REQUIRE(SM.oxidationMechanism == x);
            REQUIRE(SM.coagulationMechanism == c);
        }
    }

    SECTION("sourceTerms structure initialization") {

        // NOTE: source terms variable is owned by sootModel but initialized by psdModel

        nucleationMech  n = nucleationMech::LL;
        growthMech      g = growthMech::LL;
        oxidationMech   x = oxidationMech::LL;
        coagulationMech c = coagulationMech::LL;

        sootModel SM = sootModel(P, N, n, g, x, c);

        // soot source terms
        for (int i=0; i<N; i++)
            REQUIRE(SM.sourceTerms->sootSourceTerms.at(i) == 0);

        // gas source terms
        for (auto const& x : SM.sourceTerms->gasSourceTerms) {
            gasSp sp = x.first;
            REQUIRE(SM.sourceTerms->gasSourceTerms.at(sp) == 0);
        }

        // PAH source terms
        for (auto const& x : SM.sourceTerms->pahSourceTerms) {
            pahSp sp = x.first;
            REQUIRE(SM.sourceTerms->pahSourceTerms.at(sp) == 0);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE_SIG("getSourceTermImplementation function call", "[psdModel][getSourceTerms]", ((psdMech P, int N), P, N),
                       (psdMech::MONO,2), (psdMech::LOGN,3), (psdMech::QMOM,2), (psdMech::QMOM,4), (psdMech::QMOM,6),
                       (psdMech::MOMIC,2), (psdMech::MOMIC,3), (psdMech::MOMIC,4), (psdMech::MOMIC,5), (psdMech::MOMIC,6)) {

//TEST_CASE("getSourceTermImplementation function call", "[psdModel][getSourceTerms]") {
//
//    psdMech P = psdMech::MOMIC;
//    int N = 6;

    SECTION("with NONE soot chemistry") {

        nucleationMech  n = nucleationMech::NONE;
        growthMech      g = growthMech::NONE;
        oxidationMech   x = oxidationMech::NONE;
        coagulationMech c = coagulationMech::NONE;

        vector<double> yGas = {0, 0.1, 0.1, 0.01, 0.02, 0.03, 0.04, 2E-15};     // [H, H2, O, O2, OH, H2O, CO, C2H2]
        vector<double> yPAH = {0, 0, 0, 0, 0, 0};                               // [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
        vector<double> ySootVar = {0.003, 1.5E-5, 1E-7, 1E-10, 1E-11, 1E-12};

        state S = state();
        S.setState(2100, 101325, 0.1, 1E-5, 29, yGas, yPAH, ySootVar);

        sootModel SM = sootModel(P, N, n, g, x, c);

        SM.psd->getSourceTermsImplementation(S, SM.sourceTerms);

        REQUIRE(SM.sourceTerms->sootSourceTerms.at(0) == Approx(0).margin(1E-10));      // -0.0 == 0.0 fails comparison; Approx(0).margin passes it since difference doesn't matter for this case
        REQUIRE(SM.sourceTerms->sootSourceTerms.at(1) == Approx(0).margin(1E-10));

        for (auto const& x : SM.sourceTerms->gasSourceTerms) {
            gasSp sp = x.first;
            if (sp != gasSp::C)
                REQUIRE(SM.sourceTerms->gasSourceTerms.at(sp) == 0);
        }

        for (auto const& x : SM.sourceTerms->pahSourceTerms) {
            pahSp sp = x.first;
            REQUIRE(SM.sourceTerms->pahSourceTerms.at(sp) == 0);
        }
    }

    SECTION("with LL soot chemistry") {

        nucleationMech  n = nucleationMech::LL;
        growthMech      g = growthMech::LL;
        oxidationMech   x = oxidationMech::LL;
        coagulationMech c = coagulationMech::LL;

        vector<double> yGas = {0, 0.01, 0.01, 0.01, 0.02, 0.03, 0.04, 2E-15};     // [H, H2, O, O2, OH, H2O, CO, C2H2]
        vector<double> yPAH = {0, 0, 0, 0, 0, 0};                                 // [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
        vector<double> ySootVar = {0.003, 1.5E-5, 1E-7, 1E-10, 1E-11, 1E-12};

        sootModel SM = sootModel(P, N, n, g, x, c);

        state S = state();
        S.setState(2100, 101325, 0.1, 1E-5, 29, yGas, yPAH, ySootVar);

        SM.psd->getSourceTermsImplementation(S, SM.sourceTerms);

        REQUIRE(SM.sourceTerms->sootSourceTerms.at(0)/1E8 < 10.0);      // ORDER(1E8)
        REQUIRE(SM.sourceTerms->sootSourceTerms.at(0)/1E8 > 1.0);

        // species not affected by LL chemistry stay exactly zero; others are just very small
        REQUIRE(SM.sourceTerms->gasSourceTerms.at(gasSp::C2H2) == Approx(0).margin(1E-10));
        REQUIRE(SM.sourceTerms->gasSourceTerms.at(gasSp::O) == 0);
        REQUIRE(SM.sourceTerms->gasSourceTerms.at(gasSp::O2) == Approx(0).margin(1E-10));
        REQUIRE(SM.sourceTerms->gasSourceTerms.at(gasSp::H) == 0);
        REQUIRE(SM.sourceTerms->gasSourceTerms.at(gasSp::H2) == Approx(0).margin(1E-10));
        REQUIRE(SM.sourceTerms->gasSourceTerms.at(gasSp::OH) == 0);
        REQUIRE(SM.sourceTerms->gasSourceTerms.at(gasSp::H2O) == 0);
        REQUIRE(SM.sourceTerms->gasSourceTerms.at(gasSp::CO) == Approx(0).margin(1E-10));
        REQUIRE(SM.sourceTerms->gasSourceTerms.at(gasSp::C) == Approx(0).margin(1E-10));
        REQUIRE(SM.sourceTerms->gasSourceTerms.at(gasSp::C6H6) == 0);

        for (auto const& x : SM.sourceTerms->pahSourceTerms) {
            pahSp sp = x.first;
            REQUIRE(SM.sourceTerms->pahSourceTerms.at(sp) == 0);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////