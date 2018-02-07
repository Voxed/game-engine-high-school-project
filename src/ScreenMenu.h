#ifndef _SCREEN_MENU_H
#define _SCREEN_MENU_H

#include "Engine.h"

#include <sstream>
#include <tgmath.h>
#include <chrono>
#include <cstdlib>

class ScreenMenu : public Screen, public ActionListener
{
public:
    ScreenMenu();
    ~ScreenMenu();
    void render(SpriteBatch& batch);
    void update(float delta);
    void init();

    void onAction(Action action, float delta);
};

#endif