#ifndef _ENTITY_COMPONENT_SYSTEM_H
#define _ENTITY_COMPONENT_SYSTEM_H

#include <vector>
#include <memory>
#include <map>

extern unsigned char UPDATE_SYSTEM;
extern unsigned char RENDER_SYSTEM;
extern unsigned char ACTION_SYSTEM;

inline int getUniqueComponentID()
{
    static int lastID = 0;
    return lastID++;
}

template<typename T>
inline int getComponentID()
{
    static int componentID = getUniqueComponentID();
    return componentID;
}

#include "Component.h"
#include "Entity.h"
#include "System.h"
#include "World.h"

#endif