#include "gtest/gtest.h"

int one()
{
	return 1;
}

TEST(one, Passer)
{
	EXPECT_EQ (1, one());
}

TEST(one, Failer)
{
	EXPECT_EQ (2, one());
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
