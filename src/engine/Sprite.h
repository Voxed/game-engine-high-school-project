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

    /**
     * @brief Initialize a sprite object
     * 
     * @param texture Texture
     * @param shader Shader
     * @param x x coordiante
     * @param y y coordinate
     * @param depth Depth
     * @param scaleX x scale
     * @param scaleY y scale
     * @param anchor_x Anchor x position
     * @param anchor_y Anchor y position
     * @param rotation Rotation
     * @param color Color
     * @param usePartialTransparency Use partial transparency
     */
    Sprite(Texture *texture, Shader *shader, int x, int y, float depth = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f, int anchor_x = 0, int anchor_y = 0, float rotation = 0.0f, Color color = Color(1,1,1), bool usePartialTransparency = false);
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
    Sprite(Texture *texture, Shader *shader, int x, int y, float subX, float subY, float subW, float subH, float depth = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f, int anchor_x = 0, int anchor_y = 0, float rotation = 0.0f, Color color = Color(1,1,1), bool usePartialTransparency = false);    
    /**
     * @brief Initialize a sprite object using a temporary texture
     * 
     * @param texture Texture
     * @param shader Shader
     * @param x x coordiante
     * @param y y coordinate
     * @param depth Depth
     * @param scaleX x scale
     * @param scaleY y scale
     * @param anchor_x Anchor x position
     * @param anchor_y Anchor y position
     * @param rotation Rotation
     * @param color Color
     * @param usePartialTransparency Use partial transparency
     */
    Sprite(Texture tempTexture, Shader *shader, int x, int y, float depth = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f, int anchor_x = 0, int anchor_y = 0, float rotation = 0.0f, Color color = Color(1,1,1), bool usePartialTransparency = false);
    /**
     * @brief Initialize a sprite object using a temporary texture
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
    Sprite(Texture tempTexture, Shader *shader, int x, int y, float subX, float subY, float subW, float subH, float depth = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f, int anchor_x = 0, int anchor_y = 0, float rotation = 0.0f, Color color = Color(1,1,1), bool usePartialTransparency = false);
    void render(std::vector<Sprite*> sprites);
    /**
     * @brief Get the sprite data
     * 
     * @param vertices A reference to a vertex vector
     * @param texCoords A reference to a texture coordinate vector
     * @param indices A reference to an index vector
     * @param colors A reference to a color vector
     * @param offset The index offset
     */
    void getData(std::vector<GLfloat>& vertices, std::vector<GLfloat>& texCoords, std::vector<GLuint>& indices, std::vector<GLfloat>& colors, unsigned int offset);
    Texture* getTexture();
    /**
     * @brief Get the shader
     * 
     * @return Shader* A pointer to the shader
     */
    Shader* getShader();
};

#endif