#ifndef _SPRITE_H
#define _SPRITE_H
#include <GL/glew.h>
#include <vector>
#include "Texture.h"
#include "Shader.h"

class Sprite
{
    Texture *texture;
    Shader *shader;
public:
    static std::vector<GLfloat> VERTICES;
    static std::vector<GLuint> INDICES;
    static std::vector<GLfloat> TEX_COORDS;

    const int x;
    const int y;
    const float z;
    const float scaleX;
    const float scaleY;
    const bool usePartialTransparency;
    const float subX, subY, subW, subH;
    const bool useSubTexture;
    
    Sprite(Texture *texture, Shader *shader, int x, int y, float depth = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f, bool usePartialTransparency = false);
    Sprite(Texture *texture, Shader *shader, int x, int y, float subX, float subY, float subW, float subH, float depth = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f, bool usePartialTransparency = false);
    void render(std::vector<Sprite*> sprites);

    void getData(std::vector<GLfloat>& vertices, std::vector<GLfloat>& texCoords, std::vector<GLuint>& indices, unsigned int offset);

    Texture* getTexture();
    Shader* getShader();
};

#endif