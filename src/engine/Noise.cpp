#include "Noise.h"

/**
 * @brief Generate a perlin noise texture
 * 
 * @param height The height of the texture
 * @param width The width of the texture
 * @param a The effect intensity
 * @param seed The seed of the effect
 * @return Texture The perlin noise texture
 */
Texture Noise::generatePerlin(int height, int width, float a, float seed)
{
    if(seed == 0)
        seed = SDL_GetPerformanceCounter()%9999; //yes i know this is ugly LOL
    std::vector<Color> colors;
    float c_max = 0;
    float c_min = 0;
    std::vector<float> heightmap;
    for(int w = 0; w < width; w++)
    {
        for(int h = 0; h < height; h++)
        {
            float c = glm::perlin(glm::vec2((w+seed)/(width/a),(h+seed)/(height/a)), glm::vec2(a)) + 0.5f;
            
            if(c < c_min)   
                c_min = c;
            else if(c > c_max)
                c_max = c;

            heightmap.push_back(c);
        }
    }
    c_max = c_max - c_min;
    for(int i = 0; i < heightmap.size(); i++)
    {
        float c = heightmap[i];
        c = (c-c_min)/c_max;

        Color color = Color(c, c, c);

        colors.push_back(color);
    }
}

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
Texture Noise::generatePerlin(int height, int width, float a, std::vector<float> levels, std::vector<Color> level_colors, float seed)
{
    if(seed == 0)
        seed = SDL_GetPerformanceCounter()%9999; //but atleast it works :)
    std::vector<Color> colors;
    float c_max = 0;
    float c_min = 0;
    std::vector<float> heightmap;
    for(int w = 0; w < width; w++)
    {
        for(int h = 0; h < height; h++)
        {
            float c = glm::perlin(glm::vec2((w+seed)/(width/a),(h+seed)/(height/a)), glm::vec2(a)) + 0.5f;
            
            if(c < c_min)   
                c_min = c;
            else if(c > c_max)
                c_max = c;

            heightmap.push_back(c);
        }
    }
    c_max = c_max - c_min;
    //normalize
    for(int i = 0; i < heightmap.size(); i++)
    {
        float c = heightmap[i];
        c = (c-c_min)/c_max;

        Color color = Color(c, c, c);

        for(int i = 0; i < levels.size(); i++)
        {
            if (c <= levels[i])
            {
                color = level_colors[i];
                break;
            }
        }

        colors.push_back(color);
    }
    return Texture(colors, height, width, GL_RGBA);
}