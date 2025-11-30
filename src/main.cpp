/**
 * @file main.cpp
 * @author Yuke Brilliant H (yukebrilliant@gmail.com)
 * @brief Particle collision simulation using SFML 3.x.x
 * @memberof FP Struktur Data dan Algoritma
 */

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <optional>
#include <memory>
#include <string>
#include <iostream>

#include "core/Config.h"
#include "core/Particle.h"
#include "algorithms/BruteForce.h"
#include "algorithms/QuadTree.h"

/**
 * @brief Update particle physics and handle wall collisions
 * @param particle Particle to update
 */
void updateParticlePhysics(Particle &particle)
{
    particle.shape.move(particle.velocity);

    sf::Vector2f pos = particle.shape.getPosition();
    float r = particle.shape.getRadius();

    // Check collision with window boundaries
    if (pos.x - r < 0)
    {
        particle.shape.setPosition({r, pos.y});
        particle.velocity.x *= -1;
    }
    else if (pos.x + r > Config::WINDOW_WIDTH)
    {
        particle.shape.setPosition({static_cast<float>(Config::WINDOW_WIDTH) - r, pos.y});
        particle.velocity.x *= -1;
    }

    if (pos.y - r < 0)
    {
        particle.shape.setPosition({pos.x, r});
        particle.velocity.y *= -1;
    }
    else if (pos.y + r > Config::WINDOW_HEIGHT)
    {
        particle.shape.setPosition({pos.x, static_cast<float>(Config::WINDOW_HEIGHT) - r});
        particle.velocity.y *= -1;
    }
}

/**
 * @brief Initialize particles with random properties
 * @return Vector of initialized particles
 */
std::vector<Particle> initializeParticles()
{
    std::vector<Particle> particles;

    for (int i = 0; i < Config::PARTICLE_COUNT; ++i)
    {
        // Randomize radius between MIN and MAX
        float r = Config::MIN_PARTICLE_RADIUS + 
                  static_cast<float>(rand() % static_cast<int>(Config::MAX_PARTICLE_RADIUS - Config::MIN_PARTICLE_RADIUS));
        
        // Randomize position within window bounds
        float x = r + static_cast<float>(rand() % (Config::WINDOW_WIDTH - static_cast<int>(2 * r)));
        float y = r + static_cast<float>(rand() % (Config::WINDOW_HEIGHT - static_cast<int>(2 * r)));
        
        // Randomize velocity between MIN and MAX, excluding zero
        float vx = Config::MIN_VELOCITY + static_cast<float>(rand() % static_cast<int>(Config::MAX_VELOCITY - Config::MIN_VELOCITY + 1));
        float vy = Config::MIN_VELOCITY + static_cast<float>(rand() % static_cast<int>(Config::MAX_VELOCITY - Config::MIN_VELOCITY + 1));

        if (vx == 0) vx = 1;
        if (vy == 0) vy = 1;

        particles.emplace_back(x, y, r, sf::Vector2f(vx, vy));
    }

    return particles;
}

int main(int argc, char *argv[])
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Parse command-line arguments buat pilih algo
    std::string algoName = "brute"; // default
    if (argc > 1)
    {
        std::string arg = argv[1];
        if (arg == "--algo" && argc > 2)
        {
            algoName = argv[2];
        }

        if (arg == "--help")
        {
            std::cout << "Usage: ./run [options]\n";
            std::cout << "Options:\n";
            std::cout << "  --algo [brute|quadtree]  Select collision detection algorithm\n";
            std::cout << "  --help                  Show this help message\n";
            return 0;
        }
    }

    // Initialize SFML window with anti-aliasing
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    // Window title tergantung algo yang dipilih
    std::string windowTitle = "Particle Collision - Algorithm: " + algoName;

    sf::RenderWindow window(
        sf::VideoMode({Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}),
        windowTitle,
        sf::Style::Default,
        sf::State::Windowed,
        settings);

    window.setFramerateLimit(Config::TARGET_FPS);

    // Initialize particles
    std::vector<Particle> particles = initializeParticles();

    // Select collision detection algorithm berdasarkan argument
    std::unique_ptr<CollisionDetector> detector;
    if (algoName == "quadtree")
    {
        detector = std::make_unique<QuadTree>();
    }
    else
    {
        // Default ke brute force
        detector = std::make_unique<BruteForce>();
    }

    // Main game loop
    while (window.isOpen())
    {
        // Event handling
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // Update physics for each particle
        for (auto &particle : particles)
        {
            updateParticlePhysics(particle);
        }

        // Detect and resolve collisions
        detector->detectAndResolve(particles);

        // Render
        window.clear(sf::Color::Black);
        for (const auto &particle : particles)
        {
            window.draw(particle.shape);
        }
        window.display();
    }

    return 0;
}
