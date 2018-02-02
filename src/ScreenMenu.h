#ifndef _SCREEN_MENU_H
#define _SCREEN_MENU_H

#include "Engine.h"

#include <sstream>
#include <tgmath.h>
#include <chrono>
#include <cstdlib>

class ScreenMenu : public Screen, public ActionListener
{
    Texture fontTexture;
    Texture planetTexture;
    Texture cloudsTexture;
    Texture starTexture;
    SpriteFont spritefont;
    Shader defaultShader;
    Shader toonShader;
    Mesh sphereMesh;
    struct Star
    {
        float x, y;
        float v;
    };
    std::vector<Star> stars;

    float planetRotation;
    bool isRotating = false;
    float rotationVelocity = 0;
public:
    ScreenMenu();
    ~ScreenMenu();
    void render(SpriteBatch& batch);
    void update(float delta);
    void init();

    void onAction(Action action, float delta);
};

#endif