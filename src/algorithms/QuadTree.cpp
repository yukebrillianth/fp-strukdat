/**
 * @file QuadTree.cpp
 * @author Yuke Brilliant H (yukebrilliant@gmail.com)
 * @brief Implementation of QuadTree collision detection
 * @memberof FP Struktur Data dan Algoritma
 */

#include "algorithms/QuadTree.h"
#include "core/Config.h"

void QuadTree::detectAndResolve(std::vector<Particle> &particles)
{
    // Bikin tree baru setiap frame
    // Capacity 4 itu sweet spot antara depth vs particles per node
    Rectangle boundary(Config::WINDOW_WIDTH / 2.0f, Config::WINDOW_HEIGHT / 2.0f,
                       Config::WINDOW_WIDTH / 2.0f, Config::WINDOW_HEIGHT / 2.0f);
    QuadTreeNode tree(boundary, 4);

    // Masukin semua particles ke tree
    for (auto &particle : particles)
    {
        tree.insert(&particle);
    }

    // Untuk tiap particle, cari nearby particles dan check collision
    for (size_t i = 0; i < particles.size(); ++i)
    {
        // Bikin range query berdasarkan posisi particle + radiusnya
        // Kasih buffer dikit biarga miss particles yang berdekatan
        sf::Vector2f pos = particles[i].shape.getPosition();
        float r = particles[i].shape.getRadius();
        float searchRadius = r * 3.0f; // 3x radius buat safety margin

        Rectangle range(pos.x, pos.y, searchRadius, searchRadius);

        // Query nearby particles
        std::vector<Particle *> nearbyParticles;
        tree.query(range, nearbyParticles);

        // Check collision cuma sama nearby particles aja
        for (auto *other : nearbyParticles)
        {
            // Skip kalo particle sama
            if (other == &particles[i])
                continue;

            // Cek collision
            resolveCollision(particles[i], *other);
        }
    }
}
