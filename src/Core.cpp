#include "Core.h"

Core::Core() 
{
    int sdlErrorCode = Core::initSDL();
    if( sdlErrorCode == 0 )
    {
        int windowErrorCode = Core::initWindow();
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

Core::~Core()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Core::hasError()
{
    return error;
}

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

int Core::initWindow()
{
    window = SDL_CreateWindow(
        "Title",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_OPENGL
    );
    if( window == NULL )
    {
        printf( "Could not initialize window!\nError: %s\n", SDL_GetError() );
        return -1;
    }
    return 0;
}

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

int Core::start()
{
    Logic l = Logic();
    Graphics g = Graphics(l);

    //Main loop :)
    bool quit = false;
    SDL_Event e;
    while( !quit )
    {
        while( SDL_PollEvent(&e) )
        {
            if( e.type == SDL_QUIT )
                quit = true;
        }

        g.render();
        SDL_GL_SwapWindow(window);

        SDL_Delay(60/1000);
    }
}