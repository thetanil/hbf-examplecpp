#!/bin/bash
# Format all C++ source files using clang-format

set -e

echo "🔧 Formatting C++ source files..."

# Find all C++ files and format them
find src tests -name "*.cpp" -o -name "*.h" | while read -r file; do
    echo "Formatting: $file"
    clang-format -i "$file"
done

echo "✅ Formatting complete!"
