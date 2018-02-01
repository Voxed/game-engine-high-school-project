#include "Sprite.h"
Sprite::Sprite(Texture *texture, Shader *shader, int x, int y, float subX, float subY, float subW, float subH, float depth, float scaleX, float scaleY,  int anchor_x, int anchor_y, float rotation, bool usePartialTransparency) :
    x (x), y (y), texture( texture ), scaleX( scaleX ), scaleY( scaleY ), shader( shader ), z( depth ), usePartialTransparency( usePartialTransparency ), subX(subX), subY(subY), subW(subW), subH(subH), useSubTexture(true), useTempTexture(false), anchor_x(anchor_x), anchor_y(anchor_y), rotation(rotation)
{

}


Sprite::Sprite(Texture *texture, Shader *shader, int x, int y, float depth, float scaleX, float scaleY, int anchor_x, int anchor_y, float rotation, bool usePartialTransparency) :
    x (x), y (y), texture( texture ), scaleX( scaleX ), scaleY( scaleY ), shader( shader ), z( depth ), usePartialTransparency( usePartialTransparency ), subX(0.0f), subY(0.0f), subW(1.0f), subH(1.0f), useSubTexture(false), useTempTexture(false), anchor_x(anchor_x), anchor_y(anchor_y), rotation(rotation)
{

}

Sprite::Sprite(Texture texture, Shader *shader, int x, int y, float subX, float subY, float subW, float subH, float depth, float scaleX, float scaleY, int anchor_x, int anchor_y, float rotation, bool usePartialTransparency) :
    x (x), y (y), tempTexture( texture ), scaleX( scaleX ), scaleY( scaleY ), shader( shader ), z( depth ), usePartialTransparency( usePartialTransparency ), subX(subX), subY(subY), subW(subW), subH(subH), useSubTexture(true), useTempTexture(true), anchor_x(anchor_x), anchor_y(anchor_y), rotation(rotation)
{
}


Sprite::Sprite(Texture texture, Shader *shader, int x, int y, float depth, float scaleX, float scaleY,  int anchor_x, int anchor_y, float rotation, bool usePartialTransparency) :
    x (x), y (y), tempTexture( texture ), scaleX( scaleX ), scaleY( scaleY ), shader( shader ), z( depth ), usePartialTransparency( usePartialTransparency ), subX(0.0f), subY(0.0f), subW(1.0f), subH(1.0f), useSubTexture(false), useTempTexture(true), anchor_x(anchor_x), anchor_y(anchor_y), rotation(rotation)
{
}


Texture* Sprite::getTexture ()
{
    if(useTempTexture)
    {
        return &tempTexture;
    }
    else
    {
        return texture;
    }
}

Shader* Sprite::getShader()
{
    return shader;
}

void Sprite::getData(std::vector<GLfloat>& vertices, std::vector<GLfloat>& texCoords, std::vector<GLuint>& indices, unsigned int offset)
{
    int texWidth = getTexture()->getWidth();
    int texHeight = getTexture()->getHeight();

    float s = sin(rotation);
    float c = cos(rotation);

    vertices = {
        (float)(x - anchor_x) * c - (texHeight*scaleY*subH+y - anchor_y) * s + anchor_x,               
        (float)(x - anchor_x) * s + (texHeight*scaleY*subH+y - anchor_y) * c + anchor_y, 
        z,
        (float)(x - anchor_x) * c - (float)(y - anchor_y) * s + anchor_x,               
        (float)(x - anchor_x) * s + (float)(y - anchor_y) * c + anchor_y,               
        z,
        (texWidth*scaleX*subW+x - anchor_x) * c - (float)(y - anchor_y) * s + anchor_x,               
        (texWidth*scaleX*subW+x - anchor_x) * s + (float)(y - anchor_y) * c + anchor_y,               
        z,
        (texWidth*scaleX*subW+x - anchor_x) * c - (texHeight*scaleY*subH+y - anchor_y) * s + anchor_x,               
        (texWidth*scaleX*subW+x - anchor_x) * s + (texHeight*scaleY*subH+y - anchor_y) * c + anchor_y,               
        z
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
