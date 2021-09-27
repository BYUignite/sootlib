#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "constants.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("check for valid constants values", "[constants]") {

    SECTION("true constants are unchanged") {
        REQUIRE( Rg == 8314.46 );
        REQUIRE( Na == 6.02214086E26 );
        REQUIRE( kb == 1.38064852E-23 );
        REQUIRE( eps_c == 2.2 );
    }

    SECTION("other constant values are valid") {
        REQUIRE( Df >= 1 );
        REQUIRE( rhoSoot > 0 );
        REQUIRE( bCoag >= 1/sqrt(2) );
        REQUIRE( bCoag <= 1 );
    }
}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("get and set values from sourceTermStruct object", "[sourceTerms]") {

    sourceTermStruct ST;

    SECTION("check initialization values") {

        // soot source terms
        REQUIRE(ST.sootSourceTerms.at(0) == 0);
        REQUIRE(ST.sootSourceTerms.at(1) == 0);

        // gas source terms
        for (auto const& x : ST.gasSourceTerms) {
            gasSp sp = x.first;
            REQUIRE(ST.gasSourceTerms.at(sp) == 0);
        }

        // pah source terms
        for (auto const& x : ST.pahSourceTerms) {
            pahSp sp = x.first;
            REQUIRE(ST.pahSourceTerms.at(sp) == 0);
        }
    }

    SECTION("set values and check retrieval") {

        // soot source terms
        ST.sootSourceTerms.at(0) = 2.1;
        ST.sootSourceTerms.at(1) = 1.1E-5;

        REQUIRE(ST.sootSourceTerms.at(0) == 2.1);
        REQUIRE(ST.sootSourceTerms.at(1) == 1.1E-5);

        // gas source terms
        for (auto const& x : ST.gasSourceTerms) {
            gasSp sp = x.first;
            double d = 1.1;
            ST.gasSourceTerms.at(sp) = d;
            REQUIRE(ST.gasSourceTerms.at(sp) == d);
            d = d + 1;
        }

        // pah source terms
        for (auto const& x : ST.pahSourceTerms) {
            pahSp sp = x.first;
            double d = 1.1E-5;
            ST.pahSourceTerms.at(sp) = d;
            REQUIRE(ST.pahSourceTerms.at(sp) == d);
            d = d*10;
        }
    }
}

