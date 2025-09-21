#include <gtest/gtest.h>

#include "math_operations.h"

namespace hbf_math {
namespace test {

class MathOperationsTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test addition function
TEST_F(MathOperationsTest, AddPositiveNumbers) {
  EXPECT_EQ(add(2, 3), 5);
  EXPECT_EQ(add(10, 20), 30);
  EXPECT_EQ(add(0, 5), 5);
}

TEST_F(MathOperationsTest, AddNegativeNumbers) {
  EXPECT_EQ(add(-1, 1), 0);
  EXPECT_EQ(add(-5, -3), -8);
  EXPECT_EQ(add(-10, 5), -5);
}

// Test multiplication function
TEST_F(MathOperationsTest, MultiplyPositiveNumbers) {
  EXPECT_EQ(multiply(3, 4), 12);
  EXPECT_EQ(multiply(7, 8), 56);
  EXPECT_EQ(multiply(1, 100), 100);
}

TEST_F(MathOperationsTest, MultiplyWithZero) {
  EXPECT_EQ(multiply(0, 5), 0);
  EXPECT_EQ(multiply(10, 0), 0);
  EXPECT_EQ(multiply(0, 0), 0);
}

TEST_F(MathOperationsTest, MultiplyNegativeNumbers) {
  EXPECT_EQ(multiply(-2, 5), -10);
  EXPECT_EQ(multiply(3, -4), -12);
  EXPECT_EQ(multiply(-6, -7), 42);
}

// Test factorial function
TEST_F(MathOperationsTest, FactorialBasicCases) {
  EXPECT_EQ(factorial(0), 1);
  EXPECT_EQ(factorial(1), 1);
  EXPECT_EQ(factorial(5), 120);
  EXPECT_EQ(factorial(6), 720);
}

TEST_F(MathOperationsTest, FactorialNegativeThrows) {
  EXPECT_THROW(factorial(-1), std::invalid_argument);
  EXPECT_THROW(factorial(-5), std::invalid_argument);
}

// Test power function
TEST_F(MathOperationsTest, PowerBasicCases) {
  EXPECT_DOUBLE_EQ(power(2.0, 0), 1.0);
  EXPECT_DOUBLE_EQ(power(2.0, 3), 8.0);
  EXPECT_DOUBLE_EQ(power(5.0, 2), 25.0);
}

TEST_F(MathOperationsTest, PowerNegativeExponent) {
  EXPECT_DOUBLE_EQ(power(2.0, -1), 0.5);
  EXPECT_DOUBLE_EQ(power(4.0, -2), 0.0625);
}

TEST_F(MathOperationsTest, PowerZeroBase) {
  EXPECT_DOUBLE_EQ(power(0.0, 5), 0.0);
  EXPECT_DOUBLE_EQ(power(0.0, 0), 1.0);  // 0^0 = 1 by convention
}

}  // namespace test
}  // namespace hbf_math
