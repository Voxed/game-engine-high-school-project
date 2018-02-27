#ifndef _TRANSFORM_COMPONENT_H
#define _TRANSFORM_COMPONENT_H
#include "Engine.h"

class TransformComponent : public Component
{
public:
    int x, y;
    float scaleX, scaleY, rotation;
};

#endif