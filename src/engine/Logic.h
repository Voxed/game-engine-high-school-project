#ifndef _LOGIC_H
#define _LOGIC_H

#include "Core.h"

class Core;
class Logic
{
    Core * core;
public:
    /**
     * @brief Initialize a new logic object
     * 
     * @param core The main core
     */
    Logic(Core * c);
    /**
     * @brief The main update function
     * 
     * Called from the core
     * 
     * @param delta 
     */
    void update(float delta);
};
#endif