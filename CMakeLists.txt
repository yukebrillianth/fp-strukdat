cmake_minimum_required(VERSION 3.16)
project(ParticleCollisionSimulation LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML configuration
set(SFML_DIR "${CMAKE_SOURCE_DIR}/sfml/install/lib/cmake/SFML")
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/core/Particle.cpp
    src/algorithms/CollisionDetector.cpp
    src/algorithms/BruteForce.cpp
    src/algorithms/QuadTree.cpp
)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create executable
add_executable(run ${SOURCES})

# Link SFML libraries
target_link_libraries(run PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

# Set runtime library path for macOS
if(APPLE)
    set_target_properties(run PROPERTIES
        BUILD_RPATH "${CMAKE_SOURCE_DIR}/sfml/install/lib"
        INSTALL_RPATH "${CMAKE_SOURCE_DIR}/sfml/install/lib"
    )
endif()
