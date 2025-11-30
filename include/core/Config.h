/**
 * @file Config.h
 * @author Yuke Brilliant H (yukebrilliant@gmail.com)
 * @brief Global configuration constants for the collision simulation
 * @memberof FP Struktur Data dan Algoritma
 */

#ifndef CONFIG_H
#define CONFIG_H

namespace Config
{
    // Window dimensions
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;

    // Particle settings
    const unsigned int PARTICLE_COUNT = 30;
    const float MIN_PARTICLE_RADIUS = 20.0f;
    const float MAX_PARTICLE_RADIUS = 50.0f;

    // Physics settings
    const float MIN_VELOCITY = -3.0f;
    const float MAX_VELOCITY = 3.0f;
    const unsigned int TARGET_FPS = 60;
}

#endif // CONFIG_H
