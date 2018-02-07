#include "Sprite.h"

/**
 * @brief Initialize a sprite object
 * 
 * @param texture Texture
 * @param shader Shader
 * @param x x coordinate
 * @param y y coordinate
 * @param subX Cutout x
 * @param subY Cutout y 
 * @param subW Cutout width
 * @param subH Cutout height
 * @param depth Depth
 * @param scaleX x scale
 * @param scaleY y scale
 * @param anchor_x x Anchor x position
 * @param anchor_y Anchor y position
 * @param rotation Rotation
 * @param color Color
 * @param usePartialTransparency Use pratial transparency 
 */
Sprite::Sprite(Texture *texture, Shader *shader, int x, int y, float subX, float subY, float subW, float subH, float depth, float scaleX, float scaleY,  int anchor_x, int anchor_y, float rotation, Color color, bool usePartialTransparency) :
    x (x), y (y), texture( texture ), scaleX( scaleX ), scaleY( scaleY ), shader( shader ), z( depth ), usePartialTransparency( usePartialTransparency ), subX(subX), subY(subY), subW(subW), subH(subH), useSubTexture(true), useTempTexture(false), anchor_x(anchor_x), anchor_y(anchor_y), rotation(rotation), color(color)
{

}

/**
 * @brief Initialize a sprite object
 * 
 */
Sprite::Sprite(Texture *texture, Shader *shader, int x, int y, float depth, float scaleX, float scaleY, int anchor_x, int anchor_y, float rotation, Color color, bool usePartialTransparency) :
    x (x), y (y), texture( texture ), scaleX( scaleX ), scaleY( scaleY ), shader( shader ), z( depth ), usePartialTransparency( usePartialTransparency ), subX(0.0f), subY(0.0f), subW(1.0f), subH(1.0f), useSubTexture(false), useTempTexture(false), anchor_x(anchor_x), anchor_y(anchor_y), rotation(rotation), color(color)
{

}

/**
 * @brief Initialize a sprite object
 * 
 * @param texture Texture
 * @param shader Shader
 * @param x x coordiante
 * @param y y coordinate
 * @param subX Cutout x
 * @param subY Cutout y
 * @param subW Cutout width
 * @param subH Cutout height
 * @param depth Depth
 * @param scaleX x scale
 * @param scaleY y scale
 * @param anchor_x Anchor x position
 * @param anchor_y Anchor y position
 * @param rotation Rotation
 * @param color Color
 * @param usePartialTransparency Use partial transparency
 */
Sprite::Sprite(Texture texture, Shader *shader, int x, int y, float subX, float subY, float subW, float subH, float depth, float scaleX, float scaleY, int anchor_x, int anchor_y, float rotation, Color color, bool usePartialTransparency) :
    x (x), y (y), tempTexture( texture ), scaleX( scaleX ), scaleY( scaleY ), shader( shader ), z( depth ), usePartialTransparency( usePartialTransparency ), subX(subX), subY(subY), subW(subW), subH(subH), useSubTexture(true), useTempTexture(true), anchor_x(anchor_x), anchor_y(anchor_y), rotation(rotation), color(color)
{
}

/**
 * @brief Initialize a spirte object
 * 
 */
Sprite::Sprite(Texture texture, Shader *shader, int x, int y, float depth, float scaleX, float scaleY,  int anchor_x, int anchor_y, float rotation, Color color, bool usePartialTransparency) :
    x (x), y (y), tempTexture( texture ), scaleX( scaleX ), scaleY( scaleY ), shader( shader ), z( depth ), usePartialTransparency( usePartialTransparency ), subX(0.0f), subY(0.0f), subW(1.0f), subH(1.0f), useSubTexture(false), useTempTexture(true), anchor_x(anchor_x), anchor_y(anchor_y), rotation(rotation), color(color)
{
}

/**
 * @brief Get the texture
 * 
 * @return Texture* A pointer to the texture
 */
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

/**
 * @brief Get the shader
 * 
 * @return Shader* A pointer to the shader
 */
Shader* Sprite::getShader()
{
    return shader;
}

/**
 * @brief Get the sprite data
 * 
 * @param vertices A reference to a vertex vector
 * @param texCoords A reference to a texture coordinate vector
 * @param indices A reference to an index vector
 * @param colors A reference to a color vector
 * @param offset The index offset
 */
void Sprite::getData(std::vector<GLfloat>& vertices, std::vector<GLfloat>& texCoords, std::vector<GLuint>& indices, std::vector<GLfloat>& colors, unsigned int offset)
{
    int texWidth = getTexture()->getWidth();
    int texHeight = getTexture()->getHeight();

    float s = sin(rotation);
    float c = cos(rotation);

    colors = {
        color.r, color.g, color.b, color.a,
        color.r, color.g, color.b, color.a,
        color.r, color.g, color.b, color.a,
        color.r, color.g, color.b, color.a
    };
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
