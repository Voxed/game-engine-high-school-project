#ifndef _SPRITE_H
#define _SPRITE_H
#include <GL/glew.h>
#include <vector>
#include "Texture.h"
#include "Shader.h"
#include <cmath>
#include <algorithm>

class Sprite
{
    Texture *texture;
    Texture tempTexture;
    Shader *shader;
public:
    const bool useTempTexture;
    const int x;
    const int y;
    const float z;
    const float scaleX;
    const float scaleY;
    const bool usePartialTransparency;
    const float subX, subY, subW, subH;
    const bool useSubTexture;
    const int anchor_x;
    const int anchor_y;
    const float rotation;
    const Color color;

    
    Sprite(Texture *texture, Shader *shader, int x, int y, float depth = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f, int anchor_x = 0, int anchor_y = 0, float rotation = 0.0f, Color color = Color(1,1,1), bool usePartialTransparency = false);
    Sprite(Texture *texture, Shader *shader, int x, int y, float subX, float subY, float subW, float subH, float depth = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f, int anchor_x = 0, int anchor_y = 0, float rotation = 0.0f, Color color = Color(1,1,1), bool usePartialTransparency = false);
    Sprite(Texture tempTexture, Shader *shader, int x, int y, float depth = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f, int anchor_x = 0, int anchor_y = 0, float rotation = 0.0f, Color color = Color(1,1,1), bool usePartialTransparency = false);
    Sprite(Texture tempTexture, Shader *shader, int x, int y, float subX, float subY, float subW, float subH, float depth = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f, int anchor_x = 0, int anchor_y = 0, float rotation = 0.0f, Color color = Color(1,1,1), bool usePartialTransparency = false);
    void render(std::vector<Sprite*> sprites);

    void getData(std::vector<GLfloat>& vertices, std::vector<GLfloat>& texCoords, std::vector<GLuint>& indices, std::vector<GLfloat>& colors, unsigned int offset);

    Texture* getTexture();
    Shader* getShader();
};

#endif