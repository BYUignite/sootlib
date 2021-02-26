#include <memory>

#include "gtest/gtest.h"

#include "TestTools.h"

TEST (CoagulationModel_NONE_TEST, basic_test)
{
	const soot::State gasState = TestTools::getBlankGasState();
	const soot::MomentSootState sootState = TestTools::getBlankMomentSootState();

	const double expectedValue = 0.0;
	std::unique_ptr<soot::CoagulationModel> model = std::make_unique<soot::CoagulationModel_NONE>();

	// Using exact comparison since model should return exactly 0
	EXPECT_EQ (expectedValue, model->getCoagulationRate(gasState, sootState, 0, 0));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
