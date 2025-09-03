#!/bin/bash
# Build script that generates compile_commands.json automatically

set -e  # Exit on any error

BUILD_DIR="build"
BUILD_TYPE="${1:-Debug}"

echo "FreeRTOS Learning Project Build Script"
echo "======================================"

# Create build directory
if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir "$BUILD_DIR"
fi

# Configure with CMake
echo "Configuring with CMake (Build type: $BUILD_TYPE)..."
cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

# Build the project
echo "Building project..."
cmake --build "$BUILD_DIR" -j$(nproc)

# Copy compile_commands.json to root for clangd
if [ -f "$BUILD_DIR/compile_commands.json" ]; then
    echo "Copying compile_commands.json for clangd..."
    cp "$BUILD_DIR/compile_commands.json" .
    echo "✅compile_commands.json generated successfully"
else
    echo "⚠ Warning: compile_commands.json not found in build directory"
fi

echo ""
echo "Build complete! Available executables in $BUILD_DIR/:"
echo "- 01_basic_task"
echo "- 02_queue_example" 
echo "- 03_semaphore_example"
echo "- 04_timer_example"
echo ""
echo "To run examples: cd $BUILD_DIR && ../run_examples.sh"