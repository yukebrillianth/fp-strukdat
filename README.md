# Final Project of Data Structure and Algorithm Analysis Course

This project is the final assignment for the Data Structure and Algorithm Analysis course, supervised by `Arta Kusuma Hernanda, S.T., M.T`. The task involves creating a Collision Simulations using the C++ programming language.

> **Name**: Yuke Brilliant Hestiavin  
> **Department**: Computer Engineering  
> **NRP**: 5024241016

## Table Of Contents

- [Final Project of Data Structure and Algorithm Analysis Course](#final-project-of-data-structure-and-algorithm-analysis-course)
  - [Table Of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Project Structure](#project-structure)
  - [Algorithms](#algorithms)
  - [Dependencies](#dependencies)
  - [Building and Running the Project](#building-and-running-the-project)
  - [Progress](#progress)

## Overview

This project simulates collisions between objects using the SFML (Simple and Fast Multimedia Library) for graphics rendering. It demonstrates the principles of data structures and algorithms through the implementation of collision detection and response mechanisms.

The project implements multiple collision detection algorithms to demonstrate the performance differences between naive and optimized approaches.

## Project Structure

```
fp/
├── include/           # Header files
│   ├── core/
│   │   ├── Particle.h      # Particle class definition
│   │   └── Config.h        # Global configuration constants
│   └── algorithms/
│       ├── CollisionDetector.h    # Base interface for collision detection
│       ├── BruteForce.h           # O(n²) brute-force algorithm
│       └── QuadTree.h             # O(n log n) spatial partitioning (TODO)
├── src/               # Implementation files
│   ├── core/
│   │   └── Particle.cpp
│   ├── algorithms/
│   │   ├── CollisionDetector.cpp  # Collision resolution physics
│   │   ├── BruteForce.cpp
│   │   └── QuadTree.cpp
│   └── main.cpp       # Main application entry point
├── sfml/              # SFML library (git submodule)
├── run.sh             # Build script
└── README.md
```

## Algorithms

### Brute Force (Implemented)

- **Time Complexity**: O(n²)
- **Space Complexity**: O(1)
- **Description**: Checks every pair of particles for collisions using nested loops
- **Best For**: Small number of particles (< 100)

### QuadTree (Implemented)

- **Time Complexity**: O(n log n) average case
- **Space Complexity**: O(n)
- **Description**: Uses spatial partitioning to reduce collision checks. Rebuilds tree each frame.
- **Best For**: Large number of particles (> 100)

## Algorithm Selection

You can customize the simulation with command-line arguments:

```bash
# Basic usage
./run                                    # Default: brute-force, 30 particles
./run --algo brute                       # Explicit brute-force
./run --algo quadtree                    # Use QuadTree

# Custom particle count
./run --count 100                        # 100 particles
./run --algo quadtree --count 200        # QuadTree with 200 particles

# Custom particle size
./run --size 25                          # Fixed size (radius 25)
./run --size 10,50                       # Random size range (10-50)

# Show FPS counter
./run --fps                              # Display FPS in window title
./run --algo quadtree --count 150 --fps  # All together

# Combinations
./run --algo quadtree --count 100 --size 15,35 --fps
./run --count 50 --size 40
```

**Available Options:**

- `--algo [brute|quadtree]` - Select collision detection algorithm
- `--count N` - Number of particles (default: 30)
- `--size SIZE` - Fixed particle radius
- `--size MIN,MAX` - Random particle radius range (default: 20,50)
- `--fps` - Show FPS counter in window title
- `--help` - Show help message

## Dependencies

- C++17 or later
- SFML 3.0.2 (included as git submodule)

## Building and Running the Project

### Prerequisites

- C++17 or later
- CMake 3.16 or later
- Clang or GCC compiler

### Build Instructions

**Option 1: Using build script (recommended)**

```bash
chmod +x build.sh
./build.sh
./run
```

**Option 2: Manual CMake build**

```bash
# Build SFML first (if not already built)
cd sfml
mkdir -p build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../install -DBUILD_SHARED_LIBS=ON
cmake --build . --config Release
cmake --install . --config Release
cd ../..

# Build the project
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd ..
./run
```

## Progress

- [x] Setup SFML as a submodule and build it automatically.
- [x] Implement basic collision detection and response.
- [x] Add collision detection between multiple objects
- [x] Restructure project with proper folder organization
- [x] Implement brute-force collision detection algorithm
- [x] Implement QuadTree spatial partitioning algorithm
- [x] Add command-line argument support for algorithm selection
- [ ] Add performance metrics display (FPS, collision checks per frame)

21/10/2025

- Create the project structure and initialize SFML window.
- Fixing SFML incompatibility issues for Apple M2 ARM64 architecture.

24/11/2025

- The object can collide with the wall but not with other objects yet.
- Implement basic collision detection and response between objects.
- Update the run script to build SFML dynamically if not already built.

https://github.com/user-attachments/assets/8f7667fd-8a75-468a-a9fd-2092a1890694

26/11/2025

- Implement collision detection between multiple objects.
- TO DO: Use bruteforce method and optimize it using spatial partitioning techniques like QuadTree.

30/11/2025

- Restructure project with proper folder organization.
- Separate core components and collision detection algorithms.
- Implement CollisionDetector interface for algorithm abstraction.
- Extract Particle class and configuration into separate files.
- Add CMake build system for cross-platform compatibility.
- Implement QuadTree spatial partitioning for O(n log n) collision detection.
- Add command-line argument support: `./run --algo [brute|quadtree]`
