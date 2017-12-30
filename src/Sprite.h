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
    static GLfloat VERTICES[8];
    static GLfloat INDICES[6];
    static GLfloat TEX_COORDS[8];

    const int x;
    const int y;
    const float z;
    const float scaleX;
    const float scaleY;

    Sprite(Texture *texture, Shader *shader, int x, int y, float depth, float scaleX, float scaleY);
    void render(std::vector<Sprite*> sprites);

    Texture* getTexture();
    Shader* getShader();
};

#endif