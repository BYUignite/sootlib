#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "constants.h"

using namespace std;
using namespace soot;

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