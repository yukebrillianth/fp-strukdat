/**
 * @file CollisionDetector.cpp
 * @author Yuke Brilliant H (yukebrilliant@gmail.com)
 * @brief Implementation of base collision resolution logic
 * @memberof FP Struktur Data dan Algoritma
 */

#include "algorithms/CollisionDetector.h"
#include <cmath>

void CollisionDetector::resolveCollision(Particle &p1, Particle &p2)
{
    sf::Vector2f pos1 = p1.shape.getPosition();
    sf::Vector2f pos2 = p2.shape.getPosition();
    sf::Vector2f delta = pos1 - pos2;

    // Calculate distance between particle centers: d = sqrt(x² + y²)
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float combinedRadius = p1.shape.getRadius() + p2.shape.getRadius();

    if (distance < combinedRadius)
    {
        // Separate overlapping particles
        float overlap = 0.5f * (combinedRadius - distance);
        sf::Vector2f correction = (delta / distance) * overlap;
        p1.shape.move(correction);
        p2.shape.move(-correction);

        // Calculate new velocities after elastic collision
        sf::Vector2f normal = delta / distance;    // Normal vector between particle centers
        sf::Vector2f tangent(-normal.y, normal.x); // Tangent vector perpendicular to normal

        // Project velocities onto normal and tangent vectors
        float v1tan = p1.velocity.x * tangent.x + p1.velocity.y * tangent.y;
        float v2tan = p2.velocity.x * tangent.x + p2.velocity.y * tangent.y;

        float v1n = p1.velocity.x * normal.x + p1.velocity.y * normal.y;
        float v2n = p2.velocity.x * normal.x + p2.velocity.y * normal.y;

        // Apply conservation of momentum in 1D along normal direction
        float m1 = p1.mass;
        float m2 = p2.mass;

        float momentum1 = (v1n * (m1 - m2) + 2.0f * m2 * v2n) / (m1 + m2);
        float momentum2 = (v2n * (m2 - m1) + 2.0f * m1 * v1n) / (m1 + m2);

        // Convert velocities back to 2D
        p1.velocity.x = tangent.x * v1tan + normal.x * momentum1;
        p1.velocity.y = tangent.y * v1tan + normal.y * momentum1;

        p2.velocity.x = tangent.x * v2tan + normal.x * momentum2;
        p2.velocity.y = tangent.y * v2tan + normal.y * momentum2;
    }
}
