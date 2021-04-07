#include <memory>

#include "gtest/gtest.h"

#include "TestTools.h"

#include "sootlib/growth_model/GrowthModel_NONE.h"

TEST (GrowthModel_NONE_TEST, basic_test)
{
    const InputState inputState = TestTools::getBlankState();

	unique_ptr<GrowthModel> model = make_unique<GrowthModel_NONE>();

	// Using exact comparison since model should return exactly 0
    const double expectedValue = 0;
    EXPECT_EQ (expectedValue, model->getGrowthRate(inputState));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
