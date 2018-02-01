#ifndef _SCREEN_H
#define _SCREEN_H

#include "SpriteBatch.h"
#include "Color.h"
#include "Core.h"

class Screen
{
public:
    virtual void render(SpriteBatch& batch);
    virtual void update(float delta);
    void setBackgroundColor(Color color);
    Color getBackgroundColor();
    Core* core;
    Color backgroundColor;
};

#endif