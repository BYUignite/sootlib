#include <memory>

#include "gtest/gtest.h"

#include "TestTools.h"

#include "sootlib/coagulation_model/CoagulationModel_NONE.h"

TEST (CoagulationModel_NONE_TEST, basic_test)
{
	const InputState inputState = TestTools::getBlankState();
	unique_ptr<CoagulationModel> model = make_unique<CoagulationModel_NONE>();

	// Using exact comparison since model should return exactly 0
    const double expectedValue = 0;
    EXPECT_EQ (expectedValue, model->getCoagulationRate(inputState, 0, 0));
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
