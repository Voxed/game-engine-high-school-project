#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "../SpriteBatch.h"
#include "../Actions.h"
#include "World.h"

class World;
class System
{
public:
    World* world;
    virtual void render(SpriteBatch& b) {};
    virtual void update(float delta) {};
    virtual void onAction(Action action, float delta) {};
};

#endif