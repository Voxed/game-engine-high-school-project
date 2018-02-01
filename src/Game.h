#ifndef _GAME_H
#define _GAME_H

#include "Engine.h"
#include "ScreenMenu.h"

class Game
{
    Core core;
    ScreenMenu menu;
public:
    Game();
    bool hasError();
    int run();

};

#endif