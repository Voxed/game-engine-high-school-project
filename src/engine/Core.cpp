#include "Core.h"

/**
 * @brief Initialize the engine core
 * 
 * @param title The title of the window
 * @param width The width of the window
 * @param height The height of the window
 */
Core::Core(char * title, int width, int height) 
{
    int sdlErrorCode = Core::initSDL();
    if( sdlErrorCode == 0 )
    {
        int windowErrorCode = Core::initWindow(title, width, height);
        if( windowErrorCode == 0 )
        {
            int glErrorCode = Core::initGL();
            if( glErrorCode == 0)
            {
                printf( "Core initialization complete\n" );
                return;
            }
        }
    }
    error = true;
}

/**
 * @brief Clean up
 * 
 */
Core::~Core()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/**
 * @brief Returns initialization error
 * 
 * @return true Initialization successful
 * @return false Initialization failed
 */
bool Core::hasError()
{
    return error;
}

/**
 * @brief Initialize SDL
 * 
 * @return int Zero if initialization is successful
 */
int Core::initSDL()
{
    int errorCode = SDL_Init( SDL_INIT_VIDEO );
    if( errorCode != 0 )
    {
        printf( "Could not initialize SDL!\nError: %s\n", SDL_GetError() );
        return -1;
    }
    return 0;
}

/**
 * @brief Initialize window
 * 
 * @return int Zero if initialization is successful
 */
int Core::initWindow(char * title, int width, int height)
{
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_OPENGL
    );
    if( window == NULL )
    {
        printf( "Could not initialize window!\nError: %s\n", SDL_GetError() );
        return -1;
    }
    return 0;
}

/**
 * @brief Initialize OpenGL
 * 
 * @return int Zero if initialization is successful
 */
int Core::initGL()
{
    context = SDL_GL_CreateContext( window );
    if( context == NULL )
    {
        printf( "Could not initialize GL context!\nError: %s\n", SDL_GetError() );
        return -1;
    }

    GLenum glewError = glewInit();
    if( glewError != GLEW_NO_ERROR )
    {
        printf( "Could not intialize GLEW!\nError: %s\n", glewGetErrorString(glewError));
        return -1;
    }

    int flags = IMG_INIT_PNG;
    int inittedFlags = IMG_Init( flags );
    if( inittedFlags&flags != flags )
    {
        printf( "Could not initialize SDL-image!\nError: %s\n", IMG_GetError());
        return -1;
    }

    return 0;
}

/**
 * @brief Starts the game
 * 
 * @return int Exist status
 */
int Core::start()
{
    Logic l = Logic(this);
    Graphics g = Graphics(this, l);
    started = true;

    //Main loop :)
    bool quit = false;
    SDL_Event e;
    std::vector<int> held_keys = std::vector<int>();
    std::vector<int> held_mousebuttons = std::vector<int>();

    float lastKeyUpdate = SDL_GetPerformanceCounter();
    float lastLogicUpdate = SDL_GetPerformanceCounter();
    float lastMouseUpdate = SDL_GetPerformanceCounter();
    float lastRender = SDL_GetPerformanceCounter();


    while( !quit )
    {
        while( SDL_PollEvent(&e) )
        {
            switch( e.type ) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if(std::find(held_keys.begin(), held_keys.end(), e.key.keysym.sym) == held_keys.end())
                    {
                        for(auto const& action : Keyboard::getActions(e.key.keysym.sym))
                        {
                            Action a;
                            a.action = action;
                            a.type = ActionType::KEYBOARD;
                            a.state = ActionState::PRESSED;
                            Actions::call(a, 1.0f);
                        }
                        held_keys.push_back(e.key.keysym.sym);
                    }
                    break;
                case SDL_KEYUP:
                    for(auto const& action : Keyboard::getActions(e.key.keysym.sym))
                    {
                        Action a; 
                        a.type = ActionType::KEYBOARD;
                        a.state = ActionState::RELEASED;
                        Actions::call(a, 1.0f);
                    }
                    held_keys.erase(std::remove(held_keys.begin(), held_keys.end(), e.key.keysym.sym), held_keys.end()); 
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    for(auto const& action : Mouse::getActions(e.button.button))
                    {
                        Action a; 
                        a.type = ActionType::MOUSE;
                        a.state = ActionState::PRESSED;
                        Actions::call(a, 1.0f);
                    }
                    held_mousebuttons.push_back(e.button.button);
                    break;
                case SDL_MOUSEBUTTONUP:
                    for(auto const& action : Mouse::getActions(e.button.button))
                    {
                        Action a; 
                        a.type = ActionType::MOUSE;
                        a.state = ActionState::RELEASED;
                        Actions::call(a, 1.0f);
                    }
                    held_mousebuttons.erase(std::remove(held_mousebuttons.begin(), held_mousebuttons.end(), e.button.button), held_mousebuttons.end()); 
                    break;
            }
        }
        for(auto key : held_keys)
        {   
            for(auto const& action : Keyboard::getActions(key))
            {
                Action a;
                a.action = action;
                a.type = ActionType::KEYBOARD;
                a.state = ActionState::HELD;
                Actions::call(a, (SDL_GetPerformanceCounter() - lastKeyUpdate)/SDL_GetPerformanceFrequency());
            }
        }
        lastKeyUpdate = SDL_GetPerformanceCounter();
        for(auto mouse : held_mousebuttons)
        {
            for(auto const& action : Mouse::getActions(e.button.button))
            {
                Action a; 
                a.type = ActionType::MOUSE;
                a.state = ActionState::HELD;
                Actions::call(a, (SDL_GetPerformanceCounter() - lastMouseUpdate)/SDL_GetPerformanceFrequency());
            }
        }
        lastMouseUpdate = SDL_GetPerformanceCounter();
        l.update((SDL_GetPerformanceCounter() - lastLogicUpdate)/SDL_GetPerformanceFrequency());
        lastLogicUpdate = SDL_GetPerformanceCounter();

        g.render();
        fps = 1.0f/((SDL_GetPerformanceCounter() - lastRender)/SDL_GetPerformanceFrequency());
        lastRender = SDL_GetPerformanceCounter();

        SDL_GL_SwapWindow(window);
    }
}

/**
 * @brief Change screen
 * 
 * @param The screen to be used
 */
void Core::setScreen(Screen * scr)
{
    scr->core = this;
    this->scr = scr;
}

/**
 * @brief Get the current screen
 * 
 * @return Screen* A pointer to the current screen
 */
Screen * Core::getScreen()
{
    return scr;
}

/**
 * @brief Returns if the program has been started.
 * 
 * Useful for if you wan't functions to work in screen initializations
 * 
 * @return true Program has not started
 * @return false Program has started
 */
bool Core::hasStarted()
{
    return started;
}

/**
 * @brief Returns the current fps
 * 
 * @return int The current fps
 */
int Core::getFPS() 
{
    return fps;
}

/**
 * @brief Returns the window width
 * 
 * @return int Window width
 */
int Core::getWidth()
{
    int w;
    SDL_GetWindowSize(window, &w, NULL);
    return w;
}

/**
 * @brief Returns the window height
 * 
 * @return int Window height
 */
int Core::getHeight()
{
    int h;
    SDL_GetWindowSize(window, NULL, &h);
    return h;
}