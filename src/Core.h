#ifndef _CORE_H
#define _CORE_H
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>

#include "Graphics.h"

class Core
{
    SDL_Window * window;
    SDL_GLContext context;
    int initSDL();
    int initWindow();
    int initGL();
    bool error;
public:
    Core();
    ~Core();
    bool hasError();
    int start();
};
#endif