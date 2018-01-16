#include "Game.h"

int main()
{
    Game game;
    if( !game.hasError() )
    {
        return game.run();
    }
    return -1;
}