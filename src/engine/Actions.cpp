#include "Actions.h"

std::vector< ActionListener* > Actions::listeners = std::vector< ActionListener* >();

void Actions::addListener(ActionListener* l)
{
    listeners.push_back(l);
}

void Actions::removeListener(ActionListener* l)
{
    listeners.erase(std::remove(listeners.begin(), listeners.end(), l));
}

void Actions::call(Action action, float delta)
{
    for(auto l : listeners)
    {
        l->onAction(action, delta);
    }
}

void ActionListener::onAction(Action action, float delta)
{
    printf("Un-implemented action listener");
}