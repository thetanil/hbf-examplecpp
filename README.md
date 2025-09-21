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

### v1.0.1 test

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

#### Code Formatting

The project uses `clang-format` for consistent code formatting:

```bash
# Check if code is properly formatted
./tools/format_check.sh

# Automatically fix formatting issues
./tools/format_fix.sh

# Check formatting without making changes
find src tests -name "*.cpp" -o -name "*.h" | xargs clang-format --dry-run --Werror
```

**Note**: The CI will fail if code is not properly formatted. Always run `./tools/format_fix.sh` before committing.

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

#### Continuous Integration

The project uses GitHub Actions with `bazel-contrib/setup-bazel` for optimal CI performance:

```yaml
- name: Setup Bazel
  uses: bazel-contrib/setup-bazel@0.15.0
  with:
    bazelisk-cache: true          # Cache Bazel downloads
    disk-cache: ${{ github.workflow }}  # Per-workflow build cache
    repository-cache: true        # Shared external deps cache
```

This provides automatic caching without manual configuration and significantly faster CI runs.

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
- **v1.0.2**: CI improvements and formatting fixes
- **v1.1.0**: Added GCD function (breaking for consumers expecting only v1.0.0 API)

### Release Process

When creating a new release:

1. **Create and push a git tag**: `git tag v1.0.x && git push origin v1.0.x`
2. **Create GitHub release**: This triggers the CI workflow
3. **Automatic Renovate trigger**: The release workflow automatically notifies the meta-repository (`thetanil/hbf`) to update dependencies

**Important**: The release process requires the `RENOVATE_TOKEN` secret to be configured. If the Renovate trigger fails, the entire release workflow will fail to ensure dependency updates are properly propagated.

### Release Workflow Requirements

- **`RENOVATE_TOKEN` secret**: Must have `repo` scope for the meta-repository
- **Meta-repository access**: Token must have access to `thetanil/hbf`
- **Network connectivity**: GitHub API must be accessible during release

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

~~You may see these warnings when building (they are harmless):~~

~~WARNING: Option 'experimental_enable_bzlmod' is deprecated: Use --enable_bzlmod instead~~

**Fixed!** The deprecated `--experimental_enable_bzlmod` flag has been removed from `.bazelrc` in favor of the modern `--enable_bzlmod` flag.

If you see dependency version warnings:
```
WARNING: For repository 'rules_cc', the root module requires module version rules_cc@0.0.9, but got rules_cc@0.1.1
```

These can be resolved by updating dependency versions in `MODULE.bazel` to match resolved versions, or using `--check_direct_dependencies=off` if needed.

### Build Issues

If you encounter build failures:

```bash
# Clean and retry
bazel clean
bazel test //...

# Check Bazel version
bazel version

# Verify bzlmod is enabled
bazel info | grep bzlmod
```

### Code Formatting Issues

If CI fails due to formatting:

```bash
# Fix all formatting issues automatically
./tools/format_fix.sh

# Then rebuild and test
bazel test //...

# Verify formatting is correct
./tools/format_check.sh
```

### Release and Renovate Issues

If a release fails to trigger Renovate updates:

```bash
# Check the GitHub Actions workflow logs for:
# - RENOVATE_TOKEN configuration issues
# - HTTP status codes from GitHub API calls
# - Network connectivity problems
```

**Common Renovate trigger failures**:

- **❌ RENOVATE_TOKEN not configured**: Add the secret in repository settings
- **❌ HTTP 401/403**: Token lacks `repo` scope or access to meta-repository  
- **❌ HTTP 404**: Meta-repository `thetanil/hbf` doesn't exist or isn't accessible
- **❌ Network issues**: Temporary GitHub API problems

**Required for successful releases**:
- `RENOVATE_TOKEN` secret with `repo` scope
- Token access to `thetanil/hbf` repository  
- GitHub API connectivity during release workflow

### GitHub Actions CI Issues

**Cache service responded with 400**: This CI issue has been resolved by:
- **Migrating to `bazel-contrib/setup-bazel@0.15.0`** (replaces deprecated `bazelbuild/setup-bazelisk`)
- **Built-in intelligent caching** with `bazelisk-cache`, `disk-cache`, and `repository-cache`
- **Simplified configuration** - no manual cache setup needed
- **Per-workflow disk cache** for build artifacts
- **Shared repository cache** between workflows for external dependencies

The modern CI workflow now includes:
- Latest Bazel setup with automatic version detection from `.bazelversion`
- Advanced caching strategies for optimal performance
- Build and test validation with proper error reporting
- Module structure verification
- Optional code formatting checks with clang-format

**Benefits of the new setup**:
- ✅ Faster CI runs with intelligent caching
- ✅ No cache key conflicts or 400 errors  
- ✅ Automatic Bazel/Bazelisk version management
- ✅ Shared caches across workflow runs
- ✅ Better cache hit rates for external dependencies

## Integration

This component is designed to work with:

- `hbf_examplepy` - Python wrapper providing language bindings
- `hbf` meta-repository - Integration testing and version coordination

## License

MIT License - see LICENSE file for details.
