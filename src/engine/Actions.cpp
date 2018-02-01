#include "Actions.h"

std::vector< ActionListener* > Actions::listeners = std::vector< ActionListener* >();

void Actions::addListener(ActionListener* f)
{
    listeners.push_back(f);
}

void Actions::removeListener(ActionListener* f)
{
    listeners.erase(std::remove(listeners.begin(), listeners.end(), f));
}

void Actions::call(Action action, float delta)
{
    for(auto l : listeners)
    {
        l->onAction(action, delta);
    }
}

void ActionListener::onAction(Action action_name, float delta)
{
    printf("WARNING: Un-implemented action listener");
}