#include "PlayerSystem.h"

void PlayerSystem::update(float delta)
{

}

void PlayerSystem::render(SpriteBatch& b)
{
    //Render all of the players in the world!
    auto entities = world -> getEntities<PlayerComponent>();
    std::remove_if(entities.begin(), entities.end(), [](Entity* e){ return 
        !( e -> hasComponent<TransformComponent>() );
    });

    
}

void PlayerSystem::onAction(Action action, float delta)
{

}