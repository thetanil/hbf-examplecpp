#!/bin/bash
# Check C++ source files formatting using clang-format

set -e

echo "🔍 Checking C++ source files formatting..."

# Check all C++ files
if find src tests -name "*.cpp" -o -name "*.h" | xargs clang-format --dry-run --Werror; then
    echo "✅ All files are properly formatted!"
    exit 0
else
    echo "❌ Formatting errors found!"
    echo ""
    echo "To fix formatting issues, run:"
    echo "  bazel run //tools:format_fix"
    echo "  # or directly:"
    echo "  ./tools/format_fix.sh"
    exit 1
fi
