/**
 * Simulasi Partikel Sederhana menggunakan SFML 3.x.x
 * FP Struktur Data dan Algoritma
 * Dibuat oleh: @yukebrillianth
 * NRP: 5024241016
 */

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <optional>

// window dimensions
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

// Particle structy
struct Particle
{
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float mass;

    Particle(float x, float y, float radius, sf::Vector2f vel)
    {
        // pake vector2f untuk v3.x.x
        shape.setPosition({x, y});
        shape.setRadius(radius);
        shape.setOrigin({radius, radius});

        // random RGB value
        shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));

        velocity = vel;
        mass = radius;
    }
};

void resolveCollision(Particle &p1, Particle &p2)
{
    sf::Vector2f pos1 = p1.shape.getPosition();
    sf::Vector2f pos2 = p2.shape.getPosition();
    sf::Vector2f delta = pos1 - pos2;

    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float combinedRadius = p1.shape.getRadius() + p2.shape.getRadius();

    if (distance < combinedRadius)
    {
        // cek overlap dan pisahkan partikel
        float overlap = 0.5f * (combinedRadius - distance);
        sf::Vector2f correction = (delta / distance) * overlap;
        p1.shape.move(correction);
        p2.shape.move(-correction);

        // calculate new velocities after collision
        sf::Vector2f normal = delta / distance;
        sf::Vector2f tangent(-normal.y, normal.x);
    }
}

int main()
{
    /**
     * Inisialisasi window SFML 3.x.x
     * Untuk SFML 2.x.x, gunakan:
     * sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Simulasi Partikel");
     *
     */
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Simulasi Partikel Collission", sf::Style::Default, sf::State::Windowed, settings);

    window.setFramerateLimit(60);

    std::vector<Particle> particles;

    for (int i = 0; i < 15; ++i)
    {
        float r = 20.0f + static_cast<float>(rand() % 30);
        float x = r + static_cast<float>(rand() % (WINDOW_WIDTH - static_cast<int>(2 * r)));
        float y = r + static_cast<float>(rand() % (WINDOW_HEIGHT - static_cast<int>(2 * r)));
        float vx = -4.0f + static_cast<float>(rand() % 9);
        float vy = -4.0f + static_cast<float>(rand() % 9);

        if (vx == 0)
            vx = 1;
        if (vy == 0)
            vy = 1;

        particles.emplace_back(x, y, r, sf::Vector2f(vx, vy));
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        // logika fisika
        for (size_t i = 0; i < particles.size(); ++i)
        {
            particles[i].shape.move(particles[i].velocity);

            sf::Vector2f pos = particles[i].shape.getPosition();
            float r = particles[i].shape.getRadius();

            // cek tumbukan dinding window
            if (pos.x - r < 0)
            {
                particles[i].shape.setPosition({r, pos.y});
                particles[i].velocity.x *= -1;
            }
            else if (pos.x + r > WINDOW_WIDTH)
            {
                particles[i].shape.setPosition({static_cast<float>(WINDOW_WIDTH) - r, pos.y});
                particles[i].velocity.x *= -1;
            }

            if (pos.y - r < 0)
            {
                particles[i].shape.setPosition({pos.x, r});
                particles[i].velocity.y *= -1;
            }
            else if (pos.y + r > WINDOW_HEIGHT)
            {
                particles[i].shape.setPosition({pos.x, static_cast<float>(WINDOW_HEIGHT) - r});
                particles[i].velocity.y *= -1;
            }

            // cek tabrkan antar partikel
            // for (size_t j = i + 1; j < particles.size(); ++j)
            // {
            //     resolveCollision(particles[i], particles[j]);
            // }
        }

        window.clear(sf::Color::Black);
        for (const auto &p : particles)
        {
            window.draw(p.shape);
        }
        window.display();
    }

    return 0;
}