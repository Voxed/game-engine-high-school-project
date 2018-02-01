#ifndef _CORE_H
#define _CORE_H
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

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
    int initWindow(char * title, int width, int height);
    int initGL();
    bool error = false;
    Screen * scr;
    bool started = false;
    float fps;
public:
    Core(char * title, int width, int height);
    ~Core();
    bool hasError();
    bool hasStarted();
    int start();
    void setScreen(Screen * scr);
    Screen * getScreen();
    int getFPS();
    int getWidth();
    int getHeight();
};

#include "Screen.h"

#endif