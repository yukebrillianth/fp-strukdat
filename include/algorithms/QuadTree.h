/**
 * @file QuadTree.h
 * @author Yuke Brilliant H (yukebrilliant@gmail.com)
 * @brief QuadTree-based collision detection using spatial partitioning
 * @memberof FP Struktur Data dan Algoritma
 */

#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "algorithms/CollisionDetector.h"
#include <memory>

// Rectangle buat nge-define area/boundary
struct Rectangle
{
    float x, y; // posisi center
    float w, h; // half-width dan half-height

    Rectangle(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

    // Cek apakah particle ada di dalam rectangle ini
    bool contains(const Particle &particle) const
    {
        sf::Vector2f pos = particle.shape.getPosition();
        return (pos.x >= x - w && pos.x <= x + w &&
                pos.y >= y - h && pos.y <= y + h);
    }

    // Cek apakah rectangle ini overlap sama rectangle lain
    bool intersects(const Rectangle &other) const
    {
        return !(other.x - other.w > x + w ||
                 other.x + other.w < x - w ||
                 other.y - other.h > y + h ||
                 other.y + other.h < y - h);
    }
};

// Node untuk QuadTree
class QuadTreeNode
{
private:
    Rectangle boundary;
    int capacity; // max particles sebelum subdivide
    std::vector<Particle *> particles;
    bool divided;

    // 4 children: northwest, northeast, southwest, southeast
    std::unique_ptr<QuadTreeNode> nw;
    std::unique_ptr<QuadTreeNode> ne;
    std::unique_ptr<QuadTreeNode> sw;
    std::unique_ptr<QuadTreeNode> se;

    // Subdivide node jadi 4 quadrants
    void subdivide()
    {
        float x = boundary.x;
        float y = boundary.y;
        float w = boundary.w / 2;
        float h = boundary.h / 2;

        // Bikin 4 child nodes
        nw = std::make_unique<QuadTreeNode>(Rectangle(x - w, y - h, w, h), capacity);
        ne = std::make_unique<QuadTreeNode>(Rectangle(x + w, y - h, w, h), capacity);
        sw = std::make_unique<QuadTreeNode>(Rectangle(x - w, y + h, w, h), capacity);
        se = std::make_unique<QuadTreeNode>(Rectangle(x + w, y + h, w, h), capacity);

        divided = true;
    }

public:
    QuadTreeNode(Rectangle boundary, int capacity)
        : boundary(boundary), capacity(capacity), divided(false)
    {
        particles.reserve(capacity);
    }

    // Insert particle ke tree
    bool insert(Particle *particle)
    {
        // Kalo particle ga masuk boundary, skip
        if (!boundary.contains(*particle))
        {
            return false;
        }

        // Kalo masih ada space dan belum divided, masukkan disini
        if (particles.size() < capacity && !divided)
        {
            particles.push_back(particle);
            return true;
        }

        // Kalo belum divided, subdivide dulu
        if (!divided)
        {
            subdivide();
            // Pindahin particles yang udah ada ke children
            for (auto *p : particles)
            {
                nw->insert(p) || ne->insert(p) || sw->insert(p) || se->insert(p);
            }
            particles.clear();
        }

        // Insert ke salah satu child
        return nw->insert(particle) || ne->insert(particle) ||
               sw->insert(particle) || se->insert(particle);
    }

    // Query particles dalam range tertentu
    void query(const Rectangle &range, std::vector<Particle *> &found)
    {
        // Kalo range ga overlap sama boundary, skip
        if (!boundary.intersects(range))
        {
            return;
        }

        // Check particles di node ini
        for (auto *p : particles)
        {
            if (range.contains(*p))
            {
                found.push_back(p);
            }
        }

        // Kalo udah divided, query children juga
        if (divided)
        {
            nw->query(range, found);
            ne->query(range, found);
            sw->query(range, found);
            se->query(range, found);
        }
    }
};

/**
 * @class QuadTree
 * @brief Implements spatial partitioning for efficient collision detection
 * 
 * QuadTree ini rebuild setiap frame buat simplicity.
 * Bisa di-optimasi nanti dengan update incremental.
 */
class QuadTree : public CollisionDetector
{
public:
    /**
     * @brief Detect and resolve collisions using QuadTree approach
     * @param particles Vector of particles to check
     * 
     * Time Complexity: O(n log n) average case
     * Space Complexity: O(n)
     */
    void detectAndResolve(std::vector<Particle> &particles) override;
};

#endif // QUAD_TREE_H
