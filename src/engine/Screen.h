#ifndef _SCREEN_H
#define _SCREEN_H

#include "SpriteBatch.h"
#include "Color.h"
#include "Core.h"

class Screen
{
public:
    /**
     * @brief The render event
     * 
     * @param batch The batch that will be rendered to the screen in the core
     */
    virtual void render(SpriteBatch& batch);
    /**
     * @brief The update event
     * 
     * @param delta The delta speed of which the program is moving (in seconds)
     */
    virtual void update(float delta);
    Core* core;
    Color backgroundColor;
};

#endif