#ifndef _SCREEN_MENU_H
#define _SCREEN_MENU_H

#include "Engine.h"

class ScreenMenu : public Screen, public ActionListener
{
    Texture text;
    Texture font;
    Shader shad;
public:
    ScreenMenu();
    void render(SpriteBatch& batch);
    void update(float delta);
    void init();

    void onAction(Action action);
};

#endif