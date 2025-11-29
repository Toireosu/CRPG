#!/usr/bin/env bash
set -e

# Paths
BUILD_DIR="build"
SRC_DIR="$(pwd)"
EXEC="$BUILD_DIR/Falloff.exe"   # MinGW places exe directly in build dir

# Hardcoded compiler
CC="/c/msys64/ucrt64/bin/gcc.exe"
CXX="/c/msys64/ucrt64/bin/g++.exe"

# Clean build folder
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Ensure MSYS2 compiler DLLs are in PATH
export PATH="/c/msys64/ucrt64/bin:$PATH"

# Generate Makefiles with hardcoded compiler
cmake -G "MinGW Makefiles" \
      -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_C_COMPILER="$CC" \
      -DCMAKE_CXX_COMPILER="$CXX" \
      "$SRC_DIR"

# Build the project
mingw32-make

cd ..

# Run the executable
echo "Running $EXEC..."
"$EXEC"