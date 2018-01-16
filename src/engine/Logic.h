#ifndef _LOGIC_H
#define _LOGIC_H

#include "Core.h"

class Core;
class Logic
{
    Core * core;
public:
    Logic(Core * c);
    void update(float delta);
};
#endif