#ifndef _PERLIN_H
#define _PERLIN_H

#include "Texture.h"
#include "Color.h"
#include <vector>
#include <glm/gtc/noise.hpp>

class Noise
{
public:
    /**
     * @brief Generate a perlin noise texture
     * 
     * @param height The height of the texture
     * @param width The width of the texture
     * @param a The effect intensity
     * @param seed The seed of the effect
     * @return Texture The perlin noise texture
     */
    static Texture generatePerlin(int height, int width, float a, float seed = 0);
    /**
     * @brief Generate a perlin noise texture
     * 
     * @param height The height of the texture
     * @param width The width of the texture
     * @param a The intensity of the effects
     * @param levels The levels to bind colors to
     * @param level_colors The colors of which to bind
     * @param seed The seed of the effect
     * @return Texture The perlin noise texture
     */
    static Texture generatePerlin(int height, int width, float a, std::vector<float>, std::vector<Color>, float seed = 0);
};

#endif