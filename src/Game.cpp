#include "Game.h"

Game::Game() : core((char *)"Voxel Engine Demo", 720, 480)
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