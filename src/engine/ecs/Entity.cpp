#include "Entity.h"

Entity* Entity::addComponent(int id, Component* c)
{  
    components.insert(std::make_pair(id, std::unique_ptr<Component>(c)));
    return this;
}

Component* Entity::getComponentFromID(int componentID)
{
    std::map<int, std::unique_ptr<Component>>::iterator ci;
    if( (ci = components.find(componentID)) != components.end() )
    {
        return ci->second.get();
    }
    else
    {
        return nullptr;
    }
}

