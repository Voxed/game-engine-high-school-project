#ifndef _SCREEN_MENU_H
#define _SCREEN_MENU_H

#include "Engine.h"

#include <sstream>
#include <tgmath.h>
#include <chrono>

class ScreenMenu : public Screen, public ActionListener
{
    Texture font;
    Texture planet;
    Texture cloud;
    SpriteFont sf;
    Shader shad;
    Shader shad2;
    Mesh mesh;
    float rot;
    float scale;
    
    bool rotating = false;
    float rot_velocity;
public:
    ScreenMenu();
    ~ScreenMenu();
    void render(SpriteBatch& batch);
    void update(float delta);
    void init();

    void onAction(Action action, float delta);
};

#endif