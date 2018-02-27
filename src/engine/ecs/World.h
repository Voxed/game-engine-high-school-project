#ifndef _WORLD_H
#define _WORLD_H

#include <map>
#include <memory>
#include <type_traits>
#include "System.h"
#include "ECS.h"
#include "../SpriteBatch.h"
#include "../Actions.h"

class System;
class Entity;
class World
{
    std::map<int, std::unique_ptr<System>> systems;
    std::map<int, std::unique_ptr<Entity>> entities;
    std::vector<int> renderSystems;
    std::vector<int> updateSystems;
    std::vector<int> actionSystems;
    void addSystem(System*, unsigned char systems);
    int lastSystemID = 0;
    int lastEntityID = 0;

    std::vector<Entity*> getEntities(int component_id);
public:
    template<typename T>
    void addSystem(unsigned char systems) {
        addSystem(new T, systems);
    }
    void render(SpriteBatch& b);
    void update(float delta);
    void emitAction(Action action, float delta);

    Entity* spawnEntity();
    std::vector<Entity*> getEntities();
    template<typename T>
    std::vector<Entity*> getEntities(){ return getEntities(getComponentID<T>()); };
};

#endif