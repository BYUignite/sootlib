#include <memory>

#include "gtest/gtest.h"
#include "sootlib/coagulation_model/CoagulationModel_NONE.h"

TEST (CoagulationModelNONETEST, basic_test)
{
	constexp double expectedValue = 0.0;
	std::unique_ptr<CoagulationModel> model = std::make_unique<CoagulationModel_NONE>();

	EXPECT_EQ (expectedValue, model->getCoagulationRate());
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
