To write a test

1) Create `your_test.cc` in either the standard or cantera folder, depending on if this test is going
to include cantera components. Include `your_test` in the list of tests in the appropiate `CMakeLists.txt`

2) In your_test.cc, `#include "gtest/gtest.h"`

3) Create a main method as follows:
```
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```
4) Write a unit test with a test suite name and a test name. For example, if you are writing a
test called ones which is part of a test suite called basic_tests, write the following:
```
TEST (basic_tests, ones)
{
    // testing here
}
```
5) Unit tests should have 1 or more conditions to test. You can do this with macros including:
* `EXPECT_EQ (expected, tested)` - test fails if values are not equal, other conditions still run
* `ASSERT_EQ (expected, tested)` - test fails if values are not equal, test ends immediately

For floating point comparisons it is useful to use:
* `ASSERT_FLOAT_EQ (expected, actual)`
* `ASSERT_DOUBLE_EQ (expected, actual)`
* `ASSERT_NEAR (expected, actual, absolute_range)`
* `EXPECT_FLOAT_EQ (expected, actual)`
* `EXPECT_DOUBLE_EQ (expected, actual)`
* `EXPECT_NEAR (expected, actual, absolute_range)`
```
TEST (basic_tests, ones)
{
    EXPECT_EQ (1, 1);
}
```
6) Connect your unit tests to functional code. Below is an example file:
```
#include "gtest/gtest.h"

int echo(int num)
{
    return num;
}

TEST (echo_tests, one)
{
    ASSERT_EQ (1, echo(1));
}

TEST (echo_tests, two)
{
    ASSERT_EQ (2, echo(2));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```
7) You can `#include "TestTools.h"` to do things like generate dummy models

8) Here is a resource with more information: https://developer.ibm.com/technologies/systems/articles/au-googletestingframework/
