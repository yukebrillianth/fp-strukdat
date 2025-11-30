#!/bin/bash
set -e

# Build SFML if needed
if [ ! -d "sfml/install/lib" ]; then
  echo "-------- Building SFML 3.0.2 --------"
  
  cd sfml  
  mkdir -p build
  cd build
  
  cmake .. \
    -DCMAKE_INSTALL_PREFIX=../install \
    -DBUILD_SHARED_LIBS=ON \
    -DCMAKE_BUILD_TYPE=Release

  cmake --build . --config Release
  cmake --install . --config Release
  
  cd ../..
  echo "-------- SFML Built Successfully --------"
fi

# Build the project using CMake
echo "-------- Building Collision Simulation --------"

mkdir -p build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

cd ..

echo "-------- Build Complete --------"
echo "Run with: ./run"
