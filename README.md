# HBF Example C++ Component

A simple C++ mathematical library component for the HBF (Harmonizing Build Federation) demo.

## Overview

This component provides basic mathematical operations that can be consumed by other components in the HBF ecosystem. It demonstrates:

- Bazel module (bzlmod) integration
- Cross-language interoperability
- Semantic versioning
- Comprehensive testing

## Functions Provided

### v1.0.0 Functions

- `add(int a, int b)` - Add two integers
- `multiply(int a, int b)` - Multiply two integers  
- `factorial(int n)` - Calculate factorial of non-negative integer
- `power(double base, int exponent)` - Calculate power with integer exponent

### v1.1.0 Functions (Added Later)

- `gcd(int a, int b)` - Calculate greatest common divisor

## Building

### Prerequisites

- Bazel 6.0+ with bzlmod support
- C++17 compatible compiler

### Development Workflow

#### Quick Start
```bash
# Clone and enter the repository
git clone https://github.com/thetanil/hbf-examplecpp.git
cd hbf-examplecpp

# Build and test everything (recommended first step)
bazel test //...
```

#### Build Commands

```bash
# Build the main library
bazel build //src:math_operations

# Build everything in the project
bazel build //...

# Build with verbose output for debugging
bazel build //... --verbose_failures
```

#### Testing Commands

```bash
# Run all tests
bazel test //...

# Run specific test target
bazel test //tests:test_math_operations

# Run tests with detailed output
bazel test //tests:test_math_operations --test_output=all

# Run tests with error details only
bazel test //... --test_output=errors
```

#### Development and Debugging

```bash
# Validate project structure
bazel query //... --output=package

# List all available targets
bazel query //...

# Build in debug mode
bazel build //... --compilation_mode=dbg

# Clean build artifacts
bazel clean

# Clean everything including external dependencies
bazel clean --expunge
```

#### Expected Output

When running `bazel test //... --test_output=all`, you should see:
```
[==========] Running 10 tests from 1 test suite.
[----------] 10 tests from MathOperationsTest
[ RUN      ] MathOperationsTest.AddPositiveNumbers
[       OK ] MathOperationsTest.AddPositiveNumbers (0 ms)
[ RUN      ] MathOperationsTest.AddNegativeNumbers
[       OK ] MathOperationsTest.AddNegativeNumbers (0 ms)
... (8 more tests)
[==========] 10 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 10 tests.
```

## Usage in Other Components

### As a Bazel Dependency

Add to your `MODULE.bazel`:

```bazel
bazel_dep(name = "hbf_examplecpp", version = "1.0.0")
```

Use in your `BUILD.bazel`:

```bazel
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
    name = "my_app",
    srcs = ["main.cpp"],
    deps = ["@hbf_examplecpp//src:math_operations"],
)
```

### Example Usage in C++

```cpp
#include "math_operations.h"
#include <iostream>

int main() {
    // Basic operations
    std::cout << "Add: " << hbf_math::add(5, 3) << std::endl;           // 8
    std::cout << "Multiply: " << hbf_math::multiply(4, 7) << std::endl; // 28
    
    // Advanced operations
    std::cout << "Factorial: " << hbf_math::factorial(5) << std::endl;  // 120
    std::cout << "Power: " << hbf_math::power(2.0, 8) << std::endl;     // 256.0
    
    return 0;
}
```

### Testing Your Integration

```bash
# Build your project that depends on hbf_examplecpp
bazel build //:my_app

# Run integration tests
bazel test //...
```

## Versioning

This component follows semantic versioning:

- **v1.0.0**: Initial release with basic mathematical operations
- **v1.1.0**: Added GCD function (breaking for consumers expecting only v1.0.0 API)

## Testing

The component includes comprehensive unit tests covering:

- **Positive and negative number handling** - All functions tested with various number ranges
- **Edge cases** - Zero values, large numbers, boundary conditions  
- **Error conditions** - Exception handling for invalid inputs (e.g., negative factorial)
- **Boundary value testing** - Corner cases like 0^0, negative exponents

### Test Coverage

| Function | Test Cases | Coverage |
|----------|------------|----------|
| `add()` | Positive, negative, zero | ✅ Complete |
| `multiply()` | Positive, negative, zero | ✅ Complete |
| `factorial()` | Basic cases, negative (throws) | ✅ Complete |
| `power()` | Basic, negative exponent, zero base | ✅ Complete |

### Running Tests

```bash
# Quick test run (recommended)
bazel test //...

# Detailed test output showing all test cases
bazel test //tests:test_math_operations --test_output=all

# Test only with build output
bazel test //... --test_output=errors

# Run tests multiple times (for flaky test detection)
bazel test //... --runs_per_test=5
```

### Test Results Example

All 10 tests should pass successfully:
- `AddPositiveNumbers`, `AddNegativeNumbers`
- `MultiplyPositiveNumbers`, `MultiplyWithZero`, `MultiplyNegativeNumbers`  
- `FactorialBasicCases`, `FactorialNegativeThrows`
- `PowerBasicCases`, `PowerNegativeExponent`, `PowerZeroBase`

## Troubleshooting

### Common Warnings

You may see these warnings when building (they are harmless):

```
WARNING: Option 'experimental_enable_bzlmod' is deprecated: Use --enable_bzlmod instead
WARNING: For repository 'rules_cc', the root module requires module version rules_cc@0.0.9, but got rules_cc@0.1.1
```

These can be resolved by:
1. Updating `.bazelrc` to use `--enable_bzlmod` instead of the experimental flag
2. Updating dependency versions in `MODULE.bazel` to match resolved versions

### Build Issues

If you encounter build failures:

```bash
# Clean and retry
bazel clean
bazel build //...

# Check Bazel version
bazel version

# Verify bzlmod is enabled
bazel info | grep bzlmod
```

## Integration

This component is designed to work with:

- `hbf_examplepy` - Python wrapper providing language bindings
- `hbf` meta-repository - Integration testing and version coordination

## License

MIT License - see LICENSE file for details.
