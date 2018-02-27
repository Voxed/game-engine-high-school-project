#ifndef _SCREEN_MENU_H
#define _SCREEN_MENU_H

#include "Engine.h"
#include <sstream>
#include <tgmath.h>
#include <chrono>
#include <cstdlib>

#include "PlayerSystem.h"

class GameScreen : public Screen, public ActionListener
{
    World world;
    Texture fontTexture;
    Texture logoTexture;
    SpriteFont spriteFont;
    Shader defaultShader;
    float dpi = 3.0f;
public:
    GameScreen();
    ~GameScreen();
    void render(SpriteBatch& batch);
    void update(float delta);
    void init();

    void onAction(Action action, float delta);
};

#endif