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
    Graphics(Core * c, Logic& logic);
    void render();
};
#endif