#include "Noise.h"

Texture Noise::generatePerlin(int height, int width, float a)
{
    std::vector<Color> colors;
    for(int w = 0; w < width; w++)
    {
        for(int h = 0; h < height; h++)
        {
            float c = glm::perlin(glm::vec2(w/(width/a),h/(height/a)), glm::vec2(a)) + 0.5f;

            colors.push_back(Color(c, c, c));
        }
    }
    return Texture(colors, height, width, GL_RGB);
}

Texture Noise::generatePerlin(int height, int width, float a, std::vector<float> levels, std::vector<Color> level_colors)
{
    std::vector<Color> colors;
    for(int w = 0; w < width; w++)
    {
        for(int h = 0; h < height; h++)
        {
            float c = glm::perlin(glm::vec2(w/(width/a),h/(height/a)), glm::vec2(a))/2 + 0.5f;
            
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
    }
    return Texture(colors, height, width, GL_RGBA);
}