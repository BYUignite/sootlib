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

TEST_CASE("sootModel object initialization", "[sootModel]") {

 }

////////////////////////////////////////////////////////////////////////////////
