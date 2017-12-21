#ifndef _TEXTURE_H
#define _TEXTURE_H
#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

class Texture
{
    GLuint textureID;
public:
    Texture();
    Texture(std::string filePath);  
    GLuint getTextureID();  
};
#endif