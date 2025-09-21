#include "math_operations.h"

namespace hbf_math {

int add(int a, int b) { return a + b; }

int multiply(int a, int b) { return a * b; }

long long factorial(int n) {
  if (n < 0) {
    throw std::invalid_argument("Factorial of negative number is undefined");
  }
  if (n <= 1) {
    return 1;
  }
  return n * factorial(n - 1);
}

double power(double base, int exponent) {
  if (exponent == 0) {
    return 1.0;
  }
  if (exponent < 0) {
    return 1.0 / power(base, -exponent);
  }
  return base * power(base, exponent - 1);
}
}  // namespace hbf_math
