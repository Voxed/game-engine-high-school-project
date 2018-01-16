#ifndef _SCREEN_MENU_H
#define _SCREEN_MENU_H

#include "Engine.h"

class ScreenMenu : public Screen, public ActionListener
{
    
public:
    ScreenMenu();
    void render(SpriteBatch& batch);
    void update(float delta);

    void onAction(Action action);
};

#endif