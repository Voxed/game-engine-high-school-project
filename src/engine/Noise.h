#ifndef _PERLIN_H
#define _PERLIN_H

#include "Texture.h"
#include "Color.h"
#include <vector>
#include <glm/gtc/noise.hpp>

class Noise
{
public:
    static Texture generatePerlin(int height, int width, float a, float seed = 0);
    static Texture generatePerlin(int height, int width, float a, std::vector<float>, std::vector<Color>, float seed = 0);
};

#endif