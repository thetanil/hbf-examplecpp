#pragma once

#include <stdexcept>

namespace hbf_math {
    /**
     * Add two integers.
     * @param a First integer
     * @param b Second integer
     * @return Sum of a and b
     */
    int add(int a, int b);
    
    /**
     * Multiply two integers.
     * @param a First integer
     * @param b Second integer
     * @return Product of a and b
     */
    int multiply(int a, int b);
    
    /**
     * Calculate factorial of a non-negative integer.
     * @param n Non-negative integer
     * @return Factorial of n
     * @throws std::invalid_argument if n is negative
     */
    long long factorial(int n);
    
    /**
     * Calculate power of a number.
     * @param base Base number
     * @param exponent Integer exponent
     * @return base raised to the power of exponent
     */
    double power(double base, int exponent);
}
