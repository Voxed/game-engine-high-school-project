#ifndef _PLAYER_SYSTEM_H
#define _PLAYER_SYSTEM_H

#include <algorithm>

#include "Engine.h"
#include "PlayerComponent.h"
#include "TransformComponent.h"

class PlayerSystem : public System
{
public:
    void render(SpriteBatch& b);
    void update(float delta);
    void onAction(Action action, float delta);
};

#endif