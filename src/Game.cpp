#include "Game.h"

Game::Game()
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