#ifndef _SCREEN_MENU_H
#define _SCREEN_MENU_H

#include "Engine.h"

class ScreenMenu : public Screen
{

public:
    ScreenMenu();
    void render(SpriteBatch& batch);
    void update(float delta);
};

#endif