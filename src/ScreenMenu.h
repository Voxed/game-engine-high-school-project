#ifndef _SCREEN_MENU_H
#define _SCREEN_MENU_H

#include "Engine.h"

#include <sstream>
#include <tgmath.h>

class ScreenMenu : public Screen, public ActionListener
{
    Texture font;
    SpriteFont sf;
    Shader shad;
public:
    ScreenMenu();
    void render(SpriteBatch& batch);
    void update(float delta);
    void init();

    void onAction(Action action);
};

#endif