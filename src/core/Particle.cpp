/**
 * @file Particle.cpp
 * @author Yuke Brilliant H (yukebrilliant@gmail.com)
 * @brief Implementation of the Particle class
 * @memberof FP Struktur Data dan Algoritma
 */

#include "core/Particle.h"
#include <cstdlib>

Particle::Particle(float x, float y, float radius, sf::Vector2f vel)
{
    shape.setPosition({x, y});
    shape.setRadius(radius);
    shape.setOrigin({radius, radius});

    // Generate random RGB color
    shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));

    velocity = vel;
    mass = radius;
}
