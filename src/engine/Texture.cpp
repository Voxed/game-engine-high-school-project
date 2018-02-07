#include "Texture.h"

/**
 * @brief Initialize empty object
 * 
 */
Texture::Texture()
{

}

/**
 * @brief Initialize texture object from file
 * 
 * @param filePath The relative file path to load from
 */
Texture::Texture(std::string filePath)
{
    SDL_Surface * surface = IMG_Load(filePath.c_str());
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    int mode = GL_RGB;
    if(surface->format->BytesPerPixel == 4)
    {
        mode = GL_RGBA;
    }
    width = surface->w;
    height = surface->h;
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

//null(void);

Texture::Texture(std::vector<Color> colors, int width, int height, int mode)
{
    std::vector<float> pixels;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    this->width = width;
    this->height = height;
    int size = width * height;
    for(int i = 0; i < size; i++)
    {
        Color c = colors[i];
        pixels.push_back(c.r);
        pixels.push_back(c.g);
        pixels.push_back(c.b);
        if(mode == GL_RGBA)
            pixels.push_back(c.a);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_FLOAT, &pixels[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

/**
 * @brief Initialize a texture of empty data
 * 
 * @param w The width of the empty texture
 * @param h The height of the empty texture
 * @param mode The mode of the empty texture
 */
Texture::Texture(int w, int h, int mode)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    width = w;
    height = h;
    glTexImage2D(GL_TEXTURE_2D, 0, mode, w, h, 0, mode, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

/**
 * @brief Get the texture id
 * 
 * @return GLuint The texture id
 */
GLuint Texture::getTextureID()
{
    return textureID;
}

/**
 * @brief Get the texture height
 * 
 * @return int The texture height
 */
int Texture::getHeight()
{
    return height;
}

/**
 * @brief Get the texture width
 * 
 * @return int The texture width
 */
int Texture::getWidth()
{
    return width;
}

/**
 * @brief Bind the texture to the target
 * 
 * @param target The texture target to bind to
 */
void Texture::bind(GLenum target)
{
    glActiveTexture( target );
    glBindTexture( GL_TEXTURE_2D, getTextureID() );
}

/**
 * @brief Clear up texture memory
 * 
 */
void Texture::remove()
{
    glDeleteTextures(1, &textureID);
}