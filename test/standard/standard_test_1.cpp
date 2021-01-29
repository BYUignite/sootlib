#include "gtest/gtest.h"

int one()
{
	return 1;
}

TEST(test_suite, test_name)
{
	EXPECT_EQ (1, 1);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
