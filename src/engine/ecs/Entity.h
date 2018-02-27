#ifndef _ENTITY_H
#define _ENTITY_H

#include <map>
#include <memory>
#include "Component.h"
#include "ECS.h"

class Entity
{
    std::map<int, std::unique_ptr<Component>> components;
    Entity* addComponent(int id, Component*);
public:
    Component* getComponentFromID(int componentId);
    int getEntityID();
    template<typename T>
    Entity* addComponent() {return addComponent(getComponentID<T>(), new T);};
    
    template<typename T>
    T* getComponent() {return (T*)getComponentFromID(getComponentID<T>());};  

    template<typename T>
    bool hasComponent() {return getComponent<T>() != nullptr;};
};

#endif