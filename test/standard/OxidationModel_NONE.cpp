#include <memory>

#include "gtest/gtest.h"
#include "sootlib/oxidation_model/OxidationModel_NONE.h"

TEST (OxidationModel_NONE_TEST, basic_test)
{
	const double expectedValue = 0.0;
	std::unique_ptr<soot::OxidationModel> model = std::make_unique<soot::OxidationModel_NONE>();

	// Using exact comparison since model should return exactly 0
	EXPECT_EQ (expectedValue, model->getOxidationRate());
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
