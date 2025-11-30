/**
 * @file BruteForce.cpp
 * @author Yuke Brilliant H (yukebrilliant@gmail.com)
 * @brief Implementation of brute-force collision detection
 * @memberof FP Struktur Data dan Algoritma
 */

#include "algorithms/BruteForce.h"

void BruteForce::detectAndResolve(std::vector<Particle> &particles)
{
    // Check every pair of particles for collision
    for (size_t i = 0; i < particles.size(); ++i)
    {
        for (size_t j = i + 1; j < particles.size(); ++j)
        {
            resolveCollision(particles[i], particles[j]);
        }
    }
}
