#ifndef _SCREEN_MENU_H
#define _SCREEN_MENU_H

#include "Engine.h"

#include <sstream>

class ScreenMenu : public Screen, public ActionListener
{
    Texture text;
    Texture text2;
    Texture font;
    SpriteFont sf;
    Shader shad;
    float x;
    int fps;
public:
    ScreenMenu();
    void render(SpriteBatch& batch);
    void update(float delta);
    void init();

    void onAction(Action action);
};

#endif