/**
 * @file CollisionDetector.h
 * @author Yuke Brilliant H (yukebrilliant@gmail.com)
 * @brief Abstract base class for collision detection algorithms
 * @memberof FP Struktur Data dan Algoritma
 */

#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include "core/Particle.h"
#include <vector>

/**
 * @class CollisionDetector
 * @brief Interface for different collision detection algorithms
 */
class CollisionDetector
{
public:
    virtual ~CollisionDetector() = default;

    /**
     * @brief Detect and resolve collisions between particles
     * @param particles Vector of particles to check for collisions
     */
    virtual void detectAndResolve(std::vector<Particle> &particles) = 0;

protected:
    /**
     * @brief Resolve collision between two particles
     * @param p1 First particle
     * @param p2 Second particle
     * 
     * Uses elastic collision physics with momentum conservation
     */
    void resolveCollision(Particle &p1, Particle &p2);
};

#endif // COLLISION_DETECTOR_H
