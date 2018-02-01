#ifndef _SCREEN_MENU_H
#define _SCREEN_MENU_H

#include "Engine.h"

#include <sstream>
#include <tgmath.h>
#include <chrono>

class ScreenMenu : public Screen, public ActionListener
{
    Texture fontTexture;
    Texture planetTexture;
    Texture cloudsTexture;
    SpriteFont spritefont;
    Shader defaultShader;
    Shader toonShader;
    Mesh sphereMesh;

    float planetRotation;
    bool isRotating = false;
    float rotationVelocity;
public:
    ScreenMenu();
    ~ScreenMenu();
    void render(SpriteBatch& batch);
    void update(float delta);
    void init();

    void onAction(Action action, float delta);
};

#endif