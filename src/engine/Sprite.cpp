#include "Sprite.h"

std::vector<GLfloat> Sprite::VERTICES = {
    0.0, 1.0,
    0.0, 0.0,
    1.0, 0.0,
    1.0, 1.0
};
std::vector<GLfloat> Sprite::TEX_COORDS = {
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f
};
std::vector<GLuint> Sprite::INDICES = {
    0,1,2,
    2,0,3
};

Sprite::Sprite(Texture *texture, Shader *shader, int x, int y, float subX, float subY, float subW, float subH, float depth, float scaleX, float scaleY, bool usePartialTransparency) :
    x (x), y (y), texture( texture ), scaleX( scaleX ), scaleY( scaleY ), shader( shader ), z( depth ), usePartialTransparency( usePartialTransparency ), subX(subX), subY(subY), subW(subW), subH(subH), useSubTexture(true)
{

}


Sprite::Sprite(Texture *texture, Shader *shader, int x, int y, float depth, float scaleX, float scaleY, bool usePartialTransparency) :
    x (x), y (y), texture( texture ), scaleX( scaleX ), scaleY( scaleY ), shader( shader ), z( depth ), usePartialTransparency( usePartialTransparency ), subX(0.0f), subY(0.0f), subW(1.0f), subH(1.0f), useSubTexture(false)
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

void Sprite::getData(std::vector<GLfloat>& vertices, std::vector<GLfloat>& texCoords, std::vector<GLuint>& indices, unsigned int offset)
{
    int texWidth = texture->getWidth();
    int texHeight = texture->getHeight();
    vertices = {
        (float)x,               texHeight*scaleY*subH+y, z,
        (float)x,               (float)y,                z,
        texWidth*scaleX*subW+x, (float)y,                z,
        texWidth*scaleX*subW+x, texHeight*scaleY*subH+y, z
    };
    texCoords = {
        subX        , subY + subH,
        subX        , subY,
        subX + subW, subY,
        subX + subW, subY + subH
    };
    indices = {
        0+offset,1+offset,2+offset,
        2+offset,0+offset,3+offset
    };
}
