#ifndef _TEXTURE_H
#define _TEXTURE_H
#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <vector>
#include <GL/glew.h>

#include "Color.h"

class Texture
{
    GLuint textureID = 0;
    int width;
    int height;
    bool partialTransparency;
public:
    /**
     * @brief Initialize empty object
     * 
     */
    Texture();
    Texture(std::vector<Color> colors, int width, int height, int mode);
    /**
     * @brief Initialize texture object from file
     * 
     * @param filePath The relative file path to load from
     */
    Texture(std::string filePath);
    /**
     * @brief Initialize a texture of empty data
     * 
     * @param width The width of the empty texture
     * @param height The height of the empty texture
     * @param mode The mode of the empty texture
     */
    Texture(int width, int height, int mode);  
    /**
     * @brief Get the texture id
     * 
     * @return GLuint The texture id
     */
    GLuint getTextureID();  
    /**
     * @brief Get the texture height
     * 
     * @return int The texture height
     */
    int getWidth();
    /**
     * @brief Get the texture width
     * 
     * @return int The texture width
     */
    int getHeight();
    /**
     * @brief Bind the texture to the target
     * 
     * @param target The texture target to bind to
     */
    void bind(GLenum target);
    /**
     * @brief Clear up texture memory
     * 
     */
    void remove();
};
#endif