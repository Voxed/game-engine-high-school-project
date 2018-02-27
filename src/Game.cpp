#include "Game.h"

Game::Game() : core((char *)"GALAXY ONE ARCADE MACHINE", 720*2, 480*2)
{
}

bool Game::hasError()
{
    return core.hasError();
}

int Game::run()
{
    core.setScreen(&menu);
    return core.start();
    
}