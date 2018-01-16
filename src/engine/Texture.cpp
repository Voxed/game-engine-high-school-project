#include "Texture.h"

Texture::Texture()
{

}

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

GLuint Texture::getTextureID()
{
    return textureID;
}

int Texture::getHeight()
{
    return height;
}
int Texture::getWidth()
{
    return width;
}

void Texture::bind(GLenum target)
{
    glActiveTexture( target );
    glBindTexture( GL_TEXTURE_2D, getTextureID() );
}
