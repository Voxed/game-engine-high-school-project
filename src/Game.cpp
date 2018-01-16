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
    ScreenMenu menu;
    core.setScreen(&menu);
    return core.start();
}