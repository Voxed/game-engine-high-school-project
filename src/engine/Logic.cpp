#include "Logic.h"

Logic::Logic(Core * core)
{
    this->core = core;
}

void Logic::update(float delta)
{
    core->getScreen()->update(delta);
}