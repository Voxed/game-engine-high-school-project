#include "Actions.h"

/**
 * @brief All the current action listeners
 * 
 */
std::vector< ActionListener* > Actions::listeners = std::vector< ActionListener* >();

/**
 * @brief Add an action listener
 * 
 * @param l The action listener to be used
 */
void Actions::addListener(ActionListener* l)
{
    listeners.push_back(l);
}

/**
 * @brief Remove an action listener
 * 
 * @param l The action listener to be removed
 */
void Actions::removeListener(ActionListener* l)
{
    listeners.erase(std::remove(listeners.begin(), listeners.end(), f));
}

/**
 * @brief Call an action
 * 
 * @param action Action
 * @param delta The current update delta
 */
void Actions::call(Action action, float delta)
{
    for(auto l : listeners)
    {
        l->onAction(action, delta);
    }
}

/**
 * @brief The action event.
 * 
 * Gets called every time an action is called
 * 
 * @param action The action that was called
 * @param delta The current update delta
 */
void ActionListener::onAction(Action action, float delta)
{
    printf("Un-implemented action listener");
}