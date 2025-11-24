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

echo "-------- Compiling Simulasi --------"

# Explanation of Flags:
# -I : Look for headers (SFML/Graphics.hpp) in the INSTALL folder
# -L : Look for library files (libsfml-graphics.dylib) in the INSTALL folder
# -Wl,-rpath : Tells the resulting executable where to look for .dylib files at RUNTIME

clang++ main.cpp -o run \
  -I"$(pwd)/sfml/install/include" \
  -L"$(pwd)/sfml/install/lib" \
  -Wl,-rpath,"$(pwd)/sfml/install/lib" \
  -lsfml-graphics -lsfml-window -lsfml-system \
  -std=c++17

echo "-------- Build Complete --------"
echo "Run with: ./run"