#include "Sprite.h"

GLfloat Sprite::VERTICES[8] = {
    0.0, 0.0,
    0.0, 1.0,
    1.0, 1.0,
    1.0, 0.0
};
GLfloat Sprite::TEX_COORDS[8] = {
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f
};
GLfloat Sprite::INDICES[6] = {
    0,1,2,
    2,0,3
};

Sprite::Sprite(Texture *texture, Shader *shader, int x, int y, float depth, float scaleX, float scaleY) :
    x (x), y (y), texture( texture ), scaleX( scaleX ), scaleY( scaleY ), shader( shader ), z( depth )
{

}

Texture* Sprite::getTexture ()
{
    return texture;
}

Shader* Sprite::getShader()
{
    return shader;
}


