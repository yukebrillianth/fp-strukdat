#!/bin/bash
set -e

if [ ! -d "sfml/install/lib" ]; then
  echo "-------- Building SFML 3.0.2 --------"
  
  cd sfml  
  mkdir -p build
  cd build
  
  # Configure CMake
  # -DCMAKE_INSTALL_PREFIX=../install : Tells CMake to put the final files in sfml/install
  # -DBUILD_SHARED_LIBS=ON            : We want .dylib files (dynamic linking)
  # -DCMAKE_BUILD_TYPE=Release        : Optimized build
  cmake .. \
    -DCMAKE_INSTALL_PREFIX=../install \
    -DBUILD_SHARED_LIBS=ON \
    -DCMAKE_BUILD_TYPE=Release

  cmake --build . --config Release
  cmake --install . --config Release
  
  cd ../..
  echo "-------- SFML Built Successfully --------"
fi

echo "-------- Compiling Collision Simulation --------"

# Compile all source files
# Explanation of Flags:
# -I : Look for headers in the include directory and SFML install folder
# -L : Look for library files in the SFML install folder
# -Wl,-rpath : Tells the executable where to look for .dylib files at runtime
# -lsfml-* : Link against SFML libraries
# -std=c++17 : Use C++17 standard

clang++ \
  src/main.cpp \
  src/core/Particle.cpp \
  src/algorithms/CollisionDetector.cpp \
  src/algorithms/BruteForce.cpp \
  src/algorithms/QuadTree.cpp \
  -o run \
  -I"$(pwd)/include" \
  -I"$(pwd)/sfml/install/include" \
  -L"$(pwd)/sfml/install/lib" \
  -Wl,-rpath,"$(pwd)/sfml/install/lib" \
  -lsfml-graphics -lsfml-window -lsfml-system \
  -std=c++17

echo "-------- Build Complete --------"
echo "Run with: ./run"