#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <GL/glew.h>

#include "Logic.h"
#include "Shader.h"
#include "Texture.h"

#include "SpriteBatch.h"
#include "Sprite.h"

#include "Core.h"

#include <chrono>
#include <iterator>

class Core;
class Logic;
class Graphics
{
    Texture text;
    Shader shad;

    Logic& logic;
    
    SpriteBatch batch;
    Core * core;
public:
    /**
     * @brief Initialize new graphics object
     * 
     * @param core The main core
     * @param logic The logic object
     */
    Graphics(Core * c, Logic& logic);
    /**
     * @brief The main rendering event
     * 
     * Called from the core
     * 
     */
    void render();
};
#endif