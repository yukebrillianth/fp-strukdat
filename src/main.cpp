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
 * @param count Number of particles to create
 * @param minSize Minimum particle radius
 * @param maxSize Maximum particle radius
 * @return Vector of initialized particles
 */
std::vector<Particle> initializeParticles(int count, float minSize, float maxSize)
{
    std::vector<Particle> particles;

    for (int i = 0; i < count; ++i)
    {
        // Randomize radius between min and max
        float r;
        int sizeRange = static_cast<int>(maxSize - minSize);
        if (sizeRange > 0) {
            r = minSize + static_cast<float>(rand() % sizeRange);
        } else {
            // Kalo range terlalu kecil, pake minSize aja
            r = minSize;
        }
        
        // Randomize position within window bounds
        int xRange = Config::WINDOW_WIDTH - static_cast<int>(2 * r);
        int yRange = Config::WINDOW_HEIGHT - static_cast<int>(2 * r);
        
        float x = r + static_cast<float>(rand() % (xRange > 0 ? xRange : 1));
        float y = r + static_cast<float>(rand() % (yRange > 0 ? yRange : 1));
        
        // Randomize velocity between MIN and MAX, excluding zero
        int velRange = static_cast<int>(Config::MAX_VELOCITY - Config::MIN_VELOCITY + 1);
        float vx = Config::MIN_VELOCITY + static_cast<float>(rand() % (velRange > 0 ? velRange : 1));
        float vy = Config::MIN_VELOCITY + static_cast<float>(rand() % (velRange > 0 ? velRange : 1));

        if (vx == 0) vx = 1;
        if (vy == 0) vy = 1;

        particles.emplace_back(x, y, r, sf::Vector2f(vx, vy));
    }

    return particles;
}

int main(int argc, char *argv[])
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Default values
    std::string algoName = "brute";
    int particleCount = Config::PARTICLE_COUNT;
    float minSize = Config::MIN_PARTICLE_RADIUS;
    float maxSize = Config::MAX_PARTICLE_RADIUS;
    bool showFPS = false;

    // Parse command-line arguments
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--algo" && i + 1 < argc)
        {
            algoName = argv[++i];
        }
        else if (arg == "--count" && i + 1 < argc)
        {
            particleCount = std::stoi(argv[++i]);
        }
        else if (arg == "--size" && i + 1 < argc)
        {
            // Format: --size min,max atau --size fixed
            std::string sizeArg = argv[++i];
            size_t commaPos = sizeArg.find(',');
            if (commaPos != std::string::npos)
            {
                minSize = std::stof(sizeArg.substr(0, commaPos));
                maxSize = std::stof(sizeArg.substr(commaPos + 1));
            }
            else
            {
                // Kalo ga ada koma, berarti fixed size
                minSize = maxSize = std::stof(sizeArg);
            }
        }
        else if (arg == "--fps")
        {
            showFPS = true;
        }
        else if (arg == "--help")
        {
            std::cout << "Usage: ./run [options]\n\n";
            std::cout << "Options:\n";
            std::cout << "  --algo [brute|quadtree]  Select collision detection algorithm (default: brute)\n";
            std::cout << "  --count N                Number of particles (default: " << Config::PARTICLE_COUNT << ")\n";
            std::cout << "  --size MIN,MAX           Particle size range (default: " << Config::MIN_PARTICLE_RADIUS 
                      << "," << Config::MAX_PARTICLE_RADIUS << ")\n";
            std::cout << "  --size SIZE              Fixed particle size\n";
            std::cout << "  --fps                    Show FPS counter\n";
            std::cout << "  --help                   Show this help message\n\n";
            std::cout << "Examples:\n";
            std::cout << "  ./run --algo quadtree --count 100 --fps\n";
            std::cout << "  ./run --count 50 --size 30\n";
            std::cout << "  ./run --size 10,50 --fps\n";
            return 0;
        }
    }

    // Initialize SFML window with anti-aliasing
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    // Window title dengan info particles dan algo
    std::string windowTitle = "Collision Sim - " + algoName + " | " + 
                              std::to_string(particleCount) + " particles";

    sf::RenderWindow window(
        sf::VideoMode({Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT}),
        windowTitle,
        sf::Style::Default,
        sf::State::Windowed,
        settings);

    window.setFramerateLimit(Config::TARGET_FPS);

    // Initialize particles dengan custom parameters
    std::vector<Particle> particles = initializeParticles(particleCount, minSize, maxSize);

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

    // Setup FPS counter
    sf::Clock fpsClock;
    int frameCount = 0;
    float fps = 0.0f;

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

        // Calculate FPS
        if (showFPS)
        {
            frameCount++;
            if (fpsClock.getElapsedTime().asSeconds() >= 1.0f)
            {
                fps = frameCount / fpsClock.restart().asSeconds();
                frameCount = 0;
                
                // Update window title dengan FPS
                std::string title = "Collision Sim - " + algoName + " | " + 
                                  std::to_string(particleCount) + " particles | FPS: " + 
                                  std::to_string(static_cast<int>(fps));
                window.setTitle(title);
            }
        }

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
