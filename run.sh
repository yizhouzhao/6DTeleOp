#!/bin/bash

# Stop on first error
# set -e

# Define colors for output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== Building OpenCV Project ===${NC}"

# Remove build directory if it exists
if [ -d "build" ]; then
    echo "Removing old build directory..."
    rm -rf build
fi

# Create build directory and navigate to it
echo "Creating fresh build directory..."
mkdir -p build
cd build

# Run CMake configuration
echo "Running CMake configuration..."
cmake ..

# Build the project
echo "Building project..."
cmake --build .


echo -e "${GREEN}=== Build successful! ===${NC}"
echo -e "${BLUE}=== Running $EXECUTABLE ===${NC}"

# Run the executable
EXECUTABLE="./src/6DTeleOp"
./$EXECUTABLE

echo -e "${GREEN}=== Execution complete ===${NC}"