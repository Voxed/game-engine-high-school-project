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
    /**
     * @brief Initialize SDL
     * 
     * @return int Zero if initialization is successful
     */
    int initSDL();
    /**
     * @brief Initialize window
     * 
     * @return int Zero if initialization is successful
     */
    int initWindow(char * title, int width, int height);
    /**
     * @brief Initialize OpenGL
     * 
     * @return int Zero if initialization is successful
     */
    int initGL();
    bool error = false;
    Screen * scr;
    bool started = false;
    float fps;
public:
    /**
     * @brief Initialize the engine core
     * 
     * @param title The title of the window
     * @param width The width of the window
     * @param height The height of the window
     */
    Core(char * title, int width, int height);
    /**
     * @brief Clean up
     * 
     */
    ~Core();
    /**
     * @brief Returns initialization error
     * 
     * @return true Initialization successful
     * @return false Initialization failed
     */
    bool hasError();
    /**
     * @brief Returns if the program has been started.
     * 
     * Useful for if you wan't functions to work in screen initializations
     * 
     * @return true Program has not started
     * @return false Program has started
     */
    bool hasStarted();
    /**
     * @brief Starts the game
     * 
     * @return int Exist status
     */
    int start();
    /**
     * @brief Change screen
     * 
     * @param The screen to be used
     */
    void setScreen(Screen * scr);
    /**
     * @brief Get the current screen
     * 
     * @return Screen* A pointer to the current screen
     */
    Screen * getScreen();
    /**
     * @brief Returns the current fps
     * 
     * @return int The current fps
     */
    int getFPS();
    /**
     * @brief Returns the window width
     * 
     * @return int Window width
     */
    int getWidth();
    /**
     * @brief Returns the window height
     * 
     * @return int Window height
     */
    int getHeight();
};

#include "Screen.h"

#endif