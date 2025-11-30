/**
 * @file Particle.h
 * @author Yuke Brilliant H (yukebrilliant@gmail.com)
 * @brief Particle class representing a circular object with physics properties
 * @memberof FP Struktur Data dan Algoritma
 */

#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

/**
 * @class Particle
 * @brief Represents a circular particle with position, velocity, and mass
 */
class Particle
{
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float mass;

    /**
     * @brief Construct a new Particle object
     * @param x Initial x-position
     * @param y Initial y-position
     * @param radius Radius of the particle (also determines mass)
     * @param vel Initial velocity vector
     */
    Particle(float x, float y, float radius, sf::Vector2f vel);
};

#endif // PARTICLE_H
