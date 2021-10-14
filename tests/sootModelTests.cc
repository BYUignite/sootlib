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

TEMPLATE_TEST_CASE_SIG("get/set values of sourceTerms from sootModel object", "[sootModel][sourceTerms]", ((psdMech P, int N), P, N),
                       (psdMech::MONO,2), (psdMech::LOGN,3), (psdMech::QMOM,2), (psdMech::QMOM,4), (psdMech::QMOM,6),
                       (psdMech::MOMIC,2), (psdMech::MOMIC,3), (psdMech::MOMIC,4), (psdMech::MOMIC,5), (psdMech::MOMIC,6)) {

//TEST_CASE("getSourceTermImplementation function call", "[psdModel][getSourceTerms]") {
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
}