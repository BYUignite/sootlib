#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "constants.h"

using namespace std;
using namespace soot;

TEST_CASE("check constants values", "[constants]") {

    REQUIRE( Rg == 8314.46 );
    REQUIRE( Na == 6.02214086E26 );
    REQUIRE( kb == 1.38064852E-23 );

}