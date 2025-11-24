# Final Project of Data Structure and Algorithm Analysis Course

This project is the final assignment for the Data Structure and Algorithm Analysis course, supervised by `Arta Kusuma Hernanda, S.T., M.T`. The task involves creating a Collision Simulations using the C++ programming language.

> **Name**: Yuke Brilliant Hestiavin  
> **Department**: Computer Engineering  
> **NRP**: 5024241016

## Table Of Contents

- [Final Project of Data Structure and Algorithm Analysis Course](#final-project-of-data-structure-and-algorithm-analysis-course)
  - [Table Of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Dependencies](#dependencies)
  - [Building and Running the Project](#building-and-running-the-project)
  - [Progress](#progress)

## Overview

This project simulates collisions between objects using the SFML (Simple and Fast Multimedia Library) for graphics rendering. It demonstrates the principles of data structures and algorithms through the implementation of collision detection and response mechanisms.

## Dependencies

- C++17 or later
- SFML 3.0.2

## Building and Running the Project

To build and run the project, follow these steps:

1. Ensure you have C++17 or later installed on your system.
2. Clone the repository to your local machine.
3. Navigate to the project directory.
4. Run the provided `run.sh` script to build SFML (if not already built) and compile the project:
   ```bash
   ./run.sh
   ```
5. After successful compilation, run the simulation:
   ```bash
   ./run
   ```

## Progress

- [x] Setup SFML as a submodule and build it automatically.
- [x] Implement basic collision detection and response.
- [ ] Add more complex collision scenarios and object types.
- [ ] Add collision detection between multiple objects

21/10/2025

- Create the project structure and initialize SFML window.
- Fixing SFML incompatibility issues for Apple M2 ARM64 architecture.

24/11/2025

- The object can collide with the wall but not with other objects yet.
- Implement basic collision detection and response between objects.
- Update the run script to build SFML dynamically if not already built.
