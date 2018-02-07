#include "Logic.h"

/**
 * @brief Initialize a new logic object
 * 
 * @param core The main core
 */
Logic::Logic(Core * core)
{
    this->core = core;
}

/**
 * @brief The main update function
 * 
 * Called from the core
 * 
 * @param delta 
 */
void Logic::update(float delta)
{
    core->getScreen()->update(delta);
}