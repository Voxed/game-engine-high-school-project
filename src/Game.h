#ifndef _GAME_H
#define _GAME_H

#include "Engine.h"
#include "GameScreen.h"

class Game
{
    Core core;
    GameScreen menu;
public:
    Game();
    bool hasError();
    int run();

};

#endif