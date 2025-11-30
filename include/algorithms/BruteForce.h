/**
 * @file BruteForce.h
 * @author Yuke Brilliant H (yukebrilliant@gmail.com)
 * @brief Brute-force collision detection algorithm
 * @memberof FP Struktur Data dan Algoritma
 */

#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include "algorithms/CollisionDetector.h"

/**
 * @class BruteForce
 * @brief Implements O(n²) brute-force collision detection
 * 
 * Checks every pair of particles for collisions using nested loops.
 * Simple but inefficient for large numbers of particles.
 */
class BruteForce : public CollisionDetector
{
public:
    /**
     * @brief Detect and resolve collisions using brute-force approach
     * @param particles Vector of particles to check
     * 
     * Time Complexity: O(n²) where n is the number of particles
     * Space Complexity: O(1)
     */
    void detectAndResolve(std::vector<Particle> &particles) override;
};

#endif // BRUTE_FORCE_H
