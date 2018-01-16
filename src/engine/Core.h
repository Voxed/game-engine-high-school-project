#ifndef _CORE_H
#define _CORE_H
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include <algorithm>

#include "Logic.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Actions.h"
#include "Mouse.h"

class Screen;
class Core
{
    SDL_Window * window;
    SDL_GLContext context;
    int initSDL();
    int initWindow();
    int initGL();
    bool error;
    Screen * scr;
    bool started = false;
public:
    Core();
    ~Core();
    bool hasError();
    bool hasStarted();
    int start();
    void setScreen(Screen * scr);
    Screen * getScreen();
};

#include "Screen.h"

#endif