#include <memory>

#include "gtest/gtest.h"

#include "TestTools.h"

#include "sootlib/oxidation_model/OxidationModel_NONE.h"

TEST (OxidationModel_NONE_TEST, basic_test)
{
    const InputState inputState = TestTools::getBlankState();
	unique_ptr<OxidationModel> model = make_unique<OxidationModel_NONE>();

	// Using exact comparison since model should return exactly 0
    const double expectedValue = 0;
    EXPECT_EQ (expectedValue, model->getOxidationRate(inputState));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
