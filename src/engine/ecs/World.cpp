#include "World.h"

void World::addSystem(System* sys, unsigned char systems)
{
    lastSystemID++;
    this -> systems.insert(std::make_pair(lastSystemID, std::unique_ptr<System>(sys)));
    if(systems & UPDATE_SYSTEM) updateSystems.push_back(lastSystemID);
    if(systems & RENDER_SYSTEM) renderSystems.push_back(lastSystemID);
    if(systems & ACTION_SYSTEM) actionSystems.push_back(lastSystemID);
    sys -> world = this;
}

void World::render(SpriteBatch& b)
{
    for(int i : renderSystems)
    {
        systems.find(i) -> second.get() -> render(b);
    }
}

void World::update(float delta)
{
    for(int i : updateSystems)
    {
        systems.find(i) -> second.get() -> update(delta);
    }
}

void World::emitAction(Action action, float delta)
{
    for(int i : actionSystems)
    {
        systems.find(i) -> second.get() -> onAction(action, delta);
    }
}

Entity* World::spawnEntity()
{
    int id = lastEntityID++;
    entities.insert(std::make_pair(id, std::unique_ptr<Entity>(new Entity)));
    return entities.find(id) -> second.get();
}

std::vector<Entity*> World::getEntities()
{
    std::vector<Entity*> entities;
    for(auto& e : this -> entities)
    { 
        entities.push_back(e.second.get());
    }
    return entities;
}

std::vector<Entity*> World::getEntities(int component_id)
{
    std::vector<Entity*> filteredEntities;
    for(auto& e : this -> entities)
    { 
        if( e.second -> getComponentFromID(component_id) != nullptr)
            filteredEntities.push_back(e.second.get());
    }
    return filteredEntities;
}