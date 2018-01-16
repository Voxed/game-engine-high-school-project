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

void Actions::call(Action action)
{
    for(auto l : listeners)
    {
        l->onAction(action);
    }
}

void ActionListener::onAction(Action action_name)
{
    printf("WARNING: Un-implemented action listener");
}