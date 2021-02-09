#include <memory>

#include "gtest/gtest.h"

#include "TestTools.h"

#include "sootlib/nucleation_model/NucleationModel_NONE.h"

TEST (NucleationModel_NONE_TEST, basic_test)
{
	const soot::GasState gasState = TestTools::getBlankGasState();
	const soot::SootState sootState = TestTools::getBlankSootState();

	const double expectedValue = 0.0;
	std::unique_ptr<soot::NucleationModel> model = std::make_unique<soot::NucleationModel_NONE>();

	// Using exact comparison since model should return exactly 0
	EXPECT_EQ (expectedValue, model->getNucleationRate(gasState, sootState));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
