#ifndef _TEXTURE_H
#define _TEXTURE_H
#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

class Texture
{
    GLuint textureID = 0;
    int width;
    int height;
    bool partialTransparency;
public:
    Texture();
    Texture(std::string filePath);
    Texture(int width, int height, int mode);  
    GLuint getTextureID();  
    int getWidth();
    int getHeight();
    void bind(GLenum target);
};
#endif