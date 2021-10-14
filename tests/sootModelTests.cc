#include <catch2/catch.hpp>

#include "sootModel.h"
#include "constants.h"

CATCH_REGISTER_ENUM( soot::psdMech, soot::psdMech::MONO, soot::psdMech::LOGN, soot::psdMech::QMOM, soot::psdMech::MOMIC, soot::psdMech::SECT )
CATCH_REGISTER_ENUM( soot::nucleationMech, soot::nucleationMech::NONE, soot::nucleationMech::LL, soot::nucleationMech::LIN, soot::nucleationMech::PAH )
CATCH_REGISTER_ENUM( soot::growthMech, soot::growthMech::NONE, soot::growthMech::LL, soot::growthMech::LIN, soot::growthMech::HACA)
CATCH_REGISTER_ENUM( soot::oxidationMech, soot::oxidationMech::NONE, soot::oxidationMech::LL, soot::oxidationMech::HACA, soot::oxidationMech::LEE_NEOH, soot::oxidationMech::NSC_NEOH)
CATCH_REGISTER_ENUM( soot::coagulationMech, soot::coagulationMech::NONE, soot::coagulationMech::LL, soot::coagulationMech::FUCHS, soot::coagulationMech::FRENK)

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE_SIG("sootModel object initialization", "[sootModel]", ((psdMech P, int N), P, N),
                       (psdMech::MONO,2), (psdMech::LOGN,3), (psdMech::QMOM,2), (psdMech::QMOM,4), (psdMech::QMOM,6),
                       (psdMech::MOMIC,2), (psdMech::MOMIC,3), (psdMech::MOMIC,4), (psdMech::MOMIC,5), (psdMech::MOMIC,6)) {

    nucleationMech  n = nucleationMech::NONE;
    growthMech      g = growthMech::NONE;
    oxidationMech   x = oxidationMech::NONE;
    coagulationMech c = coagulationMech::NONE;

    sootModel SM = sootModel(P, N, n, g, x, c);

    REQUIRE(SM.psdMechanism == P);
    REQUIRE(SM.psd->nMom == N);

 }

////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE_SIG("set/get/reset values of sourceTerms from sootModel object", "[sootModel][sourceTerms]", ((psdMech P, int N), P, N),
                       (psdMech::MONO,2), (psdMech::LOGN,3), (psdMech::QMOM,2), (psdMech::QMOM,4), (psdMech::QMOM,6),
                       (psdMech::MOMIC,2), (psdMech::MOMIC,3), (psdMech::MOMIC,4), (psdMech::MOMIC,5), (psdMech::MOMIC,6)) {

//TEST_CASE("getSourceTermImplementation function call", "[sootModel][sourceTerms]") {
//
//    psdMech P = psdMech::MOMIC;
//    int N = 6;

    nucleationMech  n = nucleationMech::NONE;
    growthMech      g = growthMech::NONE;
    oxidationMech   x = oxidationMech::NONE;
    coagulationMech c = coagulationMech::NONE;

    sootModel SM = sootModel(P, N, n, g, x, c);

    // set sootSourceTerms
    for(int i=0; i<SM.psd->nMom; i++)
        SM.sourceTerms->sootSourceTerms.at(i) = i+5;

    // set gasSourceTerms
    for (auto const& x : SM.sourceTerms->gasSourceTerms) {
        gasSp sp = x.first;
        int i=0;
        SM.sourceTerms->gasSourceTerms.at(sp) = i;
        i++;
    }

    // set pahSourceTerms
    for (auto const& x : SM.sourceTerms->pahSourceTerms) {
        pahSp sp = x.first;
        int i=10;
        SM.sourceTerms->pahSourceTerms.at(sp) = i;
        i++;
    }

    // check sootSourceTerms
    for(int i=0; i<SM.psd->nMom; i++)
        REQUIRE(SM.sourceTerms->sootSourceTerms.at(i) == i+5);

    // check gasSourceTerms
    for (auto const& x : SM.sourceTerms->gasSourceTerms) {
        gasSp sp = x.first;
        double i=0;
        double temp = SM.sourceTerms->gasSourceTerms.at(sp);
        REQUIRE(temp == i);
        i++;
    }

    // check pahSourceTerms
    for (auto const& x : SM.sourceTerms->pahSourceTerms) {
        pahSp sp = x.first;
        int i=10;
        REQUIRE(SM.sourceTerms->pahSourceTerms.at(sp) == i);
        i++;
    }

    // reset sourceTerms
    SM.resetSourceTerms();

    // check reset sootSourceTerms
    for(int i=0; i<SM.psd->nMom; i++)
        REQUIRE(SM.sourceTerms->sootSourceTerms.at(i) == 0);

    // check reset gasSourceTerms
    for (auto const& x : SM.sourceTerms->gasSourceTerms) {
        gasSp sp = x.first;
        REQUIRE(SM.sourceTerms->gasSourceTerms.at(sp) == 0);
    }

    // check reset pahSourceTerms
    for (auto const& x : SM.sourceTerms->pahSourceTerms) {
        pahSp sp = x.first;
        REQUIRE(SM.sourceTerms->pahSourceTerms.at(sp) == 0);
    }

}

////////////////////////////////////////////////////////////////////////////////

TEMPLATE_TEST_CASE_SIG("calcSourceTerms function call", "[sootModel][getSourceTerms]", ((psdMech P, int N), P, N),
                       (psdMech::MONO,2), (psdMech::LOGN,3), (psdMech::QMOM,2), (psdMech::QMOM,4), (psdMech::QMOM,6),
                       (psdMech::MOMIC,2), (psdMech::MOMIC,3), (psdMech::MOMIC,4), (psdMech::MOMIC,5), (psdMech::MOMIC,6)) {

//TEST_CASE("getSourceTermImplementation function call", "[sootModel][getSourceTerms]") {
//
//    psdMech P = psdMech::MOMIC;
//    int N = 6;

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

        SM.calcSourceTerms(S);

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